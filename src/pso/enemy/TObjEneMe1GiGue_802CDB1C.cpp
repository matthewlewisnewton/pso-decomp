#include "pso/unk/text_800870BC.h"
#include "pso/misc/ParticleFactory.h"
#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/enemy/TUnk_804E14E8.h"
#include "pso/enemy/TObjEneMe1GiGue.h"
#include "pso/TParticleCtrl.h"
#include "pso/map/FloorArea.h"
#include "pso/map/CsnQuery.h"
#include "pso/system/SoundEffect.h"
#include "pso/system/vector.h"
#include "pso/system/NinjaUtil.h"

extern "C" {
f32 atan2_float(f32 y, f32 x);
void *find_entity_by_id(u16);
void *find_active_entity_by_id(u16);
void matrix_mult_vec(s32, Vec *, Vec *);
void rotate_matrix_y(s32, s32);
void rotate_matrix_x(s32, s32);
void push_matrix_from(void *);
void pop_matrix();
void vec3_add_to(void *, void *);
void subtract_vector(void *, void *);
extern Vec lbl_804722A8;
extern const f64 lbl_804722C8[];
extern Mtx34 identity_matrix;
extern TObject *tl_04;
extern f32 lbl_805D6844;
extern f32 lbl_805D6848;
extern const f32 lbl_805DE6C0;
extern const f32 lbl_805DE6C4;
extern const f32 lbl_805DE6C8;
extern DirectAttackPayload lbl_804722B4[];
extern s32 local_client_id;
extern const f32 lbl_805D684C;
extern s32 lbl_805D6854;
}

#pragma push
#pragma opt_common_subs off
void TUnk_804E14E8::run_task() {
    TObjEneMe1GiGue *source;
    TObjChara *target;
    Vec direction;
    source = (TObjEneMe1GiGue *)find_entity_by_id(source_id);
    if (source == NULL) {
        queue_destruction();
        return;
    }
    target = (TObjChara *)find_active_entity_by_id(target_id);
    switch (state) {
    case 0:
        timer--;
        if (timer <= 0) {
            timer = 0;
            VecCopy(&projectile_position, origin);
            state = 1;
            if (get_current_floor_area() == AREA_TOWER) {
                play_sound_effect(0x4003A313, &projectile_position, 0, 0);
                return;
            }
            play_sound_effect(0x3A820, &projectile_position, 0, 0);
            return;
        }
        if (particle0 != NULL) {
            particle0->enable();
        }
        if (particle1 != NULL) {
            particle1->enable();
        }
        return;
    case 1:
        timer++;
        if (timer >= 0x5A) {
            queue_destruction();
            return;
        }
        if (target != NULL) {
            VecCopy(&direction, (const Vec *)&target->body_center_position);
            subtract_vector(&direction, &projectile_position);
            vec_set_length(&direction, homing_acceleration);
            homing_acceleration += lbl_805D684C;
            vec3_add_to(&velocity, &direction);
            vec_set_length(&velocity, lbl_805D6844);
        }
        VecCopy(&previous_projectile_position, &projectile_position);
        vec3_add_to(&projectile_position, &velocity);
        if (particle0 != NULL) {
            ((TParticleCtrl *)particle0)->set_position(&projectile_position);
        }
        if (particle1 != NULL) {
            ((TParticleCtrl *)particle1)->set_position(&projectile_position);
        }
        if (csnVector(&previous_projectile_position, &projectile_position, -1) != 0) {
            queue_destruction();
            return;
        }
        if (target != NULL && !(target->actorFlags & 0x04000A00) &&
            xyz_distance_squared(&projectile_position, (Vec *)&target->body_center_position) <= lbl_805D6844 * lbl_805D6844) {
            DirectAttackPayload h = lbl_804722B4[0];
            h.power = (f32)lbl_805D6854;
            {
                DirectAttackPayload h1 = h;
                target->receive_direct_attack(source, h1, NULL, -1, -1);
            }
            if (special_attack == 1) {
                h.kind = 0x12;
                DirectAttackPayload h2 = h;
                target->receive_direct_attack(source, h2, NULL, -1, -1);
            }
            spawn_particle_effect(&target->body_center_position, 0x8E);
            if (local_client_id == target_id) {
                source->apply_hit_shake((u32)target);
            }
            queue_destruction();
        }
        break;
    }
}
#pragma pop

TUnk_804E14E8::~TUnk_804E14E8() {
    if (particle0 != NULL) {
        particle0->queue_destruction();
        particle0 = NULL;
    }
    if (particle1 != NULL) {
        particle1->queue_destruction();
        particle1 = NULL;
    }
}

TUnk_804E14E8::TUnk_804E14E8(Vec *start, u16 target, GiGueProjectileAngles *angles,
                             s32 delay, s32 attack, u16 source)
    : TObjCollidable(tl_04) {
    target_id = target;
    source_id = source;
    special_attack = attack;
    origin = start;
    m_e8 = lbl_805DE6C0;
    push_matrix_from(identity_matrix);
    {
        Vec direction = lbl_804722A8;
        direction.z = lbl_805D6844;
        rotate_matrix_y(0, angles->y);
        rotate_matrix_x(0, angles->x);
        matrix_mult_vec(0, &direction, &velocity);
    }
    pop_matrix();
    timer = delay;
    Vec *target_position = (Vec *)&((TObjChara *)find_entity_by_id(target))->body_center_position;
    {
        GiGueProjectileAngles particle_angles;
        particle_angles.x = 0;
        particle_angles.y = (s32)(lbl_804722C8[0] * atan2_float(target_position->x - start->x, target_position->z - start->z)) + 0x4000;
        particle_angles.z = 0x4000 - (s32)(lbl_804722C8[0] * atan2_float(target_position->y - start->y, vec_xz_distance(target_position, start)));
        particle0 = (TParticleCtrl *)spawn_particle_effect_with_rotation(start, &particle_angles, 0x201, 2);
        particle1 = (TParticleCtrl *)spawn_particle_effect_with_rotation(start, &particle_angles, 0x202, 2);
    }
    homing_acceleration = lbl_805D6848;
    if (xz_distance_squared(target_position, start) < lbl_805DE6C4) {
        homing_acceleration *= lbl_805DE6C8;
    }
    state = 0;
}
