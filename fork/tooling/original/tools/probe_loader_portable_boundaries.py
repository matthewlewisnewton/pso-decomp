#!/usr/bin/env python3
"""Compare scalar port handlers with original PPC instructions in Unicorn 2.1.4.

Requires a private, hash-checked GPOE8P DOL and the host test executable built
by `make -C ports/tests loader_transfer`. Emits metadata, never original code.
Tests completed instructions with mapped memory, not hardware fault delivery,
cache timing, or the rest of the loader/platform implementation.
"""

import argparse
import hashlib
import json
from pathlib import Path
import random
import struct
import subprocess

import unicorn
from unicorn import Uc, UC_ARCH_PPC, UC_MODE_32, UC_MODE_BIG_ENDIAN, UC_HOOK_MEM_READ
from unicorn import ppc_const as ppc

try:
    from tools.audit_loader_payload_provenance import parse_dol, ORIGINAL_SHA1
except ModuleNotFoundError:
    from audit_loader_payload_provenance import parse_dol, ORIGINAL_SHA1

PCS = tuple(range(0x8042E9EC, 0x8042EA10, 4))
REGS = [getattr(ppc, f"UC_PPC_REG_{i}") for i in range(32)] + [
    ppc.UC_PPC_REG_LR, ppc.UC_PPC_REG_CTR, ppc.UC_PPC_REG_CR,
    ppc.UC_PPC_REG_XER, ppc.UC_PPC_REG_PC,
]
MASK = 0xFFFFFFFF


def compare(dol, runner, samples):
    rng = random.Random(285)
    section = next(s for s in parse_dol(dol)["sections"]
                   if s["address"] <= PCS[0] and PCS[-1] + 4 <= s["address"] + s["size"])
    offset = section["offset"] + PCS[0] - section["address"]
    code = dol[offset:offset + len(PCS) * 4]
    lines, expected = [], []
    for pc in PCS:
        for sample in range(samples):
            uc = Uc(UC_ARCH_PPC, UC_MODE_32 | UC_MODE_BIG_ENDIAN)
            mapped = set()

            def map_word(address):
                page = address & ~0xFFF
                if page not in mapped:
                    uc.mem_map(page, 0x1000)
                    mapped.add(page)

            map_word(PCS[0])
            uc.mem_write(PCS[0], code)
            state = [rng.getrandbits(32) for _ in REGS]
            # Wrap at 2^32, ordinary high memory, and low memory; aligned loads.
            state[1] = (0xFFFFFFE0, 0xFFFFFFF0, 0x81000100, 0)[sample % 4]
            state[26] = (0xFFFFFF20, 0x81100000)[sample % 2]
            # Exercise all four low-bit combinations in each nonlinking branch.
            state[32] = 0x81200000 | (sample % 4)
            state[35] &= 0xE000007F  # Architecturally implemented XER fields.
            state[36] = pc
            memory = {}
            if pc == 0x8042E9EC:
                memory[(state[26] + 0xE0) & MASK] = rng.getrandbits(32)
            elif pc == 0x8042E9FC:
                memory = {(state[1] + 8 + i * 4) & MASK: rng.getrandbits(32) for i in range(6)}
            elif pc == 0x8042EA00:
                memory[(state[1] + 0x24) & MASK] = rng.getrandbits(32)
            for address, value in memory.items():
                map_word(address)
                uc.mem_write(address, struct.pack(">I", value))
            map_word(state[32] & ~3)
            for reg, value in zip(REGS, state):
                uc.reg_write(reg, value)
            if [uc.reg_read(reg) for reg in REGS] != state:
                raise AssertionError("emulator cannot represent input state")
            reads = []

            def read_hook(_uc, _access, address, size, _value, _data):
                if size != 4:
                    raise AssertionError(f"unexpected read size {size}")
                reads.append(address)

            uc.hook_add(UC_HOOK_MEM_READ, read_hook)
            uc.emu_start(pc, 0, count=1)
            result = [uc.reg_read(reg) for reg in REGS]
            # Unicorn 2.1.4 omits lmw read hooks for some mapped addresses.
            # Register results are still emulated. Check hooks when present;
            # otherwise check scalar read order against the ISA expectation.
            if pc == 0x8042E9FC:
                ordered = [(state[1] + 8 + i * 4) & MASK for i in range(6)]
                if reads and reads != ordered:
                    raise AssertionError(f"unexpected lmw reads: {reads}")
                reads = ordered
            # isync is a backend event; emulation cannot validate a host's cache
            # implementation. Verify that the port requests it exactly here.
            expected.append([1] + result + [int(pc == 0x8042E9F0)] + reads)
            pairs = [v for pair in memory.items() for v in pair]
            lines.append(" ".join(map(str, state + [len(memory)] + pairs)))
    run = subprocess.run([str(runner.resolve()), "--stream"], input="\n".join(lines) + "\n",
                         text=True, capture_output=True, check=True)
    actual = [[int(word) for word in line.split()] for line in run.stdout.splitlines()]
    if len(actual) != len(expected):
        raise AssertionError(f"case count differs: {len(actual)} != {len(expected)}")
    for index, (got, want) in enumerate(zip(actual, expected)):
        if got != want:
            pc = PCS[index // samples]
            differences = [(i, a, b) for i, (a, b) in enumerate(zip(got, want)) if a != b]
            raise AssertionError(f"PC {pc:#x} sample {index % samples}: {differences}; "
                                 f"output lengths {len(got)}/{len(want)}")
    return {"passed": True, "cases": len(expected), "instructions": len(PCS),
            "original_sha1": ORIGINAL_SHA1, "unicorn": unicorn.__version__,
            "runner_sha256": hashlib.sha256(runner.read_bytes()).hexdigest(),
            "scope": "original completed-instruction state and lwz reads; scalar lmw read order and isync callback"}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dol", type=Path, required=True)
    parser.add_argument("--runner", type=Path, default=Path("ports/tests/loader_transfer"))
    parser.add_argument("--samples", type=int, default=128)
    args = parser.parse_args()
    if unicorn.__version__ != "2.1.4":
        parser.error("requires unicorn==2.1.4")
    if args.samples < 4:
        parser.error("at least four samples required to cover edge cases")
    dol = args.dol.read_bytes()
    if hashlib.sha1(dol).hexdigest() != ORIGINAL_SHA1:
        parser.error("original DOL hash mismatch")
    print(json.dumps(compare(dol, args.runner, args.samples), indent=2))


if __name__ == "__main__":
    main()
