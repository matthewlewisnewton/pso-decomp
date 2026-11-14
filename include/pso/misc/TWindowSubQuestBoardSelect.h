#ifndef PSO_MISC_TWINDOWSUBQUESTBOARDSELECT_H
#define PSO_MISC_TWINDOWSUBQUESTBOARDSELECT_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowSubQuestBoardSelect : public TWindowBase {
    TWindowSubQuestBoardSelect();
    virtual ~TWindowSubQuestBoardSelect();
    void update_slot_display_flags();
    int is_shortcut_active();
    void sub_8027D230();
    int is_open();
    virtual void render();
    u8 m_60;
    s8 m_61;
    u8 _pad62[0x2];
    void *m_64; // Owned opaque heading under its legacy release protocol.
    void handle_cancel();
    void handle_decide();
    void select_next();
    s32 handle_page_input();
    virtual void run_task();
};

typedef char TWindowSubQuestBoardSelect_size[sizeof(TWindowSubQuestBoardSelect) == 0x68 ? 1 : -1];

typedef char QuestBoardSelect_heading[offsetof(TWindowSubQuestBoardSelect, m_64) == 0x64 ? 1 : -1];

extern "C" {
s32 get_slot_flag__26TWindowSubQuestBoardSelectFic(s32 arg0, s8 arg1);
}
#endif
