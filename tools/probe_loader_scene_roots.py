#!/usr/bin/env python3
"""Original PPC frame/traversal controls over an explicitly synthetic task tree.

Requires unicorn==2.1.4 and the same private inputs as the read-boundary probe.
Platform calls are explicit no-op models. The original TObject constructor,
traversals, virtual no-op methods and fade ancestry gate execute unmodified.
This observes fixture dispatch, not a retail scene or cache-writer execution.
"""

import argparse
import hashlib
from pathlib import Path
import re

try:
    from tools import probe_loader_read_boundaries as read
except ModuleNotFoundError:
    import probe_loader_read_boundaries as read


EXECUTE = ("run_frame__6TLobbyFv", "__ct__7TObjectFP7TObject", "run_tasks__7TObjectFv",
           "render_nodes__7TObjectFv", "run_task__7TObjectFv", "render__7TObjectFv",
           "debug_render__7TObjectFv", "debug_update__7TObjectFv", "TLoadCtrl__sub_800F9F00",
           "all_parents_unqueued_for_destruction__7TObjectFv")
NOOPS = ("func_803DCDFC__Fv", "TLobby__sub_800F8F34", "set_depth_buffer_settings_1__Fv",
         "is_ready__22TQuestVmDownLoadServerFv", "restore_saved_depth_alpha_state",
         "func_801A5E54__Fv", "TLobby__sub_803382E4", "render_tick__Fv")
ROOTS = ("tl_su", "tl_00", "tl_camera", "tl_01", "tl_03", "tl_07", "tl_particle", "tl_fade")
MAIN, CONTROLLER = 0x81200000, 0x81203000


def bindings(text):
    result = read.symbols(text)
    for name in EXECUTE + NOOPS + ROOTS + ("TLoadCtrl__fade_task",):
        matches = re.findall(r"^" + re.escape(name) + r" = \.\w+:0x([0-9A-Fa-f]+);[^\n]*?size:0x([0-9A-Fa-f]+)", text, re.M)
        if len(matches) != 1:
            raise ValueError(f"nonunique or missing binding: {name}")
        result[name] = tuple(int(item, 16) for item in matches[0])
    return result


class SceneProbe(read.Probe):
    def __init__(self, dol, inventory, case):
        self.dispatch = []
        self.labels = {}
        super().__init__(dol, inventory, "disc_success")
        self.case = case
        # After inherited fixture/SDA controls, admit only this probe's scene code.
        self.allowed, self.starts = [], {}
        self.entries.clear()
        self.hooks = {}
        for name in EXECUTE:
            start, length = inventory[name]
            if not length or start % 4 or length % 4 or start < 0x8042EAD4 and start + length > 0x8042E8C4:
                raise ValueError(f"invalid executable fixture range: {name}")
            self.allowed.append((start, start + length))
            self.starts[start] = name
        for name in NOOPS:
            self.hooks[inventory[name][0]] = name
        if len(self.hooks) != len(NOOPS):
            raise ValueError("aliased platform boundaries")
        if any(start <= hook < end for hook in self.hooks for start, end in self.allowed):
            raise ValueError("boundary model overlaps original executable range")
        self.call("__ct__7TObjectFP7TObject", [MAIN, 0])
        self.children = {}
        roots = []
        for index, name in enumerate(ROOTS):
            root, child = MAIN + 0x100 + index * 0x100, MAIN + 0x1000 + index * 0x100
            roots.append(root)
            self.call("__ct__7TObjectFP7TObject", [root, MAIN])
            self.call("__ct__7TObjectFP7TObject", [child, root])
            self.put(name, root)
            self.labels[child] = name + "/child"
            self.children[name] = child
            if case == "root_flags":
                self.write(root + 4, b"\x00\x14")  # Root suspend-update + disallow-render.
            if case == "child_render_block":
                self.write(child + 4, b"\x00\x10")
            if case == "child_update_suspend":
                self.write(child + 4, b"\x00\x04")
        actual = []
        node = self.word(MAIN + 0x14)
        while node:
            if len(actual) >= len(ROOTS):
                raise RuntimeError("unexpected root-list cycle")
            actual.append(node)
            node = self.word(node + 0x0C)
        if actual != roots:
            raise RuntimeError("original constructor attachment control failed")
        grandchild = MAIN + 0x2000
        self.call("__ct__7TObjectFP7TObject", [grandchild, self.children["tl_particle"]])
        self.labels[grandchild] = "tl_particle/child/grandchild"
        self.put("TLoadCtrl__fade_task", 0)
        if case in ("fade_present", "fade_ancestor_queued"):
            self.call("__ct__7TObjectFP7TObject", [CONTROLLER, MAIN])
            self.put("TLoadCtrl__fade_task", CONTROLLER)
            if case == "fade_ancestor_queued":
                self.write(MAIN + 4, b"\x00\x01")

    def instruction(self, uc, pc, size, user):
        super().instruction(uc, pc, size, user)
        for name, kind in (("run_task__7TObjectFv", "update"), ("render__7TObjectFv", "render")):
            if name in self.sym and pc == self.sym[name][0]:
                receiver = uc.reg_read(read.REG[3])
                if receiver not in self.labels:
                    raise RuntimeError("unexpected virtual receiver")
                self.dispatch.append(dict(kind=kind, node=self.labels[receiver]))

    def handle(self, name, args):
        if name in NOOPS:
            return 0  # Explicit platform/deferred-work predicates for this fixture.
        return super().handle(name, args)

    def run_scene(self):
        self.call("run_frame__6TLobbyFv", [])
        update_roots = ["tl_su", "tl_camera", "tl_07", "tl_particle"]
        render_roots = ["tl_su", "tl_07", "tl_particle"]
        if self.case == "fade_present":
            update_roots.append("tl_fade")
            render_roots.append("tl_fade")
        expected = []
        for kind, roots in (("update", update_roots), ("render", render_roots)):
            if kind == "update" and self.case == "child_update_suspend":
                continue
            if kind == "render" and self.case == "child_render_block":
                continue
            for root in roots:
                expected.append(dict(kind=kind, node=root + "/child"))
                if root == "tl_particle":
                    expected.append(dict(kind=kind, node=root + "/child/grandchild"))
        if self.dispatch != expected:
            raise RuntimeError(f"unexpected dispatch for {self.case}: {self.dispatch}")
        return dict(case=self.case, dispatch=self.dispatch,
                    original_function_entries={name:self.entries[name] for name in EXECUTE})


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
    for name in EXECUTE:
        start, length = inventory[name]
        if not any(s["kind"] == "text" and s["address"] <= start and start + length <= s["address"] + s["size"] for s in read.parse_dol(dol)["sections"]):
            parser.error(f"executable range not file-backed: {name}")
    cases = ("ordinary", "root_flags", "child_render_block", "child_update_suspend", "fade_present", "fade_ancestor_queued")
    results = [SceneProbe(dol, inventory, case).run_scene() for case in cases]
    read.write_result(args.output, dict(results=results, original_sha1=read.ORIGINAL_SHA1,
        symbols_sha256=read.SYMBOLS_SHA256, unicorn_version=read.unicorn.__version__,
        limits="Synthetic TObject-only tree with original constructors/vtables/traversals. Platform calls "
        "are zero-return models; ABI limits inherited from read-boundary probe. No actual retail task "
        "tree, cache callback or runtime header value is established. No loader/helper/restore executes."))
    print(f"Six scene-root controls pass; wrote metadata to {args.output}.")


if __name__ == "__main__":
    main()
