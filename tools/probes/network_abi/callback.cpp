// Synthetic compiler control; never compiled or linked by the game build.
// Preserve both recovered slot views and the lookup, aliasing expression,
// search and null return. NO_ARGUMENT changes only callback types/invocation.
#include <stddef.h>
#include "types.h"

struct ProducerSlot;
struct ConsumerSlot;
#if NO_ARGUMENT
typedef void (*ProducerCallback)(void);
typedef void (*ConsumerCallback)(void);
#else
typedef void (*ProducerCallback)(ProducerSlot *);
typedef void (*ConsumerCallback)(ConsumerSlot *);
#endif
struct ProducerSlot {
    s32 active;
    u32 key;
    u8 opaque_thread[0x310];
    ProducerCallback func;
    u32 stack_size;
    u8 *stack;
    u8 remaining[4];
};
struct ConsumerSlot {
    s32 active;
    u32 key;
    u8 opaque_thread[0x310];
    ConsumerCallback fn;
    u8 remaining[0xc];
};
typedef char producer_size[sizeof(ProducerSlot) == 0x328 ? 1 : -1];
typedef char consumer_size[sizeof(ConsumerSlot) == 0x328 ? 1 : -1];
typedef char producer_offset[offsetof(ProducerSlot, func) == 0x318 ? 1 : -1];
typedef char consumer_offset[offsetof(ConsumerSlot, fn) == 0x318 ? 1 : -1];

#pragma pool_data off
extern "C" {
extern ProducerSlot *slots;
extern u16 slot_count;
void *current_thread(void);

void *callback(void *) {
    u32 key = (u32)current_thread();
    ConsumerSlot *p;
    u16 n = slot_count;
    ConsumerSlot *base = (*(ConsumerSlot **)&slots);
    s32 i;
    p = base;
    for (i = 0; i < n; i++) {
        if (key == p->key) break;
        p++;
    }
    if (i >= n) return NULL;
    {
        ConsumerSlot *e = &base[i];
#if NO_ARGUMENT
        e->fn();
#else
        e->fn(e);
#endif
    }
    return NULL;
}
}
