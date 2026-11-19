#!/usr/bin/env python3
"""Exercise guild-card selection, field access and copying on GPOE8P."""
import argparse
from pathlib import Path
import struct

from gpoe8p_image import GameImage


def check(image):
    game = GameImage(image)
    selected = game.call("get_selected_guild_card_record__Fv")
    entries = game.symbols["com_card_entries"]
    assert selected == game.symbols["selected_guild_card_record"]
    assert entries == selected + 0xBC
    dest = 0x81110010
    guard = bytes(range(8))
    for i in range(8):
        entry = game.call("get_com_card_entry__6TLobbyFi", i)
        assert entry == entries + 0xBC * i
        payload = bytes((17 * j + i) % 256 for j in range(0xBC))
        game.cpu.mem_write(entry, payload)
        for method, offset in [("get_name", 8), ("get_text_19", 0x19),
                               ("get_text_2a", 0x2A), ("get_text_3b", 0x3B)]:
            assert game.call(method + "__15GuildCardRecordFv", entry) == entry + offset
        for method, offset in [("get_id", 0), ("get_serial", 4)]:
            assert game.call(method + "__15GuildCardRecordCFv", entry) == struct.unpack_from(">I", payload, offset)[0]
        game.cpu.mem_write(dest - 8, guard + bytes(0xBC) + guard)
        assert game.call("copy_from__15GuildCardRecordFPC15GuildCardRecord", dest, entry) == dest
        assert game.cpu.mem_read(dest - 8, 0xCC) == guard + payload + guard
        assert game.cpu.mem_read(entry, 0xBC) == payload


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("images", type=Path, nargs="+")
    for path in parser.parse_args().images:
        check(path.read_bytes())
        print(f"{path}: selection, six field accessors and bounded copies passed for all eight cards")
