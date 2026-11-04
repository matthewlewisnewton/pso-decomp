# Character-select slot clamp (`sub_802C5F1C`)

`TAdMultiPlyChrSelectGC__sub_802C5F1C` (`0x802C50EC` unit, 236 bytes) fills a
4×3 grid of selection quads. Each cell clamps the active player slot
(`TAdMultiPlyChrSelectGC__data_805D67D8`) to 3. The source clamp is the
straightforward `idx = 3; cnt = slot; if (cnt < 4) idx = cnt;` inside the
inner loop. Under the unit's normal flags (`GC/2.6`, `-O4,s`, `-inline off`)
that compiles to the original instruction stream except for one register
pair.

## The remaining gap

| Role | Original | This source |
|---|---|---|
| hoisted row pointer `self + i*96` | `r8` | `r7` |
| cell pointer `row + j*32` | `r7` | `r8` |
| slot load | `r0` | `r8` |
| clamped slot (`li 3` / `mr`) | `r7` | `r0` |

Eleven instruction words differ, all register fields. Float registers, the
CTR loop, and the cursor epilogue match. Objdiff scores the function
99.15254%. The unit's other compiled functions are unchanged.

MWCC's frontend hoists `self + i*96` before it colours the clamp values.
Named locals are numbered below compiler temporaries, so the row temporary
is coloured first and takes `r7`. A `static inline` helper does put the row
in `r8` and the cell in `r7`, but only when the unit is built with
`-inline on`: that flag is what actually inlines the helper, turning its
locals into temporaries created before the hoist. `-inline off` (this
project's game-code default, and the compiler's `dontinline`) leaves the
helper as a call and the function grows to 332 bytes. Matt rejected a
unit `-inline on` override for this PR on 2026-11-04, so the helper is not
in the source.

Comma expressions and a ternary written before the stores lower to the same
11-word swap. A `&&` form does move the row to `r8`, and it also emits the
boolean's extra `li` / `clrlwi.` / `beq` (252 bytes). No flag-free spelling
closes the pair without a different instruction stream.
