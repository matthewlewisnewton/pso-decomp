#include "types.h"
#include "pso/unk/text_803DE7E0.h"
#include "pso/unk/text_803DE8BC.h"

extern void *sys_heap_handle;
extern "C" {
void OSFreeToHeap(void *heap, void *ptr);
void *OSAllocFromHeap(void *heap, u32 size);
void move_data__6TLobbyFPCvUl(void *, void *, void *);
}

#pragma push
#pragma scheduling off
void *sys_alloc(u32 size) {
    return OSAllocFromHeap(sys_heap_handle, size);
}
#pragma pop

#pragma push
#pragma scheduling off
void free_to_sys_heap(void *ptr) {
    OSFreeToHeap(sys_heap_handle, ptr);
}
#pragma pop

void *sys_calloc(s32 arg0, s32 arg1) {
    void *p = OSAllocFromHeap(sys_heap_handle, arg0 * arg1);
    fill_memory(p, 0, arg0 * arg1);
    return p;
}

void *fn_803DE960(void *arg0, void *size) {
    void *p = OSAllocFromHeap(sys_heap_handle, (u32)size);
    move_data__6TLobbyFPCvUl(p, arg0, size);
    OSFreeToHeap(sys_heap_handle, arg0);
    return p;
}
