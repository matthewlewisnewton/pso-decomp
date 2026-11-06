#ifndef PSO_ITEM_TITEMATTACKER_H
#define PSO_ITEM_TITEMATTACKER_H

#include "types.h"

extern "C" {
void TItemAttacker__sub_8010349C(u32 arg0);
void TItemBuff__ct(void);
u8 *__ct__13TItemAttackerFllll(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
}
s32 create_item_buff(s32 arg0);
extern "C" {
int get_item_chunk_buffer(int a0);
}

// --- C functions defined in TItemAttacker.cpp ---
extern "C" {
void TItemAttacker__sub_8010349C(u32 arg0);
void TItemBuff__ct(void);
int get_item_chunk_buffer(int a0);
}
// --- end of C functions

#endif
