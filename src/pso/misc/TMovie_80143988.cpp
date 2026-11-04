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

void pack_movie_frame(MoviePlanes_80143988 *frame) {
    const s32 width = lbl_805D56A4;
    const s32 height = lbl_805D56A8;
    const u32 width2 = (u32)width;
    const u32 luma_stride = frame->luma_stride;
    const u32 chroma_stride = frame->chroma_stride;
    u8 *dst = static_cast<u8 *>(movie_current_frame_buffer) + (((640 - width) & ~3))
        + ((((480 - height) * 640)) & ~3);
    u8 *end = dst + height * 1280;
    u8 *low = dst + 1276;
    u8 *y = frame->luma;
    u8 *y2 = y + (luma_stride & ~3U);
    u8 *u = frame->chroma0;
    u8 *v = frame->chroma1;
    const u32 row_bytes = (width2 * 2U) & ~3U;
    while (end > dst) {
        u8 *row_end = dst + row_bytes;
        while (row_end > dst) {
            __dcbt(y, 0x20);
            __dcbt(y2, 0x20);
            u32 yw;
            u32 lw;
            u32 uw;
            u32 vw;
            yw = *reinterpret_cast<const u32 *>(y + 0);
            lw = *reinterpret_cast<const u32 *>(y2 + 0);
            uw = *reinterpret_cast<const u32 *>(u + 0);
            vw = *reinterpret_cast<const u32 *>(v + 0);
            reinterpret_cast<u32 *>(dst)[0] = (yw & 0xFF000000U) | ((uw >> 8) & 0x00FF0000U)
                | ((yw >> 8) & 0x0000FF00U) | ((vw >> 24) & 0xFFU);
            reinterpret_cast<u32 *>(low)[0] = (lw & 0xFF000000U) | ((uw >> 8) & 0x00FF0000U)
                | ((lw >> 8) & 0x0000FF00U) | ((vw >> 24) & 0xFFU);
            reinterpret_cast<u32 *>(dst)[1] = ((yw << 16) & 0xFF000000U) | (uw & 0x00FF0000U)
                | ((yw << 8) & 0x0000FF00U) | ((vw >> 16) & 0xFFU);
            reinterpret_cast<u32 *>(low)[1] = ((lw << 16) & 0xFF000000U) | (uw & 0x00FF0000U)
                | ((lw << 8) & 0x0000FF00U) | ((vw >> 16) & 0xFFU);
            yw = *reinterpret_cast<const u32 *>(y + 4);
            lw = *reinterpret_cast<const u32 *>(y2 + 4);
            uw = *reinterpret_cast<const u32 *>(u + 0);
            vw = *reinterpret_cast<const u32 *>(v + 0);
            reinterpret_cast<u32 *>(dst)[2] = (yw & 0xFF000000U) | ((uw << 8) & 0x00FF0000U)
                | ((yw >> 8) & 0x0000FF00U) | ((vw >> 8) & 0xFFU);
            reinterpret_cast<u32 *>(low)[2] = (lw & 0xFF000000U) | ((uw << 8) & 0x00FF0000U)
                | ((lw >> 8) & 0x0000FF00U) | ((vw >> 8) & 0xFFU);
            reinterpret_cast<u32 *>(dst)[3] = ((yw << 16) & 0xFF000000U) | (uw & 0x00FF0000U)
                | ((yw << 8) & 0x0000FF00U) | (vw & 0xFFU);
            reinterpret_cast<u32 *>(low)[3] = ((lw << 16) & 0xFF000000U) | (uw & 0x00FF0000U)
                | ((lw << 8) & 0x0000FF00U) | (vw & 0xFFU);
            yw = *reinterpret_cast<const u32 *>(y + 8);
            lw = *reinterpret_cast<const u32 *>(y2 + 8);
            uw = *reinterpret_cast<const u32 *>(u + 4);
            vw = *reinterpret_cast<const u32 *>(v + 4);
            reinterpret_cast<u32 *>(dst)[4] = (yw & 0xFF000000U) | ((uw >> 8) & 0x00FF0000U)
                | ((yw >> 8) & 0x0000FF00U) | ((vw >> 24) & 0xFFU);
            reinterpret_cast<u32 *>(low)[4] = (lw & 0xFF000000U) | ((uw >> 8) & 0x00FF0000U)
                | ((lw >> 8) & 0x0000FF00U) | ((vw >> 24) & 0xFFU);
            reinterpret_cast<u32 *>(dst)[5] = ((yw << 16) & 0xFF000000U) | (uw & 0x00FF0000U)
                | ((yw << 8) & 0x0000FF00U) | ((vw >> 16) & 0xFFU);
            reinterpret_cast<u32 *>(low)[5] = ((lw << 16) & 0xFF000000U) | (uw & 0x00FF0000U)
                | ((lw << 8) & 0x0000FF00U) | ((vw >> 16) & 0xFFU);
            yw = *reinterpret_cast<const u32 *>(y + 12);
            lw = *reinterpret_cast<const u32 *>(y2 + 12);
            uw = *reinterpret_cast<const u32 *>(u + 4);
            vw = *reinterpret_cast<const u32 *>(v + 4);
            reinterpret_cast<u32 *>(dst)[6] = (yw & 0xFF000000U) | ((uw << 8) & 0x00FF0000U)
                | ((yw >> 8) & 0x0000FF00U) | ((vw >> 8) & 0xFFU);
            reinterpret_cast<u32 *>(low)[6] = (lw & 0xFF000000U) | ((uw << 8) & 0x00FF0000U)
                | ((lw >> 8) & 0x0000FF00U) | ((vw >> 8) & 0xFFU);
            reinterpret_cast<u32 *>(dst)[7] = ((yw << 16) & 0xFF000000U) | (uw & 0x00FF0000U)
                | ((yw << 8) & 0x0000FF00U) | (vw & 0xFFU);
            reinterpret_cast<u32 *>(low)[7] = ((lw << 16) & 0xFF000000U) | (uw & 0x00FF0000U)
                | ((lw << 8) & 0x0000FF00U) | (vw & 0xFFU);
            dst += 32;
            low += 32;
            y += 16;
            y2 += 16;
            u += 8;
            v += 8;
        }
        dst += (640 - (width2 >> 1)) * 4;
        low += (640 - (width2 >> 1)) * 4;
        y += (((luma_stride >> 1) & ~1U) - (width2 >> 2)) * 4;
        y2 += (((luma_stride >> 1) & ~1U) - (width2 >> 2)) * 4;
        u += ((chroma_stride >> 2) - (width2 >> 3)) * 4;
        v += ((chroma_stride >> 2) - (width2 >> 3)) * 4;
    }
}
}
