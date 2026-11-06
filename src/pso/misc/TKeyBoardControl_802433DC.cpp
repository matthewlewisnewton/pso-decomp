#include "types.h"
#include "pso/misc/TKeyBoardControl.h"

extern "C" {

s32 xmalloc__FUl(s32);

extern s32 player_data_load_buffer;

void TKeyBoardControl::alloc_buffer() {
    player_data_load_buffer = xmalloc__FUl(0x14000);
}

}
