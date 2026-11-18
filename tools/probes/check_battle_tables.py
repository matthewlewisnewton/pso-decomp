"""Run the GPOE8P battle loader and table getters with synthetic parameter files."""
import argparse
import itertools
from pathlib import Path
import struct

from gpoe8p_image import GameImage

FILE = 0x81121000
BANK = 0x81112000
GUARD = b"\xCD" * 16
TABLES = [
    ("base_stats", "battle_param_stats", (2,) * 8 + (4,) * 5),
    ("attack_params", "TLobby__battle_param_attacks", (2,) * 4 + (4,) * 3 + (2,) * 4 + (4,) * 5),
    ("resistance_params", "TLobby__battle_param_resistances", (2,) * 6 + (4,) * 5),
    ("movement_params", "battle_param_movement", (4,) * 12),
]
FILE_BYTES = bytes((i * 197 + (i >> 7) + 13 * (i >> 12)) % 256 for i in range(0xF600))


def run(path):
    g = GameImage(path.read_bytes())

    def resource(filename, destination, unused):
        assert filename_expected == bytes(g.cpu.mem_read(filename, 32)).split(b"\0")[0]
        assert destination == FILE
        g.cpu.mem_write(destination, FILE_BYTES)
        return len(FILE_BYTES)

    def allocate(n, unused4, unused5):
        assert n in (0xF600, 0x3D80)
        return FILE if n == 0xF600 else BANK

    def word(name):
        return struct.unpack(">I", g.cpu.mem_read(g.symbols[name], 4))[0]

    def set_word(name, value):
        g.cpu.mem_write(g.symbols[name], struct.pack(">I", value))

    expected_banks = []
    for difficulty in range(4):
        address = 0
        bank = bytearray()
        for _, _, fields in TABLES:
            section_size = 96 * sum(fields)
            source = address + difficulty * section_size
            for _ in range(96):
                for size in fields:
                    bank.extend(FILE_BYTES[source:source + size][::-1])
                    source += size
            address += 4 * section_size
        assert len(bank) == 0x3D80 and address == 0xF600
        expected_banks.append(bytes(bank))

    g.hook("__nwa__FUl", allocate)
    g.hook("__dla__FPv", lambda *_: None)
    g.hook("read_disc_file", resource)
    g.hook("is_main_phase_15__9TObjEneDDFv", lambda *_: online)
    g.hook("is_not_split_screen__13TRaderMapCoreFv", lambda *_: split_flag)
    online = split_flag = 0
    filename_expected = b"BattleParamEntry.dat"
    set_word("game_difficulty_selection", 0)
    g.cpu.mem_write(BANK - 16, GUARD + b"\xCC" * 0x3D80 + GUARD)
    g.call("alloc_battle_param_tables__Fv", instruction_limit=1_000_000)
    addr = BANK
    for getter, table, fields in TABLES:
        assert word(table) == addr
        for index in range(96):
            assert g.call("get_battle_" + getter, index) == addr + index * sum(fields)
        addr += 96 * sum(fields)
    assert addr == BANK + 0x3D80
    for difficulty, lab, online, split_flag in itertools.product(range(4), range(2), range(2), range(2)):
        filename_expected = (b"BattleParamEntry" + (b"_lab" if lab else b"")
                             + (b"_on" if online or split_flag else b"") + b".dat")
        set_word("battle_param_lab_variant", lab)
        set_word("battle_parameter_difficulty", difficulty)
        g.call("load_battle_param_entry__Fv", instruction_limit=1_000_000)
        assert g.cpu.mem_read(BANK - 16, 0x3D80 + 32) == GUARD + expected_banks[difficulty] + GUARD
        assert len(g.calls["read_disc_file"]) == 1 and g.calls["__dla__FPv"][0][0] == FILE
    g.call("free_boss4_rock__6TLobbyFv")
    assert g.calls["__dla__FPv"][0][0] == BANK and word("TLobby__battle_parameter_buffer") == 0
    assert all(word(table) == 0 for _, table, _ in TABLES)
    print(path, "384 table lookups, 32 full-file loads and release passed")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dol", type=Path, nargs="+")
    if not __debug__:
        parser.error("run with assertions enabled")
    for path in parser.parse_args().dol:
        run(path)
