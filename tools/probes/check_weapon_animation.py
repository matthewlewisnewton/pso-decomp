"""Exercise shared clamping, canopy motion and the four joint pairs on GPOE8P."""
from pathlib import Path
import struct
import sys

from unicorn.ppc_const import UC_PPC_REG_6, UC_PPC_REG_FPR1, UC_PPC_REG_FPR2, UC_PPC_REG_MSR

from gpoe8p_image import GameImage


def f32(value):
    return struct.unpack(">f", struct.pack(">f", value))[0]


def check_steps(game):
    dest = 0x81111004
    for before, step, limit, expected in (
        (2, 3, 8, 5), (6, 3, 8, 8), (8, 3, 8, 8), (12, 3, 8, 8),
        (4, -3, -2, 1), (0, -3, -2, -2), (-7, -3, -2, -2),
        (1, 0, 4, 4), (7, 0, 4, 7),
    ):
        for name, fmt in (("add_integer_clamped", "i"), ("add_float_clamped", "f")):
            game.cpu.mem_write(dest - 4, b"left" + struct.pack(">" + fmt, before) + b"tail")
            if fmt == "f":
                for reg, value in ((UC_PPC_REG_FPR1, step), (UC_PPC_REG_FPR2, limit)):
                    game.cpu.reg_write(reg, struct.unpack(">Q", struct.pack(">d", value))[0])
                game.call(name, dest)
            else:
                game.call(name, dest, step, limit)
            assert game.cpu.mem_read(dest - 4, 12) == b"left" + struct.pack(">" + fmt, expected) + b"tail"


def check_animations(game):
    obj, owner = 0x81114010, 0x81116000
    start = 4 + 0x1F8
    sound = "play_sound_effect"
    draw = "scale_current_matrix"
    game.hook(sound, lambda *_: 1)
    game.hook(draw, lambda *_: None)
    mode = 0
    game.hook("get_player_list__10TObjPlayerFv", lambda *_: mode)

    for cls in ("TUnk_804A6200", "TUnk_804A67D0"):
        suffix = "__13" + cls + "Fv"
        expected = bytearray([0xCD]) * (0x204 + 8)
        struct.pack_into(">I", expected, 4 + 0xF0, owner)
        x = y = z = 1.0
        struct.pack_into(">3f", expected, start, x, y, z)
        game.cpu.mem_write(obj - 4, bytes(expected))
        sounds = 0
        for attack in (True, False, True, False):
            for _ in range(12):
                play = False
                if attack:
                    x = max(f32(0.3), f32(x - f32(0.14)))
                    y = min(f32(1.2), f32(y + f32(0.04000001)))
                    z = max(f32(0.3), f32(z - f32(0.14)))
                else:
                    new_x = min(1.0, f32(x + f32(0.14)))
                    play = x < 1.0 and new_x == 1.0
                    x = new_x
                    y = max(1.0, f32(y - f32(0.04000001)))
                    z = min(1.0, f32(z + f32(0.14)))
                game.call(("update_attack" if attack else "update_idle") + suffix, obj)
                struct.pack_into(">3f", expected, start, x, y, z)
                assert game.cpu.mem_read(obj - 4, len(expected)) == expected
                assert game.calls.get(sound, []) == ([(0x4001AA24, owner + 0x38, 0)] if play else [])
                sounds += int(play)
        assert sounds == 2
        for mode in (0, 1, 2, 3):
            game.call("vfunc_60" + suffix, obj)
            assert [args[0] for args in game.calls.get(draw, [])] == ([obj + 0x1F8] if mode == 2 else [])


def check_lifetimes(game):
    obj, parent, item, event = 0x81120010, 0x81122000, 0x81123000, 0x81124000
    base_ctor = "__ct__11TItemWeaponFP7TObjectPUc"
    base_dtor = "__dt__11TItemWeaponFv"
    delete = "__dl__5TItemFPv"
    allocate = "__nw__15TItemHeapObjectFUl"
    get_client = "get_owner_client__5TItemFv"
    game.hook(base_ctor, lambda self, *_: self)
    game.hook(base_dtor, lambda self, *_: self)
    game.hook(delete, lambda *_: None)
    game.hook(get_client, lambda *_: 2)
    game.hook(allocate, lambda *_: storage)

    for cls, timer in (("TUnk_804A6200", "TUnk_804A0648"), ("TUnk_804A67D0", "TUnk_804A0628")):
        table = game.symbols["__vt__13" + cls]
        initial = bytearray([0xCD]) * (0x204 + 8)
        game.cpu.mem_write(obj - 4, bytes(initial))
        assert game.call("__ct__13" + cls + "FP7TObjectPUc", obj, parent, item) == obj
        assert game.calls[base_ctor] == [(obj, parent, item)]
        struct.pack_into(">I", initial, 4 + 0x18, table)
        struct.pack_into(">3f", initial, 4 + 0x1F8, 1.0, 1.0, 1.0)
        assert game.cpu.mem_read(obj - 4, len(initial)) == initial
        for this, flag in ((0, 1), (obj, -1), (obj, 0), (obj, 1)):
            assert game.call("__dt__13" + cls + "Fv", this, flag) == this
            assert [call[:2] for call in game.calls.get(base_dtor, [])] == ([(obj, 0)] if this else [])
            assert [call[0] for call in game.calls.get(delete, [])] == ([obj] if this and flag > 0 else [])
        timer_ctor = "__ct__13" + timer + "FP15TItemHeapObjectUsl"
        durations = []
        game.hook(timer_ctor, lambda *_: durations.append(game.cpu.reg_read(UC_PPC_REG_6)))
        for effects, storage in ((0, event), (parent, 0), (parent, event)):
            durations.clear()
            game.cpu.mem_write(obj + 0x174, struct.pack(">I", effects))
            game.call("vfunc_57__13" + cls + "Fv", obj)
            assert [args[0] for args in game.calls.get(allocate, [])] == ([0x2C] if effects else [])
            spawned = bool(storage and effects)
            assert [args[0] for args in game.calls.get(get_client, [])] == ([obj] if spawned else [])
            assert game.calls.get(timer_ctor, []) == ([(event, parent, 2)] if spawned else [])
            assert durations == ([90] if spawned else [])


def check_trails(game):
    weapon = 0x81118010
    expected = bytearray([0xA5]) * 0x200
    game.cpu.mem_write(weapon, bytes(expected))
    for index, start, end in ((3, -1, -1), (0, 1, 2), (2, 6, 5), (1, -1, 4), (3, 0x111, -2)):
        game.cpu.reg_write(UC_PPC_REG_6, end & 0xFFFFFFFF)
        game.call("set_weapon_trail_joints", weapon, index, start)
        expected[0x19C + index] = start & 0xFF
        expected[0x1A0 + index] = end & 0xFF
        assert game.cpu.mem_read(weapon, len(expected)) == expected


if __name__ == "__main__":
    if len(sys.argv) < 2:
        raise SystemExit(f"usage: {sys.argv[0]} PsoV3.dol [rebuilt.dol ...]")
    for filename in sys.argv[1:]:
        game = GameImage(Path(filename).read_bytes())
        game.cpu.reg_write(UC_PPC_REG_MSR, game.cpu.reg_read(UC_PPC_REG_MSR) | 0x2000)
        check_steps(game)
        check_animations(game)
        check_lifetimes(game)
        check_trails(game)
        print(f"{filename}: 18 clamp cases, 96 animation frames, eight draw modes, 16 lifetime cases and five trail writes passed")
