#ifndef PSO_MISC_TCHECKMEMORYCARDSTATE_H
#define PSO_MISC_TCHECKMEMORYCARDSTATE_H

#include "pso/misc/TCheckMemoryCard.h"

struct CheckMemoryCardPosition { f32 x, y; };
typedef void (TCheckMemoryCard::*CheckMemoryCardAction)();
struct CheckMemoryCardActionPair {
    CheckMemoryCardAction enter;
    CheckMemoryCardAction update;
};
typedef char CheckMemoryCardPosition_size[sizeof(CheckMemoryCardPosition) == 8 ? 1 : -1];
typedef char CheckMemoryCardActionPair_size[sizeof(CheckMemoryCardActionPair) == 24 ? 1 : -1];
typedef char CheckMemoryCardActionPair_update[offsetof(CheckMemoryCardActionPair, update) == 12 ? 1 : -1];

// These objects remain supplied by the original native fallback. The position
// describes its leading two floats; PMF templates and scalar padding stay there.
extern const CheckMemoryCardPosition lbl_80477DB4, lbl_80477DBC;
extern const CheckMemoryCardPosition lbl_804EF8D8;
extern const f32 lbl_805D6D98;
extern CheckMemoryCardActionPair lbl_804EF940[4];

#endif
