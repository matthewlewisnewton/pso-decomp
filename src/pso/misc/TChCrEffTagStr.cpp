#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/TChCrEffTagStr.h"
#include "pso/misc/TChCrEffTagStr.h"
#include "pso/render/render_util.h"
#include <stddef.h>

typedef char TChCrEffTagStr_state_offset[offsetof(TChCrEffTagStr, fade_state) == 0x1C ? 1 : -1];
typedef char TChCrEffTagStr_sprite_offset[offsetof(TChCrEffTagStr, sprite_id) == 0x20 ? 1 : -1];
typedef char TChCrEffTagStr_fade_offset[offsetof(TChCrEffTagStr, fade) == 0x24 ? 1 : -1];
typedef char TChCrEffTagStr_position_offset[offsetof(TChCrEffTagStr, position) == 0x28 ? 1 : -1];

#pragma readonly_strings on
const char *TChCrEffTagStr__name = "TChCrEffTagStr";

extern "C" {
s32 draw_creation_sprite_offset(s32, void *, f32 *, f32, f32, f32, f32, f32);
// This legacy symbol copies two floats; its receiver is raw vector storage.
void copy_vec2__28TWindowSubSymbolChatPartsSetFPv(void *, void *);

void TChCrEffTagStr__sub_8029AED0(void *p) {
    static_cast<TChCrEffTagStr *>(p)->fade_state = 1;
}

#pragma push
#pragma fp_contract on
void TChCrEffTagStr::render() {
    f32 scale[2];
    f32 amount;
    f32 remaining;
    set_depth_buffer_settings_1();
    amount = fade;
    remaining = 1.0f - amount;
    scale[1] = amount * amount;
    scale[0] = (0.5f * remaining) + 1.0f;
    draw_creation_sprite_offset(sprite_id, position, &scale[0], -2.4375f, amount, remaining, 1.0f, 0.5f);
    restore_saved_depth_alpha_state();
}
#pragma pop

#pragma push
#pragma opt_common_subs off
void TChCrEffTagStr::run_task() {
    f32 next;
    f32 amount;
    f32 fade_in_step = 0.13333334f;
    f32 fade_out_step = -0.06666667f;
    switch (fade_state) {
    case 0:
        amount = fade;
        if (!(amount >= 1.0f)) {
            next = amount + fade_in_step;
            fade = next;
            if (next >= 1.0f) {
                fade = 1.0f;
                break;
            }
        }
        break;
    case 1:
        next = fade + fade_out_step;
        fade = next;
        if (next <= 0.0f) {
            fade = 0.0f;
            queue_destruction();
        }
        break;
    }
}
#pragma pop

TChCrEffTagStr::~TChCrEffTagStr() {}
}
TChCrEffTagStr::TChCrEffTagStr(TObject *object, void *sprite, void *pos) : TObject(object) {
    m_name = TChCrEffTagStr__name;
    // The existing factory ABI passes the numeric sprite ID as void *.
    sprite_id = (s32)sprite;
    copy_vec2__28TWindowSubSymbolChatPartsSetFPv(position, pos);
    fade_state = 0;
    fade = 0.0f;
}
