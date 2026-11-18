#!/usr/bin/env python3
"""Trace SACK compaction in the three GPOE8P disc DOLs with Unicorn 2.1.4."""
import argparse
import hashlib
from pathlib import Path
import struct

from unicorn import Uc, UC_ARCH_PPC, UC_HOOK_MEM_READ, UC_MODE_BIG_ENDIAN, UC_MODE_PPC32
from unicorn import ppc_const as ppc

from audit_loader_payload_provenance import ORIGINAL_SHA1, parse_dol


TCB = 0x81100000
STOP = 0x80001000
GAME_ENTRY = 0x8041FED4
# Executable, SHA-1, entry, and the two PCs that read the adjacent fields.
DISC_BUILDS = (
    ("PsoV3.dol", ORIGINAL_SHA1, GAME_ENTRY, (0x8041FF9C, 0x8041FFA4)),
    ("iwanaga.dol", "4fbc45e48519f07b9b161debf0078db24c5aa24c",
     0x80152994, (0x80152A5C, 0x80152A64)),
    ("iwanagaD.dol", "0fc3904718e56689b248ade22ba8ee1327b0a0e2",
     0x8016B4EC, (0x8016B640, 0x8016B644)),
)


def check_compaction(path, expected_hash, entry, read_pcs):
    dol = path.read_bytes()
    digest = hashlib.sha1(dol).hexdigest()
    if expected_hash is not None and digest != expected_hash:
        raise ValueError(f"{path.name} has unexpected SHA-1 {digest}")
    cpu = Uc(UC_ARCH_PPC, UC_MODE_PPC32 | UC_MODE_BIG_ENDIAN)
    cpu.mem_map(0x80000000, 0x700000)
    for section in parse_dol(dol)["sections"]:
        offset = section["offset"]
        cpu.mem_write(section["address"], dol[offset:offset + section["size"]])
    cpu.mem_map(TCB, 0x10000)
    state = bytearray(0x544)
    struct.pack_into(">II", state, 0xFC, 100, 160)  # New reassembly range.
    struct.pack_into(">II", state, 0x2F8, 110, 120)  # Existing SACK inside it.
    struct.pack_into(">II", state, 0x320, 0xFFFF0000, 0x12345678)
    cpu.mem_write(TCB, bytes(state))
    cpu.reg_write(ppc.UC_PPC_REG_1, TCB + 0x8000)
    cpu.reg_write(ppc.UC_PPC_REG_3, TCB)
    cpu.reg_write(ppc.UC_PPC_REG_LR, STOP)
    reads = []

    def record_read(emu, access, address, size, value, data):
        reads.append((emu.reg_read(ppc.UC_PPC_REG_PC), address - TCB, size))

    cpu.hook_add(UC_HOOK_MEM_READ, record_read, begin=TCB + 0x320, end=TCB + 0x327)
    cpu.emu_start(entry, STOP, count=10_000)
    if cpu.reg_read(ppc.UC_PPC_REG_PC) != STOP:
        raise AssertionError(f"{path.name} did not return")
    expected_reads = [(pc, offset, 4) for pc, offset in zip(read_pcs, (0x320, 0x324))]
    if reads != expected_reads:
        raise AssertionError(f"{path.name} has unexpected reads {reads!r}")
    struct.pack_into(">II", state, 0x2F8, 100, 160)
    if cpu.mem_read(TCB, len(state)) != state:
        raise AssertionError(f"{path.name} produced an unexpected control block")
    print(f"{path.name} {digest} at {entry:#x} passed. Adjacent-field reads: {len(reads)}")
    for pc, offset, size in reads:
        print(f"  {pc:#x} read {size} bytes at TCB+{offset:#x}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("directory", type=Path, help="directory containing the three disc DOLs")
    parser.add_argument("--candidate", type=Path, help="also check the bounded game's linked DOL")
    args = parser.parse_args()
    for name, digest, entry, pcs in DISC_BUILDS:
        check_compaction(args.directory / name, digest, entry, pcs)
    if args.candidate is not None:
        check_compaction(args.candidate, None, GAME_ENTRY, ())


if __name__ == "__main__":
    main()
