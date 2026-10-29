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
#endif
