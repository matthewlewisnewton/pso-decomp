#include "pso/misc/QuestDownloadRecords.h"

// The 80 slot records at 0x80595998. Nodes they point at have separate
// storage and lifetimes; this array does not supply a node pool.
// C linkage keeps the existing unmangled symbol. See
// docs/evidence/quest-download-deferred-storage.md.
extern "C" {
QuestDownloadSlot quest_download_slot_chain_table[80];
}

typedef char QuestDownloadSlots_extent[
    sizeof(quest_download_slot_chain_table) == 0x8C0 ? 1 : -1];
