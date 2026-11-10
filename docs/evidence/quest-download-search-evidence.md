# Quest-download segment search

`TQuestVmDownLoadServer__sub_803E9A74` (`0x803E9A74`, 876 bytes) is the quest
download segment search: it scans one slot's four-byte match-token chain for
segments covering `[beg, end)`, building the result list head-first in the
matching pass and recursing through the token displacements in the second
pass. PR #295 left it undefined. This change defines it and the search is
now byte-identical: objdiff 876/876, **100%**.

| Measurement | PR #295 final | This change |
|---|---:|---:|
| `sub_803E9A74` | undefined | **100%** (876/876) |
| `sub_803E9FFC` (caller) | 100% | 100% |
| `sub_803EA1A8` (caller) | 100% | 100% |
| `sub_803EC284` | 100% | 100% |
| `sub_803F03B4` | 99.75903% | 99.75903% |
| Unit exact code | 31512/41696 | **32388/41696** |
| Unit exact functions | 158/173 | **159/173** |

## Search body

The two passes walk `quest_download_slot_chain_table[beg].tokens` backwards
by each token's signed link count (`t -= (s8)t->d`, exit when zero), the
first matching `is_valid_item_for_slot(t->a, t->b)` and, when the requested
item is set, `sub_803E7390(a, b, t->a)`; `lbl_8047F0F8` maps the token's
displacement byte to a download-buffer offset. A matching token whose
`lbl_805A0470.bytes[beg + off]` passes the inlined `IsX_803E9FFC` class is
skipped; otherwise a `QuestDownloadSegment` is taken from `sub_803ECF0C`
and prepended. The second pass recurses with
`sub_803E9A74(beg + off, end, t->a, t->b)`, fixes each returned segment's
`off` and `reserved_2` pair by the token, appends the accumulated list at
the recursion result's tail, and adopts its head. The empty-slot first-fill
allocates one segment (`off = 1`, `a = 0xFF`, `b = 0`) when the byte at
`beg` passes the name class below.

The recovered name class is a sparse ten-case switch (`0x20, 0x21, 0x2C,
0x2E, 0x3A, 0x3B, 0x3F, 0x98, 0x9B, 0x9C`) behind an explicit
`c >= 0xA0` early return.
The `cmpwi 0x2D; beq → return 0` in the original is the switch lowering's
binary-search split between the `0x2C` and `0x2E` cases, not a case; the
`cmplwi 0xA0` root cut matches the reconstructed range guard. This establishes
a matching source form, not the original source spelling. The early-return
form puts its `li 0` fallthrough in the original's place. `IsX_803E9FFC` inlines
into the first pass with its own local `jumptable_804FCA54` copy, exactly as
it does into `sub_803E9FFC` (`jumptable_804FCBB0`).

## Named sentinel word

The original returns `li r3, -1` from three search sites: the empty-range path
when `lbl_805D7888 >= 3`, the all-ones token-slot status, and propagated recursion
failure after freeing this frame's accumulated list through `sub_803ECE5C`.
The recovered caller chain tests that native 32-bit word before traversing a
returned list.

On 2026-11-10, Matt replied to the concrete sentinel question: “A macro with
that constant seems reasonable”. The recovery now gives the observed word one
name, shared only by the search and its two caller stages:

```c
#define QUEST_DOWNLOAD_LIST_SENTINEL_WORD 0xFFFFFFFFU
```

The current [typed-sentinel continuation](quest-download-typed-sentinels.md)
gives segment failure, entry failure, unavailable item input and unavailable
match tokens their own pointer-typed names. The search and both caller stages
compare pointers directly. The existing generator `void *` boundary remains,
with ordinary conversion of the typed entry-failure pointer on return.
All-ones `slot->items` still skips unavailable input, whereas an all-ones
generated result still propagates failure. The slot now consistently stores
its token pointer, including its named unavailable value, instead of writing
an integer union arm and later reading a pointer arm. Result/item macros remain
local to the cluster; the token name is shared with reset and initialization.
Unrelated ID sentinels and integer status returns remain outside this change.

| Value | Preserved native meaning |
|---|---|
| `0xFFFFFFFF` pointer/result word | Search/list failure, or unavailable slot input as described above |
| `NULL` | Empty result or allocation exhaustion; these remain indistinguishable |
| Other returned pointer | List whose nodes may be traversed and released |

Matt's reply resolves the earlier requested decision about using a named macro
for this observed constant. It does not establish the original source spelling,
a portable integer-to-pointer representation, or approval of unrelated pointer
casts. These conversions intentionally preserve the existing 32-bit PPC ABI.
Ownership, shared-storage, unchecked-input and lifecycle/reachability limitations
remain unchanged, and the unit remains incomplete and unlinked.

Historically, the 2026-11-04 pointer-sentinel family was rejected. The initial
recovery used `QUEST_DOWNLOAD_SEGMENT_SCAN_FAILED` as a typed `(T *)-1` macro
while that decision remained pending. Matching output alone did not resolve it;
the present change follows Matt's later macro direction and uses the explicit
unsigned word consistently through the caller chain.

The earlier named-word checkpoint preserved the complete provider object byte-for-byte
(SHA-256 `22752cb218bdba3d7392a4506abdf15e494734223c38622c9e902ecab5885230`)
and the complete frontend object. The typed continuation preserves allocated
bytes and relocation targets, with compiler anonymous names renumbered only.
All 168 compiled provider bodies, 16 frontend
bodies, allocated data/layout/relocations and all 173 provider report entries
are unchanged. The search remains 876/876, its wrapper 428/428 and its downstream
consumer 476/476, all 100%. Native contract review verifies the three failure
returns, cleanup before recursive propagation, null allocation results and the
consumer's separate integer failure path. Full native build, no-loss comparisons,
exception-register check and independent exact-head review accompany publication.
No new runtime execution or matching/linkage gain is claimed for a spelling-only
change. The unit remains 159/173 exact, five undefined and nine partial, unlinked.

## Register allocation findings

CodeWarrior 1.2.5's allocator made the recovery depend on several source
shapes, each verified by rebuild:

- `t = slot->tokens; if (t == ...)` loads into a scratch temp and copies
  into the walker's home (`lwz r3; addi r20, r3`) whenever the loaded
  pointer must survive a call. Assigning inside the condition
  (`if ((t = expr) == ...)`) binds the load directly to the walker's home.
- A local `slot` variable takes the pool register after the loop offset
  (`r22`), splitting from the original (`r21`). Spelling the slot
  expression inline and letting common-subexpression elimination hold it
  (`quest_download_slot_chain_table[beg]`, used again for the second
  pass's reload) reproduces the original's single `r21` address temp and
  the in-place phase-two reload `lwz r21, 0(r21)`.
- The segment fill stores `t->a` to both `seg->a` and `seg->reserved_2[0]`.
  Two `t->a` expressions reload between the byte stores (the `u8` store may
  alias the token), and reading `seg->a` back reloads too. The nested
  assignment `seg->reserved_2[0] = (seg->a = t->a)` loads once and stores
  twice with no extra value.
- `off` must be `s32` for the `(s16)` cast to emit its `extsh`; as `u8` the
  compiler elides the extension.
- The first-fill returns the allocation result through both paths
  (`if (seg != NULL) { fill } return seg;`), which lets the allocation-null
  branch jump straight to the epilogue with `r3` already zero, as in the
  original. An early `return NULL` instead materializes an extra
  `li r3, 0; b` stub.

## `sub_803F03B4` header

The entry merger remains 99.75903% objdiff (332/332 bytes). Its only
remaining differences are the four header words that color the length mask
`r9` and the name displacement `r10` instead of the original's `r10`/`r9`.
The recorded source-side probes over permutations of the four header statements,
association and cast spellings of both expressions, named temporaries,
declaration styles (`register`, declarations-first), and loop forms leave
the coloring unchanged; the tested compiler versions that recolor it
(1.1p1, 1.3+) break other exact functions in the unit. These negative probes
do not establish that no matching source exists under the pinned profile.

## Initial recovery validation

`ninja` rebuilds `PsoV3.dol` and the SHA-1 check passes.
`python3 tools/check_pr.py --no-build` against the freshly built baseline:
**PASS**, new exact functions 1 (`0x803E9A74`), regressions 0, matched code
31512 → 32388 (+876), linked units unchanged (3568 all exact).
`python3 tools/list_port_exceptions.py --check` passes with no new
exception.

## Native result contract and bounded follow-up

An original-object reference audit found two direct calls to the search:
the recursive call at `0x803E9D44` and the call in `sub_803E9FFC` at
`0x803EA030`. Both test all ones before traversing a returned list.

The three all-ones producers are distinct from allocation exhaustion:

- `beg >= end` returns all ones when `lbl_805D7888 >= 3`, and zero in the
  other mode.
- An all-ones slot word returns failure before token dereference or allocation.
- An all-ones recursive result first frees this frame's accumulated segment
  list, then propagates failure.

The allocator itself returns zero when its free list is empty. The first-fill
path returns that zero directly; a failed first-pass allocation skips that
node while retaining earlier results. A zero recursive result contributes
nothing. Thus zero does not distinguish an empty list from allocation
exhaustion, and it cannot replace the all-ones failure state without changing
the native behavior.

`sub_803E9FFC` propagates all ones before allocating entry nodes. Otherwise it
converts any returned segments, frees the entire original segment list even
if entry allocation stopped early, and may add an independent direct entry.
Its caller `sub_803EA1A8` clears existing slot entries and returns integer
zero on that failure. Its own fallback-entry allocation failure instead
returns integer `-1`; those function-specific contracts must not be conflated.

The native slot producer calls `find_longest_match_entry` at `0x803EAA50`,
rejects an all-ones result, and on success stores the length at slot+0x18
and the actual token pointer at slot+0. The slot word is not an index or a
length-based handle. These observations justify preserving three states;
they establish the representation contract, independently of Matt's later macro decision above.

Six private cast-free slot-check variants were compiled with the unchanged
GC/1.2.5 profile. They retained the other exact functions but reduced the
search to 99.06393–99.84018%. The clearer form classifies the existing integer
status arm before loading the token pointer; a comma expression that loads
the pointer first provides less semantic improvement. Two four-byte union
result variants also regressed the exact `sub_803E9FFC` caller: the factory
form scored 90.84475% for the search and 96.40187% for the caller; the
constructor form scored 91.87215% and 91.57944%. Neither is an adopted repair
or proof of a portable result representation. Those experiments did not resolve the then-pending spelling decision; the
later macro direction is recorded above. The tests are not an impossibility proof.

## Entry-merger live ranges

The four remaining `sub_803F03B4` words reflect different legal register reuse
at the header-to-loop transition:

| Value | Definition | Last header use | Original | Recovery |
| --- | --- | --- | --- | --- |
| Masked encoded length | +0x18 | +0x24 | r10 | r9 |
| Name displacement plus 3 | +0x1C | +0x28 | r9 | r10 |
| End pointer | +0x24 | Live through loop | r7 | r7 |
| Entry cursor | +0x28 | Live through loop | r10 | r10 |

The length and displacement temporaries overlap. The length dies before the
cursor definition, so its register can be reused as in the original. The
displacement's last use is also the cursor's definition, allowing the
coalescing chosen by the recovery. This describes the emitted live ranges;
it does not establish the compiler allocator's internal choice mechanism.

Nine targeted source-interface/data-flow probes retained the same four
differences at +0x18, +0x1C, +0x24 and +0x28, with no existing exact-function
regressions. These covered semantic length/cursor helpers, combined bounds
outputs, a cursor that first seeds the upper bound, and consistent reversal
of the duplicate-merge helper's parameters, alone and with the semantic
helpers. No probe was adopted. No pragma, dummy local, shared text-skip helper
change, compiler override or claim that matching source is impossible follows
from these negative results.

The separate input-record and partial DC20 continuation is documented in
[quest-download-input-records.md](quest-download-input-records.md). The unit
remains 159/173 exact and unlinked. DC20 remains 94.41237%; the separate
[cache-page rotation recovery](quest-download-cache-rotation.md) defines
`sub_803E95BC` at 90.330185% in the standard report (90.18868% in the
relocation-sensitive probe). The [lifecycle continuation](quest-download-cache-lifecycle.md)
defines the loader at 88.67273% standard / 88.09091% relocation-sensitive and
the initializer at 82.47771% / 57.057323%, both as partial source. The
[relocation continuation](quest-download-cache-relocation.md) defines `sub_803E8924`
at 98.10317%. The [replacement continuation](quest-download-cache-replacement.md)
defines `sub_803E8DA0` at 90.71134% in the standard report. The
[primary-page removal continuation](quest-download-primary-removal.md) defines
`sub_803EF208` at 95.303925%. The [byte-input consumer continuation](quest-download-byte-conversion.md)
defines `sub_803EDF64` at 62.267857% in the standard report (62.267857% in the
relocation-sensitive comparison), preserving the frontend producer lifetime hold.
Five functions remain undefined and nine are inexact, including `sub_803F03B4`.
