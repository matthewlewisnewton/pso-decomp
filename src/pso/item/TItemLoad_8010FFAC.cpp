#include "types.h"
#include "pso/unk/text_803CC294.h"
#include "pso/item/TItemLoad.h"
#include "pso/item/ItemArchiveReader.h"

extern "C" {

u32 ADXF_OpenAfs(s32, s32);

AdxfHandle *ItemArchiveReader::open(s32 arg1) {
    AdxfHandle *file;
    if (mode == 1) {
        close();
        handle = (AdxfHandle *)ADXF_OpenAfs(partition, arg1);
        file = handle;
        if (file != NULL) {
            sectors = ADXF_GetFsizeSct((u8 *)file);
        }
    }
    return handle;
}

}
