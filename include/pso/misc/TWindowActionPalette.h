#ifndef PSO_MISC_TWINDOWACTIONPALETTE_H
#define PSO_MISC_TWINDOWACTIONPALETTE_H

#include "types.h"
#include "pso/TObject.h"

// The window lifecycle remains at the recovered C ABI boundary; TObject
// supplies the verified scene-node prefix and four virtual slots.
struct TWindowActionPalette : public TObject {
    // This first declaration selects the TU that emits the native vtable.
    virtual void render();
    virtual ~TWindowActionPalette();
    virtual void run_task();
    struct ChildList {
        u32 count;
        void **entries;
    };
    struct Scale {
        f32 x;
        f32 y;
    };

    u8 unknown_1c[4];

    s16 m_20;

    u8 unk_22[0x2];
    ChildList children;
    u8 unk_2C[0x28];
    f32 m_54;
    u8 unk_58[0x4];
    s32 m_5c;
    u8 resources[3][4];
    u8 state;
    u8 unknown_6d[3];
    Scale scale;
    void set_bank_panel_art(unsigned short state);
    static void update_slot_icon(void *arg0, int idx, int mode, u16 slot);
    void update_slot_sprites(int idx, int mode, u16 slot);
    void draw_frame(int arg1);
    // Legacy entry accessors: their receiver is a four-byte palette entry.
    void set_slot(u8 v);
    void set_mode(u8 v);
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
