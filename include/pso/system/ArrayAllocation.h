#ifndef PSO_SYSTEM_ARRAY_ALLOCATION_H
#define PSO_SYSTEM_ARRAY_ALLOCATION_H

#include "types.h"

// Calling these functions only obtains or releases raw storage. Use a new
// expression when construction of a typed array is required.
void *operator new[](size_t bytes);
void operator delete[](void *storage);

#endif
