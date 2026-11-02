#include "types.h"

// Encoded display-prefix bytes, initialized by 5B94 and updated by B4D4.
// The following scratch object is separate storage, not this array's tail.
// Inactive continuation: see quest-download-display-prefix.md.
extern "C" {
u8 lbl_80596258[12];
}

typedef char QuestDownloadDisplayPrefix_extent[
    sizeof(lbl_80596258) == 12 ? 1 : -1];
