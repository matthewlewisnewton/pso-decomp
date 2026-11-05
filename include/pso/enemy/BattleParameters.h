#ifndef PSO_ENEMY_BATTLEPARAMETERS_H
#define PSO_ENEMY_BATTLEPARAMETERS_H

#include "types.h"

struct AttackParams;
struct ActorParamBlock;

// Each enemy interprets its movement parameters independently.
struct BattleMovementParams {
    f32 m_00;
    f32 m_04;
    f32 m_08;
    f32 m_0c;
    f32 m_10;
    f32 m_14;
    s32 m_18;
    s32 m_1c;
    s32 m_20;
    s32 m_24;
    s32 m_28;
    s32 m_2c;
};
// The base-stat record's individual fields remain to be established.
struct BattleBaseStats;

extern "C" {
BattleMovementParams *get_battle_movement_params(s32 index);
ActorParamBlock *get_battle_resistance_params(s32 index);
AttackParams *get_battle_attack_params(s32 index);
BattleBaseStats *get_battle_base_stats(s32 index);
}

#endif
