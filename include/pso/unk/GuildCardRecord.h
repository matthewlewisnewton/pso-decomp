#ifndef PSO_UNK_GUILDCARDRECORD_H
#define PSO_UNK_GUILDCARDRECORD_H

#include "types.h"
#include <stddef.h>

// inferred: one com-card list record (0xBC bytes). TLobby keeps the selected card and an
// 8-entry list; serial comes from a running counter (init_player_entry__6TLobbyFPvPv).
struct GuildCardRecord {
    s32 id;
    s32 serial;
    char name[0x11];
    char s19[0x11];
    char s2A[0x11];
    char s3B[0x11];
    struct { u8 bytes[8]; } f4C;
    s32 f54;
    struct { u8 bytes[0x64]; } ext;

    GuildCardRecord();
    s32 get_id() const;
    s32 get_serial() const;
    char *get_name();
    char *get_text_19();
    char *get_text_2a();
    char *get_text_3b();
    GuildCardRecord *copy_from(const GuildCardRecord *source);
};

typedef char GuildCardRecord_size[sizeof(GuildCardRecord) == 0xBC ? 1 : -1];
typedef char GuildCardRecord_ext_offset[offsetof(GuildCardRecord, ext) == 0x58 ? 1 : -1];

extern GuildCardRecord selected_guild_card_record;
GuildCardRecord *get_selected_guild_card_record();

#endif
