# `vec3_add_to` paired-single asm exception

`vec3_add_to` (`0x803D8910`, `src/pso/unk/text_803D8910.cpp`, 36 bytes) is one
approved exception to the no-assembly rule, the same kind as
`transform_chunk_vertices_pos_normal` in PR #281. Matt approved it on
2026-11-04 (11:14 AM PT): a one-time documented asm exception, modelled on
#281. The background for why MWCC cannot emit this class of code is
`docs/evidence/paired-single-sdk-asm.md` on the #281 branch. This note covers
only `vec3_add_to`.

The original is nine instructions and a `blr`, with no stack frame:

```
psq_l  f0, 0(r3), 0, qr0
psq_l  f2, 0(r4), 0, qr0
psq_l  f1, 8(r3), 1, qr0
ps_add f0, f2, f0
psq_l  f3, 8(r4), 1, qr0
ps_add f1, f3, f1
psq_st f0, 0(r3), 0, qr0
psq_st f1, 8(r3), 1, qr0
blr
```

`r3` is `dst` and `r4` is `src`. The xy pair is loaded with W=0 and z with
W=1 (ps1 forced to 1.0), then added in place: `dst += src`. That is the shape
of the Dolphin SDK's `PSVECAdd`, but not that function: `PSVECAdd` takes three
pointers and writes a separate destination, and its register schedule differs.
GC/2.6 has no `psq_l` / `psq_st` intrinsic. `__vec2x32float__` emits `psq_lx`
(indexed) plus a scalar `z`, never these D-form `psq_l` / `psq_st` opcodes
(56 and 60).

The definition is an MWCC `asm void` with `nofralloc`, guarded by
`#ifdef __MWERKS__`. The `#else` branch is the scalar add
(`dst->x += src->x`, and the same for y and z). The GameCube build uses the
asm and matches all 36 bytes. A port compiles the scalar branch.

`vec3_dot` (`0x803D89C0`, 0x28 bytes) and `vec3_cross` (`0x803D8A18`, 0x54
bytes) are not part of this exception, and they are not the SDK paired-single
routines. Matt approved trying `PSVECDotProduct` / `PSVECCrossProduct` on
2026-11-04 (4:39 PM PT). The originals do not match those routines, so the
asm was not added.

`vec3_dot` is ten scalar instructions: `lfs` / `fmuls` / `fmadds` / `blr`,
first opcode `0xC0030000` (`lfs f0, 0(r3)`). The Dolphin SDK
`PSVECDotProduct` (dolsdk2004 `src/mtx/vec.c`), compiled with this unit's
GC/2.6, is 0x20 bytes and starts `0xE0430004` (`psq_l f2, 4(a), 0, qr0`),
then `ps_mul` / `ps_madd` / `ps_sum0`. It is not linked in this binary.

`vec3_cross` returns `f32`. It is `lfs` / `fmuls` / `fmsubs` / `stfs`, a
double `fmadd` for the length square, then `frsqrte` / `fres` / `blr`. First
opcode `0xC1040004` (`lfs f8, 4(r4)`). The SDK `PSVECCrossProduct` is `void`,
0x3C bytes, and the copy already in this binary (`0x80377040`) starts
`0xE0240000` (`psq_l`) and uses `ps_merge10` / `ps_muls0` / `ps_msub` /
`psq_st`. Compiling that SDK body with GC/2.6 reproduces those 0x3C bytes.
It does not compute a length or a reciprocal.

Both stay the plain C in this file. That C is not byte-exact: GC/2.6's
register allocator does not keep the original registers, and
`__fres(__frsqrte(...))` inserts an `frsp` the original does not have.

The register entry for `vec3_add_to` is in `docs/porting-exceptions.md`.
