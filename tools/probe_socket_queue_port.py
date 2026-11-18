#!/usr/bin/env python3
"""Compare the socket port's test stream against the original GPOE8P DOL with Unicorn."""
import argparse
from dataclasses import dataclass, field
import hashlib
from pathlib import Path
import random
import struct
import subprocess

from unicorn import Uc, UC_ARCH_PPC, UC_HOOK_CODE, UC_MODE_BIG_ENDIAN, UC_MODE_PPC32
from unicorn import ppc_const as ppc

from audit_loader_payload_provenance import ORIGINAL_SHA1, parse_dol


TCB, PACKET, STACK, DATA, RING = 0x81100000, 0x81101000, 0x81110000, 0x81120000, 0x81130000
GATHER, ACK, SACK = 0x80420410, 0x8041FFF8, 0x8041FED4
STREAM_OP = {GATHER: 0, ACK: 1, SACK: 2}
COMPLETE_REQUEST, WAKE = 0x804220A0, 0x8042276C
STOP = 0x80001000
FLAG = 0x204
SLOTS = 65

# Fields touched by the fixtures and queue routines. Carry the remaining TCB
# bytes, padding and descriptor kind bytes through the comparison verbatim.
FRAGMENT_FORMAT = "H2sI4s"
PACKET_FORMAT = "H2sII" + FRAGMENT_FORMAT * 12
REQUEST_FORMAT = "I4sHHI"
TCB_FORMAT = (
    "16sI4sI4sIII" + PACKET_FORMAT
    + "50sh64I"  # last_reasm and 32 reassembly ranges
    + "II244s10I"  # completion callbacks and five SACK ranges
    + "528sI16s"  # independent scoreboard state and FIFO capacity
)
RECORD_FORMATS = {
    "control": TCB_FORMAT,
    "packet": PACKET_FORMAT,
    "ring": REQUEST_FORMAT * SLOTS,
    "event": "IIII" + REQUEST_FORMAT,
}
BIG = {name: struct.Struct(">" + fmt) for name, fmt in RECORD_FORMATS.items()}
assert BIG["control"].size == 0x544 and BIG["packet"].size == 0x9C
assert BIG["ring"].size == SLOTS * 16 and BIG["event"].size == 32
RAM_REF = b"\x01\0\0\0"


@dataclass
class Case:
    operation: int
    offset: int = 0
    length: int = 0
    reenter: bool = False
    control: bytearray = field(default_factory=lambda: bytearray(0x544))
    packet: bytes = bytes(0x9C)
    ring: bytearray = field(default_factory=lambda: bytearray(SLOTS * 16))
    data: bytes = bytes(8192)

    def init_ring(self, head, lengths, stride, rng=None):
        struct.pack_into(">I4s", self.control, 0x10, RING, RAM_REF)
        struct.pack_into(">II", self.control, 0x20, len(lengths), head)
        self.control[FLAG] = 0x80
        for index, length in enumerate(lengths):
            slot = (head + index) % SLOTS
            offset = rng.randrange(8) if rng is not None else 0
            callback = 0 if rng is not None else index + 1
            struct.pack_into(">I4sHHI", self.ring, 16 * slot,
                             DATA + stride * index, RAM_REF, length, offset, callback)

    def init_fifo(self, capacity, head, occupancy, lengths, base, stride):
        struct.pack_into(">I4s", self.control, 0x10, DATA, RAM_REF)
        struct.pack_into(">II", self.control, 0x20, occupancy, head)
        struct.pack_into(">II", self.control, 0x30, len(lengths), sum(lengths))
        struct.pack_into(">I", self.control, 0x530, capacity)
        for index, length in enumerate(lengths):
            struct.pack_into(">H2xI4s", self.control, 0x38 + 12 * index,
                             length, DATA + base + stride * index, RAM_REF)


def gather_case(rng, queued):
    case = Case(GATHER)
    lengths = [rng.randrange(1, 48) for _ in range(rng.randrange(1, 9))]
    total = sum(lengths)
    if queued:
        case.init_ring(rng.randrange(SLOTS), lengths, 512, rng)
    else:
        occupancy = rng.randrange(129)
        case.init_fifo(128, rng.randrange(128), occupancy, lengths, 4096, 512)
        total += occupancy
    case.offset = rng.randrange(total)
    case.length = rng.randrange(1, total - case.offset + 1)
    return case


def ack_case(rng, queued, index):
    case = Case(ACK, data=rng.randbytes(8192))
    lengths = [rng.randrange(1, 28) for _ in range(rng.randrange(1, 8))]
    if queued:
        case.init_ring(rng.randrange(SLOTS), lengths, 64)
        struct.pack_into(">I", case.control, 0x34, sum(lengths))
        case.reenter = index % 4 == 0 and len(lengths) > 1
        if case.reenter:
            case.length = lengths[0] + rng.randrange(lengths[1])
        else:
            case.length = rng.randrange(sum(lengths) + 1)
    else:
        head = rng.randrange(96)
        occupancy = rng.randrange(97)
        case.init_fifo(96, head, occupancy, lengths, 1024, 64)
        struct.pack_into(">I", case.control, 0x28, (head + occupancy) % 96)
        struct.pack_into(">I", case.control, 0x1FC, 1)
        case.length = rng.randrange(occupancy + sum(lengths) + 1)
    return case


def sack_case(rng, index):
    case = Case(SACK)
    latest = index % 33 - 1
    struct.pack_into(">h", case.control, 0xFA, latest)
    base = 0xFFFFFFF0 if index % 2 else rng.getrandbits(32)

    def put_range(offset):
        start = (base + rng.randrange(128)) & 0xFFFFFFFF
        end = (start + rng.randrange(32)) & 0xFFFFFFFF
        struct.pack_into(">II", case.control, offset, start, end)

    for i in range(32):
        put_range(0xFC + 8 * i)
    for i in range(5):
        put_range(0x2F8 + 8 * i)
    case.control[0x320:0x328] = rng.randbytes(8)
    if index == 1:
        struct.pack_into(">II", case.control, 0xFC, 100, 160)
        struct.pack_into(">II", case.control, 0x2F8, 110, 120)
    return case


class Retail:
    def __init__(self, path):
        dol = path.read_bytes()
        if hashlib.sha1(dol).hexdigest() != ORIGINAL_SHA1:
            raise ValueError(f"Expected GPOE8P Rev 2 PsoV3.dol at {path}")
        self.cpu = Uc(UC_ARCH_PPC, UC_MODE_BIG_ENDIAN | UC_MODE_PPC32)
        self.cpu.mem_map(0x80000000, 0x700000)
        self.cpu.mem_map(TCB, 0x40000)
        for section in parse_dol(dol)["sections"]:
            offset = section["offset"]
            self.cpu.mem_write(section["address"], dol[offset:offset + section["size"]])
        self.cpu.reg_write(ppc.UC_PPC_REG_2, 0x805DFD00)
        self.cpu.reg_write(ppc.UC_PPC_REG_13, 0x805DA600)
        self.cpu.mem_write(0x805C1D48, struct.pack(">I", TCB))
        for address in (COMPLETE_REQUEST, WAKE):
            self.cpu.hook_add(UC_HOOK_CODE, self.notify, begin=address, end=address)
        self.events = []
        self.reenter = False

    def notify(self, cpu, address, size, user_data):
        is_request = address == COMPLETE_REQUEST
        args = [cpu.reg_read(reg) for reg in (ppc.UC_PPC_REG_3, ppc.UC_PPC_REG_4, ppc.UC_PPC_REG_5)]
        request = cpu.mem_read(cpu.reg_read(ppc.UC_PPC_REG_6), 16) if is_request else bytes(16)
        self.events.append(struct.pack(">4I", 1 if is_request else 2, *args) + request)
        if is_request and self.reenter and len(self.events) == 1:
            count, head = struct.unpack(">II", cpu.mem_read(TCB + 0x20, 8))
            if count:
                next_head = (head + 17) % SLOTS
                record = bytes(cpu.mem_read(RING + 16 * head, 16))
                cpu.mem_write(RING + 16 * next_head, record)
                cpu.mem_write(TCB + 0x24, struct.pack(">I", next_head))
        cpu.reg_write(ppc.UC_PPC_REG_3, 0)
        cpu.reg_write(ppc.UC_PPC_REG_PC, cpu.reg_read(ppc.UC_PPC_REG_LR))

    def run(self, case):
        cpu = self.cpu
        for address, region in ((TCB, case.control), (PACKET, case.packet), (RING, case.ring), (DATA, case.data)):
            cpu.mem_write(address, bytes(region))
        self.events.clear()
        self.reenter = case.reenter
        if case.operation == GATHER:
            args = (case.offset, case.length, PACKET, TCB)
        elif case.operation == ACK:
            args = (case.length, TCB)
        else:
            args = (TCB,)
        for reg, value in zip((ppc.UC_PPC_REG_3, ppc.UC_PPC_REG_4, ppc.UC_PPC_REG_5, ppc.UC_PPC_REG_6), args):
            cpu.reg_write(reg, value)
        cpu.reg_write(ppc.UC_PPC_REG_1, STACK)
        cpu.reg_write(ppc.UC_PPC_REG_LR, STOP)
        cpu.emu_start(case.operation, STOP, count=50_000)
        if cpu.reg_read(ppc.UC_PPC_REG_PC) != STOP or (case.operation != SACK and cpu.reg_read(ppc.UC_PPC_REG_3) != 0):
            raise AssertionError("Retail routine did not return success on a valid fixture")
        packet = cpu.mem_read(PACKET, len(case.packet))
        if case.operation == GATHER:
            count, length = struct.unpack_from(">II", packet, 4)
            if not (0 < count <= 12 and length == case.length):
                raise AssertionError("Retail packet has unexpected fragment count or byte total")
        return (cpu.mem_read(TCB, len(case.control)), packet, cpu.mem_read(RING, len(case.ring)),
                cpu.mem_read(DATA, len(case.data)))


def read_exact(pipe, size):
    data = pipe.read(size)
    if len(data) != size:
        raise EOFError(f"Port returned {len(data)} bytes, expected {size}")
    return data


class Port:
    def __init__(self, process):
        self.process = process
        marker = read_exact(process.stdout, 4)
        try:
            self.endian = {b"\x01\x02\x03\x04": ">", b"\x04\x03\x02\x01": "<"}[marker]
        except KeyError:
            raise ValueError(f"Invalid port stream marker {marker.hex()}") from None
        self.native = {name: struct.Struct(self.endian + fmt) for name, fmt in RECORD_FORMATS.items()}

    def encode(self, record, data):
        return self.native[record].pack(*BIG[record].unpack(data))

    def check(self, case, retail, label):
        control, packet, ring, data = retail.run(case)
        input_control = case.control.copy()
        flags = input_control[FLAG] >> 7 | (2 if case.reenter else 0)
        input_control[FLAG] &= 0x7F
        args = struct.pack(self.endian + "4I", flags, STREAM_OP[case.operation], case.offset, case.length)
        self.process.stdin.write(b"".join((args, self.encode("control", input_control),
                                          self.encode("packet", case.packet), self.encode("ring", case.ring), case.data)))
        self.process.stdin.flush()

        expected_status = struct.pack(self.endian + "2I", 0, control[FLAG] >> 7)
        control[FLAG] &= 0x7F
        regions = (
            ("status and queued flag", expected_status),
            ("control block", self.encode("control", control)),
            ("packet", self.encode("packet", packet)),
            ("ring", self.encode("ring", ring)),
            ("data", data),
            ("event count", struct.pack(self.endian + "I", len(retail.events))),
        )
        for name, expected in regions:
            self.compare(name, expected, label)
        for i, event in enumerate(retail.events):
            self.compare(f"event {i}", self.encode("event", event), label)

    def compare(self, name, expected, label):
        got = read_exact(self.process.stdout, len(expected))
        if got != expected:
            offset = next(i for i, (a, b) in enumerate(zip(got, expected)) if a != b)
            raise AssertionError(f"{label} {name}+{offset:#x}: port {got[offset]:#04x}, retail {expected[offset]:#04x}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dol", type=Path, required=True)
    parser.add_argument("command", nargs=argparse.REMAINDER, help="after --, port binary and any emulator prefix")
    args = parser.parse_args()
    command = args.command[1:] if args.command[:1] == ["--"] else args.command
    if not command:
        parser.error("provide the port executable after --")
    retail = Retail(args.dol)
    with subprocess.Popen([*command, "--stream"], stdin=subprocess.PIPE, stdout=subprocess.PIPE) as process:
        try:
            port = Port(process)
            for operation, seed, count in ((GATHER, 457, 1200), (ACK, 1457, 800)):
                rng = random.Random(seed)
                for queued in (True, False):
                    name = ("gather" if operation == GATHER else "ACK") + (" queued" if queued else " FIFO")
                    event_count = 0
                    for i in range(count):
                        case = gather_case(rng, queued) if operation == GATHER else ack_case(rng, queued, i)
                        port.check(case, retail, f"{name} case {i}")
                        event_count += len(retail.events)
                    print(f"{name}: {count} comparisons passed, {event_count} completion events", flush=True)
            rng = random.Random(2457)
            for i in range(1024):
                port.check(sack_case(rng, i), retail, f"SACK case {i}")
            print("SACK: 1024 complete connection-record comparisons passed", flush=True)
            process.stdin.close()
            if process.stdout.read(1):
                raise ValueError("Unexpected output after the last case")
            if process.wait() != 0:
                raise RuntimeError(f"Port exited with status {process.returncode}")
        except BaseException:
            process.kill()
            raise


if __name__ == "__main__":
    main()
