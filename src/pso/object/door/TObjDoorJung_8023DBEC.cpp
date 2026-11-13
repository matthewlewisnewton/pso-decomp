#include "types.h"
#include "pso/object/door/TObjDoorJung.h"
#include "pso/render/GinjaMaterialState.h"

extern "C" {
s32 strcmp(const char *, const char *);
void set_material_texture_slot(void *);

s32 GinjaTextureList::find_entry_by_name(const char *name) {
    GinjaTextureEntry *ents;
    u32 i;
    if (this != NULL) {
        ents = entries;
        if (ents != NULL) {
            for (i = 0; i < count; i++) {
                if (strcmp(name, ents[i].name) == 0) {
                    return i;
                }
            }
        }
    }
    return -1;
}

void TObjDoorJung::free_children(void *arg1) {
    if (this->m_prev != NULL) {
        set_material_texture_slot(this->m_prev);
    }
    if (this->m_next != NULL) {
        ((void (*)(void *, void *))set_material_texture_slot)(this->m_next, arg1);
    }
}

}
