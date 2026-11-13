# Gol Dragon fireball unit

Recovery base: fork `main` `7ebf37b813`. The existing
`pso/boss/TBoss8DragonEffBullet.cpp` unit owns four functions at
`0x802FE0E0..0x802FE48C` (940 bytes) and its 24-byte compiler-generated vtable.
The functions already matched and linked, but the constructor and update used
raw field overlays, and their descriptors, class name and float pool were
outside the source-owned split.

## Layout and interfaces

The constructor copies the start position into +0x1C and the target into +0x28,
subtracts the position, normalizes the direction and saves the target distance
at +0x40. The update advances the traveled distance at +0x3C by 25 per frame,
clamps the final displacement, and moves each position component with a fused
multiply-add. The signed state at +0x38 selects flight, impact and delayed
destruction. The lifetime at +0x34 counts impact updates and the destruction
wait. The mode at +0x44 selects a particle descriptor; the 16-bit owner ID at
+0x48 is passed to `get_enemy_entity` on impact.

The two pointers at +0x4C/+0x50 are particle controllers, released on impact
and destruction. Mode 3 creates the second emitter with particle ID 0x204.
Its more specific role is unresolved, so it remains `secondary_emitter`.
The pointer at +0x54 selects a three-word trail/impact/burst descriptor.
The class declares all these fields with offset and size assertions.

All four creation sites in `TBoss8Dragon.cpp` now use ordinary `new` and the
native constructor, with shared `Vec` locals replacing the local vector stand-in.
Their allocation, null checks, argument order and caller
instructions remain exact. The larger Dragon's raw-vector and embedded-parent
views remain bounded preexisting interfaces. The impact helper retains its
existing integer address parameter; this unit does not recover that helper's
wider setup-instance contract.

## Compile, compare, research, refine

The first typed C++ reconstruction matched the render, update, destructor and
native constructor exactly against the original assembly. Replacing the former
constructor symbol with the compiler-generated C++ name also preserves all
four caller sites. The [Dragon 1 fireball](dragon-fireball-unit.md) supplied a
close comparison for the movement, particle and lifecycle representation.

Defining the three particle descriptors before the functions made CodeWarrior
hoist a shared `.rodata` base and save an extra register: the constructor fell
to 87.652176%. Moving definitions after their uses restored independent address
loads, but both const-struct and const-array forms landed in `.data`; providing
complete array extents did not change that result. The constructor was then
99.565216%, with relocation differences still present.

The [ballistic particle investigation](ballistic-particle-recovery.md) documents
the same early-definition/shared-base behavior and its scoped `pool_data off`
solution. Applying that control only to this constructor preserves all four
functions, descriptor storage, generated vtable and relocations. The existing
`fp_contract on` scope remains on the update. Both controls and port guidance
are recorded in the exceptions register. No assembly or handwritten vtable is
introduced.

## Data ownership

The constructor selects the three descriptors at
`0x80474B68..0x80474B8C`; its name pointer at `0x805D4018` refers to the following
`TBoss8DragonEffBullet` string at `0x80474B8C`. The read-only split ends at
`0x80474BA8`, including six zero alignment bytes. The name pointer is four bytes,
with a four-byte alignment tail in its eight-byte split range. Its old symbol
extent incorrectly included that tail. This follows the
[Gcrna storage case](gcrna-static-storage.md).

Ordinary `25.0f` and `0.0f` literals emit the float pool at
`0x805DEF00..0x805DEF08`. `localize_split_globals.py` verified fresh active
original and compiled consumers before localizing its two anonymous exports.
The final inventory contains 8,564 active consumer objects and no foreign
references to the claimed descriptors, name or scalar pool. Generated retention
adds five definitions and removes none; the linked-unit list stays unchanged.

## Validation

The complete unit has 4/4 exact functions, 940 exact source-linked code bytes,
and 104 exact source-linked data bytes. Matched and linked data each gain 80
bytes, with no changed denominators or loss of address coverage. The allocated
sections have the original alignment and contents, allowing only their terminal
zero padding; all 40 resolved relocations match. The four modified creation
sites retain exact caller functions.

The clean baseline and final candidate reproduce original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. `tools/check_pr.py` passes,
including no-loss reporting, all 3,616 source-linked units and generated
retention freshness.
