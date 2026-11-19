#include "types.h"
#include "pso/system/data/FlagWord.h"
#include "pso/item/TItemMenuCtrl_80115AF0.h"
#include "pso/item/TItemMenuCtrl.h"
#include "pso/math/ClampedStep.h"
#include "pso/player/TObjPlayer.h"
#include "pso/boss/derolle/TObjBoss2Tunnel.h"
#include "pso/effect/item/TItemEffectWeapon.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/system/task/TObject.h"

extern "C" {
u8 * __ct__15TEffStarLight2DFPvPvP7TObject(void *, s32, s32, s32);
int set__8FlagWordFUl(void*);

int TItemMenuCtrl::set_menu_flags() { return set__8FlagWordFUl((char*)this + 0x1c); }
}


#pragma push
#pragma scheduling off
u8 *spawn_star_light_2d(s32 arg0, s32 arg1, s32 arg2) {
    u8 *eff_star_light2_d;
    u8 *var_r0;
    if (is_split_screen() == 0) {
        eff_star_light2_d = (u8 *)(TObject::operator new(0x4C));
        var_r0 = eff_star_light2_d;
        if (var_r0 != NULL) {
            var_r0 = (u8 *)(__ct__15TEffStarLight2DFPvPvP7TObject(eff_star_light2_d, arg0, arg1, arg2));
        }
        return var_r0;
    }
    return NULL;
}
#pragma pop

void add_float_clamped(f32 *value, f32 step, f32 target) {
    *value += step;
    if (step > 0.0f) {
        if (*value > target) {
            *value = target;
        }
    } else if (*value < target) {
        *value = target;
    }
}

void add_integer_clamped(s32 *value, s32 step, s32 target) {
    *value += step;
    if (step > 0) {
        if (*value > target) {
            *value = target;
        }
    } else if (*value < target) {
        *value = target;
    }
}

void advance_angle_wrap(s32 *arg0, s32 arg1) {
    s32 temp_r4;
    *arg0 += arg1;
    temp_r4 = *arg0;
    if (temp_r4 >= 0x10000) {
        *arg0 = temp_r4 + 0xFFFF0000;
    }
}
