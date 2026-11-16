#include "pso/system/ArrayAllocation.h"
struct NJS_OBJECT;
#include "types.h"
#include "pso/enemy/TObjEneRe7Berura_803E4CE0.h"
#include "pso/misc/PhotonBlastSummon.h"
#include "pso/player/TObjPlayer_800D8A2C.h"
#include "pso/system/vector.h"
#include "pso/misc/TSceneSora.h"
#include "pso/player/TObjPlayer.h"
#include "pso/TObject.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TFogCtrl.h"
#include "pso/misc/TNowLoading.h"
#include "pso/misc/TScene.h"
#include "pso/misc/TUnk_804C3248.h"
#include "pso/map/FloorArea.h"
#include "pso/misc/CameraHelpers.h"
#pragma push

#include <stddef.h>
inline void *operator new[](size_t, void *p) { return p; }
#include "pso/TParticleCtrl.h"


struct RecoveredGlobal_801A7310_TCameraCtrl__data_804FF628 {
    s32 value;
    u8 remaining[0x8];
};

struct Ent_801A70C8 { s32 a; f32 b; s32 c; };

struct Ent_801A710C { u32 a; f32 b; s32 c; };

extern "C" {
void cache_target_and_forward__11TCameraCtrlFl(const CameraPlayback *, s32);
extern RecoveredGlobal_801A7310_TCameraCtrl__data_804FF628 TCameraCtrl__view_state;
extern struct Ent_801A70C8 deferred_photon_blast_hit_queue[32];
extern s32 deferred_photon_blast_hit_count;
extern struct Ent_801A710C photon_blast_hit_queue[32];
extern s32 photon_blast_hit_count;
extern u32 lbl_805D5D20;
const f32 *get_photon_blast_entry__10TObjPlayerFi(s32);
}
extern u32 lbl_805D5D18;

void clear_deferred_photon_blast_hits(void) {
    s32 i;
    deferred_photon_blast_hit_count = 0;
    for (i = 0; i < 32; i++) {
        deferred_photon_blast_hit_queue[i].a = 0xFFFF;
        deferred_photon_blast_hit_queue[i].b = 0.0f;
        deferred_photon_blast_hit_queue[i].c = -1;
    }
}

void clear_photon_blast_hits(void) {
    s32 i;
    photon_blast_hit_count = 0;
    for (i = 0; i < 32; i++) {
        photon_blast_hit_queue[i].a = 0xFFFF;
        photon_blast_hit_queue[i].b = 0.0f;
        photon_blast_hit_queue[i].c = -1;
    }
}

void queue_deferred_photon_blast_hit(u32 arg0, s32 arg1, s32 arg2, f32 unused) {
    s32 found = 0;
    if (deferred_photon_blast_hit_count < 0x20) {
        const f32 *e = get_photon_blast_entry__10TObjPlayerFi(arg1);
        if (arg2 == 0) {
            s32 i;
            for (i = 0; i < deferred_photon_blast_hit_count; i++) {
                if (arg0 == (u32)deferred_photon_blast_hit_queue[i].a) {
                    found = 1;
                }
            }
        }
        if (found == 0) {
            deferred_photon_blast_hit_queue[deferred_photon_blast_hit_count].c = arg1;
            deferred_photon_blast_hit_queue[deferred_photon_blast_hit_count].b = e[0];
            deferred_photon_blast_hit_queue[deferred_photon_blast_hit_count].a = arg0;
            lbl_805D5D20 = arg0;
            deferred_photon_blast_hit_count++;
        }
    }
}

void queue_photon_blast_hit(u32 identity, s32 kind, s32 allow_duplicate, f32 scale) {
    const f32 *entry;
    s32 duplicate = 0;
    s32 i;
    if (photon_blast_hit_count >= 32) {
        return;
    }
    entry = get_photon_blast_entry__10TObjPlayerFi(kind);
    if (allow_duplicate == 0) {
        for (i = 0; i < photon_blast_hit_count; i++) {
            if (photon_blast_hit_queue[i].a == identity) {
                duplicate = 1;
            }
        }
    }
    if (duplicate == 0) {
        photon_blast_hit_queue[photon_blast_hit_count].c = kind;
        photon_blast_hit_queue[photon_blast_hit_count].b = *entry;
        photon_blast_hit_queue[photon_blast_hit_count].a = identity;
        lbl_805D5D18 = identity;
        photon_blast_hit_count = photon_blast_hit_count + 1;
    }
}

void queue_deferred_photon_blast_support(u32 identity, s32 kind, s32 allow_duplicate) {
    queue_deferred_photon_blast_hit(identity, kind, allow_duplicate, 1.0f);
}

void queue_photon_blast_support(u32 identity, s32 kind, s32 allow_duplicate) {
    queue_photon_blast_hit(identity, kind, allow_duplicate, 1.0f);
}
typedef char RecoveredGlobal_801A7310_TCameraCtrl__data_804FF628_size[sizeof(RecoveredGlobal_801A7310_TCameraCtrl__data_804FF628) == 0xC ? 1 : -1];

void TUnk_804C3248::begin_photon_summon_camera(s8 arg1) {
    u8 *arg0 = (u8 *)this;
    CameraPlayback stack;
    stack.index = arg1;
    if (get_current_floor_area() == AREA_DARK_FALZ) stack.bank = 1; else stack.bank = 0;
    stack.flags = 0;
    stack.frame = 0.0f;
    stack.frame_step = 1.0f;
    if ((*(s32 *)((s8 *)&TCameraCtrl__view_state.value + 8) & 4) || (*(s32 *)((s8 *)&TCameraCtrl__view_state.value + 8) & 8)) {
        TCameraCtrl::select_active_controller(5);
    }
    cache_target_and_forward__11TCameraCtrlFl(&stack, 0x4222);
    set_scripted_camera_pose(&position, &position, &rotation);
    *(s32 *)((s8 *)arg0 + 0xFC) = 1;
}

#pragma pop

#pragma push

#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
struct ByteBlock_C { u8 bytes[0xc]; };

struct PbCameraParams_801A73B0 {
    u8 pad0[0x14];
    s32 projection;
    s32 pad18;
    Vec position;
    Vec target;
    u8 pad34[0x50 - 0x34];
};

struct Reg_801A7578 {
    PhotonAttachment *list;
    s32 count;
};

typedef struct Vec_801A7428 { f32 x, y, z; } Vec_801A7428;

struct Rec_801A7428 { s32 a, b, c; Vec_801A7428 v; s32 d; };

struct PhotonAttachmentSpec {
    s32 effect_id, arg1, arg2, joint;
    s32 rotation[3];
    s32 flags;
};

struct Group_801A7428 {
    PhotonAttachmentSpec *attachments;
    u32 attachment_count;
    Rec_801A7428 *entries;
    s32 count;
};

struct Obj_801A7428 {
    u8 pad0[0x38];
    Vec_801A7428 pos;
    u8 pad44[0x60 - 0x44];
    s32 f60;
};

extern "C" {
void set_active_camera_pose_from_params(u8 *arg0);
void approach_vector_fixed_distance(Vec *, Vec *, Vec *, f32);
void update_photon_blast_camera_pose(TUnk_804C3248 *self, f32 unused);
void transform_point_to_view(Vec *, Vec *);
extern Vec lbl_80446A44;
extern struct Reg_801A7578 photon_blast_joint_origins[];
extern s32 photon_blast_joint_index;
void *create_timed_particle_emitter(void *owner, s32 id, s32 b, s32 c);
void *find_entity_by_id(u16 id);
void matrix_mult_vec(s32, Vec_801A7428 *, Vec_801A7428 *);
void rotate_matrix_y(s32, s32);
s32 push_matrix_from(void *src);
s32 pop_matrices(s32 arg0);
extern Group_801A7428 photon_blast_attachment_table[];
extern u8 identity_matrix[];
void update_photon_blast_camera_pose(TUnk_804C3248 *self, f32 unused) {
    struct PbCameraParams_801A73B0 parameters;
    approach_vector_fixed_distance(&self->camera_position, &self->camera_destination_position, &self->camera_position, 0.48f);
    approach_vector_fixed_distance(&self->camera_target, &self->camera_destination_target, &self->camera_target, 0.55f);
    VecCopy((Vec *)&parameters.position, (const Vec *)&self->camera_position);
    VecCopy((Vec *)&parameters.target, (const Vec *)&self->camera_target);
    parameters.projection = 0x4222;
    set_active_camera_pose_from_params((u8 *)&parameters);
}

void spawn_photon_blast_opening_effects(s32 arg0, s32 arg1) {
    Rec_801A7428 rec;
    Vec_801A7428 pos;
    Obj_801A7428 *obj;
    Group_801A7428 *g;
    Rec_801A7428 *entries;
    s32 count;
    s32 i;
    obj = (Obj_801A7428 *)find_entity_by_id(arg1);
    if (obj == NULL) {
        return;
    }
    g = &photon_blast_attachment_table[arg0];
    count = g->count;
    if (count <= 0) {
        return;
    }
    entries = g->entries;
    for (i = 0; i < count; i++) {
        copy_effect_params((u8 *)&rec, (u8 *)&entries[i]);
        push_matrix_from(identity_matrix);
        rotate_matrix_y(0, obj->f60);
        matrix_mult_vec(0, &rec.v, &pos);
        pop_matrices(1);
        pos.x += obj->pos.x;
        pos.y += 30.0f + obj->pos.y;
        pos.z += obj->pos.z;
        create_timed_particle_emitter(&pos, rec.a, rec.b, rec.c);
    }
}
}

void copy_effect_params(u8 *arg0, u8 *arg1) {
    *(s32 *)((s8 *)arg0 + 0) = (s32) *(s32 *)((s8 *)arg1 + 0);
    *(s32 *)((s8 *)arg0 + 4) = (s32) *(s32 *)((s8 *)arg1 + 4);
    *(s32 *)((s8 *)arg0 + 8) = (s32) *(s32 *)((s8 *)arg1 + 8);
    *(ByteBlock_C *)((s32) arg0 + 0xC) = *(const ByteBlock_C *)((s32) arg1 + 0xC);
    *(s32 *)((s8 *)arg0 + 0x18) = (s32) *(s32 *)((s8 *)arg1 + 0x18);
}
void publish_photon_blast_joint_origins(NJS_OBJECT *) {
    s32 i;
    for (i = 0; i < photon_blast_joint_origins->count; i++) {
        PhotonAttachment *node = &photon_blast_joint_origins->list[i];
        if (photon_blast_joint_index == node->joint_index) {
            Vec origin = lbl_80446A44;
            transform_point_to_view(&origin, &node->position);
        }
    }
    photon_blast_joint_index += 1;
}

#pragma pop

#pragma push

struct PhotonAngles { s32 x, y, z; };

extern Vec_801A7428 lbl_80446A38;
extern "C" {
void rotate_matrix_x(s32, s32);
void rotate_matrix_z(s32, s32);
}
void direction_to_rotation_xz(u8 *, s32 *, s32 *);
void *create_timed_particle_emitter_with_angles(void *, void *, s32, s32, s32, s32);

extern "C" {


void TObjPlayer::clear_render_context() { set_chunk_model_node_callback(0); }

void TUnk_804C3248::set_photon_blast_joint_callback() {
    photon_blast_joint_index = 0;
    photon_blast_joint_origins[0].list = m_148;
    photon_blast_joint_origins[0].count = m_100;
    set_chunk_model_node_callback(publish_photon_blast_joint_origins);
}

void TUnk_804C3248::update_photon_blast_attachments() {
    u32 i;
    PhotonAttachment *e;
    for (i = 0; i < m_100; i++) {
        if (m_148[i].particle->all_parents_unqueued_for_destruction() == 0) {
            m_148[i].particle = NULL;
        }
        e = &m_148[i];
        if (e->particle != NULL) {
            if (e->joint_index >= 0) {
                e->particle->set_position(&e->position);
            } else {
                e->particle->set_position(&position);
            }
        }
    }
}

void TUnk_804C3248::free_photon() { if (m_148) ::operator delete[](m_148); }

#pragma push
#pragma inline_depth(1)
#pragma dont_inline off
#pragma auto_inline off
void spawn_photon_blast_attachment_effects(TUnk_804C3248 *self, s32 kind) {
    Group_801A7428 *group = &photon_blast_attachment_table[kind];
    self->m_100 = group->attachment_count;
    if (self->m_100 != 0) {
        struct { s32 arg1; s32 arg2; s32 effect_id; } params;
        PhotonAngles rotation;
        PhotonAttachmentSpec *spec;
        PhotonAttachmentSpec *specs;
        u32 i;
        self->m_148 = new (::operator new[](self->m_100 * sizeof(PhotonAttachment))) PhotonAttachment[self->m_100];
        specs = group->attachments;
        for (i = 0; i < self->m_100; i++) {
            spec = &specs[i];
            params.arg1 = spec->arg1;
            params.arg2 = spec->arg2;
            params.effect_id = spec->effect_id;
            copy_xyz(&rotation, spec->rotation);
            s32 flags = spec->flags;
            s32 angles[3];
            Vec_801A7428 direction = lbl_80446A38;
            if (rotation.z || rotation.x || rotation.y) {
                push_matrix_from(identity_matrix);
                rotate_matrix_z(0, rotation.z);
                rotate_matrix_x(0, rotation.x);
                rotate_matrix_y(0, rotation.y);
                matrix_mult_vec(0, &direction, &direction);
                pop_matrices(1);
                push_matrix_from(identity_matrix);
                rotate_matrix_y(0, self->rotation.yaw);
                matrix_mult_vec(0, &direction, &direction);
                pop_matrices(1);
                direction_to_rotation_xz((u8 *)&direction, &angles[0], &angles[2]);
                angles[1] = 0;
            } else {
                angles[0] = 0;
                angles[1] = 0;
                angles[2] = 0;
            }
            self->m_148[i].particle = (TParticleCtrl *)create_timed_particle_emitter_with_angles(&self->position, &angles, params.effect_id, params.arg1, params.arg2, flags & 0xffff);
            self->m_148[i].joint_index = spec->joint;
            copy_xyz(self->m_148[i].rotation, &rotation);
        }
    }
}

#pragma pop

s32 update_all_default__8TFogCtrlFv(TUnk_804C3248 *) { return TFogCtrl::update_all(0); }
void apply_all_default__8TFogCtrlFv(TUnk_804C3248 *) { TFogCtrl::apply_all(63, 0); }

#pragma pop

#pragma push
extern s32 TSceneSora__sky_active_flag;
extern u32 TSceneSora__instance;
u16 TCameraCtrl__sub_8006A5DC();


s32 queue_destruction__7TObjectFv(void *);
void allow_rendering__7TObjectFv(TObject *arg0);

void disallow_rendering__7TObjectFv(TObject *arg0);

extern void *tl_05;

void TUnk_804C3248::update_if_active() {
    if (!(*(s32 *)&this->unk_154 & 1)) {
        TCameraCtrl::update();
        TSceneSora::update((s32)this);
        update_all_default__8TFogCtrlFv(this);
        TObjPlayer__sub_800D8A6C();
    }
    if (tl_05 != 0) {
        allow_rendering__7TObjectFv((TObject *)tl_05);
    }
}

void TUnk_804C3248::enter_scene() {
    s32 arg0 = (s32)this;
    setup_photon_blast_camera();
    reset_state__10TSceneSoraFv(arg0);
    apply_all_default__8TFogCtrlFv(this);
    TObjPlayer__sub_800D8A60();
    if (tl_05 != NULL) {
        disallow_rendering__7TObjectFv((TObject *)tl_05);
    }
}
void TSceneSora::update(s32 _w0) {
    TScene::set_ready();
    if ((u32) TSceneSora__instance != 0U) {
        TSceneSora__sky_active_flag = 1;
    }
}
void reset_state__10TSceneSoraFv(s32 _w0) {
    TScene::reset_counter();
    if ((u32) TSceneSora__instance != 0U) {
        TSceneSora__sky_active_flag = 0;
    }
}
void TUnk_804C3248::update_state() {
    switch (*(s32 *)((s8 *)this + 0xFC)) {
    case 0:
        update_photon_blast_camera_pose(this, 1.0f);
        return;
    case 1:
        if ((get_scripted_camera_playback()->flags & 1) || (TCameraCtrl__sub_8006A5DC() != 5)) {
            queue_destruction__7TObjectFv(this);
        }
        return;
    }
}

#pragma pop

#pragma push
s32 restore_player_cameras(void);
void __ct__10TObjMotionFP7TObject(void *, void *);
void __dl__7TObjectFPv(void *);
void *__dt__10TObjMotionFv(void *arg0, s16 arg1);

void TCameraCtrl::update() { restore_player_cameras(); TCameraCtrl::release_photon_blast_camera(); }

extern s32 lbl_804C3248[];

struct Vec_801A7B14
{
  f32 x;
  f32 y;
  f32 z;
};

s32 activate_camera_mode(s32 arg0);
void *get_player_by_client_id(s32 i);

extern Vec_801A7B14 lbl_80446A08;
extern Vec_801A7B14 lbl_80446A14;
extern Vec_801A7B14 lbl_80446A20;
extern Vec_801A7B14 lbl_80446A2C;
extern s32 local_client_id;
void TUnk_804C3248::setup_photon_blast_camera() {
    u8 *arg0 = (u8 *)this;
  Vec_801A7B14 a = lbl_80446A08;
  Vec_801A7B14 b = lbl_80446A14;
  Vec_801A7B14 c = lbl_80446A20;
  Vec_801A7B14 d = lbl_80446A2C;
  u8 *p;
  if ((*((s32 *)(arg0 + 0x138))) == 0)
  {
    b.x = -8.75f;
    b.y = 43.92f;
    b.x = 28.79f;
    d.x = 0.0f;
    d.y = 39.0f;
    d.x = 0.0f;
  }
  p = (u8 *)get_player_by_client_id(local_client_id);
  if (p != 0)
  {
    push_matrix_from(identity_matrix);
    rotate_matrix_y(0, *((s32 *)(p + 0x60)));
    ((void (*)(s32, void *, void *))matrix_mult_vec)(0, &a, &a);
    ((void (*)(s32, void *, void *))matrix_mult_vec)(0, &b, &b);
    ((void (*)(s32, void *, void *))matrix_mult_vec)(0, &c, &c);
    ((void (*)(s32, void *, void *))matrix_mult_vec)(0, &d, &d);
    pop_matrices(1);
    a.x += *((f32 *)(p + 0x38));
    a.y += *((f32 *)(p + 0x3C));
    a.z += *((f32 *)(p + 0x40));
    b.x += *((f32 *)(p + 0x38));
    b.y += *((f32 *)(p + 0x3C));
    b.z += *((f32 *)(p + 0x40));
    c.x += *((f32 *)(p + 0x38));
    c.y += *((f32 *)(p + 0x3C));
    c.z += *((f32 *)(p + 0x40));
    d.x += *((f32 *) (p - -0x38));
    d.y += *((f32 *)(p + 0x3C));
    d.z += *((f32 *)(p + 0x40));
    VecCopy(&camera_position, (const Vec *)&a);
    VecCopy(&camera_destination_position, (const Vec *)&b);
    VecCopy(&camera_target, (const Vec *)&c);
    VecCopy(&camera_destination_target, (const Vec *)&d);
    activate_camera_mode(9);
  }
}

void *__dt__13TUnk_804C3248Fv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = lbl_804C3248;
        ((TUnk_804C3248 *)arg0)->m_148 = 0;
        __dt__10TObjMotionFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

extern void *tl_06;

void *photon_base_ct(void *arg0) {
    __ct__10TObjMotionFP7TObject(arg0, tl_06);
    *(s32 **)((s8 *)arg0 + 0x18) = lbl_804C3248;
    ((TUnk_804C3248 *)arg0)->m_134 = 0;
    ((TUnk_804C3248 *)arg0)->m_100 = 0;
    *(u32 *)((s8 *)arg0 + 0x138) = 0;
    ((TUnk_804C3248 *)arg0)->m_150 = 1.0f;
    *(u32 *)((s8 *)arg0 + 0x154) = 0;
    ((TUnk_804C3248 *)arg0)->m_13c = 0.0f;
    *(f32 *)((s8 *)arg0 + 0x140) = 0.0f;
    ((TUnk_804C3248 *)arg0)->m_144 = 0.0f;
    ((TUnk_804C3248 *)arg0)->m_148 = 0;
    *(u16 *)((s8 *)arg0 + 0x14C) = 0;
    *(u32 *)((s8 *)arg0 + 0xFC) = 0;
    ((TUnk_804C3248 *)arg0)->camera_target.x = 0.0f;
    ((TUnk_804C3248 *)arg0)->camera_target.y = 0.0f;
    ((TUnk_804C3248 *)arg0)->camera_target.z = 0.0f;
    ((TUnk_804C3248 *)arg0)->camera_position.x = 0.0f;
    ((TUnk_804C3248 *)arg0)->camera_position.y = 0.0f;
    ((TUnk_804C3248 *)arg0)->camera_position.z = 0.0f;
    ((TUnk_804C3248 *)arg0)->camera_destination_target.x = 0.0f;
    ((TUnk_804C3248 *)arg0)->camera_destination_target.y = 0.0f;
    ((TUnk_804C3248 *)arg0)->camera_destination_target.z = 1.0f;
    ((TUnk_804C3248 *)arg0)->camera_destination_position.x = 0.0f;
    ((TUnk_804C3248 *)arg0)->camera_destination_position.y = 0.0f;
    ((TUnk_804C3248 *)arg0)->camera_destination_position.z = 1.0f;
    return arg0;
}

}

#pragma pop

extern "C" {
PhotonAttachmentSpec lbl_804C2438[10] = {
    {0x136, 0x1e, 0x14, 0x27, {0, 0, 0}, 0},
    {0x137, 0x14, 0x28, 0x11, {0, 0, 0}, 0},
    {0x137, 0x14, 0x28, 0x1b, {0, 0, 0}, 0},
    {0x138, 0x2d, 1, 0x27, {0, 0, 0}, 0},
    {0x139, 0xa, 0x32, 0x27, {0, 0, 0}, 0},
    {0x13a, 0x34, 0x14, 0x27, {0, 0, 0}, 0},
    {0x13b, 0x34, 0x14, 0x27, {0, 0, 0}, 0},
    {0x13d, 0x39, 1, 0x27, {0, 0, 0}, 0},
    {0x13c, 0x6b, 1, -2, {0, 0, 0}, 0},
    {0x140, 0x6b, 1, -2, {0, 0, 0}, 0},
};

PhotonAttachmentSpec lbl_804C2578[9] = {
    {0x130, 0xa, 0x42, 0x21, {0, 0, 0}, 0},
    {0x131, 0x37, 0xf, 0x21, {0, 0, 0}, 0},
    {0x132, 0x37, 0x14, 0x21, {0, 0, 0}, 0},
    {0x132, 0x55, 3, 0x21, {0x4000, 0, 0}, 0},
    {0x133, 0x39, 1, 0x21, {0, 0, 0}, 0},
    {0x133, 0x4b, 1, 0x21, {0x4000, 0, 0}, 0},
    {0x141, 0x5a, 0x28, 4, {0, 0, 0}, 0},
    {0x141, 0x87, 5, 4, {0, 0, 0}, 0},
    {0x141, 0x91, 2, 4, {0, 0, 0}, 0},
};

PhotonAttachmentSpec lbl_804C2698[32] = {
    {0x154, 1, 0x73, 0x15, {0, 0, 0}, 0},
    {0x155, 2, 0x73, 0x15, {0, 0, 0}, 0},
    {0x154, 1, 0x73, 0x1c, {0, 0, 0}, 0},
    {0x155, 2, 0x73, 0x1c, {0, 0, 0}, 0},
    {0x154, 1, 0x6e, 0x22, {0, 0, 0}, 0},
    {0x155, 2, 0x6e, 0x22, {0, 0, 0}, 0},
    {0x154, 1, 0x6e, 0x29, {0, 0, 0}, 0},
    {0x155, 2, 0x6e, 0x29, {0, 0, 0}, 0},
    {0x154, 1, 0x6e, 0x37, {0, 0, 0}, 0},
    {0x155, 2, 0x6e, 0x37, {0, 0, 0}, 0},
    {0x154, 1, 0x6e, 0x3e, {0, 0, 0}, 0},
    {0x155, 2, 0x6e, 0x3e, {0, 0, 0}, 0},
    {0x154, 1, 0x6e, 0x31, {0, 0, 0}, 0},
    {0x155, 2, 0x6e, 0x31, {0, 0, 0}, 0},
    {0x154, 1, 0x6e, 0x46, {0, 0, 0}, 0},
    {0x155, 2, 0x6e, 0x46, {0, 0, 0}, 0},
    {0x154, 1, 0x73, 0x4e, {0, 0, 0}, 0},
    {0x155, 2, 0x73, 0x4e, {0, 0, 0}, 0},
    {0x158, 1, 1, 2, {0, 0, 0}, 0},
    {0x158, 0x3c, 1, 2, {0, 0, 0}, 0},
    {0x15b, 1, 1, 2, {0, 0, 0}, 0},
    {0x15b, 0x3c, 1, 2, {0, 0, 0}, 0},
    {0x15e, 0x6a, 1, 0xc, {0, 0, 0}, 0},
    {0x15e, 0x6c, 1, 0xc, {0, 0, 0}, 0},
    {0x159, 0x6c, 7, 0xc, {0, 0x8000, 0}, 0},
    {0x156, 0x75, 1, 0x4e, {0, 0x8000, 0}, 0},
    {0x157, 0x75, 1, 0x4e, {0, 0x8000, 0}, 0},
    {0x156, 0x77, 1, 0x4e, {0, 0x8000, 0}, 0},
    {0x157, 0x77, 1, 0x4e, {0, 0x8000, 0}, 0},
    {0x156, 0x79, 1, 0x4e, {0, 0x8000, 0}, 0},
    {0x157, 0x79, 1, 0x4e, {0, 0x8000, 0}, 0},
    {0x174, 0x6a, 1, 0x4e, {0, 0, 0}, 0},
};

PhotonAttachmentSpec lbl_804C2A98[6] = {
    {0x164, 0x4e, 1, 0x21, {0, 0, 0}, 0},
    {0x167, 1, 0x6e, 0x25, {0, 0, 0}, 0},
    {0x167, 1, 0x6e, 0x29, {0, 0, 0}, 0},
    {0x168, 0x57, 1, 5, {0, 0, 0}, 0},
    {0x168, 0x59, 1, 5, {0, 0, 0}, 0},
    {0x166, 1, 1, 5, {0, 0, 0}, 0},
};

PhotonAttachmentSpec lbl_804C2B58[6] = {
    {0x164, 0x58, 1, 0x21, {0, 0, 0}, 0},
    {0x167, 1, 0x6e, 0x25, {0, 0, 0}, 0},
    {0x167, 1, 0x6e, 0x29, {0, 0, 0}, 0},
    {0x168, 0x57, 1, 5, {0, 0, 0}, 0},
    {0x168, 0x59, 1, 5, {0, 0, 0}, 0},
    {0x166, 1, 1, 5, {0, 0, 0}, 0},
};

PhotonAttachmentSpec lbl_804C2C18[6] = {
    {0x152, 0x6d, 0xf, 0x11, {0, 0, 0}, 0},
    {0x152, 0x7c, 0xf, 0xc, {0, 0, 0}, 0},
    {0x165, 1, 1, 0x31, {0, 0, 0}, 0},
    {0x15b, 1, 1, 0x31, {0, 0, 0}, 0},
    {0x173, 0x42, 0x36, 0x1e, {0, 0, 0}, 0},
    {0x173, 0x42, 0x36, 0x28, {0, 0, 0}, 0},
};

PhotonAttachmentSpec lbl_804C2CD8[19] = {
    {0x15c, 1, 0x6e, 0x22, {0, 0, 0}, 0},
    {0x15c, 1, 0x6e, 0x23, {0, 0, 0}, 0},
    {0x15d, 0x55, 0x16, 0xc, {-0x4000, -0x38e, 0}, 0},
    {0x15d, 0x55, 0x16, 0x11, {-0x4000, 0x38e, 0}, 0},
    {0x159, 0x57, 0xc, 7, {0x4000, 0, 0}, 0},
    {0x175, 0x5f, 1, 7, {0, 0, 0}, 0},
    {0x175, 0x64, 1, 7, {0, 0, 0}, 0},
    {0x175, 0x6e, 1, 7, {0, 0, 0}, 0},
    {0x163, 0x18, 2, 0x1d, {0, 0, 0}, 0},
    {0x163, 0x3a, 2, 7, {0, 0, 0}, 0},
    {0x162, 0x3b, 2, 7, {0, 0, 0}, 0},
    {0x163, 0x55, 2, 0x1d, {0, 0, 0}, 0},
    {0x15a, 5, 1, 7, {0, 0, 0}, 0},
    {0x172, 4, 1, 7, {0, 0, 0}, 0},
    {0x15b, 6, 1, 7, {0, 0, 0}, 0},
    {0x15a, 0x41, 1, 7, {0, 0, 0}, 0},
    {0x172, 0x3f, 1, 7, {0, 0, 0}, 0},
    {0x15b, 0x40, 1, 7, {0, 0, 0}, 0},
    {0x174, 0x6c, 1, 7, {0, 0, 0}, 0},
};

Rec_801A7428 lbl_804C2F38[4] = {
    {0x13e, 0, 1, {0.0f, 40.0f, 0.0f}, 0},
    {0x13f, 0, 0x1e, {0.0f, 0.0f, 0.0f}, 0},
    {0x142, 0xa, 0x14, {0.0f, 40.0f, 0.0f}, 0},
    {0x143, 0x14, 0xa, {0.0f, 40.0f, 0.0f}, 0},
};

Rec_801A7428 lbl_804C2FA8[4] = {
    {0x13e, 0, 1, {0.0f, 20.0f, 50.0f}, 0},
    {0x13f, 0, 0x1e, {0.0f, 0.0f, 50.0f}, 0},
    {0x142, 0xa, 0x14, {0.0f, 20.0f, 50.0f}, 0},
    {0x143, 0x14, 0xa, {0.0f, 20.0f, 50.0f}, 0},
};

Rec_801A7428 lbl_804C3018[4] = {
    {0x13e, 0, 1, {0.0f, 40.0f, 0.0f}, 0},
    {0x13f, 0, 0x1e, {0.0f, 0.0f, 0.0f}, 0},
    {0x142, 0xa, 0x14, {0.0f, 40.0f, 0.0f}, 0},
    {0x143, 0x14, 0xa, {0.0f, 40.0f, 0.0f}, 0},
};

Rec_801A7428 lbl_804C3088[4] = {
    {0x13e, 0, 1, {0.0f, 40.0f, 0.0f}, 0},
    {0x13f, 0, 0x1e, {0.0f, 0.0f, 0.0f}, 0},
    {0x142, 0xa, 0x14, {0.0f, 40.0f, 0.0f}, 0},
    {0x143, 0x14, 0xa, {0.0f, 40.0f, 0.0f}, 0},
};

Rec_801A7428 lbl_804C30F8[4] = {
    {0x13e, 0, 1, {0.0f, 40.0f, 0.0f}, 0},
    {0x13f, 0, 0x1e, {0.0f, 0.0f, 0.0f}, 0},
    {0x142, 0xa, 0x14, {0.0f, 40.0f, 0.0f}, 0},
    {0x143, 0x14, 0xa, {0.0f, 40.0f, 0.0f}, 0},
};

Rec_801A7428 lbl_804C3168[4] = {
    {0x13e, 0, 1, {0.0f, 40.0f, 0.0f}, 0},
    {0x13f, 0, 0x1e, {0.0f, 0.0f, 0.0f}, 0},
    {0x142, 0xa, 0x14, {0.0f, 40.0f, 0.0f}, 0},
    {0x143, 0x14, 0xa, {0.0f, 40.0f, 0.0f}, 0},
};

Group_801A7428 photon_blast_attachment_table[7] = {
    {lbl_804C2C18, 6, lbl_804C30F8, 4},
    {lbl_804C2CD8, 19, lbl_804C3168, 4},
    {lbl_804C2578, 9, lbl_804C2FA8, 4},
    {lbl_804C2438, 10, lbl_804C2F38, 4},
    {lbl_804C2698, 32, lbl_804C3018, 4},
    {lbl_804C2A98, 6, lbl_804C3088, 4},
    {lbl_804C2B58, 6, lbl_804C3088, 4},
};
}

Reg_801A7578 photon_blast_joint_origins[1];
Ent_801A710C photon_blast_hit_queue[32];
Ent_801A70C8 deferred_photon_blast_hit_queue[32];

extern "C" {
s32 photon_blast_joint_index;
}
