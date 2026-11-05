# Indirect texture scroll offset and copy propagation

Base: fork `main` `915508a9d`, merged into PR
[#291](https://github.com/matthewlewisnewton/pso-decomp/pull/291). Unit
`pso/effect/TEffIndirectCtrl_802A88AC.cpp`, function
`deform_indirect_texture_scroll` (`0x802A8FD8`, 564 bytes). Flags are the
unit defaults (`GC/2.6`, `-O4,s`, `-inline off`, `-use_lmw_stmw on`,
`-sdata2 4`) unless stated. Allocation was read with the MWCC debugger
(retrowin32 + `mwcc_debugger.py`, GC/2.6 support) and every result was
checked against the split original object.

## Observed allocation

Scroll setup at `+0x10C`, and the pixel add at `+0x180`:

| Role | Original | One `off16 = offset` before the axis loop |
|---|---|---|
| `px & 63` (`pxm`) | `clrlwi r30,r21,26` | `clrlwi r29,r21,26` |
| `py & 63` (`pym`) | `clrlwi r29,r20,26` | `clrlwi r28,r20,26` |
| `(s16)offset` (`off16`) | `extsh r28,r4` | `extsh r30,r4` |
| pixel add | `add r5,r5,r28` | `add r5,r5,r30` |

The two `mr r0,...` in the start selection follow the same permutation: six
register operands, 99.78723%, same 141 instructions. Main matched only by
adding a cancelling `off16++; off16--;` in the line loop.

## Mechanism

- Virtual registers: parameters first (`p` r32 ... `phase` r36), then
  function-scope locals in reverse declaration order (`w` r37 ... `off16` r51,
  `pym` r52, `pxm` r53). Block-scoped locals are numbered below every
  function-scope local. Frontend temps (`@n`) come next, then backend temps.
- The high-pressure locals all reach the allocator's second priority level
  and are added in ascending order, so they are coloured in descending order:
  the `buf` base (a late backend temp) r31, then r53, r52, r51, ... This is the
  original's `pxm` r30, `pym` r29, `off16` r28, `first` r27 ... `p` r19.
- The frontend copy-propagates `off16 = (s16)offset` into a use in the same
  basic block. It hoists `(u32)off16` out of the pixel, line, and axis loops to
  the block right after the assignment, so the single assignment is
  propagated and deleted. The backend then computes the value as
  `extsh r69,r42`. Being the highest-numbered of that level apart from the
  `buf` base, r69 is coloured r30, ahead of `pxm` and `pym`.

## Source shapes (single assignment, no steering)

| Shape | Result |
|---|---|
| Assignment before the masks, before the axis loop, or in its `for` init | propagated; six operands |
| Assignment at the top of the line loop | propagated (the hoisted use lands in the same block); six operands |
| Assignment at the top of the axis loop | kept as r51; registers match, but `extsh` is hoisted after `addi r31,r1,8` |
| Assignment at the top of the pixel loop, or after the tile call | exact, but a loop-invariant reassignment written only for the compiler |
| `s16` declared in the pixel loop | kept, but numbered r37 and coloured r20 |
| Dead `off16 = 0` before the real assignment | removed before propagation; six operands |
| `static inline` per-pixel helper with an `s16` parameter (`-inline on`) | argument substituted; same r30 temp |
| Masks written inside the start selection | frontend temps numbered below r69; worse |
| GC/2.0, 2.5, 2.7 | same six operands; 2.0p1, 1.3, 1.3.2, 3.0a3 change other functions |

Earlier PR logs also covered narrowing scope and width, structs, arrays,
constructors, base classes, references, unions, and algebraic identities.
Each one either scalar-replaces to the same temp or changes the frame or the
instructions.

## Unit switches

Each switch was added to the unit's flags with the source unchanged:

| Switch | `deform_indirect_texture_scroll` | Rest of the unit |
|---|---|---|
| `-fp_contract on` / `off` | six operands | identical |
| `-inline on`, `noauto`, `auto`, `on,noauto` | six operands | identical |
| `-inline all` | six operands | ctor and both wave helpers change |
| `-inline deferred`, `auto,deferred` | six operands | both wave helpers change |
| `-opt nolifetimes`, `nostrength`, `nodeadcode` | six operands | identical |
| `-opt nocse` | 140 instructions | both wave helpers change |
| `-opt noloop` | exact | both wave helpers change |
| `-opt nopeephole` | 149 instructions | every function changes |
| `-opt nodeadstore` | exact (the dead store survives and backend CSE reuses it) | identical |
| `-opt noprop` | exact (`off16` stays r51) | identical |

`-opt noprop` switches off the propagation that removes `off16`, so it is the
one used. With it, the honest source compiles to the same object as main's
steered source: `.text` bytes and relocations, `.rodata`, `.sdata2`, `.data`,
`.bss`, `.sbss`, `.sdata`, section sizes, and symbols.

PR [#161](https://github.com/matthewlewisnewton/pso-decomp/pull/161) builds
this unit with GC/2.0 for `run_task`. Its source with the cancelling pair
removed and `-opt noprop` added compiles to the same `.text` (including
`run_task`), `.rodata`, `.sdata2`, and `.data` as its current object.
