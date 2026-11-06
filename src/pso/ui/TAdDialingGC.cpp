#include "types.h"
#include "pso/ui/TAdDialingGC.h"

struct RecoveredGlobal_80328D50___vt__12TAdDialingGC {
    s32 value;
    u8 remaining[0x14];
};

extern "C" {
u8 * __dt__7TObjectFv(void *, s16);
void __dl__7TObjectFPv(s32);
extern RecoveredGlobal_80328D50___vt__12TAdDialingGC __vt__12TAdDialingGC;
extern s32 TAdDialingGC__instance;
u8 *__dt__12TAdDialingGCFv(u8 *arg0, s16 arg1);
int TAdDialingGC__sub_80328B20(void*);

void TAdDialingGC::render() { TAdDialingGC__sub_80328B20(this); render_if_flag_set(); draw_if_flag_set(); update(); }

s32 update_dial_state__12TAdDialingGCFv();
s32 update_state__12TAdDialingGCFv();
s32 update_dial_state__12TAdDialingGCFl();

void TAdDialingGC::run_task() {

    switch (this->m_1c) {
    case 0:
        update_dial_state__12TAdDialingGCFl();
        break;
    case 1:
        update_state__12TAdDialingGCFv();
        break;
    case 2:
        update_dial_state__12TAdDialingGCFv();
        break;
    }
    update_selection();
    this->m_24 = (this->m_24 + 1);
}
typedef char RecoveredGlobal_80328D50___vt__12TAdDialingGC_size[sizeof(RecoveredGlobal_80328D50___vt__12TAdDialingGC) == 0x18 ? 1 : -1];
u8 *__dt__12TAdDialingGCFv(u8 *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = &__vt__12TAdDialingGC.value;
        TAdDialingGC__instance = 0;
        __dt__7TObjectFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv((s32) arg0);
        }
    }
    return arg0;
}

}
