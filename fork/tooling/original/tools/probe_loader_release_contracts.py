#!/usr/bin/env python3
"""Original PPC release/lifetime controls with explicit allocator/platform models.

Inputs stay private. This tests chosen valid storage/tree fixtures and ordering,
not retail aliases, allocator effects or an observed restart race. Requires
unicorn==2.1.4; see launch-dol-stranded-epilogue.md for limits and reproduction.
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


EXECUTE = (
    "register_callback__23TAdSinglePlyChrSelectGCFis", "TAdSinglePlyChrSelectGC__sub_801FC8B4",
    "__dt__12TPlyCharDataFv", "__dt__14TPlyDispConfigFv", "destroy_arrays__14TPlyDispConfigFii",
    "free_if_valid__14TPlyDispConfigFls", "__destroy_arr", "free_item_loader__6TLobbyFv",
    "__dt__13RelocatedFileFv", "fn_8026AC50", "heap_alloc__5THeapFUl", "heap_free__5THeapFPv",
    "__ct__5THeapFUli", "__dt__5THeapFv", "__dl__5THeapFPv", "__ct__7TObjectFP7TObject",
    "__dt__7TObjectFv", "run_tasks__7TObjectFv", "queue_destruction__7TObjectFv", "TLoadCtrl__ct",
    "__dt__9TLoadCtrlFv", "cleanup_scene__9TLoadCtrlFv", "run_task__9TLoadCtrlFv",
    "all_parents_unqueued_for_destruction__7TObjectFv")
FREES = ("__dl__FPv", "__dla__FPv", "xfree__FPv", "__dl__7TObjectFPv")
NOOPS = ("release_bgm_resource__6TLobbyFv", "fn_8034AD28", "reset_default_view__11TCameraCtrlFv",
         "reset__11TCameraCtrlFv", "reset_view_state__11TCameraCtrlFv", "init_default_view__11TCameraCtrlFv",
         "create__11TCameraCtrlFv", "controller_stuff__Fv", "update_input_frame__16TKeyBoardControlFv",
         "update_sound_request_slots__Fv", "activate_camera_mode", "set_active_camera_pose")
MODELS = ("xmalloc__FUl", "memset", "__nw__7TObjectFUl", "__ct__9TAdFadeGCFP7TObjectPv")
GLOBALS = ("TLoadCtrl__instance", "TLoadCtrl__loading_mode", "TLoadCtrl__fade_task", "tl_su", "tl_fade",
           "camera_ctrl_instance", "chat_log_lines", "chat_last_line_buffer", "TAdScrollWinGC__chat_log_heap",
           "item_loader_instance", "lbl_805D49D8")
SU, FADE_ROOT, OLD, NEW, FADE = 0x81200000, 0x81200100, 0x81201000, 0x81201100, 0x81202000
HEAP, POOL, FILE, FILE_BUFFER, CHARS, LEAF = 0x81208000, 0x81210000, 0x81209000, 0x81220000, 0x81240000, 0x81280000
CANARY = 0xC0FFEE00
WINDOW_TABLES = {"__vt__7TObject":"__dt__7TObjectFv",
                 "__vt__17TWindowCtrlScreen":"__dt__17TWindowCtrlScreenFv",
                 "__vt__14TWindowCtrlSub":"__dt__14TWindowCtrlSubFv",
                 "__vt__18TWindowCtrlClipOut":"__dt__18TWindowCtrlClipOutFv"}


def bindings(text):
    result = read.symbols(text)
    for name in set(EXECUTE + FREES + NOOPS + MODELS + GLOBALS + tuple(WINDOW_TABLES) + tuple(WINDOW_TABLES.values())):
        rows = re.findall(r"^" + re.escape(name) + r" = \.\w+:0x([0-9A-Fa-f]+);[^\n]*?size:0x([0-9A-Fa-f]+)", text, re.M)
        if len(rows) != 1:
            raise ValueError(f"nonunique or missing binding: {name}")
        result[name] = tuple(int(value, 16) for value in rows[0])
    return result


class ReleaseProbe(read.Probe):
    def __init__(self, dol, inventory, case):
        self.leaf_flags, self.frees, self.heap_snapshot = Counter(), [], None
        super().__init__(dol, inventory, "disc_success")
        self.case = case
        self.allowed, self.starts, self.hooks = [], {}, {}
        self.entries.clear()
        for name in EXECUTE:
            start, size = inventory[name]
            if not size or start % 4 or size % 4 or start < 0x8042EAD4 and start + size > 0x8042E8C4:
                raise ValueError("invalid release-probe range")
            self.allowed.append((start, start + size))
            self.starts[start] = name
        for name in FREES + NOOPS + MODELS:
            address = inventory[name][0]
            if address in self.hooks:
                raise ValueError("aliased release boundary")
            self.hooks[address] = name
        if any(start <= address < end for address in self.hooks for start, end in self.allowed):
            raise ValueError("boundary overlaps original execution")
        self.put("TLoadCtrl__instance", CANARY)
        self.fade_allocations = 0

    def instruction(self, uc, pc, size, user):
        super().instruction(uc, pc, size, user)
        if pc == self.sym["free_if_valid__14TPlyDispConfigFls"][0]:
            self.leaf_flags[uc.reg_read(read.REG[4])] += 1

    def handle(self, name, args):
        if name in FREES:
            self.frees.append(dict(boundary=name, address=args[0]))
            if name == "xfree__FPv" and args[0] == POOL:
                first = self.word(POOL)
                self.heap_snapshot = [first, self.word(first), self.word(first + 4)]
            return 0  # Logical free only; real allocator behavior is outside the model.
        if name in NOOPS:
            return 0
        if name == "xmalloc__FUl":
            if args[0] != 0x2000:
                raise RuntimeError("unexpected heap fixture allocation")
            return POOL
        if name == "memset":
            return super().handle(name, args)
        if name == "__nw__7TObjectFUl":
            self.fade_allocations += 1
            if self.fade_allocations != 1 or args[0] != 0x38:
                raise RuntimeError("unexpected loading allocation")
            return FADE
        if name == "__ct__9TAdFadeGCFP7TObjectPv":
            if args != [FADE, FADE_ROOT, 2]:
                raise RuntimeError("unexpected fade-constructor arguments")
            saved = self.uc.context_save()
            self.call("__ct__7TObjectFP7TObject", args[:2])
            self.uc.context_restore(saved)
            return FADE  # Base-node-only fade model; no fade rendering is executed.
        raise RuntimeError(f"unmodeled release boundary {name}")

    def run_array(self):
        self.write(CHARS, b"\xDE\xAD\xBE\xEF" * (0x12000 // 4))
        self.word(LEAF, 0xDEADBEEF)
        if self.case == "leaf_positive_delete":
            self.call("free_if_valid__14TPlyDispConfigFls", [LEAF, 1])
            expected = [dict(boundary="__dl__FPv", address=LEAF)]
            if self.leaf_flags != {1:1}:
                raise RuntimeError("positive leaf-delete control failed")
        else:
            pointer = 0 if self.case == "array_null" else CHARS
            delete = int(self.case != "array_keep_storage")
            self.call("register_callback__23TAdSinglePlyChrSelectGCFis", [pointer, delete])
            expected = [dict(boundary="__dl__FPv", address=CHARS)] if pointer and delete else []
            leaves = 112 if pointer else 0
            if self.entries["free_if_valid__14TPlyDispConfigFls"] != leaves:
                raise RuntimeError("unexpected fixed leaf count")
            if self.leaf_flags != ({0xFFFFFFFF:112} if pointer else {}):
                raise RuntimeError("array callback delete-flag control failed")
            if self.entries["__destroy_arr"] != (29 if pointer else 0):
                raise RuntimeError("unexpected nested-array count")
        if self.frees != expected:
            raise RuntimeError("unexpected array deletion boundary")

    def run_item(self):
        self.put("item_loader_instance", 0 if self.case == "item_null" else FILE)
        self.put("lbl_805D49D8", 0x12345678)
        self.word(FILE, FILE_BUFFER)
        self.word(FILE + 4, 0xDEADBEEF)  # Relocated root is never dereferenced here.
        self.call("free_item_loader__6TLobbyFv", [])
        first = list(self.frees)
        self.call("free_item_loader__6TLobbyFv", [])
        expected = [] if self.case == "item_null" else [
            dict(boundary="__dla__FPv", address=FILE_BUFFER), dict(boundary="__dl__FPv", address=FILE)]
        if self.frees != expected or self.frees != first or self.word(self.sym["item_loader_instance"][0]):
            raise RuntimeError("resource-release/idempotence control failed")
        if self.word(self.sym["lbl_805D49D8"][0]) != (0x12345678 if self.case == "item_null" else 0):
            raise RuntimeError("resource-root clearing control failed")

    def run_heap(self):
        self.call("__ct__5THeapFUli", [HEAP, 0x2000, 8])
        self.put("TAdScrollWinGC__chat_log_heap", HEAP)
        if self.case == "chat_populated":
            blocks = [self.call("heap_alloc__5THeapFUl", [HEAP, size]) for size in (0x100, 0x80, 0x40)]
            if any(not POOL < value < POOL + 0x2000 for value in blocks) or len(set(blocks)) != 3:
                raise RuntimeError("heap allocation control failed")
            self.word(self.sym["chat_log_lines"][0], blocks[0])
            self.word(self.sym["chat_log_lines"][0] + 29 * 4, blocks[1])
            self.put("chat_last_line_buffer", blocks[2])
        self.call("fn_8026AC50", [])
        self.call("fn_8026AC50", [])  # Cleared globals must not cause repeated frees.
        if self.entries["heap_free__5THeapFPv"] != (3 if self.case == "chat_populated" else 0):
            raise RuntimeError("heap-free target/count control failed")
        if self.frees != [dict(boundary="xfree__FPv", address=POOL), dict(boundary="xfree__FPv", address=HEAP)]:
            raise RuntimeError("unexpected heap allocator boundary")
        if self.heap_snapshot != [POOL + 8, 0, 0x1FF8]:
            raise RuntimeError("valid free-list coalescing control failed")
        if self.word(self.sym["TAdScrollWinGC__chat_log_heap"][0]) or self.word(self.sym["chat_last_line_buffer"][0]):
            raise RuntimeError("chat-heap globals not cleared")
        if any(self.word(self.sym["chat_log_lines"][0] + index * 4) for index in range(30)):
            raise RuntimeError("chat lines not cleared")

    def start_new_fixture(self):
        self.put("TLoadCtrl__loading_mode", 0)
        self.call("TLoadCtrl__ct", [NEW, SU])
        self.put("TLoadCtrl__instance", NEW)  # Chosen publication point of a restart.
        if self.word(self.sym["TLoadCtrl__fade_task"][0]) != FADE:
            raise RuntimeError("original new-controller fade publication failed")

    def run_loading(self):
        self.call("__ct__7TObjectFP7TObject", [SU, 0])
        self.call("__ct__7TObjectFP7TObject", [FADE_ROOT, 0])
        self.put("tl_su", SU)
        self.put("tl_fade", FADE_ROOT)
        self.put("camera_ctrl_instance", 0)
        self.put("TLoadCtrl__loading_mode", 3)
        self.call("TLoadCtrl__ct", [OLD, SU])
        self.put("TLoadCtrl__instance", OLD)
        self.call("cleanup_scene__9TLoadCtrlFv", [])
        if self.word(self.sym["TLoadCtrl__instance"][0]) or not self.uc.mem_read(OLD + 5, 1)[0] & 1:
            raise RuntimeError("original cleanup queue/clear control failed")
        if self.case == "restart_before_drain":
            self.start_new_fixture()
        self.call("run_tasks__7TObjectFv", [SU])
        if self.case == "restart_after_drain":
            self.start_new_fixture()
            self.call("run_tasks__7TObjectFv", [SU])
        instance, fade = (self.word(self.sym[name][0]) for name in ("TLoadCtrl__instance", "TLoadCtrl__fade_task"))
        if self.case == "restart_after_drain":
            if (instance, fade, self.word(NEW + 0x20), self.uc.mem_read(FADE + 5, 1)[0]) != (NEW, FADE, 1, 0):
                raise RuntimeError("serialized restart control failed")
        elif self.case == "restart_before_drain":
            if instance or fade or self.word(NEW + 0x20) or not self.uc.mem_read(FADE + 5, 1)[0] & 1:
                raise RuntimeError("old-destructor/new-state ordering control failed")
        elif instance or fade or self.word(SU + 0x14):
            raise RuntimeError("no-restart drain control failed")
        if self.entries["__dt__9TLoadCtrlFv"] != 1 or self.frees != [dict(boundary="__dl__7TObjectFPv", address=OLD)]:
            raise RuntimeError("unexpected controller destruction")
        return dict(instance=instance, fade=fade, new_tick=self.word(NEW + 0x20),
                    fade_flags=self.uc.mem_read(FADE + 5, 1)[0], su_first_child=self.word(SU + 0x14))

    def run_release(self):
        loading = None
        if self.case.startswith("array_") or self.case == "leaf_positive_delete":
            self.run_array()
        elif self.case.startswith("item_"):
            self.run_item()
        elif self.case.startswith("chat_"):
            self.run_heap()
        else:
            loading = self.run_loading()
        if loading is None and self.word(self.sym["TLoadCtrl__instance"][0]) != CANARY:
            raise RuntimeError("disjoint loading-state canary changed")
        return dict(case=self.case, frees=self.frees, leaf_delete_flags=dict(self.leaf_flags),
                    pre_allocator_free_heap_snapshot=self.heap_snapshot, loading_state=loading,
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
    window_targets = []
    for table, destructor in WINDOW_TABLES.items():
        address, size = inventory[table]
        if size != 24:
            parser.error("unexpected window vtable extent")
        for section in read.parse_dol(dol)["sections"]:
            if section["address"] <= address and address + size <= section["address"] + section["size"]:
                offset = section["offset"] + address - section["address"]
                target = struct.unpack_from(">I", dol, offset + 8)[0]
                if target != inventory[destructor][0]:
                    parser.error("window constructor-contract vtable target differs")
                window_targets.append(dict(vtable=table, destructor=destructor, target=target))
                break
        else:
            parser.error("window vtable not file-backed")
    for name in EXECUTE:
        start, size = inventory[name]
        if not any(s["kind"] == "text" and s["address"] <= start and start + size <= s["address"] + s["size"] for s in read.parse_dol(dol)["sections"]):
            parser.error(f"unbacked original range: {name}")
    cases = ("array_destroy", "array_keep_storage", "array_null", "leaf_positive_delete",
             "item_release", "item_null", "chat_populated", "chat_empty", "loading_drain",
             "restart_before_drain", "restart_after_drain")
    read.write_result(args.output, dict(results=[ReleaseProbe(dol, inventory, case).run_release() for case in cases],
        window_vtable_targets_under_constructor_contract=window_targets,
        original_sha1=read.ORIGINAL_SHA1, symbols_sha256=read.SYMBOLS_SHA256,
        unicorn_version=read.unicorn.__version__,
        limits="Chosen valid disjoint storage/tree fixtures, fixed allocator/platform boundary models and "
        "a base-node-only fade constructor. Logical frees do not model allocator effects. Restart publishes "
        "an original constructed controller at a chosen point; full start_loading/resource callbacks are "
        "not executed. No retail alias, live state, restart interleaving, payload clobber or restore ownership "
        "is established. Inherited limited ABI model; no loader/helper/restore executes."))
    print(f"Eleven release/lifetime controls pass; wrote metadata to {args.output}.")


if __name__ == "__main__":
    main()
