#ifndef PSO_QUEST_DOWNLOAD_RECORDS_H
#define PSO_QUEST_DOWNLOAD_RECORDS_H

#include "types.h"
#include "stddef.h"

struct QuestDownloadTextNode;
struct QuestDownloadEntryNode;
struct QuestDownloadItemNode;

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

struct QuestDownloadSlot {
    void *tokens;
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
QUEST_RECORD_CHECK(QuestSlot_extent, sizeof(QuestDownloadSlot) == 0x1C);
QUEST_RECORD_CHECK(QuestSlot_entry_offset, offsetof(QuestDownloadSlot, entryHead) == 8);
QUEST_RECORD_CHECK(QuestSlot_text_offset, offsetof(QuestDownloadSlot, textHead) == 0xC);
#undef QUEST_RECORD_CHECK

extern "C" {
// Backing storage remains provided by the original automatic BSS owner.
extern QuestDownloadSlot quest_download_slot_chain_table[80];
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
