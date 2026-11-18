#include "types.h"
#include "pso/player/TObjPlayer_803DF7A8.h"

struct CollisionPoint { f32 x, y, z; };
struct CollisionSphere { CollisionPoint center; f32 radius; };
struct Faces_803E0ED4 { s32 v[6][4]; };

extern "C" {
// The names preserve existing linker symbols; the arguments are the observed
// box points, sphere and bounds, without assigning them to a class.
void calc_bounds_min_max__10TObjPlayerFPvPvPv(CollisionPoint *, CollisionPoint *, CollisionPoint *);
void calc_bounds__10TObjPlayerFPUcPUc(CollisionSphere *, CollisionPoint *, CollisionPoint *);
s32 test_aabb_overlap__10TObjPlayerFPUcPUcPUc(CollisionPoint *, CollisionPoint *, CollisionPoint *, CollisionPoint *);
#pragma push
#pragma fp_contract off
#pragma use_lmw_stmw off
// Adapted from upstream PR #311; see docs/evidence/collision-contact-units.md.
struct FaceEdgeLoop { s32 v[5]; };
inline const Faces_803E0ED4 *box_faces() {
    static const Faces_803E0ED4 box_face_vertex_index_table = {
        {{0, 1, 2, 3}, {4, 7, 6, 5}, {0, 3, 7, 4}, {2, 1, 5, 6}, {0, 4, 5, 1}, {3, 2, 6, 7}}};
    return &box_face_vertex_index_table;
}
inline const Faces_803E0ED4 *box_adjacent() {
    static const Faces_803E0ED4 box_edge_adjacent_face_table = {
        {{4, 3, 5, 2}, {2, 5, 3, 4}, {0, 5, 1, 4}, {0, 4, 1, 5}, {2, 1, 3, 0}, {0, 3, 1, 2}}};
    return &box_edge_adjacent_face_table;
}
inline const FaceEdgeLoop *box_order() {
    static const FaceEdgeLoop box_edge_order_table = {{0, 1, 2, 3, 0}};
    return &box_edge_order_table;
}

// Match the native single-precision rounding after reciprocal-square-root refinement.
static inline f32 sqrtf_803E112C(f32 x) {
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

#pragma push
#pragma dont_inline off
#pragma inline_depth(2)
#pragma opt_loop_invariants off
s32 test_box_sphere_contact(CollisionPoint *corners, CollisionSphere *sphere) {
    CollisionPoint boxMin;
    CollisionPoint boxMax;
    CollisionPoint sphereMin;
    CollisionPoint sphereMax;
    calc_bounds_min_max__10TObjPlayerFPvPvPv(corners, &boxMin, &boxMax);
    calc_bounds__10TObjPlayerFPUcPUc(sphere, &sphereMin, &sphereMax);
    if (test_aabb_overlap__10TObjPlayerFPUcPUcPUc(&boxMin, &boxMax, &sphereMin, &sphereMax) != 0) {
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
            normalScale = 1.0f / sqrtf_803E112C(normal->z * normal->z + (normal->x * normal->x + normal->y * normal->y));
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
            f32 planeDist = sqrtf_803E112C((footZ - center->z) * (footZ - center->z) +
                                  ((footX - center->x) * (footX - center->x) + (footY - center->y) * (footY - center->y)));
            for (j = 0; j < 4; j++) {
                planeDistSq = planeDist * planeDist;
                FaceEdgeLoop loop = *box_order();
                startX = corners[face[loop.v[j]]].x;
                CollisionPoint *end = &corners[face[loop.v[j + 1]]];
                edgeX = startX - end->x;
                edgeY = (startY = corners[face[loop.v[j]]].y) - end->y;
                edgeZ = (startZ = corners[face[loop.v[j]]].z) - end->z;
                const s32 &adjacentFace = adjacentFaces.v[i][loop.v[j]];
                edgeT = (edgeZ * (footZ - startZ) + (edgeX * (footX - startX) + edgeY * (footY - startY))) / (edgeZ * edgeZ + (edgeX * edgeX + edgeY * edgeY));
                nearX = edgeX * edgeT;
                nearX += startX;
                nearY = edgeY * edgeT;
                nearY += startY;
                nearZ = edgeZ * edgeT - -startZ;
                toEdgeX = nearX - footX;
                toEdgeY = nearY - footY;
                toEdgeZ = nearZ - footZ;
                toEdgeScale = 1.0f / sqrtf_803E112C(toEdgeZ * toEdgeZ + (toEdgeX * toEdgeX + toEdgeY * toEdgeY));
                toEdgeX *= toEdgeScale;
                toEdgeY *= toEdgeScale;
                toEdgeZ *= toEdgeScale;
                if ((f32)__fabs(normals[adjacentFace].x - toEdgeX) <= 0.025f &&
                    (f32)__fabs(normals[adjacentFace].y - toEdgeY) <= 0.025f &&
                    (f32)__fabs(normals[adjacentFace].z - toEdgeZ) <= 0.025f &&
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
            toFootScale = 1.0f / sqrtf_803E112C(toFootZ * toFootZ + (toFootX * toFootX + toFootY * toFootY));
            toFootX *= toFootScale;
            toFootY *= toFootScale;
            toFootZ *= toFootScale;
            if ((f32)__fabs(normal->x - toFootX) <= 0.025f && (f32)__fabs(normal->y - toFootY) <= 0.025f &&
                (f32)__fabs(normal->z - toFootZ) <= 0.025f) {
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
