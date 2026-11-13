#include "types.h"
#include "pso/TObjBoss5Ctrl.h"
#include "pso/boss/TBoss8Dragon_8028A8F8.h"
#include "pso/boss/TBoss8Dragon_80067034.h"
#include "pso/boss/TBoss8Dragon.h"

extern "C" {
void TBoss8Dragon__sub_8028B0DC(void *, s32, s32);
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
    TObject *floor_grass;
    TObject *floor_stone;
    if (boss5_ctrl_instance != NULL) {
        floor_grass = boss5_ctrl_instance->floor_grass;
        if (floor_grass != NULL) {
            TBoss8Dragon__sub_8028A900(floor_grass, (arg0), (arg1));
        }
        floor_stone = boss5_ctrl_instance->floor_stone;
        if (floor_stone != NULL) {
            TBoss8Dragon::trigger_switches_in_range(floor_stone, (void *)arg0, (void *)arg1);
        }
    }
}

void TBoss8Dragon__sub_800670E0(s32 arg0, s32 arg1) {
    TObject *pillar_controller;
    if (boss5_ctrl_instance != NULL) {
        pillar_controller = boss5_ctrl_instance->pillar_controller;
        if (pillar_controller != NULL) {
            TBoss8Dragon__sub_8028B0DC(pillar_controller, arg0, arg1);
        }
    }
}

}
