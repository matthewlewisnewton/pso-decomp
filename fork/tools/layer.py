"""The fork layer: which paths belong to the fork and never go upstream.

Everything else in the repository follows upstream. See fork/README.md.
"""
from __future__ import annotations

import subprocess
from pathlib import Path

# A path is in the layer when it is one of these directories or inside one, or matches one of
# these file-name prefixes. Keep this list short: every entry is a place upstream must never use.
LAYER_DIRS = ("fork",)
LAYER_PREFIXES = (".github/workflows/fork-",)

UPSTREAM_REF = "upstream/master"


def is_layer_path(path: str) -> bool:
    path = path.strip("/")
    for d in LAYER_DIRS:
        if path == d or path.startswith(d + "/"):
            return True
    return any(path.startswith(p) for p in LAYER_PREFIXES)


def exclude_pathspecs() -> list[str]:
    """Pathspecs selecting everything outside the layer."""
    specs = ["."]
    specs += [f":(exclude,top){d}" for d in LAYER_DIRS]
    specs += [f":(exclude,top,glob){p}*" for p in LAYER_PREFIXES]
    return specs


def git(*args: str, cwd: Path | None = None, env: dict | None = None, check: bool = True,
        stdin: bytes | None = None) -> str:
    result = subprocess.run(["git", *args], cwd=cwd, env=env, input=stdin, capture_output=True)
    if check and result.returncode != 0:
        raise GitError(f"git {' '.join(args)}: {result.stderr.decode(errors='replace').strip()}")
    return result.stdout.decode(errors="replace")


class GitError(RuntimeError):
    pass


def repo_root(cwd: Path | None = None) -> Path:
    return Path(git("rev-parse", "--show-toplevel", cwd=cwd).strip())


def changed_paths(base: str, head: str, cwd: Path | None = None) -> list[str]:
    out = git("diff", "--no-renames", "--name-only", "-z", base, head, cwd=cwd)
    return [p for p in out.split("\0") if p]
