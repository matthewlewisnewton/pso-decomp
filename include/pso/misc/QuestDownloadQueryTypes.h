#ifndef PSO_QUEST_DOWNLOAD_QUERY_TYPES_H
#define PSO_QUEST_DOWNLOAD_QUERY_TYPES_H

#include "types.h"
#include "stddef.h"

struct QuestDownloadQueryEntry {
    u8 a;
    u8 b;
    u8 c;
    u8 pad;
    u16 key;
};

// 803F03B4 writes six-byte entries and stops at index 32.
struct QuestDownloadQueryResult {
    s16 len;
    u32 x4;
    s16 len2;
    s16 xa;
    s16 count;
    QuestDownloadQueryEntry entries[32];
};

// The leading bytes have no observed direct access through this symbol.
// Slots follow this object in native storage; they are separate objects.
struct QuestDownloadWorkspace {
    u8 leading[0x8C0];
    QuestDownloadQueryResult result;
};

extern "C" QuestDownloadWorkspace lbl_80595008;

typedef char QuestQueryEntry_extent[sizeof(QuestDownloadQueryEntry) == 6 ? 1 : -1];
typedef char QuestQueryResult_entries[offsetof(QuestDownloadQueryResult, entries) == 14 ? 1 : -1];
typedef char QuestQueryResult_extent[sizeof(QuestDownloadQueryResult) == 0xD0 ? 1 : -1];
typedef char QuestWorkspace_result[offsetof(QuestDownloadWorkspace, result) == 0x8C0 ? 1 : -1];
typedef char QuestWorkspace_extent[sizeof(QuestDownloadWorkspace) == 0x990 ? 1 : -1];

#endif
