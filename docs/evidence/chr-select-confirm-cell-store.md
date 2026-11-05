# Character-select plate: typed tables, the cell store, and the float order

Base: fork `main` `f6dedd375`, merged into PR
[#214](https://github.com/matthewlewisnewton/pso-decomp/pull/214). Unit
`pso/ui/TAdMultiPlyChrSelectGC_802C50EC.cpp`, functions
`TAdMultiPlyChrSelectGC__sub_802C5688` (`0x802C5688`, 700 bytes) and
`TAdMultiPlyChrSelectGC__sub_802C6660` (`0x802C6660`, 488 bytes). Unit flags
are `GC/2.6`, `-O4,s`, `-inline off`, `-fp_contract on` (section 5 of the
porting-exceptions register). Allocation was read with the MWCC debugger
(retrowin32 + `mwcc_debugger.py`, GC/2.6) and the
[mweppc](https://github.com/doldecomp/mweppc) decompilation.

## The object is a `TAdChrSelPlyPlateGC`

The callers pass `TAdMultiPlyChrSelectGC::m_5c`. `fn_802C6F20` fills that field:
it allocates 0x538 bytes and calls `TAdChrSelPlyPlateGC__ct`. The vtable at
`lbl_804E0B10` holds `__dt__19TAdChrSelPlyPlateGCFv`, then the functions at
`0x802C6AC8` and `0x802C54C4` (`update_selection`, `update`), then
`render_shadows__7TObjectFv`. The fields that `5688` and `6660` use are now
members of `TAdChrSelPlyPlateGC`, and so are `find_active_slot`,
`find_first_open_cell`, and their callers `update_selection`,
`handle_dpad_input`, `update_option_cursor` and `move_cursor`. Those six were
renamed `__19TAdChrSelPlyPlateGC` in `symbols.txt`. They compile to the same
bytes as before, and no call site casts between the two classes.

## Typed tables

- Main declared the shown-flag and slot-id tables as `void *[4]` and reached
  them through `(s32 *)` cast macros.
- `IRO_FindAssigned` only recognises an `EOBJREF` base. A store through
  `ETYPCON(EOBJREF)` or through a pointer is therefore indirect, and it kills
  every global load (`GetExprKillsByIndirectAssignment`). The frontend then
  re-read the active player before the slot-id store. That swapped the cell
  offset and `player * 4` between `r9` and `r10`.
- Typed as `s32[4]` / `f32[4]` and indexed in place, all three stores are
  direct stores to known objects. The player load stays available, and the
  integer registers of `5688` match the original.

## Float operand order (`5688` closed, `6660` partly)

- `optimizecomm` (`CExpr.c`) runs at parse time. It swaps the operands of a
  commutative operator when `left->cost > right->cost`. It does not run on
  division. A float constant on the right of a multiply is swapped to the left;
  an integer constant on the right is left alone.
- `makediadicnode` (`CExpr2.c`) computes the costs. A global load
  (`EINDIRECT(EOBJREF)`) costs 1. A product of two such loads costs 2.
- Plain `(f32)player * row_h * scale` is therefore parsed as
  `scale * ((f32)player * row_h)`. It emits `fmuls fD, f_scale, f_product`.
- The original has `fmuls f1, f1, f2` (product first). That is what a
  non-commutative `/ 256.0f` becomes after the backend folds the division into
  a multiply by the pooled reciprocal: the dividend stays on the left.
- The pool entry is the four bytes at `0x805DE584` (`3b800000`, 1/256). The
  unit's `.sdata2` split owns them, and objdiff maps
  `TAdMultiPlyChrSelectGC__data_805DE584` to the compiler pool `@168`.
  `802C5688` is then 100% (700/700). `802C6660` moves from 95.29% to 96.07%:
  the scale load and the bias register match, and the cell store below does
  not.
- A float local for each product also puts the product on the left, and the
  review rejected those single-use locals. They are not in the source.

## Remaining gap 2: the occupied-cell store (`6660`)

- Frontend linearisation distributes `grid[row + 1][col + 1]` into
  `row * 20 + col * 4 + 0x18`. The code is `stw r5, 0x18(r3)`.
- The original adds 1 to each coordinate (`addi r0, r5, 1`; `addi r0, r3, 1`),
  then scales and adds them, and stores with `stwx`. That happens when the
  incremented coordinates are held in variables before indexing.
- `row++; col++;` on the `split_slot_index` outputs is not an alternative.
  Both are address-taken, so the increments are stored back to the stack
  (94.92%).

## Measured shapes

The source uses `/ 256.0f` for the three UV scales in each function. The review
of [#214](https://github.com/matthewlewisnewton/pso-decomp/pull/214) rejected
single-use locals, so none of the local-variable shapes below is kept.

| `5688` | `6660` | Shape |
|---|---|---|
| 100% | 96.07% | `/ 256.0f`, pool at `0x805DE584` (source) |
| 99.63% | 95.29% | plain `* data_805DE584` |
| 100% | — | `5688`: float local per product (`player0`/`v0`/`player1`/`v1`) |
| — | 96.07% | `6660`: float local per product only |
| — | 99.22% | `6660`: `row_i`/`col_i`/`occupied` cell pointer only |
| — | 100% | `6660`: both of the above |
| — | 94.92% | `6660`: `row++; col++;` before the store |

The two-step `s32 (*sel)[3] = self->sel;` that older heads used in `5688` is no
longer needed: with the typed tables, the plain `self->sel[player][f4EC]` gives
the original integer code.
