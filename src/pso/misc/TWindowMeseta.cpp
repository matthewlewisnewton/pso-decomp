#include "types.h"
#include "pso/misc/TWindowSubStatusDisp_8025A9B4.h"
#include "pso/misc/TWindowSubStatusDisp_80287570.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowMeseta.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowSubStatusDisp.h"

#pragma readonly_strings on

extern "C" {
const char *TWindowMeseta__class_name = "TWindowMeseta";
}


struct Sub_80269244 { u8 pad0[8]; f32 x8; };



extern "C" {
extern s32 TWindowMeseta__window_descriptor[];
extern const char *TWindowMeseta__class_name;


void TWindowMeseta::run_task() {
    u8 *arg0 = (u8 *)this;
    s32 temp_r3;

    temp_r3 = get_meseta_value();
    if (temp_r3 != (s32) this->m_68) {
        this->m_68 = temp_r3;
        ((TWindowSubStatusDisp *)(((TWindowBase *)arg0)->get_array_entry(1)))->set_animated_target(this->m_68, 9.0f);
    }
    ((TWindowDD *)arg0)->initialize_subwindow();
    ((TWindowBase *)arg0)->update_window_entry_list((u8 *)&this->m_24);
}

TWindowMeseta::~TWindowMeseta() {}

TWindowMeseta::TWindowMeseta(void *position, s32 client, s32 text)
    : TWindowBase((u8 *)TWindowMeseta__window_descriptor, (s16)client, (u8 *)position) {
    Sub_80269244 *a;
    Sub_80269244 *b;
    m_name = TWindowMeseta__class_name;
    m_64 = client;
    m_68 = get_meseta_value();
    a = (Sub_80269244 *)get_array_entry(0);
    b = (Sub_80269244 *)get_array_entry(1);
    set_text_entry_string((u8 *)a, (u32)text, 0);
    ((TWindowSubStatusDisp *)b)->set_all_values(m_68);
    m_38 = 10.0f + b->x8;
    save_position();
    m_60 = TWindowSubStatusDisp__sub_802877A4(m_48 - 16.0f);
    if (TCameraCtrl::get_camera_id() > 2) {
        m_6c = 0.75f;
        m_70 = 0.75f;
    } else {
        m_6c = 1.0f;
        m_70 = 1.0f;
    }
}

}
