# Orbit particle unit recovery

Recovered from fork main `fffd67d0c3` and integrated with `f8a71fae8a`
(2026-11-10). The original split remains `pso/misc/ParticleOrbit.cpp`:
text `0x80089F7C..0x8008B478`, rodata `0x80439530..0x80439540`, and
sdata2 `0x805D9528..0x805D9558`. No split boundaries or symbol names change.

## Update behavior and types

`TUnk_8048E790::run_task` occupies `0x8008A080..0x8008A92C` (2,220 bytes).
It advances the orbit, optionally follows a registered entity's virtual center,
rotates the orbit/rise vectors, evaluates the color envelope, advances spin
and animation, and calls the existing retirement method. The direct orbit
path tests that **all three** angle words are nonzero; changing that to the
more usual “any angle” condition changes behavior.

The method uses the existing particle base, `ParticleParam`, `ParticleDefinition`,
entity lookup, and real center virtual. Its derived tail is declared in
`TUnk_8048E790.h`: motion step, X/Z orbit center, radius, vertical offset,
and orbit angle. The existing pulse-angle word remains `m_dc`. The class stays
0xE0 bytes, with a size assertion. No second particle or parameter layout is
introduced. The orbit variant uses the shared parameter slots at +0x50,
+0x38 and +0x3C for its RGB rates; this does not rename those slots for other
variants.

The sprite table declaration matches its owner's `void *[0x6C]`. Entries cross
the existing `TUnk_804C57F0::m_28` opaque boundary into `ParticleDefinition`.
The pre-existing constructor views and other provisional rendering interfaces
remain bounded legacy interfaces; this change does not claim complete recovery
of those APIs. Known inherited calls and the no-argument matrix push now use
their actual call boundaries.

## Guess, compare, research, and repeat

The production compiler is stock GC/2.6 with the normal `-O4,s`, `-inline off`,
and `-sdata2 4` settings. No per-unit command-line override or object
post-processing is added.

The first update reconstruction compiled at 86.35496%. Investigation used
[conversion-pool evidence](conversion-pool-constants.md), the
[inline-clamp case](chr-select-slot-clamp-inline.md), the ordinary clamp in
`ChunkMaterialState.cpp`, and [Moja's compiler-tracing method](moja-compiler-tracing.md).
A passive mwcc-debugger/retrowin32 run against the stock compiler exposed the
frontend envelope temporaries and FPR coalescing.

Representative measured update arrangements:

| Source arrangement | Match |
| --- | ---: |
| First reconstruction, named scalar references | 86.35496% |
| Literal pools and packed color copy | 95.21081% |
| Float color aggregate and inline clamps | 98.558556% |
| Propagation disabled, explicit intermediate integer casts | 99.96397% |
| Propagation disabled, direct byte casts | 100% |
| Final age/opacity pair and RGB channels, normal propagation | 100% |

Other bounded probes covered direct clamps, helper return/output parameters,
value/reference arguments, declaration lifetimes, an extracted envelope helper,
and individual optimizer settings. None is retained merely to change register
allocation. Disabling common-subexpression elimination, for example, adds
repeated age loads and does not match.

During integration, the newly merged
[radial particle recovery](radial-particle-update.md) supplied the close sibling
case: a two-element normalized-age/opacity pair and three RGB channels.
Applying that representation preserves the complete update match with ordinary
propagation, so the experimental propagation pragma is removed. Every local
has a role in the envelope. The array spelling is not proof of the original
source declaration.

The update requires fused orbit and color calculations, so it has a scoped
`fp_contract on`, like the existing two initializers. The renderer's arithmetic
is unchanged. A port should preserve fused single-precision operations where
native rounding matters.

The packed color is formed by writing a live `u32` through `u8 *`, legal
unsigned-byte access to its object representation. GameCube byte order gives
0xAARRGGBB. A little-endian port must explicitly pack alpha/red/green/blue with
shifts; removing compiler annotations alone does not preserve that word.

## Complete object and source linkage

All eight functions and all allocated sections match. The emitted sizes and
alignments are text 5,372 bytes/alignment 4, rodata 16 bytes/alignment 8,
and sdata2 48 bytes/alignment 8. An unused duplicate `clear_active_flag`
definition is removed from this object; its original owner remains the
ballistic unit at `0x80088000`. Keeping the duplicate adds 16 foreign bytes.

The signed and unsigned conversion biases are compiler-generated. The first
40 bytes of sdata2 come from scalar literals in first-use order. The original
final eight-byte object `lbl_805D9550` contains the angular range and a trailing
zero; its definition and small-data section annotation retain that whole
object. Ordinary array placement changes the initializer addressing and layout.

Twelve compiler-pool exports are localized only after the repository scanner
checks every active original and compiled consumer and finds no references.
The named final object remains exported. Source linkage adds one unit and
four generated retention entries, preserving the existing linkset.

Validation compares complete sections, alignment, function order, exports,
relocations, affected consumers, source selection, the original DOL hash, and
repository-wide address coverage. Relative to the integrated main baseline:
+1 exact function, +2,220 exact code bytes, +64 exact data bytes, and
+5,372 source-linked code bytes / +64 source-linked data bytes.

Raw disassembly, original objects, compiler traces, and experimental sources
remain local under the ignored build directory.
