#include "pso/math/ClampedStep.h"
#include "types.h"
#include "pso/item/TItemMenuCtrl_80115AF0.h"
#include "pso/TItemMenuCtrl.h"
#include "pso/item/TItemEffOrgaFlowShot.h"
#include "pso/player/TObjPlayer.h"
#include "pso/effect/TEffStarLight2D.h"

extern "C" s32 is_split_screen();

void TItemMenuCtrl::set_menu_flags(u32 mask) {
    menu_flags.set(mask);
}

TEffStarLight2D *spawn_star_light_2d(void *position, void *parameters, TObject *parent) {
    if (is_split_screen() == 0) {
        return new TEffStarLight2D(position, parameters, parent);
    }
    return NULL;
}

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

void add_integer_clamped(s32 *angle, s32 step, s32 target) {
    *angle += step;
    if (step > 0) {
        if (*angle > target) {
            *angle = target;
        }
    } else if (*angle < target) {
        *angle = target;
    }
}

void advance_angle_wrap(s32 *value, s32 step) {
    *value += step;
    s32 angle = *value;
    if (angle >= 0x10000) {
        *value = angle - 0x10000;
    }
}
