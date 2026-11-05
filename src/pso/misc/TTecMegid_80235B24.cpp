#include "pso/system/SoundEffect.h"
#include "types.h"
#include "pso/misc/TUnk_804CCA90.h"
#include "pso/misc/TTecMegid_80235B24.h"
#include "pso/object/TObject_80019A50.h"

#include "pso/misc/TTecMegid.h"

extern "C" {


void TUnk_804CCA90::run_task() {
    u8 *arg0 = (u8 *)this;
    *(s16 *)((s8 *)arg0 + 0x1E) = (s16) (*(s16 *)((s8 *)arg0 + 0x1E) + 1);
    if ((s16) *(s16 *)((s8 *)arg0 + 0x1E) > (s16) *(s16 *)((s8 *)arg0 + 0x1C)) {
        play_sound_effect((s32)(*(s32 *)((s8 *)arg0 + 0x20)), (const Vec *)(arg0 + 0x24), 0, 0);
        queue_destruction__7TObjectFv(arg0);
    }
}


}
TUnk_804CCA90::~TUnk_804CCA90() {

}
