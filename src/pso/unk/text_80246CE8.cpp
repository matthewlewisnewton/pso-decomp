#include "types.h"
#include "pso/misc/TWindowChallengeResult.h"
#include "pso/unk/text_80246CE8.h"
#include "pso/misc/TWindowBase.h"

extern "C" {
s32 draw_visible_window_entries(void *, void *, int);
void TWindowChallengeResult::render() {
    s32 context = setup_window_draw_context((s32)&scale_x);
    draw_window_frame((void *)context);
    draw_visible_window_entries(this, &m_24, context);
}

}
