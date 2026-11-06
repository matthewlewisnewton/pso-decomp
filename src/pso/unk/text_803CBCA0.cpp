#include "pso/system/AdxmThreadStorage.h"
#include "pso/unk/text_803CBCA0.h"

#include "types.h"
extern "C" {
s32 OSGetCurrentThread();
void OSSuspendThread(void *);
void OSSetThreadPriority(s32, s32);
extern s32 lbl_805D7594;
extern s32 lbl_805D75AC;
void fn_803CBCA0(void) {
    s32 t;
    if (--lbl_805D7594 == 0) {
        t = OSGetCurrentThread();
        OSSuspendThread(&adxm_busy_wait_thread);
        OSSetThreadPriority(t, lbl_805D75AC);
    }
}

}
