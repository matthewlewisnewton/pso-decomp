#include "types.h"
#include "pso/system/memory.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TUnk_804CF930.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/misc/TWindowSubStatusDisp_803DEE6C.h"
#include "pso/misc/TTecRaFoie.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TWindowKeyBoardSoft.h"
#include "pso/object/TObjFish.h"
#include "pso/ui/TAdChrMoveEffectGC.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

extern GinjaTextureList *lbl_805D63F0;

struct Pos_80256E0C { f32 x; f32 y; };

struct Quad_80256E0C { f32 x0, y0, x1, y1, u0, v0, u1, v1; };

// Definitions run last-to-first under this unit's -inline off,deferred, so
// the emitted .text is address order and __vt__13TUnk_804CF918 precedes
// __vt__13TUnk_804CF930.
extern "C" {
void TWindowSubStatusDisp__sub_80256C40(TUnk_804CF930 *self, TWindowDrawContext *ctx, Pos_80256E0C *pos, f32 depth);
f32 fabs_float(f32);
const f32 lbl_805DCECC = 2.0f;

TUnk_804CF930::TUnk_804CF930(void *src_raw, s16 arg2) : TUnk_804CF918(arg2) {
    TUnk_804CF930_init *src = static_cast<TUnk_804CF930_init *>(src_raw);
    width = 0.0f;
    x = src->x;
    y = src->y;
    depth = src->depth;
    scale = src->scale;
    color = src->color;
    flags = (u16)src->flags;
    maximum = src->maximum;
    target = src->target;
}

TUnk_804CF930::~TUnk_804CF930() {}

void TUnk_804CF930::update() {
    f32 goal;
    f32 diff;
    flags &= ~4;
    if (maximum <= 0.0f || target <= 0.0f) {
        goal = 0.0f;
    } else {
        goal = (target * scale) / maximum;
    }
    diff = goal - width;
    if (fabs_float(diff) < lbl_805DCECC) {
        width = goal;
        flags |= 4;
    } else if (diff > 0.0f) {
        width += lbl_805DCECC;
    } else {
        width -= lbl_805DCECC;
    }
}

void TUnk_804CF930::render(TWindowDrawContext *ctx) {
    // depth before bar: the two values live across the draw calls, and this
    // order is what puts depth in f31 and the bar in f29.
    f32 depth_term;
    f32 len;
    Pos_80256E0C pos;
    f32 bar;
    f32 sum = y / 21.0f + x / ctx->inner_w;
    // Signed cast. Its bias is this unit's .rodata (lbl_8044EE40). Nothing
    // else loads that object, so it is scope:local. Naming the double emits
    // a second copy and the lis/lfd stops matching the compiler pool.
    f32 tick = (f32)ctx->open_tick;

    sum *= 7.5f;
    bar = (tick - sum) * 17.0f;
    if (bar <= 0.0f) {
        return;
    }
    if (width <= 0.0f && (flags & 8) == 0) {
        return;
    }
    if (width > bar) {
        len = bar;
    } else {
        len = width;
    }
    pos.x = ctx->inner_x + x;
    pos.y = ctx->inner_y + y;
    depth_term = -1.0f / (0.299f * depth + ctx->depth);
    begin_screen_draw(1);
    set_current_texture_list(lbl_805D63F0);
    set_draw_texture_and_color(0xB, -1);
    if ((flags & 8) != 0) {
        TWindowSubStatusDisp__sub_80256C40(this, ctx, &pos, depth_term);
    }
    if (bar > 0.0f) {
        set_constant_material_color(color);
        draw_status_gauge_bar(ctx, &pos, depth_term, len);
    }
    TWindowSubStatusDisp::get_player();
}

void TUnk_804CF930::draw_status_gauge_bar(TWindowDrawContext *ctx, void *pos_arg, f32 depth, f32 len) {
    Pos_80256E0C *pos = (Pos_80256E0C *)pos_arg;
    Quad_80256E0C q;
    f32 w;
    f32 end;
    if (len <= 0.0f) {
        return;
    }
    if (len < 4.0f) {
        w = len;
    } else {
        w = 4.0f;
    }
    q.x0 = pos->x;
    q.y0 = pos->y;
    q.x1 = pos->x + w;
    q.y1 = 7.0f + pos->y;
    q.u0 = 0.8984375f;
    q.v0 = 0.1171875f;
    q.u1 = (230.0f + w) / 256.0f;
    q.v1 = 0.14453125f;
    if (TWindowKeyBoardSoft::try_open(ctx, &q.x0) != 0) {
        draw_textured_quad_at_depth(&q.x0, depth);
    }
    if (len <= 4.0f) {
        return;
    }
    w = (len < scale - 4.0f) ? len - 4.0f : scale - 8.0f;
    q.x0 = 4.0f + pos->x;
    q.y0 = pos->y;
    q.x1 = q.x0 + w;
    q.y1 = 7.0f + pos->y;
    q.u0 = 0.92578125f;
    q.v0 = 0.1171875f;
    q.u1 = 0.97265625f;
    q.v1 = 0.14453125f;
    if (TWindowKeyBoardSoft::try_open(ctx, &q.x0) != 0) {
        draw_textured_quad_at_depth(&q.x0, depth);
    }
    end = scale - 4.0f;
    if (len <= end) {
        return;
    }
    w = len - end;
    q.x0 = pos->x + end;
    q.y0 = pos->y;
    q.x1 = w + q.x0;
    q.y1 = 7.0f + pos->y;
    q.u0 = 0.984375f;
    q.v0 = 0.1171875f;
    q.u1 = (252.0f + w) / 256.0f;
    q.v1 = 0.14453125f;
    if (TWindowKeyBoardSoft::try_open(ctx, &q.x0) != 0) {
        draw_textured_quad_at_depth(&q.x0, depth);
    }
}

void TWindowSubStatusDisp__sub_80256C40(TUnk_804CF930 *self, TWindowDrawContext *ctx, Pos_80256E0C *pos, f32 depth) {
    Quad_80256E0C q;
    f32 w;
    w = self->scale - -2.0f;
    q.x0 = -1.0f + pos->x;
    q.y0 = -1.0f + pos->y;
    q.x1 = 20.0f + q.x0;
    q.y1 = 9.0f + q.y0;
    q.u0 = 0.1484375f;
    q.v0 = 0.93359375f;
    q.u1 = 0.2265625f;
    q.v1 = 0.96875f;
    if (TWindowKeyBoardSoft::try_open(ctx, &q.x0) != 0) {
        draw_textured_quad_at_depth(&q.x0, depth);
    }
    q.x0 = 20.0f + (-1.0f + pos->x);
    q.y0 = -1.0f + pos->y;
    q.x1 = ((q.x0 + w) - 20.0f) - 20.0f;
    q.y1 = 9.0f + q.y0;
    q.u0 = 0.23046875f;
    q.v0 = 0.93359375f;
    q.u1 = 0.30859375f;
    q.v1 = 0.96875f;
    if (TWindowKeyBoardSoft::try_open(ctx, &q.x0) != 0) {
        draw_textured_quad_at_depth(&q.x0, depth);
    }
    q.x0 = ((-1.0f + pos->x) + w) - 20.0f;
    q.y0 = -1.0f + pos->y;
    q.x1 = 20.0f + q.x0;
    q.y1 = 9.0f + q.y0;
    q.u0 = 0.41015625f;
    q.v0 = 0.93359375f;
    q.u1 = 0.48828125f;
    q.v1 = 0.96875f;
    if (TWindowKeyBoardSoft::try_open(ctx, &q.x0) != 0) {
        draw_textured_quad_at_depth(&q.x0, depth);
    }
}

void TUnk_804CF930::calc_bar_width() {
    f32 goal;
    f32 max = maximum;
    f32 v;
    if (max <= 0.0f || (goal = target) <= 0.0f) {
        v = 0.0f;
    } else {
        v = (goal * scale) / max;
    }
    width = v;
}

void TUnk_804CF918::render(TWindowDrawContext *) {}
void TUnk_804CF918::update() {}

TUnk_804CF918::TUnk_804CF918(s16 arg) {
    flags = 0;
    m_2 = arg;
}

TUnk_804CF918::~TUnk_804CF918() {}

}
