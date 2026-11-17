#include "pso/player/PlayerLevelTable.h"
#include "pso/item/InventoryEntryCopy.h"
#include "types.h"
#include "pso/unk/text_802C3AC0.h"
extern "C" {
void *get_ptr_4__10TObjPlayerFv(void *);
void init_class_starting_inventory(void *arg0) {
    u8 *p = (u8 *) arg0;
    char v = ((char *)p)[0x3A1];
    p[0] = 5;
    copy_item_entry_array(p[0], (Entry_802C3A50 *)get_class_starting_inventory(v), (Entry_802C3A50 *)get_ptr_4__10TObjPlayerFv(p));
}

}
