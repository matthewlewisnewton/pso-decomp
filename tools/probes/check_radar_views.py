#!/usr/bin/env python3
"""Exercise the camera view layout shared by the three GPOE8P radar modes."""
import argparse
from pathlib import Path
import struct

from unicorn.ppc_const import UC_PPC_REG_MSR

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


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("images", type=Path, nargs="+")
    for path in parser.parse_args().images:
        check(path.read_bytes())
        print(f"{path}: initialization and bounded camera copies passed for all three radar views")
