#ifndef PSO_MISC_TWINDOWSUBITEMLIST_H
#define PSO_MISC_TWINDOWSUBITEMLIST_H

#include "types.h"
#include "pso/misc/TWindowMenuIconLine.h"

struct TWindowSubItemList : public TWindowMenuIconLine {
    TWindowSubItemList(void *position, s32 client);
    virtual ~TWindowSubItemList();
    void reset_selected();
    void refresh();
    void sub_8027ACF8(u8 *);
    void render();
    void run_task();
    u8 unk_88[0x4];
    s32 m_8c;
};

typedef char TWindowSubItemList_size[sizeof(TWindowSubItemList) == 0x90 ? 1 : -1];

extern "C" TWindowSubItemList *create_sub_item_list_window(void *position, void *extent, s32 client);

typedef char TWindowSubItemList_unk_88_offset[offsetof(TWindowSubItemList, unk_88) == 0x88 ? 1 : -1];
typedef char TWindowSubItemList_m_8c_offset[offsetof(TWindowSubItemList, m_8c) == 0x8C ? 1 : -1];

#endif
