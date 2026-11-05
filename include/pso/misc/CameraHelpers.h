#ifndef PSO_MISC_CAMERA_HELPERS_H
#define PSO_MISC_CAMERA_HELPERS_H

#include "types.h"
#include <dolphin/mtx.h>

#include "pso/system/AngleTypes.h"

struct CameraPlayback {
    u8 bank;
    u8 index;
    u16 flags;
    f32 frame;
    f32 frame_step;
};

void step_camera_scalar(const f32* current, const f32* target, f32* output, f32 step);
extern "C" {
BOOL approach_camera_vector(Vec* current, Vec* target, f32 rate);
void set_scripted_camera_pose(const Vec* position, const Vec* target, const CameraAngles* angles);
}
extern "C" void cache_target_and_forward__11TCameraCtrlFl(const CameraPlayback *playback, s32 projection);
// The original lower boundary has a mutable parameter. Its implementation only
// reads the argument; retain that boundary for CodeWarrior's alias analysis.
void configure_scripted_camera_playback(CameraPlayback *playback, s32 unused);
extern "C" {
CameraPlayback* get_scripted_camera_playback();
}

#include <stddef.h>
typedef char CameraPlaybackSize[(sizeof(CameraPlayback) == 0xC) ? 1 : -1];
typedef char CameraPlaybackFlagsOffset[(offsetof(CameraPlayback, flags) == 2) ? 1 : -1];
typedef char CameraPlaybackFrameOffset[(offsetof(CameraPlayback, frame) == 4) ? 1 : -1];
typedef char CameraPlaybackStepOffset[(offsetof(CameraPlayback, frame_step) == 8) ? 1 : -1];
#endif
