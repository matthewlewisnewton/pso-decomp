# Chunk vertex-color cache constant ownership

Base: fork main `45f9e45bd94f2beba952ca4f2cdfc3b03ec5623a`.

`pso/unk/text_803E4CE8.cpp` already source-links its one 164-byte function,
`cache_chunk_vertex_colors`. Its two constants were outside the split in the
16-byte original-only range `0x805E10B0..0x805E10C0`.

The original function loads `0.0f` at `0x805E10B0` and `1.0f` at
`0x805E10B4` before its loop. Each iteration transforms the position through
`matrix_mult_vec(NULL, ...)`, copies the color word from input `+0x0C` to
output `+0x18`, and writes the normal `(0, 1, 0)` at output `+0x0C`.
The strides are 16 bytes for input and 32 bytes for output; the final output
word is untouched. The source now expresses those fields as `Vec` and `u32`
records, with size checks, and uses the existing matrix helper declaration.

The dispatcher at `0x803E4230` selects this format for vertex type `0x23`.
It passes the same three-field job as the other vertex transforms, plus an
unused matrix argument in r4. A shared `ChunkVertexJob` declaration preserves
that call boundary. The cache routine itself selects the current matrix by
passing NULL to `matrix_mult_vec`. The matrix argument retains the existing
32-bit declaration; this change does not establish a typed interface for the
other chunk transforms or recover the original source filename.

## Compiler comparison and ownership

The first typed candidate with ordinary floating-point literals reproduces
all instructions but initially scores 99.756096%: the two literal relocations
point into a new private `.sdata2` section that the old split does not own.
The [laser-light pool](laser-light-constant-pool.md) and
[conversion-pool investigation](conversion-pool-constants.md) describe this
same distinction between instruction matching and complete object ownership.

A fresh inventory of all 8,572 configured original and compiled consumers
finds only `text_803E4CE8` referring to `lbl_805E10B0` and `lbl_805E10B4`.
The adjacent `lbl_805E10B8` is read by `text_803E4D8C`; its eight-byte object
stays original-only. Native literal emission and those references support
assigning exactly `0x805E10B0..0x805E10B8` to the cache unit and localizing its
two private split symbols with `localize_split_globals.py`. No named constant
copies, padding arrays, compiler overrides or new pragmas are needed.

## Validation

The untouched base was built with fresh split objects and its retention check
passed before editing. The completed cache object matches all allocated
bytes: `.text` 164 and `.sdata2` 8. Both SDA21 relocations resolve to pool
offsets 0 and 4; the REL24 relocation still targets `matrix_mult_vec`.
All three allocated relocation tuples agree after normalizing local symbols
to section offsets. The compiled pool has the required eight-byte alignment,
and the actual linker inputs select the compiled cache object.

`tools/check_pr.py` passes. Matched and source-linked data increase by eight
bytes, with no change to total data, exact functions, matched code or linked
code. All 3,620 linked units remain exact. The caller retains its 27/29 exact
functions and unchanged data scores; its remaining recovery is outside this
unit. Generated retention metadata is unchanged. The rebuilt DOL retains
SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
