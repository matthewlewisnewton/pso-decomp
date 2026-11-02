#ifndef PSO_UNK_TEXT_8007A7B8_H
#define PSO_UNK_TEXT_8007A7B8_H

#include "types.h"

// One record of the 32-entry array at lbl_804FF9C0 (0x380 bytes total,
// 0x1C stride). fn_8007A6C8 builds that array through __construct_array with
// TObjPlayer__sub_8007A7B8 as the element constructor. A record is reset to
// six 0.0f words followed by one zero s32 by the clearing routine at
// 0x8007A7E8, which the constructor calls for each entry. The storage is a
// record pool, not an array of live TObjPlayer objects.
struct Record_8007A7B8 {
    f32 field_0x00;
    f32 field_0x04;
    f32 field_0x08;
    f32 field_0x0c;
    f32 field_0x10;
    f32 field_0x14;
    s32 field_0x18;
};

typedef char Record_8007A7B8_size[sizeof(Record_8007A7B8) == 0x1C ? 1 : -1];

extern "C" {
Record_8007A7B8 *TObjPlayer__sub_8007A7B8(Record_8007A7B8 *record);
}

#endif
