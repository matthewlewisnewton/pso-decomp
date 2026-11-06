#include "types.h"
#include "pso/misc/TPlayerBattleCtrl4P.h"

extern "C" {

u32 __nw__7TObjectFUl(int);
s32 strncpy(void *, void *, int);

extern s32 tl_00;
extern u8 *TPlayerBattleCtrl4P__instance;

void TPlayerBattleCtrl4P::init_instance_with_text(s32 arg0, s32 arg1) {
    if ((void *) TPlayerBattleCtrl4P__instance == NULL) {
        u32 mem = __nw__7TObjectFUl(0x2A0);
        if (mem != 0U) {
            ((TPlayerBattleCtrl4P *)mem)->construct((TObject*)tl_00);
        }
    }
    if ((void *) TPlayerBattleCtrl4P__instance != NULL) {
        strncpy(TPlayerBattleCtrl4P__instance + 0x38, (void *)arg1, 0x200);
        *(s32 *)((s8 *)TPlayerBattleCtrl4P__instance + 0x1C) = arg0;
    }
}

}
