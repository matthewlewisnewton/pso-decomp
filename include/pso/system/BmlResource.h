#ifndef PSO_SYSTEM_BML_RESOURCE_H
#define PSO_SYSTEM_BML_RESOURCE_H

#include "pso/system/BmlAccessors.h"
#include <stddef.h>

struct BmlModelEntry {
    s32 m_0;
    s32 m_4;
    NJS_OBJECT *model;
    GinjaTextureList *m_c;
};

typedef char BmlModelEntry_size[sizeof(BmlModelEntry) == 0x10 ? 1 : -1];
typedef char BmlModelEntry_model_offset[offsetof(BmlModelEntry, model) == 0x8 ? 1 : -1];
typedef char BmlModelEntry_texture_offset[offsetof(BmlModelEntry, m_c) == 0xC ? 1 : -1];

struct AnimationMotion;
struct BmlMotionEntry {
    u32 unknown;
    AnimationMotion *motion;
};

struct BmlResource {
    u8 m_0[0x42C];
    BmlModelEntry *models;
    BmlMotionEntry *motions;
};

#endif
