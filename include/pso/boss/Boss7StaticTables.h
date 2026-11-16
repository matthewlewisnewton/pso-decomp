#ifndef PSO_BOSS_BOSS7STATICTABLES_H
#define PSO_BOSS_BOSS7STATICTABLES_H

#include "pso/object/TObjMotion.h"

struct Ent_802E88F8;
struct BmlResourceDescriptor;
struct Boss7ResourceCallbacks {
    void (*load)();
    void (*unload)();
};
typedef char Boss7ResourceCallbacks_size[sizeof(Boss7ResourceCallbacks) == 8 ? 1 : -1];
struct Boss7PatternTables {
    Ent_802E88F8 *actions[4];
    Vec *positions[4];
    s32 *angles[4];
};

// The legacy native constructor addresses this contiguous linked data pool.
// Boss7DeRolLeCBehavior.cpp owns its real objects and compiler-generated vtable;
// this bounded address view remains at the existing constructor ABI boundary.
struct Boss7ConstructorTables {
    Vec scale;
    Vec joint_offsets[4];
    Boss7PatternTables patterns;
    u8 remaining_leading_tables[0x30];
    u8 movement_data[0xA0];
    TObjMotionAction first_action;
    u8 before_vtable[0x118];
    void *first_virtual_entry;
};
typedef char Boss7Patterns_offset[offsetof(Boss7ConstructorTables, patterns) == 0x3C ? 1 : -1];
typedef char Boss7ActionTable_offset[offsetof(Boss7ConstructorTables, first_action) == 0x13C ? 1 : -1];
typedef char Boss7Vtable_offset[offsetof(Boss7ConstructorTables, first_virtual_entry) == 0x264 ? 1 : -1];

extern "C" {
extern Vec lbl_804E3BF0;
extern Vec lbl_804E3BFC[4];
extern const Ent_802E88F8 *boss7_pattern_actions[4];
extern const Vec *boss7_pattern_positions[4];
extern const s32 *boss7_pattern_yaws[4];
extern TObjMotionAction boss7_motion_actions[17];
extern Boss7ResourceCallbacks lbl_804E3C5C[6];
extern BmlResourceDescriptor lbl_804E3D1C;
}

#endif
