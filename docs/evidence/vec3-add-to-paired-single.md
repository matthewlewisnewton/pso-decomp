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

`vec3_dot` (`0x803D89C0`) and `vec3_cross` (`0x803D8A18`) are not part of this
exception. They are scalar `lfs` / `fmadds` / `fmsubs` / `frsqrte` / `fres`,
written as plain C in the same file. That C is not byte-exact: GC/2.6's
register allocator does not keep the original registers, and
`__fres(__frsqrte(...))` inserts an `frsp` the original does not have. No
scheduling pragma and no asm was added for them.

The register entry for `vec3_add_to` is in `docs/porting-exceptions.md`.
