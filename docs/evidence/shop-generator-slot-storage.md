# Shop generator slot storage

Initially based on fork main `f1227326c4b7deaa4c33186978ad623862b590d5`;
refreshed and revalidated against `f9b6cf76d9171b3dce5082b1484a85f4579855cd`
after the ending-controller work merged.

`TShopGenerator__slot_active_table` owns the 16 bytes at
`.bss 0x80513ED0–0x80513EE0`. Both service-dispatch reset routines explicitly
clear four signed words; the setter and clearer store 1 and 0 using a `u16`
slot index. The predicate compares the selected word with 1. These accesses
support an ordinary `s32[4]`, replacing the former word-plus-byte-tail wrapper.
The original symbol is exactly 16 bytes, with no unknown tail or source padding.

A fresh census of all 5,064 active original objects finds ten HA/LO references,
all in `TShopGenerator.cpp`, and no unresolved BSS relocation targets. The
original object for the new range and the compiler object both use alignment 8.
The unit already links from source; this change adds the array's BSS split.

The predicate's old byte offset `(helper(arg0) * 4) & 0x3FFFC` selects the low
16 bits of the helper result. Ordinary indexing with an explicit `u16` conversion
preserves that truncation, including the native rotate/mask instruction.
`TShopGenerator__sub_80222DAC` returns the supplied index in split-screen mode,
otherwise zero. Existing medical-center code uses the same indexed-array form.
The change preserves the existing caller-domain requirement; it adds no bounds
check or new optimizer setting.

## Validation

The full native build reproduces DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. `check_pr.py --no-build`, strict
original-address no-loss checks (including padding), actual source-link inputs,
and both port-exception inventory checks pass against the freshly built base.
All existing code bytes and resolved code relocation targets remain identical.
Matched and source-linked data each increase by 16 bytes; function/code counts
and all coverage denominators are unchanged. Retention adds the array name,
removes no names, and sorts three existing bone-rotation entries.

## Deferred adjacent work

The neighboring gear, equipment and technique-shop arrays at
`0x80513EB0–0x80513ED0` and `0x80513EE0–0x80513EF0` are another 48 bytes.
Their reset loops and stores support four-word arrays, but their owners are
being changed by PR #562. Wait for that work before recovering their storage.
Their getter-local `int[]` declarations must also be reconciled with the proposed
`s32[4]` definitions in their owners (`s32` is `signed long`), using shared
C-linkage headers.

The separate fog-instance table remains deferred: its constructor stores
through a pointer-array view while consumers use signed integer words and
multiple recovered class views. A complete pointer contract is needed before
assigning real storage; matching a new integer array alone would not resolve it.
