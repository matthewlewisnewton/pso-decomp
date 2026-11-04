#include "types.h"

struct MoviePlanes_80143988 {
    u8 *luma;
    u8 *chroma0;
    u8 *chroma1;
    u32 luma_stride;
    u32 chroma_stride;
    u32 chroma1_stride;
};

extern "C" {
extern void *movie_current_frame_buffer;
extern s32 lbl_805D56A4;
extern s32 lbl_805D56A8;

// Each plane cursor is kept one word behind the bytes it reads or writes.
// The last access of a group is then `*(p += n)`, which MWCC emits as
// lwzu/stwu with the original `addi reg, reg, -4` prologue bias.
// Chroma and luma are inserted with __rlwinm/__rlwimi. The equivalent `|`
// masks compile to `or` for the second consumer of each chroma word; the
// rotate-insert form keeps both scanlines on `rlwimi`.
void pack_movie_frame(MoviePlanes_80143988 *frame) {
    const s32 width = lbl_805D56A4;
    const s32 height = lbl_805D56A8;
    const u32 width2 = (u32)width;
    const u32 luma_stride = frame->luma_stride;
    const u32 chroma_stride = frame->chroma_stride;
    u32 *dp = reinterpret_cast<u32 *>(static_cast<u8 *>(movie_current_frame_buffer)
        + ((640 - width) & 0x7FFFFFFCU)
        + ((((480 - height) * 640)) & ~3));
    u32 *lp = dp + (1280 / 4) - 1;
    u32 *y = reinterpret_cast<u32 *>(frame->luma);
    u32 *y2 = reinterpret_cast<u32 *>(frame->luma + (luma_stride & ~3U));
    u32 *u = reinterpret_cast<u32 *>(frame->chroma0);
    u32 *v = reinterpret_cast<u32 *>(frame->chroma1);
    dp -= 1;
    y -= 1;
    y2 -= 1;
    u -= 1;
    v -= 1;
    u32 *end = dp + height * (1280 / 4);
    const u32 row_bytes = (width2 << 1) & 0x7FFFFFFCU;
    const u32 dst_pad = 640U - (width2 >> 1);
    const u32 y_pad = ((luma_stride >> 1) & ~1U) - (width2 >> 2);
    const u32 c_pad = (chroma_stride >> 2) - (width2 >> 3);
    while (end > dp) {
        u32 *row_end = dp + (row_bytes >> 2);
        while (row_end > dp) {
            u32 uw = u[1];
            u32 vw = v[1];
            u32 yw = y[1];
            u32 lw = y2[1];
            __dcbt(y, 32);
            u32 c = __rlwimi(__rlwinm(uw, 24, 8, 15), vw, 8, 24, 31);
            u32 hi = __rlwimi(__rlwimi(c, yw, 0, 0, 7), yw, 24, 16, 23);
            u32 lo = __rlwimi(__rlwimi(c, lw, 0, 0, 7), lw, 24, 16, 23);
            dp[1] = hi;
            lp[1] = lo;
            c = __rlwimi(__rlwinm(uw, 0, 8, 15), vw, 16, 24, 31);
            yw = y[2];
            lw = *(y2 += 2);
            hi = __rlwimi(__rlwimi(c, yw, 16, 0, 7), yw, 8, 16, 23);
            lo = __rlwimi(__rlwimi(c, lw, 16, 0, 7), lw, 8, 16, 23);
            dp[2] = hi;
            lp[2] = lo;
            c = __rlwimi(__rlwinm(uw, 8, 8, 15), vw, 24, 24, 31);
            hi = __rlwimi(__rlwimi(c, yw, 0, 0, 7), yw, 24, 16, 23);
            lo = __rlwimi(__rlwimi(c, lw, 0, 0, 7), lw, 24, 16, 23);
            dp[3] = hi;
            lp[3] = lo;
            c = __rlwimi(__rlwinm(uw, 16, 8, 15), vw, 0, 24, 31);
            hi = __rlwimi(__rlwimi(c, yw, 16, 0, 7), yw, 8, 16, 23);
            lo = __rlwimi(__rlwimi(c, lw, 16, 0, 7), lw, 8, 16, 23);
            dp[4] = hi;
            lp[4] = lo;
            __dcbt(y2, 32);
            uw = *(u += 2);
            vw = *(v += 2);
            yw = y[3];
            lw = y2[1];
            c = __rlwimi(__rlwinm(uw, 24, 8, 15), vw, 8, 24, 31);
            hi = __rlwimi(__rlwimi(c, yw, 0, 0, 7), yw, 24, 16, 23);
            lo = __rlwimi(__rlwimi(c, lw, 0, 0, 7), lw, 24, 16, 23);
            dp[5] = hi;
            lp[5] = lo;
            c = __rlwimi(__rlwinm(uw, 0, 8, 15), vw, 16, 24, 31);
            hi = __rlwimi(__rlwimi(c, yw, 16, 0, 7), yw, 8, 16, 23);
            lo = __rlwimi(__rlwimi(c, lw, 16, 0, 7), lw, 8, 16, 23);
            dp[6] = hi;
            lp[6] = lo;
            yw = *(y += 4);
            lw = *(y2 += 2);
            c = __rlwimi(__rlwinm(uw, 8, 8, 15), vw, 24, 24, 31);
            lp[7] = __rlwimi(__rlwimi(c, lw, 0, 0, 7), lw, 24, 16, 23);
            dp[7] = __rlwimi(__rlwimi(c, yw, 0, 0, 7), yw, 24, 16, 23);
            c = __rlwimi(__rlwinm(uw, 16, 8, 15), vw, 0, 24, 31);
            *(dp += 8) = __rlwimi(__rlwimi(c, yw, 16, 0, 7), yw, 8, 16, 23);
            *(lp += 8) = __rlwimi(__rlwimi(c, lw, 16, 0, 7), lw, 8, 16, 23);
        }
        dp += dst_pad;
        lp += dst_pad;
        y += y_pad;
        y2 += y_pad;
        u += c_pad;
        v += c_pad;
    }
}
}
