#ifndef PSO_MISC_TWINDOWSUBCUSTOMSELECT_H
#define PSO_MISC_TWINDOWSUBCUSTOMSELECT_H

#include "types.h"
#include "pso/misc/TWindowAddition.h"

struct TWindowSubCustomSelect : public TWindowAddition {
    virtual ~TWindowSubCustomSelect();
    virtual void render();
    u8 m_70;
    u8 m_71;
    u8 m_72;
    u8 m_73;
    u32 m_74;
    u32 m_78;
    u32 m_7c;
    u32 m_80;
    void handle_cancel();
    void handle_decide();
    s32 update_list_scroll();
    void handle_grid_navigation();
    void draw_cursor(u8 *arg1);
    void draw_palette_cells(int arg1);
    virtual void run_task();
    int is_active();
};

typedef char TWindowSubCustomSelect_size[sizeof(TWindowSubCustomSelect) == 0x84 ? 1 : -1];

extern "C" {
u8 *TWindowSubCustomSelect__ct(TWindowSubCustomSelect *arg0, s32 arg1);
void *__dt__22TWindowSubCustomSelectFv(void *arg0, s16 arg1);
void render__22TWindowSubCustomSelectFv(TWindowSubCustomSelect *arg0);
}

typedef char TWindowSubCustomSelect_fields_begin[offsetof(TWindowSubCustomSelect, m_70) == 0x70 ? 1 : -1];

#endif
