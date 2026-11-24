# battle-params

Renamed the four per-enemy battle parameter getters (0x8001E1D8, 0x8001E210, 0x8001E248,
0x8001E280) from `TLobby::dispatch_shared_handler_a`, `register_object`,
`dispatch_shared_handler_b` and `register_boss` to the fork's `get_battle_movement_params`,
`get_battle_resistance_params`, `get_battle_attack_params` and `get_battle_base_stats`, declared
in `include/pso/enemy/BattleParameters.h` (copied from the fork unchanged).

- `AttackParams` and `ActorParamBlock` are structs in upstream (`pso/player/PlayerAttackParams.h`),
  so the header's forward declarations agree.
- The four definitions in `TLobby_8001D6A0.cpp` now return the typed pointers via a cast.
- Typed results no longer convert implicitly to `s32`/`void *`/`f32 *`; the call sites got the
  smallest cast that restores the old type. Pointer arithmetic on `BattleMovementParams *` scales
  by the struct size (0x30), so `TBoss4Type3.cpp` needs `(u8 *)` before `+ offset`, and its
  `*get_battle_base_stats(...)` read is `*(s16 *)` (the old local declaration returned `s16 *`).
  Both showed as one lost match until fixed.
- Local extern declarations of the mangled names were removed from about 40 files.
- No config file (`config.yml`, `splits.txt`) mentioned the old names. Methods named
  `register_object` on other classes (`TObjPlayer::register_object` and others) are untouched.
