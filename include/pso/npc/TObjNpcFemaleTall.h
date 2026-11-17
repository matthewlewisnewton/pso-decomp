#ifndef PSO_NPC_TOBJNPCFEMALETALL_H
#define PSO_NPC_TOBJNPCFEMALETALL_H

#include "types.h"
#include "pso/npc/TUnk_804A8640.h"

struct BmlResource;

struct TObjNpcFemaleTall : public TUnk_804A8640 {
    virtual ~TObjNpcFemaleTall();
    static void destroy_instance();
    static void load_resource_instance();
};

typedef char TObjNpcFemaleTall_size[sizeof(TObjNpcFemaleTall) == 0x3B8 ? 1 : -1];

extern "C" {
u8 *TObjNpcFemaleTall__ct(u8 *arg0, s32 arg1, s32 arg2);
void TObjNpcFemaleTall__sub_8014AA28(void *arg0, s32 arg1);
void *__dt__17TObjNpcFemaleTallFv(void *arg0, s16 arg1);
}

// --- C functions defined in TObjNpcFemaleTall.cpp ---
extern "C" {
u8 *TObjNpcFemaleTall__ct(u8 *arg0, s32 arg1, s32 arg2);
void TObjNpcFemaleTall__sub_8014AA28(void *arg0, s32 arg1);
void *__dt__17TObjNpcFemaleTallFv(void *arg0, s16 arg1);
}
// --- end of C functions

extern "C" {
extern BmlResource *TObjNpcFemaleTall__instance;
}

#endif
