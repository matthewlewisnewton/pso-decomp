#include "types.h"
#include "pso/boss/TBoss3VoloptHiraisin.h"
#include "pso/object/obj_band.h"
#include "pso/system/vector.h"
#include "pso/enemy/TObjEneRe2Flower_EffCurse3.h"
#include "pso/object/TObjMotion.h"
#include "pso/player/TObjEneRe2Flower_Bomb.h"
#include "pso/enemy/TUnk_80493450.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/enemy/TObjEneBeast.h"
#include "pso/enemy/TObjEnemyCustom.h"
#include "pso/player/TObjPlayer.h"
#include "pso/boss/TObjBoss2Tunnel.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/misc/TNowLoading.h"

struct Sub350_800C57F0 { char pad[8]; void *p8; };
struct Ctl_800C5B10 { u8 pad[8]; void *field_8; };

extern "C" {
s32 check_path_obstructed(void *, void *);
f32 get_collision_body_radius(void *, s32);
s32 pop_matrix();
s32 enemy_wander_home__9TObjEnemyFlfff(void *, int, f32, f32, f32);
f32 fabs_float(f32);
f64 atan2_float(f32, f32);
f32 horizontal_distance_squared(void *, void *);
s32 approach_angle_limited(int, int, int);
s32 project_actor_to_ground(void *, void *, int);
s32 minimap_render_dot(void *, int, int, int);
s32 vec3_add_to(void *, void *);
s32 rotate_vector_by_matrix(int, void *, void *);
s32 rotate_matrix_y(int, int);
s32 subtract_vector(void *, void *);
s32 push_matrix_from(void *);
s32 pop_matrices(int);
extern const f64 lbl_8043BC88;
extern Vec lbl_8050BEE0;
extern Vec lbl_8050BF00;
extern u8 identity_matrix[];

s32 apply_actor_gravity(void *, int, f32);
}
void move_with_wall_slide(u8 *arg0);
extern "C" {
s32 obj_testFlags30__14TObjCollidableFUl(void *, int);
void *spawn_particle_effect(void *pos, s32 id);
s32 advance_animation_playback(TObjMotion *);
extern const f32 lbl_805DA034;
extern const f32 lbl_805DA038;
extern const f32 lbl_805DA03C;
extern const f32 lbl_805DA040;
int unlink_enemy_group_relations__13TUnk_80493450Fv(void*);
int send_entity_set_flags__9TObjEnemyFv(void*);
s32 obj_setFlags30(void *, s32);
    extern const float lbl_805DA058;
    extern const float lbl_805DA05C;
    extern const float lbl_805DA060;
    extern const float lbl_805DA064;
s32 update_movement_status__9TObjCharaFv(void *);
s32 submit_cursor_candidate(void *, int);
extern const f32 lbl_805DA048;
s32 update_action_hold_status__9TObjCharaFv(void *);
u16 get_entity_id(void *);
int queue_destruction__7TObjectFv(void*);
f32 random_ratio__9TObjCharaFv(s32 arg0);
s32 enemy_move_toward(void *, s32, void *, int, f32);
s32 test_elt_flag__13TUnk_80493450Fll(void *, int, int);
extern const f32 lbl_805DA044;
extern const f32 lbl_805DA054;
extern const f32 lbl_805DA028;
extern const f32 lbl_805DA02C;
extern const f32 lbl_805DA030;
s32 enemy_turn_toward_dest(void *, s32);
s32 get_current_floor(void);
u8 *get_enemy_entity(u16 arg0);
TObjPlayer *get_player_by_client_id(s32 i);
extern const f32 lbl_805DA04C;
extern const f32 lbl_805DA050;
f32 enemy_backstep_from_point(void *, void *, f32);
s32 turn_toward_direction__9TObjCharaFlP3Vec(void *, void *, void *);
s32 angle_difference_abs(s32, s32);
void TUnk_80493450::sub_800C4E08() {
    if (obj_testFlags30(0x100000) != 0) {
        this->unk_394 = (f32) this->unk_39C;
        this->m_c8 = (f32) this->unk_3A4;
        return;
    }
    this->unk_394 = (f32) this->m_398;
    this->m_c8 = (f32) this->m_3a0;
}

s32 TUnk_80493450::update_target_near_flag() {
    f32 temp_f31;
    u8 *temp_r0;
    u8 *temp_r31;
    temp_r0 = this->target;
    if (temp_r0 == NULL) {
        obj_clearFlags30(0x100000);
        return;
    }
    if ((get_entity_id(temp_r0) < 0x1000U) && (this->is_actor_cadence_frame(0x1E) != 0)) {
        temp_r31 = this->target;
        temp_f31 = horizontal_distance_squared(temp_r31 + 0x38, (void *) ((u8 *)this + 0x38));
        switch (((TObjPlayer *)temp_r31)->class_flags & CLASS_FLAG_TYPE_MASK) {
        case CLASS_FLAG_HUNTER:
            if (obj_testFlags30(0x100000) != 0) {
                if (lbl_805DA028 < temp_f31) {
                    obj_clearFlags30(0x100000);
                }
            } else if (temp_f31 < lbl_805DA02C) {
                obj_setFlags30(this, 0x100000);
            }
            break;
        default:
            if (obj_testFlags30(0x100000) != 0) {
                if (lbl_805DA030 < temp_f31) {
                    obj_clearFlags30(0x100000);
                }
            } else if (temp_f31 < lbl_805DA028) {
                obj_setFlags30(this, 0x100000);
            }
            break;
        }
    } else {
        obj_setFlags30(this, 0x100000);
    }
}

int TUnk_80493450::beast_retire_corpse() { return queue_destruction__7TObjectFv(this); }
void TUnk_80493450::beast_update_dead() {
    u8 *arg0 = (u8 *)this;
    advance_animation_playback(this);
    if (objInBand((GameObj *)(arg0), lbl_805DA034) != 0) {
        this->vfunc_98();
    }
    if (objInBand((GameObj *)(arg0), lbl_805DA038) != 0) {
        spawn_particle_effect(((u8 *)&this->position), 0xF3);
        this->vfunc_94();
    }
    if (this->m_c0 < (lbl_805DA03C * (lbl_805DA040 * this->m_c8))) {
        move_with_wall_slide((arg0));
        x_speed = (f32) (x_speed * lbl_805DA03C);
        this->m_310 = (f32) (this->m_310 * lbl_805DA03C);
    } else if (obj_testFlags30(0x800000) == 0) {
        apply_actor_gravity(arg0, 0, lbl_805DA034);
    }
    this->unk_380 = (f32) (this->unk_380 - this->m_384);
    if (this->unk_380 <= this->unk_388) {
        this->beast_retire_corpse();
    }
}
void TUnk_80493450::vfunc_63() { if (this->mode != 8) { this->mode = 8; this->m_b8 = 8; unlink_enemy_group_relations(); clear_player_status_flag((s32)((void*)0), (u32)((void*)1)); ((TObjPlayer *)this)->refresh_lobby_state(); send_entity_set_flags(); } }
void TUnk_80493450::beast_update_hurt() {
    u8 *arg0 = (u8 *)this;
    Vec v;

    advance_animation_playback(this);
    VecCopy((Vec *)&v, (const Vec *)&m_2fc);
    lbl_8050BEE0.x = lbl_8050BEE0.y = lbl_805DA034;
    lbl_8050BEE0.z = get_collision_body_radius(this, 0);
    ((void (*)(void *, void *))push_matrix_from)(identity_matrix, &lbl_8050BEE0);
    rotate_matrix_y(0, -rotation_y);
    rotate_vector_by_matrix(0, &lbl_8050BEE0, &lbl_8050BEE0);
    pop_matrix();
    vec3_add_to(&v, &lbl_8050BEE0);
    v.x += x_speed;
    v.z += m_310;
    if (check_path_obstructed(this, &v) == 0) {
        move_with_wall_slide(arg0);
        x_speed *= lbl_805DA03C;
        m_310 *= lbl_805DA03C;
    } else {
        x_speed = m_310 = lbl_805DA034;
    }
    ((TObjCollidable *)this)->update_collisions();
    if (objInBand((GameObj *)this, (f32)lbl_805DA034) != 0) {
        this->vfunc_97();
    }
    if (m_b4 != 8) {
        obj_clearFlags30(0x600);
        clear_player_status_flag((s32)((void *)0), (u32)((void *)0x04000000));
        if ((s32)subtype == 0) {
            if ((f32)hp < (f32)hpmax * parameters[0]) {
                obj_clearFlags30(0x1000);
                m_374 = (s16)(lbl_805DA044 * (lbl_805DA048 + parameters[0]));
            }
        }
        referenceHp = hp;
    }
    minimap_render_dot(&position, -0x5DB4, 1, 0);
}
void TUnk_80493450::vfunc_62() {
    if ((s16) this->mode != 7) {
        this->mode = 7;
        this->m_b8 = 6;
    }
    obj_clearFlags30(0x240000);
}
void TUnk_80493450::vfunc_89() {  }
void TUnk_80493450::vfunc_61() { obj_clearFlags30(256); }

void TUnk_80493450::beast_update_attack() {
    if (targetId < 0x1000) {
        TObjPlayer *player = get_player_by_client_id(targetId);
        if (player != NULL && player->get_field_3e4() == get_current_floor()) {
            target = (u8 *)player;
        } else {
            target = NULL;
        }
    } else if (targetId < 0x4000) {
        target = get_enemy_entity(targetId);
    } else {
        target = NULL;
    }
    advance_animation_playback(this);
    switch (phase) {
    case 0:
        phase = 1;
    case 1:
        if (objInBand((GameObj *)this, lbl_805DA04C) != 0) {
            if (target != NULL && ((TObjChara *)target)->select_melee_contact_body(this, lbl_805DA048) != 0) {
                ((TObjChara *)target)->receive_physical_attack(this, lbl_805DA048);
                ((TObjChara *)target)->apply_knockback_from_attacker((u8 *)this, lbl_805DA050);
            }
            vfunc_96();
        }
        vfunc_93();
        if (m_b4 != 4) {
            phase = 2;
            m_b8 = 0;
            timer = 0xF;
        }
        break;
    case 2:
        timer--;
        if (timer < 0) {
            obj_clearFlags30(0x200000);
            timer = 0;
            vfunc_100();
        }
        break;
    }
    apply_actor_gravity(this, 0, lbl_805DA034);
    enemy_turn_toward_dest(this, ((s32 *)movementParameters)[2]);
    ((TObjCollidable *)this)->update_collisions();
    minimap_render_dot(&position, -0x5DB4, 1, 0);
}

void TUnk_80493450::vfunc_60() {
    switch (this->mode) {
    case 0:
        break;
    case 1:
        this->phase = 0;
        if (this->children == NULL) {
            this->mode = 3;
            this->m_b8 = 7;
        } else {
            this->mode = 2;
            this->m_b8 = 10;
        }
        obj_clearFlags30(0x04040000);
        clear_player_status_flag((s32)((void *)0), (u32)((void *)0x0A000000));
        break;
    case 2:
        break;
    default:
        this->mode = 5;
        this->phase = 1;
        if (lbl_805DA03C < random_ratio()) {
            this->m_b8 = 3;
        } else {
            this->m_b8 = 4;
        }
        obj_setFlags30(this, 0x200000);
        obj_clearFlags30(0x04040000);
        clear_player_status_flag((s32)((void *)0), (u32)((void *)0x0A000000));
        break;
    }
}

s32 TUnk_80493450::update_movement_status() {
    if (TObjChara::update_movement_status() != 0) {
        switch (mode) {
        case 0:
            m_390 = 0;
            mode = 1;
            phase = 0;
            m_b8 = 0;
            obj_clearFlags30(0x04040000);
            clear_player_status_flag(0, 0x0A000000);
            break;
        }
        return 1;
    }
    return 0;
}

s32 TUnk_80493450::update_action_hold_status() {
    if (TObjChara::update_action_hold_status() != 0) {
        switch (mode) {
        case 0:
            m_390 = 0;
            mode = 1;
            phase = 0;
            m_b8 = 0;
            obj_clearFlags30(0x04040000);
            clear_player_status_flag(0, 0x0A000000);
            break;
        }
        return 1;
    }
    return 0;
}

void TUnk_80493450::beast_update_group_chase() {
    f32 d;
    f32 r;
    advance_animation_playback(this);
    switch (phase) {
    case 0:
        phase = 1;
        vfunc_99();
        break;
    }
    if (target != NULL) {
        Vec v = *(Vec *)&((TObjChara *)target)->m_2fc;
        d = enemy_backstep_from_point(this, &v, m_398);
        turn_toward_direction__9TObjCharaFlP3Vec(this, ((Sub350_800C57F0 *)movementParameters)->p8, &x_speed);
        r = m_398 + bodies->radius;
        if (d < r * r) {
            mode = 3;
            phase = 0;
            obj_clearFlags30(0x1000);
            m_374 = 0;
        }
    }
    ((TObjCollidable *)this)->update_collisions();
    minimap_render_dot(&position, -0x5DB4, 1, 0);
}

void TUnk_80493450::beast_update_approach() {
    u8 *arg0 = (u8 *)this;
    Vec sp14;
    f32 r;
    switch (this->phase) {
    case 0:
        apply_actor_gravity(arg0, 0, lbl_805DA034);
        advance_animation_playback(this);
        if (objInBand((GameObj *)arg0, (f32)lbl_805DA034) != 0) {
            this->vfunc_95();
        }
        if (this->m_b4 != 0x20U) {
            this->phase = 1;
            this->m_b8 = 2;
        }
        break;
    default:
        if (this->target != NULL) {
            if (test_elt_flag(0, 0x300000) != 0) {
                if (this->m_38c++ < lbl_805DA054) {
                    VecCopy((Vec *)&sp14, &this->home_position);
                } else {
                    VecCopy((Vec *)&sp14, (const Vec *)&((TObjChara *)this->target)->m_2fc);
                }
            } else {
                this->m_38c = 0U;
                VecCopy((Vec *)&sp14, (const Vec *)&((TObjChara *)this->target)->m_2fc);
            }
            update_target_near_flag();
            sub_800C4E08();
            advance_animation_playback(this);
            {
                Vec sp8 = sp14;
                enemy_move_toward(arg0, ((EnemyMoveParams *)movementParameters)->turn_speed, &sp8, 0, this->unk_394);
            }
            if (this->targetId == 0xFFFF) {
                if (horizontal_distance_squared((u8 *)&this->m_29c, (u8 *)&this->position) < (r = this->unk_394 + this->bodies->radius) * r ||
                    lbl_805DA044 < (f32) (*(s32 *)&this->m_2ac)++) {
                    this->target = NULL;
                    this->m_2ac = 0;
                }
            }
        }
        break;
    }
    ((TObjCollidable *)arg0)->update_collisions();
    minimap_render_dot((u8 *)&this->position, -0x5DB4, 1, 0);
    ((TObjBase *)arg0)->obj_clearFlags30(0x200000);
}

void TUnk_80493450::update_turn_toward_target() {
    TUnk_80493450 *arg0 = this;
    s32 ang;
    advance_animation_playback(this);
    switch (arg0->phase) {
    case 0:
        if (objInBand((GameObj *)arg0, (f32)lbl_805DA034) != 0) {
            arg0->vfunc_95();
        }
        if (arg0->m_b4 != 0x20) {
            arg0->phase = 1;
            arg0->m_b8 = 2;
        }
        break;
    case 1:
        if (arg0->target != NULL && arg0->is_actor_cadence_frame(0x1E) != 0) {
            Vec d;
            VecCopy((Vec *)&d, (const Vec *)&((TObjChara *)arg0->target)->m_2fc);
            subtract_vector(&d, &arg0->m_2fc);
            ang = turn_toward_direction__9TObjCharaFlP3Vec(arg0, ((Ctl_800C5B10 *)arg0->movementParameters)->field_8, &d);
            if (d.x * d.x + d.z * d.z < lbl_805DA030 || arg0->children == 0) {
                arg0->mode = 3;
                arg0->phase = 1;
                arg0->m_b8 = 2;
            } else if (ang <= ((TObjPlayer *)(arg0->m_318))->get_field_0c()) {
                arg0->phase = 2;
                arg0->m_b8 = 0;
            }
        }
        break;
    case 2:
        if (arg0->target != NULL && arg0->is_actor_cadence_frame(0x1E) != 0) {
            Vec d;
            VecCopy((Vec *)&d, (const Vec *)&((TObjChara *)arg0->target)->m_2fc);
            subtract_vector(&d, &arg0->m_2fc);
            ang = angle_difference_abs(arg0->rotation_y, (s32)(lbl_8043BC88 * atan2_float(d.x, d.z)));
            if (d.x * d.x + d.z * d.z < lbl_805DA030 || arg0->children == 0) {
                arg0->mode = 3;
                arg0->phase = 1;
                arg0->m_b8 = 2;
            } else if (((TObjPlayer *)(arg0->m_318))->get_field_0c() < ang) {
                arg0->phase = 1;
                arg0->m_b8 = 2;
            }
        }
        break;
    }
    apply_actor_gravity(arg0, 0, lbl_805DA034);
    ((TObjCollidable *)arg0)->update_collisions();
    minimap_render_dot(&arg0->position, -0x5DB4, 1, 0);
}

void TUnk_80493450::vfunc_59() {
    u8 *arg0 = (u8 *)this;
    if (obj_testFlags30(0x1000) != 0) {
        this->mode = 4;
    }
    switch (this->mode) {
    case 1:
        this->phase = 0;
        if ((u32) this->children == 0U) {
            this->mode = 3;
            this->m_b8 = 7;
        } else {
            this->mode = 2;
            this->m_b8 = 0xA;
        }
        ((TObjBase *)arg0)->obj_clearFlags30(0x04040000);
        ((TObjCollidable *)arg0)->clear_player_status_flag((s32)((void*)(0)), (u32)((void*)(0x0A000000U)));
        break;
    case 2:
    case 3:
        break;
    case 4:
        this->m_b8 = 5;
        break;
    default:
        this->mode = 3;
        this->phase = 1;
        this->m_b8 = 2;
        ((TObjBase *)arg0)->obj_clearFlags30(0x04040000);
        ((TObjCollidable *)arg0)->clear_player_status_flag((s32)((void*)(0)), (u32)((void*)(0x0A000000U)));
        break;
    }
}

void TUnk_80493450::beast_idle_update() {
    u8 *arg0 = (u8 *)this;
    f32 r;
    f32 dist;
    f32 range;
    s32 diff;
    s32 angle;
    s32 angle2;
    TUnk_80493450 *other;

    ((TUnk_80493450 *)arg0)->update_target_near_flag();
    ((TUnk_80493450 *)arg0)->sub_800C4E08();
    advance_animation_playback(this);
    if (this->phase != 1) {
        this->phase = 1;
        ((TUnk_80493450 *)arg0)->link_into_group_chain();
        *(s32 *)&this->m_378 = ((TObjEnemy *)arg0)->has_group();
    }
    *(s32 *)&this->m_37c = ((TUnk_80493450 *)arg0)->countChildren();
    other = (TUnk_80493450 *)next;
    if (other != NULL) {
        diff = (s32 &)other->m_37c - *(s32 *)&this->m_37c;
        if (diff > 1) {
            ((TObjEnemy *)arg0)->link_last_group_child((TObjEnemy *)other, (TObjEnemy *)arg0);
            *(s32 *)&this->m_37c = *(s32 *)&this->m_37c + 1;
            (s32 &)other->m_37c = (s32 &)other->m_37c - 1;
        } else if (diff < -1) {
            ((TObjEnemy *)arg0)->link_last_group_child((TObjEnemy *)arg0, (TObjEnemy *)other);
            *(s32 *)&this->m_37c = *(s32 *)&this->m_37c - 1;
            (s32 &)other->m_37c = (s32 &)other->m_37c + 1;
        }
    }
    dist = horizontal_distance_squared((u8 *)&this->position, (u8 *)&this->home_position);
    range = parameters[1] + (((EnemyMoveParams *)movementParameters)->min_distance + bodies->radius);
    if (range * range < dist) {
        VecCopy((Vec *)&this->m_29c, &this->home_position);
        VecCopy((Vec *)&this->m_290, (const Vec *)&this->m_2fc);
        VecCopy(&this->prev_position, (const Vec *)&this->position);
        VecCopy((Vec *)&lbl_8050BEE0, &this->home_position);
        subtract_vector(&lbl_8050BEE0, (u8 *)&this->position);
        angle = lbl_8043BC88 * atan2_float(lbl_8050BEE0.x, lbl_8050BEE0.z);
        lbl_8050BF00.x = lbl_8050BF00.y = lbl_805DA034;
        lbl_8050BF00.z = this->unk_394;
        push_matrix_from(identity_matrix);
        rotate_matrix_y(0, angle);
        rotate_vector_by_matrix(0, &lbl_8050BF00, &lbl_8050BF00);
        pop_matrices(1);
        vec3_add_to(&lbl_8050BF00, (u8 *)&this->position);
        if (project_actor_to_ground(arg0, &lbl_8050BF00, 0) == 1) {
            this->m_b8 = 2;
            VecCopy((Vec *)&this->position, (const Vec *)&lbl_8050BF00);
            this->rotation_y = approach_angle_limited(this->rotation_y, angle, ((EnemyMoveParams *)movementParameters)->turn_speed);
            goto end;
        }
        r = fabs_float(lbl_8050BEE0.z);
        if (fabs_float(lbl_8050BEE0.x) < r) {
            angle = lbl_8043BC88 * atan2_float(lbl_8050BEE0.x, lbl_805DA034);
        } else {
            angle = lbl_8043BC88 * atan2_float(lbl_805DA034, lbl_8050BEE0.z);
        }
        lbl_8050BF00.x = lbl_8050BF00.y = lbl_805DA034;
        lbl_8050BF00.z = this->unk_394;
        push_matrix_from(identity_matrix);
        rotate_matrix_y(0, angle);
        rotate_vector_by_matrix(0, &lbl_8050BF00, &lbl_8050BF00);
        pop_matrices(1);
        vec3_add_to(&lbl_8050BF00, (u8 *)&this->position);
        if (project_actor_to_ground(arg0, &lbl_8050BF00, 0) == 1) {
            this->m_b8 = 2;
            VecCopy((Vec *)&this->position, (const Vec *)&lbl_8050BF00);
            this->rotation_y = approach_angle_limited(this->rotation_y, angle, ((EnemyMoveParams *)movementParameters)->turn_speed);
            goto end;
        }
        r = fabs_float(lbl_8050BEE0.z);
        if (fabs_float(lbl_8050BEE0.x) < r) {
            angle2 = lbl_8043BC88 * atan2_float(lbl_805DA034, lbl_8050BEE0.z);
        } else {
            angle2 = lbl_8043BC88 * atan2_float(lbl_8050BEE0.x, lbl_805DA034);
        }
        lbl_8050BF00.x = lbl_8050BF00.y = lbl_805DA034;
        lbl_8050BF00.z = this->unk_394;
        push_matrix_from(identity_matrix);
        rotate_matrix_y(0, angle2);
        rotate_vector_by_matrix(0, &lbl_8050BF00, &lbl_8050BF00);
        pop_matrices(1);
        vec3_add_to(&lbl_8050BF00, (u8 *)&this->position);
        if (project_actor_to_ground(arg0, &lbl_8050BF00, 0) == 1) {
            this->m_b8 = 2;
            VecCopy((Vec *)&this->position, (const Vec *)&lbl_8050BF00);
            this->rotation_y = approach_angle_limited(this->rotation_y, angle2, ((EnemyMoveParams *)movementParameters)->turn_speed);
        } else {
            this->m_b8 = 2;
        }
    } else if (*(s32 *)&this->m_37c == 0 && lbl_805DA034 < parameters[1]) {
        this->m_b8 = 2;
        ((s32 (*)(void *, f32, int, f32, f32))enemy_wander_home__9TObjEnemyFlfff)(arg0, ((EnemyMoveParams *)movementParameters)->min_distance, ((EnemyMoveParams *)movementParameters)->turn_speed, parameters[1], parameters[1]);
    } else {
        this->request_stand_action();
    }
end:
    if (obj_testFlags30(0x800000) == 0) {
        apply_actor_gravity(arg0, 0, lbl_805DA034);
    }
    ((TObjCollidable *)arg0)->refresh_collision_body_centers();
    minimap_render_dot((u8 *)&this->position, -0x5DB4, 1, 0);
    ((TObjBase *)arg0)->obj_clearFlags30(0x04240000);
    ((TObjCollidable *)arg0)->clear_player_status_flag((s32)((void *)0), (u32)((void *)0x0A000000));
}

void TUnk_80493450::vfunc_58() {
    switch (this->mode) {
    case 1:
        if ((s32) this->m_390 != 0) {
            this->mode = 0;
            this->phase = 0;
        }
        break;
    case 0:
        switch ((s16) this->phase) {
        case 2:
            if ((s32) this->m_390 != 0) {
                this->phase = 0;
            }
            break;
        }
        break;
    default:
        if ((s32) this->m_390 != 0) {
            this->mode = 0;
        } else {
            this->mode = 1;
        }
        this->phase = 0;
        ((TUnk_80493450 *)this)->request_stand_action();
        obj_setFlags30(this, 0x04040000);
        set_indexed_flags(0, 0x0A000000);
        break;
    }
}

u16 find_nearest_visible_player(void *, int, f32);
u32 csnVector(void *, void *, s32);
extern s32 lbl_805D586C;
extern s32 lbl_805D5870;
extern const Vec lbl_8043BC68;
}
u16 get_enemy_target_id(void *p);
extern "C" {

void TUnk_80493450::vfunc_28() {
    TUnk_80493450 *self = this;
    u16 best;
    TObjPlayer *player;
    u16 id;
    f32 best_dist;
    f32 dist;

    if (self->m_390 == 1) {
        self->targetId = 0xFFFF;
        obj_setFlags30(self, 0x04040000);
    } else if (self->obj_testFlags30(0x1000) != 0) {
        if (--self->m_374 < 0) {
            self->targetId = 0xFFFF;
            self->m_374 = 0;
            obj_setFlags30(self, 0x1000);
        } else {
            self->targetId = find_nearest_visible_player(self, 0, *(f32 *)self->movementParameters);
        }
    } else if (self->obj_testFlags30(0x10) != 0) {
        if (self->is_actor_cadence_frame(0x1E) != 0) {
            s32 i = 0;
            best = 0xFFFF;
            Vec d = lbl_8043BC68;
            best_dist = *(f32 *)self->movementParameters * *(f32 *)self->movementParameters;
            for (; i < lbl_805D586C + lbl_805D5870; i++) {
                player = TObjPlayer::get_player_data(i);
                if (player == NULL) {
                    break;
                }
                id = get_entity_id(player);
                if (id < 0x4000 && id != self->entity_id && player->obj_testFlags30(0x03000800) == 0) {
                    VecCopy(&d, (Vec *)&player->m_2fc);
                    subtract_vector(&d, &self->m_2fc);
                    dist = d.x * d.x + d.z * d.z;
                    if (dist < best_dist && check_path_obstructed(self, &player->m_2fc) != 1 &&
                        csnVector(&self->m_2fc, &player->m_2fc, -1) == 0) {
                        best = id;
                        best_dist = dist;
                    }
                }
            }
            self->targetId = best;
        }
    } else if (self->m_378 != 0) {
        self->targetId = get_enemy_target_id(self->groupRoot());
    } else if (self->is_actor_cadence_frame(0x1E) != 0) {
        self->targetId = find_nearest_visible_player(self, 0, *(f32 *)self->movementParameters);
    }
    if (self->targetId < 0x1000) {
        TObjPlayer *p = get_player_by_client_id(self->targetId);
        if (p != NULL && p->get_field_3e4() == get_current_floor()) {
            self->target = (u8 *)p;
        } else {
            self->target = NULL;
        }
    } else if (self->targetId < 0x4000) {
        self->target = get_enemy_entity(self->targetId);
    } else {
        self->target = NULL;
    }
}

#pragma defer_codegen on
TUnk_80493450::TUnk_80493450(TObject *parent) : TObjEnemy(parent) {
    mode = 0;
    phase = 0;
    m_374 = 0;
    m_376 = 0;
    m_378 = 0;
    m_37c = 0;
    unk_380 = lbl_805DA034;
    m_384 = lbl_805DA058;
    unk_388 = lbl_805DA05C;
    m_38c = 0;
    m_390 = 0;
    m_398 = lbl_805DA060;
    unk_39C = lbl_805DA064;
    unk_394 = lbl_805DA060;
    m_3a0 = lbl_805DA060;
    unk_3A4 = lbl_805DA064;
}
TUnk_80493450::~TUnk_80493450() {}

void TUnk_80493450::run_task() {
    u8 *arg0 = (u8 *)this;
  s16 temp_r0;
  if (TObjPlayer::check_demo_mode() == 1)
  {
    (this->vfunc_101());
    return;
  }
  temp_r0 = this->mode;
  {
    switch (temp_r0)
    {
      case 0:
        (this->vfunc_83());
        break;
      case 1:
        (this->beast_idle_update());
        break;
      case 2:
        (this->update_turn_toward_target());
        break;
      case 3:
        (this->beast_update_approach());
        break;
      case 4:
        (this->beast_update_group_chase());
        break;
      case 5:
        (this->beast_update_attack());
        break;
      case 6:
        (this->vfunc_89());
        break;
      case 7:
        (this->beast_update_hurt());
        break;
      case 8:
        (this->beast_update_dead());
        break;
      case 9:
        (this->beast_retire_corpse());
        break;
    }
  }
  ((TObjEnemy *)arg0)->update_prev_position();
  ((TObjChara *)arg0)->refresh_center_from_body();
  submit_cursor_candidate((void *) arg0, -1);
  this->m_2b4 = (f32) ((this->m_2b4) + lbl_805DA048);
}

}
