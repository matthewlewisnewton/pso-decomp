#!/usr/bin/env python3
"""Controlled execution of pinned original PPC read/caller code, not a game run.

Requires unicorn==2.1.4. Original code is private input; only synthetic data,
explicit external-call models and bounded metadata are used/emitted. The probe
stops before fn_8042EBA4: it never executes LaunchDol or predicts its jump.
"""

import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import re
import struct

from unicorn import Uc, UC_ARCH_PPC, UC_MODE_32, UC_MODE_BIG_ENDIAN, UC_HOOK_CODE
from unicorn import ppc_const as ppc
import unicorn

try:
    from tools.audit_loader_payload_provenance import parse_dol, ORIGINAL_SHA1, write_result
except ModuleNotFoundError:
    from audit_loader_payload_provenance import parse_dol, ORIGINAL_SHA1, write_result


EXECUTE = (
    "launch_switcher_dol", "update_lobby_scene__6TSceneFPCv", "get_resource_file_size__6TLobbyFPCv",
    "get_file_size__6TLobbyFPCv", "read_disc_file", "read_whole_file__8TGStreamFPCvPUc",
    "open__8TGStreamFPvPvi", "reset__8TGStreamFv", "reset_gstream_buffer",
    "find_gsl_entry__FPCvl", "get_gstream_file_size", "read_sectors_sync__8TGStreamFll",
    "destroy_gstream", "set_read_params__6TLobbyFPP10AdxfHandleii", "reset_read_state__6TLobbyFv",
    "draw_chunk_vertices_cached", "TObjPlayer__sub_803E492C",
)
HOOKS = (
    "ADXF_Open", "ADXF_Close", "ADXF_GetFsizeByte", "ADXF_Seek", "ADXF_GetStat",
    "read_checked_align__6TLobbyFPvlPv", "run_frame__6TLobbyFv", "strcmp", "strncpy",
    "strcpy", "strlen", "memset", "memmove", "move_data__FPvPCvUl", "VISetBlack",
    "VIFlush", "VIWaitForRetrace", "GXDrawDone", "fn_8042EAD4", "fn_8042EBA4",
)
GLOBALS = ("resource_decompress_buffer", "chunk_vertex_cache_state", "chunk_render_flags",
           "chunk_vertex_cache_buffer", "lbl_805D77E4", "TItemDrop__gsl_adxf_handle",
           "TItemDrop__gsl_entry_count", "gsl_archive_entries", "gstream_sector_buffer",
           "gstream_file_size", "pending_file_read_handle_ref", "pending_file_read_sector_count",
           "pending_file_read_destination")
BUFFER, ALTERNATE, CACHED, MODEL, RECORDING, ARGUMENT = (
    0x81000000, 0x81080000, 0x81100000, 0x81101000, 0x81102000, 0x81103000)
STOP = 0x813FF000
ENTRY_DISC, ENTRY_GSL, ENTRY_CACHE, ENTRY_STALE = (0x90001000, 0x90002000, 0x90003000, 0x90004000)
SYMBOLS_SHA256 = "2987de0609254a30675f5c8300f88e02568cf34b704ffa951b882e8f259017d9"
REG = [getattr(ppc, f"UC_PPC_REG_{i}") for i in range(32)]


def symbols(text):
    result = {}
    required = set(EXECUTE + HOOKS + GLOBALS)
    for name, address, size in re.findall(
            r"^(\S+) = \.\w+:0x([0-9A-Fa-f]+);[^\n]*?size:0x([0-9A-Fa-f]+)", text, re.M):
        if name not in required:  # Unit-local duplicate labels are not bindings.
            continue
        if name in result:
            raise ValueError(f"duplicate symbol: {name}")
        result[name] = (int(address, 16), int(size, 16))
    if set(result) != required:
        raise ValueError(f"missing required bindings: {sorted(required - set(result))}")
    return result


def synthetic_image(size, entry):
    result = bytearray(size)
    struct.pack_into(">I", result, 0xE0, entry)
    return bytes(result)


class Probe:
    def __init__(self, dol, inventory, case):
        self.sym, self.case = inventory, case
        self.uc = Uc(UC_ARCH_PPC, UC_MODE_32 | UC_MODE_BIG_ENDIAN)
        self.uc.mem_map(0x80000000, 0x800000)
        self.uc.mem_map(BUFFER, 0x400000)
        for s in parse_dol(dol)["sections"]:
            self.uc.mem_write(s["address"], dol[s["offset"]:s["offset"] + s["size"]])
        self.uc.reg_write(REG[1], 0x813F0000)
        # Native linked ELF's _SDA_BASE_ and _SDA2_BASE_, unchanged for this DOL.
        self.uc.reg_write(REG[13], 0x805DA600)
        self.uc.reg_write(REG[2], 0x805DFD00)
        self.allowed = [(inventory[n][0], inventory[n][0] + inventory[n][1]) for n in EXECUTE]
        self.hooks = {inventory[n][0]: n for n in HOOKS}
        self.steps, self.event, self.calls, self.reads, self.frames = 0, None, [], [], 0
        self.timeline = []
        self.entries = Counter()
        self.returns = {}
        self.opens, self.polls, self.offset = 0, 0, 0
        self.pending = None
        self.forwarded = None
        self.uc.hook_add(UC_HOOK_CODE, self.instruction)
        self.starts = {inventory[n][0]: n for n in EXECUTE}
        self.put("gstream_file_size", 0x12345678)
        if self.call("get_gstream_file_size", []) != 0x12345678:
            raise RuntimeError("SDA/global binding control failed")
        self.put("gstream_file_size", 0)
        self.disc = synthetic_image(4864, ENTRY_DISC)
        self.archive = synthetic_image(6912, ENTRY_GSL)
        self.payload = self.disc
        self.write(BUFFER, synthetic_image(0x80000, ENTRY_STALE))
        self.write(CACHED, synthetic_image(0x100, ENTRY_CACHE))
        self.write(ARGUMENT, b"synthetic-argument\0")
        self.put("resource_decompress_buffer", BUFFER)
        self.put("chunk_vertex_cache_state", RECORDING)
        self.put("lbl_805D77E4", 4)
        self.word(RECORDING, CACHED)
        self.word(RECORDING + 4, 0 if case == "callback_empty" else 0x100)
        self.call("TObjPlayer__sub_803E492C", [ALTERNATE if case == "callback_unaliased" else BUFFER, 0x2000])
        if self.word(self.sym["chunk_vertex_cache_buffer"][0]) != (ALTERNATE if case == "callback_unaliased" else BUFFER):
            raise RuntimeError("cache setter/global binding control failed")
        # The original setter clears flags; apply the chosen callback precondition afterwards.
        self.put("chunk_render_flags", 4 if case == "callback_guarded" else 0)
        if case in ("gsl_match", "gsl_miss"):
            self.put("TItemDrop__gsl_adxf_handle", 0x81104000)
            self.put("TItemDrop__gsl_entry_count", 1)
            start = self.sym["gsl_archive_entries"][0]
            self.write(start, b"switcher.dol\0" if case == "gsl_match" else b"different.dol\0")
            self.word(start + 0x20, 7)
            self.word(start + 0x24, len(self.archive))

    def word(self, address, value=None):
        if value is None:
            return struct.unpack(">I", self.uc.mem_read(address, 4))[0]
        self.write(address, struct.pack(">I", value & 0xFFFFFFFF))

    def put(self, name, value):
        self.word(self.sym[name][0], value)

    def write(self, address, data):
        self.uc.mem_write(address, data)

    def string(self, address):
        data = bytearray()
        for offset in range(256):
            value = self.uc.mem_read(address + offset, 1)[0]
            if not value:
                return bytes(data)
            data.append(value)
        raise RuntimeError("unterminated synthetic string")

    def instruction(self, uc, pc, size, user):
        self.steps += 1
        if self.steps > 20000:
            raise RuntimeError("instruction bound exceeded")
        if pc == STOP or pc in self.hooks:
            self.event = "return" if pc == STOP else self.hooks[pc]
            uc.emu_stop()
        elif size != 4 or pc % 4 or not any(start <= pc and pc + size <= end for start, end in self.allowed):
            raise RuntimeError(f"unmodeled code boundary 0x{pc:08X}")
        elif pc in self.starts:
            self.entries[self.starts[pc]] += 1
        start, length = self.sym["read_whole_file__8TGStreamFPCvPUc"]
        if pc == start + length - 4:
            if bytes(uc.mem_read(pc, 4)) != b"\x4e\x80\x00\x20":
                raise RuntimeError("read return observation is not blr")
            self.returns["read_whole_file"] = uc.reg_read(REG[3])

    def call(self, name, arguments):
        for i, value in enumerate(arguments, 3):
            self.uc.reg_write(REG[i], value)
        self.uc.reg_write(ppc.UC_PPC_REG_LR, STOP)
        self.uc.reg_write(ppc.UC_PPC_REG_PC, self.sym[name][0])
        while True:
            self.event = None
            self.uc.emu_start(self.uc.reg_read(ppc.UC_PPC_REG_PC), STOP + 4, count=20001)
            event = self.event
            if event == "return":
                return self.uc.reg_read(REG[3])
            if event is None:
                raise RuntimeError("execution stopped without a modeled boundary")
            args = [self.uc.reg_read(REG[i]) for i in range(3, 6)]
            self.calls.append(event)
            value = self.handle(event, args)
            if event == "fn_8042EBA4" or value == "bounded_wait":
                return value
            # GPR-only call model: CR/CTR/FPR state is retained, not full ABI emulation.
            target = self.uc.reg_read(ppc.UC_PPC_REG_LR)
            for reg in [0, *range(3, 13)]:
                self.uc.reg_write(REG[reg], 0xBAD00000 + reg)
            self.uc.reg_write(REG[3], value & 0xFFFFFFFF)
            self.uc.reg_write(ppc.UC_PPC_REG_PC, target)

    def handle(self, name, a):
        x, y, z = a
        if name == "fn_8042EBA4":
            self.forwarded = dict(buffer=x, queried_size=y, header_entry=self.word(x + 0xE0))
            return 0
        elif name == "ADXF_Open":
            self.opens += 1
            return 0 if self.case == "size_failure" and self.opens == 2 else 0x81105000
        elif name == "ADXF_GetFsizeByte":
            return len(self.disc)
        elif name == "ADXF_Seek":
            self.payload = self.archive
            self.offset = 0
            return 0
        elif name == "read_checked_align__6TLobbyFPvlPv":
            self.polls = 0
            self.pending = (z, self.payload[self.offset:self.offset + y * 2048])
            self.reads.append(dict(sectors=y, destination=z))
            self.offset += y * 2048
            self.timeline.append(dict(event="read_start", request=len(self.reads),
                                      pending_destination=self.word(self.sym["pending_file_read_destination"][0])))
            return -3 if self.case == "start_failure_wait" else y
        elif name == "ADXF_GetStat":
            self.polls += 1
            if self.case == "start_failure_wait":
                return "bounded_wait" if self.polls == 9 else 2
            if self.case.startswith("callback_") and len(self.reads) == 2 and self.polls == 1:
                return 2
            address, data = self.pending
            self.write(address, data.ljust(self.reads[-1]["sectors"] * 2048, b"\0"))
            self.pending = None
            self.timeline.append(dict(event="read_complete", request=len(self.reads),
                pending_count=self.word(self.sym["pending_file_read_sector_count"][0]),
                pending_destination=self.word(self.sym["pending_file_read_destination"][0])))
            return 3
        elif name == "run_frame__6TLobbyFv":
            self.frames += 1
            before = self.word(BUFFER + 0xE0)
            if self.case.startswith("callback_"):
                saved = self.uc.context_save()
                self.call("draw_chunk_vertices_cached", [MODEL])
                self.uc.context_restore(saved)
            self.timeline.append(dict(event="frame_callback", request=len(self.reads),
                                      buffer_entry_before=before, buffer_entry_after=self.word(BUFFER + 0xE0)))
            return 0
        elif name in ("memmove", "move_data__FPvPCvUl"):
            self.write(x, bytes(self.uc.mem_read(y, z)))
            return x
        elif name == "memset":
            self.write(x, bytes([y & 255]) * z)
            return x
        elif name == "strlen":
            return len(self.string(x))
        elif name in ("strncpy", "strcpy"):
            data = self.string(y)
            self.write(x, data[:z].ljust(z, b"\0") if name == "strncpy" else data + b"\0")
            return x
        elif name == "strcmp":
            left, right = self.string(x), self.string(y)
            return (left > right) - (left < right)
        elif name in ("VISetBlack", "GXDrawDone"):
            self.timeline.append(dict(event=name, buffer_entry=self.word(BUFFER + 0xE0)))
            return 0
        elif name in ("ADXF_Close", "VIFlush", "VIWaitForRetrace", "fn_8042EAD4"):
            return 0
        raise RuntimeError(f"missing explicit boundary model: {name}")

    def run(self):
        status = self.call("launch_switcher_dol", [ARGUMENT])
        return dict(case=self.case, status="bounded_wait" if status == "bounded_wait" else "forwarded",
                    forwarded=self.forwarded, read_requests=self.reads, frame_callbacks=self.frames,
                    buffer_entry=self.word(BUFFER + 0xE0), alternate_entry=self.word(ALTERNATE + 0xE0),
                    file_open_calls=self.opens,
                    external_call_events=self.calls, timeline=self.timeline,
                    original_function_entries=dict(self.entries),
                    observed_return_values=self.returns,
                    pending_read_after_stop={name:self.word(self.sym[name][0]) for name in
                        ("pending_file_read_handle_ref", "pending_file_read_sector_count", "pending_file_read_destination")})


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dol", type=Path, required=True)
    parser.add_argument("--symbols", type=Path, default=Path("config/GPOE8P/psov3/symbols.txt"))
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if unicorn.__version__ != "2.1.4":
        parser.error("requires pinned unicorn==2.1.4")
    data = args.dol.read_bytes()
    if hashlib.sha1(data).hexdigest() != ORIGINAL_SHA1:
        parser.error("game DOL does not match pinned input")
    raw_symbols = args.symbols.read_bytes()
    if hashlib.sha256(raw_symbols).hexdigest() != SYMBOLS_SHA256:
        parser.error("symbol inventory changed; reauthenticate bindings before using the probe")
    inventory = symbols(raw_symbols.decode())
    text = [s for s in parse_dol(data)["sections"] if s["kind"] == "text"]
    for name in EXECUTE:
        start, size = inventory[name]
        end = start + size
        if not size or start % 4 or size % 4 or not any(s["address"] <= start and end <= s["address"] + s["size"] for s in text):
            parser.error(f"unsupported executable range for {name}")
        if start < 0x8042EAD4 and end > 0x8042E8C4:
            parser.error("execution allowlist intersects held loader/restore/initializer")
        helper, length = inventory["fn_8042EBA4"]
        if start < helper + length and end > helper:
            parser.error("execution allowlist intersects forwarding helper")
    if len({inventory[n][0] for n in HOOKS}) != len(HOOKS):
        parser.error("aliased boundary models")
    cases = ("disc_success", "gsl_match", "gsl_miss", "size_failure", "callback_alias",
             "callback_guarded", "callback_empty", "callback_unaliased", "start_failure_wait")
    results = [Probe(data, inventory, case).run() for case in cases]
    expected = (ENTRY_DISC, ENTRY_GSL, ENTRY_DISC, ENTRY_STALE, ENTRY_CACHE,
                ENTRY_DISC, ENTRY_DISC, ENTRY_DISC, None)
    for row, value in zip(results, expected):
        if value is None:
            assert row["status"] == "bounded_wait" and row["forwarded"] is None
        else:
            assert row["forwarded"]["header_entry"] == value, row
    for row in results:
        name = row["case"]
        assert row["original_function_entries"]["launch_switcher_dol"] == 1
        assert row["original_function_entries"]["open__8TGStreamFPvPvi"] == 1
        assert row["original_function_entries"]["find_gsl_entry__FPCvl"] == 2
        expected_requests = [] if name == "size_failure" else [
            dict(sectors=3 if name == "gsl_match" else 2, destination=BUFFER)]
        if name not in ("size_failure", "start_failure_wait"):
            expected_requests.append(dict(sectors=1, destination=inventory["gstream_sector_buffer"][0]))
        assert row["read_requests"] == expected_requests
        assert row["frame_callbacks"] == (8 if name == "start_failure_wait" else 1 if name.startswith("callback_") else 0)
        assert row["original_function_entries"].get("draw_chunk_vertices_cached", 0) == int(name.startswith("callback_"))
        assert row["alternate_entry"] == (ENTRY_CACHE if name == "callback_unaliased" else 0)
        if row["status"] == "forwarded":
            assert row["forwarded"]["buffer"] == BUFFER
            assert row["forwarded"]["queried_size"] == (6912 if row["case"] == "gsl_match" else 4864)
            assert all(value == 0 for value in row["pending_read_after_stop"].values())
        if row["case"].startswith("callback_"):
            assert row["frame_callbacks"] == 1
            assert row["external_call_events"].index("VISetBlack") > row["external_call_events"].index("run_frame__6TLobbyFv")
        if row["read_requests"] and row["status"] == "forwarded":
            completed = [i for i, event in enumerate(row["timeline"]) if event["event"] == "read_complete"]
            assert len(completed) == len(row["read_requests"])
            black = next(i for i, event in enumerate(row["timeline"]) if event["event"] == "VISetBlack")
            assert max(completed) < black
            for index in completed:
                event = row["timeline"][index]
                request = row["read_requests"][event["request"] - 1]
                assert event["pending_count"] == request["sectors"] and event["pending_destination"] == request["destination"]
        if row["case"] == "callback_unaliased":
            assert row["alternate_entry"] == ENTRY_CACHE
        if row["case"] == "size_failure":
            assert row["read_requests"] == []
            assert row["observed_return_values"]["read_whole_file"] == 0xFFFFFFFF
        elif row["status"] == "forwarded":
            assert row["observed_return_values"]["read_whole_file"] == (6912 if name == "gsl_match" else 4864)
        else:
            assert row["observed_return_values"] == {}
            assert row["pending_read_after_stop"]["pending_file_read_sector_count"] == 2
            assert row["pending_read_after_stop"]["pending_file_read_destination"] == BUFFER
        if row["case"] == "gsl_match":
            assert row["file_open_calls"] == 0
    write_result(args.output, dict(original_sha1=ORIGINAL_SHA1, symbols_sha256=SYMBOLS_SHA256,
        unicorn_version=unicorn.__version__, results=results,
        assumptions="Synthetic 4864/6912-byte images and initialized fixture memory; chosen I/O outcomes, "
        "completion timing and single draw-cache callback replace external device/frame behavior. "
        "All unseeded mapped memory starts zero; no runtime state is inferred. Boundary returns "
        "clobber volatile GPRs but retain CR/CTR/FPR state: this is not full ABI emulation.",
        limits="Explicit synthetic I/O and callback boundary models, not a hardware/game run. "
        "No selected source, status sequence, callback reachability or runtime header value is proved. "
        "Execution stops before the forwarding helper; all loader/restore ownership holds remain."))
    print(f"Nine controlled cases pass; wrote metadata to {args.output}.")


if __name__ == "__main__":
    main()
