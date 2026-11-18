#include "types.h"
#include "pso/ui/window/TWindowChoiceSetting.h"


#pragma push
#pragma fp_contract on
void TWindowChoiceSetting::sub_80249078() {
    f32 target;
    u32 steps;

    if (this->m_80 & 1) {
        steps = this->get_array_entry(this->get_field_74());
        target = *(f32 *)(steps + 0xC);
    } else {
        target = 0.0f;
    }
    steps = tween_ticks;
    if (steps == 0) {
        scroll_offset[1] = target;
        return;
    }
    target += 0.5f * (this->target_size[1] - this->frame_size[1]);
    scroll_offset[1] += (target - scroll_offset[1]) / (f32)steps;
}
#pragma pop
