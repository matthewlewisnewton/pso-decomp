#include "types.h"
#include "pso/player/TObjPlayer.h"
#include "pso/system/ChunkPolygonList.h"

extern "C" {

typedef ChunkColorVertex Vtx_803E549C;

typedef union {
    u8 u8;
    u16 u16;
    s16 s16;
    u32 u32;
    s32 s32;
    f32 f32;
} WGPipe_803E549C;
#define GXWGFifo_803E549C (*(volatile WGPipe_803E549C *)0xCC008000)

void Dolphin_GXSetVtxDesc(int, int);
void GXClearVtxDesc(void);
void GXSetVtxAttrFmt(int, int, int, int, u8);
void GXBegin(int, int, u16);
extern u32 chunk_render_flags;

s32 resolve_render_keys__10TObjPlayerFPPUlPPUl();

extern s32 lbl_805D7778;

void TObjPlayer::set_global_7778(s32 arg0) {
    lbl_805D7778 = arg0;
}

void TObjPlayer::update_render_state() {
    resolve_render_keys__10TObjPlayerFPPUlPPUl();
    TObjPlayer::advance_render_counters();
}

#pragma push
#pragma use_lmw_stmw off
void draw_chunk_color_tex_strips(s16 *p, Vtx_803E549C *verts, u32 flags, s32 big) {
    s32 draw;
    u32 count;
    s32 extra;
    s32 n;

    draw = 1;
    extra = (flags >> 14) & 3;
    count = flags & 0x3FFF;
    if (chunk_render_flags != 0) {
        if (chunk_render_flags & 1) {
            if (chunk_render_flags & 0x200) {
                TObjPlayer::clear_move_state_bits();
                draw = 0;
            }
        } else if ((chunk_render_flags & 2) && (chunk_render_flags & 0x400)) {
            TObjPlayer::clear_move_state_bits();
            draw = 0;
        }
    }
    TObjPlayer::clear_move_state_bits();
    GXClearVtxDesc();
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 3, big ? 0xC : 8);
    Dolphin_GXSetVtxDesc(9, 1);
    Dolphin_GXSetVtxDesc(0xB, 1);
    Dolphin_GXSetVtxDesc(0xD, 1);
    do {
        n = *p++;
        if (n < 0) {
            n = -n;
        }
        if (draw) {
            GXBegin(0x98, 0, n);
        }
        do {
            Vtx_803E549C *v = &verts[p[0]];
            u32 c;
            s16 s = p[1];
            s16 t = p[2];
            p += 3;
            if (draw) {
                f32 x;
                f32 y;
                f32 z;
                z = v->z;
                y = v->y;
                x = v->x;
                GXWGFifo_803E549C.f32 = x;
                GXWGFifo_803E549C.f32 = y;
                GXWGFifo_803E549C.f32 = z;
                c = v->color;
                GXWGFifo_803E549C.u32 = ((c & 0xFFFFFF) << 8) | ((c & 0xFF000000) >> 24);
                GXWGFifo_803E549C.s16 = s;
                GXWGFifo_803E549C.s16 = t;
            }
            p += extra;
        } while (--n != 0);
    } while (--count != 0);
}
#pragma pop

}
