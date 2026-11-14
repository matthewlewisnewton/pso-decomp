#ifndef PSO_MISC_TWINDOWDRAWCONTEXT_H
#define PSO_MISC_TWINDOWDRAWCONTEXT_H

#include "types.h"
#include <stddef.h>

// Prefix of the text window opened for a menu frame.
// draw_frame reads x/y/w/inner_h/color. The clip rect continues through
// clip_bottom, so the singleton allocated for a frame is 0x4C bytes.
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

    s32 is_point_in_bounds(f32 *quad);
    void scale_point_about_pivot(f32 *q);
    void set_open_tick(s32 arg1);
    void set_bounds(f32 a, f32 b, f32 c, f32 d);
    void shrink_clip_right();
    void animate_scale();
    static TWindowDrawContext *open_singleton(f32 *pos, f32 *size, f32 *scale, f32 depth, int flags);
    static u32 get_or_create_instance();
    static u32 free_singleton(u32 arg0, s16 arg1);
    u32 init_layout();
};

typedef char TWindowDrawContext_size[sizeof(TWindowDrawContext) == 0x4C ? 1 : -1];
typedef char TWindowDrawContext_inner_h[offsetof(TWindowDrawContext, inner_h) == 0x1C ? 1 : -1];
typedef char TWindowDrawContext_color[offsetof(TWindowDrawContext, color) == 0x34 ? 1 : -1];
typedef char TWindowDrawContext_depth[offsetof(TWindowDrawContext, depth) == 0x38 ? 1 : -1];
typedef char TWindowDrawContext_clip_left[offsetof(TWindowDrawContext, clip_left) == 0x3C ? 1 : -1];
typedef char TWindowDrawContext_clip_top[offsetof(TWindowDrawContext, clip_top) == 0x40 ? 1 : -1];
typedef char TWindowDrawContext_clip_right[offsetof(TWindowDrawContext, clip_right) == 0x44 ? 1 : -1];
typedef char TWindowDrawContext_clip_bottom[offsetof(TWindowDrawContext, clip_bottom) == 0x48 ? 1 : -1];

extern "C" TWindowDrawContext *get_draw_context__11TWindowBaseFPv(void *window);

#endif
