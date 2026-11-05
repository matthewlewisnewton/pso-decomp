#include "types.h"
#include "pso/system/memory.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/misc/TUnk_804CE018.h"
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

struct Bar_80256C00 {
    u8 pad0[0x14];
    f32 scale;
    u8 pad1[4];
    f32 width;
    f32 max;
    f32 target;
};

struct Gauge_802571B4 {
    u16 flags;
    u8 pad2[0x12];
    f32 scale;
    u8 pad18[4];
    f32 cur;
    f32 max;
    f32 val;
};

struct Pos_80256E0C { f32 x; f32 y; };

struct Quad_80256E0C { f32 x0, y0, x1, y1, u0, v0, u1, v1; };

extern "C" {
void calc_bar_width__20TWindowSubStatusDispFPv(struct Bar_80256C00 *bar);
f32 fabs_float(f32);
const f32 lbl_805DCECC = 2.0f;
void step_gauge_bar_width(Gauge_802571B4 *g);
void draw_textured_quad_at_depth(f32 *q, f32 depth);
void draw_status_gauge_bar__13TUnk_804CF930FP18TWindowDrawContextPvff(Gauge_80256E0C *self, TWindowDrawContext *ctx, Pos_80256E0C *pos, f32 depth, f32 len);
void TWindowSubStatusDisp__sub_80256BF8(void);
void TWindowSubStatusDisp__sub_80256BFC(void);
// Same symbol as the s16 member below. init_from's argument is the int
// parameter and the original call is `mr r4, r5`. Calling the short member
// from that int emits `extsh` and drops the function. Short callers pass a
// short and do not extend, so the definition stays s16.
void sub_80256BDC__13TUnk_804CF930Fs(TUnk_804CF930 *self, int arg);

void *TUnk_804CF930::destroy(s16 arg1) {
    if (this != NULL) {
        *(TUnk_804CF918_table **)((u8 *)this + 4) = &lbl_804CF918;
        if (arg1 > 0) {
            ::operator delete(this);
        }
    }
    return this;
}

void TUnk_804CF930::sub_80256BDC(s16 arg1) {
    *(TUnk_804CF918_table **)((u8 *)this + 4) = &lbl_804CF918;
    this->flags = 0;
    this->m_2 = arg1;
}

void TWindowSubStatusDisp__sub_80256BF8(void) {  }
void TWindowSubStatusDisp__sub_80256BFC(void) {  }
void calc_bar_width__20TWindowSubStatusDispFPv(struct Bar_80256C00 *bar) {
    f32 target;
    f32 max = bar->max;
    f32 v;
    if (max <= 0.0f || (target = bar->target) <= 0.0f) {
        v = 0.0f;
    } else {
        v = (target * bar->scale) / max;
    }
    bar->width = v;
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
    if (TWindowKeyBoardSoft::try_open(ctx, &q) != 0) {
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
    if (TWindowKeyBoardSoft::try_open(ctx, &q) != 0) {
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
    if (TWindowKeyBoardSoft::try_open(ctx, &q) != 0) {
        draw_textured_quad_at_depth(&q.x0, depth);
    }
}

void TUnk_804CF930::draw_status_gauge_bar(TWindowDrawContext *ctx, void *pos_arg, f32 depth, f32 len) {
    Pos_80256E0C *pos = (Pos_80256E0C *)pos_arg;
    Box_8024E8E8 q;
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
    if (TWindowKeyBoardSoft::try_open(ctx, &q) != 0) {
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
    if (TWindowKeyBoardSoft::try_open(ctx, &q) != 0) {
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
    if (TWindowKeyBoardSoft::try_open(ctx, &q) != 0) {
        draw_textured_quad_at_depth(&q.x0, depth);
    }
}

void TWindowSubStatusDisp__sub_80257024(TUnk_804CF930 *self, TWindowDrawContext *ctx) {
    // depth before bar: the two values live across the draw calls, and this
    // order is what puts depth in f31 and the bar in f29.
    f32 depth;
    f32 len;
    Pos_80256E0C pos;
    f32 bar;
    f32 sum = self->y / 21.0f + self->x / ctx->inner_w;
    // Signed cast. Its bias is this unit's .rodata (lbl_8044EE40). Nothing
    // else loads that object, so it is scope:local. Naming the double emits
    // a second copy and the lis/lfd stops matching the compiler pool.
    f32 tick = (f32)ctx->open_tick;

    sum *= 7.5f;
    bar = (tick - sum) * 17.0f;
    if (bar <= 0.0f) {
        return;
    }
    if (self->width <= 0.0f && (self->flags & 8) == 0) {
        return;
    }
    if (self->width > bar) {
        len = bar;
    } else {
        len = self->width;
    }
    pos.x = ctx->inner_x + self->x;
    pos.y = ctx->inner_y + self->y;
    depth = -1.0f / (0.299f * self->depth + ctx->depth);
    begin_screen_draw(1);
    set_current_texture_list(lbl_805D63F0);
    set_draw_texture_and_color(0xB, -1);
    if ((self->flags & 8) != 0) {
        TWindowSubStatusDisp__sub_80256C40(self, ctx, &pos, depth);
    }
    if (bar > 0.0f) {
        set_constant_material_color(self->color);
        self->draw_status_gauge_bar(ctx, &pos, depth, len);
    }
    TWindowSubStatusDisp::get_player();
}

void step_gauge_bar_width(Gauge_802571B4 *g) {
    f32 target;
    f32 diff;
    g->flags &= ~4;
    if (g->max <= 0.0f || g->val <= 0.0f) {
        target = 0.0f;
    } else {
        target = (g->val * g->scale) / g->max;
    }
    diff = target - g->cur;
    if (fabs_float(diff) < lbl_805DCECC) {
        g->cur = target;
        g->flags |= 4;
    } else if (diff > 0.0f) {
        g->cur += lbl_805DCECC;
    } else {
        g->cur -= lbl_805DCECC;
    }
}

void *TWindowSubStatusDisp__sub_80257298(TUnk_804CF930 *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(TUnk_804CF918_table **)((u8 *)arg0 + 4) = &lbl_804CF930;
        arg0->destroy(0);
        if (arg1 > 0) {
            ::operator delete(arg0);
        }
    }
    return arg0;
}

void *TUnk_804CF930::init_from(void *src_raw, int arg2) {
    TUnk_804CF930_init *src = static_cast<TUnk_804CF930_init *>(src_raw);
    sub_80256BDC__13TUnk_804CF930Fs(this, arg2);
    *(TUnk_804CF918_table **)((u8 *)this + 4) = &lbl_804CF930;
    width = 0.0f;
    x = src->x;
    y = src->y;
    depth = src->depth;
    scale = src->scale;
    color = src->color;
    flags = (u16)src->flags;
    maximum = src->maximum;
    target = src->target;
    return this;
}

}
