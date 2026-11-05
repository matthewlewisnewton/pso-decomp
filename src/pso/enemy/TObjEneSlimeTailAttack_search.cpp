#include "pso/enemy/TObjEneSlimeTailAttack.h"

extern "C" s32 find_nearest_hittable_enemy__10TObjPlayerFiPvf(void *, int, f32);

// Kept adjacent to the main Slime unit: the original emits this method after
// the compiler-generated state-table initializer.
int TObjEneSlimeTailAttack::find_nearest_enemy_with_flag(f32 distance) {
    u16 target;
    actorFlags |= 0x02000000;
    target = find_nearest_hittable_enemy__10TObjPlayerFiPvf(this, 0, distance);
    actorFlags &= ~0x02000000;
    return target;
}
