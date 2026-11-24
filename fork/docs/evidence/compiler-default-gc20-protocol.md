# TProtocol in the GC/2.0 default migration

Investigation: 2026-11-16, source revision `08c178922f`. Production source
and shared headers remain unchanged by this investigation. Experiments use
same-basename copies and private header overlays in
`/tmp/pso-gc20-protocol-repair`.

## Retained GC/1.3.2 is a promising alternative

| Compiler | Exact original-owned functions | Changed emitted helper functions versus GC/2.6 |
|---|---:|---:|
| GC/2.6 | 79/79 | 0 |
| GC/2.0 | 76/79 | 6 |
| GC/1.3.2 | 79/79 | 14 |

Unchanged source with GC/1.3.2 restores all three exact matches lost under
GC/2.0. It also restores the other three emitted helpers that GC/2.0
changed. Its 14 differences are other generated helpers which are not
original-owned functions in this unit. All allocated non-code contents,
sizes and ELF alignment remain baseline-equivalent. The full allocated
object is **not** equivalent, because those 14 emitted bodies and their
layout differ. Therefore this candidate needs an integrated link: its
success depends on which weak definitions the linker selects across the
whole project. An object-level 79/79 result alone cannot authorize it.

The GC/1.3.2 command retains all existing source and flags and changes only
the compiler executable. Compiler diagnostics are empty. The comparison
against original split objects uses `functionRelocDiffs=data_value`.

## GC/2.0 source and option experiments

The three lost original-owned functions are the `TMessageBox` and
`TChatMessage` copy constructors and `QuestListEntry` assignment. GC/2.0
moves the first header load before prologue stores in the constructors,
and uses different scalar load/store scheduling and register assignment.
The remaining changed emitted helpers are `TUserAns` and `TPlyJoinGame`
copy constructors and `TPlyMeetUserExtension` assignment.

Twenty-three accepted source/option probes did not preserve the complete
GC/2.6 object under GC/2.0:

- Explicit `TMessageBox` copy construction using member initializers and
  ordinary `memcpy`, intrinsic `__memcpy`, or aggregate text copies. The
  intrinsic reproduces the implicit constructor's existing discrepancy;
  the other forms introduce larger changes.
- Removing constness from the source view inside that explicit constructor
  leaves the discrepancy unchanged. These were diagnostic alternatives,
  not a recommended API change.
- Constructor-local scheduling, pointer analysis, propagation, common
  subexpression, lifetimes, dead-code and peephole pragmas leave the six
  discrepancies unchanged. Header-wide scheduling settings additionally
  change other emitted functions.
- Whole-unit scheduling, peephole, propagation and lifetime options do not
  solve the complete object. Disabling scheduling changes 128 emitted
  functions; disabling peephole changes 83. Disabling propagation changes
  eight, while disabling lifetimes leaves the same six differences.

A further `-opt nopointeranalysis` probe was rejected with an unknown-option
warning even though compilation returned success. It is excluded from the
23 accepted probes and provides no evidence about that optimizer control.
The two unchanged compiler builds bring the diagnostic total to 26.

No tested GC/2.0 source repair was adopted. The unchanged GC/1.3.2 candidate
is preferable to expanding source steering if integrated linking confirms
that the different weak helpers are not selected.

## Reproduction

- `runprobe.py`: baseline, source/header variants and normalized whole-object
  comparisons. It imports the earlier audit's `normalize.py` helper.
- `more.py`: additional explicit-constructor and whole-unit option probes.
- `retained.py`: unchanged GC/1.3.2 compilation.
- `<variant>/`: source/header overlay, exact `argv.json`, compiler `log`,
  output object, baseline diff and result summary.
- `retained_132/original.json`: original-owned function comparison for the
  retained-compiler candidate; `baseline/original.json` is the GC/2.0
  original comparison.

The older `probe.py` entry point duplicates the first-stage harness;
`runprobe.py` avoids a module-name collision with the earlier audit helper.
Tools, compiler binaries and generated includes are read-only inputs from
`/home/matt/workspace/pso-decomp/build`. Original split objects come from
`/tmp/pso-compiler-consolidation-20261113/original/obj` and the GC/2.6 baseline
from `/tmp/pso-gc20-default-impact/objects/pso__network__TProtocol.cpp`.
The experiment does not establish Sega's historical compiler choice.

## Combined acceptance

The final [GC/2.0 adoption](compiler-default-gc20-adoption.md) integrates
these compiler choices and passes the original DOL hash and all no-loss
checks. No experimental source changes are included.
