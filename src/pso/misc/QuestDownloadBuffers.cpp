#include "types.h"
#include "pso/misc/QuestDownloadCacheTypes.h"
#include "pso/misc/QuestDownloadRecords.h"

// BSS from 0x8058DE08 through 0x80596668. The provider unit's first BSS
// object is quest_download_block_pool: init_block_free_list addresses it as
// ...bss.0. These objects are the bytes packed in front of that pool.
// See docs/evidence/quest-download-deferred-storage.md.
char quest_vm_download_server_file_info[0x44];
QuestDownloadFileCache quest_download_slot_table;
u8 quest_name_index_table[1024][4];
u8 lbl_80591AC4[0x404];
u8 lbl_80591EC8[0x2000];
QuestDownloadCachedNameIndex lbl_80593EC8;

// One query entry as written by TQuestVmDownLoadServer__sub_803F03B4:
// byte 0, byte 1, byte 2, an unread pad byte, then a halfword at +4.
// The writer strides 6 and stops when the index reaches 32.
struct QuestDownloadQueryEntry {
    u8 a;
    u8 b;
    u8 c;
    u8 pad;
    u16 key;
};

// The Out_803F0268 view with its real 32-entry capacity. 803EA428 reads
// len at +0, x4 at +4 and len2 at +8, then passes this object to
// build_item_list and to 803F06B8 / 803F0268.
struct QuestDownloadQueryResult {
    s16 len;
    u32 x4;
    s16 len2;
    s16 xa;
    s16 count;
    QuestDownloadQueryEntry entries[32];
};

// lbl_80595008 is one exported object. Its only relocations are in
// 803EA428 and 803EA9E8. Both add 0x8C0 before touching the query result,
// or add 0x990 before touching quest_download_slot_chain_table. Nothing
// loads or stores the leading 0x8C0 bytes through this symbol, and that
// span is not a second copy of the slot array.
struct QuestDownloadWorkspace {
    u8 leading[0x8C0];
    QuestDownloadQueryResult result;
};

// Twelve encoded characters. 803E5B94 copies lbl_8047E68C
// (20 20 8E 63 20 20 20 20 20 20 00 00) here. 803EB4D4 then stores ASCII
// digits at offsets 5, 6 and 7, and 803EC95C reads from offset 0 until NUL.
// 803EBEFC and 803EC460 only add 12, which is quest_download_text_buffer.
// symbols.txt still names the object lbl_80596258; the executable has no
// other name for it.
struct QuestDownloadDisplayPrefix {
    char text[12];
};

extern "C" {
QuestDownloadWorkspace lbl_80595008;
QuestDownloadSlot quest_download_slot_chain_table[80];
QuestDownloadDisplayPrefix lbl_80596258;
u8 quest_download_text_buffer[0x404];
}

typedef char QuestDownloadBuffers_tail[
    sizeof(QuestDownloadQueryEntry) == 6
        && offsetof(QuestDownloadQueryResult, len) == 0
        && offsetof(QuestDownloadQueryResult, x4) == 4
        && offsetof(QuestDownloadQueryResult, len2) == 8
        && offsetof(QuestDownloadQueryResult, xa) == 10
        && offsetof(QuestDownloadQueryResult, count) == 12
        && offsetof(QuestDownloadQueryResult, entries) == 14
        && sizeof(QuestDownloadQueryResult) == 0xD0
        && offsetof(QuestDownloadWorkspace, result) == 0x8C0
        && sizeof(lbl_80595008) == 0x990
        && sizeof(quest_download_slot_chain_table) == 0x8C0
        && sizeof(lbl_80596258) == 0xC
        && sizeof(quest_download_text_buffer) == 0x404
        ? 1
        : -1];
