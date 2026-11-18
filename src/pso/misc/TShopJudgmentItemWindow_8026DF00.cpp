#include "types.h"
#include "pso/misc/TUnk_804D0948.h"
#include "pso/misc/TShopJudgmentItemWindow_8026DF00.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TShopJudgmentItemWindow.h"

extern "C" {
s32 TShopJudgmentItemWindow__sub_80267F9C(void *, int);
extern s32 TShopJudgmentItemWindow__item_list_rect_table[];
extern s32 local_client_id;

u8 *create_item_list_window(s32 arg0, s32 arg1, s32 arg2) {
    s32 camera_id;
    camera_id = TCameraCtrl::get_camera_id();
    switch (camera_id) {
    case 1:
        TShopJudgmentItemWindow__sub_80267F9C(TShopJudgmentItemWindow__item_list_rect_table, arg1);
        break;
    case 2:
        TShopJudgmentItemWindow__sub_80267F9C((void *) ((u8 *)TShopJudgmentItemWindow__item_list_rect_table + 8), arg1);
        break;
    case 3:
    case 4:
        TShopJudgmentItemWindow__sub_80267F9C((void *) ((u8 *)TShopJudgmentItemWindow__item_list_rect_table + 0x10), arg1);
        break;
    }
    return (u8 *)new TUnk_804D0948(arg0, (u32)arg1, arg2);
}

void TShopJudgmentItemWindow::open_default(s32 a) {
    create_item_list_window(a, 0x40, local_client_id);
}

}
