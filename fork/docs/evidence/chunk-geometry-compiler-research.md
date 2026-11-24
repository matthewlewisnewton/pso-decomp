# Complete chunk geometry unit and compiler research

This records the complete recovery, measured after merging fork main
`7a97a878737615c8c6929889a167944fcd9cfc2a`. Main now selects GC 2.0
for the Ginja library and the linker. The unit
`pso/unk/text_803E2D70.cpp` is source-linked: **29/29 functions, 7140/7140 code
bytes, and 68/68 reported data bytes match**, including
the two native assembly bodies described in
[the exception record](paired-single-sdk-asm.md). The weighted transform uses
Matt's previously approved native body and a compiled scalar fallback; the
dispatcher needs no assembly exception. This does not claim source-only
replacements for the two native bodies. The linked DOL retains SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3` while taking this unit from its
compiled object.

The current-main baseline had 27/29 exact functions, 5728/7140 exact code bytes,
48/68 exact data bytes, and no source link for this unit. The final change adds
two exact functions, 1412 exact code bytes, 20 exact data bytes, and one linked
unit. The `.sdata2` report includes four bytes of alignment after four floats.

## GC 2.0 is an equally good candidate

Compile the current source with the unit's configured flags, changing only the
compiler executable. After the existing `.sdata2=4` comment alignment adjustment:

| Stock compiler | Exact functions | Remaining mismatch |
|---|---:|---|
| GC/1.3 | 28/29 | `transform_chunk_object_tree`, 96.47059% |
| GC/1.3.2 | 28/29 | same |
| GC/1.3.2r | 28/29 | same |
| GC/2.0 | 29/29 | none |
| GC/2.0p1 | 28/29 | `draw_projected_textured_strip`, 97.849464% |
| GC/2.6 | 29/29 | none |

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

## Resolving the dispatcher register difference

The earlier `dispatch_chunk_polygon_list` at `0x803E3F2C` had the original
772-byte size and instruction sequence. Two register operands differed: the first signed
16-bit narrowing after the AND mask uses `r3` instead of `r26`, and the following
OR read that same scratch register. The score was 99.94819% on all six profiles
above. Behavioral equivalence did not satisfy the exact-match and source-link
requirements. The final dispatcher matches all 772 bytes.

The MWCC debugger shows a nested short conversion followed by promotion to a
32-bit local. The inner conversion allocates a backend scratch register; the
outer promotion recognizes the preceding extension and returns it without
honoring the destination hint. Copy propagation deletes the copy to the first
masked local, whose only use is the OR. Later values have other uses or reaching
definitions and retain copies that coalesce into `r26`.

The [slot-clamp inline recovery](chr-select-slot-clamp-inline.md) and
[technique-handler allocation](cast-technique-6x47-register-allocation.md)
provided concrete precedents for helper temporaries and narrow/wide local
lifetimes. The successful source combines those ideas using ordinary local
aggregates, without an inline helper or a bitfield:

- `CommandState::wire` retains the immutable signed 16-bit command word.
- `CommandState::header` is an `int`, the promoted working header and later
  strip flags.
- A local `MaskWord` holds an ordinary `s16 value`. Compound AND and OR each
  narrow to that signed word before the result is promoted into the header.

Scalar replacement gives the aggregate members compiler temporary lifetimes,
which lets the register allocator merge the wire, masked result, and working
header where their live ranges permit. Unrelated named locals retain the
original payload-load and call registers. These structures describe scalar
parser state; their memory layout, padding, and addresses are never observed.
They emit no extra storage, branches, or instructions.

Controlled comparisons against the final source:

| Change | Dispatcher result |
|---|---|
| Final ordinary members, default lifetime optimization | 100%, 772 B |
| Add `opt_lifetimes off` | also 100%; unnecessary and omitted |
| Use a signed 16-bit bitfield instead of the `s16` member | also 100%; unnecessary and omitted |
| Use `s32` (`long`) instead of the promoted `int` header | 98.03109% |
| Replace `MaskWord` with a standalone `s16` local | 99.404144%, 776 B |
| Replace `CommandState` with standalone locals | 98.80829%, 780 B |
| Enable propagation instead of scoped `opt_propagation off` | 99.507774%, 19 operand differences |

The existing scoped `bool off` and `use_lmw_stmw off` preserve integer predicates
and native save/restore helpers. No additional lifetime control was retained.
The corresponding compiler implementation can be inspected in
[mweppc](https://github.com/doldecomp/mweppc), particularly
`InstrSelection.c`, `Operands.c`, `CopyPropagation.c`, and `IROUseDef.c`.

Earlier measured routes, isolated from production source:

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
  improve the earlier result.

## Data, source linking, and validation

The four compiler-emitted floats at `0x805E109C` through `0x805E10A8` are private
to this unit. A fresh census of 8679 compiled and original objects from the
generated active inventory found no external references to their old split
labels. Their local symbol scope preserves native pooling without dropping an
external API. The `.sdata2=4` alignment adjustment preserves the original
four-byte placement in both ELF and CodeWarrior metadata.

`link_units.py scan --write` admits the entire unit and adds 19 retention
entries, removing none. A subsequent configured build links the compiled
object and passes the original DOL hash. `check_pr.py` validates no loss against
the freshly built current-main baseline, the exact linked-unit set, and retention
metadata. No artificial split or instruction patch is used.

The host dispatcher probe covers eight state/cache/render paths and 62208
additional combinations of command flags, strip formats, and full-width masks.
Expected masked flags are derived from unsigned bits independently of signed
narrowing; ASan and UBSan pass, including negative flags and signed information
boundaries. The weighted scalar fallback passes its 640 native-instruction
reference cases. Independent review also checked the final aggregate form and
compiler comparisons.

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
possible C++ source. The final source link uses the already approved weighted
native body; none of these unsuccessful alternatives or additional assembly
exceptions was adopted.
