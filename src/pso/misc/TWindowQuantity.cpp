#include "types.h"
#include "pso/misc/TWindowSubStatusDisp_8025A9B4.h"
#include "pso/misc/TWindowSubStatusDisp_80287570.h"
#include "pso/ui/TObjBagWarnWin_8006EF24.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowQuantity.h"
#include "pso/misc/WindowLayoutDescriptor.h"
#include "pso/misc/TWindowOptionCtrl_8026CBA4.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowSubStatusDisp.h"

extern "C" {
extern u8 lbl_804D0830[];
WindowLayoutDescriptor quantity_window_layout = {
    {160.0f, 27.0f}, 50100.0f, lbl_804D0830, 0x82B
};
}


extern "C" {
s32 draw_visible_window_entries(void *, void *, int);
u32 calc_text_width(void);
extern const char *lbl_805D39B0;
static const f32 lbl_805DD2D0 = 24.0f;
static const f32 lbl_805DD2D4 = 12.0f;
static const f32 lbl_805DD2D8 = 8.0f;
static const f32 lbl_805DD2DC = 0.75f;
extern const f32 lbl_805DD2E0;
s32 draw_window_tab(s32, s32, s32, f32);
int initialize_subwindow__9TWindowDDFv(void*);

void TWindowQuantity::set_position(s32 arg1) {
    draw_window_tab(arg1, arg1 + 0x10, 3, this->m_60);
}

void TWindowQuantity::render() {
    s32 ctx;
    ctx = setup_window_draw_context((s32)&m_64);
    set_position(ctx);
    draw_visible_window_entries(this, (u8 *)this + 0x24, ctx);
}

void TWindowQuantity::run_task() { initialize_subwindow__9TWindowDDFv(this); update_window_entry_list((char*)this + 0x24); }

TWindowQuantity::~TWindowQuantity() {}

TWindowQuantity::TWindowQuantity(s32 client)
    : TWindowBase((u8 *)&quantity_window_layout, (s16)client,
        (u8 *)get_window_layout_position(0x2A)) {
    u8 *e1;
    u8 *e0;
    s32 id;
    f32 n;
    m_name = lbl_805D39B0;
    id = TQuestVmDownLoadServer__sub_8006EF6C(1);
    n = (f32)calc_text_width();
    m_60 = TWindowSubStatusDisp__sub_802877A4(lbl_805DD2D0 + (lbl_805DD2D4 + n));
    e0 = (u8 *)get_array_entry(0);
    e1 = (u8 *)get_array_entry(1);
    set_text_entry_string(e0, id, 0);
    *(f32 *)(e1 + 8) = lbl_805DD2D0 + (lbl_805DD2D4 + (lbl_805DD2D8 + n));
    m_38 = TWindowSubStatusDisp::get_base_y(m_60);
    save_position();
    if (TCameraCtrl::get_camera_id() > 2) {
        m_64 = lbl_805DD2DC;
        m_68 = lbl_805DD2DC;
    } else {
        m_64 = lbl_805DD2E0;
        m_68 = lbl_805DD2E0;
    }
}

TWindowQuantity *create_window_quantity(s32 client) {
    return new TWindowQuantity(client);
}

}
