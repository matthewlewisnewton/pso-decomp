#ifndef PSO_MISC_PARTICLEFACTORY_H
#define PSO_MISC_PARTICLEFACTORY_H
#include "types.h"
struct Vec;
class TParticleCtrl;
extern "C" {
TParticleCtrl *spawn_particle_effect(const Vec *position, s32 id);
}
#endif
