#ifndef PSO_MAP_CSN_GROUND_QUERY_H
#define PSO_MAP_CSN_GROUND_QUERY_H
#include "types.h"
#include <dolphin/mtx.h>

struct CsnGroundSurface {
    Vec point;
    Vec normal;
    u32 flags;
    u8 unknown_1c[0x1c];
    Vec point_38;
    u8 unknown_44[0x10];
    Vec point_54;
};

struct CsnGroundHit {
    u32 flags;
    CsnGroundSurface *surface;
};
struct CsnHit;

extern "C" {
CsnHit *csnVecterUnder(const Vec *origin, u32 mask);

// Query from source.y + 20. The source and destination may alias; on a miss,
// the final copy then leaves the shared position raised by 20.
s32 adjust_point_to_ground(const Vec *source, Vec *destination);
s32 adjust_point_to_ground_with_normal(const Vec *source, Vec *destination, Vec *normal);
}
#endif
