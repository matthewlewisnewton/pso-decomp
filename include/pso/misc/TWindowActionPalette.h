#ifndef PSO_MISC_TWINDOWACTIONPALETTE_H
#define PSO_MISC_TWINDOWACTIONPALETTE_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowActionPalette : public TWindowBase {
    TWindowActionPalette(s32 slot);
    // Retain main's key-function ownership in the consolidated unit.
    virtual void render();
    virtual ~TWindowActionPalette();
    virtual void run_task();
    struct Scale {
        f32 x;
        f32 y;
    };


    u8 resources[3][4];
    u8 state;
    u8 unknown_6d[3];
    Scale scale;
    void set_bank_panel_art(unsigned short state);
    static void update_slot_icon(void *arg0, int idx, int mode, u16 slot);
    void update_slot_sprites(int idx, int mode, u16 slot);
    void draw_frame(int arg1);
    int handle_input_forward();
    static void is_channel_active_at(s32 arg0, s32 arg1, s32 arg2);
    static void set_palette_entry(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
    static void set_slot_by_index(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
    static void set_slot_mode(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
    static void get_entry_by_index(s32 *arg0, s32 arg1);
    static u8 *get_slot_type(s32 arg0, s32 arg1, s32 arg2);
    static void get_slot_type_for_index(s32 *arg0, s32 arg1);
};

struct TWindowHelpItem;
extern "C" {
s32 get_palette_item_amount(u16 slot, s32 client_id);
void update_palette_item_count_label(TWindowHelpItem *label, u8 *icon, int group, u16 slot, s32 client_id);
}

#endif
