#include "types.h"
#include "pso/unk/text_80278964.h"
#include "pso/unk/text_802789E0.h"
#include "pso/misc/TWindowShortListCtrl.h"

extern "C" {

int clamp_selection_to_valid_entry__20TShopArmorListWindowFv(void*);
int save_cursor_selection__20TShopArmorListWindowFv(void*);
int reset_list__20TShopArmorListWindowFv(void*);
int build_shop_item_list__10TObjPlayerFv(void*);

void TWindowShortListCtrl::update_variant_a() { save_cursor_selection__20TShopArmorListWindowFv(this); reset_list__20TShopArmorListWindowFv(this); refresh_battle_stat_list(this); clamp_selection_to_valid_entry__20TShopArmorListWindowFv(this); }

void TWindowShortListCtrl::update_variant_b() { save_cursor_selection__20TShopArmorListWindowFv(this); reset_list__20TShopArmorListWindowFv(this); fn_802789E0((u8 *)this); clamp_selection_to_valid_entry__20TShopArmorListWindowFv(this); }

void TWindowShortListCtrl::update_variant_c() { save_cursor_selection__20TShopArmorListWindowFv(this); reset_list__20TShopArmorListWindowFv(this); build_shop_item_list__10TObjPlayerFv(this); clamp_selection_to_valid_entry__20TShopArmorListWindowFv(this); }

}
