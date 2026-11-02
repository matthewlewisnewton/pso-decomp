#include "types.h"

// Proposed byte-storage definition of the existing exported allocation only.
// Original provider code retains all access and query interpretation. The
// first 0x8C0 bytes are uninterpreted, not padding or a claimed slot array.
extern "C" {
u8 lbl_80595008[0x990];
}

typedef char QuestDownloadWorkspace_extent[
    sizeof(lbl_80595008) == 0x990 ? 1 : -1];
