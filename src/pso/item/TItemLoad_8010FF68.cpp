#include "types.h"
#include "pso/misc/TLobby.h"
#include "pso/TItemLoad.h"
#include "pso/item/ItemArchiveReader.h"

void ItemArchiveReader::close() {
    if (handle != NULL) {
        ADXF_Close(handle);
        handle = NULL;
        sectors = 0;
    }
}
