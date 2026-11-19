#ifndef PSO_EFFECT_GROUND_EFFECTS_H
#define PSO_EFFECT_GROUND_EFFECTS_H

#include "types.h"

struct Vec;

extern "C" {
void spawn_ground_effect(const Vec *position, s32 lifetime);
void spawn_effect_at_ground(const Vec *position, s32 lifetime);
}

#endif
