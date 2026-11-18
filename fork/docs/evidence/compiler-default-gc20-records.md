# Record-copy exceptions while adopting GC/2.0

Investigation date: 2026-11-16. Source revision `08c178922f`.

Both `pso/object/TObjResultWin.cpp` and
`pso/misc/TPlyMeetUserExtension_801DAC6C.cpp` can use **GC/1.3.2 without
source or flag changes**. This removes their need for GC/2.6 while keeping
the planned GC/2.0 game default and the already-retained GC/1.3.2 compiler.
The investigation did not edit either production source or configuration;
combined migration and linking are handled separately.

| Unit | Original exact functions, GC/2.6 | GC/2.0 unchanged | GC/1.3.2 unchanged | `.text` bytes |
|---|---:|---:|---:|---:|
| `TObjResultWin.cpp` | 9/9 | 8/9 | 9/9 | 1,576 |
| `TPlyMeetUserExtension_801DAC6C.cpp` | 4/4 | 3/4 | 4/4 | 868 |

Fresh compiles of both GC/2.6 and GC/1.3.2 preserve every allocated section's
contents, size and ELF alignment, all defined external/weak symbol layouts,
and normalized relocation positions, types and targets. Both GC/1.3.2
objects also match every original-owned function in the freshly split
original comparison. Compiler diagnostics are empty. This object comparison
excludes compiler comment metadata, so the full link remains an independent
acceptance requirement.

## Why the GC/2.0 probes differed

`copy_challenge_result_record` copies a three-word summary followed by two
20-byte entries. GC/2.0 hoists the second summary load before the first
store and changes temporary register allocation and address preparation.
The two subsequent entry-copy loops retain the original instructions.
The complete helper scores 85.31% under GC/2.0.

`TPlyMeetUserExtension` copies 64 bytes of tags, one word, and two 16-byte
names. GC/2.0 preserves the initial tag-copy loop but hoists and interleaves
the following word/name loads and stores differently. The helper scores
70.04%. Both GC/1.3.2 and GC/2.6 reproduce the original schedule with the
existing source; this does not identify the historical compiler.

## Bounded source and option experiments

Before testing GC/1.3.2, ten source variants tested ordinary representations:
whole-record assignment, named summary-field copies, the existing shared
`ChallengeResultRecord` type instead of local copy types, a mutable local
source view, a summary array, local aggregate temporaries, and word-array
or named-word representations for the name blocks. None preserved either
complete object under GC/2.0. The real shared ResultWin type changes the
entry-copy expansion more substantially; it is not an equivalent compiler
migration by itself.

Twenty-eight accepted option diagnostics covered seven optimizer disables
per unit and seven source-level scheduling/pointer-analysis settings per
unit. Propagation, loop, strength, dead-store and pointer-analysis controls
did not resolve these helpers. Other controls affected additional functions.
Disabling scheduling brings the MeetUserExtension helper to 95.36%: its
body matches, but the initial count/pointer setup instructions occur in a
different order. The diagnostic pragma also applies to subsequent functions,
which regress; it was not proposed for adoption. No diagnostics reported an
unknown option or illegal pragma. No source variant, compiler flag or pragma
from these unsuccessful GC/2.0 probes is needed for the GC/1.3.2 candidates.

GC/1.2.5n was also tested unchanged and regresses seven ResultWin functions
and all four MeetUserExtension functions. It offers no configuration-only
alternative for these two units.

## Reproduction

Private artifacts are under `/tmp/pso-gc20-record-repairs/`:

- `record_probe.py`: unchanged GC/2.0 baselines and ten source variants.
- `flags.py`: the 28 accepted option diagnostics.
- `versions.py`: unchanged GC/1.3.2 and GC/1.2.5n comparisons.
- `validate.py`: fresh GC/2.6 baselines, complete normalized-object comparison
  against GC/1.3.2, original-function counts and provenance hashes.
- `result/version_1.3.2/` and `meet/version_1.3.2/`: source snapshots, exact
  argv, diagnostics, objects, original/baseline objdiff JSON and results.
- `manifest.json`: revision, production-source and validation-artifact SHA-256.

Scripts run from the repository root. They use the installed tools and
compilers read-only from `/home/matt/workspace/pso-decomp/build`, and the
original split objects plus normalized ELF comparison helper from
`/tmp/pso-compiler-consolidation-20261113`. Source basenames are preserved
in isolated directories. A Python helper module name collision interrupted
one initial diagnostic driver; it was corrected and the full diagnostic
batch rerun. That interrupted invocation is not an additional result.

The successful candidates require only changing these two units' compiler
assignments to GC/1.3.2. No source patch or shared-header change is needed.

## Combined acceptance

The final [GC/2.0 adoption](compiler-default-gc20-adoption.md) integrates
these compiler choices and passes the original DOL hash and all no-loss
checks. No experimental source changes are included.
