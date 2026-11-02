// The three camera slices share a native conversion/viewport literal pool.
// Keep the first three small functions immediate: their zero literal precedes
// the named scale below. The remaining definitions run backwards under native
// deferred generation so their emitted code retains original address order.
// Parsing those bodies before defining the scale keeps CameraViewParams::apply's
// multiply intact. This is an emission arrangement, not recovered source order.
#include "pso/misc/TCameraCtrl_native.h"

#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TUnk_80488A28::run_task() { }
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void *TCameraCtrl::get_target_ptr() { return &m_44; }
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl__sub_800687C8(void) {
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_800687C8_TCameraCtrl__data_804FF6C4 *)&TCameraCtrl__up_vector).value) + 0) = (f32) 0.0f;
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_800687C8_TCameraCtrl__data_804FF6C4 *)&TCameraCtrl__up_vector).value) + 4) = (f32) TCameraCtrl__data_805D8FAC;
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_800687C8_TCameraCtrl__data_804FF6C4 *)&TCameraCtrl__up_vector).value) + 8) = (f32) 0.0f;
}
#pragma pop

// The compiler emits deferred functions in reverse definition order.
#pragma defer_codegen on

#pragma push
#pragma dont_inline off
#pragma auto_inline off
int TCameraCtrl__sub_8006B3B8(void* p) { return set_fixed_position_and_target__11TCameraCtrlFPUcPUc(p); }
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
int TCameraCtrl::reset_battle_camera() { return reset_to_local_player__11TCameraCtrlFv(this); }
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
int TCameraCtrl__sub_8006B370(f32 farg0) {
    u32 v = *(u32 *)&farg0 & 0x7F800000;
    return v == 0x7F800000;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
int is_quest_active(void) { return quest_active_flag; }
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
s32 get_mode__11TCameraCtrlFPv(void* p) { return *(s32*)((char*)p + 0x1c); }
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
// Entity-ID queries return a widened 16-bit field in r3.
s32 TCameraCtrl__sub_8006B358(void* p) { return *(u16*)((char*)p + 0x20); }
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::set_target_coords(int a0, int a1) { TCameraCtrl__viewport_x = a0; TCameraCtrl__viewport_y = a1; }
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::set_target(int a0, int a1) { TCameraCtrl__viewport_size = a0; TCameraCtrl__viewport_height = a1; }
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
int TCameraCtrl::get_camera_id() { return TCameraCtrl__camera_id; }
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
int TCameraCtrl::get_instance() { return camera_split_screen_selector; }
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
s32 *get_character_select_request_buffer(void) {
    return &chr_select_request_buffer.value;
}
#pragma pop


#pragma push
#pragma opt_common_subs off
#pragma dont_inline off
#pragma auto_inline off
u8 *TCameraCtrl__ct(u8 *arg0, void *parent) {
    s32 i;
    s32 k;
    s32 j;
    __ct__7TObjectFP7TObject(arg0, parent);
    ((Cam_8006B0D4 *)arg0)->vt = (void **)lbl_80488AC0;
    ((Cam_8006B0D4 *)arg0)->name = lbl_805D283C;
    ((Cam_8006B0D4 *)arg0)->f1C = 0;
    camera_ctrl_instance = arg0;
    ((Cam_8006B0D4 *)arg0)->f19C = 0x3555;
    ((Cam_8006B0D4 *)arg0)->f90 = 0;
    ((Cam_8006B0D4 *)arg0)->f174 = 0;
    ((Cam_8006B0D4 *)arg0)->f1C8.x = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f1C8.y = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f1C8.z = 0.0f;
    for (i = 0; i < 4; i++) {
        ((Cam_8006B0D4 *)arg0)->f94[i] = 0;
        ((Cam_8006B0D4 *)arg0)->fA4[i].x = 0.0f;
        ((Cam_8006B0D4 *)arg0)->fA4[i].y = 0.0f;
        ((Cam_8006B0D4 *)arg0)->fA4[i].z = 0.0f;
        ((Cam_8006B0D4 *)arg0)->f134[i].x = 0.0f;
        ((Cam_8006B0D4 *)arg0)->f134[i].y = 0.0f;
        ((Cam_8006B0D4 *)arg0)->f134[i].z = 0.0f;
        ((Cam_8006B0D4 *)arg0)->f164[i] = 0;
    }
    ((Cam_8006B0D4 *)arg0)->f178.x = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f178.y = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f178.z = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f1A0.x = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f1A0.y = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f1A0.z = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f184.x = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f184.y = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f184.z = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f1AC.x = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f1AC.y = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f1AC.z = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f190 = 0;
    ((Cam_8006B0D4 *)arg0)->f194 = 0;
    ((Cam_8006B0D4 *)arg0)->f198 = 0;
    ((Cam_8006B0D4 *)arg0)->f1C0 = 0;
    ((Cam_8006B0D4 *)arg0)->f1B8 = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f1BC = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f8C = 0;
    ((Cam_8006B0D4 *)arg0)->f68.x = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f68.y = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f68.z = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f20 = 0;
    ((Cam_8006B0D4 *)arg0)->f24 = 0;
    ((Cam_8006B0D4 *)arg0)->f28 = 0;
    ((Cam_8006B0D4 *)arg0)->f2C = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f30 = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f34 = 0;
    ((Cam_8006B0D4 *)arg0)->f64 = 0;
    ((Cam_8006B0D4 *)arg0)->f38[0] = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f38[1] = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f38[2] = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f38[3] = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f38[4] = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f38[5] = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f38[6] = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f38[7] = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f38[8] = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f38[9] = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f74 = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f78 = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f7C = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f80 = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f80 = 0.0f;
    ((Cam_8006B0D4 *)arg0)->f80 = 0.0f;
    {
        for (k = 0; k < 13; k++) {
            ((s32 *)camera_controller_registry)[(*(Count_8006B0D4 *)TCameraCtrl__view_state).count++] = ((s32 (**)(void))lbl_80488A8C)[k]();
        }
    }
    (*(Count_8006B0D4 *)TCameraCtrl__view_state).flag = 0;
    for (j = 0; j < 4; j++) {
        ((Cam_8006B0D4 *)arg0)->fD4[j].x = 0.0f;
        ((Cam_8006B0D4 *)arg0)->fD4[j].y = 0.0f;
        ((Cam_8006B0D4 *)arg0)->fD4[j].z = 0.0f;
        ((Cam_8006B0D4 *)arg0)->f104[j].x = 0.0f;
        ((Cam_8006B0D4 *)arg0)->f104[j].y = 0.0f;
        ((Cam_8006B0D4 *)arg0)->f104[j].z = 0.0f;
    }
    lbl_804FF5E8[0] = 0.0f;
    lbl_804FF5E8[1] = 0.0f;
    lbl_804FF5E8[2] = 0.0f;
    lbl_804FF5E8[3] = 0.0f;
    lbl_804FF5E8[4] = 0.0f;
    lbl_804FF5E8[5] = lbl_805D8FE4;
    return arg0;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::setup_default_view(void *arg1_arg) {
    Vec_8006AF9C *arg1 = (Vec_8006AF9C *)arg1_arg;
    Vec_8006AF9C eye;
    Vec_8006AF9C at;
    Vec_8006AF9C d;
    Vec_8006AF9C *pat;
    eye.x = lbl_804FF5E8[0];
    eye.y = lbl_804FF5E8[1];
    eye.z = lbl_804FF5E8[2];
    if (arg1 != 0) {
        eye.x += arg1->x;
        eye.y += arg1->y;
        eye.z += arg1->z;
    }
    at.x = lbl_804FF5E8[3] + eye.x;
    at.y = lbl_804FF5E8[4] + eye.y;
    at.z = lbl_804FF5E8[5] + eye.z;
    d.x = eye.x - at.x;
    d.y = eye.y - at.y;
    d.z = eye.z - at.z;
    pat = &at;
    if (0.0f == vec_squared_length(&d)) {
        pat->z += TCameraCtrl__data_805D8FAC;
    }
    if (0.0f == d.x && 0.0f == d.z) {
        pat->z += TCameraCtrl__data_805D8FAC;
    }
    set_perspective_projection_from_fov(m_19c, TCameraCtrl__data_805D8FDC, TCameraCtrl__data_805D8FAC, TCameraCtrl__data_805D8FE0);
    set_camera_look_at((u8 *)&eye, (u8 *)&at, (u8 *)TCameraCtrl__up_vector);
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
u8 *copy_view_params__11TCameraCtrlFii(C30_8006AD34 *destination, const C30_8006AD34 *source) {
    *destination = *source;
    return (u8 *)destination;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::run_task() {
    V3_8006AD34 v;
    u8 *t;
    s32 i;
    m_1c = 1;
    update_target_from_state();
    cycle_spectate_target__11TCameraCtrlFv(this);
    update_active_controller();
    reset_view_flags__11TCameraCtrlFv(this);
    if ((camera_ctrl_instance) != NULL) {
        if (TCameraCtrl__sub_8006B370((*(f32 *)((camera_ctrl_instance) + (0x178)))) == 0 && TCameraCtrl__sub_8006B370((*(f32 *)((camera_ctrl_instance) + (0x17C)))) == 0) {
            TCameraCtrl__sub_8006B370((*(f32 *)((camera_ctrl_instance) + (0x180))));
        }
        if (TCameraCtrl__sub_8006B370((*(f32 *)((camera_ctrl_instance) + (0x178)))) == 0 && TCameraCtrl__sub_8006B370((*(f32 *)((camera_ctrl_instance) + (0x17C)))) == 0) {
            TCameraCtrl__sub_8006B370((*(f32 *)((camera_ctrl_instance) + (0x180))));
        }
        if (TCameraCtrl__sub_8006B370((*(f32 *)((camera_ctrl_instance) + (0x184)))) == 0 && TCameraCtrl__sub_8006B370((*(f32 *)((camera_ctrl_instance) + (0x188)))) == 0) {
            TCameraCtrl__sub_8006B370((*(f32 *)((camera_ctrl_instance) + (0x18C))));
        }
    }
    if ((camera_ctrl_instance) != NULL) {
        t = get_target__11TCameraCtrlFv(this);
        v.x = (((f32 *)t)[0] + (*(f32 *)((camera_ctrl_instance) + (0x184)))) - (*(f32 *)((camera_ctrl_instance) + (0x178)));
        v.y = (((f32 *)t)[1] + (*(f32 *)((camera_ctrl_instance) + (0x188)))) - (*(f32 *)((camera_ctrl_instance) + (0x17C)));
        v.z = (((f32 *)t)[2] + (*(f32 *)((camera_ctrl_instance) + (0x18C)))) - (*(f32 *)((camera_ctrl_instance) + (0x180)));
        lbl_804FF5E8[0] = position.x;
        lbl_804FF5E8[1] = position.y;
        lbl_804FF5E8[2] = position.z;
        if (0.0f != vec_squared_length(&v)) {
            normalize_vector(&v);
        }
        lbl_804FF5E8[3] = v.x;
        lbl_804FF5E8[4] = v.y;
        lbl_804FF5E8[5] = v.z;
        vector_length(&v);
    }
    if (is_split_screen() != 0) {
        if (TCameraCtrl__view_state[0] == 5) {
            ((TObjBoss2Tunnel *)lbl_804FF5E8)->render(&TCameraCtrl__view_matrices[TCameraCtrl::get_camera_no()]);
            for (i = 1; i < 4; i++) {
                copy_view_params__11TCameraCtrlFii(&TCameraCtrl__view_matrices[i], &TCameraCtrl__view_matrices[0]);
            }
        } else {
            ((TObjBoss2Tunnel *)lbl_804FF5E8)->render(&TCameraCtrl__view_matrices[TCameraCtrl::get_camera_no()]);
        }
    } else {
        ((TObjBoss2Tunnel *)lbl_804FF5E8)->render(TCameraCtrl__view_matrix);
    }
    calc_rotated_axes();
}
#pragma pop


#pragma push
#pragma opt_common_subs off
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::calc_rotated_axes() {
    typedef char sp8_offset[(offsetof(Stack_8006AC70, sp8) == 0x0) ? 1 : -1];
    typedef char spC_offset[(offsetof(Stack_8006AC70, spC) == 0x4) ? 1 : -1];
    typedef char sp10_offset[(offsetof(Stack_8006AC70, sp10) == 0x8) ? 1 : -1];
    typedef char sp14_offset[(offsetof(Stack_8006AC70, sp14) == 0xC) ? 1 : -1];
    typedef char sp18_offset[(offsetof(Stack_8006AC70, sp18) == 0x10) ? 1 : -1];
    typedef char sp1C_offset[(offsetof(Stack_8006AC70, sp1C) == 0x14) ? 1 : -1];
    Stack_8006AC70 stack;
    stack.sp14 = *(s32 *)((s8 *)&lbl_8043818C.value + 0);
    stack.sp18 = *(s32 *)((s8 *)&lbl_8043818C.value + 4);
    stack.sp1C = *(s32 *)((s8 *)&lbl_8043818C.value + 8);
    stack.sp8 = *(s32 *)((s8 *)&lbl_80438198.value + 0);
    stack.spC = *(s32 *)((s8 *)&lbl_80438198.value + 4);
    stack.sp10 = *(s32 *)((s8 *)&lbl_80438198.value + 8);
    push_matrix_from((void *) (&(*(RecoveredGlobal_8006AC70_lbl_8058D490 *)&identity_matrix).value));
    rotate_matrix_y(0, (void *)this->m_194);
    rotate_vector_by_current_matrix((void *)&stack.sp14, (void *)camera_right);
    pop_matrix();
    push_matrix_from((void *) (&(*(RecoveredGlobal_8006AC70_lbl_8058D490 *)&identity_matrix).value));
    rotate_matrix_x(0, (void *)this->m_190);
    rotate_vector_by_current_matrix((void *)&stack.sp8, (void *) (&(*(RecoveredGlobal_8006AC70_lbl_804FF61C *)&camera_pitch_rotated_up_vector).value));
    pop_matrix();
}
#pragma pop


#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::calc_axes_from_angles(s32 arg0, s32 arg1, s32 arg2) {
    typedef char sp8_offset[(offsetof(Stack_8006ABAC, sp8) == 0x0) ? 1 : -1];
    typedef char spC_offset[(offsetof(Stack_8006ABAC, spC) == 0x4) ? 1 : -1];
    typedef char sp10_offset[(offsetof(Stack_8006ABAC, sp10) == 0x8) ? 1 : -1];
    typedef char sp14_offset[(offsetof(Stack_8006ABAC, sp14) == 0xC) ? 1 : -1];
    typedef char sp18_offset[(offsetof(Stack_8006ABAC, sp18) == 0x10) ? 1 : -1];
    typedef char sp1C_offset[(offsetof(Stack_8006ABAC, sp1C) == 0x14) ? 1 : -1];
    Stack_8006ABAC stack;
    stack.sp14 = *(s32 *)((s8 *)&lbl_804381A4.value + 0);
    stack.sp18 = *(s32 *)((s8 *)&lbl_804381A4.value + 4);
    stack.sp1C = *(s32 *)((s8 *)&lbl_804381A4.value + 8);
    stack.sp8 = *(s32 *)((s8 *)&lbl_804381B0.value + 0);
    stack.spC = *(s32 *)((s8 *)&lbl_804381B0.value + 4);
    stack.sp10 = *(s32 *)((s8 *)&lbl_804381B0.value + 8);
    push_matrix_from((void *)&identity_matrix.value);
    rotate_matrix_y(0, (void *)arg2);
    rotate_vector_by_current_matrix((void *)&stack.sp14, (void *)camera_right);
    pop_matrix();
    push_matrix_from((void *)&identity_matrix.value);
    rotate_matrix_x(0, (void *)arg1);
    rotate_vector_by_current_matrix((void *)&stack.sp8, (void *)&camera_pitch_rotated_up_vector.value);
    pop_matrix();
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::render() {
    if ((is_split_screen() == 0) && (TMainTask::get_render_pass() != 1)) {
        if (m_1c == 0) {
            setup_default_view(0);
        }
        m_1c = 0;
    }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
Ctl_8006AA90 *TCameraCtrl__sub_8006AA90(Ctl_8006AA90 *self, s16 arg1) {
    s32 i;
    if (self != NULL) {
        *(u8 **)((u8 *)self + 0x18) = ((u8 *)lbl_80488AC0);
        camera_ctrl_instance = 0;
        for (i = 0; i < 13; i++) {
            if (camera_controller_registry[i] != NULL) {
                delete (Ctl_8006AA90 *)camera_controller_registry[i];
                camera_controller_registry[i] = NULL;
            }
        }
        ((s32 *)&TCameraCtrl__view_state)[1] = 0;
        __dt__7TObjectFv(self, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(self);
        }
    }
    return self;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::update_target_from_state() {
    if ((!(*(s32 *)((s8 *)TCameraCtrl__view_state + 8) & 4) && !(*(s32 *)((s8 *)TCameraCtrl__view_state + 8) & 8)) || (*(s32 *)((s8 *)TCameraCtrl__view_state + 8) & 0x20) || (*(s32 *)((s8 *)TCameraCtrl__view_state + 8) & 0x80) || (*(s32 *)((s8 *)TCameraCtrl__view_state + 8) & 0x800)) {
        if (*(s32 *)((s8 *)TCameraCtrl__view_state + 8) & 2) {
            select_camera_controller(this->m_20 + 9);
            return;
        }
        if ((*(s32 *)((s8 *)TCameraCtrl__view_state + 8) & 0x20) || (*(s32 *)((s8 *)TCameraCtrl__view_state + 8) & 0x80)) {
            select_camera_controller(*(u8 *)((s8 *)TCameraCtrl__view_state + 1));
            u32 temp = (u32)get_player_by_client_id(local_client_id);
            if (temp != 0U) {
                reset_cameras_to_actor((void *)temp, 0);
            }
        }
    }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::update_active_controller() {
  s32 temp_r3;
  s32 var_r27;
  s32 camera_no;
  s32 *new_var;
  u8 *temp_r30;
  if (((u8) (*((u8 *) (((s8 *) (&(*(RecoveredGlobal_8006A7D8_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + 0)))) != 0)
  {
    camera_no = 0;
  }
  else
    if (is_split_screen() != 0)
  {
    camera_no = TCameraCtrl::get_camera_no();
  }
  else
  {
    camera_no = 0;
  }
  temp_r30 = (u8 *)camera_controller_registry[TCameraCtrl__view_state[0] + camera_no];
  if (temp_r30 != 0)
  {
    if (!((*((s32 *) (((s8 *) (&(*(RecoveredGlobal_8006A7D8_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + 8))) & 0x800))
    {
      (((VObj_18_9639c7 *)(temp_r30))->m1());
    }
    if ((*((s32 *) (((s8 *) (&(*(RecoveredGlobal_8006A7D8_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + 8))) & 2)
    {
      (((VObj_18_9639c7 *)(temp_r30))->m4((0)));
    }
    else
      if ((*((s32 *) (((s8 *) (&(*(RecoveredGlobal_8006A7D8_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + 8))) & 0x80)
    {
      (((VObj_18_9639c7 *)(temp_r30))->m4((1)));
    }
    apply_camera_controller_pose((int) temp_r30);
    new_var = (s32 *) (((s8 *) (&(*(RecoveredGlobal_8006A7D8_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + 8);
    var_r27 = 0;
    if (is_split_screen() != 0)
    {
      if ((((*new_var) & 0x20) || ((*new_var) & 0x800)) && (!((*new_var) & (0x1000 << camera_no))))
      {
        var_r27 = 1;
        *new_var = (s32) ((*((s32 *) (((s8 *) (&(*(RecoveredGlobal_8006A7D8_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + 8))) & ((-0x1001) << camera_no));
      }
    }
    else
      if (((*new_var) & 0x20) || ((*((s32 *) (((s8 *) (&(*(RecoveredGlobal_8006A7D8_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + 8))) & 0x800))
    {
      var_r27 = 1;
    }
    if (var_r27 != 0)
    {
      update_position();
    }
    else
    {
      if ((*((s32 *) (((s8 *) temp_r30) + 0x38))) & 1)
      {
        resolve_anchor_obstruction__11TCameraCtrlFv((void *) this, (int) temp_r30);
      }
      temp_r3 = *((s32 *) (((s8 *) temp_r30) + 0x38));
      if (temp_r3 & 4)
      {
        update_pose_smoothing();
      }
      else
        if (temp_r3 & 8)
      {
        update_target_smoothing();
      }
      else
      {
        update_position();
      }
      if ((*((s32 *) (((s8 *) temp_r30) + 0x38))) & 1)
      {
        clamp_to_target_obstruction__11TCameraCtrlFv((void *) this, (int) temp_r30);
      }
      update_shake();
    }
    set_perspective_projection_from_fov(this->m_19c, (f32) TCameraCtrl__data_805D8FDC, (f32) TCameraCtrl__data_805D8FAC, (f32) TCameraCtrl__data_805D8FE0);
    (((VObj_18_9639c7 *)(temp_r30))->m9());
    if (is_split_screen() == 0)
    {
      *((s32 *) (((s8 *) ((u8 *)this)) + 0x94)) = this->m_194;
    }
  }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void select_camera_controller(s32 arg0) {
  u8 *temp_r0;
  (*(RecoveredGlobal_8006A788_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value = arg0;
  // The original lookup masks the selector to its low byte.
  temp_r0 = (u8 *)camera_controller_registry[(u8)arg0];
  if (temp_r0 != 0)
  {
    (((VObj_18_f8ef8c *)(temp_r0))->m5());
  }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::update_shake() {
  Cam_8006A6C4 *self = (Cam_8006A6C4 *) this;
  f32 amp;
  s32 k;
  if (self->f1C0 != 0) {
    self->f1C0--;
    k = self->f1C0 * 40;
    amp = self->f1C4 * (f32)self->f1C0;
    self->f68 = 0.0f;
    self->f6C = amp * sin_table_lookup((s32)(lbl_805D8FF4 * (f32)k));
    self->f70 = 0.0f;
  }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::select_active_controller(s8 arg0) {
  f32 temp_f0;
  f32 temp_f0_2;
  f32 temp_f0_3;
  f32 temp_f0_4;
  f32 temp_f0_5;
  f32 temp_f0_6;
  u8 *temp_r31;
  (*(RecoveredGlobal_8006A5EC_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value = arg0;
  // Keep the unsigned low-byte lookup even though the argument is signed.
  temp_r31 = (u8 *)camera_controller_registry[(u8)arg0];
  if (temp_r31 != 0)
  {
    (((VObj_18_f8ef8c *)(temp_r31))->m5());
    if (((void *) camera_ctrl_instance) != 0)
    {
      temp_f0 = *((f32 *) (((s8 *) temp_r31) + 0x3C));
      *((f32 *) (((s8 *) camera_ctrl_instance) + 0x1A0)) = temp_f0;
      *((f32 *) (((s8 *) camera_ctrl_instance) + 0x178)) = temp_f0;
      temp_f0_2 = *((f32 *) (((s8 *) temp_r31) + 0x40));
      *((f32 *) (((s8 *) camera_ctrl_instance) + 0x1A4)) = temp_f0_2;
      *((f32 *) (((s8 *) camera_ctrl_instance) + 0x17C)) = temp_f0_2;
      temp_f0_3 = *((f32 *) (((s8 *) temp_r31) + 0x44));
      *((f32 *) (((s8 *) camera_ctrl_instance) + 0x1A8)) = temp_f0_3;
      *((f32 *) (((s8 *) camera_ctrl_instance) + 0x180)) = temp_f0_3;
      temp_f0_4 = *((f32 *) (((s8 *) temp_r31) + 0x48));
      *((f32 *) (((s8 *) camera_ctrl_instance) + 0x1AC)) = temp_f0_4;
      *((f32 *) (((s8 *) camera_ctrl_instance) + 0x184)) = temp_f0_4;
      temp_f0_5 = *((f32 *) (((s8 *) temp_r31) + 0x4C));
      *((f32 *) (((s8 *) camera_ctrl_instance) + 0x1B0)) = temp_f0_5;
      *((f32 *) (((s8 *) camera_ctrl_instance) + 0x188)) = temp_f0_5;
      temp_f0_6 = *((f32 *) (((s8 *) temp_r31) + 0x50));
      *((f32 *) (((s8 *) camera_ctrl_instance) + 0x1B4)) = temp_f0_6;
      *((f32 *) (((s8 *) camera_ctrl_instance) + 0x18C)) = temp_f0_6;
    }
  }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
// Consumers retain a 16-bit result; the stored controller selector is one byte.
u16 TCameraCtrl__sub_8006A5DC(void) {
    return (*(RecoveredGlobal_8006A5DC_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void reset_cameras_to_actor(void *actor, s32 arg1) {
  s32 view = 0;
  u16 new_var;
  s32 count = 0;
  Ctrl_8006A410 *c;
  s32 id;
  s32 i;
  if (actor == 0)
  {
    return;
  }
  new_var = (u16) get_entity_id(actor);
  id = new_var;
  if (is_split_screen() == 0)
  {
    view = 0;
  }
  else
  {
    Views_8006A410 *v = (Views_8006A410 *) get_character_select_request_buffer();
    for (i = 0; i < 4; i++)
    {
      s32 p = v->players[i];
      if (p == id)
      {
        view = count;
      }
      if (p >= 0)
      {
        count++;
      }
    }
  }
  c = (Ctrl_8006A410 *)camera_controller_registry[TCameraCtrl__view_state[0] + view];
  if (c != 0)
  {
    if (is_split_screen() == 0)
    {
      *((void **) (((s8 *) camera_ctrl_instance) + 0x90)) = actor;
    }
    ((TUnk_80488A28 *)c)->set_target((u32)actor);
    c->m6(actor);
    if (is_split_screen() != 0)
    {
      *((s32 *) (((s8 *) TCameraCtrl__view_state) + 8)) |= 0x800;
      if (is_boss_area() == 0)
      {
        *((s32 *) (((s8 *) TCameraCtrl__view_state) + 8)) |= 0x1000;
        *((s32 *) (((s8 *) TCameraCtrl__view_state) + 8)) |= 0x2000;
        *((s32 *) (((s8 *) TCameraCtrl__view_state) + 8)) |= 0x4000;
        *((s32 *) (((s8 *) TCameraCtrl__view_state) + 8)) |= 0x8000;
        *((s32 *) (((s8 *) TCameraCtrl__view_state) + 8)) &= (-0x1001) << view;
      }
    }
    else
    {
      *((s32 *) (((s8 *) TCameraCtrl__view_state) + 8)) |= 0x800;
    }
  }
  c = (Ctrl_8006A410 *)camera_controller_registry[view];
  if (c != 0)
  {
    ((TUnk_80488A28 *)c)->set_target((u32)actor);
    c->m6(actor);
  }
  if (camera_ctrl_instance != 0)
  {
    VecCopy((Vec *)(&((Master_8006A410 *) camera_ctrl_instance)->pos[view]), (const Vec *)&c->pos);
    VecCopy((Vec *)(&((Master_8006A410 *) camera_ctrl_instance)->tgt[view]), (const Vec *)&c->tgt);
  }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::reset_view_state() {
    A_8006A35C *pa = (A_8006A35C *)TCameraCtrl__view_state;
    B_8006A35C *pb = (B_8006A35C *)TCameraCtrl__data_804FF634;
    C_8006A35C *pc;
    TCameraCtrl__pose_snap_flags = 0;
    ((A_8006A35C *)TCameraCtrl__view_state)->f0 = 0;
    pa->f2 = 0;
    pa->f4 = 0;
    pa->f8 = 0;
    pb->f18 = 0.0f;
    pb->f28 = 0.0f;
    pb->f2c = 0.0f;
    pb->f8 = 0.0f;
    pb->fc = 0.0f;
    pb->f30 = 0.0f;
    pb->f34 = 0.0f;
    pb->f38 = 0.0f;
    pb->f3c = 0.0f;
    pb->f40 = TCameraCtrl__data_805D8FAC;
    pb->f44 = TCameraCtrl__data_805D8FD8;
    TCameraCtrl__sub_80068358(pb, pa, TCameraCtrl__data_805D8FAC, 0.0f);
    ((C_8006A35C *)TCameraCtrl__up_vector)->f0 = 0.0f;
    pc = (C_8006A35C *)TCameraCtrl__up_vector;
    pc->f4 = TCameraCtrl__data_805D8FAC;
    pc->f8 = 0.0f;
    camera_view_state_flag = 0;
    camera_ctrl_view_state_byte = -1;
    TCameraCtrl__data_805D4E0A = 0;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void reset__11TCameraCtrlFv(void) {
    TCameraCtrl__data_805D4E0A = 0;
    TCameraCtrl__sub_80068354();
    *(s8 *)((s8 *)TCameraCtrl__view_state + 0) = 0;
    *(s16 *)((s8 *)TCameraCtrl__view_state + 2) = 0;
    *(s32 *)((s8 *)TCameraCtrl__view_state + 4) = 0;
    *(s32 *)((s8 *)TCameraCtrl__view_state + 8) = 0;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::cycle_spectate_target() {
    void *pad;
    u8 *q;
    u8 *pl;
    s8 tries;
    u16 slot;
    s32 i;
    if (is_split_screen() != 0 || is_quest_active() != 0) {
        return;
    }
    pad = controller_input_state.unk70;
    if (is_on_current_screen__11TCameraCtrlFv(pad, 0x20000) == 0 ||
        TWindowShortListCtrl__check_controller_button(pad, 0x10) == 0 ||
        is_on_current_screen__11TCameraCtrlFv(pad, 0x10000) == 0 ||
        (pl = get_player_by_client_id(local_client_id)) == 0 ||
        (tries = 0, ((Sel_8006A13C *)TCameraCtrl__view_state)->busy != 0) ||
        get_current_floor_area() == AREA_DRAGON ||
        get_current_floor_area() == AREA_DE_ROL_LE ||
        get_current_floor_area() == AREA_VOL_OPT ||
        get_current_floor_area() == AREA_DARK_FALZ ||
        get_current_floor_area() == AREA_GAL_GRYPHON ||
        get_current_floor_area() == AREA_OLGA_FLOW ||
        get_current_floor_area() == AREA_BARBA_RAY ||
        get_current_floor_area() == AREA_GOL_DRAGON ||
        get_current_floor_area() == AREA_LOBBY ||
        get_current_floor_area() == AREA_PIONEER2_EP2 ||
        get_current_floor_area() == AREA_PIONEER2_EP1) {
        return;
    }
    slot = ((Sel_8006A13C *)TCameraCtrl__view_state)->slot;
    while (tries <= 3) {
        slot++;
        tries++;
        if (slot >= 4) {
            slot = 0;
        }
        q = get_player_by_client_id(slot);
        if (q != 0) {
            if (((TObjPlayer *)q)->get_floor() == ((TObjPlayer *)pl)->get_floor() && obj_testFlags30__14TObjCollidableFUl((u32)q, 0x02000000) == 0) {
                ((Sel_8006A13C *)TCameraCtrl__view_state)->slot = slot;
                reset_cameras_to_actor((void *)q, 0);
                for (i = 0; i < 4; i++) {
                    u8 *p = get_player_by_client_id(i);
                    if (p != 0) {
                        ((TObjPlayer *)p)->refresh_equipment_slot();
                    }
                }
                return;
            }
        }
    }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::set_shake_preset(s32 arg0) {
    void *p;
    if ((void *) camera_ctrl_instance != NULL) {
        switch (arg0) {
        case 0:
            *(s32 *)((s8 *)camera_ctrl_instance + 0x1C0) = 0x14;
            p = camera_ctrl_instance;
            *(f32 *)((s8 *)p + 0x1C4) = (f32) lbl_805D8FE8;
            start_pad_rumble_all(0x60, 0x14);
            return;
        case 1:
            *(s32 *)((s8 *)camera_ctrl_instance + 0x1C0) = 0x1E;
            p = camera_ctrl_instance;
            *(f32 *)((s8 *)p + 0x1C4) = (f32) lbl_805D8FEC;
            start_pad_rumble_all(0xA0, 0x1E);
            return;
        case 2:
            *(s32 *)((s8 *)camera_ctrl_instance + 0x1C0) = 0x1E;
            p = camera_ctrl_instance;
            *(f32 *)((s8 *)p + 0x1C4) = (f32) lbl_805D8FF0;
            start_pad_rumble_all(0xE0, 0x1E);
            break;
        }
    }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl__sub_8006A044(s32 id, f32 v) {
    O_8006A044 *p;
    if ((*(O_8006A044 * *)&camera_ctrl_instance) != 0) {
        (*(O_8006A044 * *)&camera_ctrl_instance)->v = v;
        p = (*(O_8006A044 * *)&camera_ctrl_instance);
        p->id = id;
        start_pad_rumble_all(0x60, id);
    }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void *TCameraCtrl::get_params() { return &m_20; }
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::reset_view_flags() {
    Cam_80069F20 *c = ((Cam_80069F20 *)&TCameraCtrl__view_state);
    f32 v;
    c->flags &= ~0x20;
    c->flags &= ~0x80;
    c->flags &= ~0x800;
    if (c->flags & 2) {
        c->flags &= ~2;
        c->flags |= 0x100;
    } else if (c->flags & 0x100) {
        c->flags |= 0x80;
        c->flags &= ~0x100;
    }
    if (c->flags & 0x40) {
        c->flags &= ~0x40;
    }
    if (c->flags & 0x100) {
        return;
    }
    if (c->flags & 0x80) {
        return;
    }
    if (camera_ctrl_instance == 0) {
        return;
    }
    v = 0.0f;
    ((Out_80069F20 *)camera_ctrl_instance)->f20 = 0;
    ((Out_80069F20 *)camera_ctrl_instance)->f24 = 0;
    ((Out_80069F20 *)camera_ctrl_instance)->f28 = 0;
    ((Out_80069F20 *)camera_ctrl_instance)->f2c = v;
    ((Out_80069F20 *)camera_ctrl_instance)->f30 = v;
    ((Out_80069F20 *)camera_ctrl_instance)->f34 = 0;
    ((Out_80069F20 *)camera_ctrl_instance)->f64 = 0;
    ((Out_80069F20 *)camera_ctrl_instance)->f38 = v;
    ((Out_80069F20 *)camera_ctrl_instance)->f3c = v;
    ((Out_80069F20 *)camera_ctrl_instance)->f40 = v;
    ((Out_80069F20 *)camera_ctrl_instance)->f44 = v;
    ((Out_80069F20 *)camera_ctrl_instance)->f48 = v;
    ((Out_80069F20 *)camera_ctrl_instance)->f4c = v;
    ((Out_80069F20 *)camera_ctrl_instance)->f50 = v;
    ((Out_80069F20 *)camera_ctrl_instance)->f54 = v;
    ((Out_80069F20 *)camera_ctrl_instance)->f58 = v;
    ((Out_80069F20 *)camera_ctrl_instance)->f5c = v;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
s32 activate_camera_mode(s32 arg0) {
  u8 *temp_r3;
  short new_var;
  if ((*((s32 *) (((s8 *) (&(*(RecoveredGlobal_80069E7C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + 8))) & 4)
  {
    return 0;
  }
  *((s32 *) (((s8 *) (&(*(RecoveredGlobal_80069E7C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + 8)) = *((s32 *) (((s8 *) (&(*(RecoveredGlobal_80069E7C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + 8));
  new_var = 8;
  *((s32 *) (((s8 *) (&(*(RecoveredGlobal_80069E7C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + new_var)) = (*((s32 *) (((s8 *) (&(*(RecoveredGlobal_80069E7C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + new_var))) | 4;
  if (arg0 == (*((u8 *) (((s8 *) (&(*(RecoveredGlobal_80069E7C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + 0))))
  {
    *((u8 *) (((s8 *) (&(*(RecoveredGlobal_80069E7C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + 0)) = arg0;
  }
  else
  {
    if (((*((u8 *) (((s8 *) (&(*(RecoveredGlobal_80069E7C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + 0))) != 5) && ((*((u8 *) (((s8 *) (&(*(RecoveredGlobal_80069E7C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + 0))) != 9))
    {
      *((u8 *) (((s8 *) (&(*(RecoveredGlobal_80069E7C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + 1)) = *((u8 *) (((s8 *) (&(*(RecoveredGlobal_80069E7C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + 0));
    }
    *((u8 *) (((s8 *) (&(*(RecoveredGlobal_80069E7C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value)) + 0)) = arg0;
  }
  temp_r3 = (u8 *)camera_controller_registry[TCameraCtrl__view_state[0]];
  if (temp_r3 != 0)
  {
    (((VObj_18_f8ef8c *)(temp_r3))->m5());
  }
  return 1;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
s32 restore_player_cameras(void) {
    s32 identity;
    u8 *player;
    if (*(u32 *)((s8 *)&TCameraCtrl__view_state + 8) & 4) {
        *(u32 *)((s8 *)&TCameraCtrl__view_state + 8) &= ~4;
        if (TCameraCtrl__sub_8006A5DC() == 5 && camera_controller_registry[5] != NULL && TCameraCtrl__saved_projection_angle != 0) {
            *(s32 *)((u8 *)camera_controller_registry[5] + 0x54) = TCameraCtrl__saved_projection_angle;
        }
        *(u32 *)((s8 *)&TCameraCtrl__view_state + 8) |= 0x20;
    }
    if (is_split_screen() != 0) {
        for (identity = 0; identity < 4; identity++) {
            player = get_player_by_client_id(identity);
            if (player != NULL) {
                reset_cameras_to_actor(player, 0);
            }
        }
    } else {
        player = get_player_by_client_id(local_client_id);
        if (player != NULL) {
            reset_cameras_to_actor(player, 0);
        }
    }
    return 0;
}
#pragma pop


#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma dont_inline off
#pragma auto_inline off
s32 TCameraCtrl::release_photon_blast_camera() {
    s32 temp_r0;
    if (*(s32 *)((s8 *)(&(*(RecoveredGlobal_80069D7C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value) + 8) & 8) {
        temp_r0 = *(s32 *)((s8 *)(&(*(RecoveredGlobal_80069D7C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value) + 8) & 0xFFFFFFF7;
        *(s32 *)((s8 *)(&(*(RecoveredGlobal_80069D7C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value) + 8) = temp_r0;
        *(s32 *)((s8 *)(&(*(RecoveredGlobal_80069D7C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value) + 8) = (s32) (temp_r0 | 0x20);
    }
    return 0;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void set_active_camera_pose_from_params(u8 *arg0) {
    u8 *temp_r4;
    if ((*(s32 *)((s8 *)(&(*(RecoveredGlobal_80069D04_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value) + 8) & 8) || (*(s32 *)((s8 *)(&(*(RecoveredGlobal_80069D04_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value) + 8) & 4)) {
        temp_r4 = (u8 *)camera_controller_registry[TCameraCtrl__view_state[0]];
        if (temp_r4 != NULL) {
            *(f32 *)((s8 *)temp_r4 + 0x3C) = (f32) *(f32 *)((s8 *)arg0 + 0x1C);
            *(f32 *)((s8 *)temp_r4 + 0x40) = (f32) *(f32 *)((s8 *)arg0 + 0x20);
            *(f32 *)((s8 *)temp_r4 + 0x44) = (f32) *(f32 *)((s8 *)arg0 + 0x24);
            *(f32 *)((s8 *)temp_r4 + 0x48) = (f32) *(f32 *)((s8 *)arg0 + 0x28);
            *(f32 *)((s8 *)temp_r4 + 0x4C) = (f32) *(f32 *)((s8 *)arg0 + 0x2C);
            *(f32 *)((s8 *)temp_r4 + 0x50) = (f32) *(f32 *)((s8 *)arg0 + 0x30);
            *(s32 *)((s8 *)temp_r4 + 0x54) = (s32) *(s32 *)((s8 *)arg0 + 0x14);
        }
    }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void set_active_camera_pose(u8 *arg0, u8 *arg1) {
    u8 *temp_r5;
    if ((*(s32 *)((s8 *)(&(*(RecoveredGlobal_80069C94_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value) + 8) & 8) || (*(s32 *)((s8 *)(&(*(RecoveredGlobal_80069C94_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value) + 8) & 4)) {
        temp_r5 = (u8 *)camera_controller_registry[TCameraCtrl__view_state[0]];
        if (temp_r5 != NULL) {
            *(f32 *)((s8 *)temp_r5 + 0x3C) = (f32) *(f32 *)((s8 *)arg0 + 0);
            *(f32 *)((s8 *)temp_r5 + 0x40) = (f32) *(f32 *)((s8 *)arg0 + 4);
            *(f32 *)((s8 *)temp_r5 + 0x44) = (f32) *(f32 *)((s8 *)arg0 + 8);
            *(f32 *)((s8 *)temp_r5 + 0x48) = (f32) *(f32 *)((s8 *)arg1 + 0);
            *(f32 *)((s8 *)temp_r5 + 0x4C) = (f32) *(f32 *)((s8 *)arg1 + 4);
            *(f32 *)((s8 *)temp_r5 + 0x50) = (f32) *(f32 *)((s8 *)arg1 + 8);
        }
    }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::update_pose_smoothing() {
    u8 *arg0 = (u8 *)this;
  u8 *new_var;
  u8 *temp_r30;
  u8 *current;
  u8 *temp_r31;
  if ((*(s32 *)&TCameraCtrl__pose_snap_flags) & 1)
  {
    update_position();
    TCameraCtrl__sub_800689E8();
    return;
  }
  if (is_split_screen() != 0)
  {
    temp_r30 = (u8 *) (arg0 + (TCameraCtrl::get_camera_no() * 0xC));
    new_var = (temp_r30 + 0xD4);
    temp_r31 = new_var;
    approach_camera_vector((void *) temp_r31, (u8 *)&this->unk_1A0, (f32) (*((f32 *) (((s8 *) arg0) + 0x1B8))));
    VecCopy(&this->position, (const Vec *)temp_r31);
    current = (temp_r30 + 0x104);
    approach_camera_vector((void *) current, (u8 *)&this->m_1ac, this->m_1bc);
    VecCopy((Vec *)(arg0 + 0x184), (const Vec *)current);
    return;
  }
  approach_camera_vector(&this->position, (u8 *)&this->unk_1A0, (f32) (*((f32 *) (((s8 *) arg0) + 0x1B8))));
  approach_camera_vector((u8 *)&this->m_184, (u8 *)&this->m_1ac, this->m_1bc);
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::update_position() {
    u8 *arg0 = (u8 *)this;
    u8 *temp_r3;
    this->position.x = (f32) *(f32 *)&this->unk_1A0;
    this->position.y = (f32) this->m_1a4;
    this->position.z = (f32) *(f32 *)&this->unk_1A8;
    this->m_184 = (f32) this->m_1ac;
    *(f32 *)&this->unk_188 = (f32) *(f32 *)&this->unk_1B0;
    this->m_18c = (f32) this->m_1b4;
    this->m_1c8 = (f32) this->position.x;
    *(f32 *)&this->unk_1CC = (f32) this->position.y;
    this->m_1d0 = (f32) this->position.z;
    if (is_split_screen() != 0) {
        temp_r3 = arg0 + (TCameraCtrl::get_camera_no() * 0xC);
        *(f32 *)((s8 *)temp_r3 + 0x134) = (f32) this->position.x;
        *(f32 *)((s8 *)temp_r3 + 0x138) = (f32) this->position.y;
        *(f32 *)((s8 *)temp_r3 + 0x13C) = (f32) this->position.z;
    }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::update_target_smoothing() {
    u8 *arg0 = (u8 *)this;
    u8 *temp_r3;
    u8 *temp_r3_2;
    this->position.x = (f32) *(f32 *)&this->unk_1A0;
    this->position.y = (f32) this->m_1a4;
    this->position.z = (f32) *(f32 *)&this->unk_1A8;
    this->m_1c8 = (f32) this->position.x;
    *(f32 *)&this->unk_1CC = (f32) this->position.y;
    this->m_1d0 = (f32) this->position.z;
    if (is_split_screen() != 0) {
        temp_r3 = arg0 + (TCameraCtrl::get_camera_no() * 0xC);
        *(f32 *)((s8 *)temp_r3 + 0x134) = (f32) this->position.x;
        *(f32 *)((s8 *)temp_r3 + 0x138) = (f32) this->position.y;
        *(f32 *)((s8 *)temp_r3 + 0x13C) = (f32) this->position.z;
    }
    temp_r3_2 = (u8 *)camera_controller_registry[TCameraCtrl__view_state[0]];
    if ((temp_r3_2 != NULL) && !(*(s32 *)((s8 *)temp_r3_2 + 0x38) & 0x10)) {
        *(f32 *)&this->unk_188 = (f32) *(f32 *)&this->unk_1B0;
    }
    approach_camera_vector((u8 *)&this->m_184, (u8 *)&this->m_1ac, this->m_1bc);
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::clamp_to_target_obstruction() {
    View_800698C8 *self = (View_800698C8 *)this;
    s32 n;
    Hit_800698C8 *hit;
    s32 *flag;
    n = TCameraCtrl::get_camera_no();
    if (is_split_screen() != 0) {
        flag = &self->split_flags[n];
    } else {
        flag = &self->flag;
    }
    if (*flag == 0) {
        return;
    }
    if (is_split_screen() != 0) {
        hit = (Hit_800698C8 *)csnVector(&self->split_tgt[n], &self->split_pos[n], 0x901);
    } else {
        hit = (Hit_800698C8 *)csnVector(&self->tgt, &self->pos, 0x901);
    }
    if (hit == NULL) {
        return;
    }
    if (is_split_screen() != 0) {
        self->split_pos[n].x = hit->point->x;
        self->split_pos[n].y = hit->point->y;
        self->split_pos[n].z = hit->point->z;
        VecCopy((Vec *)&self->pos, (const Vec *)&self->split_pos[n]);
    } else {
        self->pos.x = hit->point->x;
        self->pos.y = hit->point->y;
        self->pos.z = hit->point->z;
    }
    if (is_split_screen() != 0) {
        self->split_look[n].x = self->split_pos[n].x + hit->point[1].x;
        self->split_look[n].y = self->split_pos[n].y + hit->point[1].y;
        self->split_look[n].z = self->split_pos[n].z + hit->point[1].z;
    } else {
        self->look.x = self->pos.x + hit->point[1].x;
        self->look.y = self->pos.y + hit->point[1].y;
        self->look.z = self->pos.z + hit->point[1].z;
    }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::resolve_anchor_obstruction() {
    View_800696D0 *self = (View_800696D0 *)this;
    Vec_800696D0 d;
    s32 n;
    s32 *flag;
    Hit_800696D0 *hit;
    if (is_split_screen() != 0) {
        n = TCameraCtrl::get_camera_no();
        flag = &self->split_flags[n];
        hit = (Hit_800696D0 *)csnVector(&self->split_look[n], &self->eye, 0x901);
    } else {
        hit = (Hit_800696D0 *)csnVector(&self->look, &self->eye, 0x901);
        flag = &self->flag;
    }
    if (hit != NULL) {
        if (is_split_screen() != 0) {
            n = TCameraCtrl::get_camera_no();
            d.x = self->eye.x - self->split_look[n].x;
            d.y = self->eye.y - self->split_look[n].y;
            d.z = self->eye.z - self->split_look[n].z;
        } else {
            d.x = self->eye.x - self->look.x;
            d.y = self->eye.y - self->look.y;
            d.z = self->eye.z - self->look.z;
        }
        if (0.0f != vector_length(&d)) {
            normalize_vector(&d);
        }
        if (is_split_screen() != 0) {
            n = TCameraCtrl::get_camera_no();
            self->split_look[n].x = hit->point->x - d.x;
            self->split_look[n].y = hit->point->y - d.y;
            self->split_look[n].z = hit->point->z - d.z;
        } else {
            self->look.x = hit->point->x - d.x;
            self->look.y = hit->point->y - d.y;
            self->look.z = hit->point->z - d.z;
        }
        *flag = 1;
    } else {
        if (is_split_screen() != 0) {
            n = TCameraCtrl::get_camera_no();
            VecCopy((Vec *)&self->split_look[n], (const Vec *)&self->split_pos[n]);
        } else {
            VecCopy((Vec *)&self->look, (const Vec *)&self->pos);
        }
        *flag = 0;
    }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void*TCameraCtrl::get_target() { return (char*)this + 0x68; }
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void CameraViewParams::apply() {
    *(s32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value) + 8) = (s32) (*(s32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value) + 8) | 0x200);
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 *)&TCameraCtrl__data_804FF634).value) + 0x28) = (f32) width;
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 *)&TCameraCtrl__data_804FF634).value) + 0x2C) = (f32) height;
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 *)&TCameraCtrl__data_804FF634).value) + 8) = (f32) center_x;
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 *)&TCameraCtrl__data_804FF634).value) + 0xC) = (f32) center_y;
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 *)&TCameraCtrl__data_804FF634).value) + 0x18) = (f32) *(f32 *)((s8 *)&scene_projection_state.value + 0x50);
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 *)&TCameraCtrl__data_804FF634).value) + 0x1C) = (f32) *(f32 *)((s8 *)&scene_projection_state.value + 0x4C);
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 *)&TCameraCtrl__data_804FF634).value) + 0x20) = (f32) TCameraCtrl__data_805D8FAC;
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 *)&TCameraCtrl__data_804FF634).value) + 0x24) = (f32) (TCameraCtrl__data_805D8FAC / *(f32 *)((s8 *)&scene_projection_state.value + 0x4C));
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 *)&TCameraCtrl__data_804FF634).value) + 0) = (f32) (*(f32 *)((s8 *)&scene_projection_state.value + 0x4C) * *(f32 *)((s8 *)&scene_projection_state.value + 0x50));
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 *)&TCameraCtrl__data_804FF634).value) + 4) = (f32) -(TCameraCtrl__data_805D8FAC * *(f32 *)((s8 *)&scene_projection_state.value + 0x50));
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 *)&TCameraCtrl__data_804FF634).value) + 0x30) = (f32) pad_30[0];
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 *)&TCameraCtrl__data_804FF634).value) + 0x34) = (f32) pad_30[1];
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 *)&TCameraCtrl__data_804FF634).value) + 0x38) = (f32) pad_30[2];
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 *)&TCameraCtrl__data_804FF634).value) + 0x3C) = (f32) pad_30[3];
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 *)&TCameraCtrl__data_804FF634).value) + 0x40) = (f32) pad_30[4];
    *(f32 *)((s8 *)(&(*(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 *)&TCameraCtrl__data_804FF634).value) + 0x44) = (f32) pad_30[5];
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void CameraViewParams::apply_if_overridden() {
    if (*(s32 *)((s8 *)&TCameraCtrl__view_state[0] + 8) & 0x400) {
        apply();
    }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
s32 CameraViewParams::begin_override() {
    if ((*(G_800695A0 *)&TCameraCtrl__view_state).flags & 0x400) {
        return 0;
    }
    (*(G_800695A0 *)&TCameraCtrl__view_state).flags |= 0x400;
    apply();
    return 1;
}
#pragma pop


#pragma push
#pragma opt_common_subs off
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::reset_viewport_scissor() {
    typedef char sp8_offset[(offsetof(Stack_80069534, sp8) == 0x0) ? 1 : -1];
    typedef char spC_offset[(offsetof(Stack_80069534, spC) == 0x4) ? 1 : -1];
    typedef char sp10_offset[(offsetof(Stack_80069534, sp10) == 0x8) ? 1 : -1];
    typedef char sp14_offset[(offsetof(Stack_80069534, sp14) == 0xC) ? 1 : -1];
    Stack_80069534 stack;
    stack.sp8 = *(s32 *)((s8 *)&camera_ctrl_scissor_default_vec.value + 0);
    stack.spC = *(s32 *)((s8 *)&camera_ctrl_scissor_default_vec.value + 4);
    stack.sp10 = *(s32 *)((s8 *)&camera_ctrl_scissor_default_vec.value + 8);
    stack.sp14 = *(s32 *)((s8 *)&camera_ctrl_scissor_default_vec.value + 0xC);
    if (*(s32 *)((s8 *)(&(*(RecoveredGlobal_80069534_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value) + 8) & 0x200) {
        *(s32 *)((s8 *)(&(*(RecoveredGlobal_80069534_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value) + 8) = (s32) (*(s32 *)((s8 *)(&(*(RecoveredGlobal_80069534_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value) + 8) & 0xFFFFFDFF);
    }
    set_viewport_scissor__11TCameraCtrlFiPv(0, (void *)&stack.sp8);
}
#pragma pop


#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma dont_inline off
#pragma auto_inline off
void end_view_override() {
    typedef char sp8_offset[(offsetof(Stack_800694A8, sp8) == 0x0) ? 1 : -1];
    typedef char sp10_offset[(offsetof(Stack_800694A8, sp10) == 0x8) ? 1 : -1];
    typedef char sp14_offset[(offsetof(Stack_800694A8, sp14) == 0xC) ? 1 : -1];
    typedef char sp30_offset[(offsetof(Stack_800694A8, sp30) == 0x28) ? 1 : -1];
    typedef char sp34_offset[(offsetof(Stack_800694A8, sp34) == 0x2C) ? 1 : -1];
    typedef char sp38_offset[(offsetof(Stack_800694A8, sp38) == 0x30) ? 1 : -1];
    typedef char sp3C_offset[(offsetof(Stack_800694A8, sp3C) == 0x34) ? 1 : -1];
    typedef char sp40_offset[(offsetof(Stack_800694A8, sp40) == 0x38) ? 1 : -1];
    typedef char sp44_offset[(offsetof(Stack_800694A8, sp44) == 0x3C) ? 1 : -1];
    typedef char sp48_offset[(offsetof(Stack_800694A8, sp48) == 0x40) ? 1 : -1];
    typedef char sp4C_offset[(offsetof(Stack_800694A8, sp4C) == 0x44) ? 1 : -1];
    Stack_800694A8 stack;
    if (*(s32 *)((s8 *)(&(*(RecoveredGlobal_800694A8_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value) + 8) & 0x400) {
        *(s32 *)((s8 *)(&(*(RecoveredGlobal_800694A8_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value) + 8) = (s32) (*(s32 *)((s8 *)(&(*(RecoveredGlobal_800694A8_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value) + 8) & 0xFFFFFBFF);
    }
    stack.sp10 = 320.0f;
    stack.sp14 = 240.0f;
    stack.sp30 = 640.0f;
    stack.sp34 = 480.0f;
    stack.sp38 = 0.0f;
    stack.sp3C = 0.0f;
    stack.sp40 = TCameraCtrl__data_805D8FD0;
    stack.sp44 = TCameraCtrl__data_805D8FD4;
    stack.sp48 = TCameraCtrl__data_805D8FAC;
    stack.sp4C = TCameraCtrl__data_805D8FD8;
    ((CameraViewParams *)&stack.sp8)->apply();
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::init_default_view() {
    typedef char sp8_offset[(offsetof(Stack_800693F4, sp8) == 0x0) ? 1 : -1];
    typedef char sp10_offset[(offsetof(Stack_800693F4, sp10) == 0x8) ? 1 : -1];
    typedef char sp14_offset[(offsetof(Stack_800693F4, sp14) == 0xC) ? 1 : -1];
    typedef char sp20_offset[(offsetof(Stack_800693F4, sp20) == 0x18) ? 1 : -1];
    typedef char sp30_offset[(offsetof(Stack_800693F4, sp30) == 0x28) ? 1 : -1];
    typedef char sp34_offset[(offsetof(Stack_800693F4, sp34) == 0x2C) ? 1 : -1];
    typedef char sp38_offset[(offsetof(Stack_800693F4, sp38) == 0x30) ? 1 : -1];
    typedef char sp3C_offset[(offsetof(Stack_800693F4, sp3C) == 0x34) ? 1 : -1];
    typedef char sp40_offset[(offsetof(Stack_800693F4, sp40) == 0x38) ? 1 : -1];
    typedef char sp44_offset[(offsetof(Stack_800693F4, sp44) == 0x3C) ? 1 : -1];
    typedef char sp48_offset[(offsetof(Stack_800693F4, sp48) == 0x40) ? 1 : -1];
    typedef char sp4C_offset[(offsetof(Stack_800693F4, sp4C) == 0x44) ? 1 : -1];
    Stack_800693F4 stack;
    TCameraCtrl__camera_mode = 0;
    TCameraCtrl::set_target_coords(0, 0);
    TCameraCtrl::set_target(0x280, 0x1E0);
    stack.sp10 = 320.0f;
    stack.sp14 = 240.0f;
    stack.sp30 = 640.0f;
    stack.sp34 = 480.0f;
    stack.sp20 = lbl_805D8FCC;
    stack.sp38 = 0.0f;
    stack.sp3C = 0.0f;
    stack.sp40 = TCameraCtrl__data_805D8FD0;
    stack.sp44 = TCameraCtrl__data_805D8FD4;
    stack.sp48 = TCameraCtrl__data_805D8FAC;
    stack.sp4C = TCameraCtrl__data_805D8FD8;
    ((CameraViewParams *)&stack.sp8)->apply();
    ((TCameraCtrl *)(&(*(RecoveredGlobal_800693F4_TCameraCtrl__data_804FF634 *)&TCameraCtrl__data_804FF634).value))->update_projection_params();
    camera_default_view_value = TCameraCtrl__data_805D8FAC;
    camera_default_view_value_b = TCameraCtrl__data_805D8FD8;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::reset_default_view() {
    typedef char sp8_offset[(offsetof(Stack_80069318, sp8) == 0x0) ? 1 : -1];
    typedef char sp10_offset[(offsetof(Stack_80069318, sp10) == 0x8) ? 1 : -1];
    typedef char sp14_offset[(offsetof(Stack_80069318, sp14) == 0xC) ? 1 : -1];
    typedef char sp20_offset[(offsetof(Stack_80069318, sp20) == 0x18) ? 1 : -1];
    typedef char sp30_offset[(offsetof(Stack_80069318, sp30) == 0x28) ? 1 : -1];
    typedef char sp34_offset[(offsetof(Stack_80069318, sp34) == 0x2C) ? 1 : -1];
    typedef char sp38_offset[(offsetof(Stack_80069318, sp38) == 0x30) ? 1 : -1];
    typedef char sp3C_offset[(offsetof(Stack_80069318, sp3C) == 0x34) ? 1 : -1];
    typedef char sp40_offset[(offsetof(Stack_80069318, sp40) == 0x38) ? 1 : -1];
    typedef char sp44_offset[(offsetof(Stack_80069318, sp44) == 0x3C) ? 1 : -1];
    Stack_80069318 stack;
    TCameraCtrl__camera_mode = 0;
    TCameraCtrl::set_target_coords(0, 0);
    TCameraCtrl::set_target(0x280, 0x1E0);
    TCameraCtrl::set_fullscreen_viewport();
    TCameraCtrl::reset_viewport_scissor();
    fn_803D64F8(&lbl_804FF5E8[0]);
    camera_renderer_setup_nop(&lbl_804FF5E8[0], 0x3555);
    TCameraCtrl::update_camera_state((f32) (0.0f), (f32) (0.0f), (f32) (0.0f));
    TCameraCtrl::look_at_position((f32) (0.0f), (f32) (0.0f), lbl_805D8FE4);
    stack.sp10 = 320.0f;
    stack.sp14 = 240.0f;
    stack.sp30 = 640.0f;
    stack.sp34 = 480.0f;
    stack.sp20 = lbl_805D8FCC;
    stack.sp38 = 0.0f;
    stack.sp3C = 0.0f;
    stack.sp40 = TCameraCtrl__data_805D8FD0;
    stack.sp44 = TCameraCtrl__data_805D8FD4;
    camera_default_view_value = TCameraCtrl__data_805D8FAC;
    camera_default_view_value_b = TCameraCtrl__data_805D8FD8;
    ((TCameraCtrl *)(&stack.sp8))->update_projection_params();
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
s32 TCameraCtrl__sub_80069304(void) {
    return ((u32) *(u32 *)((s8 *)(&(*(RecoveredGlobal_80069304_TCameraCtrl__data_804FF628 *)&TCameraCtrl__view_state).value) + 8) >> 0xAU) & 1;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::create() {
    void *obj = __nw__7TObjectFUl(0x1D4);
    if (obj != 0) {
        TCameraCtrl__ct((u8 *)obj, (void *)tl_camera);
    }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
s32 *TCameraCtrl::get_view_matrix() {
    if (is_split_screen() != 0) {
        if (get_mode__11TCameraCtrlFPv((void *) (&(*(RecoveredGlobal_80069258_main_task *)&(*(RecoveredGlobal_800691C8_main_task *)&main_task)).value)) & 1) {
            return (long *) ((u8 *)&(*(RecoveredGlobal_80069258_TCameraCtrl__data_804FF700 *)&TCameraCtrl__view_matrices).value + ((TCameraCtrl::get_instance() - 1) * 0x30));
        }
        return (long *) ((u8 *)&(*(RecoveredGlobal_80069258_TCameraCtrl__data_804FF700 *)&TCameraCtrl__view_matrices).value + (TCameraCtrl::get_camera_no() * 0x30));
    }
    return &(*(RecoveredGlobal_80069258_TCameraCtrl__data_804FF6D0 *)&TCameraCtrl__view_matrix).value;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::apply_split_screen_view_matrix() {
    if (is_split_screen() != 0) {
        if (get_mode__11TCameraCtrlFPv(&(*(RecoveredGlobal_800691C8_main_task *)&main_task).value) & 1) {
            TCameraCtrl::concat_matrix(0U, (u32) ((u8 *)&TCameraCtrl__view_matrices[0] + ((TCameraCtrl::get_instance() - 1) * 0x30)));
            return;
        }
        TCameraCtrl::concat_matrix(0U, (u32) ((u8 *)&TCameraCtrl__view_matrices[0] + (TCameraCtrl::get_camera_no() * 0x30)));
        return;
    }
    TCameraCtrl::concat_matrix(0U, (u32) &TCameraCtrl__view_matrix[0]);
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void transform_to_view__11TCameraCtrlFii(s32 arg0, s32 arg1) {
    push_matrix();
    if (is_split_screen() != 0) {
        TCameraCtrl::concat_matrix((u32)(0), (u32)((void *) ((u8 *)&(*(RecoveredGlobal_80069148_TCameraCtrl__data_804FF700 *)&TCameraCtrl__view_matrices).value + (TCameraCtrl::get_camera_no() * 0x30))));
    } else {
        TCameraCtrl::concat_matrix((u32)(0), (u32)((void *) (&(*(RecoveredGlobal_80069148_TCameraCtrl__data_804FF6D0 *)&TCameraCtrl__view_matrix).value)));
    }
    matrix_mult_vec(0, (void *)arg0, (void *)arg1);
    pop_matrix();
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
s32 TCameraCtrl::get_camera_target_id(s32 arg0) {
    s32 var_r31;
    s32 var_r3;
    u32 temp_r3;
    void *temp_r3_2;
    if (is_split_screen() != 0) {
        var_r31 = 0xFFFF;
        if (arg0 < 0) {
            var_r3 = arg0;
        } else {
            var_r3 = get_camera_mode__11TCameraCtrlFv();
        }
        if (var_r3 >= 4) {
            return 0xFFFF;
        }
        temp_r3_2 = camera_controller_registry[var_r3];
        if (temp_r3_2 != NULL) {
            var_r31 = TCameraCtrl__sub_8006B358(temp_r3_2);
        }
        return var_r31;
    }
    if ((void *) camera_ctrl_instance != NULL) {
        temp_r3 = *(u32 *)((s8 *)camera_ctrl_instance + 0x90);
        if (temp_r3 != 0U) {
            return get_entity_id((void *)temp_r3);
        }
    }
    return 0xFFFF;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::restore_full_screen_view() {
    if (is_split_screen() == 0) {
        ((TCameraCtrl *)((s32) &lbl_804FF67C[0]))->copy_view_state((s32)((s32) &TCameraCtrl__data_804FF634[0]));
        TCameraCtrl__sub_801E32D8(320.0f, 240.0f);
        GXSetScissorBoxOffset(0, 0);
        GXSetScissor(0, 0, 0x280, 0x1E0);
        TCameraCtrl__data_805D4E0A = 0;
    }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::copy_view_state(s32 src) {
    s32 dst = (s32)this;
    *(O_80068FCC *)dst = *(O_80068FCC *)src;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl__sub_80068EF0(void) {
    f32 neg_w;
    f32 neg_h;
    if (is_split_screen() == 0) {
        ((TCameraCtrl *)((s32) &TCameraCtrl__data_804FF634[0]))->copy_view_state((s32)((s32) &lbl_804FF67C[0]));
        neg_w = -(*(f32 *)((s8 *)&TCameraCtrl__data_804FF634[0] + 8) - 320.0f);
        neg_h = -(*(f32 *)((s8 *)&TCameraCtrl__data_804FF634[0] + 0xC) - 240.0f);
        if (0.0f == neg_w && 0.0f == neg_h) {
            TCameraCtrl__data_805D4E0A = 0;
        } else {
            TCameraCtrl__data_805D4E0A = 1;
        }
        GXSetScissorBoxOffset((s32) neg_w, (s32) neg_h);
        TCameraCtrl__sub_801E32D8(*(f32 *)((s8 *)&TCameraCtrl__data_804FF634[0] + 8), *(f32 *)((s8 *)&TCameraCtrl__data_804FF634[0] + 0xC));
        if ((void *) camera_ctrl_instance != NULL) {
            set_perspective_projection_from_fov((s32) ((TCameraCtrl *) camera_ctrl_instance)->m_19c, TCameraCtrl__data_805D8FDC, TCameraCtrl__data_805D8FAC, TCameraCtrl__data_805D8FE0);
        }
    }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
f32 TCameraCtrl::get_view_scale() {
    if (is_split_screen() != 0) {
        if (TCameraCtrl::get_camera_id() == 2) {
            return TCameraCtrl__data_805D8FAC;
        }
        return lbl_805D8FC8;
    }
    return TCameraCtrl__data_805D8FAC;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
f32 TCameraCtrl::get_fov() {
    if (is_split_screen() != 0) {
        if (TCameraCtrl::get_camera_id() == 2) {
            return TCameraCtrl__data_805D8FAC;
        }
        return lbl_805D8FC8;
    }
    return TCameraCtrl__data_805D8FAC;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::set_split_viewport(s32 arg0, s32 i) {
    switch (arg0) {
    case 1:
        TCameraCtrl::set_fullscreen_viewport();
        break;
    case 2:
        TCameraCtrl::set_target_coords(0, 0);
        TCameraCtrl::set_target(0x280, 0xF0);
        GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, TCameraCtrl__data_805D8FAC);
        if (i == 0) {
            GXSetScissor(0, 0x6A, 0x280, 0xF0);
            GXSetScissorBoxOffset(0, 0x6A);
        } else {
            GXSetScissor(0, 0x74, 0x280, 0xF0);
            GXSetScissorBoxOffset(0, -0x7C);
        }
        break;
    case 3:
        if (i != 2) {
            quad_80068B34(i);
        } else {
            TCameraCtrl::set_target_coords(0xA0, 0xF0);
            TCameraCtrl::set_target(0x140, 0xF0);
        }
        viewport_80068B34();
        break;
    case 4:
        quad_80068B34(i);
        viewport_80068B34();
        break;
    default:
        TCameraCtrl::set_fullscreen_viewport();
        break;
    }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::set_fullscreen_viewport() {
    TCameraCtrl::set_target_coords(0, 0);
    TCameraCtrl::set_target(0x280, 0x1E0);
    GXSetViewport((f32) TCameraCtrl__viewport_x, (f32) TCameraCtrl__viewport_y, (f32) TCameraCtrl__viewport_size, (f32) TCameraCtrl__viewport_height, (f32) (0.0f), (f32) (TCameraCtrl__data_805D8FAC));
    GXSetScissor((int) ((s32) TCameraCtrl__viewport_x), (int) ((s32) TCameraCtrl__viewport_y), (int) ((s32) TCameraCtrl__viewport_size), (int) ((s32) TCameraCtrl__viewport_height));
    GXSetScissorBoxOffset(0, 0);
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
f32 TCameraCtrl::get_split_offset(s32 arg0) {
    if ((is_split_screen() != 0) && (TCameraCtrl::get_camera_id() == 2)) {
        if (arg0 == 0) {
            return 106.0f;
        }
        return 116.0f;
    }
    return 0.0f;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
f32 TCameraCtrl__sub_80068A04(void) {
    return 0.0f;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
bool TCameraCtrl__sub_800689F4(void) {
    return TCameraCtrl__data_805D4E0A != 0;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl__sub_800689E8(void) { TCameraCtrl__pose_snap_flags = 0; }
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
u16 TCameraCtrl::get_nth_view_player_id(s32 n) {
    s32 count = 0;
    u16 result = 0;
    Cam_80068958 *cam;
    s32 i;
    s32 v;
    if (is_split_screen() == 0) {
        return local_client_id;
    }
    cam = (Cam_80068958 *)get_character_select_request_buffer();
    for (i = 0; i < 4; i++) {
        v = cam->ids[i];
        if (v >= 0 && v != 0xFFFF) {
            if (count == n) {
                result = v;
            }
            count++;
        }
    }
    return result;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
s32 TCameraCtrl::get_split_screen_view_index(u16 id) {
    s32 result = 0;
    s32 n = 0;
    struct Cam_800688D0 *cam;
    s32 i;
    if (is_split_screen() == 0) {
        return 0;
    }
    cam = (struct Cam_800688D0 *) get_character_select_request_buffer();
    for (i = 0; i < 4; i++) {
        if (cam->slots[i] == id) {
            result = n;
        }
        if (cam->slots[i] >= 0) {
            n++;
        }
    }
    return result;
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::sync_split_view_slots(s32 arg0, s32 arg1) {
    s32 i;
    s32 id;
    if ((*(Cam_80068810 * *)&camera_ctrl_instance) != NULL) {
        id = (u16)TCameraCtrl::get_nth_view_player_id(arg0);
        if (id != 0xFFFF) {
            (*(Cam_80068810 * *)&camera_ctrl_instance)->slots[id] = (*(Cam_80068810 * *)&camera_ctrl_instance)->f194;
            VecCopy((Vec *)(&(*(Cam_80068810 * *)&camera_ctrl_instance)->vecs[id]), (const Vec *)(&(*(Cam_80068810 * *)&camera_ctrl_instance)->v178));
        }
    }
    if (arg1 != 0) {
        for (i = 0; i < 4; i++) {
            (*(Cam_80068810 * *)&camera_ctrl_instance)->slots[i] = (*(Cam_80068810 * *)&camera_ctrl_instance)->f194;
            VecCopy((Vec *)(&(*(Cam_80068810 * *)&camera_ctrl_instance)->vecs[i]), (const Vec *)(&(*(Cam_80068810 * *)&camera_ctrl_instance)->v178));
        }
    }
}
#pragma pop


#pragma push
#pragma dont_inline off
#pragma auto_inline off
void TCameraCtrl::copy_vec_to_default(u8 *arg0) {
    VecCopy((Vec *)(&TCameraCtrl__up_vector[0]), (const Vec *)(arg0));
}
#pragma pop


// The shared scale is the second small-data object, following the initial zero.
// Its explicit section also keeps GC/1.3.2 from selecting mutable .sdata.
__declspec(section ".sdata2") const f32 TCameraCtrl__data_805D8FAC = 1.0f;
