#ifndef PSO_ENEMY_BATTLEPARAMETERS_H
#define PSO_ENEMY_BATTLEPARAMETERS_H

#include "types.h"

struct AttackParams;
struct ActorParamBlock;

// Each enemy interprets its movement parameters independently.
struct BattleMovementParams;
// The base-stat record's individual fields remain to be established.
struct BattleBaseStats;

extern "C" {
BattleMovementParams *get_battle_movement_params(s32 index);
ActorParamBlock *get_battle_resistance_params(s32 index);
AttackParams *get_battle_attack_params(s32 index);
BattleBaseStats *get_battle_base_stats(s32 index);
}

#endif
