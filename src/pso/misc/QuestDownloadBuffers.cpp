#include "types.h"
#include "pso/misc/QuestDownloadCacheTypes.h"

// Six real buffer objects recovered as a provisional data-only unit.
// Workspace, slot and shared text storage remain in the original fallback.
// See docs/evidence/quest-download-buffer-types.md for the recovery boundary.
char quest_vm_download_server_file_info[0x44];
QuestDownloadFileCache quest_download_slot_table;
u8 quest_name_index_table[1024][4];
u8 lbl_80591AC4[0x404];
u8 lbl_80591EC8[0x2000];
QuestDownloadCachedNameIndex lbl_80593EC8;
