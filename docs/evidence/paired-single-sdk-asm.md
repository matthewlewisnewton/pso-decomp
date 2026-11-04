# Paired-single SDK assembly and MWCC (no-asm exception record)

> **Exception record.** `transform_chunk_vertices_pos_normal` (0x803E3390,
> `src/pso/unk/text_803E2D70.cpp`) is the single exception to the
> CONTRIBUTING.md no-assembly rule, approved by Matt on 2026-11-04. It covers
> only this function. The no-asm rule otherwise stands.

Some GameCube functions in this binary are hand-scheduled Gekko paired-single
assembly copied from (or modelled on) the Dolphin SDK, not CodeWarrior output.
They cannot be matched from C with this toolchain. This note explains how to
recognize them and what the repository does with them.

## Recognizing hand-written paired-single code

Signs that a function was written as `asm`, not compiled by MWCC:

- Argument loads (`lwz`) **before** `stwu r1, ...` in the prologue.
- Callee-saved FPRs saved with `stfd f14`, `f15`, ... upward, with **no**
  companion `psq_st`, restored with `lfd`. MWCC's own Gekko callee-save is
  `stfd` + `psq_st`, allocated from `f31` downward.
- `psq_l` / `psq_lu` with an explicitly chosen W bit and GQR (for example
  `psq_l f1, 8(r4), 1, qr0`, forcing ps1 to 1.0).
- Lane-selecting arithmetic: `ps_madds0`, `ps_madds1`, `ps_muls0`,
  `ps_muls1`.
- `psq_stu` stores with update, and a `mtctr` / peeled-iteration / `bdnz`
  loop.

## Example: `transform_chunk_vertices_pos_normal` (0x803E3390)

In `src/pso/unk/text_803E2D70.cpp` (PR #281). The original (288 B) has every
sign above. It is shaped like the SDK's `PSMTXROMultVecArray` (reordered
matrix from `PSMTXReorder`, `ps_madds0`/`ps_madds1` for position) but is a
custom variant:

- different arity: a job pointer instead of four register arguments;
- 24-byte source vertices (three 8-byte `psq_lu`) and 32-byte destination
  (`psq_stu` +12, +8, +4, +8; 8 padding bytes untouched), versus 12/12 in the
  SDK;
- `count - 1` iterations with a peeled first vertex, versus `count / 2`;
- a 3x3 normal transform using `ps_muls1` (no translation).

So it cannot be replaced by a call to `PSMTXROMultVecArray`. Before the
exception the source used the scalar `C_MTX*`-style equivalent, which compiles
to 304 B and scores 0%.
`GXSetVtxAttrFmtv` in the same unit is the same kind of code.

## The Dolphin SDK ships these as `asm void`

Nintendo's `PSMTX*` routines are `asm void` in the SDK; only the `C_MTX*`
twins (`mtx.c`) are C. Every matching project checked keeps them as asm (or,
for libogc, GNU assembler):

| Project | Where | URL |
|---|---|---|
| Dolphin SDK (doldecomp/dolsdk2001) | `src/mtx/psmtx.c` (`asm void PSMTXReorder`, `PSMTXROMultVecArray`, ...); scalar `C_MTX*` in `src/mtx/mtx.c` | https://github.com/doldecomp/dolsdk2001/blob/master/src/mtx/psmtx.c |
| Twilight Princess (zeldaret/tp) | `libs/dolphin/src/mtx/psmtx.c`, `libs/revolution/src/mtx/psmtx.c` | https://github.com/zeldaret/tp/blob/main/libs/dolphin/src/mtx/psmtx.c |
| Melee (doldecomp/melee) | `libs/dolphin/src/dolphin/mtx/psmtx.c` | https://github.com/doldecomp/melee/blob/master/libs/dolphin/src/dolphin/mtx/psmtx.c |
| Super Mario Sunshine | `libs/dolphin/src/mtx/mtxvec.c` | https://github.com/doldecomp/sms |
| Wind Waker (zeldaret/tww) | `src/dolphin/mtx/mtxvec.c`, `mtx.c`, `quat.c` | https://github.com/zeldaret/tww |
| Mario Kart Double Dash | `libs/dolphin/mtx/mtxvec.c`, `mtx.c`, `quat.c` | https://github.com/doldecomp/mkdd |
| Animal Crossing, GC/2.6 (this unit's compiler) | `src/static/dolphin/2.6/src/mtx/psmtx.c`: `asm void PSMTXROMultVecArray`, the SDK schedule byte for byte | https://github.com/ACreTeam/ac-decomp/blob/master/src/static/dolphin/2.6/src/mtx/psmtx.c |
| Star Fox Adventures / Decomp Academy | teaches paired singles as an `asm {}` block; states MWCC has no `psq_l`/`psq_st`/`ps_*` intrinsic | https://github.com/zcanann/SFA-Decomp, https://decomp-academy.dev/courses/gamecube-c/lesson/advanced-psq-asm-exception |
| Mario Kart Wii (nw4r) | `register __vec2x32float__` used inside a hand-written `asm { psq_l; ps_madds0; ... }` | https://github.com/snailspeed3/mkw/blob/78572c95/lib/nw4r/math/mathTriangular.cpp |
| libogc | `ps_guMtxConcat`, `ps_guVecMultiply`, ... in GNU assembler | https://github.com/devkitPro/libogc/blob/master/libogc/gu_psasm.S |

Instruction reference: https://www.wiibrew.org/wiki/Paired_single.

## Why C cannot produce it with MWCC

- **No intrinsics.** The builtin name tables of every installed MWCC (GC 1.0
  through 3.0a5.2 and the Wii compilers) contain `__fabs`, `__fabsf`,
  `__fmadd`, `__fmadds` and AltiVec `vec_*`, but no `ps`/`psq` intrinsic.
  `__PSQ_L`, `__PS_MADDS0`, `__PS_MULS1` compile to ordinary `bl` calls; the
  `PS_MADDS0` strings in the compiler belong to the inline-assembler opcode
  table.
- **`__vec2x32float__`** is a real MWCC type. Measured here, it emits
  `psq_l`/`psq_st`/`ps_mul`/`ps_merge00` at compiler-chosen offsets, but a
  float broadcast becomes `ps_merge00` + `ps_mul`, never the lane-selecting
  `ps_muls0/1` / `ps_madds0/1`, and never a chosen W/GQR. An explicit column
  loop gave 296 B and 0%.
- **GCC/LLVM paired builtins** (`paired.h`, `__builtin_paired_madds0`,
  `llvm.ppc.paired.*`) and ProDG `-mpaired-single` belong to other
  compilers. ProDG on the scalar loop still emitted scalar `fmuls`/`fmadds`.
  Swapping the unit compiler would also lose the functions already matching
  on GC/2.6.
- **Flags and pragmas.** Sweeps across GC/Wii compilers with `-O2`..`-O4,p/s`,
  `-opt nopeephole/all`, `-fp_contract on`, `-vector on`, and per-function
  `#pragma fp_contract on` / `#pragma scheduling on` produced no
  lane-selecting paired-single ops and scored 0%. No flag produces pre-`stwu`
  loads or an f14-up `stfd`-only save.

## Repository policy and the one exception

CONTRIBUTING.md forbids assembly anywhere (including `asm void`, `asm {}`,
and `orig_asm` includes). Functions of this kind normally stay as the honest
scalar C equivalent, in the style of the SDK's `C_MTX*` functions, and remain
unmatched. Do not chase them with steering pragmas, `__vec2x32float__`
rewrites, or compiler swaps.

**Exception (approved by Matt, 2026-11-04):** `transform_chunk_vertices_pos_normal`
only. It is SDK-style hand-written paired-single code that MWCC cannot emit,
and every matching project above keeps such routines as `asm void`. It is
written the same way, as an MWCC `asm void` with `nofralloc`, the
instructions written out with labels and comments. It does not use an
`orig_asm` include or `.incbin`. The function now matches 100% (288 B).

The asm is guarded by `#ifdef __MWERKS__`. The `#else` branch keeps the scalar
C++ implementation as real compiled code for other compilers or future ports,
mirroring the SDK's `PSMTX*` (asm) / `C_MTX*` (C) split. The GameCube build
always uses the asm.

No other function is covered. Any further exception needs Matt's explicit
approval and its own entry here.
