#ifndef PSO_MISC_TWINDOWMENUMAINMENU_H
#define PSO_MISC_TWINDOWMENUMAINMENU_H

#include "types.h"
#include <stddef.h>
#include "pso/misc/TUnk_804CE018.h"
#include "pso/misc/TWindowDrawContext.h"

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
    u8 m_61;
    u16 m_62;
    void* m_64;
    u8 unk_68[0xDC];
};

typedef char TWindowMenuMainMenu_size[sizeof(TWindowMenuMainMenu) == 0x144 ? 1 : -1];
typedef char TWindowMenuMainMenu_m40[offsetof(TWindowMenuMainMenu, m_40) == 0x40 ? 1 : -1];
typedef char TWindowMenuMainMenu_m48[offsetof(TWindowMenuMainMenu, m_48) == 0x48 ? 1 : -1];
typedef char TWindowMenuMainMenu_m54[offsetof(TWindowMenuMainMenu, m_54) == 0x54 ? 1 : -1];
typedef char TWindowMenuMainMenu_unk22[offsetof(TWindowMenuMainMenu, unk_22) == 0x22 ? 1 : -1];
typedef char TWindowMenuMainMenu_unk3c[offsetof(TWindowMenuMainMenu, unk_3c) == 0x3C ? 1 : -1];
typedef char TWindowMenuMainMenu_unk50[offsetof(TWindowMenuMainMenu, unk_50) == 0x50 ? 1 : -1];

extern "C" {
u8 *TWindowMenuMainMenu__ct(TWindowMenuMainMenu *arg0, s32 arg1, s16 arg2);
void *__dt__19TWindowMenuMainMenuFv(void *arg0, s16 arg1);
void render__19TWindowMenuMainMenuFv(s32 arg0);
void run_task__19TWindowMenuMainMenuFv(TWindowMenuMainMenu *arg0);
}

// --- C functions defined in TWindowMenuMainMenu.cpp ---
extern "C" {
u8 *TWindowMenuMainMenu__ct(TWindowMenuMainMenu *window_menu_main_menu, s32 arg1, s16 arg2);
void *__dt__19TWindowMenuMainMenuFv(void *arg0, s16 arg1);
void render__19TWindowMenuMainMenuFv(s32 arg0);
void run_task__19TWindowMenuMainMenuFv(TWindowMenuMainMenu *window_menu_main_menu);
}
// --- end of C functions

#endif
