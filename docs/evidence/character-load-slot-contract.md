# Character-load slots and request ownership

This independent extraction is based on fork main
`5bba9c44adebc1cfa019def85e1f39f6da340ef0`, taking the character-load portion of
[PR #303 at `3ed9b21ae`](https://github.com/matthewlewisnewton/pso-decomp/tree/3ed9b21ae3d8b887e18642e3e561063fb1eb2c98).
It does not change the BML return contract or networking interfaces.

## Native interface evidence

The four request records in `request_model_loads` at `0x8028CD18` carry a signed
slot at +8, a completion mask at +0xC and a borrowed flags pointer at +0x10.
The `TChCrLoadGmNjReq` constructor at `0x8028C7BC` stores these at +0x24, +0x20
and +0x28 respectively. The request remains 0x78 bytes. Its name buffer is a
48-byte copy at +0x30, with no promise of NUL termination.

The request dispatcher at `0x8028C6EC` forwards its receiver to the starter at
`0x8028C650`, which forwards it to slot acquisition at `0x8028C8E0`. These two
methods belong to `TChCrLoadGmNjReq`. The state at +0x2C, claimed word at +0x6C
and lifetime at +0x70 now have matching fields and offset assertions. The parent
argument to base construction and receiver to queued destruction are explicit.
Completion retains release, flag masking and queued-destruction order. The flags
remain borrowed; no lifetime or synchronization guarantee is added.

At `0x8028D628`, r3 is a numeric slot and r4 a signed byte count, not a lobby
receiver. The zero-size wrapper at `0x8028D714` forwards that slot. Reset at
`0x8028D738` consumes only the slot, stores and returns an unsigned address word;
both callers ignore the return. Its old second argument was residual register
state. `CharacterLoadBuffer.h` shares these declarations and the two native
32-bit buffer-base words. The predicate at `0x8028D5D4` still produces zero or
one, with a shared `s32(void *)` contract and explicit receiver at its caller.
It does not establish a more specific predicate input type.

Keep the original signed slot/size tests, unsigned address arithmetic, rounding,
pre-check cursor advance and failure behavior. `TLobby__sub_8028D7D0` returns
void and does not enforce its bounds checks. Negative or otherwise invalid slots
are not made safe. Allocation sizes, null handling, fixed-size copying, completion
behavior and existing bugs are preserved. The small allocation/free wrappers
use the existing canonical `xmalloc`/`xfree` interfaces with explicit arguments.

## Fold and attribution

The adjacent already-linked ranges `8028D5D4–8028D714` and
`8028D714–8028D8B8` become one source unit sharing the two actual cursor arrays.
This removes the second fragment's incompatible first-element structure views.
The surviving filename is inherited; the grouping does not establish the
historical translation-unit boundary or a class owner for the free helpers.

The fold derives from [4f2f4f597](https://github.com/matthewlewisnewton/pso-decomp/commit/4f2f4f59756621fdfc560f386f346ad40e0c59f0),
by Matthew Lewis Newton with Cursor coauthorship. The interface work derives
from Codex commits `6c59fae67`, `8a4b57975`, `b68b6afb9`, `a32c3fcf8` and
`063f1fe55` in that preserved history. No original game bytes or build products
are included.

## Validation against current main

The coordinated native build reproduces the original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`; address-based `check_pr.py` passes.
Matched functions remain 27,440, matched code 4,238,432 bytes and matched data
1,477,407 bytes. Linked code/data remain 3,874,412/1,354,403 bytes. There is no
new function, byte or linked-address coverage claim. Four export names change;
one already-linked fragment disappears through the fold.

All nine affected compiled units are exact and source-selected. Of 3,631 active
compiled objects, 3,626 are raw-identical to authenticated main. Four differ
only in the four listed export renames, checked across complete ELF sections,
metadata, symbols and relocations. The folded object's 740-byte text and
compiler function metadata concatenate the two main objects exactly; its
48-byte BSS is unchanged. All symbol locations and relocations reconcile, and
its complete allocated sections and relocation records equal the fresh original
split. Compiler comment/string-table changes from the fold are not hidden.

The actual ordered linker inputs equal main minus the removed source fragment:
3,607 source providers and 1,338 unchanged original fallbacks. Fresh generated
retention adds only `TLobby__sub_8028D7D0`, `lbl_80518850` and
`chr_select_load_buffer_table`, now referenced within the same object, with no
removals. All 18,605 retention entries pass. Python syntax, 306 synthetic tool
tests, existing portable behavior and ASan/UBSan suites, 32-bit header/layout
checks and exception inventory checks pass. No compiler setting or pragma is added; the generated
inventory changes only one existing intrinsic's line number.

The #437 refresh preserves reviewed head `a84a5d3f1778cd81c571730a66f0ce78a8877a95`
in history and integrates the pinned main without changing any character-load source.
The main-only recovery gains belong to the integrated changes, not this extraction.
Existing portable suites are not new character-load runtime characterization and
do not establish 64-bit safety.
