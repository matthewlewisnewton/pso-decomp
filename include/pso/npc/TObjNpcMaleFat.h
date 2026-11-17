#ifndef PSO_NPC_TOBJNPCMALEFAT_H
#define PSO_NPC_TOBJNPCMALEFAT_H

#include "types.h"
#include "pso/npc/TUnk_804A9F50.h"

struct BmlResource;

struct TObjNpcMaleFat : public TUnk_804A9F50 {
    virtual ~TObjNpcMaleFat();
    static void free_static_model();
    static void load_static_resource();
};

typedef char TObjNpcMaleFat_size[sizeof(TObjNpcMaleFat) == 0x3B8 ? 1 : -1];

extern "C" {
u8 *TObjNpcMaleFat__ct(u8 *arg0, s32 arg1, s32 arg2);
void *TObjNpcMaleMacho__create(void *arg0);
void *__dt__14TObjNpcMaleFatFv(void *arg0, s16 arg1);
}

// --- C functions defined in TObjNpcMaleFat.cpp ---
extern "C" {
u8 *TObjNpcMaleFat__ct(u8 *player, s32 arg1, s32 arg2);
void *TObjNpcMaleMacho__create(void *arg0);
void *__dt__14TObjNpcMaleFatFv(void *arg0, s16 arg1);
}
// --- end of C functions

extern "C" {
extern BmlResource *TObjNpcMaleFat__static_model_resource;
}

#endif
