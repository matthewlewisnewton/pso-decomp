#!/usr/bin/env python3
"""Run the GPOE8P texture-strip builder, collector, scrolling and release code."""
import argparse
from pathlib import Path
import struct

from gpoe8p_image import GameImage


BUILD = "build_tables__17Boss6ScrollStripsFPC14Boss6StripDescl"
SCROLL = "scroll_strips_uv__17Boss6ScrollStripsFll"
FREE = "free_buffer_pairs__17Boss6ScrollStripsFv"
OWNER = 0x81110000
SPECS = OWNER + 0x40
ROOT = OWNER + 0x100
ARCHIVE = OWNER + 0x800
VERTICES = ((11, 3, 6), (12, -8, 260))


def words(*values):
    return struct.pack(f">{len(values)}I", *values)


def halfwords(*values):
    return struct.pack(f">{len(values)}H", *(v & 0xffff for v in values))


def check(image, fail_first_pair):
    game = GameImage(image)
    read = game.cpu.mem_read
    write = game.cpu.mem_write

    def word(addr):
        return struct.unpack(">I", read(addr, 4))[0]

    next_address = OWNER + 0x1000
    allocated = {}
    freed = []
    active_archive = 0
    models = []
    lookups = []

    def allocate(size, is_pair):
        nonlocal next_address, fail_first_pair
        if is_pair:
            assert size == 0x14
            if fail_first_pair:
                fail_first_pair = False
                return 0
        addr = next_address
        next_address += (size + 31) & ~15
        assert addr not in allocated
        allocated[addr] = (size, is_pair)
        write(addr, bytes([0xA5]) * (size + 8))
        return addr

    def release(addr, is_pair):
        assert addr in allocated and allocated[addr][1] == is_pair
        assert addr not in freed
        freed.append(addr)

    def get_model(archive, index, unused):
        assert archive == ARCHIVE
        models.append(index)
        return ROOT

    def find_node(model, index, unused):
        assert model == ROOT
        lookups.append(index)
        return ROOT

    game.hook("get_fish_count__8TObjFishFv", lambda *_: active_archive)
    game.hook("get_bml_model", get_model)
    game.hook("find_model_node__FUll", find_node)
    game.hook("__nw__FUl", lambda n, *_: allocate(n, True))
    game.hook("__nwa__FUl", lambda n, *_: allocate(n, False))
    game.hook("__dl__FPv", lambda addr, *_: release(addr, True))
    game.hook("__dla__FPv", lambda addr, *_: release(addr, False))

    sentinel = bytes([0xCC]) * 0x14
    write(OWNER, sentinel)
    game.call(BUILD, OWNER, SPECS, 2)
    active_archive = ARCHIVE
    for specs, count in ((0, 2), (SPECS, 0), (SPECS, -1)):
        game.call(BUILD, OWNER, specs, count)
    assert not allocated and read(OWNER, 0x14) == sentinel

    # One matching chunk at each node. The root and sibling use texture 7.
    write(ROOT + 0x2c, words(ROOT + 0x40, ROOT + 0x80))
    streams = []
    for index, texture in enumerate((7, 9, 7)):
        node = ROOT + index * 0x40
        model = ROOT + 0x200 + index * 0x20
        stream = ROOT + 0x300 + index * 0x40
        write(node + 4, words(model))
        write(model + 4, words(stream))
        # Include both polygon winding signs. Each vertex has an index and a UV pair.
        length = 2 if index == 0 else -2
        data = halfwords(8, texture, 0x41, 8, 1, length, *VERTICES[0], *VERTICES[1], 0xff)
        write(stream, data)
        streams.append((stream, data))

    write(SPECS, words(4, 11, 7, 5, 17, 9))
    missing_first = fail_first_pair
    game.call(BUILD, OWNER, SPECS, 2)
    assert models == [4, 5] and lookups == [11, 17]
    assert word(OWNER) == 2 and read(OWNER + 8, 8) == bytes(8)
    array = word(OWNER + 16)
    assert allocated[array] == (8, False)
    pairs = [word(array), word(array + 4)]
    assert bool(pairs[0]) == (not missing_first) and pairs[1]
    for pair, selected in zip(pairs, ((0, 2), (1,))):
        if not pair:
            continue
        assert word(pair) == 2 * len(selected) and word(pair + 4) == len(selected)
        refs, uvs = word(pair + 8), word(pair + 12)
        assert allocated[refs] == allocated[uvs] == (8 * len(selected), False)
        for i, index in enumerate(selected):
            assert read(refs + 8 * i, 8) == words(streams[index][0] + 8, uvs + 8 * i)
            assert read(uvs + 8 * i, 8) == halfwords(3, 6, -8, 260)

    u = v = 0
    for du, dv in ((8, 0), (0, 34), (257, -300), (-280, 7)):
        u += du
        v += dv
        game.call(SCROLL, OWNER, du, dv)
        assert read(OWNER + 8, 8) == words(u & 0xffffffff, v & 0xffffffff)
        for index, (addr, original) in enumerate(streams):
            expected = bytearray(original)
            if pairs[1 if index == 1 else 0]:
                # The game uses signed remainders, including for negative offsets.
                offset_u = (abs(u) % 256) * (-1 if u < 0 else 1)
                offset_v = (abs(v) % 256) * (-1 if v < 0 else 1)
                for i, (_, x, y) in enumerate(VERTICES):
                    expected[14 + 6 * i:18 + 6 * i] = halfwords(x + offset_u, y + offset_v)
            assert read(addr, len(original)) == expected

    game.call(FREE, OWNER)
    assert word(OWNER + 16) == 0 and read(array, 8) == bytes(8)
    assert set(freed) == set(allocated) and freed[-1] == array
    for addr, (size, _) in allocated.items():
        assert read(addr + size, 8) == bytes([0xA5]) * 8


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dol", type=Path, nargs="+")
    if not __debug__:
        parser.error("run with assertions enabled")
    for path in parser.parse_args().dol:
        image = path.read_bytes()
        for failure in (False, True):
            check(image, failure)
        print(f"{path}: strip selection, both winding signs, scrolling and release passed")
