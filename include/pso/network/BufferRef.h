#ifndef PSO_NETWORK_BUFFERREF_H
#define PSO_NETWORK_BUFFERREF_H

#include "types.h"
#include <stddef.h>

struct NetBufferRef {
    u32 value;
    u8 kind;
    u8 padding[3];
};

typedef char NetBufferRef_size_check[(sizeof(NetBufferRef) == 8) ? 1 : -1];
typedef char NetBufferRef_kind_check[(offsetof(NetBufferRef, kind) == 4) ? 1 : -1];

/* Native descriptor discriminants. The distinction between kinds 1 and 3 is
 * not inferred from the old TLobby placeholder names. */
extern "C" {
void NetBufferRefInitKind1(NetBufferRef *ref, s32 value);
void NetBufferRefInitKind3(NetBufferRef *ref, s32 value);
void NetBufferRefInitKind4(NetBufferRef *ref, s32 value);
}

#endif
