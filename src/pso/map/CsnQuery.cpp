#include "pso/math/ScratchVectorStorage.h"
#include "types.h"
#include "pso/system/vector.h"
#include "pso/map/CsnQuery.h"
#include "pso/player/TObjPlayer.h"
#include "pso/object/TObjMapCsn.h"
#include "pso/render/render_util.h"

#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
struct ByteBlock_C { u8 bytes[0xc]; };

struct RecoveredGlobal_800790F0_lbl_804F5800 {
    s32 value;
    u8 remaining[0xFC];
};

struct Obj_8007A32C { s32 f0; f32 f4; s32 f8; u8 fc[4]; };

struct E_80079580 { u8 pad[0x24]; u32 f24; };

struct Vec_80079608 {
    f32 x;
    f32 y;
    f32 z;
};

typedef CsnContact Hit_80079608;

struct Query_80079608 {
    s32 count;
    u8 pad4[4];
    void *flags;
    Vec_80079608 origin;
    Vec_80079608 *offsets;
};

typedef CsnQueryResult Result_80079608;

struct Poly_8007970C { u8 pad[0x24]; };

struct Mesh_8007970C {
    u8 pad0[4];
    u32 flags;
    s32 count;
    Poly_8007970C *polys;
};

struct Node_8007970C {
    Mesh_8007970C *mesh;
};

struct Poly_800797DC { u8 pad[0x24]; };

struct Mesh_800797DC {
    u8 pad0[4];
    u32 flags;
    s32 count;
    Poly_800797DC *polys;
};

struct Node_800797DC {
    Mesh_800797DC *mesh;
};

struct Vec_800798A0 {
    f32 x;
    f32 y;
    f32 z;
};

struct Face_800798A0 {
    u16 idx[3];
    u16 flags;
    Vec_800798A0 n;
};

// The collision model stores one 0x24-byte triangle per entry.
struct CsnTriangle {
    u16 indices[3];
    u16 flags;
    Vec normal;
    Vec center;
    f32 radius;
};

struct CsnModel {
    u8 unknown_00[4];
    const Vec *vertices;
    s32 triangle_count;
    const CsnTriangle *triangles;
};

typedef char CsnTriangleSize[sizeof(CsnTriangle) == 0x24 ? 1 : -1];

struct M_80079C64 { u8 pad[4]; f32 x; f32 y; f32 z; f32 rad; u32 flags; };

struct P_80079C64 { f32 x; f32 y; f32 z; };

struct E_80079580;
struct V_80079F58 { f32 x, y, z; };

struct Poly_80079F58 {
    u8 pad0[0x14];
    f32 x;
    f32 y;
    f32 z;
    f32 radius;
};

struct Mesh_80079F58 {
    u32 f0;
    u32 id;
    s32 count;
    Poly_80079F58 *polys;
};

struct Grp_80079F58 {
    Mesh_80079F58 *mesh;
    f32 x;
    f32 y;
    f32 z;
    f32 radius;
    s32 flags;
};

struct Out_80079F58 { u8 pad[0x24]; u32 id; };

struct Vec_8007A138 { f32 x, y, z; };

struct Wall_8007A138 {
    u32 f0;
    Vec_8007A138 pos;
    f32 radius;
    u32 flags;
};

extern RecoveredGlobal_800790F0_lbl_804F5800 lbl_804F5800;
extern "C" {
s32 csn_query_hit_count;
f32 csn_query_nearest_hit_t;
CsnHit *csn_query_hit_buffer;
s32 wall_query_hit_result;

s32 get_csn_group_flags(u8 arg0);
void TObjPlayer__sub_80079108(void);
s32 TObjPlayer__sub_80079118(s32 *);
void TObjPlayer__sub_8007911C(void);
void TObjPlayer__sub_80079120(s32);
s32 evaluate_ground_triangles(Vec *origin, u32 mask, CsnGroup *const *groups);
extern s32 lbl_804389CC[];
s32 *csnVectorUnder(Vec *arg0, u32 *arg1, s32 arg2);
s32 TObjPlayer__sub_80079118(s32 * _w0);
void TObjPlayer__sub_80079120(s32 _w0);
extern u32 lbl_804FFD40[];
extern s32 lbl_804389E8[];
void *query_wall_radial(Obj_8007A32C *self);
void TObjPlayer__sub_80079124(void *, void *);
u32 TObjPlayer__sub_80079DE0(void *, void *);
f32 vec_squared_length(Vec *);
extern s32 lbl_804389C0[];
s32 *csnLookAt(s32 arg0, s32 arg1);
s32 intersect_wall_triangle_one_sided(void *, void *, void *, E_80079580 *, u32, s32);
f32 fabs_float(f32);
extern const f32 lbl_805D9204;
s32 select_deepest_wall_ray(Query_80079608 *q, Result_80079608 *r);
void TObjPlayer__sub_80079124(void * _w0, void * _w1);
s32 query_segment_wall_meshes(void *arg0, void *arg1, u32 arg2, Node_8007970C **list);
s32 check_line_hits_walls__10TObjPlayerFPvPviPv(void *arg0, void *arg1, int arg2, Node_800797DC **list);
f32 vec3_dot(void *, void *);
void vec3_cross(void *, void *, void *);
extern Vec_800798A0 lbl_8050BF20;
extern Vec_800798A0 lbl_8050BF40;
extern Vec_800798A0 lbl_8050BF60;
extern const f32 lbl_805D91F0;
extern const f32 lbl_805D91F4;
extern const f32 lbl_805D91F8;
extern const f32 lbl_805D91FC;
extern const f32 lbl_805D9200;
static const f32 lbl_805D9208 = -1e-05f;
static const f32 lbl_805D920C = 1.0f;
CsnGroup **get_data_ptr__10TObjMapCsnFv();
M_80079C64 *refill_csn_candidate_cache(P_80079C64 *arg0, M_80079C64 **arg1, u32 arg2);
f32 newton_sqrtf(f32);
void TObjPlayer__sub_80079114(void);
f32 vector_length(void *);
Wall_8007A138 *query_collision_segment_groups(Vec_8007A138 *a, Vec_8007A138 *b, u32 mask);
s32 calc_segment_xz_distance_sq(Vec_8007A138 *c, Vec_8007A138 *o, Vec_8007A138 *e, Vec_8007A138 *d, f32 radius, f32 hsq, f32 inv);

typedef char RecoveredGlobal_800790F0_lbl_804F5800_size[sizeof(RecoveredGlobal_800790F0_lbl_804F5800) == 0x100 ? 1 : -1];
s32 get_csn_group_flags(u8 arg0) {
    return *(u8 *)((s8 *)((u8 *)&lbl_804F5800.value + arg0) + 0) & 0xC0;
}

void TObjPlayer__sub_80079108(void) {  }
void TObjPlayer__sub_8007910C(const CsnContact *, const NJS_ARGB *) {  }
void TObjPlayer__sub_80079110(const CsnHit *) {  }
void TObjPlayer__sub_80079114(void) {  }
s32 TObjPlayer__sub_80079118(s32 * _w0) {  }
void TObjPlayer__sub_8007911C(void) {  }
void TObjPlayer__sub_80079120(s32 _w0) {  }
void TObjPlayer__sub_80079124(void * _w0, void * _w1) {  }

#pragma push
#pragma fp_contract on
s32 calc_segment_xz_distance_sq(Vec_8007A138 *c, Vec_8007A138 *o, Vec_8007A138 *e, Vec_8007A138 *d, f32 radius, f32 hsq, f32 inv) {
    f32 x;
    f32 z;
    f32 cx;
    f32 cz;
    f32 ddx;
    f32 ddz;
    f32 proj;
    f32 dx;
    f32 dz;
    f32 dist;
    cz = c->z;
    cx = c->x;
    x = cx - o->x;
    z = cz - o->z;
    ddz = d->z;
    ddx = d->x;
    proj = ddx * x + ddz * z;
    if (proj > lbl_805D91F0) {
        if (proj >= hsq) {
            dx = e->x - cx;
            dz = e->z - cz;
            dist = dx * dx + dz * dz;
        } else {
            f32 t = proj * inv;
            dz = z - t * ddz;
            dx = x - t * ddx;
            dist = dx * dx + dz * dz;
        }
    } else {
        dist = x * x + z * z;
    }
    return dist <= radius * radius;
}
}
extern s32 lbl_80438988[];
void *query_prepared_wall_polygons(void *self);
extern s32 lbl_804389A8[];
extern E_80079580 *wall_query_scene_buffer;
s32 query_wall_segment(void *arg0, void *arg1, void *arg2, s32 arg3);
CsnGroup *select_ground_query_groups(CsnVector *arg0, u32 arg1);
s32 prepare_wall_query_polygons(void *arg0, f32 r, s32 mask);

static inline void store_ground_contact(CsnContact *contact, f32 x, f32 y, f32 z,
                                        f32 t, f32 nx, f32 ny, f32 nz, const CsnTriangle *triangle) {
    contact->point.x = x;
    contact->point.y = lbl_805D91F8 * t + y;
    contact->point.z = z;
    contact->normal.x = nx;
    contact->normal.y = ny;
    contact->normal.z = nz;
    contact->flags = triangle->flags;
}

extern "C" s32 evaluate_ground_triangles(Vec *origin, u32 mask, CsnGroup *const *groups) {
    Vec direction;
    u32 mask_10;
    u32 mask_04;
    u32 mask_02;
    u32 mask_08;
    u32 ground_mask;
    s32 i;
    s32 count;
    const Vec *vertices;
    const CsnTriangle *triangle;
    CsnContact *contacts;
    // The original leaves this register untouched until a contact is stored.
    // The only read before a store can be the call to the empty debug hook.
#ifdef __MWERKS__
    CsnContact *selected;
#else
    CsnContact *selected = NULL;
#endif
    CsnHit &result = lbl_80500140;
    result.hit = 0;
    contacts = result.contact;
    lbl_8050BF60.x = origin->x;
    lbl_8050BF60.y = lbl_805D91F8 + origin->y;
    lbl_8050BF60.z = origin->z;
    f32 nearest = lbl_805D91F4;
    vsub(origin, &lbl_8050BF60, &direction);

    f32 x = origin->x;
    f32 y = origin->y;
    f32 z = origin->z;
    mask_10 = mask & 0x10;
    mask_04 = mask & 0x4;
    mask_02 = mask & 0x2;
    mask_08 = mask & 0x8;
    ground_mask = mask & ~0x1E;

    for (; *groups != NULL; ++groups) {
        CsnModel *model = (*groups)->model;
        i = 0;
        count = model->triangle_count;
        triangle = model->triangles;
        vertices = model->vertices;
        for (; i < count; ++i, ++triangle) {
            f32 bx, ax, az, bz;
            u16 flags = triangle->flags;
            if (!(flags & mask)) {
                continue;
            }
            f32 dz = triangle->center.z;
            f32 dx = triangle->center.x;
            f32 radius = triangle->radius;
            dx -= x;
            dz -= z;
            radius *= radius;
            if (dx * dx + dz * dz > radius) {
                continue;
            }
            f32 ny = triangle->normal.y;
            if (ny < lbl_805D91FC) {
                continue;
            }
            const Vec *a = &vertices[triangle->indices[0]];
            const Vec *b = &vertices[triangle->indices[1]];
            const Vec *c = &vertices[triangle->indices[2]];
            if (a->y > y && b->y > y && c->y > y) {
                continue;
            }
            az = a->z - z;
            bx = b->x - x;
            ax = a->x - x;
            bz = b->z - z;
            // The signed edge tests use the triangle winding in the XZ plane.
            if (az * bx - ax * bz < lbl_805D9200) {
                continue;
            }
            f32 cx = c->x - x;
            f32 cz = c->z - z;
            if (bz * cx - bx * cz < lbl_805D9200) {
                continue;
            }
            if (cz * ax - cx * az < lbl_805D9200) {
                continue;
            }
            f32 ay = a->y - y;
            f32 nx = triangle->normal.x;
            f32 nz = triangle->normal.z;
            // Keep the negation in the contracted dot product before division.
            f32 plane = -(az * nz + (ax * nx + ay * ny));
            f32 t = -(plane / (lbl_805D91F8 * ny));
            // Slot zero keeps the nearest ground hit. The remaining slots
            // keep the last hit for their respective surface bits.
            if (mask_10 && (flags & 0x10)) {
                result.hit |= 0x10;
                selected = &contacts[1];
                store_ground_contact(selected, x, y, z, t, nx, ny, nz, triangle);
            }
            if (mask_04 && (triangle->flags & 0x4)) {
                result.hit |= 0x4;
                selected = &contacts[2];
                store_ground_contact(selected, x, y, z, t, nx, ny, nz, triangle);
            }
            if (mask_02 && (triangle->flags & 0x2)) {
                result.hit |= 0x2;
                selected = &contacts[3];
                store_ground_contact(selected, x, y, z, t, nx, ny, nz, triangle);
            }
            if (mask_08 && (triangle->flags & 0x8)) {
                result.hit |= 0x8;
                selected = &contacts[4];
                store_ground_contact(selected, x, y, z, t, nx, ny, nz, triangle);
            }
            if ((triangle->flags & ground_mask) && t < nearest) {
                result.hit |= 1;
                nearest = t;
                selected = contacts;
                store_ground_contact(selected, x, y, z, t, nx, ny, nz, triangle);
            }
            TObjPlayer__sub_80079110(&result);
            TObjPlayer__sub_8007910C(selected, &debug_color_blue);
        }
    }
    return result.hit & 1;
}
#pragma pop

s32 query_wall_segment(void *arg0, void *arg1, void *arg2, s32 arg3) {
    u8 sp8[12];
    s32 r;
    E_80079580 *p = wall_query_scene_buffer;
    vsub(arg0, arg1, sp8);
    r = 0;
    wall_query_hit_result = arg3;
    csn_query_nearest_hit_t = lbl_805D91F4;
    for (; p->f24 != 0; p = (E_80079580 *)((u8 *)p + 0x28)) {
        if (intersect_wall_triangle_one_sided(arg0, sp8, arg2, p, p->f24, 3) != 0) {
            r = 1;
        }
    }
    return r;
}

#pragma push
#pragma fp_contract on

s32 select_deepest_wall_ray(Query_80079608 *q, Result_80079608 *r) {
    Vec_80079608 end;
    s32 i;
    s32 n;
    Vec_80079608 *off;
    Hit_80079608 *hit;
    f32 d;
    i = 0;
    r->hit = 0;
    r->index = -1;
    r->best = lbl_805D9204;
    off = q->offsets;
    hit = r->contact;
    n = q->count;
    for (; i < n; off++, hit++, i++) {
        end.x = q->origin.x + off->x;
        end.y = q->origin.y + off->y;
        end.z = q->origin.z + off->z;
        if (query_wall_segment(&q->origin, &end, q->flags, (s32)hit) != 0) {
            f32 dz = end.z - hit->point.z;
            f32 dx = end.x - hit->point.x;
            d = fabs_float(dx * hit->normal.x + dz * hit->normal.z);
            if (r->best < d) {
                r->hit = 1;
                r->best = d;
                r->index = i;
            }
        }
    }
    return r->hit;
}
#pragma pop

s32 query_segment_wall_meshes(void *arg0, void *arg1, u32 arg2, Node_8007970C **list) {
    u8 dir[12];
    Mesh_8007970C *mesh;
    s32 i;
    s32 n;
    u32 flags;
    Poly_8007970C *poly;
    TObjPlayer__sub_80079124(arg0, arg1);
    csn_query_hit_buffer = &lbl_80500140;
    csn_query_hit_buffer->hit = 0;
    wall_query_hit_result = (s32)csn_query_hit_buffer->contact;
    csn_query_nearest_hit_t = lbl_805D91F4;
    vsub(arg0, arg1, dir);
    for (; *list != NULL; list++) {
        mesh = (*list)->mesh;
        i = 0;
        n = mesh->count;
        poly = mesh->polys;
        flags = mesh->flags;
        for (; i < n; i++, poly++) {
            intersect_wall_triangle_one_sided(arg0, dir, (void *)arg2, (E_80079580 *)poly, flags, 0);
        }
    }
    return csn_query_hit_buffer->hit;
}

s32 check_line_hits_walls__10TObjPlayerFPvPviPv(void *arg0, void *arg1, int arg2, Node_800797DC **list) {
    u8 dir[12];
    Mesh_800797DC *mesh;
    s32 i;
    s32 n;
    u32 flags;
    Poly_800797DC *poly;
    csn_query_hit_buffer = &lbl_80500140;
    csn_query_hit_buffer->hit = 0;
    wall_query_hit_result = (s32)csn_query_hit_buffer->contact;
    vsub(arg0, arg1, dir);
    for (; *list != NULL; list++) {
        mesh = (*list)->mesh;
        i = 0;
        n = mesh->count;
        poly = mesh->polys;
        flags = mesh->flags;
        for (; i < n; i++, poly++) {
            if (intersect_wall_triangle_one_sided(arg0, dir, (void *)arg2, (E_80079580 *)poly, flags, 1) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

#pragma push
#pragma fp_contract on
#define FACE ((Face_800798A0 *)arg3)
#define ORG ((Vec_800798A0 *)arg0)
#define DIR ((Vec_800798A0 *)arg1)
#define VERTS ((Vec_800798A0 *)arg4)

s32 intersect_wall_triangle_one_sided(void *arg0, void *arg1, void *arg2, E_80079580 *arg3, u32 arg4, s32 arg5) {
    Vec_800798A0 n;
    Vec_800798A0 *v;
    Vec_800798A0 *v1;
    f32 denom;
    f32 t;

    if ((FACE->flags & (u32)arg2) == 0) {
        return 0;
    }
    n.x = FACE->n.x;
    n.y = FACE->n.y;
    n.z = FACE->n.z;
    denom = vec3_dot(DIR, &n);
    if (denom >= lbl_805D9208) {
        return 0;
    }
    v = &VERTS[FACE->idx[0]];
    scratch_vec.vector.x = ORG->x - v->x;
    scratch_vec.vector.y = ORG->y - v->y;
    scratch_vec.vector.z = ORG->z - v->z;
    t = vec3_dot(&scratch_vec.vector, &n);
    if (t <= lbl_805D91FC) {
        return 0;
    }
    t = -(t / denom);
    if (t > lbl_805D920C || t < lbl_805D91F0) {
        return 0;
    }
    lbl_8050BF60.x = DIR->x * t + ORG->x;
    lbl_8050BF60.y = DIR->y * t + ORG->y;
    lbl_8050BF60.z = DIR->z * t + ORG->z;
    v1 = &VERTS[FACE->idx[1]];
    vsub(&lbl_8050BF60, v, &scratch_vec.vector);
    vsub(&lbl_8050BF60, v1, &lbl_8050BF00.vector);
    vec3_cross(&scratch_vec.vector, &lbl_8050BF00.vector, &lbl_8050BF40);
    if (vec3_dot(&lbl_8050BF40, &n) < lbl_805D91F0) {
        return 0;
    }
    vsub(&lbl_8050BF60, &VERTS[FACE->idx[2]], &lbl_8050BF20);
    vec3_cross(&lbl_8050BF00.vector, &lbl_8050BF20, &lbl_8050BF40);
    if (vec3_dot(&lbl_8050BF40, &n) < lbl_805D91F0) {
        return 0;
    }
    vec3_cross(&lbl_8050BF20, &scratch_vec.vector, &lbl_8050BF40);
    if (vec3_dot(&lbl_8050BF40, &n) < lbl_805D91F0) {
        return 0;
    }
    switch (arg5) {
    case 0:
        if (t < csn_query_nearest_hit_t) {
            csn_query_nearest_hit_t = t;
            csn_query_hit_buffer->hit = 1;
            VecCopy((Vec *)wall_query_hit_result, (const Vec *)&lbl_8050BF60);
            VecCopy((Vec *)(wall_query_hit_result + 0xC), (const Vec *)&n);
            *(u32 *)((s8 *)wall_query_hit_result + 0x18) = FACE->flags;
        }
        break;
    case 1:
        csn_query_hit_buffer->hit = 1;
        VecCopy((Vec *)wall_query_hit_result, (const Vec *)&lbl_8050BF60);
        VecCopy((Vec *)(wall_query_hit_result + 0xC), (const Vec *)&n);
        *(u32 *)((s8 *)wall_query_hit_result + 0x18) = FACE->flags;
        break;
    case 2:
        if (csn_query_hit_count >= 0x20) {
            return 0;
        }
        csn_query_hit_buffer->hit = 1;
        VecCopy((Vec *)wall_query_hit_result, (const Vec *)&lbl_8050BF60);
        VecCopy((Vec *)(wall_query_hit_result + 0xC), (const Vec *)&n);
        *(u32 *)((s8 *)wall_query_hit_result + 0x18) = FACE->flags;
        wall_query_hit_result += 0x1C;
        csn_query_hit_count++;
        break;
    case 3:
        if (t < csn_query_nearest_hit_t) {
            csn_query_nearest_hit_t = t;
            VecCopy((Vec *)wall_query_hit_result, (const Vec *)&lbl_8050BF60);
            VecCopy((Vec *)(wall_query_hit_result + 0xC), (const Vec *)&n);
            *(u32 *)((s8 *)wall_query_hit_result + 0x18) = FACE->flags;
        }
        break;
    }
    return 1;
}
#pragma pop
#undef FACE
#undef ORG
#undef DIR
#undef VERTS

#pragma fp_contract on

#pragma push
#pragma fp_contract on
M_80079C64 *refill_csn_candidate_cache(P_80079C64 *arg0, M_80079C64 **arg1, u32 arg2) {
    f32 rr;
    f32 dz;
    f32 dx;
    s32 n = 0;
    M_80079C64 **it;
    M_80079C64 *m;
    M_80079C64 **first;
    TObjMapCsn::get_map_count();
    it = (M_80079C64 **)get_data_ptr__10TObjMapCsnFv();
    first = arg1;
    while ((m = *it++) != 0) {
        if ((m->flags & arg2) && !(m->flags & 0x40000000)) {
            dz = m->z - arg0->z;
            dx = m->x - arg0->x;
            rr = m->rad;
            rr *= rr;
            if (dx * dx + dz * dz <= rr) {
                n++;
                if (n >= 0xF) {
                    break;
                }
                *arg1++ = m;
            }
        }
    }
    *arg1 = 0;
    return *first;
}
#pragma pop

CsnGroup *select_ground_query_groups(CsnVector *origin, u32 mask) {
  f32 dx;
  f32 dz;
  f32 r;
  int capacityReached;
  s32 count = 0;
  CsnGroup **input;
  CsnGroup *group;
  float zSquared;
  CsnGroup **output;
  float zDelta;
  TObjMapCsn::get_map_count();
  input = get_data_ptr__10TObjMapCsnFv();
  output = ((CsnGroup * *)&lbl_804FFD40);
  while ((group = *(input++)) != 0)
  {
    if (group->flags & mask)
    {
      zDelta = group->center.z - origin->z;
      dz = zDelta;
      r = group->radius;
      r = r * r;
      dx = group->center.x - origin->x;
      zSquared = dz * dz;
      if (((dx * dx) + zSquared) <= r)
      {
        count++;
        capacityReached = count >= 0x100;
        if (capacityReached)
        {
          break;
        }
        *(output++) = group;
      }
    }
  }
  *output = 0;
  return ((CsnGroup * *)&lbl_804FFD40)[0];
}

u32 TObjPlayer__sub_80079DE0(void *a, void *b) {
    Vec_8007A138 d;
    s32 n;
    Wall_8007A138 *w;
    Wall_8007A138 **src;
    Wall_8007A138 **dst;
    f32 len;
    f32 lenSq;
    f32 inv;
    f32 r;
    f32 dsq;
    n = 0;
    TObjMapCsn::get_map_count();
    src = (Wall_8007A138 **)get_data_ptr__10TObjMapCsnFv();
    dst = (Wall_8007A138 **)lbl_804FFD40;
    vsub(a, b, &d);
    lenSq = d.x * d.x + d.z * d.z;
    if (lbl_805D91F0 == lenSq) {
        lenSq = lbl_805D91FC;
    }
    inv = lbl_805D920C / lenSq;
    len = newton_sqrtf(lenSq);
    while ((w = *src++) != NULL) {
        if (w->flags & 0x8000) {
            vsub(a, &w->pos, &scratch_vec.vector);
            dsq = vec_squared_length(&scratch_vec.vector);
            r = len + w->radius;
            r *= r;
            if (dsq <= r) {
                if (calc_segment_xz_distance_sq(&w->pos, (Vec_8007A138 *)a, (Vec_8007A138 *)b, &d, w->radius, lenSq, inv) != 0) {
                    if (++n >= 0x100) {
                        break;
                    }
                    *dst++ = w;
                }
            }
        }
    }
    *dst = NULL;
    ((void (*)(void *))TObjPlayer__sub_80079114)(lbl_804FFD40);
    return lbl_804FFD40[0];
}

#pragma push
#pragma fp_contract on
s32 prepare_wall_query_polygons(void *arg0, f32 r, s32 mask) {
    V_80079F58 *pos = (V_80079F58 *)arg0;
    Grp_80079F58 **lp;
    s32 i;
    s32 count;
    s32 cnt;
    Poly_80079F58 *poly;
    Mesh_80079F58 *mesh;
    Out_80079F58 *out;
    Grp_80079F58 **src;
    Grp_80079F58 *g;
    s32 n;
    Grp_80079F58 **dst;
    TObjMapCsn::get_map_count();
    src = (Grp_80079F58 **)get_data_ptr__10TObjMapCsnFv();
    if (src == NULL) {
        return 0;
    }
    n = 0;
    dst = (Grp_80079F58 **)lbl_804FFD40;
    while ((g = *src++) != NULL) {
        if (g->flags & mask) {
            f32 b;
            f32 dz = g->z - pos->z;
            f32 dx = g->x - pos->x;
            b = r + g->radius;
            b *= b;
            if (dx * dx + dz * dz <= b) {
                if (++n >= 0x100) {
                    break;
                }
                *dst++ = g;
            }
        }
    }
    *dst = NULL;
    src = (Grp_80079F58 **)lbl_804FFD40;
    out = (Out_80079F58 *)wall_query_scene_buffer;
    cnt = 0;
    while ((g = *src++) != NULL) {
        mesh = g->mesh;
        count = mesh->count;
        poly = mesh->polys;
        for (i = 0; i < count; poly++, i++) {
            f32 dz = poly->z - pos->z;
            f32 dx = poly->x - pos->x;
            f32 b = r + poly->radius;
            b *= b;
            if (dx * dx + dz * dz <= b) {
                if (++cnt >= 0x200) {
                    break;
                }
                ((TObjPlayer *)out)->copy_wall_polygon((u8 *)poly);
                out->id = mesh->id;
                out++;
            }
        }
    }
    out->id = 0;
    return cnt;
}
#pragma pop

void TObjPlayer::copy_wall_polygon(u8 *arg1) {
    u8 *arg0 = (u8 *)this;
    *(s32 *)((s8 *)arg0 + 0) = (s32) *(s32 *)((s8 *)arg1 + 0);
    this->m_flags = (u16) *(u16 *)((s8 *)arg1 + 4);
    this->m_id = (u16) *(u16 *)((s8 *)arg1 + 6);
    *(ByteBlock_C *)((s32) (u8 *)&this->m_prev) = *(const ByteBlock_C *)((s32) arg1 + 8);
    *(ByteBlock_C *)((s32) (u8 *)&this->m_down) = *(const ByteBlock_C *)((s32) arg1 + 0x14);
    *(f32 *)&this->m_20 = (f32) *(f32 *)((s8 *)arg1 + 0x20);
}

Wall_8007A138 *query_collision_segment_groups(Vec_8007A138 *a, Vec_8007A138 *b, u32 mask) {
    Vec_8007A138 d;
    s32 n;
    Wall_8007A138 *w;
    Wall_8007A138 **src;
    Wall_8007A138 **dst;
    f32 len;
    f32 lenSq;
    f32 inv;
    f32 r;
    f32 dsq;
    n = 0;
    TObjMapCsn::get_map_count();
    src = (Wall_8007A138 **)get_data_ptr__10TObjMapCsnFv();
    dst = (Wall_8007A138 **)lbl_804FFD40;
    vsub(a, b, &d);
    len = vector_length(&d);
    lenSq = d.x * d.x + d.z * d.z;
    if (lbl_805D91F0 == lenSq) {
        lenSq = lbl_805D91FC;
    }
    inv = lbl_805D920C / lenSq;
    newton_sqrtf(lenSq);
    while ((w = *src++) != NULL) {
        if (w->flags & mask) {
            scratch_vec.vector.x = w->pos.x - a->x;
            scratch_vec.vector.z = w->pos.z - a->z;
            dsq = scratch_vec.vector.x * scratch_vec.vector.x + scratch_vec.vector.z * scratch_vec.vector.z;
            r = len + w->radius;
            r *= r;
            if (dsq <= r) {
                if (calc_segment_xz_distance_sq((Vec_8007A138 *)(&w->pos), (Vec_8007A138 *)(a), (Vec_8007A138 *)(b), (Vec_8007A138 *)(&d), w->radius, lenSq, inv) != 0) {
                    if (++n >= 0x100) {
                        break;
                    }
                    *dst++ = w;
                }
            }
        }
    }
    *dst = NULL;
    ((void (*)(void *))TObjPlayer__sub_80079114)(lbl_804FFD40);
    return (Wall_8007A138 *)lbl_804FFD40[0];
}

void *query_prepared_wall_polygons(void *self) {
    void *r;
    TObjPlayer__sub_8007911C();
    r = &csn_query_map_object;
    if (select_deepest_wall_ray((Query_80079608 *)(self), (Result_80079608 *)(r)) == 0) {
        r = 0;
    }
    TObjPlayer__sub_80079118(lbl_80438988);
    return r;
}

void *query_wall_radial(Obj_8007A32C *self) {
    void *r;
    TObjPlayer__sub_8007911C();
    r = &csn_query_map_object;
    if (prepare_wall_query_polygons(self->fc, self->f4, self->f8) == 0) {
        r = 0;
    } else if (select_deepest_wall_ray((Query_80079608 *)(self), (Result_80079608 *)(r)) == 0) {
        r = 0;
    }
    TObjPlayer__sub_80079118(lbl_804389A8);
    return r;
}

s32 *csnLookAt(s32 arg0, s32 arg1) {
    s32 *var_r31;
    TObjPlayer__sub_8007911C();
    var_r31 = &lbl_80500140.hit;
    TObjPlayer__sub_80079124((void *)arg0, (void *)arg1);
    if (TObjPlayer__sub_80079DE0((void *)arg0, (void *)arg1) == 0U) {
        var_r31 = NULL;
    } else if (check_line_hits_walls__10TObjPlayerFPvPviPv((void *)arg0, (void *)arg1, 0x8000, (Node_800797DC **)((void *) (((s32 *)&lbl_804FFD40)))) == 0) {
        var_r31 = NULL;
    }
    TObjPlayer__sub_80079118(lbl_804389C0);
    return var_r31;
}

s32 *csnVectorUnder(Vec *arg0, u32 *arg1, s32 arg2) {
    s32 *var_r31;
    TObjPlayer__sub_80079108();
    TObjPlayer__sub_8007911C();
    TObjPlayer__sub_80079120((s32)arg0);
    var_r31 = &lbl_80500140.hit;
    if ((u32) *arg1 == 0U) {
        if (((u32)refill_csn_candidate_cache((P_80079C64 *)(arg0), (M_80079C64 **)(arg1), arg2)) == 0U) {
            var_r31 = NULL;
        } else if (evaluate_ground_triangles(arg0, arg2, (CsnGroup *const *)arg1) == 0) {
            var_r31 = NULL;
        }
    } else {
        if (evaluate_ground_triangles(arg0, arg2, (CsnGroup *const *)arg1) != 0) {
            goto done;
        }
        if (((u32)refill_csn_candidate_cache((P_80079C64 *)(arg0), (M_80079C64 **)(arg1), arg2)) == 0U) {
            var_r31 = NULL;
        } else if (evaluate_ground_triangles(arg0, arg2, (CsnGroup *const *)arg1) == 0) {
            var_r31 = NULL;
        }
    }
done:
    TObjPlayer__sub_80079118(lbl_804389CC);
    return var_r31;
}
CsnHit *csnVecterUnder(const Vec *origin, u32 mask) {
    CsnHit *var_r31;
    TObjPlayer__sub_80079108();
    TObjPlayer__sub_8007911C();
    TObjPlayer__sub_80079120((s32)origin);
    var_r31 = &lbl_80500140;
    if (((u32)select_ground_query_groups((CsnVector *)(origin), mask)) == 0U) {
        var_r31 = 0;
    } else if (evaluate_ground_triangles(const_cast<Vec *>(origin), mask, (CsnGroup *const *)lbl_804FFD40) == 0) {
        var_r31 = 0;
    }
    TObjPlayer__sub_80079118(lbl_804389E8);
    return var_r31;
}
