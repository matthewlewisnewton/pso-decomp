#include "pso/system/BmlTextureList.h"
#include "pso/system/BmlResource.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/misc/RenderFadeState.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/system/vector.h"
#include "pso/misc/TRaderMapCore.h"
#include "pso/object/TObjFish.h"
#include "pso/object/TObjMotion.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjChara.h"
#include "pso/item/TObjContainerJungEnemy.h"
#include "pso/item/TObjContainerIdo.h"
#include "pso/item/TUnk_804B97C0.h"
#include "pso/misc/TContainerAncient01.h"
#include "pso/misc/TContainerAncient01R.h"
#include "types.h"
#include "pso/TParticleCtrl.h"
#include "pso/misc/TLobby.h"
#include "pso/npc/TObjNpcEnemy.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/item/TObjContainerJungEx_8018D900.h"
#include "pso/player/TUnk_804B6C24.h"
#include "pso/object/TObjChip.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/item/TObjContainerJungEx.h"
#include "pso/item/TObjContainerItem.h"
#include "pso/item/TObjContainerJung.h"

extern "C" {
static __declspec(section ".rodata") const char fe_obj_hako01_gj[] ATTRIBUTE_ALIGN(4) = "fe_obj_hako01.gj";
static __declspec(section ".rodata") const char fe_obj_hako01_hahen1_gj[] ATTRIBUTE_ALIGN(4) = "fe_obj_hako01_hahen1.gj";
static __declspec(section ".rodata") const char fe_obj_hako01_hahen2_gj[] ATTRIBUTE_ALIGN(4) = "fe_obj_hako01_hahen2.gj";
static __declspec(section ".rodata") const char fe_obj_hako01_light_gj[] ATTRIBUTE_ALIGN(4) = "fe_obj_hako01_light.gj";
static __declspec(section ".rodata") const char bm_obj_hako01_bml[] ATTRIBUTE_ALIGN(4) = "bm_obj_hako01.bml";
static __declspec(section ".rodata") const char fe_obj_hako02_gj[] ATTRIBUTE_ALIGN(4) = "fe_obj_hako02.gj";
static __declspec(section ".rodata") const char fe_obj_hako02_hahen1_gj[] ATTRIBUTE_ALIGN(4) = "fe_obj_hako02_hahen1.gj";
static __declspec(section ".rodata") const char fe_obj_hako02_hahen2_gj[] ATTRIBUTE_ALIGN(4) = "fe_obj_hako02_hahen2.gj";
static __declspec(section ".rodata") const char fe_obj_hako02_light_gj[] ATTRIBUTE_ALIGN(4) = "fe_obj_hako02_light.gj";
static __declspec(section ".rodata") const char fe_obj_hako02_bml[] ATTRIBUTE_ALIGN(4) = "fe_obj_hako02.bml";

const char *bm_obj_hako01_model_names[5] = {
    fe_obj_hako01_gj, fe_obj_hako01_hahen1_gj, fe_obj_hako01_hahen2_gj, fe_obj_hako01_light_gj, NULL,
};
__declspec(section ".sdata") const char *bm_obj_hako01_motion_names[1] = { NULL };
BmlResourceDescriptor TObjContainerJung__resource_descriptor = {
    bm_obj_hako01_bml, bm_obj_hako01_model_names, bm_obj_hako01_motion_names, 4, 0,
};

const char *fe_obj_hako02_model_names[5] = {
    fe_obj_hako02_gj, fe_obj_hako02_hahen1_gj, fe_obj_hako02_hahen2_gj, fe_obj_hako02_light_gj, NULL,
};
__declspec(section ".sdata") const char *fe_obj_hako02_motion_names[1] = { NULL };
// Loaded by TObjContainerJungEx::load_resource_instance.
BmlResourceDescriptor fe_obj_hako02_resource_descriptor = {
    fe_obj_hako02_bml, fe_obj_hako02_model_names, fe_obj_hako02_motion_names, 4, 0,
};

CollisionBody container_jung_collision_desc = {
    { 0.0f, 6.0f, 0.0f }, 9.0f, 9.0f, 0, 0x38003, { 0.0f, 0.0f, 0.0f }, 0.0f,
};

s32 TObjContainerJung__bml_model_resource;
s32 TObjContainerJung__bml_aux_handle;
u32 TObjContainerJungEx__resource_bundle;

static __declspec(section ".rodata") const char TObjContainerJung_class_name[] ATTRIBUTE_ALIGN(4) = "TObjContainerJung";
__declspec(section ".sdata") const char *TObjContainerJung__name = TObjContainerJung_class_name;

static __declspec(section ".rodata") const TObjChipParams container_jung_debris_desc = {
    { 0.5f, 0.03f, 0.3f }, { 0.0f, 0.0f, 0.0f }, { 3.0f, 6.0f, 3.0f }, { 0x800, 0x100, 0x800 }, { 4, 0x32 }, { 0.0f, 0.8f }, 0, 0, 0x16,
};
static __declspec(section ".rodata") const TObjChipParams container_jung_spawn_params = {
    { 0.5f, 0.03f, 0.2f }, { 0.0f, 0.0f, 0.0f }, { 3.5f, 6.0f, 3.5f }, { 0x400, 0x100, 0x400 }, { 4, 0x32 }, { 0.0f, 0.7f }, 0, 0, 0x16,
};

static __declspec(section ".rodata") const char TObjContainerJungEx_class_name[] ATTRIBUTE_ALIGN(4) = "TObjContainerJungEx";
__declspec(section ".sdata") const char *TObjContainerJungEx__name = TObjContainerJungEx_class_name;

static __declspec(section ".rodata") const TObjChipParams container_jung_ex_spawn_params_a = {
    { 0.5f, 0.07f, 0.26f }, { 0.0f, 0.0f, 0.0f }, { 5.0f, 5.0f, 5.0f }, { 0x400, 0x100, 0x400 }, { 5, 0x32 }, { 0.0f, 0.6f }, 0, 0, 0x16,
};
static __declspec(section ".rodata") const TObjChipParams container_jung_ex_spawn_params_b = {
    { 0.5f, 0.07f, 0.26f }, { 0.0f, 0.0f, 0.0f }, { 4.0f, 4.5f, 4.0f }, { 0x200, 0x100, 0x200 }, { 6, 0x32 }, { 0.0f, 0.5f }, 0, 0, 0x16,
};

static __declspec(section ".rodata") const char TObjContainerJungEnemy_class_name[] ATTRIBUTE_ALIGN(4) = "TObjContainerJungEnemy";
__declspec(section ".sdata") const char *TObjContainerJungEnemy__name = TObjContainerJungEnemy_class_name;

static __declspec(section ".rodata") const TObjChipParams container_jung_enemy_spawn_params_a = {
    { 0.5f, 0.03f, 0.2f }, { 0.0f, 0.0f, 0.0f }, { 3.0f, 5.0f, 3.0f }, { 0x800, 0x100, 0x800 }, { 7, 0x32 }, { 0.0f, 1.0f }, 0, 0, 0x16,
};
static __declspec(section ".rodata") const TObjChipParams container_jung_enemy_spawn_params_b = {
    { 0.5f, 0.03f, 0.19f }, { 0.0f, 0.0f, 0.0f }, { 3.5f, 5.0f, 3.5f }, { 0x400, 0x100, 0x400 }, { 5, 0x32 }, { 0.0f, 1.0f }, 0, 0, 0x16,
};

extern const char lbl_80445430[] = "EVT NO : %d";
// The debug string occupies the final aligned slot of the unit.
extern const char lbl_8044543C[0x14] = "MODEL SELECT";
}

extern "C" {
u32 init_collision_body_parts(void *, s32, s32);

s32 free_collision_body_parts(void *);
s32 __dl__7TObjectFPv(void *);

s32 post_translate_matrix(void *);
void draw_ginja_object(void *);
s32 rotate_matrix_y(s32, s32);
s32 push_matrix();
s32 pop_matrix();
void *__nw__7TObjectFUl(int);

extern void *tl_05;

}

struct Obj_8018CBF0 { u8 pad0[0x84]; s32 id; };

struct Obj_8018CB44 { u8 pad0[0x1C]; u16 f1C; u8 pad1[0x62]; u32 f80; s32 f84; };

struct Pkt_8018CB44 { u16 a; u16 b; s32 c; s32 d; s32 e; };

extern "C" {
void queue_destruction__7TObjectFv(void *arg0);
void debug_printf_at(s32 id, const char *fmt, ...);
s32 get_current_floor();
extern s32 local_client_id;

s32 scale_matrix(s32, f32, f32, f32);

struct Vec_8018C9F0 { f32 x, y, z; };
struct Obj_8018C9F0 {
    u8 pad0[0x24];
    s32 f24;
    u8 pad28[0x10];
    Vec_8018C9F0 pos;
    u8 pad44[0x326 - 0x44];
    s16 f326;
    u8 pad328[0x36C - 0x328];
    s32 f36c;
    s32 f370;
};

void *spawn_particle_effect_with_flags(void *pos, s32 id, s32 flags);
u8 *__ct__8TObjChipFP7TObjectP14TObjChipParams(u8 *arg0, u8 *arg1, u8 *arg2);
}
void play_container_break_sound(s32 arg0);

extern "C" {
u32 init_collision_body_parts(void *, s32, s32);
u8 * init_container_base(void *, s32);
extern s32 __vt__22TObjContainerJungEnemy[];
s32 get_model__19TObjContainerJungExFl(s32);
s32 TObjContainerJung__sub_8018D3B8(s32);
s32 get_model_by_index__17TObjContainerJungFl(s32);
s32 free_collision_body_parts(void *);
s32 submit_cursor_candidate(void *, s32);
s32 __dl__7TObjectFPv(void *);
void *__nw__7TObjectFUl(int);

extern void *tl_05;

}

struct Vec_8018CFD4 { f32 x, y, z; };

struct Obj_8018CFD4 { u8 pad[0x38]; Vec_8018CFD4 pos; };

extern "C" {
u32 init_collision_body_parts(void *, s32, s32);
u8 * init_container_base(void *, s32);

extern s32 __vt__19TObjContainerJungEx[];
void *spawn_particle_effect_with_flags(void *pos, s32 id, s32 flags);
}
void play_container_break_sound(s32 arg0);
extern "C" {
s32 get_model__19TObjContainerJungExFl(s32);
void *__nw__7TObjectFUl(int);
extern void *tl_05;
s32 post_translate_matrix(void *);
s32 scale_matrix(s32, f32, f32, f32);

s32 free_collision_body_parts(void *);
s32 submit_cursor_candidate(void *, s32);
s32 rotate_matrix_y(s32, s32);
s32 push_matrix();
s32 __dl__7TObjectFPv(void *);

}

struct Vec_8018D4DC { f32 x, y, z; };

struct Obj_8018D4DC {
    u8 pad0[0x38];
    Vec_8018D4DC pos;
    u8 pad44[0x326 - 0x44];
    s16 f326;
};

extern "C" {
u32 init_collision_body_parts(void *, s32, s32);
u8 * init_container_base(void *, s32);

extern s32 __vt__17TObjContainerJung[];
s32 scale_matrix(s32, f32, f32, f32);
s32 rotate_matrix_y(s32, s32);
s32 push_matrix();
s32 post_translate_matrix(void *);

void *spawn_particle_effect_with_flags(void *pos, s32 id, s32 flags);
}
void play_container_break_sound(s32 arg0);
extern "C" {
void *__nw__7TObjectFUl(int);
extern void *tl_05;
s32 free_collision_body_parts(void *);
s32 submit_cursor_candidate(void *, s32);
s32 __dl__7TObjectFPv(void *);

}

// Deferred generation preserves the native text and virtual table order.
#pragma defer_codegen on
extern "C" {

u8 *TObjContainerJung__ct(u8 *arg0, s32 arg1, s32 _w2) {
    init_container_base(arg0, arg1);
    *(s32 **)((s8 *)arg0 + 0x18) = __vt__17TObjContainerJung;
    *(s32 *)((s8 *)arg0 + 0) = (s32) TObjContainerJung__name;
    ((TObjContainerJung *)arg0)->mode = 0;
    ((TObjContainerJung *)arg0)->actorFlags = (s32) (((TObjContainerJung *)arg0)->actorFlags | 0x60000000);
    init_collision_body_parts(arg0, (s32) &container_jung_collision_desc, 1);
    ((TObjPlayer *)arg0)->register_object_by_id();
    VecCopy((Vec *)(arg0 + 0x74), (const Vec *)(arg0 + 0x38));
    VecCopy((Vec *)(arg0 + 0x2FC), (const Vec *)(arg0 + 0x38));
    *(f32 *)((s8 *)arg0 + 0x78) = (f32) (*(f32 *)((s8 *)arg0 + 0x78) + container_jung_collision_desc.offset.y);
    return arg0;
}

TObjContainerJung::~TObjContainerJung() {
    unregister_object_by_id();
    free_collision_body_parts(this);
}

void TObjContainerJung::vfunc_80() {

    switch (this->mode) {
    case 0:
        if ((s32) this->m_364 != 0) {
            submit_cursor_candidate(this, -1);
        }
    case 1:
        return;
    }
}

void TObjContainerJung::vfunc_81() {
    if ((void *)(*(u8 **)&TObjContainerJung__bml_model_resource) != NULL) {
        switch (this->mode) {
        case 0:
            set_current_texture_list((GinjaTextureList *)(TObjContainerJung__bml_aux_handle));
            push_matrix();
            post_translate_matrix((u8 *)&this->position);
            rotate_matrix_y(0, this->rotation.yaw);
            scale_matrix(0, 0.85f, 0.85f, 0.85f);
            draw_ginja_object((void *)(u8 *)get_bml_model((BmlResource *)*(u8 **)&TObjContainerJung__bml_model_resource, 0));
            TParticleCtrl::begin_effect_render();
            draw_ginja_object((void *)(u8 *)get_bml_model((BmlResource *)*(u8 **)&TObjContainerJung__bml_model_resource, 3));
            TParticleCtrl::end_effect_render();
            pop_matrix();
            break;
        case 1:
            break;
        }
    }
}

void TObjContainerJung::vfunc_6(s16 *arg1, s32 arg2) {
    u8 *arg0 = (u8 *)this;
    if (arg2 != 0) {
        if ((s16) *arg1 == 1) {
            this->vfunc_79();
            ((TObjChara *)arg0)->request_box_item_drop((u8 *)&this->position, 1);
            ((TObjCollidable *)arg0)->clear_player_status_flag(0, 1);
            ((TObjCollidable *)arg0)->set_flag8();
            queue_destruction__7TObjectFv((arg0));
            this->mode = 1;
        }
    } else if ((s16) *arg1 == 1) {
        ((TObjCollidable *)arg0)->clear_player_status_flag(0, 1);
        ((TObjCollidable *)arg0)->set_flag8();
        queue_destruction__7TObjectFv((arg0));
        this->mode = 1;
    }
}

#pragma push
#pragma opt_propagation off
void TObjContainerJung::vfunc_79() const {
    const Obj_8018D4DC *self = reinterpret_cast<const Obj_8018D4DC *>(this);
    void *o;
    if (self->f326 != 1) {
        TObjChipParams a = container_jung_debris_desc;
        f32 pz;
        f32 py;
        f32 px;
        px = self->pos.x;
        py = self->pos.y;
        pz = self->pos.z;
        a.pos.x = px;
        a.pos.y = py;
        a.pos.z = pz;
        a.pad_38[0] = py;
        a.model = (s32) (u8 *)get_bml_model((BmlResource *)TObjContainerJung__bml_model_resource, 1);
        a.textures = TObjContainerJung__bml_aux_handle;
        TObjChipParams b = container_jung_spawn_params;
        f32 qz;
        f32 qy;
        f32 qx;
        qx = self->pos.x;
        qy = self->pos.y;
        qz = self->pos.z;
        b.pos.x = qx;
        b.pos.y = qy;
        b.pos.z = qz;
        b.pad_38[0] = qy;
        b.model = (s32) (u8 *)get_bml_model((BmlResource *)TObjContainerJung__bml_model_resource, 2);
        b.textures = TObjContainerJung__bml_aux_handle;
        spawn_particle_effect_with_flags((void *)&self->pos, 0x45, 0x40);
        spawn_particle_effect_with_flags((void *)&self->pos, 0x46, 0x40);
        o = __nw__7TObjectFUl(0x234);
        if (o != 0) {
            __ct__8TObjChipFP7TObjectP14TObjChipParams((u8 *)o, (u8 *)tl_05, (u8 *)&a);
        }
        o = __nw__7TObjectFUl(0x234);
        if (o != 0) {
            __ct__8TObjChipFP7TObjectP14TObjChipParams((u8 *)o, (u8 *)tl_05, (u8 *)&b);
        }
        play_container_break_sound((s32)self);
    }
}
#pragma pop

void TObjContainerJung::load_resources() {
    s32 temp_r3;
    s32 var_r0;
    temp_r3 = (int)new BmlResource(5, &TObjContainerJung__resource_descriptor, 0, 0, (void *)(0));
    var_r0 = temp_r3;
    (*(u8 * *)&TObjContainerJung__bml_model_resource) = (unsigned char *) ((void *) var_r0);
    TObjContainerJung__bml_aux_handle = (s32)TObjFish__sub_8001EDB0((BmlResource *)var_r0, 0);
}

void TObjContainerJung::release() {
    delete (BmlResource *)(TObjContainerJung__bml_model_resource);
    TObjContainerJung__bml_model_resource = 0;
    TObjContainerJung__bml_aux_handle = 0;
}

void *TObjContainerJung::create(void *arg0) {
    void *o = __nw__7TObjectFUl(0x368);
    if (o != NULL) {
        o = TObjContainerJung__ct((u8 *)o, (s32)tl_05, (s32)arg0);
    }
    return o;
}

u8 *TObjContainerJung::get_model_by_index(s32 arg0) {
    if ((void *) (*(u8 * *)&TObjContainerJung__bml_model_resource) != NULL) {
        return (u8 *)get_bml_model((BmlResource *)(*(u8 * *)&TObjContainerJung__bml_model_resource), arg0);
    }
    return NULL;
}

s32 TObjContainerJung__sub_8018D3B8(s32) {
    return TObjContainerJung__bml_aux_handle;
}

u8 *TObjContainerJungEx__ct(u8 *arg0, s32 arg1, s32 _w2) {
    init_container_base(arg0, arg1);
    *(s32 **)((s8 *)arg0 + 0x18) = __vt__19TObjContainerJungEx;
    *(s32 *)((s8 *)arg0 + 0) = (s32) TObjContainerJungEx__name;
    ((TObjContainerJungEx *)arg0)->mode = 0;
    ((TObjContainerJungEx *)arg0)->actorFlags = (s32) (((TObjContainerJungEx *)arg0)->actorFlags | 0x60000000);
    init_collision_body_parts(arg0, (s32) &container_jung_collision_desc, 1);
    ((TObjPlayer *)arg0)->register_object_by_id();
    VecCopy((Vec *)(arg0 + 0x74), (const Vec *)(arg0 + 0x38));
    VecCopy((Vec *)(arg0 + 0x2FC), (const Vec *)(arg0 + 0x38));
    *(f32 *)((s8 *)arg0 + 0x78) = (f32) (*(f32 *)((s8 *)arg0 + 0x78) + container_jung_collision_desc.offset.y);
    return arg0;
}

TObjContainerJungEx::~TObjContainerJungEx() {
    unregister_object_by_id();
    free_collision_body_parts(this);
}

void TObjContainerJungEx::vfunc_80() {

    switch (this->mode) {
    case 0:
        if ((s32) this->m_364 != 0) {
            submit_cursor_candidate(this, -1);
        }
    case 1:
        return;
    }
}

void TObjContainerJungEx::vfunc_81() {

    switch (this->mode) {
    case 0:
        set_current_texture_list((GinjaTextureList *)(TObjContainerJungEx__sub_8018D900(0)));
        push_matrix();
        post_translate_matrix((u8 *)&this->position);
        rotate_matrix_y(0, this->rotation.yaw);
        scale_matrix(0, 0.85f, 0.85f, 0.85f);
        draw_ginja_object((void *)get_model__19TObjContainerJungExFl(0));
        TParticleCtrl::begin_effect_render();
        draw_ginja_object((void *)get_model__19TObjContainerJungExFl(3));
        TParticleCtrl::end_effect_render();
        pop_matrix();
    case 1:
        return;
    }
}

void TObjContainerJungEx::vfunc_6(s16 *arg1, s32 arg2) {
    u8 *arg0 = (u8 *)this;
    if (arg2 != 0) {
        if ((s16) *arg1 == 1) {
            this->vfunc_79();
            ((TUnk_804B6C24 *)arg0)->spawn_item((s32)arg0);
            ((TObjCollidable *)arg0)->set_flag8();
            queue_destruction__7TObjectFv((arg0));
            this->mode = 1;
        }
    } else if ((s16) *arg1 == 1) {
        ((TObjCollidable *)arg0)->set_flag8();
        queue_destruction__7TObjectFv((arg0));
        this->mode = 1;
    }
}

#pragma push
#pragma opt_propagation off
void TObjContainerJungEx::vfunc_79() const {
    const Obj_8018CFD4 *self = reinterpret_cast<const Obj_8018CFD4 *>(this);
    TObjChipParams a = container_jung_ex_spawn_params_a;
    f32 pz;
    f32 py;
    f32 px;
    px = self->pos.x;
    py = self->pos.y;
    pz = self->pos.z;
    a.pos.x = px;
    a.pos.y = py;
    a.pos.z = pz;
    a.pad_38[0] = py;
    a.model = get_model__19TObjContainerJungExFl(1);
    a.textures = (s32)TObjContainerJungEx__sub_8018D900(0);
    TObjChipParams b = container_jung_ex_spawn_params_b;
    f32 qz;
    f32 qy;
    f32 qx;
    qx = self->pos.x;
    qy = self->pos.y;
    qz = self->pos.z;
    b.pos.x = qx;
    b.pos.y = qy;
    b.pos.z = qz;
    b.pad_38[0] = qy;
    b.model = get_model__19TObjContainerJungExFl(2);
    b.textures = (s32)TObjContainerJungEx__sub_8018D900(0);
    spawn_particle_effect_with_flags((void *)&self->pos, 0x45, 0x40);
    spawn_particle_effect_with_flags((void *)&self->pos, 0x46, 0x40);
    void *o = __nw__7TObjectFUl(0x234);
    if (o != NULL) {
        __ct__8TObjChipFP7TObjectP14TObjChipParams((u8 *)o, (u8 *)tl_05, (u8 *)&a);
    }
    o = __nw__7TObjectFUl(0x234);
    if (o != NULL) {
        __ct__8TObjChipFP7TObjectP14TObjChipParams((u8 *)o, (u8 *)tl_05, (u8 *)&b);
    }
    play_container_break_sound((s32)self);
}
#pragma pop

void *TObjContainerJungEx::create(void *arg0) {
    void *o = __nw__7TObjectFUl(0x368);
    if (o != NULL) {
        o = TObjContainerJungEx__ct((u8 *)o, (s32)tl_05, (s32)arg0);
    }
    return o;
}

u8 *TObjContainerJungEnemy__ct(u8 *arg0, s32 arg1, s32 _w2) {
    init_container_base(arg0, arg1);
    *(s32 **)((s8 *)arg0 + 0x18) = __vt__22TObjContainerJungEnemy;
    *(s32 *)((s8 *)arg0 + 0) = (s32) TObjContainerJungEnemy__name;
    ((TObjContainerJungEnemy *)arg0)->load_models();
    ((TObjContainerJungEnemy *)arg0)->mode = 0;
    ((TObjContainerJungEnemy *)arg0)->actorFlags = (s32) (((TObjContainerJungEnemy *)arg0)->actorFlags | 0x60000000);
    init_collision_body_parts(arg0, (s32) &container_jung_collision_desc, 1);
    ((TObjPlayer *)arg0)->register_object_by_id();
    VecCopy((Vec *)(arg0 + 0x74), (const Vec *)(arg0 + 0x38));
    VecCopy((Vec *)(arg0 + 0x2FC), (const Vec *)(arg0 + 0x38));
    *(f32 *)((s8 *)arg0 + 0x78) = (f32) (*(f32 *)((s8 *)arg0 + 0x78) + container_jung_collision_desc.offset.y);
    return arg0;
}

TObjContainerJungEnemy::~TObjContainerJungEnemy() {
    unregister_object_by_id();
    free_collision_body_parts(this);
}

void *TObjContainerJungEnemy::create(void *arg0) {
    void *o = __nw__7TObjectFUl(0x378);
    if (o != NULL) {
        o = TObjContainerJungEnemy__ct((u8 *)o, (s32)tl_05, (s32)arg0);
    }
    return o;
}

void TObjContainerJungEnemy::load_models() {
    s32 var_r0;
    s32 temp_r3 = *(s32 *)&this->set_params[1];
    if (temp_r3 < 0) {
        var_r0 = 0;
    } else {
        var_r0 = 1;
        if (temp_r3 <= 1) {
            var_r0 = temp_r3;
        }
    }
    switch (var_r0) {
    case 0:
        this->m_368 = get_model_by_index__17TObjContainerJungFl(0);
        this->m_36c = get_model_by_index__17TObjContainerJungFl(1);
        this->m_370 = get_model_by_index__17TObjContainerJungFl(2);
        this->m_374 = get_model_by_index__17TObjContainerJungFl(3);
        this->texlist = TObjContainerJung__sub_8018D3B8(0);
        return;
    default:
    case 1:
        this->m_368 = get_model__19TObjContainerJungExFl(0);
        this->m_36c = get_model__19TObjContainerJungExFl(1);
        this->m_370 = get_model__19TObjContainerJungExFl(2);
        this->m_374 = get_model__19TObjContainerJungExFl(3);
        this->texlist = (s32)TObjContainerJungEx__sub_8018D900(0);
        return;
    }
}

void TObjContainerJungEnemy::vfunc_80() {

    switch (this->mode) {
    case 0:
        if ((s32) this->m_364 != 0) {
            submit_cursor_candidate(this, -1);
        }
    case 1:
        return;
    }
}

void TObjContainerJungEnemy::vfunc_81() {

    switch (this->mode) {
    case 0:
        set_current_texture_list((GinjaTextureList *)(this->texlist));
        push_matrix();
        post_translate_matrix((u8 *)&this->position);
        rotate_matrix_y(0, this->rotation.yaw);
        scale_matrix(0, 0.85f, 0.85f, 0.85f);
        draw_ginja_object(*(void * *)&this->m_368);
        TParticleCtrl::begin_effect_render();
        draw_ginja_object(*(void * *)&this->m_374);
        TParticleCtrl::end_effect_render();
        pop_matrix();
    case 1:
        return;
    }
}

void TObjContainerJungEnemy::debug_print_item_box_info() {
    Obj_8018CBF0 *self = (Obj_8018CBF0 *)this;
    ((TObjContainerJungEnemy *)self)->load_models();
    TObjNpcEnemy::set_global_count(0xFF00FF);
    debug_printf_at(0x130020, lbl_80445430, this->set_params[0]);
    debug_printf_at(0x130021, lbl_8044543C);
    TObjNpcEnemy::set_global_count(0xF0F0F0FF);
}

f32 TObjContainerJungEnemy::receive_physical_attack(void *, f32) {
    Obj_8018CB44 *arg0 = (Obj_8018CB44 *)this;
    s16 sp8;
    Pkt_8018CB44 pkt;
    if ((this->entity_id >= 0x1000U) && (arg0->f80 != 0U) && (((TObjCollidable *)arg0)->access_object_saved_state(&sp8, 1) != 0)) {
        sp8 = 1;
        ((TObjCollidable *)arg0)->access_object_saved_state(&sp8, 0);
        ((TObjCollidable *)arg0)->send_object_state_update(&sp8);
        ((TLobby *)(&pkt))->init_packet_67_04();
        pkt.b = this->entity_id;
        pkt.c = get_current_floor();
        pkt.d = this->set_params[0];
        pkt.e = local_client_id;
        ((TLobby *)(&pkt))->byteswap_and_send();
    }
    return 0.0f;
}

#pragma push
#pragma opt_propagation off
void TObjContainerJungEnemy::vfunc_79() const {
    const Obj_8018C9F0 *self = reinterpret_cast<const Obj_8018C9F0 *>(this);
    if (self->f326 != 1) {
        TObjChipParams a = container_jung_enemy_spawn_params_a;
        f32 za;
        f32 ya;
        f32 xa;
        xa = self->pos.x;
        ya = self->pos.y;
        za = self->pos.z;
        a.pos.x = xa;
        a.pos.y = ya;
        a.pos.z = za;
        a.pad_38[0] = ya;
        a.model = self->f36c;
        a.textures = self->f24;
        TObjChipParams b = container_jung_enemy_spawn_params_b;
        f32 zb;
        f32 yb;
        f32 xb;
        xb = self->pos.x;
        yb = self->pos.y;
        zb = self->pos.z;
        b.pos.x = xb;
        b.pos.y = yb;
        b.pos.z = zb;
        b.pad_38[0] = yb;
        b.model = self->f370;
        b.textures = self->f24;
        spawn_particle_effect_with_flags((void *)&self->pos, 0x45, 0x40);
        spawn_particle_effect_with_flags((void *)&self->pos, 0x46, 0x40);
        void *o = __nw__7TObjectFUl(0x234);
        if (o != 0) {
            __ct__8TObjChipFP7TObjectP14TObjChipParams((u8 *)o, (u8 *)tl_05, (u8 *)&a);
        }
        o = __nw__7TObjectFUl(0x234);
        if (o != 0) {
            __ct__8TObjChipFP7TObjectP14TObjChipParams((u8 *)o, (u8 *)tl_05, (u8 *)&b);
        }
        play_container_break_sound((s32)self);
    }
}
#pragma pop

void TObjContainerJungEnemy::vfunc_6(s16 *arg1, s32 arg2) {
    u8 *arg0 = (u8 *)this;
    if (arg2 != 0) {
        if ((s16) *arg1 == 1) {
            ((TObjContainerJungEnemy *)arg0)->vfunc_79();
            ((TObjCollidable *)arg0)->clear_player_status_flag(0, 1);
            ((TObjCollidable *)arg0)->set_flag8();
            queue_destruction__7TObjectFv((arg0));
            this->mode = 1;
        }
    } else if ((s16) *arg1 == 1) {
        ((TObjCollidable *)arg0)->clear_player_status_flag(0, 1);
        ((TObjCollidable *)arg0)->set_flag8();
        queue_destruction__7TObjectFv((arg0));
        this->mode = 1;
    }
}

}
