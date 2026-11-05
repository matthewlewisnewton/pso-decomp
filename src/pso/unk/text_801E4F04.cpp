#include "pso/system/ArrayAllocation.h"
#include "types.h"
#include "pso/unk/TUnk_804C57F0.h"
#include "pso/unk/text_801E4F04.h"


extern "C" {

s32 __ct__7TObjectFP7TObject();

extern s32 __vt__13TUnk_804C57F0[];

}
TUnk_804C57F0::~TUnk_804C57F0() {
    ::operator delete[](*(void **)((s8 *)this + 0x20));
    this->m_20 = 0;
    ::operator delete[](*(void **)((s8 *)this + 0x1C));
    *(s32 *)((s8 *)this + 0x1C) = 0;
}


void *quad_sprite_base_ct(void *arg0, void *arg_r4, void *arg2) {
    s32 temp_r31;

    __ct__7TObjectFP7TObject();
    *(s32 **)((s8 *)arg0 + 0x18) = __vt__13TUnk_804C57F0;
    ((TUnk_804C57F0 *)arg0)->m_28 = arg2;
    temp_r31 = *(s32 *)((s8 *)(((TUnk_804C57F0 *)arg0)->m_28) + 0xC);
    *(s32 *)((s8 *)arg0 + 0x1C) = (s32)::operator new[](temp_r31 * 0x2C);
    ((TUnk_804C57F0 *)arg0)->m_20 = (s32)::operator new[](temp_r31 * 4);
    ((TUnk_804C57F0 *)arg0)->quad_sprite_reset_entries();
    return arg0;
}

