# TBoss2DeRolLe update and pulsing-color register allocation

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


## Complete-unit recovery

The earlier conclusion records the limited source forms tested at that checkpoint.
The completed implementation uses the existing `EffectGeometryParameters` record
and preserves the runtime parameter table's mutability. Under MWCC, five
four-byte `__memcpy` operations copy the twenty-byte template into a live record.
Unsigned numerical cursors reproduce the original two eight-byte iterations and
four-byte tail without forming pointers before either object. The mutable
parameter-table pointer is loaded before the tail copy, then its power value
overrides `field_4`. The other-compiler branch uses ordinary aggregate copying.
This avoids accessing float storage through integer lvalues. The record and
copy boundary follow the repository's typed Dragon attack parameters.

The color update decomposes packing into unsigned channel values. Its first
half-word swap retains one guarded `__rlwimi`; the other-compiler branch expresses
the same insert with masks and shifts. This replaces two inherited unguarded
inserts. Exhaustive byte-channel comparison covers the portable first-color
result `(v / 4) << 16 | 0xff00 | v` for all 256 channel values.

With GC/2.6 and the integrated unit flags, isolated full-unit variants reproduce
these results against the split original:

| Source form | Laser action `8002FE60` | Color update `80033684` |
|---|---:|---:|
| Completed implementation | 100% | 100% |
| Ordinary aggregate copy in the laser action | 99.38865% | 100% |
| Ordinary first-color masks in the MWCC path | 100% | 99.27273% |

The constructor, destructor and five virtual overrides use the native class
interface. The compiler emits the vtable; no hand-written table remains.
Reverse definitions with `-inline off,deferred` place the vtable at
`.data+0x3f8`, ahead of the switch tables. This follows the existing
[compiler-emission investigation](compiler-emission-evidence.md).
`-str reuse,readonly` places `deldeath.adx` in the owned `.rodata` pool.
Scalar literals and expression ordering recover the full constant pool.
These settings are matching constraints, not evidence of original source order.
The existing provisional offset views and legacy helper interfaces remain;
this change does not claim a complete typed layout for every boss field.

Integration on fork main `c17ee9946c4d6887e37a01c390320bb25e9a793c`
preserves the newer typed `TBoss2Fin` construction. All 110 functions,
29,644 code bytes and 3,684 data bytes match. All five allocated sections
have identical raw bytes, sizes and alignment; all 1,706 relocations into
those sections have identical offsets, types and resolved target addresses.
The 114 localized anonymous constants/string labels have no foreign consumers
in the fresh 8,552-object compiled/original inventory. Splits are unchanged.
The actual linker input is the compiled object, and the final DOL retains
SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
