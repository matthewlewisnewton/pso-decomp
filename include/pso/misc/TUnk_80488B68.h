#ifndef PSO_MISC_TUNK_80488B68_H
#define PSO_MISC_TUNK_80488B68_H
#include "types.h"
#include "pso/misc/TUnk_80488A28.h"
#include "pso/misc/CameraHelpers.h"

struct CameraMotionData { u32 data; u32 frames; };
struct Entry_8006C6CC;

class TUnk_80488B68 : public TUnk_80488A28 {
public:
    TUnk_80488B68();
    virtual ~TUnk_80488B68();
    virtual void run_task();
    Vec position_origin;
    Vec target_origin;
    CameraAngles angles;
    CameraMotionData *motion_data;
    Entry_8006C6CC *mode;
    CameraPlayback playback;
};
typedef char TUnk_80488B68_size[sizeof(TUnk_80488B68) == 0xA4 ? 1 : -1];
typedef char TUnk_80488B68_origin_offset[offsetof(TUnk_80488B68, position_origin) == 0x6C ? 1 : -1];
typedef char TUnk_80488B68_target_offset[offsetof(TUnk_80488B68, target_origin) == 0x78 ? 1 : -1];
typedef char TUnk_80488B68_angles_offset[offsetof(TUnk_80488B68, angles) == 0x84 ? 1 : -1];
typedef char TUnk_80488B68_motion_offset[offsetof(TUnk_80488B68, motion_data) == 0x90 ? 1 : -1];
typedef char TUnk_80488B68_mode_offset[offsetof(TUnk_80488B68, mode) == 0x94 ? 1 : -1];
typedef char TUnk_80488B68_playback_offset[offsetof(TUnk_80488B68, playback) == 0x98 ? 1 : -1];

#endif
