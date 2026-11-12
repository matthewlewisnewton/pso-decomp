#include "types.h"
#include "pso/misc/QuestDownloadScratch.h"
#include "pso/misc/QuestDownloadCacheTypes.h"
#include "pso/misc/QuestDownloadRecords.h"
#include "pso/misc/QuestDownloadQueryTypes.h"

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

// Twelve encoded characters. 803E5B94 copies lbl_8047E68C
// (20 20 8E 63 20 20 20 20 20 20 00 00) here. 803EB4D4 then stores ASCII
// digits at offsets 5, 6 and 7, and 803EC95C reads from offset 0 until NUL.
// 803EBEFC and 803EC460 only add 12, which is quest_download_text_buffer.
// symbols.txt still names the object lbl_80596258; the executable has no
// other name for it.

extern "C" {
QuestDownloadWorkspace lbl_80595008;
QuestDownloadSlot quest_download_slot_chain_table[80];
QuestDownloadDisplayPrefix lbl_80596258;
u8 quest_download_text_buffer[0x404] ATTRIBUTE_ALIGN(4);
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
