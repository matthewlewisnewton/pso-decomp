#ifndef PSO_BOSS_BOSS7STATICTABLES_H
#define PSO_BOSS_BOSS7STATICTABLES_H

#include "pso/object/TObjMotion.h"

struct Ent_802E88F8;
struct Boss7PatternTables {
    Ent_802E88F8 *actions[4];
    Vec *positions[4];
    s32 *angles[4];
};

// A bounded view of the original data block, shared with the constructor.
// The remaining resource/action records and vtable still belong to the
// original data split; this declaration does not define their storage.
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

extern "C" Boss7ConstructorTables lbl_804E3BF0;

#endif
