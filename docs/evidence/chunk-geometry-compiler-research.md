# Chunk geometry compiler and register-allocation research

This records an **incomplete recovery**, measured after merging fork main
`f1227326c4b7deaa4c33186978ad623862b590d5`. The unit
`pso/unk/text_803E2D70.cpp` remains unlinked: 28/29 functions match, including
the two native assembly bodies described in
[the exception record](paired-single-sdk-asm.md). That count does not establish
a source-only replacement for those bodies. Exact code is 6368/7140 bytes;
the reported 68 bytes of data match. Passing the original DOL hash currently
uses the original fallback object for this unit.

## GC 2.0 is an equally good candidate

Compile the current source with the unit's configured flags, changing only the
compiler executable. After the existing `.sdata2=4` comment alignment adjustment:

| Stock compiler | Exact functions | Additional mismatch beyond dispatcher |
|---|---:|---|
| GC/1.3 | 27/29 | `transform_chunk_object_tree`, 96.47059% |
| GC/1.3.2 | 27/29 | same |
| GC/1.3.2r | 27/29 | same |
| GC/2.0 | 28/29 | none |
| GC/2.0p1 | 27/29 | `draw_projected_textured_strip`, 97.849464% |
| GC/2.6 | 28/29 | none |

GC 2.0 and GC 2.6 produce matching code for **all 29 functions relative to
each other**, with identical `.text`, `.bss`, and `.sdata2` scores. Their
compiler-identification records differ. These results cannot identify which
compiler produced the original unit. They also do not rule out retuning the
source for a 1.3 compiler. The assembly branches remain active in this test.

Reproduce with a configured and built checkout:

```sh
python3 tools/probes/compare_chunk_geometry_compilers.py \
  --objdiff /path/to/objdiff-cli \
  --output-dir /tmp/chunk-geometry-compilers
```

The output directory contains each compiled object, its comparison with the
original object, a direct 2.0-versus-2.6 comparison, and a summary with the source
and compiler SHA-256 hashes and compiler arguments. Nothing changes the
production compiler override or linkset.

## The remaining dispatcher difference

`dispatch_chunk_polygon_list` at `0x803E3F2C` has the original 772-byte size
and instruction sequence. Two register operands differ: the first signed
16-bit narrowing after the AND mask uses `r3` instead of `r26`, and the following
OR reads that same scratch register. The score is 99.94819% on all six profiles
above. Behavioral equivalence does not satisfy this repository's exact-match
and source-link requirements.

The MWCC debugger shows a nested short conversion followed by promotion to a
32-bit local. The inner conversion allocates a backend scratch register; the
outer promotion recognizes the preceding extension and returns it without
honoring the destination hint. Copy propagation deletes the copy to the first
masked local, whose only use is the OR. Later values have other uses or reaching
definitions and retain copies that coalesce into `r26`.

The [slot-clamp inline recovery](chr-select-slot-clamp-inline.md) and
[technique-handler allocation](cast-technique-6x47-register-allocation.md)
provided concrete precedents for helper temporaries and narrow/wide local
lifetimes. Applying those techniques here has not yet yielded an exact object.
The corresponding compiler implementation can be inspected in
[mweppc](https://github.com/doldecomp/mweppc), particularly
`InstrSelection.c`, `Operands.c`, `CopyPropagation.c`, and `IROUseDef.c`.

Further measured routes, all isolated from production source:

- A signed 16-bit bitfield with compound masking gets both mask destinations
  into the original register, but adds conversions elsewhere. Mixed wide and
  narrow views do not retain that result without additional instructions.
- Short/bitfield headers with peephole optimization enabled remove instructions
  that the original retains. Cross-checking GC 2.0, 1.3.2, and 2.6 did not fix it.
- Strongly typed compound operators, aggregate returns, references, pointers,
  condition-declaration objects, C99 anonymous storage, local arrays, and loop
  scope changes retain the two differences or add code/stack traffic.
- A two-stage masking loop makes the masked value loop-carried and uses `r26`,
  but leaves extra control instructions after compilation/unrolling. This is
  not a matching replacement.
- Seventy-two combinations of optimization levels 2/3/4, propagation,
  lifetimes, and common-subexpression settings on GC 2.0/1.3.2/1.3.2r did not
  improve the current result.

## Weighted transform source alternatives

The signed-short conversion route with `gecko_float_typecons` **does emit GQR1
writes and indexed quantized loads**. Its GQR1 value is `0x00070007` (signed
16-bit, scale zero), followed by a separate multiplication. The original uses
`0x08070807` (scale eight). Therefore a blanket statement that MWCC cannot emit
GQR1 or indexed quantized loads is incorrect.

Native-pair arithmetic and broadcasts were checked across GC 1.3 through 3.0
and nine Wii compiler versions. The probes emitted broadcasts plus paired
multiply/multiply-add, rather than the original lane-select instructions.
Wii 1.7's `vec2x32float_align_4` pragma permits native-pair members in exact
28-byte input and 32-byte output records. That fixes a type-layout limitation,
but the resulting 540-byte transform still uses scale-zero GQR conversion and
different arithmetic from the original 640-byte function. A control using
array/cast views gives the same code-size result; the size change alone is not
evidence of progress toward matching.

These are negative results for the tested routes, not a proof about every
possible C++ source. No additional assembly exception, instruction patch,
artificial unit split, or linkset change was adopted during this research.
