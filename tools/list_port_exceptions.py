#!/usr/bin/env python3
"""List source constructs a non-GameCube port must rewrite.

Writes docs/porting-exceptions-generated.md: asm bodies, MWCC intrinsics,
direct hardware addresses, CodeWarrior pragmas (per file) and the per-unit
compiler overrides in configure.py with their recorded comments.

    python3 tools/list_port_exceptions.py            # regenerate the doc
    python3 tools/list_port_exceptions.py --check    # fail if it is stale
    python3 tools/list_port_exceptions.py --pr 281   # scan an open PR's added lines
    python3 tools/list_port_exceptions.py --upstream-catchup  # list upstream catch-up cheats

--check also validates the "Upstream catch-up (rewrite later)" table in
docs/porting-exceptions.md: every row needs a function/symbol, unit, file
that exists, upstream PR (#167-#191), a known cheat type, the fork PR and
the tag "upstream catch-up, rewrite later".
"""
import argparse, collections, re, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OUT = ROOT / "docs" / "porting-exceptions-generated.md"
SRC_DIRS = ("src", "include")
EXTS = {".c", ".cpp", ".h", ".hpp", ".inc"}
ASM = re.compile(r"^\s*(?:static\s+)?asm\b|\basm\s*[({]|__asm\b|orig_asm/|\.incbin")
INTRIN = re.compile(r"\b(__fabsf|__fabs|__cntlzw|__frsqrte|__fres|__rlwinm|__rlwimi|__abs|__labs|__sync|__dcbz|__dcbf|__dcbst|__dcbi|__icbi|__lwbrx|__lhbrx|__stwbrx|__sthbrx|__mftb|__mfspr|__mtspr|__vec2x32float__|__fsel|__fnabs|__setflm)\b")
HW = re.compile(r"0x(?:CC00|CD00|E000)[0-9A-Fa-f]{4}\b|\bGQR\d?\b|\bmtspr\b|\bmfspr\b")
PRAGMA = re.compile(r"^\s*#pragma\s+(\w+)")
NEUTRAL_PRAGMAS = {"push", "pop", "once"}

def files():
    for d in SRC_DIRS:
        for p in sorted((ROOT / d).rglob("*")):
            if p.suffix in EXTS and p.is_file():
                yield p

def scan_lines(rel, lines, hits):
    for n, line in enumerate(lines, 1):
        code = line.split("//")[0]
        if ASM.search(code):
            hits["asm"].append((rel, n, line.strip()))
        for m in INTRIN.finditer(code):
            hits["intrinsic"].append((rel, n, m.group(1)))
        if HW.search(code):
            hits["hardware"].append((rel, n, line.strip()))
        m = PRAGMA.match(line)
        if m and m.group(1) not in NEUTRAL_PRAGMAS:
            hits["pragma"].append((rel, n, m.group(1)))

def configure_overrides():
    """(unit, override, comment) for every per-file entry in configure.py."""
    out, comment = [], []
    entry = re.compile(r'^\s*"([^"]+\.(?:c|cpp))":\s*\{(.*)')
    for line in (ROOT / "configure.py").read_text().splitlines():
        s = line.strip()
        if s.startswith("#"):
            comment.append(s.lstrip("# ").strip()); continue
        m = entry.match(line)
        if m:
            body = m.group(2)
            ver = re.search(r'"mw_version":\s*"([^"]+)"', body)
            flags = re.findall(r'"(-[^"]+)"', body)
            desc = ", ".join(([ver.group(1)] if ver else []) + flags) or "(multi-line entry; see configure.py)"
            out.append((m.group(1), desc, " ".join(comment)))
            comment = []
            continue
        if not s.startswith('"') or s.endswith(("[", "{")):
            comment = [] if not s.startswith(('"mw_version"', '"cflags"', '"symbol')) else comment
    return out

REGISTER = ROOT / "docs" / "porting-exceptions.md"
CATCHUP_HEADING = "## 7. Upstream catch-up"
CATCHUP_TAG = "upstream catch-up, rewrite later"
CATCHUP_TYPES = ("asm", "raw offset cast", 'extern "C" mangled name', "steering pragma", "shadow struct")
CATCHUP_UPSTREAM = range(167, 192)
CATCHUP_COLS = ("symbol", "unit", "file", "upstream", "type", "fork_pr", "tag")

def _cell(s):
    return s.strip().strip("`").strip()

def _pr_number(s):
    m = re.search(r"/pull/(\d+)", s) or re.fullmatch(r"\[?#(\d+)\]?(?:\(.*\))?", s.strip())
    return int(m.group(1)) if m else None

def catchup_entries():
    """(rows, errors) for the upstream catch-up table of the register."""
    lines = REGISTER.read_text().splitlines()
    try:
        start = next(i for i, l in enumerate(lines) if l.startswith(CATCHUP_HEADING))
    except StopIteration:
        return [], [f"{REGISTER.relative_to(ROOT)}: missing section '{CATCHUP_HEADING} ...'"]
    rows, errors, seen_header = [], [], False
    for n, line in enumerate(lines[start + 1:], start + 2):
        if line.startswith("## "):
            break
        if not line.startswith("|"):
            continue
        cells = [c.strip() for c in re.split(r"(?<!\\)\|", line.strip())[1:-1]]
        if not seen_header:
            seen_header = True; continue
        if all(set(c) <= set("-: ") for c in cells):
            continue
        where = f"{REGISTER.relative_to(ROOT)}:{n}"
        if len(cells) != len(CATCHUP_COLS):
            errors.append(f"{where}: expected {len(CATCHUP_COLS)} columns, got {len(cells)}"); continue
        row = dict(zip(CATCHUP_COLS, cells))
        for k in CATCHUP_COLS:
            if not _cell(row[k]):
                errors.append(f"{where}: empty {k}")
        up = _pr_number(row["upstream"])
        if up not in CATCHUP_UPSTREAM:
            errors.append(f"{where}: upstream PR must be one of zeroz41 #167-#191, got {row['upstream']!r}")
        typ = _cell(row["type"])
        if typ not in CATCHUP_TYPES and not re.match(r"other:\s*\S", typ):
            errors.append(f"{where}: cheat type must be one of {', '.join(CATCHUP_TYPES)} or 'other: <what>', got {typ!r}")
        if _pr_number(row["fork_pr"]) is None:
            errors.append(f"{where}: fork PR must be a PR number (#N or a link), got {row['fork_pr']!r}")
        if _cell(row["tag"]) != CATCHUP_TAG:
            errors.append(f"{where}: tag must be exactly '{CATCHUP_TAG}'")
        f = _cell(row["file"])
        if f and not (ROOT / f).exists():
            errors.append(f"{where}: file {f} does not exist")
        row["upstream_n"], row["type_name"] = up, typ.split(":")[0] if typ.startswith("other") else typ
        rows.append(row)
    return rows, errors

def print_catchup(rows, errors):
    print(f"upstream catch-up exceptions: {len(rows)}  (register: {REGISTER.relative_to(ROOT)}, section '{CATCHUP_HEADING} (rewrite later)')")
    by_type = collections.Counter(r["type_name"] for r in rows)
    by_up = collections.Counter(r["upstream_n"] for r in rows)
    if rows:
        print("by cheat type: " + ", ".join(f"{k} {v}" for k, v in by_type.most_common()))
        print("by upstream PR: " + ", ".join(f"#{k} {v}" for k, v in sorted(by_up.items(), key=lambda kv: (kv[0] is None, kv[0] or 0))))
        for t in sorted(by_type):
            print(f"\n[{t}]")
            for r in sorted((r for r in rows if r["type_name"] == t), key=lambda r: (r["upstream_n"] or 0, r["file"])):
                print(f"  upstream #{r['upstream_n']}  {_cell(r['symbol'])}  ({_cell(r['unit'])}, {_cell(r['file'])})  fork {_cell(r['fork_pr'])}")
    for e in errors:
        print(f"ERROR: {e}")

def esc(s):
    return s.replace("|", "\\|")

def render(hits, overrides):
    o = ["# Porting exceptions: generated inventory", "",
         "Generated by `python3 tools/list_port_exceptions.py`; do not edit by hand.",
         "The curated register with reasons is [porting-exceptions.md](porting-exceptions.md).", ""]
    pr_files = collections.defaultdict(collections.Counter)
    for f, _, k in hits["pragma"]:
        pr_files[f][k] += 1
    o += ["## Counts", "", "| Category | Hits | Files |", "|---|---:|---:|"]
    for k in ("asm", "intrinsic", "hardware", "pragma"):
        o.append(f"| {k} | {len(hits[k])} | {len({h[0] for h in hits[k]})} |")
    o.append(f"| configure.py per-unit override | {len(overrides)} | {len(overrides)} |")
    kinds = collections.Counter(k for _, _, k in hits["pragma"])
    o += ["", "Pragma kinds (excluding push/pop/once): " + ", ".join(f"`{k}` {v}" for k, v in kinds.most_common()), ""]
    o += ["## Assembly", "", "| File:line | Source |", "|---|---|"]
    o += [f"| `{f}:{n}` | `{esc(t)}` |" for f, n, t in hits["asm"]]
    o += ["", "## MWCC intrinsics", "", "| File:line | Intrinsic |", "|---|---|"]
    o += [f"| `{f}:{n}` | `{t}` |" for f, n, t in hits["intrinsic"]]
    o += ["", "## Direct hardware access", "", "| File:line | Source |", "|---|---|"]
    o += [f"| `{f}:{n}` | `{esc(t)}` |" for f, n, t in hits["hardware"]]
    o += ["", "## configure.py per-unit compiler overrides", "", "| Unit | Override | Recorded reason (configure.py comment) |", "|---|---|---|"]
    o += [f"| `{u}` | `{esc(d)}` | {esc(c) or 'no comment of its own (may share the comment of the entry above; otherwise reason not recorded)'} |" for u, d, c in overrides]
    o += ["", "## CodeWarrior pragmas per file", "", "| File | Pragmas |", "|---|---|"]
    for f in sorted(pr_files):
        o.append(f"| `{f}` | " + ", ".join(f"{k}×{v}" for k, v in pr_files[f].most_common()) + " |")
    return "\n".join(o) + "\n"

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--upstream-catchup", action="store_true", help="list and count the upstream catch-up register entries")
    ap.add_argument("--count", action="store_true", help="with --upstream-catchup: print only the count line")
    ap.add_argument("--pr", type=int, help="print exceptions on added lines of this PR (needs gh)")
    a = ap.parse_args()
    if a.upstream_catchup:
        rows, errors = catchup_entries()
        if a.count:
            print(f"{len(rows)}" + (f" ({len(errors)} errors)" if errors else ""))
        else:
            print_catchup(rows, errors)
        return 1 if errors else 0
    hits = collections.defaultdict(list)
    if a.pr:
        diff = subprocess.run(["gh", "pr", "diff", str(a.pr)], cwd=ROOT, capture_output=True, text=True, check=True).stdout
        cur, lines = None, collections.defaultdict(list)
        for l in diff.splitlines():
            if l.startswith("+++ b/"): cur = l[6:]
            elif l.startswith("+") and not l.startswith("+++") and cur and Path(cur).suffix in EXTS:
                lines[cur].append(l[1:])
        for f, ls in lines.items(): scan_lines(f, ls, hits)
        for k, v in hits.items():
            for f, _, t in v: print(f"{k}\t{f}\t{t}")
        return 0
    for p in files():
        scan_lines(str(p.relative_to(ROOT)), p.read_text(errors="replace").splitlines(), hits)
    text = render(hits, configure_overrides())
    if a.check:
        rc = 0
        if not OUT.exists() or OUT.read_text() != text:
            print(f"{OUT.relative_to(ROOT)} is stale; rerun tools/list_port_exceptions.py"); rc = 1
        _, errors = catchup_entries()
        for e in errors:
            print(f"upstream catch-up register: {e}"); rc = 1
        return rc
    OUT.write_text(text); print(f"wrote {OUT.relative_to(ROOT)}")
    return 0

if __name__ == "__main__":
    sys.exit(main())
