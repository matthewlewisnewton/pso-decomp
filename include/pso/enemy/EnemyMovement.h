#ifndef PSO_ENEMY_ENEMY_MOVEMENT_H
#define PSO_ENEMY_ENEMY_MOVEMENT_H

#include "types.h"

// Compatibility entry for target-direction movement of DD_ST-derived actors.
// The returned collision-query record is borrowed and remains opaque here.
// A later collision query may overwrite its contents.
extern "C" u8 *TObjEneEpsilon__sub_800B92F8(u8 *actor, s32 max_step, f32 distance);

#endif
