#ifndef PSO_UI_WINDOW_TWINDOWSUBEQUIPLIST_H
#define PSO_UI_WINDOW_TWINDOWSUBEQUIPLIST_H

#include "types.h"

struct TItem;
#include "pso/ui/window/TWindowMenuIconLine.h"

struct TWindowSubEquipList : public TWindowMenuIconLine {
    virtual ~TWindowSubEquipList();
    virtual void render();
    void run_task();
    void update_window();
    int build_equipment_list();
    void add_status_line(u8 arg1, TItem *arg2, s32 arg3);
};

typedef char TWindowSubEquipList_size[sizeof(TWindowSubEquipList) == 0x88 ? 1 : -1];

extern "C" {
u8 *TWindowSubEquipList__ct(u8 *arg0, s32 arg1, s16 arg2);
void *__dt__19TWindowSubEquipListFv(void *arg0, s16 arg1);
u8 *create_equip_list_window(s32 arg0, s32 arg1, s16 arg2);
}

// --- C functions defined in TWindowSubEquipList.cpp ---
extern "C" {
u8 *TWindowSubEquipList__ct(u8 *arg0, s32 arg1, s16 arg2);
void *__dt__19TWindowSubEquipListFv(void *arg0, s16 arg1);
u8 *create_equip_list_window(s32 arg0, s32 arg1, s16 arg2);
}
// --- end of C functions

#endif
