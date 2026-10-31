# Battle parameter tables

The four indexed getters in `pso/enemy/BattleParameters.h` return pointers into
separate battle parameter tables selected when the tables are loaded. Their
wrappers forward the current difficulty and index to the underlying lookups;
the lookups index the loaded table and do not check bounds. The loaded records
are mutable. The original code uses 96 entries per table.

| Getter | Record stride | Shared type |
| --- | --- | --- |
| `get_battle_movement_params` | `0x30` | `BattleMovementParams` (opaque) |
| `get_battle_resistance_params` | `0x20` | `ActorParamBlock` |
| `get_battle_attack_params` | `0x30` | `AttackParams` |
| `get_battle_base_stats` | `0x24` | `BattleBaseStats` (opaque) |

The movement records are interpreted differently by different enemies, so a
single universal field layout is not established. The base-stat stride is
known, but its fields and original source-level type name need further work.
The index's original signedness and the ownership of the loaded storage are
also not established. Existing callers still use integer-held addresses and
local overlays in places; these declarations describe the lookup interface,
not a proof of those overlays' C++ object lifetime or aliasing semantics.

`TObjEneDD::reset_hp` accepts base, attack, and resistance records in that
order and forwards them to the enemy combat-stat binding before copying HP to
its reference HP. Callers also pass null for individual records, including
attack-only updates. For a null argument, the binding retains the installed
record, or returns early if no record is installed; `reset_hp` still copies
current HP afterward. The binding itself still exposes byte pointers. Legacy
hand-mangled calls to `reset_hp` remain compatibility declarations, including
some integer return types and an extra argument at one call site; recovering
the member signature does not make those declarations type-safe.

`TObjEneDD::reload_stats_keep_hp_tp` takes the same three records in the same
order. It saves HP, maximum HP, TP and maximum TP, calls the binding, and
restores all four fields even if the binding returns early. Existing callers
still use hand-mangled compatibility declarations with integer or `void *`
parameters and, in most cases, an integer return; this member signature does
not make those declarations type-safe.
