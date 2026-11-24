#!/usr/bin/env python3
"""Check that the fork is upstream plus a layer that only adds files.

    python3 fork/tools/check_layer.py [REF]          # REF defaults to HEAD

Two rules:
  1. No layer path exists upstream. If upstream ever adds one, the layer has to move.
  2. Outside the layer, REF differs from upstream only by patches that are waiting to merge
     there. The script lists those files. With --expect-clean it fails if there are any, which
     is the state right after every pending patch has landed and upstream has been merged.

With --against BRANCH it also checks that BRANCH, a patch branch, keeps layer and patch
changes in separate commits, so the export step never has to split a commit.
"""
from __future__ import annotations

import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from export_patch import patch_base  # noqa: E402
from layer import UPSTREAM_REF, GitError, changed_paths, git, is_layer_path  # noqa: E402


def upstream_layer_collisions(upstream: str, cwd: Path | None = None) -> list[str]:
    files = git("ls-tree", "-r", "--name-only", "-z", upstream, cwd=cwd).split("\0")
    return [f for f in files if f and is_layer_path(f)]


def pending_patch_files(upstream: str, ref: str, cwd: Path | None = None) -> list[str]:
    return [p for p in changed_paths(upstream, ref, cwd=cwd) if not is_layer_path(p)]


def mixed_commits(base: str, branch: str, cwd: Path | None = None) -> list[str]:
    mixed = []
    for commit in git("rev-list", "--no-merges", f"{base}..{branch}", cwd=cwd).split():
        paths = [p for p in git("diff-tree", "--no-commit-id", "--name-only", "-r", "-z", commit, cwd=cwd).split("\0") if p]
        kinds = {is_layer_path(p) for p in paths}
        if len(kinds) == 2:
            mixed.append(commit)
    return mixed


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("ref", nargs="?", default="HEAD")
    ap.add_argument("--upstream", default=UPSTREAM_REF)
    ap.add_argument("--expect-clean", action="store_true", help="fail if any non-layer file differs from upstream")
    ap.add_argument("--against", metavar="BRANCH", help="also check a patch branch cut from REF")
    args = ap.parse_args()
    failed = False
    try:
        collisions = upstream_layer_collisions(args.upstream)
        if collisions:
            failed = True
            print(f"FAIL: upstream has {len(collisions)} file(s) on a fork-layer path, for example {collisions[0]}")
        pending = pending_patch_files(args.upstream, args.ref)
        print(f"{len(pending)} non-layer file(s) differ from {args.upstream}")
        for p in pending[:40]:
            print(f"  {p}")
        if len(pending) > 40:
            print(f"  ... and {len(pending) - 40} more")
        if pending and args.expect_clean:
            failed = True
            print("FAIL: expected no differences outside the layer")
        if args.against:
            base = patch_base(args.ref, args.against)
            mixed = mixed_commits(base, args.against)
            if mixed:
                failed = True
                print(f"FAIL: {len(mixed)} commit(s) on {args.against} change both layer and patch files:")
                for c in mixed:
                    print("  " + git("log", "-1", "--format=%h %s", c).strip())
    except GitError as e:
        print(f"check_layer: {e}", file=sys.stderr)
        return 2
    print("FAIL" if failed else "PASS")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
