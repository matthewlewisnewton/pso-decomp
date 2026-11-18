#ifndef PSO_UI_WINDOW_TWINDOWSUBITEMLIST_H
#define PSO_UI_WINDOW_TWINDOWSUBITEMLIST_H

#include "types.h"
#include "pso/ui/window/TWindowMenuIconLine.h"

struct TWindowSubItemList : public TWindowMenuIconLine {
    TWindowSubItemList(void *position, s32 client);
    virtual ~TWindowSubItemList();
    void sub_8027ACF8(u8 *);
    void render();
    void run_task();
    u8 unk_88[0x4];
    s32 m_8c;
};

typedef char TWindowSubItemList_size[sizeof(TWindowSubItemList) == 0x90 ? 1 : -1];

extern "C" u8 *create_sub_item_list_window(s32 arg0, s32 arg1, s32 arg2);

#endif
