#ifndef PSO_MISC_TWINDOWMENUMAINMENU_H
#define PSO_MISC_TWINDOWMENUMAINMENU_H

#include "types.h"
#include <stddef.h>
#include "pso/misc/TUnk_804CE018.h"
#include "pso/misc/TWindowDrawContext.h"

// One row of the main menu. Eight of these are embedded at 0x64, stride 0x18.
// init_color writes the four floats and the five bytes that follow; the
// constructor walks that array, not the menu object itself.
struct TMainMenuEntry {
    f32 x;
    f32 y;
    f32 cur_x;
    f32 cur_y;
    s8 fade;
    s8 icon;
    s8 kind;
    u8 flags;
    s8 tween;
    u8 b5;
    u8 b6;
    u8 b7;
    void init_color();
    void update_item_tween();
    int is_item_active();
};

typedef char TMainMenuEntry_size[sizeof(TMainMenuEntry) == 0x18 ? 1 : -1];
typedef char TMainMenuEntry_flags[offsetof(TMainMenuEntry, flags) == 0x13 ? 1 : -1];
typedef char TMainMenuEntry_kind[offsetof(TMainMenuEntry, kind) == 0x12 ? 1 : -1];

// get_row_position writes this pair: y then x.
struct TMainMenuRow {
    f32 y;
    f32 x;
};

struct TWindowMenuMainMenu : public TUnk_804CE018 {
    virtual ~TWindowMenuMainMenu();
    void handle_navigation_input();
    void handle_confirm();
    void handle_cancel();
    void draw_frame(TWindowDrawContext *context);
    TWindowDrawContext *setup_content_frame();
    void set_target_y(f32 target);
    void update_scaled_position();
    void update_slide_position();
    void draw_entries_reversed(TWindowDrawContext *context);
    void pop_level();
    s32 update_if_active(s32 id);
    int get_menu_flag();
    int is_flag_set();
    virtual void render();
    virtual void run_task();
    u8 _pad1C[0x4];
    u16 m_20;
    s16 unk_22;
    u8 unk_24[0x8];
    s32 m_2c;
    u8 unk_30[0xC];
    f32 unk_3c;
    f32 m_40[2];
    f32 m_48[2];
    u32 unk_50;
    f32 m_54;
    u8 unk_58[0x8];
    u8 m_60;
    s8 m_61;
    s16 m_62;
    TMainMenuEntry entries[8];
    TMainMenuEntry *slots[8];
};

typedef char TWindowMenuMainMenu_size[sizeof(TWindowMenuMainMenu) == 0x144 ? 1 : -1];
typedef char TWindowMenuMainMenu_m40[offsetof(TWindowMenuMainMenu, m_40) == 0x40 ? 1 : -1];
typedef char TWindowMenuMainMenu_m48[offsetof(TWindowMenuMainMenu, m_48) == 0x48 ? 1 : -1];
typedef char TWindowMenuMainMenu_m54[offsetof(TWindowMenuMainMenu, m_54) == 0x54 ? 1 : -1];
typedef char TWindowMenuMainMenu_unk22[offsetof(TWindowMenuMainMenu, unk_22) == 0x22 ? 1 : -1];
typedef char TWindowMenuMainMenu_unk3c[offsetof(TWindowMenuMainMenu, unk_3c) == 0x3C ? 1 : -1];
typedef char TWindowMenuMainMenu_unk50[offsetof(TWindowMenuMainMenu, unk_50) == 0x50 ? 1 : -1];
typedef char TWindowMenuMainMenu_entries[offsetof(TWindowMenuMainMenu, entries) == 0x64 ? 1 : -1];
typedef char TWindowMenuMainMenu_slots[offsetof(TWindowMenuMainMenu, slots) == 0x124 ? 1 : -1];

extern "C" {
u8 *TWindowMenuMainMenu__ct(TWindowMenuMainMenu *arg0, s32 arg1, s16 arg2);
void *__dt__19TWindowMenuMainMenuFv(void *arg0, s16 arg1);
void run_task__19TWindowMenuMainMenuFv(TWindowMenuMainMenu *arg0);
}

// --- C functions defined in TWindowMenuMainMenu.cpp ---
extern "C" {
u8 *TWindowMenuMainMenu__ct(TWindowMenuMainMenu *window_menu_main_menu, s32 arg1, s16 arg2);
void *__dt__19TWindowMenuMainMenuFv(void *arg0, s16 arg1);
void run_task__19TWindowMenuMainMenuFv(TWindowMenuMainMenu *window_menu_main_menu);
}
// --- end of C functions

#endif
