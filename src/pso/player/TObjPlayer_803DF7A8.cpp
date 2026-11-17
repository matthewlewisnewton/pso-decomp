


#include "types.h"
#include "pso/unk/text_803DA798.h"
#include "pso/player/TObjPlayer_803DF7A8.h"
#include "pso/player/TObjPlayer.h"


struct RecoveredGlobal_803E1D1C_lbl_804FC780 {
    s32 value;
    u8 remaining[0x24];
};




struct Vec_803E1B1C { f32 x, y, z; };


typedef struct TexObj_803E1D90 { u32 dummy[8]; } TexObj_803E1D90;

typedef struct TexHdr_803E1D90 {
    u32 f0;
    s32 format;
    u32 f8;
    u32 fC;
    u32 width;
    u32 height;
    u32 f18;
    u32 flags;
    void *image;
} TexHdr_803E1D90;

typedef struct TexInfo_803E1D90 { u32 f0; u32 f4; u32 tlut; TexHdr_803E1D90 *hdr; } TexInfo_803E1D90;

typedef struct TexEnt_803E1D90 { u32 f0; u32 f4; TexInfo_803E1D90 *info; } TexEnt_803E1D90;

typedef struct TexList_803E1D90 { TexEnt_803E1D90 *ents; } TexList_803E1D90;

typedef struct Ctx_803E1D90 { u8 pad[0x20]; TexList_803E1D90 *list; } Ctx_803E1D90;


struct V_803E18C0 { f32 x, y, z; };

struct Line_803E18C0 { V_803E18C0 o; V_803E18C0 d; };


struct Faces_803E0ED4 { s32 v[6][4]; };

extern "C" {
s32 GXLoadPosMtxImm(void *, int);
extern RecoveredGlobal_803E1D1C_lbl_804FC780 gx_pos_mtx_index_table;
extern s32 current_matrix;
extern const f32 lbl_805E1038;
extern const f32 lbl_805E103C;
extern s32 tex_matrix_id_table[];
void GXLoadTexMtxImm(void *mtx, u32 id, s32 type);
void OSPanic(const char *, int, const char *, ...);
extern char lbl_804FC7F8[];
extern char lbl_805D46F0[4];
void calc_bounds_min_max__10TObjPlayerFPvPvPv(struct Vec_803E1B1C *pts, struct Vec_803E1B1C *mn, struct Vec_803E1B1C *mx);
void Dolphin_GXInitTexObj(TexObj_803E1D90 *, void *, u16, u16, s32, s32, s32, u8);
void GXInitTexObjCI(TexObj_803E1D90 *, void *, u16, u16, s32, s32, s32, u8, u32);
void GXLoadTexObj(TexObj_803E1D90 *, s32);
extern s32 list_texture_map_table[];
extern TexObj_803E1D90 list_texture_tex_obj;
extern Ctx_803E1D90 *current_render_context;
extern const f32 lbl_805E1020;
extern const f32 lbl_805E1024;
extern const f64 lbl_805E1028;
extern const f64 lbl_805E1030;
f32 project_point_onto_line(V_803E18C0 *p, Line_803E18C0 *l, V_803E18C0 *out);
s32 TObjPlayer__sub_803DFB1C(Vec_803E1B1C *a, Vec_803E1B1C *b);
s32 __SITransfer(Vec_803E1B1C *a, Vec_803E1B1C *b);
extern const Faces_803E0ED4 box_face_corner_index_table;
s32 test_box_overlap__10TObjPlayerFPvPv(Vec_803E1B1C *boxA, Vec_803E1B1C *boxB);
s32 TObjPlayer::test_aabb_overlap(u8 *arg1, u8 *arg2, u8 *arg3) {
    u8 *arg0 = (u8 *)this;
    if (*(f32 *)((s8 *)arg1 + 0) < *(f32 *)((s8 *)arg2 + 0)) {
        return 0;
    }
    if (*(f32 *)((s8 *)arg0 + 0) > *(f32 *)((s8 *)arg3 + 0)) {
        return 0;
    }
    if (*(f32 *)((s8 *)arg1 + 4) < *(f32 *)((s8 *)arg2 + 4)) {
        return 0;
    }
    if (*(f32 *)((s8 *)arg0 + 4) > *(f32 *)((s8 *)arg3 + 4)) {
        return 0;
    }
    if (*(f32 *)((s8 *)arg1 + 8) < *(f32 *)((s8 *)arg2 + 8)) {
        return 0;
    }
    return (u32) __cntlzw(*(f32 *)((s8 *)arg0 + 8) > *(f32 *)((s8 *)arg3 + 8)) >> 5;
}


#pragma push
#pragma fp_contract off


struct CollisionPoint { f32 x,y,z; };
struct CollisionSphere { CollisionPoint center; f32 radius; };
extern const s32 box_face_vertex_index_table[6][4],box_edge_adjacent_face_table[6][4];
extern const f32 lbl_805E1000,lbl_805E1018,lbl_805E101C;
extern const f64 lbl_805E1008,lbl_805E1010;
static inline CollisionPoint collisionSubtract(CollisionPoint a,CollisionPoint b) {
    CollisionPoint r={a.x-b.x,a.y-b.y,a.z-b.z};return r;
}
static inline f32 collisionDot(CollisionPoint a,CollisionPoint b) {
    return a.z*b.z+(a.x*b.x+a.y*b.y);
}
static inline f32 collisionRoot(f32 squared) {
    if(squared>lbl_805E1000) {
        f64 inverse=__frsqrte(squared);
        inverse=(lbl_805E1008*inverse)*(lbl_805E1010-squared*(inverse*inverse));
        inverse=(lbl_805E1008*inverse)*(lbl_805E1010-squared*(inverse*inverse));
        inverse=(lbl_805E1008*inverse)*(lbl_805E1010-squared*(inverse*inverse));
        return (f32)(squared*inverse);
    }
    return squared;
}
static inline CollisionPoint collisionScale(CollisionPoint a,f32 scale) {
    CollisionPoint r={a.x*scale,a.y*scale,a.z*scale};return r;
}
static inline CollisionPoint collisionProject(CollisionPoint a,CollisionPoint v,f32 scale) {
    CollisionPoint r={a.x+v.x*scale,a.y+v.y*scale,a.z+v.z*scale};return r;
}
static inline int collisionNormalEquals(CollisionPoint a,CollisionPoint b) {
    return (f32)__fabs(a.x-b.x)<=lbl_805E101C && (f32)__fabs(a.y-b.y)<=lbl_805E101C && (f32)__fabs(a.z-b.z)<=lbl_805E101C;
}
static inline CollisionPoint collisionNormalize(CollisionPoint p) {
    return collisionScale(p,lbl_805E1018/collisionRoot(collisionDot(p,p)));
}

#pragma use_lmw_stmw off
struct Point2_803E0CC8 { f32 u, v; };
s32 TObjPlayer__sub_803DF9D0(Point2_803E0CC8 *a, Point2_803E0CC8 *b);
f32 TObjPlayer__sub_803DF840(Point2_803E0CC8 *p, Point2_803E0CC8 *a, Point2_803E0CC8 *b);
extern const f32 lbl_805E0FFC;
extern const f32 lbl_805E0FD8, lbl_805E0FDC, lbl_805E0FE0, lbl_805E0FF8;
extern const f64 lbl_805E0FE8, lbl_805E0FF0;

f32 TObjPlayer__sub_803DF840(Point2_803E0CC8 *p, Point2_803E0CC8 *a, Point2_803E0CC8 *b) {
    f32 lineU;
    f32 lineV;
    f32 lineC;
    if ((f32)__fabs(p->u - a->u) < 0.025f) {
        lineU = 1.0f;
        lineV = 0.0f;
        lineC = -p->u;
    } else {
        lineU = a->v - p->v;
        lineV = -(a->u - p->u);
        lineC = (-p->u * lineU) - (p->v * lineV);
    }
    f64 distance = lineC + (lineU * b->u + lineV * b->v);
    distance = __fabs(distance);
    distance = (f32)distance;
    f32 normalLength = lineU * lineU + lineV * lineV;
    if (normalLength > 0.0f) {
        volatile f32 rounded;
        f64 inverse = __frsqrte(normalLength);
        inverse = (0.5 * inverse) * (3.0 - normalLength * (inverse * inverse));
        inverse = (0.5 * inverse) * (3.0 - normalLength * (inverse * inverse));
        inverse = (0.5 * inverse) * (3.0 - normalLength * (inverse * inverse));
        rounded = (f32)(normalLength * inverse);
        normalLength = rounded;
    }
    distance = (f32)distance / normalLength;
    f32 squaredLength = (p->u - a->u) * (p->u - a->u) + (p->v - a->v) * (p->v - a->v);
    f32 length;
    if (squaredLength > 0.0f) {
        volatile f32 rounded;
        f64 inverse = __frsqrte(squaredLength);
        inverse = (0.5 * inverse) * (3.0 - squaredLength * (inverse * inverse));
        inverse = (0.5 * inverse) * (3.0 - squaredLength * (inverse * inverse));
        inverse = (0.5 * inverse) * (3.0 - squaredLength * (inverse * inverse));
        rounded = (f32)(squaredLength * inverse);
        length = rounded;
    } else {
        length = squaredLength;
    }
    return 0.5f * ((f32)distance * length);
}

s32 TObjPlayer__sub_803DF9D0(Point2_803E0CC8 *a, Point2_803E0CC8 *b) {
    Point2_803E0CC8 *p;
    Point2_803E0CC8 *inner;
    Point2_803E0CC8 *outer;
    f32 areaA;
    f32 areaB;
    f32 limit;
    s32 i;
    areaA = TObjPlayer__sub_803DF840(a, a + 1, a + 2) + TObjPlayer__sub_803DF840(a, a + 2, a + 3);
    areaB = TObjPlayer__sub_803DF840(b, b + 1, b + 2) + TObjPlayer__sub_803DF840(b, b + 2, b + 3);
    if (areaA < areaB) {
        inner = a;
        outer = b;
        limit = areaB;
    } else {
        inner = b;
        outer = a;
        limit = areaA;
    }
    for (i = 0, p = inner, limit = 1.025f * limit; i < 4; p++, i++) {
        if (TObjPlayer__sub_803DF840(p, outer, outer + 1) + TObjPlayer__sub_803DF840(p, outer + 1, outer + 2) +
                TObjPlayer__sub_803DF840(p, outer + 2, outer + 3) + TObjPlayer__sub_803DF840(p, outer + 3, outer) <
            limit) {
            return 1;
        }
    }
    return 0;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(4)
static inline f32 sqrtf_803DFB1C(f32 x) {
    volatile f32 y;
    if (x > 0.0f) {
        f64 guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

// The scoped optimization setting preserves the native loop/register layout.
// Adapted from upstream PR #309; see docs/evidence/quad-sphere-collision-wip.md.
#pragma push
#pragma opt_loop_invariants off
s32 TObjPlayer__sub_803DFB1C(Vec_803E1B1C *a, Vec_803E1B1C *b) {
    Point2_803E0CC8 pa[4];
    Point2_803E0CC8 pb[4];
    s32 hitXY;
    s32 hitXZ;
    s32 hitYZ;
    s32 inXY;
    s32 inXZ;
    s32 inYZ;
    s32 i;
    s32 j;
    s32 result;
    f32 lengthSqAYZ;
    f32 prevAvXZ;
    f32 prevAuYZ;
    f32 prevBuXY;
    f32 prevBvXY;
    f32 prevBvXZ;
    f32 curAvXZ;
    f32 prevAuXZ;
    f32 curBuXY;
    f32 curBvXY;
    f32 curBvXZ;
    f32 lengthSqAXY;
    f32 lengthSqAXZ;
    f32 hitUXY;
    f32 interAXY;
    f32 prevAvYZ;
    f32 prevBuXZ;
    f32 slopeAXZ;
    f32 slopeAXY;
    f32 curAuYZ;
    f32 curBuXZ;
    f32 curAuXZ;

    hitXY = 0;
    hitXZ = 0;
    hitYZ = 0;
    {
        s32 vertA;
        s32 vertB;
        s32 parallel;
        s32 onA;
        s32 onB;
        f32 prevAu;
        f32 prevAv;
        f32 curAu;
        f32 curAv;
        f32 lineAu;
        f32 toPrev;
        f32 toCur;
        f32 length;
        f32 hitV;
        f32 slopeB;
        f32 interB;
        f32 lineBu;

        prevAu = a[3].x;
        prevAv = a[3].y;
        for (i = 0; i < 4; i++) {
            curAu = a[i].x;
            curAv = a[i].y;
            if (prevAu < curAu - 0.025f || prevAu > 0.025f + curAu) {
                slopeAXY = (curAv - prevAv) / (curAu - prevAu);
                interAXY = prevAv - slopeAXY * prevAu;
                vertA = 0;
            } else {
                lineAu = prevAu;
                vertA = 1;
            }
            prevBuXY = b[3].x;
            prevBvXY = b[3].y;
            for (j = 0; j < 4; j++) {
                parallel = 0;
                lengthSqAXY = (prevAu - curAu) * (prevAu - curAu) + (prevAv - curAv) * (prevAv - curAv);
                curBuXY = b[j].x;
                curBvXY = b[j].y;
                if (prevBuXY < curBuXY - 0.025f || prevBuXY > 0.025f + curBuXY) {
                    slopeB = (curBvXY - prevBvXY) / (curBuXY - prevBuXY);
                    interB = prevBvXY - slopeB * prevBuXY;
                    vertB = 0;
                } else {
                    lineBu = prevBuXY;
                    vertB = 1;
                }
                if (vertA == 0 && vertB == 0) {
                    if (slopeAXY < slopeB - 0.025f || slopeAXY > 0.025f + slopeB) {
                        hitUXY = (interB - interAXY) / (slopeAXY - slopeB);
                        hitV = interAXY + slopeAXY * hitUXY;
                    } else {
                        parallel = 1;
                    }
                } else if (vertB == 0) {
                    hitUXY = lineAu;
                    hitV = interB + slopeB * hitUXY;
                } else if (vertA == 0) {
                    hitUXY = lineBu;
                    hitV = interAXY + slopeAXY * hitUXY;
                } else {
                    parallel = 1;
                }
                if (parallel == 0) {
                    onA = 0;
                    onB = 0;
                    toPrev = sqrtf_803DFB1C((prevAu - hitUXY) * (prevAu - hitUXY) + (prevAv - hitV) * (prevAv - hitV));
                    toCur = sqrtf_803DFB1C((curAu - hitUXY) * (curAu - hitUXY) + (curAv - hitV) * (curAv - hitV));
                    length = sqrtf_803DFB1C(lengthSqAXY);
                    if (0.025f + length >= toPrev + toCur - 0.025f) {
                        onA = 1;
                    }
                    toPrev = sqrtf_803DFB1C((prevBuXY - hitUXY) * (prevBuXY - hitUXY) + (prevBvXY - hitV) * (prevBvXY - hitV));
                    toCur = sqrtf_803DFB1C((curBuXY - hitUXY) * (curBuXY - hitUXY) + (curBvXY - hitV) * (curBvXY - hitV));
                    length = sqrtf_803DFB1C((prevBuXY - curBuXY) * (prevBuXY - curBuXY) + (prevBvXY - curBvXY) * (prevBvXY - curBvXY));
                    if (0.025f + length >= toPrev + toCur - 0.025f) {
                        onB = 1;
                    }
                    if (onA != 0 && onB != 0) {
                        hitXY = 1;
                        break;
                    }
                }
                prevBuXY = curBuXY;
                prevBvXY = curBvXY;
            }
            if (hitXY != 0) {
                break;
            }
            prevAu = curAu;
            prevAv = curAv;
        }
    }
    {
        s32 vertA;
        s32 vertB;
        s32 parallel;
        s32 onA;
        s32 onB;
        f32 lineAu;
        f32 toPrev;
        f32 toCur;
        f32 length;
        f32 interA;
        f32 hitU;
        f32 hitV;
        f32 slopeB;
        f32 interB;
        f32 lineBu;

        prevAuXZ = a[3].x;
        prevAvXZ = a[3].z;
        for (i = 0; i < 4; i++) {
            curAuXZ = a[i].x;
            curAvXZ = a[i].z;
            if (prevAuXZ < curAuXZ - 0.025f || prevAuXZ > 0.025f + curAuXZ) {
                slopeAXZ = (curAvXZ - prevAvXZ) / (curAuXZ - prevAuXZ);
                interA = prevAvXZ - slopeAXZ * prevAuXZ;
                vertA = 0;
            } else {
                lineAu = prevAuXZ;
                vertA = 1;
            }
            prevBuXZ = b[3].x;
            prevBvXZ = b[3].z;
            for (j = 0; j < 4; j++) {
                parallel = 0;
                lengthSqAXZ = (prevAuXZ - curAuXZ) * (prevAuXZ - curAuXZ) + (prevAvXZ - curAvXZ) * (prevAvXZ - curAvXZ);
                curBuXZ = b[j].x;
                curBvXZ = b[j].z;
                if (prevBuXZ < curBuXZ - 0.025f || prevBuXZ > 0.025f + curBuXZ) {
                    slopeB = (curBvXZ - prevBvXZ) / (curBuXZ - prevBuXZ);
                    interB = prevBvXZ - slopeB * prevBuXZ;
                    vertB = 0;
                } else {
                    lineBu = prevBuXZ;
                    vertB = 1;
                }
                if (vertA == 0 && vertB == 0) {
                    if (slopeAXZ < slopeB - 0.025f || slopeAXZ > 0.025f + slopeB) {
                        hitU = (interB - interA) / (slopeAXZ - slopeB);
                        hitV = interA + slopeAXZ * hitU;
                    } else {
                        parallel = 1;
                    }
                } else if (vertB == 0) {
                    hitU = lineAu;
                    hitV = interB + slopeB * hitU;
                } else if (vertA == 0) {
                    hitU = lineBu;
                    hitV = interA + slopeAXZ * hitU;
                } else {
                    parallel = 1;
                }
                if (parallel == 0) {
                    onA = 0;
                    onB = 0;
                    toPrev = sqrtf_803DFB1C((prevAuXZ - hitU) * (prevAuXZ - hitU) + (prevAvXZ - hitV) * (prevAvXZ - hitV));
                    toCur = sqrtf_803DFB1C((curAuXZ - hitU) * (curAuXZ - hitU) + (curAvXZ - hitV) * (curAvXZ - hitV));
                    length = sqrtf_803DFB1C(lengthSqAXZ);
                    if (0.025f + length >= toPrev + toCur - 0.025f) {
                        onA = 1;
                    }
                    toPrev = sqrtf_803DFB1C((prevBuXZ - hitU) * (prevBuXZ - hitU) + (prevBvXZ - hitV) * (prevBvXZ - hitV));
                    toCur = sqrtf_803DFB1C((curBuXZ - hitU) * (curBuXZ - hitU) + (curBvXZ - hitV) * (curBvXZ - hitV));
                    length = sqrtf_803DFB1C((prevBuXZ - curBuXZ) * (prevBuXZ - curBuXZ) + (prevBvXZ - curBvXZ) * (prevBvXZ - curBvXZ));
                    if (0.025f + length >= toPrev + toCur - 0.025f) {
                        onB = 1;
                    }
                    if (onA != 0 && onB != 0) {
                        hitXZ = 1;
                        break;
                    }
                }
                prevBuXZ = curBuXZ;
                prevBvXZ = curBvXZ;
            }
            if (hitXZ != 0) {
                break;
            }
            prevAuXZ = curAuXZ;
            prevAvXZ = curAvXZ;
        }
    }
    {
        s32 vertA;
        s32 vertB;
        s32 parallel;
        s32 onA;
        s32 onB;
        f32 lineAu;
        f32 toPrev;
        f32 toCur;
        f32 length;
        f32 curAv;
        f32 prevBu;
        f32 slopeA;
        f32 prevBv;
        f32 interA;
        f32 hitU;
        f32 hitV;
        f32 curBu;
        f32 curBv;
        f32 slopeB;
        f32 interB;
        f32 lineBu;

        prevAuYZ = a[3].y;
        prevAvYZ = a[3].z;
        for (i = 0; i < 4; i++) {
            curAuYZ = a[i].y;
            curAv = a[i].z;
            if (prevAuYZ < curAuYZ - 0.025f || prevAuYZ > 0.025f + curAuYZ) {
                slopeA = (curAv - prevAvYZ) / (curAuYZ - prevAuYZ);
                interA = prevAvYZ - slopeA * prevAuYZ;
                vertA = 0;
            } else {
                lineAu = prevAuYZ;
                vertA = 1;
            }
            prevBu = b[3].y;
            prevBv = b[3].z;
            for (j = 0; j < 4; j++) {
                parallel = 0;
                lengthSqAYZ = (prevAuYZ - curAuYZ) * (prevAuYZ - curAuYZ) + (prevAvYZ - curAv) * (prevAvYZ - curAv);
                curBu = b[j].y;
                curBv = b[j].z;
                if (prevBu < curBu - 0.025f || prevBu > 0.025f + curBu) {
                    slopeB = (curBv - prevBv) / (curBu - prevBu);
                    interB = prevBv - slopeB * prevBu;
                    vertB = 0;
                } else {
                    lineBu = prevBu;
                    vertB = 1;
                }
                if (vertA == 0 && vertB == 0) {
                    if (slopeA < slopeB - 0.025f || slopeA > 0.025f + slopeB) {
                        hitU = (interB - interA) / (slopeA - slopeB);
                        hitV = interA + slopeA * hitU;
                    } else {
                        parallel = 1;
                    }
                } else if (vertB == 0) {
                    hitU = lineAu;
                    hitV = interB + slopeB * hitU;
                } else if (vertA == 0) {
                    hitU = lineBu;
                    hitV = interA + slopeA * hitU;
                } else {
                    parallel = 1;
                }
                if (parallel == 0) {
                    onA = 0;
                    onB = 0;
                    toPrev = sqrtf_803DFB1C((prevAuYZ - hitU) * (prevAuYZ - hitU) + (prevAvYZ - hitV) * (prevAvYZ - hitV));
                    toCur = sqrtf_803DFB1C((curAuYZ - hitU) * (curAuYZ - hitU) + (curAv - hitV) * (curAv - hitV));
                    length = sqrtf_803DFB1C(lengthSqAYZ);
                    if (0.025f + length >= toPrev + toCur - 0.025f) {
                        onA = 1;
                    }
                    toPrev = sqrtf_803DFB1C((prevBu - hitU) * (prevBu - hitU) + (prevBv - hitV) * (prevBv - hitV));
                    toCur = sqrtf_803DFB1C((curBu - hitU) * (curBu - hitU) + (curBv - hitV) * (curBv - hitV));
                    length = sqrtf_803DFB1C((prevBu - curBu) * (prevBu - curBu) + (prevBv - curBv) * (prevBv - curBv));
                    if (0.025f + length >= toPrev + toCur - 0.025f) {
                        onB = 1;
                    }
                    if (onA != 0 && onB != 0) {
                        hitYZ = 1;
                        break;
                    }
                }
                prevBu = curBu;
                prevBv = curBv;
            }
            if (hitYZ != 0) {
                break;
            }
            prevAuYZ = curAuYZ;
            prevAvYZ = curAv;
        }
    }
    for (i = 0; i < 4; i++) {
        pa[i].u = a[i].x;
        pa[i].v = a[i].y;
        pb[i].u = b[i].x;
        pb[i].v = b[i].y;
    }
    inXY = TObjPlayer__sub_803DF9D0(pa, pb);
    for (i = 0; i < 4; i++) {
        pa[i].u = a[i].x;
        pa[i].v = a[i].z;
        pb[i].u = b[i].x;
        pb[i].v = b[i].z;
    }
    inXZ = TObjPlayer__sub_803DF9D0(pa, pb);
    for (i = 0; i < 4; i++) {
        pa[i].u = a[i].y;
        pa[i].v = a[i].z;
        pb[i].u = b[i].y;
        pb[i].v = b[i].z;
    }
    inYZ = TObjPlayer__sub_803DF9D0(pa, pb);
    result = 0;
    if ((hitXY != 0 || inXY != 0) && (hitXZ != 0 || inXZ != 0) && (hitYZ != 0 || inYZ != 0)) {
        result = 1;
    }
    return result;
}
#pragma pop
#pragma pop

s32 __SITransfer(Vec_803E1B1C *a, Vec_803E1B1C *b) {
    Point2_803E0CC8 pa[4];
    Point2_803E0CC8 pb[4];
    s32 mask = 0;
    s32 i;
    for (i = 0; i < 4; i++) {
        pa[i].u = a[i].x;
        pa[i].v = a[i].y;
        pb[i].u = b[i].x;
        pb[i].v = b[i].y;
    }
    if (TObjPlayer__sub_803DF9D0(pa, pb) != 0) {
        mask |= 4;
    }
    for (i = 0; i < 4; i++) {
        pa[i].u = a[i].x;
        pa[i].v = a[i].z;
        pb[i].u = b[i].x;
        pb[i].v = b[i].z;
    }
    if (TObjPlayer__sub_803DF9D0(pa, pb) != 0) {
        mask |= 2;
    }
    for (i = 0; i < 4; i++) {
        pa[i].u = a[i].y;
        pa[i].v = a[i].z;
        pb[i].u = b[i].y;
        pb[i].v = b[i].z;
    }
    if (TObjPlayer__sub_803DF9D0(pa, pb) != 0) {
        mask |= 1;
    }
    return mask;
}

s32 test_box_overlap__10TObjPlayerFPvPv(Vec_803E1B1C *boxA, Vec_803E1B1C *boxB) {
    Vec_803E1B1C qa[4];
    Vec_803E1B1C qb[4];
    Vec_803E1B1C mnA;
    Vec_803E1B1C mxA;
    Vec_803E1B1C mnB;
    Vec_803E1B1C mxB;
    s32 i;
    s32 j;
    s32 mask;
    s32 *fa;
    s32 *fb;
    int k;
    mask = 0;
    calc_bounds_min_max__10TObjPlayerFPvPvPv((struct Vec_803E1B1C *)(boxA), (struct Vec_803E1B1C *)(&mnA), (struct Vec_803E1B1C *)(&mxA));
    calc_bounds_min_max__10TObjPlayerFPvPvPv((struct Vec_803E1B1C *)(boxB), (struct Vec_803E1B1C *)(&mnB), (struct Vec_803E1B1C *)(&mxB));
    if (((TObjPlayer *)((u8 *)&mnA))->test_aabb_overlap((u8 *)&mxA, (u8 *)&mnB, (u8 *)&mxB) != 0) {
    Faces_803E0ED4 faces = box_face_corner_index_table;
    for (i = 0; i < 6; i++) {
        fa = faces.v[i];
        qa[0].x = boxA[fa[0]].x; qa[0].y = boxA[fa[0]].y; qa[0].z = boxA[fa[0]].z;
        qa[1].x = boxA[fa[1]].x; qa[1].y = boxA[fa[1]].y; qa[1].z = boxA[fa[1]].z;
        qa[2].x = boxA[fa[2]].x; qa[2].y = boxA[fa[2]].y; qa[2].z = boxA[fa[2]].z;
        qa[3].x = boxA[fa[3]].x; qa[3].y = boxA[fa[3]].y; qa[3].z = boxA[fa[3]].z;
        for (j = 0; j < 6; j++) {
            fb = faces.v[j];
            qb[0].x = boxB[fb[0]].x; qb[0].y = boxB[fb[0]].y; qb[0].z = boxB[fb[0]].z;
            qb[1].x = boxB[fb[1]].x; qb[1].y = boxB[fb[1]].y; qb[1].z = boxB[fb[1]].z;
            qb[2].x = boxB[fb[2]].x; qb[2].y = boxB[fb[2]].y; qb[2].z = boxB[fb[2]].z;
            qb[3].x = boxB[fb[3]].x; qb[3].y = boxB[fb[3]].y; qb[3].z = boxB[fb[3]].z;
            if (TObjPlayer__sub_803DFB1C(qa, qb) != 0) {
                return 1;
            }
            mask |= __SITransfer(qa, qb);
            if (mask == 7) {
                return 1;
            }
        }
    }
    return 0;
    }
    return 0;
}

// Sphere-contact candidate adapted from upstream PR #311; not yet an exact match.
struct FaceEdgeLoop { s32 v[5]; };
extern const FaceEdgeLoop lbl_8047E558;
inline const Faces_803E0ED4 *box_faces() { return (const Faces_803E0ED4 *)box_face_vertex_index_table; }
inline const Faces_803E0ED4 *box_adjacent() { return (const Faces_803E0ED4 *)box_edge_adjacent_face_table; }
inline const FaceEdgeLoop *box_order() { return &lbl_8047E558; }
#pragma push
#pragma dont_inline off
#pragma inline_depth(2)
#pragma opt_loop_invariants off
s32 test_box_sphere_contact(CollisionPoint *corners, CollisionSphere *sphere) {
    CollisionPoint boxMin;
    CollisionPoint boxMax;
    CollisionPoint sphereMin;
    CollisionPoint sphereMax;
    calc_bounds_min_max__10TObjPlayerFPvPvPv((Vec_803E1B1C *)corners, (Vec_803E1B1C *)&boxMin, (Vec_803E1B1C *)&boxMax);
    ((TObjPlayer *)sphere)->calc_bounds((u8 *)&sphereMin, (u8 *)&sphereMax);
    if (((TObjPlayer *)&boxMin)->test_aabb_overlap((u8 *)&boxMax, (u8 *)&sphereMin, (u8 *)&sphereMax) != 0) {
        Faces_803E0ED4 faces = *box_faces();
        CollisionPoint normals[6];
        Faces_803E0ED4 adjacentFaces = *box_adjacent();
        s32 i;
        s32 j;
        s32 inside = 1;
        f32 toFootX;
        f32 footX;
        f32 normalScale;
        f32 footY;
        f32 footZ;
        f32 nearX;
        f32 edgeX;
        f32 nearY;
        f32 planeT;
        f32 edgeY;
        f32 toFootY;
        f32 nearZ;
        f32 toFootScale;
        f32 planeDistSq;
        f32 edgeZ;
        f32 startY;
        f32 toEdgeX;
        f32 toEdgeY;
        f32 startX;
        f32 toEdgeScale;
        f32 toFootZ;
        f32 edgeT;
        f32 toEdgeZ;
        f32 startZ;
        for (i = 0; i < 6; i++) {
            s32 *face = faces.v[i];
            CollisionPoint *normal = &normals[i];
            normal->x = -((corners[face[1]].y - corners[face[0]].y) * (corners[face[2]].z - corners[face[0]].z) - (corners[face[1]].z - corners[face[0]].z) * (corners[face[2]].y - corners[face[0]].y));
            normal->y = -((corners[face[1]].z - corners[face[0]].z) * (corners[face[2]].x - corners[face[0]].x) - (corners[face[1]].x - corners[face[0]].x) * (corners[face[2]].z - corners[face[0]].z));
            normal->z = -((corners[face[1]].x - corners[face[0]].x) * (corners[face[2]].y - corners[face[0]].y) - (corners[face[1]].y - corners[face[0]].y) * (corners[face[2]].x - corners[face[0]].x));
            normalScale = lbl_805E1018 / sqrtf_803DFB1C(normal->z * normal->z + (normal->x * normal->x + normal->y * normal->y));
            normal->x *= normalScale;
            normal->y *= normalScale;
            normal->z *= normalScale;
        }
        for (i = 0; i < 6; i++) {
            s32 faceHit = 1;
            CollisionPoint *normal = &normals[i];
            s32 *face = faces.v[i];
            CollisionPoint *center = &sphere->center;
            f32 planeD = -(normal->z * corners[face[0]].z + (normal->x * corners[face[0]].x + normal->y * corners[face[0]].y));
            planeT = -(planeD + (center->z * normal->z + (center->x * normal->x + center->y * normal->y))) /
                     (normal->z * normal->z + (normal->x * normal->x + normal->y * normal->y));
            footX = center->x + planeT * normal->x;
            footY = center->y + planeT * normal->y;
            footZ = center->z + planeT * normal->z;
            f32 planeDist = sqrtf_803DFB1C((footZ - center->z) * (footZ - center->z) +
                                  ((footX - center->x) * (footX - center->x) + (footY - center->y) * (footY - center->y)));
            for (j = 0; j < 4; j++) {
                planeDistSq = planeDist * planeDist;
                FaceEdgeLoop loop = *box_order();
                s32 cornerOffset = loop.v[j] << 2;
                startX = corners[*(s32 *)((u8 *)face + cornerOffset)].x;
                CollisionPoint *end = &corners[face[loop.v[j + 1]]];
                edgeX = startX - end->x;
                edgeY = (startY = corners[*(s32 *)((u8 *)face + cornerOffset)].y) - end->y;
                edgeZ = (startZ = corners[*(s32 *)((u8 *)face + cornerOffset)].z) - end->z;
                edgeT = (edgeZ * (footZ - startZ) + (edgeX * (footX - startX) + edgeY * (footY - startY))) / (edgeZ * edgeZ + (edgeX * edgeX + edgeY * edgeY));
                nearX = edgeX * edgeT;
                nearX += startX;
                nearY = edgeY * edgeT;
                nearY += startY;
                nearZ = edgeZ * edgeT - -startZ;
                toEdgeX = nearX - footX;
                toEdgeY = nearY - footY;
                toEdgeZ = nearZ - footZ;
                toEdgeScale = lbl_805E1018 / sqrtf_803DFB1C(toEdgeZ * toEdgeZ + (toEdgeX * toEdgeX + toEdgeY * toEdgeY));
                toEdgeX *= toEdgeScale;
                toEdgeY *= toEdgeScale;
                toEdgeZ *= toEdgeScale;
                if ((f32)__fabs(normals[*(s32 *)((u8 *)adjacentFaces.v[i] + cornerOffset)].x - toEdgeX) <= lbl_805E101C &&
                    (f32)__fabs(normals[*(s32 *)((u8 *)adjacentFaces.v[i] + cornerOffset)].y - toEdgeY) <= lbl_805E101C &&
                    (f32)__fabs(normals[*(s32 *)((u8 *)adjacentFaces.v[i] + cornerOffset)].z - toEdgeZ) <= lbl_805E101C &&
                    sphere->radius >= planeDist) {
                    faceHit &= 1;
                } else if (planeDist <= sphere->radius) {
                    if ((footZ - nearZ) * (footZ - nearZ) + ((footX - nearX) * (footX - nearX) + (footY - nearY) * (footY - nearY)) <=
                        sphere->radius * sphere->radius - planeDistSq) {
                        faceHit &= 1;
                    } else {
                        faceHit = 0;
                    }
                } else {
                    faceHit = 0;
                }
            }
            if (faceHit != 0) {
                return 1;
            }
            toFootX = footX - center->x;
            toFootY = footY - center->y;
            toFootZ = footZ - center->z;
            toFootScale = lbl_805E1018 / sqrtf_803DFB1C(toFootZ * toFootZ + (toFootX * toFootX + toFootY * toFootY));
            toFootX *= toFootScale;
            toFootY *= toFootScale;
            toFootZ *= toFootScale;
            if ((f32)__fabs(normal->x - toFootX) <= lbl_805E101C && (f32)__fabs(normal->y - toFootY) <= lbl_805E101C &&
                (f32)__fabs(normal->z - toFootZ) <= lbl_805E101C) {
                inside &= 1;
            } else {
                inside = 0;
            }
        }
        if (inside != 0) {
            return 1;
        }
    }
    return 0;
}
#pragma pop

#pragma pop


__declspec(section ".sdata2") extern const f64 lbl_805E1040;
__declspec(section ".sdata2") extern const f64 lbl_805E1048;
}

s32 spheres_overlap(CollisionSphere_80155C54 *arg0, CollisionSphere_80155C54 *arg1) {
    f32 temp_f2;
    f32 temp_f3;
    f32 temp_f4;
    f32 temp_f5;
    temp_f3 = arg1->center.x - arg0->center.x;
    temp_f4 = arg1->center.y - arg0->center.y;
    temp_f2 = arg1->center.z - arg0->center.z;
    temp_f5 = arg0->radius + arg1->radius;
    return ((temp_f2 * temp_f2) + ((temp_f3 * temp_f3) + (temp_f4 * temp_f4))) <= (temp_f5 * temp_f5);
}


#pragma push
#pragma scheduling off

f32 project_point_onto_line(V_803E18C0 *p, Line_803E18C0 *l, V_803E18C0 *out) {
    f32 t;
    f32 x;
    f32 r;
    t = (l->d.z * (p->z - l->o.z) + (l->d.x * (p->x - l->o.x) + l->d.y * (p->y - l->o.y))) /
        (l->d.z * l->d.z + (l->d.x * l->d.x + l->d.y * l->d.y));
    if (out != NULL) {
        out->x = l->o.x + l->d.x * t;
        out->y = l->o.y + l->d.y * t;
        out->z = l->o.z + l->d.z * t;
        x = (p->z - out->z) * (p->z - out->z) + ((p->x - out->x) * (p->x - out->x) + (p->y - out->y) * (p->y - out->y));
    } else {
        x = (p->z - (l->o.z + l->d.z * t)) * (p->z - (l->o.z + l->d.z * t)) +
            ((p->x - (l->o.x + l->d.x * t)) * (p->x - (l->o.x + l->d.x * t)) +
             (p->y - (l->o.y + l->d.y * t)) * (p->y - (l->o.y + l->d.y * t)));
    }
    if (x < lbl_805E1020) {
        return lbl_805E1024;
    }
    if (x > lbl_805E1024) {
        volatile f32 y;
        f64 g = __frsqrte(x);
        g = lbl_805E1028 * g * (lbl_805E1030 - g * g * x);
        g = lbl_805E1028 * g * (lbl_805E1030 - g * g * x);
        g = lbl_805E1028 * g * (lbl_805E1030 - g * g * x);
        y = (f32)(x * g);
        r = y;
    } else {
        r = x;
    }
    return r;
}
#pragma pop

#pragma push
#pragma scheduling off
f32 xyz_distance(Vec *a, Vec *b) {
    f32 x = (a->z - b->z) * (a->z - b->z) + ((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
    f32 r;
    if (x < lbl_805E1038) {
        return lbl_805E103C;
    }
    if (x > lbl_805E103C) {
        volatile f32 y;
        f64 g = __frsqrte(x);
        g = lbl_805E1040 * g * (lbl_805E1048 - g * g * x);
        g = lbl_805E1040 * g * (lbl_805E1048 - g * g * x);
        g = lbl_805E1040 * g * (lbl_805E1048 - g * g * x);
        y = (f32)(x * g);
        r = y;
    } else {
        r = x;
    }
    return r;
}
#pragma pop


void calc_bounds_min_max__10TObjPlayerFPvPvPv(struct Vec_803E1B1C *pts, struct Vec_803E1B1C *mn, struct Vec_803E1B1C *mx) {
    s32 i;
    mn->x = pts->x;
    mn->y = pts->y;
    mn->z = pts->z;
    mx->x = pts->x;
    mx->y = pts->y;
    mx->z = pts->z;
    pts++;
    for (i = 1; i < 8; i++, pts++) {
        if (pts->x < mn->x) mn->x = pts->x;
        if (pts->y < mn->y) mn->y = pts->y;
        if (pts->z < mn->z) mn->z = pts->z;
        if (pts->x > mx->x) mx->x = pts->x;
        if (pts->y > mx->y) mx->y = pts->y;
        if (pts->z > mx->z) mx->z = pts->z;
    }
}

void TObjPlayer::calc_bounds(u8 *arg1, u8 *arg2) {
    u8 *arg0 = (u8 *)this;
    *(f32 *)((s8 *)arg1 + 0) = (f32) (*(f32 *)((s8 *)arg0 + 0) - *(f32 *)((s8 *)arg0 + 0xC));
    *(f32 *)((s8 *)arg1 + 4) = (f32) (*(f32 *)((s8 *)arg0 + 4) - *(f32 *)((s8 *)arg0 + 0xC));
    *(f32 *)((s8 *)arg1 + 8) = (f32) (*(f32 *)((s8 *)arg0 + 8) - *(f32 *)((s8 *)arg0 + 0xC));
    *(f32 *)((s8 *)arg2 + 0) = (f32) (*(f32 *)((s8 *)arg0 + 0) + *(f32 *)((s8 *)arg0 + 0xC));
    *(f32 *)((s8 *)arg2 + 4) = (f32) (*(f32 *)((s8 *)arg0 + 4) + *(f32 *)((s8 *)arg0 + 0xC));
    *(f32 *)((s8 *)arg2 + 8) = (f32) (*(f32 *)((s8 *)arg0 + 8) + *(f32 *)((s8 *)arg0 + 0xC));
}


extern s8 scene_fog_enable_flag;


#pragma push
#pragma scheduling off
typedef char RecoveredGlobal_803E1D1C_lbl_804FC780_size[sizeof(RecoveredGlobal_803E1D1C_lbl_804FC780) == 0x28 ? 1 : -1];
void load_current_pos_matrix(s32 arg0) {
    GXLoadPosMtxImm((void *)current_matrix, (int) (*(s32 *)((s8 *)((u8 *)&gx_pos_mtx_index_table.value + (arg0 * 4)) + 0)));
}
#pragma pop


#pragma push
#pragma scheduling off
void load_current_tex_matrix(s32 i) {
    GXLoadTexMtxImm((void *)current_matrix, tex_matrix_id_table[i], 0);
}
#pragma pop


void load_list_texture(s32 idx, s32 wrapS, s32 wrapT, s32 map) {
    TexInfo_803E1D90 *info = current_render_context->list->ents[idx].info;
    TexHdr_803E1D90 *hdr = info->hdr;
    u32 flags = hdr->flags;
    u8 mip;
    if (flags & 0x80000000) {
        mip = 1;
    } else {
        mip = 0;
    }
    if (flags & 0x8000) {
        GXInitTexObjCI(&list_texture_tex_obj, hdr->image, hdr->width, hdr->height, hdr->format, wrapS, wrapT, mip, info->tlut);
    } else {
        Dolphin_GXInitTexObj(&list_texture_tex_obj, hdr->image, hdr->width, hdr->height, hdr->format, wrapS, wrapT, mip);
    }
    GXLoadTexObj(&list_texture_tex_obj, list_texture_map_table[map]);
}


void TObjPlayer::reload_texture(s32 arg1, u32 arg2, void *arg3) {
    s32 size;
    if ((arg2 & 0x40000000) != 0) {
        size = arg1;
    } else {
        OSPanic(lbl_804FC7F8, 0x30, lbl_805D46F0);
    }
    TObjPlayer__sub_803DAE1C((s32)this, size, (u32)arg3);
}

void TObjPlayer::set_effect_active() {
    scene_fog_enable_flag = 1;
}


void TObjPlayer::reset_particle_counter() {
    scene_fog_enable_flag = 0;
}

TexObj_803E1D90 list_texture_tex_obj;
