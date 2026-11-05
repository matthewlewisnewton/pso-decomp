#ifndef PSO_MATH_MATRIXCOPY_H
#define PSO_MATH_MATRIXCOPY_H

#include "dolphin/mtx/GeoTypes.h"

extern "C" void copy_matrix(MtxP dest, const f32 (*source)[4]);
extern "C" void concat_matrix(MtxP dest, const f32 (*source)[4]);

#endif
