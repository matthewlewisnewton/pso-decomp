#ifndef PSO_SYSTEM_BML_RESOURCE_CLASS_H
#define PSO_SYSTEM_BML_RESOURCE_CLASS_H

#include "types.h"
#include <stddef.h>

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

typedef char BmlResource_size[sizeof(BmlResource) == 0x440 ? 1 : -1];
typedef char BmlResource_models_offset[offsetof(BmlResource, models) == 0x42C ? 1 : -1];

#endif
