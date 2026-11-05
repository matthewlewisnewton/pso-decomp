#include "types.h"
#include "pso/boss/TObjBoss2Tunnel_803E2BAC.h"
#include "pso/player/TObjPlayer_803E21B8.h"
#include "pso/boss/TObjBoss2Tunnel.h"
#include "pso/player/TObjPlayer.h"

extern "C" {
s32 GXBegin(int, int, u16);
extern const f32 lbl_805E1080;

void TObjBoss2Tunnel::reset_player_state() {
    TObjPlayer__sub_803E2248();
}

typedef union {
    u8 u8;
    u16 u16;
    u32 u32;
    s32 s32;
    f32 f32;
} WGPipe_803E2BCC;
#define GXWGFifo_803E2BCC (*(volatile WGPipe_803E2BCC *)0xCC008000)
void TObjBoss2Tunnel::draw_projected_quads(ProjectedVertex *vertices, int n) {
    s32 i;
    f32 one;
    GXBegin(0x98, 4, n);
    one = lbl_805E1080;
    for (i = 0; i != n; i++) {
        f32 x;
        f32 y;
        f32 w;
        u32 c;
        w = one / vertices->z;
        y = vertices->y * w;
        x = vertices->x * w;
        GXWGFifo_803E2BCC.f32 = x;
        GXWGFifo_803E2BCC.f32 = y;
        GXWGFifo_803E2BCC.f32 = w;
        c = vertices->color;
        GXWGFifo_803E2BCC.u32 = ((c & 0xFFFFFF) << 8) | ((c & 0xFF000000) >> 24);
        vertices++;
    }
}

void TObjBoss2Tunnel__sub_803E2D10(s32 arg0) {
    TObjPlayer::load_screen_space_matrix();
    if (arg0 != 0) {
        TObjPlayer__sub_803E21DC();
        return;
    }
    setup_opaque_color_draw();
}

}
