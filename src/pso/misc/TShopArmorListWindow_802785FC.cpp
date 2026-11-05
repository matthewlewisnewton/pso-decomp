#include "types.h"
#include "pso/misc/TShopArmorListWindow.h"

extern "C" {

int build_usable_item_list(void*);

void TShopArmorListWindow::close_list() { save_cursor_selection(); reset_list(); build_usable_item_list(this); clamp_selection_to_valid_entry(); }

}
