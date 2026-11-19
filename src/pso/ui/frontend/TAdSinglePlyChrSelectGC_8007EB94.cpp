#include "types.h"
#include "pso/system/memory.h"

void *operator new(size_t size) {
    return xmalloc(size);
}

void safe_free(void *allocation) {
    if (allocation != NULL) {
        xfree(allocation);
    }
}
