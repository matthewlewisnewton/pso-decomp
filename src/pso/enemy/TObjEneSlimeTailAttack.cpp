#include "pso/enemy/BattleParameters.h"
#include "pso/render/render_util.h"
#include "pso/player/TObjPlayer_803E4954.h"
// Deferred generation keeps the native virtual tables in their original data
// order. Definitions below run in reverse address order to preserve text order.
#pragma defer_codegen on
#include "types.h"
#include "pso/enemy/TObjEneRe7Berura_803E4CE0.h"
#include "pso/player/TObjChara.h"
#include "pso/player/TObjPlayer.h"
#include "pso/TObject.h"
#include "pso/TObjControl.h"
#include "pso/system/BmlResource.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/object/TObjMotion.h"
#include "pso/misc/TLobby.h"
#include "pso/enemy/TObjEneSlimeOne.h"
#include "pso/enemy/TObjEneSlimeWaterBomb.h"
#include "pso/enemy/TObjEneSlimeTailAttack.h"
#include "pso/system/vector.h"

#include <stddef.h>

#include "pso/TParticleCtrl.h"
#include "pso/boss/TBoss3Volopt.h"
#include "pso/boss/TBoss4Type2.h"
#include "pso/enemy/TObjEneLappy.h"
#include "pso/enemy/TObjEnePanarms.h"
#include "pso/enemy/TObjEneRe7Berura.h"
#include "pso/misc/TNowLoading.h"
#include "pso/object/TObjFish.h"

typedef void (TObjEneSlimeOne::*SlimeAction)();
struct SlimeState { SlimeAction fn; SlimeAction update; };

struct E_800EB8DC { s32 f0; s32 f4; };

struct O_800EB8DC { u8 pad[0x3b8]; E_800EB8DC arr[4]; };

typedef struct { f32 x, y, z; } Vec_800EB7BC;
struct Tmpl_800EB7BC {
    s16 a;
    s16 b;
    s16 c;
    u16 d;
    u8 pad8[8];
    Vec_800EB7BC pos;
    u8 rest[0x40 - 0x1C];
};

struct Blob_800EB7BC { u8 bytes[0x40]; };

struct Slot_800EB7BC { s32 active; u32 obj; };

struct Obj_800EB7BC {
    u8 pad0[0x38];
    Vec_800EB7BC pos;
    u8 pad44[0x374 - 0x44];
    Tmpl_800EB7BC tmpl;
    s32 count;
    Slot_800EB7BC slots[8];
};

extern "C" {
s32 has_no_active_slot(O_800EB8DC *self);
u32 create__15TObjEneSlimeOneFlll(void *, void *, u32);
s32 spawn_slime_in_slot(Obj_800EB7BC *arg0, s32 arg1, Vec_800EB7BC *arg2, u32 arg3);


s32 spawn_slime_in_slot(Obj_800EB7BC *origin, s32 arg1, Vec_800EB7BC *arg2, u32 arg3);

s32 has_no_active_slot(O_800EB8DC *self);

}

#include "pso/unk/text_803E2D70.h"
#include "pso/enemy/TObjEneSlimeOne_800EC394.h"
#include "pso/enemy/TObjEneSlime.h"

#define CAT2(a,b) a##b
#define CAT(a,b) CAT2(a,b)
#define VA virtual void CAT(f,__LINE__)();
struct Base_800EBB18_800EB9F0 { char pad[0x18]; };
struct VObj_800EBB18_800EB9F0 : Base_800EBB18_800EB9F0 {
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
VA
    virtual void m77(s32 *);
};

struct Slot_800EB910 { s32 state; void *obj; };

struct Obj_800EB910 { u8 pad[0x3b8]; Slot_800EB910 slots[4]; };

struct Slot_800EB984 { s32 state; void *obj; };

struct Obj_800EB984 { u8 pad[0x3b8]; Slot_800EB984 slots[4]; };

extern "C" {
extern const Slot_800EB984 lbl_8043D218;
void debug_printf_at(s32 id, const char *fmt, ...);
s32 push_matrix();
s32 pop_matrix();
s32 set_global_param__8TObjFishFl();
extern char lbl_8043D298[];
extern void *slime_debug_label_table[2];
extern s32 lbl_80496368[2];
extern void *slime_bml_resource;
extern u32 model_render_flags;
void queue_destruction__7TObjectFv(void *arg0);

void TObjEneSlime__sub_800EB9F0(void* p, void* q);

}

#include "pso/enemy/TObjEneSlime_800EBBC8.h"
#include "pso/object/TObjDFHorming.h"

struct RecoveredGlobal_800EBC28___vt__12TObjEneSlime {
    s32 value;
    u8 remaining[0x14C];
};

extern "C" {
s32 __ct__9TObjEnemyFP7TObject(void *);
extern s32 __vt__12TObjEneSlime[];
extern s32 lbl_805D2AD8;
void __dt__11BmlResourceFv(void*, int);
void __dl__7TObjectFPv(void *);
void *__dt__9TObjEnemyFv(TObjEnemy *arg0, s16 arg1);

void *__dt__12TObjEneSlimeFv(void *arg0, s16 arg1);

extern void *slime_bml_resource;

typedef char RecoveredGlobal_800EBC28___vt__12TObjEneSlime_size[sizeof(RecoveredGlobal_800EBC28___vt__12TObjEneSlime) == 0x150 ? 1 : -1];
u8 *TObjEneSlime__ct(TObjEneSlime *ene_slime, s32 arg1, u8 *arg2);

}

extern "C" {

void *__ct__11BmlResourceFlP21BmlResourceDescriptorllPv(void *, s32, s32 *, s32, s32, s32);

extern BmlResourceDescriptor slime_pair_resource_descriptor;
extern void *slime_bml_resource;
extern const f32 lbl_805DA66C;
extern const f32 lbl_805DA6B4;

extern s32 tl_04;

}

#include "pso/misc/MaterialColorFade.h"
#include "pso/player/TObjPlayer_800EBE2C.h"
#include "pso/system/ChunkMaterialState.h"

struct Stack_800EBE74 {
    f32 sp8;
    f32 spC;
    f32 sp10;
    f32 sp14;
};

extern "C" {
extern const f32 lbl_805DA6B4;
extern int saved_model_render_flags;
extern int saved_chunk_polygon_flags_and_mask;
extern int saved_chunk_polygon_flags_or_mask;
extern int chunk_polygon_flags_or_mask;
extern int chunk_polygon_flags_and_mask;
extern u32 model_render_flags;
extern const f32 lbl_805DA6F8;

void TObjPlayer__sub_800EBE48(f32 farg0);

}

#undef VA
#undef CAT
#undef CAT2

extern "C" {
f64 atan2_float(f32, f32);
u32 csnLookAt(void *, void *);
s32 angle_difference_abs(s32, s32);
s32 approach_angle_limited(s32, s32, s32);
s32 project_actor_to_ground(void *, void *, int);
s32 vec3_add_to(void *, void *);
f32 vector_length(void *);
void normalize_vector(void *);
extern const f64 lbl_8043D280[];
extern const f32 lbl_805DA718;
extern const f32 lbl_805DA71C;
extern const f32 lbl_805DA720;
extern const f32 lbl_805DA724;
f32 random_ratio__9TObjCharaFv(void *);
s32 play_sound_effect(int, void *, int, int);
f32 sin_table_lookup(s32);
f32 cos_table_lookup(s32);
extern const f32 lbl_805DA66C;
extern const f32 lbl_805DA6B4;
extern const f32 lbl_805DA758;
extern const f32 lbl_805DA6AC;
void TObjPlayer__sub_800EBE48(f32 farg0);
s32 defer_render__7TObjectFv(void *);
void scale_matrix_vec3(u8 *arg0, u8 *arg1);
s32 rotate_matrix_y(int, int);
s32 push_matrix();
s32 pop_matrix();
s32 post_translate_matrix(void *);
extern const f32 lbl_805DA67C;
extern const f32 lbl_805DA6E4;
extern const f32 lbl_805DA728;
s32 TObjFish__sub_8001EDB0(s32, s32);

u8 *get_instance__15TObjEneSlimeOneFv();
s32 init_collision_body_parts(void *, void *, int);
extern const f32 lbl_805DA754;
extern SlimeState lbl_80496574[15];
extern s32 lbl_80496368[2];
extern TObjMotionAction lbl_8049639C[7];

#pragma push
#pragma auto_inline on
#pragma dont_inline off
#pragma inline_depth(2)

#pragma pop

// Twelve-byte per-enemy saved-state record exchanged by TObjEnemy.
struct SlimeSavedState {
    s32 flags;
    u16 unknown4;
    s16 unknown6;
    u8 unknown8[4];
};

u16 find_nearest_visible_player(void *, void *, f32);
void queue_destruction__7TObjectFv(void *);

u8 * get_bml_motion(s32, s32);
void transform_to_view__11TCameraCtrlFii(s32, s32);
void *spawn_particle_effect(void *pos, s32 id);
void *create_particle_emitter(void *pos, s32 id);
void get_slime_tail_pose(SlimeTailPose *arg0);
SlimeTailPose * copy_slime_tail_pose(SlimeTailPose *dst, SlimeTailPose *src);
void capture_slime_tail_node(void);
void reset_slime_tail_node_index(void);
s16 check_player_field_7cc__15TObjEneSlimeOneFv();
void draw_blob_shadow(s32 arg0);
void * __ct__11TObjControlFP7TObject(void *, s32);
u8 *get_enemy_entity(u16 arg0);
int get_entity_id(void *);
void *__dt__9TObjEnemyFv(TObjEnemy *arg0, s16 arg1);
s32 __ct__9TObjEnemyFP7TObject(void *);

}
void direction_to_rotation_xz(u8 *arg0, s32 *arg1, s32 *arg2);
extern "C" {
s32 advance_animation__10TObjMotionFv(void *);
void free_collision_body_parts(void *);
TObjPlayer *get_player_by_client_id(s32);
void __dl__7TObjectFPv(void *);
void * __nw__7TObjectFUl(s32);
s32 scale_matrix(int, f32, f32, f32);
s32 rotate_matrix_z(int, int);
void subtract_vector(void *, void *);
void translate_matrix(u32 arg0, f32 x, f32 y, f32 z);
s32 rotate_matrix_x(int, int);
s32 scale_current_matrix(Vec *);
void draw_chunk_object(void *child);

extern const Vec lbl_8043D230;
extern const Vec lbl_8043D23C;
extern DirectAttackPayload lbl_8043D260[];
extern SlimeTailPose lbl_80501010;
extern const char *TObjEneSlimeOne_class_name;
extern const char *lbl_805D2AE0;
extern int lbl_805D52B4;
extern s32 registered_player_count;
extern const f32 lbl_805DA670;
extern const f32 lbl_805DA674;
extern const f32 lbl_805DA678;
extern const f32 lbl_805DA680;
extern const f32 lbl_805DA684;
extern const f32 lbl_805DA688;
extern const f32 lbl_805DA68C;
extern const f32 lbl_805DA690;
extern const f32 lbl_805DA694;
extern const f32 lbl_805DA698;
extern const f32 lbl_805DA69C;
extern const f32 lbl_805DA6A0;
extern const f32 lbl_805DA6A4;
extern const f32 lbl_805DA6A8;
extern const f32 lbl_805DA6B0;
extern const f32 lbl_805DA6B8;
extern const f32 lbl_805DA6BC;
extern const f32 lbl_805DA6C0;
extern const f32 lbl_805DA6C4;
extern const f32 lbl_805DA6C8;
extern const f32 lbl_805DA6CC;
extern const f32 lbl_805DA6D0;
extern const f32 lbl_805DA6D4;
extern const f32 lbl_805DA6D8;
extern const f32 lbl_805DA6DC;
extern const f32 lbl_805DA6E0;
extern const f32 lbl_805DA6E8;
extern const f32 lbl_805DA6EC;
extern const f32 lbl_805DA6F0;
extern const f32 lbl_805DA6F4;
extern const f32 lbl_805DA6F8;
extern const f32 lbl_805DA6FC;
extern const f32 lbl_805DA708;
extern const f32 lbl_805DA70C;
extern const f32 lbl_805DA710;
extern const f32 lbl_805DA714;
extern const f32 lbl_805DA72C;
extern const f32 lbl_805DA730;
extern const f32 lbl_805DA734;
extern const f32 lbl_805DA738;
extern const f32 lbl_805DA73C;
extern const f32 lbl_805DA740;
extern const f32 lbl_805DA744;
extern const f32 lbl_805DA748;
extern const f32 lbl_805DA74C;
extern const f32 lbl_805DA750;
extern s32 tl_04;

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off

extern "C" {
extern u8 lbl_8043D008[];
}
extern "C" {
extern u8 lbl_8043D01C[];
}
extern "C" {
extern u8 lbl_8043D030[];
}
extern "C" {
extern u8 lbl_8043D044[];
}
extern "C" {
extern u8 lbl_8043D058[];
}
extern "C" {
extern u8 lbl_8043D06C[];
}
extern "C" {
extern u8 lbl_8043D080[];
}
extern "C" {
extern u8 lbl_8043D09C[];
}
extern "C" {
extern u8 lbl_8043D0B8[];
}
extern "C" {
extern u8 lbl_8043D0D4[];
}
extern "C" {
extern u8 lbl_8043D0F0[];
}
extern "C" {
extern u8 lbl_8043D108[];
}
extern "C" {
extern u8 lbl_8043D120[];
}
extern "C" {
extern u8 lbl_8043D138[];
}
extern "C" {
extern u8 lbl_8043D150[];
}
extern "C" {
extern u8 lbl_8043D16C[];
}
extern "C" {
extern u8 lbl_8043D188[];
}
extern "C" {
extern u8 lbl_8043D1A0[];
}
extern "C" {
extern u8 lbl_8043D1B8[];
}
extern "C" {
extern u8 lbl_8043D1D0[];
}
extern "C" {
extern u8 lbl_8043D1EC[];
}
extern "C" {
extern u8 lbl_8043D210[];
}
extern "C" {
extern u8 lbl_805DA668[];
}
extern "C" {
s32 submit_cursor_candidate(void *, s32);
s32 minimap_render_dot(void *, s32, s32, s32);
s32 play_persistent_sound(s32 id, s32 a1, u32 src, s32 a3, s32 flags);
}

extern const char *slime_model_name_ptr_table[7];
extern const char *bm4_ps_ma_body_motion_names[15];

const char *slime_model_name_ptr_table[7] = {
    (const char *)lbl_8043D008, (const char *)lbl_8043D01C, (const char *)lbl_8043D030, (const char *)lbl_8043D044,
    (const char *)lbl_8043D058, (const char *)lbl_8043D06C, NULL,
};
const char *bm4_ps_ma_body_motion_names[15] = {
    (const char *)lbl_8043D080, (const char *)lbl_8043D09C, (const char *)lbl_8043D0B8, (const char *)lbl_8043D0D4,
    (const char *)lbl_8043D0F0, (const char *)lbl_8043D108, (const char *)lbl_8043D120, (const char *)lbl_8043D138,
    (const char *)lbl_8043D150, (const char *)lbl_8043D16C, (const char *)lbl_8043D188, (const char *)lbl_8043D1A0,
    (const char *)lbl_8043D1B8, (const char *)lbl_8043D1D0, NULL,
};
BmlResourceDescriptor slime_pair_resource_descriptor = {
    (const char *)lbl_8043D1EC, slime_model_name_ptr_table, bm4_ps_ma_body_motion_names, 6, 14,
};
__declspec(section ".data") void *slime_debug_label_table[2] = {
    (void *)&lbl_8043D210, (void *)&lbl_805DA668,
};
__declspec(section ".data") s32 lbl_80496368[2] = {
    0x4, 0x5,
};
CollisionBody lbl_80496370[1] = {
    {{0.0F, 15.0F, 0.0F}, 7.5F, 0.0F, 0, 0x8003, {0.0F, 0.0F, 0.0F}, 0.0F},
};
TObjMotionAction lbl_8049639C[7] = {
        {1, 0, 10, 0.5F, 0},
        {2, 2, 10, 0.5F, 0},
        {1, 0, 13, 0.5F, 0},
        {2, 0, 2, 0.8F, 0},
        {3, 0, 8, 0.8F, 0},
        {3, 0, 3, 0.8F, 0},
        {3, 0, 9, 0.8F, 0},
};
SlimeState lbl_80496574[15] = {
        {&TObjEneSlimeOne::init_state, &TObjEneSlimeOne::update_wait_search},
        {&TObjEneSlimeOne::reset_display, &TObjEneSlimeOne::fn_800EA820},
        {&TObjEneSlimeOne::init_slime_display, &TObjEneSlimeOne::fn_800EA678},
        {&TObjEneSlimeOne::fn_800EA56C, &TObjEneSlimeOne::fn_800EA364},
        {&TObjEneSlimeOne::enter_slime_state, &TObjEneSlimeOne::update_slime_timer},
        {&TObjEneSlimeOne::enter_appear_state, &TObjEneSlimeOne::update_dive_timer},
        {&TObjEneSlimeOne::fn_800EA120, &TObjEneSlimeOne::fn_800E9EFC},
        {&TObjEneSlimeOne::init_slime_state, &TObjEneSlimeOne::fn_800E9DC8},
        {&TObjEneSlimeOne::fn_800E9D7C, &TObjEneSlimeOne::fn_800E9BCC},
        {&TObjEneSlimeOne::begin_appear, &TObjEneSlimeOne::update_water_bomb_timer},
        {&TObjEneSlimeOne::start_tail_attack, &TObjEneSlimeOne::tick_timer},
        {&TObjEneSlimeOne::reset_display_state, &TObjEneSlimeOne::update_tick},
        {&TObjEneSlimeOne::init_split_effect, &TObjEneSlimeOne::fn_800E969C},
        {&TObjEneSlimeOne::fn_800E95F4, &TObjEneSlimeOne::update_effect_fade_lifetime},
        {&TObjEneSlimeOne::fn_800E9538, &TObjEneSlimeOne::fn_800E92D8},
};
__declspec(section ".data") s32 lbl_804966DC[2] = {
    0x0, 0x2,
};
__declspec(section ".data") s32 slime_tail_attack_id_pair[2] = {
    0x4, 0x5,
};
__declspec(section ".data") s32 TObjEneSlime__attack_target_param_table[2] = {
    0x30, 0x34,
};
__declspec(section ".data") s32 lbl_804966F4[2] = {
    0x1, 0x3,
};
__declspec(section ".data") s32 lbl_804966FC[2] = {
    0x30, 0x34,
};
Vec slime_tail_attack_zero_vec = {0.0F, 0.0F, 0.0F};
Vec slime_tail_attack_transform = {0.0F, 0.0F, 0.0F};

#pragma pop

extern "C" const char *TObjEneSlimeTailAttack__name;

f32 fabs_float(f32);
extern const f32 lbl_805DA700;
extern const f32 lbl_805DA704;

}

#pragma auto_inline off
#pragma dont_inline off
#pragma inline_depth(1)

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
void TObjPlayer::push_material_color_override(f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    Stack_800EBE74 stack;
    (*(s32 *)&saved_model_render_flags) = (*(s32 *)&model_render_flags);
    (*(s32 *)&saved_chunk_polygon_flags_and_mask) = (*(s32 *)&chunk_polygon_flags_and_mask);
    (*(s32 *)&saved_chunk_polygon_flags_or_mask) = (*(s32 *)&chunk_polygon_flags_or_mask);
    (*(s32 *)&model_render_flags) |= 0x20;
    set_chunk_material_override_pair(0xFF00, 0x800);
    stack.spC = farg1;
    stack.sp10 = farg2;
    stack.sp8 = lbl_805DA6F8 + farg0;
    stack.sp14 = farg3;
    set_constant_material((const NJS_ARGB *)((&stack.sp8)));
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
extern "C" {
void TObjPlayer__sub_800EBE48(f32 farg0) {
    TObjPlayer::push_material_color_override(farg0, lbl_805DA6B4, lbl_805DA6B4, lbl_805DA6B4);
}
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
void TObjPlayer::init_render_globals() { chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask; chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask; model_render_flags = saved_model_render_flags; }
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
s32 TObjEneSlime::create(s32 arg0) {
    s32 ene_slime;
    s32 var_r4;

    ene_slime = (s32)__nw__7TObjectFUl(0x3D8);
    if (ene_slime != 0) {
        var_r4 = (s32)__nw__7TObjectFUl(0x20);
        if (var_r4 != 0) {
            var_r4 = (s32)__ct__11TObjControlFP7TObject((void *)var_r4, (s32)tl_04);
        }
        ene_slime = (s32)TObjEneSlime__ct((TObjEneSlime *)((u8 *)ene_slime), var_r4, (u8 *)arg0);
    }
    return ene_slime;
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEneSlime::spawn_pair() {
    void *temp_r4;
    void *temp_r5;
    void *temp_r5_2;

    temp_r4 = ::operator new(0x440);
    if (temp_r4 != NULL) {
        temp_r4 = __ct__11BmlResourceFlP21BmlResourceDescriptorllPv(temp_r4, 1, (s32 *)&slime_pair_resource_descriptor, 0, 0, 0);
    }
    slime_bml_resource = temp_r4;
    temp_r5 = *(void **)((s8 *)temp_r4 + 0x42C);
    TObjEneSlime::spawn_child(0x28, *(s32 *)((s8 *)temp_r5 + 0x48), *(s32 *)((s8 *)temp_r5 + 0x4C), lbl_805DA66C, lbl_805DA6B4);
    temp_r5_2 = *(void **)((s8 *)slime_bml_resource + 0x42C);
    TObjEneSlime::spawn_child(0x29, *(s32 *)((s8 *)temp_r5_2 + 0x58), *(s32 *)((s8 *)temp_r5_2 + 0x5C), lbl_805DA66C, lbl_805DA6B4);
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEneSlime::free_instance() {
    if ((u32) slime_bml_resource != 0U) {
        __dt__11BmlResourceFv((void*)slime_bml_resource, 1);
        slime_bml_resource = 0U;
    }
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
extern "C" {
u8 *TObjEneSlime__ct(TObjEneSlime *ene_slime, s32 arg1, u8 *arg2) {
    s32 temp_r0;
    __ct__9TObjEnemyFP7TObject(ene_slime);
    *(s32 **)((s8 *)ene_slime + 0x18) = &(*(RecoveredGlobal_800EBC28___vt__12TObjEneSlime *)&__vt__12TObjEneSlime).value;
    *(s32 *)((s8 *)ene_slime + 0) = (s32) lbl_805D2AD8;
    ((TObjEneSlime *)(ene_slime))->apply_set_data(arg2);
    ((TObjEneSlime *)(ene_slime))->clear_lobby_object_state();
    ((TBoss3Volopt *)ene_slime)->reset_photon_effect();
    TBoss4DarkFalz__sub_8004B4F0(((u8 *)ene_slime + 0x374), (arg2));
    ene_slime->m_3b4 = (s32) *(s16 *)((s8 *)arg2 + 2);
    temp_r0 = ene_slime->m_3b4;
    if (temp_r0 < 1) {
        if (TObjPlayer::check_demo_mode() != 0) {
            ene_slime->m_3b4 = 3;
        }
    } else if (temp_r0 > 4) {
        ene_slime->m_3b4 = 4;
    }
    ene_slime->actorFlags = (s32) (ene_slime->actorFlags | 0x02000000);
    ene_slime->init_slots();
    return (u8 *)ene_slime;
}
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
extern "C" {
void *__dt__12TObjEneSlimeFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__12TObjEneSlime;
        ((TObjEneSlime *)arg0)->release_split_slimes();
        __dt__9TObjEnemyFv((TObjEnemy *)arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEneSlime::vfunc_63() { this->release_split_slimes(); }
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEneSlime::run_task() {
    s32 sp8;

    if ((TObjPlayer::check_demo_mode() == 0) && (has_no_active_slot((O_800EB8DC *)this) != 0)) {
        sp8 = 0x800;
        send_6x0A_enemy_state(&sp8);
        exchange_object_state((s32)&sp8, (s16)0);
        ((VObj_800EBB18_800EB9F0 *)this)->m77(&sp8);
        send_entity_set_flags();
        queue_destruction__7TObjectFv(this);
    }
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEneSlime::render() {
    u8 *arg0 = (u8 *)this;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r31;
    temp_r31 = ((s32 (*)(void))defer_render__7TObjectFv)();
    if (TObjPlayer::check_demo_mode() != 0) {
        temp_r30 = (this->state36C * 4) & 4;
        debug_printf_at(0x130020, lbl_8043D298, (int) (*(s32 *)((s8 *)((u8 *)slime_debug_label_table + temp_r30) + 0)));
        TObjPlayer::toggle_particle_effect();
        push_matrix();
        temp_r30_2 = *(s32 *)((s8 *)((u8 *)lbl_80496368 + temp_r30) + 0);
        ((s32 (*)(void *, void *))post_translate_matrix)((void *) ((u8 *)arg0 + 0x38), (void *)lbl_80496368);
        TObjFish__sub_8001EDB0((s32)slime_bml_resource, temp_r30_2);
        set_global_param__8TObjFishFl();
        if (temp_r31 != 0) {
            model_render_flags |= 0x400000;
            set_chunk_render_flags(1);
            draw_chunk_object((void *)get_bml_model((BmlResource *)slime_bml_resource, temp_r30_2));
            clear_chunk_render_flags();
            model_render_flags &= 0xFFBFFFFF;
        } else {
            set_chunk_render_flags(2);
            set_cull_back();
            draw_chunk_object((void *)get_bml_model((BmlResource *)slime_bml_resource, temp_r30_2));
            set_cull_front();
            draw_chunk_object((void *)get_bml_model((BmlResource *)slime_bml_resource, temp_r30_2));
            set_cull_none();
            clear_chunk_render_flags();
        }
        pop_matrix();
        TParticleCtrl::end_effect_render();
    }
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
extern "C" {
void TObjEneSlime__sub_800EB9F0(void* p, void* q) { *(u32*)((char*)p + 0x0) = *(u32*)((char*)q + 0x0); *(u32*)((char*)p + 0x4) = *(u32*)((char*)q + 0x4); }
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEneSlime::init_slots() {
    s32 i;
    for (i = 0; i < 4; i++) {
        TObjEneSlime__sub_800EB9F0(&((Obj_800EB984 *)this)->slots[i], (void *)&lbl_8043D218);
    }
    spawn_slime_in_slot((Obj_800EB7BC *)this, 0, 0, 0);
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEneSlime::release_split_slimes() {
    Obj_800EB910 *self = (Obj_800EB910 *)this;
    s32 i;
    for (i = 0; i < 4; i++) {
        Slot_800EB910 *s = &self->slots[i];
        if (s->state == 1) {
            if (s->obj != 0) {
                TObjEneSlimeOne__sub_800EC470(s->obj);
                s->obj = 0;
            }
            s->state = 2;
        }
    }
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
extern "C" {
s32 has_no_active_slot(O_800EB8DC *self) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (self->arr[i].f0 == 1) {
            return 0;
        }
    }
    return 1;
}
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
extern "C" {
s32 spawn_slime_in_slot(Obj_800EB7BC *origin, s32 arg1, Vec_800EB7BC *arg2, u32 arg3) {
    Tmpl_800EB7BC t;
    Slot_800EB7BC *slot;
    s32 n;
    if (arg1 < 0 || arg1 >= origin->count || origin->slots[arg1].active != 0) {
        return 0;
    }
    *(Blob_800EB7BC *) &t = *(Blob_800EB7BC *) &origin->tmpl;
    n = arg1 + 1;
    t.a = origin->tmpl.a + n;
    t.b = 0;
    t.d = origin->tmpl.d + n;
    if (arg2 == NULL) {
        VecCopy((Vec *)&t.pos, (const Vec *)&origin->pos);
    } else {
        VecCopy((Vec *)&t.pos, (const Vec *)arg2);
    }
    slot = &origin->slots[arg1];
    if (arg3 == 0) {
        slot->obj = TObjEneSlimeOne::create((s32) origin, (s32) &t);
    } else {
        slot->obj = create__15TObjEneSlimeOneFlll(origin, &t, arg3);
    }
    if (slot->obj == 0) {
        return 0;
    }
    slot->active = 1;
    return 1;
}
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEneSlime::release_child_slot(s32 id) {
    s32 i = id - entity_id - 1;
    if (i < 0 || i >= 4 || child_slots[i].state != 1) {
        return;
    }
    child_slots[i].slime = 0;
    child_slots[i].state = 2;
}
#pragma pop
#pragma push
s32 TObjEneSlime::try_spawn_child(void *arg1) {
    s32 i;
    Vec pos;
    Vec dir;
    s32 ang;
    s32 n;
    TObjEneSlime *origin = this;
    n = origin->m_3b4;
    for (i = 0; i < n && origin->child_slots[i].state != 0; i++) {
    }
    if (i == n) {
        return 0;
    }
    VecCopy((Vec *)&pos, (const Vec *)arg1);
    pos.y += lbl_805DA66C;
    ang = (s16) (lbl_805DA758 * random_ratio__9TObjCharaFv(origin));
    dir.x = sin_table_lookup(ang);
    dir.y = lbl_805DA6B4;
    dir.z = cos_table_lookup(ang);
    if (vector_length(&dir) <= lbl_805DA718) {
        dir.x = lbl_805DA67C;
        dir.z = dir.y = lbl_805DA6B4;
    } else {
        normalize_vector(&dir);
    }
    play_sound_effect(0x4003A619, &pos, 0, 0);
    return spawn_slime_in_slot((Obj_800EB7BC *)origin, i, (Vec_800EB7BC *)&pos, (u32)&dir);
}
#pragma pop

#pragma push

s32 TObjEneSlimeOne::create(s32 owner, s32 set_data) {
    return (s32)new TObjEneSlimeOne(new TObjControl((TObject *)tl_04), (TObjEneSlime *)owner, (void *)set_data);
}
#pragma pop

#pragma push

s32 TObjEneSlimeOne::create(s32 owner, s32 set_data, s32 velocity) {
    return (s32)new TObjEneSlimeOne(new TObjControl((TObject *)tl_04), (TObjEneSlime *)owner, (void *)set_data, (const Vec *)velocity);
}
#pragma pop

#pragma push

#pragma opt_common_subs off
TObjEneSlimeOne::TObjEneSlimeOne(TObject *parent, TObjEneSlime *owner, void *set_data)
    : TObjEnemy(parent) {
    SlimeSavedState state;
    m_name = TObjEneSlimeOne_class_name;
    add_flags_2e4(2);
    apply_set_data(set_data);
    if (exchange_object_state((s32)&state, 1) != 0) {
        state.flags = 0;
        state.unknown6 = 0;
        exchange_object_state((s32)&state, 0);
    }
    slime_group = owner;
    initialize_slime_instance_state();
    project_actor_to_ground(this, &position, 0);
    set_state(0);
}
#pragma pop

#pragma push

#pragma opt_common_subs off
TObjEneSlimeOne::TObjEneSlimeOne(TObject *parent, TObjEneSlime *owner, void *set_data, const Vec *velocity)
    : TObjEnemy(parent) {
    SlimeSavedState state;
    m_name = TObjEneSlimeOne_class_name;
    add_flags_2e4(2);
    apply_set_data(set_data);
    if (exchange_object_state((s32)&state, 1) != 0) {
        state.flags = 0;
        state.unknown6 = 0;
        exchange_object_state((s32)&state, 0);
    }
    slime_group = owner;
    VecCopy(&m_3dc, velocity);
    initialize_slime_instance_state();
    set_state(14);
}
#pragma pop

#pragma push

void TObjEneSlimeOne::initialize_slime_instance_state() {
  void *p;
  s32 id;
  s32 *new_var2;
  Vec *new_var;
    TObjEneSlimeOne *actor = this;
  actor->m_380 = get_instance__15TObjEneSlimeOneFv();
  if ((random_ratio__9TObjCharaFv(actor) < lbl_805DA754) || ((actor->state36C) & 1))
  {
    actor->variant = 1;
  }
  else
  {
    actor->variant = 0;
  }
  new_var2 = &(actor->variant);
  id = ((s32 *) lbl_804966DC)[*new_var2];
  actor->texlist = TObjFish__sub_8001EDB0((s32)(actor->m_380), id);
  actor->model = (void *)get_bml_model((BmlResource *)actor->m_380, id);
  VecCopy(&actor->prev_position, VecCopy(&actor->home_position, VecCopy(&actor->center, &actor->position)));
  actor->collision_body = (CollisionBody *)init_collision_body_parts(actor, lbl_80496370, 1);
  actor->set_field_d8((s32)lbl_8049639C);
  actor->set_field_dc((s32)((BmlResource *)actor->m_380)->motions);
  actor->set_animation(0);
  actor->set_field_b8(0);
  VecCopy(new_var = actor->body_center(), &actor->position);
  actor->movement_velocity.z = lbl_805DA6B4;
  actor->movement_velocity.y = lbl_805DA6B4;
  actor->movement_velocity.x = lbl_805DA6B4;
  actor->target = 0;
  if ((*new_var2) == 0)
  {
    actor->bind_enemy_combat_stats((u8 *)(get_battle_base_stats(0x30)), (u8 *)(get_battle_attack_params(0x30)), (u8 *)(get_battle_resistance_params(0x30)));
  }
  else
  {
    actor->bind_enemy_combat_stats((u8 *)(get_battle_base_stats(0x34)), (u8 *)(get_battle_attack_params(0x34)), (u8 *)(get_battle_resistance_params(0x34)));
  }
  actor->referenceHp = actor->hp;
  ((TBoss3Volopt *)actor)->reset_photon_effect();
  actor->movementParameters = 0;
  if ((*new_var2) == 0)
  {
    actor->set_param(0x13);
  }
  else
  {
    actor->set_param(0x14);
  }
  p = new SlimeAnimationState((TObjEneSlimeOne *)actor);
  actor->animation = (SlimeAnimationState *)p;
  actor->m_3e8 = 0;
  actor->m_3cc = 0xFFFF;
  actor->copy_position();
}
#pragma pop

#pragma push

TObjEneSlimeOne::~TObjEneSlimeOne() {
    free_collision_body_parts(this);
    collision_body = NULL;
    if (m_3e8 != NULL) {
        TParticleCtrl::release(m_3e8);
        m_3e8 = NULL;
    }
    delete animation;
    animation = NULL;
}
#pragma pop

#pragma push

void TObjEneSlimeOne::run_task() {
    if (TObjPlayer::check_demo_mode() == 0) {
        if ((s32)this->m_384 != 13 && (this->slime_group == 0 || ((TObject *)this->slime_group)->all_parents_unqueued_for_destruction() == 0)) {
            set_state(13);
        }
        set_target_flag_bit0();
        {
            SlimeState *tbl = lbl_80496574;
            SlimeAction a = tbl[m_384].update;
            if (a != 0) {}
            (this->*a)();
        }
        update_prev_position();
        ((TObjPlayer *)this)->update_collisions();
        if ((s32)this->m_3ec != 0) {
            submit_cursor_candidate(this, -1);
        }
        ((TObjEneSlimeOne *)this)->animation->advance();
        play_persistent_sound(0x4003B21C, (s32)this, (u32)&this->position, 0, 0);
        update_trail_position();
        clear_child_flag();
        if ((s32)this->m_384 != 13) {
            minimap_render_dot(body_center(), -0x5DB4, 1, 0);
        }
    }
}
#pragma pop

#pragma push

void TObjEneSlimeOne::render() {
    TObjEneSlimeOne *ene_slime_one = this;
    s32 temp_r31;
    if ((TObjPlayer::check_demo_mode() == 0) && !(ene_slime_one->m_3a0 <= lbl_805DA6B4) && (ene_slime_one->update_object_view_visibility(lbl_805DA728, lbl_805DA6E4) != 0)) {
        temp_r31 = ene_slime_one->defer_render();
        if (ene_slime_one->m_3a0 < lbl_805DA67C) {
            TObjPlayer__sub_800EBE48(ene_slime_one->m_3a0);
        }
        TObjPlayer::toggle_particle_effect();
        push_matrix();
        {
            Vec v = ene_slime_one->position;
            v.y += ene_slime_one->vertical_offset;
            post_translate_matrix(&v);
        }
        rotate_matrix_y(0, ene_slime_one->rotation_y);
        scale_matrix_vec3(0, (u8 *)&ene_slime_one->render_scale);
        ((TObjEneSlimeOne *)ene_slime_one)->animation->draw(temp_r31);
        pop_matrix();
        TParticleCtrl::end_effect_render();
        if (ene_slime_one->m_3a0 < lbl_805DA67C) {
            TObjPlayer::init_render_globals();
        }
        ene_slime_one->sub_800E9090();
    }
}
#pragma pop

#pragma push

void TObjEneSlimeOne::set_state(s32 arg1) {
    m_384 = arg1;
    SlimeAction a = lbl_80496574[m_384].fn;
    if (a != 0) {}
    (this->*a)();
}
#pragma pop

#pragma push

void TObjEneSlimeOne::set_random_timer(s32 minimum, s32 range) {
    m_390 = minimum + (s32)((f32)range * random_ratio__9TObjCharaFv(this));
}
#pragma pop

#pragma push
#pragma fp_contract on
s32 TObjEneSlimeOne::project_to_ground() {
    Vec sp = position;
    sp.y = sp.y + lbl_805DA6AC;
    if (project_actor_to_ground(this, &sp, 0) != 0) {
        position.y += lbl_805DA678 * (sp.y - position.y);
        return 1;
    }
    return 0;
}
#pragma pop

#pragma push

void TObjEneSlimeOne::set_display_mode(s32 mode) {
    collision_body->flags &= 0xF5FFF297;
    switch (mode) {
    case 0:
        collision_body->flags |= 0x0A000000 | 0x528;
        m_3ec = 0;
        return;
    case 1:
        collision_body->flags |= 0x0A000000 | 0x28;
        m_3ec = 0;
        return;
    case 2:
        m_3ec = 1;
        return;
    }
}

#pragma pop

#pragma push

void TObjEneSlimeOne::set_target_flag_bit0() {
    collision_body->flags |= 1;
}
#pragma pop

#pragma push

void TObjEneSlimeOne::clear_child_flag() {
    if (m_3ec == 0) {
        collision_body->flags &= ~1;
    }
}
#pragma pop

#pragma push

f32 TObjEneSlimeOne::receive_direct_attack(void *attacker, DirectAttackPayload payload,
                                         void *source, s32, s32) {
    if (payload.kind == 2 && slime_group != 0 &&
        slime_group->all_parents_unqueued_for_destruction()) {
        slime_group->try_spawn_child(&position);
    }
    TObjChara::receive_direct_attack(attacker, payload, source, -1, -1);
    return lbl_805DA6B4;
}
#pragma pop

#pragma push

void TObjEneSlimeOne::vfunc_63() { if (*(int *)&this->m_384 != 13) { set_state((s32)((void*)((void*)13))); } }
#pragma pop

#pragma push

void TObjEneSlimeOne::vfunc_62() {
    u8 *arg0 = (u8 *)this;
    if ((s32) this->m_384 != 0xC) {
        if (((s32) this->m_2d4 < (s32) registered_player_count) && (((u32 (*)(void))get_player_by_client_id)() != 0U) && (check_player_field_7cc__15TObjEneSlimeOneFv() == 2) && ((u32) this->slime_group != 0U) && (((TObject *)((void *) this->slime_group))->all_parents_unqueued_for_destruction() != 0)) {
            slime_group->try_spawn_child((u8 *)&this->position);
        }
        this->actorFlags = (s32) (this->actorFlags & 0xFFFFFDFF);
        ((TObjEneSlimeOne *)arg0)->set_state((s32)((void*)(0xC)));
    }
}
#pragma pop

#pragma push

void TObjEneSlimeOne::vfunc_61() {
    u8 *arg0 = (u8 *)this;
    if ((s32) this->m_384 != 0xB) {
        this->actorFlags = (s32) (this->actorFlags & 0xFFFFFEFF);
        ((TObjEneSlimeOne *)arg0)->set_state((s32)((void*)(0xB)));
    }
}
#pragma pop

#pragma push

void TObjEneSlimeOne::set_random_timer_15() { set_random_timer(15, 15); }
#pragma pop

#pragma push

void TObjEneSlimeOne::init_state() {
    project_to_ground();
    vertical_offset = lbl_805DA708;
    this->render_scale.z = lbl_805DA6B4;
    render_scale.y = lbl_805DA6B4;
    render_scale.x = lbl_805DA6B4;
    this->m_3a0 = lbl_805DA6B4;
    this->m_3c8 = 0;
    this->animation->set_state(7);
    set_display_mode(0);
    this->actorFlags = (this->actorFlags | 0x40000);
    this->set_random_timer_15();
}
#pragma pop

#pragma push

void TObjEneSlimeOne::update_wait_search() {
    TObjEneSlimeOne *ene_slime_one = (TObjEneSlimeOne *)this;
    s32 temp_r0;
    s32 temp_r0_2;

    temp_r0 = ene_slime_one->m_390 - 1;
    ene_slime_one->m_390 = temp_r0;
    if (temp_r0 <= 0) {
        if (((u16 (*)(void *, s32, f32))find_nearest_visible_player)(ene_slime_one, 0, (*(f32 *)&lbl_805DA6DC)) == 0xFFFF) {
            temp_r0_2 = ene_slime_one->m_3c8 + 1;
            ene_slime_one->m_3c8 = temp_r0_2;
            if (temp_r0_2 >= 5) {
                ene_slime_one->position.x = (f32) ene_slime_one->home_position.x;
                ene_slime_one->position.z = (f32) ene_slime_one->home_position.z;
                ene_slime_one->m_3c8 = 5;
            }
            ene_slime_one->set_random_timer_15();
            return;
        }
        ene_slime_one->set_state((s32)((void*)(1)));
    }
}
#pragma pop

#pragma push

void TObjEneSlimeOne::reset_display() {
    set_display_mode(0);
    this->actorFlags = (this->actorFlags & 0xfffbffff);
    this->m_398 = lbl_805DA6B4;
    vertical_offset = lbl_805DA708;
}
#pragma pop

#pragma push
#pragma fp_contract on
void TObjEneSlimeOne::fn_800EA820() {
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f1_4;
    f32 var_f31;
    var_f31 = lbl_805DA67C;
    vertical_offset = (f32) (lbl_805DA708 * (lbl_805DA67C - this->m_398));
    render_scale.x = (f32) ((this->m_398 * (lbl_8043D23C.x - lbl_8043D230.x)) + lbl_8043D230.x);
    render_scale.y = (f32) ((this->m_398 * (lbl_8043D23C.y - lbl_8043D230.y)) + lbl_8043D230.y);
    this->render_scale.z = (f32) ((this->m_398 * (lbl_8043D23C.z - lbl_8043D230.z)) + lbl_8043D230.z);
    temp_f1 = this->m_398;
    if (temp_f1 > lbl_805DA740) {
        var_f31 = (lbl_805DA67C - temp_f1) / lbl_805DA73C;
    }
    temp_f1_2 = var_f31 * (lbl_805DA670 * sin_table_lookup(this->m_390 << 0xC));
    render_scale.x = (f32) (render_scale.x * (lbl_805DA67C + temp_f1_2));
    this->render_scale.z = (f32) (this->render_scale.z * (lbl_805DA67C - temp_f1_2));
    this->m_390 = (s32) (this->m_390 + 1);
    temp_f1_3 = this->m_398;
    if (temp_f1_3 >= lbl_805DA678) {
        this->m_3a0 = (f32) lbl_805DA67C;
    } else {
        this->m_3a0 = (f32) (lbl_805DA748 * temp_f1_3);
    }
    temp_f1_4 = this->m_398 + lbl_805DA750;
    this->m_398 = temp_f1_4;
    if (temp_f1_4 > lbl_805DA67C) {
        if (find_nearest_visible_player(this, 0, lbl_805DA6DC) != 0xFFFF) {
            this->set_state(3);
        } else {
            this->set_state(2);
        }
    }
}
#pragma pop

#pragma push

void TObjEneSlimeOne::init_slime_display() {
    m_398 = lbl_805DA67C;
    vertical_offset = lbl_805DA6B4;
    set_display_mode(0);
    this->animation->set_state(7);
}
#pragma pop

#pragma push
#pragma fp_contract on
void TObjEneSlimeOne::fn_800EA678() {
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f1_4;
    f32 var_f31;
    var_f31 = lbl_805DA67C;
    vertical_offset = (f32) (lbl_805DA708 * (lbl_805DA67C - this->m_398));
    render_scale.x = (f32) ((this->m_398 * (lbl_8043D23C.x - lbl_8043D230.x)) + lbl_8043D230.x);
    render_scale.y = (f32) ((this->m_398 * (lbl_8043D23C.y - lbl_8043D230.y)) + lbl_8043D230.y);
    this->render_scale.z = (f32) ((this->m_398 * (lbl_8043D23C.z - lbl_8043D230.z)) + lbl_8043D230.z);
    temp_f1 = this->m_398;
    if (temp_f1 > lbl_805DA740) {
        var_f31 = (lbl_805DA67C - temp_f1) / lbl_805DA73C;
    }
    temp_f1_2 = var_f31 * (lbl_805DA744 * sin_table_lookup(this->m_390 << 0xA));
    render_scale.x = (f32) (render_scale.x * (lbl_805DA67C + temp_f1_2));
    this->render_scale.z = (f32) (this->render_scale.z * (lbl_805DA67C - temp_f1_2));
    this->m_390 = (s32) (this->m_390 + 1);
    temp_f1_3 = this->m_398;
    if (temp_f1_3 >= lbl_805DA678) {
        this->m_3a0 = (f32) lbl_805DA67C;
    } else {
        this->m_3a0 = (f32) (lbl_805DA748 * temp_f1_3);
    }
    temp_f1_4 = this->m_398 + lbl_805DA74C;
    this->m_398 = temp_f1_4;
    if (temp_f1_4 < lbl_805DA6B4) {
        this->set_state(0);
    }
}
#pragma pop

#pragma push
#pragma fp_contract on
void TObjEneSlimeOne::fn_800EA56C() {
    s32 temp_r31;
    movement_speed = (f32) lbl_805DA6B4;
    if (find_nearest_visible_player(this, &movement_direction, lbl_805DA6DC) == 0xFFFF) {
        this->set_state(2);
        return;
    }
    temp_r31 = (s32) (lbl_805DA738 * random_ratio__9TObjCharaFv(this));
    movement_direction.x = (f32) ((lbl_805DA6E0 * sin_table_lookup(temp_r31)) + movement_direction.x);
    movement_direction.z = (f32) ((lbl_805DA6E0 * cos_table_lookup(temp_r31)) + movement_direction.z);
    if (vector_length(&movement_direction) <= lbl_805DA718) {
        this->set_state(2);
        return;
    }
    normalize_vector(&movement_direction);
    m_398 = ((lbl_805DA6E4 * random_ratio__9TObjCharaFv(this)) + lbl_805DA720);
    m_3a0 = (f32) lbl_805DA67C;
    this->animation->set_state((s32)((void *) 8));
    set_display_mode(1);
}
#pragma pop

#pragma push
#pragma fp_contract on
#pragma opt_common_subs off
void TObjEneSlimeOne::fn_800EA364() {
    Vec sp8;
    f32 s;
    f32 c;
    f32 t;
    f32 d;
    s32 i;
    s32 ang;
    this->rotation_y += 0x100;
    if (this->m_398 > lbl_805DA6B4) {
        motion_phase += 0xC00;
        d = lbl_805DA734 * (lbl_805DA678 * (lbl_805DA678 + sin_table_lookup(motion_phase)));
        t = movement_speed + d;
        movement_speed = t;
        if (t > lbl_805DA710) {
            movement_speed = lbl_805DA710;
        }
    } else {
        t = movement_speed - lbl_805DA734;
        movement_speed = t;
        if (t < lbl_805DA6B4) {
            movement_speed = lbl_805DA6B4;
        }
    }
    this->m_398 -= movement_speed;
    VecCopy(&prev_position, &position);
    for (i = 1; i < 15; i++) {
        position.x += movement_speed * this->movement_direction.x;
        position.y += movement_speed * movement_direction.y;
        position.z += movement_speed * this->movement_direction.z;
        if (project_to_ground() != 0 && csnLookAt(&prev_position, &position) == 0) {
            break;
        }
        ang = i << 12;
        if (i & 1) {
            ang *= -1;
        }
        s = sin_table_lookup(ang);
        c = cos_table_lookup(ang);
        this->movement_direction.x = c * this->movement_direction.x - s * this->movement_direction.z;
        this->movement_direction.z = s * this->movement_direction.x + c * this->movement_direction.z;
        VecCopy(&position, &prev_position);
    }
    if (this->m_398 <= lbl_805DA6B4 && lbl_805DA6B4 == movement_speed) {
        if (find_nearest_visible_player(this, &sp8, lbl_805DA720) != 0xFFFF && vector_length(&sp8) > lbl_805DA6E0) {
            this->set_state(4);
        } else {
            this->set_state(3);
        }
    }
}
#pragma pop

#pragma push

void TObjEneSlimeOne::enter_slime_state() {
    state_timer = 8;
    this->animation->set_state(9);
    play_sound_effect(0x4003AD1D, &position, 0, 0);
    set_display_mode(1);
}
#pragma pop

#pragma push

void TObjEneSlimeOne::update_slime_timer() {
    s32 temp_r0;

    temp_r0 = state_timer - 1;
    state_timer = temp_r0;
    if (temp_r0 == 0) {
        spawn_particle_effect(body_center(), 0xCD);
    }
    if (this->animation->is_finished() == 1) {
        if (this->is_timer_active() != 0) {
            this->set_state(7);
            return;
        }
        this->set_state(6);
    }
}
#pragma pop

#pragma push

void TObjEneSlimeOne::enter_appear_state() {
    state_timer = 20;
    play_sound_effect(0x4003AD1D, &position, 0, 0);
    animation->set_state(10);
    set_display_mode(1);
}
#pragma pop

#pragma push

void TObjEneSlimeOne::update_dive_timer() {
    s32 temp_r0;

    temp_r0 = state_timer - 1;
    state_timer = temp_r0;
    if (temp_r0 == 0) {
        spawn_particle_effect(body_center(), 0xCD);
    }
    if (this->animation->is_finished() == 1) {
        this->set_state(3);
    }
}
#pragma pop

#pragma push

void TObjEneSlimeOne::fn_800EA120() {
    TObjEneSlimeOne *actor = this;
  unsigned int new_var;
  actor->m_3cc = 0xFFFF;
  actor->motion_phase = (s32) ((((s32) (lbl_805DA730 * random_ratio__9TObjCharaFv((void *)((s32) actor)))) + 4) << 0x10);
  actor->m_390 = 0x7FFFFFFF;
  actor->turn_step = 0x400;
  new_var = 1;
  if (random_ratio__9TObjCharaFv((void *)((s32) actor)) > (*(const f32 *)&lbl_805DA678))
  {
    actor->turn_step = (s32) ((actor->turn_step) * (-new_var));
  }
  actor->animation->set_state((s32)((void*)((int) new_var)));
  actor->set_display_mode(2);
}
#pragma pop

#pragma push
#pragma fp_contract on
void TObjEneSlimeOne::fn_800E9EFC() {
    TObjEneSlimeOne *ene_slime_one = this;
    Vec sp14;
    Vec sp8;
    f32 f;
    u16 r;
    s32 n;

    f = sin_table_lookup(ene_slime_one->motion_phase);
    if (f < lbl_805DA6B4) {
        f = lbl_805DA6B4;
    }
    ene_slime_one->rotation_y = f * (f32)ene_slime_one->turn_step + (f32)ene_slime_one->rotation_y;
    if (ene_slime_one->m_3cc == 0xFFFF) {
        r = find_nearest_visible_player(ene_slime_one, &sp14, lbl_805DA72C);
        if (r != 0xFFFF &&
            angle_difference_abs(ene_slime_one->rotation_y, (s32)(lbl_8043D280[0] * ((f32 (*)(f32, f32))atan2_float)(sp14.x, sp14.z))) < 0x1C71) {
            ene_slime_one->motion_phase = 0;
            ene_slime_one->m_3cc = r;
        }
    }
    ene_slime_one->motion_phase -= 0x600;
    if (ene_slime_one->motion_phase <= 0) {
        n = (f32)*(u32 *)((s8 *)(get_bml_motion((s32)ene_slime_one->m_380, 10)) + 4) / lbl_805DA678;
        ene_slime_one->motion_phase = 0;
        if (ene_slime_one->m_3cc != 0xFFFF) {
            sp8.x = lbl_805DA67C;
            sp8.z = sp8.y = lbl_805DA6B4;
            TObjPlayer::calc_distance_to_client((s32)ene_slime_one, (u16)(ene_slime_one->m_3cc), (u32)&sp8);
            ene_slime_one->rotation_y = approach_angle_limited(ene_slime_one->rotation_y, (s32)(lbl_8043D280[0] * ((f32 (*)(f32, f32))atan2_float)(sp8.x, sp8.z)), 0x280);
        }
        if (ene_slime_one->m_390 > n) {
            ene_slime_one->animation->set_state((s32)((void *)0));
            ene_slime_one->m_390 = n;
        } else if (--ene_slime_one->m_390 <= 0) {
            if (ene_slime_one->m_3cc == 0xFFFF) {
                ene_slime_one->set_state(5);
            } else {
                ene_slime_one->set_state(8);
            }
        }
    }
}
#pragma pop

#pragma push

void TObjEneSlimeOne::init_slime_state() {
    TObjEneSlimeOne *actor = this;
    actor->set_random_timer(0x1E, 0x1E);
    actor->turn_step = 0x888;
    if (random_ratio__9TObjCharaFv(actor) > lbl_805DA678) {
        actor->turn_step = actor->turn_step * 0xFFFFFFFF;
    }
    actor->animation->set_state((s32)((void*)(1)));
    actor->set_display_mode(2);
}
#pragma pop

#pragma push

void TObjEneSlimeOne::fn_800E9DC8() {
    f32 sp[3];
    s32 r = 0;
    s32 t;
    rotation_y = rotation_y + turn_step;
    if (this->find_nearest_enemy_with_flag((s32)sp, (f32)lbl_805DA728) != 0xFFFF) {
        t = (s32) (lbl_8043D280[0] * atan2_float(sp[0], sp[2]));
        if (angle_difference_abs(rotation_y, t) < 0x444) {
            rotation_y = t;
            r = 1;
        }
    }
    m_390 = m_390 - 1;
    if (r != 0 || m_390 < 0) {
        this->set_state(9);
    }
}
#pragma pop

#pragma push

void TObjEneSlimeOne::fn_800E9D7C() {
    set_random_timer(30, 30);
    this->animation->set_state(0);
    set_display_mode(2);
}
#pragma pop

#pragma push

void TObjEneSlimeOne::fn_800E9BCC() {
    f32 v[3];
    s32 t;
    v[0] = lbl_805DA67C;
    v[2] = v[1] = lbl_805DA6B4;
    if (m_3cc != 0xFFFF) {
        TObjPlayer::calc_distance_to_client((s32)this, (u16)m_3cc, (u32)v);
    }
    t = (s32) (lbl_8043D280[0] * atan2_float(v[0], v[2]));
    rotation_y = approach_angle_limited(rotation_y, t, 0x200);
    if (angle_difference_abs(rotation_y, t) < 0x200) {
        m_390 = 0;
    }
    VecCopy(&prev_position, &position);
    if (vector_length(v) <= lbl_805DA718) {
        v[0] = lbl_805DA67C;
        v[2] = v[1] = lbl_805DA6B4;
    } else {
        normalize_vector(v);
    }
    v[0] *= lbl_805DA71C;
    v[1] *= lbl_805DA71C;
    v[2] *= lbl_805DA71C;
    vec3_add_to(&position, v);
    if (project_actor_to_ground(this, &position, 0) == 0 || csnLookAt(&prev_position, &position) != 0) {
        VecCopy(&position, &prev_position);
    }
    if (--m_390 <= 0) {
        if (vector_length(v) > lbl_805DA720 || random_ratio__9TObjCharaFv(this) < lbl_805DA724) {
            this->set_state(9);
        } else {
            this->set_state(10);
        }
    }
}
#pragma pop

#pragma push

void TObjEneSlimeOne::begin_appear() {
    m_390 = 90;
    state_timer = 19;
    animation->set_state(3);
    set_display_mode(2);
}
#pragma pop

#pragma push

void TObjEneSlimeOne::update_water_bomb_timer() {
    s32 temp_r0;
    s32 temp_r0_2;

    state_timer = (s32) (state_timer - 1);
    temp_r0 = state_timer;
    if (temp_r0 > 0) {
        spawn_particle_effect(body_center(), 0xFF);
    } else if (temp_r0 == 0) {
        play_sound_effect(0x4003A017, &position, 0, 0);
        spawn_particle_effect(body_center(), 0xE2);
        TObjEneSlimeWaterBomb::create((TObjEneSlimeOne *)this, (TObjEneSlimeOne *)this);
    }
    temp_r0_2 = m_390 - 1;
    m_390 = temp_r0_2;
    if (temp_r0_2 <= 0) {
        if (this->is_timer_active() != 0) {
            this->set_state(7);
            return;
        }
        this->set_state(5);
    }
}
#pragma pop

#pragma push
#pragma fp_contract on
void TObjEneSlimeOne::start_tail_attack() {
    TObjEneSlimeOne *self = this;
    f32 r;
    s32 ang;
    s32 n;
    f32 len;
    TObjChara *t;
    t = ((TObjChara * (*)(s32))get_player_by_client_id)(self->m_3cc);
    if (t == NULL || (t->actorFlags & 0x02000800)) {
        self->set_state(5);
        return;
    }
    VecCopy((Vec *)&self->attack_position, (const Vec *)&t->position);
    r = lbl_805DA6AC * random_ratio__9TObjCharaFv(self) + lbl_805DA710;
    ang = lbl_805DA714 * random_ratio__9TObjCharaFv(self);
    self->attack_position.x = r * sin_table_lookup(ang) + self->attack_position.x;
    self->attack_position.z = r * cos_table_lookup(ang) + self->attack_position.z;
    Vec dir = self->attack_position;
    subtract_vector(&dir, &self->position);
    len = vector_length(&dir);
    if (lbl_805DA6B4 == len) {
        self->set_state(5);
        return;
    }
    n = len / lbl_805DA66C;
    if (vector_length(&dir) <= lbl_805DA718) {
        dir.x = (*(const f32 *)&lbl_805DA67C);
        dir.z = dir.y = lbl_805DA6B4;
    } else {
        normalize_vector(&dir);
    }
    dir.x *= lbl_805DA66C;
    dir.y *= lbl_805DA66C;
    dir.z *= lbl_805DA66C;
    Vec pos = self->position;
    pos.y += lbl_805DA6AC;
    while (n > 0) {
        Vec tmp = pos;
        if (project_actor_to_ground(self, &tmp, 0) == 0 || csnLookAt(&self->position, &pos) != 0) {
            self->set_state(9);
            return;
        }
        n--;
        ((void (*)(void *, void *))vec3_add_to)(&pos, &dir);
    }
    self->m_390 = 0x5A;
    self->animation->set_state((s32)((void*)((void *)0)));
    play_sound_effect(0x4003A318, &self->attack_position, 0, 0);
    TObjEneSlimeTailAttack::create((s32)self, (const Vec *)&self->attack_position, self->rotation_y, (TObjEneSlimeOne *)self);
    self->set_display_mode(2);
}
#pragma pop

#pragma push

void TObjEneSlimeOne::tick_timer() {
    TObjEneSlimeOne *ene_slime_one = (TObjEneSlimeOne *)this;
    s32 temp_r0;

    temp_r0 = ene_slime_one->m_390 - 1;
    ene_slime_one->m_390 = temp_r0;
    if (temp_r0 <= 0) {
        ene_slime_one->set_state(5);
    }
}
#pragma pop

#pragma push

void TObjEneSlimeOne::reset_display_state() {
    render_scale.z = lbl_805DA67C;
    render_scale.y = lbl_805DA67C;
    render_scale.x = lbl_805DA67C;
    state_timer = 0;
    this->animation->set_state(4);
    set_display_mode(2);
}
#pragma pop

#pragma push

void TObjEneSlimeOne::update_tick() {
    TObjEneSlimeOne *ene_slime_one = (TObjEneSlimeOne *)this;
    s32 temp_r3;

    temp_r3 = ene_slime_one->state_timer + 1;
    ene_slime_one->state_timer = temp_r3;
    if (!(temp_r3 & 3)) {
        spawn_particle_effect(ene_slime_one->body_center(), 0xE0);
    }
    if (ene_slime_one->motion_flags & 0x10) {
        if (ene_slime_one->is_timer_active() != 0) {
            ene_slime_one->set_state(7);
            return;
        }
        ene_slime_one->set_state(6);
    }
}
#pragma pop

#pragma push

void TObjEneSlimeOne::init_split_effect() {
    render_scale.z = lbl_805DA67C;
    render_scale.y = lbl_805DA67C;
    render_scale.x = lbl_805DA67C;
    spawn_particle_effect(body_center(), 0xCE);
    play_sound_effect(0x4003A61A, &position, 0, 0);
    animation->set_state(5);
    set_display_mode(0);
}
#pragma pop

#pragma push

void TObjEneSlimeOne::fn_800E969C() {
    TObjEneSlimeOne *ene_slime_one = (TObjEneSlimeOne *)this;
    if (ene_slime_one->motion_flags & 0x10) {
        ene_slime_one->set_state(5);
    }
}
#pragma pop

#pragma push

void TObjEneSlimeOne::fn_800E95F4() {
    TObjEneSlimeOne *arg0 = this;
    u8 *object;
    object = (u8 *)((u8 *)arg0->slime_group);
    if ((object != NULL) && (((TObject *)object)->all_parents_unqueued_for_destruction() != 0)) {
        arg0->slime_group->release_child_slot((s32) arg0->entity_id);
    }
    arg0->render_scale.z = (f32) lbl_805DA67C;
    arg0->render_scale.y = (f32) lbl_805DA67C;
    arg0->render_scale.x = (f32) lbl_805DA67C;
    arg0->m_390 = 5;
    arg0->distribute_experience_and_request_drop();
    ((s32 (*)(s32, u32, s16, s32))play_sound_effect)(0x4003A81B, (u32)(&arg0->position), 0, 0);
    spawn_particle_effect((arg0->body_center()), 0xFE);
    arg0->animation->set_state(5);
    arg0->set_display_mode(0);
}
#pragma pop

#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
void TObjEneSlimeOne::update_effect_fade_lifetime() {
    f32 temp_f1;
    s32 temp_r0;
    temp_f1 = m_3a0 + lbl_805DA70C;
    m_3a0 = temp_f1;
    if (temp_f1 < lbl_805DA6B4) {
        m_3a0 = (f32) lbl_805DA6B4;
    }
    temp_r0 = m_390 - 1;
    m_390 = temp_r0;
    if (temp_r0 <= 0) {
        queue_destruction__7TObjectFv(this);
    }
}
#pragma pop

#pragma push

void TObjEneSlimeOne::fn_800E9538() {
    m_3e8 = (void *)create_particle_emitter((&position), 0xE1);
    vertical_offset = (f32) lbl_805DA708;
    this->render_scale.z = (f32) lbl_805DA6B4;
    render_scale.y = (f32) lbl_805DA6B4;
    render_scale.x = (f32) lbl_805DA6B4;
    this->m_3a0 = (f32) lbl_805DA6B4;
    this->animation->set_state(7);
    set_display_mode(0);
}
#pragma pop

#pragma push
#pragma fp_contract on
void TObjEneSlimeOne::fn_800E92D8() {
    s32 landed = 0;
    s32 tries = 4;
    s32 angle;
    f32 s;
    f32 c;

    this->m_3dc.y += lbl_805DA700;
    do {
        Vec next;
        Vec probe;
        VecCopy(&next, &this->position);
        vec3_add_to(&next, &this->m_3dc);
        VecCopy(&probe, &next);
        probe.y += lbl_805DA6AC + fabs_float(this->m_3dc.y);
        if (project_actor_to_ground(this, &probe, 0) != 0) {
            VecCopy(&this->position, &next);
            if (!(this->position.y > probe.y)) {
                this->position.y = probe.y;
                landed = 1;
            }
            break;
        }
        s = sin_table_lookup(0x4000);
        c = cos_table_lookup(0x4000);
        this->m_3dc.x = c * this->m_3dc.x + s * this->m_3dc.z;
        this->m_3dc.z = -s * this->m_3dc.x + c * this->m_3dc.z;
    } while (--tries > 0);
    if (tries == 0) {
        Vec probe;
        this->m_3dc.x = this->m_3dc.z = lbl_805DA6B4;
        VecCopy(&probe, &this->position);
        probe.y += lbl_805DA6AC + fabs_float(this->m_3dc.y);
        if (project_actor_to_ground(this, &probe, 0) != 0) {
            if (!(this->position.y > probe.y)) {
                this->position.y = probe.y;
                landed = 1;
            }
        } else {
            landed = 1;
        }
    }
    if (this->m_3e8 != NULL) {
        ((TParticleCtrl *)this->m_3e8)->set_position(&this->position);
    }
    if (landed != 0) {
        if (this->m_3e8 != NULL) {
            TParticleCtrl::release(this->m_3e8);
            this->m_3e8 = NULL;
        }
        for (angle = 0; angle < 0xFFFF; angle += 0x1000) {
            Vec p = *&this->position;
            p.x = lbl_805DA704 * sin_table_lookup(angle) + p.x;
            p.y += lbl_805DA708;
            p.z = lbl_805DA704 * cos_table_lookup(angle) + p.z;
            spawn_particle_effect(&p, 0xE2);
        }
        project_to_ground();
        this->set_state(1);
    }
}
#pragma pop

#pragma push

void TObjEneSlimeOne::copy_position() {
    VecCopy(&trail_position, &position);
}
#pragma pop

#pragma push

void TObjEneSlimeOne::update_trail_position() {
    Vec delta;
    VecCopy(&delta, &position);
    subtract_vector(&delta, &trail_position);
    delta.x *= lbl_805DA6FC;
    delta.y *= lbl_805DA6FC;
    delta.z *= lbl_805DA6FC;
    vec3_add_to(&trail_position, &delta);
}

#pragma pop

#pragma push

void TObjEneSlimeOne::sub_800E9090() {
    TObjEneSlimeOne *self = this;
    Vec c;
    Vec b;
    f32 s;
    s32 ang;
    s32 t;
    s32 w1;
    s32 w0;
    s = lbl_805DA678 * self->m_3a0;
    Vec a = self->position;
    subtract_vector(&a, &self->trail_position);
    a.x *= lbl_805DA678;
    a.y *= lbl_805DA678;
    a.z *= lbl_805DA678;
    VecCopy((Vec *)&c, (const Vec *)&self->trail_position);
    vec3_add_to(&c, &a);
    c.y += lbl_805DA6E8;
    ang = (*(const f64 *)&lbl_8043D280) * ((f32 (*)(f32, f32))atan2_float)(a.x, a.z);
    b.x = lbl_805DA6EC;
    b.y = lbl_805DA6F0;
    b.z = lbl_805DA6EC * vector_length(&a) / lbl_805DA6F4;
    if (b.x > b.z) {
        b.x = b.z;
    }
    if (s < lbl_805DA684 || b.x < lbl_805DA684) {
        return;
    }
    TObjPlayer::push_material_color_override(s, lbl_805DA6F8, lbl_805DA6B4, lbl_805DA67C);
    ((void (*)(void))push_matrix)();
    ((void (*)(void *))post_translate_matrix)(&c);
    rotate_matrix_y(0, ang);
    scale_matrix_vec3((u8 *)(0), (u8 *)&b);
    t = slime_tail_attack_id_pair[self->variant];
    TObjFish::set_global_param(TObjFish__sub_8001EDB0((s32)self->m_380, t));
    draw_chunk_object((void *)(get_bml_model((BmlResource *)self->m_380, t)));
    ((int (*)(void))pop_matrix)();
    TObjPlayer::init_render_globals();
}
#pragma pop

#pragma push
#pragma fp_contract on
#pragma opt_common_subs off
TObjEneSlimeWaterBomb::TObjEneSlimeWaterBomb(TObjEneSlimeOne *parent, TObjEneSlimeOne *owner)
    : TObjEnemy(parent) {
    f32 s;
    f32 c;
    m_name = lbl_805D2AE0;
    this->owner = owner;
    rotation_y = ((TObjEneSlimeOne *)m_up)->rotation_y;
    VecCopy(&position, &((TObjEneSlimeOne *)m_up)->position);
    s = sin_table_lookup(rotation_y);
    c = cos_table_lookup(rotation_y);
    position.x += lbl_805DA6E0 * s;
    position.y += lbl_805DA6E4;
    position.z += lbl_805DA6E0 * c;
    movement.x = lbl_805DA6D8 * s;
    movement.y = lbl_805DA6B4;
    movement.z = lbl_805DA6D8 * c;
    lifetime = lbl_805DA6B4;
    particle = (TParticleCtrl *)create_particle_emitter(&position, 0xCF);
    attack_power = *(f32 *)get_battle_movement_params(TObjEneSlime__attack_target_param_table[this->owner->get_attack_target()]);
    if (attack_power < lbl_805DA6B4) {
        attack_power = lbl_805DA6B4;
    }
    elapsed_frames = 0;
}
#pragma pop

#pragma push

TObjEneSlimeWaterBomb::~TObjEneSlimeWaterBomb() {
    if (particle != NULL) {
        TParticleCtrl::release(particle);
        particle = NULL;
    }
}
#pragma pop

#pragma push

TObjEneSlimeWaterBomb *TObjEneSlimeWaterBomb::create(TObjEneSlimeOne *parent, TObjEneSlimeOne *owner) {
    return new TObjEneSlimeWaterBomb(parent, owner);
}
#pragma pop

#pragma push

void TObjEneSlimeWaterBomb::run_task() {
    s32 die = 0;
    movement.y += lbl_805DA6D0;
    vec3_add_to(&position, &movement);
    if (++elapsed_frames > 0x14F) {
        die = 1;
    }
    {
        Vec probe = position;
        probe.y += lbl_805DA6AC;
        if (((s32 (*)(void *, void *, void *))project_actor_to_ground)(this, &probe, &ground_normal) != 0) {
            ground_height = probe.y;
            if (position.y <= ground_height) {
                position.y = ground_height;
                movement.y *= lbl_805DA6D4;
                spawn_particle_effect(&position, 0xE2);
            }
        } else {
            die = 1;
        }
    }
    if (particle != NULL) {
        particle->set_position(&position);
    }
    if (owner->is_in_water_bomb_states() != 0 || check_hits() != 0) {
        die = 1;
    }
    {
        f32 next_lifetime = lifetime + lbl_805DA6D8;
        lifetime = next_lifetime;
        if (next_lifetime >= lbl_805DA6DC || die != 0) {
            spawn_particle_effect(&position, 0xE2);
            queue_destruction__7TObjectFv(this);
        }
    }
}
#pragma pop

#pragma push
#pragma fp_contract on
#pragma opt_common_subs off
void TObjEneSlimeWaterBomb::render() {
    Vec shadow_scale;
    s32 angle_x;
    s32 angle_z;
    f32 height;
    f32 width;
    push_matrix();
    translate_matrix(0, position.x, lbl_805DA670 + ground_height, position.z);
    direction_to_rotation_xz((u8 *)&ground_normal, &angle_x, &angle_z);
    rotate_matrix_z(0, angle_z);
    rotate_matrix_x(0, angle_x + 0x4000);
    height = position.y - ground_height;
    if (height > lbl_805DA6C8) {
        height = lbl_805DA6C8;
    } else if (height < lbl_805DA6B4) {
        height = lbl_805DA6B4;
    }
    width = lbl_805DA6CC * (lbl_805DA67C - height / lbl_805DA6C8) + lbl_805DA670;
    shadow_scale.x = shadow_scale.y = width;
    shadow_scale.z = lbl_805DA67C;
    scale_current_matrix(&shadow_scale);
    draw_blob_shadow(0);
    pop_matrix();
}
#pragma pop

#pragma push

s32 TObjEneSlimeWaterBomb::check_hits() {
    s32 hit;
    TObjChara *player;
    TObjChara *enemy;
    DirectAttackPayload attack = lbl_8043D260[0];
    u16 player_id;
    s32 enemy_id;
    hit = 0;
    attack.power = attack_power;
    VecCopy((Vec *)&body_center_position, &position);
    player_id = find_nearest_visible_player(this, 0, lbl_805DA6A8);
    if (player_id != 0xFFFF) {
        player = get_player_by_client_id(player_id);
        if (player != NULL && !(horizontal_distance_squared(&body_center_position, &player->body_center_position) > lbl_805DA6A8)) {
            f32 damage = player->receive_direct_attack(owner, attack, 0, -1, -1);
            if (lbl_805DA6B4 != damage) {
                player->apply_knockback_from_attacker((u8 *)this, damage);
            }
            hit = 1;
        }
    }
    enemy_id = find_nearest_enemy_masked(lbl_805DA6A8);
    if (enemy_id != 0xFFFF) {
        enemy = (TObjChara *)get_enemy_entity(enemy_id);
        if (enemy != NULL && !(horizontal_distance_squared(&body_center_position, &enemy->body_center_position) > lbl_805DA6A8)) {
            f32 damage = enemy->receive_direct_attack(owner, attack, 0, -1, -1);
            if (lbl_805DA6B4 != damage) {
                enemy->apply_knockback_from_attacker((u8 *)this, damage);
            }
            hit = 1;
        }
    }
    return hit;
}
#pragma pop

#pragma push

TObjEneSlimeTailAttack::TObjEneSlimeTailAttack(TObject *parent, const Vec *position, s32 angle, TObjEneSlimeOne *owner)
    : TObjEnemy(parent) {
    m_name = TObjEneSlimeTailAttack__name;
    this->owner = owner;
    BmlResource *resource = (BmlResource *)get_instance__15TObjEneSlimeOneFv();
    u32 id = ((s32 *)lbl_804966F4)[this->owner->get_attack_target()];
    texlist = TObjFish__sub_8001EDB0((s32)resource, id);
    model = (void *)get_bml_model(resource, id);
    action_table = lbl_8049639C;
    set_field_d8((s32)lbl_8049639C);
    motion_list = resource->motions;
    set_field_dc((s32)resource->motions);
    requested_action = 6;
    set_animation(requested_action);
    set_field_b8(requested_action);
    rotation_y = angle;
    VecCopy(&this->position, position);
    active = 1;
    last_hit_player = 0xFFFF;
    stretch_scale.x = stretch_scale.y = stretch_scale.z = lbl_805DA67C;
    fade = lbl_805DA67C;
}
#pragma pop

#pragma push

TObjEneSlimeTailAttack::~TObjEneSlimeTailAttack() {}
#pragma pop

#pragma push

TObjEneSlimeTailAttack *TObjEneSlimeTailAttack::create(s32, const Vec *position, s32 angle, TObjEneSlimeOne *owner) {
    return new TObjEneSlimeTailAttack(new TObjControl((TObject *)tl_04), position, angle, owner);
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
#pragma fp_contract on
void TObjEneSlimeTailAttack::run_task() {
    if (active != 0) {
        check_hits();
        advance_animation__10TObjMotionFv(this);
        if (this->motion_flags & 0x10) {
            queue_destruction__7TObjectFv(this);
            return;
        }
        if (owner->is_in_water_bomb_states() != 0) {
            active = 0;
        }
    } else {
        this->frame += lbl_805DA670 * (lbl_805DA68C - this->frame);
        fade = (f32) (fade + lbl_805DA6B8);
        position.y = (f32) (position.y + lbl_805DA6BC);
        stretch_scale.x = (f32) (stretch_scale.x + lbl_805DA6C0);
        stretch_scale.y = (f32) (stretch_scale.y + lbl_805DA6C4);
        stretch_scale.z = (f32) (stretch_scale.z + lbl_805DA6C0);
        if (stretch_scale.y <= lbl_805DA684) {
            queue_destruction__7TObjectFv(this);
        }
    }
}
#pragma pop

#pragma push

s32 TObjEneSlimeTailAttack::check_hits() {
    TObjEneSlimeTailAttack *self = this;
    DirectAttackPayload hit;
    s32 result;
    TObjChara *e;
    TObjChara *e2;
    u16 id;
    s32 id2;
    f32 t = self->frame;
    if (t < lbl_805DA6A0 || t > lbl_805DA6A4) {
        return 0;
    }
    hit.kind = 0;
    result = 0;
    hit.power = *(s16 *)get_battle_base_stats((s32)lbl_804966FC[self->owner->get_attack_target()]);
    id = find_nearest_visible_player(self, 0, lbl_805DA6A8);
    if (id != 0xFFFF && id != self->last_hit_player) {
        e = get_player_by_client_id(id);
        if (e != NULL) {
            TObjPlayer *pl = (TObjPlayer *)e;
            f32 lo = pl->position.y - lbl_805DA6AC;
            f32 hi = lbl_805DA6AC + (pl->position.y + pl->m_d48);
            if (!(self->body_center_position.y < lo) && !(self->body_center_position.y > hi) &&
                !(horizontal_distance_squared(&self->body_center_position, &pl->position) > lbl_805DA6B0)) {
                f32 damage = e->receive_direct_attack(self->owner, hit, 0, -1, -1);
                if (lbl_805DA6B4 != damage) {
                    e->apply_knockback_from_attacker((u8 *)self, damage);
                }
                self->last_hit_player = id;
                result = 1;
            }
        }
    }
    id2 = self->find_nearest_enemy_with_flag(lbl_805DA6A8);
    if (id2 != 0xFFFF) {
        TObjEneSlimeOne *owner = self->owner;
        if (owner == NULL || id2 != (u16)get_entity_id(owner)) {
            e2 = (TObjChara *)get_enemy_entity(id2);
            if (e2 != NULL && !(horizontal_distance_squared(&self->body_center_position, &e2->body_center_position) > lbl_805DA6B0)) {
                f32 damage = e2->receive_direct_attack(self->owner, hit, 0, -1, -1);
                if (lbl_805DA6B4 != damage) {
                    e2->apply_knockback_from_attacker((u8 *)self, damage);
                }
                result = 1;
            }
        }
    }
    return result;
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEneSlimeTailAttack::render() {
  f32 temp_f1;
  f32 temp_f3;
  sub_800E841C();
  if (active != 0)
  {
    temp_f3 = this->frame;
    temp_f1 = lbl_805DA68C;
    if (temp_f3 < temp_f1)
    {
      draw_stretched_segment(&owner->position, &position, (f32) (temp_f3 / temp_f1));
    }
    else
      if ((temp_f3 >= lbl_805DA690) && (temp_f3 < lbl_805DA694))
    {
      draw_stretched_segment(&position, &owner->position, (f32) ((temp_f3 - lbl_805DA690) / temp_f1));
    }
  }
  temp_f1 = this->frame;
  if ((temp_f1 >= lbl_805DA698) && (temp_f1 < lbl_805DA69C))
  {
    draw_blob_shadows();
  }
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEneSlimeTailAttack::sub_800E841C() {
    u8 *arg0 = (u8 *)this;
    push_matrix();
    post_translate_matrix((u8 *)&this->position);
    rotate_matrix_y(0, (int) (rotation_y));
    TObjFish::set_global_param((int) (texlist));
    if (active != 0) {
        reset_slime_tail_node_index();
        set_chunk_model_node_callback((s32)capture_slime_tail_node);
        ((TObjMotion *)arg0)->draw();
        set_chunk_model_node_callback(NULL);
        get_slime_tail_pose(&pose);
        VecCopy((Vec *)&body_center_position, &pose.attachment);
    } else {
        TObjPlayer__sub_800EBE48((f32) fade);
        scale_matrix_vec3(0, (u8 *)&stretch_scale);
        reset_slime_tail_node_index();
        set_chunk_model_node_callback((s32)capture_slime_tail_node);
        ((TObjMotion *)arg0)->draw();
        set_chunk_model_node_callback(NULL);
        get_slime_tail_pose(&pose);
        VecCopy((Vec *)&body_center_position, &pose.attachment);
        TObjPlayer::init_render_globals();
    }
    pop_matrix();
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
#pragma fp_contract on
void TObjEneSlimeTailAttack::draw_stretched_segment(void *arg1, void *arg2, f32 t) {
    f32 len;
    f32 k;
    f32 saved;
    Vec d;
    VecCopy((Vec *)&d, (const Vec *)((Vec *)arg2));
    ((s32 (*)(void *, void *))subtract_vector)(&d, ((Vec *)arg1));
    len = vector_length(&d);
    push_matrix();
    k = lbl_805DA678 * (lbl_805DA67C + t);
    {
        Vec p = *((Vec *)arg1);
        p.x += k * d.x;
        p.y += k * d.y + lbl_805DA680;
        p.z += k * d.z;
        post_translate_matrix(&p);
    }
    rotate_matrix_y(0, (s32)(lbl_8043D280[0] * atan2_float(d.x, d.z)));
    {
        f32 r = lbl_805DA67C - t;
        scale_matrix(0, lbl_805DA67C, lbl_805DA678, r * len / lbl_805DA66C);
    }
    TObjFish::set_global_param(this->texlist);
    TObjPlayer__sub_800EBE48(lbl_805DA688 * t + lbl_805DA684);
    saved = this->frame;
    this->frame = lbl_805DA68C;
    this->draw();
    this->frame = saved;
    TObjPlayer::init_render_globals();
    pop_matrix();
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEneSlimeTailAttack::draw_blob_shadows() {
    s32 i;
    f32 k;
    s32 spC;
    s32 sp8;
    k = lbl_805DA66C;
    for (i = 0; i < 4; i++) {
        Vec v = pose.shadows[i];
        Vec normal;
        v.y += k;
        if (((s32 (*)(void *, Vec *, Vec *))project_actor_to_ground)(this, &v, &normal) != 0) {
            push_matrix();
            translate_matrix(0, v.x, lbl_805DA670 + v.y, v.z);
            direction_to_rotation_xz((u8 *)&normal, &spC, &sp8);
            rotate_matrix_z(0, sp8);
            rotate_matrix_x(0, spC + 0x4000);
            scale_matrix(0, lbl_805DA674, lbl_805DA674, lbl_805DA674);
            draw_blob_shadow(0);
            pop_matrix();
        }
    }
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
void reset_slime_tail_node_index(void) { lbl_805D52B4 = 0; }
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
void capture_slime_tail_node(void) {
    if ((s32) (*(s32 *)&lbl_805D52B4) == 7) {
        transform_to_view__11TCameraCtrlFii((s32) &slime_tail_attack_zero_vec, (s32) &lbl_80501010.attachment);
    }
    if (((s32) (*(s32 *)&lbl_805D52B4) >= 4) && ((s32) (*(s32 *)&lbl_805D52B4) < 8)) {
        transform_to_view__11TCameraCtrlFii((s32) &slime_tail_attack_transform, (s32)&lbl_80501010.shadows[lbl_805D52B4 - 4]);
    }
    (*(s32 *)&lbl_805D52B4) += 1;
}
#pragma pop

#pragma push
#pragma inline_depth(2)
#pragma auto_inline on
#pragma dont_inline on
SlimeTailPose *copy_slime_tail_pose(SlimeTailPose *dst, SlimeTailPose *src) {
    *dst = *src;
    return dst;
}
#pragma pop

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
void get_slime_tail_pose(SlimeTailPose *dst) {
    copy_slime_tail_pose(dst, &lbl_80501010);
}
#pragma pop

#pragma auto_inline on
#pragma dont_inline off
#pragma inline_depth(2)

extern "C" {
__declspec(section ".sdata2") extern const f32 lbl_805DA678 = 0.5F;
__declspec(section ".sdata2") extern const f32 lbl_805DA67C = 1.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA680 = -0.5F;
__declspec(section ".sdata2") extern const f32 lbl_805DA684 = 0.0500000007F;
__declspec(section ".sdata2") extern const f32 lbl_805DA688 = 0.100000009F;
__declspec(section ".sdata2") extern const f32 lbl_805DA68C = 7.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA690 = 41.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA694 = 48.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA698 = 12.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA69C = 35.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6A0 = 17.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6A4 = 30.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6A8 = 25.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6AC = 5.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6B0 = 56.25F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6B4 = 0.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6B8 = -0.0333333351F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6BC = -0.0166666675F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6C0 = 0.0666666701F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6C4 = -0.0316666663F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6C8 = 40.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6CC = 0.649999976F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6D0 = -0.0500000007F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6D4 = -0.975000024F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6D8 = 0.600000024F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6DC = 200.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6E0 = 15.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6E4 = 20.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6E8 = -1.125F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6EC = 1.25F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6F0 = 0.214285716F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6F4 = 11.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6F8 = -1.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA6FC = 0.0250000004F;
__declspec(section ".sdata2") extern const f32 lbl_805DA700 = -0.075000003F;
__declspec(section ".sdata2") extern const f32 lbl_805DA704 = 12.5F;
__declspec(section ".sdata2") extern const f32 lbl_805DA708 = -2.5F;
__declspec(section ".sdata2") extern const f32 lbl_805DA70C = -0.200000003F;
__declspec(section ".sdata2") extern const f32 lbl_805DA710 = 2.5F;
__declspec(section ".sdata2") extern const f32 lbl_805DA714 = 65536.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA718 = 0.00999999978F;
__declspec(section ".sdata2") extern const f32 lbl_805DA71C = 0.200000003F;
__declspec(section ".sdata2") extern const f32 lbl_805DA720 = 50.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA724 = 0.449999988F;
__declspec(section ".sdata2") extern const f32 lbl_805DA728 = 500.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA72C = 162.5F;
__declspec(section ".sdata2") extern const f32 lbl_805DA730 = 4.0F;
__declspec(section ".sdata2") extern const f32 lbl_805DA734 = 0.25F;
}
