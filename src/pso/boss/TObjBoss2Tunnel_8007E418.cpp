#include "types.h"
#include "pso/map/CsnQuery.h"
#include "pso/boss/TObjBoss2Tunnel_8007E418.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/system/vector.h"
#include "pso/boss/TObjBoss2Tunnel.h"
#include "pso/misc/TCameraCtrl.h"

extern "C" {
f32 sin_table_lookup(s32);
f32 cos_table_lookup(s32);
s32 get_view_matrix__11TCameraCtrlFv();
s32 matrix_mult_vec(s32, s32, s32);
s32 push_matrix();
extern const f32 TObjBoss2Tunnel__data_805D9234;
s32 angle_diff_s16(s32, s32);
s32 approach_angle_limited(s32, s32, s32);
int vec3_add_to(void*, void*);

s32 TObjBoss2Tunnel::decrement_packed_timer(u32 *arg0, s32 arg1) {
    u32 temp_r5;

    temp_r5 = *arg0;
    if ((s32)((temp_r5 >> 24) - arg1) < 0) {
        *arg0 = temp_r5 & 0xFFFFFF;
        return 1;
    }
    *arg0 = ((((temp_r5 >> 24) - arg1) << 24) & 0xFF000000) | (temp_r5 & 0xFFFFFF);
    return 0;
}

extern f32 TObjBoss2Tunnel__data_805D9210;

s32 adjust_point_to_ground_with_normal(const Vec *source, Vec *destination, Vec *normal) {
    CsnHit *hit;

    VecCopy(destination, source);
    destination->y += TObjBoss2Tunnel__data_805D9210;
    hit = csnVecterUnder(destination, 0x16EF);
    if (hit != NULL) {
        VecCopy(destination, &hit->contact->point);
        VecCopy(normal, &hit->contact->normal);
        return 1;
    }
    VecCopy(destination, source);
    return 0;
}

s32 adjust_point_to_ground(const Vec *source, Vec *destination) {
    CsnHit *hit;

    VecCopy(destination, source);
    destination->y += TObjBoss2Tunnel__data_805D9210;
    hit = csnVecterUnder(destination, 0x16EF);
    if (hit != NULL) {
        VecCopy(destination, &hit->contact->point);
        return 1;
    }
    VecCopy(destination, source);
    return 0;
}

void TObjBoss2Tunnel::init_zako(void* a1, s32 _w2) { rotate_xz_pair_by_angle((f32 *)this, (f32 *)((char*)this + 0x8), (s32)_w2); vec3_add_to(this, a1); }

s16 TObjBoss2Tunnel::turn_toward_angle_limited(s32 arg0, s32 cur, s32 target, s32 step, s32 limit) {
    target = angle_diff_s16(arg0, target);
    if (target > limit) {
        target = limit;
    } else if (target < -limit) {
        target = -limit;
    }
    if (cur * target >= 0) {
        cur = approach_angle_limited(cur, target, step);
    } else if (cur * angle_diff_s16(cur, target) >= 0) {
        if (cur >= 0) {
            cur = cur - step;
        } else {
            cur = cur + step;
        }
    } else {
        cur = approach_angle_limited(cur, target, step);
    }
    return cur;
}

s32 count_active_segments__15TObjBoss2TunnelFPv(void *arg0) {
    s32 temp_r3;
    s32 var_r31;

    var_r31 = 0;
    do {
        temp_r3 = *(s32 *)((s8 *)arg0 + 0);
        if (!(temp_r3 & 8)) {
            var_r31 += 1;
        }
        if (!(temp_r3 & 0x10)) {
            var_r31 += count_active_segments__15TObjBoss2TunnelFPv((void *)(*(void **)((s8 *)arg0 + 0x2C)));
        }
        arg0 = *(void **)((s8 *)arg0 + 0x30);
    } while (arg0 != NULL);
    return var_r31;
}

extern f32 TObjBoss2Tunnel__data_805D926C;

s32 TObjBoss2Tunnel::count_tree_nodes() {
    s32 var_r31;
    u8 *temp_r3;
    u8 *temp_r3_2;
    var_r31 = 1;
    temp_r3 = (u8 *)this->m_2c;
    if (temp_r3 != NULL) {
        var_r31 = ((TObjBoss2Tunnel *)temp_r3)->count_tree_nodes() + 1;
    }
    temp_r3_2 = (u8 *)this->m_30;
    if (temp_r3_2 != NULL) {
        var_r31 += ((TObjBoss2Tunnel *)temp_r3_2)->count_tree_nodes();
    }
    return var_r31;
}

f32 TObjBoss2Tunnel::calc_scaled_value(s32 arg0, f32 farg0) {
    return (TObjBoss2Tunnel__data_805D926C * farg0) / sin_table_lookup(arg0 / 2);
}
#pragma push
#pragma fp_contract on
void rotate_vec_xz(void *arg0, void *arg1, s32 arg2) {
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f31;
    f32 temp_f3;
    temp_f31 = cos_table_lookup(arg2);
    temp_f1 = sin_table_lookup(arg2);
    temp_f0 = *(f32 *)((s8 *)arg0 + 0);
    temp_f3 = *(f32 *)((s8 *)arg0 + 8);
    *(f32 *)((s8 *)arg1 + 8) = (f32) ((temp_f31 * temp_f3) - (temp_f1 * temp_f0));
    *(f32 *)((s8 *)arg1 + 0) = (f32) ((temp_f1 * temp_f3) + (temp_f31 * temp_f0));
}
#pragma pop

#pragma push
#pragma fp_contract on
void rotate_xz_pair_by_angle(f32 *arg0, f32 *arg1, s32 arg2) {
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f31;
    f32 temp_f3;
    temp_f31 = cos_table_lookup(arg2);
    temp_f1 = sin_table_lookup(arg2);
    temp_f0 = *arg0;
    temp_f3 = *arg1;
    *arg1 = (temp_f31 * temp_f3) - (temp_f1 * temp_f0);
    *arg0 = (temp_f1 * temp_f3) + (temp_f31 * temp_f0);
}
#pragma pop

#pragma push
#pragma fp_contract on
bool is_vec_xz_cross_negative(u8 *arg0, u8 *arg1) {
    return (((*(f32 *)((s8 *)arg0 + 8) * *(f32 *)((s8 *)arg1 + 0)) - (*(f32 *)((s8 *)arg0 + 0) * *(f32 *)((s8 *)arg1 + 8))) >= TObjBoss2Tunnel__data_805D9234) == 0;
}
#pragma pop

#pragma push
#pragma fp_contract on
void TObjBoss2Tunnel::transform_vec_by_camera(s32 arg0, s32 arg1, s32 arg2) {
    push_matrix();
    TCameraCtrl::concat_matrix(0, get_view_matrix__11TCameraCtrlFv());
    matrix_mult_vec(0, arg1, arg2);
    pop_matrix();
}
#pragma pop

}
