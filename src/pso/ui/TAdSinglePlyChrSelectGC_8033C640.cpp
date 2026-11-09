#include "types.h"
#include "pso/misc/TCheckMemoryCard.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

void *TAdSinglePlyChrSelectGC::create_check_memory_card(void *arg0, void *arg1, void *arg2) {
    void *o;
    o = new TCheckMemoryCard((TObject *)arg0, (void *)arg1, (void *)arg2, (void *)0);
    return o;
}
