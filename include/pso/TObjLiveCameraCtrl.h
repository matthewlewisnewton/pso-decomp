#ifndef PSO_TOBJLIVECAMERACTRL_H
#define PSO_TOBJLIVECAMERACTRL_H

#include "pso/TObject.h"
#include "types.h"

class TObjLiveCameraCtrl : public TObject {
public:
    TObjLiveCameraCtrl(TObject *parent);
    virtual ~TObjLiveCameraCtrl();
    void sub_8030B818(int);
    s32 get_local_client_id();
    u16 get_first_dragon_part_id();
    void choose_next_camera_shot();
    void update_live_camera();
    void update_toggle_state();
    virtual void run_task();
    // 1 orbits a player, 2 sits behind a player, 3 sits behind an enemy,
    // 4 is a random wide shot, 5 is the fixed view held until the dragon wakes.
    s16 shot;
    s16 shot_frames;  // counts down to the next shot; negative holds the shot
    s32 effect_on;    // whether camera_object's effect is switched on
    u16 target_id;    // the player's client id or the enemy's entity id
    s32 m_28;         // orbit angle
    s32 orbit_step;   // added to m_28 each frame of shot 1
    f32 orbit_height; // eye height above the player in shot 1
    f32 vector_34[3]; // eye
    f32 vector_40[3]; // look-at point
    s32 slot_index;
    TObject *camera_object;
    u32 rng[58];      // SubtractiveRng state

public:
    static s32 get_table_entry(s32 arg0);
};

#include <stddef.h>
typedef char TObjLiveCameraCtrl_target_id_offset[offsetof(TObjLiveCameraCtrl, target_id) == 0x24 ? 1 : -1];
typedef char TObjLiveCameraCtrl_vector_34_offset[offsetof(TObjLiveCameraCtrl, vector_34) == 0x34 ? 1 : -1];
typedef char TObjLiveCameraCtrl_vector_40_offset[offsetof(TObjLiveCameraCtrl, vector_40) == 0x40 ? 1 : -1];
typedef char TObjLiveCameraCtrl_slot_index_offset[offsetof(TObjLiveCameraCtrl, slot_index) == 0x4c ? 1 : -1];
typedef char TObjLiveCameraCtrl_camera_object_offset[offsetof(TObjLiveCameraCtrl, camera_object) == 0x50 ? 1 : -1];
typedef char TObjLiveCameraCtrl_size[sizeof(TObjLiveCameraCtrl) == 0x13C ? 1 : -1];

#endif
