#ifndef PSO_ENEMY_MOJARESOURCESTATE_H
#define PSO_ENEMY_MOJARESOURCESTATE_H

#include "types.h"

struct BattleBaseStats;
struct AttackParams;
struct ActorParamBlock;
struct BattleMovementParams;
struct BmlResource;
struct SampledMotionPoints;

extern "C" {
extern BattleBaseStats **lbl_805D50C8;
extern AttackParams **lbl_805D50CC;
extern ActorParamBlock **lbl_805D50D0;
extern BattleMovementParams **lbl_805D50D4;
extern BmlResource *lbl_805D50D8;
extern SampledMotionPoints *lbl_805D50DC;
}

#endif
