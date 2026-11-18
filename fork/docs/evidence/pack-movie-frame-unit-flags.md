# `pack_movie_frame` and the unit `-opt` switches

Merged into PR [#167](https://github.com/matthewlewisnewton/pso-decomp/pull/167).
Unit `pso/misc/TMovie_80143988.cpp`, function `pack_movie_frame`
(`0x80143988`, 564 bytes, the only function in the unit). Unit defaults are
`GC/2.6`, `-O4,s`, `-inline off`, `-use_lmw_stmw on`, `-sdata2 4`. The
allocation and the backend passes were read with the MWCC debugger
(retrowin32 + `mwcc_debugger.py`). The pass logic was checked against
[doldecomp/mweppc](https://github.com/doldecomp/mweppc)
(`Coloring.c`, `Peephole.c`, `Scheduler.c`, `CodeGen.c`, `CodeMotion.c`).

## Result by switch set

Same source in every row (`src/pso/misc/TMovie_80143988.cpp`):

| `-opt` switches | Match | Size | Notes |
|---|---:|---:|---|
| `nolifetimes,nocse,noprop,noloop` | 100% | 564 | the unit setting |
| `nolifetimes,nocse,noprop` | 93.06% | 564 | pad/stride shifts coloured in another order |
| `nolifetimes,noprop,noloop,nostrength` | 93.06% | 564 | same |
| `nolifetimes,nocse,noloop,nostrength` | 70.50% | 596 | `touch` propagated as a constant |
| `nocse,noprop,noloop,nostrength` | 53.40% | 568 | lifetimes split, `stmw r21` |
| none | 54.68% | 564 | `stmw r21` |

## Constraints the source follows

- **rlwimi needs the complementary mask.** `adjustforward` rewrites
  `rlwinm t; or d, a, t` to `rlwimi` only when the bits of `a` outside the
  inserted field are known (`canuseinsert`). `x |= field` fails that test, so
  each insert is written `x = (field) | (x & ~mask)` with the new field on
  the left.
- **Allocation follows declaration order.** With `nolifetimes` each named
  local has one virtual register. Locals are numbered in reverse declaration
  order and coloured after all temporaries, so they are coloured in
  declaration order. `touch` interferes with more than 28 nodes, so it is
  deferred, coloured first, and gets `r0`. Each node takes the lowest free
  volatile register, then the lowest free nonvolatile already in use, and
  only then a new one from `r31` down.
- **In-place pointer decrements are sunk.** The forward peephole moves
  `addi rX, rX, imm` down to the next instruction that uses `rX`, or to the
  block's branch. It runs again after the pre-RA scheduler, when the entry
  block is already merged with the outer loop's preheader. So `cb -= 1`
  would end up after the hoisted pad shifts. `cb = cb_src - 1` is not in
  place, so it stays where the scheduler put it. `cb_src` and `cb` get the
  same register (`addi r12, r12, -4`) because `cb_src` is coloured once
  `r3`–`r11` are taken. `luma_src` takes `r31` for the same reason: it is
  declared after `width`, `height`, `cr_src`, `cb_src`, `y`, `dst` and `low`,
  and before `lw`/`uw`/`vw`/`lo`.
- **Block split at the second `__dcbt`.** `newstatement` starts a new block
  once the current one has more than 100 pcodes. Writing each chroma extract
  as two statements (`hi = uw >> 8; hi &= 0x00FF0000;`) puts the first half of
  the loop at 101 initial pcodes, so the second half starts a new block at
  its `__dcbt`. With one statement the split fell three statements later and
  the scheduler interleaved differently.
- **Early luma reload.** The second luma pair is loaded after the second
  word's inserts and before its stores. The loads then follow only the first
  word's stores in program order, which gives the target's
  `lwz r10, 8(r31)` / `lwzu r28, 8(r9)` placement.

## What did not work

- `#pragma scheduling once` (schedule factor 1, no pre-RA scheduling and no
  early block merge) fixes the entry tail but reallocates everything: 69%.
- Bitfield structs for the packed word generate `operator=` calls.
- No source found matches under the default switches. The best scored
  56.04%: without `nolifetimes` the lifetimes are split and `stmw` starts
  at `r21`.
