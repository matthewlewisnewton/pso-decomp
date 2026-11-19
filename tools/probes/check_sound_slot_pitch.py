"""Exercise the sound request pitch gate and its changes to individual voices."""
from pathlib import Path
import struct
import sys

from gpoe8p_image import GameImage

UPDATE = "update_technique_slot__10TTecRaFoieFl"
SET_PITCH = "set_sound_slot_pitch"
VOICE_COUNT = 32
VOICE_SIZE = 0xA0


def check(path):
    image = path.read_bytes()
    gate = GameImage(image)
    gate.hook(SET_PITCH, lambda *_: None)
    for enabled in (0, 1, -1):
        gate.cpu.mem_write(gate.symbols["lbl_805D62B0"], struct.pack(">i", enabled))
        for slot in (-1, 0, 31, 32, 39, 40):
            gate.call(UPDATE, slot, -0x181, 11)
            expected = [(slot, 0xFFFFFE7F, 11)] if enabled and 0 <= slot < 40 else []
            assert gate.calls.get(SET_PITCH, []) == expected, (enabled, slot)

    game = GameImage(image)
    pool = game.symbols["lbl_805162EC"]
    guard = bytes([0xA5]) * 8
    initial = guard + bytes([0xCD]) * (VOICE_SIZE * VOICE_COUNT) + guard
    for enabled, slot, pitch, duration, scaled in (
        (1, 0, 0x100, 0, 682),
        (1, 31, -0x181, 11, -1026),
        (-1, 17, 0, -2, 0),
        (1, 7, 0x40000, 19, -699050),
        (1, -1, 4, 3, None),
        (1, 32, 4, 3, None),
        (1, 39, 4, 3, None),
        (1, 40, 4, 3, None),
        (0, 0, 0x100, 5, None),
    ):
        game.cpu.mem_write(pool - len(guard), initial)
        game.cpu.mem_write(game.symbols["lbl_805D62B0"], struct.pack(">i", enabled))
        game.call(UPDATE, slot, pitch, duration)
        expected = bytearray(initial)
        if scaled is not None:
            duration_word = duration if duration > 0 else 0x88888888
            struct.pack_into(">iII", expected, len(guard) + slot * VOICE_SIZE + 0x7C,
                             scaled, duration_word, duration_word)
        assert game.cpu.mem_read(pool - len(guard), len(expected)) == expected, (enabled, slot, pitch)
    print(f"{path}: 18 forwarding cases and nine complete voice-pool checks passed")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        raise SystemExit(f"usage: {sys.argv[0]} PsoV3.dol [rebuilt.dol ...]")
    for filename in sys.argv[1:]:
        check(Path(filename))
