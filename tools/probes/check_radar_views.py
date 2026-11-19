#!/usr/bin/env python3
"""Exercise the camera view layout shared by the three GPOE8P radar modes."""
import argparse
from pathlib import Path
import struct

from unicorn.ppc_const import UC_PPC_REG_6, UC_PPC_REG_7, UC_PPC_REG_FPR1, UC_PPC_REG_MSR

from gpoe8p_image import GameImage


def check(image):
    game = GameImage(image)
    game.cpu.reg_write(UC_PPC_REG_MSR, game.cpu.reg_read(UC_PPC_REG_MSR) | 0x2000)
    camera = game.symbols["camera_world_view"]
    views = game.symbols["TRaderMapCore__map_view_state"]
    original = struct.pack(">6f2i2f", 0, 0, 0, 0, 0, -1, 0, 0x2AAA, -1, -60000)
    guard = b"\xa5" * 4
    for i in range(3):
        address = views + i * 0x28
        game.cpu.mem_write(address - 4, guard + bytes(0x28) + guard)
        game.call("initialize_radar_map_view", address)
        assert game.cpu.mem_read(address - 4, 0x30) == guard + original + guard
        record = struct.pack(">6f2i2f", i, 1, -2, 3, -4, 5, -32768 + i, 16384, 0.125, -8.75)
        game.cpu.mem_write(camera, record)
        game.call("copy_from__17RadarMapViewStateFPC17RadarMapViewState", address, camera)
        assert game.cpu.mem_read(address - 4, 0x30) == guard + record + guard
        assert game.cpu.mem_read(camera, 0x28) == record

    pos = 0x81110010
    count = game.symbols["TRaderMapCore__data_805D5F30"]
    markers = game.symbols["TRaderMapCore__marker_buffer"]
    game.cpu.mem_write(views, struct.pack(">3f", 0, 0, 0))
    # Unicorn lacks the Gekko paired-single register spill and reload. The
    # surrounding stfd/lfd pair preserves scalar f31 for this routine.
    start = game.symbols["add_radar_scaled_gate"]
    for offset, instruction in [(0x10, 0xF3E10038), (0xBC, 0xE3E10038)]:
        assert game.cpu.mem_read(start + offset, 4) == struct.pack(">I", instruction)
        game.cpu.mem_write(start + offset, struct.pack(">I", 0x60000000))

    for used, x, flags, expected in [(0, 300., 0, 1), (1, 301., 0, 0), (127, 301., 1, 1), (128, 0., 1, 0)]:
        game.cpu.mem_write(count, struct.pack(">I", used))
        game.cpu.mem_write(pos, struct.pack(">3f", x, -95., 0))
        before = bytes([0xA5]) * (128 * 20)
        game.cpu.mem_write(markers, before)
        game.cpu.reg_write(UC_PPC_REG_6, 0xFFFFFFFD)
        game.cpu.reg_write(UC_PPC_REG_7, flags)
        game.cpu.reg_write(UC_PPC_REG_FPR1, struct.unpack(">Q", struct.pack(">d", 0.375))[0])
        assert game.call("add_radar_scaled_gate", pos, 0xFF00FF00, 0xFFFF) == expected
        assert game.cpu.mem_read(count, 4) == struct.pack(">I", used + expected)
        after = bytearray(before)
        if expected:
            struct.pack_into(">3fHhI", after, used * 20, x, 0, 0.375, 0xFFFF, -3, 0xFF00FF00)
        assert game.cpu.mem_read(markers, len(before)) == after


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("images", type=Path, nargs="+")
    for path in parser.parse_args().images:
        check(path.read_bytes())
        print(f"{path}: three radar views and four gate distance, flag and capacity cases passed")
