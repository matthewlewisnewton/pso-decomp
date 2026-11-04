#ifndef PSO_MISC_TWINDOWMAINMENU_802AD538_H
#define PSO_MISC_TWINDOWMAINMENU_802AD538_H

#include "types.h"

struct TMainMenuRow;

extern "C" {
void TWindowMainMenu__sub_802AD74C(void *p);
int TWindowMainMenu__sub_802ADB00(u8 *arg0);
u8 *find_active_item_by_id__15TWindowMainMenuFii(s32 arg0, s32 arg1);
void get_row_position__15TWindowMainMenuFiPvi(s32 arg0, TMainMenuRow *arg1, s32 arg2);
void init_row_entry__15TWindowMainMenuFPvicc(u8 *window_sub_symbol_chat_parts_set, s32 arg1, s8 arg2, s8 arg3);
s32 is_not_split_screen(void *);
}

// --- C functions defined in TWindowMainMenu_802AD538.cpp ---
extern "C" {
void TWindowMainMenu__sub_802AD74C(void *p);
int TWindowMainMenu__sub_802ADB00(u8 *arg0);
u8 *find_active_item_by_id__15TWindowMainMenuFii(s32 arg0, s32 arg1);
void get_row_position__15TWindowMainMenuFiPvi(s32 arg0, TMainMenuRow *arg1, s32 arg2);
void init_row_entry__15TWindowMainMenuFPvicc(u8 *window_sub_symbol_chat_parts_set, s32 arg1, s8 arg2, s8 arg3);
s32 is_not_split_screen(void *);
}
// --- end of C functions

#endif
