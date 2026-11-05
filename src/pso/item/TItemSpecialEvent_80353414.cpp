#include "types.h"
#include "pso/TMainTask.h"
#include "pso/item/TItemSpecialEvent.h"

TItemSpecialEvent *TItemSpecialEvent::create(u8 *item) {
    if (item != NULL) {
        return new TItemSpecialEvent(tl_05, item);
    }
    return NULL;
}
