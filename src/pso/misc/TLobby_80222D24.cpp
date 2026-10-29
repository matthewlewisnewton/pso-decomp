#include "types.h"
#include "pso/misc/TLobby_80222D24.h"
#include "pso/unk/text_800F9B84.h"
#include "pso/misc/TLobby.h"
#include "pso/ui/Language.h"

#pragma readonly_strings on

extern "C" {
const char *text_shop_rel_name_table[6] = { "TextShopJapanese.rel", "TextShopEnglish.rel", "TextShopGerman.rel", "TextShopFrench.rel", "TextShopSpanish.rel", NULL };
}


#pragma fp_contract on
#pragma fp_contract on
extern "C" {
extern const char *text_shop_rel_name_table[6];
extern s32 lbl_805D6238;
extern u32 lbl_805D6258;
s32 is_split_screen();
void TLobby::free_singleton() {
    if ((u32) lbl_805D6258 != 0U) {
        TLobby::free_nodes_with_id((u32)((void*)lbl_805D6258));
        lbl_805D6258 = 0U;
    }
}
void TLobby::create_named_lobby_object() {
    if (((s32) lbl_805D6238 < 0) || ((s32) lbl_805D6238 > 9)) {
        lbl_805D6238 = 0;
    }
    (*(s32 *)&lbl_805D6258) = create_named_object(((s32 *)text_shop_rel_name_table)[current_language]);
}
#pragma push
#pragma scheduling off
s32 TShopGenerator__sub_80222DAC(s32 arg0) {
    return ((is_split_screen() - 1) == 0) ? arg0 : 0;
}
#pragma pop

#pragma push
#pragma scheduling off
#pragma pop

}
