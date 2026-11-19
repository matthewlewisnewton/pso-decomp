#ifndef PSO_SYSTEM_MEMORY_H
#define PSO_SYSTEM_MEMORY_H

#include "types.h"

void move_data(void *dst, const void *src, u32 bytes);
void move_words(void *dst, const void *src, s32 count);

void safe_free(void *allocation);
void xfree(void *p);
void * xmalloc(u32 bytes);

#endif
