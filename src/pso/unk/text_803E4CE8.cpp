#include "pso/system/ChunkVertexJob.h"
#include "dolphin/mtx.h"
#include "pso/unk/text_803D853C.h"

struct ColoredChunkVertex {
    Vec position;
    u32 color;
};

struct CachedChunkVertex {
    Vec position;
    Vec normal;
    u32 color;
    u32 padding;
};

typedef char ColoredChunkVertex_size[sizeof(ColoredChunkVertex) == 0x10 ? 1 : -1];
typedef char CachedChunkVertex_size[sizeof(CachedChunkVertex) == 0x20 ? 1 : -1];

extern "C" void cache_chunk_vertex_colors(ChunkVertexJob *job, s32) {
    s32 count = job->count;
    const ColoredChunkVertex *src = (const ColoredChunkVertex *)job->src;
    CachedChunkVertex *dst = (CachedChunkVertex *)job->dst;
    f32 normalY;
    f32 normalXZ;
    normalXZ = 0.0f;
    normalY = 1.0f;
    while (count-- > 0) {
        matrix_mult_vec(NULL, &src->position, &dst->position);
        dst->color = src->color;
        src++;
        dst->normal.x = normalXZ;
        dst->normal.y = normalY;
        dst->normal.z = normalXZ;
        dst++;
    }
}
