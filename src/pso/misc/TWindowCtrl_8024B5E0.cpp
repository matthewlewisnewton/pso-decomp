#include "types.h"
#include "pso/misc/TWindowCtrl.h"

s32 TWindowCtrl::open_default(u16 speaker, s32 text) {
    return TWindowCtrl::open(speaker, text, 15);
}
