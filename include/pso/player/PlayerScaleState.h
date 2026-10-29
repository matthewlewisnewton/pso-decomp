#ifndef PSO_PLAYER_PLAYERSCALESTATE_H
#define PSO_PLAYER_PLAYERSCALESTATE_H

#include "types.h"

struct PlayerScaleState {
    // Bit 0: the player is drawn at scalar times its size.
    int is_scaled();
    f32 get_scalar();

    u16 actor_id;
    u16 padding;
    s32 flags;
    f32 scalar;
    f32 model[3];
    f32 camera_position[3];
    f32 camera_target[3];
};

struct PlayerShrinkPacket {
    u8 command;
    u8 size;
    u16 actor_id;
    f32 scalar;
};

struct PlayerRestoreSizePacket {
    u8 command;
    u8 size;
    u16 actor_id;
};

#endif
