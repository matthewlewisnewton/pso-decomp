#include "types.h"
#include "pso/ui/TObjBagWarnWin_8006EED4.h"
#include "pso/TObjBagWarnWin.h"

extern "C" {

void __ct__7TObjectFP7TObject(void *);

extern s32 __vt__14TObjBagWarnWin[];
extern void *lbl_805D2848;

void *__ct__14TObjBagWarnWinFv(void *bag_warn_win) {
    __ct__7TObjectFP7TObject(bag_warn_win);
    *(s32 **)((s8 *)bag_warn_win + 0x18) = __vt__14TObjBagWarnWin;
    *(void * *)&((TObjBagWarnWin *)bag_warn_win)->m_name = lbl_805D2848;
    *(u32 *)((s8 *)bag_warn_win + 0x1C) = 0;
    *(u32 *)((s8 *)bag_warn_win + 0xA0) = 0;
    return bag_warn_win;
}

}
