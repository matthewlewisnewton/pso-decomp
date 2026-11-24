# TBoss6Type1 `.sdata2` integer constants

`pso/boss/TBoss6Type1.cpp` is built with `-inline deferred`, so every function
is generated at the end of the file, last-defined first, and the float literal
pool follows that order. Seven `s32` values sit inside that pool and the
original reads each of them with `lwz`:

| Address | Value | Readers | Source name |
|---|---:|---|---|
| `0x805DE2D4` | 24 | `TBoss6Type1__sub_802B4A9C`, `clear_slot_array` | `boss6_type1_particle_slot_count` |
| `0x805DE3A8` | 256 | `update_sway`, `TBoss6Type1__sub_802B7D50` | `boss6_type1_sway_speed_min` |
| `0x805DE3AC` | 64 | `update_sway` | `boss6_type1_sway_speed_range` |
| `0x805DE3B0` | 20 | `update_sway`, `TBoss6Type1__sub_802B7D50` | `boss6_type1_sway_hold_min` |
| `0x805DE3B4` | 20 | `update_sway` | `boss6_type1_sway_hold_range` |
| `0x805DE3C4` | 2 | `set_motion_set`, `advance_animations`, `TBoss6Type1__sub_802B854C` | `boss6_type1_anim_count` |
| `0x805DE3C8` | 1 | `advance_animations` | `boss6_type1_main_anim` |

Each one is placed just before the literals of the first function (in
generation order) that reads it: 24 follows `0.0f` at `0x805DE2D0`; 256/64/20/20
come before `update_sway`'s 2.5/0.75/-5; 2 and 1 come before `run_task`'s -1/15.

## What MWCC does (GC/2.6 frontend)

- `CInit` marks a `const` scalar with a constant initializer as inline data.
  `CExpr_RewriteConst` replaces any later read of it by the value (`li`).
- An inline-data constant with external linkage, or whose address was already
  taken, is written out when it is defined (`CInit_ExportConst`), at parse
  time. Under deferred generation that puts it ahead of every literal.
- An internal-linkage one is written out only when a function that still
  refers to it is generated (`CInline_ExportCheck`), i.e. in generation order.

## Forms measured

Probe files compiled with the unit's flags:

| Form | Reads | Pool position |
|---|---|---|
| `static const s32 N = 24;` before use (file or class scope, `this->N`) | folded to `li` | not emitted |
| `const int` read as `long` | folded | not emitted |
| class `static const s32 N;` defined after use | `lwz` | offset 0 |
| `extern const s32 N;` then `const s32 N = 24;` after use (also unnamed namespace, `extern "C"`, `__declspec(section)`) | `lwz` | offset 0 |
| `static const s32 N;` forward declaration | error: needs initializer | — |
| `extern const s32 N;` then `static const s32 N = 24;` after use | `lwz` | first use in generation order |

Only the last form gives the original object. Standard C++ rejects a `static`
definition after an `extern` declaration; MWCC accepts it without a diagnostic.
It is recorded in [porting-exceptions.md](../porting-exceptions.md) section 5.

## Ownership

Every reference to `0x805DE2C8`..`0x805DE3F0` is in `TBoss6Type1`. The two
`s8[2]` tables at `0x805DE2C8` (`{0x12, 10}`) and `0x805DE2CC` (`{0x12, -2}`)
are ordinary data, written at parse time ahead of the first literal; the floats
at `0x805DE3CC`..`0x805DE3EC` are `run_task`, `render_shadows`,
`TBoss6Type1__sub_802B8A70`, `TBoss6Type1__sub_802B8BB4`,
`TBoss6Type1__sub_802B8E1C`, `randomize_attack`, `TBoss6Type1__sub_802B909C` and
`set_sync_data` literals in that order. The split's `.sdata2` is
`0x805DE2C8`..`0x805DE3F0`; the compiled section is 296 bytes and identical.
