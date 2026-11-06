#include "pso/TItemDropSub.h"

extern s32 TItemDropSub__instance;

TItemDropSub::~TItemDropSub() {
    TItemDropSub__instance = 0;
}
