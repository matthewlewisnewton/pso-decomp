#include "types.h"
#include "pso/unk/text_803DA798.h"
#include "pso/player/TObjPlayer_803DF7A8.h"
#include "pso/player/TObjPlayer.h"

extern "C" {
void OSPanic(const char *, int, const char *, ...);
extern char lbl_804FC7F8[];
extern char lbl_805D46F0[4];
}

void TObjPlayer::reload_texture(s32 arg1, u32 arg2, void *arg3) {
    s32 size;
    if ((arg2 & 0x40000000) != 0) {
        size = arg1;
    } else {
        OSPanic(lbl_804FC7F8, 0x30, lbl_805D46F0);
    }
    TObjPlayer__sub_803DAE1C((s32)this, size, (u32)arg3);
}

extern "C" {
char lbl_804FC7F8[] = "nuReLoadTexture.c";
}
