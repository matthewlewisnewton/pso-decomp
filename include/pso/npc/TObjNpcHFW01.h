#ifndef PSO_NPC_TOBJNPCHFW01_H
#define PSO_NPC_TOBJNPCHFW01_H

#include "types.h"
#include "pso/npc/TUnk_804A92A8.h"

struct GinjaTextureList;

struct TObjNpcHFW01 : public TUnk_804A92A8 {
    virtual ~TObjNpcHFW01();
    static void free_static_resources();
    static void load_resources();
};

typedef char TObjNpcHFW01_size[sizeof(TObjNpcHFW01) == 0x3B8 ? 1 : -1];

extern "C" {
extern s32 *TObjNpcHFW01__resource_node;
extern GinjaTextureList *TObjNpcHFW01__texture_handle;
u8 *TObjNpcHFW01__ct(u8 *arg0, s32 arg1, s32 arg2);
void *TObjNpcHHM00__create(void *arg0);
void *__dt__12TObjNpcHFW01Fv(void *arg0, s16 arg1);
}

// --- C functions defined in TObjNpcHFW01.cpp ---
extern "C" {
u8 *TObjNpcHFW01__ct(u8 *player, s32 arg1, s32 arg2);
void *TObjNpcHHM00__create(void *arg0);
void *__dt__12TObjNpcHFW01Fv(void *arg0, s16 arg1);
}
// --- end of C functions

#endif
