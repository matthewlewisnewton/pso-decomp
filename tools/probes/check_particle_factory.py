"""Exercise the position-based particle factories and initializers in a matching game image."""
import argparse
from pathlib import Path
import struct

from unicorn.ppc_const import UC_PPC_REG_MSR

from gpoe8p_image import GameImage


def check(image):
    game = GameImage(image)
    cpu = game.cpu
    cpu.reg_write(UC_PPC_REG_MSR, cpu.reg_read(UC_PPC_REG_MSR) | 0x2000)
    particle = 0x81110010
    position = 0x81111004
    global_table = 0x81112000
    area_table = 0x81128000
    task = 0x81130000
    clip_task = 0x81131000
    coordinates = struct.pack(">3f", 35.5, -10.25, 0.125)
    cpu.mem_write(position, coordinates)
    sentinel = bytes([0xA5]) * (0x78 + 8)
    for name, value in (("particle_pool_limit", 0x200), ("particle_global_entry_table", global_table),
                        ("particle_area_entry_table", area_table), ("tl_07", task), ("tl_clipout", clip_task)):
        cpu.mem_write(game.symbols[name], struct.pack(">I", value))

    allocate = "__nw__7TObjectFUl"
    construct = "__ct__7TObjectFP7TObject"
    game.hook(allocate, lambda *_: allocated)
    game.hook(construct, lambda *_: None)
    cases = 0
    for name, flags in (("spawn_particle_effect", 0), ("spawn_particle_effect_with_flags", 0x40),
                        ("spawn_particle_effect_with_flags", 0x14800)):
        for effect_id, entry in ((0, global_table), (0x1FF, global_table + 0x1FF * 0x98),
                                 (0x200, area_table), (0x23F, area_table + 0x3F * 0x98),
                                 (0x240, None)):
            for allocated in (particle, 0):
                cpu.mem_write(particle - 4, sentinel)
                result = game.call(name, position, effect_id, flags)
                assert [args[0] for args in game.calls.get(allocate, [])] == ([0x78] if entry else [])
                assert cpu.mem_read(position, 12) == coordinates
                cases += 1
                if not allocated or entry is None:
                    assert result == 0 and construct not in game.calls
                    assert cpu.mem_read(particle - 4, len(sentinel)) == sentinel
                    continue
                assert result == particle
                assert [args[:2] for args in game.calls[construct]] == [(particle, task)]
                assert cpu.mem_read(particle - 4, 4) == cpu.mem_read(particle + 0x78, 4) == sentinel[:4]
                assert cpu.mem_read(particle + 0x28, 8) == struct.pack(">IHH", entry, flags & 0xFFFF, 0xFFFF)
                assert cpu.mem_read(particle + 0x30, 16) == struct.pack(">4I", 1, 0, 0, 0)
                owner = clip_task if flags & 0x4800 == 0x4800 else task
                assert cpu.mem_read(particle + 0x58, 4) == struct.pack(">I", owner)
                assert cpu.mem_read(particle + 0x60, 24) == coordinates + bytes(12)
    return cases


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("images", type=Path, nargs="+")
    for path in parser.parse_args().images:
        print(f"{path}: {check(path.read_bytes())} particle factory cases passed")
