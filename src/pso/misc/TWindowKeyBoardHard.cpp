#include "types.h"
#include "pso/misc/TWindowSubStatusDisp_8024FBA8.h"
#include "pso/misc/TKeyBoardControl_8025CB70.h"
#include "pso/misc/TWindowKeyBoardHard.h"
#include "pso/misc/TWindowKeyBoardBase.h"
#include "pso/misc/TWindowDrawContext.h"
#include "pso/misc/TWindowDD.h"
#include "pso/ui/Language.h"

#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
struct Pt_80260020 { f32 x, y; };




extern "C" {
extern s32 lbl_8044F0CC[];
extern s32 lbl_8044F0D4[];
extern s32 keyboard_hard_status_text_a[];
extern s32 keyboard_hard_status_text_b[];
extern s32 lbl_8044F0FC[];
extern s32 lbl_8044F104[];
static const f32 lbl_805DD068 = -1.0f;
static const f32 lbl_805DD06C = 100000.0f;
extern const f32 lbl_805DD070;

void TWindowKeyBoardHard::release_keyboard() { TWindowKeyBoardBase* m = this->m_composer; if (m) m->reset_input_flags_for_language(); }

void TWindowKeyBoardHard::draw_status_text(TWindowDrawContext *ctx) {
    s32 flags;
    if (m_composer != NULL && current_language == LANGUAGE_JAPANESE) {
        f32 inv = lbl_805DD068 / ctx->depth;
        Pt_80260020 pt;
        pt.x = ctx->inner_x;
        pt.y = ctx->inner_y;
        set_text_draw_params((s32)ctx, 0, 0, (f32)inv, (f32)lbl_805DD06C);
        flags = m_composer->m_b4;
        if (!(flags & 1)) {
            draw_window_text((f32 *)&pt, (const char *)lbl_8044F0CC, -1, 0, (f32)lbl_805DD070);
        } else if (flags & 2) {
            draw_window_text((f32 *)&pt, (const char *)lbl_8044F0D4, -1, 0, (f32)lbl_805DD070);
        } else if (flags & 4) {
            if (flags & 8) {
                draw_window_text((f32 *)&pt, (const char *)keyboard_hard_status_text_a, -1, 0, (f32)lbl_805DD070);
            } else {
                draw_window_text((f32 *)&pt, (const char *)keyboard_hard_status_text_b, -1, 0, (f32)lbl_805DD070);
            }
        } else if (flags & 8) {
            draw_window_text((f32 *)&pt, (const char *)lbl_8044F0FC, -1, 0, (f32)lbl_805DD070);
        } else {
            draw_window_text((f32 *)&pt, (const char *)lbl_8044F104, -1, 0, (f32)lbl_805DD070);
        }
    }
}

void TWindowKeyBoardHard::render() {
    s32 temp;
    if (((s32) this->m_68 > 0) && (is_key_active() == 0)) {
        temp = TWindowDD::draw_default_entry((s32)this);
        draw_status_text((TWindowDrawContext *)temp);
    }
}

}
