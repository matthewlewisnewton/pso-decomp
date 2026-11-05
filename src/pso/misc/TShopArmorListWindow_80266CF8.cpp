#include "types.h"
#include "pso/misc/TWindowSubStatusDisp_80257784.h"
#include "pso/misc/TShopArmorListWindow.h"
#include "pso/misc/TWindowSubStatusDisp.h"

struct Win_80266CF8 { u8 p0[0x72]; s16 f72; s16 f74; u8 p76[2]; s16 f78; };

extern "C" {
void *get_array_entry__13TUnk_804CE018Fi(void *, s32);
s32 select_cursor_entry__22TWindowSubShortCutListFv();

void TShopArmorListWindow::clamp_selection_to_valid_entry() {
    Win_80266CF8 *w = (Win_80266CF8 *)this;
    void *e;
    if (w->f72 >= 0) {
        if (w->f78 >= w->f72) {
            w->f74 = w->f72 - 1;
            return;
        }
        e = get_array_entry__13TUnk_804CE018Fi(w, w->f78);
        while (((TWindowSubStatusDisp *)e)->is_flag_4_set() == 0) {
            w->f78 = w->f78 - 1;
            e = get_array_entry__13TUnk_804CE018Fi(w, w->f78);
        }
        w->f74 = w->f78;
    }
}

void TShopArmorListWindow::save_cursor_selection() {
    this->m_78 = (s16) this->m_74;
    this->m_7c = select_cursor_entry__22TWindowSubShortCutListFv();
}
void TShopArmorListWindow::reset_list() {
    u32 i;
    this->m_72 = 0;
    this->m_74 = 0;
    for (i = 0; i < (u32)*(s16 *)&this->unk_76; i++) {
        reset__20TWindowSubStatusDispFPv(get_array_entry__13TUnk_804CE018Fi(this, i));
    }
}

}
