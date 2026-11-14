#ifndef PSO_MISC_WINDOWVERTEXBUFFERABI_H
#define PSO_MISC_WINDOWVERTEXBUFFERABI_H

#include "types.h"

// Historical export for eight 24-byte records in raw destination storage.
// All observed callers supply -1 in the word argument and depth in f1.
// The callee overwrites that word before using it; its meaning is not recovered.
// This does not establish TWindowDD ownership or a complete native buffer type.
extern "C" void reset_entries__9TWindowDDFf(void *storage, s32 unused_word, f32 depth);

// Copy eight UV pairs into offsets 12/16 of the same 24-byte vertex records.
// The existing seven-bank table and the caller's word-valued index are retained.
extern "C" void copy_vertex_uv_table(void *storage, s32 index);

#endif
