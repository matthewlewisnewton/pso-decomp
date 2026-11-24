#!/usr/bin/env python3
"""Controlled original PPC phase dispatch with explicit predecessor models.

No retail predecessor/state or cleanup implementation is simulated. The pinned
original phase table and dispatcher select callbacks. Stop before the modem
selection helper; never execute the loader, read path or restore.
Requires unicorn==2.1.4 and authorized private original input.
"""

import argparse
from collections import Counter
import hashlib
from pathlib import Path
import re
import struct

try:
    from tools import probe_loader_read_boundaries as read
except ModuleNotFoundError:
    import probe_loader_read_boundaries as read


EXECUTE = ("main", "TAdTrialModemChkGC__sub_803354E8",
           "check_modem_result__18TAdTrialModemChkGCFv", "TAdTrialModemChkGC__sub_803354A4")
HOOKS = ("init_game_systems__Fv", "shutdown_and_reset_system__Fv",
         "stop_audio_streams__6TLobbyFv", "TLobby__sub_80145A94", "TAdTrialModemChkGC__sub_8007FA24")
ROOTS = ("tl_su", "tl_00", "tl_01", "tl_07", "tl_particle")
GLOBALS = ("main_phase_table", "main_phase_state", "lbl_804C5820") + ROOTS


class ProbeStop(Exception):
    pass


def bindings(text):
    result = read.symbols(text)
    for name in EXECUTE + HOOKS + GLOBALS:
        matches = re.findall(r"^" + re.escape(name) + r" = \.\w+:0x([0-9A-Fa-f]+);[^\n]*?size:0x([0-9A-Fa-f]+)", text, re.M)
        if len(matches) != 1:
            raise ValueError(f"nonunique or missing binding: {name}")
        result[name] = tuple(int(value, 16) for value in matches[0])
    return result


def initialized_span(dol, address, size):
    for section in read.parse_dol(dol)["sections"]:
        if section["address"] <= address and address + size <= section["address"] + section["size"]:
            offset = section["offset"] + address - section["address"]
            return dol[offset:offset + size]
    raise ValueError("table not backed by initialized input")


def phase_rows(dol, inventory):
    address, size = inventory["main_phase_table"]
    if size != 0x108:
        raise ValueError("unexpected phase table extent")
    data = initialized_span(dol, address, size)
    rows = [struct.unpack_from(">3I", data, index * 12) for index in range(22)]
    expected = tuple(inventory[name][0] for name in EXECUTE[1:])
    if rows[19] != expected:
        raise ValueError("phase 19 bindings differ")
    return rows


class PhaseProbe(read.Probe):
    def __init__(self, dol, inventory, case, rows):
        self.trace = []
        self.outcome = None
        super().__init__(dol, inventory, "disc_success")
        self.case = case
        self.rows = rows
        self.state = inventory["main_phase_state"][0]
        self.predecessor = {"menu_predecessor": 2, "offline_predecessor": 14,
                            "online_predecessor": 15}.get(case)
        self.allowed, self.starts, self.hooks = [], {}, {}
        self.entries.clear()
        for name in EXECUTE:
            start, size = inventory[name]
            if not size or start % 4 or size % 4 or start < 0x8042EAD4 and start + size > 0x8042E8C4:
                raise ValueError(f"invalid original range: {name}")
            self.allowed.append((start, start + size))
            self.starts[start] = name
        self.hooks = {inventory[name][0]: name for name in HOOKS}
        if len(self.hooks) != len(HOOKS):
            raise ValueError("aliased phase boundary models")
        if self.predecessor is not None:
            for kind, address in zip(("init", "update", "exit"), rows[self.predecessor]):
                if not address or address in self.hooks:
                    raise ValueError("missing or aliased predecessor callback")
                self.hooks[address] = "predecessor_" + kind
        if any(start <= address < end for address in self.hooks for start, end in self.allowed):
            raise ValueError("boundary model overlaps original execution")
        self.root_snapshot = {name:self.word(inventory[name][0]) for name in ROOTS}
        if any(self.root_snapshot.values()):
            raise RuntimeError("fixture expected empty root globals")

    def handle(self, name, args):
        self.trace.append(name)
        if name == "init_game_systems__Fv":
            self.word(self.state, self.predecessor if self.predecessor is not None else 19)
            self.word(self.state + 4, 0)
            self.word(self.state + 0x10, 0)
            return 0
        if name == "predecessor_update":
            self.word(self.state + 4, 19)
            self.word(self.state + 0x10, 1)
            return 0
        if name in ("predecessor_init", "predecessor_exit"):
            return 0  # Callback body is intentionally not executed or modeled.
        if name == "stop_audio_streams__6TLobbyFv":
            if self.case == "update_suppressed":
                self.word(self.state + 4, 0)
                self.word(self.state + 0x10, 1)
            return 0
        if name == "TLobby__sub_80145A94":
            return 0  # Chosen account predicate for the helper's argument-1 path.
        if name == "TAdTrialModemChkGC__sub_8007FA24":
            if args[0] != 1:
                raise RuntimeError("unexpected modem helper argument")
            self.outcome = "modem_helper_boundary"
            raise ProbeStop
        if name == "shutdown_and_reset_system__Fv":
            self.outcome = "shutdown_boundary"
            raise ProbeStop
        raise RuntimeError(f"unmodeled phase boundary {name}")

    def run_phase(self):
        try:
            self.call("main", [])
        except ProbeStop:
            pass
        expected = ["init_game_systems__Fv"]
        if self.predecessor is not None:
            expected += ["predecessor_init", "predecessor_update", "predecessor_exit"]
        expected += ["stop_audio_streams__6TLobbyFv"]
        if self.case == "update_suppressed":
            expected += ["shutdown_and_reset_system__Fv"]
            if self.entries[EXECUTE[2]] or self.entries[EXECUTE[3]] != 1 or self.outcome != "shutdown_boundary":
                raise RuntimeError("suppressed update/exit control failed")
        else:
            expected += ["TLobby__sub_80145A94", "TAdTrialModemChkGC__sub_8007FA24"]
            if self.entries[EXECUTE[2]] != 1 or self.outcome != "modem_helper_boundary":
                raise RuntimeError("phase-update helper boundary not reached")
        if self.trace != expected:
            raise RuntimeError(f"unexpected phase order: {self.trace}")
        previous = self.word(self.state + 0x14)
        if self.predecessor is not None and previous != self.predecessor:
            raise RuntimeError("previous phase was not recorded")
        if self.entries["main"] != 1 or self.entries[EXECUTE[1]] != 1:
            raise RuntimeError("original dispatcher/entry callback control failed")
        if self.word(self.state) != (0 if self.case == "update_suppressed" else 19):
            raise RuntimeError("unexpected final current phase")
        return dict(case=self.case, predecessor=self.predecessor, outcome=self.outcome,
                    boundary_trace=self.trace, root_globals=self.root_snapshot,
                    current_phase=self.word(self.state), previous_phase=previous,
                    original_function_entries={name:self.entries[name] for name in EXECUTE},
                    predecessor_callbacks=None if self.predecessor is None else self.rows[self.predecessor])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dol", type=Path, required=True)
    parser.add_argument("--symbols", type=Path, default=Path("config/GPOE8P/psov3/symbols.txt"))
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    dol, raw = args.dol.read_bytes(), args.symbols.read_bytes()
    if read.unicorn.__version__ != "2.1.4" or hashlib.sha1(dol).hexdigest() != read.ORIGINAL_SHA1 or hashlib.sha256(raw).hexdigest() != read.SYMBOLS_SHA256:
        parser.error("emulator/input bindings differ from pinned checkpoint")
    inventory = bindings(raw.decode())
    for name in EXECUTE:
        start, size = inventory[name]
        if not any(s["kind"] == "text" and s["address"] <= start and start + size <= s["address"] + s["size"] for s in read.parse_dol(dol)["sections"]):
            parser.error(f"original range not file-backed: {name}")
    rows = phase_rows(dol, inventory)
    address, length = inventory["lbl_804C5820"]
    if length != 108 * 0x28:
        parser.error("unexpected particle definition extent")
    definitions = initialized_span(dol, address, length)
    kinds = Counter(struct.unpack_from(">I", definitions, index * 0x28 + 0x24)[0] for index in range(108))
    if any(kind > 4 for kind in kinds):
        parser.error("unhandled original quad-sprite factory selector")
    cases = ("direct_phase19", "menu_predecessor", "offline_predecessor", "online_predecessor", "update_suppressed")
    results = [PhaseProbe(dol, inventory, case, rows).run_phase() for case in cases]
    read.write_result(args.output, dict(results=results, phase19_callbacks=rows[19],
        particle_definition_count=108, particle_factory_selectors=dict(sorted(kinds.items())),
        original_sha1=read.ORIGINAL_SHA1, symbols_sha256=read.SYMBOLS_SHA256,
        unicorn_version=read.unicorn.__version__,
        limits="Synthetic phase/root state and explicit predecessor/device/account boundary outcomes. "
        "Actual predecessor callbacks are intercepted, not executed; this proves dispatcher selection/order "
        "under the chosen state, not cleanup effects or a retail transition. Stops before modem helper. "
        "No real root contents, runtime header, loader handoff or restore ownership is established."))
    print(f"Five phase-dispatch controls pass; wrote metadata to {args.output}.")


if __name__ == "__main__":
    main()
