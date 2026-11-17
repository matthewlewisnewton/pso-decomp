#ifndef PSO_MATH_NEWTON_SQRT_INLINE_H
#define PSO_MATH_NEWTON_SQRT_INLINE_H

#include "types.h"

extern "C" {
// Existing read-only half and three constants used by the surviving helper.
extern const f64 lbl_80434098;
extern const f64 lbl_804340A0;

inline f32 newton_sqrtf(f32 x) {
    volatile f32 y;
    if (x > (0.0f)) {
        f64 guess = __frsqrte(x);
        guess = lbl_80434098 * guess * (lbl_804340A0 - (f64) x * (guess * guess));
        guess = lbl_80434098 * guess * (lbl_804340A0 - (f64) x * (guess * guess));
        guess = lbl_80434098 * guess * (lbl_804340A0 - (f64) x * (guess * guess));
        y = (f32) ((f64) x * guess);
        return y;
    }
    return x;
}
}

#endif
