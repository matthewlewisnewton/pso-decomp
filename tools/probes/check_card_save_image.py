"""Exercise the retail memory-card save writer and reader with guarded buffers."""
import argparse
from pathlib import Path
import struct
import zlib

from gpoe8p_image import GameImage, MASK


DESCRIPTOR = 0x81110000
READ_RESULT = 0x81110100
HEADER = 0x81111000
BANNER = 0x81114000
ICON = 0x81116000
PAYLOAD = 0x81118000
IMAGE = 0x81120000
HEADER_SIZE = 0x2048


def run(dol):
    game = GameImage(dol)
    cpu = game.cpu
    writer, = [name for name in game.symbols if name.startswith("build_save_file_image__")]
    banner = bytes(range(256)) * 24
    icon = bytes(reversed(range(256))) * 8
    cpu.mem_write(BANNER, banner)
    cpu.mem_write(ICON, icon)
    cpu.mem_write(game.symbols["TAdPlayerLoadGC__banner_file_buf"], struct.pack(">I", BANNER))
    for i in range(6):
        address = game.symbols["TAdPlayerLoadGC__banner_buffers"] + 4 * i
        cpu.mem_write(address, struct.pack(">I", ICON + i * 4))
        cpu.mem_write(DESCRIPTOR - 1, b"\xa5" * 0x62)
        game.call("set_card_save_artwork", DESCRIPTOR, i)
        expected = b"\xa5" * 0x45 + struct.pack(">II", BANNER, ICON + i * 4) + b"\xa5" * 0x15
        assert bytes(cpu.mem_read(DESCRIPTOR - 1, 0x62)) == expected
    game.call("set_card_save_artwork", DESCRIPTOR, 6)
    assert bytes(cpu.mem_read(DESCRIPTOR - 1, 0x62)) == expected

    def allocate(size, _r4, _r5):
        assert size == HEADER_SIZE
        cpu.mem_write(HEADER - 1, b"\xcc" * (HEADER_SIZE + 2))
        return HEADER

    game.hook("__nw__FUl", allocate)
    game.hook("__dl__FPv", lambda *_: None)
    game.hook("getDateStamp__FP9DateStamp", lambda *_: 0)
    for size in (0, 3, 8191, 8192, 8193):
        payload = bytes((i * 13 + 17) % 256 for i in range(size))
        cpu.mem_write(PAYLOAD, payload or b"\x00")
        for title, omit_space in ((b"Guild Card", 0), (b"Download", 1), (b"A" * 32, 1)):
            desc = bytearray(0x60)
            desc[0x12:0x12 + len(title)] = title
            struct.pack_into(">II", desc, 0x44, BANNER, ICON)
            struct.pack_into(">H", desc, 0x54, omit_space)
            struct.pack_into(">II", desc, 0x58, PAYLOAD, size)
            cpu.mem_write(DESCRIPTOR, bytes(desc))
            cpu.mem_write(IMAGE - 1, b"\xa5" * (HEADER_SIZE + size + 2))
            blocks = game.call(writer, IMAGE, DESCRIPTOR, instruction_limit=2_000_000)
            assert blocks == 3 + size // 8192
            assert game.calls["__dl__FPv"][0][0] == HEADER
            assert cpu.mem_read(HEADER - 1, 1) == cpu.mem_read(HEADER + HEADER_SIZE, 1) == b"\xcc"
            expected = bytearray(HEADER_SIZE)
            expected[:0x20] = b"PSO EPISODE I & II Plus".ljust(0x20, b"\x00")
            expected[0x20:0x40] = (title + (b"" if omit_space else b" "))[:32].ljust(0x20, b"\x00")
            expected[0x40:0x1840] = banner
            expected[0x1840:0x2040] = icon
            struct.pack_into(">I", expected, 0x2040, size)
            struct.pack_into(">I", expected, 0x2044, zlib.crc32(expected))
            assert bytes(cpu.mem_read(IMAGE - 1, HEADER_SIZE + size + 2)) == b"\xa5" + expected + payload + b"\xa5"
            for corrupt in (False, True):
                if corrupt:
                    cpu.mem_write(IMAGE + 0x40, b"\xff")
                before = bytes(cpu.mem_read(IMAGE, HEADER_SIZE))
                cpu.mem_write(READ_RESULT - 1, b"\x5a" * 0x62)
                status = game.call("read_card_save_header", READ_RESULT, IMAGE, instruction_limit=2_000_000)
                assert status == ((-224 & MASK) if corrupt else 0)
                expected_result = bytearray(b"\x5a" * 0x62)
                if not corrupt:
                    struct.pack_into(">II", expected_result, 0x59, IMAGE + HEADER_SIZE, size)
                assert cpu.mem_read(READ_RESULT - 1, 0x62) == expected_result
                assert cpu.mem_read(IMAGE, HEADER_SIZE) == before


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dol", type=Path)
    args = parser.parse_args()
    run(args.dol.read_bytes())
    print("Card artwork, 15 save images and 30 header reads passed.")
