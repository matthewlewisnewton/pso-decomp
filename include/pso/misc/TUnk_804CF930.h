#ifndef PSO_MISC_TUNK_804CF930_H
#define PSO_MISC_TUNK_804CF930_H
#include "types.h"
#include <stddef.h>
#include "pso/misc/TUnk_804CF918.h"
#include "pso/misc/TWindowDrawContext.h"

// Init record passed to init_from. The layout walker advances 0x24 bytes
// per gauge entry (kind, then the fields copied below).
struct TUnk_804CF930_init {
    s32 kind;
    f32 x;
    f32 y;
    f32 depth;
    u32 color;
    s32 flags;
    f32 scale;
    f32 maximum;
    f32 target;
};

class TUnk_804CF930 : public TUnk_804CF918 {
public:
    virtual ~TUnk_804CF930();
    virtual void update();
    virtual void render(TWindowDrawContext *context);
    virtual void calc_bar_width();

    // Base constructor, then this class's vtable at +4, then the init record.
    TUnk_804CF930(void *src, s16 arg2);

    f32 depth;
    f32 x;
    f32 y;
    f32 scale;
    u32 color;
    f32 width;
    f32 maximum;
    f32 target;

    // TWindowDrawContext* is the name draw_status_gauge_bar__13TUnk_804CF930FP18TWindowDrawContextPvff.
    void draw_status_gauge_bar(TWindowDrawContext *, void *, f32, f32);
};

typedef char TUnk_804CF930_size[sizeof(TUnk_804CF930) == 0x28 ? 1 : -1];
typedef char TUnk_804CF930_init_size[sizeof(TUnk_804CF930_init) == 0x24 ? 1 : -1];
typedef char TUnk_804CF930_depth_offset[offsetof(TUnk_804CF930, depth) == 0x8 ? 1 : -1];
typedef char TUnk_804CF930_x_offset[offsetof(TUnk_804CF930, x) == 0xC ? 1 : -1];
typedef char TUnk_804CF930_y_offset[offsetof(TUnk_804CF930, y) == 0x10 ? 1 : -1];
typedef char TUnk_804CF930_scale_offset[offsetof(TUnk_804CF930, scale) == 0x14 ? 1 : -1];
typedef char TUnk_804CF930_color_offset[offsetof(TUnk_804CF930, color) == 0x18 ? 1 : -1];
typedef char TUnk_804CF930_width_offset[offsetof(TUnk_804CF930, width) == 0x1C ? 1 : -1];
typedef char TUnk_804CF930_maximum_offset[offsetof(TUnk_804CF930, maximum) == 0x20 ? 1 : -1];
typedef char TUnk_804CF930_target_offset[offsetof(TUnk_804CF930, target) == 0x24 ? 1 : -1];

#endif
