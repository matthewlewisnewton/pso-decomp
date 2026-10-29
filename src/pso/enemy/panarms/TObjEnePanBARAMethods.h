#ifndef PSO_ENEMY_PANARMS_TOBJENEPANBARAMETHODS_H
#define PSO_ENEMY_PANARMS_TOBJENEPANBARAMETHODS_H

// Source-private definitions, included only by TObjEnePanarms.cpp.
#pragma push
s32 TObjEnePanBARA::fn_800E2FB4() { return state == 9 || state == 11; }
#pragma pop
#pragma push
int TObjEnePanBARA::find_nearest_enemy_with_flag_alt_target(Vec *direction, f32 radius) {
    u16 target;
    actorFlags |= 0x02000000;
    target = find_nearest_hittable_enemy__10TObjPlayerFiPvf(this, direction, radius);
    actorFlags &= ~0x02000000;
    return target;
}
#pragma pop
#pragma push
#pragma fp_contract on
void TObjEnePanBARA::set_random_action_timer(int minimum, int range) {
    action_timer = (s32)((f32)range * random_ratio() + (f32)minimum);
}
#pragma pop
#pragma push
s32 TObjEnePanBARA::is_below_half_hp() {
    s32 result = 0;
    if (part_index == 0 && other_half->fn_800DFB44() == 0 && m_3c0 == 0 && hp <= initial_hp / 2) result = 1;
    return (u8)result;
}
#pragma pop
#pragma push
s32 TObjEnePanBARA::fn_800E2E68() { return state == 14; }
#pragma pop
#pragma push
s32 TObjEnePanBARA::fn_800E2E54() { return state == 13; }
#pragma pop
#pragma push
s32 TObjEnePanBARA::check_can_attack() {
    s32 result = 0;
    if (m_3c4 == 0 && other_half->fn_800DFB44() != 0) result = 1;
    return (u8)result;
}
#pragma pop
#pragma push
s32 TObjEnePanBARA::is_phase_12() {
    return (u8)(state == 12);
}
#pragma pop

#endif
