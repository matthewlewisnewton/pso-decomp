#ifndef PSO_SYSTEM_BML_RESOURCE_H
#define PSO_SYSTEM_BML_RESOURCE_H

#include "types.h"

struct BmlModelEntry {
    s32 m_0;
    s32 m_4;
    s32 model;
    s32 m_c;
};

struct AnimationMotion;
struct BmlMotionEntry {
    u32 unknown;
    AnimationMotion *motion;
};

struct BmlResourceDescriptor;
struct BmlResource {
    BmlResource(s32 kind, BmlResourceDescriptor *descriptor, s32 callback, s32 context, void *arena);
    ~BmlResource();

    u32 flags;
    s32 loaded_models;
    s32 loaded_motions;
    s32 loaded_textures;
    s32 load_state;
    s32 unknown_14;
    s32 handles[256];
    s32 handle_count;
    s32 callback;
    s32 callback_context;
    void *arena;
    s32 arena_offset;
    BmlModelEntry *models;
    BmlMotionEntry *motions;
    s32 model_count;
    s32 motion_count;
    s32 expected_textures;
};

extern "C" s32 get_bml_model(BmlResource *resource, s32 index);

#endif
