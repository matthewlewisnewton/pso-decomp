# Character-creation shape blending

`pso/ui/TAdSinglePlyChrSelectGC_8028EF14.cpp` owns `0x8028EF14–0x80290B3C`.
The two missing bodies were `blend_shape_chunk_vertices` (760 bytes at
`0x8028F6A0`) and `calc_shape_region_coefficients` (188 bytes at `0x8028FA30`).
Together they complete all 41 functions / 7,208 code bytes in the unit.

## Calculation and chunk format

The 24 sample indices select eight triangles from nine `(width, height)`
points. The first two vertices of each triangle share a width, so the third
weight is `(x - x0) / (x2 - x0)`. The second weight is
`((y - y0) - (y2 - y0) * third) / (y1 - y0)`; the first is the remainder.
The table is now expressed as integer indices and float pairs instead of
pointer-shaped numeric initializers. Its bytes and relocations are unchanged.

The chunk walker uses the low byte of the chunk header through the existing
`map_button_code`: `0x29` has three extra words per vertex, `0x2C` has four,
and a negative result terminates traversal. The next header word's upper half
is the vertex count. Three source streams are blended into the destination:
position, normalized nonzero normal, and (when present) the packed upper-half
weight. The destination's lower-half index is preserved. The original limits
traversal to 1,000 chunks and retains an empty three-iteration counted loop.

## Compiler evidence

The pinned GC/2.6 compiler with the unit's existing `fp_contract on` emits the
original fused arithmetic. Initial scalar C++ and reduced C forms reproduced
the calculation but differed in scheduling, conversion stack slots, and FPR
allocation. The relevant repository precedents were
[conversion pools](conversion-pool-constants.md),
[compiler emission](compiler-emission-evidence.md),
[compiler tracing](moja-compiler-tracing.md), and the
[vector-math survey](gc-decomp-vector-math-survey.md).

For the chunk walker, separate signed-to-float inputs preserve the conversion
slot order. Advancing each source cursor in the last normal-component read
preserves scheduling across the length/normalization calls. The shared
`f32_bits` / `bits_to_f32` helpers express the mixed float/integer stream.

For the coefficients, scalar expression forms, coordinate reuse, typed table
views, inline helpers, C versus C++, and supported optimization settings were
compiled and compared. Coordinate reuse narrowed the mismatch to a swap of
FPRs 3 and 4. A GC/2.6 trace using
[mwcc-debugger](https://github.com/cadmic/mwcc-debugger) showed the anonymous
height load being allocated before the shared quotient temporary. With
`opt_propagation off`, explicit scalar locals retain their identities. Their
declaration order was derived from the compiler's interference graph; it
reproduces all FPRs without additional arithmetic. Keeping the second and
third sample lookups in their coordinate expressions also preserves the
original GPR allocation. The pragma is scoped to this one function.

The existing deferred-codegen scope emits definitions in reverse order.
Definitions were reordered to match all 41 original function positions,
including the three `TCMCharacter` model-part methods. Existing constructor,
destructor, and virtual-table representations remain unchanged; this change
does not infer new class ownership for their legacy interfaces.

## Data boundary and linkage

The signed integer conversion naturally emits the eight-byte double bias at
`0x80451CD8`. It immediately follows this unit's read-only data and precedes
`CharacterAppearanceTables` at `0x80451CE0`. Extending the read-only split to
`0x80451CE0` gives the unit its compiler-generated pool; no bias bytes are
hand-defined. The localization tool checks all current split and compiled
consumers before making unreferenced pool/anonymous symbols local. It verified
217 existing string literals and the conversion bias (218 symbols total);
none has a consumer outside this unit.

The native static dispatch-array guard is at `0x805D655C`, four bytes past
an eight-byte boundary. The preceding `creation_resource_ready_state` word at
`0x805D6558` is defined here as well: this unit initializes and clears it in
the constructor/destructor, and owns all transitions through states 0, 1 and
2; `TObjCMName` only observes it. Claiming this word restores the compiler's
eight-byte `.sbss` alignment and places the native guard at offset four.
The three trailing bytes are alignment padding, not an additional object.

Whole-unit validation includes function order, allocated section layout,
relocations, source-link eligibility, the original DOL SHA-1, and the
address-based no-loss report against fork main `e9b77fcfdcc2335c9a5a92886826022c80505e67`.

The source-linked build passes the original DOL SHA-1. `check_pr.py --no-build`
passes after that build: +2 exact functions, +948 matched code bytes,
+12 matched data bytes, +1 linked unit, +7,208 source-linked code bytes and
+154,020 source-linked data bytes, with no regressions. All six allocated
sections and all 41 functions compare at 100%. Generated retention adds
103 symbols and removes none.
