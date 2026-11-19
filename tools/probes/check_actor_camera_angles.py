"""Verify actor positions, orientations and scripted camera playback on GPOE8P."""
import argparse
from pathlib import Path
import struct

from unicorn.ppc_const import UC_PPC_REG_MSR

from gpoe8p_image import GameImage


ACTOR = 0x81110000
CAMERA = 0x81111000
POSITION = 0x81112000
TARGET = 0x81112020
PLAYBACK = 0x81112100
CONTROLLER = 0x81114000
DIRECTORY = 0x81115000
ENTRIES = 0x81115100
MODES = 0x81115200
MOTION = 0x81115300


def run(dol):
    game = GameImage(dol)
    cpu = game.cpu
    cpu.reg_write(UC_PPC_REG_MSR, cpu.reg_read(UC_PPC_REG_MSR) | 0x2000)
    symbols = game.symbols

    def put(address, fmt, *values):
        cpu.mem_write(address, struct.pack(">" + fmt, *values))

    def read(address, fmt):
        return struct.unpack(">" + fmt, cpu.mem_read(address, struct.calcsize(">" + fmt)))

    original = bytes((i * 7) % 256 for i in range(0x90))
    cpu.mem_write(ACTOR, original)
    assert game.call("get_rotation__8TObjBaseFv", ACTOR) == ACTOR + 0x5c
    game.call("save_previous_position__8TObjBaseFv", ACTOR)
    expected = bytearray(original)
    expected[0x44:0x50] = original[0x38:0x44]
    assert cpu.mem_read(ACTOR, len(original)) == expected

    position = (3.0, 4.0, -7.0)
    target = (-2.0, 0.5, 10.0)
    put(POSITION, "3f", *position)
    put(TARGET, "3f", *target)
    put(ACTOR + 0x5c, "3i", -20, 0x7123, 31)
    slot = symbols["camera_controller_registry"] + 5 * 4
    put(slot, "I", 0)
    game.call("set_scripted_camera_pose", POSITION, TARGET, ACTOR + 0x5c)
    assert game.call("get_scripted_camera_playback") == 0
    put(slot, "I", CAMERA)
    cpu.mem_write(CAMERA, b"\x5a" * 0xa4)
    game.call("set_scripted_camera_pose", POSITION, TARGET, ACTOR + 0x5c)
    expected = bytearray(b"\x5a" * 0xa4)
    struct.pack_into(">6f", expected, 0x6c, *position, *target)
    struct.pack_into(">i", expected, 0x88, 0x7123)
    assert cpu.mem_read(CAMERA, 0xa4) == expected

    game.hook("get_current_floor_area__Fv", lambda *_: area)
    game.hook("TCameraCtrl__sub_8006A5DC", lambda *_: active)
    for area, bank, index in ((0, 0, 0), (3, 2, 7), (7, 7, 1)):
        put(symbols["camera_path_bank_table"] + area * 8, "I", MODES)
        put(symbols["TCameraCtrl__camera_banks"] + bank * 8, "I", DIRECTORY)
        put(DIRECTORY, "I", ENTRIES)
        put(ENTRIES + 4 * index, "I", MOTION)
        put(PLAYBACK, "BBHff", bank, index, 0x1234, 2.0, 0.5)
        for ctrl in (0, CONTROLLER):
            put(symbols["camera_ctrl_instance"], "I", ctrl)
            put(CONTROLLER + 0x19c, "I", 0x2000)
            put(symbols["TCameraCtrl__saved_projection_angle"], "I", 13)
            put(symbols["scripted_camera_projection_angle"], "I", 17)
            game.call("cache_target_and_forward__14CameraPlaybackCFl", PLAYBACK, 0x3333)
            assert read(symbols["TCameraCtrl__saved_projection_angle"], "I") == ((0x2000 if ctrl else 13),)
            assert read(symbols["scripted_camera_projection_angle"], "I") == ((0x3333 if ctrl else 17),)
            assert read(CAMERA + 0x90, "II") == (MOTION, MODES + bank * 8)
            assert cpu.mem_read(CAMERA + 0x98, 12) == cpu.mem_read(PLAYBACK, 12)
        for active in (5, 2):
            assert game.call("get_scripted_camera_playback") == CAMERA + 0x98
            assert read(CAMERA + 0x9a, "H") == ((0x1234 if active == 5 else 0x1235),)

    def sample(_out, motion, outputs):
        assert motion == MOTION
        pos, direction = read(outputs, "II")
        put(pos, "3f", *position)
        put(direction, "3f", *target)

    game.hook("sample_camera_motion__FPUclPUcf", sample)
    put(CAMERA + 0x90, "II", MOTION, MODES)
    for flags, start, frames, final, stopped in (
        (4, 1, 10, 2.0, 0), (4, 3, 4, 3.0, 1), (0x24, 3, 4, 0.0, 0),
        (4, 4999, 6000, 5999.0, 1), (0x24, 4999, 6000, 0.0, 0),
    ):
        put(MOTION + 4, "I", frames)
        put(MODES + 4, "I", flags)
        put(CAMERA + 0x9a, "Hff", 0, float(start), 1.0)
        game.call("run_task__13TUnk_80488B68Fv", CAMERA)
        assert read(CAMERA + 0x3c, "3f") == position
        assert read(CAMERA + 0x48, "3f") == tuple(a + b for a, b in zip(position, target))
        assert read(CAMERA + 0x54, "I") == (0x3333,)
        assert read(CAMERA + 0x9a, "Hf") == (stopped, final)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dol", type=Path)
    args = parser.parse_args()
    run(args.dol.read_bytes())
    print("Actor orientation, position copies and scripted camera playback passed.")
