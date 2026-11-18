#include "types.h"
#include "pso/misc/TWindowSubEquipKind.h"
#include "pso/unk/text_80278E48.h"

extern "C" {
s32 TShopJudgmentItemWindow__sub_80267F9C(void *, int);
u8 *create_equip_kind_window(s32 arg0, s32 arg1, s32 arg2) {
    TShopJudgmentItemWindow__sub_80267F9C((void *)arg1, 0x1F);
    return (u8 *)new TWindowSubEquipKind((void *)arg0, arg2);
}

}
