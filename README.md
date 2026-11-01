# Phantasy Star Online Episode I & II Plus

A work-in-progress matching decompilation of *Phantasy Star Online Episode I & II Plus* for the Nintendo
GameCube, USA version 1.02 (`GPOE8P`): C and C++ source that compiles to the same code as the game's executable,
function for function, in its original translation units.

Nothing from the game is included here. You need your own copy of the game to build it; see [Legal](#legal).

## Progress

<!-- progress-table -->
| | Matched | Linked |
|:--|--:|--:|
| Code | 94.71% (4,122,736 of 4,353,092) | 76.77% (3,341,952 of 4,353,092) |
| Data | 73.16% (1,288,599 of 1,761,375) | 53.36% (939,823 of 1,761,375) |
| Functions | 98.88% (27,262 of 27,572) | |
| Units | | 69.88% (3,540 of 5,066) |
<!-- /progress-table -->

Measured on `PsoV3.dol` on 2026-11-01 at validated source commit
[`6d3955be03`](https://github.com/matthewlewisnewton/pso-decomp/commit/6d3955be03c76b4c62ef1c9ea861c5f411894bc1).
The README-only publication commit records the measurements of its parent source tree.
A function is matched when it compiles to the original's exact bytes. Code, data and
units are linked when the build takes them from compiled source instead of the original. Data includes `.bss`.
The build still uses 1,526 original-object fallback units; matched functions in those units are not counted as
source-linked coverage. Unit counts can change when translation units are consolidated.

## Target

| | |
|---|---|
| Game | Phantasy Star Online Episode I & II Plus, USA v1.02 (`GPOE8P`) |
| Disc | SHA-1 `0ff155311f4cc57951c03baeb1a8cc15de5fe1cd` |
| Executable | `files/PsoV3.dol`, SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3` |
| Compiler | Metrowerks CodeWarrior for GameCube: GC/2.6 for most game code, older versions for the SDK, MetroTRK, MusyX and some game units |

## Building

You need Python 3.10 or newer, [Ninja](https://ninja-build.org/) and your own dump of the disc.

1. Put the disc image (ISO, GCM, RVZ, WIA, GCZ or CISO) in `orig/GPOE8P/`.
2. Run:

       python configure.py
       ninja

The first build downloads the compilers, [decomp-toolkit](https://github.com/encounter/decomp-toolkit),
[objdiff](https://github.com/encounter/objdiff) and binutils into `build/`. On Linux and macOS the compilers run
through [wibo](https://github.com/decompals/wibo); to use Wine instead, pass its path to `configure.py --wrapper`.

`ninja` rebuilds `PsoV3.dol` and checks it against the original's SHA-1, along with the 648 relocatable data files
and the language files the game loads. Code that is not decompiled yet still comes from the disc, so a passing
build does not mean the decompilation is complete. The same goes for the functions Nintendo and Metrowerks wrote
in assembly: `tools/orig_asm.py` rebuilds their bodies from your disc before anything is compiled.

## Objdiff and the progress page

`ninja` also writes `objdiff.json` in the repository folder and the objdiff progress report,
`build/GPOE8P/report.json`.

- **objdiff.** Download [objdiff](https://github.com/encounter/objdiff/releases) and open the repository folder
  in it. It reads `objdiff.json`, rebuilds a unit when you save its source and shows each function next to the
  original.
- **Progress page.** Turn the report into a page you can browse by unit and function:

      python tools/progress_map.py build/GPOE8P/report.json -o build/progress

  Then open `build/progress/index.html` in a browser. Add `--readme README.md` to refresh the table above.

## Working on it

- **Check for regressions.** Run `ninja baseline` before a change and `python tools/check_pr.py` after it. It
  rebuilds, compares the reports by original address, so renaming, folding or splitting units never hides a lost
  match, and checks that every linked unit still links from source.

[CONTRIBUTING.md](CONTRIBUTING.md) covers what a change can do and the rules for it.
[docs/architecture.md](docs/architecture.md) describes how the executable and the source tree are laid out.
The [documentation index](docs/README.md) links to contributor guides and recovery evidence.

## Credits

Built with [decomp-toolkit](https://github.com/encounter/decomp-toolkit), [objdiff](https://github.com/encounter/objdiff)
and [dtk-template](https://github.com/encounter/dtk-template). The Dolphin SDK and runtime sources are adapted from
other GameCube decompilations; [third_party/](third_party/README.md) lists them.

## Legal

This repository contains no game assets, no game files, no assembly and no code copied from the game. Every line of
source was written by hand, by this project's contributors or by the open-source projects credited above, to
compile into the same machine code as the original. Everything else the build needs comes from your own legally
obtained copy of the game, on your machine, when you build.

*Phantasy Star Online* is a trademark of SEGA. This project is not affiliated with or endorsed by SEGA or Nintendo.

## License

[MIT](LICENSE). Code adapted from other projects keeps its original notices.

### Development evidence comparison

`python3 tools/evidence_applicability.py BASELINE.json CURRENT.json` compares
independently prepared, reviewed inventories. It prints JSON and exits nonzero
when evidence is missing or a file hash does not match. It never changes a
receipt, runs a build, authorizes reuse, or establishes acceptance freshness.
An unchanged aggregate coverage report is not proof of binary equivalence.

Both JSON snapshots have `version: 1`, a full 40-character `revision`, an
absolute `root`, `proofs`, `global_inputs`, and a nonempty `consumers` object.
Every file entry is `{"path": "relative/path", "sha256": "<lowercase 64-digit SHA-256>"}`;
paths must be root-relative, contain no parent traversal, and resolve to regular files inside the snapshot root. Both the supplied path and its resolved root-relative path are compared, so a rename or changed symlink target is treated as a change even when bytes match. `proofs` contains
`graph` and `inventory_review`; the baseline also contains
`development_receipt`. Each is a file entry. `global_inputs` contains nonempty
file-entry maps under each of `source`, `tool`, `compiler`, `config`, and
`generated`. Each consumer has a nonempty `inputs` file-entry map. The baseline
consumer also has a nonempty `outputs` map. Stable keys identify equivalent
inputs across snapshots; all relevant compiler flags, transitive headers,
imported helpers, generated inputs, tools and output artifacts must be covered.
Output paths and hashes in the report identify baseline files only.

These inventories and proof files are **inputs to review**, not independently
verified claims of completeness, successful builds, or proof authenticity. The
operator must independently verify the graph and receipt semantics, the review
binding to both exact inventories, and their completeness before considering the
comparison. Whole-graph hashes from existing preparation receipts alone are not
per-consumer dependency inventories. Missing or stale files make the comparison
incomplete; changed global inputs affect every consumer, and changed consumer
inputs affect that consumer. New or removed consumers are affected. The queue
alone decides whether any artifact may be used, after independent review and
all applicable current-main, raw no-loss, DOL and ordered-link-input gates.
