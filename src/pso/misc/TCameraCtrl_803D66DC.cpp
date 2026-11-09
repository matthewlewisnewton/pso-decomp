#include "pso/animation/MotionContext.h"
#include "types.h"
#include "pso/system/NinjaTypes.h"
#include "pso/misc/TCameraCtrl_803D6538.h"

#include <stddef.h>
#include "pso/misc/TCameraCtrl.h"
#include "pso/player/TObjPlayer.h"
struct Stack_803D6DDC {
    u8 * sp8;
    u8 * spC;
    f32 sp10;
};

struct Stack_803D6E8C {
    u8 * sp8;
    u8 * spC;
    f32 sp10;
};

struct RecoveredGlobal_803D662C_lbl_8058D4D0 {
    s32 value;
    u8 remaining[0x24];
};

struct RecoveredGlobal_803D77C0_lbl_8047E3C8 {
    s32 value;
    u8 remaining[0xC];
};

struct RecoveredGlobal_803D77C0_lbl_804FA500 {
    s32 value;
    u8 remaining[0x8];
};

struct RecoveredGlobal_803D77C0_lbl_804FA50C {
    s32 value;
    u8 remaining[0xC];
};

struct RecoveredGlobal_803D77C0_lbl_804FA51C {
    s32 value;
    u8 remaining[0x20];
};

struct RecoveredGlobal_803D78A8_lbl_8058CAB8 {
    s32 value;
    u8 remaining[0x7C];
};

struct St_803D7784 { s32 a0, a4, a8, ac, b0, b4, b8, x1c; };

struct Vec_803D7504 { f32 x, y, z; };
struct Quat_803D7504 { f32 x, y, z, w; };

struct Vec_803D7CA4 { f32 x, y, z; };

struct Angles_803D7CA4 { s32 x, y, z; };

struct Quat_803D7CA4 { f32 x, y, z, w; };

struct V_803D6558 { f32 x, y, z; };

struct G_803D6688 { f32 f0, f4, pad8[2], f10, f14, f18, f1c, f20, f24; };

struct St_803D6BA4 { u8 pad0[0xC]; u32 *keys; u32 *vals; f32 t; u8 pad18[4]; s32 idx; u8 pad20[4]; void (*fn24)(u32, u32, s32, f32); void (*fn28)(u32, u32, s32, f32); void (*fn2c)(u32, u32, s32, f32); };

struct St_803D6C1C { u8 pad0[0xC]; u32 *keys; u32 *vals; f32 t; u8 pad18[4]; s32 idx; u8 pad20[4]; void (*fn24)(u32, u32, s32, f32); void (*fn28)(u32, u32, s32, f32); void (*fn2c)(u32, u32, s32, f32); };

struct St_803D6C94 { u8 pad0[0xC]; u32 *keys; u32 *vals; f32 t; u8 pad18[4]; s32 idx; u8 pad20[4]; void (*fn24)(u32, u32, s32, f32); void (*fn28)(u32, u32, s32, f32); void (*fn2c)(u32, u32, s32, f32); };

struct St_803D6D0C { u8 pad0[0xC]; u32 *keys; u32 *vals; f32 t; u8 pad18[4]; s32 idx; };

struct Vec_803D7D30 { f32 x, y, z; };

struct Vec4_803D7D30 { f32 w, x, y, z; };

struct Key_803D7D30 {
    u32 flags;
    u8 pad4[4];
    Vec_803D7D30 pos;
    Vec_803D7D30 rot;
    Vec_803D7D30 scl;
    u8 pad2c[8];
    f32 w;
};

struct Smp_803D7D30 {
    u8 pad[0x30];
    s32 (*f30)(void *);
    s32 (*f34)(void *);
    s32 (*f38)(void *);
    s32 (*f3C)(void *);
};

struct Stack_803D6F20 {
    u8 * sp8;
    u8 * spC;
    f32 sp10;
};

struct Stack_803D6FC8 {
    u8 * sp8;
    u8 * spC;
    f32 sp10;
};

struct Stack_803D7128 {
    u8 * sp8;
    u8 * spC;
    f32 sp10;
};

struct Proj_803D676C { f32 m[4][4]; s32 f40; f32 f44, f48, f4C, f50, f54; };

struct Disp_803D676C { u8 pad[6]; u16 h; };

struct MotionQuaternionKey {
  u32 frame;
  f32 rotation[4];
};

struct SplineKey_803D7288 { u32 frame; f32 value[3]; };

struct Cam_803D66DC { f32 f0, f4, f8, fC, f10, f14, f18, f1C, f20, f24; };

extern u8 *current_motion_context;
extern "C" {
s32 C_MTXPerspective(void *, f32, f32, f32, f32);
s32 GXSetProjection(void *, int);
f64 atan(f32);
f32 sin_table_lookup(s32);
f32 cos_table_lookup(s32);
extern Proj_803D676C scene_projection_state;
extern RecoveredGlobal_803D662C_lbl_8058D4D0 camera_clip_parameters;
extern G_803D6688 lbl_8058D4F8;
extern Disp_803D676C *active_gx_render_mode;
extern const f32 lbl_805E0E18;
extern const f64 lbl_805E0E20;
extern const f64 lbl_805E0E28;
extern const f32 lbl_805E0E30;
extern const f32 lbl_805E0E34;
extern const f32 lbl_805E0E38;
void blend_quaternions_nlerp(void *a, void *b, void *out, f32 t);
void interpolate_spline_cyclic_cubic(struct SplineKey_803D7288 *keys, u32 count, f32 frame, f32 *output);
extern const f32 lbl_805E0E10;
extern const f32 lbl_805E0E50;
void C_MTXLookAt(void *, void *, void *, void *);
extern u8 *current_matrix;
extern f32 motion_blend_factor;
extern const f32 lbl_805E0E00;
extern const f32 lbl_805E0E04;
extern RecoveredGlobal_803D77C0_lbl_8047E3C8 lbl_8047E3C8;
extern RecoveredGlobal_803D77C0_lbl_804FA500 motion_sampler_function_table;
extern RecoveredGlobal_803D77C0_lbl_804FA50C motion_angle_sampler_table;
extern RecoveredGlobal_803D77C0_lbl_804FA51C motion_key_sampler_table;
extern s32 motion_packed_rotation_mode;
extern RecoveredGlobal_803D78A8_lbl_8058CAB8 camera_motion_context_table;
extern u8 lbl_8058CB38[0x10];
s32 translate_matrix(s32, f32, f32, f32);
void rotate_matrix_by_node_angles(void *, int);
void scale_current_matrix(void *);
void post_translate_matrix(void *);
void set_matrix_identity(u8 *arg0);
}
extern u8 camera_look_at_up_vector[];
extern const f32 lbl_805E0E08;
void euler_zyx_to_quaternion(u8 *arg0, u8 *arg1);
void euler_yxz_to_quaternion(u8 *arg0, u8 *arg1);
extern const f32 lbl_805E0E88;

#pragma push
#pragma use_lmw_stmw off

#pragma push
#pragma opt_common_subs off

void TCameraCtrl::update_projection_params() {
    Cam_803D66DC *arg0 = (Cam_803D66DC *)this;
    f32 c, b, a;
    (*(Cam_803D66DC *)&lbl_8058D4F8).f18 = a = arg0->f18;
    (*(Cam_803D66DC *)&lbl_8058D4F8).f8 = b = arg0->f8;
    (*(Cam_803D66DC *)&lbl_8058D4F8).fC = c = arg0->fC;
    (*(Cam_803D66DC *)&lbl_8058D4F8).f0 = (*(Cam_803D66DC *)&lbl_8058D4F8).f1C * a;
    (*(Cam_803D66DC *)&lbl_8058D4F8).f4 = -((*(Cam_803D66DC *)&lbl_8058D4F8).f20 * a);
    (*(Cam_803D66DC *)&lbl_8058D4F8).f10 = lbl_805E0E10 / (*(Cam_803D66DC *)&lbl_8058D4F8).f0;
    (*(Cam_803D66DC *)&lbl_8058D4F8).f14 = lbl_805E0E10 / (*(Cam_803D66DC *)&lbl_8058D4F8).f4;
    (*(Cam_803D66DC *)&camera_clip_parameters).f8 = (*(Cam_803D66DC *)&camera_clip_parameters).f20 - b;
    (*(Cam_803D66DC *)&camera_clip_parameters).fC = (*(Cam_803D66DC *)&camera_clip_parameters).f18 - b;
    (*(Cam_803D66DC *)&camera_clip_parameters).f10 = (*(Cam_803D66DC *)&camera_clip_parameters).f24 - c;
    (*(Cam_803D66DC *)&camera_clip_parameters).f14 = (*(Cam_803D66DC *)&camera_clip_parameters).f1C - c;
}
#pragma pop
