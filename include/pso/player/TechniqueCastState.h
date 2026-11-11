#ifndef PSO_PLAYER_TECHNIQUECASTSTATE_H
#define PSO_PLAYER_TECHNIQUECASTSTATE_H

#include "types.h"

// One target of a technique cast: an entity id and a signed halfword.
struct TechniqueTarget {
    u16 entity_id;
    s16 unknown_a2;
};

// TObjPlayer+0x428: the technique being cast, its targets, and the per-technique
// level tables.
struct TechniqueCastState {
    u8 level;                     // 0x00
    u8 slot;                      // 0x01
    u8 unk_02[2];
    s16 technique;                // 0x04
    s16 target_count;             // 0x06: clamped to 0..10
    u8 unk_08[0x18];
    TechniqueTarget targets[10];  // 0x20
    u8 levels[0x14];              // 0x48: indexed by technique
    u8 unk_5C[0x28];

    void set_technique(s16 technique);
    void set_level(u8 level);
    u8 get_valid_technique();
    s32 check_technique_level(s32 technique, u8 level);
    void set_target_count(s16 count);
    TechniqueTarget *get_targets();
};

#endif
