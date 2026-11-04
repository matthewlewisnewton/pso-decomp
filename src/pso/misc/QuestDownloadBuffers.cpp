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
extern "C" {
u8 lbl_80595008[0x990];
QuestDownloadSlot quest_download_slot_chain_table[80];
u8 lbl_80596258[0xC];
u8 quest_download_text_buffer[0x404];
}

typedef char QuestDownloadBuffers_tail[
    sizeof(lbl_80595008) == 0x990
        && sizeof(quest_download_slot_chain_table) == 0x8C0
        && sizeof(lbl_80596258) == 0xC
        && sizeof(quest_download_text_buffer) == 0x404
        ? 1
        : -1];
