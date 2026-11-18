#ifndef PSO_PLAYER_PLAYERSCALESTATE_H
#define PSO_PLAYER_PLAYERSCALESTATE_H

#include "types.h"
#include "pso/system/FlagWord.h"

struct PlayerScaleCameraOffsets {
    PlayerScaleCameraOffsets *clear();
    f32 position[3];
    f32 target[3];
};

struct PlayerScaleState {
    PlayerScaleState *initialize();
    void reset();
    void set_scalar(f32 scale);
    void set_model_scale(f32 scale);

    // Bit 0: the player is drawn at scalar times its size.
    int is_scaled();
    f32 get_scalar();

    u16 actor_id;
    u16 padding;
    FlagWord flags;
    f32 scalar;
    f32 model[3];
    PlayerScaleCameraOffsets camera;
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
