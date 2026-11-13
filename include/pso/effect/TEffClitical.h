#ifndef PSO_EFFECT_TEFFCLITICAL_H
#define PSO_EFFECT_TEFFCLITICAL_H

#include "pso/effect/TEffect.h"

class TEffClitical : public TEffect {
public:
    TEffClitical(const Vec *position);
    virtual ~TEffClitical();
    virtual void run_task();
    virtual void render();
    static void create(const Vec *position);

    s32 texture_frame;
    s32 spawn_state;
};
typedef char EffCliticalSize[sizeof(TEffClitical) == 0x78 ? 1 : -1];
typedef char EffCliticalFrameOffset[offsetof(TEffClitical, texture_frame) == 0x70 ? 1 : -1];
typedef char EffCliticalSpawnOffset[offsetof(TEffClitical, spawn_state) == 0x74 ? 1 : -1];

extern "C" {
void approach_position_if_far(u8 *arg0, u8 *arg1, f32 farg0);
void init_texture_copy_rect(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
}

#endif
