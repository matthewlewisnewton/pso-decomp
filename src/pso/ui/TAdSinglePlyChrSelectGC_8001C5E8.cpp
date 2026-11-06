#include "types.h"
#include "pso/ui/TAdSinglePlyChrSelectGC_8001C5E8.h"
#include "pso/misc/TLoadCtrl.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

extern u8 lbl_805D4A78;

u8 TAdSinglePlyChrSelectGC::get_chr_select_state() {
    return lbl_805D4A78;
}

extern s32 guild_card_save_file_block_count;

s32 TAdSinglePlyChrSelectGC__sub_8001C5F0(void) {
    return guild_card_save_file_block_count;
}

extern void *TLoadCtrl__instance;

void TLoadCtrl::set_field1C(s32 arg0) {
    if ((void *) TLoadCtrl__instance != NULL) {
        *(s32 *)((s8 *)TLoadCtrl__instance + 0x1C) = arg0;
    }
}
