#include "types.h"
#include "pso/ui/TAdChrSelPlyPlateGC.h"

extern "C" {

s32 __dl__7TObjectFPv(void *);
s32 __dt__7TObjectFv(void *, s32);

extern s32 lbl_804E0B10[];
extern u32 ad_chr_sel_ply_plate_instance;

void *__dt__19TAdChrSelPlyPlateGCFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = lbl_804E0B10;
        if ((u32) ad_chr_sel_ply_plate_instance != 0U) {
            ad_chr_sel_ply_plate_instance = 0U;
        }
        __dt__7TObjectFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

}
