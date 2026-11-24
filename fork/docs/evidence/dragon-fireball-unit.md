# Dragon fireball unit

Recovery base: fork `main` `12df54a1235a003cee3c4aa6d80fd5d386d8b160`.
The existing `pso/boss/TBoss1DragonEffBullet.cpp` unit owns five functions at
`0x8002B9CC..0x8002BD34` (872 bytes) and its compiler-generated 24-byte vtable.
The code already matched and linked; this recovery replaces its provisional
representations and brings the remaining 72 data bytes into source.

## Class and caller evidence

The constructor at `0x8002BC30` copies two Vec arguments to +0x1C/+0x28,
subtracts the first from the second, normalizes that direction, and stores the
returned target distance at +0x40. The update at `0x8002B9D0` advances traveled
distance (+0x3C) by 25, clamps the last movement step, and updates both emitter
positions. State +0x38 selects flight, impact, and delayed destruction. The
signed counter +0x34 counts impact updates and the subsequent destruction wait.
The two pointers at +0x44/+0x48 are particle controllers; both are queued for
destruction on impact and in the destructor. The second pointer's distinct
purpose is unresolved, so it remains `secondary_emitter`.

The class now declares these members directly, with size and offset assertions.
A native constructor replaces the free constructor and manual vtable store.
All four creation sites in the Dragon unit use ordinary `new`, retaining the
original allocation/null-check/constructor instructions. Their local destination
vectors use the shared Vec. The Dragon's embedded parent and model-vector
storage remain existing provisional boundaries; this change does not recover
that larger class's full layout. The impact call retains its existing signed
address-word parameter and the Dragon instance accessor its existing integer
carrier; neither interface is reinterpreted here.

## Compile, compare, research, and refine

The first typed reconstruction matches the render, update, destructor, and
constructor exactly. The selector is 94.7619%: the shared `bool isV2Mode()`
declaration adds `clrlwi r0,r3,24` before its signed switch comparisons. The
[main-phase predicate case](main-phase-predicate-evidence.md) documents the same
full-register return boundary. Changing the declaration and definition to `s32`
fixes the selector, but directly returning the Boolean comparison moves a byte
mask into the predicate, leaving that function at 89.5%. Explicit integer
normalization (`condition ? 1 : 0`), also used by the repository's subcommand
validators, preserves the predicate's original `subic`/`subfe` sequence. Both
units then have all functions exact. No new compiler control is needed.

The original update uses fused multiply-adds for its three movement components.
Its existing scoped `fp_contract on` is retained. The compiler-generated vtable
and definition order remain native; no assembly or manual table is introduced.

## Data ownership and padding

The selector refers to the two three-word particle-ID tables at
`0x80435410..0x80435428`; the name pointer at `0x805D2670` refers to the
`TBoss1DragonEffBullet` string at `0x80435428`. The update and selector share
`dragon_fireball_particle_ids` at `0x805D4B48`. The constructor and update own
the zero/25 float pool at `0x805D8140..0x805D8148`.

The [Gcrna storage case](gcrna-static-storage.md) explains pointer symbol extents
that included following alignment padding. Both fireball pointers have their
extents corrected from eight to four bytes, without fabricated extra members.
Their split ranges retain eight bytes each. The 48-byte rodata range contains
46 emitted bytes and two zero alignment bytes. The compiled sbss/sdata ranges
contain four bytes each and have four-byte zero tails. All section alignments
and 43 resolved relocations agree with the original object. The repository
scanner accepts these terminal alignment tails; the linked DOL confirms layout.

The two float exports are localized using `localize_split_globals.py` only after
its fresh active original/compiled inventory finds no external references.
Regenerated retention adds five definitions and removes none. The linked-unit
list is unchanged because this code unit was already source-linked.

## Validation

A clean baseline and the complete candidate rebuild produce original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. `check_pr.py` passes: no exact
function, matched code, linked unit, or non-padding address coverage is lost.
All five functions (872 code bytes) and all 96 owned data bytes are exact and
source-linked. Matched and linked data each gain 72 bytes. All 3,622 linked
units remain exact; generated retention is current.

The report denominator loses four zero padding bytes at `.sbss 0x805D4B44`:
claiming the following pointer range leaves that alignment-only automatic gap
outside the generated objects. `report_delta.py` identifies and permits this
padding loss; there is no symbol or live storage in it, and the final DOL is
unchanged. The body and other Dragon caller functions remain exact.

Raw objects, disassembly, compiler probes, and build reports stay local.
