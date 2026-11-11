#!/usr/bin/env python3
"""Original menu-update controls for retaining or replacing a phase-19 request.

Uses explicit synthetic factory/platform/account predicates; not a retail run.
Original request setter, title action, menu update, card-state getter and main
dispatcher execute. Stops at the modem helper or a modeled shutdown boundary.
"""

import argparse
import hashlib
from pathlib import Path
import re

try:
    from tools import probe_loader_phase_cleanup as phase
except ModuleNotFoundError:
    import probe_loader_phase_cleanup as phase

read = phase.read
EXECUTE = ("fn_8023F3F8", "open_keyboard__13TUnk_804EEF64Fv", "TKeyBoardControl__sub_8000F9CC",
           "TKeyBoardControl__sub_8000F92C", "get_instance__15TAdPlayerLoadGCFv")
NOOPS = ("func_803DCDFC__Fv", "controller_stuff__Fv", "update_input_frame__16TKeyBoardControlFv",
         "begin_frame__9TMainTaskFv", "run_task__9TMainTaskFv", "render__9TMainTaskFv",
         "render_screen_overlay__9TMainTaskFv", "process_async_file_reads__Fv",
         "update_sound_request_slots__Fv", "run_save_load_sequence__23TAdSinglePlyChrSelectGCFv",
         "noop__23TAdSinglePlyChrSelectGCFv", "render_tick__Fv")
MODELS = ("create_mode_scene__21TAdMultiChgGameModeGCFv", "func_801A5E54__Fv",
          "is_ready__22TQuestVmDownLoadServerFv")
GLOBALS = ("lbl_805D63C8", "card_load_sequence_state", "lobby_game_mode_state")


def bindings(text):
    result = phase.bindings(text)
    for name in EXECUTE + NOOPS + MODELS + GLOBALS:
        rows = re.findall(r"^" + re.escape(name) + r" = \.\w+:0x([0-9A-Fa-f]+);[^\n]*?size:0x([0-9A-Fa-f]+)", text, re.M)
        if len(rows) != 1:
            raise ValueError(f"nonunique or missing binding: {name}")
        result[name] = tuple(int(item, 16) for item in rows[0])
    return result


class RequestProbe(phase.PhaseProbe):
    def __init__(self, dol, inventory, case, rows):
        super().__init__(dol, inventory, "menu_predecessor", rows)
        self.case = case
        self.requests = []
        self.factory_snapshot = None
        self.hooks.pop(rows[2][1])  # Execute the actual menu update instead.
        for name in EXECUTE:
            start, size = inventory[name]
            if not size or start % 4 or size % 4 or start < 0x8042EAD4 and start + size > 0x8042E8C4:
                raise ValueError("invalid request-probe range")
            self.allowed.append((start, start + size))
            self.starts[start] = name
        for name in NOOPS + MODELS:
            address = inventory[name][0]
            if address in self.hooks:
                raise ValueError("aliased request boundary model")
            self.hooks[address] = name
        if any(start <= address < end for address in self.hooks for start, end in self.allowed):
            raise ValueError("boundary model intersects original execution")
        self.put("lbl_805D63C8", 2)
        self.put("card_load_sequence_state", int(case == "card_guarded"))
        self.word(self.state + 0x0C, 0)  # Explicit queued destination for override control.
        self.exit_snapshot = None

    def instruction(self, uc, pc, size, user):
        super().instruction(uc, pc, size, user)
        if "TKeyBoardControl__sub_8000F9CC" in self.sym and pc == self.sym["TKeyBoardControl__sub_8000F9CC"][0]:
            self.requests.append(uc.reg_read(read.REG[3]))

    def handle(self, name, args):
        if name == "create_mode_scene__21TAdMultiChgGameModeGCFv":
            self.trace.append(name)
            saved = self.uc.context_save()
            # Chosen request-producing action at this modeled factory boundary.
            self.call("open_keyboard__13TUnk_804EEF64Fv", [0x81106000])
            self.uc.context_restore(saved)
            self.factory_snapshot = [self.word(self.state + offset) for offset in (0, 4, 0x10)]
            return 0
        if name == "predecessor_exit":
            self.exit_snapshot = [self.word(self.state + offset) for offset in (0, 4, 0x10)]
        if name in NOOPS:
            self.trace.append(name)
            return 0
        if name in MODELS:
            self.trace.append(name)
            if name == "func_801A5E54__Fv":
                return int(self.case == "queued_overwrite")
            if name == "is_ready__22TQuestVmDownLoadServerFv":
                return int(self.case in ("quest_ready_overwrite", "card_guarded"))
            raise RuntimeError("missing explicit request model")
        return super().handle(name, args)

    def run_request(self):
        try:
            self.call("main", [])
        except phase.ProbeStop:
            pass
        overwritten = self.case in ("quest_ready_overwrite", "queued_overwrite")
        if self.factory_snapshot != [2, 19, 1] or self.word(self.sym["lobby_game_mode_state"][0]) != 3:
            raise RuntimeError("original title request did not preserve current phase/set pending phase")
        if self.requests != ([19, 0] if self.case == "quest_ready_overwrite" else [19]):
            raise RuntimeError("unexpected original request sequence")
        if self.outcome != ("shutdown_boundary" if overwritten else "modem_helper_boundary"):
            raise RuntimeError("unexpected request-survival outcome")
        if self.entries["fn_8023F3F8"] != 1 or self.entries["open_keyboard__13TUnk_804EEF64Fv"] != 1:
            raise RuntimeError("original update/action not executed")
        if self.entries["get_instance__15TAdPlayerLoadGCFv"] != 1:
            raise RuntimeError("original card-state getter not executed")
        if self.entries["TKeyBoardControl__sub_8000F92C"] != int(self.case == "queued_overwrite"):
            raise RuntimeError("queued-phase override gate failed")
        if self.entries[phase.EXECUTE[2]] != int(not overwritten):
            raise RuntimeError("unexpected phase-19 update entry")
        if self.case == "card_guarded" and any(name in self.trace for name in MODELS[1:]):
            raise RuntimeError("card-state guard did not skip later predicates")
        if self.trace.count("predecessor_exit") != 1 or self.word(self.state + 0x14) != 2:
            raise RuntimeError("menu exit/previous-phase bookkeeping failed")
        expected_exit = [2, 0 if overwritten else 19, 3 if self.case == "queued_overwrite" else 1]
        if self.exit_snapshot != expected_exit or self.entries["main"] != 1:
            raise RuntimeError("original main/menu-exit state control failed")
        expected_final = [0, 0, expected_exit[2]] if overwritten else [19, 19, 0]
        if [self.word(self.state + offset) for offset in (0, 4, 0x10)] != expected_final:
            raise RuntimeError("unexpected final phase/next/result state")
        return dict(case=self.case, outcome=self.outcome, factory_phase_snapshot=self.factory_snapshot,
            menu_exit_phase_snapshot=self.exit_snapshot,
            setter_arguments=self.requests, boundary_trace=self.trace,
            current_phase=self.word(self.state), next_phase=self.word(self.state + 4),
            result_flag=self.word(self.state + 0x10),
            original_function_entries={name:self.entries[name] for name in phase.EXECUTE + EXECUTE})


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dol", required=True, type=Path)
    parser.add_argument("--symbols", type=Path, default=Path("config/GPOE8P/psov3/symbols.txt"))
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    dol, raw = args.dol.read_bytes(), args.symbols.read_bytes()
    if read.unicorn.__version__ != "2.1.4" or hashlib.sha1(dol).hexdigest() != read.ORIGINAL_SHA1 or hashlib.sha256(raw).hexdigest() != read.SYMBOLS_SHA256:
        parser.error("emulator/input bindings differ from pinned checkpoint")
    inventory = bindings(raw.decode())
    for name in phase.EXECUTE + EXECUTE:
        start, size = inventory[name]
        if not any(s["kind"] == "text" and s["address"] <= start and start + size <= s["address"] + s["size"] for s in read.parse_dol(dol)["sections"]):
            parser.error(f"unbacked original range: {name}")
    rows = phase.phase_rows(dol, inventory)
    cases = ("request_survives", "quest_ready_overwrite", "card_guarded", "queued_overwrite")
    result = dict(results=[RequestProbe(dol, inventory, case, rows).run_request() for case in cases],
        original_sha1=read.ORIGINAL_SHA1, symbols_sha256=read.SYMBOLS_SHA256,
        unicorn_version=read.unicorn.__version__,
        limits="Synthetic phase/card state and explicit factory/platform/account/quest predicates. "
        "Predecessor init/exit bodies and main task work are intercepted, not executed. "
        "The factory model invokes one original request action; it does not prove actual menu input, "
        "constructor guards, cleanup effects or a retail transition. Inherited limited ABI model. "
        "Stops before modem helper or shutdown; no file read, loader or restore executes.")
    read.write_result(args.output, result)
    print(f"Four request-survival controls pass; wrote metadata to {args.output}.")


if __name__ == "__main__":
    main()
