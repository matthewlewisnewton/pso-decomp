#include "types.h"
#include "pso/ui/window/TWindowDrawContext.h"
#include "pso/ui/window/TWindowAddition.h"

#pragma readonly_strings on

extern "C" {
const char *lbl_805D3878 = "TWindowAddition";
}

#pragma push
#pragma fp_contract on
void TWindowAddition::step_window_tween() {
    f32 d;
    u32 n = tween_ticks;
    if (n == 0) {
        d = target_size[0] - frame_size[0];
        save_position();
    } else {
        d = (target_size[1] - frame_size[1]) / n;
        frame_position[0] += (target_position[0] - frame_position[0]) / n;
        frame_position[1] += (target_position[1] - frame_position[1]) / tween_ticks;
        frame_size[0] += (target_size[0] - frame_size[0]) / tween_ticks;
        frame_size[1] += d;
        tween_ticks--;
    }
    scroll_offset[1] -= 0.5f * d;
}
#pragma pop

TWindowDrawContext *TWindowAddition::setup_content_draw_context() {
    TWindowDrawContext *context = setup_window_draw_context(content_scale);
    context->inner_x -= scroll_offset[0];
    context->inner_y -= scroll_offset[1];
    return context;
}

void TWindowAddition::init_content_frame(u8 *descriptor) {
    m_name = lbl_805D3878;
    scroll_offset[0] = 0.0f;
    scroll_offset[1] = 0.0f;
    set_content_scale(1.0f, 1.0f);
}
