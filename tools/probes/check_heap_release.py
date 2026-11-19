"""Check the game's nullable heap release, its data-file wrapper and scalar allocation."""
import argparse
from pathlib import Path

from gpoe8p_image import GameImage


def run(dol):
    game = GameImage(dol)
    memory = 0x81110020
    guard = bytes(range(64))
    game.cpu.mem_write(memory - 16, guard)
    game.hook("xfree__FPv", lambda *_: None)
    for entry in ("safe_free__FPv", "free_data_file"):
        game.call(entry, 0)
        assert "xfree__FPv" not in game.calls
        for ptr in (memory, memory + 13):
            game.call(entry, ptr)
            assert [args[0] for args in game.calls["xfree__FPv"]] == [ptr]
        assert game.cpu.mem_read(memory - 16, len(guard)) == guard
    game.hook("xmalloc__FUl", lambda size, *_: memory if size else 0)
    for size in (0, 4, 8, 4096):
        assert game.call("__nw__FUl", size) == (memory if size else 0)
        assert [args[0] for args in game.calls["xmalloc__FUl"]] == [size]


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dol", type=Path)
    run(parser.parse_args().dol.read_bytes())
    print("Heap release, data-file cleanup and scalar allocation passed.")
