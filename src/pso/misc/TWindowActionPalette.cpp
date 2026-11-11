#include "pso/system/GinjaMaterialState.h"
#include "pso/misc/WindowLayoutDescriptor.h"
#include "pso/misc/ActionPaletteTagAbi.h"
#include "types.h"
#include "pso/item/TItem.h"
#include "pso/misc/TWindowSubStatusDisp_802598E4.h"
#include "pso/misc/TWindowHelpItem.h"
#include "pso/boss/TBoss8Dragon.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/misc/TWindowBase.h"
#include "pso/TWindowEffectLight.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/misc/TWindowActionPalette.h"
#include "pso/TPlyDispData.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TWindowDD.h"
#include "pso/player/TObjPlayer.h"
#include <stddef.h>
#include "pso/item/TItemMag.h"
#include "pso/misc/TMainCursor.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/object/TObjFish.h"

// Bounded view of the 0x38-byte sprite produced by init_part_scaled.
struct PaletteIconPart {
    u8 pad0[0x1C];
    f32 u0;
    f32 v0;
    f32 u1;
    f32 v1;
    u8 pad2c[0x34 - 0x2C];
    s32 kind;
};

struct PaletteIconUV { f32 u; f32 v; };

struct PaletteItemKind { u8 group; u8 index; };

extern "C" {
TObjPlayer *get_player_by_client_id(s32 i);
s8 clamp_char_at__10TObjPlayerFl(u32, s32);
extern const f32 lbl_805DCA28;
extern const f32 lbl_805DCA2C;
extern const f32 lbl_805DCA30;
extern const f32 lbl_805DCA34;
extern const f32 lbl_805DCA38;
extern const f32 lbl_805DCA3C;
extern const f32 lbl_805DCA40;
extern const f32 lbl_805DCA44;
void draw_action_palette_icon(PaletteIconPart *icon, int group, u16 index);
s32 fn_801B7CEC(void *player, s32 kind, u8 group, u8 index);
}
s32 get_palette_consumable_count(u16 slot, s32 client_id);
extern const PaletteItemKind lbl_8044E5E8[13];
void set_sprite_uv_from_pixels(u8 *arg0, f32 farg0, f32 farg1);

extern const f32 lbl_805DCA1C;
extern const f32 lbl_805DCA20;
extern const f32 lbl_805DCA24;

PaletteIconUV action_palette_icon_uv_tables[19] = {
    {50.0f, 0.0f}, {50.0f, 43.0f}, {50.0f, 86.0f}, {100.0f, 0.0f},
    {100.0f, 43.0f}, {100.0f, 86.0f}, {0.0f, 0.0f}, {0.0f, 43.0f},
    {0.0f, 86.0f}, {200.0f, 0.0f}, {0.0f, 129.0f}, {50.0f, 172.0f},
    {0.0f, 172.0f}, {50.0f, 129.0f}, {200.0f, 86.0f}, {150.0f, 0.0f},
    {150.0f, 86.0f}, {150.0f, 43.0f}, {200.0f, 43.0f},
};
PaletteIconUV lbl_804CDD40[17] = {
    {0.0f, 0.0f}, {0.0f, 43.0f}, {0.0f, 86.0f}, {50.0f, 0.0f},
    {50.0f, 43.0f}, {50.0f, 86.0f}, {100.0f, 0.0f}, {50.0f, 129.0f},
    {100.0f, 43.0f}, {0.0f, 172.0f}, {0.0f, 129.0f}, {150.0f, 43.0f},
    {50.0f, 172.0f}, {0.0f, 129.0f}, {0.0f, 0.0f}, {0.0f, 86.0f},
    {0.0f, 43.0f},
};
PaletteIconUV lbl_804CDDC8[6] = {
    {200.0f, 172.0f}, {150.0f, 129.0f}, {150.0f, 172.0f}, {200.0f, 129.0f},
    {100.0f, 172.0f}, {100.0f, 129.0f},
};
PaletteIconUV lbl_804CDDF8[3] = {
    {200.0f, 43.0f}, {200.0f, 0.0f}, {200.0f, 86.0f},
};
PaletteIconUV lbl_804CDE10[8] = {
    {0.0f, 0.0f}, {100.0f, 129.0f}, {100.0f, 172.0f}, {200.0f, 129.0f},
    {200.0f, 172.0f}, {100.0f, 86.0f}, {100.0f, 86.0f}, {50.0f, 0.0f},
};
// Serialized inputs consumed by init_window_layout_entries. These are layout
// records, not the allocated sprite/number entry objects.
struct PaletteScaledSpriteLayout {
    u32 kind;
    f32 position[2];
    f32 extent[2];
    f32 texture_pixels[2];
    f32 depth;
    u32 color;
    GinjaTextureList **texture_list;
    u32 mode;
    u32 flags;
};

struct PaletteNumberLayout {
    u32 kind;
    f32 position[2];
    f32 depth;
    u32 color;
    u32 flags;
    s32 value;
};

struct PaletteEntryLayouts {
    u32 entries_per_repeat;
    u32 repeat_count;
    PaletteScaledSpriteLayout panel;
    PaletteScaledSpriteLayout bank_panel;
    PaletteScaledSpriteLayout slot0_icon;
    PaletteNumberLayout slot0_count;
    PaletteScaledSpriteLayout slot1_icon;
    PaletteNumberLayout slot1_count;
    PaletteScaledSpriteLayout slot2_icon;
    PaletteNumberLayout slot2_count;
};

typedef char PaletteScaledSpriteLayout_size[sizeof(PaletteScaledSpriteLayout) == 0x30 ? 1 : -1];
typedef char PaletteScaledSpriteLayout_texture[offsetof(PaletteScaledSpriteLayout, texture_list) == 0x24 ? 1 : -1];
typedef char PaletteScaledSpriteLayout_flags[offsetof(PaletteScaledSpriteLayout, flags) == 0x2C ? 1 : -1];
typedef char PaletteNumberLayout_size[sizeof(PaletteNumberLayout) == 0x1C ? 1 : -1];
typedef char PaletteNumberLayout_value[offsetof(PaletteNumberLayout, value) == 0x18 ? 1 : -1];
typedef char PaletteEntryLayouts_size[sizeof(PaletteEntryLayouts) == 0x14C ? 1 : -1];
typedef char PaletteEntryLayouts_first[offsetof(PaletteEntryLayouts, panel) == 8 ? 1 : -1];
typedef char PaletteEntryLayouts_slot0[offsetof(PaletteEntryLayouts, slot0_icon) == 0x68 ? 1 : -1];
typedef char PaletteEntryLayouts_last[offsetof(PaletteEntryLayouts, slot2_count) == 0x130 ? 1 : -1];

extern "C" GinjaTextureList *lbl_805D63F0;

PaletteEntryLayouts lbl_804CDE50 = {
    8, 1,
    {6, {45.0f, 53.0f}, {91.0f, 54.0f}, {92.0f, 0.0f}, 0.4f, 0xFF666666, &lbl_805D63F0, 0, 0x14},
    {6, {13.0f, 0.0f}, {91.0f, 54.0f}, {0.0f, 0.0f}, 0.4f, 0xFFFFFFFF, &lbl_805D63F0, 0, 0x14},
    {6, {50.0f, 32.0f}, {50.0f, 43.0f}, {150.0f, 86.0f}, 0.4f, 0xFFFFFFFF, &lbl_805D63F0, 4, 0x14},
    {4, {79.0f, 85.0f}, 0.5f, 0xFFFFFFFF, 6, 0},
    {6, {94.0f, 6.0f}, {50.0f, 43.0f}, {150.0f, 86.0f}, 0.4f, 0xFFFFFFFF, &lbl_805D63F0, 4, 0x14},
    {4, {34.0f, 60.0f}, 0.5f, 0xFFFFFFFF, 6, 0},
    {6, {6.0f, 58.0f}, {50.0f, 43.0f}, {150.0f, 86.0f}, 0.4f, 0xFFFFFFFF, &lbl_805D63F0, 4, 0x14},
    {4, {124.0f, 60.0f}, 0.5f, 0xFFFFFFFF, 6, 0}
};

WindowLayoutDescriptor twindow_action_palette_layout = {
    {150.0f, 107.0f}, 50000.0f, &lbl_804CDE50, 0xB28
};

struct Win_802437C4 {
    u8 pad0[0x20];
    s16 id;
    u8 pad22[0x40 - 0x22];
    f32 x, y, w, h;
    u8 pad50[0x70 - 0x50];
    f32 sx, sy;
};

struct Ent_802437C4 { u8 pad0[8]; f32 x, y, w, h; };

struct Pt_802437C4 { f32 x, y; };

extern "C" {
s32 is_split_screen();
s32 sub_80244994__11TWindowBaseFv();
extern const f32 lbl_805DCA2C;
void spawn_action_palette_slot_light(Win_802437C4 *arg0, s32 arg1);

}

typedef char palette_children_offset[offsetof(TWindowActionPalette, m_24) == 0x24 ? 1 : -1];
typedef char palette_resources_offset[offsetof(TWindowActionPalette, resources) == 0x60 ? 1 : -1];
typedef char palette_state_offset[offsetof(TWindowActionPalette, state) == 0x6C ? 1 : -1];
typedef char palette_scale_offset[offsetof(TWindowActionPalette, scale) == 0x70 ? 1 : -1];
typedef char palette_size[sizeof(TWindowActionPalette) == 0x78 ? 1 : -1];

struct TWindowActionPalette;

struct Rect_80243B6C { f32 x0, y0, x1, y1, u0, v0, u1, v1; };

struct Ctx_80243B6C { f32 x; f32 y; u8 pad8[0x34 - 0x8]; s32 tex; };

struct Obj_80243968 { u8 pad[0x20]; s16 id; u8 pad22[0x3e]; u32 cur[3]; };

struct Ent_80243968 { u8 pad[0x2c]; s32 color; };

extern "C" {
void* get_array_entry__11TWindowBaseFi(TWindowActionPalette*,int);
s32 is_split_screen();
s32 fn_8002AE08(s32);
s32 is_on_current_screen__11TCameraCtrlFv(void *, s32);
u16 select_action_palette_and_apply__10TObjPlayerFlll(int, int, int, int);

u16 get_entry_by_index__20TWindowActionPaletteFPll(int, int);
s32 get_slot_type_for_index__20TWindowActionPaletteFPll(int, int);

s32 is_action_channel_available__10TObjPlayerFii(s32, s32);

extern const u8 lbl_805DCA10[4];
extern const u8 lbl_805DCA14[4];
extern const u8 lbl_805DCA18[4];
s32 is_player_input_active(int);
s32 TObjPlayer__sub_80354D5C(int);
extern u8 controller_input_state[];
s32 get_window_layout_position(s32);
void *__construct_array(void *, void *, void *, u32, u32);
s32 init_gc_tag(s32 arg0);

extern u32 __vt__20TWindowActionPalette[6];
extern const char *lbl_805D3870;
extern const f32 lbl_805DCA2C;
extern const f32 lbl_805DCA48;
extern const f32 lbl_805DCAA0;
extern const f32 lbl_805DCAA4;
f32 TWindowSubComCard__sub_80244784(TWindowSubComCard *);
s32 TWindowSubComCard__sub_802452DC(int);
s32 TWindowSubComCard__sub_80245320(void *, void *);
s32 TWindowSubComCard__sub_802454E4(int);
s32 TWindowSubComCard__sub_80245558(void *, void *, void *);
s32 apply_context_transform_to_rect(void *, void *);
s32 begin_screen_draw(int);
s32 draw_textured_quad_at_depth(void *, f32);
s32 set_draw_texture_and_color(int, int);
extern const f32 lbl_805DCA24;
extern const f32 lbl_805DCA34;
extern const f32 lbl_805DCA4C;
extern const f32 lbl_805DCA50;
extern const f32 lbl_805DCA54;
extern const f32 lbl_805DCA58;
extern const f32 lbl_805DCA5C;
extern const f32 lbl_805DCA60;
extern const f32 lbl_805DCA64;
extern const f32 lbl_805DCA68;
extern const f32 lbl_805DCA6C;
extern const f32 lbl_805DCA70;
extern const f32 lbl_805DCA74;
extern const f32 lbl_805DCA78;
extern const f32 lbl_805DCA7C;
extern const f32 lbl_805DCA80;
extern const f32 lbl_805DCA84;
extern const f32 lbl_805DCA88;
extern const f32 lbl_805DCA8C;
extern const f32 lbl_805DCA90;
extern const f32 lbl_805DCA94;
extern const f32 lbl_805DCA98;
extern const f32 lbl_805DCA9C;
s32 TObjPlayer__sub_80354C7C(s32);
s32 setup_window_draw_context__11TWindowBaseFl(void *, void *);
void draw_visible_window_entries(void *, void *, int);
void __destroy_arr(void *, void *, int, int);
}
void set_sprite_uv_from_pixels(u8 *arg0, f32 farg0, f32 farg1);
extern float TWindowActionPalette__bank_panel_uv_origins[][2];

// GC/2.6 deferred generation emits these definitions in reverse order and
// places the native palette vtable before the icon switch table. See
// docs/evidence/action-palette-unit.md.
TWindowActionPalette::TWindowActionPalette(s32 slot)
    : TWindowBase((u8 *)&twindow_action_palette_layout, (s16)slot, (u8 *)get_window_layout_position(0x1F)) {
    __construct_array(resources, (void *)init_gc_tag, (void *)TPlyDispConfig::free_if_valid, 4, 3);
    m_name = lbl_805D3870;
    if (TCameraCtrl::get_camera_id() > 2) {
        scale.x = lbl_805DCA2C;
        scale.y = lbl_805DCA2C;
    } else if (TCameraCtrl::get_camera_id() == 2) {
        scale.x = lbl_805DCAA0;
        scale.y = lbl_805DCAA0;
    } else {
        scale.x = lbl_805DCAA4;
        scale.y = lbl_805DCAA4;
    }
    m_58 = lbl_805DCA48;
    state = 0;
    m_20 = (s16)slot;
    for (u32 i = 0; i < 3; i++) {
        set_mode__20TWindowActionPaletteFUc(resources, 0);
        set_slot__20TWindowActionPaletteFUc(resources, 0);
    }
}

TWindowActionPalette::~TWindowActionPalette() {
    __destroy_arr(resources, (void *)TPlyDispConfig::free_if_valid, 4, 3);
}

void TWindowActionPalette::run_task() {
    s32 player;
    s32 effect;
    s32 slot;
    u16 v;
    u16 target;
    u8 cnt;
    u8 *help;
    player = (s32)get_player_by_client_id(m_20);
    if (player == 0 || (effect = ((TObjPlayer *)player)->refresh_effect()) == 0) {
        return;
    }
    if (!(m_2c & 2)) {
        m_5c = 0x01000000;
    }
    slot = is_player_input_active(m_20);
    if (is_on_current_screen__11TCameraCtrlFv(controller_input_state + slot * 0x50 + 0x20, fn_8002AE08(m_20)) != 0) {
        state = 3;
    }
    help = (u8 *)get_array_entry__11TWindowBaseFi(this, 0);
    TWindowHelpItem::set_help_text((s32)help, m_20);
    cnt = state;
    if ((s8)cnt > 0) {
        state = cnt - 1;
        ((TWindowHelpItem *)help)->m_2c = -1;
    } else {
        ((TWindowHelpItem *)help)->m_2c = 0xFF666666;
    }
    v = select_action_palette_and_apply__10TObjPlayerFlll(player, 0, 0, 0);
    if (v == 0) {
        v = get_entry_by_index__20TWindowActionPaletteFPll(effect, 1);
        update_slot_sprites(0, get_slot_type_for_index__20TWindowActionPaletteFPll(effect, 1), v);
    } else {
        update_slot_sprites(0, 7, v);
    }
    if (TObjPlayer__sub_80354D5C((u16)m_20) != 0 && ((TWindowActionPalette *)(player + 0x500))->handle_input_forward() != 0) {
        TWindowActionPalette::update_slot_icon(this, 1, 7, 7);
    } else {
        v = get_entry_by_index__20TWindowActionPaletteFPll(effect, 2);
        update_slot_sprites(1, get_slot_type_for_index__20TWindowActionPaletteFPll(effect, 2), v);
    }
    v = get_entry_by_index__20TWindowActionPaletteFPll(effect, 3);
    update_slot_sprites(2, get_slot_type_for_index__20TWindowActionPaletteFPll(effect, 3), v);
    target = TObjPlayer::get_current_target_id();
    if (target == 0xFFFF || target == m_20 || ((TObjPlayer *)player)->get_photon_blast_charge() <= 0) {
        if (((TWindowActionPalette *)(player + 0x500))->handle_input_forward() != 0) {
            if (is_split_screen() != 0) {
                set_bank_panel_art(3);
            } else {
                set_bank_panel_art(0);
            }
        } else {
            set_bank_panel_art(1);
        }
    } else {
        set_bank_panel_art(2);
    }
    ((TWindowDD *)this)->initialize_subwindow();
    update_fade();
    update_window_entry_list(&m_24);
}

void TWindowActionPalette::render() {
    s32 context = setup_window_draw_context__11TWindowBaseFl(this, &scale);
    draw_visible_window_entries(this, &m_24, context);
    draw_frame(context);
}

#pragma push
#pragma fp_contract on
void TWindowActionPalette::draw_frame(int arg1) {
    Rect_80243B6C r1;
    Rect_80243B6C r2;
    Rect_80243B6C r4;
    Rect_80243B6C r3;
    Ctx_80243B6C *ctx = (Ctx_80243B6C *)arg1;
    f32 scale;
    f32 depth;
    scale = TWindowSubComCard__sub_80244784((TWindowSubComCard *)this);
    depth = lbl_805DCA48 / this->m_54;
    begin_screen_draw(1);
    set_current_texture_list((GinjaTextureList *)(((void *)lbl_805D63F0)));
    set_draw_texture_and_color(2, ctx->tex);
    if (is_split_screen() == 0) {
        r1.x0 = lbl_805DCA4C - lbl_805DCA50 * scale;
        r1.y0 = lbl_805DCA54 - lbl_805DCA58 * scale;
        r1.x1 = lbl_805DCA50 + r1.x0;
        r1.y1 = lbl_805DCA5C + r1.y0;
        r1.u0 = lbl_805DCA24;
        r1.v0 = lbl_805DCA60;
        r1.u1 = lbl_805DCA64;
        r1.v1 = lbl_805DCA68;
        draw_textured_quad_at_depth(&r1, depth);
    }
    r2.x0 = lbl_805DCA6C + ctx->x;
    r2.y0 = ctx->y;
    r2.x1 = lbl_805DCA70 + r2.x0;
    r2.y1 = lbl_805DCA74 + r2.y0;
    r2.u0 = lbl_805DCA24;
    r2.v0 = lbl_805DCA78;
    r2.u1 = lbl_805DCA7C;
    r2.v1 = lbl_805DCA80;
    apply_context_transform_to_rect(ctx, &r2);
    draw_textured_quad_at_depth(&r2, depth);
    r3.x0 = lbl_805DCA84 + ctx->x;
    r3.y0 = lbl_805DCA88 + ctx->y;
    r3.x1 = lbl_805DCA70 + r3.x0;
    r3.y1 = lbl_805DCA74 + r3.y0;
    r3.u0 = lbl_805DCA8C;
    r3.v0 = lbl_805DCA78;
    r3.u1 = lbl_805DCA90;
    r3.v1 = lbl_805DCA80;
    apply_context_transform_to_rect(ctx, &r3);
    draw_textured_quad_at_depth(&r3, depth);
    r4.x0 = ctx->x;
    r4.y0 = ctx->y;
    r4.x1 = lbl_805DCA34 + r4.x0;
    r4.y1 = lbl_805DCA94 + r4.y0;
    r4.v0 = r4.u0 = lbl_805DCA24;
    r4.u1 = lbl_805DCA98;
    r4.v1 = lbl_805DCA9C;
    apply_context_transform_to_rect(ctx, &r4);
    draw_textured_quad_at_depth(&r4, depth);
    TWindowSubStatusDisp::get_player();
    if (TWindowSubComCard__sub_80245558(ctx, (u8 *)ctx + 0x10, (u8 *)ctx + 0x18) != 0) {
        TWindowSubComCard__sub_802454E4(2);
        TWindowSubComCard__sub_80245320(&r4, ctx);
        TWindowSubComCard__sub_802452DC(2);
    }
}
#pragma pop

void TWindowActionPalette::update_slot_sprites(int idx, int mode, u16 slot) {
    s32 player;
    u8 *help;
    u8 *cursor;

    player = (s32)get_player_by_client_id(this->m_20);
    if (player != 0) {
        help = (u8 *)get_array_entry__11TWindowBaseFi((TWindowActionPalette *)this, lbl_805DCA10[idx]);
        if (is_action_channel_available__10TObjPlayerFii(player, lbl_805DCA14[idx]) != 0) {
            *(s32 *)(help + 0x2C) = -1;
        } else {
            *(s32 *)(help + 0x2C) = 0xFF404040;
        }
        update_palette_item_count_label((TWindowHelpItem *)get_array_entry__11TWindowBaseFi((TWindowActionPalette *)this, lbl_805DCA18[idx]), help, mode, slot, this->m_20);
        cursor = (u8 *)this + 0x60 + idx * 4;
        if ((u16)mode != ((TMainCursor *)cursor)->get_type() || ((TMainCursor *)cursor)->get_enabled() != slot) {
            set_mode__20TWindowActionPaletteFUc(cursor, mode);
            set_slot__20TWindowActionPaletteFUc(cursor, slot);
            draw_action_palette_icon((PaletteIconPart *)help, mode, slot);
        }
    }
}

void TWindowActionPalette::update_slot_icon(void *arg0, int idx, int mode, u16 slot) {
    if ((u32)get_player_by_client_id(((Obj_80243968 *)arg0)->id) != 0) {
        Ent_80243968 *ent = (Ent_80243968 *)((void *)get_array_entry__11TWindowBaseFi((TWindowActionPalette*)(((Obj_80243968 *)arg0)), 4));
        if (TObjPlayer__sub_80354C7C((u16)((Obj_80243968 *)arg0)->id) != 0) {
            ent->color = -1;
        } else {
            ent->color = 0xFF404040;
        }
        ((TWindowHelpItem *)((void *)get_array_entry__11TWindowBaseFi((TWindowActionPalette*)(((Obj_80243968 *)arg0)), 5)))->set_flag0_bit2();
        void *cur = &((Obj_80243968 *)arg0)->cur[idx];
        if ((u16)mode != ((TMainCursor *)cur)->get_type() || ((TMainCursor *)cur)->get_enabled() != (u16)slot) {
            set_mode__20TWindowActionPaletteFUc(cur, mode);
            set_slot__20TWindowActionPaletteFUc(cur, slot);
            draw_action_palette_icon((PaletteIconPart *)ent, mode, slot);
        }
    }
}

void TWindowActionPalette::set_bank_panel_art(unsigned short state) {
    void* sprite=get_array_entry__11TWindowBaseFi(this,1);
    set_sprite_uv_from_pixels((u8 *)sprite, TWindowActionPalette__bank_panel_uv_origins[state][0], TWindowActionPalette__bank_panel_uv_origins[state][1]);
}

#pragma push
#pragma fp_contract on
void spawn_action_palette_slot_light(Win_802437C4 *arg0, s32 arg1) {
    Pt_802437C4 pt;
    s16 kind;
    Ent_802437C4 *e;
    f32 s;
    f32 hw;
    f32 s2;
    f32 hw2;
    if (sub_80244994__11TWindowBaseFv() == 0) {
        return;
    }
    switch (arg1) {
    case 1:
        kind = 0;
        e = (Ent_802437C4 *)((TWindowBase *)arg0)->get_array_entry(2);
        break;
    case 2:
        kind = 2;
        e = (Ent_802437C4 *)((TWindowBase *)arg0)->get_array_entry(4);
        break;
    case 3:
        kind = 1;
        e = (Ent_802437C4 *)((TWindowBase *)arg0)->get_array_entry(6);
        break;
        return;
    default:
        return;
    }
    if (is_split_screen() != 0) {
        hw = lbl_805DCA2C * arg0->w;
        s = arg0->sx;
        pt.x = s * ((lbl_805DCA2C * e->w + e->x) - hw) + (hw * s + arg0->x);
        hw2 = lbl_805DCA2C * arg0->h;
        s2 = arg0->sy;
        pt.y = s2 * ((lbl_805DCA2C * e->h + e->y) - hw2) + (hw2 * s2 + arg0->y);
    } else {
        pt.x = lbl_805DCA2C * e->w + (arg0->x + e->x);
        pt.y = lbl_805DCA2C * e->h + (arg0->y + e->y);
    }
    TWindowEffectLight::create(&pt, kind, arg0->id);
}
#pragma pop

void draw_action_palette_icon(PaletteIconPart *icon, int group, u16 index) {
    PaletteIconUV *row;
    switch ((u16)group) {
    case 0:
        icon->kind = 4;
        icon->u0 = lbl_805DCA34;
        icon->v0 = lbl_805DCA38;
        break;
    case 2:
        icon->kind = 4;
        row = lbl_804CDDF8;
        icon->u0 = row[index].u;
        icon->v0 = row[index].v;
        break;
    case 3:
        icon->kind = 3;
        row = action_palette_icon_uv_tables;
        icon->u0 = row[index].u;
        icon->v0 = row[index].v;
        break;
    case 4:
        if (index >= 13) {
            icon->kind = 5;
        } else {
            icon->kind = 4;
        }
        row = lbl_804CDD40;
        icon->u0 = row[index].u;
        icon->v0 = row[index].v;
        break;
    case 5:
        icon->kind = 3;
        row = lbl_804CDDC8;
        icon->u0 = row[index].u;
        icon->v0 = row[index].v;
        break;
    case 7:
        if (index >= 7) {
            icon->kind = 5;
        } else {
            icon->kind = 4;
        }
        row = lbl_804CDE10;
        icon->u0 = row[index].u;
        icon->v0 = row[index].v;
        break;
    }
    icon->u1 = lbl_805DCA3C + icon->u0;
    icon->v1 = lbl_805DCA40 + icon->v0;
    icon->u0 = icon->u0 * lbl_805DCA44;
    icon->v0 = icon->v0 * lbl_805DCA44;
    icon->u1 = icon->u1 * lbl_805DCA44;
    icon->v1 = icon->v1 * lbl_805DCA44;
}

#pragma push
#pragma fp_contract on
void update_palette_item_count_label(TWindowHelpItem *window_help_item, u8 *arg1, int arg2, u16 arg3, s32 arg4) {
    s32 v;
    u32 p;
    if ((u16)arg2 != 4) {
        window_help_item->set_flag0_bit2();
        return;
    }
    if (arg3 >= 0xD) {
        p = (u32)get_player_by_client_id(arg4);
        if (p == 0) {
            v = 0;
        } else {
            v = clamp_char_at__10TObjPlayerFl(p + 0x7C4, arg3 - 0xD);
        }
    } else {
        v = get_palette_item_amount(arg3, arg4);
    }
    if (v <= 0) {
        window_help_item->set_flag0_bit2();
        return;
    }
    ((TWindowSubStatusDisp *)window_help_item)->clear_visible_flag();
    *(s32 *)((s8 *)window_help_item + 0x1C) = *(s32 *)((s8 *)arg1 + 0x2C);
    *(s32 *)((s8 *)window_help_item + 0x20) = v;
    draw_right_aligned_number(window_help_item);
    // Legacy entry receiver: this float is not a TObject/Base member.
    *(f32 *)((u8 *)window_help_item + 8) = lbl_805DCA2C * *(f32 *)((s8 *)window_help_item + 0x10) + (*(f32 *)((s8 *)arg1 + 8) - lbl_805DCA28);
    *(f32 *)((s8 *)window_help_item + 0xC) = *(f32 *)((s8 *)arg1 + 0xC) - lbl_805DCA30;
}
#pragma pop

s32 get_palette_consumable_count(u16 slot, s32 client_id) {
    TObjPlayer *player = get_player_by_client_id(client_id);
    if (player == NULL) {
        return -1;
    }
    if (slot >= 13) {
        if (clamp_char_at__10TObjPlayerFl((u32)player + 0x7C4, slot - 13) > 0) {
            return slot;
        }
        return -1;
    }
    const PaletteItemKind *kind = &lbl_8044E5E8[slot];
    return fn_801B7CEC(player, 3, kind->group, kind->index);
}

s32 get_palette_item_amount(u16 slot, s32 client_id) {
    TItem *o;

    s32 id = get_palette_consumable_count(slot, client_id);
    if (id == -1) {
        return 0;
    }
    o = find_item_by_id(id);
    if (o == NULL) {
        return 0;
    }
    return o->get_amount();
}

void TWindowHelpItem::set_help_text(s32 arg0, s32 arg1) {
    if (((TBoss8Dragon *)arg1)->test_card_flag_2() != 0) {
        set_sprite_uv_from_pixels((u8 *)arg0, lbl_805DCA1C, lbl_805DCA20);
        return;
    }
    set_sprite_uv_from_pixels((u8 *)arg0, lbl_805DCA1C, lbl_805DCA24);
}
