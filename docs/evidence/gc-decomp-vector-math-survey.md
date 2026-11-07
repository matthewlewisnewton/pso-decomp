# GameCube decomp survey: scalar vector math

## Scope and bottom line

Surveyed on 2026-11-05 for PR #128 (`vec3_dot`, 0x803D89C0, and
`vec3_cross`, 0x803D8A18). This is a source survey, not a new local match
attempt. Links below are to immutable source revisions unless stated
otherwise.

**No surveyed project supplies a new plain-C form that reproduces PSO's
original register coloring.** The same source idioms seen elsewhere are
already represented by the local probes: flat three-term dot expressions,
explicit component locals, temporary-vector cross products, and
`-fp_contract on`. Projects generally accept the register assignment their
compiler produces; they do not document a general source-only way to skip a
low volatile FPR while that register is unused.

There is also no new evidence for treating these PSO functions as SDK
paired-single routines. The SDK implementations are explicit paired-single
assembly, while PSO's targets are scalar `lfs`/`fmuls`/`fmadds`/`fmsubs`.
Finally, PSO's `frsqrte` directly followed by `fres` is not the usual
normalization sequence in the surveyed sources.

## What other projects use

| Project / source | Vector-math form | Relevance to #128 |
| --- | --- | --- |
| [Pikmin 2, `Vector3.h`](https://github.com/projectPiki/pikmin2/blob/83d333976e808aad75b4c7d304c3d19a22e82423/include/Vector3.h#L362-L384) | `dot` is one flat `x*x + y*y + z*z` expression. One `cross` overload computes three locals and returns a vector; another stores y, z, x into a temporary before copying it. | These are ordinary source shapes, not evidence of a skipped FPR. Their declaration/store order is target-specific. The direct subtraction differs from PSO's original, which computes the subtracted product first and then uses `fmsubs`. |
| [Melee, `lbvector.c`](https://github.com/doldecomp/melee/blob/aa874f58021675e595d67d16c7e58b1dc73f24a6/src/melee/lb/lbvector.c#L78-L101) | `lbVector_Angle` uses a flat scalar three-term dot product; `lbVector_CrossprodNormalized` calls `PSVECCrossProduct`, then normalizes with `1.0f / len` and scalar multiplies. | Confirms that scalar dot expressions and SDK paired-single cross products coexist in one unit. A named high-level operation does not imply one universal implementation. |
| [Mario Kart: Double Dash!!, `JGeometry/Vec.h`](https://github.com/doldecomp/mkdd/blob/a10a8322655d5da6a161a38d543f9273e59007da/include/JSystem/JGeometry/Vec.h#L333-L360) | `dot`, `cross`, `squared`, and length delegate to the SDK/JMath inline vector routines; normalization uses an inverse square root followed by scaling. | These are not standalone precedents for PSO's scalar `vec3_dot` or its combined cross/reciprocal helper. |
| [Brawl, `mt_vector.h`](https://github.com/doldecomp/brawl/blob/5efd9ce7d574e0471704116c18f109aab8012ea4/include/Brawl/Include/mt/mt_vector.h#L229-L244) and [`mt_vector.cpp`](https://github.com/doldecomp/brawl/blob/5efd9ce7d574e0471704116c18f109aab8012ea4/src/sora/mt/mt_vector.cpp#L105-L130) | Three-term dot products and squared length are flat scalar expressions. Normalization computes `rsqrtf(lengthSq())`, then multiplies components. | The closest general normalization idiom still contains a separate helper boundary/operation sequence; it does not justify dropping PSO's observed `fres`. Brawl is a Wii-era codebase, so it is supporting context rather than same-compiler proof. |
| [Dolphin SDK C fallbacks in Melee, `vec.c`](https://github.com/doldecomp/melee/blob/b666b4cd87b0c9f6647d5ec7377f1112b6b153f5/libs/dolphin/src/dolphin/mtx/vec.c#L148-L217) | `C_VECDotProduct` is z + (x + y); `C_VECCrossProduct` writes three direct subtractions to a temporary and copies it out. | These are additional ordinary C shapes only. The same file provides separate `PSVECDotProduct` and `PSVECCrossProduct` asm bodies, so neither C fallback establishes the bytes of PSO's custom scalar functions. |

The public Metroid Prime repository returned by older search results was not
retrievable during this survey. No Prime-specific claim is used here; search
snippets are not treated as primary evidence.

## Compiler-pattern evidence

The public GameCube examples in Decomp Academy agree with the local result
that contraction controls the arithmetic skeleton:

- The [3D dot-product example](https://decomp-academy.dev/courses/gamecube-c/lesson/floats-dot-product-3d)
  is one `fmuls` followed by two `fmadds`, with `lfs` loads interleaved.
- The [dot-chain scheduling example](https://decomp-academy.dev/courses/gamecube-c/lesson/optimization-fp-dot-chain)
  explains that `fp_contract` forms the multiply-add chain and that the
  scheduler rearranges loads. It uses `-O4,p`, not PSO's unit configuration.
- The [two-product example](https://decomp-academy.dev/courses/gamecube-c/lesson/floats-dot-product-2d)
  likewise shows that either product can seed the standalone multiply.

Those examples explain PSO's opcode sequence but not its exact registers.
In particular, scheduling examples do not justify changing PSO's `-O3`,
`-inline off` unit flags, and a different scheduling mode tends to hoist
loads rather than reproduce the original order. The local backend analysis
in [`vec3-add-to-paired-single.md`](vec3-add-to-paired-single.md) remains
the stronger evidence for this target: at this configuration, lowest-free
coloring cannot produce `b.x` in `f3` in `vec3_dot`, or the length square in
`f10` while `f3` is unused in `vec3_cross`.

## Application to the two PSO targets

### `vec3_dot`

The ordinary contracted source shape is confirmed by Pikmin 2, Melee, Brawl,
and the SDK C fallback. PSO already has the corresponding one-`fmuls`,
two-`fmadds` shape and 93.5% at `-fp_contract on`.

The survey found **no untried source idiom with credible register-allocation
evidence**. More permutations of declarations or operand order would repeat
the exhaustive local search, not test a new hypothesis. The peer examples
support the arithmetic shape of the plain C body; they do not reproduce PSO's
registers. `vec3_dot` is therefore shipped as the original assembly leaf
through `orig_asm`, with the plain C body kept as the non-MWCC fallback.

### `vec3_cross`

The peer sources confirm the conventional three direct component
subtractions, but PSO's original has a different evaluation order and keeps
its inputs/results in a specific register assignment. The locally retained
subtracted-product-then-reassign form reproduces the opcode order and scores
91.19%; the conventional SDK/Pikmin-style shape does not resolve the
remaining coloring mismatch.

The return tail is independent evidence. The surveyed C implementations use
`sqrtf`, `1.0f / len`, `rsqrtf`, or an explicit paired-single normalization
sequence. PSO instead emits double `frsqrte` immediately followed by single
`fres`. With this compiler's `double __frsqrte(double)` and
`float __fres(float)` declarations, plain C inserts `frsp`. None of the
surveyed idioms removes that conversion. `vec3_cross` is therefore shipped
as the original assembly leaf, with the retained C body as the non-MWCC
fallback.

## Recommendation

`vec3_dot`, `vec3_cross` and `normalize_vector` are recovered as original
assembly leaves through the standard `orig_asm` mechanism, with scalar C/C++
fallbacks for ports; see [`vec3-add-to-paired-single.md`](vec3-add-to-paired-single.md).
This survey remains the evidence for why GC/2.6 cannot produce those bodies
from C. Do not copy another project's source form merely because its
mathematics is equivalent, and do not infer an SDK paired-single exception
from a similarly named operation. A future exact-C attempt would need new
evidence about this MWCC version's allocation/emission behavior, not another
generic vector implementation. The existing `vec3_add_to` exception is
unchanged.
