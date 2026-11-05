#include "types.h"
#include "pso/THunterGuildWarning.h"

extern "C" {

extern const char *lbl_805D3648;
extern THunterGuildWarning *THunterGuildWarning__instance;

}
THunterGuildWarning::THunterGuildWarning(TObject *object, s32 mode) : TObject(object) {
    m_name = lbl_805D3648;
    m_warning_type = mode;
    m_timer = 90;
    sub_802119CC();
    sub_80211774(m_warning_type);
    THunterGuildWarning__instance = this;
}
