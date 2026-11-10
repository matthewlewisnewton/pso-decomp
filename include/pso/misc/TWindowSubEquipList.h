#ifndef PSO_MISC_TWINDOWSUBEQUIPLIST_H
#define PSO_MISC_TWINDOWSUBEQUIPLIST_H

#include "types.h"
#include "pso/misc/TWindowMenuIconLine.h"

struct TItem;

struct TWindowSubEquipList : public TWindowMenuIconLine {
    TWindowSubEquipList(void *position, s32 client);
    virtual ~TWindowSubEquipList();
    virtual void render();
    void run_task();
    void update_window();
    void build_equipment_list();
    void add_status_line(u8 icon, TItem *item, s32 slot);
};

typedef char TWindowSubEquipList_size[sizeof(TWindowSubEquipList) == 0x88 ? 1 : -1];

extern "C" u8 *create_equip_list_window(s32 arg0, s32 arg1, s32 arg2);

#endif
