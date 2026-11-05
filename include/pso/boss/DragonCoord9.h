#ifndef PSO_BOSS_DRAGONCOORD9_H
#define PSO_BOSS_DRAGONCOORD9_H
#include "types.h"

// Nine floats. Both dragon bosses embed two of them. The constructor calls
// reset_coords (the zeroing store sequence) and the destructor is the empty
// deleting destructor: it frees the block only when the flag is positive,
// and both bosses pass -1.
struct DragonCoord9 {
    f32 v[9];
    DragonCoord9();
    ~DragonCoord9();
};
typedef char DragonCoord9_size[sizeof(DragonCoord9) == 0x24 ? 1 : -1];

#endif
