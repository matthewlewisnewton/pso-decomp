#include "pso/item/ItemArchiveReader.h"

AdxfHandle *ItemArchiveReader::open(s32 file) {
    if (mode == 1) {
        close();
        handle = ADXF_OpenAfs(partition, file);
        if (handle != NULL) {
            sectors = ADXF_GetFsizeSct(handle);
        }
    }
    return handle;
}
