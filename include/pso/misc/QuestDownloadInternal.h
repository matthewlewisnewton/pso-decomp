#ifndef PSO_QUEST_DOWNLOAD_INTERNAL_H
#define PSO_QUEST_DOWNLOAD_INTERNAL_H

// Shared native layouts, declarations and inline helpers for the three
// quest-download objects. See docs/evidence/quest-download-unit-completion.md.
#include "types.h"
#include "pso/misc/QuestDownloadScratch.h"
#include "pso/misc/QuestDownloadRecords.h"
#include "pso/misc/QuestDownloadQueryTypes.h"
#include "pso/misc/QuestDownloadCacheTypes.h"
#include "pso/misc/TQuestVmDownLoadServer_803E6970.h"
#include "pso/misc/TQuestVmDownLoadServer.h"

// Native input records: DC20 writes ch at +0 and len at +4, stride 8;
// 6B70 and sum_entry_sizes read the same signed length word.
struct QuestDownloadInputEntry {
    u16 ch;
    u16 reserved;
    s32 len;
};
typedef char QuestDownloadInputEntry_extent[sizeof(QuestDownloadInputEntry) == 8 ? 1 : -1];
typedef char QuestDownloadInputEntry_ch_offset[offsetof(QuestDownloadInputEntry, ch) == 0 ? 1 : -1];
typedef char QuestDownloadInputEntry_len_offset[offsetof(QuestDownloadInputEntry, len) == 4 ? 1 : -1];

union QuestDownloadPoolCell;
// A free cell links actual free members; allocation starts the new node lifetime.
struct QuestDownloadFreeLink { QuestDownloadFreeLink *next; };
union QuestDownloadPoolCell {
    QuestDownloadFreeLink free;
    QuestDownloadTextNode text;
    QuestDownloadEntryNode entry;
    QuestDownloadQueueNode queue;
    QuestDownloadSegment segment;
    QuestDownloadItemNode item;
};
typedef char QuestDownloadFreeLink_pointer[sizeof(QuestDownloadFreeLink) == 4 && offsetof(QuestDownloadFreeLink, next) == 0 && sizeof(s32) == sizeof(void *) ? 1 : -1];
typedef char QuestDownloadPoolCell_extent[sizeof(QuestDownloadPoolCell) == 0x14 ? 1 : -1];
#pragma push
#pragma dont_inline off
#pragma inline_depth(2)
// A tag selects the application placement form without redefining the runtime's
// reserved two-argument signature. Every site supplies its actual member storage.
enum QuestDownloadPoolPlacement { quest_download_pool_storage };
inline void *operator new(size_t, void *storage, QuestDownloadPoolPlacement) { return storage; }
#pragma pop

// 0x28-byte buffer. sub_803E9A74 loads one byte at this address plus the
// index (lbz). sub_803EDC20 writes the same bytes through lbl_805D78B8 /
// lbl_805D78BC (stb, then addi by 1) after those cursors are planted here.
struct RecoveredGlobal_803E6ACC_lbl_805A0470 {
    u8 bytes[0x28];
};

struct RecoveredGlobal_803E6ACC_lbl_805A05D0 {
    s32 value;
    u8 remaining[0xC4];
};

struct RecoveredGlobal_803E9F20_lbl_80595998 {
    s32 value;
    u8 remaining[0x8BC];
};

struct RecoveredGlobal_803E6ED0_lbl_805A05D0 {
    s32 value;
    u8 remaining[0xC4];
};

struct RecoveredGlobal_803E721C_lbl_8047E698 {
    s32 value;
    u8 remaining[0x1FC];
};

struct E_803E6F48 { u16 key; u8 val; u8 pad; };

typedef Req_803EEF2C Msg_803E92C0;

typedef Req_803EEF2C Msg_803E9348;

typedef QuestDownloadQueryEntry Item_803EA384;
typedef QuestDownloadQueryResult Hdr_803EA384;

struct Obj_803EA960 { u8 pad[2]; u8 type; };

struct File_803F09FC {
    s32 remain;
    s32 pos;
};

typedef Req_803EEF2C Msg_803E90A8;

struct Info_803F0138 {
    s16 id;
    s16 off;
    u8 pad4[8];
    u8 *p;
};

typedef QuestDownloadQueryEntry Ent_803F03B4;
typedef QuestDownloadQueryResult Out_803F0268;

struct Src_803EBD38 { u16 x0; u16 x2; u8 x4; u8 text[1]; };

// Unresolved native common-base views. These retain the existing exact accesses
// while the filename/cache/header owner is investigated. The separate exported
// extents and reviewed cache types do not establish these larger C++ objects.
struct Cache_803E840C {
    u8 name[0x44];
    QuestDownloadCacheEntry ents[128];
    QuestDownloadCachePage pages[10];
};

struct Buf_803E82AC {
    u8 name[0x3CBC];
    u8 hdr[0x400];
};

struct Out_803E8C2C { s16 a; s16 id; s16 len; s16 pre; u8 pad[4]; u8 *ent; };

typedef Req_803EEF2C Msg_803E9190;

struct Out_803E8B1C { s16 a; s16 id; u8 pad[8]; u8 *ent; };

extern "C" {

extern RecoveredGlobal_803E6ACC_lbl_805A0470 lbl_805A0470;
extern QuestDownloadInputEntry quest_download_entry_table[39];
typedef char QuestDownloadInputTable_extent[sizeof(quest_download_entry_table) == 0x138 ? 1 : -1];
extern RecoveredGlobal_803E6ACC_lbl_805A05D0 lbl_805A05D0;
extern s32 lbl_805D7848;
extern u8 *lbl_805D78B8;
extern u8 *lbl_805D78BC;
extern s32 lbl_805D78C0;
extern QuestDownloadInputEntry *lbl_805D78C4;
extern QuestDownloadInputEntry *lbl_805D78C8;
extern s32 *quest_download_buffer_ptr;
extern s32 *lbl_805D78D0;
extern s32 *quest_download_buffer_start;
extern s32 *quest_vm_download_buffer_end;
extern s32 quest_download_match_length_limit;
extern s32 quest_download_server_state;
extern s32 lbl_805D7904;
extern char quest_vm_download_server_file_info[0x44];
extern s32 lbl_805D78F8;
extern u8 lbl_80591EC8[0x2000];
extern QuestDownloadCachedNameIndex lbl_80593EC8;
extern s8 lbl_805D7868;

extern const u8 lbl_8047F8B8[0x100];
extern RecoveredGlobal_803E721C_lbl_8047E698 single_byte_to_jis_table;
s32 strcpy(void *, void *);
s32 dispatch_request_0x20__19TWindowKeyBoardSoftFll(void *, void *);
s32 dispatch_request_0x1c__19TWindowKeyBoardSoftFv();
extern s32 quest_download_initialized;
extern s32 lbl_805D7834;
extern s32 lbl_805D7908;
extern s32 lbl_805D790C;
extern s32 lbl_805E10D8;
extern s32 lbl_805E10E0;
extern s32 lbl_805D7888;
extern u16 quest_download_char_code_table[];

extern u8 quest_name_index_table[1024][4];
void __VIRetraceHandler(void);
s32 TQuestVmDownLoadServer__sub_803E93DC(void);
void TQuestVmDownLoadServer__sub_803E95BC(void);
u32 aram_read_thunk__22TQuestVmDownLoadServerFUli(void *handle, void *dst, s32 size);
QuestDownloadTextNode *detach_node_chain__22TQuestVmDownLoadServerFPv(QuestDownloadTextNode *p);
QuestDownloadTextNode *advance_nodes__22TQuestVmDownLoadServerFPvi(QuestDownloadTextNode *p, s32 n);
extern s32 lbl_805D78AC;
extern QuestDownloadFreeLink *lbl_805D78B0;
QuestDownloadTextNode *TQuestVmDownLoadServer__sub_803EB878(QuestDownloadTextNode *p);
void TQuestVmDownLoadServer__sub_803ECD1C(QuestDownloadQueueNode *p);
void TQuestVmDownLoadServer__sub_803ECD8C(QuestDownloadEntryNode *p);
void TQuestVmDownLoadServer__sub_803ECE5C(QuestDownloadSegment *p);
extern E_803E6F48 jis_to_single_byte_symbol_table[];
extern QuestDownloadFileCache quest_download_slot_table;
QuestDownloadEntryNode *insert_sorted_node__22TQuestVmDownLoadServerFPvPv(QuestDownloadEntryNode *arg0, QuestDownloadEntryNode *arg1);
int strncmp(const char *, const char *, u32);
extern s32 quest_download_name_search_lo;
extern s32 quest_download_name_search_hi;
QuestDownloadItemNode *TQuestVmDownLoadServer__sub_803ECF84(void);
QuestDownloadItemNode *build_item_list__22TQuestVmDownLoadServerFiPv(s32 arg0, Hdr_803EA384 *arg1);
void TQuestVmDownLoadServer__sub_803EADD4(QuestDownloadSlot *arg0, s32 arg1);
s32 TQuestVmDownLoadServer__sub_803EC95C(u16 *, u8 *, int);
s32 TQuestVmDownLoadServer__sub_803EB420(s32 arg0, s32 arg1, QuestDownloadTextNode *arg2, u16 *arg3);
extern u8 quest_download_keyword_table[];
char *strncpy(char *, const char *, u32);
s32 TQuestVmDownLoadServer__sub_803E8DA0(char *, Req_803EEF2C *, s32);
extern s32 lbl_805D7900;
s32 TQuestVmDownLoadServer__sub_803EEF2C(Req_803EEF2C *arg0);
void TQuestVmDownLoadServer__sub_803E8924(s32 id);
void TQuestVmDownLoadServer__sub_803EF8E0(u8 *p);
extern u32 lbl_805D7910;
extern File_803F09FC lbl_805D7914;
extern u8 lbl_80591AC4[];
extern s32 lbl_805D7820;
extern s32 quest_download_ask_header_size;
extern s32 quest_download_header_name_index_hi_count;
extern u8 *lbl_805D786C;
extern u8 *lbl_805D7870;
extern QuestDownloadCachedNameNode *lbl_805D7878;
extern s32 lbl_805D7874;
extern s32 lbl_805D78FC;
void append_message_text__22TQuestVmDownLoadServerFPviPvUc(u8 *arg0, s32 arg1, Msg_803E90A8 *arg2, u8 arg3);
u32 strlen(const char *);
extern s32 lbl_805D78A4;
extern s32 lbl_805D78EC;
s32 count_fitting_entries__22TQuestVmDownLoadServerFPv(QuestDownloadTextNode *arg0);
s32 TQuestVmDownLoadServer__sub_803EC71C(u16 *, u8 *, s32);

extern u16 lbl_805A0340[];
extern u8 *quest_download_text_write_ptr;
void TQuestVmDownLoadServer__sub_803EBA98(s32 arg0, QuestDownloadTextNode *arg1);
extern u16 lbl_805A02A8[];
extern s32 lbl_805D7898;
extern QuestDownloadTextNode *lbl_805D78A0;
extern s32 lbl_805D78E4;
extern s32 lbl_805D78E8;
extern s32 lbl_805D78F0;
u8 *get_cached_page__22TQuestVmDownLoadServerFi(s32 page);
s32 find_symbol_entry__22TQuestVmDownLoadServerFPvsPv(const char *name, s16 len, Info_803F0138 *out);
void DCInvalidateRange(void *, u32);
void ARQPostRequest(void *req, u32 owner, u32 type, u32 prio, u32 src, u32 dst, u32 len, void (*cb)(u8 *));
u32 OSGetTick(void);
u32 __OSBusClock : 0x800000F8;
void *memcpy(void *, const void *, u32);
void OSReport(const char *, ...);
void ARQRemoveRequest(void *);
extern u8 quest_download_aram_dma_buffer[];
extern const char aram_dma_timeout_message[];
extern u32 lbl_805D791C;
extern u32 lbl_805D7920;
extern u32 lbl_805D7924;
extern s32 quest_download_aram_dma_pending;
extern u32 lbl_805D792C;
void TQuestVmDownLoadServer__sub_803EB4D4(void);
void TQuestVmDownLoadServer__sub_803EC284(s32, s32);
extern s32 lbl_805D789C;
s32 TQuestVmDownLoadServer__sub_803EB7C0(QuestDownloadTextNode *arg0);
void release_node_chain__22TQuestVmDownLoadServerFPv(QuestDownloadItemNode *p);
s32 TQuestVmDownLoadServer__sub_803F03B4(u8 *data, Ent_803F03B4 *ents, s32 n, s32 *max);
s32 TQuestVmDownLoadServer__sub_803F0268(const char *name, s16 len, Out_803F0268 *out);
s32 TQuestVmDownLoadServer__sub_803E7390(u8 a, u8 b, u8 c);
extern const u8 lbl_805E10C8[8];
QuestDownloadSegment *TQuestVmDownLoadServer__sub_803E9A74(s32, s32, u8, u8);
void *TQuestVmDownLoadServer__sub_803ECF48(void);
void *TQuestVmDownLoadServer__sub_803E9FFC(s32 arg0, s32 arg1, QuestDownloadItemNode *t);
void *TQuestVmDownLoadServer__sub_803ECED0(void);
void *TQuestVmDownLoadServer__sub_803ECF0C(void);
extern QuestDownloadCachePage *file_page_cache_head;
s32 TQuestVmDownLoadServer__sub_803E8C2C(char *arg0, s16 arg1, Out_803E8C2C *arg2);
void TQuestVmDownLoadServer__sub_803EFF20(u8 *data, s32 a1, s32 a2, s32 *best, u8 *dst, s32 flags);
extern const char ask_header_signature[];
extern const s16 quest_download_lz_match_index_table[];
extern const QuestDownloadMatchToken quest_download_lz_match_entry_table[];
extern u8 lbl_8047F0F8[];
const QuestDownloadMatchToken *find_longest_match_entry__22TQuestVmDownLoadServerFPviPv(u8 *arg0, s32 arg1, s32 *arg2);
void build_message_packet__22TQuestVmDownLoadServerFPviPvUc(u8 *arg0, s32 arg1, Msg_803E9190 *arg2, u8 arg3);
s32 lookup_name_entry__22TQuestVmDownLoadServerFPvsPv(char *arg0, s16 arg1, Out_803E8B1C *arg2);
extern u8 lbl_8047E898[];
extern u16 lbl_8047E8A4[];
void TQuestVmDownLoadServer__sub_803EFCB4(u8 *data, s32 a1, s32 a2, s32 *cnt, s32 *total, u8 *buf, s32 flags);
extern u8 *lbl_805D7824;

typedef char RecoveredGlobal_803E6ACC_lbl_805A0470_size[sizeof(RecoveredGlobal_803E6ACC_lbl_805A0470) == 0x28 ? 1 : -1];
typedef char RecoveredGlobal_803E6ACC_lbl_805A05D0_size[sizeof(RecoveredGlobal_803E6ACC_lbl_805A05D0) == 0xC8 ? 1 : -1];

extern u8 lbl_8047F9B8[];
extern u8 *lbl_8047FBD4[];
s32 TQuestVmDownLoadServer__sub_803F06B8(const char *, s16, Out_803F0268 *);
extern s32 lbl_805D7880;
extern u8 lbl_805D7894[4];
extern u8 lbl_805E10D0[4];
#pragma push
#pragma dont_inline off
#pragma inline_depth(4)
inline s32 IsX_803E9FFC(u8 arg0) {
    if ((lbl_805D7888 - 1) <= 1U) {
        return 0;
    }
    switch (arg0) {
    case 0x9D:
    case 0xA1:
    case 0xA3:
    case 0xA5:
    case 0xA7:
    case 0xA9:
    case 0xC3:
    case 0xE3:
    case 0xE5:
    case 0xE7:
    case 0xEE:
    case 0xF2:
    case 0xF3:
        return 1;
    default:
        return 0;
    }
}
#pragma pop
#pragma push
#pragma dont_inline off
#pragma inline_depth(4)
inline s32 IsNameChar_803E9A74(u8 c) {
    if (c >= 0xA0) {
        return 0;
    }
    switch (c) {
    case 0x20:
    case 0x21:
    case 0x2C:
    case 0x2E:
    case 0x3A:
    case 0x3B:
    case 0x3F:
    case 0x98:
    case 0x9B:
    case 0x9C:
        return 1;
    default:
        return 0;
    }
}
#pragma pop
#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline s32 display_convert_text(s32 start, const s32 &length, QuestDownloadTextNode *head, u16 *out) {
    QuestDownloadTextNode *part;
    s32 written;
    u16 *data;
    s32 count;
    s32 begin;
    data = out;
    count = length;
    begin = start;
    if (head == NULL || (head->flags & 0x80)) {
        return TQuestVmDownLoadServer__sub_803E6970(begin, count, data, 0);
    }
    part = head;
    written = 0;
    for (;;) {
        written += TQuestVmDownLoadServer__sub_803EC95C(data + written, reinterpret_cast<u8 *>(part) + 1, 6);
        if (!(part->flags & 1)) break;
        part = part->next;
    }
    data += written;
    return written + TQuestVmDownLoadServer__sub_803E6970((s32)(begin + head->payload.head.length),
        (s32)(count - head->payload.head.length), data, 0);
}
#pragma pop
#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline s32 display_group_count(QuestDownloadTextNode *p) {
    s32 n = 0;
    while (p != NULL) {
        while (p->flags & 1) p = p->next;
        p = p->next;
        n++;
    }
    return n;
}
#pragma pop
#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline QuestDownloadTextNode *display_next_group(QuestDownloadTextNode *p) {
    while (p->flags & 1) p = p->next;
    return p->next;
}
#pragma pop
#pragma push
#pragma opt_dead_assignments off
#pragma dont_inline off
#pragma inline_depth(1)
inline QuestDownloadTextNode *Detach_803EBBBC(QuestDownloadTextNode *p) {
    QuestDownloadTextNode *next;
    while (p->flags & 1) {
        p = p->next;
    }
    next = p->next;
    p->next = NULL;
    return next;
}
#pragma pop
#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
#pragma opt_propagation off
inline s32 count_encoded_download_input(QuestDownloadInputEntry *&entry) {
    QuestDownloadInputEntry *end = lbl_805D78C8;
    entry = end;
    s32 encoded = 0;
    QuestDownloadInputEntry *scan;
    for (scan = quest_download_entry_table; scan < end; scan++) {
        if (scan->ch & 0xFF00) encoded += 2;
        else encoded++;
    }
    return encoded;
}
#pragma pop
#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline u8 Upper_803EDDA4(s32 code) {
    u8 ch = code;
    if ((u8)code >= 0x61U && (u8)code <= 0x7aU) {
        ch -= 0x20;
    }
    return ch;
}
#pragma pop
#pragma push
#pragma dont_inline off
#pragma inline_depth(3)
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma opt_lifetimes off
inline size_t selection_workspace_address(const QuestDownloadWorkspace &workspace) {
    return reinterpret_cast<size_t>(&workspace);
}
#pragma pop
#pragma push
#pragma dont_inline off
#pragma inline_depth(3)
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma opt_lifetimes off
inline size_t borrow_selection_address(const size_t &address) {
    return address;
}
#pragma pop
#pragma push
#pragma dont_inline off
#pragma inline_depth(3)
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma opt_lifetimes off
inline s32 borrow_selection_limit(const s32 &limit) {
    return limit;
}
#pragma pop
#pragma push
#pragma dont_inline off
#pragma inline_depth(3)
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma opt_lifetimes off
inline s32 select_download_length(s32 start, s32 end) {
    s32 length = TQuestVmDownLoadServer::select_best_slot_entry(start, end, -1);
    return length;
}
#pragma pop
#pragma push
#pragma dont_inline off
#pragma inline_depth(2)
#pragma opt_propagation off
inline void append_candidate_items(QuestDownloadItemNode *item, QuestDownloadItemNode **tail) {
    while (*tail != NULL) {
        tail = &(*tail)->next;
    }
    *tail = item;
}
#pragma pop
#pragma push
#pragma dont_inline off
#pragma inline_depth(2)
#pragma opt_propagation off
inline void set_candidate_span(QuestDownloadSlot *slot, s32 maximum) {
    slot->x17 = maximum;
}
#pragma pop
#pragma push
#pragma dont_inline off
#pragma inline_depth(2)
#pragma opt_propagation off
struct QuestDownloadWorkspaceAddress {
    size_t address;
    QuestDownloadWorkspaceAddress(size_t base) : address(base) {}
};
#pragma pop
#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
#pragma opt_propagation off
struct DownloadDecoderState {
    u16 lead;
    DownloadDecoderState() : lead(0) {}
};
#pragma pop
#define QUEST_DOWNLOAD_LIST_SENTINEL_WORD 0xFFFFFFFFU
#define QUEST_DOWNLOAD_SEGMENT_SCAN_FAILED ((QuestDownloadSegment *)QUEST_DOWNLOAD_LIST_SENTINEL_WORD)
#define QUEST_DOWNLOAD_ENTRY_LIST_FAILED ((QuestDownloadEntryNode *)QUEST_DOWNLOAD_LIST_SENTINEL_WORD)
#define QUEST_DOWNLOAD_ITEM_LIST_UNAVAILABLE ((QuestDownloadItemNode *)QUEST_DOWNLOAD_LIST_SENTINEL_WORD)
#ifdef __MWERKS__
#define QUEST_WORKSPACE_SLOT(address, index) reinterpret_cast<QuestDownloadSlot *>((address) + sizeof(QuestDownloadWorkspace) + (index) * sizeof(QuestDownloadSlot))
#define QUEST_WORKSPACE_RESULT(address) reinterpret_cast<Out_803F0268 *>((address) + offsetof(QuestDownloadWorkspace, result))
#else
#define QUEST_WORKSPACE_SLOT(address, index) (&quest_download_slot_chain_table[index])
#define QUEST_WORKSPACE_RESULT(address) (&lbl_80595008.result)
#endif
u8 *get_cached_page__22TQuestVmDownLoadServerFi(s32 page);
void TQuestVmDownLoadServer__sub_803E95BC(void);
QuestDownloadSegment *TQuestVmDownLoadServer__sub_803E9A74(s32 beg, s32 end, u8 a, u8 b);
const QuestDownloadMatchToken *find_longest_match_entry__22TQuestVmDownLoadServerFPviPv(u8 *arg0, s32 arg1, s32 *arg2);
s32 TQuestVmDownLoadServer__sub_803E9F54(s32 arg0);
QuestDownloadEntryNode *insert_sorted_node__22TQuestVmDownLoadServerFPvPv(QuestDownloadEntryNode *arg0, QuestDownloadEntryNode *arg1);
s32 TQuestVmDownLoadServer__sub_803EA428(s32 start, s32 end);
void TQuestVmDownLoadServer__sub_803EB4D4(void);
QuestDownloadTextNode *advance_nodes__22TQuestVmDownLoadServerFPvi(QuestDownloadTextNode *p, s32 n);
s32 TQuestVmDownLoadServer__sub_803EB7C0(QuestDownloadTextNode *arg0);
s32 count_chain_nodes__22TQuestVmDownLoadServerFv(QuestDownloadTextNode *p);
QuestDownloadTextNode *TQuestVmDownLoadServer__sub_803EB878(QuestDownloadTextNode *p);
QuestDownloadTextNode *detach_node_chain__22TQuestVmDownLoadServerFPv(QuestDownloadTextNode *p);
void append_unique_node__22TQuestVmDownLoadServerFiPvPvPv(s32 start, QuestDownloadTextNode **headp, QuestDownloadTextNode **tailp, QuestDownloadTextNode *n);
QuestDownloadTextNode *get_next_node__22TQuestVmDownLoadServerFPv(QuestDownloadQueueNode *p);
void TQuestVmDownLoadServer__sub_803EBC88(s32 mode);
QuestDownloadTextNode *TQuestVmDownLoadServer__sub_803EBEFC(QuestDownloadEntryPrefix *a);
void TQuestVmDownLoadServer__sub_803EC09C(void);
s32 TQuestVmDownLoadServer__sub_803EDC20(u32 input_address);
u8 *TQuestVmDownLoadServer__sub_803EDDA4(u16 *start, u16 *end);
void TQuestVmDownLoadServer__sub_803EE2F4(s32 start, s32 end);
void TQuestVmDownLoadServer__sub_803EE580(s32 start, s32 length, QuestDownloadTextNode *text, QuestDownloadEntryNode *entries);
void TQuestVmDownLoadServer__sub_803EFCB4(u8 *data, s32 key, s32 sub_key, s32 *cnt, s32 *total, u8 *buf, s32 flags);
void TQuestVmDownLoadServer__sub_803EFF20(u8 *data, s32 key, s32 sub_key, s32 *best, u8 *dst, s32 flags);
s32 TQuestVmDownLoadServer__sub_803F0048(s32 id, u8 a1, u8 a2, void *dst);
s32 find_symbol_entry__22TQuestVmDownLoadServerFPvsPv(const char *name, s16 len, Info_803F0138 *out);
s32 TQuestVmDownLoadServer__sub_803F0268(const char *name, s16 len, Out_803F0268 *out);
s32 TQuestVmDownLoadServer__sub_803F03B4(u8 *cursor, Ent_803F03B4 *ents, s32 n, s32 *max);

s32 TQuestVmDownLoadServer__sub_803E6970(s32 start, s32 count, u16 *buf, s32 flag);

void TQuestVmDownLoadServer__sub_803E6ACC(s32 arg0);

void TQuestVmDownLoadServer__sub_803E6B70(u8 *dst, s32 start, s32 count, s32 mode);

#pragma push
#pragma opt_common_subs off
typedef char RecoveredGlobal_803E6ED0_lbl_805A05D0_size[sizeof(RecoveredGlobal_803E6ED0_lbl_805A05D0) == 0xC8 ? 1 : -1];

#pragma pop

s32 TQuestVmDownLoadServer__sub_803E6F98(u16 arg0);

s32 TQuestVmDownLoadServer__sub_803E7018(u16 arg0);

s32 TQuestVmDownLoadServer__sub_803E7098(u8 *p, u16 code);

s32 TQuestVmDownLoadServer__sub_803E719C(u8 arg0, s32 arg1);

typedef char RecoveredGlobal_803E721C_lbl_8047E698_size[sizeof(RecoveredGlobal_803E721C_lbl_8047E698) == 0x200 ? 1 : -1];

u16 TQuestVmDownLoadServer__sub_803E721C(u16 arg0);

struct Row_803E7390 { s16 single; s16 pair; };

s32 TQuestVmDownLoadServer__sub_803E7390(u8 a, u8 b, u8 c);

s32 TQuestVmDownLoadServer__sub_803E779C(u32 arg0, s32 *arg1, s32 *arg2, s32 *arg3);

void TQuestVmDownLoadServer__sub_803E79AC(void);

#pragma push
#pragma dont_inline off
#pragma inline_depth(2)
inline s32 Open_803E7B9C(void) {
    s32 h = TQuestVmDownLoadServer__sub_803F0BE0(quest_vm_download_server_file_info, (void *)lbl_805D78F8);
    if (h == -1) {
        lbl_805D7904 = -1;
        return -1;
    }
    lbl_805D7904 = h;
    return 0;
}
inline s32 Seek_803E7B9C(s32 pos) {
    if (TQuestVmDownLoadServer__sub_803F09FC((void *)lbl_805D7904, pos, 0) == -1) {
        if (Open_803E7B9C() != 0) {
            return -1;
        }
        if (TQuestVmDownLoadServer__sub_803F09FC((void *)lbl_805D7904, pos, 0) == -1) {
            return -1;
        }
    }
    return 0;
}
inline s32 Write_803E7B9C(void) {
    return -1;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(4)
inline s32 Open_803E7ACC(void) {
    void *mode = (void *)lbl_805D78F8;
    s32 h = TQuestVmDownLoadServer__sub_803F0BE0(quest_vm_download_server_file_info, mode);
    if (h == -1) {
        lbl_805D7904 = -1;
        return -1;
    }
    lbl_805D7904 = h;
    return 0;
}
inline s32 Seek_803E7ACC(s32 h, s32 pos, s32 whence) {
    return TQuestVmDownLoadServer__sub_803F09FC((void *)h, pos, whence);
}
inline s32 SeekRetry_803E7ACC(s32 pos) {
    if (Seek_803E7ACC(lbl_805D7904, pos, 0) == -1) {
        if (Open_803E7ACC() != 0) {
            return -1;
        }
        if (Seek_803E7ACC(lbl_805D7904, pos, 0) == -1) {
            return -1;
        }
    }
    return 0;
}

#pragma pop

#pragma pop

u8 *get_cached_page__22TQuestVmDownLoadServerFi(s32 page);

#pragma push
#pragma dont_inline off
#pragma inline_depth(4)
static inline s32 match_803E7E3C(u8 *p, u8 *q) {
    s32 i;
    u8 c;
    for (i = 0; i < 4; i++, p++, q++) {
        c = *p;
        if (c != *q || c == 0) {
            break;
        }
    }
    return i;
}

#pragma pop

s32 find_name_index__22TQuestVmDownLoadServerFv(const char *name);

void TQuestVmDownLoadServer__sub_803E7F9C(u8 *text, s16 mode);

s32 TQuestVmDownLoadServer__sub_803E8084(void);

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline s32 Open_803E8624(void) {
    s32 h = TQuestVmDownLoadServer__sub_803F0BE0(quest_vm_download_server_file_info, (void *)lbl_805D78F8);
    if (h == -1) {
        lbl_805D7904 = -1;
        return -1;
    }
    lbl_805D7904 = h;
    return 0;
}
inline s32 Seek_803E8624(s32 h, s32 pos, s32 whence) {
    return TQuestVmDownLoadServer__sub_803F09FC((void *)((void *)h), pos, whence);
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(2)
inline s32 Open_803E8150(void) {
    s32 h = TQuestVmDownLoadServer__sub_803F0BE0(quest_vm_download_server_file_info, (void *)lbl_805D78F8);
    if (h == -1) {
        lbl_805D7904 = -1;
        return -1;
    }
    lbl_805D7904 = h;
    return 0;
}
inline s32 Seek_803E8150(s32 pos) {
    if (TQuestVmDownLoadServer__sub_803F09FC((void *)lbl_805D7904, pos, 0) == -1) {
        if (Open_803E8150() != 0) {
            return -1;
        }
        if (TQuestVmDownLoadServer__sub_803F09FC((void *)lbl_805D7904, pos, 0) == -1) {
            return -1;
        }
    }
    return 0;
}
inline s32 Write_803E8150(void) {
    return -1;
}
s32 TQuestVmDownLoadServer__sub_803E8150(void);
#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(2)
inline s32 Open_803E82AC(Buf_803E82AC *b) {
    s32 h = TQuestVmDownLoadServer__sub_803F0BE0(b->name, (void *)lbl_805D78F8);
    if (h == -1) {
        lbl_805D7904 = -1;
        return -1;
    }
    lbl_805D7904 = h;
    return 0;
}
inline s32 Seek_803E82AC(Buf_803E82AC *b, s32 pos) {
    if (TQuestVmDownLoadServer__sub_803F09FC((void *)lbl_805D7904, pos, 0) == -1) {
        if (Open_803E82AC(b) != 0) {
            return -1;
        }
        if (TQuestVmDownLoadServer__sub_803F09FC((void *)lbl_805D7904, pos, 0) == -1) {
            return -1;
        }
    }
    return 0;
}

#pragma pop

#pragma pop

s32 TQuestVmDownLoadServer__sub_803E86C8(void);

s32 TQuestVmDownLoadServer__sub_803E8788(int _w0, void * _w1, int _w2);

// Provisional native link name: the first word is the provider's opaque
// handle, not a TQuestVmDownLoadServer receiver.
u32 aram_read_thunk__22TQuestVmDownLoadServerFUli(void *handle, void *dst, s32 size);

void TQuestVmDownLoadServer__sub_803E8918(void);

// Move the indexed record to the append page, preserving native reservation
// and identity-check order. See the lifecycle evidence for unchecked preconditions.
#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
// Borrowed view of a variable-length cache record; it does not own storage.
struct CachedRecordView {
    u8 *record;
    CachedRecordView(u8 *const &data) : record(data) {}
    u8 *bytes() const { return record; }
    s32 length() const { return (u16)(bytes()[0] + (bytes()[1] << 8)); }
    u8 name_length() const { return record[2]; }
    char *name() const { return (char *)(record + 3); }
};
#pragma inline_depth(2)
void TQuestVmDownLoadServer__sub_803E8924(s32 id);
#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline s32 IsSjisLead_803E92C0(u8 c) {
    if ((c >= 0x80 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC)) {
        return 1;
    }
    return 0;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline s32 IsSjisLead_803E90A8(u8 c) {
    if ((c >= 0x80 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC)) {
        return 1;
    }
    return 0;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline s32 Hash_803E8C2C(char *s) {
    s32 h;
    u8 c = s[0];
    if (c >= 0xA0 && c < 0xF0) {
        h = c - 0xA0;
    } else {
        h = 0;
    }
    return h;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline s32 Hash_803E8B1C(char *s) {
    s32 h;
    u8 c = s[0];
    if (c >= 0xA0 && c < 0xF0) {
        h = c - 0xA0;
    } else {
        h = 0;
    }
    return h;
}
s32 lookup_name_entry__22TQuestVmDownLoadServerFPvsPv(char *arg0, s16 arg1, Out_803E8B1C *arg2);
#pragma pop

s32 TQuestVmDownLoadServer__sub_803E8C2C(char *arg0, s16 arg1, Out_803E8C2C *arg2);
#pragma pop

// Native code reaches the separate index relative to the byte-cache address.
#ifdef __MWERKS__
#define QUEST_DOWNLOAD_CACHE_INDEX(address) reinterpret_cast<QuestDownloadCachedNameIndex *>((address) + sizeof(lbl_80591EC8))
#else
#define QUEST_DOWNLOAD_CACHE_INDEX(address) (&lbl_80593EC8)
#endif

// Replace a matching name and append its encoded record. Native unchecked
// search-stop, node-availability and bounded-input preconditions are retained.
#pragma push
#pragma opt_common_subs off
#pragma dont_inline off
#pragma inline_depth(2)
#pragma opt_propagation on
#pragma opt_lifetimes off
struct CachedNameBucket {
    s32 value;
    CachedNameBucket(u8 first) {
        if (first >= 0xA0 && first < 0xF0) {
            value = first - 0xA0;
        } else {
            value = 0;
        }
    }
};
inline QuestDownloadCachedNameNode *find_replacement_name_link(
        char *name, size_t cacheAddress, const s16 &inputLength, QuestDownloadCachedNameNode **&link) {
    s16 wanted;
    QuestDownloadCachedNameNode *node;
    QuestDownloadCachedNameNode *previous;
    u8 recordLength;
    previous = NULL;
    wanted = inputLength;
    CachedNameBucket bucket((u8)name[0]);
    node = QUEST_DOWNLOAD_CACHE_INDEX(cacheAddress)->heads[bucket.value];
    for (; node != NULL; node = node->next) {
        u8 *indexed = node->encodedRecord;
        recordLength = indexed[2];
        s32 comparison = strncmp((const char *)(indexed + 3), name, (s16)recordLength);
        if (comparison == 0) {
            if (wanted == (s16)recordLength) {
                break;
            }
        } else if (comparison > 0) {
            break;
        }
        previous = node;
    }
    if (previous == NULL) {
        link = &QUEST_DOWNLOAD_CACHE_INDEX(cacheAddress)->heads[bucket.value];
    } else {
        link = &previous->next;
    }
    return node;
}
inline QuestDownloadCachedNameNode *find_cached_insertion_link(
        char *name, size_t cacheAddress, const s16 &inputLength, QuestDownloadCachedNameNode **&link) {
    s32 bucket;
    s16 wanted;
    QuestDownloadCachedNameNode *node;
    QuestDownloadCachedNameNode *previous;
    u8 recordLength;
    previous = NULL;
    u8 first = (u8)name[0];
    wanted = inputLength;
    if (first >= 0xA0 && first < 0xF0) {
        bucket = first - 0xA0;
    } else {
        bucket = 0;
    }
    node = QUEST_DOWNLOAD_CACHE_INDEX(cacheAddress)->heads[bucket];
    for (; node != NULL; node = node->next) {
        u8 *indexed = node->encodedRecord;
        recordLength = indexed[2];
        s32 comparison = strncmp((const char *)(indexed + 3), name, (s16)recordLength);
        if (comparison == 0) {
            if (wanted == (s16)recordLength) {
                break;
            }
        } else if (comparison > 0) {
            break;
        }
        previous = node;
    }
    if (previous == NULL) {
        link = &QUEST_DOWNLOAD_CACHE_INDEX(cacheAddress)->heads[bucket];
    } else {
        link = &previous->next;
    }
    return node;
}
inline void write_cached_record(u8 *p, s32 length, Req_803EEF2C *req, s32 value) {
    *p++ = length % 256;
    *p++ = length / 256;
    *p++ = req->len;
    strncpy((char *)p, req->name, req->len);
    p += req->len;
    *p++ = req->x7;
    *p++ = value;
    u8 extra = req->x8;
    if (extra != 0 || req->x7 >= 0x2D) {
        *p++ = extra;
    }
    TQuestVmDownLoadServer::copy_sjis_string(req->text, p);

}
inline s32 cached_record_length(Req_803EEF2C *req) {
    s32 width;
    s32 metadata;
    if (req->x8 != 0 || req->x7 >= 0x2D) metadata = 3;
    else metadata = 2;
    width = TQuestVmDownLoadServer::calc_sjis_string_width(req->text);
    s32 total;
    // Discarding the prefix assignment's value preserves MWCC's temporary handoff.
    return ((void)(total = req->len + metadata), metadata = total + width) + 3;
}
s32 TQuestVmDownLoadServer__sub_803E8DA0(char *key, Req_803EEF2C *req, s32 value);
#pragma pop

void append_message_text__22TQuestVmDownLoadServerFPviPvUc(u8 *arg0, s32 arg1, Msg_803E90A8 *arg2, u8 arg3);
#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(2)
inline s32 IsSjisLead_803E9190(u8 c) {
    if ((c >= 0x80 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC)) {
        return 1;
    }
    return 0;
}
inline void CopyText_803E9190(u8 *s, u8 *p) {
    while (*s != 0) {
        if (IsSjisLead_803E9190(*s)) {
            *p++ = *s++;
        } else {
            *p++ = 0xFF;
        }
        *p++ = *s++;
    }
}
void build_message_packet__22TQuestVmDownLoadServerFPviPvUc(u8 *arg0, s32 arg1, Msg_803E9190 *arg2, u8 arg3);
#pragma pop

#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline s32 IsSjisLead_803E9348(u8 c) {
    if ((c >= 0x80 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC)) {
        return 1;
    }
    return 0;
}

#pragma pop

// Rebuild the name index from the persisted eight-page byte image. Bounds,
// initialized page index and producer-consistent names remain preconditions.
#pragma push
#pragma opt_common_subs off
#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
// The caller supplies the copied, terminated name. The stopping node and its
// predecessor link are both needed by insertion and page rotation.
inline QuestDownloadCachedNameNode *find_cached_name_link(
        char *name, size_t cacheAddress, u8 inputLength, QuestDownloadCachedNameNode **&link) {
    s16 wanted;
    s32 bucket;
    QuestDownloadCachedNameNode *node;
    QuestDownloadCachedNameNode *previous;
    u8 recordLength;
    previous = NULL;
    u8 first = (u8)name[0];
    if (first >= 0xA0 && first < 0xF0) {
        bucket = first - 0xA0;
    } else {
        bucket = 0;
    }
    node = QUEST_DOWNLOAD_CACHE_INDEX(cacheAddress)->heads[bucket];
    wanted = (s16)inputLength;
    for (; node != NULL; node = node->next) {
        u8 *indexed = node->encodedRecord;
        recordLength = indexed[2];
        s32 comparison = strncmp((const char *)(indexed + 3), name, (s16)recordLength);
        if (comparison == 0) {
            if (wanted == (s16)recordLength) {
                break;
            }
        } else if (comparison > 0) {
            break;
        }
        previous = node;
    }
    if (previous == NULL) {
        link = &QUEST_DOWNLOAD_CACHE_INDEX(cacheAddress)->heads[bucket];
    } else {
        link = &previous->next;
    }
    return node;
}
#pragma push
#pragma inline_depth(2)
inline s32 read_name_image_bytes(void *file, u8 *image, s32 length) {
    return (s32)aram_read_thunk__22TQuestVmDownLoadServerFUli(file, image, length);
}
// Keep the fixed cache-image read distinct from its byte-count adapter; their
// native inline lifetimes also determine the rebuild name-buffer offset.
inline s32 read_cached_name_image(void *file, u8 *image) {
    return (s32)read_name_image_bytes(file, image, 0x2000);
}
s32 TQuestVmDownLoadServer__sub_803E93DC(void);
#pragma pop

#pragma pop

#pragma pop

// Rotate the encoded-name cache page and return its indexed nodes to the
// existing free list. Requires valid bounded records and a consistent index.

void TQuestVmDownLoadServer__sub_803E95BC(void);

void TQuestVmDownLoadServer__sub_803E9764(void);

// This existing link name denotes the cache initializer here; no SDK owner
// or retrace-handler semantics are inferred from the placeholder symbol.
void __VIRetraceHandler(void);

typedef char RecoveredGlobal_803E9F20_lbl_80595998_size[sizeof(RecoveredGlobal_803E9F20_lbl_80595998) == 0x8C0 ? 1 : -1];

QuestDownloadSegment *TQuestVmDownLoadServer__sub_803E9A74(s32 beg, s32 end, u8 a, u8 b);

const QuestDownloadMatchToken *find_longest_match_entry__22TQuestVmDownLoadServerFPviPv(u8 *arg0, s32 arg1, s32 *arg2);

s32 TQuestVmDownLoadServer__sub_803E9F54(s32 arg0);

// List failure/unavailable input is all-ones in the native 32-bit result word.
// NULL remains an empty or allocation-exhausted list, not this failure. See
// docs/evidence/quest-download-search-evidence.md.

// The quest download name character class. The original lowers this sparse
// switch behind an explicit range guard at the head of the slot search.

// Scan one slot's match-token chain for segments covering [beg, end). A
// token names an item pair (a, b); lbl_8047F0F8 maps its displacement byte
// to an offset into the download buffer, and the first-fill path above
// covers the empty-slot single-byte case. The walk runs backwards by the
// token's signed link count.
QuestDownloadEntryNode *insert_sorted_node__22TQuestVmDownLoadServerFPvPv(QuestDownloadEntryNode *arg0, QuestDownloadEntryNode *arg1);
void *TQuestVmDownLoadServer__sub_803E9FFC(s32 arg0, s32 arg1, QuestDownloadItemNode *t);

extern "C" QuestDownloadItemNode lbl_8047F8A8;
// Local pass settings preserve the separate generator result and traversal
// cursor, the cached position and the original write boundary. pragma pop
// restores the surrounding profile; option recognition is tested separately.
s32 TQuestVmDownLoadServer__sub_803EA1A8(s32 index, s32 limit);

QuestDownloadItemNode *build_item_list__22TQuestVmDownLoadServerFiPv(s32 arg0, Hdr_803EA384 *arg1);

s32 TQuestVmDownLoadServer__sub_803EA428(s32 start, s32 end);

extern s32 lbl_805D7880;
s32 TQuestVmDownLoadServer__sub_803EA1A8(s32, s32);
s32 TQuestVmDownLoadServer__sub_803F06B8(const char *, s16, Out_803F0268 *);

// These two native routines retain the workspace allocation address while
// accessing the separately allocated following slots. Ports use their real
// objects directly; no larger C++ owner is asserted for the native address map.

// This local value borrows the native workspace address; the following slot
// array remains a separate object. Its constructor also preserves the native
// temporary lifetime, as in CachedRecordView above.

void TQuestVmDownLoadServer__sub_803EA9E8(s32 start, s32 inputEnd, s32 mode, s32 selectedLength);

void TQuestVmDownLoadServer__sub_803EADD4(QuestDownloadSlot *arg0, s32 arg1);

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline s32 Len_803EB328(QuestDownloadTextNode *p) {
    s32 n;
    if (p->flags == 0x80) {
        return lbl_805D78EC * 2;
    }
    n = (lbl_805D78EC - p->payload.head.length) * 2;
    while (p->flags & 1) {
        n += strlen(reinterpret_cast<char *>(&p->payload));
        p = p->next;
    }
    return n + strlen(reinterpret_cast<char *>(&p->payload));
}
inline QuestDownloadTextNode *Next_803EB328(QuestDownloadTextNode *p) {
    while (p->flags & 1) {
        p = p->next;
    }
    return p->next;
}

void TQuestVmDownLoadServer__sub_803EAE84(s32 arg0, s32 arg1, void *arg2);

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline QuestDownloadTextNode *Advance_803EB0D8(QuestDownloadTextNode *p, s32 n) {
    s32 i;
    for (i = 0; i != n; i++) {
        while (p->flags & 1) {
            p = p->next;
        }
        p = p->next;
    }
    return p;
}
inline void Reload_803EB0D8(void) {
    s32 r = count_fitting_entries__22TQuestVmDownLoadServerFPv((QuestDownloadTextNode *)((*(QuestDownloadTextNode * *)&lbl_805D78A0)));
    if (r == 0) {
        TQuestVmDownLoadServer__sub_803EC284(0, 0);
    } else {
        lbl_805D789C = r;
    }
    lbl_805D7898 = 0;
}
s32 TQuestVmDownLoadServer__sub_803EB0D8(s32 arg0, s32 arg1);
#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline QuestDownloadTextNode *advance_entry_groups(QuestDownloadTextNode *p, s32 n) {
    while (n-- != 0) {
        while (p->flags & 1) {
            p = p->next;
        }
        p = p->next;
    }
    return p;
}
inline s32 count_fitting_groups(QuestDownloadTextNode *head) {
    QuestDownloadTextNode *p;
    s32 n;
    s32 total;
    s32 limit;
    if (head == NULL) {
        return 0;
    }
    p = head;
    n = total = 0;
    limit = lbl_805D78A4 - 9;
    while (n < 9 && p != NULL) {
        total += TQuestVmDownLoadServer__sub_803EB7C0((QuestDownloadTextNode *)p) + 3;
        if (total > limit) {
            break;
        }
        n++;
        while (p->flags & 1) {
            p = p->next;
        }
        p = p->next;
    }
    if (n == 0) {
        return 1;
    }
    return n;
}
s32 TQuestVmDownLoadServer__sub_803EB208(s32 mode, s32 force);
#pragma pop

s32 count_fitting_entries__22TQuestVmDownLoadServerFPv(QuestDownloadTextNode *arg0);
#pragma pop

s32 TQuestVmDownLoadServer__sub_803EB420(s32 start, s32 count, QuestDownloadTextNode *arg2, u16 *buf);

void TQuestVmDownLoadServer__sub_803EB4D4(void);

QuestDownloadTextNode *advance_nodes__22TQuestVmDownLoadServerFPvi(QuestDownloadTextNode *p, s32 n);

s32 TQuestVmDownLoadServer__sub_803EB7C0(QuestDownloadTextNode *arg0);

s32 count_chain_nodes__22TQuestVmDownLoadServerFv(QuestDownloadTextNode *p);

QuestDownloadTextNode *TQuestVmDownLoadServer__sub_803EB878(QuestDownloadTextNode *p);

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline s32 Conv_803EB8BC(s32 start, s32 arg1, QuestDownloadTextNode *arg2, u16 *arg3) {
    s32 n;
    QuestDownloadTextNode *p;
    u16 *b = arg3;
    s32 lim = arg1;
    u8 unused[8];
    if (arg2 == NULL || (arg2->flags & 0x80)) {
        return TQuestVmDownLoadServer__sub_803E6970(start, lim, b, 0);
    }
    p = arg2;
    n = 0;
    for (;;) {
        n += TQuestVmDownLoadServer__sub_803EC95C(b + n, reinterpret_cast<u8 *>(p) + 1, 6);
        if (!(p->flags & 1)) {
            break;
        }
        p = p->next;
    }
    b += n;
    return n + TQuestVmDownLoadServer__sub_803E6970((s32)(start + arg2->payload.head.length), (s32)(lim - arg2->payload.head.length), b, 0);
}
inline s32 Find_803EB8BC(u8 *key, s32 len) {
    s32 l;
    u8 *p;
    for (p = quest_download_text_buffer; p < quest_download_text_write_ptr; p += l) {
        l = *p++;
        if (l == len && strncmp((const char *)p, (const char *)key, l) == 0) {
            return 1;
        }
    }
    return 0;
}
inline void Add_803EB8BC(u8 *key, s32 len) {
    if (quest_download_text_write_ptr + len + 1 <= quest_download_text_buffer + 0x400) {
        *quest_download_text_write_ptr++ = len;
        strncpy((char *)quest_download_text_write_ptr, (const char *)key, len);
        quest_download_text_write_ptr += len;
    }
}
inline QuestDownloadTextNode *Last_803EB8BC(QuestDownloadTextNode *p) {
    if (p == NULL) {
        return NULL;
    }
    for (;;) {
        if (p->next == NULL) {
            break;
        }
        p = p->next;
    }
    return p;
}

QuestDownloadTextNode *detach_node_chain__22TQuestVmDownLoadServerFPv(QuestDownloadTextNode *p);
#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline s32 Conv_803EBA98(s32 start, s32 arg1, QuestDownloadTextNode *arg2, u16 *arg3) {
    QuestDownloadTextNode *p;
    s32 n;
    u16 *b = arg3;
    s32 lim = arg1;
    u8 unused[8];
    if (arg2 == NULL || (arg2->flags & 0x80)) {
        return TQuestVmDownLoadServer__sub_803E6970(start, lim, b, 0);
    }
    p = arg2;
    n = 0;
    for (;;) {
        n += TQuestVmDownLoadServer__sub_803EC95C(b + n, reinterpret_cast<u8 *>(p) + 1, 6);
        if (!(p->flags & 1)) {
            break;
        }
        p = p->next;
    }
    b += n;
    return n + TQuestVmDownLoadServer__sub_803E6970((s32)(start + arg2->payload.head.length), (s32)(lim - arg2->payload.head.length), b, 0);
}
// Keep these display helpers in the existing depth-one converter region.
// The readonly length reference avoids an additional by-value inline argument
// temporary in GC/1.2.5. See the display-recovery evidence for native checks.

extern u8 lbl_805D7894[4];
extern u8 lbl_805E10D0[4];

void append_unique_node__22TQuestVmDownLoadServerFiPvPvPv(s32 start, QuestDownloadTextNode **headp, QuestDownloadTextNode **tailp, QuestDownloadTextNode *n);

inline QuestDownloadTextNode *Next_803EBA98(QuestDownloadTextNode *p) {
    while (p->flags & 1) {
        p = p->next;
    }
    return p->next;
}
void TQuestVmDownLoadServer__sub_803EBA98(s32 start, QuestDownloadTextNode *arg1);
#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline QuestDownloadTextNode *build_entry_text(s32 idx, s32 len, s32 mode) {
    void *first;
    void *tail;
    Src_803EBD38 *src = (Src_803EBD38 *)quest_download_text_buffer;
    src->x0 = 0xFFFF;
    src->x2 = 0;
    src->x4 = 0;
    TQuestVmDownLoadServer__sub_803E6B70(src->text, idx, len, mode);
    return (QuestDownloadTextNode *)TQuestVmDownLoadServer::build_text_node_chain(src, NULL, len, &first, &tail);
}

QuestDownloadTextNode *get_next_node__22TQuestVmDownLoadServerFPv(QuestDownloadQueueNode *p);
#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline QuestDownloadTextNode *Default_803EBEFC(s32 x) {
    QuestDownloadTextNode *n = (QuestDownloadTextNode *)TQuestVmDownLoadServer__sub_803ECED0();
    if (n != NULL) {
        n->flags = 0x80;
        n->payload.head.text[0] = 0;
        n->payload.head.length = x;
        n->payload.head.kind = 0;
        n->payload.head.source = 0;
        n->payload.head.id = 0xFFFF;
        n->next = NULL;
    }
    return n;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline s32 Copy_803EBD38(u8 *dst, u8 *src, s32 max) {
    s32 n = max;
    u8 *s = src;
    u8 *d = dst;
    while (*s != 0 && n > 0) {
        if (TQuestVmDownLoadServer::is_sjis_lead_byte(*s)) {
            if (n <= 1) {
                break;
            }
            *d++ = *s++;
            n--;
        }
        *d++ = *s++;
        n--;
    }
    *d = 0;
    return max - n;
}

void TQuestVmDownLoadServer__sub_803EBC88(s32 mode);

#pragma pop

// Native code keeps the display-prefix address when addressing the following
// scratch allocation. Ports use that separate byte-array object directly.
#ifdef __MWERKS__
#define QUEST_TEXT_SCRATCH(prefix) reinterpret_cast<u8 *>((size_t)(prefix) + sizeof(QuestDownloadDisplayPrefix))
#else
#define QUEST_TEXT_SCRATCH(prefix) quest_download_text_buffer
#endif

#pragma pop

QuestDownloadQueueNode *TQuestVmDownLoadServer__sub_803ECE94(void);
QuestDownloadTextNode *get_next_node__22TQuestVmDownLoadServerFPv(QuestDownloadQueueNode *);

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline QuestDownloadTextNode *Default_803EC09C(s32 x) {
    QuestDownloadTextNode *n = (QuestDownloadTextNode *)TQuestVmDownLoadServer__sub_803ECED0();
    if (n != NULL) {
        n->flags = 0x80;
        n->payload.head.text[0] = 0;
        n->payload.head.length = x;
        n->payload.head.kind = 0;
        n->payload.head.source = 0;
        n->payload.head.id = 0xFFFF;
        n->next = NULL;
    }
    return n;
}
inline QuestDownloadTextNode *Last_803EC09C(QuestDownloadTextNode *p) {
    if (p == NULL) {
        return NULL;
    }
    for (;;) {
        if (p->next == NULL) {
            break;
        }
        p = p->next;
    }
    return p;
}

QuestDownloadTextNode *TQuestVmDownLoadServer__sub_803EBEFC(QuestDownloadEntryPrefix *a);
#pragma pop

void TQuestVmDownLoadServer__sub_803EC09C(void);

// Depth 2 lets the page fit inline the nested group walk at both sites; a
// depth-1 region leaves it out of line and changes both expansions.
#pragma push
#pragma dont_inline off
#pragma inline_depth(2)
inline QuestDownloadTextNode *next_text_group(QuestDownloadTextNode *node) {
    while (node->flags & 1) {
        node = node->next;
    }
    return node->next;
}
inline s32 count_text_groups_that_fit(QuestDownloadTextNode *head) {
    QuestDownloadTextNode *node;
    s32 n;
    s32 total;
    s32 limit;
    if (head == NULL) {
        return 0;
    }
    node = head;
    n = total = 0;
    limit = lbl_805D78A4 - 9;
    while (n < 9 && node != NULL) {
        total += TQuestVmDownLoadServer__sub_803EB7C0(node) + 3;
        if (total > limit) {
            break;
        }
        n++;
        node = next_text_group(node);
    }
    if (n == 0) {
        return 1;
    }
    return n;
}
inline void advance_text_groups(QuestDownloadTextNode *&head, s32 count) {
    for (s32 i = 0; i != count; i++) {
        QuestDownloadTextNode *node = head;
        while (node->flags & 1) {
            node = node->next;
        }
        head = node->next;
    }
}
void TQuestVmDownLoadServer__sub_803EC284(s32 index, s32 mode);

inline QuestDownloadTextNode *Default_803EC460(s32 x) {
    QuestDownloadTextNode *n = (QuestDownloadTextNode *)TQuestVmDownLoadServer__sub_803ECED0();
    if (n != NULL) {
        n->flags = 0x80;
        n->payload.head.text[0] = 0;
        n->payload.head.length = x;
        n->payload.head.kind = 0;
        n->payload.head.source = 0;
        n->payload.head.id = 0xFFFF;
        n->next = NULL;
    }
    return n;
}

void TQuestVmDownLoadServer__sub_803EC460(s32 pos, s32 x);
#pragma pop

// The callers validate Shift-JIS lead bytes; this conversion checks the trail byte.
u16 TQuestVmDownLoadServer__sub_803EC69C(u16 code);

#pragma push
#pragma dont_inline off
#pragma inline_depth(3)
static inline s32 Kind_803EC71C(u16 ch) { return (ch >> 8) & 0xf; }
// The promoted cursor result and validation references preserve the original
// inlined frame and validation register lifetimes.
static inline u32 ReadNext_803EC71C(u16 *&text) { return *++text; }
static inline s32 IsJisByte_803EC71C(const s32 &ch) {
    s32 result = 0;
    if (ch >= 0x21U && ch <= 0x7eU) {
        result = 1;
    }
    return result;
}
static inline s32 IsJisPair_803EC71C(const s32 &lo, const s32 &hi) {
    s32 result = 0;
    if (IsJisByte_803EC71C(hi) && IsJisByte_803EC71C(lo)) {
        result = 1;
    }
    return result;
}
static inline s32 IsJis_803EC71C(u16 code) {
    s32 lo = code & 0xff;
    s32 hi = (code >> 8) & 0xff;
    return IsJisPair_803EC71C(lo, hi);
}
// The encoder supplies nonzero character classes as odd/even pairs.
// Preserve the original cursor advances when a pair is rejected.
s32 TQuestVmDownLoadServer__sub_803EC71C(u16 *text, u8 *out, s32 count);
#pragma pop

s32 TQuestVmDownLoadServer__sub_803EC884(u16 arg0);

u8 TQuestVmDownLoadServer__sub_803EC8D8(u16 arg0);

s32 TQuestVmDownLoadServer__sub_803EC95C(u16 *out, u8 *text, int attr);

void TQuestVmDownLoadServer__sub_803ECA1C(u16 *arg0, s32 arg1, s32 arg2);

#pragma push
#pragma dont_inline off
#pragma inline_depth(2)
inline s32 IsLead_803ECAE8(u32 c) {
  if (((c < 0x81) || (c > 0xFC)) || ((c >= 0xA0) && (c < 0xE0)))
  {
    return 0;
  }
  return 1;
}

inline s32 IsTrail_803ECAE8(u8 c) {
  if (((c < 0x40) || (c > 0xFC)) || (c == 0x7F))
  {
    return 0;
  }
  return 1;
}

inline s32 IsSjis_803ECAE8(s32 lo, s32 hi) {
  if (IsLead_803ECAE8(hi) == 0)
  {
    return 0;
  }
  return IsTrail_803ECAE8(lo);
}

inline s32 IsJis_803ECAE8(u8 c) {
  s32 r = 0;
  if ((c >= 0x21) && (c <= 0x7E))
  {
    r = 1;
  }
  return r;
}

inline s32 IsJisPair_803ECAE8(s32 lo, s32 hi) {
  s32 r = 0;
  if (IsJis_803ECAE8(hi) && IsJis_803ECAE8(lo))
  {
    r = 1;
  }
  return r;
}

inline s32 Kind_803ECAE8(u16 c, s32 lo) {
  switch (c & 0xFF00)
  {
    case 0x8000:

    case 0x8500:
      return 1;

    case 0x8600:
      if (lo < 0x9E)
    {
      return 1;
    }
      break;

  }

  return 2;
}

#pragma pop

s32 TQuestVmDownLoadServer__sub_803ECC7C(u16 arg0);

#pragma push
#pragma dont_inline off
#pragma inline_depth(2)
inline void return_quest_pool_cell(void *storage) {
    QuestDownloadPoolCell *cell = static_cast<QuestDownloadPoolCell *>(storage);
    new (&cell->free, quest_download_pool_storage) QuestDownloadFreeLink;
    cell->free.next = lbl_805D78B0;
    lbl_805D78B0 = &cell->free;
    lbl_805D78AC += 1;
}
void TQuestVmDownLoadServer__sub_803ECD1C(QuestDownloadQueueNode *p);
void free_node_list__22TQuestVmDownLoadServerFv(QuestDownloadTextNode *p);
void TQuestVmDownLoadServer__sub_803ECD8C(QuestDownloadEntryNode *p);
void release_node_chain__22TQuestVmDownLoadServerFPv(QuestDownloadItemNode *p);
void TQuestVmDownLoadServer__sub_803ECE5C(QuestDownloadSegment *p);
#pragma push
#pragma inline_depth(1)
inline QuestDownloadFreeLink *pop_free_block() {
    QuestDownloadFreeLink *p = lbl_805D78B0;
    if (p == NULL) return NULL;
    lbl_805D78B0 = lbl_805D78B0->next;
    lbl_805D78AC--;
    return p;
}
QuestDownloadQueueNode *TQuestVmDownLoadServer__sub_803ECE94(void);
void *TQuestVmDownLoadServer__sub_803ECED0(void);
void *TQuestVmDownLoadServer__sub_803ECF0C(void);
void *TQuestVmDownLoadServer__sub_803ECF48(void);
QuestDownloadItemNode *TQuestVmDownLoadServer__sub_803ECF84(void);
#pragma pop

void push_download_entry__22TQuestVmDownLoadServerFPl(void *arg0);
extern QuestDownloadPoolCell quest_download_block_pool[2000];
extern s32 quest_download_free_list_ready_flag;

#pragma pop

typedef char RecoveredGlobal_803EE2E4_lbl_8058DC98_size[sizeof(lbl_8058DC98) == 0x50 ? 1 : -1];

u16 TQuestVmDownLoadServer__sub_803ED0B4(u8 *arg0, u16 arg1);

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline s32 InRange_803ED26C(u8 v) {
    s32 r = 0;
    if (v >= 1 && v <= 0xD) {
        r = 1;
    }
    return r;
}

s32 calc_item_entry_cost__22TQuestVmDownLoadServerFUcUcl(QuestDownloadEntryPrefix *a, u8 k, u8 v, s32 base);
#pragma pop

s32 calc_entry_cost__22TQuestVmDownLoadServerFPvPv(QuestDownloadEntryPrefix *a, QuestDownloadEntryPrefix *b);

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline s32 entry_source_is_special(QuestDownloadEntryNode *entry) {
    if (entry->prefix.src != NULL && (entry->prefix.src->a == 0x28 || entry->prefix.src->a == 0x29)) {
        return 1;
    }
    return 0;
}
inline u16 entry_follow_score(QuestDownloadEntryNode *entry, QuestDownloadEntryNode *next) {
    s32 own_length;
    s32 next_length;
    s32 terminal;
    if (next == NULL) {
        next_length = entry->prefix.off;
        own_length = 0;
        terminal = 1;
    } else {
        own_length = entry->prefix.off;
        terminal = 0;
        next_length = next->prefix.off;
    }
    // EntryPrefix is the actual first POD member, so this conversion also
    // preserves a null next pointer without dereferencing it.
    return entry->xa + (own_length * 16 + next_length * 17)
        + calc_entry_cost__22TQuestVmDownLoadServerFPvPv(
            reinterpret_cast<QuestDownloadEntryPrefix *>(entry),
            reinterpret_cast<QuestDownloadEntryPrefix *>(next))
        + terminal * 50;
}
s32 TQuestVmDownLoadServer__sub_803ED84C(QuestDownloadEntryNode *entry, s32 index, s32 limit);
#pragma pop

#pragma push
#pragma opt_common_subs off

#pragma push
#pragma dont_inline off
#pragma inline_depth(2)
inline s32 IsSpecial_803ED9AC(QuestDownloadEntryNode *e) {
    if (e->prefix.src != NULL && (e->prefix.src->a == 0x28 || e->prefix.src->a == 0x29)) {
        return 1;
    }
    return 0;
}
inline void Relax_803ED9AC(QuestDownloadEntryNode *best, s32 idx, s32 max) {
    QuestDownloadEntryNode *q;
    s32 v;
    s32 n = best->prefix.off;
    if (best->prefix.a == 0xFF || idx + n >= max) {
        return;
    }
    q = quest_download_slot_chain_table[idx + n].entryHead;
    if (q == NULL) {
        return;
    }
    for (; q != NULL; q = q->next) {
        q->xa = 0;
        if (!IsSpecial_803ED9AC(q)) {
            v = calc_entry_cost__22TQuestVmDownLoadServerFPvPv(&best->prefix, &q->prefix);
            if (v > 0) {
                q->xa = v;
            }
        }
    }
}

#pragma pop
#pragma pop

s32 TQuestVmDownLoadServer__sub_803EDB20(u8 arg0);

s32 TQuestVmDownLoadServer__sub_803EDB3C(u8 arg0);

s32 TQuestVmDownLoadServer__sub_803EDB58(u8 arg0);

s32 TQuestVmDownLoadServer__sub_803EDB74(u8 arg0);

s32 TQuestVmDownLoadServer__sub_803EDC20(u32 input_address);

// The packet ABI carries a valid input character-array address. The state
// constructor preserves the native pending-byte initialization and reset.
u8 *TQuestVmDownLoadServer__sub_803EDDA4(u16 *start, u16 *end);

extern u8 lbl_8047F9B8[];
extern u8 *lbl_8047FBD4[];

// The frontend starts and fills the actual halfword scratch object.
s32 TQuestVmDownLoadServer__sub_803EDF64(const u16 *input, s32 count,
                                      u16 *output, s32 *outputCount);

void TQuestVmDownLoadServer__sub_803EE2E4(void);

extern u8 lbl_8058DC48[0x50];
extern u8 lbl_8058DCE8[0x50];

// Native 0x28-byte allocation; only the leading request is accessed here.
struct QuestDownloadRequestStorage { Req_803EEF2C request; u8 remaining[0x18]; };
typedef char QuestDownloadRequestStorage_extent[sizeof(QuestDownloadRequestStorage) == 0x28 ? 1 : -1];
typedef char QuestDownloadRequestStorage_request[offsetof(QuestDownloadRequestStorage, request) == 0 ? 1 : -1];
extern QuestDownloadRequestStorage lbl_805A0698;
s32 TQuestVmDownLoadServer__sub_803EEDC0(Req_803EEF2C *, s32 *, s32);
s32 TQuestVmDownLoadServer__sub_803EF958(u32, u16, s32 *, s32);

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
// Borrows the request allocation while its leading request is assembled.
struct QuestDownloadRequestView {
    QuestDownloadRequestStorage *storage;
    QuestDownloadRequestView(QuestDownloadRequestStorage *value) : storage(value) {}
};

void TQuestVmDownLoadServer__sub_803EE2F4(s32 start, s32 end);

#pragma pop

// Keep the independent buffer addresses and native call-site lifetimes.
void TQuestVmDownLoadServer__sub_803EE580(s32 start, s32 length, QuestDownloadTextNode *text, QuestDownloadEntryNode *entries);

u16 *TQuestVmDownLoadServer__sub_803EE718(s32 i, s32 len);

u8 *TQuestVmDownLoadServer__sub_803EE828(void);

void TQuestVmDownLoadServer__sub_803EE870(s32 index, s32 mode);

s32 TQuestVmDownLoadServer__sub_803EE934(void);

s32 TQuestVmDownLoadServer__sub_803EEA48(s32 arg0, s32 arg1, void *arg2, s32 *arg3);

struct Tbl_803EEB10 {
    u8 units[0x14];
    u8 fullwidth_digits[0x18];
    u8 kanji_digits[0x18];
    u8 *sets[2];
    u8 *units_text;
};
struct Out_803EEB10 {
    u16 mode;
    s16 x2;
    u8 x4;
    u8 text[1];
};
extern Tbl_803EEB10 quest_download_number_text_table;

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline s32 IsSmall_803EEB10(s32 d) {
    s32 r = 0;
    if (d >= 1 && d <= 3) {
        r = 1;
    }
    return r;
}

void *format_number_text__22TQuestVmDownLoadServerFiiPvi(s32 arg0, s32 arg1, void *arg2, s32 mode);

#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(4)
#pragma opt_common_subs off
inline u32 Call_803EED0C(s32 a, s32 b, s32 c, s32 d) {
    return ((u32)format_number_text__22TQuestVmDownLoadServerFiiPvi((s32)a, (s32)b, (void *)c, (s32)d));
}
s32 TQuestVmDownLoadServer__sub_803EED0C(s32 arg0, s32 arg1, s32 arg2);
#pragma pop

s32 TQuestVmDownLoadServer__sub_803EED9C(u32 arg0);

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline void release_index_entries(s32 *ids, s32 n) {
    s32 i;
    s32 a;
    s32 b;
    s32 c;
    for (i = 0; i < n; i++) {
        s32 page = TQuestVmDownLoadServer__sub_803E779C(ids[i], &a, &b, &c);
        if (page != -1) {
            if (a != -1) {
                TQuestVmDownLoadServer__sub_803EF8E0(get_cached_page__22TQuestVmDownLoadServerFi(page) + a);
                TQuestVmDownLoadServer::set_active();
            }
            if (b != -1) {
                TQuestVmDownLoadServer__sub_803EF8E0(TQuestVmDownLoadServer::get_buffer_ptr(b));
                TQuestVmDownLoadServer__sub_803E8918();
            }
        }
    }
}
inline s32 is_digit_string(u8 *s) {
    for (; *s != 0; s++) {
        if (*s < 0x30 || *s > 0x39) {
            return 0;
        }
    }
    return 1;
}
s32 TQuestVmDownLoadServer__sub_803EEDC0(Req_803EEF2C *req, s32 *ids, s32 n);
#pragma pop

s32 TQuestVmDownLoadServer__sub_803EEF2C(Req_803EEF2C *arg0);

inline u8 *skip_entry_text(u8 *p, u8 *end) {
    for (; p < end; p += 2) {
        if (*p <= 0x38) {
            break;
        }
    }
    return p;
}

inline void shift_bytes(u8 *p, u8 *end, s32 delta) {
    u8 *s;
    if (delta > 0) {
        for (s = end - 1; p <= s; s--) {
            s[delta] = *s;
        }
    } else if (delta < 0) {
        for (; p < end; p++) {
            p[delta] = *p;
        }
    }
}

s32 TQuestVmDownLoadServer__sub_803EEFC8(u8 *rec, Req_803EEF2C *msg);

#pragma push
#pragma dont_inline off
#pragma inline_depth(2)
inline void shift_tail_bytes(u8 *p, u8 *end, s32 delta) {
    if (delta > 0) {
        for (end--; p <= end; end--) {
            end[delta] = *end;
        }
    } else if (delta < 0) {
        for (; p < end; p++) {
            p[delta] = *p;
        }
    }
}

inline s32 max_entry_index(u8 *rec) {
    s32 max = 0;
    u8 *end = rec + (u16)(rec[0] + (rec[1] << 8));
    u8 *p = rec + 3 + rec[2];
    while (p < end) {
        if (max < p[1]) {
            max = p[1];
        }
        p += 2;
        if (*p <= 0xB) {
            p++;
        }
        p = skip_entry_text(p, end);
    }
    return max;
}

// These spans are tails after a nonempty record in the same cached page.
// source is strictly past the array start: the backward cursor can finish one
// byte before source while remaining inside the backing page.
#ifdef __MWERKS__
#define QUEST_DOWNLOAD_SHIFT_ADDRESS(pointer, delta) \
    reinterpret_cast<u8 *>((delta) + reinterpret_cast<size_t>(pointer))
#else
#define QUEST_DOWNLOAD_SHIFT_ADDRESS(pointer, delta) ((pointer) + (delta))
#endif
inline void shift_removed_record_tail(u8 *source, u8 *end, const s32 &delta) {
    if (delta > 0) {
        --end;
        u8 *destination = QUEST_DOWNLOAD_SHIFT_ADDRESS(end, delta);
        for (; source <= end; end--, destination--) {
            *destination = *end;
        }
    } else if (delta < 0) {
        u8 *destination = QUEST_DOWNLOAD_SHIFT_ADDRESS(source, delta);
        for (; source < end; source++, destination++) {
            *destination = *source;
        }
    }
}

// Partial-message removal already shortened its record. Keep this operation's
// inline boundary separate from whole-record removal; see the unit evidence.
inline void shift_compacted_record_tail(u8 *p, u8 *end, s32 delta) {
    shift_tail_bytes(p, end, delta);
}
// Remove one matching message from a primary cached page. Caller-supplied
// names/text and page records retain the native bounded-input preconditions.
s32 TQuestVmDownLoadServer__sub_803EF208(Req_803EEF2C *request);

s32 TQuestVmDownLoadServer__sub_803EF538(Msg_803E9190 *msg);
#pragma pop

void TQuestVmDownLoadServer__sub_803EF8E0(u8 *p);

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
s32 TQuestVmDownLoadServer__sub_803EF958(u32 id, u16 key, s32 *ids, s32 n);

static inline s32 merge_duplicate_download_entry(Ent_803F03B4 *base, const Ent_803F03B4 *entry) {
    for (; base < entry; base++) {
        if (base->a == entry->a && base->b == entry->b) {
            if (base->key < entry->key) {
                base->key = entry->key;
            }
            return 1;
        }
    }
    return 0;
}

// The original's duplicate and encoded-text scans have separate cursor/result
// handoffs. Keep their caller in this existing inline-helper region; see
// docs/evidence/quest-download-unit-completion.md for the cursor lifetime.

#pragma pop

void TQuestVmDownLoadServer__sub_803EFCB4(u8 *data, s32 key, s32 sub_key, s32 *cnt, s32 *total, u8 *buf, s32 flags);

void TQuestVmDownLoadServer__sub_803EFF20(u8 *data, s32 key, s32 sub_key, s32 *best, u8 *dst, s32 flags);

s32 TQuestVmDownLoadServer__sub_803F0048(s32 id, u8 a1, u8 a2, void *dst);

s32 find_symbol_entry__22TQuestVmDownLoadServerFPvsPv(const char *name, s16 len, Info_803F0138 *out);

s32 TQuestVmDownLoadServer__sub_803F0268(const char *name, s16 len, Out_803F0268 *out);

s32 TQuestVmDownLoadServer__sub_803F03B4(u8 *cursor, Ent_803F03B4 *ents, s32 n, s32 *max);

s32 TQuestVmDownLoadServer__sub_803F0500(u8 *name, s16 len, Out_803E8C2C *out);

s32 TQuestVmDownLoadServer__sub_803F06B8(const char *name, s16 len, Out_803F0268 *out);

s32 TQuestVmDownLoadServer__sub_803F0890(void);

s32 TQuestVmDownLoadServer__sub_803F08E4(s8 *quest_vm_down_load_server);

s32 TQuestVmDownLoadServer__sub_803F09A4(void);

s32 TQuestVmDownLoadServer__sub_803F09FC(void *arg0, int arg1, int arg2);

s32 TQuestVmDownLoadServer__sub_803F0BD8(void * _w0);

s32 TQuestVmDownLoadServer__sub_803F0BE0(void * _w0, void * _w1);

void TQuestVmDownLoadServer__sub_803F0BE8(u8 *arg0);

void TQuestVmDownLoadServer__sub_803F0C04(u32 aram_addr, s32 size, u32 owner, u32 priority, u32 timeout_ms);

}

extern u16 lbl_805A02A8[0x4C];
extern u16 lbl_805A0340[0x98];
extern RecoveredGlobal_803E6ACC_lbl_805A0470 lbl_805A0470;
extern QuestDownloadInputEntry quest_download_entry_table[39];
extern RecoveredGlobal_803E6ACC_lbl_805A05D0 lbl_805A05D0;
extern QuestDownloadRequestStorage lbl_805A0698;
extern u8 quest_download_aram_dma_buffer[0x2060];

#endif
