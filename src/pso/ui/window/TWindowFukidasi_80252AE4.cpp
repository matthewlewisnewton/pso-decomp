#include "pso/ui/window/TUnk_804CF0B8.h"
#include "pso/ui/window/TWindowCtrl.h"
#include "pso/boss/darkfalz/TOBoss4Rock.h"

extern "C" {
u8 *get_zero_vec2();
extern u8 window_fukidasi_addition_params[];
}

TUnk_804CF0B8::~TUnk_804CF0B8() {
    if (is_flag_set()) {
        clear_visible_flag();
        TWindowCtrl::release_slot(&m_73);
    }
    if (name != NULL) {
        mem_free(name);
        name = NULL;
    }
}

TUnk_804CF0B8::TUnk_804CF0B8(u16 speaker, s32 text, s32 client, f32 scale)
    : TWindowAddition(window_fukidasi_addition_params, (s16)client, get_zero_vec2()) {
    sub_80251DF0(speaker, text, client, scale);
}
