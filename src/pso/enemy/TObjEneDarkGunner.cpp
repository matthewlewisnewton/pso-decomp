#include "types.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/enemy/TObjEneMe1Canadin_EffLineFade.h"
#include "pso/enemy/TObjEneDarkGunner.h"

extern "C" {

void __dl__7TObjectFPv(void *);
void __dt__7TObjectFv(void *, int);

void TObjEneMe1Canadin_EffLineFade::run_task() {
    s32 var_r31;

    var_r31 = this->m_37;
    var_r31 -= 0x10;
    if (var_r31 < 0) {
        var_r31 = 0;
        queue_destruction__7TObjectFv(this);
    }
    this->m_37 = (u8) var_r31;
    this->m_3b = (s8) var_r31;
}

extern s32 lbl_80490458[];

void *TObjEneDarkGunner::deleting_dtor(s16 arg1) {
    if (this != NULL) {
        *(s32 **)((s8 *)this + 0x18) = lbl_80490458;
        __dt__7TObjectFv(this, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(this);
        }
    }
    return this;
}

}
