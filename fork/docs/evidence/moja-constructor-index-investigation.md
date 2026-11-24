# Moja constructor index investigation — PR 394

Date: 2026-11-10. Investigated immutable PR head
`2484bc5ae9d6042a06d935a27663696d7d2bb99e` in a separate managed worktree.

## Recommendation

The first 216-probe sweep below found no complete matching replacement among
the five proposed alternatives. A subsequent
[compiler-tracing and Dreamcast-informed round](moja-compiler-tracing.md)
found an exact real byte-offset lookup that removes the divide-back operation,
plus an independently exact field-clamp cleanup. Both remain reviewable scratch
candidates; PR 394's approved source has not been changed.

The strongest next direction is recovery of the original Moja compilation unit
and its shared constant pool. With ordinary table indexing, literal `0.0f` and
`1.0f` clamp bounds, and the constructor pragma removed, **all 2,204 raw `.text`
bytes match the already-matching baseline**, including the entire 632-byte
constructor. Four relocations refer to newly emitted constants instead of the
original shared bounds, and `.sdata2` grows from 8 to 16 bytes. This is a useful
source-recovery lead, not an exact object or a patch ready to integrate.

The follow-up traces establish the relevant virtual-register and literal-pool
mechanisms. Further blind permutations of index algebra or the tested flags
have lower priority. API typing remains a useful independent cleanup; it does
not fix this match.

## Method and provenance

Three subagents investigated inline helpers, clamp/constant context, and table
layout/API types. The parent independently investigated compiler settings and
verified the key raw-section comparisons. There were 216 successful probe
compilations across the four lanes, including repeated controls and 12 duplicate
inline confirmation runs, plus the matching baseline compilation. This count
is not a count of unique algorithms or independent hypotheses.

- Original DOL SHA-1 verified locally:
  `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- Original objects freshly split using this PR head's `config.yml`, `splits.txt`,
  and `symbols.txt`, with `dtk dol split --no-update`.
- Compiler: CodeWarrior GC/2.6, production Moja flags including `-O4,s`,
  `-inline off,deferred`, and `-sdata2 4`, except explicitly tested settings.
- Tool versions checked: dtk 1.8.4, objdiff-cli 3.6.1, wibo 1.0.3.
- Every source variant compiled the complete six-function Moja unit. The
  matching baseline reproduced all six functions and owned sections at 100%:
  `.text` 2204 bytes, `.data` 776 bytes, `.sdata2` 8 bytes.
- Comparisons used `functionRelocDiffs=data_value`, per-function outcomes,
  source-side section sizes, and selected raw ELF section/relocation checks.
  Final successful compiler runs had no compiler warnings.

Scores below are objdiff scores, not percentages of identical instruction words.
Objdiff can report the target's 8-byte small-data fragment as 100% while the
candidate emits 16 or 24 bytes; source-side section sizes were checked separately.

No production source, header, split, compiler configuration, or PR was changed.
This first round did not run a full-game link or `check_pr.py`: no candidate in
that round passed the complete-object requirements. The follow-up's exact
candidates also await integration and normal linked validation.

## What the scaled index compensates for

The approved spelling converts an element index into a byte offset and back:

```cpp
const size_t kind = variant;
const size_t variant_offset = kind * sizeof(*lbl_805D50C8);
// Both entries are pointers, four bytes on GameCube.
lbl_805D50C8[variant_offset / sizeof(*lbl_805D50C8)];
lbl_805D50D0[variant_offset / sizeof(*lbl_805D50D0)];
```

The experiments isolate two coupled constraints:

| Source form | Constructor score | Remaining mismatch |
|---|---:|---|
| Approved scaled index, named bounds, CSE off | 100% | None |
| Direct index, named bounds, CSE off | 99.841774% | Four r7/r8 instruction words |
| Direct index, named bounds, CSE on | 99.43038% | Fourteen floating-point register words; table registers now correct |
| Direct index, literal bounds, pragma removed | 99.87342% | Raw `.text` identical; four bound relocations and extra 8 bytes of `.sdata2` |

The direct-index/CSE-off differences occur at constructor offsets `+0x170`,
`+0x174`, `+0x188`, and `+0x190`: original addresses `0x800AFA20`, `0x800AFA24`,
`0x800AFA38`, and `0x800AFA40`. The table pointer and shared scaled index exchange
r7 and r8. Function order, section sizes/alignment, and data bytes remain unchanged.

The literal/default-CSE candidate's changed bound relocations are at constructor
`+0x80`, `+0xa8`, `+0xc0`, and `+0xe0`. They target generated literals rather than
shared zero/one at `0x805D9BD8` and `0x805D9BDC`. Equal raw instruction bytes do
not imply an equal linked executable when those relocations differ.

## Findings by option

| Option | Probe coverage | Finding |
|---|---|---|
| Natural inline helpers | 92 compilations, including repeated controls | Generic/specific lookups, combined binding, initialization helpers, aggregates, and reference/value/pointer clamps did not produce an exact replacement. Best remained 99.841774%. A CSE-off inline helper inside a CSE-on constructor did not retain a useful optimization boundary. Five siblings and data remained exact. |
| Clamp form and constant context | 39 variants | Literal bounds plus default CSE reproduce all raw instruction bytes but introduce the four relocation differences and 8 extra small-data bytes. Locals, references, branch forms, and visible/after-use constant definitions did not fix complete-object matching. |
| Real 2×3 attack-table structure | Included in 48 table/type probes | Valid storage model: changing the six-pointer allocation to two rows of three leaves the loader exact. Constructor drops to 98.28481% with CSE off because it computes `variant * 12 + attack * 4` rather than scaling the combined flat index. |
| Typed API and indices | Included in 48 table/type probes | Signedness, locals, and all six argument-local declaration orders leave the same register swap. A typed binding API produces identical raw code to its untyped counterpart; only the mangled call relocation changes. It requires broader caller/definition/config migration and offers no match improvement here. |
| Supported compiler settings | 37 variants including direct control | Propagation, lifetimes, strength reduction, peephole, dead assignments, pointer analysis, loop invariants, and selected combinations do not fix it. Disabling scheduling worsens it. Removing deferred emission changes code/data layout; other optimization levels regress the unit. |

Typed-API scores are slightly lower solely because the old mangled symbol remains
in the comparison target. Renaming the symbol consistently would remove that
penalty but would not alter the table-register mismatch.

The inline precedent in `chr-select-slot-clamp-inline.md` remains valid for that
other unit. These tests show it does not transfer to Moja merely by wrapping
operations in a plausible helper. They do not prove no original inline form
could ever match.

## Next investigation: ownership and pooling

The fresh split leaves `.sdata2 0x805D9BD8..0x805D9C60` as a 136-byte automatic
object, `auto_11_805D9BD8_sdata2`. Its first two entries are the shared zero and
one. The constructor-exclusive 0.3f/0.6f constants follow immediately at
`0x805D9C60..0x805D9C68`.

The preceding source `TObjPlayer_800ACA60.cpp` is substantially Moja code, including
appearance clamping, rare-variant selection, updates, rendering, and target
acquisition. Earlier Moja members, the resource loader, and `run_task` all use the
shared pool. A useful initial ownership hypothesis covers code
`0x800ACA60..0x800AFB28` and pool `0x805D9BD8..0x805D9C68`.

That is not a proven original object boundary. Additional simple Moja members at
`0x800ACA0C`/`0x800ACA10` currently sit at the end of Shark, and `bindModel` at
`0x800AFB30` sits in the next unit. Their inline/emission ownership also needs
checking before choosing final boundaries.

A follow-up should establish the actual consumers and emission ownership,
recover natural literal forms across the supported unit, and test whether MWCC
pools them at the original shared addresses. It must preserve every existing
function, section, relocation, and linked range. Simply assigning the whole
pool to the six-function tail, adding duplicate definitions, or filling gaps by
hand would not establish that recovery. No broad fold was attempted here.

## Local reproduction artifacts

The complete candidate sources, header overlays, compile commands, compiler logs,
objects, objdiff outputs, generation scripts, and individual reports are retained
in ignored `build/moja-index-investigation/` in the investigation worktree. These
are local artifacts, not files distributed with this repository. The tracked
[follow-up report](moja-compiler-tracing.md#reproducing-the-method) explains how
to reproduce the method from a fresh checkout. Extracted material stays under
ignored `build/`; do not commit it.

- Inline helper report: `inline_helpers/findings.txt`.
- Clamp/constant report: `clamp_context/REPORT.md`.
- Table/type report: `table_types/FINDINGS.md`.
- Compiler-setting report: `compiler_settings/FINDINGS.md`.
- Recorded-command replay script: `replay.py`.
- Provenance manifest: `manifest.json`.

For example, from this worktree:

```sh
python3 build/moja-index-investigation/replay.py clamp_context/diag_literal_default.cpp
```

The replay uses the recorded compiler command and relocates scratch paths into
the archived artifact directory, then diffs against the saved freshly split Moja
object. In this environment wibo requires execution outside the restricted
sandbox because a required system call otherwise causes SIGSYS. Reproduction
still requires the locally installed compiler/tool paths recorded in the manifest.
