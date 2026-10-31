#ifndef PSO_SYSTEM_MATRIXVECTORARRAY_H
#define PSO_SYSTEM_MATRIXVECTORARRAY_H

#include "types.h"

struct Vec;
extern "C" {
// Transform an array with m, or with the current matrix when m is NULL.
void matrix_mult_vec_array(f32 (*m)[4], const Vec *src, Vec *dst, u32 count);
}

#endif
