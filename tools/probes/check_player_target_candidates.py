"""Exercise player target collection, sorting and squared range forwarding in the game image."""
import argparse
from pathlib import Path
import struct

from unicorn.ppc_const import UC_PPC_REG_FPR1, UC_PPC_REG_MSR

from gpoe8p_image import GameImage


def set_range(cpu, value):
    cpu.reg_write(UC_PPC_REG_FPR1, struct.unpack(">Q", struct.pack(">d", value))[0])


def check(image):
    game = GameImage(image)
    cpu = game.cpu
    cpu.reg_write(UC_PPC_REG_MSR, cpu.reg_read(UC_PPC_REG_MSR) | 0x2000)
    enemy = 0x81110000
    players = [enemy + 0x1000 * i for i in range(1, 5)]
    ids = [0x8012, 0x0110, 0xFF02, 0x4138]
    distances = [25, 4, 9, 4]
    cpu.mem_write(enemy + 0x38, struct.pack(">3f", 1, 500, 2))
    for player, (x, z) in zip(players, ((4, 6), (1, 4), (4, 2), (3, 2))):
        cpu.mem_write(player + 0x38, struct.pack(">3f", x, -90, z))

    game.hook("get_game_mode__6TLobbyFv", lambda *_: count)
    game.hook("get_player_data__10TObjPlayerFi", lambda index, *_: players[index])
    game.hook("is_alive__8TObjBaseFv", lambda player, *_: int(players.index(player) in alive))
    game.hook("get_entity_id", lambda player, *_: ids[players.index(player)])
    collector = "collect_enemy_target_candidates"
    # Unicorn supports the scalar saves and restores of f30/f31. Skip their Gekko-only
    # paired-single spill slots, which the collector never reads as scalar data.
    start = game.symbols[collector]
    for offset, instruction in ((0x10, 0xF3E10048), (0x18, 0xF3C10038),
                                (0x1A8, 0xE3E10048), (0x1B0, 0xE3C10038)):
        assert cpu.mem_read(start + offset, 4) == struct.pack(">I", instruction)
        cpu.mem_write(start + offset, struct.pack(">I", 0x60000000))
    wrapper = "collect_target_candidates__9TObjEneDDFf"
    cases = (
        (0, (), 0, ()),
        (4, (), 48, ()),
        (4, (0, 1, 2, 3), 4, ()),
        (4, (0, 1, 2, 3), 9, (3, 1)),
        (4, (0, 2), 26, (2, 0)),
        (4, (0, 1, 2, 3), 26, (1, 3, 2, 0)),
        (4, (0, 1, 2), 0, (1, 2, 0)),
        (4, (0, 1, 2), -1, (1, 2, 0)),
    )
    for routine in (collector, wrapper):
        output = 0x81116004 if routine == collector else game.symbols["enemy_target_candidate_table"]
        original = cpu.mem_read(output - 4, 40)
        for count, alive, limit, expected in cases:
            block = bytearray([0xA5] * 40)
            cpu.mem_write(output - 4, bytes(block))
            set_range(cpu, limit)
            assert game.call(routine, enemy, output) == len(expected)
            for i, player in enumerate(expected):
                struct.pack_into(">H", block, 4 + i * 8, ids[player])
                struct.pack_into(">f", block, 8 + i * 8, distances[player])
            assert cpu.mem_read(output - 4, 40) == block
        cpu.mem_write(output - 4, bytes(original))

    forwarded = []

    def observe(enemy_arg, records, unused):
        forwarded.append((enemy_arg, cpu.reg_read(UC_PPC_REG_FPR1)))
        return 0

    game.hook(collector, observe)
    for limit in (-1.0, 0.0, 22500.0):
        output = 0x81116004
        cpu.mem_write(output - 4, bytes([0xA5]) * 12)
        set_range(cpu, limit)
        bits = cpu.reg_read(UC_PPC_REG_FPR1)
        assert game.call("TObjEneMe1Canadin__sub_8009E860", enemy, output) == 0
        assert forwarded.pop() == (enemy, bits)
        assert cpu.mem_read(output - 4, 12) == bytes([0xA5]) * 4 + struct.pack(">f", -1) + bytes([0xA5]) * 4
    return 2 * len(cases) + 3


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("images", type=Path, nargs="+")
    for path in parser.parse_args().images:
        print(f"{path}: {check(path.read_bytes())} player targeting cases passed")
