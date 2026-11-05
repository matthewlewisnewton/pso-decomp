#!/usr/bin/env python3
"""Fold MWCC's split .bss locals back into the DOL's global symbols.

TLobby_801461EC.cpp keeps the small adjacent arrays the original compiler
pooled through one base register. Those locals are not symbols in the DOL, so
objdiff attributes the pool immediates to the wrong name and the .bss section
misses. This rewrites the object after compile:

- relocations of the compiler anchor ``...bss.0`` point at ``lbl_8050C0A8``
- each global .bss object grows to the next global (the locals sit in the gaps)
- the local .bss symbols are dropped

Instruction bytes are left alone. Running it again is a no-op.
"""

import struct
import sys

ANCHOR = "...bss.0"


def _shdrs(data):
    e_shoff = struct.unpack_from(">I", data, 32)[0]
    e_shentsize = struct.unpack_from(">H", data, 46)[0]
    e_shnum = struct.unpack_from(">H", data, 48)[0]
    e_shstrndx = struct.unpack_from(">H", data, 50)[0]
    hdrs = []
    for i in range(e_shnum):
        off = e_shoff + i * e_shentsize
        hdrs.append(struct.unpack_from(">IIIIIIIIII", data, off))
    return hdrs, e_shstrndx


def _name(data, strtab_off, n):
    end = data.index(b"\0", strtab_off + n)
    return data[strtab_off + n : end].decode()


def main(path):
    data = bytearray(open(path, "rb").read())
    if data[:4] != b"\x7fELF":
        sys.exit(f"{path}: not an ELF")
    hdrs, shstrndx = _shdrs(data)
    shstr = hdrs[shstrndx][4]
    sections = [(_name(data, shstr, h[0]), h) for h in hdrs]
    by_name = dict(sections)
    sym_off, sym_size, sym_entsize, str_link = (
        by_name[".symtab"][4],
        by_name[".symtab"][5],
        by_name[".symtab"][9],
        by_name[".symtab"][6],
    )
    str_off = hdrs[str_link][4]
    bss_index = next(i for i, (name, _) in enumerate(sections) if name == ".bss")
    bss_size = hdrs[bss_index][5]
    nsyms = sym_size // sym_entsize

    def read_sym(i):
        o = sym_off + i * sym_entsize
        st_name, st_value, st_size, st_info, st_other, st_shndx = struct.unpack_from(
            ">IIIBBH", data, o
        )
        return o, st_name, st_value, st_size, st_info, st_other, st_shndx, _name(data, str_off, st_name)

    anchor = c0a8 = None
    for i in range(nsyms):
        _, _, _, _, _, _, _, name = read_sym(i)
        if name == ANCHOR:
            anchor = i
        elif name == "lbl_8050C0A8":
            c0a8 = i
    if anchor is None:
        return 0
    if c0a8 is None:
        sys.exit(f"{path}: {ANCHOR} present but lbl_8050C0A8 is missing")

    for name, h in sections:
        if not name.startswith(".rela"):
            continue
        roff, rsize, rentsize = h[4], h[5], h[9]
        for i in range(rsize // rentsize):
            o = roff + i * rentsize
            r_info = struct.unpack_from(">I", data, o + 4)[0]
            if (r_info >> 8) == anchor:
                struct.pack_into(">I", data, o + 4, (c0a8 << 8) | (r_info & 0xFF))

    globals_in_bss = []
    locals_in_bss = []
    for i in range(nsyms):
        o, st_name, st_value, st_size, st_info, st_other, st_shndx, name = read_sym(i)
        if st_shndx != bss_index:
            continue
        bind, typ = st_info >> 4, st_info & 0xF
        if bind == 1 and typ == 1:  # STB_GLOBAL, STT_OBJECT
            globals_in_bss.append((st_value, o, name))
        elif bind == 0 and typ in (0, 1):
            locals_in_bss.append(o)
    globals_in_bss.sort()
    for i, (value, o, name) in enumerate(globals_in_bss):
        end = globals_in_bss[i + 1][0] if i + 1 < len(globals_in_bss) else bss_size
        struct.pack_into(">I", data, o + 8, end - value)
    for o in locals_in_bss:
        struct.pack_into(">IIIBBH", data, o, 0, 0, 0, 0, 0, 0)
    open(path, "wb").write(data)
    return 0


if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <object>")
    sys.exit(main(sys.argv[1]))
