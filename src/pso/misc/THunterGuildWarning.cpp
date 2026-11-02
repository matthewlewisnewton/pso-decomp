#include "types.h"
#include "pso/THunterGuildWarning.h"

extern "C" {

void THunterGuildWarning__sub_80211774(THunterGuildWarning *, s32);
void THunterGuildWarning__sub_802119CC(THunterGuildWarning *);

extern const char *lbl_805D3648;
extern THunterGuildWarning *THunterGuildWarning__instance;

}
THunterGuildWarning::THunterGuildWarning(TObject *object, s32 arg2) : TObject(object) {
    m_name = lbl_805D3648;
    m_warning_type = arg2;
    m_timer = 90;
    THunterGuildWarning__sub_802119CC(this);
    THunterGuildWarning__sub_80211774(this, m_warning_type);
    THunterGuildWarning__instance = this;
}
