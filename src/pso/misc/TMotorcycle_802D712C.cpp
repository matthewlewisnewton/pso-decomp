#include "types.h"
#include "pso/misc/TMotorcycle_802D712C.h"
#include "pso/misc/TMotorcycle.h"

#pragma push
#pragma scheduling off
NpcAnimationBinding &NpcAnimationBinding::operator=(const NpcAnimationBinding &other) {
    motions = other.motions;
    actions = other.actions;
    default_action = other.default_action;
    mode2_action = other.mode2_action;
    debug_action_limit = other.debug_action_limit;
    return *this;
}

#pragma pop
extern "C" {

void *insert_slot_by_id__12TObjNpcEnemyFs();

void TMotorcycle::add_entry(s16 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1) {
    void *temp_r3;

    temp_r3 = insert_slot_by_id__12TObjNpcEnemyFs();
    if (temp_r3 != NULL) {
        *(s16 *)((s8 *)temp_r3 + 0) = arg0;
        *(s16 *)((s8 *)temp_r3 + 2) = 2;
        *(f32 *)((s8 *)temp_r3 + 4) = farg1;
        *(s32 *)((s8 *)temp_r3 + 8) = arg1;
        *(s32 *)((s8 *)temp_r3 + 0xC) = arg2;
        *(f32 *)((s8 *)temp_r3 + 0x10) = farg0;
        *(s32 *)((s8 *)temp_r3 + 0x14) = 0;
        *(s32 *)((s8 *)temp_r3 + 0x18) = 0;
        *(s16 *)((s8 *)temp_r3 + 0x1C) = 0;
        *(s16 *)((s8 *)temp_r3 + 0x1E) = 0;
        *(s16 *)((s8 *)temp_r3 + 0x20) = 0;
    }
}
}
