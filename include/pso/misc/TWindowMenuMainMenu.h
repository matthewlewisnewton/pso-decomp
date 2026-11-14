#ifndef PSO_MISC_TWINDOWMENUMAINMENU_H
#define PSO_MISC_TWINDOWMENUMAINMENU_H

#include "types.h"
#include <stddef.h>
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowDrawContext.h"

// get_row_position writes this pair: x then y (the entry's x/y targets).
struct TMainMenuRow {
    f32 x;
    f32 y;
};

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
    void draw_item_labels(TWindowDrawContext *context);
    int is_item_active();
    void sub_802AD74C();
    void set_symbol_chat_parts(TMainMenuRow *row);
    void init_row_entry(TMainMenuRow *row, s8 icon, s8 fade);
    void update_item_tween();
    void init_color();
    void copy_color_entry(TMainMenuEntry *src);
};

typedef char TMainMenuEntry_size[sizeof(TMainMenuEntry) == 0x18 ? 1 : -1];
typedef char TMainMenuEntry_flags[offsetof(TMainMenuEntry, flags) == 0x13 ? 1 : -1];
typedef char TMainMenuEntry_kind[offsetof(TMainMenuEntry, kind) == 0x12 ? 1 : -1];

struct TWindowMenuMainMenu : public TWindowBase {
    TWindowMenuMainMenu(void *position, s32 client);
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
    void park_selection();
    int get_selected_item_type();
    void sub_802ADADC(int slot);
    int sub_802ADB00();
    void clear_menu_flags();
    int find_free_item_slot();
    void get_row_position(TMainMenuRow *row, int index);
    s32 is_not_split_screen();
    TMainMenuEntry *append_child_rows(int id);
    void play_cursor_sound(int delta);
    TMainMenuEntry *update_if_active(s32 id);
    TMainMenuEntry *find_active_item_by_id(int id);
    TMainMenuEntry *find_free_slot();
    s32 count_active_items();
    int get_menu_flag();
    int is_flag_set();
    virtual void render();
    virtual void run_task();
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

#endif
