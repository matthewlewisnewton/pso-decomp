#ifndef PSO_UNK_TLOBBY_8001EF5C_H
#define PSO_UNK_TLOBBY_8001EF5C_H

#include "types.h"
#include "pso/system/BmlAccessors.h"

extern "C" {
s32 alloc_load_data__6TLobbyFPviii(void *arg0, s32 base, s32 arg2, s32 arg3);
void increment_ref_and_set_flag__6TLobbyFPv(void *arg0);
}
void load_bin_model_callback(void *request);
void load_bin_motion_callback(void *arg0);

// --- C functions defined in TLobby_8001EF5C.cpp ---
extern "C" {
s32 alloc_load_data__6TLobbyFPviii(void *arg0, s32 base, s32 arg2, s32 arg3);
int fn_8001ED90(void *p);
AnimationMotion *get_bml_motion(BmlResource *resource, s32 index);
void increment_ref_and_set_flag__6TLobbyFPv(void *arg0);
}
// --- end of C functions

#endif
