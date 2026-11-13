#include "types.h"
#include "pso/system/Adxf.h"
#include "pso/unk/TLobby.h"
#include "pso/item/TItemLoad.h"
#include "pso/item/ItemArchiveReader.h"

void ItemArchiveReader::close() {
    if (handle != NULL) {
        ADXF_Close(handle);
        handle = NULL;
        sectors = 0;
    }
}
