#ifndef PSO_UNK_CHALLENGEEVENT_H
#define PSO_UNK_CHALLENGEEVENT_H

#include "types.h"
#include <stddef.h>

// Challenge-mode event records the TLobby event-set loader reads.
struct ChallengeEventHeader {
    s32 commandOffset;
    s32 eventOffset;
    s32 eventCount;
    u32 format;

    void swap_endian();
};

struct ChallengeRandomEvent {
    s32 id;
    s16 flags;
    s16 eventType;
    s16 room;
    s16 wave;
    s16 minDelay;
    s16 maxDelay;
    u8 minEnemies;
    u8 maxEnemies;
    s16 maxWaves;
    s32 commandOffset;

    void swap_endian();
};

struct ChallengeEventCommand {
    u8 opcode;

    void append() const;
};

typedef char ChallengeEventHeader_size[sizeof(ChallengeEventHeader) == 0x10 ? 1 : -1];
typedef char ChallengeRandomEvent_size[sizeof(ChallengeRandomEvent) == 0x18 ? 1 : -1];
typedef char ChallengeRandomEvent_commandOffset[offsetof(ChallengeRandomEvent, commandOffset) == 0x14 ? 1 : -1];

#endif
