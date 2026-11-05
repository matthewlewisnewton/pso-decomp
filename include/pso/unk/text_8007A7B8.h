#ifndef PSO_UNK_TEXT_8007A7B8_H
#define PSO_UNK_TEXT_8007A7B8_H

#include "pso/map/CsnResult.h"

// The initializer at 0x8007A6C8 constructs 32 contacts with 0x1C stride.
// The constructor at 0x8007A7B8 calls the clearing routine at 0x8007A7E8.
typedef CsnContact Record_8007A7B8;

typedef char Record_8007A7B8_size[sizeof(Record_8007A7B8) == 0x1C ? 1 : -1];

extern "C" {
extern Record_8007A7B8 lbl_804FF9C0[32];
void clear_velocity_vectors__10TObjPlayerFv(Record_8007A7B8 *record);
}

#endif
