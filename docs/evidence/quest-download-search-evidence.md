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

## Sentinel spelling

The original returns `li r3, -1` from three sites: the empty-range path when
`lbl_805D7888 >= 3`, the all-ones slot status, and the propagated recursion
failure (which first frees the accumulated list through `sub_803ECE5C`).
A standalone probe confirmed `return ((T *)-1)` compiles to a bare
`li r3, -1` with no stack traffic, and the recovery spells it once as a
named constant used at the three failure returns:

```c
#define QUEST_DOWNLOAD_SEGMENT_SCAN_FAILED ((QuestDownloadSegment *)-1)
```

with `if ((t = quest_download_slot_chain_table[beg].tokens) ==
(QuestDownloadMatchToken *)-1)` for the slot status and the existing
`(u32)sub == 0xFFFFFFFFU` word test on the recursion result, the same
word-test its matched caller `sub_803E9FFC` already uses. This belongs to
the pointer-sentinel spelling family Matt rejected on 2026-11-04. The
concrete spelling above still requires his explicit sign-off. A matching
compiler result does not clear that decision: PR #366 must remain draft
until the gate is resolved. Leaving the search undefined remains an option
if this spelling is not approved.

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
