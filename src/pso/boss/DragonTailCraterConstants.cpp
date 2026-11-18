#include "pso/boss/DragonTailCraterConstants.h"

const f32 dragon_tail_hit_scale = 1.0f;
// The yaw constant starts at the next eight-byte boundary in the original pool.
const f32 dragon_crater_yaw_units_per_turn ATTRIBUTE_ALIGN(8) = 65536.0f;
const f32 dragon_crater_random_scale = 1.0f / 32768.0f;
