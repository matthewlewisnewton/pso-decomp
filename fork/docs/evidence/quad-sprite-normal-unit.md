# Normal quad-sprite unit completion

`TQuadSpriteNormal.cpp` owns `801E5598..801E58D8`: render, destructor and
constructor, totaling 832 code bytes. The starting implementation already
matched and linked those functions and 32 data bytes. This change preserves
that code coverage and recovers another 40 matched, source-linked data bytes.

## Renderer and shared boundaries

The renderer is now `TQuadSpriteNormal::render()` rather than a C function
with an unrelated self structure. It uses the shared `ParticleDefinition`
layout and `Vec`, and the existing declarations for matrix transformation and
quad drawing. Descriptor offsets `04`, `08`, `0C`, `10`, `14`, `18` and `1C`
select the texture list, texture, UV count, four-float UV records, width,
height and color. The local draw record contains four screen edges followed
by those four UV values. Node position and offset occupy `04..1B`; the byte
at `29` selects the screen-space path when equal to one. Unused node and
projection fields retain provisional views instead of speculative names.

The shared sprite base still has raw list/count fields and a C constructor.
Its recovery involves the other sprite classes and is outside this unit.
The normal-sprite C constructor now explicitly accepts and forwards its
parent and `ParticleDefinition *`, matching the caller in
`TParticleCtrl::create_quad_sprites` and the unchanged registers at
`801E5894..801E58A8`. Its declaration is shared with that caller. The existing
vptr assignment remains at this bounded lifetime interface; the destructor
still makes the compiler emit the vtable. No vtable table is written by hand.

## Emission experiments

The initial member conversion retained all three exact functions. Replacing
the two explicit byte strides with ordinary `i` indexing swaps `r29` and
`r30` at the UV/list accesses and increments. Keeping the separate strides
preserves the original operands while naming the record sizes with `sizeof`.
The existing floating-point contraction scope is unchanged.

A direct string-literal pointer initializer emits the name in `.data`,
shifting the vtable. Following the repository's
[ending-picture investigation](ending-picture-recovery.md), an explicit const
character array emits the name in `.rodata` and leaves the vtable in place.
[Compiler-emission evidence](compiler-emission-evidence.md) also motivates
checking relocation targets rather than instruction scores alone. These are
observed compiler behaviors, not claims about Sega's original source spelling.

## Owned storage and validation

The constructor's pointer at `805D35A8` refers to the `TQuadSpriteNormal`
string at `80449860`. The renderer uses `480.0f`, `-1.0f` and `1.0f` at
`805DC460`, `805DC464` and `805DC468`. The source now owns all of them.
The pointer and last float are four-byte objects; their former eight-byte
symbol extents included linker alignment padding. The localization tool
checks the active original and compiled object inventory and finds no
foreign consumer of the last float before making its anonymous label local.

The complete unit covers `.rodata` `80449860..80449878`, `.data`
`804C6910..804C6928`, `.sdata` `805D35A8..805D35B0` and `.sdata2`
`805DC460..805DC470`: 72 data bytes including native alignment tails.
Compiled sections have six, four and four fewer bytes respectively in
`.rodata`, `.sdata` and `.sdata2`; the linker recreates those zero tails.
No data denominator or named object is removed.

All three functions, section bytes, alignments and 34 normalized relocations
match. The actual linker inputs select the compiled source object. The full
build reproduces DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`;
`check_pr.py` passes with no code, function, data or linked-unit losses and
40 additional matched and linked data bytes. Retention regeneration adds the
two recovered globals and sorts three existing bone-rotation entries without
changing their membership. No compiler setting or exception is added.
