#ifndef PSO_PROTOCOL_BOSS_ACTION_PACKET_H
#define PSO_PROTOCOL_BOSS_ACTION_PACKET_H

#include "pso/protocol/protocol_types.h"
#include <stddef.h>

// These commands use the common four-byte wire header. Its client_id word
// identifies the boss entity, rather than a player slot.
struct BossActionPacket {
    G_ClientIDHeader header;
    s16 action;
    s16 sequence;
};
struct BossTargetActionPacket {
    BossActionPacket action;
    s32 target_entity_id;
};
struct DragonActionPacket {
    BossTargetActionPacket target;
    f32 x;
    f32 z;
};
struct GolDragonActionPacket {
    DragonActionPacket dragon;
    s8 mode;
};

typedef char BossActionPacketSize[sizeof(BossActionPacket) == 8 ? 1 : -1];
typedef char BossTargetActionPacketSize[sizeof(BossTargetActionPacket) == 12 ? 1 : -1];
typedef char DragonActionPacketSize[sizeof(DragonActionPacket) == 20 ? 1 : -1];
typedef char GolDragonActionPacketSize[sizeof(GolDragonActionPacket) == 24 ? 1 : -1];
typedef char BossActionOffset[offsetof(BossActionPacket, action) == 4 ? 1 : -1];
typedef char BossSequenceOffset[offsetof(BossActionPacket, sequence) == 6 ? 1 : -1];
typedef char BossTargetOffset[offsetof(BossTargetActionPacket, target_entity_id) == 8 ? 1 : -1];

// Receive buffers may contain encoded bytes rather than live packet objects.
// Conversion accepts aligned packet storage; send also accepts the typed records
// above. The float coordinates and Gol Dragon mode are not byte-swapped here.
extern "C" {
void send_boss_action_6x12(void *packet);
void bswap_boss_action_6x12(void *packet);
void init_boss_action_6x12(void *packet);
void bswap_boss_action_6x11(void *packet);
void bswap_boss_action_6x10(void *packet);
void bswap_boss_action_6xAA(void *packet);
void bswap_boss_action_6xA9(void *packet);
void send_boss_action_6xA9(void *packet);
void send_boss_action_6xAA(void *packet);
void send_boss_action_6xA8(void *packet);
void bswap_boss_action_6xA8(void *packet);
}

#endif
