# The fork layer

This repository is a fork of [zeroz41/pso-decomp](https://github.com/zeroz41/pso-decomp).
It exists to develop patches that merge upstream cleanly. Everything in `fork/` supports
that work and is never proposed upstream.

## The two rules

1. **Code follows upstream.** Outside the layer, `main` is upstream's `master` plus
   patches that are still waiting to merge there.
2. **The layer only adds files.** It lives in `fork/` and in workflow files named
   `.github/workflows/fork-*.yml`. It never edits a file upstream owns, so merging
   upstream cannot conflict with it.

`fork/tools/layer.py` is the one definition of which paths are in the layer.

## Working on a patch

1. Cut a branch from `main`.
2. Do the work. Keep layer changes (notes, evidence, tooling) in separate commits from
   changes to upstream-owned files.
3. Notes on how a match was found go in `fork/notes/` or the pull request description,
   not in source comments. Upstream's rules do not allow them in the repository.
4. Validate with upstream's `python tools/check_pr.py`.
5. Merge the branch into `main` with `--no-ff`, so the fork has the work straight away.
6. Export it for upstream:

       python3 fork/tools/export_patch.py my-branch -m "Match TObjEneDimedian"

   This creates a local branch `export/my-branch`: one commit on `upstream/master` holding
   the branch's changes with the layer left out. It does not push and does not touch the
   checkout.
7. Build the export branch and run `tools/check_pr.py` on it. It is a different tree from
   `main`, so it needs its own check.
8. Proposing it upstream needs Matt's confirmation for that specific push or pull request.

A patch that builds on another patch upstream has not merged yet will not apply to
`upstream/master`. Export the earlier one first and pass `--onto export/earlier-branch`.

## Staying in sync

- Merge `upstream/master` into `main` with an ordinary merge. Never use `-s ours`: it
  records upstream's changes as taken when the tree did not take them, and every later
  upstream change to those files then conflicts.
- After upstream merges a patch, the same change arrives from both sides and the merge
  resolves itself. If upstream changed the patch in review, take upstream's version.
- `python3 fork/tools/check_layer.py` lists every non-layer file that differs from
  upstream. That list should only ever be the patches waiting to merge. Right after all
  of them have landed, `--expect-clean` must pass.
- `python3 fork/tools/check_layer.py --against my-branch` checks that a patch branch keeps
  layer and patch changes in separate commits.

## Tests

    python3 -m unittest discover -s fork/tools/tests -v

They build small throwaway repositories and need no game data or compiler.
