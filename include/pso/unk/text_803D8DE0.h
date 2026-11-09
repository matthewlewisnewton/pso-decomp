#ifndef PSO_UNK_TEXT_803D8DE0_H
#define PSO_UNK_TEXT_803D8DE0_H
#include "types.h"
#include <dolphin/mtx.h>
// Transform count vectors by the rotation part; matrix == 0 selects the current
// matrix. Source and destination may be the same array.
extern "C" void fn_803D8DE0(u32 matrix, const Vec *src, Vec *dst, u32 count);
#endif
