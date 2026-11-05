#include "types.h"
#include "pso/misc/TWindowSubComCard_80265410.h"
#include "pso/misc/TWindowSubComCard.h"

extern "C" {

s32 TWindowSubComCardList__sub_802757AC(s32, const void *, s32, s32, s32);
s32 __nw__7TObjectFUl(s32);

s32 TWindowSubComCard::create_card_list(const void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_r3;

    fn_80266378(7);
    var_r3 = __nw__7TObjectFUl(0xA0);
    if (var_r3 != 0) {
        var_r3 = TWindowSubComCardList__sub_802757AC(var_r3, arg0, arg1, arg2, arg3);
    }
    return var_r3;
}

}
