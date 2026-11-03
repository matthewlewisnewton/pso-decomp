#ifndef PSO_MISC_TWINDOWDRAWCONTEXT_H
#define PSO_MISC_TWINDOWDRAWCONTEXT_H

#include "types.h"
#include <stddef.h>

// Prefix of the text-window object opened for a menu frame.
// draw_frame reads x/y/w/inner_h/color; label quads also read depth and the clip origin.
struct TWindowDrawContext {
    f32 x;
    f32 y;
    f32 w;
    f32 h;
    f32 inner_x;
    f32 inner_y;
    f32 inner_w;
    f32 inner_h;
    f32 pivot[2];
    f32 scale[2];
    s32 open_tick;
    u32 color;
    f32 depth;
    f32 clip_left;
    f32 clip_top;
};

typedef char TWindowDrawContext_size[sizeof(TWindowDrawContext) == 0x44 ? 1 : -1];
typedef char TWindowDrawContext_inner_h[offsetof(TWindowDrawContext, inner_h) == 0x1C ? 1 : -1];
typedef char TWindowDrawContext_color[offsetof(TWindowDrawContext, color) == 0x34 ? 1 : -1];
typedef char TWindowDrawContext_depth[offsetof(TWindowDrawContext, depth) == 0x38 ? 1 : -1];
typedef char TWindowDrawContext_clip_left[offsetof(TWindowDrawContext, clip_left) == 0x3C ? 1 : -1];
typedef char TWindowDrawContext_clip_top[offsetof(TWindowDrawContext, clip_top) == 0x40 ? 1 : -1];

extern "C" TWindowDrawContext *get_draw_context__11TWindowBaseFPv(void *window);

#endif
