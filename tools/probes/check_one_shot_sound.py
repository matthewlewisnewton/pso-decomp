"""Check one-shot sound admission, position ownership and returned request handles."""
import argparse
import struct
from pathlib import Path

from unicorn.ppc_const import UC_PPC_REG_6, UC_PPC_REG_MSR

from gpoe8p_image import GameImage


def check(dol):
    game = GameImage(dol)
    cpu = game.cpu
    cpu.reg_write(UC_PPC_REG_MSR, cpu.reg_read(UC_PPC_REG_MSR) | 0x2000)
    pool = game.symbols["lbl_805145F0"]
    enabled = game.symbols["lbl_805D62B0"]
    last_slot = game.symbols["last_sound_effect_slot"]
    arena = 0x81113000
    position = arena + 0x38
    vector = struct.pack(">fff", 2.5, -70.25, 0.125)
    sound_id = 0x4002B21A
    slot = 37
    record = pool + slot * 40
    rejected = 0xFFFFFFFF
    packed_requests = []

    def word(address):
        return struct.unpack(">I", cpu.mem_read(address, 4))[0]

    def store(address, value):
        cpu.mem_write(address, struct.pack(">I", value))

    def allocate(request_id, source, adjustment):
        packed_requests.append((request_id, source, adjustment, cpu.reg_read(UC_PPC_REG_6)))
        return allocator_result

    game.hook("play_packed_sound_once__FUllll", allocate)
    game.hook("TLobby__sub_80227AF8", lambda *_: None)
    game.hook("fn_802264B8", lambda *_: admitted)
    cases = ("disabled", "reserved", "duplicate", "no slot", "out of range",
             "no position", "world position", "expired duplicate")
    for case in cases:
        cpu.mem_write(pool, bytes(40 * 40))
        cpu.mem_write(arena, bytes([0x7D]) * 0x100)
        cpu.mem_write(position, vector)
        store(last_slot, 0x6B6B)
        store(enabled, int(case != "disabled"))
        packed_requests.clear()
        allocator_result = rejected if case == "no slot" else slot
        admitted = int(case != "out of range")
        request_id = 0xF0000 if case == "reserved" else sound_id
        source = 0 if case == "no position" else position
        flags = int(case == "world position")
        if case in ("duplicate", "expired duplicate"):
            other = pool + 39 * 40
            store(other, 0x400)
            store(other + 4, sound_id)
            cpu.mem_write(other + 24, struct.pack(">H", 0x94 if case == "duplicate" else 0x93))

        before = bytes(cpu.mem_read(pool, 40 * 40))
        caller = bytes(cpu.mem_read(arena, 0x100))
        cpu.reg_write(UC_PPC_REG_6, flags)
        result = game.call("play_sound_effect", request_id, source, -13)
        accepted = case in ("no position", "world position", "expired duplicate")
        assert result == word(last_slot) == (slot if accepted else rejected), case
        assert cpu.mem_read(arena, 0x100) == caller, case
        if case in ("disabled", "reserved", "duplicate"):
            assert not packed_requests, case
        else:
            assert packed_requests == [(request_id, source, 0xFFFFFFF3, flags)], case

        after = bytes(cpu.mem_read(pool, 40 * 40))
        if case in ("disabled", "reserved", "duplicate", "no slot"):
            assert after == before and "TLobby__sub_80227AF8" not in game.calls, case
            continue
        assert after[:slot * 40] == before[:slot * 40], case
        assert after[(slot + 1) * 40:] == before[(slot + 1) * 40:], case
        assert word(record + 4) == request_id and word(record + 8) == source, case
        assert cpu.mem_read(record + 12, 12) == (vector if source else bytes(12)), case
        assert cpu.mem_read(record + 24, 4) == struct.pack(">Hh", 0x96, -13), case
        positions = [(args[0], args[1]) for args in game.calls.get("TLobby__sub_80227AF8", [])]
        assert positions == ([(slot, record + 12)] if source else []), case
        assert game.calls["fn_802264B8"][0][:2] == (slot, 0), case
        if accepted:
            assert word(record) & 0x600 == 0x600, case
            assert bool(word(record) & 0x2000) == bool(flags & 1), case
    return len(cases)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("images", nargs="+", type=Path)
    for image in parser.parse_args().images:
        print(f"{image}: {check(image.read_bytes())} one-shot sound cases passed")
