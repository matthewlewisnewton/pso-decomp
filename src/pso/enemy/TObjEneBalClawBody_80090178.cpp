#define TOBJECT_OUT_OF_LINE_HELPERS
#include "types.h"
#include "pso/enemy/TObjEneBalClawBody.h"
#include "pso/system/BmlResource.h"
#include "pso/system/vector.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/TObjControl.h"
#include "pso/TMainTask.h"
#include "pso/system/NinjaUtil.h"
#include "pso/player/TObjPlayer_801AF2F0.h"
#include "pso/player/TObjPlayer.h"
#include "pso/enemy/TObjEneLappy_800F5DE0.h"

extern "C" {
TObjMotionAction balclaw_body_actions[] = {
    {1, 0, 9, 0.8f, 0}, {1, 1, 9, 0.8f, 1},
    {2, 0, 6, 0.5f, 4}, {2, 0, 7, 0.6f, 8},
    {3, 4, 8, 0.5f, 16}, {1, 5, 5, 0.8f, 0},
    {1, 5, 5, 0.8f, 1}, {2, 5, 0, 0.6f, 4},
    {2, 5, 2, 0.7f, 8}, {3, 5, 3, 0.6f, 16},
    {2, 5, 4, 0.5f, 1}, {2, 5, 1, 0.6f, 1},
};
struct BalClawAttackParams {
    f32 distance;
    f32 m_4;
    s32 m_8;
    s16 m_c;
    s16 m_e;
    s32 m_10;
    s32 m_14;
    s32 m_18;
};
BalClawAttackParams player_attack_param_table[] = {
    {150.0f, 0.5555555f, 0x400, 30, 0, 0, 1, 0},
    {150.0f, 0.5555555f, 0x400, 30, 0, 0, 1, 0},
};
CollisionBody balclaw_body_collision = {{0.0f,18.0f,0.0f},5.0f,0.0f,0,0x8003,{0.0f,0.0f,0.0f},0.0f};
extern const char *lbl_805D2970;
extern const f32 lbl_805D9620;
u8 *lbl_805007A8[2];
u8 *lbl_805007B0[2];
u8 *lbl_805007B8[2];
extern BmlResource *lbl_805D4F20;
void TObjEneBalClawClaw__sub_8008DC90(TObjEneBalClawBody *);
void minimap_render_dot(const Vec *, s32, s32, s32);
extern const f32 lbl_805D9644;
extern const f32 lbl_805D9670;
extern const f32 lbl_805D9674;
extern const f32 lbl_805D9678;
extern const f32 lbl_805D967C;
}

// Deferred code generation emits these definitions in reverse order, matching
// the original function order and placing the native vtable before switch data.
void TObjEneBalClaw::select_model(s32 i) {
    model = (void *)lbl_805D4F20->models[i].model;
    texlist = lbl_805D4F20->models[i].m_c;
}

TObjEneBalClawBody::TObjEneBalClawBody(TObject *parent, BalClawSetData *set_data)
    : TObjEneBalClaw(parent) {
    m_name = lbl_805D2970;
    apply_set_data(set_data);
    VecCopy((Vec *)&m_290, VecCopy((Vec *)&m_29c, &position));
    motion_list = lbl_805D4F20->motions;
    action_table = balclaw_body_actions;
    set_field_d8((s32)action_table);
    init_collision_body_parts(this, &balclaw_body_collision, 1);
    m_b8 = 0;
    set_animation(m_b8);
    set_field_b8(m_b8);
    hp = hpmax;
    tp = tpmax;
    referenceHp = hp;
    update_prev_position();
    initialize_enemy_photon_effect(this);
    m_3b8 = 0;
    m_3bc = lbl_805D9620;
    clear_attack_flag();
    if (set_data->wave != 0) sub_800C7860();
    m_3ac = 25.0f;
    m_3b0 = 40.0f;
    m_3b4 = m_3ac;
    m_3d8 = 4;
    for (s32 i = 0; i < 4; ++i) claw_ids[i] = 0xffff;
    set_form(1);
    bind_enemy_combat_stats(lbl_805007A8[0], lbl_805007B0[0], lbl_805007B8[0]);
    effects[0] = NULL;
    effects[1] = NULL;
    effects[2] = NULL;
    effects[3] = NULL;
    clear_lobby_object_state();
}

TObjEneBalClawBody::~TObjEneBalClawBody() {
    free_collision_body_parts(this);
    if (effects[0] != NULL) effects[0]->queue_destruction();
    if (effects[1] != NULL) effects[1]->queue_destruction();
    if (effects[2] != NULL) effects[2]->queue_destruction();
    if (effects[3] != NULL) effects[3]->queue_destruction();
    if (get_flag_0x388_b24()) {
        for (s32 i = 0; i < m_3d8; ++i) {
            TObject *object = find_entity_by_id(claw_ids[i]);
            if (object != NULL) object->queue_destruction();
        }
    }
}


void *TObjEneBalClawBody::create(void *set_data) {
    TObjControl *control = new TObjControl(tl_04);
    return new TObjEneBalClawBody(control, (BalClawSetData *)set_data);
}

void TObjEneBalClawBody::run_task() {
    TObjEneBalClaw__sub_8008D68C();
    if (TObjPlayer::check_demo_mode() == 1) {
        TObjEneBalClawClaw__sub_8008DC90(this);
        fn_8008FC0C();
        return;
    }
    if ((m_388 & 0x02000000) && get_flag_0x388_b24() == 0) {
        update_if_active(2);
    } else {
        sub_8008FC10();
    }
    if (mode != (s32)next_action) {
        if ((s32)state != -1) {
            state = -1;
            sub_8008FF50();
        }
        mode = next_action;
        state = 0;
    }
    sub_8008FF50();
    update_wobble();
    update_claw_angle();
    VecCopy(body_center(), &position);
    m_300 += m_3b4 + m_3bc;
    bodies->offset.y = m_3b4 + m_3bc;
    submit_cursor_candidate(this, -1);
    minimap_render_dot(&position, -0x5DB4, 1, 0);
}

void TObjEneBalClawBody::sub_8008FF50() {
    switch (mode) {
    case 0: update_dragon_boss_state(); return;
    case 1: fn_8008FAD0(); return;
    case 2: fn_8008F1DC(); return;
    case 9: fn_8008EDE8(); return;
    case 4: fn_8008F910(); return;
    case 5: run_death_sequence(); return;
    case 7: fn_8008EC3C(); return;
    case 10: fn_8008E310(); return;
    case 11: fn_8008E254(); return;
    case 12: update_move_to_target(); return;
    case 8: fn_8008DD14(); break;
    }
}

void TObjEneBalClawBody::sub_8008FC10() {
    f32 distance;
    s32 old_range;
    if (mode != 0 && mode != 8) {
        action_timer++;
    }
    if (get_flag_0x388_b24() != 0) {
        switch (mode) {
        case 0:
        case 1:
            if (action_timer > 0x708 || m_3da >= 2) {
                update_if_active(11);
                return;
            }
            break;
        }
        if (is_actor_cadence_frame(30) != 0) {
            find_target_in_range(lbl_805D9644);
        }
        switch (mode) {
        case 0:
        case 8:
            if (target != NULL) {
                update_if_active(1);
                range_state = 2;
            } else {
                sub_800C73F4();
            }
            break;
        case 1:
            if (target != NULL) {
                distance = xz_distance_squared(&((TObjBase *)target)->position, &position);
                old_range = range_state;
                switch (old_range) {
                case 0:
                    if (distance > lbl_805D9670) range_state = 1;
                    break;
                case 1:
                    if (distance < lbl_805D9674) range_state = 0;
                    else if (distance > lbl_805D9678) range_state = 2;
                    break;
                case 2:
                    if (distance < lbl_805D967C) range_state = 1;
                    break;
                }
                if (old_range != range_state) {
                    switch (range_state) {
                    case 0: update_if_active(9); break;
                    case 1: clear_attack_flag(); break;
                    case 2: set_attack_distance_flag(); break;
                    }
                }
            } else {
                update_if_active(8);
            }
            break;
        }
    } else {
        if (is_actor_cadence_frame(30) != 0 && mode != 2) {
            find_target_in_range(lbl_805D9644);
        }
        switch (mode) {
        case 0:
            if (is_actor_cadence_frame(30) != 0 && target == NULL) {
                update_if_active(10);
                return;
            }
            break;
        case 1:
        case 12:
            if (action_timer > 0x708) {
                update_if_active(10);
                return;
            }
            break;
        }
        switch (mode) {
        case 0:
        case 8:
            if (target != NULL) update_if_active(12);
            else sub_800C73F4();
            break;
        case 1:
            if (target == NULL) update_if_active(8);
            break;
        }
    }
}

void TObjEneBalClawBody::fn_8008FC0C() {}
