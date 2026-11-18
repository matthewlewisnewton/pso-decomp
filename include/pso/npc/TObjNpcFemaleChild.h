#ifndef PSO_NPC_TOBJNPCFEMALECHILD_H
#define PSO_NPC_TOBJNPCFEMALECHILD_H

#include "types.h"
#include "pso/npc/TUnk_804A8640.h"

struct BmlResource;

struct TObjNpcFemaleChild : public TUnk_804A8640 {
    virtual ~TObjNpcFemaleChild();
    static void release_static_instance();
    static void load_shared_resource();
};

typedef char TObjNpcFemaleChild_size[sizeof(TObjNpcFemaleChild) == 0x3B8 ? 1 : -1];

extern "C" {
u8 *TObjNpcFemaleChild__ct(u8 *arg0, s32 arg1, s32 arg2);
void *TObjNpcFemaleDwarf__create(void *arg0);
void *__dt__18TObjNpcFemaleChildFv(void *arg0, s16 arg1);
}

// --- C functions defined in TObjNpcFemaleChild.cpp ---
extern "C" {
u8 *TObjNpcFemaleChild__ct(u8 *arg0, s32 arg1, s32 arg2);
void *TObjNpcFemaleDwarf__create(void *arg0);
void *__dt__18TObjNpcFemaleChildFv(void *arg0, s16 arg1);
}
// --- end of C functions

extern "C" {
extern BmlResource *TObjNpcFemaleChild__static_instance;
}

#endif
