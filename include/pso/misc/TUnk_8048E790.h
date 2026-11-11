#ifndef PSO_MISC_TUNK_8048E790_H
#define PSO_MISC_TUNK_8048E790_H
#include "types.h"
#include "pso/misc/TUnk_8048E728.h"

class TUnk_8048E790 : public TUnk_8048E728 {
public:
    virtual ~TUnk_8048E790();
    virtual void run_task();
    void *init_random_particle(void *, void *, void *, void *);
    void retire_orbit_particle();
    virtual void render();
    f32 motion_step;            // 0xC0
    f32 center_x, center_z;      // 0xC4, 0xC8
    u8 unk_CC[0x4];
    f32 radius;                 // 0xD0
    f32 vertical_offset;        // 0xD4
    s32 orbit_angle;            // 0xD8
    s32 m_dc;
};

typedef char OrbitParticleSize[sizeof(TUnk_8048E790) == 0xE0 ? 1 : -1];

#endif
