#ifndef PSO_ITEM_INVENTORYENTRYCOPY_H
#define PSO_ITEM_INVENTORYENTRYCOPY_H
#include "types.h"

// Provisional 0x1C-byte inventory entry view owned by the copy provider.
struct Entry_802C3A50;
extern "C" void copy_item_entry_array(s32 count, Entry_802C3A50 *source, Entry_802C3A50 *destination);
#endif
