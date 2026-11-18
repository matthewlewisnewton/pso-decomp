#ifndef PSO_SYSTEM_STRIPBUFFERPAIR_H
#define PSO_SYSTEM_STRIPBUFFERPAIR_H

#include "types.h"

struct StripReference {
    s16 *strip;
    s16 *uv;
};

// The strips of a model node whose texture passes the filter, collected into
// a strip array and a UV array (scroll_strip_uvs animates the UVs,
// destroy_buffer_pair frees both).
struct StripBufferPair {
    s32 uv_count;  // Vertex count; each saved UV occupies two s16 values.
    s32 strip_count;  // Number of collected polygon-list chunks.
    StripReference *strips;
    s16 *uvs;
    u8 unk_10[0x4];
    StripBufferPair(s32 model, s32 filter);
};

typedef char StripBufferPair_size[sizeof(StripBufferPair) == 0x14 ? 1 : -1];

extern "C" void scroll_strip_uvs(StripBufferPair *buffers, s16 du, s16 dv);

#endif
