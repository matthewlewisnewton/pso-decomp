#ifndef PSO_RENDER_COLOR_LINE_LIST_H
#define PSO_RENDER_COLOR_LINE_LIST_H

#include "types.h"

struct ColorLineVertex {
    f32 x, y;
};

struct ColorLineList {
    ColorLineVertex *verts;
    u32 *colors;
    s32 unk_8;
    s32 count;

    // 0x801E35C4 consumes this vertex/color descriptor, not a creation-menu object.
    void draw_tri_fan_2d(s32 n, s32 flags, f32 scale);
    void draw_strip_swap_color(s32 n, s32 flags, f32 scale);
};

#endif
