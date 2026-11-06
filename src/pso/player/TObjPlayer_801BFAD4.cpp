#include "types.h"
#include "pso/player/TObjPlayer_801BFAD4.h"
#include "pso/system/memory.h"

extern s32 lbl_804C3E38[];

void *TObjPlayer__sub_801BFAD4(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 4) = lbl_804C3E38;
        if (arg1 > 0) {
            ::operator delete(arg0);
        }
    }
    return arg0;
}
