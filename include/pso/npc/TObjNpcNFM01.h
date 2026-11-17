#ifndef PSO_NPC_TOBJNPCNFM01_H
#define PSO_NPC_TOBJNPCNFM01_H

#include "types.h"
#include "pso/npc/TUnk_804A9F50.h"

struct GinjaTextureList;

struct TObjNpcNFM01 : public TUnk_804A9F50 {
    virtual ~TObjNpcNFM01();
    static void free_resources();
    static void load_resources();
};

typedef char TObjNpcNFM01_size[sizeof(TObjNpcNFM01) == 0x3B8 ? 1 : -1];

extern "C" {
u8 *TObjNpcNFM01__ct(u8 *arg0, s32 arg1, s32 arg2);
void *TObjNpcNFW00__create(void *arg0);
void *__dt__12TObjNpcNFM01Fv(void *arg0, s16 arg1);
}

// --- C functions defined in TObjNpcNFM01.cpp ---
extern "C" {
u8 *TObjNpcNFM01__ct(u8 *player, s32 arg1, s32 arg2);
void *TObjNpcNFW00__create(void *arg0);
void *__dt__12TObjNpcNFM01Fv(void *arg0, s16 arg1);
}
// --- end of C functions

extern "C" {
extern s32 *TObjNpcNFM01__model_object;
extern GinjaTextureList *TObjNpcNFM01__texture_handle;
}

#endif
