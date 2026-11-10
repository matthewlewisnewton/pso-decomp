#ifndef PSO_SYSTEM_CVFS_DEVICE_CALLBACKS_H
#define PSO_SYSTEM_CVFS_DEVICE_CALLBACKS_H

#include "types.h"

// CVFS passes its mutable local path buffer to a device's size query.
// Open returns the backend's opaque handle, not a particular backend record.
typedef s32 CvFsGetFileSizeFunction(char *name);
typedef void *CvFsOpenFunction(const char *name, s32 entry, s32 mode);

#endif
