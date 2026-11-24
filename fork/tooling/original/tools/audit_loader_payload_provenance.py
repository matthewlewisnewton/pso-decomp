#!/usr/bin/env python3
"""Read-only metadata for the pinned retail loader and switcher payload.

This describes file bytes and direct branch encodings, not runtime memory,
successful I/O, a complete call graph, or ownership of the held restore.
No original bytes are emitted. See docs/evidence/launch-dol-stranded-epilogue.md.
"""

import argparse
import hashlib
import json
from pathlib import Path
import struct

try:
    from tools.audit_loader_indirect_targets import ORIGINAL_SHA1, WATCH, direct_target
except ModuleNotFoundError:  # Direct script invocation from the repository root.
    from audit_loader_indirect_targets import ORIGINAL_SHA1, WATCH, direct_target


PAYLOAD_SHA1 = "4b386d2c190b42b5bc3a0c42ec4d3bff08f6d048"
TARGETS = {0x8007F970: "launch_switcher_dol", 0x8042EBA4: "fn_8042EBA4",
           0x8042E8C4: "LaunchDol"}


def overlap(address, size, watched=WATCH):
    """Mathematical half-open ranges; wrapping ranges must be rejected first."""
    return size > 0 and address < watched[1] and watched[0] < address + size


def parse_dol(data):
    if len(data) < 0x100:
        raise ValueError("truncated DOL header")
    word = lambda offset: struct.unpack_from(">I", data, offset)[0]
    sections = []
    for kind, count, off, addr, size in (("text", 7, 0, 0x48, 0x90),
                                         ("data", 11, 0x1C, 0x64, 0xAC)):
        active = True
        for slot in range(count):
            offset, address, length = (word(base + 4 * slot) for base in (off, addr, size))
            # LaunchDol terminates each loop on its first zero file offset.
            active = active and offset != 0
            if offset == 0:
                continue
            if offset < 0x100 or offset + length > len(data):
                raise ValueError("section file extent outside payload")
            if address + length > 0x100000000:
                raise ValueError("wrapping section destination")
            sections.append(dict(kind=kind, slot=slot, offset=offset,
                                 address=address, size=length, loader_active=active))
    bss, length, entry = word(0xD8), word(0xDC), word(0xE0)
    if bss + length > 0x100000000:
        raise ValueError("wrapping BSS destination")
    return dict(sections=sections, bss=dict(address=bss, size=length), entry=entry)


def payload_metadata(data):
    header = parse_dol(data)
    active = [section for section in header["sections"] if section["loader_active"]]
    return dict(
        file_bytes=len(data), sha1=hashlib.sha1(data).hexdigest(),
        sha256=hashlib.sha256(data).hexdigest(), **header,
        entry_in_restore=WATCH[0] <= header["entry"] < WATCH[1],
        entry_in_active_text=any(s["kind"] == "text" and
                                s["address"] <= header["entry"] < s["address"] + s["size"]
                                for s in active),
        active_section_destinations_overlap_restore=any(overlap(s["address"], s["size"]) for s in active),
        bss_overlaps_restore=overlap(**header["bss"]),
        read_full_sectors=len(data) // 2048, read_remainder_bytes=len(data) % 2048,
        limits="File header only. Runtime source selection, successful reading, header preservation, "
               "source-buffer address/aliasing and callbacks are not established.")


def main_metadata(data):
    header = parse_dol(data)
    direct, stored = [], []
    strings = {}
    for section in header["sections"]:
        offset, address, size = (section[key] for key in ("offset", "address", "size"))
        if section["kind"] == "text" and (address % 4 or size % 4):
            raise ValueError("unaligned text range unsupported by instruction scan")
        # Data words are aligned by runtime address, not section-relative offset.
        for pos in range((-address) % 4, size - 3, 4):
            word = struct.unpack_from(">I", data, offset + pos)[0]
            if section["kind"] == "text":
                target = direct_target(word, address + pos)
                if target in TARGETS:
                    direct.append(dict(pc=address + pos, target=target,
                                       target_name=TARGETS[target], link=bool(word & 1)))
            elif word in TARGETS:
                stored.append(dict(address=address + pos, value=word, target_name=TARGETS[word]))
        for label in (0x80438D20, 0x80480404):
            if address <= label < address + size:
                start = offset + label - address
                end = data.find(b"\0", start, min(offset + size, start + 128))
                if end < 0:
                    raise ValueError("unterminated watched filename")
                strings[f"0x{label:08X}"] = data[start:end].decode("ascii")
    return dict(sha1=hashlib.sha1(data).hexdigest(), direct_references=direct,
                aligned_initialized_data_words=stored, watched_filenames=strings,
                limits="Direct branch encodings and aligned initialized-data words only; "
                       "unreachable words, indirect calls and constructed/runtime addresses are unresolved.")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dol", required=True, type=Path)
    parser.add_argument("--payload", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    dol, payload = args.dol.read_bytes(), args.payload.read_bytes()
    for name, data, expected in (("game DOL", dol, ORIGINAL_SHA1),
                                  ("switcher payload", payload, PAYLOAD_SHA1)):
        if hashlib.sha1(data).hexdigest() != expected:
            parser.error(f"{name} SHA-1 does not match the pinned retail input")
    result = dict(game=main_metadata(dol), payload=payload_metadata(payload))
    write_result(args.output, result)
    print(f"Wrote bounded metadata to {args.output}; runtime entry remains unknown.")


def write_result(path, result):
    # Never overwrite a receipt or an input, including through an existing symlink.
    with path.open("x") as handle:
        handle.write(json.dumps(result, indent=2) + "\n")


if __name__ == "__main__":
    main()
