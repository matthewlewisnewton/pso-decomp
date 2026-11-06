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
    BmlResource(s32 kind, BmlResourceDescriptor *desc, s32 callback, s32 context, void *arena);
    ~BmlResource();
    void free_if_not_in_arena(void *ptr);
    void reset();
    void load_texture_sub(void *filename, s32 index);
    void set_flag_and_notify();
    s32 load_bin_motion(s32 name, s32 index);
    s32 load_bin_model(s32 name, s32 index);

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
typedef char BmlResource_handles_offset[offsetof(BmlResource, handles) == 0x18 ? 1 : -1];
typedef char BmlResource_handle_count_offset[offsetof(BmlResource, handle_count) == 0x418 ? 1 : -1];
typedef char BmlResource_arena_offset[offsetof(BmlResource, arena) == 0x424 ? 1 : -1];
typedef char BmlResource_models_offset[offsetof(BmlResource, models) == 0x42C ? 1 : -1];
typedef char BmlResource_motions_offset[offsetof(BmlResource, motions) == 0x430 ? 1 : -1];
typedef char BmlResource_model_count_offset[offsetof(BmlResource, model_count) == 0x434 ? 1 : -1];

// Callers allocate the storage. A constructor's implicit this, and a static
// member's emission order, both miss the original .text layout.
BmlResource *init_from_id_lists(BmlResource *self, s32 kind, u32 *models, u32 *motions, s32 on_loaded,
                                s32 on_loaded_arg, void *load_buffer);

#endif
