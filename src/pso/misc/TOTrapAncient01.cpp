#include "pso/player/demo_mode.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/misc/PersistentSound.h"
#include "pso/system/SoundEffect.h"
#include "pso/math/ScratchVectorStorage.h"
#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/misc/TKeyBoardControl_8000F764.h"
#include "pso/misc/TOTrap_801791EC.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/player/TObjPlayer_800D7BFC.h"
#include "pso/object/TObjMotion.h"
#include "pso/player/TObjChara.h"
#include "pso/misc/TOTrapAncient02R.h"
#include "pso/misc/TOTrap.h"
#include "pso/misc/TOTrapAncient01.h"
#include "pso/TParticleCtrl.h"
#include "pso/misc/RenderFadeState.h"
#include "pso/misc/TMotorcycle.h"
#include "pso/misc/TRaderMapCore.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/map/FloorArea.h"
#include "pso/object/TObjChip.h"
#include "pso/misc/ParticleFactory.h"
#include "pso/player/TObjPlayer_801AF2F0.h"

struct E_8017A1A4 { u8 pad[0xc]; f32 f; u8 pad2[0x2c - 0x10]; };

struct Obj_8017A1A4 { u8 pad[0xa4]; E_8017A1A4 *arr; };

struct Self_80179EC0 { u8 pad[0x18]; s32 *vt; u8 pad1c[0x358 - 0x1C]; u8 arr[4][0x1C]; };

struct Self_80179F40 { u8 pad[0x358]; u8 arr[4][0x1C]; };

struct VBase_801797D4 { char pad[0x18]; };

struct VObj_801797D4 : VBase_801797D4 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20(s32, f32);
    virtual void m21(void *, void *, s32, s32, s32);
    virtual void m22();
    virtual void m23(void *, f32);
};

struct Ent_801797D4 { u8 pad[0xC]; f32 fC; };

struct Pair_801797D4 { s32 a; s32 b; };

struct Trap_801797D4 : VObj_801797D4 {
    u8 pad1C[0xA4 - 0x1C];
    Ent_801797D4 *fA4;
    u8 padA8[0x2A8 - 0xA8];
    s32 f2A8;
    u8 pad2AC[0x344 - 0x2AC];
    Pair_801797D4 f344;
    u8 pad34C[0x354 - 0x34C];
    f32 f354;
};

struct Vec_80179B8C { f32 x, y, z; };

struct Node_80179B8C { u8 pad0[4]; s32 f4; u8 mtx[0x2C - 8]; Node_80179B8C *child; };

struct FadeBase_80179B8C { char pad[0x14]; };

struct Fade_80179B8C : FadeBase_80179B8C {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    u8 pad18[4];
};

struct VBase_80179B8C { char pad[0x18]; };

struct VObj_80179B8C : VBase_80179B8C {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual s32 m8(f32, f32);
};

struct Trap_80179B8C : VObj_80179B8C {
    u8 pad1C[0x24 - 0x1C];
    s32 f24;
    u8 pad28[0x34 - 0x28];
    Node_80179B8C *model;
    u8 pos38[0x60 - 0x38];
    s32 f60;
    u8 pad64[0x6C - 0x64];
    f32 f6C;
    u8 pad70[0x340 - 0x70];
    s32 f340;
    u8 pad344[0x358 - 0x344];
    Fade_80179B8C fades[4];
};

struct TrapChipParams {
    f32 params[3];
    f32 pos[3];
    f32 velocity[3];
    s32 rotation[3];
    s32 count_and_lifetime[2];
    f32 floor_and_scale[2];
    s32 model;
    s32 textures;
    s32 kind;
};
typedef char TrapChipParams_size[sizeof(TrapChipParams) == 0x4c ? 1 : -1];

extern "C" {
u16 get_entity_id(TObjBase *);
void obj_set_flag_20000(TObjBase *);
void obj_clear_flag30_20000(TObjBase *);
// Trap callers show this receiver is not restricted to TObjEnemy.
u16 find_nearest_visible_player(void *, Vec *, f32);
f32 horizontal_distance_squared(const Vec *, const Vec *);
s32 obj_is_hit_receivable(u8 *);

s32 check_player_flag1__6TLobbyFv();
extern s32 local_client_id;
s32 TObjFish__sub_8001EDB0(void *, s32);
s32 get_bml_model(void *, s32);
#pragma readonly_strings on
const char *bm_o_trap_ancient01_model_names[] = {
    "fe_obj_o_turigane_hahen01.gj", "fe_obj_o_turigane_hahen02.gj",
    "fe_obj_o_turigane_hahen03.gj", "fs_obj_o_turigane.gj", NULL
};
const char *bm_o_trap_ancient01_motion_names[] = {NULL};
BmlResourceDescriptor bm_o_trap_ancient01_resource_descriptor = {
    "bm_o_trap_ancient01.bml", bm_o_trap_ancient01_model_names,
    bm_o_trap_ancient01_motion_names, 4, 0
};
CollisionBody lbl_804B4844 = {
    {0.0f, 20.0f, 0.0f}, 14.0f, 0.0f, 0, 0x08011f04,
    {0.0f, 0.0f, 0.0f}, 0.0f
};
const char *TOTrapAncient01__class_name = "TOTrapAncient01";
#pragma readonly_strings reset
// The original symbol reserves eight bytes; only the first word is accessed here.
struct AncientTrapResourceSlot { u32 value; u8 reserved[4]; };
AncientTrapResourceSlot TOTrapAncient01__bml_resource;
extern const f32 TOTrapAncient01__data_805DBA4C;
extern const f32 lbl_805DBA5C;
f32 TObjPlayer__sub_8017A1A4(Obj_8017A1A4 *self, s32 i);
s32 free_collision_body_parts(void *);
s32 __destroy_arr(void *, void *, int, int);
void __dl__7TObjectFPv(void *);
extern s32 __vt__15TOTrapAncient01[];
Self_80179EC0 *__dt__15TOTrapAncient01Fv(Self_80179EC0 *self, s16 flag);
s32 init_collision_body_parts(void *, void *, int);
void TOTrap__ct(void *, void *, void *);
void __construct_array(void *, void *, void *, int, int);
void __ct__15RenderFadeStateFv(void *);
extern const f32 lbl_805DBA54;
extern const f32 lbl_805DBA6C;
extern const f32 lbl_805DBA74;
VObj_801797D4 *get_battle_param__10TObjPlayerFi(s32);
s32 check_value_equals__13TUnk_804B6C24Fl(void *, s32);
void submit_cursor_candidate(void *, s32);

extern s32 lbl_805D3530;
extern const f32 lbl_805DBA48;
extern const f32 lbl_805DBA50;
extern void *tl_06;
s32 is_split_screen();
s32 get_camera_mode__11TCameraCtrlFv();
void update__15RenderFadeStateFv(void *);
s32 rand(void);
int rotate_matrix_y(int, int);
int push_matrix();
int pop_matrix();
int post_translate_matrix(void *);
int draw_ginja_model(int);
void translate_matrix(s32, f32, f32, f32);
extern s32 model_render_flags;
extern s32 saved_model_render_flags;
extern s32 saved_chunk_polygon_flags_and_mask;
extern s32 saved_chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_and_mask;
extern const f32 lbl_805DBA58;
extern const f32 lbl_805DBA60;
extern const f32 lbl_805DBA64;
extern const f32 lbl_805DBA68;
void render__15TOTrapAncient01Fv(Trap_80179B8C *self);
void fn_80141CF0(void *, void *, void *);
void TOTrapAncient02R__sub_80154D78(void *);
void *__nw__7TObjectFUl(int);
s32 is_current_room(void *);

extern void *tl_05;
extern s32 trap_ancient_light_color[];

// Reverse definitions with deferred generation reproduce this unit's original
// function order and place the native vtable before the switch tables.
// This describes compiler emission, not a claim about the historical source.

void TOTrapAncient02R::vfunc_86() {
    s32 x;
    x = is_current_room(this);
    if (x == 1) {
        fn_80141CF0((void *)((char *)this + 80), (&scratch_vec.vector), trap_ancient_light_color);
        TOTrapAncient02R__sub_80154D78(this);
    }
}

f32 TObjPlayer__sub_8017A1A4(Obj_8017A1A4 *self, s32 i) {
    return self->arr[i].f;
}

#pragma push
#pragma fp_contract on
#define self ((u8 *)arg0)
void *TOTrapAncient01__ct(void *arg0, void *arg1, void *arg2) {
    s32 i;
    TOTrap__ct(arg0, arg1, arg2);
    *(s32 **)((s8 *)self + 0x18) = __vt__15TOTrapAncient01;
    __construct_array(self + 0x358, (void *)__ct__15RenderFadeStateFv, (void *)__dt__15RenderFadeStateFv, 0x1C, 4);
    *(const char **)((s8 *)self + 0) = TOTrapAncient01__class_name;
    ((TOTrapAncient01 *)arg0)->apply_object_set_data((void *)((s32)arg2));
    ((TObjChara *)arg0)->initialize_position_copies();
    ((TObjChara *)arg0)->calc_attach_pos();
    *(s32 *)((s8 *)self + 0x34) = get_bml_model((void *)TOTrapAncient01__bml_resource.value, 3);
    *(s32 *)((s8 *)self + 0x24) = TObjFish__sub_8001EDB0((void *)TOTrapAncient01__bml_resource.value, 3);
    *(s16 *)((s8 *)self + 0x326) = 0;
    *(f32 *)((s8 *)self + 0x334) = 0.5f * *(f32 *)((s8 *)self + 0x68) + 30.0f;
    if (*(f32 *)((s8 *)self + 0x6C) < 0.0f) {
        *(f32 *)((s8 *)self + 0x6C) = 0.0f;
    }
    if (*(f32 *)((s8 *)self + 0x70) < 1.0f) {
        *(f32 *)((s8 *)self + 0x70) = 1.0f;
    }
    *(f32 *)((s8 *)self + 0x34C) = -*(f32 *)((s8 *)self + 0x6C) / *(f32 *)((s8 *)self + 0x70);
    *(f32 *)((s8 *)self + 0x350) = 30.0f + (f32)*(s32 *)((s8 *)self + 0x8C);
    if (get_main_phase() == 0xE) {
        *(f32 *)((s8 *)self + 0x350) *= lbl_805DBA74;
    }
    if (*(f32 *)((s8 *)self + 0x350) < 0.0f) {
        *(f32 *)((s8 *)self + 0x350) = 0.0f;
    }
    *(f32 *)((s8 *)self + 0x354) = *(f32 *)((s8 *)self + 0x350);
    if (*(s32 *)((s8 *)self + 0x84) < 0) {
        *(s32 *)((s8 *)self + 0x84) = 0;
    }
    *(f32 *)((s8 *)self + 0x348) = ((TOTrapAncient01 *)arg0)->vfunc_87((f32)*(s32 *)((s8 *)self + 0x84));
    if (*(s32 *)((s8 *)self + 0x88) < 0) {
        *(s32 *)((s8 *)self + 0x88) = 0;
    } else if (*(s32 *)((s8 *)self + 0x88) > 5) {
        *(s32 *)((s8 *)self + 0x88) = 5;
    }
    *(s32 *)((s8 *)self + 0x344) = *(s32 *)((s8 *)self + 0x88);
    *(f32 *)((s8 *)self + 0x338) = 15.0f;
    *(u16 *)((s8 *)self + 0x33C) = 0xFFFF;
    init_collision_body_parts(arg0, &lbl_804B4844, 1);
    ((TObjCollidable *)arg0)->refresh_collision_body_centers();
    *(u32 *)((s8 *)self + 0x30) |= 0x60040000;
    ((TObjChara *)arg0)->get_or_assign_entity_id(0);
    ((TObjPlayer *)arg0)->register_object_by_id();
    for (i = 0; i < 4; i++) {
        ((RenderFadeState *)(((Self_80179F40 *)arg0)->arr[i]))->activate_and_dispatch();
    }
    return arg0;
}
#undef self
#pragma pop

TOTrapAncient01::~TOTrapAncient01() {
    unregister_object_by_id();
    free_collision_body_parts(this);
}

void TOTrapAncient01::load_resources() {
  TOTrapAncient01__bml_resource.value = (u32)new BmlResource(1, &bm_o_trap_ancient01_resource_descriptor, 0, 0, NULL);
  TMotorcycle::add_entry(0x39, get_bml_model((void *)TOTrapAncient01__bml_resource.value, 3), TObjFish__sub_8001EDB0((void *)TOTrapAncient01__bml_resource.value, 3), 20.0f, 0.0f);
}

void TOTrapAncient01::release_static_resource() {
    if ((u32) TOTrapAncient01__bml_resource.value != 0U) {
        delete (BmlResource *)((void*)TOTrapAncient01__bml_resource.value);
        TOTrapAncient01__bml_resource.value = 0U;
    }
}

void *TOTrapAncient01::create() {
    void *o = __nw__7TObjectFUl(0x3C8);
    if (o != NULL) {
        o = TOTrapAncient01__ct(o, tl_05, this);
    }
    return o;
}

#pragma push
#pragma opt_lifetimes off
#pragma fp_contract on
void render__15TOTrapAncient01Fv(Trap_80179B8C *self) {
    Fade_80179B8C *fade;
    Node_80179B8C *n;
    s32 i;
    Vec_80179B8C v;
    i = 0;
    if (is_split_screen() != 0) {
        i = get_camera_mode__11TCameraCtrlFv();
    }
    fade = &self->fades[i];
    update__15RenderFadeStateFv(fade);
    self->f340 = self->m8(400.0f, 20.0f);
    if (self->f340 == 1) {
        if (((RenderFadeState *)fade)->updateFromCamera((const f32*)(self->pos38)) == 1) {
            saved_model_render_flags = model_render_flags;
            saved_chunk_polygon_flags_and_mask = chunk_polygon_flags_and_mask;
            saved_chunk_polygon_flags_or_mask = chunk_polygon_flags_or_mask;
            fade->m6();
        }
        push_matrix();
        post_translate_matrix(self->pos38);
        rotate_matrix_y(0, self->f60);
        if (check_demo_mode() != 1 && self->f6C <= 0.0f) {
            v.x = 0.1f * (0.000030517578125f * (f32)rand()) - 0.05f;
            v.y = 0.0f;
            v.z = 0.1f * (0.000030517578125f * (f32)rand()) - 0.05f;
            post_translate_matrix(&v);
        }
        set_current_texture_list((GinjaTextureList *)(self->f24));
        n = self->model;
        push_matrix();
        translate_matrix(0, 0.0f, self->f6C, 0.0f);
        post_translate_matrix(n->mtx);
        draw_ginja_model(self->model->f4);
        n = n->child;
        push_matrix();
        post_translate_matrix(n->mtx);
        TParticleCtrl::begin_effect_render();
        draw_ginja_model(n->f4);
        TParticleCtrl::end_effect_render();
        pop_matrix();
        pop_matrix();
        pop_matrix();
        if (((RenderFadeState *)fade)->updateFromCamera((const f32*)(self->pos38)) == 1) {
            fade->m7();
            chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;
            chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask;
            model_render_flags = saved_model_render_flags;
        }
    }
}
#pragma pop

// The offsets 0x326 and 0x34c remain provisional.
void TOTrapAncient01::vfunc_81() {
    f32 &step = *(f32 *)((u8 *)this + 0x34c);
    scale.y += step;
    if (!(0.0f < scale.y)) {
        goto grounded;
    }
    switch (get_current_floor_area()) {
        case AREA_CAVE1: case AREA_CAVE2: case AREA_CAVE3:
            play_persistent_sound(0x4321a, this, &position, 0, 0);
            return;
        case AREA_MINE1: case AREA_MINE2:
            play_persistent_sound(0x4004b211, this, &position, 0, 0);
            return;
        case AREA_RUINS1: case AREA_RUINS2: case AREA_RUINS3:
            play_persistent_sound(0x4004b217, this, &position, 0, 0);
            return;
        case AREA_VR_SPACESHIP_ALPHA: case AREA_VR_SPACESHIP_BETA:
            play_persistent_sound(0x4004b212, this, &position, 0, 0);
            return;
// Keep the grounded path inside the switch's lexical extent so no-op case
// labels below bind directly to the common epilogue. Moving it outside creates
// a branch thunk and changes the compiler-generated jump-table relocations.
grounded:
    {
        *(s16 *)((u8 *)this + 0x326) = 3;
        scale.y = 0.0f;
        calc_attach_pos();
        clear_player_status_flag(0, 0x08001f04);
        set_indexed_flags(0, 0x8003);
        obj_clearFlags30(0x40000);
        spawn_particle_effect(&position, 0x8f);
        spawn_particle_effect(&position, 0x8f);
        player = find_nearest_visible_player(this, NULL, range);
        if (player != 0xffff) {
            TObjPlayer *p = (TObjPlayer *)get_player_by_client_id(player);
            target = (u8 *)p;
            if (target != NULL) {
                f32 d = horizontal_distance_squared(&((TObjPlayer *)target)->position, &position);
                dist -= TObjPlayer__sub_8017A1A4((Obj_8017A1A4 *)p, 0);
                if (d < dist * dist) {
                    if (TObjPlayer::is_locally_controlled(target)) {
                        send_6x2C_impose_hold(p, &position, -1, 0, dist);
                        obj_set_flag_20000(p);
                    }
                } else {
                    player = 0xffff;
                    target = NULL;
                }
            }
        } else {
            target = NULL;
        }
    }
        case AREA_PIONEER2_EP1:
            return;
        case AREA_FOREST1:
        case AREA_FOREST2:
        case AREA_DRAGON:
        case AREA_DE_ROL_LE:
        case AREA_VOL_OPT:
        case AREA_DARK_FALZ:
        case AREA_LOBBY:
        case AREA_BATTLE1:
        case AREA_BATTLE2:
        case AREA_PIONEER2_EP2:
        case AREA_VR_TEMPLE_ALPHA:
        case AREA_VR_TEMPLE_BETA:
            return;
    }
}

void TOTrapAncient01::vfunc_82() {
    s32 i;
    VObj_801797D4 *p;
    this->calc_attach_pos();
    ((Trap_801797D4 *)this)->f354 -= 1.0f;
    if (((Trap_801797D4 *)this)->f354 < 0.0f) {
        ((Trap_801797D4 *)this)->fA4->fC = 15.0f;
        set_indexed_flags(0, 0x100);
        TObjPlayer::init_all_slots();
        ((TObjPlayer *)this)->check_object_collisions();
        for (i = 0; i < 16; i++) {
            p = get_battle_param__10TObjPlayerFi(i);
            if (p == 0) {
                break;
            }
            if (obj_is_hit_receivable((u8 *)p) == 0) {
                break;
            }
            if (check_value_equals__13TUnk_804B6C24Fl(p, lbl_805D3530) == 0) {
                break;
            }
            {
            Pair_801797D4 v = ((Trap_801797D4 *)this)->f344;
            p->m21(this, &v, 0, -1, -1);
            }
            if (((Trap_801797D4 *)this)->f344.a < 5) {
                p->m23(((Trap_801797D4 *)this), 0.0f);
            }
        }
        ((Trap_801797D4 *)this)->m20(((Trap_801797D4 *)this)->f2A8, 1.0f);
    }
    submit_cursor_candidate(((Trap_801797D4 *)this), -1);
    switch (get_current_floor_area()) {
    case AREA_RUINS1:
    case AREA_RUINS2:
    case AREA_RUINS3:
        play_persistent_sound((s32)(0x4004C618), (const void *)(((Trap_801797D4 *)this)), (const Vec *)((u8 *)((Trap_801797D4 *)this) + 0x38), 0, 0);
        break;
    case AREA_VR_SPACESHIP_ALPHA:
    case AREA_VR_SPACESHIP_BETA:
        play_persistent_sound((s32)(0x4004C610), (const void *)(((Trap_801797D4 *)this)), (const Vec *)((u8 *)((Trap_801797D4 *)this) + 0x38), 0, 0);
        break;
    case AREA_PIONEER2_EP1:
        return;
    case AREA_FOREST1:
        break;
    case AREA_FOREST2:
        return;
    case AREA_CAVE1:
        break;
    case AREA_CAVE2:
        return;
    case AREA_CAVE3:
        break;
    case AREA_MINE1:
        return;
    case AREA_MINE2:
        break;
    case AREA_DRAGON:
        break;
    case AREA_DE_ROL_LE:
        return;
    case AREA_VOL_OPT:
        break;
    case AREA_DARK_FALZ:
        return;
    case AREA_LOBBY:
        break;
    case AREA_BATTLE1:
        return;
    case AREA_BATTLE2:
        break;
    case AREA_PIONEER2_EP2:
        return;
    case AREA_VR_TEMPLE_ALPHA:
        break;
    case AREA_VR_TEMPLE_BETA:
        return;
    }
}

void TOTrapAncient01::vfunc_84() {  }

f32 TOTrapAncient01::receive_physical_attack(void *arg1, f32 farg0) {
    this->release_trapped_player();
    return TOTrap::receive_physical_attack(arg1, farg0);
}

#pragma push
#pragma pool_data off
#pragma opt_lifetimes off
void TOTrapAncient01::play_sounds() {
    TrapChipParams a = {
        {0.5f, 0.03f, 0.15f}, {0.0f, 0.0f, 0.0f},
        {3.0f, 5.0f, 3.0f}, {0x800, 0x100, 0x800}, {4, 30},
        {0.0f, 1.0f}, 0, 0, 22
    };
    {
        f32 x = position.x, y = position.y, z = position.z;
        a.pos[0] = x;
        a.pos[1] = y;
        a.pos[2] = z;
        a.floor_and_scale[0] = y;
    }
    a.model = get_bml_model((void *)TOTrapAncient01__bml_resource.value, 0);
    a.textures = TObjFish__sub_8001EDB0((void *)TOTrapAncient01__bml_resource.value, 0);
    TrapChipParams b = {
        {0.5f, 0.03f, 0.15f}, {0.0f, 0.0f, 0.0f},
        {3.0f, 5.0f, 3.0f}, {0x800, 0x100, 0x800}, {4, 30},
        {0.0f, 1.0f}, 0, 0, 22
    };
    {
        f32 x = position.x, y = position.y, z = position.z;
        b.pos[0] = x;
        b.pos[1] = y;
        b.pos[2] = z;
        b.floor_and_scale[0] = y;
    }
    b.model = get_bml_model((void *)TOTrapAncient01__bml_resource.value, 1);
    b.textures = TObjFish__sub_8001EDB0((void *)TOTrapAncient01__bml_resource.value, 1);
    TrapChipParams c = {
        {0.5f, 0.03f, 0.15f}, {0.0f, 0.0f, 0.0f},
        {3.0f, 5.0f, 3.0f}, {0x800, 0x100, 0x800}, {4, 30},
        {0.0f, 1.0f}, 0, 0, 22
    };
    {
        f32 x = position.x, y = position.y, z = position.z;
        c.pos[0] = x;
        c.pos[1] = y;
        c.pos[2] = z;
        c.floor_and_scale[0] = y;
    }
    c.model = get_bml_model((void *)TOTrapAncient01__bml_resource.value, 2);
    c.textures = TObjFish__sub_8001EDB0((void *)TOTrapAncient01__bml_resource.value, 2);
    void *o = __nw__7TObjectFUl(0x234);
    if (o != NULL) __ct__8TObjChipFP7TObjectP14TObjChipParams((u8 *)o, (u8 *)tl_06, (u8 *)&a);
    o = __nw__7TObjectFUl(0x234);
    if (o != NULL) __ct__8TObjChipFP7TObjectP14TObjChipParams((u8 *)o, (u8 *)tl_06, (u8 *)&b);
    o = __nw__7TObjectFUl(0x234);
    if (o != NULL) __ct__8TObjChipFP7TObjectP14TObjChipParams((u8 *)o, (u8 *)tl_06, (u8 *)&c);
    TParticleCtrl *particle = spawn_particle_effect(&position, 0x8b);
    if (particle != NULL) particle->set_scale(1.25f, 1.25f);
    switch (get_current_floor_area()) {
    case AREA_SEABED_UPPER: case AREA_SEABED_LOWER:
        play_sound_effect(0x4004c118, &position, 0, 0); return;
    case AREA_VR_TEMPLE_ALPHA: case AREA_VR_TEMPLE_BETA:
        play_sound_effect(0x4bc07, &position, 0, 0); return;
    case AREA_VR_SPACESHIP_ALPHA: case AREA_VR_SPACESHIP_BETA:
        play_sound_effect(0x4004bc07, &position, 0, 0); return;
    case AREA_SEASIDE_NIGHT:
        play_sound_effect(0x4004bc19, &position, 0, 0); return;
    case AREA_TOWER:
        play_sound_effect(0x4004bc19, &position, 0, 0); return;
    case AREA_CENTRAL_CONTROL_AREA: case AREA_JUNGLE_NORTH:
    case AREA_JUNGLE_EAST: case AREA_MOUNTAIN: case AREA_SEASIDE:
    case AREA_GAL_GRYPHON: case AREA_OLGA_FLOW: case AREA_BARBA_RAY:
    case AREA_GOL_DRAGON:
        break;
    }
    play_sound_effect(0x4004bc12, &position, 0, 0);
}
#pragma pop

void TOTrapAncient01::release_trapped_player() {
    s32 temp_r3;
    s32 temp_r3_2;
    if (TRaderMapCore::is_not_split_screen() == 1) {
        if (this->target != NULL) {
            temp_r3 = (s32)get_player_by_client_id((get_entity_id((TObjBase *)this->target)));
            if (temp_r3 != 0) {
                if (check_player_flag1__6TLobbyFv() != 0) {
                    TObjPlayer::send_code_45_1(temp_r3);
                }
                obj_clear_flag30_20000((TObjBase *)temp_r3);
            }
        }
    } else if ((this->target != NULL) && ((s32) local_client_id == (s32) get_entity_id((TObjBase *)this->target))) {
        temp_r3_2 = (s32)get_player_by_client_id(local_client_id);
        if (temp_r3_2 != 0) {
            if (check_player_flag1__6TLobbyFv() != 0) {
                TObjPlayer::send_code_45_1(temp_r3_2);
            }
            obj_clear_flag30_20000((TObjBase *)temp_r3_2);
        }
    }
}

void TOTrapAncient01::vfunc_6(s16 *arg1, s32 arg2) {
    if ((s16) *arg1 == 4) {
        if (arg2 == 1) {
            this->play_sounds();
        }
        this->release_trapped_player();
        set_flag8();
        queue_destruction__7TObjectFv(this);
    }
}

void TOTrapAncient01::vfunc_88() {  }

void TOTrapAncient01::vfunc_86() {  }

void TOTrap::apply_knockback_from_attacker(u8 *, f32) {  }

}
