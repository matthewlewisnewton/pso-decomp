#include "types.h"
#include "pso/boss/TBoss8Dragon_8028A8F8.h"
#include "pso/boss/TBoss8Dragon_80067034.h"
#include "pso/boss/TBoss8Dragon.h"

extern "C" {
void TBoss8Dragon__sub_8028B0DC(void *, s32, s32);
extern u8 *boss5_ctrl_instance;
}

#pragma fp_contract on
s32 is_within_xz_distance(Vec *pos, XzSwitchNode *node, f32 limit) {
    f32 temp_f2;
    f32 temp_f4;
    temp_f2 = pos->x - node->x;
    temp_f4 = pos->z - node->z;
    return ((temp_f2 * temp_f2) + (temp_f4 * temp_f4)) < limit;
}

f32 calc_sq_offset(EffectGeometryParameters *params, f32 extra) {
    f32 temp_f0;

    temp_f0 = params->field_8 + extra;
    return temp_f0 * temp_f0;
}

extern "C" {
void TBoss8Dragon__sub_80067074(s32 arg0, s32 arg1) {
    u32 temp_r3;
    u32 temp_r3_2;
    if ((void *) boss5_ctrl_instance != NULL) {
        temp_r3 = *(u32 *)((s8 *)boss5_ctrl_instance + 0x1C);
        if (temp_r3 != 0U) {
            TBoss8Dragon__sub_8028A900((void *)temp_r3, (arg0), (arg1));
        }
        temp_r3_2 = *(u32 *)((s8 *)boss5_ctrl_instance + 0x20);
        if (temp_r3_2 != 0U) {
            TBoss8Dragon::trigger_switches_in_range((void *)temp_r3_2, (void *)arg0, (void *)arg1);
        }
    }
}

void TBoss8Dragon__sub_800670E0(s32 arg0, s32 arg1) {
    u8 *temp_r3;
    if ((void *) boss5_ctrl_instance != NULL) {
        temp_r3 = (u8 *)(*(u8 **)((s8 *)boss5_ctrl_instance + 0x24));
        if (temp_r3 != NULL) {
            TBoss8Dragon__sub_8028B0DC(temp_r3, arg0, arg1);
        }
    }
}

}
