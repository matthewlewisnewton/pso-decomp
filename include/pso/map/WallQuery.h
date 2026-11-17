#ifndef PSO_MAP_WALLQUERY_H
#define PSO_MAP_WALLQUERY_H
#include "pso/map/CsnResult.h"
struct WallQuery {
    s32 count;
    f32 radius;
    u32 mask;
    f32 origin[3];
    Vec *offsets;
};
typedef char WallQuerySize[sizeof(WallQuery) == 0x1C ? 1 : -1];
typedef char WallQueryOriginOffset[offsetof(WallQuery, origin) == 0xC ? 1 : -1];
extern "C" {
CsnHit *csnVector(const Vec *from, const Vec *to, u32 mask);
CsnQueryResult *query_wall_radial(WallQuery *query);
}
CsnQueryResult *query_prepared_wall_polygons(void *query);
#endif
