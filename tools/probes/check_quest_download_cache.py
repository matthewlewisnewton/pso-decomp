#!/usr/bin/env python3
"""Check the GPOE8P quest file cache and its encoded-name index."""
import argparse
from pathlib import Path
import struct

from unicorn.ppc_const import UC_PPC_REG_6

from gpoe8p_image import GameImage


def word(game, address):
    return struct.unpack(">I", game.cpu.mem_read(address, 4))[0]


def check(dol):
    game = GameImage(dol)
    slots = game.symbols["quest_download_slot_table"]
    head = game.symbols["file_page_cache_head"]
    pages = [slots + 0x400 + i * 0x40C for i in range(10)]
    game.cpu.mem_write(slots, b"\x55" * 0x2C78)
    game.call("init_page_cache__22TQuestVmDownLoadServerFv")
    assert word(game, head) == pages[0]
    assert game.cpu.mem_read(slots, 0x400) == (b"\0" + b"\x55" * 7) * 128
    for i, page in enumerate(pages):
        following = pages[i + 1] if i < 9 else 0
        assert game.cpu.mem_read(page, 12) == struct.pack(">iII", -1, 0, following)
        assert game.cpu.mem_read(page + 12, 0x400) == b"\x55" * 0x400
        game.cpu.mem_write(page, struct.pack(">I", i))

    order = list(range(10))
    for i in [0, 9, 4, 4, 0]:
        assert game.call("get_cached_page__22TQuestVmDownLoadServerFl", i) == pages[i] + 12
        order.remove(i)
        order.insert(0, i)
        chain = word(game, head)
        for j in order:
            assert chain == pages[j]
            chain = word(game, chain + 8)
        assert chain == 0

    acquire = "acquire_slot_entry__22TQuestVmDownLoadServerFllll"
    release = "release_ref_slot__22TQuestVmDownLoadServerFUl"
    for i in range(128):
        game.cpu.reg_write(UC_PPC_REG_6, 0x80 + i)
        assert game.call(acquire, i, 0x200 + i, i) == i
        assert game.cpu.mem_read(slots + 8 * i, 8) == struct.pack(">BBHhh", 1, 0x80 + i, i, 0x200 + i, i)
    assert game.call(acquire, 22, 0x216, 22) == 22
    assert game.cpu.mem_read(slots + 8 * 22, 1) == b"\x02"
    assert game.call(acquire, 129, 0, 0) == 0xFFFFFFFF
    for _ in range(2):
        assert game.call(release, 22) == 0
    for slot in (22, 128):
        assert game.call(release, slot) == 0xFFFFFFFF

    index = game.symbols["quest_name_cache_index"]
    pool = index + 80 * 4
    game.cpu.mem_write(index, b"\x55" * 0x1140)
    game.hook("read_quest_name_cache_image", lambda *_: -1)
    game.call("initialize_quest_name_cache")
    assert game.cpu.mem_read(index, 80 * 4) == bytes(80 * 4)
    assert word(game, game.symbols["quest_name_cache_free_nodes"]) == pool
    for i in range(512):
        link = pool + 8 * (i + 1) if i < 511 else 0
        assert game.cpu.mem_read(pool + 8 * i, 8) == struct.pack(">II", 0x55555555, link)


def check_name_image(dol):
    game = GameImage(dol)
    image = game.symbols["quest_name_cache_image"]
    index = game.symbols["quest_name_cache_index"]
    pool = index + 0x140
    free = game.symbols["quest_name_cache_free_nodes"]
    cursor = game.symbols["quest_name_cache_write_cursor"]
    page_end = game.symbols["quest_name_cache_page_end"]
    slot = game.symbols["quest_download_slot_table"]
    contents = bytearray(0x2000)
    records = []
    for page, names in [(0, [b"B", b"A"]), (1, [b"C", b"\xa4X"]), (7, [b"\xefY"])]:
        offset = page * 0x400
        for name in names:
            size = 3 + len(name)
            contents[offset:offset + size] = struct.pack("<HB", size, len(name)) + name
            records.append(image + offset)
            offset += size

    seek = "seek_or_reopen__22TQuestVmDownLoadServerFi"
    read = "aram_read_thunk__22TQuestVmDownLoadServerFUli"
    seek_ok = False
    read_size = 0

    def seek_image(position, *_):
        assert position == 0x1400
        return 0 if seek_ok else -1

    def read_image(file, dest, length):
        assert dest == image and length == 0x2000
        game.cpu.mem_write(dest, bytes(contents[:read_size]))
        return read_size

    game.hook(seek, seek_image)
    game.hook(read, read_image)
    assert game.call("read_quest_name_cache_image") == 0xFFFFFFFF
    assert read not in game.calls
    seek_ok = True
    read_size = 0x1FFF
    assert game.call("read_quest_name_cache_image") == 0xFFFFFFFF
    read_size = len(contents)
    game.call("initialize_quest_name_cache")
    assert word(game, cursor) == image + 8 and word(game, page_end) == image + 0x400

    def bucket(number):
        result = []
        node = word(game, index + 4 * number)
        while node:
            assert node not in result and pool <= node < pool + 512 * 8
            result.append(node)
            node = word(game, node + 4)
        return result

    nodes = [pool + 8 * i for i in range(len(records))]
    assert [word(game, n) for n in nodes] == records
    assert bucket(0) == [nodes[1], nodes[0], nodes[2]]
    assert bucket(4) == [nodes[3]] and bucket(79) == [nodes[4]]
    assert word(game, free) == pool + 40
    game.cpu.mem_write(slot + 6, struct.pack(">h", 0x1003))
    game.cpu.mem_write(slot + 14, struct.pack(">h", 0x7001))
    game.call("rotate_quest_name_cache_page")
    assert word(game, cursor) == image + 0x400 and word(game, page_end) == image + 0x800
    assert bucket(0) == [nodes[1], nodes[0]] and bucket(4) == [] and bucket(79) == [nodes[4]]
    assert word(game, free) == nodes[3] and word(game, nodes[3] + 4) == nodes[2]
    assert word(game, nodes[2] + 4) == pool + 40
    assert game.cpu.mem_read(slot + 6, 2) == b"\xff\xff"
    assert game.cpu.mem_read(slot + 14, 2) == b"\x70\x01"


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("images", type=Path, nargs="+")
    for path in parser.parse_args().images:
        image = path.read_bytes()
        check(image)
        check_name_image(image)
        print(f"{path}: 128 slots, ten linked pages, 80 buckets, 512 free-list nodes, file reads and page eviction passed")
