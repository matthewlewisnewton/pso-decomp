#ifndef PSO_ENEMY_TOBJENEEPSILON_H
#define PSO_ENEMY_TOBJENEEPSILON_H

#include "types.h"
#include "pso/enemy/TObjEneDD_ST.h"

struct TObjEneEpsilon : public TObjEneDD_ST {
    virtual ~TObjEneEpsilon();
    s32 update_movement_status();
    s32 is_target_in_attack_range();
    u8 unk_374[0x18];
    u16 m_38c;
    u8 unk_38E[0x2];
    u32 m_390;
    u8 unk_394[0xC];
    f32 m_3a0;
    void* m_3c0;
    void fire_attack_a(s32 arg1, s32 arg2, f32 farg0);
    void fire_attack_b(s32 arg1, s32 arg2, f32 farg0);
    void fire_attack_c(s32 arg1, s32 arg2, f32 farg0);
    void update_angle(s32 arg1);
    s32 update_death_check();
};

#endif
