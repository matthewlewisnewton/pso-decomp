#include "types.h"
#include "pso/system/vector.h"
#include "pso/ui/TAdRicoRingCtrl.h"

extern const f32 lbl_805D7E48;
#pragma push
#pragma fp_contract on
void TAdRicoRingCtrl::sub_8001B424(s32 arg1) {
    u32 temp_r3;
    u8 *temp_r3_2;
    u8 *temp_r4;
    if (arg1 != 0) {
        temp_r3 = this->m_1c;
        if (temp_r3 != 0U) {
            VecCopy((Vec *)(temp_r3 + 0x58), (const Vec *)(arg1));
        }
        temp_r3_2 = (u8 *)this->m_20;
        if (temp_r3_2 != NULL) {
            VecCopy((Vec *)(temp_r3_2 + 0x58), (const Vec *)(arg1));
            temp_r4 = (u8 *)this->m_20;
            *(f32 *)((s8 *)temp_r4 + 0x5C) = (f32) -((lbl_805D7E48 * *(f32 *)((s8 *)(*(void **)((s8 *)(*(u8 **)((s8 *)temp_r4 + 0x4C)) + 4)) + 0x14)) - *(f32 *)((s8 *)temp_r4 + 0x5C));
        }
    }
}
#pragma pop
