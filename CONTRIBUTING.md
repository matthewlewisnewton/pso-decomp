# Contributing

This is a matching decompilation: a function counts when its compiled code is byte-identical to the original,
lives in the unit that owns its address, and uses ownership and names supported by evidence. The objdiff report
(`build/GPOE8P/report.json`) measures matches; the linked-unit checks and actual linker inputs separately show
what the build takes from source. Use whatever tools you like; send a reviewable pull request.

## Setup

Follow [Building](README.md#building) in the README. Never commit the original or anything extracted or built from
it: `orig/` and `build/` are ignored.

## What a change can do

- **Match functions.** C or C++ for functions that were not matched before, which objdiff reports as exact.
- **Define data.** A unit's tables, strings and other data objects in source, so its data sections match.
- **Link a unit.** Once every function and data section in a unit matches, `tools/link_units.py scan --write` adds
  it to `config/GPOE8P/psov3/linked_units.txt` so the build takes it from source.
- **Fold or split units.** Move functions and data into the unit that owns them, merging ranges that belong to one
  original object file or splitting ones that don't, and update `config/GPOE8P/psov3/splits.txt` to match.
- **Name things.** Real names for functions, classes, members and data, in the same change as the evidence for them.

[docs/architecture.md](docs/architecture.md) explains units, linking and the source layout.

## Recovering a function

1. Find the unit that owns its address in `config/GPOE8P/psov3/splits.txt`; its source file has the same path
   under `src/`.
2. Use an evidence-backed member or free function and shared declarations where known. If ownership or a type is
   unresolved, keep the boundary provisional and document it rather than inventing a class interface. Keep virtual
   declarations in the verified slot order.
3. Open the repository in objdiff, select the unit and compare. objdiff rebuilds the unit when you save.
4. Prefer address order when it produces the correct object. Where it does not, use the source order and supported
   compiler settings that reproduce the original emitted layout; explain the reason and validate the complete object.

## Checking a change

Build the commit your change starts from and save its report:

    python configure.py
    ninja
    ninja baseline

Then make your change and run:

    python tools/check_pr.py

It must end in `PASS`. It runs these checks, which you can also run one at a time:

- `ninja` rebuilds `PsoV3.dol` and checks it against the original's SHA-1.
- `python tools/report_delta.py build/GPOE8P/baseline.json build/GPOE8P/report.json --check` compares the reports by
  original address, so renames and folds can't hide a loss: no exact function, linked unit or data range may go
  missing. Alignment padding that drops out of every unit when you split one off is shown but allowed, since its
  bytes are zero and nothing lives there. `ninja changes` lists the per-function differences.
- `python tools/link_units.py check` checks that every unit in `linked_units.txt` still links from source. objdiff
  can score a unit 100% while its object won't link. One example is a constant or string turned into a literal
  that `symbols.txt` still exports as a global.

When `link_units.py` reports a problem, run `python tools/link_units.py scan`. It writes every reason for each unit
to `config/GPOE8P/psov3/linked_units_blocked.json`:

- `missing <symbol>`: the original exports a symbol your source no longer defines. Run
  `python tools/localize_split_globals.py --write <unit>`, then rebuild. It marks the symbol `scope:local` in
  `symbols.txt` after checking that no other object refers to it. If something else does refer to it, define it
  in source under that name instead.
- `section <name>`: the compiled object has data the unit's split doesn't own yet. Claim that range in
  `splits.txt`.
- `size`, `alignment`, `order` or `data-layout`: the object's layout still differs from the original's.
- `data <section>:<percent>`: that section's data doesn't match yet.

`localize_split_globals.py` only marks symbols in units whose reasons are all `missing`, since any other reason
would keep the unit from linking anyway.

When your change makes a whole unit match, run `python tools/link_units.py scan --write` to link it, then
`python configure.py` and `ninja` again, and commit the updated `linked_units.txt` and `config.yml`.

## Rules

- Nothing that matches or links today may stop matching or linking: `tools/check_pr.py` must pass.
- Normally keep one source file per unit and shared class declarations in `include/`. Compiler-supported header and
  source organization may differ where needed to reproduce native code and data emission; explain the arrangement
  and avoid artificial units, references or hand-written tables. Source definition order is a readability preference,
  not a substitute for matching the emitted object. In CodeWarrior, deferred emission can change function, vtable
  and switch-table ordering: ascending definitions in the Gee investigation retained instruction bytes but changed
  relocation positions and vtable layout ([evidence](docs/compiler-emission-evidence.md)). This is evidence for an
  exception, not proof of the original source order.
  Check code, data, alignment and relocations, not function scores alone.
- No assembly, anywhere. A function Nintendo or Metrowerks wrote in assembly keeps its C signature with the body
  `#include "orig_asm/<unit>/<function>.inc"`, and `tools/orig_asm.py` generates that body from the disc during the
  build. Never write assembly by hand; a function that can only be matched that way stays unmatched.
- No data copied out of the game: no byte dumps of textures, models, sounds or other assets.
- Write readable source and prefer evidence-backed members and real types. Unresolved offsets, opaque pointers and
  legacy declarations may remain at a bounded interface when the evidence is incomplete; document their uncertainty
  and improve them as the evidence permits. Do not fabricate ownership or use casts to conceal incompatible APIs.
  Do not write vtables by hand.
- Explain non-obvious matching constraints, ABI boundaries and uncertain ownership in concise comments or evidence
  documents. Addresses can identify the relevant original code. Avoid commented-out code and speculative claims: a
  reproducible explanation helps future contributors avoid undoing a necessary arrangement.
- Names come from evidence in the executable: strings, class-name tables, vtables, call patterns. Keep the
  placeholder (`fn_<address>`) rather than guess.
- Code copied or adapted from another project keeps its notices. Add the project to `third_party/README.md`,
  with its license text under `third_party/LICENSES/` if its terms require a copy.

## Pull requests

- One coherent piece of work per pull request, such as one class or one unit.
- Title it with the result: `Match TObjEneDimedian`, `Link TLobby.cpp`, `Split TBoss8Dragon into its units`.
- Say what changed: matched functions and code and data bytes before and after (the first lines of
  `report_delta.py`), and the evidence for any unit boundary or name.
- Base independent work on the current fork `master`; a dependency stack may use an explicit fork-local base.
  Identify prerequisite PRs and immutable commits, and validate both the incremental change and its combined base.
  Re-run `tools/check_pr.py` after rebasing or integration.
- Use clear commit messages and describe the result, validation and remaining uncertainties in the pull request.
  Fork maintainers choose the merge method that preserves useful history and dependency context.
