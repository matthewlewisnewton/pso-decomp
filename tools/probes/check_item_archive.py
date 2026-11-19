#!/usr/bin/env python3
"""Exercise the item model and texture archive loaders in a linked GameCube image."""
import argparse
from pathlib import Path
import struct

from unicorn import ppc_const as ppc
from gpoe8p_image import GameImage

OBJECT = 0x81111020
FILENAME = 0x81112000
BUFFER = 0x81113000
HANDLE = 0x81114000
DESTINATION = 0x81116000
GUARD = b"\xa5" * 16
READER = "__17ItemArchiveReader"
LOADER = "__13TUnk_8049F42C"
OPEN = "ADXF_OpenAfs"
CLOSE = "ADXF_Close"
SIZE = "ADXF_GetFsizeSct"
STATUS = "ADXF_GetStat"
READ = "ADXF_ReadNw32"
ERROR = "notify_error__6TLobbyFPCc"


class ItemArchive(GameImage):
    def __init__(self, image):
        super().__init__(image)
        self.handle = HANDLE
        self.status = 2
        self.hook(OPEN, lambda *_: self.handle)
        self.hook(SIZE, lambda *_: 9)
        self.hook(CLOSE, lambda *_: 0)
        self.hook(STATUS, lambda *_: self.status)
        self.hook(READ, lambda *_: 17)
        self.hook(ERROR, lambda *_: 0)
        self.hook("__nwa__FUl", lambda *_: BUFFER)
        self.hook("TLobby__sub_801E3E9C", lambda *_: 0)
        self.set_word(self.symbols["item_load_compressed_work_buffer"], DESTINATION)
        self.busy = self.symbols["item_load_work_buffer_busy"]

    def word(self, address):
        return struct.unpack(">I", self.cpu.mem_read(address, 4))[0]

    def set_word(self, address, value):
        self.cpu.mem_write(address, struct.pack(">I", value))

    def initialize(self, texture):
        suffix = "41C" if texture else "40C"
        size = 0x28 if texture else 0x40
        name = "construct" if texture else "construct_with_vtable"
        partition, files = (0xB5, 0x144) if texture else (0xB4, 0x12F)
        self.cpu.mem_write(OBJECT - len(GUARD), GUARD + b"\xcc" * size + GUARD)
        self.set_word(self.busy, 0)
        self.cpu.reg_write(ppc.UC_PPC_REG_6, files)
        self.call(name + "__13TUnk_8049F" + suffix + "FPCcll", OBJECT, FILENAME, partition)
        assert self.calls["__nwa__FUl"][0][0] == ((files + 1) * 2 + 0x116) & ~3
        assert self.calls["TLobby__sub_801E3E9C"] == [(partition, FILENAME, BUFFER)]
        assert [self.word(OBJECT + i) for i in range(0, 0x20, 4)] == [
            BUFFER, 0, partition, 0, 1, self.symbols["lbl_8049F" + suffix], 0, 0]
        assert self.cpu.mem_read(OBJECT - len(GUARD), len(GUARD)) == GUARD
        assert self.cpu.mem_read(OBJECT + size, len(GUARD)) == GUARD
        return partition

    def reader_cases(self):
        for mode in (0, 1, 2):
            for previous in (0, HANDLE + 4):
                for self.handle in (0, HANDLE):
                    partition = self.initialize(True)
                    self.set_word(OBJECT + 4, previous)
                    self.set_word(OBJECT + 12, 28)
                    self.set_word(OBJECT + 16, mode)
                    result = self.call("open" + READER + "Fl", OBJECT, 13)
                    expected = self.handle if mode == 1 else previous
                    assert result == self.word(OBJECT + 4) == expected
                    sectors = 9 if mode == 1 and expected else 0 if mode == 1 and previous else 28
                    assert self.word(OBJECT + 12) == sectors
                    events = ([CLOSE] if previous else []) + [OPEN] + ([SIZE] if expected else [])
                    assert list(self.calls) == (events if mode == 1 else [])
                    if OPEN in self.calls:
                        assert self.calls[OPEN][0][:2] == (partition, 13)
                    if CLOSE in self.calls:
                        assert self.calls[CLOSE][0][0] == previous
                    if SIZE in self.calls:
                        assert self.calls[SIZE][0][0] == expected
                    assert self.call("get_status" + READER + "Fv", OBJECT) == self.status
                    assert self.calls[STATUS][0][0] == expected
                    self.call("close" + READER + "Fv", OBJECT)
                    assert self.word(OBJECT + 4) == 0
                    assert self.word(OBJECT + 12) == (0 if expected else sectors)

    def lifecycle(self, texture, status):
        partition = self.initialize(texture)
        self.handle = HANDLE
        self.status = 2
        assert self.call("begin_load" + LOADER + "Fl", OBJECT, 42) == 1
        assert self.call("begin_load" + LOADER + "Fl", OBJECT, 45) == 0
        self.set_word(self.busy, 1)
        self.call("update_state" + LOADER + "Fv", OBJECT)
        assert not self.calls and self.word(OBJECT + 0x18) == 1
        self.set_word(self.busy, 0)
        self.call("update_state" + LOADER + "Fv", OBJECT)
        assert self.calls[OPEN][0][:2] == (partition, 42)
        assert self.calls[READ] == [(HANDLE, 9, DESTINATION)]
        assert self.word(OBJECT + 0x18) == 2 and self.word(self.busy) == 1
        self.call("update_state" + LOADER + "Fv", OBJECT)
        assert list(self.calls) == [STATUS] and self.word(OBJECT + 0x18) == 2
        self.status = status
        self.call("update_state" + LOADER + "Fv", OBJECT)
        assert list(self.calls) == [STATUS, CLOSE]
        assert self.word(OBJECT + 4) == self.word(OBJECT + 12) == 0
        assert self.word(OBJECT + 0x18) == (4 if status == 3 else 1)
        if status == 3:
            callback = "vfunc_3__13TUnk_8049F" + ("41C" if texture else "40C") + "Fv"
            self.call("update_state" + LOADER + "Fv", OBJECT)
            assert self.calls[callback][0][0] == OBJECT
        self.call("reset_state" + LOADER + "Fv", OBJECT)
        assert self.word(OBJECT + 0x18) == self.word(self.busy) == 0
        assert self.word(OBJECT + 0x1C) == (2 if status == 3 else 3)


def check(path):
    game = ItemArchive(path.read_bytes())
    game.reader_cases()
    for suffix in ("40C", "41C"):
        game.hook("vfunc_3__13TUnk_8049F" + suffix + "Fv", lambda *_: None)
    for texture in (False, True):
        for status in (0, 1, 3, 4):
            game.lifecycle(texture, status)
    for offset in range(32):
        result = game.call("ADXF_ReadNw", HANDLE, 7, DESTINATION + offset)
        if offset:
            assert result == 0xFFFFFFFD and list(game.calls) == [ERROR]
        else:
            assert result == 17 and game.calls[READ] == [(HANDLE, 7, DESTINATION)]
    print(f"{path}: 12 archive opens, eight loader lifecycles and 32 read alignments passed")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dol", nargs="+", type=Path)
    if not __debug__:
        parser.error("run with assertions enabled")
    for dol in parser.parse_args().dol:
        check(dol)
