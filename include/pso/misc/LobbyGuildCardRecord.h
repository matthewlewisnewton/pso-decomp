#ifndef PSO_MISC_LOBBYGUILDCARDRECORD_H
#define PSO_MISC_LOBBYGUILDCARDRECORD_H

#include "types.h"
#include <stddef.h>

struct LobbyGuildCardRecord {
    LobbyGuildCardRecord();

    s32 id;
    s32 f4;
    char name[0x11];
    char s19[0x11];
    char s2A[0x11];
    char s3B[0x11];
    struct {
        u8 bytes[8];
    } f4C;
    s32 f54;
    struct {
        u8 bytes[0x64];
    } ext;
};

typedef char LobbyGuildCardRecord_size[sizeof(LobbyGuildCardRecord) == 0xBC ? 1 : -1];
typedef char LobbyGuildCardRecord_ext_offset[offsetof(LobbyGuildCardRecord, ext) == 0x58 ? 1 : -1];

extern "C" {
extern LobbyGuildCardRecord selected_guild_card_record;
}

#endif
