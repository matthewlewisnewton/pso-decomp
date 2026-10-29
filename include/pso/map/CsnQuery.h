#ifndef PSO_MAP_CSNQUERY_H
#define PSO_MAP_CSNQUERY_H

#include "types.h"
#include <stddef.h>
#include <dolphin/mtx.h>

struct CsnModel;
struct CsnVector {
    f32 x, y, z;
};

struct CsnGroup {
    CsnModel* model;
    CsnVector center;
    f32 radius;
    u32 flags;
};

typedef char CsnVectorSize[sizeof(CsnVector) == 0xC ? 1 : -1];
typedef char CsnGroupSize[sizeof(CsnGroup) == 0x18 ? 1 : -1];
typedef char CsnGroupCenterOffset[offsetof(CsnGroup, center) == 4 ? 1 : -1];
typedef char CsnGroupRadiusOffset[offsetof(CsnGroup, radius) == 0x10 ? 1 : -1];
typedef char CsnGroupFlagsOffset[offsetof(CsnGroup, flags) == 0x14 ? 1 : -1];

CsnGroup* select_ground_query_groups(CsnVector* origin, u32 mask);

// The polygon a segment query hit: the hit point and the polygon normal.
struct CsnContact {
    Vec point;
    Vec normal;
    u32 flags;
};

// The result csnVector returns (one static record, NULL when nothing is hit).
struct CsnHit {
    u8 pad_0[0x4];
    CsnContact *contact;
    u8 pad_8[0x38];
};

extern "C" {
CsnHit *csnVector(const Vec *from, const Vec *to, u32 mask);
}

extern "C" {
void TObjPlayer__sub_80079108(void);
void TObjPlayer__sub_8007910C(void);
void TObjPlayer__sub_80079110(void);
void TObjPlayer__sub_80079114(void);
s32 TObjPlayer__sub_80079118(s32 *_w0);
void TObjPlayer__sub_8007911C(void);
void TObjPlayer__sub_80079120(s32 _w0);
void TObjPlayer__sub_80079124(void *_w0, void *_w1);
s32 *csnLookAt(s32 arg0, s32 arg1);
s32 *csnVecterUnder(s32 origin, s32 mask);
s32 *csnVectorUnder(Vec *arg0, u32 *arg1, s32 arg2);
s32 get_csn_group_flags(u8 arg0);
}
s32 prepare_wall_query_polygons(void *arg0, f32 r, s32 mask);
void *query_prepared_wall_polygons(void *self);
s32 query_wall_segment(void *arg0, void *arg1, void *arg2, s32 arg3);
CsnGroup *select_ground_query_groups(CsnVector *origin, u32 mask);

#endif
