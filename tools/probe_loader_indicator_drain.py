#!/usr/bin/env python3
"""Known loading-indicator ownership/drain controls, not retail-state evidence.

Original constructors, destructors and read-wait frame/traversal code execute.
Math/platform and surviving update/render bodies have explicit boundary models.
Requires unicorn==2.1.4 and authenticated private original input.
"""

import argparse
from collections import Counter
import hashlib
from pathlib import Path
import re

try:
    from tools import probe_loader_scene_roots as scene
    from tools import probe_loader_release_contracts as release
except ModuleNotFoundError:
    import probe_loader_scene_roots as scene
    import probe_loader_release_contracts as release

read = scene.read
EXECUTE = tuple(dict.fromkeys(scene.EXECUTE + (
    "__dt__7TObjectFv", "queue_destruction__7TObjectFv", "TLoadCtrl__ct", "run_task__9TLoadCtrlFv",
    "render__9TLoadCtrlFv", "cleanup_scene__9TLoadCtrlFv", "__dt__9TLoadCtrlFv",
    "TNowLoading__ct", "__dt__11TNowLoadingFv", "render__11TNowLoadingFv", "TNowLoading__sub_8001D4D0",
    "TAdLoadNetworkGC__ct", "__dt__16TAdLoadNetworkGCFv", "render__16TAdLoadNetworkGCFv", "TLoadingCur__ct", "__dt__11TLoadingCurFv",
    "fn_80086FE0", "initialize_with_direction__13TParticleCtrlFPvPvPviiiii", "__dt__13TParticleCtrlFv",
    "VecCopy__FP3VecPC3Vec")))
SURVIVING_BODIES = ("run_task__11TNowLoadingFv", "run_task__16TAdLoadNetworkGCFv",
                    "run_task__11TLoadingCurFv", "render__11TLoadingCurFv", "run_task__13TParticleCtrlFv")
NOOPS = tuple(dict.fromkeys(scene.NOOPS + release.NOOPS))
MODELS = ("__nw__7TObjectFUl", "__dl__7TObjectFPv", "__ct__9TAdFadeGCFP7TObjectPv",
          "direction_to_rotation_xz__FPUcPlPl")
GLOBALS = scene.ROOTS + ("TLoadCtrl__instance", "TLoadCtrl__loading_mode", "TLoadCtrl__fade_task",
                       "camera_ctrl_instance", "particle_pool_limit", "particle_global_entry_table")
LOAD, POSITION, ROTATION, TABLE = 0x81202000, 0x81230000, 0x81230100, 0x81240000


def bindings(text):
    inventory = scene.bindings(text)
    for name in EXECUTE + SURVIVING_BODIES + NOOPS + MODELS + GLOBALS:
        rows = re.findall(r"^" + re.escape(name) + r" = \.\w+:0x([0-9A-Fa-f]+);[^\n]*?size:0x([0-9A-Fa-f]+)", text, re.M)
        if len(rows) != 1:
            raise ValueError(f"nonunique or missing binding: {name}")
        inventory[name] = tuple(int(value, 16) for value in rows[0])
    return inventory


class IndicatorProbe(read.Probe):
    def __init__(self, dol, inventory, case):
        self.allocations, self.frees, self.events, self.body_markers = [], [], [], []
        self.in_frame = False
        super().__init__(dol, inventory, "disc_success")
        self.case = case
        self.uc.reg_write(read.ppc.UC_PPC_REG_MSR, self.uc.reg_read(read.ppc.UC_PPC_REG_MSR) | 0x2000)
        self.allowed, self.starts, self.hooks = [], {}, {}
        self.entries.clear()
        for name in EXECUTE:
            start, size = inventory[name]
            if not size or start % 4 or size % 4 or start < 0x8042EAD4 and start + size > 0x8042E8C4:
                raise ValueError(f"invalid indicator execution range: {name}")
            self.allowed.append((start, start + size))
            self.starts[start] = name
        for name in NOOPS + MODELS + SURVIVING_BODIES:
            address = inventory[name][0]
            if address in self.hooks:
                raise ValueError(f"aliased indicator model: {name}")
            self.hooks[address] = name
        if any(start <= address < end for address in self.hooks for start, end in self.allowed):
            raise ValueError("indicator boundary overlaps original execution")
        self.roots = {}
        for index, name in enumerate(scene.ROOTS):
            node = 0x81200000 + index * 0x100
            self.call("__ct__7TObjectFP7TObject", [node, 0])
            self.put(name, node)
            self.roots[node] = name
        self.put("particle_pool_limit", 0x1000)
        self.put("particle_global_entry_table", TABLE)  # Synthetic, zero descriptors.
        self.put("camera_ctrl_instance", 0)
        self.put("TLoadCtrl__loading_mode", 0)
        self.call("TLoadCtrl__ct", [LOAD, self.root("tl_su")])
        self.put("TLoadCtrl__instance", LOAD)
        self.call("run_task__9TLoadCtrlFv", [LOAD])
        if len(self.allocations) != 1 or self.word(LOAD + 0x20) != 1:
            raise RuntimeError("tick-one no-indicator control failed")
        self.call("run_task__9TLoadCtrlFv", [LOAD])
        if self.word(LOAD + 0x20) != 2:
            raise RuntimeError("original tick-two indicator construction failed")
        sizes = [row["size"] for row in self.allocations]
        if sizes != [0x38, 0x3C, 0x40] + [0x78] * 5 + [0x5C, 0x78]:
            raise RuntimeError("unexpected original loading allocation order")
        self.controllers = [row["address"] for row in self.allocations if row["size"] == 0x78]
        now, net, cursor = (next(row["address"] for row in self.allocations if row["size"] == size) for size in (0x3C, 0x40, 0x5C))
        if (self.word(LOAD + 0x14), self.word(now + 0x14), self.word(net + 0x0C)) != (now, net, cursor):
            raise RuntimeError("original loading descendant construction failed")
        if self.word(now + 0x10) != LOAD or any(self.word(node + 0x10) != now for node in (net, cursor)):
            raise RuntimeError("original loading descendant parent links failed")
        if any(self.word(now + offset) for offset in (0x1C, 0x20, 0x24, 0x28)):
            raise RuntimeError("NowLoading's own four references are not zero")
        if [self.word(net + 0x20 + index * 4) for index in range(5)] + [self.word(cursor + 0x1C)] != self.controllers:
            raise RuntimeError("Net5 plus Cursor1 reference identities differ")
        self.owner_records = []
        for node in self.controllers:
            if self.word(node + 0x10) != self.root("tl_07") or self.word(node + 0x58) != node:
                raise RuntimeError("original particle attachment/self-owner control failed")
            table = self.word(node + 0x18)
            if self.word(table + 0x10) != inventory["render__7TObjectFv"][0]:
                raise RuntimeError("particle controller render slot is not original TObject no-op")
            self.owner_records.append(dict(controller=node, parent=self.root("tl_07"), owner=node))
        self.extra = None
        if case == "unrelated_controller":
            self.extra = self.call("fn_80086FE0", [POSITION, ROTATION, 0x16, 1])
            if self.extra in self.controllers or not self.extra:
                raise RuntimeError("unrelated controller allocation failed")
        self.fade = self.word(inventory["TLoadCtrl__fade_task"][0])
        self.call("cleanup_scene__9TLoadCtrlFv", [])
        if self.word(inventory["TLoadCtrl__instance"][0]) or not self.flags(LOAD) & 1:
            raise RuntimeError("cleanup did not queue controller and clear instance")
        if case == "protected_loader":
            self.write(LOAD + 4, b"\x00\x21")
        if case == "protected_particle":
            self.write(self.controllers[0] + 4, b"\x00\x20")

    def root(self, name):
        return self.word(self.sym[name][0])

    def flags(self, node):
        return int.from_bytes(self.uc.mem_read(node + 4, 2), "big")

    def instruction(self, uc, pc, size, user):
        super().instruction(uc, pc, size, user)
        if not self.in_frame:
            return
        receiver = uc.reg_read(read.REG[3])
        if pc in (self.sym["run_tasks__7TObjectFv"][0], self.sym["render_nodes__7TObjectFv"][0]) and receiver in self.roots:
            kind = "update" if pc == self.sym["run_tasks__7TObjectFv"][0] else "render"
            self.events.append(dict(kind=kind, root=self.roots[receiver], known_controllers_freed=sum(node in self.frees for node in self.controllers)))
        if pc in self.starts and self.starts[pc].startswith("__dt__"):
            self.events.append(dict(kind="destructor", function=self.starts[pc], receiver=receiver))

    def handle(self, name, args):
        if name == "__nw__7TObjectFUl":
            if args[0] not in (0x38, 0x3C, 0x40, 0x5C, 0x78) or len(self.allocations) >= 11:
                raise RuntimeError("unexpected indicator allocation boundary")
            address = 0x81210000 + len(self.allocations) * 0x100
            self.allocations.append(dict(address=address, size=args[0]))
            return address
        if name == "__dl__7TObjectFPv":
            if args[0] in self.frees:
                raise RuntimeError("duplicate logical indicator free")
            self.frees.append(args[0])
            return 0
        if name == "__ct__9TAdFadeGCFP7TObjectPv":
            if args[1:] != [self.root("tl_fade"), 2]:
                raise RuntimeError("unexpected fade construction boundary")
            saved = self.uc.context_save()
            self.call("__ct__7TObjectFP7TObject", args[:2])
            self.uc.context_restore(saved)
            return args[0]  # Explicit base-node-only fade model.
        if name == "direction_to_rotation_xz__FPUcPlPl":
            self.word(args[1], 0)
            self.word(args[2], 0)
            return 0  # Chosen angles; no direction-math behavior claimed.
        if name in SURVIVING_BODIES:
            self.body_markers.append(dict(function=name, receiver=args[0]))
            return 0  # Surviving task/render effects are outside this experiment.
        if name in NOOPS:
            return 0
        raise RuntimeError(f"unmodeled indicator boundary: {name}")

    def run_indicator(self):
        self.in_frame = True
        self.call("run_frame__6TLobbyFv", [])
        roots = [(row["kind"], row["root"]) for row in self.events if "root" in row]
        update_roots, render_roots = ["tl_su", "tl_camera", "tl_07", "tl_particle"], ["tl_su", "tl_07", "tl_particle"]
        if self.case == "protected_loader":
            update_roots.append("tl_fade")
            render_roots.append("tl_fade")
        if roots != [("update", name) for name in update_roots] + [("render", name) for name in render_roots]:
            raise RuntimeError("original read-wait frame phase order failed")
        expected = set() if self.case == "protected_loader" else {LOAD} | {row["address"] for row in self.allocations if row["size"] != 0x38 and row["address"] != self.extra}
        if self.case == "protected_particle":
            expected.remove(self.controllers[0])
        if set(self.frees) != expected or len(self.frees) != len(expected):
            raise RuntimeError("unexpected indicator/particle destruction boundary")
        count = 0 if self.case == "protected_loader" else 5 if self.case == "protected_particle" else 6
        renders = [row for row in self.events if row["kind"] == "render"]
        if any(row["known_controllers_freed"] != count for row in renders):
            raise RuntimeError("known controller destruction did not precede all render traversals")
        body_counts = Counter(row["function"] for row in self.body_markers)
        expected_bodies = ({"run_task__13TParticleCtrlFv": 6, "render__11TLoadingCurFv": 1} if self.case == "protected_loader"
                           else {"run_task__13TParticleCtrlFv": 1} if self.case == "unrelated_controller" else {})
        if body_counts != expected_bodies:
            raise RuntimeError("unexpected surviving task/render boundary dispatch")
        if self.case == "protected_loader" and self.flags(LOAD) != 0x20:
            raise RuntimeError("protected-loader queue clearing control failed")
        if self.case == "protected_particle" and self.flags(self.controllers[0]) != 0x20:
            raise RuntimeError("protected-particle queue clearing control failed")
        if self.word(self.sym["TLoadCtrl__instance"][0]):
            raise RuntimeError("cleanup instance unexpectedly republished")
        if self.case != "protected_loader" and (self.word(self.sym["TLoadCtrl__fade_task"][0]) or not self.flags(self.fade) & 1):
            raise RuntimeError("fade queue/current-slot teardown control failed")
        return dict(case=self.case, original_constructor_allocations=self.allocations,
            known_particle_attachment_and_self_owner=self.owner_records, logical_frees=self.frees,
            known_controllers_destroyed_before_render=count, unrelated_controller=self.extra,
            frame_events=self.events, surviving_body_boundary_markers=self.body_markers,
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
        start, size = inventory[name]
        if not any(s["kind"] == "text" and s["address"] <= start and start + size <= s["address"] + s["size"] for s in read.parse_dol(dol)["sections"]):
            parser.error(f"unbacked original range: {name}")
    cases = ("queued_loader", "protected_loader", "protected_particle", "unrelated_controller")
    result = dict(results=[IndicatorProbe(dol, inventory, case).run_indicator() for case in cases],
        original_sha1=read.ORIGINAL_SHA1, symbols_sha256=read.SYMBOLS_SHA256, unicorn_version=read.unicorn.__version__,
        limits="Chosen valid disjoint loading tree and synthetic zero particle descriptors/pool limit. "
        "Original tick-two constructors establish Net5+Cursor1 controller references. Full start_loading "
        "is not executed. Fade uses a base-node-only model; angles, platform/resource effects and surviving "
        "task/render bodies are modeled. Frees are logical, without allocator reuse. This establishes "
        "conditional destruction of those known controllers before rendering, not actual retail state, "
        "all generated effects, arbitrary aliases/cache writers, payload integrity or restore ownership. "
        "Inherited limited ABI model; no file read, modem helper, loader or restore executes.")
    read.write_result(args.output, result)
    print(f"Four indicator-drain controls pass; wrote metadata to {args.output}.")


if __name__ == "__main__":
    main()
