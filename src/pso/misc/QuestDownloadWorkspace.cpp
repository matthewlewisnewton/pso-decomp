#include "types.h"

// The existing lbl_80595008 allocation, 0x80595008..0x80595998. Original
// provider code keeps access and query interpretation. The first 0x8C0 bytes
// are uninterpreted storage, not padding and not the slot array that begins
// at the next object. C linkage keeps the existing unmangled symbol. See
// docs/evidence/quest-download-workspace.md.
extern "C" {
u8 lbl_80595008[0x990];
}

typedef char QuestDownloadWorkspace_extent[
    sizeof(lbl_80595008) == 0x990 ? 1 : -1];
