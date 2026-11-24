# MusyX assembly and scalar fallbacks

`do_src1`, `do_src2`, `DoCrossTalk`, and `HandleReverb` are vendor MusyX
routines that shipped as hand-written PowerPC, not as MWCC output. The
GameCube build keeps those bodies (`orig_asm` includes under `#ifdef
__MWERKS__`). Each one now has a scalar C implementation in the `#else`
branch for other compilers. Matt approved that split on 2026-11-04: assembly
stays only when a scalar C/C++ equivalent is compiled beside it.

The register entry is section 1 of `docs/porting-exceptions.md` (landed with
PR #315). This note is the evidence cited there. The scalar fallback is PR #316.

## Why the assembly stays

The bodies are Factor 5 MusyX aux kernels, the same family as the Dolphin
AXFX chorus and high-quality reverb (`doldecomp/dolsdk2001`
`src/axfx/chorus.c`, `src/axfx/reverb_hi.c`). Signs in this binary:

- `DoCrossTalk` and `HandleReverb` use paired-single ops (`ps_merge00`,
  `ps_mul`, `ps_muls0`, `ps_sum0`). MWCC has no paired-single intrinsic that
  emits that schedule. See `docs/evidence/paired-single-sdk-asm.md` on
  `upstream-pr-178-transform-chunk-vertices-pos-normal` for the same limit.
- `do_src1` / `do_src2` are hand-scheduled integer/FPU loops (`addc` + `mcrxr`
  for the phase carry, `fctiwz` + `stfiwx` stores, a fixed 160-iteration
  count). They are not MWCC output of the scalar C.

The GameCube objects stay byte-identical to the disc. The scalar code is not
part of that build.

## Where the fallbacks are

| Function | Address | Scalar code |
| --- | --- | --- |
| `DoCrossTalk` | 0x803BED6C | `src/musyx/runtime/StdReverb/reverb.c` |
| `HandleReverb` | 0x803BEEFC | `src/musyx/runtime/StdReverb/reverb.c` |
| `do_src1` | 0x803BF500 | `src/musyx/runtime/Chorus/chorus_fx.c` |
| `do_src2` | 0x803BF698 | `src/musyx/runtime/Chorus/chorus_fx.c` |

Sources used while deriving the C, and where this binary differs:

- AxioDL/musyx `717404d77c17a95dd101bbe737d0f9549ab600e6`,
  `src/musyx/runtime/Chorus/chorus_fx.c` and
  `src/musyx/runtime/StdReverb/reverb.c` (CC0). Their `#else` paths are the
  closest C. Three details do not match this DOL:
  - Coefficient index. The disc uses `rlwinm rT, posLo, 7, 21, 27` (a byte
    offset into `rsmpTab12khz`). AxioDL uses `(posLo >> 9) & 0x7f`.
  - `DoCrossTalk` scales the `(start, end)` pair by `value0_6` (`ps_muls0`)
    and converts with `fctiw` (round-to-nearest-even). That is the
    `MUSY_VERSION <= 2.0.0` schedule. AxioDL's scalar mix has no `0.6` and
    truncates.
  - Predelay. `HandleReverb` reloads `preDelayCurrent` from the reverb object
    on every sample (`lwz r29, 0x1B8(r28)` with `r28 = rv + k*4`) and stores
    the advanced pointer with `stw r29, 0x1B8(r30)`, where `r30` is the
    delay-line base. The struct field is not updated. The audible effect,
    when `preDelayFrames != 0`, is a one-sample delay through `line[0]`, plus
    that store into the line. AxioDL writes the pointer back to
    `preDelayCurrent`.
- doldecomp/dolsdk2001 `src/axfx/chorus.c` annotates the same `do_src1` /
  `do_src2` instruction schedule (AXFX chorus, no scalar body).

`fctiwz` in the chorus resamplers and in `HandleReverb`'s output store is
truncation toward zero (`(s32)` of an in-range float). `DoCrossTalk`'s
`fctiw` is round-to-nearest-even, implemented by `fctiw_round`.

## How the fallback was checked

- GameCube: both units were 100% before the split (`chorus_fx` 2384/2384
  code bytes, `reverb` 3168/3168). The `__MWERKS__` branch is the previous
  assembly, so those scores stay 100% and `tools/check_pr.py` must report no
  regressions.
- Host typecheck: `g++ -m32 -std=c++98 -fsyntax-only` on both translation
  units, `__MWERKS__` undefined, exit 0. `-m32` is required because `s32` is
  `signed long` and the header layout asserts assume a 32-bit `long`.
- Host execution: this machine has `libc.so.6` for i386 but no 32-bit crt, so
  the in-tree objects were not linked. The `#else` bodies were compiled as
  ordinary 64-bit C++ with `s32` as `int` and the structs those functions
  actually touch, then run. Results: `do_src1` of a constant 1000 truncates
  to 97 (`1000 * rsmpTab12khz[0]`); `posLo 0x12345678` uses float index 256,
  not AxioDL's 172; `DoCrossTalk(1000, 0, 0.5, 0.5)` stores 500 and 300
  (`0.6 * 500`), and `fctiw` maps 0.5, 1.5, and -1.5 to 0, 2, and -2;
  `HandleReverb` with `mix == 0` stores `(s32)(0.6 * sample)`, leaves
  `preDelayCurrent` on the line base, writes the last sample to `line[0]`,
  and writes the 4-byte pointer bits at float index 110.
