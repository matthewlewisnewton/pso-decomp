#ifndef PSO_NPC_TOBJNPCFEMALEFAT_H
#define PSO_NPC_TOBJNPCFEMALEFAT_H

#include "types.h"
#include "pso/npc/TUnk_804A8640.h"

struct BmlResource;

struct TObjNpcFemaleFat : public TUnk_804A8640 {
    virtual ~TObjNpcFemaleFat();
    static void free_static_model();
    static void load_static_resource();
};

typedef char TObjNpcFemaleFat_size[sizeof(TObjNpcFemaleFat) == 0x3B8 ? 1 : -1];

extern "C" {
u8 *TObjNpcFemaleFat__ct(u8 *arg0, s32 arg1, s32 arg2);
void *TObjNpcFemaleMacho__create(void *arg0);
void *__dt__16TObjNpcFemaleFatFv(void *arg0, s16 arg1);
}

// --- C functions defined in TObjNpcFemaleFat.cpp ---
extern "C" {
u8 *TObjNpcFemaleFat__ct(u8 *arg0, s32 arg1, s32 arg2);
void *TObjNpcFemaleMacho__create(void *arg0);
void *__dt__16TObjNpcFemaleFatFv(void *arg0, s16 arg1);
}
// --- end of C functions

extern "C" {
extern BmlResource *TObjNpcFemaleFat__static_model;
}

#endif
