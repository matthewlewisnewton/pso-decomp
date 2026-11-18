#include "types.h"
#include "pso/misc/TCameraCtrl_8006C254.h"
#include "pso/misc/TUnk_80488B38.h"
#include "pso/misc/TUnk_80488B68.h"
#include "pso/misc/TUnk_80488B08.h"
#include "pso/system/vector.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/CameraHelpers.h"
#include <stddef.h>
#include "pso/misc/TCameraCtrl_80067FC0.h"
#include "pso/misc/TCameraCtrl_8006C580.h"
#include "pso/system/memory.h"
#include "pso/misc/TUnk_80488D70.h"
#include "pso/misc/TScene.h"
#include "pso/map/FloorArea.h"

#pragma push
#pragma fp_contract on
#pragma pop

struct RecoveredGlobal_8006C03C_lbl_804FF5E8 {
    s32 value;
    u8 remaining[0x24];
};

struct RecoveredFields_8006C03C_arg0 {
    u8 unknown_0[0x3C];
    f32 field_3C;
    f32 field_40;
    f32 field_44;
    f32 field_48;
    f32 field_4C;
    f32 field_50;
};

struct RecoveredFields_8006C03C_lbl_805D4DF0 {
    u8 unknown_0[0x178];
    f32 field_178;
    f32 field_17C;
    f32 field_180;
    f32 field_184;
    f32 field_188;
    f32 field_18C;
};

extern "C" {
void direction_to_pitch_yaw(u8 *arg0, s32 *arg1, s32 *arg2);
}
void set_camera_look_at(u8 *eye, u8 *target, u8 *up);
extern RecoveredGlobal_8006C03C_lbl_804FF5E8 lbl_804FF5E8;
extern void *camera_ctrl_instance;
extern void* camera_controller_registry[];
void* camera_controller_registry[];

extern "C" {
f32 vector_length(const Vec*);
void approach_vector_fixed_distance(const Vec*, const Vec*, Vec*, f32);
static const f64 lbl_804383D8 = 5.0;

u16 TCameraCtrl__sub_8006A5DC();
f32 fabs_float(f32);
f32 atan2_float(f32 y, f32 x);
f32 newton_sqrtf(f32);
static const f64 lbl_804383D0 = 10430.38043493439;
s32 angle_difference_abs(s32, s32);
s32 approach_angle_limited(s32, s32, s32);

}

s32 approach_camera_scalar(f32 *arg0, f32 *arg1, f32 farg0);
s32 approach_camera_scalar(f32 *arg0, f32 *target, f32 farg0) {
  f32 step;
  f32 new_var;
  f32 temp_f1;
  temp_f1 = fabs_float((*arg0) - (*target));
  step = (0.16f * temp_f1) * (new_var = farg0);
  if (temp_f1 > step)
  {
    step_camera_scalar((f32 *)((void *) arg0), (f32 *)((void *) target), (f32 *)((void *) arg0), (f32) step);
    return 0;
  }
  *arg0 = *target;
  return 1;
}

void step_camera_scalar(const f32* current, const f32* target, f32* output, f32 step) {
    f32 distance = fabs_float(*current - *target);
    if (0.0f == distance || distance <= step) {
        *output = *target;
        return;
    }
    f32 value = *current;
    if (value < *target) {
        *output = value + step;
        return;
    }
    *output = value - step;
}

void direction_to_pitch_yaw(u8 *arg0, s32 *arg1, s32 *arg2) {
  f32 new_var;
  f32 temp_f0;
  f32 temp_f1;
  *arg2 = (s32) (lbl_804383D0 * atan2_float(-(*((f32 *) (((s8 *) arg0) + 0))), -(*((f32 *) (((s8 *) arg0) + 8)))));
  temp_f1 = *((f32 *) (((s8 *) arg0) + 0));
  temp_f0 = *((f32 *) (((s8 *) arg0) + 8));
  new_var = newton_sqrtf((temp_f1 * temp_f1) + (temp_f0 * temp_f0));
  *arg1 = (s32) (lbl_804383D0 * atan2_float((f64) (*((f32 *) (((s8 *) arg0) + 4))), new_var));
}

BOOL approach_camera_vector(Vec *current, Vec *target, f32 rate) {
    f32 base_step;
    Vec delta;
    delta.x = current->x - target->x;
    delta.y = current->y - target->y;
    delta.z = current->z - target->z;
    f32 distance = vector_length(&delta);
    base_step = 0.16f * distance;
    f32 step = base_step * rate;
    if (distance > step) {
        if (step >= lbl_804383D8) {
            step = 12.0f;
        }
        approach_vector_fixed_distance(current, target, current, step);
        return FALSE;
    }
    target->x = current->x;
    target->y = current->y;
    target->z = current->z;
    return TRUE;
}

s32 TCameraCtrl::clamp_distance(s32 arg0, s32 arg1, s32 arg2) {
    if (angle_difference_abs(arg1, arg0) < (s32) (arg2 * 0x7F)) {
        return arg1;
    }
    return approach_angle_limited(arg0, arg1, arg2 * 0x7F);
}

void set_scripted_camera_pose(const Vec* position, const Vec* target, const CameraAngles* angles) {
    TUnk_80488B68* camera = (TUnk_80488B68*)camera_controller_registry[5];
    if (camera != NULL) {
        VecCopy(&camera->position_origin, position);
        VecCopy(&camera->target_origin, target);
        camera->angles.yaw = angles->yaw;
    }
}

extern s32 TCameraCtrl__saved_projection_angle;
extern s32 scripted_camera_projection_angle;

#pragma push
#pragma opt_common_subs off
typedef char RecoveredGlobal_8006C03C_lbl_804FF5E8_size[sizeof(RecoveredGlobal_8006C03C_lbl_804FF5E8) == 0x28 ? 1 : -1];
typedef char RecoveredFields_8006C03C_arg0_3C_offset[offsetof(RecoveredFields_8006C03C_arg0, field_3C) == 0x3C ? 1 : -1];
typedef char RecoveredFields_8006C03C_arg0_40_offset[offsetof(RecoveredFields_8006C03C_arg0, field_40) == 0x40 ? 1 : -1];
typedef char RecoveredFields_8006C03C_arg0_44_offset[offsetof(RecoveredFields_8006C03C_arg0, field_44) == 0x44 ? 1 : -1];
typedef char RecoveredFields_8006C03C_arg0_48_offset[offsetof(RecoveredFields_8006C03C_arg0, field_48) == 0x48 ? 1 : -1];
typedef char RecoveredFields_8006C03C_arg0_4C_offset[offsetof(RecoveredFields_8006C03C_arg0, field_4C) == 0x4C ? 1 : -1];
typedef char RecoveredFields_8006C03C_arg0_50_offset[offsetof(RecoveredFields_8006C03C_arg0, field_50) == 0x50 ? 1 : -1];
typedef char RecoveredFields_8006C03C_lbl_805D4DF0_178_offset[offsetof(RecoveredFields_8006C03C_lbl_805D4DF0, field_178) == 0x178 ? 1 : -1];
typedef char RecoveredFields_8006C03C_lbl_805D4DF0_17C_offset[offsetof(RecoveredFields_8006C03C_lbl_805D4DF0, field_17C) == 0x17C ? 1 : -1];
typedef char RecoveredFields_8006C03C_lbl_805D4DF0_180_offset[offsetof(RecoveredFields_8006C03C_lbl_805D4DF0, field_180) == 0x180 ? 1 : -1];
typedef char RecoveredFields_8006C03C_lbl_805D4DF0_184_offset[offsetof(RecoveredFields_8006C03C_lbl_805D4DF0, field_184) == 0x184 ? 1 : -1];
typedef char RecoveredFields_8006C03C_lbl_805D4DF0_188_offset[offsetof(RecoveredFields_8006C03C_lbl_805D4DF0, field_188) == 0x188 ? 1 : -1];
typedef char RecoveredFields_8006C03C_lbl_805D4DF0_18C_offset[offsetof(RecoveredFields_8006C03C_lbl_805D4DF0, field_18C) == 0x18C ? 1 : -1];
void TCameraCtrl::apply_look_at_from_target() {
    u8 *arg0 = (u8 *)this;
    Vec target;
    Vec direction;
    direction.x = ((RecoveredFields_8006C03C_arg0 *)arg0)->field_48 - ((RecoveredFields_8006C03C_arg0 *)arg0)->field_3C;
    direction.y = ((RecoveredFields_8006C03C_arg0 *)arg0)->field_4C - ((RecoveredFields_8006C03C_arg0 *)arg0)->field_40;
    direction.z = ((RecoveredFields_8006C03C_arg0 *)arg0)->field_50 - ((RecoveredFields_8006C03C_arg0 *)arg0)->field_44;
    direction_to_pitch_yaw((u8 *)&direction, (s32 *)((void *) ((*(u8 * *)&camera_ctrl_instance) + 0x190)), (s32 *)((void *) ((*(u8 * *)&camera_ctrl_instance) + 0x194)));
    target.x = ((RecoveredFields_8006C03C_lbl_805D4DF0 *)(*(u8 * *)&camera_ctrl_instance))->field_184;
    target.y = ((RecoveredFields_8006C03C_lbl_805D4DF0 *)(*(u8 * *)&camera_ctrl_instance))->field_188;
    target.z = ((RecoveredFields_8006C03C_lbl_805D4DF0 *)(*(u8 * *)&camera_ctrl_instance))->field_18C;
    Vec up = {0.0f, 1.0f, 0.0f};
    set_camera_look_at(((*(u8 * *)&camera_ctrl_instance) + 0x178), (u8 *)&target, (u8 *)&up);
    *(f32 *)((s8 *)&lbl_804FF5E8.value + 0) = (f32) ((RecoveredFields_8006C03C_lbl_805D4DF0 *)(*(u8 * *)&camera_ctrl_instance))->field_178;
    *(f32 *)((s8 *)&lbl_804FF5E8.value + 4) = (f32) ((RecoveredFields_8006C03C_lbl_805D4DF0 *)(*(u8 * *)&camera_ctrl_instance))->field_17C;
    *(f32 *)((s8 *)&lbl_804FF5E8.value + 8) = (f32) ((RecoveredFields_8006C03C_lbl_805D4DF0 *)(*(u8 * *)&camera_ctrl_instance))->field_180;
}
#pragma pop

extern "C" void cache_target_and_forward__11TCameraCtrlFl(const CameraPlayback *playback_data, s32 unused) {
    if ((void *) camera_ctrl_instance != NULL) {
        TCameraCtrl__saved_projection_angle = *(s32 *)((s8 *)camera_ctrl_instance + 0x19C);
        scripted_camera_projection_angle = unused;
    }
    // The lower helper reads through a const local and never writes its input.
    configure_scripted_camera_playback(const_cast<CameraPlayback*>(playback_data), unused);
}

void configure_scripted_camera_playback(CameraPlayback *playback_data, s32 unused) {
    const CameraPlayback *playback = playback_data;
    TUnk_80488B68* camera = (TUnk_80488B68*)camera_controller_registry[5];
    if (camera != NULL) {
        camera->playback.index = playback->index;
        camera->playback.bank = playback->bank;
        camera->playback.flags = playback->flags;
        camera->playback.frame = playback->frame;
        camera->playback.frame_step = playback->frame_step;
        camera->mode = &camera_path_bank_table[get_current_floor_area()].entries[camera->playback.bank];
        camera->motion_data = TCameraCtrl__camera_banks.e[playback->bank].directory->entries[camera->playback.index];
    }
}

CameraPlayback* get_scripted_camera_playback() {
    TUnk_80488B68* camera = (TUnk_80488B68*)camera_controller_registry[5];
    if (camera != NULL) {
        CameraPlayback* playback = &camera->playback;
        if (TCameraCtrl__sub_8006A5DC() != 5) {
            playback->flags |= 1;
        }
        return playback;
    }
    return NULL;
}

#pragma push
#pragma fp_contract on

#pragma pop
