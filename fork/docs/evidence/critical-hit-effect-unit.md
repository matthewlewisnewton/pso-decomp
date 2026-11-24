# Critical-hit effect complete-unit recovery

The existing `TEffClitical` spelling is retained from the executable string at
`0x80438EA8`. The unit owns seven functions at `0x80082308..0x8008271C`.
Its renderer temporarily replaces an animated texture slot, draws the effect
model facing the camera, then restores the slot and material flags. The update
spawns particles 7, 11, 12 and 14 once; particle 12 starts 20 units below the
effect. Alpha approaches zero by 0.15, scale approaches (2,2,2) by 0.2, and
the texture frame cycles through 0..6. Reaching zero alpha queues destruction.

The allocation is 0x78 bytes: the shared 0x70-byte TEffect followed by the
32-bit texture frame and spawn state. The color and scale targets are ordinary
local aggregate initializers, reproducing the original seven word loads and
stores. This removes the old stack-byte overlays, integer type-punning and
scoped `opt_common_subs off` / `opt_propagation off`.

## Compile, compare, research, revise

The first typed reconstruction matched approximately 95% of the unit. The
constructor, destructor, factory and texture-slot helper already matched.
The renderer used small-data addressing for an incorrectly placed eight-byte
external texture-list descriptor; declaring its real `.data` placement restores
the independent absolute address. Removing extra aliases from the distance
helper restores native register allocation. An independently compiled C89
version of that helper also matches all 148 bytes. The production unit stays C++.

The update with named target aggregates scored 97.14737%. Separate assignment,
a grouped work record and reversed declarations scored 84.31579%, 80.642105%
and 97.53684%. Ordinary local initializers reproduce every instruction; the
remaining 99.42105% comparison differences were anonymous initializer relocations
until the unit claimed its original data ranges. The investigation follows the
local-initializer and constant-placement precedents in
[orbit particle recovery](orbit-particle-recovery.md),
[ballistic particle recovery](ballistic-particle-recovery.md) and
[window effect light recovery](window-effect-light-recovery-evidence.md). These
arrangements reproduce the emitted object; they do not prove original source spelling.

## Data and interfaces

The unit now owns `.rodata` `0x80438EA8..0x80438ED8`, `.data`
`0x8048E2E0..0x8048E300`, `.bss` `0x80500610..0x80500620`, `.sdata` `0x805D2900..0x805D2908`, and
`.sdata2` `0x805D93A8..0x805D93B8`. The class string precedes the color
and scale initializer records. `clitical_vec_b` is a 12-byte Vec; the following
four zero bytes align the next unit. Its old inferred 16-byte extent included
that padding. The renderer's single-entry texture list at `0x8048E2E0`
points to its scratch `GinjaTextureEntry` at `0x80500610`; neither has other
original consumers. Both are now source-owned. The scratch entry's old 16-byte
extent likewise included four alignment bytes after the 12-byte entry.
The eight-byte object at `0x805D93B0` retains its scalar 1.0
and trailing zero, with guarded small-read-only-data placement and a late
definition. The preceding `0x805D93A0` scalar belongs to the freeze-shell
reader and remains outside this unit. No vtable is written by hand.

The factory takes a position in r3, and has exactly one original external caller,
in `TObjPlayer_80011014.cpp`. A static `create(const Vec*)` and matching
constructor replace the old call on a cast position-as-effect receiver. The
caller uses a real Vec local. Addresses, extents, instructions and relocations
are preserved; the new signatures express the observed contract rather than
claim recovered historical declarations. The texture-slot helpers retain their
existing C linkage and bounded pointer/word interfaces.

## Validation

Against fork main `12df54a1235a003cee3c4aa6d80fd5d386d8b160`, all seven
functions (1,044 bytes) and all 120 owned data bytes match. The 44-byte
compiled rodata and 12-byte compiled BSS each have a four-byte zero alignment
tail in the original; the linker recreates both tails. All 62 allocated-section
relocations agree in offset, type and absolute target. The linker selects the
compiled effect object. The sole factory caller's unit remains 226/226 exact.

The unchanged-main baseline and final native builds reproduce DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. `tools/check_pr.py --no-build`
passes after the full build: zero address-based code/function/data/link losses,
all 3,622 linked units exact, and retention metadata consistent. Matched and
source-linked data increase by 96 bytes; matched code and function counts are
unchanged. This completes data ownership of a previously code-linked unit.
Repository source-tool tests (346), Python syntax, portable behavior and
ASan/UBSan checks pass, as do the exception inventory and changed-line whitespace.
