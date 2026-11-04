#!/usr/bin/env python3
"""localize_split_globals.py — unblock exact units that `link_units.py`
refuses with only `missing <sym>`.

dtk exports every symbol of a split object as a global unless symbols.txt
says `scope:local`. A unit whose source keeps that object anonymous (a pooled
`.rodata` double the compiler names `@123`, a string literal, a `static`
callback) compiles to an object without the global, so the link check refuses
it: another unit might reference it. When no other object does, the global is
an artifact of the split, and marking it `scope:local` removes the refusal
without changing a byte of the DOL.

Two of those anonymous objects are MWCC's int-to-double biases
(0x4330000000000000 and 0x4330000080000000). When the original split's symbol
is exactly that 8-byte object, the plan labels it as a compiler-generated
conversion-pool constant. An unreferenced one is localized even if another
missing symbol in the same unit is referenced elsewhere. A referenced one is
not. `--pools-only` limits the plan and the write to those constants. Bytes
that merely contain the pattern, or a symbols.txt entry that is not an 8-byte
.rodata/.sdata2 object, are not labeled and do not get that exception.

"No other object" is checked against the undefined symbols of the objects
the link actually uses: the split object (build/GPOE8P/obj) of every unit in
report.json and the compiled object (build/GPOE8P/src) of every unit, since
the following scan may link any exact one.
The current generated split configuration supplies split-only consumers too.
Missing or malformed consumers reject the whole plan; retired split objects are
ignored. Rebuild first: these checks do not prove object/source freshness.

  localize_split_globals.py [UNIT...]          # plan
  localize_split_globals.py --write [UNIT...]  # edit symbols.txt, then rebuild
                                               # and run link_units.py check
  localize_split_globals.py --pools-only       # only the two MWCC biases

UNIT is a unit name as link_units.py prints it (pso/effect/TEffHit.cpp).
Without one, every missing-only unit in linked_units_blocked.json is planned.
Run `link_units.py scan` first: it writes that file.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import link_units as lu  # noqa: E402

SYMBOLS = lu.CFG_DIR / "symbols.txt"
BLOCKED = lu.CFG_DIR / "linked_units_blocked.json"


def elf_symbols(path: Path) -> tuple[set[str], set[str]]:
    """(defined globals, undefined globals) of a big-endian ELF32 object."""
    b = path.read_bytes()
    def fail(reason: str):
        raise ValueError(f"{path}: {reason}")
    if len(b) < 52 or b[:7] != b"\x7fELF\x01\x02\x01":
        fail("expected ELF32 big-endian object")
    kind, machine = struct.unpack_from(">HH", b, 16)
    if kind != 1 or machine != 20:
        fail("expected relocatable PowerPC object")
    shoff = int.from_bytes(b[0x20:0x24], "big")
    shentsize, shnum = struct.unpack_from(">HH", b, 0x2E)
    if shentsize != 40 or not shnum or shoff < 52 or shoff + shnum * 40 > len(b):
        fail("invalid section table")
    hdrs = [struct.unpack_from(">10I", b, shoff + i * 40) for i in range(shnum)]
    defined, undefined = set(), set()
    tables = 0
    for header in hdrs:
        _, typ, _, _, off, size, link, _, _, entsize = header
        if typ != 2:
            continue
        tables += 1
        if entsize != 16 or size < 16 or size % 16 or off + size > len(b):
            fail("invalid symbol table")
        if link >= shnum or hdrs[link][1] != 3:
            fail("invalid symbol string-table link")
        stroff, strsize = hdrs[link][4:6]
        if not strsize or stroff + strsize > len(b):
            fail("invalid symbol string table")
        strtab = b[stroff:stroff + strsize]
        if strtab[0] != 0 or strtab[-1] != 0 or any(b[off:off + 16]):
            fail("invalid null symbol or string table")
        for o in range(off + 16, off + size, 16):
            name_off, _, _, info, _, shndx = struct.unpack_from(">IIIBBH", b, o)
            if name_off >= strsize or (shndx >= shnum and shndx < 0xFF00) or shndx == 0xFFFF:
                fail("invalid symbol name or section index")
            end = strtab.find(b"\0", name_off)
            if end < 0:
                fail("unterminated symbol name")
            if info >> 4 not in (1, 2):
                continue
            try:
                name = strtab[name_off:end].decode("utf-8")
            except UnicodeDecodeError:
                fail("invalid UTF-8 symbol name")
            (undefined if shndx == 0 else defined).add(name)
    if tables != 1:
        fail("expected one symbol table")
    return defined, undefined


def consumer_objects(report: dict, config: dict) -> list[Path]:
    """Require the current split census, including extensionless generated units."""
    split_units = config["units"]
    report_units = report["units"]
    if not split_units or not report_units:
        raise ValueError("empty split configuration or report")
    if any((u.get("metadata") or {}).get("module_name") not in (None, "psov3")
           for u in report_units):
        raise ValueError("unsupported non-psov3 report consumer")
    def key(name: str) -> str:
        # objdiff drops source extensions even for units with no compiled source.
        return str(Path(name).with_suffix("")) if Path(name).suffix in (".cpp", ".cp", ".c", ".s", ".S") else name

    names = [key(u["name"]) for u in split_units]
    report_names = [key(u["name"].removeprefix(lu.UNIT_PREFIX)) for u in report_units]
    if len(set(names)) != len(names) or len(set(report_names)) != len(report_names):
        raise ValueError("duplicate unit in split configuration or report")
    if set(names) != set(report_names):
        raise ValueError("split configuration/report unit census differs; rebuild first")
    objects = []
    for u in split_units:
        obj = lu.ROOT / u["object"]
        expected = lu.SPLIT_OBJ_DIR / (key(u["name"]) + ".o")
        if obj != expected or not obj.is_relative_to(lu.SPLIT_OBJ_DIR) or ".." in obj.parts:
            raise ValueError(f"inconsistent split object path: {obj}")
        objects.append(obj)
    if len(set(objects)) != len(objects):
        raise ValueError("duplicate split object")
    for u in report_units:
        if (u.get("metadata") or {}).get("source_path"):
            n = lu.unit_name(u)
            if not Path(n).suffix or Path(n).is_absolute() or ".." in Path(n).parts:
                raise ValueError(f"unsupported compiled unit: {n}")
            objects.append(lu.OBJ_DIR / Path(n).with_suffix(".o"))
    return objects


def validate_candidates(report: dict, want: dict[str, str]) -> None:
    """A cached missing-only scan must still describe the inspected objects."""
    by_name = {lu.unit_name(u): u for u in report["units"]}
    for name in set(want.values()):
        u = by_name.get(name)
        if u is None or not (u.get("metadata") or {}).get("source_path"):
            raise ValueError(f"candidate absent from source report: {name}")
        if not lu.report_scores_exact(u):
            raise ValueError(f"candidate report no longer exact: {name}")
        current = set(lu.missing_compiled_symbols(u))
        expected = {s for s, owner in want.items() if owner == name}
        if current != expected:
            raise ValueError(f"cached missing symbols changed: {name}; rerun link_units.py scan")
        checks = (lu.extra_compiled_sections, lu.extra_compiled_symbols,
                  lu.global_data_layout_mismatch, lu.section_size_mismatch,
                  lu.section_alignment_mismatch, lu.function_order_mismatch)
        for check in checks:
            reasons = check(u)
            if reasons:
                raise ValueError(f"candidate no longer missing-only: {name}: {check.__name__}: {reasons}")


def _pool_inventory_ok(text: str, name: str) -> bool:
    """symbols.txt agrees this name is an 8-byte object in a constant section."""
    prefix = name + " = "
    for line in text.splitlines():
        if not line.startswith(prefix):
            continue
        return (re.search(r"= \.(?:rodata|sdata2):", line) is not None
                and "type:object" in line and re.search(r"\bsize:0x8\b", line) is not None)
    return False


def _pool_label(kinds: dict[str, str], symbol: str) -> str:
    kind = kinds.get(symbol)
    if not kind:
        return symbol
    return f"{symbol} [compiler-generated conversion pool: {kind}]"


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--pools-only", action="store_true",
                    help="localize only unreferenced MWCC int-to-double biases")
    ap.add_argument("units", nargs="*", help="limit to these units")
    args = ap.parse_args()

    if not BLOCKED.exists():
        sys.exit(f"missing {BLOCKED.relative_to(lu.ROOT)}: run tools/link_units.py scan first")
    snapshots: dict[Path, str] = {}
    def read(path: Path) -> bytes:
        data = path.read_bytes()
        snapshots[path] = hashlib.sha256(data).hexdigest()
        return data

    blocked = json.loads(read(BLOCKED))
    if args.units:
        unknown = [u for u in args.units if u not in blocked]
        if unknown:
            sys.exit("not blocked by link_units.py scan: " + ", ".join(unknown))
        blocked = {u: blocked[u] for u in args.units}
    want: dict[str, str] = {}  # symbol -> unit
    for unit, reasons in blocked.items():
        if reasons and all(r.startswith("missing ") for r in reasons):
            for r in reasons:
                symbol = r.split(" ", 1)[1]
                if symbol in want and want[symbol] != unit:
                    raise ValueError(f"ambiguous candidate owner: {symbol}")
                want[symbol] = unit
    if not want:
        print("no missing-only units")
        return 0

    report = json.loads(read(lu.REPORT))
    config = json.loads(read(lu.SPLIT_CONFIG))
    symbol_data = read(SYMBOLS)
    read(lu.SPLITS)
    objs = consumer_objects(report, config)
    referenced: dict[str, set[Path]] = {s: set() for s in want}
    for obj in objs:
        # Require every current input. Absence is not evidence of no reference.
        read(obj)
        _, undef = elf_symbols(obj)
        for s in undef & want.keys():
            referenced[s].add(obj)
    validate_candidates(report, want)

    def own(obj: Path, unit: str) -> bool:
        stem = unit.rsplit(".", 1)[0]
        return obj.as_posix().endswith("/" + stem + ".o")

    inventory = symbol_data.decode()
    kinds: dict[str, str] = {}
    for symbol, unit in want.items():
        split = lu.SPLIT_OBJ_DIR / Path(unit).with_suffix(".o")
        kind = lu.conversion_pool_kind(split, symbol) if split.is_file() else None
        # The object bytes and the checked-in inventory both have to describe
        # an 8-byte constant. Either one being a larger or different object
        # means this is not a compiler pool entry we are willing to reclassify.
        if kind and _pool_inventory_ok(inventory, symbol):
            kinds[symbol] = kind

    ok_units: dict[str, list[str]] = {}
    bad_units: dict[str, list[str]] = {}
    for s, unit in want.items():
        # The unit's own compiled object counts as a referencer: when its
        # source still says `extern f32 lbl_X;` for a literal the unit now
        # owns, localizing leaves lbl_X undefined at link time (the split
        # object that defined it is no longer linked). Fix that unit's source
        # to define the literal instead.
        others = [o for o in referenced[s] if not (own(o, unit) and o.is_relative_to(lu.SPLIT_OBJ_DIR))]
        (bad_units if others else ok_units).setdefault(unit, []).append(s)
    # A referenced symbol blocks the unit's other missing symbols. An
    # unreferenced conversion-pool constant stays localizable on its own:
    # its bytes are the compiler bias, and no split actually uses the export.
    for unit, symbols in list(ok_units.items()):
        if unit not in bad_units:
            continue
        pools = [s for s in symbols if s in kinds]
        if pools:
            ok_units[unit] = pools
        else:
            del ok_units[unit]
    if args.pools_only:
        for unit, symbols in list(ok_units.items()):
            pools = [s for s in symbols if s in kinds]
            if pools:
                ok_units[unit] = pools
            else:
                del ok_units[unit]
    syms = {s for v in ok_units.values() for s in v}
    for symbol in syms:
        unit = want[symbol]
        if [o for o in referenced[symbol] if not (own(o, unit) and o.is_relative_to(lu.SPLIT_OBJ_DIR))]:
            raise ValueError(f"refusing to localize referenced symbol: {symbol}")
    lines = symbol_data.decode().splitlines(keepends=True)
    found = set()
    for i, line in enumerate(lines):
        m = re.match(r"(\S+) = ", line)
        if not m or m[1] not in syms:
            continue
        symbol = m[1]
        if symbol in found or ("scope:" in line and "scope:global" not in line):
            raise ValueError(f"ambiguous or already localized symbol inventory: {symbol}; rebuild first")
        found.add(symbol)
        if "scope:global" in line:
            lines[i] = line.replace("scope:global", "scope:local")
        else:
            body, nl = line.rstrip("\n"), "\n" if line.endswith("\n") else ""
            lines[i] = body + (" scope:local" if "//" in body else " // scope:local") + nl
    if found != syms:
        raise ValueError(f"symbols absent from current inventory: {sorted(syms - found)}")

    # Check the same inventory again before reporting a usable plan or writing.
    # This catches replacement during inspection, not pre-existing stale builds.
    for path, digest in snapshots.items():
        if hashlib.sha256(path.read_bytes()).hexdigest() != digest:
            raise ValueError(f"input changed during localization: {path}; no symbols written")

    for u, v in sorted(ok_units.items()):
        print(f"local {u}: {', '.join(_pool_label(kinds, s) for s in v)}")
    for u, v in sorted(bad_units.items()):
        print(f"keep  {u}: {', '.join(_pool_label(kinds, s) for s in v)} referenced elsewhere")
        for symbol in sorted(v):
            for obj in sorted(referenced[symbol]):
                if not (own(obj, u) and obj.is_relative_to(lu.SPLIT_OBJ_DIR)):
                    print(f"  {_pool_label(kinds, symbol)} <- {obj.relative_to(lu.ROOT)}")
    scope = "conversion-pool constants" if args.pools_only else "symbols"
    print(f"{len(ok_units)} units / {len(syms)} {scope} localizable; "
          f"{len(bad_units)} units referenced elsewhere")

    if args.write and syms:
        SYMBOLS.write_text("".join(lines))
        print(f"marked {len(syms)} symbols scope:local in {SYMBOLS.relative_to(lu.ROOT)}")
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except (OSError, ValueError, KeyError, TypeError, struct.error) as exc:
        sys.exit(f"localization refused: {exc}")
