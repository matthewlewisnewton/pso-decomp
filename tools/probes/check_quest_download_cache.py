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

    index = game.symbols["lbl_80593EC8"]
    pool = index + 80 * 4
    game.cpu.mem_write(index, b"\x55" * 0x1140)
    game.hook("TQuestVmDownLoadServer__sub_803E93DC", lambda *_: -1)
    game.call("__VIRetraceHandler")
    assert game.cpu.mem_read(index, 80 * 4) == bytes(80 * 4)
    assert word(game, game.symbols["lbl_805D7878"]) == pool
    for i in range(512):
        link = pool + 8 * (i + 1) if i < 511 else 0
        assert game.cpu.mem_read(pool + 8 * i, 8) == struct.pack(">II", 0x55555555, link)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("images", type=Path, nargs="+")
    for path in parser.parse_args().images:
        check(path.read_bytes())
        print(f"{path}: 128 slots, ten linked pages, 80 name buckets and 512 free-list nodes passed")
