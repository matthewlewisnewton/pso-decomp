# Adopt GC/2.0 as compiler default and linker

This records the initial adoption before merging newer main. See the
[current main-merge validation](compiler-default-gc20-main-merge.md) for the
final assignments and acceptance results. In that final configuration, the
nine initial GC/1.3.2 experiment units return to the GC/2.0 default.

Date: 2026-11-16. Baseline: `08c178922fb8da57f44c2d9fc4efb5ebdecf05b4`.
The working configuration now uses GC/2.0 for the linker and most sources.
No compiler or linker assignment uses GC/2.6. This is a validated matching
configuration, not a claim about Sega's historical compiler selection.

## Changes

The [reverse sweep](compiler-default-gc20-impact.md) established that 3,392
former GC/2.6 C/C++ units produce equivalent objects under GC/2.0. Those
assignments now use GC/2.0, including explicit middleware/runtime profiles.
Gryphon, Slime and Dragon inherit the new default without source changes;
their redundant compiler overrides are removed and Dragon's flags remain.

The five originally retained GC/2.6 exceptions are resolved as follows:

| Unit | Final compiler | Validation |
|---|---|---|
| `pso/network/TProtocol.cpp` | GC/1.3.2 | All 79 original-owned functions match; the combined link validates selection of the 14 differing emitted helpers. |
| `pso/object/TObjTombstone.cpp` | GC/1.3.2 | Complete normalized object equivalent to GC/2.6; 37/37 original functions exact. |
| `pso/object/TObjResultWin.cpp` | GC/1.3.2 | Complete normalized object equivalent to GC/2.6; 9/9 exact. |
| `pso/misc/TPlyMeetUserExtension_801DAC6C.cpp` | GC/1.3.2 | Complete normalized object equivalent to GC/2.6; 4/4 exact. |
| `pso/boss/TBoss2DeRolLe.cpp` | GC/2.0 default | All 108 existing exact functions remain exact. The sole changed already-unmatched function improves from 97.96943% to 98.58079%. |

The bounded source experiments are documented for
[TProtocol](compiler-default-gc20-protocol.md),
[the record helpers](compiler-default-gc20-records.md), and
[Tombstone/De Rol Le](compiler-default-gc20-tombstone.md). None of their
source or header variants is adopted. The final change only changes compiler
and linker selection, documentation and the generated exception inventory.
Source, headers, flags, symbols, splits, linkset, retention entries, and
object processing are unchanged. The prior nine GC/2.0-to-GC/1.3.2 migrations
remain in place.

The new inventory has five compiler versions, down from six:

| Compiler | Configured entries |
|---|---:|
| GC/2.0 | 3,398 |
| GC/1.3.2 | 34 |
| GC/1.3 | 59 |
| GC/1.2.5n | 134 |
| GC/1.2.5 | 8 |

Counts include generated assembly and an absent-source entry; they are not
C/C++ compilation counts. Retiring GC/1.3 and GC/1.2.5 remains separate work
before the proposed three-compiler set is achieved.

## Validation

The baseline build and report are preserved at
`/tmp/pso-gc20-migration-20261113/baseline`. Initial experiments separately
validated the broad GC/2.0 migration, GC/2.0 linker, and the four GC/1.3.2
profiles. The final combined configuration was built in a private copy at
`/tmp/pso-gc20-adoption-20261116/final`, using the same original inputs and
pinned tools as the preceding audit. All resolved object options, their
order, and the linker version were compared to the working checkout.

- `ninja -j2` passes; the linked DOL SHA-1 remains
  `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- `tools/check_pr.py --no-build --baseline
  /tmp/pso-gc20-migration-20261113/baseline/build/GPOE8P/report.json` passes
  after the combined build.
- Exact functions remain 27,444; matched code remains 4,241,872 bytes;
  matched data remains 1,477,679 bytes. No exact-function regressions.
- All 3,610 source-linked units remain exact; source-bearing unit count
  remains 3,632.
- Retention has 18,650 entries, with zero additions or removals.
- The report differs only in De Rol Le's improved nonexact function score.
  Overall fuzzy match increases from 97.8309% to 97.831154%; the report is
  intentionally not described as byte-identical.
- Independent configuration review confirms no noncompiler option, object
  order, source path, or link-status change from HEAD, apart from the
  compiler/version assignments described here.

Logs and machine-readable results are `final-build.log`, `final-check.log`
and `final-check.json` in the experiment directory. `manifest.json` records
hashes of the final configuration, reports, output DOL and selected compiler
and linker binaries. Derived objects and original data remain outside the
repository. `git diff --check` and the generated exception inventory check
also pass.
