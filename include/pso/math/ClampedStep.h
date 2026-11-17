#ifndef PSO_MATH_CLAMPED_STEP_H
#define PSO_MATH_CLAMPED_STEP_H

#include "types.h"

// Add the signed step, then clamp only in that direction. These do not choose
// a direction from the current value and do not wrap angles.
extern "C" {
void add_float_clamped(f32 *value, f32 step, f32 limit);
void add_integer_clamped(s32 *value, s32 step, s32 limit);
}

#endif
