#!/usr/bin/env python3
"""Post-process pso/misc/TNpcPlayer.o.

MWCC schedules init_follow_target's 18.0 vector like the original only when the
source uses a literal, and it then emits a second .rodata copy instead of
lbl_8043FFAC. Point those relocs at the named object and delete the copy.

npc_player_is_small_obstacle lives in .discard so its 12.0f is pooled before
calc_box_escape_axis's 7.0f. Nothing calls it. Clear the section's allocation
flag, and stop counting the helper as a function, so mwld does not fold it
into .text.
"""

import sys


def be(buf, off, n=4):
    return int.from_bytes(buf[off:off + n], "big")


def wbe(buf, off, n, val):
    buf[off:off + n] = val.to_bytes(n, "big")


def load_sections(buf):
    shoff, shentsize, shnum, shstrndx = be(buf, 0x20), be(buf, 0x2E, 2), be(buf, 0x30, 2), be(buf, 0x32, 2)
    shstr_off = shoff + shstrndx * shentsize
    names = buf[be(buf, shstr_off + 16):be(buf, shstr_off + 16) + be(buf, shstr_off + 20)]

    def name_at(no):
        return names[no:names.index(0, no)].decode()

    secs = []
    for i in range(shnum):
        o = shoff + i * shentsize
        secs.append({
            "i": i, "hdr": o, "name": name_at(be(buf, o)), "type": be(buf, o + 4),
            "flags": be(buf, o + 8), "foff": be(buf, o + 16), "size": be(buf, o + 20),
            "link": be(buf, o + 24), "info": be(buf, o + 28), "entsize": be(buf, o + 36),
        })
    return shoff, shentsize, shnum, secs


def main(path):
    orig = bytearray(open(path, "rb").read())
    if orig[:4] != b"\x7fELF":
        sys.exit(f"{path}: not an ELF")
    shoff, shentsize, shnum, secs = load_sections(orig)
    by = {s["name"]: s for s in secs}
    ro = by.get(".rodata")
    symsec = next(s for s in secs if s["type"] == 2)
    strsec = secs[symsec["link"]]
    strtab = bytes(orig[strsec["foff"]:strsec["foff"] + strsec["size"]])

    def sname(no):
        return strtab[no:strtab.index(0, no)].decode()

    syms = []
    for idx, o in enumerate(range(symsec["foff"], symsec["foff"] + symsec["size"], 16)):
        syms.append({
            "idx": idx, "o": o, "name": sname(be(orig, o)), "value": be(orig, o + 4),
            "size": be(orig, o + 8), "info": orig[o + 12], "shndx": be(orig, o + 14, 2),
        })
    idx_of = {s["name"]: s["idx"] for s in syms if s["name"]}
    if "lbl_8043FFAC" not in idx_of:
        sys.exit(f"{path}: missing lbl_8043FFAC")
    ac = next(s for s in syms if s["name"] == "lbl_8043FFAC")
    if ac["shndx"] != ro["i"]:
        sys.exit(f"{path}: lbl_8043FFAC is not in .rodata")
    ac_bytes = bytes(orig[ro["foff"] + ac["value"]:ro["foff"] + ac["value"] + ac["size"]])

    ro_objs = sorted(
        (s for s in syms if s["shndx"] == ro["i"] and s["size"] and s["name"] != "lbl_8043FFAC"),
        key=lambda s: s["value"])
    dup = None
    for s in ro_objs:
        blob = bytes(orig[ro["foff"] + s["value"]:ro["foff"] + s["value"] + s["size"]])
        if blob == ac_bytes:
            dup = s
            break

    cut_at = None
    cut_len = 0
    if dup is not None:
        later = [s["value"] for s in ro_objs if s["value"] > dup["value"]]
        span_end = min(later) if later else ro["size"]
        if span_end <= dup["value"]:
            sys.exit(f"{path}: empty span for {dup['name']}")
        cut_len = span_end - dup["value"]
        cut_at = ro["foff"] + dup["value"]

    if cut_at is None:
        new = bytearray(orig)
        adj = lambda off: off
        new_shoff = shoff
    else:
        new = bytearray(orig[:cut_at] + orig[cut_at + cut_len:])
        def adj(off):
            return off - cut_len if off > cut_at else off
        new_shoff = adj(shoff)
        wbe(new, 0x20, 4, new_shoff)
        for s in secs:
            base = new_shoff + s["i"] * shentsize
            wbe(new, base + 16, 4, adj(s["foff"]))
            if s["name"] == ".rodata":
                wbe(new, base + 20, 4, s["size"] - cut_len)
        # Retarget relocations that named the duplicate, then shift surviving
        # .rodata symbols and drop the duplicate's definition.
        dup_idx = dup["idx"]
        ac_idx = ac["idx"]
        for s in secs:
            if s["type"] != 4:
                continue
            base = adj(s["foff"])
            for k in range(s["size"] // 12):
                o = base + k * 12
                info = be(new, o + 4)
                if (info >> 8) == dup_idx:
                    wbe(new, o + 4, 4, (ac_idx << 8) | (info & 0xFF))
        sym_base = adj(symsec["foff"])
        for s in syms:
            o = sym_base + s["idx"] * 16
            if s["idx"] == dup["idx"]:
                wbe(new, o + 4, 4, 0)
                wbe(new, o + 8, 4, 0)
                new[o + 12] = 0
                wbe(new, o + 14, 2, 0)
            elif s["shndx"] == ro["i"] and s["value"] >= dup["value"] + cut_len:
                wbe(new, o + 4, 4, s["value"] - cut_len)

    # Section names live in .shstrtab; the header table may have moved.
    shoff2 = be(new, 0x20)
    shstrndx = be(new, 0x32, 2)
    shstr_hdr = shoff2 + shstrndx * shentsize
    shstr = new[be(new, shstr_hdr + 16):be(new, shstr_hdr + 16) + be(new, shstr_hdr + 20)]

    def sec_name(i):
        o = shoff2 + i * shentsize
        no = be(new, o)
        return shstr[no:shstr.index(0, no)].decode()

    disc_i = next((i for i in range(shnum) if sec_name(i) == ".discard"), None)
    if disc_i is not None:
        o = shoff2 + disc_i * shentsize
        # Not allocated, so mwld does not fold the helper into .text.
        wbe(new, o + 8, 4, 0)
        sym_base = adj(symsec["foff"])
        for s in syms:
            if s["shndx"] == disc_i and (s["info"] & 0xF) == 2:
                so = sym_base + s["idx"] * 16
                # Keep the definition (relocs in the dead section still name it)
                # but not as a function, so it is not subtracted from .text.
                new[so + 12] = s["info"] & 0xF0

    open(path, "wb").write(new)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <object>")
    main(sys.argv[1])
