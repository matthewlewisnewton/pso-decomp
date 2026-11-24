# PR #295 survey: quest-download pagination and the slot word

## Scope

Surveyed on 2026-11-05 for
[PR #295](https://github.com/matthewlewisnewton/pso-decomp/pull/295).
This is a source and history survey, not a match attempt. No C/C++ in the
quest-download unit was edited here.

The survey started at `c23caa9f0` (Sol round six). Before this note was
written, the matching worker pushed `73cf385bb` ("Match the first page-fit
expansion with the file's inline helper"). The mismatch section below is that
commit, checked against the original split object and against the clean
`wave2-pr295` build of that same commit (worktree clean, report and object
newer than the commit). Scores from earlier commits are labeled as history.

Compiler for every score in this note: GC/1.2.5, `-O4,p -inline off`, unit
`src/pso/misc/TQuestVmDownLoadServer_803E6970.cpp`. "Report" means
`report.json`. The unit stays unlinked. Project totals on the live head's
report are still 4,164,972 matched code bytes and 27,339 matched functions:
the latest pagination edit did not add an exact function.

## What is stuck

Two separate problems are being conflated in the attempt log.

1. `TQuestVmDownLoadServer__sub_803EC284` (`0x803EC284`, 476 bytes) is a real
   page fit. On `73cf385bb` the first measurement and the group advance match
   the original instruction stream, including `head`/`mode`/`index` in
   `r31`/`r30`/`r29` and the fit count in `r4`. What remains is the second
   measurement's register coloring and an 8-byte stack frame the body never
   touches (`stwu -56` / `stmw r25,28` against `stwu -64` / `stmw r25,36`).
   Report score **98.94958%**.
2. `TQuestVmDownLoadServer__sub_803E9A74` (`0x803E9A74`, 876 bytes) is
   undefined on this head. The original slot word at offset 0 is a pointer
   that also holds the all-bits-one failure value. Matt rejected every
   spelling of that value. The exact reset and `init_entries` on this head
   still compile main's inherited `(void *)-1` stores. Replacing those with
   null is a measured regression, not an untried idea.

`sub_803F03B4` (report 86.73494%, 328/332 bytes, `mulli`/`clrlwi` order) is a
third, unrelated leftover. It is not the pagination residual.

## Sources

- PR comments on #295 through Sol round six (`c23caa9f0`).
- `pilot-logs/attempts/pr295-ds1017-attempts.md`,
  `pilot-logs/attempts/pr295-grok-attempts.md` (through the wave-19 section,
  which is the measurement behind `73cf385bb`).
- `docs/evidence/quest-download-pr295-sol-r5.md`,
  `docs/evidence/quest-download-pr295-sol-r6.md`.
- `wave16-gpt-pr295/gpt-task/results.md` and
  `wave16-gpt-pr295/docs/evidence/quest-download-slot-representation.md`
  (local Sol rounds; not the PR head).
- `pilot-logs/wave16-review2/findings/pr295.txt`.
- Original split object
  `build/GPOE8P/obj/pso/misc/TQuestVmDownLoadServer_803E6970.o`
  (symbols `sub_803EC284` at `0x5914`, `sub_803E9A74` at `0x3104`,
  `sub_803EADD4` at `0x4464`, `init_entries` at `0x4580`).
- In-repo notes: `docs/evidence/chr-select-slot-clamp-inline.md`,
  `docs/evidence/cast-technique-6x47-register-allocation.md`,
  `docs/evidence/tboss2-derolle-register-allocation.md`.

## Compact history

Exactness was reached twice, then given up because the source that produced
it was rejected. Later rounds have been trading score for a source Matt can
keep. The live head is one of those later rounds, not a new algorithm.

| Head / note | `sub_803EC284` | `sub_803E9A74` | Why it stopped |
|---|---:|---:|---|
| `65c9049d4` | 100% (476/476), frame `-64` | 100% (876/876) | `#pragma opt_propagation off` on the search. Fresh pointer matched the first page only (94.4%). |
| `e4124eb98`, pragmas removed | 96.93277% (480 vs 476) | 98.173515% (880 vs 876) | Parked. Token load went through `r3`; page frame shrank. |
| `5cdb83815` (ds1017) | 100% via `PaginationFitCursor` + depth-2 helpers | 100% via assignment-in-condition, no `slot` local | Helpers are not inlined under `-inline off` without the region (fit 37.5%, search helpers 99.34% pragma-free). Macros 93.6%. Local-class methods 38.5%. `__inline` / `__forceinline` not honored. 208 declaration permutations of the search stayed ≤ 99.77%. |
| `205e2be6b` | 100%, own `inline_depth(2)` region kept | 100%, switches written in the function, pragma region deleted | Handwritten fit with the same opcodes: 97.605%, frame `-48`, `head` in `r25` not `r31`. |
| `8b17b56c1` | 100% inside the depth-1 region main already opens | 100% | `-inline on,noauto,level=2` also makes the fit exact and shrinks exact `sub_803EA1A8` from frame `-48` to `-40` (100% → 99.958%). Rejected as a unit profile. |
| `b6d169d47` | 100% | 100% with `(T *)-1` | Bare `return -1` does not compile. `== -1` on an `s32` emits `cmpwi`, not `addis`/`cmplwi`. |
| `34269603c` | 100% | 100% via `null - 1` and an empty base | Review rejected null-pointer arithmetic and a base added only so the cast would fold. |
| `a6f988f4b` | 98.655%, frame `-56`, second fit rotated | 100% with one named `(T *)-1` | Cursor wrapper and `mode = count` removed. Sentinel marked proposed, not approved. |
| `7d819bbb5` | 98.655%, same frame | undefined | Matt rejected the sentinel. Writers restored to main's `(void *)-1`. |
| `200eb5b59` | **99.958%**. Both expansions match; only `stwu -56` / `stmw r25,28` differ | undefined | Second helper declared in the opposite order so the second site colors forward. Frame did not grow. Caller-side cursor still rejected. |
| `4b8d5de23` / `f9264353b` (Sol r5) | 97.22689%, frame `-48`, direct scalar, mode and count separate | undefined | Steering removed on purpose. Scalar helpers at unit `-inline on`/`noauto` score 99.663864% and again shrink `sub_803EA1A8`. |
| `c23caa9f0` (Sol r6) | 97.31092%, still frame `-48`. Mode/index/head were `r31`/`r30`/`r29` against the target `r30`/`r29`/`r31`; count in `r0` | undefined | 66 full-unit shapes. Best unretained copy of the inputs was 97.52101%. None recovered frame `-64`. |
| `73cf385bb` (live) | **98.94958%**, frame `-56`. First fit and advance match; second fit rotated | undefined | Puts the fit back in the existing depth-1 region and writes the count through the saved mode parameter. Does not restore the 99.958% second helper. |

Whole-unit flags measured on this source family and rejected, because each
one drops at least one function that is already exact (`sub_803EA1A8` is the
usual victim; `-inline auto` / `deferred` drop dozens, worst to 0):

`-inline on`, `-inline noauto`, `-inline on,noauto,level=2`, `-inline level=2`,
`-inline auto`, `-inline deferred`, `-inline on,deferred`, `-inline auto,deferred`,
`-inline off,deferred`, `-inline all`, `-fp_contract on` (last one is a no-op
on the object).

Null-only slot stores, measured on the local Sol tree rather than on the live
PR head: `sub_803EADD4` **97.704544%** (180 vs 176 bytes), `init_entries`
**96.29508%**, search **90.76712%**. Four exact functions regress (2,016
bytes). That candidate was not kept. The live PR never took those null stores;
reset and `init_entries` are still report 100% (176 and 488 bytes).

## Current pagination mismatch

Original and live body are the same length. The prologue through the first
measurement and the advance loop compare equal, instruction for instruction.
The split is the second measurement, then every frame immediate.

| Role | Original `0x803EC284` | Live `73cf385bb` |
|---|---|---|
| Frame | `stwu r1,-64`; `stmw r25,36(r1)`; epilogue `lmw r25,36` / `lwz r0,68` / `addi r1,r1,64` | `stwu r1,-56`; `stmw r25,28`; epilogue offsets 28 / 60 / 56 |
| Mode | `r30` (`addi r30,r4,0`) | `r30` |
| Index | `r29` | `r29` |
| Head (`textHead`) | `r31` | `r31` |
| First fit node / n / total / limit | `r25` / `r26` / `r27` / `r28`, then `mr r4,r26` | same |
| Advance | `mtctr r4`; `subf r29,r4,r29`; copy head to `r3`; walk `r3`; `lwz r31,16(r3)`; `bdnz` | same |
| Second fit node / total / limit / n | `r25` / `r27` / `r26` / `r28`, then `mr. r4,r28` | `r28` / `r26` / `r25` / `r27`, then `mr. r4,r27` |
| Empty page | `li r3,0`; `li r4,0`; `bl` self | same |

The second site is not a different schedule. It is the same compare, the same
`+ 3`, the same `flags & 1` walk, and the same "zero means one group" fixup,
colored from the other end of the callee-saved range. Relative to the first
site, the original swaps only `n` and `limit` (`r26`/`r28` become `r28`/`r26`)
and leaves `node`/`total` in `r25`/`r27`. The live second site assigns
declaration order forward from `r28`: `node`, `n`, `total`, `limit` land in
`r28`, `r27`, `r26`, `r25`.

That matches the allocator behavior already measured at `200eb5b59`: the first
inline of this helper is colored in reverse declaration order, the next inline
in forward order. Reversing the second helper's declarations made that forward
coloring land on the original registers and produced 99.958%. The eight bytes
between offset 28 and offset 36 were still never loaded or stored. The live
commit deliberately did not restore that second declaration order.

The extra 8 bytes have shown up only when the inliner reserved a home it did
not later use:

- Handwritten loops, no helper: frame `-48` (`stmw` at 20). Same opcodes can
  be forced; `head` falls out of `r31`.
- One inline expansion in the depth-1 region (live, and the 98.655% single
  helper): frame `-56`.
- Two declaration-order helpers, still one nesting level: frame stays `-56`
  (the 99.958% result).
- The rejected `PaginationFitCursor` plus a nested walk, inside a depth-1 or
  depth-2 region: frame `-64`, and with the `r3` copy on the advance, 100%.

`sub_803EB208` in this same file is the control. Its `count_fitting_groups` /
`advance_entry_groups` are the same measurement and the same flag walk, one
expansion each, and that function is report 100% (288/288). Moving
`sub_803EC284` into their region and calling them scored 94.412%: the helper
inlines, but the caller's count handoff does not allocate like the cursor
fit. One expansion is a solved shape. The second expansion is the unsolved one.

Calls that stay real `bl`s on both sides: `sub_803EC09C`, `get_buffer_size`,
`sub_803EB7C0`, the recursive `sub_803EC284(0, 0)`, and `sub_803EB4D4`. The
original is not auto-inlining those.

## Slot word, reset, and search

Disassembly of the original, not the attempt notes:

- `sub_803EADD4` at `0x803EADF0`: `li r0,-1`; `stw r0,0(r31)`; `stb r0,24(r31)`.
  The same register initializes the pointer word and the length byte, which
  is why the byte is `0xFF`. `items` is then tested with `addis`/`cmplwi`
  against `0xFFFF` and cleared to null. `entryHead` gets the same all-ones
  test; `textHead` is only tested against null.
- `init_entries` writes `r5 = -1` to slot+0 and to the three trailing bytes,
  and writes a zero register to the other pointer fields. Eighty slots, stride
  `0x1C`, counted with `divwu`.
- `sub_803E9A74` loads slot+0 into `r20` (`0x803E9ACC` in the linked DOL;
  object offset `0x315c`). It tests all-ones with `addis r0,r20,1` /
  `cmplwi r0,65535` and returns `li r3,-1`. It then tests null with
  `cmplwi r20,0`. The early `pos >= end` path returns null when a global mode
  is below 3, and `li r3,-1` when that mode is at least 3. Those are different
  results.

The producer is still unrecovered `sub_803EA9E8`. At `0x803EAA54` it tests the
dictionary routine's all-ones return and leaves the slot alone. Otherwise
`0x803EAA6C` is `stw r3,0(slot)` of the record pointer just returned, and the
length goes to slot+0x18 only on that path. Search then `lbz`s through the
loaded word and subtracts a signed 4-byte stride from it. There is no table
base added in between. An integer index, a handle, or a status field next to
the pointer would be a different ABI: the successful value is the address, and
the failure value occupies the same register the address would.

Local Sol round four's null model collapses those two results. That is why
search falls to 90.76712% and the two writers lose exactness, not because a
declaration was unlucky. The live head's exact writers are exact because they
still contain main's `(void *)-1`. That is an inherited blocker. It is not an
approval, and this survey does not propose putting it back under another name
(`(T *)-1`, `null - 1`, empty base, `reinterpret_cast<u32> == 0xFFFFFFFF`, or
an `s32` compared with `cmpwi`).

Leaving `sub_803E9A74` undefined is the honest current state. No cast-free
pointer return names the constant `-1`, and GC/1.2.5 rejects a bare integer
return into `QuestDownloadSegment *`.

## Precedents

### Same file, strong

`count_fitting_groups` and `advance_entry_groups`, used by exact
`sub_803EB208`, are the same page arithmetic: reserve 9 bytes, add
`sub_803EB7C0(node) + 3`, cap at 9 groups, force one group when the first
does not fit, walk `flags & 1`. They show that one inline expansion of this
loop matches under the file's existing depth-1 region. They do not show how a
second expansion of that same helper keeps `node` in `r25` while swapping
`n` and `limit`.

### Same repo, useful but not this compiler

`docs/evidence/chr-select-slot-clamp-inline.md` (PR #294, GC/2.6, `-inline on`)
is the closest local explanation of why an inline changes coloring: MWCC
numbers arguments, then named locals, then `@` temporaries, and an inlined
helper's locals become `@` temps before the later passes. The out-of-line
clamp was 99.15% and the inline was exact. Applying that here as a unit
`-inline on` is already measured and regresses `sub_803EA1A8`. The note is
evidence about virtual-register order, not a flag to copy onto a GC/1.2.5
`-inline off` unit.

`docs/evidence/cast-technique-6x47-register-allocation.md` (also GC/2.6) shows
a copy between two named locals surviving when coalescing does not join them.
That is why `mr r4,r26` needs the count to be a value the parameter can hold
after mode has been saved. The live head already does that. Another temporary
will not invent the missing frame slot.

`docs/evidence/tboss2-derolle-register-allocation.md` is a different residue:
the original saves fewer callee-saved registers because a counter reuses a
dead object pointer. Here both sides save `r25`–`r31`. The permutation is
inside the second loop, and the frame delta is unused space, not a missing
`stmw` register.

### Public compiler notes, on point for the frame

[cadmic/mwcc-debugger `README.md` at `1fa61bc3`](https://github.com/cadmic/mwcc-debugger/blob/1fa61bc3d21263009b4f794021e59e7b265182b8/README.md)
documents GC/1.0–1.2.5 stack allocation in this order: 8 bytes for the
callee's `r0`/`r1` save if the function makes a call, outgoing stack
arguments, homes for this function's arguments whether or not they got
registers, locals and frontend temps that were not given a register before
regalloc, regalloc spills, then backend temps. It also says these versions do
not reclaim a slot whose local was optimized out or never assigned a register.
That is the mechanism that fits the measured `-48` / `-56` / `-64` ladder: each
inlined helper can contribute a home the body never reads. The debugger itself
only dumps `variables.txt` for GC/1.1. A GC/1.2.5 trace of this unit already
failed to attach, so a GC/1.1 dump would be a hint about names, not proof.

[stephenjayakar/melee-mwcc-register-skill at `9c1b058a`](https://github.com/stephenjayakar/melee-mwcc-register-skill/blob/9c1b058a3181d9cbe541fff7cdb01d836e4dfce3/SKILL.md)
reconstructs GC/1.2.5n coloring: ascending virtual ids are simplified onto a
stack, so they color in reverse, and call-crossing values fall back through
`r31` downward. That agrees with the first fit coloring in reverse declaration
order and with `head` taking `r31`. It is a model of another project's
compiler build, not a trace of this object, and it does not by itself explain
why the second inline flips to forward order. The flip is an observed fact of
this unit (`200eb5b59`), not something the skill proves.

No public GameCube decomp surveyed for this note has this quest-download page
fit, or a source idiom that reserves an unused 8-byte home without an inlined
local the compiler decided to keep. Copying another project's pagination would
not be evidence.

## Experiments worth one compile, and the ones to stop

Do not restore a sentinel, a cursor wrapper, a fake base, padding, an
int/pointer pun, a unit inline flag, or `opt_*` / `scheduling` pragmas. Do not
permute the four fit locals again: twenty-four orders of one shared scope left
the second `node` in `r27` whenever the first `node` was `r25`, and separate
`n2`/`node2` locals pulled `head` back out of `r31`.

### 1. Name the missing slot, once

Hypothesis: the 8 bytes are the GC/1.2.5 argument/local home of one inlined
parameter or frontend temp, retained after the value stayed in a register.
The mwcc-debugger layout is the reason to believe the slot has a name.

Change: no source change. Run the existing GC/1.1 variable dump on the live
`sub_803EC284` only, and compare it with a dump of exact `sub_803EB208`.

Confirms if the fit function has one home `sub_803EB208` does not, and that
home's size is 8 (or 4 plus alignment). Refutes if the dump shows the same
homes and the frame delta is only a backend temp the dump does not name.
Either way, stop. Do not retune the source from a GC/1.1 name that the 1.2.5
binary cannot confirm. Previous attempt: a GC/1.1 trace of the old scalar
body, not of `73cf385bb`.

Risk: none to the unit if the dump is read-only. A failed attach is an
answer, not a prompt to switch compilers.

### 2. Nested continuation walk, still at depth 1

Hypothesis: the historical `-64` frame appeared when the `flags & 1` walk was
its own inline inside the fit, contributing the home in experiment 1, not
when a one-pointer struct existed. `Next_803EB328` in this file is already
that walk.

Change: call that existing inline (or a file-local equivalent with the same
body) from `count_text_groups_that_fit` and from `advance_text_groups`. Do
not add a struct. Do not give the second fit its own declaration order. Leave
`inline_depth(1)` where it is.

Confirms if the frame becomes `-64`, the body gains no stack store the
original lacks, and `sub_803EC460` stays 100%. Refutes if the call stays out
of line. A previous `pagination_step` at depth 1 stayed out of line and scored
92.521%; treat a repeat of that as a stop, not as a cue to add another
wrapper.

Risk: `sub_803EC460` and `Default_803EC460` share this region and are exact.
Any drop there rejects the edit even if pagination's frame grows.

### 3. One depth step, only if experiment 2 stays out of line

Hypothesis: depth 1 cannot see a nested inline, and the old 100% result used
depth 2 for exactly that nest. Raising the existing region's depth from 1 to
2, with the nest from experiment 2 and without a cursor, is the unmeasured
combination. The old depth-2 region wrapped the cursor helpers; this would
wrap the helpers that are already honest.

Confirms on the same criteria as experiment 2, plus no other function in the
region changing its frame. Refutes if `sub_803EC460` loses the 8 bytes it
already matches, which is the failure mode `-inline on` has against
`sub_803EA1A8`.

Risk: high, and one compile is the budget. Do not walk depth through 3, 4,
and `auto` afterward. Those profiles are already rejected.

### Not worth another round

- Restoring the 99.958% opposite declaration order. It fixes the second site's
  registers and has already been shown not to grow the frame. Combining it
  with experiment 2 would be declaration-order steering of two copies of one
  function. Record it only if experiment 2 has already produced a real home
  and the coloring is the only delta left; do not start there.
- Sol r5/r6 control-flow batches: `for` headers, remaining-byte budgets,
  post-tested scans, list-link walks, shared scan state, unsigned counts,
  mode switches. The retained band was 97.23–97.52% with frame `-48`. The
  live head already beats that on registers. Repeating the batches will not
  create a stack home.
- Any new model of slot+0. The producer store, the search dereference, and
  the reset `li`/`stw` agree. Portable null is the measured 90.76712% /
  97.704544% / 96.29508% regression. An explicit status beside the pointer
  adds a store the exact reset does not have.

This is not a proof that no honest source is exact. It is a proof that the
remaining pagination bytes are an unused frame slot plus one reversed coloring
of a second inline, and that the search's missing constant is the rejected
pointer value rather than an undiscovered field.
