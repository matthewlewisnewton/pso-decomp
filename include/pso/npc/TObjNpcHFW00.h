#ifndef PSO_NPC_TOBJNPCHFW00_H
#define PSO_NPC_TOBJNPCHFW00_H

#include "types.h"
#include "pso/npc/TUnk_804A92A8.h"

struct GinjaTextureList;

struct TObjNpcHFW00 : public TUnk_804A92A8 {
    virtual ~TObjNpcHFW00();
    static void free_resources();
    static void load_resources();
};

typedef char TObjNpcHFW00_size[sizeof(TObjNpcHFW00) == 0x3B8 ? 1 : -1];

extern "C" {
u8 *TObjNpcHFW00__ct(u8 *arg0, s32 arg1, s32 arg2);
void *TObjNpcHFW01__create(void *arg0);
void *__dt__12TObjNpcHFW00Fv(void *arg0, s16 arg1);
}

// --- C functions defined in TObjNpcHFW00.cpp ---
extern "C" {
u8 *TObjNpcHFW00__ct(u8 *player, s32 arg1, s32 arg2);
void *TObjNpcHFW01__create(void *arg0);
void *__dt__12TObjNpcHFW00Fv(void *arg0, s16 arg1);
}
// --- end of C functions

extern "C" {
extern s32 *TObjNpcHFW00__shared_resource_obj;
extern GinjaTextureList *TObjNpcHFW00__texture_handle;
}

#endif
