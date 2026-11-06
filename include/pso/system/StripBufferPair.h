#ifndef PSO_SYSTEM_STRIPBUFFERPAIR_H
#define PSO_SYSTEM_STRIPBUFFERPAIR_H

#include "types.h"

// The strips of a model node whose texture passes the filter, collected into
// a strip array and a UV array (scroll_strip_uvs animates the UVs,
// destroy_buffer_pair frees both).
struct StripBufferPair {
    s32 uv_count;
    s32 strip_count;
    void *strips;
    void *uvs;
    u8 unk_10[0x4];
    StripBufferPair(s32 model, s32 filter);
};

typedef char StripBufferPair_size[sizeof(StripBufferPair) == 0x14 ? 1 : -1];

#endif
