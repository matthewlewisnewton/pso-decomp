# Impact of replacing the GC/2.6 compiler default with GC/2.0

This is the initial feasibility report. The subsequent
[adoption record](compiler-default-gc20-adoption.md) resolves its five
exceptions and also tests the GC/2.0 linker.

A complete same-source, same-flags sweep finds that GC/2.0 is a credible
alternative default. Of 3,397 current GC/2.6 C/C++ units, 3,392 produce
identical allocated contents, ELF section alignment, external/weak symbol
layout and normalized relocations under GC/2.0. All units compile
successfully under both versions. Only five objects change, affecting ten
emitted function instances and losing six currently exact original-function
matches. No currently nonexact original function becomes exact.

An isolated full-build experiment also validates migrating the 3,392
equivalent units together while retaining GC/2.6 for the five changed units
and the linker. The original DOL hash and all repository no-regression
checks pass. This does not identify Sega's original compiler. No production
source or compiler assignment was changed by this investigation.

## Coverage and results

The inventory comes from the working configuration based on
`08c178922fb8da57f44c2d9fc4efb5ebdecf05b4`, including the nine prior
GC/2.0-to-GC/1.3.2 migrations. Those migrations do not affect the GC/2.6
population. This sweep tests every existing C/C++ source assigned GC/2.6,
not a sample. It includes explicit GC/2.6 library profiles as well as the
main-game default; changing `GAME_COMPILER` alone would affect only the
main-game rows.

| Population | Tested units | Equivalent objects | Changed objects | Changed emitted functions | Exact original functions lost |
|---|---:|---:|---:|---:|---:|
| Main game | 3,232 | 3,227 | 5 | 10 | 6 |
| Middleware/runtime | 165 | 165 | 0 | 0 | 0 |
| Total | 3,397 | 3,392 | 5 | 10 | 6 |

The 3,399 configured GC/2.6 entries also include
`pso/ui/TAdMultiPlyChrSelectGC_literals.s`, which does not invoke the C/C++
compiler, and `pso/unk/tails_adjacent_name.cpp`, whose source is absent.
Neither is a failed compilation or part of the 3,397 tested sources.

The equivalent objects own 3,448,552 of the tested units' 3,500,488 original
`.text` bytes. All 188,224 bytes owned by the tested middleware/runtime
units are in equivalent objects. These are original unit sizes, not counts
of changed instructions; most functions inside the five changed units are
also unchanged.

Comparing fresh baseline and candidate objects separately against original
split objects yields 23,928 exact original functions under GC/2.6 and
23,922 under GC/2.0, out of 23,976 original functions in the tested units.
These are object-comparison counts, not a new integrated build report.

## Repair queue

| Unit | Source-linked now? | Changed emitted function instances | Exact original matches lost | Character of difference |
|---|---|---:|---:|---|
| `pso/network/TProtocol.cpp` | Yes | 6 | 3 | Aggregate copy constructors and assignments |
| `pso/object/TObjTombstone.cpp` | Yes | 1 | 1 | `TObjTombstoneRecord` assignment |
| `pso/object/TObjResultWin.cpp` | Yes | 1 | 1 | `copy_challenge_result_record` |
| `pso/misc/TPlyMeetUserExtension_801DAC6C.cpp` | Yes | 1 | 1 | `TPlyMeetUserExtension` assignment |
| `pso/boss/TBoss2DeRolLe.cpp` | No | 1 | 0 | Already-unmatched `TBoss2DeRolLe__sub_8002FE60` |

All five change only `.text` contents; their allocated data contents and
section sizes/alignments remain unchanged. Defined external/weak symbol
layouts are unchanged in all five. Normalized relocations are unchanged in
the four linked units; De Rol Le also changes relocation positions within
its already-unmatched function.

The six changed `TProtocol` outputs are the copy constructors of
`TMessageBox`, `TChatMessage`, `TUserAns`, and `TPlyJoinGame`, and the
assignments of `QuestListEntry` and `TPlyMeetUserExtension`. Some emitted
weak helpers are not original-owned functions in that unit, which is why
six changed emitted functions do not mean six lost original matches.
Their linker selection must be checked in an integrated migration.

Instruction inspection narrows the six exact losses further:

- `TMessageBox`: GC/2.0 hoists the first header load across prologue setup.
- `QuestListEntry`: the first word's register and store scheduling change.
- `TChatMessage`: the first load moves and the later member-copy loads and
  stores interleave differently.
- `TObjTombstoneRecord`: scalar member loads/stores use a different schedule
  and alternating registers before the unchanged array-copy loop.
- `copy_challenge_result_record`: the first three-word summary copy changes
  load/store scheduling and registers; the source currently casts the
  record to local chunk structs before assigning its three components.
- `TPlyMeetUserExtension`: the tail name-field copies interleave differently;
  the source is an explicit helper using local chunk structs.

The first four are compiler-generated member-copy operations. The latter
two expose plausible source-organization questions before optimizer flags
are considered. None of the six differences is an indirect-versus-direct
call mismatch, and this inspection does not certify a source repair.

The initial source-repair scope is therefore four source-linked game
units, six exact original functions, and additional changed weak helper
copies. De Rol Le's existing exact functions are preserved, but retaining
its old profile until its one changed nonexact function is understood would
avoid an unrelated change. This sweep does not establish whether natural
source changes can repair the four linked units. The changes cluster in
aggregate-copy code, so their small count should not be mistaken for a
calendar estimate: earlier compiler-consolidation attempts showed that
individual scheduling differences can require substantial investigation.

## Method and reproducibility

Both compiler versions freshly compile every tested source with the same
resolved production flags and include files, changing only the compiler
executable and output path. The commands add an explicit language selector
when none is present. The generated headers, tool binaries and compilers
are read-only inputs from `/home/matt/workspace/pso-decomp/build`.

Object comparison includes allocated section bytes, sizes and ELF
alignment; defined external/weak symbol names and layouts; and relocation
positions, kinds and targets. Local relocation targets are normalized to
section plus offset and addend, so compiler-generated local names do not
create false differences. Compiler `.comment` metadata is excluded from
this equivalence test. All five units using an existing `cw_align`
postprocessing setting were also checked after applying that unchanged
setting independently to copies of both objects; all remain equivalent.

Original comparisons use `objdiff-cli` with
`functionRelocDiffs=data_value` and the original split objects from the
preceding consolidation audit, generated with the same current
symbols/splits. The original DOL was independently rechecked as SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

Local reproduction artifacts are under `/tmp/pso-gc20-default-impact/`:

- `inventory.json`: resolved current assignments, flags and unit sizes.
- `sweep.py`: fresh compilation and original-comparison driver; imports
  `probe.py` and `normalize.py` from the preceding audit directory
  `/tmp/pso-compiler-consolidation-20261113/`.
- `objects/`: exact compiler argv, diagnostics, compiled objects and JSON
  comparisons for each unit. Equivalent candidates reuse the baseline's
  original-comparison result after normalized equivalence is established.
- `results.json`, `results.jsonl`, `summary.txt`: complete results.
- `alignment-checks.json`: unchanged alignment-postprocessor checks.
- `manifest.json`: source revision and SHA-256 hashes of configuration,
  splits/symbols, source files, headers, compiler/tool binaries and results.

The complete sweep used two workers and finished in approximately
89 seconds. Derived original objects and compiled artifacts stay outside
the repository.

## Isolated integrated validation

A private copy of the previously validated nine-unit migration build at
`/tmp/pso-gc20-migration-20261113/candidate` was placed in
`/tmp/pso-gc20-default-impact/integrated`. Its sources and headers hash-match
the sweep inputs. Only this private copy's compiler configuration changed:
all GC/2.6 compiler assignments move to GC/2.0 except the five changed units
listed above; the linker remains GC/2.6. Existing flags, source, alignment
adjustments, symbols, splits and source linkage are preserved.

The build log records all 3,392 compiler edges rebuilding before linking.
Validation results:

- `ninja -j2` passes, including the original DOL SHA-1
  `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- `report.json` is byte-identical to the nine-unit migration baseline:
  27,444 exact functions, 4,241,872 matched code bytes and 1,477,679 matched
  data bytes.
- `tools/check_pr.py --no-build --baseline <candidate>/build/GPOE8P/report.json`
  passes, covering address-based no-loss and source linkage checks.
- All 3,610 linked units remain exact; no regressed linked units.
- The 18,650-entry retention inventory has no additions or removals.

Logs are `integrated-build.log`, `integrated-check.log` and
`integrated-check.json` under the scratch directory. This experiment
validates the broad equivalent-output migration with five exceptions; it
does not migrate or repair the exceptions themselves. Production
`configure.py` remains unchanged by this investigation.

## Interpretation and remaining validation

This result overturns the assumption that changing the default to GC/2.0
would necessarily cause widespread output changes: 99.85% of the tested
objects are equivalent without source edits. It does not prove GC/2.0 was
historically the primary compiler. Existing source has been developed
against matching profiles, and equivalent output under two compilers
cannot identify which compiler produced the original.

A GC/2.0 default is a small, concrete repair experiment worth pursuing
before forcing the three remaining GC/2.0 exceptions onto GC/2.6. It could
also replace all currently GC/2.6-assigned middleware/runtime compilers at
the object-equivalence level. Retiring GC/2.6 completely still requires
repairing or otherwise preserving the changed objects.

The isolated integration checks compiler comment metadata, weak selection
and full-link behavior for the 3,392 equivalent migrations as a combined
change. Changing the linker to GC/2.0 has not been tested. Repairing and
migrating any of the five remaining GC/2.6 units also requires new full
validation under [CONTRIBUTING.md](../../CONTRIBUTING.md).
