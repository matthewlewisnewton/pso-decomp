#include "types.h"
#include "pso/TObject.h"
#include "pso/misc/TWindowCtrl.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TUnk_804CE964.h"
#include "pso/unk/text_8026CB5C.h"
#include "pso/misc/TWindowTradeRequest.h"

extern "C" {
s32 draw_visible_window_entries(void *, void *, int);
int initialize_subwindow__9TWindowDDFv(void*);
extern "C" u8 lbl_805D63F0[];
void set_help_mode__14TWindowComCardFl(void *entry, s32 arg1);
extern const f32 lbl_805DCBD0;
extern struct Obj054_80249DE4 *TWindowCtrl__active_window;
extern u16 lbl_805D63FC;
struct Obj054_80249DE4 { char pad[0x38]; u32 field38; };
void request_active_window_close(void);
void queue_destruction__7TObjectFv(void *);

void *lbl_804CE918[14] = {
    (void *)0x1, (void *)0x1, (void *)0x6, (void *)0x0,
    (void *)0x0, (void *)0x42000000, (void *)0x41e00000, (void *)0x0,
    (void *)0x0, (void *)0x3f000000, (void *)0xffffffff, (void *)&lbl_805D63F0,
    (void *)0x1, (void *)0x4,
};
void *TWindowComCard__window_desc_b[5] = {
    (void *)0x42000000, (void *)0x41e00000, (void *)0x4788d100, (void *)&lbl_804CE918,
    (void *)0x82b,
};
#define TWindowComCard__window_desc_b ((s32 *)TWindowComCard__window_desc_b)
}

// Deferred compilation emits these definitions in reverse order.
extern "C" {
void request_active_window_close(void) {
    if ((TWindowCtrl__active_window != NULL) && (TWindowCtrl__active_window->field38 != 0U)) {
        ((TWindowCtrl *)((void*)TWindowCtrl__active_window->field38))->set_flag1e_bit8();
    }
}


void TWindowTradeRequest::close_request_window() {
    u8 *object;
    lbl_805D63FC &= 0xFFFFFFF7;
    if ((void *) (*(u8 * *)&TWindowCtrl__active_window) != NULL) {
        object = (u8 *)(*(u8 **)((s8 *)(*(u8 * *)&TWindowCtrl__active_window) + 0x40));
        if (object != NULL) {
            queue_destruction__7TObjectFv(object);
            *(u8 **)((s8 *)(*(u8 * *)&TWindowCtrl__active_window) + 0x40) = NULL;
        }
    }
}

#pragma push
#pragma fp_contract on
TUnk_804CE964::TUnk_804CE964(TWindowBase *parent, ComCardWindowOffset *ofs, s32 col, s32 mode, s32 client)
    : TWindowBase((u8 *)TWindowComCard__window_desc_b, (s16)client, (u8 *)get_zero_vec2()) {
    m_60 = parent;
    offset.x = ofs->x;
    offset.y = ofs->y;
    m_6c = col;
    m_70 = mode;
    m_30 = lbl_805DCBD0 * (f32)m_6c + (m_60->m_40 + offset.x);
    m_34f = m_60->m_44 + offset.y;
    save_position();
    set_help_mode__14TWindowComCardFl(get_array_entry(0), mode);
}
#pragma pop


TUnk_804CE964::~TUnk_804CE964() {}

void TUnk_804CE964::run_task() {
    u8 *arg0 = (u8 *)this;
    f32 temp_f1;
    u8 *temp_r4;
    temp_r4 = (unsigned char *) (this->m_60);
    temp_f1 = *(f32 *)((s8 *)temp_r4 + 0x44);
    this->m_34f = (f32) (temp_f1 + this->offset.y);
    this->m_44 = (f32) this->m_34f;
    ((s32 (*)(void *, int, f32))initialize_subwindow__9TWindowDDFv)((void *)arg0, (int)temp_r4, (f32)temp_f1);
    ((TWindowBase *)arg0)->update_fade();
    ((TWindowBase *)arg0)->update_window_entry_list(arg0 + 0x24);
}

void TUnk_804CE964::render() {
    s32 arg0 = (s32)this;
    s8 *tmp = (s8 *)TWindowDD::draw_default_entry(arg0);
    ((s32 (*)(s32, s32, s32))draw_visible_window_entries)(arg0, arg0 + 0x24, (s32)tmp);
}

#pragma push
#pragma fp_contract on
void TWindowComCard__sub_80249D7C(u8 *arg0, s32 arg1) {
    if ((s32) *(s32 *)((s8 *)arg0 + 0x6C) != arg1) {
        *(s32 *)((s8 *)arg0 + 0x6C) = arg1;
        *(f32 *)((s8 *)arg0 + 0x30) = (f32) ((lbl_805DCBD0 * (f32) *(s32 *)((s8 *)arg0 + 0x6C)) + (*(f32 *)((s8 *)(*(void **)((s8 *)arg0 + 0x60)) + 0x40) + *(f32 *)((s8 *)arg0 + 0x64)));
        *(s32 *)((s8 *)arg0 + 0x50) = 0xF;
    }
}
#pragma pop

void TUnk_804CE964::set_selected_index(s32 arg1) {
    s32 temp;
    if ((s32) *(s32 *)((s8 *)this + 0x70) != arg1) {
        *(s32 *)((s8 *)this + 0x70) = arg1;
        temp = (s32)this->get_array_entry(0);
        set_help_mode__14TWindowComCardFl((void *)temp, *(s32 *)((s8 *)this + 0x70));
    }
}
}

s32 get_status_effect_icon_index(u32 arg0);
s32 get_status_effect_icon_index(u32 arg0) {
    switch (arg0) {
    case 3:
        return 1;
    case 9:
        return 6;
    case 10:
        return 8;
    case 11:
        return 7;
    case 12:
        return 9;
    case 15:
        return 3;
    case 16:
        return 4;
    case 17:
        return 5;
    case 18:
        return 0;
    case 2:
        return 2;
    default:
        return 0xE;
    }
}
