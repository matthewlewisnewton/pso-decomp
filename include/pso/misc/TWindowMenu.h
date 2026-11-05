#ifndef PSO_MISC_TWINDOWMENU_H
#define PSO_MISC_TWINDOWMENU_H

#include "types.h"
#include "pso/misc/TUnk_804CE018.h"
#include "pso/misc/TWindowAddition.h"

struct TWindowDrawContext;

struct TWindowMenu : public TUnk_804CE018 {
    virtual ~TWindowMenu();
    s32 get_selected_entry();
    int sub_80266BB8();
    u8 test_menu_flag();
    void render_selected_entry(TWindowDrawContext *);
    void draw_selected_bar(TWindowDrawContext *);
    void layout_entries();
    void calc_window_size();
    void update_scroll_value();
    void advance_past_disabled_menu_rows();
    void clamp_menu_choice_scroll();
    void update_target_y();
    void reset_selection();
    int is_decided();
    int is_cancelled();
    s32 get_selected_value();
    virtual void render();
    u8 _pad60[0x8];
    void* m_68;
    u8 _pad6C[0x4];
    u16 m_70;
    void set_loss_flag();
    u16 m_72;
    u16 m_74;
    u16 m_76;
    u16 m_78;
    u8 unk_7A[0x2];
    u32 m_7c;
    u32 m_80;
    u32 m_84;
    u32 m_88;
    void set_active_flag();
    void confirm_selection();
    void select_next_item();
    void move_cursor_prev();
    virtual void run_task();
    void copy_position(void* q);
    s32 is_locked(s32 arg1);
};

typedef char TWindowMenu_size[sizeof(TWindowMenu) == 0x8C ? 1 : -1];
#endif
