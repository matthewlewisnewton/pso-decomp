# Palette serialized layouts and preserved owner boundary

This follows continuation #403 at `72887757a8102459c769d0986b4c969a2911e3bd`.
It recovers the previously undeclared 332-byte entry-layout block and its
20-byte window descriptor in the existing held HelpItem_80243408 source. It
does not retry the rejected contiguous-owner or word-contract probe, activate
the source unit, or recover Palette's native destructor/table ownership.

## Schema from actual consumers

Base's initializer at 80244F2C passes descriptor offset 0x0C to
init_window_layout_entries at 80257D44. That parser reads two word counts,
allocates their product of entry pointers, and repeats the same variable-length
record sequence. Kind 6 consumes 0x30 bytes and invokes init_part_scaled; kind 4
consumes 0x1C bytes and invokes the initializer at 80259D3C. These are serialized
construction inputs, distinct from the subsequently allocated entry objects.

The 332 bytes at [804CDE50,804CDF9C) parse completely as counts 8/1 and record
kinds 6/6/6/4/6/4/6/4: five scaled sprites and three number entries. No unknown
tail, padding, extra slot or raw replacement blob is needed.

| Record | Offset | Established fields |
| --- | ---: | --- |
| Kind 6, size 0x30 | 0x00 | kind word |
| | 0x04 / 0x0C / 0x14 | two-float position / extent / pixel UV |
| | 0x1C / 0x20 | float depth / color word |
| | 0x24 / 0x28 / 0x2C | texture-list pointer-storage address / mode word / flags word |
| Kind 4, size 0x1C | 0x00 / 0x04 | kind word / two-float position |
| | 0x0C / 0x10 | float depth / color word |
| | 0x14 / 0x18 | flags word / signed value |

The initializers read precisely these offsets. Sprite initialization copies the
address at record+0x24 into entry+0x30; its renderer dereferences that storage
before passing the resulting list to the established typed texture API. All
five records relocate to the address of shared pointer storage lbl_805D63F0,
not directly to a texture-list object. The source representation preserves this
indirection. Structure size/offset assertions qualify the observed schema;
names are provisional and do not identify original source types.

The following existing descriptor at [804CDF9C,804CDFB0) is now represented by
WindowLayoutDescriptor: extent 150/107, order 50000, the entry-layout pointer
and flags 0xB28. Palette's caller declaration now names that actual descriptor
rather than an unrelated byte array. Its constructor still forwards the same
address to Base. All layout storage remains mutable as in the original data
section. The original five UV arrays and every helper contract stay unchanged.

## Complete checks and limited claim

The compiled entry records and descriptor reproduce all 352 raw bytes and six
ADDR32 relocations: five pointer-storage references and one descriptor-to-entry
reference. Existing 424-byte UV data is identical. The complete 956-byte helper
text is unchanged and matches original instructions; all five functions retain
their existing exact matches. Palette's entire compiled ELF is byte-identical
to the published checkpoint, including symbols, data and relocation records.

The held source now emits 808 data bytes: the 776-byte UV/layout/descriptor
prefix followed by its existing 32-byte compiler-generated jump table. Original
data has a separate 24-byte Palette table before that jump table, for 832 bytes.
Consequently the compiled anonymous jump table moves from offset 424 to 776,
while its original offset remains 800. Text-target comparison accounts only
for this known local jump-table position. All eight jump relocations retain
the same icon-function offsets/addends; the other resolved text/data targets
match the original. This is not a claim that the whole data section is exact
or safely source-linkable.

The complete ordered executable input list is identical to the prior checkpoint.
The full original HelpItem_80243408 object remains selected once, its compiled
source remains absent, and all other original providers and protected ranges
are unchanged. The capacity-gated full build preserves DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr passes with zero function,
metric or address-coverage change; all 3591 linked units remain exact and
retention is clean at 17989 entries. No matched-data or source-linked gain is
claimed: the report does not credit these bytes until complete data ownership
is resolved.

## Remaining evidence

This removes the opaque entry-schema gap from the
[Palette owner investigation](window-action-palette-construction.md). It does
not establish one source owner for the UV arrays, serialized layouts, compiler
table and anonymous jump table. The earlier co-owner probe also changed caller
conversion behavior. A further native activation attempt needs an independently
supported common owner and consistent caller conversion contract; declaration
variants, explicit base-hoisting or matching controls are not substitutes.

The deleting wrapper, manual/original table provider, light-helper arity,
tag/entry interfaces and all other lifetime, constant, initialization and
original-provider holds remain. The separate Word #407 lane is not imported.
