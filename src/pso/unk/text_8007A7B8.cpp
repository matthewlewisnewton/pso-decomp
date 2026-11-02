#include "types.h"
#include "pso/unk/text_8007A7B8.h"

extern "C" {

// Clearing routine at 0x8007A7E8; resets one 0x1C-byte record. The exported
// name is the original mangled symbol; the definition lives in the linked
// unit src/pso/player/TObjPlayer_8007A7E8.cpp.
void clear_velocity_vectors__10TObjPlayerFv(Record_8007A7B8 *record);

Record_8007A7B8 *TObjPlayer__sub_8007A7B8(Record_8007A7B8 *record) {
    clear_velocity_vectors__10TObjPlayerFv(record);
    return record;
}

}
