#!/usr/bin/env python3
"""Bounded syntactic request/store/callback audit; never a runtime-state proof."""

import argparse
from bisect import bisect_right
from collections import deque
import hashlib
import json
from pathlib import Path
import re
import struct

try:
    from tools.audit_loader_payload_provenance import parse_dol, ORIGINAL_SHA1, write_result
    from tools.audit_loader_indirect_targets import direct_target, signed
except ModuleNotFoundError:
    from audit_loader_payload_provenance import parse_dol, ORIGINAL_SHA1, write_result
    from audit_loader_indirect_targets import direct_target, signed


SYMBOLS_SHA256 = "ae4ee4705316c4f7102fe949b859a74d645cf2c8899e7168e5f87973de6c88a7"
SETTER, SDA, INSTANCE = 0x8000F9CC, 0x805DA600, 0x805D4A80
CONTROLLERS = {0x8001C7A0: "destructor", 0x8001C828: "constructor",
               0x8001C8B8: "cleanup_scene", 0x8001C978: "start_loading"}


def declarations(text):
    found = {}
    for name, address, size in re.findall(r"^(\S+) = \.\w+:0x([0-9A-Fa-f]+); // type:function size:0x([0-9A-Fa-f]+)", text, re.M):
        address, size = int(address, 16), int(size, 16)
        found.setdefault(address, []).append((name, size))
    # Conflicting declarations are left unresolved, never widened or guessed.
    return {address:dict(names=sorted({name for name, _ in rows}), size=rows[0][1])
            for address, rows in found.items() if len({size for _, size in rows}) == 1}


def scan_patterns(segments):
    requests, stores = [], []
    for base, words in segments:
        for index, word in enumerate(words):
            pc = base + index * 4
            if direct_target(word, pc) == SETTER:
                previous = words[index - 1] if index else 0
                literal = signed(previous & 0xFFFF, 16) if previous & 0xFFFF0000 == 0x38600000 else None
                requests.append(dict(pc=pc, link=bool(word & 1), preceding_li_r3=literal))
            op, rs, ra = word >> 26, (word >> 21) & 31, (word >> 16) & 31
            if ra == 13 and op in (36, 37, 38, 39, 44, 45, 47):
                address = (SDA + signed(word & 0xFFFF, 16)) & 0xFFFFFFFF
                width = (32 - rs) * 4 if op == 47 else 1 if op in (38, 39) else 2 if op in (44, 45) else 4
                if address < INSTANCE + 4 and INSTANCE < address + width:
                    stores.append(dict(pc=pc, opcode=op, source_register=rs, width=width))
    return requests, stores


def edges(words, start, length):
    targets, indirect = set(), []
    for index, word in enumerate(words):
        pc = start + index * 4
        target = direct_target(word, pc)
        if target is not None and not start <= target < start + length:
            targets.add(target)
        if word >> 26 == 19 and (word >> 1) & 1023 in (16, 528):
            indirect.append(pc)  # Includes possible returns; no invented call edge.
    return targets, indirect


def bounded_walk(roots, successors, targets, depth):
    queue = deque((root, (root,)) for root in roots)
    seen, paths, frontier = set(), {}, set()
    while queue:
        node, path = queue.popleft()
        if node in seen:
            continue
        seen.add(node)
        if node in targets:
            paths[node] = list(path)
        next_nodes = successors(node)
        if len(path) - 1 == depth:
            frontier.update(next_nodes - seen)
        else:
            queue.extend((item, path + (item,)) for item in sorted(next_nodes) if item not in seen)
    return seen, paths, frontier - seen


def audit(dol, symbol_text, depth):
    sections = parse_dol(dol)["sections"]
    def span(address, size):
        for section in sections:
            if section["address"] <= address and address + size <= section["address"] + section["size"]:
                offset = section["offset"] + address - section["address"]
                return dol[offset:offset + size]
        raise ValueError(f"unbacked declared range 0x{address:08X}")
    functions = declarations(symbol_text)
    starts = sorted(functions)
    def annotate(pc):
        index = bisect_right(starts, pc) - 1
        address = starts[index] if index >= 0 else None
        return functions[address]["names"] if address is not None and pc < address + functions[address]["size"] else []
    segments = [(s["address"], struct.unpack(f'>{s["size"] // 4}I', span(s["address"], s["size"])))
                for s in sections if s["kind"] == "text"]
    requests, stores = scan_patterns(segments)
    for row in requests + stores:
        row["declared_functions"] = annotate(row["pc"])
    callbacks = []
    # release_scene_resources calls these tables in this order; each backwards.
    for address, size in ((0x804CCE60, 0x38), (0x804CCDA8, 0xB8)):
        data = span(address, size)
        for index in reversed(range(size // 8)):
            target = struct.unpack_from(">I", data, index * 8 + 4)[0]
            callbacks.append(dict(table=address, slot=index, target=target,
                                  declared_functions=functions.get(target, {}).get("names", [])))
    indirect, unresolved = {}, set()
    def successors(address):
        fn = functions.get(address)
        if fn is None or not fn["size"] or fn["size"] % 4:
            unresolved.add(address)
            return set()
        data = span(address, fn["size"])
        next_nodes, sites = edges(struct.unpack(f'>{fn["size"] // 4}I', data), address, fn["size"])
        if sites:
            indirect[address] = sites
        return next_nodes
    seen, paths, frontier = bounded_walk([c["target"] for c in callbacks if c["target"]], successors, CONTROLLERS, depth)
    return dict(direct_request_encodings=len(requests), request_sites=requests,
        adjacent_literal19_patterns=[r for r in requests if r["preceding_li_r3"] == 19],
        syntactic_integer_dform_sda_stores_to_instance=stores, cleanup_callbacks_in_source_order=callbacks,
        direct_closure=dict(maximum_edges=depth, visited_entries=len(seen),
            visited_declared_entries=len(seen - unresolved),
            controller_paths={CONTROLLERS[target]:path for target, path in paths.items()},
            indirect_sites_by_declaration=indirect, unresolved_entries=sorted(unresolved),
            depth_frontier=sorted(frontier)),
        limits="Adjacent li patterns do not prove a value on every entry path. Only handled integer "
        "D-form store encodings are scanned under the canonical r13 binding; floating/paired-single, "
        "indexed, aliased and runtime writes are not covered. Function declarations "
        "only partition this syntactic audit, not original ownership. Direct closure is depth-bounded and "
        "ignores branch conditions; indirect transfers and callback state remain unknown. Absence of a "
        "controller path does not prove cleanup, preservation, inactivity or exclusion of restart.")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dol", required=True, type=Path)
    parser.add_argument("--symbols", type=Path, default=Path("config/GPOE8P/psov3/symbols.txt"))
    parser.add_argument("--depth", type=int, default=4, choices=range(7))
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    dol, raw = args.dol.read_bytes(), args.symbols.read_bytes()
    if hashlib.sha1(dol).hexdigest() != ORIGINAL_SHA1 or hashlib.sha256(raw).hexdigest() != SYMBOLS_SHA256:
        parser.error("original DOL/symbol bindings differ from pinned checkpoint")
    result = audit(dol, raw.decode(), args.depth)
    result.update(original_sha1=ORIGINAL_SHA1, symbols_sha256=SYMBOLS_SHA256)
    write_result(args.output, result)
    print(f"Wrote bounded request/callback metadata to {args.output}; runtime state remains unknown.")


if __name__ == "__main__":
    main()
