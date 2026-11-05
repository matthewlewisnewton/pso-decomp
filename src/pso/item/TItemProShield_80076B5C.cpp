#include "types.h"
#include "pso/item/TItemProShield_80076B5C.h"
#include "pso/item/TItemProShield.h"

extern "C" {

void __dl__7TObjectFPv(void *);
void __dt__7TObjectFv(void *, int);

s16 TItemProShield::get_field_2b8() { return *(s16*)((char*)this + 0x2b8); }

extern s32 lbl_804CC048[];

void *__dt__13TUnk_804CC048Fv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = lbl_804CC048;
        __dt__7TObjectFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

}
