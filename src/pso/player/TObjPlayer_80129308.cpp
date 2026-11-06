#include "types.h"
#include "pso/player/TObjPlayer_80129308.h"

extern "C" {

void construct_srank_weapon(void *);

extern s32 lbl_804A4138[];

void *TObjPlayer__sub_80129308(void *arg0) {
    construct_srank_weapon(arg0);
    *(s32 **)((s8 *)arg0 + 0x18) = lbl_804A4138;
    *(u32 *)((s8 *)arg0 + 0x1FC) = 0;
    return arg0;
}

}
