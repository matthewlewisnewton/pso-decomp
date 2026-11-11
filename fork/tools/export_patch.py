#!/usr/bin/env python3
"""Turn a patch branch cut from fork main into a branch upstream can take.

    python3 fork/tools/export_patch.py BRANCH -m "Match TObjEneDimedian"

The patch is everything BRANCH changes relative to where it left fork main, with the fork
layer left out. It is applied to upstream as one commit on a new local branch named
export/<BRANCH>. Nothing is pushed and the working tree is not touched.

A patch that needs another patch upstream does not have yet will not apply. Export the
other one first and pass its export branch with --onto.
"""
from __future__ import annotations

import argparse
import os
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from layer import UPSTREAM_REF, GitError, exclude_pathspecs, changed_paths, git, is_layer_path  # noqa: E402


def patch_base(fork_main: str, branch: str, cwd: Path | None = None) -> str:
    """Where the patch starts: the newest commit on fork main's own line that the branch contains.

    Fork main's own line is its first-parent history, which a --no-ff merge of the branch does not
    add the branch's commits to. So this still finds the start of a patch after it has been merged
    into fork main, and after the branch has merged fork main to catch up.
    """
    contained = set(git("rev-list", branch, cwd=cwd).split())
    for commit in git("rev-list", "--first-parent", fork_main, cwd=cwd).split():
        if commit in contained:
            return commit
    raise GitError(f"{branch} shares no history with {fork_main}")


def export(branch: str, message: str, fork_main: str, onto: str, name: str | None, force: bool,
           cwd: Path | None = None) -> dict:
    base = patch_base(fork_main, branch, cwd=cwd)
    head = git("rev-parse", branch, cwd=cwd).strip()
    if base == head:
        raise GitError(
            f"{branch} has no commits of its own beyond {fork_main}. If it was merged by fast-forward, "
            f"its commits are now part of {fork_main}'s own line; merge patch branches with --no-ff")
    paths = changed_paths(base, head, cwd=cwd)
    layer = [p for p in paths if is_layer_path(p)]
    patch_paths = [p for p in paths if not is_layer_path(p)]
    if not patch_paths:
        raise GitError(f"{branch} changes only fork-layer paths; there is nothing to send upstream")

    patch = git("diff", "--binary", "--full-index", base, head, "--", *exclude_pathspecs(), cwd=cwd)
    target = name or "export/" + branch.split("/", 1)[-1]
    ref = f"refs/heads/{target}"
    if git("rev-parse", "--verify", "--quiet", ref, cwd=cwd, check=False).strip() and not force:
        raise GitError(f"{target} already exists; pass --force to replace it")

    onto_commit = git("rev-parse", f"{onto}^{{commit}}", cwd=cwd).strip()
    with tempfile.TemporaryDirectory() as tmp:
        env = dict(os.environ, GIT_INDEX_FILE=str(Path(tmp) / "index"))
        git("read-tree", onto_commit, cwd=cwd, env=env)
        try:
            git("apply", "--cached", "--3way", "--whitespace=nowarn", cwd=cwd, env=env, stdin=patch.encode())
        except GitError as e:
            raise GitError(
                f"the patch does not apply to {onto}. It probably depends on another patch that "
                f"upstream does not have; export that one first and pass it with --onto.\n{e}") from None
        if git("ls-files", "--unmerged", cwd=cwd, env=env).strip():
            raise GitError(f"the patch conflicts with {onto}; rebase {branch} on a fork main that has merged it")
        tree = git("write-tree", cwd=cwd, env=env).strip()
    if tree == git("rev-parse", f"{onto_commit}^{{tree}}", cwd=cwd).strip():
        raise GitError(f"{onto} already contains this patch")
    commit = git("commit-tree", tree, "-p", onto_commit, "-m", message, cwd=cwd).strip()
    git("update-ref", ref, commit, cwd=cwd)
    return {"branch": target, "commit": commit, "onto": onto_commit, "files": patch_paths, "layer_left_out": layer}


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("branch", help="patch branch cut from fork main")
    ap.add_argument("-m", "--message", required=True, help="commit message; upstream wants one short line")
    ap.add_argument("--fork-main", default="main", help="the fork branch the patch was cut from (default: main)")
    ap.add_argument("--onto", default=UPSTREAM_REF, help=f"what to apply the patch to (default: {UPSTREAM_REF})")
    ap.add_argument("--name", help="name of the branch to create (default: export/<branch>)")
    ap.add_argument("--force", action="store_true", help="replace an existing export branch")
    args = ap.parse_args()
    try:
        r = export(args.branch, args.message, args.fork_main, args.onto, args.name, args.force)
    except GitError as e:
        print(f"export_patch: {e}", file=sys.stderr)
        return 1
    print(f"{r['branch']} -> {r['commit'][:10]} on {r['onto'][:10]}, {len(r['files'])} file(s)")
    if r["layer_left_out"]:
        print(f"left out {len(r['layer_left_out'])} fork-layer file(s)")
    print("Nothing was pushed. Build and run tools/check_pr.py on the export branch before proposing it.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
