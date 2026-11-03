#include "pso/system/ArrayAllocation.h"
#include "types.h"
#include "pso/misc/TUnk_804F1C58.h"
#include "pso/misc/TOBoss4Rock.h"

extern "C" {

void __dl__7TObjectFPv(void *);
void __dt__7TObjectFv(void *, int);

extern s32 lbl_804F1C58[];

void *TUnk_804F1C58::destroy(s16 arg1) {
    if (this != NULL) {
        *(s32 **)((s8 *)this + 0x18) = lbl_804F1C58;
        ::operator delete[](*(void * *)&(this->m_28));
        __dt__7TObjectFv(this, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(this);
        }
    }
    return this;
}

}
