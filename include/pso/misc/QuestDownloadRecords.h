#ifndef PSO_QUEST_DOWNLOAD_RECORDS_H
#define PSO_QUEST_DOWNLOAD_RECORDS_H

#include "types.h"
#include "stddef.h"

struct QuestDownloadTextNode;
struct QuestDownloadEntryNode;
struct QuestDownloadItemNode;

// Dictionary record referenced by slot+0. All-ones denotes unavailable
// tokens; NULL and a dictionary pointer are the other observed native states.
struct QuestDownloadMatchToken {
    u8 a;
    u8 b;
    u8 off;
    u8 d;
};

// Source records are the distinct sixteen-byte item objects produced by CF84.
// The four-byte slot+0 match tokens are a separate format.
struct QuestDownloadEntryPrefix {
    s16 off;
    u8 a;
    u8 b;
    QuestDownloadItemNode *src;
};
struct QuestDownloadEntryNode {
    QuestDownloadEntryPrefix prefix;
    u16 x8;
    u16 xa;
    QuestDownloadEntryNode *next;
};

#pragma push
#pragma options align=packed
struct QuestDownloadTextHead {
    char text[5];
    u8 length;
    u8 kind;
    s32 source;
    u16 id;
    u16 attribute;
};
#pragma pop

struct QuestDownloadTextContinuation { char text[15]; };
union QuestDownloadTextPayload {
    QuestDownloadTextHead head;
    QuestDownloadTextContinuation continuation;
};
struct QuestDownloadTextNode {
    u8 flags;
    QuestDownloadTextPayload payload;
    QuestDownloadTextNode *next;
};

struct QuestDownloadSegment {
    s16 off;
    u8 reserved_2[2];
    u8 a;
    u8 b;
    u8 reserved_6[2];
    QuestDownloadSegment *next;
};
struct QuestDownloadItemNode {
    s16 off;
    u8 a;
    u8 b;
    s32 x4;
    u16 c;
    u8 reserved_a[2];
    QuestDownloadItemNode *next;
};
struct QuestDownloadQueueNode {
    QuestDownloadEntryNode *entry;
    u16 score;
    u8 reserved_6[2];
    QuestDownloadTextNode *text;
    QuestDownloadQueueNode *next;
};

#define QUEST_DOWNLOAD_MATCH_TOKENS_UNAVAILABLE ((const QuestDownloadMatchToken *)0xFFFFFFFFU)

struct QuestDownloadSlot {
    const QuestDownloadMatchToken *tokens;
    QuestDownloadItemNode *items;
    QuestDownloadEntryNode *entryHead;
    QuestDownloadTextNode *textHead;
    s32 timer;
    s8 x14;
    s8 x15;
    s8 x16;
    s8 x17;
    s8 x18;
    s8 x19;
    u8 reserved_1a[2];
};

// Shared native request created by the frontend and consumed by byte-page/cache APIs.
struct Req_803EEF2C {
    char *name;
    s16 len;
    u8 pad6;
    u8 x7;
    u8 x8;
    u8 pad9[3];
    u8 *text;
};

#define QUEST_RECORD_CHECK(name, condition) typedef char name[(condition) ? 1 : -1]
QUEST_RECORD_CHECK(QuestEntryPrefix_extent, sizeof(QuestDownloadEntryPrefix) == 8);
QUEST_RECORD_CHECK(QuestEntryPrefix_offset, offsetof(QuestDownloadEntryNode, prefix) == 0);
QUEST_RECORD_CHECK(QuestEntry_extent, sizeof(QuestDownloadEntryNode) == 0x10);
QUEST_RECORD_CHECK(QuestEntry_source_offset, offsetof(QuestDownloadEntryNode, prefix.src) == 4);
QUEST_RECORD_CHECK(QuestEntry_next_offset, offsetof(QuestDownloadEntryNode, next) == 0xC);
QUEST_RECORD_CHECK(QuestTextHead_extent, sizeof(QuestDownloadTextHead) == 15);
QUEST_RECORD_CHECK(QuestText_extent, sizeof(QuestDownloadTextNode) == 0x14);
QUEST_RECORD_CHECK(QuestText_payload_offset, offsetof(QuestDownloadTextNode, payload) == 1);
QUEST_RECORD_CHECK(QuestText_next_offset, offsetof(QuestDownloadTextNode, next) == 0x10);
QUEST_RECORD_CHECK(QuestText_source_offset, offsetof(QuestDownloadTextNode, payload.head.source) == 8);
QUEST_RECORD_CHECK(QuestSegment_extent, sizeof(QuestDownloadSegment) == 0xC);
QUEST_RECORD_CHECK(QuestItem_extent, sizeof(QuestDownloadItemNode) == 0x10);
QUEST_RECORD_CHECK(QuestQueue_extent, sizeof(QuestDownloadQueueNode) == 0x10);
QUEST_RECORD_CHECK(QuestToken_extent, sizeof(QuestDownloadMatchToken) == 4);
QUEST_RECORD_CHECK(QuestSlot_extent, sizeof(QuestDownloadSlot) == 0x1C);
QUEST_RECORD_CHECK(QuestSlot_tokens_offset, offsetof(QuestDownloadSlot, tokens) == 0);
QUEST_RECORD_CHECK(QuestSlot_items_offset, offsetof(QuestDownloadSlot, items) == 4);
QUEST_RECORD_CHECK(QuestSlot_entry_offset, offsetof(QuestDownloadSlot, entryHead) == 8);
QUEST_RECORD_CHECK(QuestSlot_text_offset, offsetof(QuestDownloadSlot, textHead) == 0xC);
QUEST_RECORD_CHECK(QuestRequest_extent, sizeof(Req_803EEF2C) == 0x10);
QUEST_RECORD_CHECK(QuestRequest_name, offsetof(Req_803EEF2C, name) == 0);
QUEST_RECORD_CHECK(QuestRequest_pad6, offsetof(Req_803EEF2C, pad6) == 6);
QUEST_RECORD_CHECK(QuestRequest_len, offsetof(Req_803EEF2C, len) == 4);
QUEST_RECORD_CHECK(QuestRequest_kind, offsetof(Req_803EEF2C, x7) == 7);
QUEST_RECORD_CHECK(QuestRequest_extra, offsetof(Req_803EEF2C, x8) == 8);
QUEST_RECORD_CHECK(QuestRequest_text, offsetof(Req_803EEF2C, text) == 0xC);
#undef QUEST_RECORD_CHECK

extern "C" {
// Defined by QuestDownloadBuffers.cpp. The pointed-to nodes are not in this array.
extern QuestDownloadSlot quest_download_slot_chain_table[80];
s32 TQuestVmDownLoadServer__sub_803EF208(Req_803EEF2C *);
s32 TQuestVmDownLoadServer__sub_803EF538(Req_803EEF2C *);
s32 calc_entry_cost__22TQuestVmDownLoadServerFPvPv(QuestDownloadEntryPrefix *, QuestDownloadEntryPrefix *);
s32 TQuestVmDownLoadServer__sub_803ED84C(QuestDownloadEntryNode *, s32, s32);
s32 calc_item_entry_cost__22TQuestVmDownLoadServerFUcUcl(QuestDownloadEntryPrefix *, u8, u8, s32);
s32 count_chain_nodes__22TQuestVmDownLoadServerFv(QuestDownloadTextNode *node);
void free_node_list__22TQuestVmDownLoadServerFv(QuestDownloadTextNode *node);
void push_download_entry__22TQuestVmDownLoadServerFPl(void *node);
QuestDownloadTextNode *advance_nodes__22TQuestVmDownLoadServerFPvi(QuestDownloadTextNode *, s32);
QuestDownloadTextNode *TQuestVmDownLoadServer__sub_803EB878(QuestDownloadTextNode *);
QuestDownloadTextNode *detach_node_chain__22TQuestVmDownLoadServerFPv(QuestDownloadTextNode *);
}

#endif
