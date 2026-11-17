#ifndef PSO_NPC_TOBJNPCNFW00_H
#define PSO_NPC_TOBJNPCNFW00_H

#include "types.h"
#include "pso/npc/TUnk_804A8640.h"

struct GinjaTextureList;

struct TObjNpcNFW00 : public TUnk_804A8640 {
    virtual ~TObjNpcNFW00();
    static void free_resources();
    static void load_assets();
};

typedef char TObjNpcNFW00_size[sizeof(TObjNpcNFW00) == 0x3B8 ? 1 : -1];

extern "C" {
u8 *TObjNpcNFW00__ct(u8 *arg0, s32 arg1, s32 arg2);
void *TObjNpcNFW01__create(void *arg0);
void *__dt__12TObjNpcNFW00Fv(void *arg0, s16 arg1);
}

// --- C functions defined in TObjNpcNFW00.cpp ---
extern "C" {
u8 *TObjNpcNFW00__ct(u8 *arg0, s32 arg1, s32 arg2);
void *TObjNpcNFW01__create(void *arg0);
void *__dt__12TObjNpcNFW00Fv(void *arg0, s16 arg1);
}
// --- end of C functions

extern "C" {
extern s32 *TObjNpcNFW00__named_object_resource;
extern GinjaTextureList *TObjNpcNFW00__texture_gvm_handle;
}

#endif
