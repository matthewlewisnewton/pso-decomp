#!/usr/bin/env python3
"""Expose MWCC conversion-pool objects under the names their splits export.

MWCC emits an int-to-double bias as a local ``.rodata``/``.sdata2`` object
named ``@N``. Per-file compilation cannot make that object global from source:
a named global used by value gets a second pool copy, and the experiments in
``docs/evidence/conversion-pool-constants.md`` found no source or flag that
makes the compiler reuse the pool slot. When the original split exports the
bias and another unit loads it, the link still needs a global definition.

This post-process renames the emitted local pool object to the split's global
name and changes its binding to global. The section bytes and every relocation
in the object are unchanged; only the symbol name and binding differ. Run it
on the compiled object before the link, then link the unit normally.

The script only touches missing non-function objects that
``link_units.conversion_pool_kind`` identifies as one of MWCC's two biases. A
missing symbol without a matching local pool object at the split's section and
offset is an error, not a silent skip.
"""

from __future__ import annotations

import os
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import link_units as lu  # noqa: E402

SRC_DIR = ROOT / "build" / "GPOE8P" / "src"
OBJ_DIR = ROOT / "build" / "GPOE8P" / "obj"
OBJCOPY = ROOT / "build" / "binutils" / ("powerpc-eabi-objcopy.exe" if os.name == "nt" else "powerpc-eabi-objcopy")


def elf_symbols(path: Path) -> list[dict]:
    """Defined and undefined symbols of a big-endian ELF32 PowerPC object."""
    b = path.read_bytes()
    be = lambda o, n=4: int.from_bytes(b[o:o + n], "big")
    if len(b) < 52 or b[:7] != b"\x7fELF\x01\x02\x01":
        raise ValueError(f"{path}: expected ELF32 big-endian object")
    kind, machine = be(16, 2), be(18, 2)
    if kind != 1 or machine != 20:
        raise ValueError(f"{path}: expected relocatable PowerPC object")
    shoff, shentsize, shnum, shstrndx = be(0x20), be(0x2E, 2), be(0x30, 2), be(0x32, 2)
    if shentsize != 40 or not shnum or shoff < 52 or shoff + shnum * 40 > len(b):
        raise ValueError(f"{path}: invalid section table")
    if shstrndx >= shnum:
        raise ValueError(f"{path}: invalid section-name index")
    hdrs = [struct.unpack_from(">10I", b, shoff + i * 40) for i in range(shnum)]
    shstr_off, shstr_size = hdrs[shstrndx][4], hdrs[shstrndx][5]
    if shstr_off + shstr_size > len(b):
        raise ValueError(f"{path}: invalid section-name table")
    shstr = b[shstr_off:shstr_off + shstr_size]

    def section_name(index: int) -> str:
        name_off = hdrs[index][0]
        if name_off >= len(shstr):
            raise ValueError(f"{path}: invalid section name")
        end = shstr.find(b"\0", name_off)
        if end < 0:
            raise ValueError(f"{path}: unterminated section name")
        return shstr[name_off:end].decode("utf-8")

    sections = [
        {
            "name": section_name(i),
            "type": header[1],
            "offset": header[4],
            "size": header[5],
        }
        for i, header in enumerate(hdrs)
    ]
    out = []
    tables = [s for s in sections if s["type"] == 2]
    if len(tables) != 1:
        raise ValueError(f"{path}: expected one symbol table")
    symtab = next(i for i, s in enumerate(sections) if s["type"] == 2)
    link = hdrs[symtab][6]
    if link >= shnum or hdrs[link][1] != 3:
        raise ValueError(f"{path}: invalid symbol string-table link")
    stroff, strsize = hdrs[link][4], hdrs[link][5]
    if stroff + strsize > len(b):
        raise ValueError(f"{path}: invalid symbol string table")
    strtab = b[stroff:stroff + strsize]
    off, size = hdrs[symtab][4], hdrs[symtab][5]
    if size % 16 or off + size > len(b):
        raise ValueError(f"{path}: invalid symbol table")
    for o in range(off + 16, off + size, 16):
        name_off, value, sym_size, info, _, shndx = struct.unpack_from(">IIIBBH", b, o)
        if name_off >= len(strtab):
            raise ValueError(f"{path}: invalid symbol name")
        end = strtab.find(b"\0", name_off)
        if end < 0:
            raise ValueError(f"{path}: unterminated symbol name")
        if shndx == 0:
            section, data = "", b""
        elif shndx < shnum:
            section = sections[shndx]["name"]
            sec_off, sec_size = sections[shndx]["offset"], sections[shndx]["size"]
            if value + sym_size > sec_size or sec_off + value + sym_size > len(b):
                raise ValueError(f"{path}: symbol outside its section")
            data = b[sec_off + value:sec_off + value + sym_size]
        else:
            section, data = "", b""
        out.append({
            "name": strtab[name_off:end].decode("utf-8"),
            "value": value,
            "size": sym_size,
            "bind": info >> 4,
            "type": info & 0xF,
            "section": section,
            "data": data,
        })
    return out


def split_object(compiled: Path) -> Path:
    try:
        rel = compiled.resolve().relative_to(SRC_DIR.resolve())
    except ValueError:
        raise ValueError(f"{compiled}: not under {SRC_DIR}") from None
    return OBJ_DIR / rel


def main(path: str) -> int:
    obj = Path(path)
    if not obj.is_file():
        raise ValueError(f"{obj}: no such object")
    split = split_object(obj)
    if not split.is_file():
        raise ValueError(f"{split}: missing split object")
    compiled = elf_symbols(obj)
    defined = {s["name"] for s in compiled if s["bind"] in (1, 2) and s["section"]}
    renames = []
    for symbol in elf_symbols(split):
        if symbol["bind"] not in (1, 2) or symbol["type"] != 1 or not symbol["section"]:
            continue
        name = symbol["name"]
        if name in defined:
            continue
        kind = lu.conversion_pool_kind(split, name)
        if kind is None:
            continue
        candidates = [
            s for s in compiled
            if s["bind"] == 0 and s["type"] == 1 and s["name"] and s["size"] == 8
            and s["section"] == symbol["section"] and s["value"] == symbol["value"]
            and s["data"] == symbol["data"]
        ]
        if len(candidates) != 1:
            raise ValueError(
                f"{obj}: {name} is a {kind} conversion pool in {symbol['section']}:"
                f"0x{symbol['value']:X}, but the compiled object has {len(candidates)} "
                "matching local pool objects"
            )
        renames.append((candidates[0]["name"], name, kind))
    if not renames:
        return 0
    if not OBJCOPY.is_file():
        raise ValueError(f"{OBJCOPY}: missing binutils objcopy")
    tmp = obj.with_name(obj.name + ".pool-symbols")
    args = [str(OBJCOPY)]
    for local, name, _ in renames:
        args += ["--redefine-sym", f"{local}={name}", "--globalize-symbol", name]
    subprocess.run([*args, str(obj), str(tmp)], check=True)
    os.replace(tmp, obj)
    after = elf_symbols(obj)
    for _, name, kind in renames:
        matches = [s for s in after if s["name"] == name]
        if len(matches) != 1 or matches[0]["bind"] not in (1, 2) or matches[0]["type"] != 1:
            raise ValueError(f"{obj}: failed to expose {name} ({kind} conversion pool)")
    for local, name, kind in renames:
        print(f"{obj}: named {kind} conversion pool {local} as {name}")
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main(sys.argv[1] if len(sys.argv) == 2 else ""))
    except (OSError, ValueError, KeyError, subprocess.CalledProcessError) as exc:
        sys.exit(f"name_pool_symbols: {exc}")
