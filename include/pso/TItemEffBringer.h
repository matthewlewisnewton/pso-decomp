#ifndef PSO_TITEMEFFBRINGER_H
#define PSO_TITEMEFFBRINGER_H

#include "pso/TItemShoot.h"
#include "types.h"
#include "dolphin/mtx.h"

class TItemEffBringer : public TItemShoot {
public:
    void *m_particles[10];
    s32 m_particle_count;
    Vec m_particle_step;

    TItemEffBringer(void *owner, const Vec *pos, const Vec *dir, f32 life);
    virtual ~TItemEffBringer();
    virtual void hook();

    static void *create(u32 owner, s32 pos, s32 dir, f32 life);
};

#endif
