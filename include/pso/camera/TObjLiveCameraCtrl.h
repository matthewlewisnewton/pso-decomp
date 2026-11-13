#ifndef PSO_CAMERA_TOBJLIVECAMERACTRL_H
#define PSO_CAMERA_TOBJLIVECAMERACTRL_H

#include "pso/system/task/TObject.h"
#include "types.h"

class TObjLiveCameraCtrl : public TObject {
public:
    TObjLiveCameraCtrl(TObject *parent);
    virtual ~TObjLiveCameraCtrl();
    void sub_8030B818(int);
    void choose_next_camera_shot();
    void update_live_camera();
    void update_toggle_state();
    virtual void run_task();
    s16 shot;
    s16 shot_frames;
    s32 effect_on;
    u16 target_id;
    s32 m_28;
    s32 orbit_step;
    f32 orbit_height;
    f32 vector_34[3];
    f32 vector_40[3];
    s32 slot_index;
    TObject *camera_object;
    u32 rng[58];

public:
    static s32 get_table_entry(s32 arg0);
};

#include <stddef.h>
typedef char TObjLiveCameraCtrl_vector_34_offset[offsetof(TObjLiveCameraCtrl, vector_34) == 0x34 ? 1 : -1];
typedef char TObjLiveCameraCtrl_vector_40_offset[offsetof(TObjLiveCameraCtrl, vector_40) == 0x40 ? 1 : -1];
typedef char TObjLiveCameraCtrl_slot_index_offset[offsetof(TObjLiveCameraCtrl, slot_index) == 0x4c ? 1 : -1];
typedef char TObjLiveCameraCtrl_camera_object_offset[offsetof(TObjLiveCameraCtrl, camera_object) == 0x50 ? 1 : -1];

typedef char TObjLiveCameraCtrl_size[sizeof(TObjLiveCameraCtrl) == 0x13C ? 1 : -1];

#endif
