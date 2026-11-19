"""Exercise persistent sound slots and the area-dependent positional sound requests."""
import argparse
import struct
from pathlib import Path

from unicorn.ppc_const import UC_PPC_REG_6, UC_PPC_REG_7, UC_PPC_REG_MSR

from gpoe8p_image import GameImage


def check_slots(image):
    game = GameImage(image)
    cpu = game.cpu
    pool = game.symbols["lbl_805145F0"]
    enabled = game.symbols["lbl_805D62B0"]
    last_slot = game.symbols["last_sound_effect_slot"]
    slot = 39
    record = pool + slot * 40
    identity = 0x81113000
    position = identity + 0x38
    other_identity = identity + 0x100
    other_position = other_identity + 0x38
    sound = 0x4003B22D
    rejected = 0xFFFFFFFF
    requests = []

    def store(address, value):
        cpu.mem_write(address, struct.pack(">I", value))

    def word(address):
        return struct.unpack(">I", cpu.mem_read(address, 4))[0]

    def allocate(sound_id, owner, source):
        requests.append((sound_id, owner, source, cpu.reg_read(UC_PPC_REG_6),
                         cpu.reg_read(UC_PPC_REG_7)))
        return allocator_result

    game.hook("normalize_sound_request__FUlllll", allocate)
    game.hook("check_sound_admission_range__FPC3Vec", lambda *_: admission)

    def play(owner, source, flags=0, sound_id=sound):
        cpu.reg_write(UC_PPC_REG_6, 0xFFFFFFF3)
        cpu.reg_write(UC_PPC_REG_7, flags)
        return game.call("play_persistent_sound", sound_id, owner, source)

    for case in ("disabled", "reserved", "out of range", "allocation failure"):
        cpu.mem_write(pool, bytes(40 * 40))
        store(enabled, int(case != "disabled"))
        store(last_slot, slot)
        allocator_result = rejected
        admission = -256 if case == "out of range" else 0
        requests.clear()
        result = play(identity, position, sound_id=0xF0000 if case == "reserved" else sound)
        assert result == word(last_slot) == rejected, case
        assert len(requests) == int(case == "allocation failure"), case
        assert cpu.mem_read(pool, 40 * 40) == bytes(40 * 40), case

    for source, admission, flags in ((other_position, 0, 0), (0, 0, 0),
                                     (other_position, -256, 0), (other_position, -256, 1)):
        cpu.mem_write(pool, bytes(40 * 40))
        caller = bytes([0xA5]) * 0x180
        cpu.mem_write(identity, caller)
        store(enabled, 1)
        requests.clear()
        allocator_result = slot
        refresh_admission = admission
        admission = 0
        assert play(identity, position, flags) == word(last_slot) == slot
        assert requests == [(sound, identity, position, 0xFFFFFFF3, flags)]
        assert (word(record + 4), word(record + 8), word(record + 28)) == (sound, position, identity)
        assert cpu.mem_read(record + 24, 4) == struct.pack(">Hh", 5, -13)
        assert word(record) & 0x1600 == 0x1600
        assert bool(word(record) & 0x2000) == bool(flags)
        admission = refresh_admission
        requests.clear()
        allocator_result = 7
        # A repeated ID keeps the first owner and sends the new position to the backend.
        result = play(other_identity, source)
        if admission == -256 and not flags:
            assert result == slot and not requests and word(record + 8) == position
        else:
            assert result == allocator_result
            assert requests == [(sound, identity, source, 0xFFFFFFF3, 0)]
            assert word(record + 8) == source
        assert word(last_slot) == slot and word(record + 28) == identity
        assert cpu.mem_read(pool, slot * 40) == bytes(slot * 40)
        assert cpu.mem_read(identity, len(caller)) == caller


def check_floors(image):
    game = GameImage(image)
    position, identity, handle = 0x81113038, 0x81113000, 19
    persistent = "play_persistent_sound"
    once = "play_sound_effect"
    game.hook("get_current_floor_area__Fv", lambda *_: floor)
    game.hook(persistent, lambda *_: handle)
    game.hook(once, lambda *_: handle)
    ids = dict.fromkeys(range(0x17, 0x1C), (0x3A842, 0x3A840))
    ids.update(dict.fromkeys((0x1C, 0x1D), (0x4003A835, 0x4003A833)))
    ids[0x22] = (0x4003B22D, 0x4003B22B)
    for floor in range(0x24):
        game.call("play_floor_area_persistent_sound", identity, position)
        expected = [(ids[floor][0], identity, position)] if floor in ids else []
        assert game.calls.get(persistent, []) == expected, floor
        result = game.call("play_floor_area_sound_effect", position)
        expected = [(ids[floor][1], position, 0)] if floor in ids else []
        assert game.calls.get(once, []) == expected, floor
        assert result == (handle if floor in ids else floor), floor


def check_area_particles(image):
    game = GameImage(image)
    cpu = game.cpu
    cpu.reg_write(UC_PPC_REG_MSR, cpu.reg_read(UC_PPC_REG_MSR) | 0x2000)
    position = 0x81113038
    source = struct.pack(">fff", 7.0, -12.5, 4.0)
    raised = struct.pack(">fff", 7.0, 17.5, 4.0)
    remap = "remap_area_sound_id__12TBoss3VoloptFl"
    timed = "create_timed_particle_emitter"
    particles = []

    def timed_effect(ptr, effect, delay):
        particles.append((bytes(cpu.mem_read(ptr, 12)), effect, delay, cpu.reg_read(UC_PPC_REG_6)))

    def particle(ptr, effect, _):
        particles.append((bytes(cpu.mem_read(ptr, 12)), effect))

    game.hook("get_current_floor_area__Fv", lambda *_: floor)
    game.hook(remap, lambda sound, *_: sound + 1)
    game.hook("play_sound_effect", lambda *_: 0)
    game.hook(timed, timed_effect)
    game.hook("spawn_particle_effect", particle)
    ids = dict.fromkeys(range(0x17, 0x1C), 0x3AB3C)
    ids.update({0x1C: 0x4003AB31, 0x1D: 0x4003AB31, 0x22: 0x4003B22A, 0x23: 0x4003A359})
    for name, default_id in (("play_area_sound_and_particles_a", 0x4003AB20),
                             ("play_area_sound_and_particles_b", 0x4003AB37)):
        for floor in range(0x24):
            particles.clear()
            cpu.mem_write(position, source)
            game.call(name, position)
            assert game.calls["play_sound_effect"] == [(ids.get(floor, default_id + 1), position, 0)]
            assert [args[0] for args in game.calls.get(remap, [])] == ([] if floor in ids else [default_id])
            assert particles == [(source, 0xEA, 10, 30), (raised, 0xE9)]
            assert cpu.mem_read(position, 12) == source


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("images", type=Path, nargs="+")
    for path in parser.parse_args().images:
        image = path.read_bytes()
        check_slots(image)
        check_floors(image)
        check_area_particles(image)
        print(f"{path}: persistent slot checks and four dispatch routines on all 36 floors passed")
