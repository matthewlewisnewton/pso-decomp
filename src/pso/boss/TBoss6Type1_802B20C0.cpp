#include "pso/system/SoundEffect.h"
#include "pso/misc/PersistentSound.h"
#pragma readonly_strings on
#include "types.h"
#include "pso/misc/TOTrapAncient01_80226534.h"
#include "pso/boss/TBoss6Type1_802B20C0.h"
#include "pso/system/vector.h"
#include "pso/boss/TBoss6Type1.h"
#include "pso/boss/TBoss6PlotFalz.h"

struct TBoss6Type1Action {
    const char *name;
    s32 anim;
    s32 param;
    void (TBoss6Type1::*act)();
    void (TBoss6Type1::*idle)();
    void (TBoss6Type1::*update)();
};

TBoss6Type1Action boss6_type1_action_table[41] = {
    { "APPEAR", 2, 1, &TBoss6Type1::init_effect_slot_1, 0, &TBoss6Type1::sub_802B3B94 },
    { "RND_FLOAT", 2, 1, &TBoss6Type1::init_attack_timers, &TBoss6Type1::choose_next_action, &TBoss6Type1::tick_countdown },
    { "RND_MOVE", 2, 1, &TBoss6Type1::start_attack, 0, &TBoss6Type1::update_attack_countdown_reset },
    { "KAKUSAN", 11, 1, &TBoss6Type1::init_state_90, 0, &TBoss6Type1::sub_802B381C },
    { "KAKUSAN_MV", 11, 1, &TBoss6Type1::init_hp_state, 0, &TBoss6Type1::update_action_timer },
    { "SWORD", 13, 1, &TBoss6Type1::set_phase_timer_3E, 0, &TBoss6Type1::update_timer_state },
    { "SWORD2", 13, 1, &TBoss6Type1::set_phase_timer_3E, 0, &TBoss6Type1::update_timer_state },
    { "SWORD3", 13, 1, &TBoss6Type1::set_phase_timer_3E, 0, &TBoss6Type1::update_timer_state },
    { "SWORD_MV", 13, 1, &TBoss6Type1::init_attack_timer, 0, &TBoss6Type1::sub_802B3564 },
    { "SWORD_MV2", 13, 1, &TBoss6Type1::init_attack_timer, 0, &TBoss6Type1::sub_802B3564 },
    { "SWORD_MV3", 13, 1, &TBoss6Type1::init_attack_timer, 0, &TBoss6Type1::sub_802B3564 },
    { "SWORD_U", 12, 0, &TBoss6Type1::init_action_timer, 0, &TBoss6Type1::sub_802B343C },
    { "SWORD_U2", 12, 0, &TBoss6Type1::init_action_timer, 0, &TBoss6Type1::sub_802B343C },
    { "SWORD_U3", 12, 0, &TBoss6Type1::init_action_timer, 0, &TBoss6Type1::sub_802B343C },
    { "SWORD_U4", 12, 0, &TBoss6Type1::init_action_timer, 0, &TBoss6Type1::sub_802B343C },
    { "SWORD_U5", 12, 0, &TBoss6Type1::init_action_timer, 0, &TBoss6Type1::sub_802B343C },
    { "SWORD_D", 12, 0, &TBoss6Type1::init_action_timer, 0, &TBoss6Type1::sub_802B343C },
    { "SWORD_D2", 12, 0, &TBoss6Type1::init_action_timer, 0, &TBoss6Type1::sub_802B343C },
    { "SWORD_D3", 12, 0, &TBoss6Type1::init_action_timer, 0, &TBoss6Type1::sub_802B343C },
    { "SWORD_D4", 12, 0, &TBoss6Type1::init_action_timer, 0, &TBoss6Type1::sub_802B343C },
    { "SWORD_D5", 12, 0, &TBoss6Type1::init_action_timer, 0, &TBoss6Type1::sub_802B343C },
    { "TAILATK_MV", 14, 1, &TBoss6Type1::init_dice_state, 0, &TBoss6Type1::update_attack_timer2 },
    { "FLLSR_MV", 15, 1, &TBoss6Type1::sub_802B3320, 0, &TBoss6Type1::sub_802B31E4 },
    { "SCREAM", 20, 0, &TBoss6Type1::sub_802B3178, 0, &TBoss6Type1::update_timer },
    { "CHAL_UD", 0, 1, &TBoss6Type1::set_phase_90, &TBoss6Type1::start_action_if_idle, &TBoss6Type1::update_charge },
    { "CHAL_FLOAT", 0, 1, &TBoss6Type1::init_hp_and_state, &TBoss6Type1::sub_802B2F00, &TBoss6Type1::tick_trap_countdown },
    { "GOTO_CENTOP", 3, 0, &TBoss6Type1::init_state, 0, &TBoss6Type1::update_timer_transition },
    { "CENTOP_D", 0, 0, &TBoss6Type1::sub_802B2D68, 0, &TBoss6Type1::tick_flee_countdown },
    { "CENTOP_U", 0, 0, &TBoss6Type1::sub_802B2CB4, &TBoss6Type1::trigger_falz_phase, &TBoss6Type1::update_phase },
    { "DOWN_CENTOP", 5, 0, &TBoss6Type1::init_params, 0, &TBoss6Type1::sub_802B2A94 },
    { "LAND_CENTOP", 8, 2, &TBoss6Type1::advance_plot_to_state2, &TBoss6Type1::update_attack_state, &TBoss6Type1::update_hit_timer },
    { "BOMB_CENTOP", 8, 2, &TBoss6Type1::init_move_attack, 0, &TBoss6Type1::tick_state_410_timer },
    { "TKOF_CENTOP", 9, 0, &TBoss6Type1::enter_release_state, &TBoss6Type1::update_if_idle, &TBoss6Type1::sub_802B2724 },
    { "RET_RND_UD", 2, 0, &TBoss6Type1::init_charge, 0, &TBoss6Type1::tick_attack_sequence },
    { "GOTO_CENBTM", 2, 0, &TBoss6Type1::init_work, 0, &TBoss6Type1::update_attack_timer },
    { "CENBTM_D", 2, 0, &TBoss6Type1::sub_802B24B4, 0, &TBoss6Type1::sub_802B245C },
    { "CENBTM_U", 2, 0, &TBoss6Type1::reset_effects, &TBoss6Type1::update_state, &TBoss6Type1::update_countdown },
    { "PUT_MINE", 2, 0, &TBoss6Type1::set_phase_555, &TBoss6Type1::update_if_ready, &TBoss6Type1::update_countdown_state },
    { "RET_RND_DU", 2, 0, &TBoss6Type1::init_charge_attack, 0, &TBoss6Type1::update_attack_countdown },
    { "WAITNEXT", -1, 0, 0, &TBoss6Type1::enter_flag800_state, 0 },
    { "DEAD", -1, 0, 0, 0, 0 },
};

static const Vec centop_pos = {0.0f, 275.0f, 0.0f};
static const Vec centop_down_pos = {0.0f, 225.0f, 0.0f};
static const Vec down_centop_pos = {0.0f, 144.0f, 0.0f};
static const Vec down_centop_land_pos = {0.0f, 64.0f, 0.0f};
static const Vec cenbtm_pos = {0.0f, -145.0f, 0.0f};
static const Vec cenbtm_down_pos = {0.0f, -180.0f, 0.0f};
static Vec tkof_centop_low_pos = {0.0f, 114.0f, 0.0f};
static Vec tkof_centop_high_pos = {0.0f, 264.0f, 0.0f};

extern "C" {
s32 is_normal_difficulty();
void TBoss6Type1__sub_802B4A9C(TBoss6Type1 *boss);
void TBoss6Type1__sub_802B4B04(TBoss6Type1 *self);
void TBoss6Type1__sub_802B5140(TBoss6Type1 *arg0, s32 arg1, s32 arg2);
void TBoss6Type1__sub_802B5598(TBoss6Type1 *self, Vec *out);
s32 TBoss6Type1__sub_802B6060(TBoss6Type1 *arg0);
void TBoss6Type1__sub_802B6504(TBoss6Type1 *self);
void TBoss6Type1__sub_802B6944(TBoss6Type1 *self);
void TBoss6Type1__sub_802B6C30(TBoss6Type1 *self);
void TBoss6Type1__sub_802B715C(TBoss6Type1 *self);
void TBoss6Type1__sub_802B73AC(TBoss6Type1 *self);
void TBoss6Type1__sub_802B8A70(TBoss6Type1 *self);
void TBoss6Type1__sub_802B8BB4(TBoss6Type1 *arg0);
void TBoss6Type1__sub_802B8E1C(TBoss6Type1 *arg0);
s32 rand(void);

extern const Vec lbl_80470CE0;

void TBoss6Type1::enter_flag800_state() {
    if (this->actorFlags & 0x800) {
        send_flow_action_if_idle(this, 0x28);
        return;
    }
    send_flow_action_if_idle(this, 1);
}

void TBoss6Type1::update_attack_countdown() {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r3;
    s32 temp_r3b;

    interpolate_pos_to_target(this->action_timer, this->m_40c);
    ease_toward_target(this->action_timer, this->m_40c);
    temp_r3 = this->m_40c - 2;
    temp_r0 = this->action_timer;
    temp_r3b = temp_r3 - 0xA;
    if (temp_r0 == temp_r3) {
        set_motion_set(6);
    } else if (temp_r0 == temp_r3b) {
        this->m_438 = 1;
    }
    temp_r0_2 = this->action_timer - 1;
    this->action_timer = temp_r0_2;
    if (temp_r0_2 < 0) {
        latch_phase_counter();
        this->m_414 = 0;
        set_action_state(1);
    }
}

void TBoss6Type1::init_charge_attack() {
    this->m_40c = 0x3C;
    this->action_timer = 0x3C;
    play_sound_effect(0x4003A811, &this->position, 0, 1);
    this->release_effect_slot(0);
    this->release_effect_slot(1);
}

void TBoss6Type1::update_countdown_state() {
    s32 temp_r0;
    if ((s32) this->action_timer == (s32) ((f32) this->m_40c - 30.0f)) {
        this->release_effect_slot(3);
    }
    temp_r0 = this->action_timer - 1;
    this->action_timer = temp_r0;
    if (temp_r0 < 0) {
        this->set_action_state(0x27);
    }
}

void TBoss6Type1::update_if_ready() {
    if (((s32) this->action_timer == 0) || (this->is_timer_expired() != 0)) {
        TBoss6Type1__sub_802B8E1C(this);
    }
}

void TBoss6Type1::set_phase_555() { this->m_40c = 555; this->action_timer = 555; TBoss6Type1__sub_802B6504(this); release_effect_slot(0); release_effect_slot(1); spawn_effect_slot(3); }

void TBoss6Type1::update_countdown() {
    s32 temp_r0;

    interpolate_pos_to_target(this->action_timer, this->m_40c);
    temp_r0 = this->action_timer - 1;
    this->action_timer = temp_r0;
    if (temp_r0 < 0) {
        set_action_state(0x27);
    }
}

void TBoss6Type1::update_state() {
    if ((s32) this->action_timer == 0) {
        if (is_normal_difficulty() != 0) {
            TBoss6Type1__sub_802B8E1C(this);
            return;
        }
        if (is_field3F8_over_0x20() != 0) {
            send_flow_action_if_idle(this, 0x25);
            return;
        }
        TBoss6Type1__sub_802B8E1C(this);
    }
}

void TBoss6Type1::reset_effects() {
    this->m_40c = 0x1E;
    this->action_timer = 0x1E;
    VecCopy(&this->m_420.v, &cenbtm_pos);
    this->release_effect_slot(0);
    this->release_effect_slot(1);
}

void TBoss6Type1::sub_802B245C() {
    TBoss6Type1 *boss6_type1 = this;
    s32 temp_r0;

    boss6_type1->interpolate_pos_to_target(boss6_type1->action_timer, boss6_type1->m_40c);
    temp_r0 = boss6_type1->action_timer - 1;
    boss6_type1->action_timer = temp_r0;
    if (temp_r0 < 0) {
        boss6_type1->set_action_state((int)(0x14 - (boss6_type1->m_41c & 1)));
    }
}

void TBoss6Type1::sub_802B24B4() {
    TBoss6Type1 *boss6_type1 = this;
    boss6_type1->m_40c = 0x1E;
    boss6_type1->action_timer = 0x1E;
    VecCopy(&boss6_type1->m_420.v, &cenbtm_down_pos);
    boss6_type1->release_effect_slot(0);
    boss6_type1->release_effect_slot(1);
}

void TBoss6Type1::update_attack_timer() {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r3;
    s32 temp_r3b;

    interpolate_pos_to_target(this->action_timer, this->m_40c);
    ease_toward_target(this->action_timer, this->m_40c);
    temp_r3 = this->m_40c - 2;
    temp_r0 = this->action_timer;
    temp_r3b = temp_r3 - 0xA;
    if (temp_r0 == temp_r3) {
        set_motion_set(6);
    } else if (temp_r0 == temp_r3b) {
        this->m_438 = 0;
    }
    temp_r0_2 = this->action_timer - 1;
    this->action_timer = temp_r0_2;
    if (temp_r0_2 < 0) {
        set_action_state(0x23);
    }
}

void TBoss6Type1::init_work() {
    this->m_40c = 0x3C;
    this->action_timer = 0x3C;
    VecCopy(&this->m_420.v, &cenbtm_pos);
    play_sound_effect(0x39403, &this->node_positions_578[1].v, 0, 1);
    play_sound_effect(0x4003A811, &this->position, 0, 1);
    this->release_effect_slot(0);
    this->spawn_effect_slot(1);
}

void TBoss6Type1::tick_attack_sequence() {
    s32 temp_r0;
    s32 temp_r0_2;

    interpolate_pos_to_target(this->action_timer, this->m_40c);
    temp_r0 = this->action_timer;
    if (temp_r0 == 0x23) {
        set_motion_set(6);
    } else if (temp_r0 == 0x19) {
        this->m_438 = 1;
    }
    temp_r0_2 = this->action_timer - 1;
    this->action_timer = temp_r0_2;
    if (temp_r0_2 < 0) {
        latch_phase_counter();
        this->m_414 = 0;
        set_action_state(1);
    }
}

void TBoss6Type1::init_charge() {
    this->m_40c = 0x3C;
    this->action_timer = 0x3C;
    play_sound_effect(0x4003A811, &this->position, 0, 1);
    this->release_effect_slot(0);
    this->spawn_effect_slot(1);
}

void TBoss6Type1::sub_802B2724() {
    TBoss6Type1 *boss6_type1 = this;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r4;
    temp_r0 = boss6_type1->action_timer;
    if (temp_r0 == 0x4A) {
        VecCopy(&boss6_type1->m_420.v, &tkof_centop_low_pos);
    } else if (temp_r0 == 0x3B) {
        VecCopy(&boss6_type1->m_420.v, &tkof_centop_high_pos);
    }
    temp_r4 = boss6_type1->action_timer;
    if (temp_r4 <= 0x4A) {
        if (temp_r4 > 0x3B) {
            boss6_type1->interpolate_pos_to_target(temp_r4 - 0x3B, 0xF);
        } else {
            boss6_type1->interpolate_pos_to_target(temp_r4, boss6_type1->m_40c);
        }
    }
    temp_r0_2 = boss6_type1->action_timer - 1;
    boss6_type1->action_timer = temp_r0_2;
    if (temp_r0_2 < 0) {
        boss6_type1->set_action_state(0x27);
    }
}

void TBoss6Type1::update_if_idle() { if (this->action_timer == 0) { TBoss6Type1__sub_802B8E1C(this); } }

void TBoss6Type1::enter_release_state() {
    this->m_40c = 0x5A;
    this->action_timer = 0x5A;
    release_object(this);
    play_sound_effect(0x4003B515, (const Vec *)((u8 *)&this->position), 0, 0);
    this->spawn_effect_slot(0);
    this->release_effect_slot(1);
    this->m_3f8->activate_warp();
    this->m_3f8->reset_state();
    if (this->count_matches(0x1F, 4) == 0) {
        play_sound_effect(0x68A24, (const Vec *)((u8 *)&this->position), 0, 1);
    }
}

void TBoss6Type1::tick_state_410_timer() {
    s32 temp_r0;

    temp_r0 = this->action_timer - 1;
    this->action_timer = temp_r0;
    if (temp_r0 < 0) {
        set_action_state(0x20);
    }
}

void TBoss6Type1::init_move_attack() {
    this->m_40c = 0x1E;
    this->action_timer = 0x1E;
    this->damage_players_in_range();
    play_sound_effect(0x40039C19, (const Vec *)((u8 *)&this->position), 0, 0);
}

void TBoss6Type1::update_hit_timer() {
    s32 temp_r3;

    play_persistent_sound((s32)(0x40032614), (const void *)(this), (const Vec *)(0), 0, 0);
    if ((s32) this->action_timer == 0x3C) {
        play_sound_effect(0x39403, &this->position, 0, 1);
    }
    temp_r3 = this->action_timer;
    if (temp_r3 > 0) {
        this->action_timer = (temp_r3 - 1);
        return;
    }
    this->action_timer = 0;
}

void TBoss6Type1::update_attack_state() {
    if ((s32) this->action_timer == 0) {
        if (this->is_field4b0_delta_reached() != 0) {
            send_flow_action_if_idle(this, 0x20);
            return;
        }
        send_flow_action_if_idle(this, 0x1F);
    }
}

void TBoss6Type1::advance_plot_to_state2() {
    this->m_40c = 0x12C;
    this->action_timer = 0x12C;
    this->m_3f8->free_child();
    this->m_3f8->set_state_2();
    spawn_map_csn();
    play_sound_effect(0x40039C13, (const Vec *)((u8 *)&this->position), 0, 0);
    this->release_effect_slot(0);
    this->release_effect_slot(1);
    this->latch_phase_counter();
}

void TBoss6Type1::sub_802B2A94() {
    TBoss6Type1 *arg0 = this;
    f32 temp_f1;
    s32 temp_r0;
    s32 temp_r0_2;
    arg0->interpolate_pos_to_target(arg0->action_timer, arg0->m_40c);
    if ((s32) arg0->action_timer == (s32) ((f32) arg0->m_40c - 10.0f)) {
        arg0->m_438 = 0;
    }
    temp_f1 = arg0->position.y;
    if ((temp_f1 <= 230.0f) && (temp_f1 > 228.0f)) {
        arg0->set_motion_set(1);
    } else {
        temp_r0 = arg0->action_timer;
        if (temp_r0 == 0x46) {
            arg0->set_motion_set(7);
        } else if (temp_r0 == 0xF) {
            VecCopy(&arg0->m_420.v, &down_centop_land_pos);
        }
    }
    play_persistent_sound(0x4003B012, arg0, &arg0->position, 0, 0);
    temp_r0_2 = arg0->action_timer - 1;
    arg0->action_timer = temp_r0_2;
    if (temp_r0_2 < 0) {
        arg0->set_action_state(0x1E);
    }
}

void TBoss6Type1::init_params() {
    spawn_grav_ball();
    this->m_40c = 300;
    this->action_timer = 300;
    VecCopy((Vec *)((void *)((char *)this + 1056)), &down_centop_pos);
    spawn_effect_slot(0);
    release_effect_slot(1);
}

void TBoss6Type1::update_phase() {
    s32 temp_r0;

    interpolate_pos_to_target(this->action_timer, this->m_40c);
    temp_r0 = this->action_timer - 1;
    this->action_timer = temp_r0;
    if ((temp_r0 < 0) && (is_normal_difficulty() == 0)) {
        set_action_state(0x1D);
    }
}

void TBoss6Type1::trigger_falz_phase() {
    if (((s32) this->action_timer == 0) && (is_normal_difficulty() != 0)) {
        TBoss6Type1__sub_802B8E1C(this);
    }
}

void TBoss6Type1::sub_802B2CB4() {
    TBoss6Type1 *boss6_type1 = this;
    boss6_type1->m_40c = 0x1E;
    boss6_type1->action_timer = 0x1E;
    VecCopy(&boss6_type1->m_420.v, &centop_pos);
    boss6_type1->spawn_effect_slot(0);
    boss6_type1->release_effect_slot(1);
}

void TBoss6Type1::tick_flee_countdown() {
    s32 temp_r0;

    interpolate_pos_to_target(this->action_timer, this->m_40c);
    temp_r0 = this->action_timer - 1;
    this->action_timer = temp_r0;
    if (temp_r0 < 0) {
        set_action_state((int)(0xF - (this->m_41c & 1)));
    }
}

void TBoss6Type1::sub_802B2D68() {
    TBoss6Type1 *boss6_type1 = this;
    boss6_type1->m_40c = 0x1E;
    boss6_type1->action_timer = 0x1E;
    VecCopy(&boss6_type1->m_420.v, &centop_down_pos);
    boss6_type1->spawn_effect_slot(0);
    boss6_type1->release_effect_slot(1);
}

void TBoss6Type1::update_timer_transition() {
    s32 temp_r0;

    interpolate_pos_to_target(this->action_timer, this->m_40c);
    temp_r0 = this->action_timer - 1;
    this->action_timer = temp_r0;
    if (temp_r0 < 0) {
        set_action_state(0x1B);
    }
}

void TBoss6Type1::init_state() {
    this->m_40c = 0x3C;
    this->action_timer = 0x3C;
    VecCopy(&this->m_420.v, &centop_pos);
    play_sound_effect(0x39403, &this->node_positions_578[1].v, 0, 1);
    play_sound_effect(0x4003A811, &this->position, 0, 1);
    this->release_effect_slot(0);
    this->spawn_effect_slot(1);
}

void TBoss6Type1::tick_trap_countdown() {
    s32 temp_r0;

    play_persistent_sound(0x40038F0F, this, &this->position, 0, 0);
    temp_r0 = this->action_timer - 1;
    this->action_timer = temp_r0;
    if (temp_r0 < 0) {
        this->set_action_state(0x27);
    }
}

void TBoss6Type1::sub_802B2F00() {
    if ((((f32) this->action_timer / (f32) this->m_40c) < 0.5f) && (this->check_field4b0_threshold() != 0)) {
        this->do_attack();
        return;
    }
    if ((s32) this->action_timer == 0) {
        if (TBoss6Type1__sub_802B6060(this) != 0) {
            send_flow_action_if_idle(this, 0x1A);
            return;
        }
        send_flow_action_if_idle(this, 0x22);
    }
}

void TBoss6Type1::init_hp_and_state() { this->m_40c = 300; this->action_timer = 300; spawn_effect_slot(0); release_effect_slot(1); }

void TBoss6Type1::update_charge() {
    s32 temp_r0;

    this->interpolate_pos_to_target((s32)(this->action_timer), (s32)(this->m_40c));
    play_persistent_sound(0x40038F0F, this, &this->position, 0, 0);
    temp_r0 = this->action_timer - 1;
    this->action_timer = temp_r0;
    if (temp_r0 < 0) {
        this->set_action_state(0x27);
    }
}

void TBoss6Type1::start_action_if_idle() { if (this->action_timer == 0) { send_flow_action_if_idle(this, 25); } }

void TBoss6Type1::set_phase_90() { this->m_40c = 90; this->action_timer = 90; latch_phase_counter(); spawn_effect_slot(0); release_effect_slot(1); }

void TBoss6Type1::update_timer() {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r4;

    temp_r0 = this->action_timer;
    temp_r4 = this->m_40c - 0xF;
    if (temp_r0 >= temp_r4) {
        interpolate_pos_to_target((s32)(temp_r0 - temp_r4), 0xF);
    }
    set_flag_on_threshold();
    temp_r0_2 = this->action_timer - 1;
    this->action_timer = temp_r0_2;
    if (temp_r0_2 < 0) {
        latch_phase_counter();
        this->m_414 = 1;
        set_action_state(1);
    }
}

void TBoss6Type1::sub_802B3178() {
    m_40c = 123;
    action_timer = 123;
    clamp_to_arena_radius(&m_420.v);
    play_sound_effect(231170, NULL, 0, 0);
    spawn_effect_slot(0);
    release_effect_slot(1);
}

void TBoss6Type1::sub_802B31E4() {
    TBoss6Type1 *arg0 = this;
    s32 var_r3;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r3;
    s32 temp_r4;
    s32 temp_r5;
    s32 temp_r6;
    temp_r5 = arg0->laser_fire_time;
    temp_r4 = arg0->m_49c;
    temp_r6 = arg0->action_timer;
    temp_r0 = temp_r5 + 0x1E;
    temp_r0 = temp_r4 + temp_r0;
    temp_r0 -= temp_r4;
    temp_r3 = temp_r0 - temp_r5;
    if (temp_r6 == temp_r0) {
        arg0->set_motion_set(0x11);
    } else if (temp_r6 == temp_r3) {
        arg0->release_effect_slot(2);
        arg0->set_motion_set(0x13);
    }
    arg0->rotate_around_center((int) (arg0->action_timer), arg0->m_40c);
    temp_r3 = arg0->action_timer;
    if ((temp_r3 <= (s32) arg0->laser_fire_time) && (temp_r3 >= 0x1E)) {
        arg0->increase_field_clamped_max();
        TBoss6Type1__sub_802B6C30(arg0);
    } else {
        arg0->decrease_field_clamped_min();
    }
    if ((s32) arg0->action_timer >= 0x1E) {
        var_r3 = 0x4003B50C;
        if (arg0->m_4dc > 0.0f) {
            var_r3 = 0x4003AD0D;
        }
        play_persistent_sound(var_r3, arg0, &arg0->node_positions_578[7].v, 0, 1);
    }
    if (arg0->m_4dc > 0.0f) {
        TBoss6Type1__sub_802B4B04(arg0);
    } else {
        TBoss6Type1__sub_802B4A9C(arg0);
    }
    temp_r0_2 = arg0->action_timer - 1;
    arg0->action_timer = temp_r0_2;
    if (temp_r0_2 < 0) {
        arg0->reset_param();
        arg0->set_action_state(1);
    }
}

void TBoss6Type1::sub_802B3320() {
    action_timer = m_40c = m_49c + laser_fire_time + 30;
    play_sound_effect(0x4003A608, (const Vec *)(&node_positions_578[7].v), 0, 0);
    release_effect_slot(0);
    spawn_effect_slot(1);
    spawn_effect_slot(2);
}

void TBoss6Type1::update_attack_timer2() {
    s32 temp_r0;

    TBoss6Type1__sub_802B715C(this);
    interpolate_pos_to_target(this->action_timer, this->m_40c);
    temp_r0 = this->action_timer - 1;
    this->action_timer = temp_r0;
    if (temp_r0 < 0) {
        set_action_state(1);
    }
}

void TBoss6Type1::init_dice_state() { this->m_40c = 62; this->action_timer = 62; release_effect_slot(0); spawn_effect_slot(1); }

void TBoss6Type1::sub_802B343C() {
    TBoss6Type1 *boss6_type1 = this;
    s32 temp_r0;
    s32 temp_r4;

    TBoss6Type1__sub_802B73AC(boss6_type1);
    boss6_type1->interpolate_pos_to_target(boss6_type1->action_timer, boss6_type1->m_40c);
    temp_r0 = boss6_type1->action_timer - 1;
    boss6_type1->action_timer = temp_r0;
    if (temp_r0 < 0) {
        temp_r4 = boss6_type1->m_374;
        switch (temp_r4) {
        case 11:
            boss6_type1->set_action_state(0x1C);
            return;
        case 16:
            boss6_type1->set_action_state(0x24);
            return;
        default:
            boss6_type1->set_action_state(temp_r4 - 1);
            break;
        }
    }
}

void TBoss6Type1::init_action_timer() {
    s32 state;

    m_40c = 0x3E;
    state = m_374;
    if ((state == 0xB) || (state == 0x10)) {
        m_40c += 0x1E;
    }
    action_timer = m_40c;
    calc_grid_cell_position(&m_420.v);
    play_sound_effect(0x40039C21, &node_positions_578[9].v, 0, 0);
    release_effect_slot(0);
    release_effect_slot(1);
}

void TBoss6Type1::sub_802B3564() {
    TBoss6Type1 *boss6_type1 = this;
    s32 temp_r0;
    s32 temp_r4;

    this->update_beam_attack();
    boss6_type1->interpolate_pos_to_target(boss6_type1->action_timer, boss6_type1->m_40c);
    temp_r0 = boss6_type1->action_timer - 1;
    boss6_type1->action_timer = temp_r0;
    if (temp_r0 < 0) {
        temp_r4 = boss6_type1->m_374;
        if (temp_r4 == 8) {
            boss6_type1->set_action_state(1);
            return;
        }
        boss6_type1->set_action_state(temp_r4 - 1);
    }
}

void TBoss6Type1::init_attack_timer() {
    this->m_40c = 0x3E;
    if ((s32) this->m_374 == 8) {
        this->m_40c = (s32) (this->m_40c + 0x1E);
    }
    this->action_timer = (s32) this->m_40c;
    TBoss6Type1__sub_802B5598(this, &this->m_420.v);
    play_sound_effect(0x4003BF07, &this->node_positions_578[9].v, 0, 0);
    this->release_effect_slot(0);
    this->spawn_effect_slot(1);
}

void TBoss6Type1::update_timer_state() {
    s32 temp_r0;
    s32 temp_r4;

    this->update_beam_attack();
    temp_r0 = this->action_timer - 1;
    this->action_timer = temp_r0;
    if (temp_r0 < 0) {
        temp_r4 = this->m_374;
        if (temp_r4 == 5) {
            set_action_state(1);
            return;
        }
        set_action_state(temp_r4 - 1);
    }
}

void TBoss6Type1::set_phase_timer_3E() {
    this->m_40c = 0x3E;
    if ((s32) this->m_374 == 5) {
        this->m_40c = (s32) (this->m_40c + 0x1E);
    }
    this->action_timer = (s32) this->m_40c;
    this->m_40c = 0x3E;
    this->action_timer = 0x3E;
    play_sound_effect(0x4003BF07, &this->node_positions_578[9].v, 0, 0);
    this->spawn_effect_slot(0);
    this->release_effect_slot(1);
}

void TBoss6Type1::update_action_timer() {
    s32 temp_r0_2;

    interpolate_pos_to_target(this->action_timer, this->m_40c);
    switch (this->action_timer) {
    case 0x48:
    case 0x3E:
    case 0x52:
        TBoss6Type1__sub_802B6944(this);
        break;
    }
    temp_r0_2 = this->action_timer - 1;
    this->action_timer = temp_r0_2;
    if (temp_r0_2 < 0) {
        set_action_state(1);
    }
}

void TBoss6Type1::init_hp_state() { this->m_40c = 90; this->action_timer = 90; release_effect_slot(0); spawn_effect_slot(1); }

void TBoss6Type1::sub_802B381C() {
    TBoss6Type1 *boss6_type1 = this;
    s32 temp_r0;

    if ((s32) boss6_type1->action_timer == 0x3E) {
        ((s32 (*)(void))TBoss6Type1__sub_802B6944)();
    }
    temp_r0 = boss6_type1->action_timer - 1;
    boss6_type1->action_timer = temp_r0;
    if (temp_r0 < 0) {
        boss6_type1->set_action_state(1);
    }
}

void TBoss6Type1::init_state_90() { this->m_40c = 90; this->action_timer = 90; spawn_effect_slot(0); release_effect_slot(1); }

void TBoss6Type1::update_attack_countdown_reset() {
    s32 temp_r0;

    interpolate_pos_to_target(this->action_timer, this->m_40c);
    temp_r0 = this->action_timer - 1;
    this->action_timer = temp_r0;
    if (temp_r0 < 0) {
        set_action_state(1);
    }
}

void TBoss6Type1::start_attack() {
    if ((s32) this->m_414 == 0) {
        this->m_40c = 0x1E;
        this->action_timer = 0x1E;
    } else {
        this->m_40c = 0x1E;
        this->action_timer = 0x1E;
    }
    play_sound_effect(0x40039706, (const Vec *)((u8 *)&this->position), 0, 0);
    this->release_effect_slot(0);
    this->spawn_effect_slot(1);
    if (this->count_matches(0x19, 4) > 0) {
        this->latch_phase_counter();
        play_sound_effect(0x68A24, (const Vec *)((u8 *)&this->position), 0, 1);
    }
}

void TBoss6Type1::tick_countdown() {
    s32 temp_r0;

    temp_r0 = this->action_timer - 1;
    this->action_timer = temp_r0;
    if (temp_r0 < 0) {
        set_action_state(0x27);
    }
}

void TBoss6Type1::choose_next_action() {
    s32 temp_r31;

    if ((s32) this->action_timer == 0) {
        if ((s32) this->m_414 == 0) {
            if (this->is_ready() != 0) {
                send_flow_action_if_idle(this, 0x17);
                return;
            }
            if (this->count_matches(2, 0x10) == 0) {
                this->do_attack();
                return;
            }
            if (((this->count_matches(3, 0xA) + this->count_matches(5, 0xA)) == 0) || (((1.0f / 32768.0f) * (f32) rand()) < 0.4f)) {
                TBoss6Type1__sub_802B8BB4(this);
                return;
            }
            this->do_attack();
            return;
        }
        if (this->is_time_up() != 0) {
            TBoss6Type1__sub_802B8A70(this);
            return;
        }
        TBoss6Type1__sub_802B8BB4(this);
    }
}

void TBoss6Type1::init_attack_timers() {
    s32 temp_r0;
    s32 temp_r0_2;

    if ((s32) this->m_414 == 0) {
        this->m_40c = 0x5A;
        this->action_timer = 0x5A;
    } else if ((s32) this->m_4ac != 0) {
        temp_r0 = this->unk_4A8;
        this->m_40c = temp_r0;
        this->action_timer = temp_r0;
    } else {
        temp_r0_2 = this->m_4a4;
        this->m_40c = temp_r0_2;
        this->action_timer = temp_r0_2;
    }
    spawn_effect_slot(0);
    release_effect_slot(1);
}

void TBoss6Type1::sub_802B3B94() {
    s32 temp_r0;

    if ((s32) this->action_timer < 0x1E) {
        TBoss6Type1__sub_802B5140(this, this->action_timer, 0x1E);
    }
    temp_r0 = this->action_timer - 1;
    this->action_timer = temp_r0;
    if (temp_r0 < 0) {
        this->set_action_state(1);
    }
}

void TBoss6Type1::init_effect_slot_1() {
    VecCopy(&this->m_420.v, &lbl_80470CE0);
    this->m_40c = 0x5A;
    this->action_timer = 0x5A;
    this->spawn_effect_slot(1);
}


}
