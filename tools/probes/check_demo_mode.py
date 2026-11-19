"""Exercise the shared demo-mode predicate with the original camera state."""
import argparse
from pathlib import Path
import struct

from gpoe8p_image import GameImage


def check(dol):
    game = GameImage(dol)
    camera = game.symbols["demo_camera_controller_index"]
    assert game.symbols["lbl_805D4ECA"] == camera + 2
    cases = 0
    for flag in (0, 1, 0x7F, 0x80, 0xFF):
        for index in (-32768, -1, 0, 1, 2, 3, 4, 5, 32767):
            state = b"\x98\x5b" + struct.pack(">hB", index, flag) + b"\xd6\x21\x14"
            game.cpu.mem_write(camera - 2, state)
            expected = int(flag != 0 and index not in (2, 4))
            # Several callers previously passed an unused object in r3.
            for unused_register in (0, 0xFFFFFFFF):
                assert game.call("check_demo_mode__Fv", unused_register) == expected
                assert game.cpu.mem_read(camera - 2, len(state)) == state
                cases += 1
    return cases


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("images", nargs="+", type=Path)
    for path in parser.parse_args().images:
        print(f"{path}: {check(path.read_bytes())} demo-mode cases passed")
