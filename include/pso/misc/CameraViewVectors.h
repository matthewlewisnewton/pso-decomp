#ifndef PSO_MISC_CAMERA_VIEW_VECTORS_H
#define PSO_MISC_CAMERA_VIEW_VECTORS_H

#include "types.h"
#include <dolphin/mtx.h>
#include <stddef.h>

// Bounded view of the two four-player vector banks accessed at 8006BAB4/8006BAC8.
// The surrounding camera-controller layout is still provisional.
struct CameraViewVectors {
    u8 unknown_00[0xD4];
    Vec positions[4];
    Vec targets[4];
};
extern "C" {
Vec *TCameraCtrl__sub_8006BAB4(CameraViewVectors *views, s32 index);
Vec *TCameraCtrl__sub_8006BAC8(CameraViewVectors *views, s32 index);
}

typedef char CameraViewPositionsOffset[offsetof(CameraViewVectors, positions) == 0xD4 ? 1 : -1];
typedef char CameraViewTargetsOffset[offsetof(CameraViewVectors, targets) == 0x104 ? 1 : -1];

#endif
