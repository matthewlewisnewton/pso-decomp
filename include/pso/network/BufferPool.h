#ifndef PSO_NETWORK_BUFFERPOOL_H
#define PSO_NETWORK_BUFFERPOOL_H

#include "types.h"
#include <stddef.h>

struct Seg_80415690 {
    s16 owner;
    u16 offset;
    u16 len;
};

struct Ent_80415690 {
    u8 *buf;
    s32 free_segs;
    s32 free_bytes;
    Seg_80415690 segs[8];
};

struct Pool_80415690 {
    s16 count;
    s16 size;
    Ent_80415690 *ents;
    u8 *data;
    u8 unknown_0c[4]; // Preserve the assigned extent; no meaning inferred.
};

typedef char NetPoolSegmentSize[(sizeof(Seg_80415690) == 6) ? 1 : -1];
typedef char NetPoolEntrySize[(sizeof(Ent_80415690) == 0x3c) ? 1 : -1];
typedef char NetPoolSegmentsOffset[(offsetof(Ent_80415690, segs) == 0xc) ? 1 : -1];
typedef char NetPoolStateSize[(sizeof(Pool_80415690) == 0x10) ? 1 : -1];
typedef char NetPoolEntriesOffset[(offsetof(Pool_80415690, ents) == 4) ? 1 : -1];
typedef char NetPoolDataOffset[(offsetof(Pool_80415690, data) == 8) ? 1 : -1];

extern "C" void init_buffer_desc_a__6TLobbyFv(Pool_80415690 *pool);

#endif
