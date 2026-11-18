#include "pso/system/CurrentTextureList.h"
#include "pso/misc/WindowLayoutDescriptor.h"
#include "types.h"
#include "pso/misc/TWindowSimpleStatus.h"
#include "pso/misc/TWindowBase.h"

#include <stddef.h>
#include "pso/misc/TWindowPartyStatus.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/object/TObjFish.h"

#pragma readonly_strings on

extern "C" {
const char *TWindowPartyStatus__name = "TWindowPartyStatus";
}

struct Stack_8030C0C4 {
    f32 sp8;
    f32 spC;
    f32 sp10;
    f32 sp14;
    f32 sp18;
    f32 sp1C;
    f32 sp20;
    f32 sp24;
};

extern "C" {
s32 draw_visible_window_entries(void *, void *, int);
s32 TWindowSubComCard__sub_802452DC(int);
s32 TWindowSubComCard__sub_80245320(void *, void *);
s32 TWindowSubComCard__sub_802454E4(int);
s32 TWindowSubComCard__sub_80245558(void *, void *, void *);
s32 apply_context_transform_to_rect(void *, void *);
void begin_screen_draw(s32 arg0);
void draw_textured_quad_at_depth(f32 *q, f32 depth);
void set_draw_texture_and_color(s32 idx, s32 arg1);
extern s32 lbl_805D63F0;
extern const f32 lbl_805DF1EC;
extern const f32 lbl_805DF1F0;
extern const f32 lbl_805DF1F4;
extern const f32 lbl_805DF1F8;
extern const f32 lbl_805DF1FC;
extern const f32 lbl_805DF200;
extern const f32 lbl_805DF204;
s32 get_window_layout_position(int);
extern const char *TWindowPartyStatus__name;
extern s32 local_client_id;
int update_hp_entry__20TWindowSubStatusDispFv(void*);
s32 update_lockon_window();
int update_status_entry__20TWindowSubStatusDispFv(void*);
void update_status_help_item(s32 arg0);

void TWindowPartyStatus::draw() { update_hp_entry__20TWindowSubStatusDispFv(this); update_status_entry__20TWindowSubStatusDispFv(this); }

void TWindowPartyStatus::draw_background(u8 *arg1) {
    typedef char sp8_offset[(offsetof(Stack_8030C0C4, sp8) == 0x0) ? 1 : -1];
    typedef char spC_offset[(offsetof(Stack_8030C0C4, spC) == 0x4) ? 1 : -1];
    typedef char sp10_offset[(offsetof(Stack_8030C0C4, sp10) == 0x8) ? 1 : -1];
    typedef char sp14_offset[(offsetof(Stack_8030C0C4, sp14) == 0xC) ? 1 : -1];
    typedef char sp18_offset[(offsetof(Stack_8030C0C4, sp18) == 0x10) ? 1 : -1];
    typedef char sp1C_offset[(offsetof(Stack_8030C0C4, sp1C) == 0x14) ? 1 : -1];
    typedef char sp20_offset[(offsetof(Stack_8030C0C4, sp20) == 0x18) ? 1 : -1];
    typedef char sp24_offset[(offsetof(Stack_8030C0C4, sp24) == 0x1C) ? 1 : -1];
    Stack_8030C0C4 stack;
    f32 temp_f2;
    f32 temp_f31;
    f32 temp_f6;
    temp_f31 = lbl_805DF1EC / this->m_54;
    begin_screen_draw(1);
    set_current_texture_list((GinjaTextureList *)(lbl_805D63F0));
    set_draw_texture_and_color(0xB, (*(s32 *)((s8 *)arg1 + 0x34)));
    temp_f2 = *(f32 *)((s8 *)arg1 + 0x10);
    stack.sp8 = temp_f2;
    temp_f6 = *(f32 *)((s8 *)arg1 + 0x14);
    stack.spC = temp_f6;
    stack.sp10 = lbl_805DF1F0 + temp_f2;
    stack.sp14 = lbl_805DF1F4 + temp_f6;
    stack.sp18 = lbl_805DF1F8;
    stack.sp1C = lbl_805DF1FC;
    stack.sp20 = lbl_805DF200;
    stack.sp24 = lbl_805DF204;
    apply_context_transform_to_rect(arg1, &stack.sp8);
    draw_textured_quad_at_depth((&stack.sp8), temp_f31);
    TWindowSubStatusDisp::get_player();
    if (TWindowSubComCard__sub_80245558(arg1, arg1 + 0x10, arg1 + 0x18) != 0) {
        TWindowSubComCard__sub_802454E4(0xB);
        TWindowSubComCard__sub_80245320(&stack.sp8, arg1);
        TWindowSubComCard__sub_802452DC(0xB);
    }
}

void TWindowPartyStatus::render() {
    s32 context = TWindowDD::draw_default_entry((s32)this);
    draw_background((u8 *)context);
    draw_visible_window_entries(this, (u8 *)this + 0x24, context);
}

void TWindowPartyStatus::run_task() {
    s32 arg0 = (s32)this;
    update_lockon_window();
    draw();
    update_status_help_item((arg0));
    ((TWindowSimpleStatus *)arg0)->update_status_icons((void *)(get_window_layout_position(0xAC)));
    ((TWindowDD *)arg0)->initialize_subwindow();
    ((TWindowBase *)arg0)->update_fade();
    ((TWindowBase *)arg0)->update_window_entry_list((void *)(arg0 + 0x24));
    ((TWindowSimpleStatus *)arg0)->apply_random_shake();
}

extern u8 lbl_804E7750[];
WindowLayoutDescriptor party_status_window_params = {
    {114.0f, 46.0f}, 70100.0f, lbl_804E7750, 0xB28
};

TWindowPartyStatus::~TWindowPartyStatus() {}

TWindowPartyStatus::TWindowPartyStatus(s32 slot, u8 *descriptor)
    : TWindowSimpleStatus((void *)get_window_layout_position(0xAB), local_client_id, descriptor) {
    m_name = TWindowPartyStatus__name;
    m_20 = slot;
}

}
