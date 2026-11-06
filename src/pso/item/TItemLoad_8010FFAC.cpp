#include "types.h"
#include "pso/unk/text_803CC294.h"
#include "pso/TItemLoad.h"
#include "pso/item/ItemArchiveReader.h"

extern "C" {

AdxfHandle *ItemArchiveReader::open(s32 arg1) {
    AdxfHandle *file;
    if (mode == 1) {
        close();
        handle = ADXF_OpenAfs(partition, arg1);
        file = handle;
        if (file != NULL) {
            sectors = ADXF_GetFsizeSct(file);
        }
    }
    return handle;
}

}
