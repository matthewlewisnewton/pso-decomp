#ifndef PSO_NPC_NPC_MODEL_ENTRY_H
#define PSO_NPC_NPC_MODEL_ENTRY_H

#include "pso/npc/NpcAnimationBinding.h"
#include <stddef.h>

struct NpcModelEntry {
    s16 id;
    u16 render_mode;
    f32 vertical_offset;
    void *model;
    void *texture_list;
    f32 collision_radius;
    NpcAnimationBinding animation;

    void reset();
};

typedef char NpcModelEntry_size[sizeof(NpcModelEntry) == 0x24 ? 1 : -1];
typedef char NpcModelEntry_animation_offset[offsetof(NpcModelEntry, animation) == 0x14 ? 1 : -1];

#endif
