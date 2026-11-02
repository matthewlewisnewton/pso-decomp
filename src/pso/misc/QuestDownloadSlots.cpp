#include "pso/misc/QuestDownloadRecords.h"

// Inactive data-only continuation; see quest-download-deferred-storage.md.
// These are actual static slot objects. Their pointed-to nodes have separate
// storage and lifetimes; this definition does not supply a node pool.
extern "C" {
QuestDownloadSlot quest_download_slot_chain_table[80];
}

typedef char QuestDownloadSlots_extent[
    sizeof(quest_download_slot_chain_table) == 0x8C0 ? 1 : -1];
