#!/usr/bin/env python3
"""Original menu exit/window teardown over chosen trees; not a retail transition.

Runs original request/main/release-table/layer/window destruction code. Other
release callbacks, task work and platform effects have explicit boundary models.
Requires private pinned original input and unicorn==2.1.4.
"""

import argparse
import hashlib
from pathlib import Path
import re
import struct

try:
    from tools import probe_loader_request_survival as request
    from tools.audit_loader_indirect_targets import direct_target
    from tools.audit_loader_phase_requests import declarations
except ModuleNotFoundError:
    import probe_loader_request_survival as request
    from audit_loader_indirect_targets import direct_target
    from audit_loader_phase_requests import declarations

read, phase = request.read, request.phase
EXECUTE = (
    "release_scene_resources__6TLobbyFv", "call_funcs_reverse__6TLobbyFPvUi",
    "delete_layer_children__9TMainTaskFv", "delete_children__7TObjectFv",
    "__ct__7TObjectFP7TObject", "__dt__7TObjectFv", "run_tasks__7TObjectFv", "run_task__7TObjectFv",
    "set_parent__7TObjectFP7TObject", "queue_destruction__7TObjectFv",
    "__ct__15TWindowCtrlMainFv", "__dt__15TWindowCtrlMainFv", "free_all_windows__15TWindowCtrlMainFv",
    "init_fields__15TWindowCtrlMainFv", "release_ptr__15TWindowCtrlMainFPPv",
    "TWindowCtrlClipOut__ct", "__dt__18TWindowCtrlClipOutFv",
    "TWindowCtrlSub__ct", "__dt__14TWindowCtrlSubFv",
    "TWindowCtrlScreen__ct", "__dt__17TWindowCtrlScreenFv",
    "free_keyboard_soft__15TWindowCtrlMainFv", "free_window__15TWindowCtrlMainFv",
    "reparent_to_main_ctrl__17TWindowSubComCardFv", "TWindowCtrlMain__sub_8024CE24",
    "TLoadCtrl__ct", "cleanup_scene__9TLoadCtrlFv", "__dt__9TLoadCtrlFv")
NOOPS = ("refresh_render_state__6TLobbyFv", "free_heap__13TParticleCtrlFv",
         "clear_resource_load_tasks__Fv", "release_bgm_resource__6TLobbyFv", "fn_8034AD28",
         "reset_view_state__11TCameraCtrlFv", "init_default_view__11TCameraCtrlFv", "create__11TCameraCtrlFv")
BOUNDARIES = ("__nw__7TObjectFUl", "__dl__7TObjectFPv")
GATE_EXECUTE = ("run_task__9TMainTaskFv", "pause_update__7TObjectFv", "resume_update__7TObjectFv")
ROOTS = tuple("tl_" + name for name in (
    "su", "00", "camera", "01", "02", "03", "item_equip", "loc_start", "04", "05", "06",
    "07", "loc_end", "window", "particle", "particlemodel", "radermap", "clipout", "fade", "fadeafter"))
GLOBALS = ROOTS + ("TLoadCtrl__instance", "TLoadCtrl__loading_mode", "TLoadCtrl__fade_task",
    "camera_ctrl_instance", "TWindowCtrlMain__viewport_states", "TWindowCtrlMain__instance",
    "TWindowCtrlMain__window_task_root", "TWindowCtrlMain__screen_controller",
    "TWindowCtrlMain__sub_controller", "window_clip_out_instance", "main_task", "update_flags", "old_update_flags")
WINDOW, LOADING, CHILD = 0x81210000, 0x81211000, 0x81212000


def bindings(text):
    inventory = request.bindings(text)
    for name in EXECUTE + GATE_EXECUTE + NOOPS + BOUNDARIES + GLOBALS:
        rows = re.findall(r"^" + re.escape(name) + r" = \.\w+:0x([0-9A-Fa-f]+);[^\n]*?size:0x([0-9A-Fa-f]+)", text, re.M)
        if len(rows) != 1:
            raise ValueError(f"nonunique or missing binding: {name}")
        inventory[name] = tuple(int(value, 16) for value in rows[0])
    return inventory


def callbacks(dol):
    result = []
    for address, size in ((0x804CCE60, 0x38), (0x804CCDA8, 0xB8)):
        data = phase.initialized_span(dol, address, size)
        result.extend(struct.unpack_from(">I", data, index * 8 + 4)[0] for index in reversed(range(size // 8)))
    return result


def loading_call_sites(dol, text, inventory):
    functions = declarations(text)
    targets = {name: inventory[name][0] for name in ("TLoadCtrl__ct", "cleanup_scene__9TLoadCtrlFv")}
    # Additional pinned declarations, without adding these functions to execution.
    for name in ("start_loading__9TLoadCtrlFUl", "poll_default__9TLoadCtrlFv"):
        rows = [address for address, fn in functions.items() if name in fn["names"]]
        if len(rows) != 1:
            raise ValueError(f"ambiguous method declaration: {name}")
        targets[name] = rows[0]
    sites = []
    for section in read.parse_dol(dol)["sections"]:
        if section["kind"] != "text":
            continue
        data = dol[section["offset"]:section["offset"] + section["size"]]
        for offset in range(0, len(data), 4):
            word = struct.unpack_from(">I", data, offset)[0]
            pc = section["address"] + offset
            target = direct_target(word, pc)
            for name, address in targets.items():
                if target == address:
                    owners = [fn["names"] for start, fn in functions.items() if start <= pc < start + fn["size"]]
                    sites.append(dict(pc=pc, target=name, link=bool(word & 1), declared_owners=owners))
    return sites


class WindowProbe(request.RequestProbe):
    def __init__(self, dol, inventory, case, rows):
        super().__init__(dol, inventory, case, rows)
        # The original window initializer loads/stores floats. Enable the PPC
        # FPU in the emulator; this does not replace any original instruction.
        self.uc.reg_write(read.ppc.UC_PPC_REG_MSR, self.uc.reg_read(read.ppc.UC_PPC_REG_MSR) | 0x2000)
        self.allocations, self.frees, self.release_calls = [], [], []
        self.at_exit, self.at_helper, self.at_window_callback = None, None, None
        self.hooks.pop(rows[2][2])  # Execute the actual menu exit.
        for name in EXECUTE:
            start, size = inventory[name]
            if not size or start % 4 or size % 4 or start < 0x8042EAD4 and start + size > 0x8042E8C4:
                raise ValueError(f"invalid teardown range: {name}")
            if start in self.hooks:
                raise ValueError(f"original range was modeled: {name}")
            self.allowed.append((start, start + size))
            self.starts[start] = name
        for name in NOOPS + BOUNDARIES:
            self.hooks[inventory[name][0]] = name
        self.release_order = callbacks(dol)
        for address in self.release_order:
            if address != inventory["free_all_windows__15TWindowCtrlMainFv"][0]:
                self.hooks[address] = "release_callback_" + hex(address)
        if any(start <= address < end for address in self.hooks for start, end in self.allowed):
            raise ValueError("model overlaps executed original code")
        for index, name in enumerate(ROOTS):
            node = 0x81200000 + index * 0x100
            self.call("__ct__7TObjectFP7TObject", [node, 0])
            self.put(name, node)
        self.put("TLoadCtrl__loading_mode", 3)  # No fade allocation in this fixture.
        self.call("TLoadCtrl__ct", [LOADING, self.word(inventory["tl_su"][0])])
        self.put("TLoadCtrl__instance", LOADING)
        self.call("__ct__15TWindowCtrlMainFv", [WINDOW])
        if len(self.allocations) != 11:
            raise RuntimeError("unexpected window constructor allocation count")
        viewport5 = self.word(inventory["TWindowCtrlMain__viewport_states"][0] + 5 * 0x1C)
        self.call("__ct__7TObjectFP7TObject", [CHILD, self.word(inventory["tl_su"][0])])
        # A base-node-only compatibility fixture for the inspected window helper.
        self.call("reparent_to_main_ctrl__17TWindowSubComCardFv", [CHILD])
        if self.word(CHILD + 0x10) != viewport5:
            raise RuntimeError("original viewport-5 reparent control failed")
        if case == "escaped_window":
            self.call("set_parent__7TObjectFP7TObject", [CHILD, self.word(inventory["tl_su"][0])])
        if case == "nested_loading":
            # Deliberate generic reparent countermodel, NOT a recovered source edge.
            self.call("set_parent__7TObjectFP7TObject", [LOADING, viewport5])

    def snapshot(self):
        return dict(instance=self.word(self.sym["TLoadCtrl__instance"][0]),
                    su_child=self.word(self.word(self.sym["tl_su"][0]) + 0x14),
                    loading_parent=self.word(LOADING + 0x10), loading_flags=int.from_bytes(self.uc.mem_read(LOADING + 4, 2), "big"),
                    loading_destructors=self.entries["__dt__9TLoadCtrlFv"], logical_frees=list(self.frees))

    def instruction(self, uc, pc, size, user):
        super().instruction(uc, pc, size, user)
        if pc == self.sym["release_scene_resources__6TLobbyFv"][0]:
            self.trace.append("predecessor_exit")
            self.exit_snapshot = [self.word(self.state + offset) for offset in (0, 4, 0x10)]
            self.at_exit = self.snapshot()
        if pc == self.sym["free_all_windows__15TWindowCtrlMainFv"][0] and self.from_release_loop():
            self.at_window_callback = self.snapshot()
            self.release_calls.append(pc)

    def from_release_loop(self):
        start, size = self.sym["call_funcs_reverse__6TLobbyFPvUi"]
        return start <= self.uc.reg_read(read.ppc.UC_PPC_REG_LR) < start + size

    def handle(self, name, args):
        if name == "__nw__7TObjectFUl":
            if args[0] != 0x1C or len(self.allocations) >= 11:
                raise RuntimeError("unexpected constructor allocation")
            address = 0x81220000 + len(self.allocations) * 0x100
            self.allocations.append(address)
            return address
        if name == "__dl__7TObjectFPv":
            if args[0] in self.frees:
                raise RuntimeError("duplicate logical tree free")
            self.frees.append(args[0])
            return 0
        if name.startswith("release_callback_"):
            if self.from_release_loop():
                self.release_calls.append(int(name.removeprefix("release_callback_"), 16))
            return 0  # Callback effects outside this window/tree experiment.
        if name in NOOPS:
            return 0
        if name == "run_task__9TMainTaskFv" and self.case in ("queued_loading", "drained_loading"):
            saved = self.uc.context_save()
            self.call("cleanup_scene__9TLoadCtrlFv", [])
            if self.case == "drained_loading":
                self.call("run_tasks__7TObjectFv", [self.word(self.sym["tl_su"][0])])
            self.uc.context_restore(saved)
        if name == "TAdTrialModemChkGC__sub_8007FA24":
            self.at_helper = self.snapshot()
        return super().handle(name, args)

    def run_window(self):
        self.run_request()
        if self.release_calls != self.release_order or self.entries["delete_layer_children__9TMainTaskFv"] != 1:
            raise RuntimeError("original layer/callback release order failed")
        expected_destroyed = self.case in ("nested_loading", "drained_loading")
        if self.at_helper["instance"] != (0 if expected_destroyed or self.case == "queued_loading" else LOADING):
            raise RuntimeError("unexpected loading instance at original modem-helper boundary")
        if self.entries["__dt__9TLoadCtrlFv"] != int(expected_destroyed):
            raise RuntimeError("unexpected controller destructor count")
        if (CHILD in self.frees) != (self.case != "escaped_window"):
            raise RuntimeError("window descendant/escape control failed")
        expected = set(self.allocations + [WINDOW] + ([] if self.case == "escaped_window" else [CHILD]) + ([LOADING] if expected_destroyed else []))
        if set(self.frees) != expected or len(self.frees) != len(expected):
            raise RuntimeError("unexpected tree deletion boundary")
        if set(self.at_window_callback["logical_frees"]) != expected:
            raise RuntimeError("manager destruction did not finish at the layer-cleanup stage")
        for name in GLOBALS:
            if name.startswith("TWindowCtrlMain__") and name != "TWindowCtrlMain__viewport_states" or name == "window_clip_out_instance":
                if self.word(self.sym[name][0]):
                    raise RuntimeError("window global not cleared")
        if any(self.word(self.sym["TWindowCtrlMain__viewport_states"][0] + index * 0x1C) for index in range(6)):
            raise RuntimeError("viewport pointer not cleared")
        if self.case == "queued_loading" and not self.at_helper["loading_flags"] & 1:
            raise RuntimeError("queued SU controller was unexpectedly drained")
        if self.entries["__dt__15TWindowCtrlMainFv"] != 1 or self.entries["free_all_windows__15TWindowCtrlMainFv"] != 1:
            raise RuntimeError("window destructor/callback execution failed")
        return dict(case=self.case, before_menu_exit=self.at_exit, at_modem_helper=self.at_helper,
            before_window_release_callback=self.at_window_callback,
            release_callbacks_in_executed_order=self.release_calls, window_allocations=len(self.allocations),
            original_function_entries={name:self.entries[name] for name in phase.EXECUTE + request.EXECUTE + EXECUTE})

    def drain_gate_controls(self):
        """Separate chosen controls after the request run, not a continued game."""
        if self.case != "external_loading" or self.entries["__dt__9TLoadCtrlFv"]:
            raise RuntimeError("gate controls require the undestroyed external fixture")
        self.hooks.pop(self.sym["run_task__9TMainTaskFv"][0])
        for name in GATE_EXECUTE:
            start, size = self.sym[name]
            self.allowed.append((start, start + size))
            self.starts[start] = name
        su, parent = self.word(self.sym["tl_su"][0]), self.sym["main_task"][0]
        self.call("__ct__7TObjectFP7TObject", [parent, 0])
        self.call("set_parent__7TObjectFP7TObject", [su, parent])
        self.call("cleanup_scene__9TLoadCtrlFv", [])
        self.put("update_flags", 1)  # SU is the first sibling in this fixture.
        self.put("old_update_flags", 0)
        self.call("run_task__9TMainTaskFv", [parent])
        paused = self.snapshot()
        flags = int.from_bytes(self.uc.mem_read(su + 4, 2), "big")
        if flags != 8 or self.word(su + 0x14) != LOADING or self.entries["__dt__9TLoadCtrlFv"]:
            raise RuntimeError("paused parent traversal unexpectedly drained SU")
        self.call("run_tasks__7TObjectFv", [su])
        direct = self.snapshot()
        if self.word(su + 0x14) or self.entries["__dt__9TLoadCtrlFv"] != 1:
            raise RuntimeError("direct paused-SU traversal failed to drain queued child")
        if int.from_bytes(self.uc.mem_read(su + 4, 2), "big") != 8:
            raise RuntimeError("direct traversal changed receiver pause flag")
        new = LOADING + 0x100
        self.call("TLoadCtrl__ct", [new, su])
        self.put("TLoadCtrl__instance", new)
        self.call("cleanup_scene__9TLoadCtrlFv", [])
        self.put("update_flags", 0)
        self.call("run_task__9TMainTaskFv", [parent])
        if self.word(su + 0x14) or self.entries["__dt__9TLoadCtrlFv"] != 2 or int.from_bytes(self.uc.mem_read(su + 4, 2), "big"):
            raise RuntimeError("resumed parent traversal failed to drain queued child")
        return dict(paused_parent=paused, direct_paused_su=direct, resumed_parent_destructors=2,
            original_main_task_calls=self.entries["run_task__9TMainTaskFv"],
            first_paused_su_flags=flags, direct_call_preserves_receiver_flags=True,
            limits="Separate post-request controls, not continued modem execution. Main parent has only SU; "
            "chosen update_flags1 pauses that first sibling. Full start_loading is not executed.")


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
    for name in EXECUTE + GATE_EXECUTE:
        start, size = inventory[name]
        if not any(s["kind"] == "text" and s["address"] <= start and start + size <= s["address"] + s["size"] for s in read.parse_dol(dol)["sections"]):
            parser.error(f"unbacked original range: {name}")
    rows = phase.phase_rows(dol, inventory)
    cases = ("external_loading", "nested_loading", "queued_loading", "drained_loading", "escaped_window")
    probes = [WindowProbe(dol, inventory, case, rows) for case in cases]
    results = [probe.run_window() for probe in probes]
    result = dict(results=results, separate_drain_gate_controls=probes[0].drain_gate_controls(),
        syntactic_loading_method_call_sites=loading_call_sites(dol, raw.decode(), inventory),
        original_sha1=read.ORIGINAL_SHA1, symbols_sha256=read.SYMBOLS_SHA256, unicorn_version=read.unicorn.__version__,
        limits="Chosen disjoint constructor/tree fixtures, synthetic factory/predicates and task-boundary "
        "cleanup/drain choices. Twenty-nine other release callbacks and platform/resource operations are "
        "modeled. Frees are logical; allocator effects are absent. Window reparent uses a base-node-only "
        "compatibility fixture. Loading reparent is an explicit generic countermodel, not an authenticated "
        "source call or retail alias. Direct call encodings do not exclude indirect calls or prove control "
        "flow. Inherited limited ABI model. No actual predecessor, retail tree/state, restart interleaving, "
        "runtime header, loader handoff or restore ownership established; stops before modem helper.")
    read.write_result(args.output, result)
    print(f"Five window/menu teardown controls pass; wrote metadata to {args.output}.")


if __name__ == "__main__":
    main()
