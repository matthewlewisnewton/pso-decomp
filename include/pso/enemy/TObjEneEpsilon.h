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
