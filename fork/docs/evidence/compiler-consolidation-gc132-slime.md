# Slime under GC/1.3.2

Investigation: 2026-11-14, source baseline `08c178922f`. This is an isolated
source-repair experiment; the checkout's production source and compiler
assignment remain unchanged.

GC/1.3.2 can reproduce the complete existing GC/2.0 Slime object after
correcting call expressions and the declared placement of one external
constant. The previous compiler-only test understated the feasibility of
this alternative: most differences were caused by incompatible function
pointer casts in reconstructed source, rather than unavoidable scheduling.

| Isolated candidate | Exact original functions |
|---|---:|
| Existing source, GC/2.0 | 90/90 |
| Existing source, GC/1.3.2 | 80/90 |
| Direct calls and corrected declarations | 88/90 |
| Above, plus external constant in `.rodata` | 89/90 |
| Above, plus direct render translation call | 90/90 |

The final candidate preserves allocated section bytes, sizes and ELF
alignment, defined external/weak symbol layouts, and normalized relocation
positions/types/targets against the existing GC/2.0 object. Function scores
were also checked against the original split object. Compiler comment
metadata is not included in this normalized signature; the integrated check below validates linking separately.

## Changes and evidence

GC/1.3.2 emits indirect `lis`/`addi`/`mtctr`/`bctrl` calls for incompatible
function pointer casts that GC/2.0 reduces to direct `bl` calls. Removing
those casts recovers eight functions without changing compiler flags.

- `atan2_float` returns `f32`, consistent with
  `include/pso/player/TObjPlayer_80011014.h`. The local declaration incorrectly
  returned `f64`, while several calls cast it back to an `f32` function.
- `project_actor_to_ground` takes a pointer as its third argument, consistent
  with `include/pso/player/TObjPlayer_801542CC.h`. The local declaration used
  `int` and calls with a normal pointer cast the function. The experiment
  retains the existing opaque local interface but corrects that parameter.
- Calls to vector and matrix helpers, player lookup, and nearest-player
  search use the existing declarations directly. Player lookup explicitly
  receives `m_2d4`; the original instructions already load that field into
  the first argument register before the call.
- `defer_render` receives `this` explicitly. The matrix translation in
  `TObjEneSlime::render` receives `&position` without the unused extra
  argument invented by its function pointer cast. This also recovers the
  complete render function.
- `lbl_8043D218` is an eight-byte external slot template at original
  `.rodata:0x8043D218`, as recorded in `symbols.txt`. Explicit
  `__declspec(section ".rodata")` on its declaration prevents GC/1.3.2 from
  addressing it as small data. This recovers `init_slots`. If adopted, this
  compiler-specific declaration needs a porting-exception entry; a port
  keeps it as an ordinary external const object.

The candidate is a bounded demonstration, not a comprehensive cleanup of
this unit's remaining opaque declarations or casts. It introduces no
assembly, new ownership, changed shared headers, or compiler flag changes.

## Reproduction

`/tmp/pso-gc132-slime/probe.py` generates the source variants, records exact
compiler argv and diagnostics, and compares each against the original.
It uses the original source basename in separate directories so static
initializer names remain comparable. An initial trial with variant names
was discarded and rerun for that reason.

Final source: `/tmp/pso-gc132-slime/combined/TObjEneSlimeTailAttack.cpp`.
Reviewable source patch: `/tmp/pso-gc132-slime/combined.patch`.
Object and original comparison: `/tmp/pso-gc132-slime/combined.o` and
`combined.json`. The compiler diagnostics are empty. Original split inputs
and comparison helpers are from `/tmp/pso-compiler-consolidation-20261113`.

## Integrated validation

A private copy of the previously validated nine-unit migration build at
`/tmp/pso-gc20-migration-20261113/candidate` received only this source
candidate and the Slime compiler assignment change to GC/1.3.2. The build
in `/tmp/pso-gc132-slime/integrated` recompiled Slime and relinked the DOL.

- The original DOL SHA-1 passed:
  `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- The generated report is byte-identical to the nine-unit migration baseline.
- `tools/check_pr.py --no-build --baseline
  /tmp/pso-gc20-migration-20261113/candidate/build/GPOE8P/report.json` passed
  after the completed build: all 3,610 source-linked units remain exact,
  with no retention additions or removals across 18,650 entries.

Logs are `integrated-build.log` and `integrated-check.log` in the experiment
folder; machine-readable checks are in `integrated-check.json`. The source
patch is validated but remains isolated, pending the overall compiler-set
choice. Production source, compiler assignments and porting register were
not changed by this follow-up experiment.
