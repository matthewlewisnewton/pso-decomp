#ifndef PSO_CAMERA_CAMERAHELPERS_H
#define PSO_CAMERA_CAMERAHELPERS_H

#include "types.h"
#include <dolphin/mtx.h>
#include "pso/camera/CameraPlayback.h"


void step_camera_scalar(const f32* current, const f32* target, f32* output, f32 step);
extern "C" {
BOOL approach_camera_vector(Vec* current, Vec* target, f32 rate);
}
void configure_scripted_camera_playback(CameraPlayback *playback_data, s32 unused);

#endif
