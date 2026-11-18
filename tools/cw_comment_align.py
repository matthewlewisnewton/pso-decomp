#!/usr/bin/env python3
"""Set CodeWarrior small-data alignment on one MWCC object.

mwld reads section alignment from the CodeWarrior .comment record, not from
the ELF sh_addralign field. GC/2.6 writes 8 for .sbss and .sdata2 even with
-sdata 4 / -sdata2 4, so a unit whose original small data starts only
4-aligned (0x805D696C, 0x805DECCC) is placed 4 bytes late and every sda21
offset after that shifts. This rewrites the comment record and sh_addralign
for the named sections. It does not change section contents.
"""

import sys
from pathlib import Path

SKIP_NAMES = {"", ".symtab", ".strtab", ".shstrtab", ".comment"}


def _u32(buf: bytes, off: int) -> int:
    return int.from_bytes(buf[off : off + 4], "big")


def _content_sections(buf: bytes) -> list[tuple[int, str, int]]:
    shoff = _u32(buf, 0x20)
    shentsize = int.from_bytes(buf[0x2E:0x30], "big")
    shnum = int.from_bytes(buf[0x30:0x32], "big")
    shstrndx = int.from_bytes(buf[0x32:0x34], "big")
    str_hdr = shoff + shstrndx * shentsize
    stroff, strsize = _u32(buf, str_hdr + 16), _u32(buf, str_hdr + 20)
    shstr = buf[stroff : stroff + strsize]
    out = []
    for index in range(shnum):
        off = shoff + index * shentsize
        name = shstr[_u32(buf, off) :].split(b"\0", 1)[0].decode()
        if name in SKIP_NAMES or name.startswith(".rela"):
            continue
        out.append((off, name, _u32(buf, off + 32)))
    return out


def patch(path: Path, updates: dict[str, int]) -> None:
    buf = bytearray(path.read_bytes())
    if buf[:4] != b"\x7fELF":
        raise SystemExit(f"{path}: not an ELF object")
    sections = _content_sections(buf)
    by_name = {name: (off, align) for off, name, align in sections}
    missing = [name for name in updates if name not in by_name]
    if missing:
        raise SystemExit(f"{path}: no such section: {', '.join(missing)}")

    comment_off = None
    shoff = _u32(buf, 0x20)
    shentsize = int.from_bytes(buf[0x2E:0x30], "big")
    shnum = int.from_bytes(buf[0x30:0x32], "big")
    shstrndx = int.from_bytes(buf[0x32:0x34], "big")
    str_hdr = shoff + shstrndx * shentsize
    stroff, strsize = _u32(buf, str_hdr + 16), _u32(buf, str_hdr + 20)
    shstr = buf[stroff : stroff + strsize]
    for index in range(shnum):
        off = shoff + index * shentsize
        name = shstr[_u32(buf, off) :].split(b"\0", 1)[0].decode()
        if name == ".comment":
            comment_off, comment_size = _u32(buf, off + 16), _u32(buf, off + 20)
            comment = buf[comment_off : comment_off + comment_size]
            break
    else:
        raise SystemExit(f"{path}: no .comment section")

    marker = comment.find(b"CodeWarrior\n")
    if marker < 0:
        raise SystemExit(f"{path}: .comment has no CodeWarrior record")
    # Each recorded section is a little-endian (alignment, 0) pair.
    pattern = b"".join(
        align.to_bytes(4, "little") + b"\x00\x00\x00\x00" for _, _, align in sections
    )
    found = comment.find(pattern, marker)
    if found < 0 or comment.find(pattern, found + 1) >= 0:
        raise SystemExit(f"{path}: CodeWarrior alignment record not unique")

    for name, new_align in updates.items():
        if new_align <= 0 or new_align & (new_align - 1):
            raise SystemExit(f"{name}: alignment must be a power of two, got {new_align}")
        sec_off, _ = by_name[name]
        index = next(i for i, (_, sec_name, _) in enumerate(sections) if sec_name == name)
        pair = comment_off + found + index * 8
        buf[pair : pair + 4] = new_align.to_bytes(4, "little")
        buf[sec_off + 32 : sec_off + 36] = new_align.to_bytes(4, "big")
    path.write_bytes(buf)


def main() -> None:
    if len(sys.argv) < 3:
        raise SystemExit(f"usage: {sys.argv[0]} <object> .section=align ...")
    updates = {}
    for arg in sys.argv[2:]:
        name, _, value = arg.partition("=")
        if not name.startswith(".") or not value:
            raise SystemExit(f"expected .section=align, got {arg!r}")
        updates[name] = int(value, 0)
    patch(Path(sys.argv[1]), updates)


if __name__ == "__main__":
    main()
