#ifndef PSO_SYSTEM_BML_RESOURCE_DESCRIPTOR_H
#define PSO_SYSTEM_BML_RESOURCE_DESCRIPTOR_H

#include "types.h"
#include <stddef.h>

struct BmlResourceDescriptor {
    const char *archive_filename;
    const char *const *model_filenames;
    const char *const *motion_filenames;
    s16 model_count;
    s16 motion_count;

    void copy_from(const BmlResourceDescriptor &other);
};

typedef char BmlResourceDescriptor_size[sizeof(BmlResourceDescriptor) == 0x10 ? 1 : -1];
typedef char BmlResourceDescriptor_archive_offset[offsetof(BmlResourceDescriptor, archive_filename) == 0 ? 1 : -1];
typedef char BmlResourceDescriptor_models_offset[offsetof(BmlResourceDescriptor, model_filenames) == 4 ? 1 : -1];
typedef char BmlResourceDescriptor_motions_offset[offsetof(BmlResourceDescriptor, motion_filenames) == 8 ? 1 : -1];
typedef char BmlResourceDescriptor_model_count_offset[offsetof(BmlResourceDescriptor, model_count) == 0xC ? 1 : -1];
typedef char BmlResourceDescriptor_motion_count_offset[offsetof(BmlResourceDescriptor, motion_count) == 0xE ? 1 : -1];

#endif
