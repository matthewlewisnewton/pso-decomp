#ifndef PSO_BOSS_TBOSS8DRAGON_80067034_H
#define PSO_BOSS_TBOSS8DRAGON_80067034_H

#include "types.h"
#include <dolphin/mtx/GeoTypes.h>
#include "pso/boss/EffectGeometryParameters.h"

// Switch lists walked by sub_80067074 / sub_800670E0. flags is the word the
// callers test; x and z sit at 8 and 0x10, which is what the distance check loads.
struct XzSwitchNode {
    u32 flags;
    u32 pad_4;
    f32 x;
    f32 y;
    f32 z;
};

// pos is a Vec (object position at +0x38, or a part position). The squared
// reach comes from EffectGeometryParameters::field_8, not from a TBoss8Dragon.
s32 is_within_xz_distance(Vec *pos, XzSwitchNode *node, f32 limit);
f32 calc_sq_offset(EffectGeometryParameters *params, f32 extra);

extern "C" {
void TBoss8Dragon__sub_80067074(s32 arg0, s32 arg1);
void TBoss8Dragon__sub_800670E0(s32 arg0, s32 arg1);
}

// --- C functions defined in TBoss8Dragon_80067034.cpp ---
extern "C" {
void TBoss8Dragon__sub_80067074(s32 arg0, s32 arg1);
void TBoss8Dragon__sub_800670E0(s32 arg0, s32 arg1);
}
// --- end of C functions

#endif
