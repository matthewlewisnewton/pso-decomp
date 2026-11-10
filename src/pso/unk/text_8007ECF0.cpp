#include "pso/ui/MenuText.h"
#include "types.h"
#include "pso/misc/TWindowSubStatusDisp_80144B14.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/unk/text_8007ECF0.h"
#include "pso/misc/TDLGraph.h"
#include "pso/TObjWarpString.h"
#include "pso/misc/TLobby_801E2F94.h"

#include <stdio.h>

typedef ColorLineVertex GraphPoint;
typedef ColorLineList GraphFan;

struct E_8007F3F8 { s32 a; f32 f; };

struct O_8007F3F8 { u8 pad[0x40]; s32 count; E_8007F3F8 e[4]; };

extern "C" {
s32 fn_8007F3F8(O_8007F3F8 *arg0, f32 farg0);
struct Obj_8007F0E4 {
    u8 pad0[0x1C];
    f32 f1C;
    u32 flags;
    s32 f24;
    u8 pad28[4];
    s32 time;
    s32 f30;
};

s32 fn_8007F4B8(void *, s32, f32);

extern const GraphFan lbl_80438AB4;
extern const f32 lbl_805D92A8, lbl_805D92B4, lbl_805D92B8;
extern const char lbl_80438AD8[];
extern const char lbl_80438AE0[];
extern const char lbl_80438AEC[];
extern const f32 lbl_805D9298;
extern const f32 lbl_805D929C;
extern const f32 lbl_805D92A0;
extern const f32 lbl_805D92A4;
extern const f32 lbl_805D92AC;
extern const f32 lbl_805D92B0;

namespace GraphTemplateData {
extern "C" {
__declspec(section ".rodata") extern const char TDLGraph__class_name_string[] = "TDLGraph";
__declspec(section ".rodata") extern const GraphPoint lbl_80438AA4 = { 473.0f, 440.0f };
__declspec(section ".rodata") extern const GraphPoint lbl_80438AAC = { 142.0f, 8.0f };
__declspec(section ".rodata") extern const GraphFan lbl_80438AB4 = { 0, 0, 0, 4 };
}
}

#pragma push
#pragma opt_common_subs off
#pragma fp_contract on
void fn_8007ECF0(u8 *arg0, s32 arg1, s32 arg2) {
    f32 temp_f1;
    s32 temp_r0_2;
    s32 temp_r3;
    s32 var_r3;
    *(f32 *)((s8 *)arg0 + 0x1C) = (f32) ((f32) arg1 / (f32) arg2);
    temp_f1 = *(f32 *)((s8 *)arg0 + 0x1C);
    if (temp_f1 < lbl_805D9298) {
        *(f32 *)((s8 *)arg0 + 0x1C) = (f32) lbl_805D9298;
    } else if (temp_f1 > lbl_805D929C) {
        *(f32 *)((s8 *)arg0 + 0x1C) = (f32) lbl_805D929C;
    }
    if (((s32) *(s32 *)((s8 *)arg0 + 0x28) != 0) && (fn_8007F4B8(arg0, *(s32 *)((s8 *)arg0 + 0x24), *(f32 *)((s8 *)arg0 + 0x1C)) != 0)) {
        temp_r3 = fn_8007F3F8((O_8007F3F8 *)(arg0), *(f32 *)((s8 *)arg0 + 0x1C));
        if (temp_r3 >= 0) {
            var_r3 = temp_r3 + (s32) ((lbl_805D92A0 * ((f32) temp_r3 / lbl_805D92A4)) + lbl_805D92A0);
            if (var_r3 > 0x464F) {
                var_r3 = 0x464F;
            }
            switch (*(s32 *)((s8 *)arg0 + 0x28)) {
            case 0:
                break;
            case -1:
                if (var_r3 >= 0x12C) {
                    *(s32 *)((s8 *)arg0 + 0x28) = 1;
                    *(s32 *)((s8 *)arg0 + 0x2C) = var_r3;
                    *(s32 *)((s8 *)arg0 + 0x30) = (s32) *(s32 *)((s8 *)arg0 + 0x24);
                }
                break;
            case 1:
                temp_r0_2 = *(s32 *)((s8 *)arg0 + 0x2C);
                if (temp_r0_2 > var_r3) {
                    *(s32 *)((s8 *)arg0 + 0x2C) = var_r3;
                } else if ((s32) (var_r3 - temp_r0_2) >= 0x4B) {
                    *(s32 *)((s8 *)arg0 + 0x2C) = var_r3;
                }
                *(s32 *)((s8 *)arg0 + 0x30) = (s32) *(s32 *)((s8 *)arg0 + 0x24);
                break;
            }
        }
    }
    if (lbl_805D929C == *(f32 *)((s8 *)arg0 + 0x1C)) {
        queue_destruction__7TObjectFv((arg0));
    }
}
#pragma pop

// The separate C-linkage scope keeps later reads from folding into duplicate
// compiler literals while retaining the original exported pool symbols.
namespace GraphConstants {
extern "C" {
__declspec(section ".sdata2") extern const f32 lbl_805D9298 = 0.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D929C = 1.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D92A0 = 30.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D92A4 = 1800.0f;
}
}

void draw_outlined_string_right_aligned__14TObjWarpStringFPviiPv(void *, s32 x0, s32 y0, char *str) {
    f32 x;
    f32 y;
    f32 xr;
    f32 yb;

    x = (f32)(u32)(x0 - calc_text_width(str));
    y = (f32)y0;
    draw_menu_text(x - 2.0f, y - 2.0f, str, 0xFF000000);
    draw_menu_text(x, y - 2.0f, str, 0xFF000000);
    xr = 2.0f + x;
    draw_menu_text(xr, y - 2.0f, str, 0xFF000000);
    draw_menu_text(x - 2.0f, y, str, 0xFF000000);
    draw_menu_text(xr, y, str, 0xFF000000);
    yb = 2.0f + y;
    draw_menu_text(x - 2.0f, yb, str, 0xFF000000);
    draw_menu_text(x, yb, str, 0xFF000000);
    draw_menu_text(xr, yb, str, 0xFF000000);
    draw_menu_text(x, y, str, 0xFFFFFFFF);
}

void TDLGraph::draw_percent_text(f32 farg0, f32 farg1) {
    char text[8];
    s32 var_r5;

    if (this->m_20 & 2) {
        text[0] = '\0';
        var_r5 = (s32) (lbl_805D92AC * this->progress);
        if (var_r5 < 0) {
            var_r5 = 0;
        } else if (var_r5 > 0x64) {
            var_r5 = 0x64;
        }
        sprintf(text, lbl_80438AD8, var_r5);
        draw_outlined_string_right_aligned__14TObjWarpStringFPviiPv(this, (s32) farg0, (s32) farg1, text);
    }
}

__declspec(section ".sdata2") extern const f32 lbl_805D92AC = 100.0f;

__declspec(section ".rodata") extern const char lbl_80438AD8[] = "%3d%";

void TDLGraph::draw_countdown_timer(f32 x, f32 y) {
    Obj_8007F0E4 *self = (Obj_8007F0E4 *)this;
    char buf[16];
    s32 t;
    s32 mins;
    s32 secs;
    s32 frac;
    f32 r;
    f32 k;

    if (!(self->flags & 1)) {
        return;
    }
    buf[0] = 0;
    t = self->time;
    if (t <= 0) {
        return;
    }
    mins = t / 1800;
    secs = (t / 30) % 60;
    frac = (t % 30) / 3;
    if (mins > 0) {
        sprintf(buf, lbl_80438AE0, mins, secs, frac);
    } else {
        sprintf(buf, lbl_80438AEC, secs, frac);
    }
    draw_outlined_string_right_aligned__14TObjWarpStringFPviiPv(self, (s32)x, (s32)y, buf);
    if (self->f30 > 0 && self->f24 - self->f30 > 0x4B && self->f1C > 1e-5f) {
        k = lbl_805D929C;
        r = k / self->f1C;
        r -= k;
        self->time = (s32)(r * (f32)self->f24);
        if (self->time > 0x464F) {
            self->time = 0x464F;
        }
        self->f30 = self->f24;
    }
    if (self->time > 5) {
        self->time--;
    }
}

__declspec(section ".rodata") extern const char lbl_80438AE0[] ATTRIBUTE_ALIGN(4) = "%d\"%02d.%d ";

#pragma push
#pragma fp_contract on
void fn_8007F27C(TDLGraph *graph, const GraphPoint *position, const GraphPoint *size) {
    GraphPoint vertices[4];
    u32 colors[4];
    GraphFan fan = lbl_80438AB4;
    const f32 margin = 2.0f;
    fan.verts = vertices;
    fan.colors = colors;
    colors[0] = colors[1] = colors[2] = colors[3] = 0xff;
    vertices[0].x = vertices[3].x = position->x - margin;
    vertices[1].x = vertices[2].x = margin + (position->x + size->x);
    vertices[0].y = vertices[1].y = position->y - margin;
    vertices[2].y = vertices[3].y = margin + (position->y + size->y);
    draw_tri_fan_2d__14TObjCMHairMenuFllf(&fan, 4, 2, -2.0f);

    colors[0] = colors[1] = colors[2] = colors[3] = graph->bar_color;
    vertices[0].x = vertices[3].x = position->x;
    vertices[1].x = vertices[2].x = size->x * graph->progress + position->x;
    vertices[0].y = vertices[1].y = position->y;
    vertices[2].y = vertices[3].y = size->y + position->y;
    draw_tri_fan_2d__14TObjCMHairMenuFllf(&fan, 4, 2, lbl_805D92B8);

    colors[0] = colors[1] = colors[2] = colors[3] = graph->m_38;
    vertices[0].x = vertices[3].x = size->x + position->x;
    draw_tri_fan_2d__14TObjCMHairMenuFllf(&fan, 4, 2, lbl_805D92B8);
}

#pragma pop

__declspec(section ".sdata2") extern const f32 lbl_805D92B8 = -1.0f;

s32 fn_8007F3F8(O_8007F3F8 *arg0, f32 farg0) {
    f32 sum;
    f32 df;
    f32 da;
    s32 i;
    if (arg0->count < 9) {
        return -1;
    }
    sum = lbl_805D9298;
    for (i = 0; i < 3; i++) {
        da = (f32)(arg0->e[i].a - arg0->e[i + 1].a);
        df = arg0->e[i].f - arg0->e[i + 1].f;
        if (da <= 1e-05f || df <= 1e-05f) {
            return -1;
        }
        sum += da / df;
    }
    sum /= 3.0f;
    f32 remaining = lbl_805D929C - farg0;
    return (s32)(remaining * sum);
}

__declspec(section ".rodata") extern const char lbl_80438AEC[] = "%d.%d ";

}
