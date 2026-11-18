#!/usr/bin/env python3
"""Compare socket queue behavior and SACK reads in GPOE8P DOLs. Requires Unicorn 2.1.4."""
import argparse
import hashlib
import random
from pathlib import Path
import struct
import sys

from unicorn import Uc, UC_ARCH_PPC, UC_MODE_PPC32, UC_MODE_BIG_ENDIAN, UC_HOOK_CODE, UC_HOOK_MEM_READ
from unicorn import ppc_const as ppc

sys.path.insert(0, str(Path(__file__).resolve().parents[2]))
from tools.audit_loader_payload_provenance import ORIGINAL_SHA1, parse_dol

TCB = 0x81100000
PACKET = TCB + 0x1000
DATA = TCB + 0x20000
QUEUE = TCB + 0x30000
FINISH_REQUEST = 0x804220A0
WAKE_SENDER = 0x8042276C
RETURN = 0x80001000
STATE_SIZE = 0x544
MASK = 0xFFFFFFFF
GAME_SACK = 0x8041FED4
BROWSERS = (
    ("iwanaga.dol", "4fbc45e48519f07b9b161debf0078db24c5aa24c", 0x80152994),
    ("iwanagaD.dol", "0fc3904718e56689b248ade22ba8ee1327b0a0e2", 0x8016B4EC),
)


class Game:
    def __init__(self, path, expected_sha1=None):
        data = path.read_bytes()
        if expected_sha1 and hashlib.sha1(data).hexdigest() != expected_sha1:
            raise ValueError(f"Unexpected input revision at {path}")
        self.cpu = Uc(UC_ARCH_PPC, UC_MODE_PPC32 | UC_MODE_BIG_ENDIAN)
        self.cpu.mem_map(0x80000000, 0x700000)
        self.cpu.mem_map(TCB, 0x40000)
        self.cpu.reg_write(ppc.UC_PPC_REG_2, 0x805DFD00)
        self.cpu.reg_write(ppc.UC_PPC_REG_13, 0x805DA600)
        for section in parse_dol(data)["sections"]:
            start = section["offset"]
            self.cpu.mem_write(section["address"], data[start:start + section["size"]])

    def call(self, entry, *args):
        cpu = self.cpu
        cpu.reg_write(ppc.UC_PPC_REG_1, TCB + 0x8000)
        registers = (ppc.UC_PPC_REG_3, ppc.UC_PPC_REG_4, ppc.UC_PPC_REG_5, ppc.UC_PPC_REG_6)
        for reg, value in zip(registers, args):
            cpu.reg_write(reg, value)
        cpu.reg_write(ppc.UC_PPC_REG_LR, RETURN)
        cpu.emu_start(entry, RETURN, count=20_000)
        if cpu.reg_read(ppc.UC_PPC_REG_PC) != RETURN:
            raise AssertionError(f"Routine at {entry:#x} failed to return")
        return cpu.reg_read(ppc.UC_PPC_REG_3)

    def run(self, entry, state):
        self.cpu.mem_write(TCB, bytes(state))
        self.call(entry, TCB)
        return self.cpu.mem_read(TCB, STATE_SIZE)


def check_sack(game, entry, expected_reads):
    state = bytearray(STATE_SIZE)
    struct.pack_into(">II", state, 0xFC, 100, 160)
    struct.pack_into(">II", state, 0x2F8, 110, 120)
    struct.pack_into(">II", state, 0x320, 0xFFFF0000, 0x12345678)
    reads = []

    def record_read(cpu, access, address, size, value, user_data):
        reads.append((address - TCB, size))

    hook = game.cpu.hook_add(UC_HOOK_MEM_READ, record_read, begin=TCB + 0x320, end=TCB + 0x327)
    try:
        actual = game.run(entry, state)
    finally:
        game.cpu.hook_del(hook)
    struct.pack_into(">II", state, 0x2F8, 100, 160)
    if actual != state or reads != expected_reads:
        raise AssertionError(f"SACK state or access trace differs at {entry:#x}, reads {reads}")


def check_reassembly(original, candidate):
    cases = 0
    for origin in (0x100000, 0x7FFFFFF0, 0xFFFFFFF0):
        for count in (0, 1, 2, 3, 12, 32):
            starts = [origin + 32 * index for index in range(count)]
            positions = [start + offset for start in starts for offset in (0, 2, 23, 24, 27)]
            for position in [origin - 1, *positions, origin + 32 * count]:
                state = bytearray(STATE_SIZE)
                struct.pack_into(">Ihh", state, 0xF4, 24 * count, count - 1, 0 if count else -1)
                for index, start in enumerate(starts):
                    struct.pack_into(">II", state, 0xFC + 8 * index, start & MASK, (start + 24) & MASK)
                struct.pack_into(">I", state, 0x228, position & MASK)
                struct.pack_into(">I", state, 0x534, 4096)
                actual = candidate.run(0x8041F66C, state)
                # Compare sequence positions before truncation for an independent wraparound oracle.
                remaining = sum(start > position for start in starts)
                if actual != original.run(0x8041F66C, state) or (
                    struct.unpack_from(">Ih", actual, 0xF4) != (remaining * 24, remaining - 1)
                ):
                    raise AssertionError(f"Reassembly differs for {count} ranges at {position:#x}")
                cases += 1
    return cases


def send_fixture(rng, queue_mode, lengths, capacity, ring_head=None):
    state = bytearray(STATE_SIZE)
    ring = bytearray(65 * 16)
    struct.pack_into(">IB", state, 0x10, QUEUE if queue_mode else DATA, 1)
    struct.pack_into(">I", state, 0x34, sum(lengths))
    if queue_mode:
        head = rng.randrange(65) if ring_head is None else ring_head
        state[0x204] = 0x80
        struct.pack_into(">II", state, 0x20, len(lengths), head)
        for index, length in enumerate(lengths):
            slot = (head + index) % 65
            struct.pack_into(">IB3xhhI", ring, slot * 16, DATA + 512 * index, 1,
                             length, rng.randrange(8), index + 1)
        return state, ring, 0
    head = rng.randrange(capacity)
    used = rng.randrange(capacity + 1)
    struct.pack_into(">III", state, 0x20, used, head, (head + used) % capacity)
    struct.pack_into(">I", state, 0x530, capacity)
    struct.pack_into(">I", state, 0x30, len(lengths))
    struct.pack_into(">I", state, 0x1FC, 1)
    for index, length in enumerate(lengths):
        struct.pack_into(">h2xIB", state, 0x38 + index * 12, length, DATA + 4096 + 512 * index, 1)
    return state, ring, used


def gather(game, state, ring, offset, length):
    cpu = game.cpu
    cpu.mem_write(TCB, bytes(state))
    cpu.mem_write(QUEUE, bytes(ring))
    cpu.mem_write(PACKET, bytes(0x9C))
    status = game.call(0x80420410, offset, length, PACKET, TCB)
    packet = cpu.mem_read(PACKET, 0x9C)
    count, total = struct.unpack_from(">II", packet, 4)
    if status != 0 or not 0 < count <= 12 or total != length:
        raise AssertionError(f"Unexpected gather result {status}, {count}, {total} for {length} bytes")
    return packet, cpu.mem_read(TCB, len(state)), cpu.mem_read(QUEUE, len(ring))


def acknowledge(game, state, ring, data, amount, reenter):
    cpu = game.cpu
    events = []

    def completion(cpu, address, size, user_data):
        args = tuple(cpu.reg_read(reg) for reg in (ppc.UC_PPC_REG_3, ppc.UC_PPC_REG_4, ppc.UC_PPC_REG_5))
        request = bytes(cpu.mem_read(cpu.reg_read(ppc.UC_PPC_REG_6), 16)) if address == FINISH_REQUEST else b""
        events.append((address, args, request))
        if reenter and address == FINISH_REQUEST and len(events) == 1:
            remaining, head = struct.unpack(">II", cpu.mem_read(TCB + 0x20, 8))
            if remaining:
                next_head = (head + 17) % 65
                cpu.mem_write(QUEUE + next_head * 16, bytes(cpu.mem_read(QUEUE + head * 16, 16)))
                cpu.mem_write(TCB + 0x24, struct.pack(">I", next_head))
        cpu.reg_write(ppc.UC_PPC_REG_3, 0)
        cpu.reg_write(ppc.UC_PPC_REG_PC, cpu.reg_read(ppc.UC_PPC_REG_LR))

    cpu.mem_write(TCB, bytes(state))
    cpu.mem_write(0x805C1D48, struct.pack(">I", TCB))
    cpu.mem_write(QUEUE, bytes(ring))
    cpu.mem_write(DATA, data)
    hooks = [cpu.hook_add(UC_HOOK_CODE, completion, begin=pc, end=pc) for pc in (FINISH_REQUEST, WAKE_SENDER)]
    try:
        status = game.call(0x8041FFF8, amount, TCB)
    finally:
        for hook in hooks:
            cpu.hook_del(hook)
    if status != 0:
        raise AssertionError(f"ACK failed for {amount} bytes")
    return cpu.mem_read(TCB, len(state)), cpu.mem_read(QUEUE, len(ring)), cpu.mem_read(DATA, len(data)), events


def check_send(original, candidate):
    rng = random.Random(457)
    for queue_mode in (True, False):
        for case in range(1200):
            lengths = [rng.randrange(1, 48) for _ in range(rng.randrange(1, 9))]
            state, ring, used = send_fixture(rng, queue_mode, lengths, 128)
            total = used + sum(lengths)
            offset = rng.randrange(total)
            args = state, ring, offset, rng.randrange(1, total - offset + 1)
            if gather(original, *args) != gather(candidate, *args):
                raise AssertionError(f"Gather mismatch, queue mode {queue_mode}, case {case}")
    boundary_cases = 0
    for queue_mode in (True, False):
        for lengths in ([1], [32767], [1] * 12, [32767] * 12, [50, 32767, 2, 7, 32765], [16384] * 6):
            for head in (0, 63, 64) if queue_mode else (0,):
                state, ring, _ = send_fixture(rng, queue_mode, lengths, 96, ring_head=head)
                if not queue_mode:
                    struct.pack_into(">III", state, 0x20, 0, 0, 0)
                total = sum(lengths)
                for offset in sorted({0, total - 1, total // 2}):
                    for size in sorted({1, total - offset, min(32767, total - offset)}):
                        args = state, ring, offset, size
                        if gather(original, *args) != gather(candidate, *args):
                            raise AssertionError(f"Gather boundary mismatch for {lengths}, {offset}, {size}")
                        boundary_cases += 1
    rng = random.Random(1457)
    callbacks = 0
    for queue_mode in (True, False):
        for case in range(800):
            data = rng.randbytes(0x2000)
            lengths = [rng.randrange(1, 28) for _ in range(rng.randrange(1, 8))]
            state, ring, used = send_fixture(rng, queue_mode, lengths, 96)
            reenter = queue_mode and case % 4 == 0 and len(lengths) > 1
            amount = lengths[0] + rng.randrange(lengths[1]) if reenter else rng.randrange(used + sum(lengths) + 1)
            args = state, ring, data, amount, reenter
            actual = acknowledge(candidate, *args)
            if actual != acknowledge(original, *args):
                raise AssertionError(f"ACK mismatch, queue mode {queue_mode}, case {case}")
            callbacks += len(actual[-1])
    print(f"{2400 + boundary_cases:,} gathers and 1,600 ACKs passed, including {callbacks} completion events.")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("original", type=Path, help="original GPOE8P PsoV3.dol")
    parser.add_argument("candidate", type=Path, help="GPOE8P DOL linked with the socket C++ unit")
    parser.add_argument("--browser-dir", type=Path, help="directory containing both extracted browser DOLs")
    args = parser.parse_args()
    original = Game(args.original, ORIGINAL_SHA1)
    candidate = Game(args.candidate)
    retail_reads = [(0x320, 4), (0x324, 4)]
    check_sack(original, GAME_SACK, retail_reads)
    check_sack(candidate, GAME_SACK, [])
    if args.browser_dir:
        for name, expected_sha1, entry in BROWSERS:
            check_sack(Game(args.browser_dir / name, expected_sha1), entry, retail_reads)
    cases = check_reassembly(original, candidate)
    print(f"SACK compaction and {cases} reassembly comparisons passed.")
    check_send(original, candidate)


if __name__ == "__main__":
    main()
