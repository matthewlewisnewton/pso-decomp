#!/usr/bin/env python3
"""Exercise the linked GPOE8P ADXF implementation with synthetic streams and an AFS directory."""
import argparse
from pathlib import Path
import struct

from gpoe8p_image import GameImage

FILENAME = 0x81111000
DESTINATION = 0x81112020

STREAM = 0x8112A000
DIRECTORY = 0x8112B000
HANDLE_SIZE = 0x138
BAD_ARGUMENT = 0xFFFFFFFD
NOTIFY = "notify_error__6TLobbyFPCc"
CLOSE_STREAM = "TLobby__sub_803C8B38"
OPEN_STREAM = "TLobby__sub_803C8CDC"
OPEN_RANGE = "adxstm_open_fname_range__6TLobbyFPviiii"


class Adxf(GameImage):
    def __init__(self, dol):
        super().__init__(dol)
        self.pool = self.symbols["adxf_file_handle_pool"]
        self.stream_result = STREAM
        self.cpu.mem_write(FILENAME, b"test.afs\0")
        for name in ("init_once__6TLobbyFv", "release_ref__6TLobbyFv", CLOSE_STREAM, NOTIFY):
            self.hook(name, lambda *_: 0)
        self.hook(OPEN_STREAM, self.open_stream)
        self.hook(OPEN_RANGE, lambda *_: self.stream_result)

    def open_stream(self, name, mode, unused):
        self.cpu.mem_write(STREAM + 0x14, struct.pack(">I", 6145))
        return self.stream_result

    def check_open(self):
        handles = []
        for index in range(16):
            handle = self.call("ADXF_Open", FILENAME, index)
            assert handle == self.pool + index * HANDLE_SIZE
            handles.append(handle)
            assert self.calls[OPEN_STREAM] == [(FILENAME, index, 0)]
            assert self.call("ADXF_GetStat", handle) == 1
            assert self.call("ADXF_GetFsizeByte", handle) == 6145
            assert self.call("ADXF_GetFsizeSct", handle) == 4
        assert self.call("ADXF_Open", FILENAME, 0) == 0
        assert OPEN_STREAM not in self.calls
        for handle in handles:
            self.call("ADXF_Close", handle)
            assert self.calls[CLOSE_STREAM][0][0] == STREAM
            assert self.cpu.mem_read(handle, HANDLE_SIZE) == bytes(HANDLE_SIZE)
        self.stream_result = 0
        assert self.call("ADXF_Open", FILENAME, 0) == 0
        assert self.cpu.mem_read(self.pool, HANDLE_SIZE) == bytes(HANDLE_SIZE)
        self.stream_result = STREAM
        assert self.call("ADXF_Open", 0, 0) == 0
        assert OPEN_STREAM not in self.calls and NOTIFY in self.calls

    def check_archive(self):
        partition = 42
        table = self.symbols["afs_archive_toc_table"]
        self.cpu.mem_write(table + 4 * partition, struct.pack(">I", DIRECTORY))
        self.cpu.mem_write(DIRECTORY + 8, struct.pack(">I", 3))
        self.cpu.mem_write(DIRECTORY + 0x10, b"test.afs\0")
        self.cpu.mem_write(DIRECTORY + 0x110, struct.pack(">I4H", 7, 100, 9, 12, 5))
        for index, start, length in ((0, 100, 9), (1, 109, 12), (2, 121, 5)):
            handle = self.call("ADXF_OpenAfs", partition, index)
            assert handle == self.pool
            name, mode, first_sector = self.calls[OPEN_RANGE][0]
            assert self.cpu.mem_read(name, 9) == b"test.afs\0"
            assert (mode, first_sector) == (7, start)
            assert self.call("ADXF_GetFsizeByte", handle) == length * 2048
            assert self.call("ADXF_GetFsizeSct", handle) == length
            self.call("ADXF_Close", handle)
        for part, file in ((-1, 0), (256, 0), (0, 0), (partition, -1), (partition, 3)):
            assert self.call("ADXF_OpenAfs", part, file) == 0
            assert OPEN_RANGE not in self.calls and NOTIFY in self.calls

    def check_seeks_and_reads(self):
        handle = self.call("ADXF_Open", FILENAME, 0)
        for origin in range(3):
            for start in range(5):
                for delta in (-8, -1, 0, 1, 8):
                    self.call("ADXF_Seek", handle, start, 0)
                    base = (0, start, 4)[origin]
                    assert self.call("ADXF_Seek", handle, delta, origin) == max(0, min(base + delta, 4))
        assert self.call("ADXF_Seek", handle, 1, 3) == BAD_ARGUMENT
        assert self.call("ADXF_Stop", handle) == 4
        for op in ("ADXF_GetStat", "ADXF_GetFsizeByte", "ADXF_GetFsizeSct",
                   "ADXF_Seek", "ADXF_Stop", "ADXF_ReadNw32"):
            assert self.call(op, 0, 1, DESTINATION) == BAD_ARGUMENT
            assert NOTIFY in self.calls
        assert self.call("ADXF_ReadNw32", handle, -1, DESTINATION) == BAD_ARGUMENT
        assert self.call("ADXF_ReadNw32", handle, 1, 0) == BAD_ARGUMENT
        # The real SJ ring buffer and its virtual destructor run on the EOF path.
        assert self.call("ADXF_ReadNw32", handle, 1, DESTINATION) == 0
        assert self.call("ADXF_GetStat", handle) == 3
        assert self.call("ADXF_Stop", handle) == 4
        assert self.call("ADXF_GetStat", handle) == 1
        self.call("ADXF_Close", handle)

    def check_pending_reads(self):
        progress = 0
        status = 1

        def report_progress(stream, destination, unused):
            assert stream == STREAM
            self.cpu.mem_write(destination, struct.pack(">i", progress))
            return 1

        self.hook("TLobby__sub_803C8B2C", lambda *_: status)
        self.hook("TLobby__sub_803C85AC", report_progress)
        for name in ("TLobby__sub_803C89C4", "set_field_10_and_notify__6TLobbyFl",
                     "init_stream_position__6TLobbyFv", "set_scroll_position__6TLobbyFl"):
            self.hook(name, lambda *_: 0)

        for terminal in (3, 4):
            handle = self.call("ADXF_OpenAfs", 42, 1)
            assert self.call("ADXF_Seek", handle, 10, 0) == 10
            # Entry one starts at sector 109 and has two sectors left at position ten.
            assert self.call("ADXF_ReadNw32", handle, 5, DESTINATION) == 2
            assert self.calls["set_field_10_and_notify__6TLobbyFl"][0][:2] == (STREAM, 119)
            assert self.call("ADXF_GetStat", handle) == 2
            assert self.call("ADXF_ReadNw32", handle, 1, DESTINATION) == 0
            progress, status = 1, 2
            self.call("TLobby__sub_803CC884")
            assert self.call("ADXF_GetStat", handle) == 2
            progress, status = 2, terminal
            self.call("TLobby__sub_803CC884")
            assert self.call("ADXF_GetStat", handle) == terminal
            assert self.call("ADXF_Seek", handle, 0, 1) == 12
            self.call("ADXF_Close", handle)
            status = 1

        handle = self.call("ADXF_Open", FILENAME, 0)
        for cancel in ("ADXF_Stop", "ADXF_Seek", "ADXF_Close"):
            assert self.call("ADXF_ReadNw32", handle, 2, DESTINATION) == 2
            self.call(cancel, handle, 1, 0)
            assert self.calls["TLobby__sub_803C89C4"][0][0] == STREAM
            if cancel == "ADXF_Close":
                assert self.cpu.mem_read(handle, HANDLE_SIZE) == bytes(HANDLE_SIZE)
            else:
                assert self.call("ADXF_GetStat", handle) == 1


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dol", type=Path, nargs="+")
    if not __debug__:
        parser.error("run with assertions enabled")
    for path in parser.parse_args().dol:
        adxf = Adxf(path.read_bytes())
        adxf.check_open()
        adxf.check_archive()
        adxf.check_seeks_and_reads()
        adxf.check_pending_reads()
        print(f"{path}: ADXF pool, directory, 75 seeks, reads, cancellation and error cases passed")


if __name__ == "__main__":
    main()
