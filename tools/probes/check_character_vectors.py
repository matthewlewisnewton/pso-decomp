"""Verify character position copies and their original read and write order on GPOE8P."""
import argparse
from pathlib import Path
import struct

from unicorn import UC_HOOK_CODE
from unicorn.ppc_const import UC_PPC_REG_3, UC_PPC_REG_4, UC_PPC_REG_MSR

from gpoe8p_image import GameImage


def run(dol):
    game = GameImage(dol)
    cpu = game.cpu
    cpu.reg_write(UC_PPC_REG_MSR, cpu.reg_read(UC_PPC_REG_MSR) | 0x2000)
    actor = 0x81112000
    calls = []

    def observe(cpu, address, size, data):
        calls.append((cpu.reg_read(UC_PPC_REG_3) - actor, cpu.reg_read(UC_PPC_REG_4) - actor))

    copy = game.symbols["VecCopy__FP3VecPC3Vec"]
    cpu.hook_add(UC_HOOK_CODE, observe, begin=copy, end=copy)
    for name, transfers in (
        ("initialize_position_copies__9TObjCharaFv", ((0x29C, 0x38), (0x290, 0x29C), (0x44, 0x290))),
        ("copy_body_to_center__9TObjCharaFv", ((0x74, 0x2FC),)),
    ):
        for xyz in ((-1.25, 17.0, -0.0), (0.0, -43.75, 91.0)):
            expected = bytearray((i * 37 + i // 256) % 256 for i in range(0x350))
            struct.pack_into(">3f", expected, transfers[0][1], *xyz)
            cpu.mem_write(actor, bytes(expected))
            for dst, src in transfers:
                expected[dst:dst + 12] = expected[src:src + 12]
            calls.clear()
            game.call(name, actor)
            assert calls == list(transfers), (name, calls)
            assert cpu.mem_read(actor, len(expected)) == expected, name


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dol", type=Path)
    run(parser.parse_args().dol.read_bytes())
    print("Character position copies and surrounding storage passed.")
