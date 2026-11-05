#include "types.h"
#include "pso/unk/text_8014618C.h"
#include "pso/ui/TAdDialingGC_80328DB0.h"
#include "pso/ui/TAdDialingGC.h"
#include "pso/misc/TLobby.h"

#pragma readonly_strings on

extern "C" {
const char *lbl_805D41B0 = "TAdDialingGC";
}


extern "C" {

s32 __ct__7TObjectFP7TObject();

extern s32 __vt__12TAdDialingGC[];
extern const char *lbl_805D41B0;
extern void *TAdDialingGC__instance;

void *TAdDialingGC__ct(TAdDialingGC *ad_dialing_gc) {
    __ct__7TObjectFP7TObject();
    *(s32 **)((s8 *)ad_dialing_gc + 0x18) = __vt__12TAdDialingGC;
    *(s32 *)((s8 *)ad_dialing_gc + 0) = (s32) ((s32)lbl_805D41B0);
    TAdDialingGC__instance = ad_dialing_gc;
    if (TLobby::is_state_active() != 0) {
        ad_dialing_gc->m_1c = 1;
    } else if (TLobby__sub_8014618C() == 1) {
        ad_dialing_gc->m_1c = 2;
    } else {
        ad_dialing_gc->m_1c = 0;
    }
    ad_dialing_gc->m_20 = 0;
    ad_dialing_gc->m_24 = 0;
    ad_dialing_gc->m_28 = 0;
    ad_dialing_gc->m_30 = 0;
    ad_dialing_gc->m_68 = 0;
    ad_dialing_gc->m_a0 = 0;
    ad_dialing_gc->m_a4 = 0;
    return ad_dialing_gc;
}

}
