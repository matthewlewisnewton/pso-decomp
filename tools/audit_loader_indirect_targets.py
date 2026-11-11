#!/usr/bin/env python3
"""Bounded, read-only LR/CTR target audit of the authenticated GPOE8P DOL.

This is local constant tracking over syntactic blocks, not a complete CFG,
emulator, coverage validator or original-function ownership proof. Values are
never carried across calls/control-flow boundaries. Memory is not evaluated.
An unsupported instruction clears every fact. Unknown indirect entries into
the middle of a region remain outside the analysis.

ISA reference: https://www.nxp.com/docs/en/user-guide/MPCFPE_AD_R1.pdf
See bclr/bcctr, mfspr/mtspr and the 32-bit integer/load/store instruction forms.
"""

import argparse
from collections import Counter
from dataclasses import dataclass
import hashlib
import json
from pathlib import Path
import struct


ORIGINAL_SHA1 = "0d85744b51d7379efb025a943d0cd5aaae2191a3"
WATCH = (0x8042E9FC, 0x8042EA10)
MASK32 = 0xFFFFFFFF


@dataclass(frozen=True)
class Constant:
    value: int
    origins: frozenset


def signed(value, bits):
    return value - (1 << bits) if value & (1 << (bits - 1)) else value


def direct_target(word, pc):
    op = word >> 26
    if op not in (16, 18):
        return None
    bits, mask = (16, 0xFFFC) if op == 16 else (26, 0x03FFFFFC)
    return ((0 if word & 2 else pc) + signed(word & mask, bits)) & MASK32


def control(word):
    op = word >> 26
    xo = (word >> 1) & 1023
    if op in (16, 18):
        return "direct"
    if op == 19 and xo in (16, 528):
        return "lr" if xo == 16 else "ctr"
    if op in (3, 17) or (op == 19 and xo == 50) or (op == 31 and xo == 4):
        return "other_control"
    return None


def rotate(value, shift):
    shift &= 31
    return ((value << shift) | (value >> ((32 - shift) & 31))) & MASK32


def ppc_mask(mb, me):
    bits = range(mb, me + 1) if mb <= me else list(range(mb, 32)) + list(range(me + 1))
    return sum(1 << (31 - bit) for bit in bits)


class State:
    def __init__(self, origin_limit=32):
        self.origin_limit = origin_limit
        self.clear()

    def clear(self):
        self.gpr = [None] * 32
        self.spr = {8: None, 9: None}
        self.gpr_writers = [None] * 32
        self.spr_writers = {8: None, 9: None}

    def write(self, reg, fact, pc):
        self.gpr[reg] = fact
        self.gpr_writers[reg] = pc

    def fact(self, value, pc, *inputs):
        if any(item is None for item in inputs):
            return None
        origins = frozenset({pc}).union(*(item.origins for item in inputs))
        if len(origins) > self.origin_limit:
            return None
        return Constant(value & MASK32, origins)

    def integer(self, word, pc):
        """Apply only explicitly supported effects; False means clear all facts."""
        op = word >> 26
        rt, ra, rb = (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
        imm, simm = word & 0xFFFF, signed(word & 0xFFFF, 16)
        if op in (14, 15):
            base = self.fact(0, pc) if ra == 0 else self.gpr[ra]
            self.write(rt, None if base is None else self.fact(base.value + (simm << (16 if op == 15 else 0)), pc, base), pc)
            return True
        if op == 7:
            src = self.gpr[ra]
            self.write(rt, None if src is None else self.fact(src.value * simm, pc, src), pc)
            return True
        if op in (24, 25, 26, 27, 28, 29):
            src = self.gpr[rt]  # Logical immediates write RA, not RT/RS.
            value = imm << (16 if op in (25, 27, 29) else 0)
            if src is None:
                self.write(ra, None, pc)
            else:
                result = src.value | value if op in (24, 25) else src.value ^ value if op in (26, 27) else src.value & value
                self.write(ra, self.fact(result, pc, src), pc)
            return True
        if op == 21:  # rlwinm, including slwi/srwi/mask aliases.
            src = self.gpr[rt]
            mb, me = (word >> 6) & 31, (word >> 1) & 31
            self.write(ra, None if src is None else self.fact(rotate(src.value, rb) & ppc_mask(mb, me), pc, src), pc)
            return True
        if op in (10, 11) and not word & 0x00600000:  # 32-bit immediate compares.
            return True
        if op in (32, 34, 40, 42):  # Memory is unknown even at a constant EA.
            self.write(rt, None, pc)
            return True
        if op in (33, 35, 41, 43):
            if ra == 0 or ra == rt:
                return False
            self.write(rt, None, pc)
            self.write(ra, None, pc)
            return True
        if op == 46:  # lmw replaces every register from RT through r31.
            if ra >= rt:
                return False  # Base in the loaded range / RT=RA=0 is invalid.
            for reg in range(rt, 32):
                self.write(reg, None, pc)
            return True
        if op in (36, 38, 44, 47, 48, 50, 52, 54):
            return True  # Non-updating stores/FPR loads do not write GPR/LR/CTR.
        if op in (37, 39, 45, 49, 51, 53, 55):
            if ra == 0:
                return False
            self.write(ra, None, pc)
            return True
        if word in (0x4C00012C, 0x7C0004AC, 0x7C0006AC):
            return True  # isync/sync/eieio, exact supported encodings only.
        if op == 31:
            xo = (word >> 1) & 1023
            if xo in (0, 32) and not word & 0x00600001:
                return True  # 32-bit register compares.
            if xo in (339, 467) and not word & 1:
                spr = ((word >> 16) & 31) | ((word >> 6) & 0x3E0)
                if spr not in (8, 9):
                    return False
                if xo == 339:
                    src = self.spr[spr]
                    self.write(rt, None if src is None else self.fact(src.value, pc, src), pc)
                else:
                    src = self.gpr[rt]
                    self.spr[spr] = None if src is None else self.fact(src.value, pc, src)
                    self.spr_writers[spr] = pc
                return True
            if xo in (266, 40):  # add/subf without OE; Rc does not change value.
                a, b = self.gpr[ra], self.gpr[rb]
                self.write(rt, None if a is None or b is None else self.fact(a.value + b.value if xo == 266 else b.value - a.value, pc, a, b), pc)
                return True
            if xo in (444, 316, 28):  # or/mr, xor, and: destination RA.
                a, b = self.gpr[rt], self.gpr[rb]
                value = None if a is None or b is None else a.value | b.value if xo == 444 else a.value ^ b.value if xo == 316 else a.value & b.value
                self.write(ra, None if value is None else self.fact(value, pc, a, b), pc)
                return True
        return False


def in_text(address, segments):
    return any(base <= address < base + 4 * len(words) for base, words in segments)


def scan(segments, leaders, watch, origin_limit):
    state = State(origin_limit)
    events = []
    counts = Counter({key: 0 for key in (
        "words", "block_entries", "direct_encodings", "lr_encodings", "ctr_encodings",
        "other_control_encodings", "unsupported_barriers", "indirect_known", "indirect_unknown",
        "lr_known", "lr_unknown", "ctr_known", "ctr_unknown",
        "spr_assign_known", "spr_assign_unknown", "assign_lr_known", "assign_lr_unknown",
        "assign_ctr_known", "assign_ctr_unknown")})
    barrier_ops = Counter()
    discovered = set()
    for base, words in segments:
        state.clear()
        block = base
        for index, word in enumerate(words):
            pc = base + 4 * index
            counts["words"] += 1
            if pc in leaders:
                state.clear()
                block = pc
                counts["block_entries"] += 1
            kind = control(word)
            if kind:
                counts[kind + "_encodings"] += 1
                if kind in ("lr", "ctr"):
                    # Read the pre-instruction target, before LK or boundary clearing.
                    fact = state.spr[8 if kind == "lr" else 9]
                    # Gekko-compatible XL form: bits 16..20 are reserved here.
                    valid = not (word & 0xF800) and (kind != "ctr" or bool((word >> 21) & 4))
                    target = fact.value & ~3 if fact is not None and valid else None
                    event = {"pc": pc, "block": block, "kind": "branch_" + kind,
                             "link": bool(word & 1), "supported_encoding": valid, "target": target,
                             "last_spr_writer": state.spr_writers[8 if kind == "lr" else 9],
                             "origins": sorted(fact.origins) if target is not None else []}
                    events.append(event)
                    counts["indirect_known" if target is not None else "indirect_unknown"] += 1
                    counts[kind + ("_known" if target is not None else "_unknown")] += 1
                    if target is not None and in_text(target, segments):
                        discovered.add(target)
                state.clear()
                continue
            op, xo = word >> 26, (word >> 1) & 1023
            supported = state.integer(word, pc)
            if not supported:
                state.clear()
                counts["unsupported_barriers"] += 1
                barrier_ops[f"{op}:{xo}" if op in (19, 31) else str(op)] += 1
            elif op == 31 and xo == 467 and not word & 1:
                spr = ((word >> 16) & 31) | ((word >> 6) & 0x3E0)
                fact = state.spr[spr]
                counts["spr_assign_known" if fact is not None else "spr_assign_unknown"] += 1
                name = "assign_lr" if spr == 8 else "assign_ctr"
                counts[name + ("_known" if fact is not None else "_unknown")] += 1
                events.append({"pc": pc, "block": block, "kind": name,
                               "value": fact.value if fact else None,
                               "source_gpr": (word >> 21) & 31,
                               "last_source_writer": state.gpr_writers[(word >> 21) & 31],
                               "origins": sorted(fact.origins) if fact else []})
    hits = []
    for event in events:
        value = event.get("target", event.get("value"))
        if value is not None and watch[0] <= (value & ~3) < watch[1]:
            hits.append(event)
    return {"counts": dict(counts), "unsupported_opcodes": dict(sorted(barrier_ops.items())),
            "events": events, "watched_candidates": hits}, discovered


def analyze(segments, boundaries=(), watch=WATCH, origin_limit=32):
    """Start unknown at every boundary; never join predecessor facts."""
    leaders = {base for base, _ in segments} | set(boundaries)
    for base, words in segments:
        for index, word in enumerate(words):
            pc = base + 4 * index
            target = direct_target(word, pc)
            if target is not None and in_text(target, segments):
                leaders.add(target)
            if control(word) and in_text(pc + 4, segments):
                leaders.add(pc + 4)
    first, discovered = scan(segments, leaders, watch, origin_limit)
    added = discovered - leaders
    if added:
        leaders |= added
        result, further = scan(segments, leaders, watch, origin_limit)
        if further - leaders:
            raise RuntimeError("indirect leader discovery did not stabilize")
    else:
        result = first
    result["leaders"] = len(leaders)
    result["indirect_leaders_added"] = len(added)
    result["passes"] = 2 if added else 1
    return result


def text_segments(data):
    if len(data) < 0x100:
        raise ValueError("truncated DOL header")
    segments = []
    for index in range(7):
        off, base, size = (struct.unpack_from(">I", data, start + index * 4)[0] for start in (0, 0x48, 0x90))
        if not size:
            continue
        if off < 0x100 or off + size > len(data) or (off | base | size) & 3 or base + size > 0x100000000:
            raise ValueError("invalid DOL text range")
        if any(not (base + size <= other or other + 4 * len(words) <= base) for other, words in segments):
            raise ValueError("overlapping DOL text ranges")
        segments.append((base, struct.unpack_from(">" + str(size // 4) + "I", data, off)))
    if not segments:
        raise ValueError("no DOL text")
    return segments


def report_boundaries(report, segments):
    boundaries = set()
    anchors = {}
    for unit in report["units"]:
        if unit.get("metadata", {}).get("module_name") != "psov3":
            continue
        for function in unit.get("functions", []):
            start = int(function["metadata"]["virtual_address"])
            size = int(function["size"])
            if size <= 0 or start < 0 or (start | size) & 3 or start + size > 0x100000000:
                raise ValueError("invalid declared function extent")
            if in_text(start, segments):
                boundaries.add(start)
                anchors[start] = size
            if in_text(start + size, segments):
                boundaries.add(start + size)
    if any(anchors.get(start) != size for start, size in ((0x8042E8C4, 312), (WATCH[0], 20), (WATCH[1], 196))):
        raise ValueError("report must preserve the existing loader/restore/initializer extents")
    return boundaries


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dol", type=Path, default=Path("orig/GPOE8P/files/PsoV3.dol"))
    parser.add_argument("--report", required=True, type=Path, help="native objdiff report, used only for declared block boundaries")
    parser.add_argument("--out-dir", type=Path, default=Path("build/loader-indirect-targets"))
    args = parser.parse_args()
    data = args.dol.read_bytes()
    if hashlib.sha1(data).hexdigest() != ORIGINAL_SHA1:
        parser.error("DOL does not match the authenticated GPOE8P original")
    report_data = args.report.read_bytes()
    segments = text_segments(data)
    boundaries = report_boundaries(json.loads(report_data), segments)
    result = analyze(segments, boundaries)
    events = result.pop("events")
    result.update(original_sha1=ORIGINAL_SHA1,
                  report_sha256=hashlib.sha256(report_data).hexdigest(),
                  tool_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
                  watched_range=list(WATCH), declared_boundaries=len(boundaries),
                  scope="Syntactic local candidates only; unknown indirect entries, memory/table values, unsupported instructions and global reachability are unresolved. No original ownership, coverage or extent claim.")
    try:
        args.out_dir.mkdir(parents=True, exist_ok=False)
    except FileExistsError:
        parser.error("--out-dir must name a new directory")
    (args.out_dir / "events.json").write_text(json.dumps(events, indent=2) + "\n")
    (args.out_dir / "result.json").write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps(result, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
