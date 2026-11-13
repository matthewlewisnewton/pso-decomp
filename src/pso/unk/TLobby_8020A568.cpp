#include "types.h"
#include "pso/unk/TLobby_8020A568.h"
#include "pso/system/byteswap.h"
#include "pso/unk/TLobby.h"
#include "pso/unk/ChallengeEvent.h"

void TLobby__sub_8020A568(void* p) { bswap_32((u32 *)p); bswap_32((u32 *)((char*)p + 0x4)); bswap_32((u32 *)((char*)p + 0x8)); bswap_32((u32 *)((char*)p + 0xc)); }

void ChallengeRandomEvent::swap_endian() {
    bswap_32((u32 *)&id);
    bswap_16((u16 *)&flags);
    bswap_16((u16 *)&eventType);
    bswap_16((u16 *)&room);
    bswap_16((u16 *)&wave);
    bswap_16((u16 *)&minDelay);
    bswap_16((u16 *)&maxDelay);
    bswap_16((u16 *)&maxWaves);
    bswap_32((u32 *)&commandOffset);
}

void TLobby__sub_8020A618(void *arg0, void *arg1) {
    *(s32 *)((s8 *)arg0 + 0) = (s32) *(s32 *)((s8 *)arg1 + 0);
    *(s16 *)((s8 *)arg0 + 4) = (s16) *(s16 *)((s8 *)arg1 + 4);
    *(s16 *)((s8 *)arg0 + 6) = (s16) *(s16 *)((s8 *)arg1 + 6);
    *(s16 *)((s8 *)arg0 + 8) = (s16) *(s16 *)((s8 *)arg1 + 8);
    *(s16 *)((s8 *)arg0 + 0xA) = (s16) *(s16 *)((s8 *)arg1 + 0xA);
    *(s16 *)((s8 *)arg0 + 0xC) = (s16) *(s16 *)((s8 *)arg1 + 0xC);
    *(s16 *)((s8 *)arg0 + 0xE) = (s16) *(s16 *)((s8 *)arg1 + 0xE);
    *(u8 *)((s8 *)arg0 + 0x10) = (u8) *(u8 *)((s8 *)arg1 + 0x10);
    *(u8 *)((s8 *)arg0 + 0x11) = (u8) *(u8 *)((s8 *)arg1 + 0x11);
    *(s16 *)((s8 *)arg0 + 0x12) = (s16) *(s16 *)((s8 *)arg1 + 0x12);
    *(s32 *)((s8 *)arg0 + 0x14) = (s32) *(s32 *)((s8 *)arg1 + 0x14);
}

void ChallengeEventHeader::swap_endian() {
    bswap_32((u32 *)&commandOffset);
    bswap_32((u32 *)&eventOffset);
    bswap_32((u32 *)&eventCount);
}
