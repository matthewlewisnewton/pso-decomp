# Character-select plate: typed tables, the cell store, and the float order

Base: #214 merged as `ee5fa809f`; this evidence is retained by #250 after
folding the standalone unit into `pso/ui/TAdChrSelPlyPlateGC.cpp`. Functions
`TAdMultiPlyChrSelectGC__sub_802C5688` (`0x802C5688`, 700 bytes),
`TAdMultiPlyChrSelectGC__sub_802C5F1C` (`0x802C5F1C`, 236 bytes), and
`TAdMultiPlyChrSelectGC__sub_802C6660` (`0x802C6660`, 488 bytes). All three
match. Unit flags are `GC/2.6`, `-O4,s`, `-inline on`, `-fp_contract on`
(section 5 of the porting-exceptions register). Allocation was read with the MWCC debugger
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
  `TAdMultiPlyChrSelectGC__data_805DE584` to the compiler pool `@175`.
  `802C5688` is then 100% (700/700). `802C6660` moves from 95.29% to 96.07%
  until the cell store below is written through the shared helper.
- A float local for each product also puts the product on the left, and the
  review rejected those single-use locals. They are not in the source.

## Occupied-cell store (`6660` closed)

- `grid[row + 1][col + 1] = -1` linearises to `row * 20 + col * 4 + 0x18`
  and stores with `stw r5, 0x18(r3)`. The original adds 1 first
  (`addi r0, r5, 1`; `addi r0, r3, 1`), then scales, and stores with `stwx`.
- `row` and `col` in `802C6660` are the 0-based quad indices (`quad[row][col]`).
  The grid has a one-cell border, so the occupied cell is one past each.
  `802C5688` already holds those grid coordinates (`sel + 1`, `f4EC + 1`) and
  uses them for the read and the write.
- Both stores go through `static inline void mark_grid_cell_occupied(s32 row, s32 col)`,
  which is `grid[row][col] = -1`. `-inline on` (the same flag that inlines the
  slot clamp) evaluates `802C6660`'s `row + 1, col + 1` arguments before the
  store, which is the `addi` / `mulli 0x14` / `stwx`. `802C5688` passes the
  coordinates it already has and stays 700/700. There is no out-of-line copy.
- `row++; col++;` on the `split_slot_index` outputs is not an alternative.
  Both are address-taken, so the increments are stored back to the stack
  (94.92%). A `row_i`/`col_i` local used only for that store matches and was
  rejected as steering; it is not in the source.

## Measured shapes

The source uses `/ 256.0f` for the three UV scales in each function. The review
of [#214](https://github.com/matthewlewisnewton/pso-decomp/pull/214) rejected
single-use locals, so none of the local-variable shapes below is kept.

| `5688` | `6660` | Shape |
|---|---|---|
| 100% | 100% | `/ 256.0f` plus `mark_grid_cell_occupied` (source) |
| 100% | 96.07% | `/ 256.0f`, direct `grid[row + 1][col + 1] = -1` |
| 99.63% | 95.29% | plain `* data_805DE584` |
| 100% | — | `5688`: float local per product (`player0`/`v0`/`player1`/`v1`) |
| — | 96.07% | `6660`: float local per product only |
| — | 99.22% | `6660`: `row_i`/`col_i`/`occupied` cell pointer only |
| — | 100% | `6660`: both of the above |
| — | 94.92% | `6660`: `row++; col++;` before the store |

The two-step `s32 (*sel)[3] = self->sel;` that older heads used in `5688` is no
longer needed: with the typed tables, the plain `self->sel[player][f4EC]` gives
the original integer code.

## Earlier fold (#250)

The folded unit owns `.data 0x804E0A48-0x804E0B10` and only the eight bytes
`.sdata2 0x805DE580-0x805DE588`: the local 0.53 constant and the 1/256
reciprocal. Earlier pool entries remain externs in the preceding unit. The
source retains #214's `alpha`, `home[4][3]`/`ox`/`oy`, and
`mark_grid_cell_occupied` forms. All 36 functions, 7400 code bytes and 848
data bytes match; the unit links from source. The constructor at `0x802C6DD4` remained a separate unmatched unit in #250.

## Constructor and factory

The factory at `0x802C6F20` passes the task layer and a two-float screen position.
The constructor calls `TObject(TObject *)`, copies the position to offset `0x4A4`,
initializes three columns of each player's selection and cursor state, and resets the
ready-tag and slot tables. The constructor and destructor store the same vtable
address. Its slots resolve to the plate destructor, `run_task`, `render`, and the
inherited `TObject::render_shadows`.

Immediate emission matches the loop bodies but addresses the vtable and the two
ready-tag arrays separately. The original loads a single `.data` base at
`0x804E0A48` before calling the base constructor. The vtable and both arrays are
then base-relative at `+0xC8`, `+0x98`, and `+0xA8`. Deferred emission recovers
that base, as in the earlier plate experiment (`78c6cf717c`) and the
[TBoss8Dragon recovery](https://github.com/matthewlewisnewton/pso-decomp/pull/302).
Keeping the active player in a local passes the same word to the slot helper
after storing it in the plate, avoiding a second load.

The plate retains explicit inlining with `-inline on,deferred` and its existing
`-fp_contract on`. Enabling deferred emission on ascending definitions matched
the constructor but reversed the function order and exchanged the two
`.sdata2` literals. Reversing the definitions restores both orders. String
pooling and explicit `-pooldata on` did not affect the constructor difference.
The resulting object covers all 38 functions and owns 7,836 bytes of code and
900 bytes of data across five sections. The class-name pointer occupies four
bytes in `.sdata`. The next four bytes are alignment padding.


## Native float-pool recovery

On fork base `4b40cbeb933f52d6a86d9530abbefec9ec1f1028`, the plate's 38
functions and 900 data bytes already matched and linked. Its first eight float
constants, however, came from `TAdMultiPlyChrSelectGC_literals.s`, a separate
32-byte assembly-only unit at `805DE560..805DE580`. All references in the fresh
split and compiled object inventory belong to `TAdChrSelPlyPlateGC.cpp`.
The assembly loads identify the half-up alpha bias, alpha scale, horizontal
translation, zero, depth, fade increment, maximum alpha and cursor margin.

The first C++ experiment defined those eight exported constants in the plate
source. All 38 functions still matched, but CodeWarrior emitted the eight named
floats followed by another anonymous copy: `.sdata2` grew from 40 to 72 bytes.
The [conversion-pool investigation](conversion-pool-constants.md#duplicate-copies-that-hide-a-size-mismatch)
describes this duplicate-definition failure and the native literal solution.
Replacing the references with `0.5f`, `255.0f`, `-206.0f`, `0.0f`, `0.54f`,
`0.16666667f`, `1.0f` and `16.0f` emits exactly the original pool, followed by
the existing `0.53f` and `1/256` entries. No new compiler override or pragma is
needed. The existing deferred definition order remains necessary.

The split now assigns `805DE560..805DE588` to the plate. The eight old exported
names are local after `localize_split_globals.py` checked the fresh generated
configuration's original and compiled consumer objects and found no foreign
references. The assembly source and its link-list entry are removed.
This consolidates two previously linked units; it adds no function matches or
linked bytes and does not claim recovery of the historical translation unit.

Validation: all 38 functions (7,836 code bytes) and all 932 data bytes match.
Every allocated section's raw bytes, size and alignment equal the fresh original
split: `.text` 7,836/4, `.rodata` 640/8, `.data` 224/8, `.sdata` 4/8,
`.sbss` 24/8 and `.sdata2` 40/8 (size/alignment). The generated linker inputs
select the compiled plate object. The complete linked DOL retains SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`; the address-based report comparison
loses no functions, code or data. Linked-unit and retention checks pass with
3,625 linked units and the same 19,276 retention entries.
