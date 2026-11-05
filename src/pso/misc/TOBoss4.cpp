#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/misc/TOBoss4.h"
#include "pso/misc/TOBoss4.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

struct RecoveredGlobal_80159D24_lbl_804AFD0C { s32 value; u8 remaining[0xC]; };
typedef char RecoveredGlobal_80159D24_lbl_804AFD0C_size[sizeof(RecoveredGlobal_80159D24_lbl_804AFD0C) == 0x10 ? 1 : -1];

extern "C" {
extern RecoveredGlobal_80159D24_lbl_804AFD0C bm_o_boss4_resource_descriptor;
extern u32 lbl_805D58A8;
void *TOBoss4__ct(void *arg0);
void *__dt__7TOBoss4Fv(void *arg0, s16 arg1);
void __ct__8TObjBaseFP7TObject(void *, void *);
void __dl__7TObjectFPv(void *);

void TOBoss4::free_instance() {
    if ((u32) lbl_805D58A8 != 0U) {
        delete (BmlResource *)((void*)lbl_805D58A8);
        lbl_805D58A8 = 0U;
    }
}

extern s32 __vt__7TOBoss4[];

void TOBoss4::load_static_resource() {
    s32 temp_r3;
    s32 var_r0;
    temp_r3 = (int)new BmlResource(1, (BmlResourceDescriptor *)(&bm_o_boss4_resource_descriptor.value), 0, 0, (void *)(0));
    var_r0 = temp_r3;
    (*(s32 *)&lbl_805D58A8) = var_r0;
}

}
TOBoss4::~TOBoss4() {

}
extern "C" {

extern void *tl_05;
extern const f32 lbl_805DB310;
extern const f32 lbl_805DB31C;
extern void *lbl_805D2EB0;

void *TOBoss4__ct(void *boss4) {
    __ct__8TObjBaseFP7TObject(boss4, tl_05);
    *(s32 **)((s8 *)boss4 + 0x18) = __vt__7TOBoss4;
    *(void * *)&((TOBoss4 *)boss4)->m_name = lbl_805D2EB0;
    *(f32 *)((s8 *)boss4 + 0x90) = lbl_805DB310;
    ((TOBoss4 *)boss4)->m_94 = lbl_805DB31C;
    return boss4;
}

}
