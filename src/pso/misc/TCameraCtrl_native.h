#ifndef PSO_MISC_TCAMERACTRL_NATIVE_H
#define PSO_MISC_TCAMERACTRL_NATIVE_H

// Source-private declarations and verified storage views for TCameraCtrl.cpp.
// The legacy offset views remain bounded here while public camera ABI stays fixed.
#include "types.h"
#include "pso/TObject.h"
#include "pso/misc/TUnk_80488A28.h"
#include "pso/system/vector.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/camera/CreationCamera.h"
#include "pso/map/FloorArea.h"
#include "pso/camera/CameraViewParams.h"
#include <stddef.h>
#include "pso/system/PadRumble.h"
#include "pso/misc/TCameraCtrl_8006A03C.h"
#include "pso/player/TObjPlayer.h"
#include "pso/TMainTask.h"
#include "pso/boss/TObjBoss2Tunnel.h"

extern const f32 TCameraCtrl__data_805D8FAC;
struct RecoveredGlobal_8006ABAC_lbl_804FF610 {
    s32 value;
    u8 remaining[0x8];
};
struct RecoveredGlobal_8006ABAC_lbl_804FF61C {
    s32 value;
    u8 remaining[0x8];
};
struct Vec_8006AF9C { f32 x, y, z; };
void set_camera_look_at(u8 *eye, u8 *target, u8 *up);
extern "C" {
s32 set_perspective_projection_from_fov(int, f32, f32, f32);
f32 vec_squared_length(void *);
}
extern f32 lbl_804FF5E8[10];
extern u32 TCameraCtrl__up_vector[3];
extern const f32 TCameraCtrl__data_805D8FDC;
extern const f32 TCameraCtrl__data_805D8FE0;
struct C30_8006AD34 { u8 b[0x30]; };
f32 lbl_804FF5E8[10];
f32 camera_right[3];
RecoveredGlobal_8006ABAC_lbl_804FF61C camera_pitch_rotated_up_vector;
u8 TCameraCtrl__view_state[12];
u32 TCameraCtrl__data_804FF634[18];
u32 lbl_804FF67C[18];
u32 TCameraCtrl__up_vector[3];
u8 TCameraCtrl__view_matrix[0x30];
C30_8006AD34 TCameraCtrl__view_matrices[4];
extern void *camera_controller_registry[13];
extern void *lbl_80488AC0[6];
struct Cam_80069F20 {
    s32 f0;
    s32 f4;
    s32 flags;
};
struct Out_80069F20 {
    u8 pad0[0x20];
    s32 f20;
    s32 f24;
    s32 f28;
    f32 f2c;
    f32 f30;
    s32 f34;
    f32 f38;
    f32 f3c;
    f32 f40;
    f32 f44;
    f32 f48;
    f32 f4c;
    f32 f50;
    f32 f54;
    f32 f58;
    f32 f5c;
    u8 pad60[4];
    s16 f64;
};
struct RecoveredGlobal_80069024_TCameraCtrl__data_804FF634 {
    s32 value;
    u8 remaining[0x44];
};
struct RecoveredGlobal_80069024_lbl_804FF67C {
    s32 value;
    u8 remaining[0x44];
};
struct RecoveredGlobal_800695E8_TCameraCtrl__data_804FF628 {
    s32 value;
    u8 remaining[0x8];
};
struct RecoveredGlobal_800691C8_TCameraCtrl__data_804FF6D0 {
    s32 value;
    u8 remaining[0x2C];
};
struct RecoveredGlobal_800691C8_TCameraCtrl__data_804FF700 {
    s32 value;
    u8 remaining[0xBC];
};
struct RecoveredGlobal_800691C8_main_task {
    s32 value;
    u8 remaining[0x30];
};
struct RecoveredGlobal_800687E4_TCameraCtrl__data_804FF6C4 {
    s32 value;
    u8 remaining[0x8];
};
struct RecoveredGlobal_80069148_TCameraCtrl__data_804FF6D0 {
    s32 value;
    u8 remaining[0x2C];
};
struct RecoveredGlobal_80069148_TCameraCtrl__data_804FF700 {
    s32 value;
    u8 remaining[0xBC];
};
struct RecoveredGlobal_80069C94_TCameraCtrl__data_804FF628 {
    s32 value;
    u8 remaining[0x8];
};
struct RecoveredGlobal_80069D04_TCameraCtrl__data_804FF628 {
    s32 value;
    u8 remaining[0x8];
};
struct RecoveredGlobal_800687C8_TCameraCtrl__data_804FF6C4 {
    s32 value;
    u8 remaining[0x8];
};
struct RecoveredGlobal_80069304_TCameraCtrl__data_804FF628 {
    s32 value;
    u8 remaining[0x8];
};
struct RecoveredGlobal_8006961C_TCameraCtrl__data_804FF628 {
    s32 value;
    u8 remaining[0x8];
};
struct RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 {
    s32 value;
    u8 remaining[0x44];
};
struct RecoveredGlobal_8006961C_lbl_8058CA60 {
    s32 value;
    u8 remaining[0x54];
};
struct RecoveredGlobal_80069258_TCameraCtrl__data_804FF6D0 {
    s32 value;
    u8 remaining[0x2C];
};
struct RecoveredGlobal_80069258_TCameraCtrl__data_804FF700 {
    s32 value;
    u8 remaining[0xBC];
};
struct RecoveredGlobal_80069258_main_task {
    s32 value;
    u8 remaining[0x30];
};
struct RecoveredGlobal_80069A6C_TCameraCtrl__data_804FF628 {
    u8 value;
    u8 remaining[0xB];
};
struct Stack_80069318 {
    s32 sp8;
    u8 pad_C[0x4];
    f32 sp10;
    f32 sp14;
    u8 pad_18[0x8];
    f32 sp20;
    u8 pad_24[0xC];
    f32 sp30;
    f32 sp34;
    f32 sp38;
    f32 sp3C;
    f32 sp40;
    f32 sp44;
};
struct RecoveredGlobal_80069318_lbl_804FF5E8 { s32 value; u8 remaining[0x24]; };
struct Stack_800693F4 {
    s32 sp8;
    u8 pad_C[0x4];
    f32 sp10;
    f32 sp14;
    u8 pad_18[0x8];
    f32 sp20;
    u8 pad_24[0xC];
    f32 sp30;
    f32 sp34;
    f32 sp38;
    f32 sp3C;
    f32 sp40;
    f32 sp44;
    f32 sp48;
    f32 sp4C;
};
struct RecoveredGlobal_800693F4_TCameraCtrl__data_804FF634 { s32 value; u8 remaining[0x44]; };
struct Stack_800694A8 {
    s32 sp8;
    u8 pad_C[0x4];
    f32 sp10;
    f32 sp14;
    u8 pad_18[0x18];
    f32 sp30;
    f32 sp34;
    f32 sp38;
    f32 sp3C;
    f32 sp40;
    f32 sp44;
    f32 sp48;
    f32 sp4C;
};
struct RecoveredGlobal_800694A8_TCameraCtrl__data_804FF628 {
    s32 value;
    u8 remaining[0x8];
};
struct Stack_80069534 {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
};
struct RecoveredGlobal_80069534_lbl_804381BC {
    s32 value;
    u8 remaining[0x10];
};
struct RecoveredGlobal_80069534_TCameraCtrl__data_804FF628 {
    s32 value;
    u8 remaining[0x8];
};
struct RecoveredGlobal_80069D7C_TCameraCtrl__data_804FF628 {
    s32 value;
    u8 remaining[0x8];
};
struct VBase_18_f8ef8c
{
  char pad[0x18];
};
struct VObj_18_f8ef8c : VBase_18_f8ef8c {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual s32 m5();
};
struct RecoveredGlobal_80069E7C_TCameraCtrl__data_804FF628
{
  s32 value;
  u8 remaining[0x8];
};
struct Cam_80068958 { u8 pad[0x10]; s32 ids[4]; };
struct G_800695A0 { s32 a; s32 b; u32 flags; };
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
struct M_80068FCC { f32 m[3][4]; };
struct W_80068FCC { f32 x, y; };
struct O_80068FCC { M_80068FCC m; W_80068FCC a; W_80068FCC b; W_80068FCC c; };
struct Cam_800688D0 { u8 pad[0x10]; s32 slots[4]; };
struct RecoveredGlobal_800695E8_TCameraCtrl__data_804FF628;
struct Vec_80068810 { f32 x, y, z; };
struct Cam_80068810 {
    u8 pad0[0x94];
    void *slots[4];
    Vec_80068810 vecs[4];
    u8 padd4[0x178 - 0xD4];
    Vec_80068810 v178;
    u8 pad184[0x194 - 0x184];
    void *f194;
};
struct Vec_800696D0 { f32 x, y, z; };
struct Hit_800696D0 { u32 f0; Vec_800696D0 *point; };
struct View_800696D0 {
    u8 pad0[0xD4];
    Vec_800696D0 split_pos[4];
    Vec_800696D0 split_tgt[4];
    Vec_800696D0 split_look[4];
    s32 split_flags[4];
    s32 flag;
    Vec_800696D0 pos;
    Vec_800696D0 tgt;
    u8 pad190[0x1A0 - 0x190];
    Vec_800696D0 eye;
    u8 pad1AC[0x1C8 - 0x1AC];
    Vec_800696D0 look;
};
struct Vec_800698C8 { f32 x, y, z; };
struct Hit_800698C8 { u32 f0; Vec_800698C8 *point; };
struct View_800698C8 {
    u8 pad0[0xD4];
    Vec_800698C8 split_pos[4];
    Vec_800698C8 split_tgt[4];
    Vec_800698C8 split_look[4];
    s32 split_flags[4];
    s32 flag;
    Vec_800698C8 pos;
    Vec_800698C8 tgt;
    u8 pad190[0x1C8 - 0x190];
    Vec_800698C8 look;
};
extern "C" {
void TCameraCtrl__sub_800689E8(void);
s32 is_split_screen();
s32 approach_camera_vector(void *, void *, f32);
extern s32 TCameraCtrl__pose_snap_flags;
s32 GXSetViewport(f32, f32, f32, f32, f32, f32);
s32 GXSetScissor(int, int, int, int);
s32 GXSetScissorBoxOffset(int, int);
extern s16 TCameraCtrl__viewport_size;
extern s16 TCameraCtrl__viewport_height;
extern s16 TCameraCtrl__viewport_x;
extern s16 TCameraCtrl__viewport_y;
extern const f32 TCameraCtrl__data_805D8FDC;
extern const f32 TCameraCtrl__data_805D8FE0;
s32 set_perspective_projection_from_fov(int, f32, f32, f32);
s32 get_entity_id(void *);
s32 get_camera_mode__11TCameraCtrlFv();
s32 TCameraCtrl__sub_8006B358(void *);
extern u8 *camera_ctrl_instance;
void TCameraCtrl__sub_801E32D8(f32, f32);
extern s16 TCameraCtrl__data_805D4E0A;
s32 get_mode__11TCameraCtrlFPv(void *);
s32 matrix_mult_vec(int, void *, void *);
s32 push_matrix();
s32 pop_matrix();
void transform_to_view__11TCameraCtrlFii(s32 arg0, s32 arg1);
void set_active_camera_pose(u8 *arg0, u8 *arg1);
void set_active_camera_pose_from_params(u8 *arg0);
void TCameraCtrl__sub_800687C8(void);
s32 TCameraCtrl__sub_80069304(void);
extern RecoveredGlobal_8006961C_lbl_8058CA60 scene_projection_state;
s32 camera_renderer_setup_nop(void *, int);
s32 fn_803D64F8(void *);
extern f32 camera_default_view_value;
extern f32 camera_default_view_value_b;
extern s16 TCameraCtrl__camera_mode;
extern const f32 lbl_805D8FCC;
extern const f32 TCameraCtrl__data_805D8FD0;
extern const f32 TCameraCtrl__data_805D8FD4;
extern const f32 TCameraCtrl__data_805D8FD8;
extern const f32 lbl_805D8FE4;
s32 set_viewport_scissor__11TCameraCtrlFiPv(int, void *);
extern RecoveredGlobal_80069534_lbl_804381BC camera_ctrl_scissor_default_vec;
s32 activate_camera_mode(s32 arg0);
bool TCameraCtrl__sub_800689F4(void);
extern s32 local_client_id;
s32 *get_character_select_request_buffer(void);
}
void reset_cameras_to_actor(void *actor, s32 arg1);
extern "C" {
u16 TCameraCtrl__sub_8006A5DC();
u8 *get_player_by_client_id(s32);
extern s32 TCameraCtrl__saved_projection_angle;
s32 restore_player_cameras(void);
u8 *csnVector(void *, void *, u32);
f32 vector_length(void *);
void normalize_vector(void *);
f32 TCameraCtrl__sub_80068A04(void);
u8 *TCameraCtrl__ct(u8 *arg0, void *parent);
void * __nw__7TObjectFUl(s32);
typedef char RecoveredGlobal_800687E4_TCameraCtrl__data_804FF6C4_size[sizeof(RecoveredGlobal_800687E4_TCameraCtrl__data_804FF6C4) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_800687C8_TCameraCtrl__data_804FF6C4_size[sizeof(RecoveredGlobal_800687C8_TCameraCtrl__data_804FF6C4) == 0xC ? 1 : -1];
void TCameraCtrl__sub_800687C8(void);
struct Cam_80068958;
void TCameraCtrl__sub_800689E8(void);
bool TCameraCtrl__sub_800689F4(void);
f32 TCameraCtrl__sub_80068A04(void);
extern f32 lbl_805D8FC8;
#pragma push
#pragma dont_inline off
#pragma inline_depth(4)
inline void quad_80068B34(s32 i) {
    TCameraCtrl::set_target_coords((s32)(320.0f * (f32)(i % 2)), (s32)(240.0f * (f32)(i / 2)));
    TCameraCtrl::set_target(0x140, 0xF0);
}
inline void viewport_80068B34(void) {
    GXSetViewport(TCameraCtrl__viewport_x, TCameraCtrl__viewport_y, TCameraCtrl__viewport_size, TCameraCtrl__viewport_height, 0.0f, TCameraCtrl__data_805D8FAC);
    GXSetScissor(TCameraCtrl__viewport_x, TCameraCtrl__viewport_y, TCameraCtrl__viewport_size, TCameraCtrl__viewport_height);
}
#pragma pop
void TCameraCtrl__sub_80068EF0(void);
extern TObject *tl_camera;
typedef char RecoveredGlobal_80069024_TCameraCtrl__data_804FF634_size[sizeof(RecoveredGlobal_80069024_TCameraCtrl__data_804FF634) == 0x48 ? 1 : -1];
typedef char RecoveredGlobal_80069024_lbl_804FF67C_size[sizeof(RecoveredGlobal_80069024_lbl_804FF67C) == 0x48 ? 1 : -1];
typedef char RecoveredGlobal_800691C8_TCameraCtrl__data_804FF6D0_size[sizeof(RecoveredGlobal_800691C8_TCameraCtrl__data_804FF6D0) == 0x30 ? 1 : -1];
typedef char RecoveredGlobal_800691C8_TCameraCtrl__data_804FF700_size[sizeof(RecoveredGlobal_800691C8_TCameraCtrl__data_804FF700) == 0xC0 ? 1 : -1];
typedef char RecoveredGlobal_800691C8_main_task_size[sizeof(RecoveredGlobal_800691C8_main_task) == 0x34 ? 1 : -1];
typedef char RecoveredGlobal_80069148_TCameraCtrl__data_804FF6D0_size[sizeof(RecoveredGlobal_80069148_TCameraCtrl__data_804FF6D0) == 0x30 ? 1 : -1];
typedef char RecoveredGlobal_80069148_TCameraCtrl__data_804FF700_size[sizeof(RecoveredGlobal_80069148_TCameraCtrl__data_804FF700) == 0xC0 ? 1 : -1];
void transform_to_view__11TCameraCtrlFii(s32 arg0, s32 arg1);
typedef char RecoveredGlobal_80069258_TCameraCtrl__data_804FF6D0_size[sizeof(RecoveredGlobal_80069258_TCameraCtrl__data_804FF6D0) == 0x30 ? 1 : -1];
typedef char RecoveredGlobal_80069258_TCameraCtrl__data_804FF700_size[sizeof(RecoveredGlobal_80069258_TCameraCtrl__data_804FF700) == 0xC0 ? 1 : -1];
typedef char RecoveredGlobal_80069258_main_task_size[sizeof(RecoveredGlobal_80069258_main_task) == 0x34 ? 1 : -1];
typedef char RecoveredGlobal_800695E8_TCameraCtrl__data_804FF628_size[sizeof(RecoveredGlobal_800695E8_TCameraCtrl__data_804FF628) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_80069304_TCameraCtrl__data_804FF628_size[sizeof(RecoveredGlobal_80069304_TCameraCtrl__data_804FF628) == 0xC ? 1 : -1];
s32 TCameraCtrl__sub_80069304(void);
#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
typedef char RecoveredGlobal_800694A8_TCameraCtrl__data_804FF628_size[sizeof(RecoveredGlobal_800694A8_TCameraCtrl__data_804FF628) == 0xC ? 1 : -1];
void end_view_override();
#pragma pop
#pragma push
#pragma opt_common_subs off
typedef char RecoveredGlobal_80069534_lbl_804381BC_size[sizeof(RecoveredGlobal_80069534_lbl_804381BC) == 0x14 ? 1 : -1];
typedef char RecoveredGlobal_80069534_TCameraCtrl__data_804FF628_size[sizeof(RecoveredGlobal_80069534_TCameraCtrl__data_804FF628) == 0xC ? 1 : -1];
#pragma pop
typedef char RecoveredGlobal_8006961C_TCameraCtrl__data_804FF628_size[sizeof(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF628) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634_size[sizeof(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634) == 0x48 ? 1 : -1];
typedef char RecoveredGlobal_8006961C_lbl_8058CA60_size[sizeof(RecoveredGlobal_8006961C_lbl_8058CA60) == 0x58 ? 1 : -1];
typedef char RecoveredGlobal_80069A6C_TCameraCtrl__data_804FF628_size[sizeof(RecoveredGlobal_80069A6C_TCameraCtrl__data_804FF628) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_80069C94_TCameraCtrl__data_804FF628_size[sizeof(RecoveredGlobal_80069C94_TCameraCtrl__data_804FF628) == 0xC ? 1 : -1];
void set_active_camera_pose(u8 *arg0, u8 *arg1);
typedef char RecoveredGlobal_80069D04_TCameraCtrl__data_804FF628_size[sizeof(RecoveredGlobal_80069D04_TCameraCtrl__data_804FF628) == 0xC ? 1 : -1];
void set_active_camera_pose_from_params(u8 *arg0);
#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
typedef char RecoveredGlobal_80069D7C_TCameraCtrl__data_804FF628_size[sizeof(RecoveredGlobal_80069D7C_TCameraCtrl__data_804FF628) == 0xC ? 1 : -1];
#pragma pop
typedef struct RecoveredGlobal_80069E7C_TCameraCtrl__data_804FF628 RecoveredGlobal_80069E7C_TCameraCtrl__data_804FF628;
typedef struct VBase_18_f8ef8c VBase_18_f8ef8c;
typedef struct VObj_18_f8ef8c VObj_18_f8ef8c;
typedef char RecoveredGlobal_80069E7C_TCameraCtrl__data_804FF628_size[((sizeof(RecoveredGlobal_80069E7C_TCameraCtrl__data_804FF628)) == 0xC) ? (1) : (-1)];
s32 restore_player_cameras(void);
s32 activate_camera_mode(s32 arg0);
}
struct O_8006A044 { u8 pad[0x1c0]; s32 id; f32 v; };
struct Big_8006A13C { u8 pad[0x70]; u8 unk70[0x10]; };
struct Sel_8006A13C { u8 busy; u8 pad1; u16 slot; u8 pad4[0xC]; };
extern u8 *camera_ctrl_instance;
extern "C" {
s32 obj_testFlags30__14TObjCollidableFUl(u32, s32);
s32 is_split_screen();
}
void reset_cameras_to_actor(void *actor, s32 arg1);
extern "C" {
s32 TWindowShortListCtrl__check_controller_button(void *, s32);
s32 is_on_current_screen__11TCameraCtrlFv(void *, s32);
u8 *get_player_by_client_id(s32);
extern Big_8006A13C controller_input_state;
extern s32 local_client_id;
extern const f32 lbl_805D8FE8;
extern const f32 lbl_805D8FEC;
extern const f32 lbl_805D8FF0;
void TCameraCtrl__sub_8006A044(s32 id, f32 v);
}
struct A_8006A35C { s8 f0; u8 pad1; s16 f2; s32 f4; s32 f8; };
struct B_8006A35C { u8 pad[8]; f32 f8; f32 fc; u8 pad10[8]; f32 f18; u8 pad1c[0xC]; f32 f28; f32 f2c; f32 f30; f32 f34; f32 f38; f32 f3c; f32 f40; f32 f44; };
struct C_8006A35C { f32 f0; f32 f4; f32 f8; };
extern "C" {
void TCameraCtrl__sub_80068358(void *, void *, f32, f32);
extern s32 camera_view_state_flag;
extern s8 camera_ctrl_view_state_byte;
extern s32 TCameraCtrl__pose_snap_flags;
extern const f32 TCameraCtrl__data_805D8FD8;
}
struct RecoveredGlobal_8006A5DC_TCameraCtrl__data_804FF628 {
    u8 value;
    u8 remaining[0xB];
};
struct RecoveredGlobal_8006A788_TCameraCtrl__data_804FF628
{
  s8 value;
  u8 remaining[0xB];
};
struct VBase_18_9639c7
{
  char pad[0x18];
};
struct VObj_18_9639c7 : VBase_18_9639c7 {
    virtual void m0();
    virtual s32 m1();
    virtual void m2();
    virtual void m3();
    virtual s32 m4(s32);
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual s32 m9();
};
struct RecoveredGlobal_8006A7D8_TCameraCtrl__data_804FF628
{
  s32 value;
  u8 remaining[0x8];
};
struct RecoveredGlobal_8006A5EC_TCameraCtrl__data_804FF628
{
  s8 value;
  u8 remaining[0xB];
};
struct Vec_8006A410
{
  f32 x;
  f32 y;
  f32 z;
};
struct VBase_8006A410
{
  char pad[0x18];
};
struct Ctrl_8006A410 : VBase_8006A410 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6(void *);
    u8 pad1C[0x3C - 0x1C];
    Vec_8006A410 pos;
    Vec_8006A410 tgt;
};
struct Master_8006A410
{
  u8 pad[0xD4];
  Vec_8006A410 pos[4];
  Vec_8006A410 tgt[4];
};
struct Views_8006A410
{
  u8 pad[0x10];
  s32 players[4];
};
extern "C" {
u16 TCameraCtrl__sub_8006A5DC(void);
s32 is_split_screen();
s32 apply_camera_controller_pose(int);
s32 resolve_anchor_obstruction__11TCameraCtrlFv(void *, int);
s32 clamp_to_target_obstruction__11TCameraCtrlFv(void *, int);
extern u8 *camera_ctrl_instance;
s32 get_entity_id(void *);
s32 *get_character_select_request_buffer(void);
void reset__11TCameraCtrlFv(void);
void TCameraCtrl__sub_80068354(void);
extern s16 TCameraCtrl__data_805D4E0A;
void reset__11TCameraCtrlFv(void);
}
void select_camera_controller(s32 arg0);
void reset_cameras_to_actor(void *actor, s32 arg1);
typedef char RecoveredGlobal_8006A5DC_TCameraCtrl__data_804FF628_size[sizeof(RecoveredGlobal_8006A5DC_TCameraCtrl__data_804FF628) == 0xC ? 1 : -1];
typedef struct Ctrl_8006A410 Ctrl_8006A410;
typedef struct Master_8006A410 Master_8006A410;
typedef struct VBase_8006A410 VBase_8006A410;
typedef struct Vec_8006A410 Vec_8006A410;
typedef struct Views_8006A410 Views_8006A410;
void reset_cameras_to_actor(void *actor, s32 arg1);
extern "C" {
u16 TCameraCtrl__sub_8006A5DC(void);
typedef struct RecoveredGlobal_8006A788_TCameraCtrl__data_804FF628 RecoveredGlobal_8006A788_TCameraCtrl__data_804FF628;
typedef struct VBase_18_f8ef8c VBase_18_f8ef8c;
typedef struct VObj_18_f8ef8c VObj_18_f8ef8c;
typedef char RecoveredGlobal_8006A788_TCameraCtrl__data_804FF628_size[((sizeof(RecoveredGlobal_8006A788_TCameraCtrl__data_804FF628)) == 0xC) ? (1) : (-1)];
typedef struct RecoveredGlobal_8006A5EC_TCameraCtrl__data_804FF628 RecoveredGlobal_8006A5EC_TCameraCtrl__data_804FF628;
typedef char RecoveredGlobal_8006A5EC_TCameraCtrl__data_804FF628_size[((sizeof(RecoveredGlobal_8006A5EC_TCameraCtrl__data_804FF628)) == 0xC) ? (1) : (-1)];
struct Cam_8006A6C4
{
  u8 pad0[0x68];
  f32 f68;
  f32 f6C;
  f32 f70;
  u8 pad74[0x1C0 - 0x74];
  u32 f1C0;
  f32 f1C4;
};
f32 sin_table_lookup(s32);
extern const f32 lbl_805D8FF4;
}
void select_camera_controller(s32 arg0);
typedef struct RecoveredGlobal_8006A7D8_TCameraCtrl__data_804FF628 RecoveredGlobal_8006A7D8_TCameraCtrl__data_804FF628;
typedef struct VBase_18_9639c7 VBase_18_9639c7;
typedef struct VObj_18_9639c7 VObj_18_9639c7;
typedef char RecoveredGlobal_8006A7D8_TCameraCtrl__data_804FF628_size[((sizeof(RecoveredGlobal_8006A7D8_TCameraCtrl__data_804FF628)) == 0xC) ? (1) : (-1)];
struct Ctl_8006AA90 {
    u8 pad[0x18];
    virtual ~Ctl_8006AA90();
};
extern "C" {
void __dt__7TObjectFv(void *, s32);
void __dl__7TObjectFPv(void *);
Ctl_8006AA90 *TCameraCtrl__sub_8006AA90(Ctl_8006AA90 *self, s16 arg1);
u8 *get_player_by_client_id(s32 i);
extern s32 local_client_id;
Ctl_8006AA90 *TCameraCtrl__sub_8006AA90(Ctl_8006AA90 *self, s16 arg1);
}
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
struct RecoveredGlobal_8006B324_lbl_805137F8 {
    s32 value;
    u8 remaining[0x20];
};
struct Stack_8006ABAC {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
};
struct RecoveredGlobal_8006ABAC_lbl_804381A4 {
    s32 value;
    u8 remaining[0x8];
};
struct RecoveredGlobal_8006ABAC_lbl_804381B0 {
    s32 value;
    u8 remaining[0x8];
};
struct RecoveredGlobal_8006ABAC_lbl_8058D490 {
    s32 value;
    u8 remaining[0x2C];
};
struct Stack_8006AC70 {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
};
struct RecoveredGlobal_8006AC70_lbl_8043818C {
    s32 value;
    u8 remaining[0x8];
};
struct RecoveredGlobal_8006AC70_lbl_80438198 {
    s32 value;
    u8 remaining[0x8];
};
struct RecoveredGlobal_8006AC70_lbl_804FF610 {
    s32 value;
    u8 remaining[0x8];
};
struct RecoveredGlobal_8006AC70_lbl_804FF61C {
    s32 value;
    u8 remaining[0x8];
};
struct RecoveredGlobal_8006AC70_lbl_8058D490 {
    s32 value;
    u8 remaining[0x2C];
};
struct Vec_8006B0D4 { f32 x, y, z; };
struct Count_8006B0D4 {
    s8 flag;
    s32 count;
    u8 pad8[0x8];
};
struct Cam_8006B0D4 {
    s32 name;
    u8 pad4[0x14];
    void *vt;
    s8 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    f32 f2C;
    f32 f30;
    s32 f34;
    f32 f38[10];
    u8 pad60[0x4];
    s16 f64;
    Vec_8006B0D4 f68;
    f32 f74;
    f32 f78;
    f32 f7C;
    f32 f80;
    u8 pad84[0x8];
    s32 f8C;
    s32 f90;
    s32 f94[4];
    Vec_8006B0D4 fA4[4];
    Vec_8006B0D4 fD4[4];
    Vec_8006B0D4 f104[4];
    Vec_8006B0D4 f134[4];
    s32 f164[4];
    s32 f174;
    Vec_8006B0D4 f178;
    Vec_8006B0D4 f184;
    s32 f190;
    s32 f194;
    s32 f198;
    s32 f19C;
    Vec_8006B0D4 f1A0;
    Vec_8006B0D4 f1AC;
    f32 f1B8;
    f32 f1BC;
    s32 f1C0;
    u8 pad1C4[0x4];
    Vec_8006B0D4 f1C8;
};
extern "C" {
u8 * copy_view_params__11TCameraCtrlFii(C30_8006AD34 *arg0, const C30_8006AD34 *arg1);
extern RecoveredGlobal_8006B324_lbl_805137F8 chr_select_request_buffer;
s32 rotate_matrix_y(int, void *);
s32 rotate_matrix_x(int, void *);
s32 push_matrix_from(void *);
f32 rotate_vector_by_current_matrix(void *, void *);
s32 pop_matrix();
extern RecoveredGlobal_8006ABAC_lbl_804381A4 lbl_804381A4;
extern RecoveredGlobal_8006ABAC_lbl_804381B0 lbl_804381B0;
extern RecoveredGlobal_8006ABAC_lbl_804FF61C camera_pitch_rotated_up_vector;
extern RecoveredGlobal_8006ABAC_lbl_8058D490 identity_matrix;
extern RecoveredGlobal_8006AC70_lbl_8043818C lbl_8043818C;
extern RecoveredGlobal_8006AC70_lbl_80438198 lbl_80438198;
struct V3_8006AD34 { f32 x, y, z; };
u8 *get_target__11TCameraCtrlFv(void *);
s32 reset_view_flags__11TCameraCtrlFv(void *);
s32 cycle_spectate_target__11TCameraCtrlFv(void *);
f32 vector_length(void *);
void normalize_vector(void *);
int TCameraCtrl__sub_8006B370(f32);
s32 TCameraCtrl__sub_8006B358(void* p);
int is_quest_active(void);
int TCameraCtrl__sub_8006B3B8(void* p);
s32 get_mode__11TCameraCtrlFPv(void* p);
void render__11TCameraCtrlFv(void *arg0);
int reset_to_local_player__11TCameraCtrlFv(void*);
int set_fixed_position_and_target__11TCameraCtrlFPUcPUc(void*);
extern "C" {
void *TCameraCtrl__vt0(void);
}
extern "C" {
void *TCameraCtrl__vt10(void);
}
extern "C" {
void *TCameraCtrl__vt11(void);
}
extern "C" {
void *TCameraCtrl__vt12(void);
}
extern "C" {
void *TCameraCtrl__vt4(void);
}
extern "C" {
void *TCameraCtrl__vt5(void);
}
extern "C" {
void *TCameraCtrl__vt6(void);
}
extern "C" {
void *TCameraCtrl__vt7(void);
}
extern "C" {
void *TCameraCtrl__vt9(void);
}
extern "C" {
void render_shadows__7TObjectFv();
}
void __ct__7TObjectFP7TObject(void *, void *);
extern s32 lbl_805D283C;
extern const f32 lbl_805D8FE4;
void run_task__11TCameraCtrlFv(u8 *arg0);
void *camera_controller_registry[13] = {
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0,
};
void *lbl_80488A8C[13] = {
    (void *)&TCameraCtrl__vt0, (void *)&TCameraCtrl__vt0, (void *)&TCameraCtrl__vt0, (void *)&TCameraCtrl__vt0,
    (void *)&TCameraCtrl__vt4, (void *)&TCameraCtrl__vt5, (void *)&TCameraCtrl__vt6, (void *)&TCameraCtrl__vt7,
    (void *)&CreationCamera::create, (void *)&TCameraCtrl__vt9, (void *)&TCameraCtrl__vt10, (void *)&TCameraCtrl__vt11,
    (void *)&TCameraCtrl__vt12,
};
void *lbl_80488AC0[6] = {
    (void *)0x0, (void *)0x0, (void *)&TCameraCtrl__sub_8006AA90, (void *)&run_task__11TCameraCtrlFv,
    (void *)&render__11TCameraCtrlFv, (void *)&render_shadows__7TObjectFv,
};
    extern int camera_split_screen_selector;
#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
typedef char RecoveredGlobal_8006ABAC_lbl_804381A4_size[sizeof(RecoveredGlobal_8006ABAC_lbl_804381A4) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_8006ABAC_lbl_804381B0_size[sizeof(RecoveredGlobal_8006ABAC_lbl_804381B0) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_8006ABAC_lbl_804FF610_size[sizeof(RecoveredGlobal_8006ABAC_lbl_804FF610) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_8006ABAC_lbl_804FF61C_size[sizeof(RecoveredGlobal_8006ABAC_lbl_804FF61C) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_8006ABAC_lbl_8058D490_size[sizeof(RecoveredGlobal_8006ABAC_lbl_8058D490) == 0x30 ? 1 : -1];
#pragma pop
#pragma push
#pragma opt_common_subs off
typedef char RecoveredGlobal_8006AC70_lbl_8043818C_size[sizeof(RecoveredGlobal_8006AC70_lbl_8043818C) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_8006AC70_lbl_80438198_size[sizeof(RecoveredGlobal_8006AC70_lbl_80438198) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_8006AC70_lbl_804FF610_size[sizeof(RecoveredGlobal_8006AC70_lbl_804FF610) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_8006AC70_lbl_804FF61C_size[sizeof(RecoveredGlobal_8006AC70_lbl_804FF61C) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_8006AC70_lbl_8058D490_size[sizeof(RecoveredGlobal_8006AC70_lbl_8058D490) == 0x30 ? 1 : -1];
#pragma pop
u8 * copy_view_params__11TCameraCtrlFii(C30_8006AD34 *arg0, const C30_8006AD34 *arg1);
#pragma push
#pragma opt_common_subs off
u8 *TCameraCtrl__ct(u8 *arg0, void *parent);
#pragma pop
typedef char RecoveredGlobal_8006B324_lbl_805137F8_size[sizeof(RecoveredGlobal_8006B324_lbl_805137F8) == 0x24 ? 1 : -1];
s32 *get_character_select_request_buffer(void);
    extern int TCameraCtrl__camera_id;
    extern short TCameraCtrl__viewport_size;
    extern short TCameraCtrl__viewport_height;
    extern short TCameraCtrl__viewport_x;
    extern short TCameraCtrl__viewport_y;
s32 TCameraCtrl__sub_8006B358(void* p);
s32 get_mode__11TCameraCtrlFPv(void* p);
    extern int quest_active_flag;
int is_quest_active(void);
int TCameraCtrl__sub_8006B370(f32 farg0);
int TCameraCtrl__sub_8006B3B8(void* p);
}


#endif
