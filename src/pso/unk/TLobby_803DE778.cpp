#include <string.h>
#include "pso/system/memory.h"
#include "pso/unk/TLobby.h"

void move_data(void *dst, const void *src, u32 bytes) {
    memmove(dst, src, bytes);
}

#pragma push
#pragma scheduling off
#pragma peephole off
void TLobby::copy_u16_array(u16 *src, s32 n) {
    u16 *dst = (u16 *)this;
    memmove(dst, src, n * sizeof(u16));
}
#pragma pop

#pragma push
#pragma scheduling off
#pragma peephole off
void move_words(void *dst, const void *src, s32 count) {
    memmove(dst, src, count * sizeof(u32));
}
#pragma pop
