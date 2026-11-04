#include "types.h"
#include "pso/misc/TWindowMenuMainMenu.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowMainMenu.h"
#include "pso/misc/TWindowSubComCard.h"

struct W_802AE864 { u8 pad[0x124]; void *a[8]; };

extern "C" {
extern s32 window_menu_main_menu_params[];
extern s32 __vt__19TWindowMenuMainMenu[];
extern s32 lbl_805D3E68;
void __dl__7TObjectFPv(void *);

void TWindowMenuMainMenu::render() {
    TWindowDrawContext *frame = setup_content_frame();
    draw_frame(frame);
    draw_entries_reversed(frame);
}

void run_task__19TWindowMenuMainMenuFv(TWindowMenuMainMenu *window_menu_main_menu) {
    s32 var_r31;
    u8 temp_r3;
    u8 temp_r3_2;

    TMainMenuEntry *entry;
    temp_r3 = window_menu_main_menu->m_60;
    if (temp_r3 & 8) {
        window_menu_main_menu->m_60 = (u8) (temp_r3 | 4);
    }
    entry = window_menu_main_menu->entries;
    var_r31 = 0;
    do {
        entry->update_item_tween();
        var_r31 += 1;
        entry += 1;
    } while (var_r31 < 8);
    window_menu_main_menu->handle_navigation_input();
    ((TWindowDD *)window_menu_main_menu)->initialize_subwindow();
    window_menu_main_menu->update_slide_position();
    window_menu_main_menu->update_fade();
    temp_r3_2 = window_menu_main_menu->m_60;
    if (temp_r3_2 & 8) {
        window_menu_main_menu->m_60 = (u8) (temp_r3_2 & 0xFFFFFFF3);
    }
}

void *__dt__19TWindowMenuMainMenuFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__19TWindowMenuMainMenu;
        ((TWindowDD *)arg0)->destroy_window_base(0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}
u8 *TWindowMenuMainMenu__ct(TWindowMenuMainMenu *window_menu_main_menu, s32 arg1, s16 arg2) {
    s32 i;
    TMainMenuEntry *entry;
    ((TWindowDD *)window_menu_main_menu)->construct_base((u8 *)window_menu_main_menu_params, (s16)arg2, (u8 *)arg1);
    *(s32 **)((s8 *)window_menu_main_menu + 0x18) = __vt__19TWindowMenuMainMenu;
    entry = window_menu_main_menu->entries;
    i = 0;
    *(s32 *)((s8 *)window_menu_main_menu + 0) = lbl_805D3E68;
    window_menu_main_menu->m_60 = 4;
    window_menu_main_menu->m_61 = 0;
    window_menu_main_menu->m_62 = 0;
    window_menu_main_menu->m_20 = arg2;
    do {
        entry->init_color();
        i++;
        entry++;
    } while (i < 8);
    for (i = 0; i < 8; i++) {
        window_menu_main_menu->slots[i] = 0;
    }
    window_menu_main_menu->update_scaled_position();
    window_menu_main_menu->save_position();
    return (u8 *)window_menu_main_menu;
}

}
