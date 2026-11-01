#include "types.h"
#include "pso/misc/TWindowCtrlMain_8024EEF8.h"
#include "pso/misc/TWindowCtrlMain.h"
#include "pso/misc/TWindowKeyBoardSoft_8024E68C.h"

extern TWindowDrawContext *soft_keyboard_instance;
void TWindowCtrlMain::free_keyboard_soft() {
    if (soft_keyboard_instance != NULL) {
        free_singleton__19TWindowKeyBoardSoftFUls(soft_keyboard_instance, (s16)1);
        soft_keyboard_instance = NULL;
    }
}
void TWindowCtrlMain__sub_8024EF30(void) { soft_keyboard_instance = NULL; }
