#include "types.h"
#include "pso/misc/TWindowCtrlMain_8024EEF8.h"
#include "pso/misc/TWindowCtrlMain.h"
#include "pso/misc/TWindowKeyBoardSoft.h"

extern u32 soft_keyboard_instance;
void TWindowCtrlMain::free_keyboard_soft() {
    if ((u32) soft_keyboard_instance != 0U) {
        TWindowKeyBoardSoft::free_singleton((u32)((void*)soft_keyboard_instance), (s16)1);
        soft_keyboard_instance = 0U;
    }
}
void TWindowCtrlMain__sub_8024EF30(void) { (*(int *)&soft_keyboard_instance) = 0; }
