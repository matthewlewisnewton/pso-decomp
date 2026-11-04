#include "types.h"
#include "pso/THunterGuildWarning.h"

extern "C" {

extern const char *lbl_805D3648;
extern THunterGuildWarning *THunterGuildWarning__instance;

}
THunterGuildWarning::THunterGuildWarning(TObject *object, void *arg2) : TObject(object) {
    m_name = lbl_805D3648;
    m_warning_type = (s32)arg2;
    m_timer = 90;
    sub_802119CC();
    sub_80211774(m_warning_type);
    THunterGuildWarning__instance = this;
}
