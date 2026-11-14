#include "pso/misc/WindowLayoutDescriptor.h"
#include "types.h"
#include "pso/misc/TWindowMenuMainMenu.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowMainMenu.h"
#include "pso/misc/TWindowSubComCard.h"

extern "C" {
WindowLayoutDescriptor window_menu_main_menu_params = { {116.0f, 0.0f}, 50050.0f, NULL, 0x803U };
extern s32 lbl_805D3E68;

void TWindowMenuMainMenu::render() {
    TWindowDrawContext *frame = setup_content_frame();
    draw_frame(frame);
    draw_entries_reversed(frame);
}

void TWindowMenuMainMenu::run_task() {
    s32 var_r31;
    u8 temp_r3;
    u8 temp_r3_2;

    TMainMenuEntry *entry;
    temp_r3 = m_60;
    if (temp_r3 & 8) {
        m_60 = (u8) (temp_r3 | 4);
    }
    entry = entries;
    var_r31 = 0;
    do {
        entry->update_item_tween();
        var_r31 += 1;
        entry += 1;
    } while (var_r31 < 8);
    handle_navigation_input();
    ((TWindowDD *)this)->initialize_subwindow();
    update_slide_position();
    update_fade();
    temp_r3_2 = m_60;
    if (temp_r3_2 & 8) {
        m_60 = (u8) (temp_r3_2 & 0xFFFFFFF3);
    }
}

TWindowMenuMainMenu::~TWindowMenuMainMenu() {}
TWindowMenuMainMenu::TWindowMenuMainMenu(void *position, s32 client)
    : TWindowBase((u8 *)&window_menu_main_menu_params, (s16)client, (u8 *)position) {
    s32 i;
    TMainMenuEntry *entry;
    entry = entries;
    i = 0;
    m_name = (const char *)lbl_805D3E68;
    m_60 = 4;
    m_61 = 0;
    m_62 = 0;
    m_20 = client;
    do {
        entry->init_color();
        i++;
        entry++;
    } while (i < 8);
    for (i = 0; i < 8; i++) {
        slots[i] = 0;
    }
    update_scaled_position();
    save_position();
}

}
