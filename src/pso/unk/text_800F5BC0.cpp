#include "pso/system/ArrayAllocation.h"
#include "types.h"
#include "pso/system/StripBufferPair.h"
#include "pso/unk/text_800F5BC0.h"
#include "pso/system/memory.h"

extern "C" {
void scroll_strip_uvs(StripBufferPair *arg0, s16 arg1, s16 arg2);

void scroll_strip_uvs(StripBufferPair *arg0, s16 arg1, s16 arg2) {
    s32 i;
    s16 *strip;
    s16 *uv;
    u32 n;
    u32 j;
    s32 len;
    s32 k;
    arg1 %= 256;
    arg2 %= 256;
    for (i = 0; i < arg0->strip_count; i++) {
        strip = arg0->strips[i].strip;
        uv = arg0->strips[i].uv;
        n = *strip++ & 0x3FFF;
        for (j = 0; j < n; j++) {
            len = *strip++;
            if (len < 0) {
                len = -len;
            }
            for (k = 0; k < len; k++) {
                strip[1] = uv[0] + arg1;
                strip[2] = uv[1] + arg2;
                uv += 2;
                strip += 3;
            }
        }
    }
}
}

void *destroy_buffer_pair(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        ::operator delete[]((void *)(*(s32 *)((s8 *)arg0 + 0xC)));
        *(s32 *)((s8 *)arg0 + 0xC) = 0;
        ::operator delete[]((void *)(*(s32 *)((s8 *)arg0 + 8)));
        *(s32 *)((s8 *)arg0 + 8) = 0;
        if (arg1 > 0) {
            ::operator delete(arg0);
        }
    }
    return arg0;
}
