#ifndef PSO_NPC_NPC_MODEL_REGISTRY_H
#define PSO_NPC_NPC_MODEL_REGISTRY_H

#include "types.h"

struct NpcAnimationBinding;

struct NpcModelRegistry {
    static void register_animated_chunk(s16 id, void *model, void *texture_list,
                                        const NpcAnimationBinding *animation,
                                        f32 collision_radius, f32 vertical_offset);
};

#endif
