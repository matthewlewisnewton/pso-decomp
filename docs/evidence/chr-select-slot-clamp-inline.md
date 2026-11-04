# Character-select slot clamp is an inlined helper

`TAdMultiPlyChrSelectGC__sub_802C5F1C` (`0x802C5F1C`, 236 bytes,
`src/pso/ui/TAdChrSelPlyPlateGC.cpp`, the plate unit `0x802C50EC-0x802C6DD4`) fills
a 4x3 grid of selection quads. Each cell clamps the active player slot (`TAdMultiPlyChrSelectGC__data_805D67D8`)
to 3. Written out of line, the function compiles to the original except for one
register pair (99.15%). With the clamp in an `inline` helper (`clamped_active_slot`) and the
unit built with `-inline on,noauto`, it is byte-exact. That flag is the same
object as `-inline on`: the other 35 compiled functions match `-inline off`,
and the helper leaves no out-of-line copy (`.text` stays 7400 bytes; 7520 under
`-inline off`, where the helper is emitted and called).

## Allocation

| Role | Original | Out-of-line clamp | Inline helper |
|---|---|---|---|
| hoisted row pointer `self + i*96` | `r8` | `r7` | `r8` |
| cell pointer `row + j*32` | `r7` | `r8` | `r7` |
| slot load | `r0` | `r0` | `r0` |
| clamped slot | `r7` | `r8` | `r7` |

## Why only inlining gives it

Traced with the MWCC debugger (`GC/2.6`, unit flags) and read against the
[mweppc](https://github.com/doldecomp/mweppc) decompilation:

- The backend numbers GPR virtual registers as arguments first, then named locals,
  then compiler `@` temporaries, and colours the highest number first.
- Loop-invariant hoisting creates the row temporary before common-subexpression
  elimination creates the cell temporary. Out of line, the clamp's `cur`/`slot` are
  named locals and sit below both (`slot` r33, `cur` r34, cell r38, row r39), so the row
  is coloured first and takes `r7`.
- Inlining turns the helper's locals into `@` temporaries before those optimizer
  passes run. They are numbered above the row (`cur` r39, `slot` r38, row r37, cell r36),
  so the clamp takes `r0`/`r7` first and the row moves to `r8`, as in the original.

Spelling probes under `-inline on` (helper and caller otherwise as in the source):

| Helper / caller | Word diffs |
|---|---|
| `slot` declared before `cur`, caller reads `u0` first (source) | 0 |
| `cur` declared before `slot` | 5 (clamp `r0`/`r7` swapped) |
| slot passed as an argument (`if`, `?:`) | 5 |
| caller without the `u0` local, or calling the helper before reading `u0` | 5 (`f5`/`f6` swapped) |

Earlier out-of-line probes (declaration orders, signedness, loop shapes, scoped
temporaries, member forms, pragmas) are listed in the PR #294 and PR #250 attempt logs; none
moved the row pointer off `r7` without a no-op statement.

## Which unit inline flag

Same source, compared with the `-inline on` object (`.text` 7400, `.rodata` 640,
`.data` 200, `.sdata2` 8), which matches the original unit.

| Flag | Whole unit | What changed |
|---|---|---|
| `-inline on` | identical to the original | explicit inline only |
| `-inline on,noauto` | identical to `-inline on` | shipped flag. Same effect, and it states that auto-inline stays off |
| `-inline noauto` | identical to `-inline on` | relies on MWCC's default still being explicit inline |
| `-inline off` | `.text` 7520 | helper emitted; `sub_802C5F1C` is a call |
| `-inline auto` | `.text` 9448, 8 functions differ | also inlines unmarked calls |
| `-inline all` | same as `-inline auto` | |
| `-inline auto,deferred` | `.text` 10608, 15 functions differ, `.sdata2` moves | |
| `-inline deferred`, `-inline on,deferred` | each function's instructions match, `.text` and `.sdata2` bytes do not | deferred emission reorders the unit |
