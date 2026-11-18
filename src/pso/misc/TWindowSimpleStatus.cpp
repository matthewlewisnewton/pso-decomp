#include "pso/misc/WindowLayoutDescriptor.h"
#include "types.h"
#include "pso/misc/TWindowSubComCard_80244774.h"
#include "pso/misc/TWindowSubStatusDisp_8026F6DC.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowSimpleStatus.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowSubComCard.h"

extern "C" {
s32 draw_visible_window_entries(void *, void *, int);
extern const char *TWindowSimpleStatus__name;
extern const f32 lbl_805DD3EC;
s32 get_window_layout_position(s32);
s32 update_hp_tp_level__20TWindowSubStatusDispFv();

void TWindowSimpleStatus::render() {
    s32 context = TWindowDD::draw_default_entry((s32)this);
    draw_background((u8 *)context);
    draw_visible_window_entries(this, (u8 *)this + 0x24, context);
}

void TWindowSimpleStatus::run_task() {
    s32 arg0 = (s32)this;
    update_hp_tp_level__20TWindowSubStatusDispFv();
    update_lockon_window((u8 *)arg0);
    update_status_help_item(arg0);
    ((TWindowSimpleStatus *)arg0)->update_status_icons((void *)(get_window_layout_position(0x1D)));
    ((TWindowDD *)arg0)->initialize_subwindow();
    ((TWindowBase *)arg0)->update_fade();
    ((TWindowBase *)arg0)->update_window_entry_list((void *)(arg0 + 0x24));
    ((TWindowSimpleStatus *)arg0)->apply_random_shake();
}

extern u8 lbl_804D0B58[];
WindowLayoutDescriptor simple_status_window_layout = {
    {153.0f, 50.0f}, 50100.0f, lbl_804D0B58, 0xB28
};

TWindowSimpleStatus::~TWindowSimpleStatus() {
    // Original cleanup closes four although icon refresh manages five slots.
    for (s32 i = 0; i < 4; i++) {
        if (icon_windows[i] != NULL) {
            icon_windows[i]->close();
            icon_windows[i] = NULL;
        }
    }
}

TWindowSimpleStatus::TWindowSimpleStatus(void *position, s32 client, u8 *descriptor)
    : TWindowBase(descriptor, (s16)client, (u8 *)position) {
    m_name = TWindowSimpleStatus__name;
    m_20 = client;
    m_60 = 0;
    m_58 = lbl_805DD3EC;
    for (s32 i = 0; i < 5; i++) {
        icon_windows[i] = NULL;
    }
}

TWindowSimpleStatus *TWindowSimpleStatus::create(void *position, s32 client) {
    return new TWindowSimpleStatus(position, client, (u8 *)&simple_status_window_layout);
}

}
