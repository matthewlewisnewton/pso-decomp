#ifndef PSO_UNK_TEXT_8020A768_H
#define PSO_UNK_TEXT_8020A768_H

#include "types.h"

struct SpawnRecord_8020A9C4 {
    s16 type;
    u16 flags;
    s16 index;
    s16 children;
    u16 reserved;
    s16 actor_id;
    s16 room;
    s16 wave;
    u8 placement[0x48 - 0x10];
};

extern "C" void reserve_enemy_set_actor_ids(SpawnRecord_8020A9C4 *entries, s32 count, s32 area);

s32 load_enemy_set_file(s32 idx, s32 arg1);
void load_map_set_data(s32 idx, s32 arg1);
s32 load_object_set_file(s32 idx, s32 arg1);

#endif
