#include "pso/TItemMenuCtrl.h"

extern s32 TItemMenuCtrl__instance;

TItemMenuCtrl::~TItemMenuCtrl() {
    TItemMenuCtrl__instance = 0;
}
