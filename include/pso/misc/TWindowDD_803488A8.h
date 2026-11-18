#ifndef PSO_MISC_TWINDOWDD_803488A8_H
#define PSO_MISC_TWINDOWDD_803488A8_H

#include "types.h"

struct WindowTexturePoint {
    f32 u, v;
};

extern "C" {
extern WindowTexturePoint TWindowDD__data_805434E8[7][8];
void TWindowDD__sub_80348A2C(void *arg0, void *arg1);
f32 TWindowDD__sub_80348AD4(f32 farg0, f32 farg1);
s32 TWindowDD__sub_80348B70(s16 arg0);
}

// --- C functions defined in TWindowDD_803488A8.cpp ---
extern "C" {
void TWindowDD__sub_80348A2C(void *arg0, void *arg1);
f32 TWindowDD__sub_80348AD4(f32 farg0, f32 farg1);
s32 TWindowDD__sub_80348B70(s16 arg0);
}
// --- end of C functions

#endif
