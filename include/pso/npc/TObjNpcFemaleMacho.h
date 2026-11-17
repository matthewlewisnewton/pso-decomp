#ifndef PSO_NPC_TOBJNPCFEMALEMACHO_H
#define PSO_NPC_TOBJNPCFEMALEMACHO_H

#include "types.h"
#include "pso/npc/TUnk_804A8640.h"

struct BmlResource;

struct TObjNpcFemaleMacho : public TUnk_804A8640 {
    virtual ~TObjNpcFemaleMacho();
    static void close_dialog_window();
    static void load_resources();
};

typedef char TObjNpcFemaleMacho_size[sizeof(TObjNpcFemaleMacho) == 0x3B8 ? 1 : -1];

extern "C" {
u8 *TObjNpcFemaleMacho__ct(u8 *arg0, s32 arg1, s32 arg2);
void *TObjNpcFemaleOld__create(void *arg0);
void *__dt__18TObjNpcFemaleMachoFv(void *arg0, s16 arg1);
}

// --- C functions defined in TObjNpcFemaleMacho.cpp ---
extern "C" {
u8 *TObjNpcFemaleMacho__ct(u8 *arg0, s32 arg1, s32 arg2);
void *TObjNpcFemaleOld__create(void *arg0);
void *__dt__18TObjNpcFemaleMachoFv(void *arg0, s16 arg1);
}
// --- end of C functions

extern "C" {
extern BmlResource *TObjNpcFemaleMacho__lobby_resource;
}

#endif
