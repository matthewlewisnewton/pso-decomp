"""Exercise the shared enemy movement and targeting fields in a matching GPOE8P image."""
import argparse
from pathlib import Path
import struct

from unicorn.ppc_const import UC_PPC_REG_MSR

from gpoe8p_image import GameImage


def check(image):
    game = GameImage(image)
    cpu = game.cpu
    cpu.reg_write(UC_PPC_REG_MSR, cpu.reg_read(UC_PPC_REG_MSR) | 0x2000)
    enemy = 0x81118000
    target = 0x81119000
    other = 0x8111A000
    start = 0x370
    cases = 0

    def initial():
        return bytearray([0xA5] * 0x58)

    def execute(name, state, *args, writes=(), result=None):
        nonlocal cases
        cpu.mem_write(enemy + start, bytes(state))
        returned = game.call(name, enemy, *args)
        expected = state.copy()
        for offset, fmt, values in writes:
            struct.pack_into(">" + fmt, expected, offset - start, *values)
        assert cpu.mem_read(enemy + start, len(expected)) == expected, name
        if result is not None:
            assert returned == result, (name, returned, result)
        cases += 1

    game.hook("__ct__9TObjEnemyFP7TObject", lambda actor, *_: actor)
    entity_id = 0xA014
    cpu.mem_write(enemy + 0x1C, struct.pack(">H", entity_id))
    movement = (0x374, "IIfIII", (0, 0, 5.0, 0, 0, 0))
    execute("__ct__9TObjEneDDFP7TObject", initial(), other, writes=[movement])
    cleared = [(0x38C, "H", (0xFFFF,)), (0x390, "I", (0,))]
    execute("__ct__12TObjEneDD_STFP7TObject", initial(), other,
            writes=[movement, *cleared, (0x394, "7f", (0,) * 7),
                    (0x3B0, "4i", (entity_id % 30, 30, (entity_id + 3) % 30, 30))])
    execute("set_field_378__9TObjEneDDFl", initial(), -7, writes=[(0x378, "i", (-7,))])
    execute("set_active__12TObjEneDD_STFv", initial(), writes=[(0x388, "I", (1,))])
    execute("clear_field_388__9TObjEneDDFv", initial(), writes=[(0x388, "I", (0,))])
    for blocked, missed, limit in ((0, 0, 1), (2, 0, 2), (0, 3, 2), (-1, -2, 0), (0, 0, 0)):
        state = initial()
        struct.pack_into(">ii", state, 0x380 - start, blocked, missed)
        execute("has_move_failures__9TObjEneDDFl", state, limit, result=int(max(blocked, missed) >= limit))

    execute("init_float_params__12TObjEneDD_STFv", initial(), writes=[(0x394, "7f", (0,) * 7)])
    for limit in (1, 7, 30):
        execute("enemy_init_acquire_period__12TObjEneDD_STFl", initial(), limit,
                writes=[(0x3B0, "ii", (entity_id % limit, limit))])
        execute("enemy_init_validate_period__12TObjEneDD_STFl", initial(), limit,
                writes=[(0x3B8, "ii", ((entity_id + 3) % limit, limit))])
    cpu.mem_write(target + 0x38, struct.pack(">3f", 3.5, -8.5, 0.25))
    for pointer in (0, target):
        state = initial()
        struct.pack_into(">I", state, 0x390 - start, pointer)
        execute("enemy_copy_target_destination__12TObjEneDD_STFv", state,
                writes=[(0x394, "3f", (3.5, -8.5, 0.25))] if pointer else [])

    lookup = "find_active_entity_by_id"
    game.hook(lookup, lambda key, *_: target if key == 0xA015 else 0)
    for key, address in ((0xFFFF, 0), (0xA015, target), (0x8000, 0)):
        for name in ("enemy_set_target_id", "enemy_bind_or_clear_target"):
            execute(name, initial(), key, writes=[(0x38C, "H", (key,)), (0x390, "I", (address,))],
                    result=int(key != 0xFFFF) if name == "enemy_bind_or_clear_target" else None)
            assert [a[0] for a in game.calls.get(lookup, [])] == ([] if key == 0xFFFF else [key])
    game.hook("get_game_mode__6TLobbyFv", lambda *_: 2)
    game.hook("get_player_data__10TObjPlayerFi", lambda idx, *_: (other, target)[idx])
    cpu.mem_write(target + 0x1C, struct.pack(">H", 0x8016))
    for pointer in (target, enemy):
        writes = [(0x38C, "H", (0x8016,)), (0x390, "I", (target,))] if pointer == target else cleared
        execute("set_target_player__12TObjEneDD_STFPv", initial(), pointer, writes=writes)

    transform = "transform_relative_position__9TObjEneDDFPv"
    live = "enemy_has_live_target__12TObjEneDD_STFv"
    game.hook(transform, lambda *_: valid)
    game.hook(live, lambda *_: valid)
    for counter, valid in ((3, 1), (3, 0), (1, 1), (1, 0)):
        state = initial()
        struct.pack_into(">I", state, 0x390 - start, target)
        struct.pack_into(">ii", state, 0x3B8 - start, counter, 3)
        due = counter == 3
        execute("enemy_validate_retained_target", state,
                writes=[(0x3B8, "i", (0 if due else 2,))] + ([] if valid else cleared), result=valid)
        assert (transform in game.calls, live in game.calls) == (due, not due)
        if due:
            assert game.calls[transform][0][:2] == (enemy, target)

    # The constructor installed the original virtual table. Control the policy and
    # target predicates here so each path of the shared validation method runs.
    game.hook("vfunc_99__9TObjEneDDFv", lambda *_: allow)
    game.hook("is_player_entity_id", lambda *_: is_player)
    game.hook("enemy_validate_retained_target", lambda *_: 7)
    for allow, is_player in ((1, 0), (0, 1), (0, 0)):
        accepted = allow or is_player
        execute("check_target_validity__12TObjEneDD_STFv", initial(),
                writes=[] if accepted else cleared, result=7 if accepted else 0)
        assert ("is_player_entity_id" in game.calls) == (not allow)
        assert ("enemy_validate_retained_target" in game.calls) == bool(accepted)
    return cases


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("images", type=Path, nargs="+")
    for path in parser.parse_args().images:
        print(f"{path}: {check(path.read_bytes())} guarded enemy state cases passed")
