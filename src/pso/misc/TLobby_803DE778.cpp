#include "types.h"
#include "pso/misc/TLobby.h"

extern "C" {
s32 memmove(void *dst, const void *src, u32 n);
}

void move_data(void *dst, const void *src, u32 n) {
    memmove(dst, src, n);
}

extern "C" {

#pragma push
#pragma scheduling off
#pragma peephole off
void TLobby::copy_u16_array(u16 *src, s32 n) {
    u16 *dst = (u16 *)this;
    memmove(dst, src, n * sizeof(u16));
}
#pragma pop

}

#pragma push
#pragma scheduling off
#pragma peephole off
void move_words(void *dst, const void *src, s32 n) {
    memmove(dst, src, (u32)(n * sizeof(u32)));
}
#pragma pop
