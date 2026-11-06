#include "types.h"
#include "pso/unk/text_802C6DD4.h"

extern "C" {
u8 * TAdChrSelPlyPlateGC__ct(void *, s32, s32);
u8 *__nw__7TObjectFUl(s32);
extern u8 *ad_chr_sel_ply_plate_instance;
u8 *fn_802C6F20(s32 arg0, s32 arg1) {
    u8 *temp_r3;
    u8 *var_r0;
    if ((void *) ad_chr_sel_ply_plate_instance != NULL) {
        return NULL;
    }
    temp_r3 = (u8 *)(__nw__7TObjectFUl(0x538));
    var_r0 = temp_r3;
    if (var_r0 != NULL) {
        var_r0 = (u8 *)(TAdChrSelPlyPlateGC__ct(temp_r3, arg0, arg1));
    }
    ad_chr_sel_ply_plate_instance = var_r0;
    return var_r0;
}

}
