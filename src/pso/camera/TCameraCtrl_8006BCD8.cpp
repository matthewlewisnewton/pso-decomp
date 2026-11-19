#include "pso/camera/RadarMapViewState.h"
#include "types.h"
#include "pso/camera/TCameraCtrl_8006C254.h"
#include "pso/unk/TUnk_80488B38.h"
#include "pso/unk/TUnk_80488B68.h"
#include "pso/unk/TUnk_80488B08.h"
#include "pso/system/vector.h"
#include "pso/camera/TCameraCtrl.h"
#include "pso/camera/CameraHelpers.h"
#include <stddef.h>
#include "pso/camera/TCameraCtrl_80067FC0.h"
#include "pso/camera/TCameraCtrl_8006C580.h"
#include "pso/system/memory.h"
#include "pso/unk/TUnk_80488D70.h"
#include "pso/system/scene/TScene.h"
#include "pso/map/FloorArea.h"
#include "pso/player/TObjPlayer_80011014.h"

#pragma push
#pragma fp_contract on
#pragma pop

void direction_to_pitch_yaw(u8 *arg0, s32 *arg1, s32 *arg2);
void set_camera_look_at(u8 *eye, u8 *target, u8 *up);
extern TCameraCtrl *camera_ctrl_instance;
extern void* camera_controller_registry[];
void* camera_controller_registry[];

extern "C" {
f32 vector_length(const Vec*);
void approach_vector_fixed_distance(const Vec*, const Vec*, Vec*, f32);

u16 TCameraCtrl__sub_8006A5DC();
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
  *arg2 = (s32) (10430.38043493439 * atan2_float(-(*((f32 *) (((s8 *) arg0) + 0))), -(*((f32 *) (((s8 *) arg0) + 8)))));
  temp_f1 = *((f32 *) (((s8 *) arg0) + 0));
  temp_f0 = *((f32 *) (((s8 *) arg0) + 8));
  new_var = newton_sqrtf((temp_f1 * temp_f1) + (temp_f0 * temp_f0));
  *arg1 = (s32) (10430.38043493439 * atan2_float((f64) (*((f32 *) (((s8 *) arg0) + 4))), new_var));
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
        if (step >= 5.0) {
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

void TUnk_80488B68::post_update_view() {
    Vec at;
    Vec dir;
    dir.x = target.x - position.x;
    dir.y = target.y - position.y;
    dir.z = target.z - position.z;
    direction_to_pitch_yaw((u8 *)&dir, (s32 *)&camera_ctrl_instance->pitch, (s32 *)&camera_ctrl_instance->yaw);
    at.x = camera_ctrl_instance->tgt_x;
    at.y = camera_ctrl_instance->tgt_y;
    at.z = camera_ctrl_instance->tgt_z;
    Vec up = {0.0f, 1.0f, 0.0f};
    set_camera_look_at((u8 *)&camera_ctrl_instance->pos_x, (u8 *)&at, (u8 *)&up);
    camera_world_view.position.x = camera_ctrl_instance->pos_x;
    camera_world_view.position.y = camera_ctrl_instance->pos_y;
    camera_world_view.position.z = camera_ctrl_instance->pos_z;
}

void CameraPlayback::cache_target_and_forward(s32 angle) const {
    if ((void *) camera_ctrl_instance != NULL) {
        TCameraCtrl__saved_projection_angle = *(s32 *)((s8 *)camera_ctrl_instance + 0x19C);
        scripted_camera_projection_angle = angle;
    }
    configure_scripted_camera_playback(const_cast<CameraPlayback *>(this), angle);
}

void configure_scripted_camera_playback(CameraPlayback *playback_data, s32 unused) {
    const CameraPlayback* playback = playback_data;
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
