#include "pso/misc/PersistentSound.h"
#include "types.h"
#include "pso/misc/TOTrapAncient01_80226534.h"
#include "pso/boss/TBoss6Type2_802BF558.h"
#include "pso/unk/text_80087278.h"
#include "pso/boss/TBoss6Type2.h"

typedef struct S_802BF6CC {
    u8 pad0[0x374];
    s32 f374;
    u8 pad378[0x45C - 0x378];
    s32 f45C;
    s32 f460;
    u8 pad464[0x504 - 0x464];
    s32 f504;
} S_802BF6CC;

extern "C" {
s32 play_sound_effect(int, void *, int, int);
extern s32 lbl_805D6750;
extern u8 lbl_805D6754;
extern const f32 lbl_805DE3F4;
extern const f32 lbl_805DE4DC;
s32 TBoss6Type2__sub_802BB7C0(void *);
s32 TBoss6Type2__sub_802BA944(void *);
s32 TBoss6Type2__sub_802BA9E4();
int TBoss6Type2__sub_802BB694(void);
s32 TBoss6Type2__sub_802BB768();

extern "C" {

void TBoss6Type2::start_death_sequence(u8 *arg0) {
    s32 temp_r0;
    u8 *boss6_type2;
    u8 *var_r3;

    var_r3 = arg0;
    boss6_type2 = var_r3;
    temp_r0 = *(s32 *)((s8 *)var_r3 + 0x4C8);
    *(s32 *)((s8 *)var_r3 + 0x45C) = temp_r0;
    *(s32 *)((s8 *)var_r3 + 0x460) = temp_r0;
    switch (*(s32 *)((s8 *)var_r3 + 0x47C)) {
    case 15:
        var_r3 = (unsigned char *) ((void *)0x68522);
        break;
    case 16:
        var_r3 = (unsigned char *) ((void *)0x68521);
        break;
    case 17:
        var_r3 = (unsigned char *) ((void *)0x68523);
        break;
    }
    play_sound_effect((int)var_r3, boss6_type2 + 0x38, 0, 1);
    ((TBoss6Type2 *)boss6_type2)->destroy_part(0xD);
}

}

void TBoss6Type2::update_zako_spawn_timer() {
    s32 temp_r0;

    if (((s32) *(s32 *)&this->unk_504 == 0) && (this->turn_toward_target_position() == 0)) {
        *(s32 *)&this->unk_504 = 1;
    }
    update_zako();
    temp_r0 = this->m_460 - 1;
    this->m_460 = temp_r0;
    if (temp_r0 < 0) {
        set_action_state((void *)0x22);
    }
}

void TBoss6Type2::send_state_action() {
    if ((s32) this->m_460 == 0) {
        switch (this->m_374) {
        case 6:
            this->m_46c = 0;
            send_action_packet((s8)((void*)(0xC)));
            return;
        case 9:
            this->m_46c = 1;
            send_action_packet((s8)((void*)(0xC)));
            return;
        default:
            send_state_action_packet();
            break;
        }
    }
}

void TBoss6Type2::reset_timers_and_spawn_particle() {
    S_802BF6CC *arg0 = (S_802BF6CC *)this;
    arg0->f45C = 0x4B;
    this->m_460 = 0x4B;
    arg0->f504 = 0;
    TBoss6Type2__sub_802BB7C0(arg0);
    switch (this->m_374) {
    case 9:
    case 10:
    case 11:
        ((TBoss6Type2 *)arg0)->spawn_particle_slot(0xD);
        break;
    }
}

void TBoss6Type2::update_zako_phase() {
    s32 temp_r0;

    if (((s32) *(s32 *)&this->unk_504 == 0) && (this->turn_toward_target_position() == 0)) {
        *(s32 *)&this->unk_504 = 1;
    }
    update_zako();
    temp_r0 = this->m_460 - 1;
    this->m_460 = temp_r0;
    if (temp_r0 < 0) {
        set_action_state((void *)0xC);
    }
}
void TBoss6Type2::init_attack_params() {

    *(s32 *)&this->unk_45C = 0x4B;
    this->m_460 = 0x4B;
    *(s32 *)&this->unk_504 = 0;
    switch (this->m_374) {
    case 4:
        this->m_46c = 0;
        break;
    case 5:
        this->m_46c = 1;
        break;
    default:
        this->m_46c = 0;
        break;
    }
    TBoss6Type2__sub_802BB7C0(this);
    switch ((s32) this->m_374) {
    case 5:
        spawn_particle_slot(0xD);
        break;
    }
}

void TBoss6Type2__sub_802BF834(u8 *boss6_type2) {
    s32 temp_r0;
    if (((s32) ((TBoss6Type2 *)boss6_type2)->m_460 == (s32) (*(s32 *)((s8 *)boss6_type2 + 0x45C) - 0x1E)) && ((u16) ((TBoss6Type2 *)boss6_type2)->m_466 != 0xFFFF)) {
        play_sound_effect(0x4006A10A, boss6_type2 + 0x38, 0, 1);
        play_sound_effect(0x69E27, boss6_type2 + 0x38, 0, 1);
        spawn_particle_effect_with_flags((boss6_type2 + 0x62C), 0x223, 0x40);
    }
    temp_r0 = ((TBoss6Type2 *)boss6_type2)->m_460 - 1;
    ((TBoss6Type2 *)boss6_type2)->m_460 = temp_r0;
    if (temp_r0 < 0) {
        ((TBoss6Type2 *)boss6_type2)->set_action_state((void *)0x22);
    }
}

void TBoss6Type2::check_state_0x460_eq0() { if (this->m_460 == 0) { send_state_action_packet(); } }
void TBoss6Type2__sub_802BF904(void* p) { *(s32*)((char*)p + 0x45c) = 45; *(s32*)((char*)p + 0x460) = 45; }
void TBoss6Type2::tick_action_timer() {
    s32 temp_r0;

    temp_r0 = this->m_460 - 1;
    this->m_460 = temp_r0;
    if (temp_r0 < 0) {
        set_action_state((void *)0x22);
    }
}
void TBoss6Type2::pick_next_zako() {
    if ((s32) this->m_460 == 0) {
        this->m_466 = TBoss6Type2__sub_802BB694();
        if (this->m_466 == 0xFFFF) {
            update_action_state();
            return;
        }
        send_action_packet((s8)((void*)((void*)(3))));
    }
}

extern "C" {

void TBoss6Type2::init_timer_and_play_sound() {
    u8 *arg0 = (u8 *)this;
  if (((s8) lbl_805D6754) == 0)
  {
    lbl_805D6754 = 1;
    lbl_805D6750 = (s32) (lbl_805DE4DC / lbl_805DE3F4);
  }
  *((0, (s32 *) (((s8 *) arg0) + 0x460))) = (*((s32 *) (((s8 *) arg0) + 0x45C)) = (s32) lbl_805D6750);
  play_sound_effect(0x69126, arg0 + 0x38, 0, 1);
}

void TBoss6Type2__sub_802BFA1C(u8 *arg0) {
    s32 temp_r0;

    play_persistent_sound((s32)(0x4006A612), (const void *)((s32)arg0), (const Vec *)((u32)(arg0 + 0x38)), 0, 1);
    temp_r0 = ((TBoss6Type2 *)arg0)->m_460 - 1;
    ((TBoss6Type2 *)arg0)->m_460 = temp_r0;
    if (temp_r0 < 0) {
        play_sound_effect(0x40069E13, arg0 + 0x38, 0, 1);
        ((TBoss6Type2 *)arg0)->set_action_state((void *)2);
    }
}

}

void TBoss6Type2::reset_state_timers() {
    s32 temp_r0;

    temp_r0 = *(s32 *)((s8 *)this + 0x4EC);
    *(s32 *)&this->unk_45C = temp_r0;
    this->m_460 = temp_r0;
    TBoss6Type2__sub_802BB768();
}
void TBoss6Type2::tick_timer_460() {
    s32 temp_r0;

    temp_r0 = this->m_460 - 1;
    this->m_460 = temp_r0;
    if (temp_r0 < 0) {
        set_action_state((void *)0x22);
    }
}
void TBoss6Type2::select_attack_state() {
    if ((s32) this->m_460 == 0) {
        if (TBoss6Type2__sub_802BA9E4() != 0) {
            send_action_packet((s8)((void*)(0xD)));
            return;
        }
        if ((get_phase() == 0xD) && (is_ready_to_attack() != 0)) {
            this->m_464 = is_falz_ready();
            send_action_packet((s8)((void*)(0x18)));
            return;
        }
        if (TBoss6Type2__sub_802BA944(this) != 0) {
            send_action_packet((s8)((void*)(0xE)));
            return;
        }
        if (get_phase() == 0xD) {
            this->m_428 = pick_random_other_index();
            this->m_430 = choose_next_index();
            send_action_packet((s8)((void*)(1)));
            return;
        }
        send_action_packet((s8)((void*)(2)));
    }
}

void TBoss6Type2__sub_802BFBE4(void* p) { *(s32*)((char*)p + 0x45c) = 90; *(s32*)((char*)p + 0x460) = 90; }

}
