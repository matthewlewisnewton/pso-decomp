#include "types.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/misc/TQuestVmDownLoadServer.h"
#include "pso/system/memory.h"

void *operator new(size_t size) { return xmalloc(size); }

extern "C" {
void TAdSinglePlyChrSelectGC::safe_free(u32 address) {
    if (address != 0U) {
        xfree((void *)address);
    }
}

}
