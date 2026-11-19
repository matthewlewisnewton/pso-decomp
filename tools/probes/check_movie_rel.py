"""Check movie REL allocation, linking, entry points and cleanup on GPOE8P."""
import argparse
from pathlib import Path
import struct

from gpoe8p_image import GameImage


MODULE = 0x81110020
NAME = 0x81110100
IMAGE = 0x81110400
BSS = 0x81110800
PROLOG = 0x81110c00
EPILOG = 0x81110d00


def run(dol):
    game = GameImage(dol)
    cpu = game.cpu
    events = []
    game.symbols.update(test_prolog=PROLOG, test_epilog=EPILOG)
    cpu.mem_write(NAME, b"movie.rel\0")
    cpu.mem_write(PROLOG, bytes.fromhex("4e800020"))
    cpu.mem_write(EPILOG, bytes.fromhex("4e800020"))

    def file_size(filename, *_):
        assert filename == NAME
        assert cpu.mem_read(filename, 10) == b"movie.rel\0"
        events.append("size")
        return size

    def allocate(amount, *_):
        events.append(("allocate", amount))
        return next(allocations)

    def read(filename, target, _):
        assert (filename, target) == (NAME, IMAGE)
        events.append("read")
        cpu.mem_write(target, bytes(0x80))
        cpu.mem_write(target + 0x20, struct.pack(">I", bss_size))

    def link(header, storage, _):
        events.append(("link", header, storage))
        assert header == IMAGE
        cpu.mem_write(header + 0x34, struct.pack(">II", PROLOG, EPILOG))
        return 1

    game.hook("get_resource_file_size", file_size)
    game.hook("xmalloc__FUl", allocate)
    game.hook("read_disc_file", read)
    game.hook("OSLink", link)
    game.hook("test_prolog", lambda *_: events.append("prolog"))
    game.hook("test_epilog", lambda *_: events.append("epilog"))
    game.hook("OSUnlink", lambda image, *_: events.append(("unlink", image)))
    game.hook("xfree__FPv", lambda address, *_: events.append(("free", address)))
    game.hook("__dl__FPv", lambda address, *_: events.append(("delete", address)))
    for size, bss_size, results, final, expected in (
        (-1, 32, (), (0, 0), ["size"]),
        (0, 32, (), (0, 0), ["size"]),
        (128, 32, (0,), (0, 0), ["size", ("allocate", 128)]),
        (128, 32, (IMAGE, 0), (0, IMAGE), ["size", ("allocate", 128), "read", ("allocate", 32)]),
        (128, 0, (IMAGE,), (0, IMAGE), ["size", ("allocate", 128), "read", ("link", IMAGE, 0), "prolog"]),
        (128, 32, (IMAGE, BSS), (BSS, IMAGE),
         ["size", ("allocate", 128), "read", ("allocate", 32), ("link", IMAGE, BSS), "prolog"]),
    ):
        allocations = iter(results)
        events.clear()
        cpu.mem_write(MODULE - 4, b"\xcd" * 16)
        assert game.call("load_rel_module", MODULE, NAME) == MODULE
        assert events == expected
        assert bytes(cpu.mem_read(MODULE - 4, 16)) == b"\xcd" * 4 + struct.pack(">II", *final) + b"\xcd" * 4
        assert game.call("get_rel_module_image", MODULE) == final[1]
    for bss, image in ((0, 0), (BSS, 0), (0, IMAGE), (BSS, IMAGE)):
        for delete in (-1, 0, 1):
            cpu.mem_write(MODULE, struct.pack(">II", bss, image))
            events.clear()
            assert game.call("destroy_rel_module", MODULE, delete) == MODULE
            expected = ["epilog", ("unlink", IMAGE), ("free", IMAGE)] if image else []
            if bss:
                expected.append(("free", bss))
            if delete > 0:
                expected.append(("delete", MODULE))
            assert events == expected
            assert cpu.mem_read(MODULE - 4, 16) == b"\xcd" * 4 + bytes(8) + b"\xcd" * 4
    events.clear()
    assert game.call("destroy_rel_module", 0, 1) == 0 and not events


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dol", type=Path)
    run(parser.parse_args().dol.read_bytes())
    print("Movie REL allocation, entry points, unlink and release passed.")
