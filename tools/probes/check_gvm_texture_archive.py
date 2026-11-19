"""Exercise GVM file loading, directory flags and entry lookup against GPOE8P."""
import argparse
from pathlib import Path
import struct

from gpoe8p_image import GameImage


FILENAME = 0x81110000
SHARED = 0x81111000
LARGE = 0x81112000
LIST = 0x81114000
SEARCH = 0x81115000
GUARD = b"\xcd" * 8
NAMES = (b"frame-blue", b"frame-red")


def directory(flags):
    records = []
    for i, name in enumerate(NAMES):
        record = struct.pack(">H", 1 - i)
        if flags & 1:
            record += name.ljust(28, b"\0")
        if flags & 2:
            record += b"\x13\x57"
        if flags & 4:
            record += b"\xac\xed"
        if flags & 8:
            record += struct.pack(">I", 0x10000800 + i)
        records.append(record)
    return b"".join(records)


def archive(flags, count):
    table = directory(flags) if count else b""
    header = b"GVMH" + struct.pack("<I", len(table) + 4) + struct.pack(">HH", flags, count)
    chunk = b"GVRT" + struct.pack("<I", 12) + bytes(12)
    return header + table + chunk * count


def run(dol):
    game = GameImage(dol)
    cpu = game.cpu
    cpu.mem_write(FILENAME, b"test.gvm\0")
    error = game.symbols["lbl_8058D470"]

    def string(address):
        return bytes(cpu.mem_read(address, 64)).split(b"\0", 1)[0]

    def size(address, *_):
        assert address == FILENAME
        return file_size

    def read(address, target, _):
        assert address == FILENAME and target == storage
        cpu.mem_write(target, archive(flags, count))
        return file_size

    def allocate_list(number, size, _):
        assert (number, size) == (1, 8 + 44 * count)
        cpu.mem_write(LIST - 8, GUARD + bytes(size) + GUARD)
        return LIST

    def acquire(label, *_):
        assert string(label) == b"LoadPvmFileTls"
        return SHARED

    def acquire_large(size, *_):
        assert size == (file_size + 2047) // 2048 * 2048
        return LARGE

    def debug(fmt, filename, _):
        assert filename == FILENAME and b"%s" in string(fmt)

    game.hook("pump_frames__6TLobbyFv", lambda *_: None)
    game.hook("get_resource_file_size__8TGStreamFPCc", size)
    game.hook("debug_print__6TLobbyFPCce", debug)
    game.hook("load_sct_file__8TGStreamFPCcPUc", read)
    game.hook("tmp_buf_use_req__6TLobbyFPCc", acquire)
    game.hook("alloc__22TQuestVmDownLoadServerFUl", acquire_large)
    game.hook("TQuestVmDownLoadServer__sub_8007EBDC", allocate_list)
    game.hook("tmp_buf_release__6TLobbyFPCc", lambda *_: None)
    game.hook("safe_free__FPv", lambda *_: None)
    # Texture slot 1 means an existing GPU entry can be reused.
    game.hook("TObjPlayer__sub_803D9E38", lambda *_: 1)

    for file_size in (-1, 0):
        assert game.call("load_gvm_texture_file", FILENAME) == 0
        assert len(game.calls["debug_print__6TLobbyFPCce"]) == 1
        assert "load_sct_file__8TGStreamFPCcPUc" not in game.calls

    for file_size, storage, count in ((0x40000, SHARED, 0), (0x40001, LARGE, 0),
                                      (0x40000, SHARED, 2), (0x40001, LARGE, 2)):
        for flags in (*range(16), 0x408, 0x40f):
            result = game.call("load_gvm_texture_file", FILENAME)
            if storage == SHARED:
                label, *_ = game.calls["tmp_buf_release__6TLobbyFPCc"][0]
                assert string(label) == b"LoadPvmFileTls"
                assert "safe_free__FPv" not in game.calls
            else:
                assert game.calls["safe_free__FPv"][0][0] == LARGE
                assert "tmp_buf_release__6TLobbyFPCc" not in game.calls
            if not count:
                assert result == 0 and "TQuestVmDownLoadServer__sub_8007EBDC" not in game.calls
                continue
            assert result == LIST
            entry_base = LIST + 8
            assert cpu.mem_read(LIST, 8) == struct.pack(">II", entry_base, count)
            assert cpu.mem_read(LIST - 8, 8) == GUARD
            assert cpu.mem_read(LIST + 8 + count * 44, 8) == GUARD
            assert [(args[0], args[1]) for args in game.calls["TObjPlayer__sub_803D9E38"]] == [(LIST, 1), (LIST, 0)]
            for i, name in enumerate(NAMES):
                address, attributes, index = struct.unpack(">III", cpu.mem_read(entry_base + 12 * i, 12))
                assert address == entry_base + count * 12 + i * 32
                assert string(address) == (name if flags & 1 else b"")
                high = (0x01000000 if flags & 0x400 else 0x00800000) if flags & 8 else 0
                assert attributes == high | (1 - i)
                assert index == (0x10000800 + i if flags & 8 else 0)
                cpu.mem_write(SEARCH, name + b"\0")
                assert game.call("find_texture_entry_by_name", LIST, SEARCH) == (i if flags & 1 else 0xffffffff)
    for address in (0, LIST):
        cpu.mem_write(LIST, bytes(8))
        assert game.call("find_texture_entry_by_name", address, SEARCH) == 0xffffffff
    assert game.call("load_gvm_texture_archive", 0, LIST) == 0xffffffff
    assert cpu.mem_read(error + 8, 4) == struct.pack(">I", 1)
    cpu.mem_write(SHARED, b"NONE" + bytes(8))
    assert game.call("load_gvm_texture_archive", SHARED, LIST) == 0xffffffff
    assert cpu.mem_read(error + 8, 4) == struct.pack(">I", 4)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dol", type=Path)
    run(parser.parse_args().dol.read_bytes())
    print("GVM file buffers, directory flags, texture indices and name lookup passed.")
