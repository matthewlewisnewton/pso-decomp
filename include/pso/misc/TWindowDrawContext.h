#ifndef PSO_MISC_TWINDOWDRAWCONTEXT_H
#define PSO_MISC_TWINDOWDRAWCONTEXT_H

#include "types.h"
#include <stddef.h>

// Mutable singleton scratch state. Borrowed references last only while the
// singleton is alive and its contents are overwritten by each window setup.
struct TWindowDrawContext {
    f32 x, y, w, h;
    f32 inner_x, inner_y, inner_w, inner_h;
    f32 pivot[2], scale[2];
    s32 open_tick;
    u32 color;
    f32 depth;
    f32 clip_left, clip_top, clip_right, clip_bottom;
};
typedef char DrawContextSize[sizeof(TWindowDrawContext) == 0x4c ? 1 : -1];
struct DrawContextAlignmentProbe { char c; TWindowDrawContext d; };
typedef char DrawContextAlignment[offsetof(DrawContextAlignmentProbe, d) == 4 ? 1 : -1];
typedef char DrawContextX[offsetof(TWindowDrawContext, x) == 0x00 ? 1 : -1];
typedef char DrawContextY[offsetof(TWindowDrawContext, y) == 0x04 ? 1 : -1];
typedef char DrawContextW[offsetof(TWindowDrawContext, w) == 0x08 ? 1 : -1];
typedef char DrawContextH[offsetof(TWindowDrawContext, h) == 0x0c ? 1 : -1];
typedef char DrawContextInnerX[offsetof(TWindowDrawContext, inner_x) == 0x10 ? 1 : -1];
typedef char DrawContextInnerY[offsetof(TWindowDrawContext, inner_y) == 0x14 ? 1 : -1];
typedef char DrawContextInnerW[offsetof(TWindowDrawContext, inner_w) == 0x18 ? 1 : -1];
typedef char DrawContextInnerH[offsetof(TWindowDrawContext, inner_h) == 0x1c ? 1 : -1];
typedef char DrawContextPivot[offsetof(TWindowDrawContext, pivot) == 0x20 ? 1 : -1];
typedef char DrawContextScale[offsetof(TWindowDrawContext, scale) == 0x28 ? 1 : -1];
typedef char DrawContextTick[offsetof(TWindowDrawContext, open_tick) == 0x30 ? 1 : -1];
typedef char DrawContextColor[offsetof(TWindowDrawContext, color) == 0x34 ? 1 : -1];
typedef char DrawContextDepth[offsetof(TWindowDrawContext, depth) == 0x38 ? 1 : -1];
typedef char DrawContextClip[offsetof(TWindowDrawContext, clip_left) == 0x3c ? 1 : -1];
typedef char DrawContextClipTop[offsetof(TWindowDrawContext, clip_top) == 0x40 ? 1 : -1];
typedef char DrawContextClipRight[offsetof(TWindowDrawContext, clip_right) == 0x44 ? 1 : -1];
typedef char DrawContextClipBottom[offsetof(TWindowDrawContext, clip_bottom) == 0x48 ? 1 : -1];
extern "C" TWindowDrawContext *get_draw_context__11TWindowBaseFPv(void *window);
#endif
