#include "types.h"
#include "pso/misc/TCheckMemoryCard.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

TCheckMemoryCard *TAdSinglePlyChrSelectGC::create_check_memory_card(TObject *parent, u32 arg1, u32 arg2) {
    TCheckMemoryCard *o;
    o = new TCheckMemoryCard(parent, arg1, arg2, 0);
    return o;
}
