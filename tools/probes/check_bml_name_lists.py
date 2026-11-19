#!/usr/bin/env python3
"""Exercise the GPOE8P BML filename-list loader with simulated file reads."""
import argparse
from pathlib import Path
import struct

from unicorn import ppc_const as ppc

from gpoe8p_image import GameImage


def check(image):
    game = GameImage(image)
    archive = 0x81111000
    arrays = 0x81115000
    models = 0x81116000
    motions = models + 0x100
    calls = []
    allocations = []
    allocator = "mem_alloc" if "mem_alloc" in game.symbols else "__nwa__FUl"

    def allocate(size, *_):
        ptr = arrays + len(allocations) * 0x100
        allocations.append((size, ptr))
        game.cpu.mem_write(ptr, bytes([0xA5]) * size)
        return ptr

    def word(address):
        return struct.unpack(">I", game.cpu.mem_read(address, 4))[0]

    game.hook(allocator, allocate)
    for method in ("load_bin_model", "load_bin_motion"):
        def track(owner, name, index, group=method):
            assert owner == archive
            calls.append((group, name, index))
            return 1
        game.hook(method + "__11BmlResourceFPvl", track)
    acquire = "tmp_buf_use_req__6TLobbyFPCc"
    release = "tmp_buf_release__6TLobbyFPCc"
    game.hook(acquire, lambda *_: 0)
    game.hook(release, lambda *_: 0)
    for kind in (0, 1):
        for model_count, motion_count in [(0, 0), (3, 0), (0, 2), (3, 2)]:
            calls.clear()
            allocations.clear()
            expected_calls = []
            expected_allocations = []
            for count, address, method, stride in [(model_count, models, "load_bin_model", 16),
                                                    (motion_count, motions, "load_bin_motion", 8)]:
                pointers = [address + 0x20 + i * 8 for i in range(count)]
                game.cpu.mem_write(address, struct.pack(">" + "I" * (count + 1), *pointers, 0))
                if count:
                    expected_allocations.append(count * stride)
                if kind == 1:
                    expected_calls.extend((method, pointer, i) for i, pointer in enumerate(pointers))
            game.cpu.mem_write(archive - 4, bytes([0xCC]) * 0x448)
            for reg, val in [(ppc.UC_PPC_REG_6, motions), (ppc.UC_PPC_REG_7, 0),
                             (ppc.UC_PPC_REG_8, 42), (ppc.UC_PPC_REG_9, 0x81114000)]:
                game.cpu.reg_write(reg, val)
            assert game.call("init_from_id_lists__FP11BmlResourcelPPvPPvllPv", archive, kind, models) == archive
            assert [size for size, _ in allocations] == expected_allocations
            assert calls == expected_calls
            assert word(archive) == (0x401 if kind == 1 else 0)
            assert game.cpu.mem_read(archive + 0x18, 0x400) == bytes(0x400)
            assert [word(archive + off) for off in (0x418, 0x41C, 0x420, 0x424, 0x428)] == [0, 0, 42, 0x81114000, 0]
            assert [word(archive + off) for off in (0x434, 0x438, 0x43C)] == [model_count, motion_count, 0]
            for off, count, record in [(0x42C, model_count, bytes(4) + b"\xA5" * 4 + bytes(8)),
                                       (0x430, motion_count, b"\xA5" * 4 + bytes(4))]:
                ptr = word(archive + off)
                assert bool(ptr) == bool(count)
                if count:
                    assert game.cpu.mem_read(ptr, count * len(record)) == record * count
            assert len(game.calls.get(acquire, [])) == len(game.calls.get(release, [])) == kind
            assert word(archive - 4) == word(archive + 0x440) == 0xCCCCCCCC


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("images", nargs="+", type=Path)
    for path in parser.parse_args().images:
        check(path.read_bytes())
        print(f"{path}: eight BML filename-list cases passed")
