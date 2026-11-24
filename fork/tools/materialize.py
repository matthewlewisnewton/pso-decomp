#!/usr/bin/env python3
"""Create a disposable checkout with the fork's local tools and compatibility changes."""
from __future__ import annotations

import argparse
import gzip
from pathlib import Path
import subprocess
import sys

from layer import GitError, repo_root


OVERLAY = "fork/tooling/workspace.patch.gz"


def git(repo: Path, *args: str, patch: bytes | None = None) -> bytes:
    result = subprocess.run(
        ["git", "-C", str(repo), *args],
        input=patch,
        capture_output=True,
        check=False,
    )
    if result.returncode:
        raise GitError(result.stderr.decode(errors="replace").strip())
    return result.stdout


def materialize(repo: Path, ref: str, destination: Path) -> Path:
    head = git(repo, "rev-parse", "--verify", "--end-of-options", ref + "^{commit}").decode().strip()
    patch = gzip.decompress(git(repo, "show", head + ":" + OVERLAY))
    destination = destination.absolute()
    destination.mkdir(exist_ok=False)
    git(repo, "clone", "--shared", "--no-checkout", "--", str(repo), str(destination))
    git(destination, "checkout", "--quiet", "--detach", head)
    git(destination, "apply", "--index", "--whitespace=nowarn", "-", patch=patch)
    git(
        destination, "-c", "user.name=Fork tooling workspace",
        "-c", "user.email=fork-tooling@localhost", "-c", "commit.gpgsign=false",
        "commit", "--quiet", "-m", "Apply the local fork tooling overlay",
    )
    return destination


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("destination", type=Path, help="new local workspace directory")
    parser.add_argument("--ref", default="HEAD", help="commit containing the fork layer (default: HEAD)")
    args = parser.parse_args()
    try:
        result = materialize(repo_root(), args.ref, args.destination)
    except (GitError, OSError) as error:
        print(f"materialize: {error}", file=sys.stderr)
        return 1
    print(result)
    return 0


if __name__ == "__main__":
    sys.exit(main())
