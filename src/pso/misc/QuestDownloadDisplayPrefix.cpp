#include "types.h"

// Encoded display-prefix bytes at 0x80596258. The scratch object that follows
// is separate storage, not this array's tail. C linkage keeps the existing
// unmangled symbol. See docs/evidence/quest-download-display-prefix.md.
extern "C" {
u8 lbl_80596258[12];
}

typedef char QuestDownloadDisplayPrefix_extent[
    sizeof(lbl_80596258) == 12 ? 1 : -1];
