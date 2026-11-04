# Character-select slot clamp is an inlined helper

`TAdMultiPlyChrSelectGC__sub_802C5F1C` (`0x802C5F1C`, 236 bytes,
`src/pso/ui/TAdChrSelPlyPlateGC.cpp`, the plate unit `0x802C50EC-0x802C6DD4`) fills
a 4x3 grid of selection quads. Each cell clamps the active player slot (`TAdMultiPlyChrSelectGC__data_805D67D8`)
to 3. Written out of line, the function compiles to the original except for one
register pair (99.15%). With the clamp in an `inline` helper (`clamped_active_slot`) and the
unit built with `-inline on`, it is byte-exact. The unit's other 35 compiled functions
are identical under `-inline off` and `-inline on`, and the `static inline` helper
leaves no out-of-line copy (`.text` stays 7400 bytes; 7520 under `-inline off`, where
the helper is emitted and called). `-inline noauto,level=1` gives the same object.

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
