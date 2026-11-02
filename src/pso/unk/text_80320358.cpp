#include "types.h"
#include "pso/unk/text_80320358.h"
#include "pso/system/memory.h"
#include "pso/misc/TScene.h"

extern "C" {
s32 read_disc_file(void *, void *);
s32 OSLink(void *, void *);
void OSUnlink(void *);
RelModuleBuffer *fn_80320358(RelModuleBuffer *arg0, s16 arg1);

RelModuleBuffer *fn_80320358(RelModuleBuffer *arg0, s16 arg1) {
    u8 *t;
    if (arg0 != NULL) {
        t = (u8 *)fn_803204B0(arg0);
        if (t != NULL) {
            (*(void (**)(void))(t + 0x38))();
        }
        if (arg0->image != NULL) {
            OSUnlink(arg0->image);
            xfree(arg0->image);
            arg0->image = NULL;
        }
        if (arg0->bss != NULL) {
            xfree(arg0->bss);
            arg0->bss = NULL;
        }
        if (arg1 > 0) {
            ::operator delete(arg0);
        }
    }
    return arg0;
}

#pragma push
#pragma fp_contract on
RelModuleBuffer *load_rel_module(RelModuleBuffer *arg0, s32 arg1) {
    u8 *temp_r3;
    s32 size;
    u32 size2;
    arg0->bss = NULL;
    arg0->image = NULL;
    size = ((TScene *)arg1)->update_lobby_scene();
    if (size > 0) {
        arg0->image = xmalloc(size);
        if ((void *) arg0->image == NULL) {
            return arg0;
        }
        read_disc_file((void *)arg1, arg0->image);
        size2 = *(u32 *)((s8 *)(arg0->image) + 0x20);
        if (size2 != 0U) {
            arg0->bss = xmalloc(size2);
            if ((void *) arg0->bss == NULL) {
                return arg0;
            }
        }
        OSLink((void *) (arg0->image), (void *) (arg0->bss));
        temp_r3 = (u8 *)fn_803204B0(arg0);
        if (temp_r3 != NULL) {
            (*(s32 (**)())((s8 *)temp_r3 + 0x34))();
        }
        goto block_8;
    }
block_8:
    return arg0;
}
#pragma pop

}
