#include "types.h"
#include "pso/misc/TShopArmorListWindow.h"

extern "C" {

int populate_judgment_item_list(void*);

void TShopArmorListWindow::save_and_close() { save_cursor_selection(); reset_list(); populate_judgment_item_list(this); clamp_selection_to_valid_entry(); }

}
