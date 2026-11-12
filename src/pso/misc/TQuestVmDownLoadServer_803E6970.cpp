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
s32 TQuestVmDownLoadServer__sub_803E7098(u8 *p, u16 code);
extern u16 quest_download_char_code_table[];
s32 TQuestVmDownLoadServer__sub_803EC69C(int);
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

s32 TQuestVmDownLoadServer__sub_803E6970(s32 start, s32 count, u16 *buf, s32 flag) {
    QuestDownloadInputEntry *e;
    u16 *dst;
    QuestDownloadInputEntry *end;
    u16 *q;
    s32 hit;
    u16 c;
    s32 n;
    e = quest_download_entry_table + start;
    end = quest_download_entry_table + (start + count);
    dst = buf;
    hit = 0;
    while (e < end) {
        if (e == lbl_805D78C8) {
            for (q = (u16 *)quest_download_buffer_start; q < (u16 *)quest_vm_download_buffer_end; q++) {
                c = *q;
                if (c & 0x4000) {
                    c = TQuestVmDownLoadServer__sub_803E721C(c);
                } else {
                    c = (u8)c;
                }
                if (flag != 0 && q == (u16 *)lbl_805D78D0) {
                    n = TQuestVmDownLoadServer::encode_char_with_attr(dst, c, 8);
                    flag = 0;
                } else {
                    n = TQuestVmDownLoadServer::encode_char_with_attr(dst, c, 4);
                }
                dst += n;
            }
            hit = 1;
        }
        if (e >= lbl_805D78C4) {
            break;
        }
        if (flag != 0 && hit != 0) {
            n = TQuestVmDownLoadServer::encode_char_with_attr(dst, e->ch, 8);
            flag = 0;
        } else {
            n = TQuestVmDownLoadServer::encode_char_with_attr(dst, e->ch, 4);
        }
        dst += n;
        hit = 0;
        e++;
    }
    if (flag != 0) {
        dst += TQuestVmDownLoadServer::encode_char_with_attr(dst, 0x20, 8);
    }
    return dst - buf;
}

void TQuestVmDownLoadServer__sub_803E6ACC(s32 arg0) {
    quest_download_server_state = TQuestVmDownLoadServer::get_download_state();
    TQuestVmDownLoadServer::init_block_free_list();
    TQuestVmDownLoadServer::init_entries();
    quest_download_buffer_ptr = &lbl_805A05D0.value;
    lbl_805D78D0 = &lbl_805A05D0.value;
    quest_download_buffer_start = &lbl_805A05D0.value;
    quest_vm_download_buffer_end = &lbl_805A05D0.value;
    lbl_805D78C4 = quest_download_entry_table;
    lbl_805D78C8 = quest_download_entry_table;
    lbl_805D78B8 = lbl_805A0470.bytes;
    lbl_805D78BC = lbl_805A0470.bytes;
    lbl_805D78C0 = 0;
    TQuestVmDownLoadServer__sub_803EAE84(0, 0x50, (void *)(0));
    TQuestVmDownLoadServer__sub_803EE2E4();
    if (arg0 == 1) {
        quest_download_match_length_limit = 0x23;
        lbl_805D7848 = 1;
    }
}


void TQuestVmDownLoadServer__sub_803E6B70(u8 *dst, s32 start, s32 count, s32 mode) {
    s32 TQuestVmDownLoadServer__sub_803E6F98(u16 arg0);
    s32 TQuestVmDownLoadServer__sub_803E7018(u16 arg0);
    QuestDownloadInputEntry *e;
    QuestDownloadInputEntry *end;
    u16 c;
    u16 prev;
    s32 i;
    s32 last;
    u16 *p;

    if (mode >= 5) {
        s32 j;
        e = quest_download_entry_table;
        i = 0;
        j = 0;
        while (j < start) {
            i += e->len;
            j++;
            e++;
        }
        last = i;
        j = 0;
        while (j < count) {
            last += e->len;
            j++;
            e++;
        }
        p = (u16 *)&lbl_805A05D0 + i;
        for (; i < last; i++) {
            if (mode == 5) {
                u16 k = TQuestVmDownLoadServer::jis_to_sjis(TQuestVmDownLoadServer__sub_803E721C(*p++ | 0x100));
                dst[0] = k >> 8;
                dst[1] = k;
                dst += 2;
            } else if (mode == 6) {
                *dst++ = *p++;
            }
        }
        *dst = 0;
        return;
    }
    e = quest_download_entry_table + start;
    end = e + count;
    prev = 0;
    for (; e < end; e++) {
        c = e->ch;
        if (mode == 1) {
            if (!(c & 0xFF00)) {
                if (c == 0xDE && TQuestVmDownLoadServer__sub_803E7018(prev) != 0) {
                    dst -= 2;
                    if (prev == 0x2426) {
                        c = 0x2474;
                    } else {
                        c = prev + 1;
                    }
                } else if (c == 0xDF && TQuestVmDownLoadServer__sub_803E6F98(prev) != 0) {
                    dst -= 2;
                    c = prev + 2;
                } else {
                    c = TQuestVmDownLoadServer__sub_803E721C(c);
                }
            }
            if ((c & 0xFF00) == 0x2500) {
                c &= 0x24FF;
            }
        } else if (mode == 2) {
            if (!(c & 0xFF00)) {
                if (c == 0xDE && TQuestVmDownLoadServer__sub_803E7018(prev) != 0) {
                    dst -= 2;
                    if (prev == 0x2526) {
                        c = 0x2574;
                    } else {
                        c = prev + 1;
                    }
                } else if (c == 0xDF && TQuestVmDownLoadServer__sub_803E6F98(prev) != 0) {
                    dst -= 2;
                    c = prev + 2;
                } else {
                    c = TQuestVmDownLoadServer__sub_803E721C(c | 0x100);
                }
            }
            if ((c & 0xFF00) == 0x2400) {
                c |= 0x2500;
            }
        } else if (mode == 3) {
            dst += TQuestVmDownLoadServer__sub_803E7098(dst, c);
            continue;
        } else if (mode == 4) {
            if (!(c & 0xFF00)) {
                c = TQuestVmDownLoadServer__sub_803E721C(c | 0x100);
            }
        }
        prev = c;
        if (c & 0xFF00) {
            u16 k = TQuestVmDownLoadServer::jis_to_sjis(c);
            *dst++ = k >> 8;
            c = k;
        }
        *dst++ = c;
    }
    *dst = 0;
}

#pragma push
#pragma opt_common_subs off
typedef char RecoveredGlobal_803E6ED0_lbl_805A05D0_size[sizeof(RecoveredGlobal_803E6ED0_lbl_805A05D0) == 0xC8 ? 1 : -1];
void TQuestVmDownLoadServer::init_buffer_pointers() {
    quest_download_buffer_ptr = &(*(RecoveredGlobal_803E6ED0_lbl_805A05D0 *)&lbl_805A05D0).value;
    lbl_805D78D0 = &(*(RecoveredGlobal_803E6ED0_lbl_805A05D0 *)&lbl_805A05D0).value;
    quest_download_buffer_start = &(*(RecoveredGlobal_803E6ED0_lbl_805A05D0 *)&lbl_805A05D0).value;
    quest_vm_download_buffer_end = &(*(RecoveredGlobal_803E6ED0_lbl_805A05D0 *)&lbl_805A05D0).value;
    lbl_805D78C4 = quest_download_entry_table;
    lbl_805D78C8 = quest_download_entry_table;
    lbl_805D78B8 = lbl_805A0470.bytes;
    lbl_805D78BC = lbl_805A0470.bytes;
    lbl_805D78C0 = 0;
    TQuestVmDownLoadServer__sub_803EAE84(0, 0x50, (void *)(0));
    TQuestVmDownLoadServer__sub_803EE2E4();
}
#pragma pop

s32 TQuestVmDownLoadServer::get_buffer_size() {
    return 0x48;
}


s32 TQuestVmDownLoadServer::lookup_value_by_key(u16 arg0) {
    E_803E6F48 *p;
    for (p = jis_to_single_byte_symbol_table; p < jis_to_single_byte_symbol_table + 45; p++) {
        if (p->key == arg0) {
            return p->val;
        }
        if (p->key > arg0) {
            break;
        }
    }
    return 0;
}

bool TQuestVmDownLoadServer__sub_803E6F98(s32 arg0) {
    u8 spC;
    s32 code;
    s32 TQuestVmDownLoadServer__sub_803E7098(void *, int);
    code = arg0;
    if (TQuestVmDownLoadServer__sub_803ECC7C(arg0) != 0) {
        code = TQuestVmDownLoadServer__sub_803EC69C(code);
    }
    if (TQuestVmDownLoadServer__sub_803E7098(&spC, code) != 1) {
        return 0;
    }
    return (lbl_8047F8B8[spC] & 0xF) == 0xB;
}

bool TQuestVmDownLoadServer__sub_803E7018(s32 arg0) {
    u8 spC;
    s32 code;
    s32 TQuestVmDownLoadServer__sub_803E7098(void *, int);
    code = arg0;
    if (TQuestVmDownLoadServer__sub_803ECC7C(arg0) != 0) {
        code = TQuestVmDownLoadServer__sub_803EC69C(code);
    }
    if (TQuestVmDownLoadServer__sub_803E7098(&spC, code) != 1) {
        return 0;
    }
    return (lbl_8047F8B8[spC] & 0xF) == 0xA;
}

s32 TQuestVmDownLoadServer__sub_803E7098(u8 *p, u16 code) {
    u32 c;
    s32 w = code;

    switch (code & 0xFF00) {
    case 0x2300:
    case 0x0:
        *p = w;
        return 1;
    case 0x2500:
        code &= 0x24FF;
    case 0x2400:
    case 0x2100:
        c = TQuestVmDownLoadServer__sub_803EC8D8(code);
        if ((u8)c < 0x98 || (u8)c >= 0xF7) {
            *p = c;
            return 1;
        }
        code = quest_download_char_code_table[(u8)c - 0x98];
        *p++ = code;
        if (code & 0x8000) {
            *p = 0xDE;
            return 2;
        }
        if (code & 0x4000) {
            *p = 0xDF;
            return 2;
        }
        return 1;
    default:
        *p = 0x20;
        return 1;
    }
}

s32 TQuestVmDownLoadServer__sub_803E719C(u8 arg0, s32 arg1) {
    return arg0 | ((arg1 & 0x100) + 0x2400);
}

typedef char RecoveredGlobal_803E721C_lbl_8047E698_size[sizeof(RecoveredGlobal_803E721C_lbl_8047E698) == 0x200 ? 1 : -1];

u16 TQuestVmDownLoadServer::map_key_to_code(u32 arg0) {
    u8 *k;
    u16 *v;
    k = lbl_8047E898;
    v = lbl_8047E8A4;
    while (*k != 0) {
        if (*k == (u8)arg0) {
            u16 t = *v;
            if ((t & 0xFF00) == 0x2500 && !(arg0 & 0x100)) {
                return (u8)t | 0x2400;
            }
            return t;
        }
        k++;
        v++;
    }
    return 0;
}

u16 TQuestVmDownLoadServer__sub_803E721C(u16 arg0) {
    u16 temp_r3;
    temp_r3 = *(u16 *)((s8 *)((u8 *)&single_byte_to_jis_table.value + ((arg0 * 2) & 0x1FE)) + 0);
    if (((s32) (temp_r3 & 0xFF00) == 0x2500) && !(arg0 & 0x100)) {
        return (u8) temp_r3 | 0x2400;
    }
    return temp_r3;
}

s32 TQuestVmDownLoadServer::is_valid_item_for_slot(u8 c, u8 k) {
    if (c >= 0xC0) {
        return 1;
    }
    if (c < 0x80) {
        if (c < 0x2D && k != 0) {
            if (c >= 1 && c <= 0xD) {
                c += 0x7F;
            } else {
                c = 0;
            }
            if (c == 0) {
                return 0;
            }
        } else {
            if (c == 0xD || (c >= 0x13 && c <= 0x34) || c == 0x38) {
                return 1;
            }
            return 0;
        }
    }
    switch (c) {
    case 0x8B:
    case 0x8D:
    case 0x93:
    case 0x96:
    case 0x99:
    case 0x9A:
    case 0x9B:
    case 0x9E:
    case 0xA1:
    case 0xA2:
    case 0xA7:
    case 0xA8:
    case 0xB1:
        if ((k >= 5 && k <= 8) || k >= 0xA) {
            return 1;
        }
        break;
    case 0x97:
        if (k == 8) {
            return 0;
        }
    case 0x8E:
    case 0x92:
    case 0x94:
    case 0x95:
    case 0x98:
    case 0xA0:
        if (k >= 5) {
            return 1;
        }
        break;
    default:
        if (k == 4 || (u8)(k - 7) <= 1 || k >= 0xA) {
            return 1;
        }
        break;
    }
    return 0;
}

struct Row_803E7390 { s16 single; s16 pair; };

static const u8 glyph_bits[0x3E0] = {
    0x00, 0x08, 0x76, 0xE8, 0x4F, 0xEE, 0xDC, 0x00, 0x08, 0x76, 0xF8, 0xFF, 0xFF, 0xDD, 0x00, 0x08,
    0x76, 0xF8, 0xEF, 0xFF, 0xDD, 0x00, 0x08, 0x76, 0xF8, 0xCF, 0xFF, 0xCC, 0x00, 0x08, 0x76, 0xE8,
    0xCF, 0xEB, 0x5D, 0x00, 0x04, 0x38, 0xF4, 0x27, 0x77, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58,
    0x10, 0x00, 0x81, 0x0E, 0x30, 0x01, 0x8C, 0x0A, 0x80, 0x40, 0x87, 0xFE, 0x64, 0x4E, 0x05, 0x40,
    0xA0, 0x03, 0x6C, 0x04, 0xA3, 0x02, 0x20, 0xD0, 0x01, 0x00, 0x80, 0x51, 0x01, 0x10, 0xE8, 0xD0,
    0x97, 0xDD, 0xBB, 0x00, 0x08, 0x74, 0x00, 0x01, 0x20, 0x40, 0x00, 0x04, 0x3A, 0xF4, 0x67, 0x31,
    0x2E, 0x00, 0x02, 0x1D, 0xFA, 0xB3, 0x19, 0x15, 0x00, 0x01, 0x0E, 0x3D, 0x09, 0x8C, 0x0A, 0x80,
    0x40, 0x87, 0xBC, 0x68, 0x56, 0x05, 0x40, 0xA0, 0x43, 0x1B, 0x36, 0xAF, 0x02, 0x20, 0xD0, 0x01,
    0x26, 0x81, 0x77, 0x01, 0x10, 0xE8, 0x40, 0x90, 0xCC, 0xAA, 0x00, 0x08, 0x74, 0x28, 0x08, 0x60,
    0x54, 0x00, 0x04, 0x3A, 0xC4, 0x2C, 0xF3, 0x3F, 0x00, 0x02, 0x1D, 0x6A, 0x92, 0x79, 0x17, 0x00,
    0x00, 0x00, 0xFF, 0xFD, 0xBF, 0x03, 0x00, 0x00, 0xC0, 0x0A, 0x00, 0x3B, 0x00, 0x00, 0x00, 0xA4,
    0x60, 0xB3, 0x03, 0x20, 0x00, 0x40, 0x02, 0x06, 0x3B, 0x00, 0xFE, 0x01, 0x00, 0x20, 0x00, 0x00,
    0x01, 0x48, 0x50, 0x60, 0x00, 0x00, 0x02, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x1F,
    0x00, 0x00, 0x00, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0xA0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,
    0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x00, 0x81, 0x0E, 0x00, 0x01,
    0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x02, 0x1D, 0x00, 0x20, 0x18, 0x15, 0x89, 0x40, 0x00, 0x02,
    0x10, 0x80, 0x00, 0x37, 0x20, 0x00, 0x01, 0x08, 0x40, 0x40, 0x02, 0x18, 0x80, 0x40, 0x04, 0x20,
    0x00, 0x03, 0x00, 0x20, 0x00, 0x00, 0x01, 0x08, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x08, 0x20, 0x10, 0x01,
    0x18, 0xC0, 0x00, 0x10, 0x00, 0x00, 0x02, 0x00, 0x00, 0x01, 0x04, 0x08, 0x00, 0x03, 0x12, 0x00,
    0x80, 0x40, 0x00, 0x02, 0x00, 0x43, 0x11, 0x80, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x20, 0x00,
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x04, 0x40, 0x00, 0x00, 0x80, 0x00, 0x04,
    0x20, 0x00, 0x01, 0x08, 0x40, 0x00, 0x02, 0x10, 0x80, 0x00, 0x00, 0x20, 0x00, 0x01, 0x08, 0x40,
    0x00, 0x02, 0x10, 0x80, 0x00, 0x04, 0x28, 0x00, 0x00, 0x08, 0x40, 0x00, 0x02, 0x10, 0x80, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01,
    0x11, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
    0x10, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x14, 0x41, 0x00, 0x02, 0x10, 0x80, 0x00, 0x04, 0x08, 0x80, 0x03, 0x00, 0x40, 0x00,
    0x00, 0x10, 0x80, 0x00, 0x02, 0x50, 0x40, 0x00, 0x06, 0x30, 0x80, 0x00, 0x08, 0xC0, 0x00, 0x04,
    0x00, 0x00, 0x01, 0x00, 0x90, 0x00, 0x03, 0x10, 0x80, 0x00, 0x05, 0xA0, 0x00, 0x06, 0x30, 0x00,
    0x00, 0x00, 0x80, 0x08, 0x02, 0x34, 0xC0, 0x00, 0x08, 0x20, 0x40, 0x00, 0x08, 0x00, 0x00, 0x02,
    0x24, 0x00, 0x01, 0x0C, 0x40, 0x00, 0x02, 0x10, 0x80, 0x00, 0x04, 0x20, 0x00, 0x01, 0x08, 0x60,
    0x00, 0x02, 0x10, 0x80, 0x00, 0x02, 0x22, 0x80, 0x01, 0x0C, 0x40, 0x00, 0x02, 0x10, 0x20, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x09, 0x40, 0x00, 0x02, 0x10, 0x80, 0x00, 0x00,
    0x00, 0x80, 0x00, 0x08, 0x00, 0x00, 0x02, 0x18, 0x40, 0x00, 0x02, 0x30, 0x80, 0x02, 0x08, 0xC0,
    0x50, 0x04, 0x20, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x01, 0x0A, 0x40, 0x00, 0x02, 0x10, 0x00, 0x00, 0x04, 0x20, 0x00, 0x01, 0x08, 0x40,
    0x00, 0x02, 0x00, 0xA0, 0x20, 0x01, 0x08, 0x40, 0x00, 0x20, 0x00, 0x01, 0x09, 0x40, 0x00, 0x02,
    0x10, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x40, 0x02, 0x18, 0x00, 0x00, 0x00, 0x22,
    0x00, 0x01, 0x08, 0x40, 0x00, 0x02, 0x10, 0x80, 0x00, 0x04, 0x20, 0x00, 0x00, 0x08, 0x40, 0x00,
    0x02, 0x10, 0x80, 0x00, 0x04, 0x20, 0x00, 0x01, 0x09, 0x40, 0x00, 0x02, 0x10, 0x80, 0x00, 0x03,
    0x20, 0x00, 0x00, 0x08, 0x00, 0x40, 0x00, 0x18, 0x88, 0x40, 0x00, 0x22, 0x10, 0x80, 0x00, 0x04,
    0x20, 0x00, 0x01, 0x09, 0x40, 0x00, 0x02, 0x10, 0x80, 0x00, 0x22, 0x20, 0x00, 0x00, 0x08, 0x00,
    0x40, 0x02, 0x18, 0x80, 0x00, 0x04, 0x20, 0x50, 0x82, 0x10, 0x84, 0x20, 0x00, 0x40, 0x00, 0x02,
    0x10, 0x80, 0x00, 0x04, 0x20, 0x00, 0x00, 0x00, 0x41, 0x00, 0x40, 0x10, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x80, 0x50, 0x04, 0x20, 0x00, 0x01, 0x10, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x20, 0x01, 0x06, 0x00, 0x00, 0x00, 0x02, 0x01, 0x08, 0x40, 0x00, 0x02, 0x10, 0x80, 0x00, 0x04,
    0x20, 0x00, 0x01, 0x08, 0x40, 0x00, 0x02, 0x18, 0x80, 0x00, 0x04, 0x00, 0x00, 0x00, 0x84, 0x22,
    0x00, 0x01, 0x08, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00,
    0x00, 0x10, 0x48, 0x40, 0x02, 0x10, 0x90, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x00, 0x00,
    0x02, 0x40, 0x00, 0x04, 0x20, 0x20, 0x41, 0x02, 0x10, 0x80, 0x00, 0x04, 0x20, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x46, 0x2A, 0x90, 0x80, 0x0C, 0x24, 0x20, 0xC0, 0x0D, 0x08,
    0x40, 0x00, 0x02, 0x10, 0x90, 0x00, 0x06, 0x20, 0x01, 0x01, 0x48, 0xA4, 0x22, 0x01, 0x09, 0x48,
    0x20, 0x02, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x01, 0x08, 0x60, 0x00, 0x00, 0x00, 0x90, 0x48,
    0x00, 0x02, 0x10, 0x80, 0x00, 0x04, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x12, 0xC0, 0x00,
    0x04, 0x00, 0x00, 0x41, 0x02, 0x10, 0x80, 0x00, 0x04, 0x20, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x80, 0x00, 0x06, 0x20, 0x00, 0x00, 0x08, 0x12, 0x80, 0x00, 0x04, 0x20, 0x40, 0x01, 0x04,
    0x00, 0x00, 0x00, 0x10, 0x00, 0x80, 0x04, 0x38, 0x00, 0x01, 0x00, 0x40, 0x90, 0x00, 0x04, 0x20,
    0x00, 0x01, 0x08, 0x00, 0x02, 0x02, 0x10, 0x80, 0x00, 0x00, 0x24, 0x80, 0x01, 0x08, 0x40, 0x00,
    0x02, 0x24, 0x00, 0x01, 0x08, 0x40, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x08,
    0x60, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x40, 0x00, 0x04, 0x3A, 0xF4, 0x67, 0xB3, 0x6A, 0x00,
};

static const Row_803E7390 glyph_rows[0x72] = {
    { 2086, 4095 }, { 1214, 4095 }, { 1159, 2141 }, { 1104, 3370 }, { 1049, 6416 }, { 1104, 3370 },
    { 1104, 6579 }, { 994, 3370 }, { 939, 7032 }, { 884, 3554 }, { 2375, 5221 }, { 2375, 5221 },
    { 2375, 5221 }, { 2375, 5221 }, { 1899, 3600 }, { 2375, 2790 }, { 1899, 3987 }, { 2375, 3201 },
    { 1899, 3987 }, { 7871, 3120 }, { 2005, 2538 }, { 1927, 2276 }, { 2375, 4734 }, { 2375, 4734 },
    { 2375, 2919 }, { 1807, 2920 }, { 829, 5110 }, { 774, 5908 }, { 774, 5908 }, { 774, 7195 },
    { 774, 7032 }, { 719, 5309 }, { 664, 7032 }, { 609, 3763 }, { 774, 7032 }, { 554, 7032 },
    { 499, 6579 }, { 444, 3897 }, { 389, 7358 }, { 774, 4547 }, { 774, 4957 }, { 168, 7521 },
    { 168, 7521 }, { 112, 5525 }, { 2375, 6066 }, { 1940, 5221 }, { 334, 5221 }, { 1269, 5437 },
    { 1269, 5437 }, { 56, 2141 }, { 56, 2141 }, { 56, 6707 }, { 2375, 4194 }, { 1807, 2920 },
    { 1807, 3030 }, { 1852, 2856 }, { 1775, 2318 }, { 1731, 2318 }, { 1688, 2837 }, { 1642, 2837 },
    { 1915, 2318 }, { 1914, 2318 }, { 1913, 2318 }, { 1596, 2318 }, { 1595, 2318 }, { 1594, 4341 },
    { 1593, 2318 }, { 1592, 2318 }, { 1591, 2318 }, { 1590, 2318 }, { 1589, 2318 }, { 1588, 2318 },
    { 1527, 2463 }, { 1575, 2318 }, { 1871, 2318 }, { 1927, 2325 }, { 1688, 2318 }, { 2042, 2318 },
    { 2375, 3701 }, { 1927, 2680 }, { 2375, 4341 }, { 1478, 6871 }, { 1478, 6871 }, { 1899, 3600 },
    { 2375, 2790 }, { 1899, 2726 }, { 279, 3370 }, { 279, 4413 }, { 0, 2437 }, { 0, 4413 },
    { 1426, 4893 }, { 1927, 4265 }, { 1899, 5686 }, { 1899, 2726 }, { 1927, 2341 }, { 1959, 5735 },
    { 1959, 5735 }, { 224, 7687 }, { 1899, 3427 }, { 2375, 4341 }, { 1927, 4265 }, { 1374, 2768 },
    { 1374, 2318 }, { 1871, 2318 }, { 1871, 2318 }, { 1871, 2318 }, { 1478, 6255 }, { 1852, 2856 },
    { 1899, 4604 }, { 2375, 6187 }, { 1919, 2318 }, { 1322, 3272 }, { 1574, 3370 }, { 1927, 3427 },
};

static const u8 glyph_col[0x100] = {
    0xFF, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0xFF, 0x0B, 0x0C, 0x0D,
    0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x14, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16,
    0xFF, 0xFF, 0xFF, 0x17, 0x18, 0x19, 0x1A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x16, 0x14, 0x12, 0x0C, 0x00, 0x07, 0x16, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x0B, 0x16, 0x21, 0x2C, 0x37, 0x42,
    0x21, 0x21, 0x37, 0x4D, 0x58, 0x58, 0x2C, 0x63, 0x6E, 0x4D, 0x6E, 0x79, 0x6E, 0x42, 0x84, 0x8F,
    0x37, 0x4D, 0x2C, 0x21, 0x21, 0x6E, 0x9A, 0x21, 0x21, 0x9A, 0x9A, 0x21, 0x9A, 0x9A, 0xA5, 0xB0,
    0x9A, 0x2C, 0x9A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x25, 0x25, 0x25, 0x26, 0x26,
    0x27, 0x27, 0x28, 0x28, 0x29, 0x2A, 0x2B, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x2F, 0x2F, 0x2E, 0x2E,
    0x30, 0x31, 0x2E, 0x32, 0x32, 0x33, 0x32, 0x32, 0x32, 0x34, 0x24, 0x35, 0x35, 0x35, 0x35, 0x35,
    0x35, 0x35, 0x35, 0x24, 0x24, 0x36, 0x36, 0x37, 0x36, 0x36, 0x38, 0x36, 0x09, 0x09, 0x39, 0xFF,
};

s32 TQuestVmDownLoadServer__sub_803E7390(u8 a, u8 b, u8 c) {
    u8 col;
    const Row_803E7390 *row;
    s16 bit;
    if (c < 0x80) {
        return 0;
    }
    if (a < 0x2D && b != 0) {
        if (a >= 1 && a <= 0xD) {
            a += 0x7F;
        } else {
            a = 0;
        }
        if (a == 0) {
            return 0;
        }
    }
    col = glyph_col[a];
    if ((s16)col == 0xFF) {
        return 0;
    }
    if (c >= 0xC0) {
        row = &glyph_rows[c - 0xC0];
    } else {
        row = &glyph_rows[c - 0x41];
    }
    if (a < 0x80 || a >= 0xC0) {
        bit = row->single + col;
        return glyph_bits[bit >> 3] & lbl_805E10C8[bit & 7];
    }
    bit = row->pair + col + b - 1;
    return glyph_bits[bit >> 3] & lbl_805E10C8[bit & 7];
}

void TQuestVmDownLoadServer::invalidate_entries_by_id(s32 id) {
    s32 i;
    for (i = 0; i < 128; i++) {
        if (id == quest_download_slot_table.entries[i].cachedId) {
            quest_download_slot_table.entries[i].cachedId = -1;
        }
    }
}

void TQuestVmDownLoadServer::clear_entries_by_id(s32 id) {
    s32 i;
    for (i = 0; i < 128; i++) {
        if (id == (s16)(quest_download_slot_table.entries[i].cachedId >> 12)) {
            quest_download_slot_table.entries[i].cachedId = -1;
        }
    }
}

s32 TQuestVmDownLoadServer::release_ref_slot(u32 arg0) {
    QuestDownloadCacheEntry *r;
    if (arg0 >= 0x80U) {
        return -1;
    }
    r = &quest_download_slot_table.entries[arg0];
    if (r->referenceCount == 0) {
        return -1;
    }
    r->referenceCount--;
    return 0;
}

s32 TQuestVmDownLoadServer::set_slot_values_for_indices(s32 *arg0, s32 arg1, u32 arg2) {
    s32 i;
    for (i = 0; i < arg1; i++, arg0++) {
        s32 idx = *arg0;
        if (idx >= 0 && idx < 0x80 && quest_download_slot_table.entries[idx].referenceCount != 0) {
            quest_download_slot_table.entries[idx].value = (u8)arg2;
        }
    }
    return 0;
}

s32 TQuestVmDownLoadServer::get_max_size_of_indices(s32 arg1) {
    s32 *arg0 = (s32 *)this;
    s32 i;
    s32 max = 0;
    for (i = 0; i < arg1; i++) {
        s32 idx = arg0[i];
        if (idx >= 0 && idx < 0x80) {
            QuestDownloadCacheEntry *r = &quest_download_slot_table.entries[idx];
            if (r->referenceCount != 0) {
                if (max < r->value) {
                    max = r->value;
                }
            }
        }
    }
    return max;
}

s32 TQuestVmDownLoadServer__sub_803E779C(u32 arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    QuestDownloadCacheEntry *r;
    if (arg0 >= 0x80U) {
        return -1;
    }
    r = &quest_download_slot_table.entries[arg0];
    if (r->referenceCount == 0) {
        return -1;
    }
    *arg1 = r->fileOffset;
    *arg2 = r->cachedId;
    *arg3 = r->value;
    return r->pageIndex;
}

u32 TQuestVmDownLoadServer::acquire_slot_entry(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    QuestDownloadCacheEntry *r;
    s32 free_idx;
    r = quest_download_slot_table.entries;
    free_idx = -1;
    for (i = 0; i < 128; i++, r++) {
        if (r->referenceCount == 0) {
            if (free_idx == -1) {
                free_idx = i;
            }
        } else if (r->pageIndex == arg0 && r->fileOffset == arg1 && r->cachedId == arg2) {
            r->referenceCount++;
            return i;
        }
    }
    if (free_idx == -1) {
        return -1;
    }
    r = &quest_download_slot_table.entries[free_idx];
    r->referenceCount = 1;
    r->pageIndex = arg0;
    r->fileOffset = arg1;
    r->cachedId = arg2;
    r->value = arg3;
    return free_idx;
}

void TQuestVmDownLoadServer__sub_803E79AC(void) {
    int i;
    for (i = 0; i < 0x80; i++) {
        quest_download_slot_table.entries[i].referenceCount = 0;
    }
}


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
void TQuestVmDownLoadServer::retry_seek_active_entries() {
    QuestDownloadCachePage *e;
    u8 unused[0x18];
    for (e = file_page_cache_head; e != NULL; e = e->next) {
        if (e->state == 1) {
            SeekRetry_803E7ACC((e->pageIndex << 10) + 0x3400);
        }
    }
}
#pragma pop

u8 *get_cached_page__22TQuestVmDownLoadServerFi(s32 page) {
    u8 unused[0x38];
    QuestDownloadCachePage *prev = NULL;
    QuestDownloadCachePage *p = file_page_cache_head;

    for (;;) {
        if (p->pageIndex == page) {
            if (prev != NULL) {
                prev->next = p->next;
                p->next = file_page_cache_head;
                file_page_cache_head = p;
            }
            return p->bytes;
        }
        if (p->next == NULL) {
            break;
        }
        prev = p;
        p = p->next;
    }
    prev->next = NULL;
    p->next = file_page_cache_head;
    file_page_cache_head = p;
    if (p->state == 1) {
        if (Seek_803E7B9C(p->pageIndex * 0x400 + 0x3400) != -1) {
            Write_803E7B9C();
        }
    }
    p->pageIndex = page;
    p->state = 0;
    if (Seek_803E7B9C(p->pageIndex * 0x400 + 0x3400) != -1) {
        TQuestVmDownLoadServer::aram_dma_read((void *)lbl_805D7904, p->bytes, 0x400);
    }
    return p->bytes;
}
#pragma pop

void TQuestVmDownLoadServer::set_active() {
    file_page_cache_head->state = 1;
}


s32 TQuestVmDownLoadServer::match_prefix_length(const u8 *a, const u8 *b, s32 n) {
    s32 i;
    for (i = 0; i < n; i++, a++, b++) {
        if (*a != *b) {
            break;
        }
        if (*a == 0) {
            break;
        }
    }
    return i;
}


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

#pragma push
#pragma opt_common_subs off
s32 TQuestVmDownLoadServer::count_matching_name_prefix(s32 arg0, u8 *arg1) {
    u8 *p;
    u8 *q;
    s32 i;
    q = arg1;
    p = quest_name_index_table[arg0];
    for (i = 0; i < 4; i++, p++, q++) {
        u8 c = *p;
        if (c != *q || c == 0) {
            break;
        }
    }
    if (i < 4 && arg1[i] != 0) {
        i++;
    }
    return i;
}
#pragma pop

s32 TQuestVmDownLoadServer::has_name_mismatch(u8 *arg1) {
    s32 arg0 = (s32)this;
    s32 i = match_803E7E3C(quest_name_index_table[arg0 + 1], arg1);
    if (arg1[i] == 0) {
        return 0;
    }
    return 1;
}
#pragma pop

s32 find_name_index__22TQuestVmDownLoadServerFv(const char *name) {
    s32 mid;
    s32 hi;
    s32 lo;
    int r;
    hi = quest_download_name_search_hi;
    lo = quest_download_name_search_lo;
    while (lo + 1 < hi) {
        mid = (hi + lo) / 2;
        r = strncmp(name, (const char *)quest_name_index_table[mid], 4);
        if (r == 0) {
            return mid;
        }
        if (r > 0) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    if (strncmp(name, (const char *)quest_name_index_table[lo], 4) < 0) {
        return lo - 1;
    }
    return lo;
}

void TQuestVmDownLoadServer__sub_803E7F9C(u8 *text, s16 mode) {
    u8 c = *text;
    s32 col;
    s32 row;
    u8 *p;
    s32 index;
    if (c < 0xA1) {
        return;
    }
    p = text + 1;
    row = c - 0xA1;
    if (mode == 1) {
        col = 0;
    } else {
        u8 d = *p;
        if (d < 0xA1) {
            return;
        }
        col = d - 0xA0;
    }
    index = row * 11 + (col >> 3);
    lbl_805D7824[index] |= 1 << (col & 7);
    lbl_805D7820 = 1;
}

s32 TQuestVmDownLoadServer::is_char_allowed(s16 arg1) {
    u8 *arg0 = (u8 *)this;
  int new_var;
  u8 c = *arg0;
  s32 bit;
  s32 rowi;
  u8 *p;
  if (c < 0xA1)
  {
    return 0;
  }
  p = arg0 + 1;
  rowi = c - 0xA1;
  if (arg1 == 1)
  {
    bit = 0;
  }
  else
  {
    u8 d = *p;
    if (1)
    {
      if (d < 0xA1)
      {
        return 0;
      }
    }
    bit = d - 0xA0;
  }
  new_var = (rowi * 0xB) + (bit >> 3);
  if ((1 << (bit & 7)) & lbl_805D7824[new_var])
  {
    return 0;
  }
  return 1;
}

s32 TQuestVmDownLoadServer__sub_803E8084(void) {
  s32 temp_r3;
  s32 var_r0;
  s32 var_r0_2;
  var_r0_2 = 0;
  if (TQuestVmDownLoadServer__sub_803F09FC((void *)((void *) lbl_805D7904), 0x400, (int)((int) var_r0_2)) == (-1))
  {
    temp_r3 = TQuestVmDownLoadServer__sub_803F0BE0((void *) (quest_vm_download_server_file_info), (void *) lbl_805D78F8);
    if (temp_r3 == (-1))
    {
      lbl_805D7904 = (var_r0 = -1);
    }
    else
    {
      lbl_805D7904 = temp_r3;
      var_r0 = 0;
    }
    if (var_r0 != 0)
    {
      var_r0_2 = -1;
    }
    else
    {
      if (lbl_805D78F8)
      {
      }
      if (TQuestVmDownLoadServer__sub_803F09FC((void *)((void *) lbl_805D7904), 0x400, 0) == (-1))
      {
        var_r0_2 = -1;
      }
      else
      {
        goto block_8;
      }
    }
  }
  else
  {
    block_8:
    var_r0_2 = 0;
  }
  if (var_r0_2 == (-1))
  {
    return -1;
  }
  if (((s32)TQuestVmDownLoadServer::aram_dma_read((void *)((void *)((void *) lbl_805D7904)), quest_name_index_table, 0x1000)) != 0x1000)
  {
    return -1;
  }
  return 0;
}

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
s32 TQuestVmDownLoadServer__sub_803E8150(void) {
    u8 *p = lbl_80591AC4 + 0x30;
    if (lbl_805D7874 == quest_download_ask_header_size && lbl_805D78FC == quest_download_header_name_index_hi_count && lbl_805D7820 == 0) {
        return 0;
    }
    p[0] = lbl_805D7874 % 256;
    p[1] = lbl_805D7874 / 256;
    p[2] = lbl_805D7900 % 256;
    p[3] = lbl_805D7900 / 256;
    p[4] = lbl_805D78FC % 256;
    p[5] = lbl_805D78FC / 256;
    if (Seek_803E8150(0) == -1) {
        return -1;
    }
    return Write_803E8150();
}
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
s32 TQuestVmDownLoadServer::read_ask_header() {
    Buf_803E82AC *b = (Buf_803E82AC *)&quest_vm_download_server_file_info;
    u8 *h;
    u8 unused[0x18];
    if (Seek_803E82AC((Buf_803E82AC *)&quest_vm_download_server_file_info, 0) == -1) {
        return -1;
    }
    if ((s32)TQuestVmDownLoadServer::aram_dma_read((void *)lbl_805D7904, (b)->hdr, 0x400) != 0x400) {
        return -1;
    }
    h = (b)->hdr;
    if (strncmp((char *)h, ask_header_signature, strlen(ask_header_signature)) != 0) {
        return -1;
    }
    quest_download_name_search_lo = 0;
    quest_download_name_search_hi = h[0x2E] + (h[0x2F] << 8);
    quest_download_ask_header_size = lbl_805D7874 = h[0x30] + (h[0x31] << 8);
    quest_download_header_name_index_hi_count = lbl_805D78FC = h[0x34] + (h[0x35] << 8);
    lbl_805D7820 = 0;
    return 0;
}
#pragma pop

void TQuestVmDownLoadServer::init_page_cache() {
    Cache_803E840C *c;
    QuestDownloadCachePage *p;
    QuestDownloadCacheEntry *e;
    u32 i;
    c = (Cache_803E840C *)&quest_vm_download_server_file_info;
    file_page_cache_head = p = c->pages;
    for (; p < &c->pages[9]; p++) {
        p->pageIndex = -1;
        p->state = 0;
        p->next = p + 1;
    }
    p->pageIndex = -1;
    p->state = 0;
    p->next = NULL;
    e = c->ents;
    for (i = 0; i < 128; i++) {
        e[i].referenceCount = 0;
    }
}

s32 TQuestVmDownLoadServer::seek_or_reopen(int pos) {
    u8 unused[8];
    if (Seek_803E8624(lbl_805D7904, pos, 0) == -1) {
        if (Open_803E8624() != 0) {
            return -1;
        }
        if (Seek_803E8624(lbl_805D7904, pos, 0) == -1) {
            return -1;
        }
    }
    return 0;
}
#pragma pop

s32 TQuestVmDownLoadServer__sub_803E86C8(void) {
    if (TQuestVmDownLoadServer__sub_803F0BD8((void *)lbl_805D7904) == -1) {
        lbl_805D7904 = -1;
        return -1;
    }
    lbl_805D7904 = -1;
    return 0;
}

s32 TQuestVmDownLoadServer::find_file_info_index() {
    s32 temp_r3;
    temp_r3 = TQuestVmDownLoadServer__sub_803F0BE0((void *)((void *)quest_vm_download_server_file_info), (void *)lbl_805D78F8);
    if (temp_r3 == -1) {
        lbl_805D7904 = -1;
        return -1;
    }
    lbl_805D7904 = temp_r3;
    return 0;
}


#pragma push
#pragma opt_common_subs off
void TQuestVmDownLoadServer::set_file_info_name() {
    s32 arg0 = (s32)this;
    strcpy((void *) (quest_vm_download_server_file_info), (void *)arg0);
}
#pragma pop

s32 TQuestVmDownLoadServer__sub_803E8788(int _w0, void * _w1, int _w2) {
    return -1;
}

// Provisional native link name: the first word is the provider's opaque
// handle, not a TQuestVmDownLoadServer receiver.
u32 aram_read_thunk__22TQuestVmDownLoadServerFUli(void *handle, void *dst, s32 size) {
    return TQuestVmDownLoadServer::aram_dma_read(handle, dst, size);
}

void TQuestVmDownLoadServer::unescape_copy_string(u8 *arg0, u8 *arg1, u8 *arg2) {
    while (arg1 < arg2 && *arg1 > 0x38) {
        if (*arg1 == 0xFF) {
            arg1++;
        } else {
            *arg0++ = *arg1++;
        }
        *arg0++ = *arg1++;
    }
    *arg0 = 0;
}

s32 TQuestVmDownLoadServer::count_entries_until_terminator(const u8 *p, const u8 *end) {
    s32 n = 0;
    while (p < end && *p > 0x38) {
        if (*p == 0xFF) {
            n += 1;
        } else {
            n += 2;
        }
        p += 2;
    }
    return n;
}

void TQuestVmDownLoadServer::copy_sjis_string(u8 *arg0, u8 *arg1) {
    while (*arg0 != 0) {
        u8 c = *arg0;
        s32 lead;
        if ((c >= 0x80 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC)) {
            lead = 1;
        } else {
            lead = 0;
        }
        if (lead) {
            *arg1++ = *arg0++;
        } else {
            *arg1++ = 0xFF;
        }
        *arg1++ = *arg0++;
    }
}

s32 TQuestVmDownLoadServer::calc_sjis_string_width(u8 *arg0) {
    s32 n = 0;
    while (*arg0 != 0) {
        u8 c = *arg0;
        s32 lead;
        if ((c >= 0x80 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC)) {
            lead = 1;
        } else {
            lead = 0;
        }
        if (lead) {
            arg0 += 2;
        } else {
            arg0 += 1;
        }
        n += 2;
    }
    return n;
}

void TQuestVmDownLoadServer__sub_803E8918(void) {
    lbl_805D7868 = 1;
}

// Move the indexed record to the append page, preserving native reservation
// and identity-check order. See the lifecycle evidence for unchecked preconditions.
void TQuestVmDownLoadServer__sub_803E8924(s32 id) {
    char name[0x50];
    s16 sourcePage = (s16)(id >> 12);
    u8 *source;
    u8 *original;
    u8 *destination;
    s32 length;
    u8 len;
    s16 wanted;
    s32 bucket;
    QuestDownloadCachedNameNode *node;

    if (lbl_805D7874 == sourcePage) {
        return;
    }
    source = lbl_80591EC8 + sourcePage * 0x400 + (s16)(id & 0xFFF);
    original = source;
    if (lbl_805D7870 > lbl_805D786C - (length = (u16)(source[0] + (source[1] << 8))) - 2) {
        TQuestVmDownLoadServer__sub_803E95BC();
    }
    destination = lbl_805D7870;
    lbl_805D7870 += length;
    lbl_805D7870[0] = 0;
    lbl_805D7870[1] = 0;
    if (sourcePage == lbl_805D7874) {
        return;
    }
    len = source[2];
    strncpy(name, (const char *)(source + 3), (s16)len);
    name[(s16)len] = 0;
    u8 first = (u8)name[0];
    if (first >= 0xA0 && first < 0xF0) {
        bucket = first - 0xA0;
    } else {
        bucket = 0;
    }
    node = lbl_80593EC8.heads[bucket];
    wanted = (s16)len;
    for (; node != NULL; node = node->next) {
        u8 *indexed = node->encodedRecord;
        len = indexed[2];
        s32 comparison = strncmp((const char *)(indexed + 3), name, (s16)len);
        if (comparison == 0) {
            if (wanted == (s16)len) {
                break;
            }
        } else if (comparison > 0) {
            break;
        }
    }
    // Native code also requires a non-null stopping node at this point.
    if (node->encodedRecord == original) {
        node->encodedRecord = destination;
        for (; length != 0; length--) {
            *destination++ = *source++;
        }
        original[2] = 0;
        TQuestVmDownLoadServer::invalidate_entries_by_id(id);
    }
}



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
s32 lookup_name_entry__22TQuestVmDownLoadServerFPvsPv(char *arg0, s16 arg1, Out_803E8B1C *arg2) {
    QuestDownloadCachedNameNode *n;
    s32 r;
    u8 len;
    s32 off;
    u8 unused[8];
    u8 *e;
    for (n = lbl_80593EC8.heads[Hash_803E8B1C(arg0)]; n != NULL; n = n->next) {
        e = n->encodedRecord;
        len = e[2];
        r = strncmp((const char *)(e + 3), arg0, (s16)len);
        if (r == 0) {
            if ((s16)len == arg1) {
                break;
            }
        } else if (r > 0) {
            arg2->id = -1;
            return 0;
        }
    }
    if (n == NULL) {
        arg2->id = -1;
        return 0;
    }
    off = (u8 *)e - (u8 *)&lbl_80591EC8;
    arg2->a = 0;
    arg2->id = ((off / 1024) << 12) | (off % 1024);
    arg2->ent = e;
    return 1;
}
#pragma pop

s32 TQuestVmDownLoadServer__sub_803E8C2C(char *arg0, s16 arg1, Out_803E8C2C *arg2) {
    QuestDownloadCachedNameNode *n;
    u8 *e;
    s16 len;
    u8 *found;
    s16 pre;
    s16 blen;
    s32 r;
    s16 m;
    s32 off;
    u8 unused[8];
    blen = 0;
    pre = 0;
    arg2->pre = 0;
    arg2->len = 0;
    for (n = lbl_80593EC8.heads[Hash_803E8C2C(arg0)]; n != NULL; n = n->next) {
        e = n->encodedRecord;
        len = e[2];
        m = TQuestVmDownLoadServer::match_prefix_length(e + 3, (u8 *)arg0, (s16)len);
        if (m >= pre) {
            pre = m + 1;
        }
        r = strncmp((const char *)(e + 3), arg0, (s16)len);
        if (r == 0) {
            if ((s16)len == arg1) {
                return 2;
            }
            blen = len;
            found = e;
        } else if (r > 0) {
            if (strncmp((const char *)(e + 3), arg0, arg1) == 0) {
                return 2;
            }
            break;
        }
    }
    if (blen == 0) {
        arg2->id = -1;
        return 0;
    }
    off = (u8 *)found - (u8 *)&lbl_80591EC8;
    arg2->a = 0;
    arg2->id = ((off / 1024) << 12) | (off % 1024);
    arg2->len = blen;
    arg2->pre = pre;
    arg2->ent = found;
    return 1;
}
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
s32 TQuestVmDownLoadServer__sub_803E8DA0(char *key, Req_803EEF2C *req, s32 value) {
    QuestDownloadCachedNameNode *node;
    QuestDownloadCachedNameNode *previous;
    QuestDownloadCachedNameNode **link;
    QuestDownloadCachedNameNode *reserved;
    u8 *oldRecord;
    u8 *record;
    u8 *p;
    u8 len;
    s16 wanted;
    s32 bucket;
    s32 width;
    s32 length;
    s32 offset;

    size_t cacheAddress = (size_t)lbl_80591EC8;
    u8 *cacheBytes = reinterpret_cast<u8 *>(cacheAddress);
    lbl_805D7868 = 1;
    previous = NULL;
    u8 first = (u8)key[0];
    wanted = req->len;
    if (first >= 0xA0 && first < 0xF0) {
        bucket = first - 0xA0;
    } else {
        bucket = 0;
    }
    node = QUEST_DOWNLOAD_CACHE_INDEX(cacheAddress)->heads[bucket];
    for (; node != NULL; node = node->next) {
        u8 *indexed = node->encodedRecord;
        len = indexed[2];
        s32 comparison = strncmp((const char *)(indexed + 3), key, (s16)len);
        if (comparison == 0) {
            if (wanted == (s16)len) {
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
    // The original also dereferences its stopping node without a null check.
    oldRecord = node->encodedRecord;
    if (oldRecord[2] == req->len
            && strncmp(key, (const char *)(oldRecord + 3), req->len) == 0) {
        oldRecord[2] = 0;
        *link = node->next;
        offset = node->encodedRecord - cacheBytes;
        TQuestVmDownLoadServer::invalidate_entries_by_id(
            ((offset / 0x400) << 12) | (offset % 0x400));
        node->next = lbl_805D7878;
        lbl_805D7878 = node;
    }
    if (lbl_805D7878 == NULL) {
        TQuestVmDownLoadServer__sub_803E95BC();
    }
    reserved = lbl_805D7878;
    lbl_805D7878 = reserved->next;
    if (req->x8 != 0 || req->x7 >= 0x2D) {
        length = 3;
    } else {
        length = 2;
    }
    width = TQuestVmDownLoadServer::calc_sjis_string_width(req->text);
    length = req->len + length + width + 3;
    if (lbl_805D7870 > lbl_805D786C - length - 2) {
        TQuestVmDownLoadServer__sub_803E95BC();
    }
    record = lbl_805D7870;
    lbl_805D7870 += length;
    lbl_805D7870[0] = 0;
    lbl_805D7870[1] = 0;
    p = record;
    *p++ = length % 256;
    *p++ = length / 256;
    *p++ = req->len;
    strncpy((char *)p, req->name, req->len);
    p += req->len;
    *p++ = req->x7;
    *p++ = value;
    if (req->x8 != 0 || req->x7 >= 0x2D) {
        *p++ = req->x8;
    }
    TQuestVmDownLoadServer::copy_sjis_string(req->text, p);

    previous = NULL;
    first = (u8)key[0];
    wanted = req->len;
    if (first >= 0xA0 && first < 0xF0) {
        bucket = first - 0xA0;
    } else {
        bucket = 0;
    }
    node = QUEST_DOWNLOAD_CACHE_INDEX(cacheAddress)->heads[bucket];
    for (; node != NULL; node = node->next) {
        u8 *indexed = node->encodedRecord;
        len = indexed[2];
        s32 comparison = strncmp((const char *)(indexed + 3), key, (s16)len);
        if (comparison == 0) {
            if (wanted == (s16)len) {
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
    reserved->encodedRecord = record;
    reserved->next = node;
    *link = reserved;
    return 0;
}
#pragma pop



void append_message_text__22TQuestVmDownLoadServerFPviPvUc(u8 *arg0, s32 arg1, Msg_803E90A8 *arg2, u8 arg3) {
    u16 cur;
    s32 v;
    u8 *p;
    u8 *s;
    cur = arg0[0];
    cur += arg0[1] << 8;
    v = arg1 + cur;
    arg0[0] = v % 256;
    arg0[1] = v / 256;
    p = arg0 + cur;
    *p++ = arg2->x7;
    *p++ = arg3;
    if (arg2->x8 != 0 || arg2->x7 >= 0x2D) {
        *p++ = arg2->x8;
    }
    s = arg2->text;
    while (*s != 0) {
        if (IsSjisLead_803E90A8(*s)) {
            *p++ = *s++;
        } else {
            *p++ = 0xFF;
        }
        *p++ = *s++;
    }
}
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
void build_message_packet__22TQuestVmDownLoadServerFPviPvUc(u8 *arg0, s32 arg1, Msg_803E9190 *arg2, u8 arg3) {
    u8 unused[8];
    *arg0++ = arg1 % 256;
    *arg0++ = arg1 / 256;
    *arg0++ = arg2->len;
    strncpy((char *)arg0, arg2->name, arg2->len);
    arg0 += arg2->len;
    *arg0++ = arg2->x7;
    *arg0++ = arg3;
    if (arg2->x8 != 0 || arg2->x7 >= 0x2D) {
        *arg0++ = arg2->x8;
    }
    CopyText_803E9190(arg2->text, arg0);
}
#pragma pop

s32 TQuestVmDownLoadServer::calc_text_length() {
    Msg_803E92C0 *arg0 = (Msg_803E92C0 *)this;
    s32 n;
    u8 *p;
    s32 extra;
    if (arg0->x8 != 0 || arg0->x7 >= 0x2D) {
        extra = 3;
    } else {
        extra = 2;
    }
    p = arg0->text;
    n = 0;
    while (*p != 0) {
        if (IsSjisLead_803E92C0(*p)) {
            p += 2;
        } else {
            p += 1;
        }
        n += 2;
    }
    return extra + n;
}
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
s32 TQuestVmDownLoadServer::calc_message_length() {
    Msg_803E9348 *arg0 = (Msg_803E9348 *)this;
    s32 n;
    u8 *p;
    s32 extra;
    if (arg0->x8 != 0 || arg0->x7 >= 0x2D) {
        extra = 3;
    } else {
        extra = 2;
    }
    p = arg0->text;
    n = 0;
    while (*p != 0) {
        if (IsSjisLead_803E9348(*p)) {
            p += 2;
        } else {
            p += 1;
        }
        n += 2;
    }
    extra = arg0->len + extra;
    n = extra + n;
    return n + 3;
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
        char *name, size_t cacheAddress, u8 len, QuestDownloadCachedNameNode **&link) {
    s16 wanted;
    QuestDownloadCachedNameNode *node;
    QuestDownloadCachedNameNode *previous;
    s32 bucket;
    previous = NULL;
    u8 first = (u8)name[0];
    if (first >= 0xA0 && first < 0xF0) {
        bucket = first - 0xA0;
    } else {
        bucket = 0;
    }
    node = QUEST_DOWNLOAD_CACHE_INDEX(cacheAddress)->heads[bucket];
    wanted = (s16)len;
    for (; node != NULL; node = node->next) {
        u8 *indexed = node->encodedRecord;
        len = indexed[2];
        s32 comparison = strncmp((const char *)(indexed + 3), name, (s16)len);
        if (comparison == 0) {
            if (wanted == (s16)len) {
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
s32 TQuestVmDownLoadServer__sub_803E93DC(void) {
    char name[0x50];
    u8 *pageStart;
    u8 *record;
    s32 page;
    u8 len;
    QuestDownloadCachedNameNode *node;
    QuestDownloadCachedNameNode **link;

    size_t cacheAddress = (size_t)lbl_80591EC8;
    u8 *cacheBytes = reinterpret_cast<u8 *>(cacheAddress);
    if (TQuestVmDownLoadServer::seek_or_reopen(0x1400) == -1) {
        return -1;
    }
    s32 readCount = (s32)aram_read_thunk__22TQuestVmDownLoadServerFUli(
            (void *)lbl_805D7904, cacheBytes, 0x2000);
    if (readCount != 0x2000) {
        return -1;
    }
    pageStart = cacheBytes;
    for (page = 0; page < 8; page++, pageStart += 0x400) {
        for (record = pageStart;
             (u16)(record[0] + (record[1] << 8)) != 0;
             record += (u16)(record[0] + (record[1] << 8))) {
            len = record[2];
            if ((s16)len != 0) {
                strncpy(name, (const char *)(record + 3), (s16)len);
                name[(s16)len] = 0;
                node = find_cached_name_link(name, cacheAddress, len, link);
                if (lbl_805D7878 == NULL) {
                    TQuestVmDownLoadServer__sub_803E95BC();
                }
                QuestDownloadCachedNameNode *allocated = lbl_805D7878;
                lbl_805D7878 = allocated->next;
                allocated->encodedRecord = record;
                allocated->next = node;
                *link = allocated;
            }
        }
        if (lbl_805D7874 == page) {
            lbl_805D7870 = record;
            lbl_805D786C = pageStart + 0x400;
        }
    }
    return 0;
}
#pragma pop

#pragma pop



// Rotate the encoded-name cache page and return its indexed nodes to the
// existing free list. Requires valid bounded records and a consistent index.
#pragma push
#pragma opt_common_subs off
#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
void TQuestVmDownLoadServer__sub_803E95BC(void) {
    char name[0x50];

    size_t cacheAddress = (size_t)lbl_80591EC8;
    u8 *cacheBytes = reinterpret_cast<u8 *>(cacheAddress);
    u8 *record;
    u8 len;
    QuestDownloadCachedNameNode *node;
    QuestDownloadCachedNameNode **link;

    *lbl_805D7870++ = 0;
    *lbl_805D7870++ = 0;
    lbl_805D7874 = (lbl_805D7874 + 1) % 8;
    lbl_805D7870 = cacheBytes + lbl_805D7874 * 0x400;
    lbl_805D786C = lbl_805D7870 + 0x400;
    for (record = lbl_805D7870;
         (u16)(record[0] + (record[1] << 8)) != 0;
         record += (u16)(record[0] + (record[1] << 8))) {
        len = record[2];
        if ((s16)len != 0) {
            strncpy(name, (const char *)(record + 3), (s16)len);
            name[(s16)len] = 0;
            node = find_cached_name_link(name, cacheAddress, len, link);
            // The native code also requires a non-null stopping node here.
            if (node->encodedRecord == record) {
                *link = node->next;
                node->next = lbl_805D7878;
                lbl_805D7878 = node;
            }
        }
    }
    TQuestVmDownLoadServer::clear_entries_by_id(lbl_805D7874);
}
#pragma pop

#pragma pop



u8 *TQuestVmDownLoadServer::get_buffer_ptr(s32 arg0) {
    return lbl_80591EC8 + ((s16) (arg0 >> 0xC) << 0xA) + (s16) (arg0 & 0xFFF);
}

void TQuestVmDownLoadServer__sub_803E9764(void) {
    u8 *var_r4;
    s32 var_r3;
    s32 var_r5;
    if ((u8) (*(u8 *)&lbl_805D7868) != 0) {
        var_r3 = 0x1400;
        if (TQuestVmDownLoadServer::seek_or_reopen(0x1400) != -1) {
            var_r4 = lbl_80591EC8;
            var_r3 = lbl_805D7904;
            var_r4 = lbl_80591EC8;
            var_r5 = 0x2000;
            TQuestVmDownLoadServer__sub_803E8788(var_r3, lbl_80591EC8, 0x2000);
        }
    }
}

// This existing link name denotes the cache initializer here; no SDK owner
// or retrace-handler semantics are inferred from the placeholder symbol.
#pragma push
#pragma opt_common_subs off
void __VIRetraceHandler(void) {
    size_t cacheAddress = (size_t)lbl_80591EC8;
    QuestDownloadCachedNameNode *node = QUEST_DOWNLOAD_CACHE_INDEX(cacheAddress)->nodes;
    QuestDownloadCachedNameNode *end = node + 511;
    for (; node < end; node++) {
        node->next = node + 1;
    }
    node->next = NULL;
    lbl_805D7878 = QUEST_DOWNLOAD_CACHE_INDEX(cacheAddress)->nodes;
    for (u32 i = 0; i < 80; i++) {
        QUEST_DOWNLOAD_CACHE_INDEX(cacheAddress)->heads[i] = NULL;
    }
    if (TQuestVmDownLoadServer__sub_803E93DC() == -1) {
        u8 *bytes = reinterpret_cast<u8 *>(cacheAddress);
        u8 *page = bytes;
        for (s32 i = 0; i < 8; i++) {
            page[1] = 0;
            page[0] = 0;
            page += 0x400;
        }
        lbl_805D7874 = 0;
        lbl_805D7870 = bytes;
        // Rewind the completed page walk to the end of the first append page.
        lbl_805D786C = page -= sizeof(lbl_80591EC8) - 0x400;
    }
    lbl_805D7868 = 0;
}
#pragma pop
#undef QUEST_DOWNLOAD_CACHE_INDEX

typedef char RecoveredGlobal_803E9F20_lbl_80595998_size[sizeof(RecoveredGlobal_803E9F20_lbl_80595998) == 0x8C0 ? 1 : -1];

s32 TQuestVmDownLoadServer::is_download_cmd_allowed(u8 arg0) {
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

const QuestDownloadMatchToken *find_longest_match_entry__22TQuestVmDownLoadServerFPviPv(u8 *arg0, s32 arg1, s32 *arg2) {
    u8 *s;
    u8 *a;
    s32 k;
    s32 rem;
    const QuestDownloadMatchToken *p;
    s32 m;
    s32 best = 1;
    u8 c = arg0[0];
    if (c < 0xA0) {
        *arg2 = 1;
        return NULL;
    }
    c -= 0xA0;
    for (p = &quest_download_lz_match_entry_table[quest_download_lz_match_index_table[c + 1]] - 1; p >= &quest_download_lz_match_entry_table[quest_download_lz_match_index_table[c]]; p--) {
        a = arg0 + 1;
        rem = arg1 - 1;
        s = &lbl_8047F0F8[p->off];
        m = 1;
        k = *s++ - 1;
        while (1) {
            if (k == 0) {
                if (m > best) {
                    best = m;
                }
                *arg2 = best;
                return p;
            }
            if (rem == 0) {
                if (lbl_805D7888 >= 3) {
                    return QUEST_DOWNLOAD_MATCH_TOKENS_UNAVAILABLE;
                }
                break;
            }
            m++;
            if (*s != *a) {
                if (m > best) {
                    best = m;
                }
                break;
            }
            a++;
            s++;
            rem--;
            k--;
        }
    }
    *arg2 = best;
    return NULL;
}

void TQuestVmDownLoadServer::latch_slot_value(s32 arg0) {
    QuestDownloadSlot *slot = &quest_download_slot_chain_table[arg0];
    if (slot->x16 == 0 && slot->x14 != 0) {
        slot->x16 = slot->x15;
    }
}

s32 TQuestVmDownLoadServer__sub_803E9F54(s32 arg0) {
    QuestDownloadSlot *r;
    if (arg0 >= lbl_805D78C0) {
        return 0;
    }
    r = &quest_download_slot_chain_table[arg0];
    if (lbl_805D7848 == 2 && r->x14 == 0) {
        return 0;
    }
    return (s8)r->x15;
}

QuestDownloadEntryNode *insert_sorted_node__22TQuestVmDownLoadServerFPvPv(QuestDownloadEntryNode *arg0, QuestDownloadEntryNode *arg1) {
    QuestDownloadEntryNode *cur;
    QuestDownloadEntryNode *prev;
    s16 k = arg1->prefix.off;
    if (arg0 == NULL || arg0->prefix.off < k) {
        arg1->next = arg0;
        return arg1;
    }
    cur = arg0->next;
    prev = arg0;
    while (cur != NULL) {
        if (cur->prefix.off < k) {
            break;
        }
        prev = cur;
        cur = cur->next;
    }
    prev->next = arg1;
    arg1->next = cur;
    return arg0;
}

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
// List failure/unavailable input is all-ones in the native 32-bit result word.
// NULL remains an empty or allocation-exhausted list, not this failure. See
// docs/evidence/quest-download-search-evidence.md.
#define QUEST_DOWNLOAD_LIST_SENTINEL_WORD 0xFFFFFFFFU
#define QUEST_DOWNLOAD_SEGMENT_SCAN_FAILED ((QuestDownloadSegment *)QUEST_DOWNLOAD_LIST_SENTINEL_WORD)
#define QUEST_DOWNLOAD_ENTRY_LIST_FAILED ((QuestDownloadEntryNode *)QUEST_DOWNLOAD_LIST_SENTINEL_WORD)
#define QUEST_DOWNLOAD_ITEM_LIST_UNAVAILABLE ((QuestDownloadItemNode *)QUEST_DOWNLOAD_LIST_SENTINEL_WORD)
// The quest download name character class. The original lowers this sparse
// switch behind an explicit range guard at the head of the slot search.
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
// Scan one slot's match-token chain for segments covering [beg, end). A
// token names an item pair (a, b); lbl_8047F0F8 maps its displacement byte
// to an offset into the download buffer, and the first-fill path above
// covers the empty-slot single-byte case. The walk runs backwards by the
// token's signed link count.
QuestDownloadSegment *TQuestVmDownLoadServer__sub_803E9A74(s32 beg, s32 end, u8 a, u8 b) {
    const QuestDownloadMatchToken *t;
    QuestDownloadSegment *result;
    QuestDownloadSegment *seg;
    QuestDownloadSegment *sub;
    QuestDownloadSegment *walk;
    s32 off;

    result = NULL;
    if (beg >= end) {
        if (lbl_805D7888 < 3) {
            return NULL;
        }
        return QUEST_DOWNLOAD_SEGMENT_SCAN_FAILED;
    }
    if ((t = quest_download_slot_chain_table[beg].tokens) == QUEST_DOWNLOAD_MATCH_TOKENS_UNAVAILABLE) {
        return QUEST_DOWNLOAD_SEGMENT_SCAN_FAILED;
    }
    if (t == NULL) {
        if (IsNameChar_803E9A74(lbl_805A0470.bytes[beg]) != 0) {
            if (a == 0 || TQuestVmDownLoadServer::is_valid_item_for_slot(a, b) != 0) {
                seg = (QuestDownloadSegment *)TQuestVmDownLoadServer__sub_803ECF0C();
                if (seg != NULL) {
                    seg->off = 1;
                    seg->a = 0xFF;
                    seg->reserved_2[0] = 0xFF;
                    seg->b = 0;
                    seg->reserved_2[1] = 0;
                    seg->next = NULL;
                }
                return seg;
            }
        }
    }
    while (t != NULL) {
        if (TQuestVmDownLoadServer::is_valid_item_for_slot(t->a, t->b) == 0) {
            goto advance;
        }
        if (a != 0) {
            if (TQuestVmDownLoadServer__sub_803E7390(a, b, t->a) == 0) {
                goto advance;
            }
        }
        off = lbl_8047F0F8[t->off];
        if (beg + off >= end || IsX_803E9FFC(lbl_805A0470.bytes[beg + off]) == 0) {
            seg = (QuestDownloadSegment *)TQuestVmDownLoadServer__sub_803ECF0C();
            if (seg != NULL) {
                seg->off = (s16)off;
                seg->reserved_2[0] = (seg->a = t->a);
                seg->reserved_2[1] = (seg->b = t->b);
                seg->next = result;
                result = seg;
            }
        }
advance:
        if ((s8)t->d == 0) {
            break;
        }
        t -= (s8)t->d;
    }
    t = quest_download_slot_chain_table[beg].tokens;
    while (t != NULL) {
        if (a != 0) {
            if (TQuestVmDownLoadServer__sub_803E7390(a, b, t->a) == 0) {
                goto advance2;
            }
        }
        off = lbl_8047F0F8[t->off];
        sub = TQuestVmDownLoadServer__sub_803E9A74(beg + off, end, t->a, t->b);
        if (sub == QUEST_DOWNLOAD_SEGMENT_SCAN_FAILED) {
            TQuestVmDownLoadServer__sub_803ECE5C(result);
            return QUEST_DOWNLOAD_SEGMENT_SCAN_FAILED;
        }
        if (sub != NULL) {
            for (walk = sub; ; walk = walk->next) {
                walk->off = walk->off + off;
                walk->reserved_2[0] = t->a;
                walk->reserved_2[1] = t->b;
                if (walk->next == NULL) {
                    break;
                }
            }
            walk->next = result;
            result = sub;
        }
advance2:
        if ((s8)t->d == 0) {
            break;
        }
        t -= (s8)t->d;
    }
    return result;
}
void *TQuestVmDownLoadServer__sub_803E9FFC(s32 arg0, s32 arg1, QuestDownloadItemNode *t) {
    s32 off;
    QuestDownloadEntryNode *head;
    QuestDownloadEntryNode *tail;
    s32 pos;
    QuestDownloadSegment *s;
    QuestDownloadSegment *first;
    QuestDownloadEntryNode *o;
    off = t->off;
    head = NULL;
    tail = NULL;
    pos = arg0 + off;
    s = TQuestVmDownLoadServer__sub_803E9A74(pos, arg1, t->a, t->b);
    if (s == QUEST_DOWNLOAD_SEGMENT_SCAN_FAILED) {
        return QUEST_DOWNLOAD_ENTRY_LIST_FAILED;
    }
    for (first = s; s != NULL; s = s->next) {
        o = (QuestDownloadEntryNode *)TQuestVmDownLoadServer__sub_803ECF48();
        if (o == NULL) {
            break;
        }
        if (head == NULL) {
            head = o;
        }
        o->prefix.off = off + s->off;
        o->prefix.a = s->a;
        o->prefix.b = s->b;
        o->prefix.src = t;
        o->x8 = 0;
        o->xa = 0;
        o->next = NULL;
        if (tail != NULL) {
            tail->next = o;
        }
        tail = o;
    }
    TQuestVmDownLoadServer__sub_803ECE5C((QuestDownloadSegment *)first);
    if (off > 0 && TQuestVmDownLoadServer::is_valid_item_for_slot(t->a, t->b) != 0) {
        if (pos >= arg1 || IsX_803E9FFC(lbl_805A0470.bytes[pos]) == 0) {
            o = (QuestDownloadEntryNode *)TQuestVmDownLoadServer__sub_803ECF48();
            if (o != NULL) {
                if (head == NULL) {
                    head = o;
                }
                o->prefix.off = off;
                o->prefix.a = t->a;
                o->prefix.b = t->b;
                o->prefix.src = t;
                o->x8 = 0;
                o->xa = 0;
                o->next = NULL;
                if (tail != NULL) {
                    tail->next = o;
                }
            }
        }
    }
    return head;
}
#pragma pop


extern "C" QuestDownloadItemNode lbl_8047F8A8;
// Local pass settings preserve the separate generator result and traversal
// cursor, the cached position and the original write boundary. pragma pop
// restores the surrounding profile; option recognition is tested separately.
#pragma push
#pragma opt_propagation off
#pragma opt_common_subs off
#pragma opt_lifetimes off
s32 TQuestVmDownLoadServer__sub_803EA1A8(s32 index, s32 limit) {
    QuestDownloadSlot *slot;
    // A shared byte position keeps both borrows in the complete eighty-slot
    // representation. Valid caller indices select actual aligned Slot objects.
    s32 offset = index * sizeof(QuestDownloadSlot);
    slot = reinterpret_cast<QuestDownloadSlot *>(reinterpret_cast<u8 *>(&quest_download_slot_chain_table) + offset);
    QuestDownloadEntryNode *next;
    QuestDownloadItemNode *item;
    QuestDownloadEntryNode *entry;
    QuestDownloadEntryNode *result;
    QuestDownloadEntryNode *head;
    u8 *text;
    s32 pos;
    if (slot->items != QUEST_DOWNLOAD_ITEM_LIST_UNAVAILABLE) {
        for (item = slot->items; item != NULL; item = item->next) {
            result = static_cast<QuestDownloadEntryNode *>(TQuestVmDownLoadServer__sub_803E9FFC(index, limit, item));
            if (result == QUEST_DOWNLOAD_ENTRY_LIST_FAILED) {
                if (slot->entryHead != NULL) {
                    TQuestVmDownLoadServer__sub_803ECD8C(slot->entryHead);
                    slot->entryHead = NULL;
                }
                return 0;
            }
            if (result != NULL) {
                head = slot->entryHead;
                for (entry = result; entry != NULL; entry = next) {
                    next = entry->next;
                    head = insert_sorted_node__22TQuestVmDownLoadServerFPvPv(head, entry);
                }
                slot->entryHead = head;
            }
        }
    }
    result = static_cast<QuestDownloadEntryNode *>(TQuestVmDownLoadServer__sub_803E9FFC(index, limit, &lbl_8047F8A8));
    if (result == QUEST_DOWNLOAD_ENTRY_LIST_FAILED) {
        if (slot->entryHead != NULL) {
            TQuestVmDownLoadServer__sub_803ECD8C(slot->entryHead);
            slot->entryHead = NULL;
        }
        return 0;
    }
    if (result != NULL) {
        // Borrow the real head lvalue after the generator has returned.
        // This fixed offset names the real pointer member; no node is retyped.
        u8 *member = reinterpret_cast<u8 *>(&quest_download_slot_chain_table) + offset;
        member += offsetof(QuestDownloadSlot, entryHead);
        QuestDownloadEntryNode **headp = reinterpret_cast<QuestDownloadEntryNode **>(member);
        head = *headp;
        for (entry = result; entry != NULL; entry = next) {
            next = entry->next;
            head = insert_sorted_node__22TQuestVmDownLoadServerFPvPv(head, entry);
        }
        *headp = head;
    }
    if (slot->entryHead == NULL) {
        entry = static_cast<QuestDownloadEntryNode *>(TQuestVmDownLoadServer__sub_803ECF48());
        if (entry == NULL) return -1;
        pos = index + 1;
        text = reinterpret_cast<u8 *>(&lbl_805A0470) + pos;
        for (; pos < limit; text++, pos++) {
            if (!TQuestVmDownLoadServer::is_download_cmd_allowed(*text)) break;
        }
        entry->prefix.off = pos - index;
        entry->prefix.a = 0x28;
        entry->prefix.b = 0;
        entry->prefix.src = NULL;
        entry->x8 = 0;
        entry->xa = 0;
        entry->next = NULL;
        slot->entryHead = entry;
        return 1;
    }
    return 1;
}

#pragma pop

#undef QUEST_DOWNLOAD_SEGMENT_SCAN_FAILED

QuestDownloadItemNode *build_item_list__22TQuestVmDownLoadServerFiPv(s32 arg0, Hdr_803EA384 *arg1) {
    s16 id;
    s32 x4;
    s32 n;
    Item_803EA384 *it;
    QuestDownloadItemNode *head;
    QuestDownloadItemNode *prev;
    QuestDownloadItemNode *node;
    u8 unused[8];
    it = arg1->entries;
    head = NULL;
    prev = NULL;
    id = arg1->len;
    x4 = arg1->x4;
    n = arg1->count;
    while (n-- != 0) {
        node = TQuestVmDownLoadServer__sub_803ECF84();
        if (node == NULL) {
            break;
        }
        if (head == NULL) {
            head = node;
        }
        node->off = id;
        node->a = it->a;
        node->b = it->b;
        node->x4 = x4;
        node->c = it->key;
        node->next = NULL;
        if (prev != NULL) {
            prev->next = node;
        }
        prev = node;
        it++;
    }
    return head;
}

s32 TQuestVmDownLoadServer::count_leading_entries(s32 i, s32 end) {
    QuestDownloadSlot *e = &quest_download_slot_chain_table[i];
    s32 n;
    s32 total = 0;
    while (i < end) {
        n = e->x15;
        if (n == 0) {
            return -1;
        }
        if (e->entryHead != NULL && (u32)e->entryHead != 0xFFFFFFFF && e->entryHead->prefix.a != 0x28) {
            break;
        }
        total += n;
        i += n;
        e += n;
    }
    if (total == 0 || i >= end) {
        return total;
    }
    return total + n;
}

extern s32 lbl_805D7880;
s32 TQuestVmDownLoadServer__sub_803EA1A8(s32, s32);
s32 TQuestVmDownLoadServer__sub_803F06B8(const char *, s16, Out_803F0268 *);

// These two native routines retain the workspace allocation address while
// accessing the separately allocated following slots. Ports use their real
// objects directly; no larger C++ owner is asserted for the native address map.
#ifdef __MWERKS__
#define QUEST_WORKSPACE_SLOT(address, index) reinterpret_cast<QuestDownloadSlot *>((address) + sizeof(QuestDownloadWorkspace) + (index) * sizeof(QuestDownloadSlot))
#define QUEST_WORKSPACE_RESULT(address) (&reinterpret_cast<QuestDownloadWorkspace *>(address)->result)
#else
#define QUEST_WORKSPACE_SLOT(address, index) (&quest_download_slot_chain_table[index])
#define QUEST_WORKSPACE_RESULT(address) (&lbl_80595008.result)
#endif

s32 TQuestVmDownLoadServer__sub_803EA428(s32 start, s32 end) {
    u8 kind;
    u32 length;
    u8 *text;
    QuestDownloadSlot *slot;
    size_t workspaceAddress;
    u8 runKind;
    s32 stop;
    u8 *p;
    QuestDownloadInputEntry *last;

    workspaceAddress = reinterpret_cast<size_t>(&lbl_80595008);
    length = end - start;
    if (length == 0) return 0;
    text = lbl_805A0470.bytes + start;
    slot = QUEST_WORKSPACE_SLOT(workspaceAddress, start);
    kind = 0;
    if (TQuestVmDownLoadServer__sub_803EDB58(*text)) {
        p = text + 1;
        kind = 0x1F;
        for (end = 1; end < length; end++, p++) {
            if (!TQuestVmDownLoadServer__sub_803EDB58(*p)) break;
        }
        if (lbl_805D7888 >= 3 && end >= length) return 0;
    } else if (TQuestVmDownLoadServer__sub_803EDB3C(*text)) {
        p = text + 1;
        kind = 0x19;
        for (end = 1; end < length; end++, p++) {
            if (!TQuestVmDownLoadServer__sub_803EDB74(*p)) break;
        }
        if (lbl_805D7888 >= 3 && end >= length) return 0;
    } else if (TQuestVmDownLoadServer__sub_803EDB20(*text)) {
        if (lbl_805D7888 >= 3 && length <= 1) return 0;
        length = 1; end = 1; kind = 0x19;
        goto candidates;
    } else if ((s8)*text != 0 && *text < 0xA0) {
        if (lbl_805D7888 >= 3 && length <= 1) return 0;
        length = 1; end = 1; kind = 0x29;
        goto candidates;
    } else if ((s8)*text == 0 && (quest_download_entry_table[start].ch & 0xFF00) == 0) {
        for (stop = start + 1; stop < end; stop++) {
            if ((quest_download_entry_table[stop].ch & 0xFF00) != 0) break;
        }
        runKind = 0x19;
        goto emit_run;
    } else if ((s8)*text == 0 && TQuestVmDownLoadServer::is_download_command(quest_download_entry_table[start].ch, 0)) {
        for (stop = start + 1; stop < end; stop++) {
            if (!TQuestVmDownLoadServer::is_download_command(quest_download_entry_table[stop].ch, 1)) break;
        }
        runKind = 0x19;
emit_run:
        if (lbl_805D7888 >= 3 && stop == end) return 0;
        QuestDownloadItemNode *item = TQuestVmDownLoadServer__sub_803ECF84();
        if (item != NULL) {
            item->off = stop - start;
            item->a = runKind;
            item->b = 0;
            item->x4 = -1;
            item->c = 0;
            item->next = NULL;
            #ifdef __MWERKS__
            reinterpret_cast<QuestDownloadSlot *>(workspaceAddress + start * sizeof(QuestDownloadSlot) + sizeof(QuestDownloadWorkspace))->x17 = stop - start + 1;
#else
            slot->x17 = stop - start + 1;
#endif
            QuestDownloadItemNode **tail = &slot->items;
            while (*tail != NULL) tail = &(*tail)->next;
            *tail = item;
        }
        return 1;
    } else if ((s8)*text == 0) {
        for (stop = start + 1, text++; stop < end; stop++, text++) {
            if ((s8)*text != 0) break;
        }
        last = &quest_download_entry_table[stop];
        if (TQuestVmDownLoadServer__sub_803EC884((--last)->ch)) runKind = 0x28;
        else if (TQuestVmDownLoadServer::is_valid_sjis_code(last->ch)) runKind = 0x29;
        else runKind = 0x19;
        goto emit_run;
    } else {
        end = 1;
    }

lookup:
    {
        p = text;
        u32 remaining = length;
        length = 0;
        for (; remaining > 0; remaining--) {
            if ((s8)*p++ == 0) break;
            length++;
        }
        Out_803F0268 *result = QUEST_WORKSPACE_RESULT(workspaceAddress);
        switch (TQuestVmDownLoadServer__sub_803F06B8((char *)text, length, result)) {
        case 2:
            if (lbl_805D7888 >= 3) return 0;
            break;
        case 1:
            if (kind != 0 && result->len <= end) {
                TQuestVmDownLoadServer__sub_803EED9C(result->x4);
                length = end;
                slot->x17 = result->len2;
            } else {
                QuestDownloadItemNode *item = build_item_list__22TQuestVmDownLoadServerFiPv(start, (Hdr_803EA384 *)result);
                QuestDownloadItemNode **tail = &slot->items;
                while (*tail != NULL) tail = &(*tail)->next;
                *tail = item;
                slot->x17 = result->len2;
                length = result->len - 1;
            }
            break;
        default:
            if (kind != 0) length = end;
            else { slot->items = QUEST_DOWNLOAD_ITEM_LIST_UNAVAILABLE; return -1; }
        }
    }
candidates:
    for (; length >= end; length--) {
        if (kind != 0 && length == end) {
            QuestDownloadItemNode *item = TQuestVmDownLoadServer__sub_803ECF84();
            if (item != NULL) {
                item->off = end;
                item->a = kind;
                item->b = 0;
                item->x4 = -1;
                item->c = 0;
                item->next = NULL;
                slot->x17 = end + 1;
                QuestDownloadItemNode **tail = &slot->items;
                while (*tail != NULL) tail = &(*tail)->next;
                *tail = item;
            }
        }
        Out_803F0268 *result = QUEST_WORKSPACE_RESULT(workspaceAddress);
        if (TQuestVmDownLoadServer__sub_803F0268((char *)text, length, result) == 1) {
            if (slot->x17 == -1) slot->x17 = result->len2;
            QuestDownloadItemNode *item = build_item_list__22TQuestVmDownLoadServerFiPv(start, (Hdr_803EA384 *)result);
            QuestDownloadItemNode **tail = &slot->items;
            while (*tail != NULL) tail = &(*tail)->next;
            *tail = item;
        }
    }
    return 1;
}

void TQuestVmDownLoadServer__sub_803EA9E8(s32 start, s32 inputEnd, s32 mode, s32 selectedLength) {
    QuestDownloadSlot *slot;
    u8 *text;
    s32 selectedEnd;
    QuestDownloadSlot *first;
    s32 end;
    s32 remaining;
    s32 pos;
    size_t workspaceAddress;
    QuestDownloadEntryNode *allocated;
    s32 next;
    QuestDownloadSlot *following;
    s32 length;
    s32 tokenLength;
    s32 groupLength;
    QuestDownloadEntryNode **link;
    QuestDownloadSlot *walk;
    s32 covered;
    QuestDownloadEntryNode *entry;
    const QuestDownloadMatchToken *tokens;

    workspaceAddress = reinterpret_cast<size_t>(&lbl_80595008);
    first = QUEST_WORKSPACE_SLOT(workspaceAddress, start);
    text = lbl_805A0470.bytes + start;
    end = inputEnd;
    lbl_805D7888 = mode;
    slot = first;
    remaining = end - start;
    while (remaining > 0) {
        if (slot->tokens == QUEST_DOWNLOAD_MATCH_TOKENS_UNAVAILABLE) {

            tokens = find_longest_match_entry__22TQuestVmDownLoadServerFPviPv(text, remaining, &tokenLength);
            if (tokens == QUEST_DOWNLOAD_MATCH_TOKENS_UNAVAILABLE) break;
            slot->x18 = tokenLength;
            slot->tokens = tokens;
        }
        text++; remaining--; slot++;
    }
    if (lbl_805D7888 == 3 && lbl_805D7880 != 0) return;
    pos = start;
    selectedEnd = start + selectedLength;
    while (pos < end) {
        slot = QUEST_WORKSPACE_SLOT(workspaceAddress, pos);
        if (slot->x15 > 0) { pos += slot->x15; continue; }
        if (slot->items == NULL && TQuestVmDownLoadServer__sub_803EA428(pos, end) == 0) break;
        if (slot->entryHead == NULL && TQuestVmDownLoadServer__sub_803EA1A8(pos, end) == 0) break;
        entry = slot->entryHead;
        while (entry != NULL) {
            next = pos + entry->prefix.off;
            if (next >= end) {
                if (lbl_805D7888 >= 3) {
                    if (entry->prefix.a != 0xFF) break;
                    lbl_805D7888 = 0;
                }
            } else {
                following = QUEST_WORKSPACE_SLOT(workspaceAddress, next);
                if (following->items == NULL && TQuestVmDownLoadServer__sub_803EA428(next, end) == 0) break;
                if (following->entryHead == NULL && TQuestVmDownLoadServer__sub_803EA1A8(next, end) == 0) break;
            }
            entry = entry->next;
        }

        if (pos == start) {
            if (lbl_805D7888 == 1) {
                TQuestVmDownLoadServer::select_best_slot_entry(pos, end, selectedLength);
                first->x14 = 1;
                length = selectedLength;
                goto chosen_length;
            } else if (lbl_805D7888 == 2) {
                first->x14 = 1;
                length = selectedLength;
                goto chosen_length;
            }
        } else if (pos == selectedEnd && lbl_805D7888 == 2) {
            TQuestVmDownLoadServer::reset_slot_chain_timers(pos);
        }
        length = TQuestVmDownLoadServer::select_best_slot_entry(pos, end, -1);
        if (length == -1) break;
chosen_length:
        link = &slot->entryHead;
        entry = *link;
        while (entry != NULL) {
            if (entry->prefix.off == length) link = &entry->next;
            else { *link = entry->next; push_download_entry__22TQuestVmDownLoadServerFPl(entry); }
            entry = *link;
        }
        TQuestVmDownLoadServer__sub_803EC460(pos, length);
        slot->x15 = length;
        pos += length;
    }
    for (pos = start; pos < end; ) {
        slot = QUEST_WORKSPACE_SLOT(workspaceAddress, pos);
        walk = slot;
        covered = slot->x15;

        if (slot->x14 != 0) groupLength = covered;
        else {
            groupLength = TQuestVmDownLoadServer::count_leading_entries(pos, end);
            if (groupLength < 0) return;
            if (groupLength == 0) groupLength = covered;
            if (groupLength == covered) walk->x14 = 1;
            else {
                while (covered < groupLength) {
                    if (walk->entryHead != QUEST_DOWNLOAD_ENTRY_LIST_FAILED) TQuestVmDownLoadServer__sub_803ECD8C(walk->entryHead);
                    walk->entryHead = NULL; walk->x15 = 0;
                    free_node_list__22TQuestVmDownLoadServerFv(walk->textHead); walk->textHead = NULL;
                    covered += (walk = QUEST_WORKSPACE_SLOT(workspaceAddress, pos + covered))->x15;
                }
                if (walk->entryHead != QUEST_DOWNLOAD_ENTRY_LIST_FAILED) TQuestVmDownLoadServer__sub_803ECD8C(walk->entryHead);
                walk->entryHead = NULL; walk->x15 = 0;
                free_node_list__22TQuestVmDownLoadServerFv(walk->textHead); walk->textHead = NULL;
                slot->x15 = groupLength;
                allocated = (QuestDownloadEntryNode *)TQuestVmDownLoadServer__sub_803ECF48();
                if (allocated != NULL) {
                    allocated->prefix.off = groupLength; allocated->prefix.a = 0x28; allocated->prefix.b = 0;
                    allocated->prefix.src = NULL; allocated->x8 = 0; allocated->xa = 0; allocated->next = NULL;
                    slot->entryHead = allocated; slot->x14 = 1;
                    TQuestVmDownLoadServer__sub_803EC460(pos, groupLength);
                }
            }
        }
        pos += groupLength;
    }
}

#undef QUEST_WORKSPACE_SLOT
#undef QUEST_WORKSPACE_RESULT

void TQuestVmDownLoadServer__sub_803EADD4(QuestDownloadSlot *arg0, s32 arg1) {
    if (arg1 == 0) {
        arg0->tokens = QUEST_DOWNLOAD_MATCH_TOKENS_UNAVAILABLE;
        arg0->x18 = -1;
        if ((u32)arg0->items != 0xFFFFFFFF) {
            release_node_chain__22TQuestVmDownLoadServerFPv((QuestDownloadItemNode *)(arg0->items));
        }
        arg0->items = NULL;
        arg0->x17 = -1;
        arg0->x19 = -1;
        arg0->x16 = 0;
    }
    if (arg0->entryHead != NULL && (u32)arg0->entryHead != 0xFFFFFFFF) {
        TQuestVmDownLoadServer__sub_803ECD8C(arg0->entryHead);
    }
    arg0->entryHead = NULL;
    if (arg0->textHead != NULL) {
        free_node_list__22TQuestVmDownLoadServerFv(arg0->textHead);
    }
    arg0->textHead = NULL;
    arg0->timer = 0;
    arg0->x14 = 0;
    arg0->x15 = 0;
}

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

void TQuestVmDownLoadServer__sub_803EAE84(s32 arg0, s32 arg1, void *arg2) {
    QuestDownloadSlot *p;
    QuestDownloadSlot *end;
    end = &((QuestDownloadSlot *)quest_download_slot_chain_table)[arg1];
    p = &((QuestDownloadSlot *)quest_download_slot_chain_table)[arg0];
    for (; p < end; p++) {
        TQuestVmDownLoadServer__sub_803EADD4((QuestDownloadSlot *)(p), (s32)arg2);
    }
}


void TQuestVmDownLoadServer::init_entries() {
    QuestDownloadSlot *p;

    for (p = (QuestDownloadSlot *)quest_download_slot_chain_table; p < (QuestDownloadSlot *)quest_download_slot_chain_table + 80; p++) {
        p->tokens = QUEST_DOWNLOAD_MATCH_TOKENS_UNAVAILABLE;
        p->items = 0;
        p->entryHead = 0;
        p->textHead = 0;
        p->timer = 0;
        p->x14 = 0;
        p->x15 = 0;
        p->x16 = 0;
        p->x17 = -1;
        p->x18 = -1;
        p->x19 = -1;
    }
}

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
s32 TQuestVmDownLoadServer__sub_803EB0D8(s32 arg0, s32 arg1) {
    QuestDownloadTextNode *save = (*(QuestDownloadTextNode * *)&lbl_805D78A0);
    s32 cnt = lbl_805D789C;
    u8 unused[8];
    TQuestVmDownLoadServer__sub_803EC284(0, 0);
    if (save == (*(QuestDownloadTextNode * *)&lbl_805D78A0)) {
        if (arg1 == 0) {
            (*(QuestDownloadTextNode * *)&lbl_805D78A0) = save;
            lbl_805D789C = cnt;
            lbl_805D7898 = 0;
            return 0;
        }
        save = NULL;
    }
    for (;;) {
        if (Advance_803EB0D8((*(QuestDownloadTextNode * *)&lbl_805D78A0), lbl_805D789C) == save) {
            break;
        }
        (*(QuestDownloadTextNode * *)&lbl_805D78A0) = Advance_803EB0D8((*(QuestDownloadTextNode * *)&lbl_805D78A0), lbl_805D789C);
        Reload_803EB0D8();
    }
    if (arg0 == 1) {
        TQuestVmDownLoadServer__sub_803EB4D4();
    }
    return 1;
}
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
s32 TQuestVmDownLoadServer__sub_803EB208(s32 mode, s32 force) {
    QuestDownloadTextNode *save = lbl_805D78A0;
    s32 count;
    lbl_805D78A0 = advance_entry_groups(save, lbl_805D789C);
    count = count_fitting_groups(lbl_805D78A0);
    if (count == 0) {
        if (force == 0) {
            lbl_805D78A0 = save;
            return 0;
        }
        TQuestVmDownLoadServer__sub_803EC284(0, 0);
    } else {
        lbl_805D789C = count;
    }
    lbl_805D7898 = 0;
    if (mode == 1) {
        TQuestVmDownLoadServer__sub_803EB4D4();
    }
    return 1;
}
#pragma pop

s32 count_fitting_entries__22TQuestVmDownLoadServerFPv(QuestDownloadTextNode *arg0) {
    s32 n;
    s32 total;
    s32 lim;
    QuestDownloadTextNode *p;
    if (arg0 == NULL) {
        return 0;
    }
    p = arg0;
    total = 0;
    lim = lbl_805D78A4 - 9;
    n = 0;
    while (n < 9 && p != NULL) {
        total += Len_803EB328(p) + 3;
        if (total > lim) {
            break;
        }
        n++;
        p = Next_803EB328(p);
    }
    if (n == 0) {
        return 1;
    }
    return n;
}
#pragma pop

s32 TQuestVmDownLoadServer__sub_803EB420(s32 start, s32 count, QuestDownloadTextNode *arg2, u16 *buf) {
    s32 n;
    QuestDownloadTextNode *p;
    u8 unused[8];
    if (arg2 == NULL || (arg2->flags & 0x80)) {
        return TQuestVmDownLoadServer__sub_803E6970(start, count, buf, 0);
    }
    p = arg2;
    n = 0;
    for (;;) {
        n += TQuestVmDownLoadServer__sub_803EC95C(buf + n, reinterpret_cast<u8 *>(p) + 1, 6);
        if (!(p->flags & 1)) {
            break;
        }
        p = p->next;
    }
    buf += n;
    return n + TQuestVmDownLoadServer__sub_803E6970((s32)(start + arg2->payload.head.length), (s32)(count - arg2->payload.head.length), buf, 0);
}

QuestDownloadTextNode *advance_nodes__22TQuestVmDownLoadServerFPvi(QuestDownloadTextNode *p, s32 n) {
    s32 i;
    for (i = 0; i != n; i++) {
        while (p->flags & 1) {
            p = p->next;
        }
        p = p->next;
    }
    return p;
}



s32 TQuestVmDownLoadServer__sub_803EB7C0(QuestDownloadTextNode *arg0) {
    s32 n;
    if (arg0->flags == 0x80) {
        return lbl_805D78EC * 2;
    }
    n = (lbl_805D78EC - arg0->payload.head.length) * 2;
    while (arg0->flags & 1) {
        n += strlen(reinterpret_cast<char *>(&arg0->payload));
        arg0 = arg0->next;
    }
    return n + strlen(reinterpret_cast<char *>(&arg0->payload));
}

s32 count_chain_nodes__22TQuestVmDownLoadServerFv(QuestDownloadTextNode *p) {
    s32 n = 0;
    while (p != NULL) {
        while (p->flags & 1) {
            p = p->next;
        }
        p = p->next;
        n++;
    }
    return n;
}

QuestDownloadTextNode *TQuestVmDownLoadServer__sub_803EB878(QuestDownloadTextNode *p) {
    while (p->flags & 1) {
        p = p->next;
    }
    return p->next;
}

QuestDownloadTextNode *detach_node_chain__22TQuestVmDownLoadServerFPv(QuestDownloadTextNode *p) {
    QuestDownloadTextNode *next;
    while (p->flags & 1) {
        p = p->next;
    }
    next = p->next;
    p->next = NULL;
    return next;
}


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

void append_unique_node__22TQuestVmDownLoadServerFiPvPvPv(s32 start, QuestDownloadTextNode **headp, QuestDownloadTextNode **tailp, QuestDownloadTextNode *n) {
    s32 len;

    len = Conv_803EB8BC(start, lbl_805D78EC, n, lbl_805A0340);
    len = TQuestVmDownLoadServer__sub_803EC71C(lbl_805A0340, (u8 *)lbl_805A02A8, len);
    if (Find_803EB8BC((u8 *)lbl_805A02A8, len)) {
        free_node_list__22TQuestVmDownLoadServerFv(n);
        return;
    }
    Add_803EB8BC((u8 *)lbl_805A02A8, len);
    if (*headp == NULL) {
        *tailp = n;
        *headp = n;
    } else {
        (*tailp)->next = n;
    }
    *tailp = Last_803EB8BC(n);
}
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
extern u8 lbl_805D7894[4];
extern u8 lbl_805E10D0[4];
inline s32 display_group_count(QuestDownloadTextNode *p) {
    s32 n = 0;
    while (p != NULL) {
        while (p->flags & 1) p = p->next;
        p = p->next;
        n++;
    }
    return n;
}
inline QuestDownloadTextNode *display_next_group(QuestDownloadTextNode *p) {
    while (p->flags & 1) p = p->next;
    return p->next;
}
void TQuestVmDownLoadServer__sub_803EB4D4(void) {
    u8 *digit;
    s32 index;
    QuestDownloadTextNode *node;
    s32 written;
    s32 count;
    s32 value;
    u16 *line;
    s32 n;
    u16 *pad;
    digit = reinterpret_cast<u8 *>(lbl_80596258.text) + 5;
    count = display_group_count(lbl_805D78A0);
    count -= lbl_805D7898;
    count -= 1;
    if (count < 0) count = 0;
    if ((value = count / 100) != 0) *digit++ = value + '0';
    else *digit++ = ' ';
    count %= 100;
    if ((value = count / 10) != 0 || (u32)digit[-1] != ' ') *digit++ = value + '0';
    else *digit++ = ' ';
    count %= 10;
    *digit = count + '0';
    TQuestVmDownLoadServer__sub_803EC95C(lbl_805A0340, reinterpret_cast<u8 *>(lbl_80596258.text), 0);
    node = lbl_805D78A0;
    written = 9;
    index = 0;
    while (index < lbl_805D789C) {
        line = lbl_805A0340 + written;
        lbl_805D7894[2] = index + '1';
        written += TQuestVmDownLoadServer__sub_803EC95C(line, lbl_805D7894, 0);
        line = lbl_805A0340 + written;
        n = display_convert_text(lbl_805D78F0, lbl_805D78EC, node, line);
        if (index == lbl_805D7898) TQuestVmDownLoadServer__sub_803ECA1C(line, n, 7);
        else TQuestVmDownLoadServer__sub_803ECA1C(line, n, 0);
        written += n;
        if ((node = display_next_group(node)) == NULL) break;
        index++;
    }
    pad = lbl_805A0340 + written;
    while (written < lbl_805D78A4) {
        TQuestVmDownLoadServer__sub_803EC95C(pad, lbl_805E10D0, 0);
        pad++;
        written++;
    }
}

inline QuestDownloadTextNode *Next_803EBA98(QuestDownloadTextNode *p) {
    while (p->flags & 1) {
        p = p->next;
    }
    return p->next;
}
void TQuestVmDownLoadServer__sub_803EBA98(s32 start, QuestDownloadTextNode *arg1) {
    s32 n;
    s32 len;
    quest_download_text_write_ptr = quest_download_text_buffer;
    while (arg1 != NULL) {
        n = Conv_803EBA98(start, lbl_805D78EC, arg1, lbl_805A0340);
        len = TQuestVmDownLoadServer__sub_803EC71C(lbl_805A0340, quest_download_text_write_ptr + 1, n);
        *quest_download_text_write_ptr++ = len;
        quest_download_text_write_ptr += len;
        arg1 = Next_803EBA98(arg1);
    }
}
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

void TQuestVmDownLoadServer__sub_803EBC88(s32 mode) {
    QuestDownloadSlot *e = &quest_download_slot_chain_table[lbl_805D78F0];
    free_node_list__22TQuestVmDownLoadServerFv(e->textHead);
    e->textHead = build_entry_text(lbl_805D78F0, lbl_805D78EC, mode);
}
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
#define s ((Src_803EBD38 *)sp)
#define headp ((QuestDownloadTextNode **)hp)
#define tailp ((QuestDownloadTextNode **)tp)
void *TQuestVmDownLoadServer::build_text_node_chain(void *sp, void *a1, s32 a2, void *hp, void *tp) {
    u8 *text;
    s32 rem;
    QuestDownloadTextNode *n;
    QuestDownloadTextNode *m;
    s32 c;
    text = s->text;
    rem = strlen((const char *)text);
    n = (QuestDownloadTextNode *)TQuestVmDownLoadServer__sub_803ECED0();
    if (n == NULL) {
        return NULL;
    }
    n->flags = 0;
    c = Copy_803EBD38(reinterpret_cast<u8 *>(n->payload.head.text), text, 4);
    rem -= c;
    n->payload.head.length = a2;
    text += c;
    n->payload.head.kind = s->x4;
    n->payload.head.source = (s32)a1;
    n->payload.head.id = s->x0;
    n->payload.head.attribute = s->x2;
    n->next = NULL;
    *headp = n;
    while (rem > 0) {
        m = (QuestDownloadTextNode *)TQuestVmDownLoadServer__sub_803ECED0();
        if (m == NULL) {
            free_node_list__22TQuestVmDownLoadServerFv(*headp);
            return NULL;
        }
        n->flags |= 1;
        // Retain the two bytes that can later become a default head's
        // attribute when this cell is recycled; do not create an uninitialized
        // character tail at those positions when changing the payload member.
        u8 *bytes = reinterpret_cast<u8 *>(m);
        const u8 attribute_high = bytes[offsetof(QuestDownloadTextNode, payload.head.attribute)];
        const u8 attribute_low = bytes[offsetof(QuestDownloadTextNode, payload.head.attribute) + 1];
        new (&m->payload.continuation, quest_download_pool_storage) QuestDownloadTextContinuation;
        bytes[offsetof(QuestDownloadTextNode, payload.head.attribute)] = attribute_high;
        bytes[offsetof(QuestDownloadTextNode, payload.head.attribute) + 1] = attribute_low;
        m->flags = 2;
        c = Copy_803EBD38(reinterpret_cast<u8 *>(m->payload.continuation.text), text, 14);
        rem -= c;
        text += c;
        m->next = NULL;
        n->next = m;
        n = m;
    }
    *tailp = n;
    return *headp;
}
#undef s
#undef headp
#undef tailp
#pragma pop

// Native code keeps the display-prefix address when addressing the following
// scratch allocation. Ports use that separate byte-array object directly.
#ifdef __MWERKS__
#define QUEST_TEXT_SCRATCH(prefix) reinterpret_cast<u8 *>((size_t)(prefix) + sizeof(QuestDownloadDisplayPrefix))
#else
#define QUEST_TEXT_SCRATCH(prefix) quest_download_text_buffer
#endif
QuestDownloadTextNode *TQuestVmDownLoadServer__sub_803EBEFC(QuestDownloadEntryPrefix *a) {
    s32 count;
    QuestDownloadTextNode *first;
    QuestDownloadTextNode *tl;
    s32 pad;
    QuestDownloadTextNode *head;
    u8 *base;
    QuestDownloadItemNode *t;
    QuestDownloadTextNode *tail;
    u8 *p;

    base = reinterpret_cast<u8 *>(lbl_80596258.text);
    t = a->src;
    if (t == NULL || t->off == 0) {
def:
        return Default_803EBEFC(a->off);
    }
    if ((u32)t->x4 == 0xFFFFFFFFU) {
        if (t->a != 0x1F) {
            goto def;
        }
        if (TQuestVmDownLoadServer__sub_803EEA48((s32)&lbl_805A0470 + lbl_805D78F0, t->off, QUEST_TEXT_SCRATCH(base), &count) > 0) {
            goto build;
        }
        goto def;
    } else {
        if (TQuestVmDownLoadServer::read_quest_chunk(t->x4, t->a, t->b, QUEST_TEXT_SCRATCH(base), &count) <= 0) {
            goto def;
        }
    }
build:
    p = QUEST_TEXT_SCRATCH(base);
    tail = NULL;
    head = NULL;
    while (count > 0) {
        if (TQuestVmDownLoadServer::build_text_node_chain(p, t, t->off, &first, &tl) == NULL) {
            free_node_list__22TQuestVmDownLoadServerFv(head);
            return NULL;
        }
        if (head == NULL) {
            head = first;
            tail = tl;
        } else {
            tail->next = first;
            tail = tl;
        }
        p += 5;
        while (*p++ != 0) {
        }
        if ((u32)p & 1) {
            p++;
        }
        count--;
    }
    return head;
}
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

void TQuestVmDownLoadServer__sub_803EC09C(void) {
    s32 idx;
    QuestDownloadSlot *e;
    QuestDownloadTextNode *tail;
    QuestDownloadTextNode *head;
    QuestDownloadEntryNode *o;
    QuestDownloadQueueNode *qh;
    QuestDownloadQueueNode *q;
    QuestDownloadQueueNode *qt;
    QuestDownloadTextNode *r;
    QuestDownloadTextNode *n;

    e = &quest_download_slot_chain_table[lbl_805D78F0];
    if ((u32)(o = e->entryHead) == 0xFFFFFFFFU) {
        return;
    }
    qh = NULL;
    qt = NULL;
    for (; o != NULL; o = o->next) {
        if (o->prefix.off != lbl_805D78EC) {
            continue;
        }
        q = TQuestVmDownLoadServer__sub_803ECE94();
        if (q == NULL) {
            for (; qh != NULL; qh = qh->next) {
                push_download_entry__22TQuestVmDownLoadServerFPl(qh->text);
            }
            qh = NULL;
            break;
        }
        q->text = r = (QuestDownloadTextNode *)TQuestVmDownLoadServer__sub_803EBEFC(&o->prefix);
        q->entry = o;
        q->score = (r == NULL) ? 0 : TQuestVmDownLoadServer__sub_803ED0B4((u8 *)o, r->payload.head.attribute);
        q->next = NULL;
        if (qh == NULL) {
            qh = qt = q;
        } else {
            qt->next = q;
            qt = q;
        }
    }
    e = &quest_download_slot_chain_table[idx = lbl_805D78F0];
    head = e->textHead;
    tail = Last_803EC09C(head);
    TQuestVmDownLoadServer__sub_803EBA98(idx, (QuestDownloadTextNode *)head);
    while ((n = get_next_node__22TQuestVmDownLoadServerFPv(qh)) != NULL) {
        append_unique_node__22TQuestVmDownLoadServerFiPvPvPv(idx, (QuestDownloadTextNode **)&head, (QuestDownloadTextNode **)&tail, (QuestDownloadTextNode *)n);
    }
    if ((n = Default_803EC09C(lbl_805D78EC)) != NULL) {
        append_unique_node__22TQuestVmDownLoadServerFiPvPvPv(idx, (QuestDownloadTextNode **)&head, (QuestDownloadTextNode **)&tail, (QuestDownloadTextNode *)n);
    }
    e->textHead = head;
    TQuestVmDownLoadServer__sub_803ECD1C((QuestDownloadQueueNode *)qh);
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
QuestDownloadTextNode *get_next_node__22TQuestVmDownLoadServerFPv(QuestDownloadQueueNode *p) {
    QuestDownloadQueueNode *best = NULL;
    QuestDownloadTextNode *ret;
    u32 key;
    for (; p != NULL; p = p->next) {
        if (p->text != NULL && (best == NULL || p->score > key)) {
            best = p;
            key = p->score;
        }
    }
    if (best == NULL) {
        return NULL;
    }
    ret = best->text;
    best->text = Detach_803EBBBC(ret);
    best->score = best->text == NULL ? 0 : TQuestVmDownLoadServer__sub_803ED0B4((u8 *)best->entry, best->text->payload.head.attribute);
    return ret;
}
#pragma pop


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
void TQuestVmDownLoadServer__sub_803EC284(s32 index, s32 mode) {
    QuestDownloadTextNode *head;
    s32 saved_mode = mode;
    if (saved_mode == 1) {
        TQuestVmDownLoadServer__sub_803EC09C();
    }
    head = quest_download_slot_chain_table[lbl_805D78F0].textHead;
    if (lbl_805D7834 > 0) {
        lbl_805D78A4 = 80;
    } else {
        lbl_805D78A4 = TQuestVmDownLoadServer::get_buffer_size();
    }
    mode = count_text_groups_that_fit(head);
    while (index >= mode) {
        index -= mode;
        advance_text_groups(head, mode);
        mode = count_text_groups_that_fit(head);
        if (mode == 0) {
            TQuestVmDownLoadServer__sub_803EC284(0, 0);
            goto finish;
        }
    }
    lbl_805D78A0 = head;
    lbl_805D7898 = index;
    lbl_805D789C = mode;
finish:
    if (saved_mode == 1 && lbl_805D7834 == 0) {
        TQuestVmDownLoadServer__sub_803EB4D4();
    }
}

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

void TQuestVmDownLoadServer__sub_803EC460(s32 pos, s32 x) {
    QuestDownloadTextNode *first;
    QuestDownloadTextNode *tl;
    QuestDownloadSlot *e;
    u8 *base;
    QuestDownloadEntryNode *o;
    QuestDownloadEntryNode *best;
    u16 bestv;
    u16 v;
    QuestDownloadItemNode *t;

    e = &quest_download_slot_chain_table[pos];
    base = reinterpret_cast<u8 *>(lbl_80596258.text);
    best = NULL;
    bestv = 0;
    if (e->textHead != NULL) {
        return;
    }
    if ((u32)(o = e->entryHead) == 0xFFFFFFFFU) {
def:
        e->textHead = Default_803EC460(x);
        return;
    }
    for (; o != NULL; o = o->next) {
        if (o->prefix.off != x) {
            continue;
        }
        v = (o->prefix.src == NULL) ? 0 : TQuestVmDownLoadServer__sub_803ED0B4((u8 *)o, o->prefix.src->c);
        if (v > bestv || best == NULL) {
            bestv = v;
            best = o;
        }
    }
    if (best == NULL || (t = best->prefix.src) == NULL || t->off == 0) {
        goto def;
    }
    if ((u32)t->x4 == 0xFFFFFFFFU) {
        if (t->a != 0x1F) {
            goto def;
        }
        if (TQuestVmDownLoadServer__sub_803EED0C((s32)&lbl_805A0470 + pos, t->off, (s32)(QUEST_TEXT_SCRATCH(base))) > 0) {
            goto build;
        }
        goto def;
    } else {
        if (TQuestVmDownLoadServer__sub_803F0048(t->x4, t->a, t->b, QUEST_TEXT_SCRATCH(base)) <= 0) {
            goto def;
        }
    }
build:
    e->textHead = (QuestDownloadTextNode *)TQuestVmDownLoadServer::build_text_node_chain(QUEST_TEXT_SCRATCH(base), t, t->off, &first, &tl);
}
#pragma pop

#undef QUEST_TEXT_SCRATCH

u16 TQuestVmDownLoadServer::jis_to_sjis(u16 arg0) {
    u8 lo;
    u8 hi;
    hi = arg0 >> 8;
    lo = arg0;
    if (arg0 < 0x2121 || arg0 > 0x7E7E) {
        return 0;
    }
    if (lo < 0x21 || lo >= 0x7F) {
        return 0;
    }
    lo += 0x1F;
    if (hi & 1) {
        hi >>= 1;
    } else {
        hi >>= 1;
        hi--;
        lo += 0x5E;
    }
    if (lo >= 0x7F) {
        lo++;
    }
    if (hi < 0x2F) {
        hi += 0x71;
    } else {
        hi += 0xB1;
    }
    return (hi << 8) | lo;
}

// The callers validate Shift-JIS lead bytes; this conversion checks the trail byte.
s32 TQuestVmDownLoadServer__sub_803EC69C(int code) {
    u32 lo = code & 0xff;
    u8 hi = ((u32)code >> 8) & 0xff;
    code = hi;
    u32 row;
    u8 outlo;
    if (lo < 0x40 || lo > 0xfc || lo == 0x7f) {
        return 0;
    }
    if ((u32)code >= 0xe0) {
        code -= 0x40;
    }
    row = ((u8)code - 0x81) * 2 + 0x21;
    if ((u8)lo >= 0x9f) {
        row++;
        outlo = lo - 0x7e;
    } else if ((u8)lo >= 0x80) {
        outlo = lo - 0x20;
    } else {
        outlo = lo - 0x1f;
    }
    return ((row << 8) & 0xff00) | outlo;
}

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
s32 TQuestVmDownLoadServer__sub_803EC71C(u16 *text, u8 *out, s32 count) {
    s32 i;
    u8 *dst;
    u16 ch;
    s32 kind;
    u16 next;
    u16 pair;
    dst = out;
    i = 0;
    while (i < count) {
        ch = *text;
        kind = Kind_803EC71C(ch);
        if (kind == 0) {
            *dst = (s8)ch;
            text++;
            dst++;
            i++;
        } else if (kind & 1) {
            next = ReadNext_803EC71C(text);
            i++;
            // Narrowing to u16 retains only the first payload byte.
            pair = ch << 8;
            if (((next >> 8) & 0xf) == kind + 1) {
                pair |= next & 0xff;
                text++;
                i++;
                if (IsJis_803EC71C(pair)) {
                    pair = TQuestVmDownLoadServer::jis_to_sjis(pair);
                }
                dst[0] = (s8)(pair >> 8);
                dst[1] = (s8)pair;
                dst += 2;
            }
        }
    }
    *dst = 0;
    return dst - out;
}
#pragma pop


s32 TQuestVmDownLoadServer::is_valid_sjis_code(u16 arg0) {
    s32 var_r0;
    if ((arg0 >= 0x2120U) && (arg0 < 0x3020U)) {
        if ((s32) (arg0 & 0xFF00) == 0x2500) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        if (var_r0 != 0) {
            return 0;
        }
        return 1;
    }
    return 0;
}

s32 TQuestVmDownLoadServer__sub_803EC884(u16 arg0) {
    if (arg0 >= 0x3020U) {
        return 1;
    }
    return 0;
}

s32 TQuestVmDownLoadServer::is_download_command(u16 arg0, s32 arg1) {
    if ((arg1 != 0) && (arg0 == 0x213C)) {
        return 1;
    }
    if ((s32) (arg0 & 0xFF00) == 0x2500) {
        return 1;
    }
    return 0;
}

s32 TQuestVmDownLoadServer__sub_803EC8D8(u16 arg0) {
    s32 temp_r0;
    s32 var_r3;
    u16 var_r4;
    if ((arg0 > 0x20U) && (arg0 < 0x7FU)) {
        var_r3 = 0;
        return 0;
    }
    var_r4 = arg0;
    temp_r0 = arg0 & 0xFF00;
    switch (temp_r0) {
    case 0x2300:
        var_r3 = var_r4 & 0x7F;
        return var_r3;
    case 0x2400:
        var_r3 = (var_r4 & 0x7F) | 0x80;
        return var_r3;
    case 0x2500:
        var_r3 = 0;
        return 0;
    default:
        return TQuestVmDownLoadServer::lookup_value_by_key(arg0);
    }
}

s32 TQuestVmDownLoadServer__sub_803EC95C(u16 *out, u8 *text, int attr) {
    u16 *dst = out;
    u8 c;
    while ((c = *text) != 0) {
        if (c < 0x80 || (c >= 0xA0 && c < 0xE0)) {
            dst += TQuestVmDownLoadServer::encode_char_with_attr(dst, *text++, attr);
        } else {
            u16 ch = (c << 8) | text[1];
            dst += TQuestVmDownLoadServer::encode_char_with_attr(dst, ch, attr);
            text += 2;
        }
    }
    return dst - out;
}

void TQuestVmDownLoadServer__sub_803ECA1C(u16 *arg0, s32 arg1, s32 arg2) {
    u16 a = arg2 << 12;
    while (arg1-- != 0) {
        *arg0 = (*arg0 & 0xFFF) | a;
        arg0++;
    }
}

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

s32 TQuestVmDownLoadServer::encode_char_with_attr(u16 *out, u16 ch, s32 attr) {
  s32 hi;
  u16 c;
  s32 lo;
  int new_var;
  u16 a;
  c = ch;
  a = (attr & 0xF) << 12;
  new_var = ch & 0xFF;
  hi = (ch >> 8) & 0xFF;
  lo = new_var;
  if (IsSjis_803ECAE8(new_var, hi))
  {
    if (Kind_803ECAE8(c, new_var) == 1)
    {
      a |= 0x300;
    }
    else
    {
      a |= 0x700;
    }
  }
  else
    if (IsJisPair_803ECAE8(new_var, hi))
  {
    a |= 0x500;
    if (ch == 0x2474)
    {
      ch = 0x2574;
    }
  }
  else
  {
    *out = a | lo;
    return 1;
  }
  *(out++) = a | (ch >> 8);
  *out = (a + 0x100) | (ch & 0xFF);
  return 2;
}

#pragma pop

s32 TQuestVmDownLoadServer__sub_803ECC7C(u32 arg0) {
    u8 hi = (arg0 >> 8) & 0xFF;
    u8 lo = arg0;
    s32 lead;
    if (hi < 0x81 || hi > 0xFC || (hi >= 0xA0 && hi < 0xE0)) {
        lead = 0;
    } else {
        lead = 1;
    }
    if (lead == 0) {
        return 0;
    }
    if (lo < 0x40 || lo > 0xFC || lo == 0x7F) {
        return 0;
    }
    return 1;
}

s32 TQuestVmDownLoadServer::is_sjis_lead_byte(u8 arg0) {
    if ((arg0 < 0x81U) || (arg0 > 0xFCU) || ((arg0 >= 0xA0U) && (arg0 < 0xE0U))) {
        return 0;
    }
    return 1;
}

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
void TQuestVmDownLoadServer__sub_803ECD1C(QuestDownloadQueueNode *p) {
    while (p != NULL) {
        QuestDownloadQueueNode *next = p->next;
        if (p != NULL) return_quest_pool_cell(p);
        p = next;
    }
}
void free_node_list__22TQuestVmDownLoadServerFv(QuestDownloadTextNode *p) {
    while (p != NULL) {
        QuestDownloadTextNode *next = p->next;
        if (p != NULL) return_quest_pool_cell(p);
        p = next;
    }
}
void TQuestVmDownLoadServer__sub_803ECD8C(QuestDownloadEntryNode *p) {
    QuestDownloadEntryNode *next;
    while (p != NULL) {
        next = p->next;
        if (p != NULL) return_quest_pool_cell(p);
        p = next;
    }
}
void release_node_chain__22TQuestVmDownLoadServerFPv(QuestDownloadItemNode *p) {
    u32 prev = 0xFFFFFFFF;
    QuestDownloadItemNode *next;
    while (p != NULL) {
        next = p->next;
        if ((prev == 0xFFFFFFFF || p->x4 != prev) && (u32)p->x4 != 0xFFFFFFFF) {
            TQuestVmDownLoadServer__sub_803EED9C(p->x4);
        }
        prev = p->x4;
        if (p != NULL) return_quest_pool_cell(p);
        p = next;
    }
}
void TQuestVmDownLoadServer__sub_803ECE5C(QuestDownloadSegment *p) {
    QuestDownloadSegment *next;
    while (p != NULL) {
        next = p->next;
        if (p != NULL) return_quest_pool_cell(p);
        p = next;
    }
}
#pragma push
#pragma inline_depth(1)
inline QuestDownloadFreeLink *pop_free_block() {
    QuestDownloadFreeLink *p = lbl_805D78B0;
    if (p == NULL) return NULL;
    lbl_805D78B0 = lbl_805D78B0->next;
    lbl_805D78AC--;
    return p;
}
QuestDownloadQueueNode *TQuestVmDownLoadServer__sub_803ECE94(void) {
    QuestDownloadFreeLink *p = pop_free_block();
    if (p == NULL) return NULL;
    new (&reinterpret_cast<QuestDownloadPoolCell *>(p)->queue, quest_download_pool_storage) QuestDownloadQueueNode;
    return reinterpret_cast<QuestDownloadQueueNode *>(p);
}
void *TQuestVmDownLoadServer__sub_803ECED0(void) {
    QuestDownloadFreeLink *p = pop_free_block();
    if (p == NULL) return NULL;
    // Inspect the persistent cell representation before changing its active
    // member. Defaults retain these bytes, so initialize the new head's value
    // explicitly rather than reading an indeterminate u16 after construction.
    u8 *bytes = reinterpret_cast<u8 *>(reinterpret_cast<QuestDownloadPoolCell *>(p));
    const u8 attribute_high = bytes[offsetof(QuestDownloadTextNode, payload.head.attribute)];
    const u8 attribute_low = bytes[offsetof(QuestDownloadTextNode, payload.head.attribute) + 1];
    new (&reinterpret_cast<QuestDownloadPoolCell *>(p)->text, quest_download_pool_storage) QuestDownloadTextNode;
    new (&reinterpret_cast<QuestDownloadPoolCell *>(p)->text.payload.head, quest_download_pool_storage) QuestDownloadTextHead;
    bytes[offsetof(QuestDownloadTextNode, payload.head.attribute)] = attribute_high;
    bytes[offsetof(QuestDownloadTextNode, payload.head.attribute) + 1] = attribute_low;
    return reinterpret_cast<QuestDownloadTextNode *>(p);
}
void *TQuestVmDownLoadServer__sub_803ECF0C(void) {
    QuestDownloadFreeLink *p = pop_free_block();
    if (p == NULL) return NULL;
    new (&reinterpret_cast<QuestDownloadPoolCell *>(p)->segment, quest_download_pool_storage) QuestDownloadSegment;
    return reinterpret_cast<QuestDownloadSegment *>(p);
}
void *TQuestVmDownLoadServer__sub_803ECF48(void) {
    QuestDownloadFreeLink *p = pop_free_block();
    if (p == NULL) return NULL;
    new (&reinterpret_cast<QuestDownloadPoolCell *>(p)->entry, quest_download_pool_storage) QuestDownloadEntryNode;
    return reinterpret_cast<QuestDownloadEntryNode *>(p);
}
QuestDownloadItemNode *TQuestVmDownLoadServer__sub_803ECF84(void) {
    QuestDownloadFreeLink *p = pop_free_block();
    if (p == NULL) return NULL;
    new (&reinterpret_cast<QuestDownloadPoolCell *>(p)->item, quest_download_pool_storage) QuestDownloadItemNode;
    return reinterpret_cast<QuestDownloadItemNode *>(p);
}
#pragma pop

void push_download_entry__22TQuestVmDownLoadServerFPl(void *arg0) {
    if (arg0 != NULL) return_quest_pool_cell(arg0);
}
QuestDownloadPoolCell quest_download_block_pool[2000];
extern s32 quest_download_free_list_ready_flag;
void TQuestVmDownLoadServer::init_block_free_list() {
    QuestDownloadPoolCell *p;
    if (quest_download_free_list_ready_flag == 0 && lbl_805D78AC == 2000) return;
    lbl_805D78B0 = &quest_download_block_pool[0].free;
    for (p = quest_download_block_pool; p < &quest_download_block_pool[1999]; p++) {
        new (&p->free, quest_download_pool_storage) QuestDownloadFreeLink;
        p->free.next = &(p + 1)->free;
    }
    new (&p->free, quest_download_pool_storage) QuestDownloadFreeLink;
    p->free.next = 0;
    lbl_805D78AC = 2000;
    quest_download_free_list_ready_flag = 0;
}
#pragma pop

typedef char RecoveredGlobal_803EE2E4_lbl_8058DC98_size[sizeof(lbl_8058DC98) == 0x50 ? 1 : -1];

u16 TQuestVmDownLoadServer__sub_803ED0B4(u8 *arg0, u16 arg1) {
    if (arg1 != 0) {
        return arg1 + 0x3E8;
    }
    // All three native callers pass the complete live entry object.
    return reinterpret_cast<QuestDownloadEntryNode *>(arg0)->x8;
}


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

s32 TQuestVmDownLoadServer::calc_item_cost_bonus(u8 kind, u8 v, u8 w, s32 base, s32 add) {
    s32 r = 0;
    switch (kind) {
    case 0:
        if ((v >= 0x14 && v <= 0x19) || v == 0x32) {
            r = 0xF;
        }
        break;
    case 1:
        if (v == 0x1A) {
            r = 0x14;
        }
        break;
    case 2:
        if ((u8)(v - 0x1B) <= 1) {
            r = 0xF;
        }
        break;
    case 3:
        if (v == 0x1F || v == 0x38) {
            r = 0x14;
        }
        break;
    case 4:
        if (v == 0x16) {
            r = 0x14;
        }
        break;
    case 5:
        if (w == 0xFF) {
            if (v >= 1 && v <= 0xD) {
                r = 0xF;
            }
        } else if ((v >= 0x80 && v <= 0x8B && w == 4) || (v == 0xD && w == 0)) {
            r = 0xF;
        }
        break;
    case 6:
        if (v >= 0x14 && v <= 0x19) {
            r = 0xF;
        } else if (v == 0x1F || v == 0x38) {
            r = 0x14;
        }
        break;
    case 7:
        if (v == 0x1D) {
            r = 0xF;
        }
        break;
    case 8:
        if ((v >= 0x14 && v <= 0x19) || (v >= 1 && v <= 0xD)) {
            r = 0x14;
        }
        break;
    }
    if (r == 0) {
        return base;
    }
    return base + r + add;
}

s32 calc_item_entry_cost__22TQuestVmDownLoadServerFUcUcl(QuestDownloadEntryPrefix *a, u8 k, u8 v, s32 base) {
    s32 lvl = 0;
    QuestDownloadItemNode *s = a->src;

    if (s != NULL && ((s->a >= 0x14 && s->a <= 0x19) || s->a == 0x32)) {
        lvl = 1;
        if (s->off + 1 == a->off) {
            lvl = 2;
        }
    }
    if (k == 0xC7) {
        if (InRange_803ED26C(v)) {
            return base + 0x1E;
        }
        return base + 0x19;
    }
    if (k == 0xC8) {
        if (v == 0) {
            return base;
        }
        if (lvl == 2) {
            return base + 0x14;
        }
        return base + 5;
    }
    if (k == 0xC1 || k == 0xE1) {
        if (lvl == 2) {
            base += 5;
        }
        return base;
    }
    if ((u8)(k - 0xC4) <= 1 || (k >= 0xCE && k <= 0xD1)) {
        if ((v >= 1 && v <= 0xD) || (v >= 0x16 && v <= 0x17)) {
            return base + 5;
        }
        return base;
    }
    if (k == 0xC2) {
        if (v == 0) {
            return base;
        }
        if (lvl == 2) {
            base += 3;
        }
        return base;
    }
    if (k >= 0xFC && k <= 0xFD && v >= 1 && v <= 0x17) {
        return base + 0x12;
    }
    if ((k == 0xFA || k == 0xFE) && v >= 0x14 && v <= 0x18) {
        return base + 0x12;
    }
    return base;
}
#pragma pop


s32 TQuestVmDownLoadServer::calc_pair_cost_bonus(u8 arg0, u8 arg1, s32 arg2) {
    if (arg0 >= 0x14 && arg0 <= 0x18) {
        if (arg1 >= 0x14 && arg1 <= 0x18) {
            return arg2 + 3;
        }
        return arg2;
    }
    if (arg0 == 0x1F && arg1 == 0x1F) {
        return arg2 + 0xF;
    }
    if (arg0 == 0x21 || arg0 == 0x26 || arg0 == 0x27) {
        return arg2 + 0x14;
    }
    if (arg0 == 0x20 || arg0 == 0x22) {
        return arg2 + 0xF;
    }
    if (arg0 == 0x1B && arg1 == 0x1C) {
        return arg2 + 0x14;
    }
    if (arg0 == 0x1A && arg1 == 0x1A) {
        return arg2 + 5;
    }
    return arg2;
}

s32 TQuestVmDownLoadServer::calc_item_entry_cost_extra(u8 arg0, u8 arg1, u8 arg2, s32 arg3) {
    if ((arg0 == 0xD) && (arg1 == 0)) {
        if ((arg2 >= 1U) && (arg2 <= 0x17U)) {
            return arg3 + 3;
        }
    } else if ((arg1 >= 4U) && (arg1 <= 6U) && (arg2 >= 1U) && (arg2 <= 0x17U)) {
        if ((arg0 == 0x8D) || ((arg0 == 0x8E) && (arg1 == 6))) {
            return arg3 + 0xA;
        }
        if (arg0 <= 0x8CU) {
            return arg3 + 3;
        }
    } else if ((arg1 == 8) && (arg2 >= 0x14U) && (arg2 <= 0x18U)) {
        if (((arg0 >= 0x80U) && (arg0 <= 0x8EU)) || (arg0 == 0x92) || (arg0 == 0x94) || (arg0 == 0xA0) || (arg0 == 0xA2) || ((u8)(arg0 - 0xAE) <= 1U) || (arg0 == 0xB1) || (arg0 == 1) || ((arg0 >= 0xAU) && (arg0 <= 0xCU))) {
            return arg3 + 0xF;
        }
        return arg3 + 3;
    }
    return arg3;
}


s32 calc_entry_cost__22TQuestVmDownLoadServerFPvPv(QuestDownloadEntryPrefix *a, QuestDownloadEntryPrefix *b) {
    QuestDownloadItemNode *s2;
    u8 k;
    u8 bk;
    s32 extra;
    QuestDownloadItemNode *s;
    u8 q;
    u8 p;

    extra = 0;
    p = 0;
    q = 0;
    if ((k = a->a) >= 0x2D && k <= 0x38) {
        p = a->b;
    } else {
        q = a->b;
    }
    if (b == NULL) {
        bk = 0;
    } else if ((s = b->src) == NULL) {
        bk = 0;
    } else {
        if ((bk = s->a) == 0x28) {
            return 0;
        }
        if (bk == 0x29 || (bk == 0x19 && s->off > 0) || (bk == 0x1F && (u32)s->x4 == 0xFFFFFFFFU)) {
            extra = 0x14;
        }
    }
    if ((s2 = a->src) != NULL) {
        if (s2->a == 0x19 && s2->off == 0) {
            extra += 10;
        } else if (s2->a <= 0x19 || s2->a >= 0x1F) {
            extra += 1;
        }
    }
    if (q != 0 || k == 0xD) {
        return TQuestVmDownLoadServer::calc_item_entry_cost_extra(k, q, bk, extra);
    }
    if (k == 0x2D) {
        return TQuestVmDownLoadServer::calc_item_cost_bonus(p, bk, 0xFF, extra, 0);
    }
    if (bk >= 0x32 && bk <= 0x38) {
        if (b->src != NULL) {
            p = b->src->b;
        } else {
            p = 0;
        }
        return TQuestVmDownLoadServer::calc_item_cost_bonus(p, k, q, extra, 2);
    }
    if (k >= 0x14 && k < 0xC0) {
        return TQuestVmDownLoadServer::calc_pair_cost_bonus(k, bk, extra);
    }
    if (k >= 0xC0) {
        return calc_item_entry_cost__22TQuestVmDownLoadServerFUcUcl(a, k, bk, extra);
    }
    return extra;
}


#pragma push
#pragma opt_common_subs off
void TQuestVmDownLoadServer::reset_slot_chain_timers(s32 arg0) {
    QuestDownloadEntryNode *n;
    QuestDownloadItemNode *l;
    QuestDownloadSlot *t = &quest_download_slot_chain_table[arg0];
    for (n = t->entryHead; n != NULL; n = n->next) {
        n->xa = 0;
        l = n->prefix.src;
        if (l != NULL && l->a == 0x19 && l->off == 0) {
            n->xa = 10;
        }
    }
}
#pragma pop

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
s32 TQuestVmDownLoadServer__sub_803ED84C(QuestDownloadEntryNode *entry, s32 index, s32 limit) {
    QuestDownloadEntryNode *next;
    s32 length;
    u32 best;
    u16 score;
    if (entry_source_is_special(entry)) {
        entry->x8 = 0;
        return 0;
    }
    length = entry->prefix.off;
    if (entry->prefix.a == 0xFF || index + length >= limit) {
        best = entry_follow_score(entry, NULL);
    } else {
        if ((next = quest_download_slot_chain_table[index + length].entryHead) == NULL && lbl_805D7888 >= 3) {
            return -1;
        }
        best = 0;
        for (; next != NULL; next = next->next) {
            score = entry_follow_score(entry, next);
            if (score > (u16)best) {
                best = score;
            }
        }
    }
    entry->x8 = best;
    return 0;
}
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
s32 TQuestVmDownLoadServer::select_best_slot_entry(s32 idx, s32 max, s32 want) {
    QuestDownloadSlot *slot = &quest_download_slot_chain_table[idx];
    QuestDownloadEntryNode *e;
    QuestDownloadEntryNode *best;
    QuestDownloadEntryNode *q;
    for (e = slot->entryHead; e != NULL; e = e->next) {
        if (want < 0 || e->prefix.off == want) {
            if (TQuestVmDownLoadServer__sub_803ED84C(e, idx, max) == -1) {
                return -1;
            }
        }
    }
    if (slot == NULL || slot->entryHead == NULL) {
        return -1;
    }
    best = slot->entryHead;
    for (q = best->next; q != NULL; q = q->next) {
        if (q->x8 > best->x8) {
            best = q;
        }
    }
    Relax_803ED9AC(best, idx, max);
    return best->prefix.off;
}
#pragma pop
#pragma pop

s32 TQuestVmDownLoadServer__sub_803EDB20(u8 arg0) {
    return lbl_8047F8B8[arg0] & 0x20;
}

s32 TQuestVmDownLoadServer__sub_803EDB3C(u8 arg0) {
    return lbl_8047F8B8[arg0] & 0x40;
}

s32 TQuestVmDownLoadServer__sub_803EDB58(u8 arg0) {
    return lbl_8047F8B8[arg0] & 0x80;
}

s32 TQuestVmDownLoadServer__sub_803EDB74(u8 arg0) {
    return lbl_8047F8B8[arg0] & 0xC0;
}

s32 TQuestVmDownLoadServer::sum_entry_sizes(s32 start, s32 n) {
    QuestDownloadInputEntry *e = &quest_download_entry_table[start];
    s32 sum = 0;
    s32 i;
    for (i = n; i > 0; i--) {
        sum += e->len;
        e++;
    }
    return sum;
}

u8 *TQuestVmDownLoadServer::find_keyword_entry(u16 *start, u16 *end) {
    u8 c;
    u8 *p;
    u16 *s;
    s32 rem;
    s32 len;
    s32 n;
    len = end - start;
    p = quest_download_keyword_table;
    while (*p != 0) {
        n = *p++;
        if (len == n) {
            s = start;
            for (rem = len; rem > 0;) {
                c = *s++;
                if (c >= 0x61U && c <= 0x7AU) {
                    c -= 0x20;
                }
                if (*p != c) {
                    break;
                }
                rem--;
                p++;
            }
            if (rem == 0) {
                return p;
            }
            p += rem;
        } else {
            p += n;
        }
        while (*p++ != 0) {
        }
    }
    return NULL;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
inline s32 count_encoded_download_input(QuestDownloadInputEntry *end) {
    s32 encoded = 0;
    QuestDownloadInputEntry *scan;
    for (scan = quest_download_entry_table; scan < end; scan++) {
        if (scan->ch & 0xFF00) encoded += 2;
        else encoded++;
    }
    return encoded;
}
// The unchanged packet ABI carries a valid input character-array address.
s32 TQuestVmDownLoadServer__sub_803EDC20(u32 input_address) {
    QuestDownloadInputEntry *entry;
    u8 *codes;
    s32 count;
    u8 *input;
    u16 lead;
    s32 encoded;
    u16 ch;
    lead = 0;
    input = reinterpret_cast<u8 *>(input_address);
    entry = lbl_805D78C8;
    codes = lbl_805D78BC;
    count = lbl_805D78C0;
    encoded = count_encoded_download_input(entry);
    for (; *input != 0; input++) {
        if (lead != 0) {
            ch = TQuestVmDownLoadServer__sub_803EC69C((lead << 8) | *input);
            if (ch != 0) {
                if (count >= 0x24 || encoded >= 0x4E) return -1;
                entry->ch = ch;
                entry->len = 2;
                entry++;
                *codes++ = TQuestVmDownLoadServer__sub_803EC8D8(ch);
                count++;
                encoded += 2;
            }
            lead = 0;
        } else if (TQuestVmDownLoadServer::is_sjis_lead_byte(*input)) {
            lead = *input;
        } else if ((*input >= 0x20 && *input < 0x7F) || (*input >= 0xA0 && *input < 0xE0)) {
            if (count >= 0x24 || encoded >= 0x4F) return -1;
            entry->ch = *input;
            entry->len = 1;
            lead = 0;
            count++;
            encoded++;
            *codes++ = 0;
            entry++;
        }
    }
    lbl_805D78C8 = entry;
    lbl_805D78C4 = entry;
    lbl_805D78BC = codes;
    lbl_805D78B8 = codes;
    lbl_805D78C0 = count;
    return count;
}

inline u8 Upper_803EDDA4(s32 code) {
    u8 ch = code;
    if ((u8)code >= 0x61U && (u8)code <= 0x7aU) {
        ch -= 0x20;
    }
    return ch;
}
extern u8 lbl_8047F9B8[];
extern u8 *lbl_8047FBD4[];
u8 *TQuestVmDownLoadServer__sub_803EDDA4(u16 *start, u16 *end) {
    s32 len = end - start;
    s32 index;
    u8 **entry;
    u8 *p;
    u8 *limit;
    s32 ch;
    if (len == 0) {
        return lbl_8047F9B8 + 1;
    }
    if ((u32)(len - 1) <= 1) {
        s32 first = (u8)start[0];
        if (first >= 'a' && first <= 'z') {
            index = first - 'a';
        } else if (first >= 'A' && first <= 'Z') {
            index = first - 'A';
        } else {
            return NULL;
        }
        entry = lbl_8047FBD4 + index;
        p = *entry;
        if (len == 1) {
            return p + 1;
        }
        do {
            limit = *++entry;
        } while (limit == NULL);
        ch = Upper_803EDDA4(start[1] & 0xff);
        for (p += 11; p < limit; p += 11) {
            if (*p == ch) {
                return p + 1;
            }
        }
    }
    return NULL;
}


// The frontend starts and fills the actual halfword scratch object.
s32 TQuestVmDownLoadServer__sub_803EDF64(const u16 *input, s32 count,
                                      u16 *output, s32 *outputCount) {
    const u16 *cursor;
    u8 category;
    s32 consumed;
    u8 *mapping;
    category = lbl_8047F8B8[(u8)*input] & 0xF;
    *outputCount = 1;
    if (category <= 9) {
        if (category <= 5) {
            mapping = lbl_8047F9B8 + 1;
            cursor = input;
            consumed = 1;
            goto fallback_mapping;
        }
        if (category <= 8 || lbl_805D78E4 == 0) {
            output[0] = TQuestVmDownLoadServer__sub_803E721C(*input);
        } else {
            output[0] = TQuestVmDownLoadServer::map_key_to_code(*input);
        }
        return 1;
    }
    {
        u16 state = 0;
        if (category <= 12) {
            if (category == 12) {
                output[0] = TQuestVmDownLoadServer__sub_803E719C(0x73, *input);
                state = 1;
            } else {
                output[0] = TQuestVmDownLoadServer__sub_803E721C(*input);
                if (category == 10) state = 2;
                else state = 3;
            }
        }
        if (count == 1) {
            return state != 0 ? -1 : 0;
        }
        cursor = input + 1;
        {
            u8 next = *cursor;
            s32 first = (u8)*input;
            if (first == (u8)*cursor) {
                if (category == 12) return 2;
                if (category == 13) {
                    output[0] = TQuestVmDownLoadServer__sub_803E719C(0x43, *cursor);
                    return 1;
                }
            }
            if ((first == 'x' || first == 'X') && ((next = *(cursor = input + 1)) == 'n' || next == 'N')) {
                output[0] = TQuestVmDownLoadServer__sub_803E719C(0x73, *input);
                return 2;
            }
            if (state == 1 && next == '\'') return 2;
            category = lbl_8047F8B8[next] & 0xF;
        }
        if (category == 7 && state == 3) {
            output[0] += 2;
            return 2;
        }
        if (category == 6 && state >= 2) {
            output[0]++;
            if ((u8)*input == 0xB3) {
                output[0] = TQuestVmDownLoadServer__sub_803E719C(0x74, *cursor);
            }
            return 2;
        }
        if (state >= 2 || (category > 5 && category <= 14 && state == 1)) return 1;
        consumed = 2;
        for (;;) {
            if (category <= 5) {
                mapping = TQuestVmDownLoadServer::find_keyword_entry((u16 *)input, (u16 *)cursor + 1);
                if (mapping != NULL) goto emit_mapping;
                mapping = TQuestVmDownLoadServer__sub_803EDDA4((u16 *)input, (u16 *)cursor);
                if (mapping == NULL) return -2;
                goto fallback_mapping;
            }
            if (consumed++ >= count) return 0;
            cursor++;
            category = lbl_8047F8B8[(u8)*cursor] & 0xF;
            if ((category >= 6 && category <= 12) || consumed > 4) return -2;
        }
    }

fallback_mapping:
    // The pinned classifier has classes 1..13/15, never zero.
    mapping += (category - 1) * 2;
emit_mapping:
    *output++ = TQuestVmDownLoadServer__sub_803E719C(*mapping++, *cursor);
    if (*mapping != 0) {
        *output = TQuestVmDownLoadServer__sub_803E719C(*mapping, *cursor);
        *outputCount = 2;
    }
    return consumed;
}

#pragma pop

void TQuestVmDownLoadServer__sub_803EE2E4(void) {
    lbl_8058DC98[0] = 0;
}

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
void TQuestVmDownLoadServer__sub_803EE580(s32 start, s32 length, QuestDownloadTextNode *text, QuestDownloadEntryNode *entries) {
    s32 zero = 0;
    QuestDownloadItemNode *selected;
    s32 *ids;
    QuestDownloadRequestStorage *request = &lbl_805A0698;
    s32 count;
    if (text->payload.head.id == -1) {
        selected = NULL;
    } else {
        if ((selected = (QuestDownloadItemNode *)text->payload.head.source) == NULL) return;
    }
    new (quest_download_text_buffer, quest_download_scratch_storage) QuestDownloadScratchIds;
    ids = reinterpret_cast<QuestDownloadScratchIds *>(quest_download_text_buffer)->values;
    if (entries == NULL || entries == QUEST_DOWNLOAD_ENTRY_LIST_FAILED) {
        if (selected != NULL) *ids++ = selected->x4;
    } else {
        u32 last = -1;
        do {
            QuestDownloadItemNode *item = entries->prefix.src;
            if (item != NULL) {
                u32 id;
                if ((id = item->x4) != -1 && id != last) {
                    *ids++ = id;
                    last = id;
                }
            }
            entries = entries->next;
        } while (entries != NULL);
    }
    if (selected == NULL) {
        strncpy((char *)lbl_8058DD38, (char *)lbl_805A0470.bytes + start, length);
        lbl_8058DD38[length] = zero;
        count = TQuestVmDownLoadServer__sub_803EB420(start, length, text, lbl_805A0340);
        TQuestVmDownLoadServer__sub_803EC71C(lbl_805A0340, lbl_8058DCE8, count);
        request->request.name = (char *)lbl_8058DD38;
        request->request.len = length;
        request->request.pad6 = zero;
        request->request.x7 = 0x19;
        request->request.x8 = zero;
        request->request.text = lbl_8058DCE8;
        TQuestVmDownLoadServer__sub_803EEDC0(&request->request, reinterpret_cast<QuestDownloadScratchIds *>(quest_download_text_buffer)->values, ids - reinterpret_cast<QuestDownloadScratchIds *>(quest_download_text_buffer)->values);
    } else {
        TQuestVmDownLoadServer__sub_803EF958((u32)selected->x4, text->payload.head.id,
            reinterpret_cast<QuestDownloadScratchIds *>(quest_download_text_buffer)->values, ids - reinterpret_cast<QuestDownloadScratchIds *>(quest_download_text_buffer)->values);
    }
}

#pragma pop

void TQuestVmDownLoadServer__sub_803EE2F4(s32 start, s32 end) {
    char *name = (char *)&lbl_8058DC98;
    u8 *encoded = lbl_8058DC48;
    u16 *wide = lbl_805A0340;
    s32 length;
    QuestDownloadTextNode *text;
    QuestDownloadSlot *slot;
    while (start < end && (length = TQuestVmDownLoadServer__sub_803E9F54(start)) != 0) {
        slot = &quest_download_slot_chain_table[start];
        if (start == lbl_805D78F0 && (lbl_805D78E8 == 1 || lbl_805D7834 >= 3)) {
            text = advance_nodes__22TQuestVmDownLoadServerFPvi(lbl_805D78A0, lbl_805D7898);
        } else {
            text = advance_nodes__22TQuestVmDownLoadServerFPvi(slot->textHead, 0);
        }
        if (lbl_805D7848 != 3 && lbl_805D7834 <= 2) {
        emit_entry:
            TQuestVmDownLoadServer__sub_803EE580(start, length, text, slot->entryHead);
            start += length;
            continue;
        }
        if (slot->x16 != 0 && slot->x16 != slot->x15) {
            s32 n = length;
            strncpy((char *)lbl_8058DC98, (char *)lbl_805A0470.bytes + start, n);
            lbl_8058DC98[length] = 0;
            if (length != strlen((char *)lbl_8058DC98)) {
                name[0] = 0;
            } else {
                s32 count = TQuestVmDownLoadServer__sub_803EB420(start, n, text, lbl_805A0340);
                TQuestVmDownLoadServer__sub_803EC71C(lbl_805A0340, lbl_8058DC48, count);
            }
            TQuestVmDownLoadServer__sub_803EE580(start, length, text, slot->entryHead);
        } else {
            if ((u8)name[0] == 0) goto emit_entry;
            char *appendName = name + strlen((char *)lbl_8058DC98);
            u8 *appendEncoded = encoded + strlen((char *)encoded);
            s32 n = text->payload.head.length;
            strncpy(appendName, (char *)lbl_805A0470.bytes + start, n);
            appendName[n] = 0;
            if (n != strlen(appendName)) {
                name[0] = 0;
            } else {
                s32 count = TQuestVmDownLoadServer__sub_803EB420(start, n, text, wide);
                TQuestVmDownLoadServer__sub_803EC71C(wide, appendEncoded, count);
            }
            if ((u8)name[0] != 0) {
                Req_803EEF2C request;
                request.name = name;
                request.len = (u16)strlen(name);
                request.pad6 = 0;
                QuestDownloadItemNode *item;
                if (text == NULL || (item = (QuestDownloadItemNode *)text->payload.head.source) == NULL) {
                    request.x7 = 0x28;
                    request.x8 = 0;
                } else {
                    request.x7 = item->a;
                    request.x8 = item->b;
                }
                request.text = encoded;
                TQuestVmDownLoadServer__sub_803EEF2C(&request);
            }
            name[0] = 0;
        }
        start += length;
    }
}


u16 *TQuestVmDownLoadServer__sub_803EE718(s32 i, s32 len) {
    u16 *out;
    s32 n;
    s32 end;
    s32 r;
    QuestDownloadTextNode *node;
    out = lbl_805A0340;
    end = i + len;
    while (i < end && (n = TQuestVmDownLoadServer__sub_803E9F54(i)) != 0) {
        if (i == lbl_805D78F0) {
            if (lbl_805D78E8 == 1 || lbl_805D7834 >= 3) {
                node = advance_nodes__22TQuestVmDownLoadServerFPvi(lbl_805D78A0, lbl_805D7898);
            } else {
                node = advance_nodes__22TQuestVmDownLoadServerFPvi(quest_download_slot_chain_table[i].textHead, 0);
            }
            r = TQuestVmDownLoadServer__sub_803EB420(i, n, (QuestDownloadTextNode *)node, out);
        } else {
            r = TQuestVmDownLoadServer__sub_803EB420(i, n, (QuestDownloadTextNode *)quest_download_slot_chain_table[i].textHead, out);
        }
        out += r;
        i += n;
    }
    TQuestVmDownLoadServer__sub_803EC71C((u16 *)lbl_805A0340, (u8 *)lbl_805A02A8, (s32)(out - lbl_805A0340));
    return lbl_805A02A8;
}

u8 *TQuestVmDownLoadServer__sub_803EE828(void) {
    TQuestVmDownLoadServer__sub_803EC71C((u16 *)(((u8 *)&lbl_805A0340)), (u8 *)(((u8 *)&lbl_805A02A8)), (s32)(TQuestVmDownLoadServer__sub_803EE934()));
    return ((u8 *)&lbl_805A02A8);
}

#pragma push
#if __option(opt_propagation)
#define EE870_BASE_PREV_PROP 1
#else
#define EE870_BASE_PREV_PROP 0
#endif
#pragma opt_propagation off
#if __option(opt_propagation)
#error EE870_BASE_PROP_NOT_RECOGNIZED
#endif
void TQuestVmDownLoadServer__sub_803EE870(s32 index, s32 mode) {
    QuestDownloadSlot *base = quest_download_slot_chain_table;
    u8 *member = reinterpret_cast<u8 *>(base + index);
    // This character address stays inside the live slot and names its real
    // pointer member (offset/alignment checked in QuestDownloadRecords.h).
    member += offsetof(QuestDownloadSlot, textHead);
    QuestDownloadTextNode **head = reinterpret_cast<QuestDownloadTextNode **>(member);
    QuestDownloadTextNode *node;
    QuestDownloadTextNode *keep;
    QuestDownloadTextNode *next;
    if ((node = *head) == NULL) return;
    if (mode == 1 && (lbl_805D78E8 == 1 || lbl_805D7834 >= 3)) {
        keep = advance_nodes__22TQuestVmDownLoadServerFPvi(lbl_805D78A0, lbl_805D7898);
        while (node != NULL) {
            if (node == keep) break;
            next = TQuestVmDownLoadServer__sub_803EB878(node);
            push_download_entry__22TQuestVmDownLoadServerFPl(node);
            node = next;
        }
        *head = node;
    }
    free_node_list__22TQuestVmDownLoadServerFv(detach_node_chain__22TQuestVmDownLoadServerFPv(node));
}

#pragma pop
#if __option(opt_propagation) != EE870_BASE_PREV_PROP
#error EE870_BASE_PROP_NOT_RESTORED
#endif
#undef EE870_BASE_PREV_PROP

s32 TQuestVmDownLoadServer__sub_803EE934(void) {
    s32 r;
    QuestDownloadTextNode *node;
    u16 *out;
    s32 total;
    s32 i;
    s32 n;
    out = lbl_805A0340;
    i = 0;
    total = 0;
    while ((n = TQuestVmDownLoadServer__sub_803E9F54(i)) != 0) {
        if (i == lbl_805D78F0) {
            if (lbl_805D78E8 == 1 || lbl_805D7834 >= 3) {
                node = advance_nodes__22TQuestVmDownLoadServerFPvi(lbl_805D78A0, lbl_805D7898);
            } else {
                node = advance_nodes__22TQuestVmDownLoadServerFPvi(quest_download_slot_chain_table[i].textHead, 0);
            }
            r = TQuestVmDownLoadServer__sub_803EB420(i, n, (QuestDownloadTextNode *)node, out);
            lbl_805D78EC = n;
            TQuestVmDownLoadServer__sub_803ECA1C(out, r, 7);
        } else {
            r = TQuestVmDownLoadServer__sub_803EB420(i, n, quest_download_slot_chain_table[i].textHead, out);
            TQuestVmDownLoadServer__sub_803ECA1C(out, r, 6);
        }
        out += r;
        i += n;
        total += r;
    }
    return total;
}

s32 TQuestVmDownLoadServer__sub_803EEA48(s32 arg0, s32 arg1, void *arg2, s32 *arg3) {
    s32 i;
    void *r;
    if (lbl_805D7904 == -1) {
        return -3;
    }
    *arg3 = 0;
    r = format_number_text__22TQuestVmDownLoadServerFiiPvi(arg0, arg1, arg2, lbl_805D78FC);
    if (r != 0) {
        arg2 = r;
        (*arg3)++;
    }
    for (i = 0; i < 4; i++) {
        if (i != lbl_805D78FC) {
            r = format_number_text__22TQuestVmDownLoadServerFiiPvi(arg0, arg1, arg2, i);
            if (r != 0) {
                arg2 = r;
                (*arg3)++;
            }
        }
    }
    return 1;
}

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

#define n ((s16)arg1)
void *format_number_text__22TQuestVmDownLoadServerFiiPvi(s32 arg0, s32 arg1, void *arg2, s32 mode) {
    u8 *s = (u8 *)arg0;
    Out_803EEB10 *o = (Out_803EEB10 *)arg2;
    Tbl_803EEB10 *t = &quest_download_number_text_table;
    s32 u;
    u8 **mp;
    u8 **up;
    u8 *p;
    u8 *mark;
    s32 i;
    s32 pos;
    s32 d;
    s32 rem;
    s32 set;

    if (mode >= 2 && n > 0xD) {
        return NULL;
    }
    o->mode = mode;
    o->x2 = 0;
    o->x4 = 0;
    p = o->text;
    mp = (u8 **)((u8 *)t->sets + mode * 4);
    mark = p;
    up = &t->units_text;
    for (i = 0; i < n; i++, s++) {
        d = *s - '0';
        if (mode < 2) {
            *p++ = (*mp)[d * 2];
            *p++ = (*mp)[d * 2 + 1];
            continue;
        }
        rem = n - i - 1;
        pos = rem % 4;
        if (d != 0 && !(mode == 2 && d == 1 && (u32)(pos - 1) <= 1)) {
            set = IsSmall_803EEB10(d) ? mode - 1 : 1;
            *p++ = (*(u8 **)((u8 *)t->sets + set * 4))[d * 2];
            *p++ = (*(u8 **)((u8 *)t->sets + set * 4))[d * 2 + 1];
        }
        if (rem == 0) {
            continue;
        }
        if (pos == 0 && mark == p) {
            continue;
        }
        if (pos != 0 && d == 0) {
            continue;
        }
        if (pos == 0) {
            u = rem / 4 + 6;
        } else if (pos == 1) {
            if (mode == 2) {
                u = 4;
            } else {
                u = 0;
            }
        } else {
            u = pos + 3;
        }
        *p++ = (*up)[u * 2];
        *p++ = (*up)[u * 2 + 1];
        if (pos == 0) {
            mark = p;
        }
    }
    if (p == o->text) {
        return NULL;
    }
    *p = 0;
    return p + 1;
}
#undef n
#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(4)
#pragma opt_common_subs off
inline u32 Call_803EED0C(s32 a, s32 b, s32 c, s32 d) {
    return ((u32)format_number_text__22TQuestVmDownLoadServerFiiPvi((s32)a, (s32)b, (void *)c, (s32)d));
}
s32 TQuestVmDownLoadServer__sub_803EED0C(s32 arg0, s32 arg1, s32 arg2) {
    if (lbl_805D7904 == -1) {
        return -3;
    }
    if (Call_803EED0C(arg0, arg1, arg2, lbl_805D78FC) == 0) {
        Call_803EED0C(arg0, arg1, arg2, 0);
    }
    return 1;
}
#pragma pop

s32 TQuestVmDownLoadServer::get_download_state() {
    return lbl_805D7900;
}

s32 TQuestVmDownLoadServer__sub_803EED9C(u32 arg0) {
    TQuestVmDownLoadServer::release_ref_slot(arg0);
    return 3;
}

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
s32 TQuestVmDownLoadServer__sub_803EEDC0(Req_803EEF2C *req, s32 *ids, s32 n) {
    char buf[0x50];
    s32 v;
    if (lbl_805D7900 == 0) {
        return 3;
    }
    if (lbl_805D7904 == -1) {
        return -3;
    }
    strncpy(buf, req->name, req->len);
    buf[req->len] = 0;
    if (is_digit_string((u8 *)buf)) {
        req->x7 = 0x1F;
    }
    v = ((TQuestVmDownLoadServer *)ids)->get_max_size_of_indices(n) + 1;
    if (v == 0xFF) {
        release_index_entries(ids, n);
        v = 1;
    }
    TQuestVmDownLoadServer__sub_803E8DA0(buf, req, v);
    TQuestVmDownLoadServer::set_slot_values_for_indices(ids, n, v);
    return 3;
}
#pragma pop

s32 TQuestVmDownLoadServer__sub_803EEF2C(Req_803EEF2C *arg0) {
    char buf[0x50];
    if (lbl_805D7900 == 0) {
        return 3;
    }
    if (lbl_805D7904 == -1) {
        return -3;
    }
    strncpy(buf, arg0->name, arg0->len);
    if (arg0->x7 == 0x28 || arg0->x7 == 0x29) {
        arg0->x7 = 0x27;
    }
    buf[arg0->len] = 0;
    TQuestVmDownLoadServer__sub_803E8DA0(buf, arg0, 1);
    return 3;
}

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

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
s32 TQuestVmDownLoadServer__sub_803EEFC8(u8 *rec, Req_803EEF2C *msg) {
    s32 len;
    s32 size;
    u8 *data;
    u8 *end;
    u8 *start;
    u8 *text;
    s32 d;
    s32 n;
    u8 buf[0x80];
    TQuestVmDownLoadServer::copy_sjis_string(msg->text, buf);
    len = TQuestVmDownLoadServer::calc_sjis_string_width(msg->text);
    buf[len] = 0;
    data = rec;
    size = (u16)(rec[0] + (rec[1] << 8));
    end = rec + size;
    rec = rec + 3 + rec[2];
    while ((start = rec) < end) {
        rec += 2;
        if (*rec <= 0xB) {
            rec++;
        }
        text = rec;
        rec = skip_entry_text(rec, end);
        n = rec - text;
        if (start[0] == msg->x7 && n == len && strncmp((char *)text, (char *)buf, n) == 0) {
            break;
        }
    }
    d = rec - start;
    if (d > 0) {
        if (start == data + 3 + data[2] && rec == end) {
            return -1;
        }
        shift_bytes(rec, end, -d);
        data[0] = (size - d) % 256;
        data[1] = (size - d) / 256;
    }
    return d;
}
#pragma pop

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

#undef QUEST_DOWNLOAD_SHIFT_ADDRESS

// Partial-message removal already shortened its record. Keep this operation's
// inline boundary separate from whole-record removal; see the unit evidence.
inline void shift_compacted_record_tail(u8 *p, u8 *end, s32 delta) {
    shift_tail_bytes(p, end, delta);
}
// Remove one matching message from a primary cached page. Caller-supplied
// names/text and page records retain the native bounded-input preconditions.
s32 TQuestVmDownLoadServer__sub_803EF208(Req_803EEF2C *request) {
    s32 delta;
    char name[0x50];
    u8 *end;
    u8 *record;
    u8 len;
    s32 comparison;
    s32 size;
    s32 removed;
    s32 missing = 1;
    if (lbl_805D7904 == -1) {
        return -3;
    }
    if (lbl_805D78F8 == 0x8000) {
        return -6;
    }
    strncpy(name, request->name, request->len);
    name[request->len] = 0;
    record = get_cached_page__22TQuestVmDownLoadServerFi(
        find_name_index__22TQuestVmDownLoadServerFv(name));
    for (end = record; (size = (u16)(end[0] + (end[1] << 8))) != 0; end += size) {
    }
    for (; record < end;
         record += (u16)(record[0] + (record[1] << 8))) {
        len = record[2];
        comparison = strncmp((const char *)(record + 3), name, (s16)len);
        if (comparison == 0) {
            if ((s16)len == request->len) {
                missing = 0;
                break;
            }
        } else if (comparison > 0) {
            break;
        }
    }
    if (missing) {
        return 0;
    }
    removed = TQuestVmDownLoadServer__sub_803EEFC8(record, request);
    if (removed == 0) {
        return 0;
    }
    if (removed == -1) {
        size = (u16)(record[0] + (record[1] << 8));
        delta = -size;
        shift_removed_record_tail(record + size, end + 2, delta);
    } else {
        size = (u16)(record[0] + (record[1] << 8));
        shift_compacted_record_tail(record + size + removed, end + 2, -removed);
    }
    TQuestVmDownLoadServer__sub_803E79AC();
    TQuestVmDownLoadServer::set_active();
    return 3;
}

s32 TQuestVmDownLoadServer__sub_803EF538(Msg_803E9190 *msg) {
    u8 *end;
    u8 *page;
    u8 *p;
    s32 is_new = 1;
    u8 n;
    s32 c;
    s32 len;
    s32 size;
    char buf[0x50];
    if (lbl_805D7904 == -1) {
        return -3;
    }
    if (lbl_805D78F8 == 0x8000) {
        return -6;
    }
    strncpy(buf, msg->name, msg->len);
    buf[msg->len] = 0;
    page = get_cached_page__22TQuestVmDownLoadServerFi(find_name_index__22TQuestVmDownLoadServerFv(buf));
    for (end = page; (size = (u16)(end[0] + (end[1] << 8))) != 0; end += size) {
    }
    for (p = page; p < end; p += (u16)(p[0] + (p[1] << 8))) {
        n = p[2];
        c = strncmp((const char *)(p + 3), buf, (s16)n);
        if (c == 0) {
            if ((s16)n == msg->len) {
                is_new = 0;
                break;
            }
        } else if (c > 0) {
            break;
        }
    }
    len = is_new ? ((TQuestVmDownLoadServer *)msg)->calc_message_length() : ((TQuestVmDownLoadServer *)msg)->calc_text_length();
    if (end > page + 0x3FE - len) {
        return -5;
    }
    if (is_new) {
        shift_tail_bytes(p, end + 2, len);
        build_message_packet__22TQuestVmDownLoadServerFPviPvUc(p, len, msg, 0);
        if (msg->len <= 2) {
            TQuestVmDownLoadServer__sub_803E7F9C((u8 *)buf, msg->len);
        }
    } else {
        shift_tail_bytes(p + (u16)(p[0] + (p[1] << 8)), end + 2, len);
        append_message_text__22TQuestVmDownLoadServerFPviPvUc(p, len, msg, max_entry_index(p) + 1);
    }
    TQuestVmDownLoadServer__sub_803E79AC();
    TQuestVmDownLoadServer::set_active();
    return 3;
}
#pragma pop

void TQuestVmDownLoadServer__sub_803EF8E0(u8 *p) {
    u8 *end = p + (u16)(p[0] + (p[1] << 8));
    p = p + 3 + p[2];
    while (p < end) {
        p[1] = 0;
        p += 2;
        if (*p <= 0xB) {
            p++;
        }
        for (; p < end; p += 2) {
            if (*p <= 0x38) {
                break;
            }
        }
    }
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
s32 TQuestVmDownLoadServer__sub_803EF958(u32 id, u16 key, s32 *ids, s32 n) {
    s32 page;
    u8 *base;
    u8 *p;
    u16 off;
    if (lbl_805D7900 == 0) {
        return 3;
    }
    if (lbl_805D7904 == -1) {
        return -3;
    }
    if (id == 0xFFFFFFFF && key <= 3) {
        lbl_805D78FC = key;
        release_index_entries(ids, n);
        TQuestVmDownLoadServer::set_slot_values_for_indices(ids, n, 0);
        return 3;
    }
    {
        s32 a;
        s32 b;
        s32 v;
        page = TQuestVmDownLoadServer__sub_803E779C(id, &a, &b, &v);
        if (page == -1) {
            return 0;
        }
        off = key;
        if (key & 0x8000) {
            if (b == -1) {
                return 0;
            }
            base = TQuestVmDownLoadServer::get_buffer_ptr(b);
        } else {
            if (a == -1) {
                return 0;
            }
            base = get_cached_page__22TQuestVmDownLoadServerFi(page) + a;
        }
        v = ((TQuestVmDownLoadServer *)ids)->get_max_size_of_indices(n);
        p = base + (off & ~0x8000) + 1;
        if (*p != 0 && *p == v) {
            if (key & 0x8000) {
                TQuestVmDownLoadServer__sub_803E8924(b);
                TQuestVmDownLoadServer__sub_803E8918();
            }
            return 3;
        }
        if (++v == 0xFF) {
            release_index_entries(ids, n);
            v = 1;
        }
        *p = v;
        if (key & 0x8000) {
            TQuestVmDownLoadServer__sub_803E8924(b);
            TQuestVmDownLoadServer__sub_803E8918();
        } else {
            TQuestVmDownLoadServer::set_active();
        }
        TQuestVmDownLoadServer::set_slot_values_for_indices(ids, n, v);
        return 3;
    }
}

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
// docs/evidence/quest-download-pr295-sol61.md for the remaining header coloring.
s32 TQuestVmDownLoadServer__sub_803F03B4(u8 *data, Ent_803F03B4 *ents, s32 n, s32 *max) {
    Ent_803F03B4 *base = ents;
    u8 *end = data + (u16)(data[0] + (data[1] << 8));
    u8 *cursor = data + data[2] + 3;
    ents += n;
    while (cursor < end) {
        u8 keyb;
        ents->a = cursor[0];
        keyb = cursor[1];
        cursor += 2;
        ents->key = keyb;
        if ((u16)keyb > *max) {
            *max = ents->key;
        }
        if (*cursor <= 11) {
            ents->b = *cursor;
            cursor += 1;
        } else {
            ents->b = 0;
        }
        ents->c = 0;
        if (merge_duplicate_download_entry(base, ents) == 0) {
            n += 1;
            ents += 1;
            if (n >= 32) {
                break;
            }
        }
        cursor = skip_entry_text(cursor, end);
    }
    return n;
}
#pragma pop

u8 *TQuestVmDownLoadServer::find_insert_position(s32 key, s32 n, s32 len) {
    u8 *p = (u8 *)this;
    u8 *end = p + len;
    u8 *s;
    u8 *d;
    while (p < end) {
        if (*(u16 *)(p + 2) < key) {
            break;
        }
        p += 5;
        while (*p++ != 0) {
        }
        if ((u32)p & 1) {
            p++;
        }
    }
    if (p < end) {
        for (s = end - 1; s >= p; s--) {
            s[n] = *s;
        }
    }
    return p;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
void TQuestVmDownLoadServer__sub_803EFCB4(u8 *data, s32 key, s32 sub_key, s32 *cnt, s32 *total, u8 *buf, s32 flags) {
    u8 *p;
    u8 *end;
    u8 *rec;
    s32 size;
    u8 *text;
    Src_803EBD38 *out;
    s32 sub;
    s32 value;
    u8 unused[8];
    end = data + (u16)(data[0] + (data[1] << 8));
    p = data + 3 + data[2];
    while (p < end) {
        rec = p;
        value = p[1];
        p += 2;
        if (*p <= 0xB) {
            sub = *p;
            p++;
        } else {
            sub = 0;
        }
        if (key == rec[0] && sub_key == sub) {
            size = TQuestVmDownLoadServer::count_entries_until_terminator(p, end) + 6;
            if (size & 1) {
                size++;
            }
            out = (Src_803EBD38 *)((TQuestVmDownLoadServer *)buf)->find_insert_position(value, size, *total);
            out->x0 = flags | (rec - data);
            text = rec + 2;
            out->x2 = rec[1];
            out->x4 = 0;
            if (rec[2] <= 0xB) {
                text++;
            }
            TQuestVmDownLoadServer::unescape_copy_string(out->text, text, end);
            *total += size;
            (*cnt)++;
        }
        p = skip_entry_text(p, end);
    }
}
#pragma pop

s32 TQuestVmDownLoadServer::read_quest_chunk(u32 id, u8 a1, u8 a2, u8 *buf, s32 *out) {
    s32 a;
    s32 b;
    s32 cnt;
    s32 total;
    s32 r;
    s32 v;
    if (lbl_805D7904 == -1) {
        return -3;
    }
    r = TQuestVmDownLoadServer__sub_803E779C(id, &a, &b, &cnt);
    if (r == -1) {
        return 0;
    }
    cnt = 0;
    total = 0;
    if (a != -1) {
        TQuestVmDownLoadServer__sub_803EFCB4(get_cached_page__22TQuestVmDownLoadServerFi(r) + a, a1, a2, &cnt, &total, buf, 0);
    }
    if (b != -1) {
        TQuestVmDownLoadServer__sub_803EFCB4(TQuestVmDownLoadServer::get_buffer_ptr(b), a1, a2, &cnt, &total, buf, 0x8000);
    }
    v = cnt;
    *out = v;
    if (v == 0) {
        return 0;
    }
    return 1;
}

void TQuestVmDownLoadServer__sub_803EFF20(u8 *data, s32 key, s32 sub_key, s32 *best, u8 *dst, s32 flags) {
    u8 *p;
    u8 *rec;
    u8 *end;
    u8 *found;
    u8 *text;
    Src_803EBD38 *out;
    u8 unused[8];
    s32 start_best;
    s32 sub;
    s32 value;
    start_best = *best;
    end = data + (u16)(data[0] + (data[1] << 8));
    p = data + 3 + data[2];
    while (p < end) {
        rec = p;
        value = p[1];
        p += 2;
        if (*p <= 0xB) {
            sub = *p;
            p++;
        } else {
            sub = 0;
        }
        if (key == rec[0] && sub_key == sub && value > *best) {
            found = rec;
            *best = value;
        }
        for (; p < end; p += 2) {
            if (*p <= 0x38) {
                break;
            }
        }
    }
    if (*best > start_best) {
        out = (Src_803EBD38 *)dst;
        out->x0 = flags | (found - data);
        text = found + 2;
        out->x2 = found[1];
        out->x4 = 0;
        if (found[2] <= 0xB) {
            text++;
        }
        TQuestVmDownLoadServer::unescape_copy_string(out->text, text, end);
    }
}

s32 TQuestVmDownLoadServer__sub_803F0048(s32 id, u8 a1, u8 a2, void *dst) {
    s32 a;
    s32 b;
    s32 c;
    s32 best;
    s32 page;
    if (lbl_805D7904 == -1) {
        return -3;
    }
    page = TQuestVmDownLoadServer__sub_803E779C(id, &a, &b, &c);
    if (page == -1) {
        return 0;
    }
    best = -1;
    if (a != -1) {
        TQuestVmDownLoadServer__sub_803EFF20(get_cached_page__22TQuestVmDownLoadServerFi(page) + a, a1, a2, &best, (u8 *)dst, 0);
    }
    if (b != -1) {
        TQuestVmDownLoadServer__sub_803EFF20(TQuestVmDownLoadServer::get_buffer_ptr(b), a1, a2, &best, (u8 *)dst, 0x8000);
    }
    if (best == -1) {
        return 0;
    }
    return 1;
}

s32 find_symbol_entry__22TQuestVmDownLoadServerFPvsPv(const char *name, s16 len, Info_803F0138 *out) {
    u8 n;
    u8 *base;
    u8 *p;
    s32 id;
    s32 c;
    if (len <= 2 && ((TQuestVmDownLoadServer *)name)->is_char_allowed(len) != 0) {
        out->off = -1;
        return 0;
    }
    id = find_name_index__22TQuestVmDownLoadServerFv((const char *)name);
    {
        u8 *get_cached_page__22TQuestVmDownLoadServerFi(void);
        base = get_cached_page__22TQuestVmDownLoadServerFi();
    }
    p = base;
    while ((u16)(p[0] + (p[1] << 8)) != 0) {
        n = p[2];
        c = strncmp((const char *)(p + 3), name, (s16)n);
        if (c == 0) {
            if ((s16)n == len) {
                break;
            }
        } else if (c > 0) {
            out->off = -1;
            return 0;
        }
        p += (u16)(p[0] + (p[1] << 8));
    }
    if ((u16)(p[0] + (p[1] << 8)) == 0) {
        out->off = -1;
        return 0;
    }
    out->id = id;
    out->off = p - base;
    out->p = p;
    return 1;
}

s32 TQuestVmDownLoadServer__sub_803F0268(const char *name, s16 len, Out_803F0268 *out) {
    char buf[0x50];
    Info_803F0138 i1;
    Out_803E8B1C i2;
    s32 max;
    s32 r1;
    s32 r2;
    u32 r;
    if (lbl_805D7904 == -1) {
        return -3;
    }
    strncpy(buf, name, len);
    buf[len] = 0;
    r1 = find_symbol_entry__22TQuestVmDownLoadServerFPvsPv(buf, len, &i1);
    r2 = lookup_name_entry__22TQuestVmDownLoadServerFPvsPv((char *)(buf), len, &i2);
    if (r1 == 0 && r2 == 0) {
        return 0;
    }
    out->len = len;
    out->len2 = len;
    out->xa = 1;
    out->count = 0;
    max = 0;
    if (r1 == 1) {
        out->count = TQuestVmDownLoadServer__sub_803F03B4(i1.p, out->entries, 0, &max);
    }
    if (r2 == 1) {
        out->count = TQuestVmDownLoadServer__sub_803F03B4(i2.ent, out->entries, out->count, &max);
    }
    out->x4 = r = TQuestVmDownLoadServer::acquire_slot_entry(i1.id, i1.off, i2.id, max);
    if (r == 0xFFFFFFFF) {
        return 0;
    }
    return 1;
}

s32 TQuestVmDownLoadServer__sub_803F0500(u8 *name, s16 len, Out_803E8C2C *out) {
    s16 blen;
    s16 cnt;
    s16 pre;
    s32 idx;
    s32 first;
    u8 *page;
    u8 *p;
    u8 *found;
    u8 n;
    first = 1;
    out->pre = 0;
    out->len = 0;
    idx = find_name_index__22TQuestVmDownLoadServerFv((const char *)name);
    if (((TQuestVmDownLoadServer *)idx)->has_name_mismatch(name) == 0) {
        return 2;
    }
    pre = 0;
    for (;;) {
        page = get_cached_page__22TQuestVmDownLoadServerFi(idx);
        p = page;
        cnt = TQuestVmDownLoadServer::count_matching_name_prefix(idx, name);
        blen = 0;
        for (; (u16)(p[0] + (p[1] << 8)) != 0; p += (u16)(p[0] + (p[1] << 8))) {
            s16 m;
            s32 r;
            u8 *e = p;
            n = e[2];
            m = TQuestVmDownLoadServer::match_prefix_length(e + 3, name, (s16)n);
            if (m >= pre) {
                pre = m + 1;
            }
            r = strncmp((const char *)(e + 3), (char *)name, (s16)n);
            if (r == 0) {
                if ((s16)n == len && first) {
                    return 2;
                }
                blen = n;
                found = p;
            } else if (r > 0) {
                if (strncmp((const char *)(e + 3), (char *)name, len) == 0 && first) {
                    return 2;
                }
                break;
            }
        }
        if (blen > 0) {
            break;
        }
        if (cnt <= 1) {
            out->id = -1;
            return 0;
        }
        len = cnt - 1;
        name[len] = 0;
        idx = find_name_index__22TQuestVmDownLoadServerFv((const char *)name);
        first = 0;
    }
    out->a = idx;
    out->id = found - page;
    out->len = blen;
    out->pre = pre;
    out->ent = found;
    return 1;
}

s32 TQuestVmDownLoadServer__sub_803F06B8(const char *name, s16 len, Out_803F0268 *out) {
    char buf[0x50];
    Out_803E8C2C o1;
    Out_803E8C2C o2;
    s32 max;
    s32 r1;
    s32 r2;
    s32 n;
    u32 r;
    if (lbl_805D7904 == -1) {
        return -3;
    }
    strncpy(buf, name, len);
    buf[len] = 0;
    r1 = TQuestVmDownLoadServer__sub_803F0500((u8 *)buf, len, &o1);
    if (r1 == 2) {
        return 2;
    }
    strncpy(buf, name, len);
    buf[len] = 0;
    r2 = TQuestVmDownLoadServer__sub_803E8C2C(buf, len, &o2);
    if (r2 == 2) {
        return 2;
    }
    if (r1 == 0 && r2 == 0) {
        return 0;
    }
    out->xa = 1;
    max = 0;
    out->len2 = o1.pre > o2.pre ? o1.pre : o2.pre;
    if (o1.len > o2.len) {
        out->len = o1.len;
        out->count = TQuestVmDownLoadServer__sub_803F03B4((u8 *)o1.ent, out->entries, 0, &max);
        o2.id = -1;
    } else if (o1.len < o2.len) {
        out->len = o2.len;
        out->count = TQuestVmDownLoadServer__sub_803F03B4((u8 *)o2.ent, out->entries, 0, &max);
        o1.id = -1;
    } else {
        out->len = o1.len;
        n = TQuestVmDownLoadServer__sub_803F03B4((u8 *)o1.ent, out->entries, 0, &max);
        out->count = TQuestVmDownLoadServer__sub_803F03B4((u8 *)o2.ent, out->entries, n, &max);
    }
    out->x4 = r = TQuestVmDownLoadServer::acquire_slot_entry(o1.a, o1.id, o2.id, max);
    if (r == 0xFFFFFFFF) {
        return 0;
    }
    return 1;
}

s32 TQuestVmDownLoadServer__sub_803F0890(void) {
    if ((s32) lbl_805D7904 == -1) {
        return -3;
    }
    TQuestVmDownLoadServer__sub_803E8150();
    TQuestVmDownLoadServer__sub_803E9764();
    TQuestVmDownLoadServer::retry_seek_active_entries();
    if (TQuestVmDownLoadServer__sub_803E86C8() == -1) {
        return -2;
    }
    return 3;
}

s32 TQuestVmDownLoadServer__sub_803F08E4(s8 *quest_vm_down_load_server) {
    s32 r;

    if (lbl_805D7904 != -1) {
        return -4;
    }
    if (*quest_vm_down_load_server == 0) {
        return -1;
    }
    ((TQuestVmDownLoadServer *)quest_vm_down_load_server)->set_file_info_name();
    r = TQuestVmDownLoadServer::find_file_info_index();
    if (r != 0) {
        if (r == -1) {
            return -7;
        }
        return -8;
    }
    if (TQuestVmDownLoadServer::read_ask_header() == -1) {
        TQuestVmDownLoadServer__sub_803E86C8();
        return -2;
    }
    if (TQuestVmDownLoadServer__sub_803E8084() == -1) {
        TQuestVmDownLoadServer__sub_803E86C8();
        return -2;
    }
    TQuestVmDownLoadServer::init_page_cache();
    __VIRetraceHandler();
    if (lbl_805D78F8 == 0x8000) {
        return -6;
    }
    return 3;
}

s32 TQuestVmDownLoadServer__sub_803F09A4(void) {
    s32 var_r3;
    lbl_805D7834 = 0;
    quest_download_initialized = 1;
    lbl_805D7908 = 0;
    lbl_805D790C = 0;
    var_r3 = dispatch_request_0x20__19TWindowKeyBoardSoftFll(&lbl_805E10D8, &lbl_805E10E0);
    if (var_r3 == 0) {
        var_r3 = dispatch_request_0x1c__19TWindowKeyBoardSoftFv();
    }
    if (var_r3 > 0) {
        var_r3 = -1;
    }
    return var_r3;
}

s32 TQuestVmDownLoadServer__sub_803F09FC(void *arg0, int arg1, int arg2) {
    s32 r;
    switch (arg2) {
    case 0:
        if (arg1 < 0) {
            return -1;
        }
        lbl_805D7914.remain = lbl_805D7910 - arg1;
        lbl_805D7914.pos = arg1;
        break;
    case 1:
        r = lbl_805D7914.remain - arg1;
        if (r < 0 || (u32)r > lbl_805D7910) {
            return -1;
        }
        lbl_805D7914.remain = r;
        lbl_805D7914.pos += arg1;
        break;
    case 2:
        if (arg1 > 0) {
            return -1;
        }
        lbl_805D7914.remain = -arg1;
        arg1 = lbl_805D7910 + arg1;
        lbl_805D7914.pos = arg1 - 1;
        break;
    }
    return lbl_805D7914.pos;
}

u32 TQuestVmDownLoadServer::aram_dma_read(void *h, void *dst, int size) {
    u32 n;
    u32 len;
    u32 start;
    u8 *base;
    base = quest_download_aram_dma_buffer;
    n = lbl_805D7914.remain;
    if ((u32)lbl_805D7914.remain >= (u32)size) {
        n = size;
    }
    len = n;
    if (n & 3) {
        len = (n | 3) + 1;
    }
    DCInvalidateRange(base + 0x40, 0x2000);
    (*(u32 *)&quest_download_aram_dma_pending) = 1;
    ARQPostRequest(base + 0x2040, lbl_805D7924, 1, lbl_805D7920, lbl_805D792C + lbl_805D7914.pos,
                   (u32)(base + 0x40), len, TQuestVmDownLoadServer__sub_803F0BE8);
    start = OSGetTick();
    for (;;) {
        if ((*(u32 *)&quest_download_aram_dma_pending) == 0) {
            memcpy(dst, base + 0x40, n);
            break;
        }
        if (OSGetTick() - start > lbl_805D791C) {
            (*(u32 *)&quest_download_aram_dma_pending) = 0;
            ARQRemoveRequest(base + 0x2040);
            OSReport(aram_dma_timeout_message);
            return -1;
        }
    }
    lbl_805D7914.remain -= n;
    lbl_805D7914.pos += n;
    return n;
}

s32 TQuestVmDownLoadServer__sub_803F0BD8(void * _w0) {
    return 0;
}

s32 TQuestVmDownLoadServer__sub_803F0BE0(void * _w0, void * _w1) {
    return 1;
}

void TQuestVmDownLoadServer__sub_803F0BE8(u8 *arg0) {
    if ((u32) *(u32 *)((s8 *)arg0 + 4) == (u32) lbl_805D7924) {
        quest_download_aram_dma_pending = 0;
    }
}

void TQuestVmDownLoadServer__sub_803F0C04(u32 aram_addr, s32 size, u32 owner, u32 priority, u32 timeout_ms) {
    lbl_805D792C = aram_addr;
    lbl_805D7914.remain = size;
    lbl_805D7914.pos = 0;
    lbl_805D7924 = owner;
    lbl_805D7910 = lbl_805D7914.remain;
    lbl_805D7920 = priority;
    lbl_805D791C = timeout_ms * (__OSBusClock / 4 / 1000);
}

__declspec(section ".rodata") const char ask_header_signature[] = "ASK Copyright (C) ACCESS CO.,LTD.";
}

u16 lbl_805A02A8[0x4C];
u16 lbl_805A0340[0x98];
RecoveredGlobal_803E6ACC_lbl_805A0470 lbl_805A0470;
QuestDownloadInputEntry quest_download_entry_table[39];
RecoveredGlobal_803E6ACC_lbl_805A05D0 lbl_805A05D0;
QuestDownloadRequestStorage lbl_805A0698;
u8 quest_download_aram_dma_buffer[0x2060];

#undef QUEST_DOWNLOAD_ENTRY_LIST_FAILED
#undef QUEST_DOWNLOAD_ITEM_LIST_UNAVAILABLE
#undef QUEST_DOWNLOAD_LIST_SENTINEL_WORD
