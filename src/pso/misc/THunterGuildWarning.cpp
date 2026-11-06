#include "types.h"
#include "pso/THunterGuildWarning.h"

extern "C" {

void THunterGuildWarning__sub_80211774(void *, void *);
void THunterGuildWarning__sub_802119CC(void *);

extern void *lbl_805D3648;
extern void * THunterGuildWarning__instance;

}
THunterGuildWarning::THunterGuildWarning(TObject *object, void *arg2) : TObject(object) {
    *(void * *)&this->m_name = lbl_805D3648;
    *(void **)((s8 *)this + 0x1C) = arg2;
    *(u32 *)((s8 *)this + 0x20) = 90;
    THunterGuildWarning__sub_802119CC(this);
    THunterGuildWarning__sub_80211774(this, *(void **)((s8 *)this + 0x1C));
    THunterGuildWarning__instance = this;
}
