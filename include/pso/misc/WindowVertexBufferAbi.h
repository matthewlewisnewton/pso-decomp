#ifndef PSO_MISC_WINDOWVERTEXBUFFERABI_H
#define PSO_MISC_WINDOWVERTEXBUFFERABI_H

#include "types.h"

// Historical export for eight 24-byte records in raw destination storage.
// All observed callers supply -1 in the word argument and depth in f1.
// The callee overwrites that word before using it; its meaning is not recovered.
// This does not establish TWindowDD ownership or a complete native buffer type.
extern "C" void reset_entries__9TWindowDDFf(void *storage, s32 unused_word, f32 depth);

#endif
