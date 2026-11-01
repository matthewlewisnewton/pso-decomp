# GiFoie orbit completion tracker

Owner: PSO recovery rank 8, task-37. The owned unit is
`src/pso/misc/TTecGiFoie.cpp`; the remaining function is
`TUnk_804CC800::run_task()` at **0x80230EA0**, originally **900 bytes**.
Ownership includes finishing exact matching, source linkage, review and acceptance.
A retained owner is not a claim that a worker process is continuously executing.

## Checkpoint chain

| Checkpoint | State |
| --- | --- |
| [Original WIP c66522fd](https://github.com/matthewlewisnewton/pso-decomp/commit/c66522fd75deda654e69f4bca54b04257a512b74) / [PR146](https://github.com/matthewlewisnewton/pso-decomp/pull/146) | Preserved, open draft; original implementation is unfinished. |
| [Native lifetime/vtable PR178](https://github.com/matthewlewisnewton/pso-decomp/pull/178), head `faf702cd14096119915547de4f8e3b1d419bc7c9` | Contains c66522fd by ancestry. Native TObject construction/destruction and 24-byte vtable repair; source checks pass. Frozen for scheduled development and independent review. |
| `codex/fork-gifoie-orbit-update` | Separate owned continuation descending from PR178. Remaining update recovery and this completion checklist live here; PR178 stays frozen. |
| Main `a3f15e8dfcd316496ce0db46a4f14e7ff5c0e71b` | At the verification for this tracker, contains neither checkpoint by ancestry, has no orbit-update definition, and does not list this unit as linked. |

This chain explicitly tracks c66522fd for completion. Neither a draft nor the
lifetime/vtable checkpoint completes the original recovery goal.

## Bounded lifetime/vtable repair gates

- [x] Preserve c66522fd and carry it into the native repair continuation.
- [x] Adopt the independently allocated native lifetime, constructor-name,
  vtable-name/range and conversion-bias localization changes on the private branch.
- [x] Compose the repair with its recorded main base without overwriting other
  workers' metadata hunks.
- [x] Preserve the nine existing functions in targeted comparisons; check all
  24 vtable bytes, alignment 8, and four relocation positions/types/targets/addends.
- [x] Publish draft PR178 and obtain source-checks PASS on its frozen head.
- [x] Stage separate frozen baseline/candidate roots and a concrete development
  request; parent confirms that validation is queued, without a slot release.
- [ ] Under scheduled preparation, regenerate actual split objects and the normal
  report with the adopted names and data range. Diagnostic symbol mapping is
  not the official report.
- [ ] Refresh localization/reference checks using all final original and compiled
  inputs; retain every adjacent data/code range.
- [ ] Pass scheduled isolated development, normal `check_pr`, DOL hash,
  original-address regression checks, ordered linker inputs and ELF checks.
  Keep this whole unit on fallback while the update differs.
- [ ] Obtain independent exact-head review, author readiness and parent queue
  acceptance for this bounded repair. Do not count it as completion of the unit.

## Remaining exact-update and source-link gates

- [ ] Recover a semantically sound native 900-byte update with exact instructions
  **and relocations**. Preserve FP/trig order, balanced matrix ownership,
  emitter lifetime, callback order and the established word/byte contracts.
- [ ] Preserve all nine previously exact functions at their original addresses.
- [ ] Verify all owned code/data, exports, function order and section alignment
  in actual regenerated objects/report. After PR178's range allocation, the
  owned data comprises the existing eight-byte bias and the 24-byte orbit vtable;
  neighboring tables/vtables keep their owners.
- [ ] Once independently eligible, select this unit from compiled source using
  the repository's normal link-unit workflow, preserving unrelated list/input order.
- [ ] Prove the real linker takes `src/pso/misc/TTecGiFoie.o`, pass the original
  DOL hash and normal loss checks, and distinguish this result from fallback
  DOL success.
- [ ] Complete independent review, author readiness, gated acceptance and a main
  merge receipt for the final exact/source-linked contribution.
- [ ] Reconcile the older drafts/checkpoints only after their contents and the
  original completion goal are accounted for; retain a final evidence receipt.

## Latest bounded update experiments

The frozen repair's update is still **892/900 bytes**, **98.26667% instruction
similarity**, with **zero new exact code gain and zero actual source-link gain**.
Current work targets the final constant-address/loop-zero initialization cluster.

This execution session ran 21 private GC/2.6 probes using the frozen native-repair
source context,
strict illegal-pragma diagnostics, unique output objects, and source/object/tool/
reference hashes. All compiled successfully and preserved the nine prior exact
functions in diagnostic name-mapped comparisons. None is adopted:

| Source/optimizer hypothesis | Update bytes | Similarity |
| --- | ---: | ---: |
| Level 2 with strength reduction and loop invariants enabled | 892 | 95.48% |
| Level 1 with selected CSE/propagation/loop passes enabled | 936 | 87.27556% |
| Level 2 above, lifetime optimization disabled | 892 | 95.48% |
| Level 3, common-subexpression optimization disabled | 892 | 98.18667% |
| Separate processed-count and cursor induction variables | 892 | 97.888885% |
| Same counted cursor with alternate initializer/increment order | 892 | 97.835556% |
| One-based cursor with an inclusive bound (default/strict on/strict off) | 908 | 98.71555% |
| Zero-based cursor with an inclusive bound (three settings) | 896 | 97.77778% |
| Callback-compatible angle-word storage views (three variants) | 892 | 98.26667% |
| Typed unsigned byte cursor (three settings) | 896 | 97.37334% |
| In-class/explicit-inline virtual member emission (three variants) | 892 | 98.26667% |

The inline-member trials emitted the update as a weak out-of-line function; its
instruction body still had the same shortfall, and emission order also changed.
No trial produced an exact update or was adopted. The source in the update branch
therefore remains the frozen PR178 implementation.

These results exclude only the tested forms. Earlier native pre-increment code
reached 900 bytes and the original two-step factor-address load, but still differed
in induction state/registers. There is no impossibility or assembly-origin claim.
A follow-up session compared that reachable path against the normal pre-test
loop's zero coalescing, while leaving the repair checkpoint frozen.

## Follow-up: isolated compiler question

Six additional full-function probes compiled successfully with strict pragma
checking and preserved the nine prior exact functions in diagnostic comparisons:

| New hypothesis | Trials | Update bytes | Similarity |
| --- | ---: | ---: | ---: |
| Explicit borrowed scale/profile helper arguments, both orders and propagation default/off | 4 | 892 | 98.26667% |
| Scope-commit destructor executing the original emitter loop, pointer/reference captures | 2 | 908 | 94.44889% |

No source variant was adopted. Four borrowed-argument forms emitted exactly the
same candidate object as the frozen repair. Both scope-commit forms emitted the
same larger object as each other. All source/object/report hashes and empty
compiler logs were checked; no full build or preparation was run.

A self-contained three-source compiler reproducer now isolates the remaining
question without repository headers or game assets. Its flat zero-based loop is
200 bytes; changing only to pre-increment produces 208 bytes and restores the
separate scale-address addition/load, but initializes the induction values to
-1/-4. Explicit borrowed arguments produce 200 bytes and fold the address again.
A second compilation from the packaged runner reproduced all three object files
byte for byte. These sizes describe the diagnostic functions, not new matches.

The precise specialist question is how a defined C++ form can retain the original
zero-based pre-test traversal while keeping the scale-address temporary alive
across the profile-base register overwrite, and keeping the direction-field zero
separate from the two loop-initialization zeros. The source-only packet includes
fixed GC/2.6 options, source/tool/object hashes, callback and FP constraints, and
the exact residual original addresses. Raw reports and original disassembly stay
local. Parent routing of this question is the next concrete compiler handoff;
there is no impossibility or assembly-origin claim.

Task-37 retains implementation and source-link ownership. PR178 development
validation still awaits scheduler release. At the end of this bounded session no
compiler or full-build process is represented as running; expert follow-up and
scheduled validation are pending, and the original completion gates remain open.
