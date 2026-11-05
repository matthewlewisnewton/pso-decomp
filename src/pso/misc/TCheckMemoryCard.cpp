#include "types.h"
#include "pso/misc/TCheckMemoryCardState.h"
#include "pso/misc/TWindowSubComCard_80244774.h"

struct Base_8033C4E0_8033C420 { char pad[0x18]; };
struct VObj_8033C4E0_8033C420 : Base_8033C4E0_8033C420 { virtual void m0(int); };

void TCheckMemoryCard::render() { }

void TCheckMemoryCard::run_task() {
    CheckMemoryCardAction action;
    CheckMemoryCardActionPair *record;
    m_3c = 0;
    m_28 = sub_8033BB14();
    if (m_28 & 1) {
        set_state(0);
    }
    record = &lbl_804EF940[m_20];
    action = record->update;
    if (action != 0) {
        (this->*action)();
    }
    m_38 = m_38 - 1;
    if ((s32)m_38 < 0) {
        m_38 = 0;
    }
}

TCheckMemoryCard::~TCheckMemoryCard() {
    void *temp_r3;
    temp_r3 = this->m_30;
    if (temp_r3 != NULL) {
        if (temp_r3 != NULL) {
            ((VObj_8033C4E0_8033C420 *)temp_r3)->m0(1);
        }
        this->m_30 = NULL;
    }
    if ((u32) *(u32 *)((s8 *)this + 0x34) != 0U) {
        TWindow__close((u8 *)(*(void **)((s8 *)this + 0x34)));
        *(u32 *)((s8 *)this + 0x34) = 0U;
    }
}
extern void *TCheckMemoryCard__name;
TCheckMemoryCard::TCheckMemoryCard(TObject *object, u32 arg2, u32 arg3, u32 arg4) : TObject(object) {
    m_name = (const char *)TCheckMemoryCard__name;
    m_48 = arg2;
    m_1c = arg4;
    m_4c = arg3;
    // Inherited original debt: reset reads m_20 before initialization. This
    // receiver repair preserves that behavior; defined initialization is unresolved.
    reset();
}

TCheckMemoryCard *fn_8033C5E4(TObject *parent, u32 arg1, u32 arg2) {
    return new TCheckMemoryCard(parent, arg1, arg2, 1);
}
