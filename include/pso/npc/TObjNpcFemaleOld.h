#ifndef PSO_NPC_TOBJNPCFEMALEOLD_H
#define PSO_NPC_TOBJNPCFEMALEOLD_H

#include "types.h"
#include "pso/npc/TUnk_804A8640.h"

struct BmlResource;

struct TObjNpcFemaleOld : public TUnk_804A8640 {
    virtual ~TObjNpcFemaleOld();
    static void destroy_static_instance();
    static void load_resource_instance();
};

typedef char TObjNpcFemaleOld_size[sizeof(TObjNpcFemaleOld) == 0x3B8 ? 1 : -1];

extern "C" {
u8 *TObjNpcFemaleOld__ct(u8 *arg0, s32 arg1, s32 arg2);
void *TObjNpcFemaleTall__create(void *arg0);
void *__dt__16TObjNpcFemaleOldFv(void *arg0, s16 arg1);
}

// --- C functions defined in TObjNpcFemaleOld.cpp ---
extern "C" {
u8 *TObjNpcFemaleOld__ct(u8 *arg0, s32 arg1, s32 arg2);
void *TObjNpcFemaleTall__create(void *arg0);
void *__dt__16TObjNpcFemaleOldFv(void *arg0, s16 arg1);
}
// --- end of C functions

extern "C" {
extern BmlResource *TObjNpcFemaleOld__static_instance;
}

#endif
