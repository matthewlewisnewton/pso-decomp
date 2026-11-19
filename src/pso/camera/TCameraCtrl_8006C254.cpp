#include "pso/system/ResourceFile.h"
#include "types.h"
#include "pso/player/TObjPlayer_800666B0.h"
#include "pso/unk/TUnk_80488B68.h"
#include "pso/camera/TCameraCtrl_80067FC0.h"
#include "pso/camera/TCameraCtrl_8006C254.h"
#include "pso/unk/TUnk_80488B38.h"

#include "pso/unk/TUnk_80488B08.h"
#include "pso/system/vector.h"
#include "pso/camera/TCameraCtrl.h"
#include "pso/camera/CameraHelpers.h"
#include <stddef.h>
#include "pso/camera/TCameraCtrl_8006C580.h"
#include "pso/system/memory.h"
#include "pso/unk/TUnk_80488D70.h"
#include "pso/system/scene/TScene.h"
#include "pso/map/FloorArea.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/system/MatrixStack.h"


#pragma push
#pragma fp_contract on
#pragma pop


extern void* camera_controller_registry[];
void* camera_controller_registry[];

struct CameraMotionData;
extern "C" {

void *TCameraCtrl__vt5(void);

}

s32 TCameraCtrl__saved_projection_angle;
s32 scripted_camera_projection_angle;

#pragma push
#pragma opt_common_subs off
#pragma pop

void *TCameraCtrl__vt5(void) {
    void *o = (void *)new TUnk_80488B68();
    return o;
}

#pragma push
#pragma fp_contract on
struct Stack_8006C28C {
    void *ptrs[4];
    Vec p;
    Vec v;
    s32 sp54;
    Vec sp58;
    u8 out[0x2C];
};

void sample_camera_motion(u8 *arg0, s32 arg1, u8 *arg2, f32 farg0);
extern "C" {
f32 vec_squared_length(u8 *arg0);
void normalize_vector(Vec *);
s32 push_matrix_from(void *src);
void rotate_matrix_y(int, s32);
void matrix_mult_vec(int, Vec *, Vec *);
}
s32 pop_matrices(s32 arg0);
extern u8 identity_matrix[];

void TUnk_80488B68::run_task() {
    Stack_8006C28C st;
    Vec tmp;
    Vec p2;
    Vec v2;
    st.ptrs[0] = &st.p;
    st.ptrs[1] = &st.v;
    st.ptrs[2] = &st.sp54;
    st.ptrs[3] = &st.sp58;
    sample_camera_motion((u8 *)st.out, (s32)motion_data, (u8 *)st.ptrs, (f32)((f32)playback.frame));
    projection_angle = scripted_camera_projection_angle;
    set_camera_capture_overlay_alpha(0x8F);
    if (mode->flags & 4) {
        if (mode->flags & 0x80) {
            projection_angle = 0x36C1;
            tmp.x = st.v.x;
            tmp.y = 0.0f;
            tmp.z = st.v.z;
            f32 m = vec_squared_length((u8 *)&tmp);
            if (m) {
                normalize_vector(&tmp);
            }
            position.x = -(4e+01f * tmp.x - st.p.x);
            position.y = st.p.y;
            position.z = -(4e+01f * tmp.z - st.p.z);
            target.x = st.v.x + st.p.x;
            target.y = st.v.y + st.p.y;
            target.z = st.v.z + st.p.z;
        } else {
            position.x = st.p.x;
            position.y = st.p.y;
            position.z = st.p.z;
            target.x = st.v.x + position.x;
            target.y = st.v.y + position.y;
            target.z = st.v.z + position.z;
        }
    } else {
        p2.x = st.p.x;
        p2.y = st.p.y;
        p2.z = st.p.z;
        v2.x = st.v.x;
        v2.y = st.v.y;
        v2.z = st.v.z;
        if (vec_squared_length((u8 *)&v2) != 0.0f) {
            normalize_vector(&v2);
        }
        push_matrix_from(identity_matrix);
        rotate_matrix_y(0, angles.yaw);
        matrix_mult_vec(0, &p2, &p2);
        matrix_mult_vec(0, &v2, &v2);
        pop_matrices(1);
        position.x = p2.x + position_origin.x;
        position.y = p2.y + position_origin.y;
        position.z = p2.z + position_origin.z;
        target.x = v2.x + position.x;
        target.y = v2.y + position.y;
        target.z = v2.z + position.z;
    }
    playback.frame += playback.frame_step;
    if (playback.frame > (motion_data->frames - 1) || playback.frame >= 5e+03f) {
        if (mode->flags & 0x20) {
            playback.frame = 0.0f;
            return;
        }
        playback.frame = (motion_data->frames - 1);
        playback.flags |= 1;
    }
}
#pragma pop


TUnk_80488B68::~TUnk_80488B68() {

}

extern "C" {

s32 load_relocatable_file(s32 arg0, s32 arg1);

}
TUnk_80488B68::TUnk_80488B68() : TUnk_80488A28() {
    this->m_38 = 0;
    scripted_camera_projection_angle = 0;
    TCameraCtrl__saved_projection_angle = 0;
    playback.index = 0;
    playback.bank = 0;
    playback.flags = 0;
    playback.frame = 0.0f;
    playback.frame_step = 0.0f;
    position_origin.x = 0.0f;
    position_origin.y = 0.0f;
    position_origin.z = 0.0f;
    target_origin.x = 0.0f;
    target_origin.y = 0.0f;
    target_origin.z = 0.0f;
    angles.pitch = 0;
    angles.yaw = 0;
    angles.roll = 0;
    motion_data = NULL;
    mode = NULL;
}

void TCameraCtrl::free_entries() {
    s32 i;
    for (i = 0; i < 8; i++) {
        if (TCameraCtrl__camera_banks.e[i].p != 0) {
            xfree(TCameraCtrl__camera_banks.e[i].p);
            TCameraCtrl__camera_banks.e[i].p = 0;
        }
    }
}

void TCameraCtrl::load_camera_banks() {
    u32 j;
    Bank_8006C6CC *b;
    u32 n;
    u32 k;
    s32 i;
    s32 sz;
    for (i = 0; i < 8; i++) {
        TCameraCtrl__camera_banks.e[i].p = 0;
    }
    b = &camera_path_bank_table[get_current_floor_area()];
    if (b->entries == 0) {
        return;
    }
    n = b->count;
    if (n >= 8) {
        return;
    }
    for (j = 0; j < n; j++) {
        sz = get_resource_file_size((const char *)(b->entries[j].filename));
        if (sz <= -1) {
            return;
        }
        TCameraCtrl__camera_banks.e[j].p = xmalloc(sz);
    }
    for (k = 0; k < n; k++) {
        TCameraCtrl__camera_banks.e[k].directory = (CameraMotionDirectory *)load_relocatable_file((s32)b->entries[k].filename, (s32)TCameraCtrl__camera_banks.e[k].p);
    }
}

G_8006C668 TCameraCtrl__camera_banks;