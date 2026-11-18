#!/usr/bin/env python3
"""Check the player distance helper and Gifoie particle cleanup on a GPOE8P image."""
import argparse
import math
from pathlib import Path
import struct

from unicorn.ppc_const import UC_PPC_REG_FPR1, UC_PPC_REG_MSR

from gpoe8p_image import GameImage


def check_distance(game):
    for value in (-12.5, -0.0, 0.0, 0.03125, 0.5, 1.0, 2.0, 100.0, 65536.0, 1.0e12):
        value, = struct.unpack(">f", struct.pack(">f", value))
        bits, = struct.unpack(">Q", struct.pack(">d", value))
        game.cpu.reg_write(UC_PPC_REG_FPR1, bits)
        game.call("newton_sqrtf")
        result = game.cpu.reg_read(UC_PPC_REG_FPR1)
        actual, = struct.unpack(">d", struct.pack(">Q", result))
        expected = math.sqrt(value) if value > 0 else value
        assert struct.pack(">f", actual) == struct.pack(">f", expected), (value, actual, expected)


def check_orbits(game):
    task, table, particle = 0x81110000, 0x81110100, 0x81110200
    # This storage is the game's array-allocation API. Its name depends on
    # whether the separate allocator recovery is present in the source tree.
    free_array = "__dla__FPv" if "__dla__FPv" in game.symbols else "mem_free"
    calls = []

    def record(symbol):
        def callback(first, *_):
            calls.append((symbol, first))
        return callback

    queue = "queue_destruction__7TObjectFv"
    base = "__dt__7TObjectFv"
    release = "__dl__7TObjectFPv"
    for name in (queue, free_array, base, release):
        game.hook(name, record(name))

    for band, count in enumerate((1, 1, 1, 2, 2, 3)):
        for single in (0, 1):
            emitters = [particle + i * 0x100 for i in range(1 if single else count)]
            for destroy_storage in (-1, 0, 1):
                calls.clear()
                game.cpu.mem_write(task - 4, b"x" * (0x4c + 8))
                game.cpu.mem_write(task + 0x1c, struct.pack(">I", table))
                game.cpu.mem_write(task + 0x44, bytes((band, 9, 0, single)))
                data = struct.pack(f">{len(emitters)}I", *emitters)
                game.cpu.mem_write(table, data)
                game.call("__dt__13TUnk_804CC800Fv", task, destroy_storage)
                expected = [(queue, addr) for addr in emitters] + [(free_array, table), (base, task)]
                if destroy_storage > 0:
                    expected.append((release, task))
                assert calls == expected, (band, single, destroy_storage, calls)
                assert game.cpu.mem_read(table, len(data)) == data
                assert game.cpu.mem_read(task - 4, 4) == game.cpu.mem_read(task + 0x4c, 4) == b"xxxx"


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("images", nargs="+", type=Path)
    for path in parser.parse_args().images:
        image = GameImage(path.read_bytes())
        image.cpu.reg_write(UC_PPC_REG_MSR, image.cpu.reg_read(UC_PPC_REG_MSR) | 0x2000)
        check_distance(image)
        check_orbits(image)
        print(f"{path}: 10 distance inputs and 36 Gifoie cleanup cases passed")
