#ifndef PSO_ITEM_ITEMARCHIVEREADER_H
#define PSO_ITEM_ITEMARCHIVEREADER_H

#include "pso/system/Adxf.h"
#include <stddef.h>

// Non-task reader storage embedded at the start of the item archive loaders.
struct ItemArchiveReader {
    void *buffer;
    AdxfHandle *handle;
    s32 partition;
    s32 sectors;
    s32 mode;

    s32 get_status();
    void close();
    AdxfHandle *open(s32 file);
    void read(s32 destination);
};

typedef char ItemArchiveReaderSize[sizeof(ItemArchiveReader) == 0x14 ? 1 : -1];
typedef char ItemArchiveReaderHandleOffset[offsetof(ItemArchiveReader, handle) == 4 ? 1 : -1];
typedef char ItemArchiveReaderSectorsOffset[offsetof(ItemArchiveReader, sectors) == 0xC ? 1 : -1];

#endif
