#include "types.h"
#include "pso/misc/TLobby_8030A6A8.h"
#include "pso/misc/TOContainerAncientEnemyRare.h"
#include "pso/misc/TOContainerAncientEnemyCommon.h"
#include "pso/system/BmlTextureList.h"
#include "pso/system/BmlResource.h"
#include "pso/misc/ParticleFactory.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/render/render_util.h"
#include "pso/system/NinjaTypes.h"
#include "pso/system/vector.h"
#include "pso/object/TObjMotion.h"
#include "pso/player/TUnk_804B6C24.h"
#include "pso/misc/TOContainerAncientEnemy.h"
#include "pso/TParticleCtrl.h"
#include "pso/misc/TLobby.h"
#include "pso/npc/TObjNpcEnemy.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"
#include "pso/misc/TOContainerAncientItemRare.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/misc/TOContainerAncientItemNone.h"
#include "pso/misc/TOContainerAncientItemNone_8015BF38.h"
#include "pso/player/TObjChara.h"
#include "pso/player/TUnk_804B08BC.h"
#include "pso/unk/text_8015C048.h"
#include "pso/unk/text_8015C534.h"
#include "pso/object/TObjChip.h"
#include "pso/system/GinjaMaterial.h"
#include "pso/unk/text_80087278.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/misc/TOContainerAncientItemCommon.h"
#include "pso/item/TObjContainerItem.h"
#include "pso/system/ArrayAllocation.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/unk/text_8018A150.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/item/TObjContainerBase.h"
#include "pso/misc/TLanguage.h"
#include "pso/map/FloorArea.h"

struct AncientContainerResource {
    const char *model_filenames[4];
    BmlResourceDescriptor descriptor;
};
typedef char AncientContainerResource_size[(sizeof(AncientContainerResource) == 0x20) ? 1 : -1];
typedef char AncientContainerResource_descriptor_offset[(offsetof(AncientContainerResource, descriptor) == 0x10) ? 1 : -1];

static __declspec(section ".rodata") const char ancient_container_model[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_container.gj";
static __declspec(section ".rodata") const char ancient_container_fragment1_model[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_container_hahen01.gj";
static __declspec(section ".rodata") const char ancient_container_fragment2_model[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_container_hahen02.gj";
static __declspec(section ".rodata") const char ancient_container_bml[] ATTRIBUTE_ALIGN(4) = "bm_o_container_ancient.bml";
static __declspec(section ".rodata") const char vs2_container_fragment1_model[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_vs2container_hahen1.gj";
static __declspec(section ".rodata") const char vs2_container_fragment2_model[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_vs2container_hahen2.gj";
static __declspec(section ".rodata") const char vs2_container_model[] ATTRIBUTE_ALIGN(4) = "fs_obj_o_vs2container.gj";
static __declspec(section ".rodata") const char vs2_container_bml[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_vs2container.bml";
static __declspec(section ".rodata") const char ep2_box_model[] ATTRIBUTE_ALIGN(4) = "fs_obj_ex_box1.gj";
static __declspec(section ".rodata") const char ep2_box_fragment1_model[] ATTRIBUTE_ALIGN(4) = "fe_obj_ex_box1_hahen01.gj";
static __declspec(section ".rodata") const char ep2_box_fragment2_model[] ATTRIBUTE_ALIGN(4) = "fe_obj_ex_box1_hahen02.gj";
// The filename pool reserves a full aligned slot for its final string.
static __declspec(section ".rodata") const char ep2_box_bml[0x14] ATTRIBUTE_ALIGN(4) = "fe_obj_ex_box1.bml";
static __declspec(section ".rodata") const char TOContainerAncientItemCommon_class_name[] ATTRIBUTE_ALIGN(4) = "TOContainerAncientItemCommon";
static __declspec(section ".rodata") const char TOContainerAncientItemRare_class_name[] ATTRIBUTE_ALIGN(4) = "TOContainerAncientItemRare";
static __declspec(section ".rodata") const char TOContainerAncientItemNone_class_name[] ATTRIBUTE_ALIGN(4) = "TOContainerAncientItemNone";
static __declspec(section ".rodata") const char TOContainerAncientEnemy_class_name[] ATTRIBUTE_ALIGN(4) = "TOContainerAncientEnemy";
static __declspec(section ".rodata") const char TOContainerAncientEnemyCommon_class_name[] ATTRIBUTE_ALIGN(4) = "TOContainerAncientEnemyCommon";
static __declspec(section ".rodata") const char TOContainerAncientEnemyRare_class_name[] ATTRIBUTE_ALIGN(4) = "TOContainerAncientEnemyRare";
static __declspec(section ".rodata") const TObjChipParams fish_break_debris_desc = {
    { 0.5f, 0.07f, 0.26f }, { 0.0f, 0.0f, 0.0f }, { 5.0f, 5.0f, 5.0f }, { 0x400, 0x100, 0x400 }, { 5, 0x32 }, { 0.0f, 0.6f }, 0, 0, 0x16,
};
static __declspec(section ".rodata") const TObjChipParams fish_break_debris_desc_b = {
    { 0.5f, 0.07f, 0.26f }, { 0.0f, 0.0f, 0.0f }, { 4.0f, 4.5f, 4.0f }, { 0x200, 0x100, 0x200 }, { 6, 0x32 }, { 0.0f, 0.5f }, 0, 0, 0x16,
};
static __declspec(section ".rodata") const TObjChipParams ancient_enemy_break_debris_desc = {
    { 0.5f, 0.07f, 0.26f }, { 0.0f, 0.0f, 0.0f }, { 5.0f, 5.0f, 5.0f }, { 0x400, 0x100, 0x400 }, { 5, 0x32 }, { 0.0f, 0.6f }, 0, 0, 0x16,
};
static __declspec(section ".rodata") const TObjChipParams ancient_enemy_break_debris_desc_b = {
    { 0.5f, 0.07f, 0.26f }, { 0.0f, 0.0f, 0.0f }, { 4.0f, 4.5f, 4.0f }, { 0x200, 0x100, 0x200 }, { 6, 0x32 }, { 0.0f, 0.5f }, 0, 0, 0x16,
};
static __declspec(section ".rodata") const char ancient_enemy_event_format[] ATTRIBUTE_ALIGN(4) = "EVT NO : %d";
extern const char fs_obj_ex_box2_texture[];
extern const char fe_obj_ex_box2_hahen01_texture[];
extern const char fe_obj_ex_box2_hahen02_texture[];
extern const char fs_obj_o_vs2container_r_texture[];
extern const char fe_obj_o_vs2cont_hahen1_r_texture[];
extern const char fe_obj_o_vs2cont_hahen2_r_texture[];
extern const char fe_obj_o_container_r_texture[];
extern const char fe_obj_o_container_hahen01r_texture[];
extern const char fe_obj_o_container_hahen02r_texture[];

extern AncientContainerResource bm_o_container_ancient_resource_bundle;
extern AncientContainerResource fe_obj_o_vs2container_resource_bundle;
extern AncientContainerResource fe_obj_ex_box1_resource_bundle;
extern const char *bm_o_container_ancient_motion_names[1];
extern const char *fe_obj_o_vs2container_motion_names[1];
extern const char *fe_obj_ex_box1_motion_names[1];

extern "C" {
__declspec(section ".data") AncientContainerResource bm_o_container_ancient_resource_bundle = { { ancient_container_model, ancient_container_fragment1_model, ancient_container_fragment2_model, NULL }, { ancient_container_bml, bm_o_container_ancient_resource_bundle.model_filenames, bm_o_container_ancient_motion_names, 3, 0 } };
__declspec(section ".data") AncientContainerResource fe_obj_o_vs2container_resource_bundle = { { vs2_container_fragment1_model, vs2_container_fragment2_model, vs2_container_model, NULL }, { vs2_container_bml, fe_obj_o_vs2container_resource_bundle.model_filenames, fe_obj_o_vs2container_motion_names, 3, 0 } };
__declspec(section ".data") AncientContainerResource fe_obj_ex_box1_resource_bundle = { { ep2_box_model, ep2_box_fragment1_model, ep2_box_fragment2_model, NULL }, { ep2_box_bml, fe_obj_ex_box1_resource_bundle.model_filenames, fe_obj_ex_box1_motion_names, 3, 0 } };
__declspec(section ".sdata") const char *bm_o_container_ancient_motion_names[1] = { NULL };
__declspec(section ".sdata") const char *fe_obj_o_vs2container_motion_names[1] = { NULL };
__declspec(section ".sdata") const char *fe_obj_ex_box1_motion_names[1] = { NULL };
__declspec(section ".sdata") const char *TOContainerAncientItemCommon__name = TOContainerAncientItemCommon_class_name;
__declspec(section ".sdata") const char *TOContainerAncientItemRare__name = TOContainerAncientItemRare_class_name;
__declspec(section ".sdata") const char *TOContainerAncientItemNone__name = TOContainerAncientItemNone_class_name;
__declspec(section ".sdata") const char *TOContainerAncientEnemy__name = TOContainerAncientEnemy_class_name;
__declspec(section ".sdata") const char *TOContainerAncientEnemyCommon__name = TOContainerAncientEnemyCommon_class_name;
__declspec(section ".sdata") const char *TOContainerAncientEnemyRare__name = TOContainerAncientEnemyRare_class_name;
}

CollisionBody TOContainerAncientEnemy__collision_body_params = {
    {0.0f, 6.5f, 0.0f}, 7.5f, 7.5f, 0, 0x38003, {0.0f, 0.0f, 0.0f}, 0.0f,
};

extern s32 tl_05;
extern "C" {
void *__nw__7TObjectFUl(int);
u8 *TOContainerAncientEnemy__ct(u8 *, s32);
void *TOContainerAncientEnemyCommon__ct(void *, void *);
extern u32 ancient_container_resource_bundle;
extern u32 *ancient_container_fragment_texture_lists;
extern s32 __vt__27TOContainerAncientEnemyRare[];
extern s32 __vt__29TOContainerAncientEnemyCommon[];
extern s32 __vt__23TOContainerAncientEnemy[];
extern s32 __vt__26TOContainerAncientItemNone[];
extern s32 __vt__26TOContainerAncientItemRare[];
extern s32 __vt__28TOContainerAncientItemCommon[];
extern s32 __vt__13TUnk_804B08BC[];
}
extern "C" {
int is_quest_active(void);
extern s32 enable_v2_features;
}

struct Obj_8015BCC0 { u8 pad[0x326]; s16 a326; u8 pad2[0x364 - 0x328]; s32 a364; };

struct Obj_80188814 { u8 pad0[0x38]; u8 pos[0x4c]; s32 id; };

struct Obj_8015B94C { u8 pad[0x38]; f32 x, y, z; u8 pad44[0x326 - 0x44]; s16 f326; };

struct O_8015BAE0 { u8 pad[0x1C]; u16 id; u8 pad1e[0x80 - 0x1E]; u32 f80; s32 f84; };

struct Pk_8015BAE0 { u8 pad[2]; u16 id; s32 a; s32 b; s32 c; };

extern "C" {
s32 rotate_matrix_y(int, int);
s32 push_matrix();
s32 pop_matrix();
s32 post_translate_matrix(void *);
void draw_ginja_model(void * model);
s32 init_collision_body_parts(void *, void *, int);
u8 *init_container_base(u8 *arg0, s32 arg1, s32 arg2);
void submit_cursor_candidate(void *self, s32 x);
void debug_printf_at(s32 id, const char *fmt, ...);
extern const f32 lbl_805DB3A0;
s32 get_current_floor();
void byteswap_and_send__6TLobbyFv(void *, int);
extern s32 local_client_id;
extern const f32 lbl_805DB39C;
s32 check_value_equals__7TObjectFPCc(void *, s32);

u8 *__ct__8TObjChipFP7TObjectP14TObjChipParams(u8 *arg0, u8 *arg1, u8 *arg2);
}
void play_container_break_sound(s32 arg0);
extern "C" {
s32 free_collision_body_parts(void *);
void queue_destruction__7TObjectFv(void *arg0);
}

struct Obj_8015C234 {
    u8 pad0[0x38];
    f32 x;
    f32 y;
    f32 z;
    u8 pad44[0x326 - 0x44];
    s16 f326;
};

struct Obj_8015C48C { u8 pad[0x326]; s16 a326; u8 pad2[0x364 - 0x328]; s32 a364; };

extern "C" {
static const f32 lbl_805DB398 = 1.0f;
u8 *load_gvm_texture_file(s32 arg0);
}

// Deferred emission reproduces the native function and virtual table order.
#pragma defer_codegen on
extern "C" {

s32 TUnk_804B6C24::roll_physical_accuracy(void *, s32, f32) { return 1; }

s32 TUnk_804B6C24::try_start_action(s32, s32) { return 1; }

void TUnk_804B6C24::apply_knockback_from_attacker(u8 *, f32) {  }

f32 TUnk_804B6C24::receive_weapon_special_attack(void *, void *) {
    receive_physical_attack(NULL, lbl_805DB398);
    return lbl_805DB39C;
}

int TUnk_804B6C24::calc_distance_accuracy_penalty(void *, void *, void *, float) { return 1; }

#pragma push
#pragma pool_data off
void TLanguage::load_container_fragment_textures() {
    u8 *tbl = (u8 *)&bm_o_container_ancient_resource_bundle;
    s32 area = get_current_floor_area();
    void *p;
    if (enable_v2_features == 1 &&
        (area == AREA_BATTLE1 || area == AREA_VR_SPACESHIP_ALPHA || area == AREA_VR_SPACESHIP_BETA || area == AREA_GOL_DRAGON)) {
        p = new BmlResource(1, (BmlResourceDescriptor *)(tbl + 0x50), 0, 0, (void *)(0));
        ancient_container_resource_bundle = (u32)p;
        ancient_container_fragment_texture_lists = (u32 *)::operator new[](0xC);
        ancient_container_fragment_texture_lists[0] = (u32)load_gvm_texture_file((s32)fs_obj_ex_box2_texture);
        ancient_container_fragment_texture_lists[1] = (u32)load_gvm_texture_file((s32)fe_obj_ex_box2_hahen01_texture);
        ancient_container_fragment_texture_lists[2] = (u32)load_gvm_texture_file((s32)fe_obj_ex_box2_hahen02_texture);
    } else if (enable_v2_features == 1 &&
               (area == AREA_BATTLE2 || area == AREA_VR_TEMPLE_ALPHA || area == AREA_VR_TEMPLE_BETA || area == AREA_BARBA_RAY)) {
        p = new BmlResource(1, (BmlResourceDescriptor *)(tbl + 0x30), 0, 0, (void *)(0));
        ancient_container_resource_bundle = (u32)p;
        ancient_container_fragment_texture_lists = (u32 *)::operator new[](0xC);
        ancient_container_fragment_texture_lists[0] = (u32)load_gvm_texture_file((s32)fs_obj_o_vs2container_r_texture);
        ancient_container_fragment_texture_lists[1] = (u32)load_gvm_texture_file((s32)fe_obj_o_vs2cont_hahen1_r_texture);
        ancient_container_fragment_texture_lists[2] = (u32)load_gvm_texture_file((s32)fe_obj_o_vs2cont_hahen2_r_texture);
    } else {
        p = new BmlResource(1, (BmlResourceDescriptor *)(tbl + 0x10), 0, 0, (void *)(0));
        ancient_container_resource_bundle = (u32)p;
        ancient_container_fragment_texture_lists = (u32 *)::operator new[](0xC);
        ancient_container_fragment_texture_lists[0] = (u32)load_gvm_texture_file((s32)fe_obj_o_container_r_texture);
        ancient_container_fragment_texture_lists[1] = (u32)load_gvm_texture_file((s32)fe_obj_o_container_hahen01r_texture);
        ancient_container_fragment_texture_lists[2] = (u32)load_gvm_texture_file((s32)fe_obj_o_container_hahen02r_texture);
    }
}
#pragma pop

#pragma push
#pragma fp_contract on
void fn_8015C5F8(void) {
    s32 var_r31;
    s32 var_r30;
    u32 p;
    if ((u32) ancient_container_fragment_texture_lists != 0U) {
        var_r30 = 0;
        var_r31 = 0;
        do {
            TObjPlayer::free_if_valid((int) (*(s32 *)((s8 *)ancient_container_fragment_texture_lists + var_r31)));
            var_r30 += 1;
            var_r31 += 4;
        } while (var_r30 < 3);
        p = (u32)ancient_container_fragment_texture_lists;
        if (p != 0U) {
            ::operator delete[]((void *)p);
            ancient_container_fragment_texture_lists = NULL;
        }
    }
    p = ancient_container_resource_bundle;
    if (p != 0U) {
        delete (BmlResource *)(p);
        ancient_container_resource_bundle = 0U;
    }
}
#pragma pop

u8 *init_ancient_container(u8 *arg0, s32 arg1) {
    init_container_base((arg0), (tl_05), (arg1));
    *(s32 **)((s8 *)arg0 + 0x18) = __vt__13TUnk_804B08BC;
    ((TUnk_804B08BC *)arg0)->mode = 0;
    ((TUnk_804B08BC *)arg0)->actorFlags = (s32) (((TUnk_804B08BC *)arg0)->actorFlags | 0x60000000);
    init_collision_body_parts(arg0, &TOContainerAncientEnemy__collision_body_params, 1);
    ((TObjPlayer *)arg0)->register_object_by_id();
    VecCopy((Vec *)(arg0 + 0x74), (const Vec *)(arg0 + 0x38));
    VecCopy((Vec *)(arg0 + 0x2FC), (const Vec *)(arg0 + 0x38));
    *(f32 *)((s8 *)arg0 + 0x78) = (f32) (*(f32 *)((s8 *)arg0 + 0x78) + TOContainerAncientEnemy__collision_body_params.offset.y);
    *(s32 *)((s8 *)arg0 + 0x34) = (s32)get_bml_model((BmlResource *)((*(s32 *)&ancient_container_resource_bundle)), 0);
    ((TUnk_804B08BC *)arg0)->texlist = (s32)TObjFish__sub_8001EDB0((BmlResource *)(*(s32 *)&ancient_container_resource_bundle), 0);
    return arg0;
}

TUnk_804B08BC::~TUnk_804B08BC() {
    unregister_object_by_id();
    free_collision_body_parts(this);
}

void TUnk_804B08BC::vfunc_80() {
    Obj_8015C48C *self = (Obj_8015C48C *)this;
    switch (this->mode) {
    case 0:
        if (this->m_364 != 0) {
            submit_cursor_candidate(self, -1);
        }
        break;
    }
}

void TUnk_804B08BC::vfunc_81() {
    u8 *temp_r31;
    u8 *temp_r31_2;
    u8 *temp_r31_3;
    if ((u32) ancient_container_resource_bundle != 0U) {
        switch (this->mode) {
        case 0:
            push_matrix();
            post_translate_matrix((u8 *)&this->position);
            rotate_matrix_y(0, this->rotation.yaw);
            set_current_texture_list((GinjaTextureList *)(this->texlist));
            temp_r31 = (unsigned char *) (this->model);
            push_matrix();
            post_translate_matrix(temp_r31 + 8);
            draw_ginja_model((*(void **)((s8 *)temp_r31 + 4)));
            temp_r31_2 = (unsigned char *) (*(void **)((s8 *)temp_r31 + 0x2C));
            push_matrix();
            post_translate_matrix(temp_r31_2 + 8);
            draw_ginja_model((*(void **)((s8 *)temp_r31_2 + 4)));
            pop_matrix();
            temp_r31_3 = (unsigned char *) (*(void **)((s8 *)temp_r31_2 + 0x30));
            push_matrix();
            post_translate_matrix(temp_r31_3 + 8);
            TParticleCtrl::begin_effect_render();
            draw_ginja_model((*(void **)((s8 *)temp_r31_3 + 4)));
            TParticleCtrl::end_effect_render();
            pop_matrix();
            pop_matrix();
            pop_matrix();
            break;
        }
    }
}

void TUnk_804B08BC::vfunc_79() {
    Obj_8015C234 *self = (Obj_8015C234 *)this;
    if (this->mode == 1) {
        return;
    }
    TObjChipParams a = fish_break_debris_desc;
    a.pos.x = self->x;
    a.pos.y = self->y;
    a.pos.z = self->z;
    a.pad_38[0] = a.pos.y;
    a.model = (s32)get_bml_model((BmlResource *)ancient_container_resource_bundle, 1);
    a.textures = (s32)TObjFish__sub_8001EDB0((BmlResource *)ancient_container_resource_bundle, 1);
    TObjChipParams b = fish_break_debris_desc_b;
    b.pos.x = self->x;
    b.pos.y = self->y;
    b.pos.z = self->z;
    b.pad_38[0] = b.pos.y;
    b.model = (s32)get_bml_model((BmlResource *)ancient_container_resource_bundle, 2);
    b.textures = (s32)TObjFish__sub_8001EDB0((BmlResource *)ancient_container_resource_bundle, 2);
    if (check_value_equals__7TObjectFPCc(self, (s32)TOContainerAncientItemRare__name) != 0) {
        a.textures = ancient_container_fragment_texture_lists[1];
        b.textures = ancient_container_fragment_texture_lists[2];
    }
    {
        u8 *o = (u8 *)__nw__7TObjectFUl(0x234);
        if (o != NULL) {
            __ct__8TObjChipFP7TObjectP14TObjChipParams(o, (u8 *)tl_05, (u8 *)&a);
        }
    }
    {
        u8 *o = (u8 *)__nw__7TObjectFUl(0x234);
        if (o != NULL) {
            __ct__8TObjChipFP7TObjectP14TObjChipParams(o, (u8 *)tl_05, (u8 *)&b);
        }
    }
    spawn_particle_effect((const Vec *)(&self->x), 0x45);
    spawn_particle_effect((const Vec *)(&self->x), 0x46);
    play_container_break_sound((s32)self);
}

void *TOContainerAncientItemCommon__ct(void *container_ancient_item_common, void * _w1) {
    init_ancient_container((u8 *)container_ancient_item_common, (s32)_w1);
    *(s32 **)((s8 *)container_ancient_item_common + 0x18) = __vt__28TOContainerAncientItemCommon;
    ((TOContainerAncientItemCommon *)container_ancient_item_common)->m_name = TOContainerAncientItemCommon__name;
    return container_ancient_item_common;
}

TOContainerAncientItemCommon::~TOContainerAncientItemCommon() {}

s32 TOContainerAncientItemCommon::create() {
    s32 arg0 = (s32)this;
    s32 container_ancient_item_common;
    s32 temp_r3_2;
    s32 var_r0;
    s32 var_r0_2;
    if (((s32) enable_v2_features == 1) && (get_game_play_mode() == 1) && (is_quest_active() == 1)) {
        container_ancient_item_common = (s32)__nw__7TObjectFUl(0x368);
        var_r0_2 = container_ancient_item_common;
        if (var_r0_2 != 0) {
            var_r0_2 = ((s32)TOContainerAncientItemCommon__ct((void *)container_ancient_item_common, (void *)arg0));
        }
        return var_r0_2;
    }
    temp_r3_2 = (s32)__nw__7TObjectFUl(0x368);
    var_r0 = temp_r3_2;
    if (var_r0 != 0) {
        var_r0 = ((s32)TOContainerAncientItemCommon__ct((void *)temp_r3_2, (void *)arg0));
    }
    return var_r0;
}

void TOContainerAncientItemCommon::vfunc_6(s16 *arg1, s32 arg2) {
    if ((s16) *arg1 == 1) {
        if (arg2 != 0) {
            vfunc_79();
            this->spawn_item((s32)this);
        }
        this->mode = 1;
        set_flag8();
        queue_destruction__7TObjectFv(this);
    }
}

u8 *TOContainerAncientItemRare__ct(u8 *container_ancient_item_rare, s32 arg1) {
    init_ancient_container(container_ancient_item_rare, arg1);
    *(s32 **)((s8 *)container_ancient_item_rare + 0x18) = __vt__26TOContainerAncientItemRare;
    *(s32 *)((s8 *)container_ancient_item_rare + 0) = (s32) TOContainerAncientItemRare__name;
    ((TOContainerAncientItemRare *)container_ancient_item_rare)->texlist = (s32) *ancient_container_fragment_texture_lists;
    return container_ancient_item_rare;
}

TOContainerAncientItemRare::~TOContainerAncientItemRare() {}

void TOContainerAncientItemRare::vfunc_6(s16 *arg1, s32 arg2) {
    u8 *arg0 = (u8 *)this;
    if ((s16) *arg1 == 1) {
        if (arg2 != 0) {
            vfunc_79();
            ((TObjChara *)arg0)->request_box_item_drop((u8 *)&this->position, 1);
        }
        this->mode = 1;
        ((TObjCollidable *)arg0)->set_flag8();
        queue_destruction__7TObjectFv(arg0);
    }
}

void *TOContainerAncientItemNone__ct(void *container_ancient_item_none, void *set_data) {
    TOContainerAncientItemRare__ct((u8 *)container_ancient_item_none, (s32)set_data);
    *(s32 **)((s8 *)container_ancient_item_none + 0x18) = __vt__26TOContainerAncientItemNone;
    ((TOContainerAncientItemNone *)container_ancient_item_none)->m_name = TOContainerAncientItemNone__name;
    return container_ancient_item_none;
}

TOContainerAncientItemNone::~TOContainerAncientItemNone() {}

void *TOContainerAncientItemNone::create(void *container_ancient_item_none) {
    void *o = __nw__7TObjectFUl(0x368);
    if (o != NULL) {
        o = TOContainerAncientItemNone__ct(o, container_ancient_item_none);
    }
    return o;
}

void TOContainerAncientItemNone::vfunc_6(s16 *arg1, s32 arg2) {
    if ((s16) *arg1 == 1) {
        if (arg2 != 0) {
            this->vfunc_79();
        }
        this->mode = 1;
        set_flag8();
        queue_destruction__7TObjectFv(this);
    }
}

u8 *TOContainerAncientEnemy__ct(u8 *arg0, s32 arg1) {
    init_container_base((arg0), (tl_05), (arg1));
    *(s32 **)((s8 *)arg0 + 0x18) = __vt__23TOContainerAncientEnemy;
    *(s32 *)((s8 *)arg0 + 0) = (s32) TOContainerAncientEnemy__name;
    ((TOContainerAncientEnemy *)arg0)->mode = 0;
    ((TOContainerAncientEnemy *)arg0)->actorFlags = (s32) (((TOContainerAncientEnemy *)arg0)->actorFlags | 0x60000000);
    init_collision_body_parts(arg0, &TOContainerAncientEnemy__collision_body_params, 1);
    ((TObjPlayer *)arg0)->register_object_by_id();
    VecCopy((Vec *)(arg0 + 0x74), (const Vec *)(arg0 + 0x38));
    VecCopy((Vec *)(arg0 + 0x2FC), (const Vec *)(arg0 + 0x38));
    *(f32 *)((s8 *)arg0 + 0x78) = (f32) (*(f32 *)((s8 *)arg0 + 0x78) + TOContainerAncientEnemy__collision_body_params.offset.y);
    *(s32 *)((s8 *)arg0 + 0x34) = (s32)get_bml_model((BmlResource *)((*(s32 *)&ancient_container_resource_bundle)), 0);
    ((TOContainerAncientEnemy *)arg0)->texlist = (s32)TObjFish__sub_8001EDB0((BmlResource *)(*(s32 *)&ancient_container_resource_bundle), 0);
    return arg0;
}

TOContainerAncientEnemy::~TOContainerAncientEnemy() {
    unregister_object_by_id();
    free_collision_body_parts(this);
}

void TOContainerAncientEnemy::vfunc_80() {
    Obj_8015BCC0 *self = (Obj_8015BCC0 *)this;
    switch (this->mode) {
    case 0:
        if (this->m_364 != 0) {
            submit_cursor_candidate(self, -1);
        }
        break;
    }
}

void TOContainerAncientEnemy::vfunc_81() {
    u8 *temp_r31;
    u8 *temp_r31_2;
    u8 *temp_r31_3;
    if ((u32) ancient_container_resource_bundle != 0U) {
        switch (this->mode) {
        case 0:
            push_matrix();
            post_translate_matrix((u8 *)&this->position);
            rotate_matrix_y(0, this->rotation.yaw);
            set_current_texture_list((GinjaTextureList *)(this->texlist));
            temp_r31 = (unsigned char *) (this->model);
            push_matrix();
            post_translate_matrix(temp_r31 + 8);
            draw_ginja_model((*(void **)((s8 *)temp_r31 + 4)));
            temp_r31_2 = (unsigned char *) (*(void **)((s8 *)temp_r31 + 0x2C));
            push_matrix();
            post_translate_matrix(temp_r31_2 + 8);
            draw_ginja_model((*(void **)((s8 *)temp_r31_2 + 4)));
            pop_matrix();
            temp_r31_3 = (unsigned char *) (*(void **)((s8 *)temp_r31_2 + 0x30));
            push_matrix();
            post_translate_matrix(temp_r31_3 + 8);
            TParticleCtrl::begin_effect_render();
            draw_ginja_model((*(void **)((s8 *)temp_r31_3 + 4)));
            TParticleCtrl::end_effect_render();
            pop_matrix();
            pop_matrix();
            pop_matrix();
            break;
        }
    }
}

void TOContainerAncientEnemy::debug_print_item_box_info() {
    Obj_80188814 *self = (Obj_80188814 *)this;
    TObjNpcEnemy::set_global_count(0xFF00FF);
    debug_printf_at(0x130020, ancient_enemy_event_format, this->set_params[0]);
    TObjNpcEnemy::set_global_count(0xF0F0F0FF);
    debug_draw_sphere((const Vec *)self->pos, &debug_color_blue_alpha30, lbl_805DB3A0);
}

f32 TOContainerAncientEnemy::receive_physical_attack(void *, f32) {
    O_8015BAE0 *arg0 = (O_8015BAE0 *)this;
    s16 sp8;
    s32 r4;
    Pk_8015BAE0 pk;
    if (this->entity_id >= 0x1000U && arg0->f80 != 0U && ((TObjCollidable *)arg0)->access_object_saved_state(&sp8, 1) != 0) {
        sp8 = 1;
        ((TObjCollidable *)arg0)->access_object_saved_state(&sp8, 0);
        ((TObjCollidable *)arg0)->send_object_state_update(&sp8);
        ((TLobby *)(&pk))->init_packet_67_04();
        pk.id = this->entity_id;
        pk.a = get_current_floor();
        r4 = this->set_params[0];
        pk.b = r4;
        pk.c = local_client_id;
        byteswap_and_send__6TLobbyFv(&pk, r4);
    }
    return lbl_805DB39C;
}

void TOContainerAncientEnemy::vfunc_79() {
    Obj_8015B94C *self = (Obj_8015B94C *)this;
    void *o;
    if (this->mode != 1) {
        TObjChipParams a = ancient_enemy_break_debris_desc;
        a.pos.x = self->x;
        a.pos.y = self->y;
        a.pos.z = self->z;
        a.pad_38[0] = self->y;
        a.model = (s32)get_bml_model((BmlResource *)ancient_container_resource_bundle, 1);
        a.textures = (s32)TObjFish__sub_8001EDB0((BmlResource *)ancient_container_resource_bundle, 1);
        TObjChipParams b = ancient_enemy_break_debris_desc_b;
        b.pos.x = self->x;
        b.pos.y = self->y;
        b.pos.z = self->z;
        b.pad_38[0] = self->y;
        b.model = (s32)get_bml_model((BmlResource *)ancient_container_resource_bundle, 2);
        b.textures = (s32)TObjFish__sub_8001EDB0((BmlResource *)ancient_container_resource_bundle, 2);
        if (check_value_equals__7TObjectFPCc(self, (s32)TOContainerAncientEnemyRare__name) != 0) {
            a.textures = ancient_container_fragment_texture_lists[1];
            b.textures = ancient_container_fragment_texture_lists[2];
        }
        spawn_particle_effect((const Vec *)(&self->x), 0x45);
        spawn_particle_effect((const Vec *)(&self->x), 0x46);
        o = __nw__7TObjectFUl(0x234);
        if (o != NULL) {
            __ct__8TObjChipFP7TObjectP14TObjChipParams((u8 *)o, (u8 *)tl_05, (u8 *)&a);
        }
        o = __nw__7TObjectFUl(0x234);
        if (o != NULL) {
            __ct__8TObjChipFP7TObjectP14TObjChipParams((u8 *)o, (u8 *)tl_05, (u8 *)&b);
        }
        play_container_break_sound((s32)self);
    }
}

void TOContainerAncientEnemy::vfunc_6(s16 *arg1, s32 arg2) {
    if ((s16) *arg1 == 1) {
        if (arg2 != 0) {
            this->vfunc_79();
        }
        this->mode = 1;
        set_flag8();
        queue_destruction__7TObjectFv(this);
    }
}

void *TOContainerAncientEnemyCommon__ct(void *container_ancient_enemy_common, void *set_data) {
    TOContainerAncientEnemy__ct((u8 *)container_ancient_enemy_common, (s32)set_data);
    *(s32 **)((s8 *)container_ancient_enemy_common + 0x18) = __vt__29TOContainerAncientEnemyCommon;
    ((TOContainerAncientEnemyCommon *)container_ancient_enemy_common)->m_name = TOContainerAncientEnemyCommon__name;
    return container_ancient_enemy_common;
}

TOContainerAncientEnemyCommon::~TOContainerAncientEnemyCommon() {}

s32 TOContainerAncientEnemyCommon__create(s32 container_ancient_enemy_common) {
    s32 temp_r3;
    s32 temp_r3_2;
    s32 var_r0;
    s32 var_r0_2;
    if (((s32) enable_v2_features == 1) && (get_game_play_mode() == 1) && (is_quest_active() == 1)) {
        temp_r3 = (s32)__nw__7TObjectFUl(0x368);
        var_r0_2 = temp_r3;
        if (var_r0_2 != 0) {
            var_r0_2 = (s32)TOContainerAncientEnemyCommon__ct((void *)temp_r3, (void *)container_ancient_enemy_common);
        }
        return var_r0_2;
    }
    temp_r3_2 = (s32)__nw__7TObjectFUl(0x368);
    var_r0 = temp_r3_2;
    if (var_r0 != 0) {
        var_r0 = (s32)TOContainerAncientEnemyCommon__ct((void *)temp_r3_2, (void *)container_ancient_enemy_common);
    }
    return var_r0;
}

u8 *TOContainerAncientEnemyRare__ct(u8 *container_ancient_enemy_rare, s32 arg1) {
    TOContainerAncientEnemy__ct(container_ancient_enemy_rare, arg1);
    *(s32 **)((s8 *)container_ancient_enemy_rare + 0x18) = __vt__27TOContainerAncientEnemyRare;
    *(s32 *)((s8 *)container_ancient_enemy_rare + 0) = (s32)TOContainerAncientEnemyRare__name;
    ((TOContainerAncientEnemyRare *)container_ancient_enemy_rare)->texlist = (s32) *ancient_container_fragment_texture_lists;
    return container_ancient_enemy_rare;
}

TOContainerAncientEnemyRare::~TOContainerAncientEnemyRare() {}

}

extern __declspec(section ".rodata") const char fs_obj_ex_box2_texture[] ATTRIBUTE_ALIGN(4) = "fs_obj_ex_box2.gvm";
extern __declspec(section ".rodata") const char fe_obj_ex_box2_hahen01_texture[] ATTRIBUTE_ALIGN(4) = "fe_obj_ex_box2_hahen01.gvm";
extern __declspec(section ".rodata") const char fe_obj_ex_box2_hahen02_texture[] ATTRIBUTE_ALIGN(4) = "fe_obj_ex_box2_hahen02.gvm";
extern __declspec(section ".rodata") const char fs_obj_o_vs2container_r_texture[] ATTRIBUTE_ALIGN(4) = "fs_obj_o_vs2container_r.gvm";
extern __declspec(section ".rodata") const char fe_obj_o_vs2cont_hahen1_r_texture[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_vs2cont_hahen1_r.gvm";
extern __declspec(section ".rodata") const char fe_obj_o_vs2cont_hahen2_r_texture[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_vs2cont_hahen2_r.gvm";
extern __declspec(section ".rodata") const char fe_obj_o_container_r_texture[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_container_r.gvm";
extern __declspec(section ".rodata") const char fe_obj_o_container_hahen01r_texture[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_container_hahen01r.gvm";
extern __declspec(section ".rodata") const char fe_obj_o_container_hahen02r_texture[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_container_hahen02r.gvm";
