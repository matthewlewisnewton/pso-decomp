#include "types.h"
#include "pso/unk/text_8007F4B8.h"

struct E_8007F4B8 { s32 a; f32 f; };

struct O_8007F4B8 { u8 pad[0x40]; s32 count; E_8007F4B8 e[4]; };

extern "C" {
s32 fn_8007F4B8(O_8007F4B8 *arg0, s32 arg1, f32 farg0);

s32 fn_8007F4B8(O_8007F4B8 *arg0, s32 arg1, f32 farg0) {
    s32 i;
    if (arg1 == arg0->e[0].a || farg0 == arg0->e[0].f) {
        return 0;
    }
    for (i = 3; i > 0; i--) {
        fn_8007F560(&arg0->e[i], &arg0->e[i - 1]);
    }
    arg0->e[0].a = arg1;
    arg0->e[0].f = farg0;
    arg0->count++;
    return 1;
}

void fn_8007F560(void* p, void* q) { *(u32*)((char*)p + 0x0) = *(u32*)((char*)q + 0x0); *(f32*)((char*)p + 0x4) = *(f32*)((char*)q + 0x4); }

}
