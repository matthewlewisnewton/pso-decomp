#!/usr/bin/env python3
"""Exercise GPOE8P's result-window page input and arrow animation."""
import argparse
from pathlib import Path
import struct

from unicorn.ppc_const import UC_PPC_REG_MSR

from gpoe8p_image import GameImage


def check(image):
    game = GameImage(image)
    # The page transition uses the GameCube floating-point unit.
    game.cpu.reg_write(UC_PPC_REG_MSR, game.cpu.reg_read(UC_PPC_REG_MSR) | 0x2000)
    indicator = 0x81110010
    guard = b"\xa5" * 4
    port = 3
    channel = 1
    buttons = game.symbols["controller_input_state"] + channel * 0x50 + 0x20

    def input_channel(client, *_):
        assert client == port
        return channel

    def button_pressed(address, mask, _):
        assert address == buttons and mask in (0x10000, 0x20000, 0x30000)
        return int(bool(pressed & mask))

    game.hook("is_player_input_active", input_channel)
    game.hook("TWindowShortListCtrl__check_controller_button", button_pressed)
    game.hook("play_sound_effect", lambda *_: None)

    cases = 0
    for count in (1, 2, 3, 4, 5):
        for page in range(count):
            for pressed in (0, 0x10000, 0x20000, 0x30000):
                for offset in (-8.0, 0.0, 8.0):
                    before = struct.pack(">bb2sIf", page, count, b"xy", port, offset)
                    game.cpu.mem_write(indicator - 4, guard + before + guard)
                    moved = game.call("handle_list_page_flip_input", indicator)
                    step = (pressed == 0x10000) - (pressed == 0x20000)
                    expected = (page + step) % count
                    assert moved == int(expected != page)
                    sound = game.calls.get("play_sound_effect", [])
                    assert sound == ([(0x54100, 0, 0)] if pressed else [])
                    current, pages, unused, client, arrow = struct.unpack(
                        ">bb2sIf", game.cpu.mem_read(indicator, 12)
                    )
                    assert (current, pages, unused, client) == (expected, count, b"xy", port)
                    target = 10.0 * step if moved else offset * 0.85
                    assert abs(arrow - target) < 1e-6, (arrow, target)
                    assert game.cpu.mem_read(indicator - 4, 4) == guard
                    assert game.cpu.mem_read(indicator + 12, 4) == guard
                    assert game.call("get_type__13PageIndicatorFv", indicator) == expected
                    cases += 1
    return cases


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("images", nargs="+", type=Path)
    for path in parser.parse_args().images:
        print(f"{path}: {check(path.read_bytes())} page-input cases passed")
