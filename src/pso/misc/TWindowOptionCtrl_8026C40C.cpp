#include "types.h"
#include "pso/misc/TWindowOptionCtrl_8026C40C.h"
#include "pso/misc/TWindowSubComCard_80244774.h"
#include "pso/misc/TWindowOptionCtrl.h"
#include "pso/misc/TWindowSubComCard.h"

extern "C" {

s32 __dl__7TObjectFPv(void *);
s32 __dt__7TObjectFv(void *, s32);

extern void* __vt__17TWindowOptionCtrl[];

void *__dt__17TWindowOptionCtrlFv(TWindowOptionCtrl *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(void **)((s8 *)arg0 + 0x18) = (void *) __vt__17TWindowOptionCtrl;
        arg0->apply_selection_change();
        if ((u32) arg0->m_44 != 0U) {
            TWindow__close((u8 *)(*(void **)((s8 *)arg0 + 0x44)));
            arg0->m_44 = 0U;
        }
        if ((u32) arg0->m_40 != 0U) {
            ((TWindowSubComCard *)(*(void **)((s8 *)arg0 + 0x40)))->close();
            arg0->m_40 = 0U;
        }
        if ((u32) arg0->m_3c != 0U) {
            TWindow__close((u8 *)(*(void **)((s8 *)arg0 + 0x3C)));
            arg0->m_3c = 0U;
        }
        if ((u32) arg0->m_38 != 0U) {
            TWindow__close((u8 *)(*(void **)((s8 *)arg0 + 0x38)));
            arg0->m_38 = 0U;
        }
        if ((u32) arg0->m_34 != 0U) {
            TWindow__close((u8 *)(*(void **)((s8 *)arg0 + 0x34)));
            arg0->m_34 = 0U;
        }
        if ((u32) arg0->m_30 != 0U) {
            TWindow__close((u8 *)(*(void **)((s8 *)arg0 + 0x30)));
            arg0->m_30 = 0U;
        }
        if ((u32) arg0->m_2c != 0U) {
            TWindow__close((u8 *)(*(void **)((s8 *)arg0 + 0x2C)));
            arg0->m_2c = 0U;
        }
        if ((u32) arg0->m_28 != 0U) {
            TWindow__close((u8 *)(*(void **)((s8 *)arg0 + 0x28)));
            arg0->m_28 = 0U;
        }
        __dt__7TObjectFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

}
