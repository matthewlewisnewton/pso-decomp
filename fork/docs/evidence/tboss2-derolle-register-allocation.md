# TBoss2DeRolLe update and pulsing-color register allocation

## Complete unit recovery (2026-11-14)

Recovered from fork main `c17ee9946c4d6887e37a01c390320bb25e9a793c`,
then rebased onto `1712bd56c8bc24956dc6279019c0dda0fc577f8c` and checked
against a fresh build of that main revision.
All 110 functions (29,644 bytes) and all allocated data (3,684 bytes) now
match together under stock GC/2.0 with `-O4,s`, `-inline on` and the existing
scoped floating-point contraction settings. The unit is linked from source.

### Discarded increment versus a call argument

The final attack handler at `0x8002FE60` increments the attack count and then
calls `free_laser`. The old recovery passed the discarded postincrement result
as an extra `s32` argument. The callee only reads the actor in `r3`; its name
encodes a single `void *` parameter, and its body never reads `r4`. The original
caller's `lwz r4,count; addi r0,r4,1; stw r0,count` does not establish a second
parameter: the discarded increment naturally uses those same registers.

```cpp
self->count++;
free_laser__13TBoss2DeRolLeFPv(self);
```

Removing the unused parameter from the shared declaration, definition and call
reproduces the original receiver/velocity/hit allocation in `r29/r31/r30`.
The caller reaches 99.38865% with GC/2.6; the remaining differences are the
20-byte parameter-copy cursor and the global parameter-pointer load schedule.
GC/2.0 reproduces those too, while retaining every other exact function and
all data. This establishes a working compiler choice, not the historical
source spelling or compiler version.

The stock compiler traces explain why the extra argument mattered: its
captured old value became a coalesced frontend temporary, changing the
interference graph even though the final call still appeared to use `r4`.
Preincrement-minus-one and const-accessor candidates recovered the saved
registers but added arithmetic or loads. They are not retained. Native typed
interfaces, inline helper boundaries, pointer representations, control-flow
forms and optimizer settings were also compared against the original object.
Research included the local [word-select temporary example](twindowdd-member-standins.md),
[inline-clamp case](chr-select-slot-clamp-inline.md),
[Barba Ray pool recovery](barba-ray-table-pool-recovery.md) and
[MWCC debugger guidance](https://github.com/cadmic/mwcc-debugger).

### Color and scalar pool

The earlier inline `__rlwimi` swap is replaced by ordinary masks:

```cpp
(((color << 16) & 0xFF000000) | (color >> 16)) |
    ((color << 16) & 0x00FF0000)
```

Together with staged packing of the two primary colors, this preserves the
original rotate/insert instructions and register allocation. The compiler can
reuse the receiver register for the segment counter. Equivalent mask orders,
nested intrinsic calls, direct packing expressions, loop forms and helper
boundaries were compiled and compared; those source forms retain different
registers or rotate/mask encodings. This is a reproducible source arrangement,
not evidence of the historical helper names.

All 111 scalar values in the unit's `.sdata2` extent are distinct. Replacing
external scalar aliases with ordinary literals recovers their native pool.
Two ballistic expressions put the target-height subtraction before the
velocity product in source; their instructions remain exact, and their
literals then appear in native order. Parsing direct literal additions can
commute their operands, changing load order and FPR allocation. The shared
`add_motion_delta` helper preserves the original left operand through inline
substitution. Vector-component multiplication by one half is written as
division by two for the same reason. Explicit `-inline on` preserves all
previous matches; `-inline off` emits helper calls instead.

Research followed the [character-select inline-helper investigation](chr-select-slot-clamp-inline.md),
[operand-cost evidence](chr-select-confirm-cell-store.md),
[Barba Ray pool recovery](barba-ray-table-pool-recovery.md), and the existing
CodeWarrior debugger workflow. The local compiler-source and allocator traces
were diagnostic only; acceptance uses the pinned, unmodified GC/2.6 compiler
through wibo.

The 113 missing split exports are the 111 native scalar-pool labels and the
two compiler-generated conversion biases. `localize_split_globals.py` checked
fresh original and compiled consumer objects before marking them `scope:local`;
none has a consumer in another unit. No ranges, symbol addresses or payloads
change. The linked-unit scanner then admits the complete object. The compiler
and inline settings are recorded in the porting exceptions register; no
assembly, new intrinsic, synthetic data object or object-code patch is added.

Final validation against that fresh main baseline: `tools/check_pr.py` passes
with the source-linked DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
Gains are two exact functions, 2,272 matched code bytes, 444 matched data bytes,
and source linkage for the full 29,644 code / 3,684 data bytes. The scanner
adds this unit only; generated retention adds 109 names with no removals.
All 3,619 linked units and the unchanged code/data/function denominators pass.

The remainder below records the earlier investigation before the call boundary and compiler choice were resolved.

Base commit `0ea667b2a` (fork `main`). The two remaining approximate
functions in `psov3/pso/boss/TBoss2DeRolLe` are:

| Address | Symbol | Size | Fuzzy |
|---|---|---|---|
| `0x8002FE60` | `TBoss2DeRolLe__sub_8002FE60` | 1832 | 97.96943 |
| `0x80033684` | `update_pulsing_colors__13TBoss2DeRolLeFPv` | 440 | 95.80 |

The instruction streams already match the original almost exactly. The
remaining bytes are a callee-saved register permutation and, for
`0x8002FE60`, one scheduling decision around the `setup_instance` argument
block.

## Observed allocation

`0x8002FE60` (original vs. current source):

| Role | Original | Current |
|---|---|---|
| object pointer / `self` | `r29` | `r31` |
| `&self->vel` | `r31` | `r30` |
| `&self->hit` | `r30` | `r29` |

`0x80033684` (original vs. current source):

| Role | Original | Current |
|---|---|---|
| object pointer / `arg0` | `r29` | `r31` |
| segment target table | `r30` | `r29` |
| loop byte offset | `r31` | `r28` |
| loop counter | `r29` (reuses `self`) | `r30` |

The second function needs one fewer callee-saved register in the original
because the loop counter reuses the object register after the last read of
the object pointer. The current compiler schedules `i = 0` before that last
read, so it keeps four registers.

## Compiler experiments

All experiments used the unit's checked-in flags
(`GC/2.6`, `-O4,s`, `-inline off`, `-use_lmw_stmw on`, `-sdata2 4`) and
objdiff against the split original object `build/GPOE8P/obj/pso/boss/TBoss2DeRolLe.o`.
None produced the original allocation without changing the matching body.

- Declaring `vel`, `hit`, and `self` in different orders, initializing them
  at different points, or making `hit` local to its `case 2` block leaves the
  `0x8002FE60` allocation at `r31/r30/r29`.
- Typing the object parameter as `D_8002FE60 *`, making it a reference, or
  using the `#define self ((D_8002FE60 *)arg0)` form used elsewhere in this
  unit leaves the allocation unchanged.
- Defining both routines as actual `TBoss2DeRolLe` members (implicit `this`)
  gives the original allocation in reduced test functions, but the full
  bodies still compile to `r31/r30/r29` and `r28`-based loops. That test also
  changes the exported symbol names, so it is not a viable match.
- `#pragma opt_lifetimes`, `opt_dead_assignments`, `opt_pointer_analysis`,
  `opt_propagation`, `opt_strength_reduction`, `opt_common_subs`,
  `opt_loop_invariants`, `peephole`, `pool`, `optimization_level 1..4`,
  `opt_speed`, and `opt_space` do not change the allocation.
- `#pragma scheduling off` does produce the original allocation
  (`self`/`arg0` in `r29`, and three callee-saved registers for
  `0x80033684`), but it also drops the scheduled instruction order: the
  match falls to 78.25% and 61.86% respectively.
- `GC/2.0`, `GC/2.5`, and `GC/2.7` produce the same allocation as `GC/2.6`
  for these bodies; `GC/1.3`, `GC/1.3.2`, `GC/2.0p1`, and `GC/3.0a3` differ
  more broadly.
- `-O3,s` gives `r29` (`TBoss2DeRolLe::sub_8002FE60`, update) but loses
  level-4 transformations and the scheduled order; adding `-schedule on`
  restores the current `r31` allocation.

## Conclusion

The source forms that reproduce the original instruction order leave the
callee-saved allocation as the compiler chooses for this control-flow graph.
The only setting that reproduces the original allocation also discards the
scheduled order, so it cannot match either routine byte-for-byte. Both
functions remain at their current fuzzy scores rather than being replaced by
hand-written assembly or a body that only improves the score by changing
already-matched functions.
