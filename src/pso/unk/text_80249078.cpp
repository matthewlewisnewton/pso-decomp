#include "types.h"
#include "pso/misc/TWindowChoiceSetting.h"


#pragma push
#pragma fp_contract on
void TWindowChoiceSetting::sub_80249078() {
    f32 target;
    u32 steps;

    if (this->m_80 & 1) {
        steps = (s32)this->get_array_entry(this->get_field_74());
        target = *(f32 *)(steps + 0xC);
    } else {
        target = 0.0f;
    }
    steps = *(u32 *)&this->unk_50;
    if (steps == 0) {
        this->m_6c = target;
        return;
    }
    target += 0.5f * (this->m_3c - this->m_4c);
    this->m_6c += (target - this->m_6c) / (f32)steps;
}
#pragma pop
