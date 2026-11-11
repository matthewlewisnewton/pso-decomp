#include "pso/TObjEZRopeBase.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/misc/MaterialColorFade.h"
#include "pso/misc/TQuestVmDownLoadServer.h"
#include "pso/object/TObjHMS_EZRope_Player.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_803DF7A8.h"
#include "pso/system/ChunkMaterialState.h"
#include "pso/system/MatrixOps.h"
#include "pso/system/vector.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "types.h"


struct ByteBlock_C { u8 bytes[0xc]; };

typedef struct E1_800FF070 { s8 type; u8 pad1[0x13]; u8 *data; } E1_800FF070;

typedef struct E2_800FF070 { s8 type; u8 pad1[0x13]; } E2_800FF070;

typedef struct Obj_800FF070 {
    s32 f0;
    u8 pad4[0x14];
    void *vt;
    u8 pad1c[0x14];
    void *f30;
    E1_800FF070 *list;
    E2_800FF070 *list2;
    RopeSegment *a;
    RopeAnchor *b;
    RopeCollisionSphere *c;
} Obj_800FF070;

extern "C" {
void TObjPlayer__sub_800FF220(s32 *arg0, s32 *arg1);
void TObjPlayer__sub_800FF1FC(f32 *arg0, f32 *arg1);
void TObjPlayer__sub_800FF244(u8 *arg0, u8 *arg1);
void *TObjEZRopeBase__ct(void *);
extern u8 ezrope_chunk_material_color_table[];
extern s32 TObjHMS_EZRope_Player__name;
f32 fabs_float(f32);
f32 atan2_float(f32, f32);
f32 get_scale_factor__10TObjPlayerFv(f32);
f32 vector_length(const Vec *);
void translate_matrix_vec3(u8 *arg0, u8 *arg1);
s32 rotate_matrix_y(int, int);
f32 normalize_vector(Vec *);
s32 push_matrix();
s32 pop_matrix();
void set_chunk_material_override_pair(s32 arg0, s32 arg1);
void draw_chunk_object(void *child);
extern const f64 lbl_8043DF40;
extern u8 lbl_8048DEF4[];
extern s32 saved_model_render_flags;
extern s32 saved_chunk_polygon_flags_and_mask;
extern s32 saved_chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_and_mask;
extern s32 model_render_flags;
void __dl__7TObjectFPv(void *);
void __dt__14TObjEZRopeBaseFv(void *, int);
void *__nw__7TObjectFUl(int);

extern s32 __vt__21TObjHMS_EZRope_Player[];

void *__dt__21TObjHMS_EZRope_PlayerFv(TObjHMS_EZRope_Player *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__21TObjHMS_EZRope_Player;
        if (arg0->m_3c != NULL) { TAdSinglePlyChrSelectGC::safe_free((void *)arg0->m_3c); *(s32 *)((s8 *)arg0 + 0x3C) = 0; }
        if (*(void **)((s8 *)arg0 + 0x40) != NULL) { TAdSinglePlyChrSelectGC::safe_free((void *)(*(void **)((s8 *)arg0 + 0x40))); *(s32 *)((s8 *)arg0 + 0x40) = 0; }
        if (arg0->m_44 != NULL) { TAdSinglePlyChrSelectGC::safe_free((void *)arg0->m_44); *(s32 *)((s8 *)arg0 + 0x44) = 0; }
        __dt__14TObjEZRopeBaseFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

#define SELF ((Obj_800FF070 *)arg0)
void *TObjHMS_EZRope_Player__ct(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 base = (s32)ezrope_chunk_material_color_table;
    s32 n1;
    s32 n2;
    E2_800FF070 *q;
    E1_800FF070 *p;
    RopeSegment *d;
    RopeAnchor *e;
    TObjEZRopeBase__ct(arg0);
    n1 = 0;
    SELF->vt = (void *)(base + 0x3C);
    n2 = 0;
    SELF->f0 = TObjHMS_EZRope_Player__name;
    SELF->f30 = arg1;
    SELF->list = (E1_800FF070 *)arg2;
    SELF->list2 = (E2_800FF070 *)arg3;
    for (p = SELF->list; p->type >= 0; p++, n1++) {
    }
    if (SELF->list2 != NULL) {
        for (q = SELF->list2; q->type >= 0; q++, n2++) {
        }
    }
    SELF->a = static_cast<RopeSegment *>(TQuestVmDownLoadServer::alloc((n1 + 1) * sizeof(RopeSegment)));
    SELF->b = static_cast<RopeAnchor *>(TQuestVmDownLoadServer::alloc(n1 * sizeof(RopeAnchor)));
    if (n2 == 0) {
        SELF->c = NULL;
    } else {
        SELF->c = static_cast<RopeCollisionSphere *>(TQuestVmDownLoadServer::alloc((n2 + 1) * sizeof(RopeCollisionSphere)));
    }
    {
        E1_800FF070 *p3;
        RopeSegment *d3;
        RopeAnchor *e3;
        d3 = SELF->a;
        p3 = SELF->list;
        e3 = SELF->b;
        for (; p3->type >= 0; p3++, d3++, e3++) {
            TObjPlayer__sub_800FF244((u8 *)d3, p3->data);
            TObjPlayer__sub_800FF220((s32 *)e3, (s32 *)(base + 0x10));
        }
        d3->point_count = -1;
    }
    if (SELF->c != NULL) {
        E2_800FF070 *q4 = SELF->list2;
        RopeCollisionSphere *e4 = SELF->c;
        for (; q4->type >= 0; q4++, e4++) {
            TObjPlayer__sub_800FF1FC((f32 *)e4, (f32 *)(base + 0x20));
        }
        TObjPlayer__sub_800FF1FC((f32 *)e4, (f32 *)(base + 0x20));
    }
    static_cast<TObjEZRopeBase *>(arg0)->sub_800FF8CC(SELF->a, SELF->b, SELF->c);
    return arg0;
}

// Preserve the existing inline aggregate copies for these three record helpers.
#pragma push
#pragma inline_depth(1)
#pragma dont_inline off
void TObjPlayer__sub_800FF1FC(f32 *arg0, f32 *arg1) {
    *arg0 = *arg1;
    *reinterpret_cast<ByteBlock_C *>(reinterpret_cast<u8 *>(arg0) + 4) =
        *reinterpret_cast<const ByteBlock_C *>(reinterpret_cast<const u8 *>(arg1) + 4);
}

void TObjPlayer__sub_800FF220(s32 *arg0, s32 *arg1) {
    *arg0 = *arg1;
    *reinterpret_cast<ByteBlock_C *>(reinterpret_cast<u8 *>(arg0) + 4) =
        *reinterpret_cast<const ByteBlock_C *>(reinterpret_cast<const u8 *>(arg1) + 4);
}

void TObjPlayer__sub_800FF244(u8 *arg0, u8 *arg1) {
    *arg0 = *arg1;
    *reinterpret_cast<ByteBlock_C *>(arg0 + 4) = *reinterpret_cast<const ByteBlock_C *>(arg1 + 4);
    *reinterpret_cast<s32 *>(arg0 + 0x10) = *reinterpret_cast<const s32 *>(arg1 + 0x10);
    *reinterpret_cast<s32 *>(arg0 + 0x14) = *reinterpret_cast<const s32 *>(arg1 + 0x14);
}

#pragma pop

} // extern "C"

void *TObjPlayer::create_hairmove(void *arg1, void *arg2) {
    void *o;
    o = __nw__7TObjectFUl(0x48);
    if (o != NULL) {
        o = TObjHMS_EZRope_Player__ct(o, this, arg1, arg2);
    }
    return o;
}

void TObjHMS_EZRope_Player::sub_800FF2D0() {
    Vec d;
    RopeSegment *rec;
    RopeAnchor *ang;
    Vec *pt;
    s32 n;
    s32 yaw;
    if (segment_count == 0 || segments == NULL || anchors == NULL || points == NULL) {
        return;
    }
    rec = segments;
    ang = anchors;
    pt = points;
    for (; rec->point_count >= 2; rec++, ang++) {
        for (n = rec->point_count - 1; n > 0; n--, pt++) {
            push_matrix();
            translate_matrix_vec3((u8 *)(0), (u8 *)pt);
            VecCopy(&d, pt + 1);
            subtract_vector(&d, pt);
            if (0.0f == vector_length(&d)) {
                d.x = 0.0f;
                d.y = -1.0f;
                d.z = 0.0f;
            } else {
                normalize_vector(&d);
            }
            yaw = 0;
            if (0.0f != fabs_float(d.x) + fabs_float(d.z)) {
                yaw = (s32)(lbl_8043DF40 * atan2_float(-d.x, -d.z));
                rotate_matrix_y(0, yaw);
            }
            rotate_matrix_x(0, (s32)(lbl_8043DF40 * get_scale_factor__10TObjPlayerFv(-d.y)));
            rotate_matrix_y(0, ang->yaw - yaw);
            if (n == 1) {
                if (rec->end_model != NULL) {
                    draw_chunk_object(rec->end_model);
                }
            } else if (rec->segment_model != NULL) {
                draw_chunk_object(rec->segment_model);
            }
            pop_matrix();
        }
        pt++;
    }
    if (collision_spheres != NULL) {
        saved_model_render_flags = model_render_flags;
        saved_chunk_polygon_flags_and_mask = chunk_polygon_flags_and_mask;
        saved_chunk_polygon_flags_or_mask = chunk_polygon_flags_or_mask;
        model_render_flags |= 0x10;
        set_chunk_material_override_pair(0, 0x800);
        set_constant_material((const NJS_ARGB *)ezrope_chunk_material_color_table);
        for (RopeCollisionSphere *sphere = collision_spheres; sphere->radius >= 0.0f; ++sphere) {
            f32 s;
            push_matrix();
            translate_matrix_vec3((u8 *)(0), (u8 *)&sphere->center);
            s = 0.2f * sphere->radius;
            scale_matrix(0, s, s, s);
            draw_chunk_object(lbl_8048DEF4);
            pop_matrix();
        }
        chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;
        chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask;
        model_render_flags = saved_model_render_flags;
    }
}

void TObjEZRopeBase::sub_800FF580(Vec *point, f32 segment_length) {
    Vec position = *point;
    Vec center;
    f32 collision_radius;
    s32 iterations = 16;

    for (;;) {
        f32 deepest_overlap = 0.0f;
        // A negative radius terminates the list of collision spheres.
        RopeCollisionSphere *sphere = collision_spheres;
        for (; sphere->radius >= 0.0f; ++sphere) {
            f32 clearance = 0.5f * segment_length;
            f32 radius = clearance + sphere->radius;
            f32 distance = xyz_distance(&position, &sphere->center);
            if (distance < radius) {
                f32 overlap = radius - distance;
                if (overlap > deepest_overlap) {
                    deepest_overlap = overlap;
                    collision_radius = radius;
                    VecCopy(&center, &sphere->center);
                }
            }
        }

        if (iterations <= 0 || 0.0f == deepest_overlap) {
            VecCopy(point, &position);
            return;
        }

        subtract_vector(&position, &center);
        if (0.0f == vector_length(&position)) {
            position.x = 0.0f;
            position.y = -1.0f;
            position.z = 0.0f;
        } else {
            normalize_vector(&position);
        }
        position.x *= collision_radius;
        position.y *= collision_radius;
        position.z *= collision_radius;
        vec3_add_to(&position, &center);

        // Restore the length from the preceding rope point after pushing out.
        subtract_vector(&position, point - 1);
        if (0.0f == vector_length(&position)) {
            position.x = 0.0f;
            position.y = -1.0f;
            position.z = 0.0f;
        } else {
            normalize_vector(&position);
        }
        position.x *= segment_length;
        position.y *= segment_length;
        position.z *= segment_length;
        vec3_add_to(&position, point - 1);
        --iterations;
    }
}

void TObjEZRopeBase::sub_800FF788(const Vec *offset) {
    RopeSegment *segment = segments;
    RopeAnchor *anchor = anchors;
    Vec *point = points;
    while (segment->point_count >= 2) {
        f32 length = vector_length(&segment->step);
        VecCopy(point, &anchor->position);
        ++point;

        for (s32 remaining = segment->point_count - 1; remaining > 0; --remaining, ++point) {
            vec3_add_to(point, offset);
            subtract_vector(point, point - 1);
            if (0.0f == vector_length(point)) {
                point->x = 0.0f;
                point->y = -1.0f;
                point->z = 0.0f;
            } else {
                normalize_vector(point);
            }
            point->x *= length;
            point->y *= length;
            point->z *= length;
            vec3_add_to(point, point - 1);
            if (collision_spheres != NULL) {
                sub_800FF580(point, length);
            }
        }
        ++segment;
        ++anchor;
    }
}

void TObjEZRopeBase::sub_800FF8CC(RopeSegment *source_segments, RopeAnchor *source_anchors,
                                RopeCollisionSphere *spheres) {
    s32 total_points = 0;
    segments = source_segments;
    anchors = source_anchors;
    collision_spheres = spheres;
    segment_count = 0;
    for (RopeSegment *segment = source_segments; segment->point_count >= 2; ++segment) {
        total_points += segment->point_count;
        ++segment_count;
    }

    points = static_cast<Vec *>(TQuestVmDownLoadServer::alloc(total_points * sizeof(Vec)));
    RopeSegment *segment = segments;
    RopeAnchor *anchor = anchors;
    Vec *point = points;
    for (; segment->point_count >= 2; ++segment, ++anchor) {
        Vec position = anchor->position;
        for (s32 remaining = segment->point_count; remaining > 0; --remaining, ++point) {
            VecCopy(point, &position);
            vec3_add_to(&position, &segment->step);
        }
    }
}
