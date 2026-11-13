#define TOBJECT_OUT_OF_LINE_HELPERS // Preserve the original out-of-line destruction queue call.
#include "pso/TChCrEffFade.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/unk/text_80293D84.h"

extern "C" {
s32 TCameraCtrl__sub_80068EF0();
extern const char *lbl_805D3CC0;
extern TObject *tl_fade;
}

void TChCrEffFade::render() {
    f32 opacity;

    TCameraCtrl::restore_full_screen_view();
    switch (m_mode) {
    case 0:
        draw_fade_strip(m_opacity);
        break;
    case 1:
        fn_80293E58(this, m_opacity);
        opacity = m_opacity;
        draw_fade_strip(opacity * opacity);
        break;
    }
    TCameraCtrl__sub_80068EF0();
}

void TChCrEffFade::update_fade() {
    s32 frame = m_frame;

    // Keep full opacity through frame 3, then fade to zero at m_duration.
    if (frame <= 3) {
        m_opacity = 1.0f;
        return;
    }
    m_opacity = 1.0f - ((frame - 3) / (f32)(m_duration - 3));
}

void TChCrEffFade::run_task() {
    s32 frame;

    m_frame += m_direction;
    update_fade();
    frame = m_frame;
    if (frame <= 0 || frame >= m_duration) {
        queue_destruction();
    }
}

TChCrEffFade::~TChCrEffFade() {}

TChCrEffFade::TChCrEffFade(s32 direction, s32 duration, s32 mode)
    : TObject(tl_fade) {
    s32 bounded_duration;
    s32 step;

    m_name = lbl_805D3CC0;
    m_direction = direction;
    m_duration = duration + 3;
    bounded_duration = m_duration;
    if (bounded_duration < 4) {
        m_duration = 4;
    } else if (bounded_duration > 450) {
        m_duration = 450;
    }
    step = m_direction;
    if (step == 1) {
        m_frame = 0;
    } else if (step == -1) {
        m_frame = m_duration;
    } else {
        m_direction = 1;
        m_frame = 0;
    }
    update_fade();
    m_mode = mode;
}
