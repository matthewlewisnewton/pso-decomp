// Reverse definitions with deferred emission preserve function and native vtable order.
#pragma auto_inline off
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

extern "C" {
extern const char lbl_8043DF18[] = "TObjEZRopeBase";
extern const char lbl_8043DF28[] = "TObjHMS_EZRope_Player";

const char *TObjEZRopeBase__name = lbl_8043DF18;
const char *TObjHMS_EZRope_Player__name = lbl_8043DF28;
static NJS_ARGB ezrope_chunk_material_color_table = { 0.5f, 1.0f, 1.0f, 0.5f };
static RopeAnchor ezrope_default_anchor = { 0, { 0.0f, 0.0f, 0.0f } };
static RopeCollisionSphere ezrope_default_collision_sphere = { 0.0f, { 0.0f, 0.0f, 0.0f } };
Vec TObjEZBoneRotPlayer__chain_gravity = { 0.0f, -0.75f, 0.0f };

struct ByteBlock_C { u8 bytes[0xc]; };

void TObjPlayer__sub_800FF220(s32 *arg0, s32 *arg1);
void TObjPlayer__sub_800FF1FC(f32 *arg0, f32 *arg1);
void TObjPlayer__sub_800FF244(u8 *arg0, u8 *arg1);

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

extern u8 lbl_8048DEF4[];
extern s32 saved_model_render_flags;
extern s32 saved_chunk_polygon_flags_and_mask;
extern s32 saved_chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_and_mask;
extern s32 model_render_flags;

TObjEZRopeBase::TObjEZRopeBase(TObject *parent) : TObject(parent) {
    m_name = TObjEZRopeBase__name;
    segment_count = 0;
    segments = NULL;
    anchors = NULL;
    collision_spheres = NULL;
    points = NULL;
}

TObjEZRopeBase::~TObjEZRopeBase() {
    if (points != NULL) {
        TAdSinglePlyChrSelectGC::safe_free(points);
        points = NULL;
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
                yaw = (s32)(10430.38043493439 * atan2_float(-d.x, -d.z));
                rotate_matrix_y(0, yaw);
            }
            rotate_matrix_x(0, (s32)(10430.38043493439 * get_scale_factor__10TObjPlayerFv(-d.y)));
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
        set_constant_material(&ezrope_chunk_material_color_table);
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

void *TObjPlayer::create_hairmove(void *arg1, void *arg2) {
    return new TObjHMS_EZRope_Player(this, arg1, arg2);
}

#pragma push
#pragma inline_depth(1)
#pragma dont_inline off
void TObjPlayer__sub_800FF244(u8 *arg0, u8 *arg1) {
    *arg0 = *arg1;
    *reinterpret_cast<ByteBlock_C *>(arg0 + 4) = *reinterpret_cast<const ByteBlock_C *>(arg1 + 4);
    *reinterpret_cast<s32 *>(arg0 + 0x10) = *reinterpret_cast<const s32 *>(arg1 + 0x10);
    *reinterpret_cast<s32 *>(arg0 + 0x14) = *reinterpret_cast<const s32 *>(arg1 + 0x14);
}

void TObjPlayer__sub_800FF220(s32 *arg0, s32 *arg1) {
    *arg0 = *arg1;
    *reinterpret_cast<ByteBlock_C *>(reinterpret_cast<u8 *>(arg0) + 4) =
        *reinterpret_cast<const ByteBlock_C *>(reinterpret_cast<const u8 *>(arg1) + 4);
}

void TObjPlayer__sub_800FF1FC(f32 *arg0, f32 *arg1) {
    *arg0 = *arg1;
    *reinterpret_cast<ByteBlock_C *>(reinterpret_cast<u8 *>(arg0) + 4) =
        *reinterpret_cast<const ByteBlock_C *>(reinterpret_cast<const u8 *>(arg1) + 4);
}
#pragma pop

TObjHMS_EZRope_Player::TObjHMS_EZRope_Player(TObjPlayer *arg1, void *arg2, void *arg3)
    : TObjEZRopeBase(arg1) {
    s32 n1;
    s32 n2;
    RopePlayerSphereSource *q;
    RopePlayerSegmentSource *p;
    n1 = 0;
    n2 = 0;
    m_name = TObjHMS_EZRope_Player__name;
    player = arg1;
    segment_sources = (RopePlayerSegmentSource *)arg2;
    sphere_sources = (RopePlayerSphereSource *)arg3;
    for (p = segment_sources; p->type >= 0; p++, n1++) {
    }
    if (sphere_sources != NULL) {
        for (q = sphere_sources; q->type >= 0; q++, n2++) {
        }
    }
    segment_storage = static_cast<RopeSegment *>(TQuestVmDownLoadServer::alloc((n1 + 1) * sizeof(RopeSegment)));
    anchor_storage = static_cast<RopeAnchor *>(TQuestVmDownLoadServer::alloc(n1 * sizeof(RopeAnchor)));
    if (n2 == 0) {
        sphere_storage = NULL;
    } else {
        sphere_storage = static_cast<RopeCollisionSphere *>(TQuestVmDownLoadServer::alloc((n2 + 1) * sizeof(RopeCollisionSphere)));
    }
    {
        RopePlayerSegmentSource *p3;
        RopeSegment *d3;
        RopeAnchor *e3;
        d3 = segment_storage;
        p3 = segment_sources;
        e3 = anchor_storage;
        for (; p3->type >= 0; p3++, d3++, e3++) {
            TObjPlayer__sub_800FF244((u8 *)d3, p3->data);
            TObjPlayer__sub_800FF220(&e3->yaw, &ezrope_default_anchor.yaw);
        }
        d3->point_count = -1;
    }
    if (sphere_storage != NULL) {
        RopePlayerSphereSource *q4 = sphere_sources;
        RopeCollisionSphere *e4 = sphere_storage;
        for (; q4->type >= 0; q4++, e4++) {
            TObjPlayer__sub_800FF1FC(&e4->radius, &ezrope_default_collision_sphere.radius);
        }
        TObjPlayer__sub_800FF1FC(&e4->radius, &ezrope_default_collision_sphere.radius);
    }
    sub_800FF8CC(segment_storage, anchor_storage, sphere_storage);
}

TObjHMS_EZRope_Player::~TObjHMS_EZRope_Player() {
    if (segment_storage != NULL) {
        TAdSinglePlyChrSelectGC::safe_free(segment_storage);
        segment_storage = NULL;
    }
    if (anchor_storage != NULL) {
        TAdSinglePlyChrSelectGC::safe_free(anchor_storage);
        anchor_storage = NULL;
    }
    if (sphere_storage != NULL) {
        TAdSinglePlyChrSelectGC::safe_free(sphere_storage);
        sphere_storage = NULL;
    }
}

} // extern "C"
