#ifndef PSO_ITEM_WEAPON_ANIMATION_CHANNELS_H
#define PSO_ITEM_WEAPON_ANIMATION_CHANNELS_H
#include "types.h"
#include "pso/math/ClampedStep.h"

// Three independent float channels driven by the idle/attack transitions.
// Their model-node interpretation is not yet established.
struct WeaponAnimationChannels {
    f32 first;
    f32 second;
    f32 third;

    s32 update_idle() {
        f32 current;
        s32 reached_limit = 0;
        current = first;
        if (current < 1.0f) {
            first += 0.14f;
            if (1.0f <= first) {
                first = 1.0f;
                reached_limit = 1;
            }
        }
        add_float_clamped(&second, -0.04000001f, 1.0f);
        add_float_clamped(&third, 0.14f, 1.0f);
        return reached_limit;
    }

    void update_attack() {
        add_float_clamped(&first, -0.14f, 0.3f);
        add_float_clamped(&second, 0.04000001f, 1.2f);
        add_float_clamped(&third, -0.14f, 0.3f);
    }
};
typedef char WeaponAnimationChannelsSize[sizeof(WeaponAnimationChannels) == 12 ? 1 : -1];
#endif
