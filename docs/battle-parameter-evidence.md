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
