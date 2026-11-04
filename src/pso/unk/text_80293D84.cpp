#include "types.h"
#include "pso/unk/text_80293D84.h"
#include "pso/misc/TLobby_801E2F94.h"
#include "pso/misc/TWindowSubSymbolChatPartsSet.h"
#include <stddef.h>
#include "pso/TChCrEffFade.h"

typedef ColorLineVertex V2_80293D84;
typedef ColorLineList Prim_80293D84;

struct V2_80293E58 {
    f32 x;
    f32 y;
};

extern "C" {
u32 __cvt_fp2unsigned(f32);
extern V2_80293D84 lbl_80464ED8[6];

extern const f32 lbl_80464F10[];
extern const f32 lbl_80464F18[];

#pragma push
#pragma fp_contract on
void fn_80293D84(void *arg0, void *arg1, u32 color, f32 scale, f32 alpha) {
    V2_80293D84 *pos = (V2_80293D84 *)arg1;
    Prim_80293D84 prim;
    u32 colors[6];
    V2_80293D84 pts[6];
    s32 i;
    u32 c;
    for (i = 0; i < 6; i++) {
        pts[i].x = scale * lbl_80464ED8[i].x + pos->x;
        pts[i].y = scale * lbl_80464ED8[i].y + pos->y;
    }
    c = (color & 0x00FFFFFF) | (__cvt_fp2unsigned(255.0f * alpha) << 24);
    for (i = 0; i < 6; i++) {
        colors[i] = c;
    }
    prim.colors = colors;
    prim.unk_8 = 0;
    prim.count = 6;
    prim.verts = pts;
    prim.draw_strip_swap_color(6, 6, (-1.5f));
}
#pragma pop

void fn_80293E58(void *arg0, f32 scale) {
    V2_80293E58 p;
    f32 s = 12.0f * scale;
    s32 odd = 1;
    ((TWindowSubSymbolChatPartsSet *)(&p))->copy_vec2((void *)lbl_80464F10);
    for (; p.y < lbl_80464F18[1]; p.y += 10.38f) {
        p.x = lbl_80464F10[0];
        if (odd == 0) {
            p.x += -18.0f;
        }
        for (; p.x < lbl_80464F18[0]; p.x += 36.0f) {
            fn_80293D84(arg0, &p, 0, s, scale);
        }
        odd ^= 1;
    }
}

}

struct Stack_80293F98 : ColorLineList {
    u32 sp18;
    u32 sp1C;
    u32 sp20;
    u32 sp24;
};

struct RecoveredGlobal_80293F98_lbl_804DB900 {
    ColorLineVertex value;
    u8 remaining[0x18];
};

extern "C" {

extern RecoveredGlobal_80293F98_lbl_804DB900 chcr_eff_fade_strip_rect;

typedef char RecoveredGlobal_80293F98_lbl_804DB900_size[sizeof(RecoveredGlobal_80293F98_lbl_804DB900) == 0x20 ? 1 : -1];
typedef char Stack_80293F98_size[sizeof(Stack_80293F98) == 0x20 ? 1 : -1];
void TChCrEffFade::draw_fade_strip(f32 farg0) {
    Stack_80293F98 stack;
    s32 temp_r9;
    temp_r9 = __cvt_fp2unsigned((f32) (255.0f * farg0)) << 0x18;
    stack.sp24 = temp_r9;
    stack.sp20 = temp_r9;
    stack.sp1C = temp_r9;
    stack.sp18 = temp_r9;
    stack.colors = &stack.sp18;
    stack.unk_8 = 0;
    stack.count = 4;
    stack.verts = &chcr_eff_fade_strip_rect.value;
    stack.draw_strip_swap_color(4, 6, (-1.5f));
}

}
