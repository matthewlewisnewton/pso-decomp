#include "pso/enemy/TObjEneDD.h"
#include "pso/enemy/TObjEneDD_800BA754.h"

f32 TObjEneDD::calc_elapsed_scaled() {
    return 2.0f * (random_ratio() - 0.5f);
}

s32 TObjEneDD::vfunc_99() {
    // Keep the byte-normalized subtraction test: a direct bit test emits
    // a shorter rotate/mask instead of the original subtract/cntlzw sequence.
    return (u8)(((actorFlags & 0x10) - 0x10) == 0);
}

// The shared contact helpers still expose byte pointers at their ABI boundary.
// The actor storage and array stride come from CollisionBody, not a local view.
void TObjEneDD::vfunc_98() {
    for (s32 i = 0; i < body_count; i++) {
        set_collider_contact_low(reinterpret_cast<u8 *>(&bodies[i]));
    }
}

void TObjEneDD::vfunc_97() {
    for (s32 i = 0; i < body_count; i++) {
        set_collider_contact_high(reinterpret_cast<u8 *>(&bodies[i]));
    }
}

void TObjEneDD::vfunc_96() {
    vfunc_92();
    vfunc_93();
    actorFlags &= ~(0x04000000 | 0x00040000);
}
