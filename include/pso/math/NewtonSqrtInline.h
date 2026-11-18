#ifndef PSO_MATH_NEWTON_SQRT_INLINE_H
#define PSO_MATH_NEWTON_SQRT_INLINE_H

#include "pso/player/PlayerCombatConstants.h"

extern "C" {
inline f32 newton_sqrtf(f32 x) {
    volatile f32 y;
    if (x > (0.0f)) {
        f64 guess = __frsqrte(x);
        guess = player_rsqrt_half * guess * (player_rsqrt_three - (f64) x * (guess * guess));
        guess = player_rsqrt_half * guess * (player_rsqrt_three - (f64) x * (guess * guess));
        guess = player_rsqrt_half * guess * (player_rsqrt_three - (f64) x * (guess * guess));
        y = (f32) ((f64) x * guess);
        return y;
    }
    return x;
}
}

#endif
