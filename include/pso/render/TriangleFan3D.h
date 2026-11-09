#ifndef PSO_RENDER_TRIANGLEFAN3D_H
#define PSO_RENDER_TRIANGLEFAN3D_H

#include "types.h"
#include <dolphin/mtx.h>
#include <stddef.h>

struct TriangleFan3DUV { s16 u, v; };
struct TriangleFan3D {
    Vec *positions;
    u32 *colors;
    TriangleFan3DUV *uvs;
    s32 count;
};

typedef char TriangleFan3D_size[sizeof(TriangleFan3D) == 0x10 ? 1 : -1];
typedef char TriangleFan3D_colors_offset[offsetof(TriangleFan3D, colors) == 0x4 ? 1 : -1];
typedef char TriangleFan3D_uvs_offset[offsetof(TriangleFan3D, uvs) == 0x8 ? 1 : -1];

void draw_tri_fan_3d(TriangleFan3D *fan, s32 count, u32 flags);

#endif
