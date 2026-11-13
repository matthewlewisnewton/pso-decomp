#ifndef PSO_ENEMY_SLIME_SLIMEANIMATIONSTATE_H
#define PSO_ENEMY_SLIME_SLIMEANIMATIONSTATE_H

#include "types.h"

struct TObjEneSlimeOne;

struct SlimeMotionInfo {
    u8 pad0[4];
    u32 frame_count;
};

struct SlimeAnimationState {
    void draw(s32 deferred);
    void advance();
    s32 is_finished();
    void set_state(s32 state);

    TObjEneSlimeOne *owner;
    s32 state;
    s32 model;
    s32 texture_list;
    SlimeMotionInfo *motion;
    s32 shape_motion;
    s32 second_model;
    s32 second_texture_list;
    SlimeMotionInfo *second_motion;
    u8 pad24[4];
    f32 speed;
    f32 frame_count;
    f32 frame;
};

typedef char SlimeAnimationStateSize[sizeof(SlimeAnimationState) == 0x34 ? 1 : -1];

#endif
