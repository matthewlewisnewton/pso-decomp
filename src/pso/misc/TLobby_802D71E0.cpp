#include "pso/npc/NpcAnimationBinding.h"
#include "pso/npc/NpcModelEntry.h"
#include "pso/npc/NpcModelRegistry.h"
#include "pso/npc/TObjNpcEnemy.h"

void NpcModelRegistry::register_animated_chunk(s16 id, void *model, void *texture_list,
                                               const NpcAnimationBinding *animation,
                                               f32 collision_radius, f32 vertical_offset) {
    NpcModelEntry *entry = (NpcModelEntry *)TObjNpcEnemy::insert_slot_by_id(id);
    if (entry != NULL) {
        entry->id = id;
        entry->render_mode = 1;
        entry->vertical_offset = vertical_offset;
        entry->model = model;
        entry->texture_list = texture_list;
        entry->collision_radius = collision_radius;
        entry->animation = *animation;
    }
}
