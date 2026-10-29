#ifndef PSO_SYSTEM_VECTOR_H
#define PSO_SYSTEM_VECTOR_H

#include "types.h"
#include <dolphin/mtx.h>

Vec * VecCopy(Vec *dst, const Vec *src);
// Copies three words: a Vec, or an x/y/z angle triple.
void copy_xyz(void *dst, void *src);

f32 normalize_vector_xz(Vec *vector);

#endif
