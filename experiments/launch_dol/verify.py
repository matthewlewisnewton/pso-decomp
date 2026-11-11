#!/usr/bin/env python3
"""Compare the complete 332-byte probe to the pinned DOL, resolving its calls.

This is a private-input byte comparison, not a function-boundary or linkage
approval. It writes no binary/disassembly output and does not modify metadata.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import struct

ROOT = Path(__file__).resolve().parents[2]
START, SIZE = 0x8042E8C4, 332
ORIGINAL_SHA1 = "0d85744b51d7379efb025a943d0cd5aaae2191a3"


def require(condition, message):
    if not condition:
        raise ValueError(message)


def cstring(data, offset):
    return data[offset:data.index(b"\0", offset)].decode()


def read_candidate(path):
    data = path.read_bytes()
    require(data[:7] == b"\x7fELF\x01\x02\x01", "expected ELF32 big endian")
    header = struct.unpack_from(">16sHHIIIIIHHHHHH", data)
    require(header[1:3] == (1, 20), "expected relocatable PowerPC object")
    require(header[11] == 40, "unexpected section header size")
    sections = [struct.unpack_from(">IIIIIIIIII", data, header[6] + i * 40)
                for i in range(header[12])]

    def section(index):
        s = sections[index]
        result = data[s[4]:s[4] + s[5]]
        require(len(result) == s[5], "truncated section")
        return result

    names = section(header[13])
    allocated = [(i, s) for i, s in enumerate(sections) if s[2] & 2 and s[5]]
    require(len(allocated) == 1, "expected only one nonempty allocated section")
    text_index, text = allocated[0]
    require(cstring(names, text[0]) == ".text" and text[5] == SIZE
            and text[8] == 4, "expected 332-byte, 4-aligned .text")
    tables = [(i, s) for i, s in enumerate(sections) if s[1] == 2]
    require(len(tables) == 1, "expected one symbol table")
    table_index, table = tables[0]
    require(table[9] == 16 and table[5] % 16 == 0, "invalid symbol table")
    strings = section(table[6])
    symbols = [struct.unpack_from(">IIIBBH", section(table_index), i)
               for i in range(0, table[5], 16)]
    functions = [s for s in symbols if s[5] and s[3] & 15 == 2]
    require(len(functions) == 1, "expected only LaunchDol, with helper inlined")
    function = functions[0]
    require(cstring(strings, function[0]) == "LaunchDol"
            and function[1:4] == (0, SIZE, 0x12)
            and function[5] == text_index, "unexpected LaunchDol definition")

    relocations = []
    for i, s in enumerate(sections):
        require(s[1] != 9, "REL relocations are unsupported")
        if s[1] != 4 or not s[5]:
            continue
        # MWCC also relocates its nonallocated .mwcats compiler metadata.
        if not sections[s[7]][2] & 2:
            continue
        require(s[7] == text_index and s[6] == table_index
                and s[9] == 12 and s[5] % 12 == 0, "unexpected relocation table")
        for pos in range(0, s[5], 12):
            offset, info, addend = struct.unpack_from(">IIi", section(i), pos)
            require(info & 255 == 10 and offset % 4 == 0 and offset <= SIZE - 4,
                    "expected aligned R_PPC_REL24 call")
            relocations.append((offset, cstring(strings, symbols[info >> 8][0]), addend))
    require(len(relocations) == 10 and len({r[0] for r in relocations}) == 10,
            "expected ten distinct call relocations")
    return data, bytearray(section(text_index)), relocations


def verify(candidate, original, symbols_path):
    dol = original.read_bytes()
    require(hashlib.sha1(dol).hexdigest() == ORIGINAL_SHA1, "original DOL hash mismatch")
    expected = None
    for i in range(7):
        offset, address, size = (struct.unpack_from(">I", dol, base + i * 4)[0]
                                 for base in (0, 0x48, 0x90))
        if address <= START and START + SIZE <= address + size:
            start = offset + START - address
            expected = dol[start:start + SIZE]
    require(expected is not None and len(expected) == SIZE, "native text range missing")
    targets = {m[1]: int(m[2], 16) for m in re.finditer(
        r"^(\S+) = \.(?:text|init):(0x[0-9A-Fa-f]+);", symbols_path.read_text(), re.M)}
    data, code, relocations = read_candidate(candidate)
    for offset, name, addend in relocations:
        require(name in targets, "unresolved call target: " + name)
        word = struct.unpack_from(">I", code, offset)[0]
        require(word & 0xFC000003 == 0x48000001, "expected relative linking branch")
        displacement = targets[name] + addend - (START + offset)
        require(displacement % 4 == 0 and -(1 << 25) <= displacement < (1 << 25),
                "call displacement out of range")
        struct.pack_into(">I", code, offset, (word & 0xFC000003) | (displacement & 0x03FFFFFC))
    differences = [hex(START + i) for i in range(0, SIZE, 4)
                   if code[i:i + 4] != expected[i:i + 4]]
    return {
        "original_sha1": ORIGINAL_SHA1,
        "candidate_sha256": hashlib.sha256(data).hexdigest(),
        "native_range": [hex(START), hex(START + SIZE)],
        "bytes": SIZE,
        "relocations": len(relocations),
        "all_relocated_bytes_exact": not differences,
        "differing_word_addresses": differences,
        "boundary_or_linkage_approval": False,
        "runtime_execution": False,
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("candidate", type=Path)
    parser.add_argument("--original", type=Path, default=ROOT / "orig/GPOE8P/files/PsoV3.dol")
    parser.add_argument("--symbols", type=Path, default=ROOT / "config/GPOE8P/psov3/symbols.txt")
    args = parser.parse_args()
    try:
        result = verify(args.candidate, args.original, args.symbols)
    except (OSError, ValueError, IndexError, struct.error) as error:
        parser.exit(2, str(error) + "\n")
    print(json.dumps(result, indent=2))
    return 0 if result["all_relocated_bytes_exact"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
