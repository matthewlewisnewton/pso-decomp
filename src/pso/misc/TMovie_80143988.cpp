#include "types.h"

// The movie module fills this record through the callback used by flip_frame_buffer.
struct MoviePlanes_80143988 {
    u8 *luma;
    u8 *chroma0;
    u8 *chroma1;
    u32 luma_stride;
    u32 chroma0_stride;
    u32 chroma1_stride;
};

extern "C" {
extern void *movie_current_frame_buffer;
extern s32 lbl_805D56A4;
extern s32 lbl_805D56A8;

void pack_movie_frame(void *record) {
    MoviePlanes_80143988 frame;
    __memcpy(&frame, record, sizeof(frame));
    const u32 width = (u32)lbl_805D56A4;
    const u32 height = (u32)lbl_805D56A8;
    u8 *output = static_cast<u8 *>(movie_current_frame_buffer) + ((640U - width) & ~3U)
        + (((480U - height) * 640U) & ~3U);
    u8 *y = frame.luma;
    u8 *u = frame.chroma0;
    u8 *v = frame.chroma1;
    const u32 row_bytes = (width * 2U) & 0x7FFFFFFCU;
    const u32 chunks = (row_bytes + 31U) / 32U;
    const u32 rows = (height + 1U) / 2U;
    for (u32 row = 0; row < rows; ++row) {
        u8 *y2 = y + (frame.luma_stride & ~3U);
        for (u32 x = 0; x < chunks * 16U; x += 2) {
            u32 chroma = x / 2;
            u32 upper = ((u32)y[x] << 24) | ((u32)u[chroma] << 16)
                | ((u32)y[x + 1] << 8) | v[chroma];
            u32 lower = ((u32)y2[x] << 24) | ((u32)u[chroma] << 16)
                | ((u32)y2[x + 1] << 8) | v[chroma];
            __memcpy(output + x * 2U, &upper, 4);
            __memcpy(output + 1280U + x * 2U, &lower, 4);
        }
        if (row + 1U < rows) {
            output += chunks * 32U + (640U - (width >> 1)) * 4U;
            y += chunks * 16U + ((frame.luma_stride >> 1) - (width >> 2)) * 4U;
            u += chunks * 8U + ((frame.chroma0_stride >> 2) - (width >> 3)) * 4U;
            v += chunks * 8U + ((frame.chroma0_stride >> 2) - (width >> 3)) * 4U;
        }
    }
}
}
