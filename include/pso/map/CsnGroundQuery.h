#ifndef PSO_MAP_CSN_GROUND_QUERY_H
#define PSO_MAP_CSN_GROUND_QUERY_H
#include "types.h"
#include <stddef.h>
#include <dolphin/mtx.h>

// One collision contact in the 32-entry ground and segment query pool.
struct CsnContact {
    Vec point;
    Vec normal;
    u32 flags;

    CsnContact();
    void clear();
};

// Ground and segment queries return this shared result when they find a contact.
struct CsnHit {
    u32 hit_mask;        // (inferred) bit 0: ground contact, others: per-flag contacts
    CsnContact *contact;

    CsnHit();
    void reset();
};

typedef char CsnContactSize[sizeof(CsnContact) == 0x1C ? 1 : -1];
typedef char CsnContactNormalOffset[offsetof(CsnContact, normal) == 0xC ? 1 : -1];
typedef char CsnHitSize[sizeof(CsnHit) == 8 ? 1 : -1];
typedef char CsnHitContactOffset[offsetof(CsnHit, contact) == 4 ? 1 : -1];

extern "C" {
CsnHit *csnVecterUnder(const Vec *origin, u32 mask);

// Both helpers query from source.y + 20. On a miss, an aliased source and
// destination retain that raised position.
s32 adjust_point_to_ground(const Vec *source, Vec *destination);
s32 adjust_point_to_ground_with_normal(const Vec *source, Vec *destination, Vec *normal);
}
#endif
