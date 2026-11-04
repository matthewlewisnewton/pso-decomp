#ifndef PSO_UNK_TEXT_8020B47C_H
#define PSO_UNK_TEXT_8020B47C_H

#include "types.h"

// The four-word header has two known stream offsets; buffer ownership is unknown.
struct FloorFlagsBuffer {
    u32 object_offset;
    u32 word_04;
    u32 enemy_offset;
    u32 word_0c;
};

void fn_8020B588(FloorFlagsBuffer *buffer);
extern "C" void TLobby__sub_8020B47C(FloorFlagsBuffer *buffer);
// The caller supplies the packet length in r4; the wrapper does not use it.
void fn_8020BF68(FloorFlagsBuffer *buffer, u16 length);

#endif
