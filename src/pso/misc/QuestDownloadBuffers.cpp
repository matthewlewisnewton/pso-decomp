#include "types.h"
#include "pso/misc/QuestDownloadCacheTypes.h"

// Draft definitions only: this file has no split or linked-unit entry. The two
// cache layouts below still need coherent consumer declarations and owner review.
// The other imported definitions retain unresolved types; especially the shared
// text storage must not be activated as a byte array with incompatible users.
// See docs/evidence/quest-download-buffer-types.md.
char quest_vm_download_server_file_info[0x44];
QuestDownloadFileCache quest_download_slot_table;
u8 quest_name_index_table[1024][4];
u8 lbl_80591AC4[0x404];
u8 lbl_80591EC8[0x2000];
QuestDownloadCachedNameIndex lbl_80593EC8;
u8 lbl_80595008[0x990];
u8 quest_download_slot_chain_table[0x8C0];
u8 lbl_80596258[0xC];
u8 quest_download_text_buffer[0x404];
