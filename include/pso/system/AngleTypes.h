#ifndef PSO_SYSTEM_ANGLE_TYPES_H
#define PSO_SYSTEM_ANGLE_TYPES_H
#include "types.h"
#include <stddef.h>
struct CameraAngles { s32 pitch, yaw, roll; };
typedef char CameraAnglesSize[sizeof(CameraAngles)==12?1:-1];
typedef char CameraAnglesYawOffset[offsetof(CameraAngles,yaw)==4?1:-1];
typedef char CameraAnglesRollOffset[offsetof(CameraAngles,roll)==8?1:-1];
#endif
