#ifndef PSO_ENEMY_TOBJENEEPSILON_H
#define PSO_ENEMY_TOBJENEEPSILON_H

#include "types.h"
#include "pso/misc/RenderFadeState.h"
#include "pso/enemy/TObjEneDD_ST.h"

struct TObjEneEpsilon : public TObjEneDD_ST {
    TObjEneEpsilon(TObject *parent);
    virtual ~TObjEneEpsilon();
    int copy_position(void *);
    s32 update_movement_status();
    s32 is_target_in_attack_range();
    u8 unk_374[8];
    f32 field_37c;
    u8 unk_380[0xC];
    u16 m_38c;
    u8 unk_38E[0x2];
    u32 m_390;
    u8 unk_394[0xC];
    f32 m_3a0;
    f32 field_3a4;
    f32 field_3a8;
    f32 field_3ac;
    u8 unk_3b0[0x10];
    RenderFadeState camera_fades[4];
    void fire_attack_a(s32 arg1, s32 arg2, f32 farg0);
    void fire_attack_b(s32 arg1, s32 arg2, f32 farg0);
    void fire_attack_c(s32 arg1, s32 arg2, f32 farg0);
    void update_angle(s32 arg1);
    s32 update_death_check();
};

typedef char EpsilonSize[sizeof(TObjEneEpsilon) == 0x430 ? 1 : -1];
extern "C" void *__ct__14TObjEneEpsilonFP7TObject(void *, TObject *);

#endif
