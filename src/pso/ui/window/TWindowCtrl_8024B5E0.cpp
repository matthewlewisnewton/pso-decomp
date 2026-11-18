#include "types.h"
#include "pso/ui/window/TWindowCtrl.h"

s32 TWindowCtrl::open_default(u16 speaker, s32 text) {
    return open(speaker, text, 15);
}
