#ifndef PSO_UNK_TEXT_8020E08C_H
#define PSO_UNK_TEXT_8020E08C_H

#include "types.h"

struct Saved_8020E08C {
    u16 id;
    s16 flags;
    s16 room;
    s16 wave;
};

struct Floor_8020E08C {
    s32 objects;
    s32 enemies;
    u32 objectPlacement;
    u32 enemyPlacement;
    Saved_8020E08C *objectRows;
    Saved_8020E08C *enemyRows;
};

extern "C" Floor_8020E08C TLobby__floor_enemy_group_table[18];

#endif
