#ifndef PSO_MATH_ANGLE_LOOKUP_H
#define PSO_MATH_ANGLE_LOOKUP_H

#include "types.h"

extern "C" {
f32 sin_table_lookup(s32 angle);
f32 cos_table_lookup(s32 angle);
}

#endif
