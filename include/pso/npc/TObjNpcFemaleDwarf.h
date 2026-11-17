#ifndef PSO_NPC_TOBJNPCFEMALEDWARF_H
#define PSO_NPC_TOBJNPCFEMALEDWARF_H

#include "types.h"
#include "pso/npc/TUnk_804A8640.h"

struct BmlResource;

struct TObjNpcFemaleDwarf : public TUnk_804A8640 {
    virtual ~TObjNpcFemaleDwarf();
    static void unload_static_data();
    static void load_static_resource();
};

typedef char TObjNpcFemaleDwarf_size[sizeof(TObjNpcFemaleDwarf) == 0x3B8 ? 1 : -1];

extern "C" {
u8 *TObjNpcFemaleDwarf__ct(u8 *arg0, s32 arg1, s32 arg2);
void *TObjNpcFemaleFat__create(void *arg0);
void *__dt__18TObjNpcFemaleDwarfFv(void *arg0, s16 arg1);
}

// --- C functions defined in TObjNpcFemaleDwarf.cpp ---
extern "C" {
u8 *TObjNpcFemaleDwarf__ct(u8 *arg0, s32 arg1, s32 arg2);
void *TObjNpcFemaleFat__create(void *arg0);
void *__dt__18TObjNpcFemaleDwarfFv(void *arg0, s16 arg1);
}
// --- end of C functions

extern "C" {
extern BmlResource *TObjNpcFemaleDwarf__static_data;
}

#endif
