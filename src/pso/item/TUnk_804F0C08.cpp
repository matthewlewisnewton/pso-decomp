#include "pso/item/TUnk_804F0C08.h"

s32 TUnk_804F0C08::vfunc_7() {
    s32 temp_r4;

    temp_r4 = *(s32 *)((s8 *)this + 0xD4);
    if (temp_r4 > 0) {
        *(s32 *)((s8 *)this + 0xD4) = (temp_r4 - 1);
        return 1;
    }
    return 0;
}

TUnk_804F0C08::~TUnk_804F0C08() {}
