#include "pso/misc/ParticleFactory.h"
#ifndef PSO_UNK_TEXT_80087278_H
#define PSO_UNK_TEXT_80087278_H

#include "types.h"

class TParticleCtrl;

extern "C" {
TParticleCtrl *spawn_continuous_particle_effect_with_flags(void *parent, s32 idx, s32 flags);

void *spawn_particle_effect_with_flags(void *pos, s32 id, s32 flags);
}

#endif
