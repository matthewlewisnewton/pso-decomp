#!/usr/bin/env python3
"""Run De Rol Le and Barba Ray's dust tasks through the GX trail renderer."""
import argparse
from pathlib import Path
import struct

from unicorn import UC_HOOK_MEM_WRITE
from unicorn.ppc_const import UC_PPC_REG_MSR

from gpoe8p_image import GameImage


def check(image):
    game = GameImage(image)
    game.cpu.reg_write(UC_PPC_REG_MSR, game.cpu.reg_read(UC_PPC_REG_MSR) | 0x2000)
    fifo = 0xcc008000
    game.cpu.mem_map(fifo, 0x1000)
    writes = []

    def fifo_word(cpu, access, address, size, value, data):
        assert address == fifo and size == 4
        writes.append(value & 0xffffffff)

    game.cpu.hook_add(UC_HOOK_MEM_WRITE, fifo_word, begin=fifo, end=fifo + 3)
    for symbol in ("end_effect_render__13TParticleCtrlFv", "push_matrix", "post_translate_matrix",
                   "pop_matrix", "TObjPlayer__sub_803DF768", "reset_player_transform__Fv", "GXBegin",
                   "queue_destruction__7TObjectFv"):
        game.hook(symbol, lambda *_: None)

    task = 0x81110020
    for boss, table, counter, get_slot in (
        (2, "boss2_dust_output_table", "TObjBoss2DustCtrl_dust_counter", "TObjBoss2DustCtrl__sub_8003AB5C"),
        (7, "TObjBoss7DustCtrl__transformed_vertices", "lbl_805D6958", "TObjBoss7DustCtrl__sub_802F125C"),
    ):
        buf = game.symbols[table]
        game.cpu.mem_write(game.symbols[counter], bytes(4))
        assert [game.call(get_slot) for i in range(22)] == [i % 10 for i in range(22)]
        # Give each slot six unique positions and ARGB colors. The GPU receives RGBA.
        expected = []
        for i in range(60):
            color = 0x91428310 + i
            vertex = struct.pack(">fffI", i + 1.0, -i * 0.5, i * 0.25, color)
            game.cpu.mem_write(buf + i * 16, vertex)
            expected.extend((*struct.unpack(">3I", vertex[:12]), (color << 8 & 0xffffffff) | (color >> 24)))
        for slot in range(10):
            game.cpu.mem_write(task + 0x20, struct.pack(">I3f", slot, 2.0, 4.0, 16.0))
            writes.clear()
            game.call(f"render__13TObjBoss{boss}DustFv", task)
            assert writes == expected[slot * 24:(slot + 1) * 24]
            assert game.calls["GXBegin"] == [(0x98, 4, 6)]
            assert game.calls["post_translate_matrix"][0][0] == task + 0x24
            assert game.calls["TObjPlayer__sub_803DF768"][0][0] == 0
            assert len(game.calls["pop_matrix"]) == len(game.calls["push_matrix"]) == 1
        for tick in (0, 87, 88, 89, 90):
            game.cpu.mem_write(task + 0x1c, struct.pack(">ii3f", tick, 7, 2.0, 4.0, 16.0))
            game.call(f"run_task__13TObjBoss{boss}DustFv", task)
            t, slot, x, y, z = struct.unpack(">ii3f", game.cpu.mem_read(task + 0x1c, 20))
            assert (t, slot, x, y) == (tick + 1, 7, 2.0, 4.0)
            assert abs(z - (16.0 - 9.259259)) < 1e-6
            queued = game.calls.get("queue_destruction__7TObjectFv", [])
            assert [args[0] for args in queued] == ([task] if t >= 90 else [])


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("images", nargs="+", type=Path)
    for path in parser.parse_args().images:
        check(path.read_bytes())
        print(f"{path}: both slot rings, all 20 rendered strips and 10 lifetime cases passed")
