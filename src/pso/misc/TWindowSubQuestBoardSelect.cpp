#include "pso/misc/WindowLayoutDescriptor.h"
#include "pso/misc/TWindowSubStatusDisp_80144B14.h"
#include "pso/system/SoundEffect.h"
#include "types.h"
#include "pso/quest/TQuestThread.h"
#include "pso/misc/TWindowChoiceSetting.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TWindowSubQuestBoard.h"
#include "pso/misc/TWindowSubQuestBoardSelect.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/misc/TWindowSubStatusDisp_8025A9B4.h"
#include "pso/misc/TWindowBase.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

struct RecoveredGlobal_8027D230_lbl_805129F8 {
    s32 value;
    u8 remaining[0xD4];
};

struct Ctx_8027D444 {
    u8 pad0[0x10];
    f32 x;
    f32 y;
    u8 pad18[0x30 - 0x18];
    s32 fade;
    u8 pad34[0x38 - 0x34];
    f32 depth;
};

struct Entry_8027D444 {
    u8 pad0[0x8];
    f32 x;
    f32 y;
    f32 w;
};

struct Vec2_8027D444 { f32 x, y; };

struct Lines_8027D444 {
    Vec2_8027D444 *verts;
    u32 *colors;
    s32 f8;
    s32 count;
};

struct RecoveredGlobal_8027D888_lbl_8050E208 {
    s32 value;
    u8 remaining[0x1AC];
};

struct Ent_8027D6A0 { u8 pad0[0x20]; u8 f20[0x30]; };

struct Win_8027D6A0 { u8 pad0[0x61]; s8 f61; };

typedef s32 (*SlotFlagFn)(void *, u8);

extern "C" {
void measure_message_text_width(void *, f32);
extern RecoveredGlobal_8027D230_lbl_805129F8 quest_board_handlers;
typedef char RecoveredGlobal_8027D230_lbl_805129F8_size[sizeof(RecoveredGlobal_8027D230_lbl_805129F8) == 0xD8 ? 1 : -1];

void TWindowSubQuestBoardSelect::sub_8027D230() {
    u8 *arg0 = (u8 *)this;
    u8 *temp_r31;
    u8 *temp_r3;
    temp_r31 = (u8 *)&quest_board_handlers.value + ((s8) this->m_61 * 0x24);
    temp_r3 = (u8 *)(((TWindowBase *)arg0)->get_array_entry(1));
    set_text_entry_string((u8 *)temp_r3, (u32)temp_r31, 0);
    measure_message_text_width(temp_r3, 100000.0f);
    *(f32 *)((s8 *)temp_r3 + 8) = (f32) (385.0f - *(f32 *)((s8 *)temp_r3 + 0x10));
}

extern s32 quest_mission_manager;

s32 get_slot_flag__26TWindowSubQuestBoardSelectFic(s32 arg0, s8 arg1) {
    if (arg1 < 0) {
        return 0;
    }
    if (arg1 > 6) {
        return 0;
    }
    return TQuestThread::get_register((u8 *)quest_mission_manager, arg1 + 0x4A);
}

void TWindowSubQuestBoardSelect::update_slot_display_flags() {
    s32 var_r30;
    s32 var_r29;
    u16 *temp_r31;
    u16 *temp_r3;

    var_r29 = 1;
    var_r30 = 0;
    do {
        temp_r31 = (u16 *)get_array_entry(var_r30 + 2);
        if (((s32 (*)(void *, s8))get_slot_flag__26TWindowSubQuestBoardSelectFic)(this, (s8) var_r30) == 0) {
            *temp_r31 |= 2;
        } else {
            var_r29 = 0;
            *temp_r31 &= 0xFFFFFFFD;
        }
        var_r30 += 1;
    } while (var_r30 < 6);
    temp_r3 = (u16 *)get_array_entry(1);
    if (var_r29 != 0) {
        *(s8 *)&this->m_61 = -1;
        *temp_r3 |= 2;
        this->m_60 = (u8) (this->m_60 | 4);
        return;
    }
    *temp_r3 &= 0xFFFFFFFD;
    this->m_60 = (u8) (this->m_60 & 0xFFFFFFFB);
}


void TWindowSubQuestBoardSelect::select_next() {
    u8 temp_r3;

    if ((is_shortcut_active() == 0) && (((s32 (*)(void *, u8))get_slot_flag__26TWindowSubQuestBoardSelectFic)(this, this->m_61) == 0)) {
        do {
            this->m_61 = (this->m_61 + 1);
            temp_r3 = this->m_61;
            if ((s8) temp_r3 > 6) {
                this->m_61 = (temp_r3 - 6);
            }
        } while (((s32 (*)(void *, u8))get_slot_flag__26TWindowSubQuestBoardSelectFic)(this, this->m_61) == 0);
        sub_8027D230();
    }
}

void TWindowSubSymbolChatFaceType__sub_80283C84(void *, void *, f32, f32);
void draw_color_lines(Lines_8027D444 *l, s32 n, s32 flags, f32 scale);

void TWindowSubQuestBoardSelect__sub_8027D444(TWindowSubQuestBoardSelect *self, Ctx_8027D444 *ctx) {
    Vec2_8027D444 v[3];
    Lines_8027D444 d;
    u32 colors[3];
    Entry_8027D444 *e;
    f32 x;
    f32 y;
    u32 alpha;
    f32 x2;
    f32 y2;
    f32 depth;

    if (ctx->fade < 0) {
        return;
    }
    if (((SlotFlagFn)get_slot_flag__26TWindowSubQuestBoardSelectFic)(self, self->m_61) == 0) {
        return;
    }
    e = (Entry_8027D444 *)self->get_array_entry((s8)self->m_61 + 2);
    TWindowSubSymbolChatFaceType__sub_80283C84(ctx, &e->x, 56.0f, 0.3f);
    x = ctx->x + e->x;
    y = ctx->y + e->y;
    if (ctx->fade < 6) {
        alpha = (u32)(0.16666667f * (f32)(ctx->fade * 255)) << 24;
    } else {
        alpha = 0xFF000000;
    }
    e = (Entry_8027D444 *)self->get_array_entry(1);
    depth = 0.1794f + ctx->depth;
    d.verts = v;
    d.colors = colors;
    d.f8 = 0;
    d.colors[0] = alpha | 0xFF0000 | 0x7E00;
    d.colors[1] = d.colors[0];
    d.colors[2] = d.colors[0];
    d.count = 3;
    v[0].x = 28.0f + x;
    v[0].y = 7.0f + y;
    x2 = ctx->x + e->x;
    y2 = ctx->y + e->y;
    v[1].x = x2;
    v[1].y = 20.0f + y2;
    v[2].x = x2 + e->w;
    v[2].y = v[1].y;
    draw_color_lines(&d, 3, 0x10, depth);
}



void TWindowSubQuestBoardSelect::handle_cancel() {
    if (is_open() == 0) {
        play_sound_effect(0x52F16, 0, 0, 0);
        this->m_60 = (u8) (this->m_60 | 2);
    }
}

void TWindowSubQuestBoardSelect::handle_decide() {
    if (is_shortcut_active() == 0) {
        play_sound_effect(0x52D01, 0, 0, 0);
        this->m_60 = (u8) (this->m_60 | 1);
    }
}

s32 draw_visible_window_entries(void *, void *, int);
s32 forward_render__20TWindowSubStatusDispFv(int, int);
s32 test_flag_4c__23TAdSinglePlyChrSelectGCFv(void *, int);
s32 TWindowShortListCtrl__check_controller_button(int, int);
extern RecoveredGlobal_8027D888_lbl_8050E208 controller_input_state;

#define TBL_8027D6A0 ((Ent_8027D6A0 *)&controller_input_state)
s32 TWindowSubQuestBoardSelect::handle_page_input() {
    Win_8027D6A0 *self = (Win_8027D6A0 *)this;
    void *p;
    s8 d;
    if (is_shortcut_active() == 0 &&
        (TWindowChoiceSetting::apply_choice((s32)(p = TBL_8027D6A0[0].f20), 0xC0, 6, 1) != 0 ||
        TWindowChoiceSetting::apply_choice((s32)TBL_8027D6A0[4].f20, 0xC0, 6, 1) != 0)) {
        play_sound_effect(0x54100, 0, 0, 0);
        d = 0;
        if (TWindowChoiceSetting::apply_choice((s32)p, 0x80, 6, 1) != 0 ||
            TWindowChoiceSetting::apply_choice((s32)TBL_8027D6A0[4].f20, 0x80, 6, 1) != 0) {
            d = 1;
        }
        if (TWindowChoiceSetting::apply_choice((s32)p, 0x40, 6, 1) != 0 ||
            TWindowChoiceSetting::apply_choice((s32)TBL_8027D6A0[4].f20, 0x40, 6, 1) != 0) {
            d--;
        }
        if (d != 0) {
            do {
                self->f61 += d;
                if (self->f61 < 0) {
                    self->f61 += 6;
                }
                if (self->f61 >= 6) {
                    self->f61 -= 6;
                }
            } while (((SlotFlagFn)get_slot_flag__26TWindowSubQuestBoardSelectFic)(self, self->f61) == 0);
            ((TWindowSubQuestBoardSelect *)self)->sub_8027D230();
        }
    }
}

void TWindowSubQuestBoardSelect::render() {
    s32 context;
    context = TWindowDD::draw_default_entry((s32)this);
    draw_window_frame((void *)context);
    forward_render__20TWindowSubStatusDispFv((s32)m_64, context);
    TWindowSubQuestBoardSelect__sub_8027D444(this, (Ctx_8027D444 *)context);
    draw_visible_window_entries(this, (u8 *)this + 0x24, context);
}
typedef char RecoveredGlobal_8027D888_lbl_8050E208_size[sizeof(RecoveredGlobal_8027D888_lbl_8050E208) == 0x1B0 ? 1 : -1];
void TWindowSubQuestBoardSelect::run_task() {
    u8 *arg0 = (u8 *)this;
    u8 *temp_r31;
    if (((TWindowSubQuestBoardSelect *)arg0)->is_open() == 0) {
        ((TWindowSubQuestBoardSelect *)arg0)->select_next();
        handle_page_input();
        temp_r31 = (u8 *)&controller_input_state.value + 0x20;
        if ((TWindowShortListCtrl__check_controller_button((int)temp_r31, 4) != 0) || (test_flag_4c__23TAdSinglePlyChrSelectGCFv((void *) ((u8 *)&controller_input_state.value + 0x160), 4) != 0)) {
            ((TWindowSubQuestBoardSelect *)arg0)->handle_decide();
        }
        if ((TWindowShortListCtrl__check_controller_button((int)temp_r31, 2) != 0) || (test_flag_4c__23TAdSinglePlyChrSelectGCFv((void *) ((u8 *)&controller_input_state.value + 0x160), 2) != 0)) {
            ((TWindowSubQuestBoardSelect *)arg0)->handle_cancel();
        }
    }
    ((TWindowDD *)arg0)->initialize_subwindow();
    if ((f32) *(s32 *)&this->m_5c >= 7.5f) {
        *(s32 *)&this->m_5c = 0x186A0;
        ((TWindowSubStatusDisp *)(*(s32 *)&this->m_64))->update_subwindow();
    }
    ((TWindowBase *)arg0)->update_fade();
    ((TWindowBase *)arg0)->update_window_entry_list((u8 *)&this->m_24);
}

TWindowSubQuestBoardSelect::~TWindowSubQuestBoardSelect() {
    TWindowSubStatusDisp::destroy_status_display((s32)m_64, 1);
}

u8 *get_window_layout_position(s32);
void *construct_type1_heading__20TWindowSubStatusDispFll(void *storage, s32 text, s32 client);
s32 get_field_20__17TWindowSubComCardFv(void *entry);
extern u8 lbl_804D1848[];
WindowLayoutDescriptor TWindowSubQuestBoardSelect__window_parameters = {
    {434.0f, 184.0f}, 50150.0f, lbl_804D1848, 3
};
extern const char *TWindowSubQuestBoardSelect__class_name;
#pragma push
#pragma fp_contract on
TWindowSubQuestBoardSelect::TWindowSubQuestBoardSelect()
    : TWindowBase((u8 *)&TWindowSubQuestBoardSelect__window_parameters, 4,
                  get_window_layout_position(0x70)) {
    f32 width;
    u8 *entry;
    void *heading;
    m_name = TWindowSubQuestBoardSelect__class_name;
    heading = ::operator new(0x24);
    if (heading != NULL) {
        heading = construct_type1_heading__20TWindowSubStatusDispFll(
            heading, (s32)TWindowSubStatusDisp::get_message_10(0x2B), m_20);
    }
    m_64 = heading;
    m_60 = 0;
    entry = (u8 *)get_array_entry(0);
    set_text_entry_string(entry, (u32)TQuestThread::get_quest_name(), 0);
    width = (f32)calc_text_width((char *)get_field_20__17TWindowSubComCardFv(entry));
    *(f32 *)(entry + 8) = 210.0f - 0.5f * width;
    m_61 = -1;
    update_slot_display_flags();
    select_next();
}

#pragma pop

}
