#ifndef PSO_MISC_TUNK_8048E778_H
#define PSO_MISC_TUNK_8048E778_H
#include "types.h"
#include <stddef.h>
#include "pso/misc/TUnk_8048E728.h"

class TUnk_8048E778 : public TUnk_8048E728 {
public:
    virtual ~TUnk_8048E778();
    virtual void run_task();
    void *init_particle_random_spread(void *, void *, void *);
    void retire_ballistic_particle_if_done();
    void draw_sprite_quad(s32);
    virtual void render();
    f32 motion_frame_step;     // 0xC0
    Vec velocity;             // 0xC4, step after rotation
};

typedef char TUnk_8048E778_size[sizeof(TUnk_8048E778) == 0xD0 ? 1 : -1];
typedef char TUnk_8048E778_motion_step_offset[offsetof(TUnk_8048E778, motion_frame_step) == 0xC0 ? 1 : -1];
typedef char TUnk_8048E778_velocity_offset[offsetof(TUnk_8048E778, velocity) == 0xC4 ? 1 : -1];

#endif
