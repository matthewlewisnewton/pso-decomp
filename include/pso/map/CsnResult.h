#ifndef PSO_MAP_CSNRESULT_H
#define PSO_MAP_CSNRESULT_H

#include "types.h"
#include <stddef.h>
#include <dolphin/mtx.h>

// One entry in the 32-contact pool at 0x804FF9C0.
struct CsnContact {
    Vec point;
    Vec normal;
    u32 flags;
    CsnContact();
};

// The two-word result at 0x80500140 and the base of the query result below.
struct CsnHit {
    s32 hit;
    CsnContact *contact;
    CsnHit();
};

// The extended result at 0x80500148 adds the selected index and distance.
struct CsnQueryResult : CsnHit {
    s32 index;
    f32 best;
    CsnQueryResult();
};

typedef char CsnContactSize[sizeof(CsnContact) == 0x1C ? 1 : -1];
typedef char CsnContactNormalOffset[offsetof(CsnContact, normal) == 0xC ? 1 : -1];
typedef char CsnHitContactOffset[offsetof(CsnHit, contact) == 4 ? 1 : -1];
typedef char CsnHitSize[sizeof(CsnHit) == 8 ? 1 : -1];
typedef char CsnQueryResultSize[sizeof(CsnQueryResult) == 0x10 ? 1 : -1];

extern "C" {
// The object is in .bss, but this declaration prevents small-data addressing
// in consumers, whose original instructions use a full address relocation.
__declspec(section ".data") extern CsnHit lbl_80500140;
extern CsnQueryResult csn_query_map_object;
}

#endif
