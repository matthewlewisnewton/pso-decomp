#ifndef PSO_UI_WINDOW_TWINDOWDRAWCONTEXT_H
#define PSO_UI_WINDOW_TWINDOWDRAWCONTEXT_H

#include "types.h"
#include <stddef.h>

// Prefix of the text window opened for a menu frame; the clip rect ends at
// clip_bottom.
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
    f32 clip_right;
    f32 clip_bottom;

    s32 is_point_in_bounds(f32 *point);
};

typedef char TWindowDrawContext_size[sizeof(TWindowDrawContext) == 0x4C ? 1 : -1];
typedef char TWindowDrawContext_color[offsetof(TWindowDrawContext, color) == 0x34 ? 1 : -1];
typedef char TWindowDrawContext_clip_left[offsetof(TWindowDrawContext, clip_left) == 0x3C ? 1 : -1];
typedef char TWindowDrawContext_clip_bottom[offsetof(TWindowDrawContext, clip_bottom) == 0x48 ? 1 : -1];

#endif
