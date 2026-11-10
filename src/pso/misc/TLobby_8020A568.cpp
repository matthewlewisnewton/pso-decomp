#include "types.h"
#include "pso/misc/TLobby_8020A568.h"
#include "pso/system/byteswap.h"
#include "pso/map/ChallengeEnemySet.h"

void TLobby__sub_8020A568(void* p) { bswap_32((u32 *)p); bswap_32((u32 *)((char*)p + 0x4)); bswap_32((u32 *)((char*)p + 0x8)); bswap_32((u32 *)((char*)p + 0xc)); }

void ChallengeRandomEvent::swap_endian() {
    bswap_32(reinterpret_cast<u32 *>(&id));
    bswap_16(reinterpret_cast<u16 *>(&flags));
    bswap_16(reinterpret_cast<u16 *>(&eventType));
    bswap_16(reinterpret_cast<u16 *>(&room));
    bswap_16(reinterpret_cast<u16 *>(&wave));
    bswap_16(reinterpret_cast<u16 *>(&minDelay));
    bswap_16(reinterpret_cast<u16 *>(&maxDelay));
    bswap_16(reinterpret_cast<u16 *>(&maxWaves));
    bswap_32(reinterpret_cast<u32 *>(&commandOffset));
}

// A mutable source keeps CodeWarrior's alternating loads and stores.
void TLobby__sub_8020A618(ChallengeRandomEvent *dst, ChallengeRandomEvent *src) {
    dst->id = src->id;
    dst->flags = src->flags;
    dst->eventType = src->eventType;
    dst->room = src->room;
    dst->wave = src->wave;
    dst->minDelay = src->minDelay;
    dst->maxDelay = src->maxDelay;
    dst->minEnemies = src->minEnemies;
    dst->maxEnemies = src->maxEnemies;
    dst->maxWaves = src->maxWaves;
    dst->commandOffset = src->commandOffset;
}

void ChallengeEventHeader::swap_endian() {
    bswap_32(reinterpret_cast<u32 *>(&commandOffset));
    bswap_32(reinterpret_cast<u32 *>(&eventOffset));
    bswap_32(reinterpret_cast<u32 *>(&eventCount));
}
