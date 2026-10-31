#include "pso/enemy/TUnk_804909C4.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/map/CsnQuery.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/system/NinjaUtil.h"
#include "pso/system/vector.h"
#include "pso/TParticleCtrl.h"

extern "C" {
void check_enemy_body_collisions(TObjCollidable *);
s32 TObjPlayer__sub_800A3210(s32, s32, s32);
void vec3_add_to(Vec *, const Vec *);
f32 atan2_float(f32, f32);
void *spawn_particle_effect_with_rotation(void *, void *, s32, int);
extern TObject *tl_04;
extern f32 player_scale_factor;
}

CollisionBody projectile_collision_body = {{0.0f, 0.0f, 0.0f}, 0.0f, 0.0f, 0, 0x8003, {0.0f, 0.0f, 0.0f}, 0.0f};

s32 TUnk_804909C4::check_player_hits(s32 id) {
    TObjCollidable *other;
    s32 result = 0;
    s32 i;
    TObjChara *p;
    other = ((TObjCollidable *(*)(s32))find_entity_by_id)(id);
    if (other == NULL) {
        return 0;
    }
    other->bodies->flags &= ~1;
    TObjPlayer::init_all_slots();
    check_object_collisions();
    check_enemy_body_collisions(this);
    other->bodies->flags |= 1;
    if (bodies->flags & 0x180000) {
        for (i = 0; i < 16; i++) {
            p = (TObjChara *)TObjPlayer::get_battle_param(i);
            if (p == NULL) {
                break;
            }
            if (((s32 (*)(u8 *))obj_is_hit_receivable)((u8 *)p) != 0 && p != other) {
                DirectAttackPayload t = {0, 0.0f};
                t.power = ((s32 (*)(s32))TObjPlayer__sub_800A3210)(3);
                DirectAttackPayload u = t;
                p->receive_direct_attack(other, u, 0, -1, -1);
                p->apply_knockback_from_attacker((u8 *)other, 3.0f);
                result = 1;
            }
        }
    }
    return result;
}

void TUnk_804909C4::run_task() {
    VecCopy(&prev_position, &position);
    vec3_add_to(&position, &velocity);
    if (effect != NULL) {
        effect->set_position(&position);
    }
    if (check_player_hits(owner_id) != 0) {
        queue_destruction();
        return;
    }
    s32 remaining = lifetime - 1;
    lifetime = remaining;
    if (remaining <= 0) {
        queue_destruction();
    }
}

TUnk_804909C4::~TUnk_804909C4() {
    free_collision_body_parts(this);
    if (effect != NULL) {
        effect->queue_destruction();
    }
}

TUnk_804909C4::TUnk_804909C4(u8 *owner, const Vec *start, const Vec *target) : TObjCollidable(tl_04) {
    s32 var_r0;
    CsnHit *hit;
    init_collision_body_parts(this, &projectile_collision_body, 1);
    bodies->radius = 0.75f * player_scale_factor;
    owner_id = get_entity_id((TObjBase *)owner);
    if (((TObjPlayer *)owner)->is_flag_set_388_bit26() != 0) {
        var_r0 = 0xDA;
    } else {
        var_r0 = 0xD5;
    }
    effect_id = var_r0;
    room = ((TObjPlayer *)owner)->room;
    VecCopy(&position, start);
    VecCopy(&velocity, target);
    subtract_vector(&velocity, start);
    velocity.y = 0.0f;
    vec_set_length(&velocity, player_scale_factor);
    effect_rotation[0] = 0;
    effect_rotation[1] = (s32)(10430.38043493439 * atan2_float(velocity.x, velocity.z)) + 0x4000;
    effect_rotation[2] = 0x4000;
    effect = (TParticleCtrl *)spawn_particle_effect_with_rotation(&position, effect_rotation, effect_id, 0x42);
    {
        Vec end = velocity;
        vec_set_length(&end, 500.0f);
        vec3_add_to(&end, &position);
        hit = csnVector(&position, &end, -1);
    }
    if (hit != NULL) {
        lifetime = (s32)(vec_xz_distance(&position, &hit->contact->point) / player_scale_factor);
    } else {
        lifetime = (s32)(500.0f / player_scale_factor);
    }
}
