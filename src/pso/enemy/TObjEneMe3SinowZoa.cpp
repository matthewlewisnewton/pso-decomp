#include "pso/animation/MotionContext.h"
#include "pso/npc/NpcModelRegistry.h"
#include "pso/npc/NpcAnimationBinding.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/enemy/BattleParameters.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/system/EnemyBmlResource.h"
#include "pso/render/render_util.h"
// Deferred generation preserves original function and native-vtable order.
#pragma defer_codegen on
#include "types.h"
#include "pso/enemy/TObjEneMe3SinowZoa.h"
#include "pso/object/TObjMotion.h"
#include "pso/object/TObjMotion.h"
#include "pso/system/vector.h"
#include "pso/enemy/TObjEneDD_ST.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/enemy/TObjEneMe3SinowZoaReal.h"
#include "pso/TParticleCtrl.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/enemy/TObjEneMe1Gee.h"
#include "pso/misc/TTecGiBarta.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"
#include "pso/system/NinjaTypes.h"
#include "pso/system/BmlResource.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/system/NinjaUtil.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TBreakUpMdl.h"
#include "pso/animation/ActorAnimationState.h"

// Shared resources follow their original BSS order so the compiler pools the
// parameter tables, alternate texture list, and material pointers together.
extern "C" {
Vec lbl_80542FB0;
__declspec(section ".data") s32 sinow_zoa_base_parameters[2];
__declspec(section ".data") s32 sinow_zoa_attack_parameters[2];
__declspec(section ".data") s32 sinow_zoa_resistance_parameters[2];
__declspec(section ".data") SinowZoaKindParameters *TObjEneMe3SinowZoa__kind_param_tbls[2];
__declspec(section ".data") NJS_TEXLIST lbl_80542FDC;
Vec sinow_zoa_alternate_position;
u32 *lbl_80542FF0[4];
BmlResource *TObjEneMe3SinowZoa__data_805D6AD8;
s32 lbl_805D6ADC;
TUnk_8048FA00 *TObjEneMe3SinowZoa__data_805D6AE0;

}

extern "C" {
void advance_animation_playback(void *);
s32 play_sound_effect(s32, void *, s32, s32);
s32 pack_debug_text_position(s32, s32);
void debug_printf_at(s32 id, const char *fmt, ...);
s32 scale_matrix(int, f32, f32, f32);
s32 rotate_matrix_y(int, int);
s32 push_matrix();
s32 pop_matrix();
s32 post_translate_matrix(void *);
extern char lbl_80475FD4[];
extern char lbl_80475FE4[];
extern char lbl_80475FF4[];
extern char lbl_80476004[];
extern char lbl_80476010[];
extern char lbl_80476028[];
extern char lbl_80476040[];
extern char lbl_80476058[];
extern char lbl_80476070[];
extern char lbl_80476084[];
extern u32 *lbl_80542FF0[];
extern s32 model_render_flags;
extern const f32 TObjEneMe3SinowZoa__data_805DF2F0;
extern const f32 TObjEneMe3SinowZoa__data_805DF2F4;
extern const f32 lbl_805DF318;
extern const f32 TObjEneMe3SinowZoa__data_805DF31C;
s32 select_enemy_destination(void *, Vec, int);
s32 copy_position_if_valid__10TObjPlayerFii(void *, Vec);
s32 enemy_turn_toward_dest(void *, s32);
void enemy_set_heading_velocity(f32 speed, TObjEnemy *enemy, s32 heading);
}
void print_float_padded(s32 arg0, s32 prec, f32 val);
void move_with_wall_slide(u8 *arg0);
extern "C" {
void subtract_vector(void *, void *);
s32 push_matrix_from(void *);
s32 matrix_mult_vec(int, void *, void *);
void create__11TTecRaBartaFPvPvPvPv(void *, void *, void *, s32);
extern Vec lbl_80475FC8[];
extern SinowZoaKindParameters *TObjEneMe3SinowZoa__kind_param_tbls[];
extern u8 identity_matrix[];
extern s32 game_difficulty_selection;
extern const f32 TObjEneMe3SinowZoa__data_805DF308;
extern const f32 TObjEneMe3SinowZoa__data_805DF30C;
extern const f32 TObjEneMe3SinowZoa__data_805DF310;
extern const f32 TObjEneMe3SinowZoa__data_805DF314;
u16 get_entity_id(TObjBase *);
u32 get_valid_target_player__10TNpcPlayerFv(int);
extern CollisionBody sinow_zoa_collision_parts[];

}

extern "C" {
extern const f32 lbl_805DF304;
extern const char *TObjEneMe3SinowZoaReal__name;
extern TObject *tl_04;
void invoke_initialization_hook__9TObjEneDDFPv(void *, void *);
}

#include "pso/render/reflection.h"
#include "pso/enemy/TObjEneRecon_8029E89C.h"
extern "C" void translate_matrix(u32, f32, f32, f32);
#include "pso/unk/text_803D96A8.h"
#include "pso/enemy/TObjEneRecon.h"
#include "pso/enemy/TObjEneRe7Berura.h"

extern "C" {

s32 get_mode__11TCameraCtrlFPv(void *);
s32 post_translate_matrix(void *);
s32 rotate_matrix_y(int, int);
s32 push_matrix();

extern const f32 TObjEneMe3SinowZoa__data_805DF31C;

}

#include "pso/player/TObjChara.h"
#include "pso/misc/TRaderMapCore.h"
extern "C" void has_flag_0x800__9TObjCharaFv();
extern "C" void test_flag30_512__9TObjCharaFv();
extern "C" void test_flag_1000__9TObjCharaFv();
extern "C" void test_flag_256__9TObjCharaFv();

#include <stddef.h>
#include "pso/boss/TBoss3Volopt.h"
#include "pso/boss/TBoss8Dragon.h"
#include "pso/boss/TObjBoss2Tunnel.h"

#include "pso/enemy/TObjEneEpsilon.h"
#include "pso/enemy/TObjEneMe3ShinowaReal.h"
#include "pso/misc/TScene.h"
#include "pso/misc/TTecResta.h"
#include "pso/misc/TTecSifta.h"

#define V8(n) virtual void v##n();
#define V64(n) V8(n##0) V8(n##1) V8(n##2) V8(n##3) V8(n##4) V8(n##5) V8(n##6) V8(n##7)

struct Vec_803181A8 { f32 x, y, z; };

extern "C" {
f32 random_ratio__9TObjCharaFv(s32);
s32 transition_enemy_state__9TObjEneDDFl(void *, int);
void advance_animation_playback(void *);
s32 play_sound_effect(s32, void *, s32, s32);
extern const f32 lbl_805DF334;
struct VBase_14_948132 { char pad[0x14]; };

struct VObj_14_948132 : VBase_14_948132 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual s32 m5();
};

struct Stack_80319B8C {
    s32 sp8;
    f32 spC;
};

struct Vec_80319E74 { f32 x, y; };

struct VBase_18_64d9d3 { char pad[0x18]; };

struct VObj_18_64d9d3 : VBase_18_64d9d3 {
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
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void m60();
    virtual void m61();
    virtual void m62();
    virtual void m63();
    virtual void m64();
    virtual void m65();
    virtual void m66();
    virtual void m67();
    virtual void m68();
    virtual void m69();
    virtual void m70();
    virtual void m71();
    virtual void m72();
    virtual void m73();
    virtual void m74();
    virtual void m75();
    virtual void m76();
    virtual void m77();
    virtual void m78();
    virtual void m79();
    virtual void m80();
    virtual void m81();
    virtual void m82();
    virtual void m83();
    virtual void m84();
    virtual void m85();
    virtual void m86();
    virtual void m87();
    virtual void m88();
    virtual void m89();
    virtual void m90();
    virtual void m91();
    virtual s32 m92();
    virtual void m93();
    virtual void m94();
    virtual void m95();
    virtual void m96();
    virtual void m97();
    virtual void m98();
    virtual void m99();
    virtual s32 m100();
};

typedef struct Vec_80317F90 { f32 x; f32 y; f32 z; } Vec_80317F90;

struct VBase_18_e66632 { char pad[0x18]; };

struct VObj_18_e66632 : VBase_18_e66632 {
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
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void m60();
    virtual void m61();
    virtual void m62();
    virtual void m63();
    virtual void m64();
    virtual void m65();
    virtual void m66();
    virtual void m67();
    virtual void m68();
    virtual void m69();
    virtual void m70();
    virtual void m71();
    virtual void m72();
    virtual void m73();
    virtual void m74();
    virtual void m75();
    virtual void m76();
    virtual void m77();
    virtual void m78();
    virtual void m79();
    virtual void m80();
    virtual void m81();
    virtual void m82();
    virtual void m83();
    virtual void m84();
    virtual void m85();
    virtual void m86();
    virtual s32 m87();
    virtual void m88();
    virtual void m89();
    virtual void m90();
    virtual void m91();
    virtual void m92();
    virtual void m93();
    virtual s32 m94();
    virtual void m95();
    virtual void m96();
    virtual void m97();
    virtual void m98();
    virtual void m99();
    virtual s32 m100();
    virtual void m101();
    virtual void m102();
    virtual void m103();
    virtual s32 m104();
    virtual void m105();
    virtual void m106();
    virtual void m107();
    virtual void m108();
    virtual s32 m109();
};

struct Param_8031A2A0 { u8 pad[0x18]; s32 level; };

struct T_8031A494 { u8 pad[0x354]; f32 f354; };

struct Base_8031A4E8 { char pad[0x18]; };

struct VObj_8031A4E8 : Base_8031A4E8 {
    virtual void m0();  virtual void m1();  virtual void m2();  virtual void m3();
    virtual void m4();  virtual void m5();  virtual void m6();  virtual void m7();
    virtual void m8();  virtual void m9();  virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23();
    virtual void m24(); virtual void m25(); virtual void m26(); virtual void m27();
    virtual void m28(); virtual void m29(); virtual void m30(); virtual void m31();
    virtual void m32(); virtual void m33(); virtual void m34(); virtual void m35();
    virtual void m36(); virtual void m37(); virtual void m38(); virtual void m39();
    virtual void m40(); virtual void m41(); virtual void m42(); virtual void m43();
    virtual void m44(); virtual void m45(); virtual void m46(); virtual void m47();
    virtual void m48(); virtual void m49(); virtual void m50(); virtual void m51();
    virtual void m52(); virtual void m53(); virtual void m54(); virtual void m55();
    virtual void m56(); virtual void m57(); virtual void m58(); virtual void m59();
    virtual void m60(); virtual void m61(); virtual void m62(); virtual void m63();
    virtual void m64(); virtual void m65(); virtual void m66(); virtual void m67();
    virtual void m68(); virtual void m69(); virtual void m70(); virtual void m71();
    virtual void m72(); virtual void m73(); virtual void m74(); virtual void m75();
    virtual void m76(); virtual void m77(); virtual void m78(); virtual void m79();
    virtual void m80(); virtual void m81(); virtual void m82(); virtual void m83();
    virtual void m84(); virtual void m85(); virtual void m86();
};

struct Base_8031A538 { char pad[0x18]; };

struct VObj_8031A538 : Base_8031A538 {
    V64(a) V64(b)
    V8(c0) V8(c1) V8(c2) V8(c3) V8(c4) V8(c5) V8(c6) V8(c7)
    V8(d0) V8(d1) V8(d2) V8(d3) V8(d4) V8(d5) V8(d6) V8(d7)
    V8(e0) V8(e1) V8(e2) V8(e3) V8(e4) V8(e5) V8(e6) V8(e7)
    V8(f0) V8(f1) V8(f2) V8(f3) V8(f4) V8(f5) V8(f6) V8(f7)
    V8(g0) V8(g1) V8(g2) V8(g3) V8(g4) V8(g5) V8(g6) V8(g7)
    V8(h0) V8(h1) V8(h2) V8(h3) V8(h4) V8(h5) V8(h6) V8(h7)
    V8(i0) V8(i1) V8(i2) V8(i3) V8(i4) V8(i5) V8(i6) V8(i7)
    V8(j0) V8(j1) V8(j2) V8(j3) V8(j4) V8(j5) V8(j6) V8(j7)
    V8(k0) V8(k1) V8(k2) V8(k3) V8(k4) V8(k5) V8(k6) V8(k7)
    V8(l0) V8(l1) V8(l2) V8(l3) V8(l4) V8(l5) V8(l6)
    virtual void m95();
    virtual void m96();
    f32 f3c_get();
};

struct VObj8031A598_Base { char pad[0x14]; };

struct VObj8031A598 : VObj8031A598_Base {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
};

struct VObj8031A5E0_Base { char pad[0x14]; };

struct VObj8031A5E0 : VObj8031A5E0_Base {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
};

struct RecoveredGlobal_800E7324_lbl_8043CF94 {
    s32 value;
    u8 remaining[0x8];
};

struct Vec_800E75AC { f32 x; f32 y; f32 z; };

struct Node_800E75AC { u8 pad[0x2c]; void *child; };

struct Obj_800E75AC { u8 pad[0x34]; Node_800E75AC *node; u8 pad2[0xc0 - 0x38]; f32 fc0; u8 pad3[0xf8 - 0xc4]; s32 ff8; };

struct Sub_800E750C { f32 f0; u8 pad4[4]; f32 f8; f32 fC; f32 f10; s32 f14; s32 f18; };

struct Obj_800E750C { u8 pad0[0x60]; s32 f60; u8 pad1[0xA4 - 0x64]; Sub_800E750C *fA4; };

typedef char RecoveredGlobal_800E7324_lbl_8043CF94_size[sizeof(RecoveredGlobal_800E7324_lbl_8043CF94) == 0xC ? 1 : -1];

struct VBase_14_c143b1 { char pad[0x14]; };

struct VObj_14_c143b1 : VBase_14_c143b1 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual s32 m4();
    virtual s32 m5();
};

struct VBase_14_2ab9de { char pad[0x14]; };

struct VObj_14_2ab9de : VBase_14_2ab9de {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual s32 m3();
};

s32 is_locally_controlled__10TObjPlayerFPv(void *);
u32 get_item_field_6__10TObjPlayerFPv(void *);
f32 fabs_float(f32);
void queue_destruction__7TObjectFv(void *);
void *create_timed_particle_emitter(void *owner, s32 id, s32 b, s32 c);
void *spawn_particle_effect(void *pos, s32 id);
s32 get_item_id__5TItemFv();
}
void enemy_turn_and_move_on_ground(u8 *arg0, s32 arg1, f32 farg0);
extern "C" {

void *__dt__12TObjEneDD_STFv(void *arg0, s16 arg1);
s32 check_v2_mode__9TObjEneDDFv(s32, s32);
s32 reset_hp__9TObjEneDDFP15BattleBaseStatsP12AttackParamsP15ActorParamBlock(void *, int, int, int);
s32 initialize_enemy_state__9TObjEneDDFl(void *, int);
int vfunc_96__9TObjEneDDFv(void*);
int vfunc_95__9TObjEneDDFv(void*);
void TObjEneDD__sub_800BA438(void *, void *);
s32 init_model__9TObjEneDDFP13CollisionBodyl(void *, void *, int, int);
s32 TObjEneMe3SinowZoa__sub_800D72A4(void *);
void *__dt__13TUnk_80494938Fv(void *arg0, s16 arg1);
s32 TBoss3Volopt__sub_800D8D88(void *, f32);
f32 * TBoss3Volopt__sub_800F059C(void *);
s32 check_enemy_body_collisions(void *);
void free_collision_body_parts(void *);
void send_6x26_unequip_item__10TObjPlayerFPvPv(void *, s32);

void create__10TTecDebandFlll(void *, void *, int);
void create__9TTecJelinFllll(void *, void *, void *, int);
void create_instance__9TTecZaruaFllll(void *, void *, void *, int);
s32 TObjEneMe3SinowZoa__sub_80316840(void *);
s32 fn_80316C3C__18TObjEneMe3SinowZoaFl(void *, s32);
void fn_803170F0__18TObjEneMe3SinowZoaFl(u8 *arg0, s32 arg1);
void fn_80317254__18TObjEneMe3SinowZoaFl(u8 *arg0, s32 arg1);
void TObjEneMe3SinowZoa__sub_80317B50(void *, s32);
void TObjEneMe3SinowZoa__sub_80317F90(u8 *arg0, s32 arg1);
void TObjEneMe3SinowZoa__sub_803182F8(u8 *, s32);
void TObjEneMe3SinowZoa__sub_80318564(u8 *, s32);
void TObjEneMe3SinowZoa__sub_8031884C(void *, s32);
void TObjEneMe3SinowZoa__sub_80318C0C(void *, s32);
struct Ene_80318F7C;
void TObjEneMe3SinowZoa__sub_80318F7C(Ene_80318F7C *, s32);
void TObjEneMe3SinowZoa__sub_80319748(u8 *arg0, s32 arg1);
void TObjEneMe3SinowZoa__sub_80319B8C(u8 *arg0, s32 arg1);

void cast_technique__18TObjEneMe3SinowZoaFPv(u8 *arg0);
u8 sub_8031A454__18TObjEneMe3SinowZoaFv(u8 *arg0);

u8 is_outside_visible_range__18TObjEneMe3SinowZoaFv(T_8031A494 *self);
s32 sub_8031A4D0__18TObjEneMe3SinowZoaFv(u8 *arg0);

bool TObjEneMe3SinowZoa__sub_8031A820(u8 *arg0);
u8 check_body_collision_at__18TObjEneMe3SinowZoaFlf(Obj_800E750C *arg0, s32 arg1, f32 farg0);

f32 sin_table_lookup(s32);
f32 cos_table_lookup(s32);
void compose_motion_node_matrix(void *arg0);
s32 matrix_mult_vec(int, void *, void *);
s32 push_matrix_from(void *);
s32 pop_matrix();

extern BmlResource *TObjEneMe3SinowZoa__data_805D6AD8;
extern TUnk_8048FA00 *TObjEneMe3SinowZoa__data_805D6AE0;
extern const f32 TObjEneMe3SinowZoa__data_805DF2F0;
extern const f32 TObjEneMe3SinowZoa__data_805DF2F4;
extern const f32 TObjEneMe3SinowZoa__data_805DF2FC;
extern const f32 TObjEneMe3SinowZoa__data_805DF314;
extern const f32 TObjEneMe3SinowZoa__data_805DF31C;
extern const f32 TObjEneMe3SinowZoa__data_805DF320;
extern const f32 TObjEneMe3SinowZoa__data_805DF324;
extern const f32 TObjEneMe3SinowZoa__data_805DF328;
extern const f32 TObjEneMe3SinowZoa__data_805DF32C;
extern s32 __vt__18TObjEneMe3SinowZoa[];
extern u8 sinow_zoa_breakup_params[];
extern Vec lbl_80542FB0;
extern __declspec(section ".data") s32 sinow_zoa_base_parameters[2];
extern __declspec(section ".data") s32 sinow_zoa_attack_parameters[2];
extern __declspec(section ".data") s32 sinow_zoa_resistance_parameters[2];
extern __declspec(section ".data") NJS_TEXLIST lbl_80542FDC;
extern u8 identity_matrix[];
extern s32 game_difficulty_selection;
extern const f32 lbl_805DF2F8;
extern const f32 lbl_805DF300;
extern const f32 lbl_805DF304;
extern const f32 lbl_805DF330;
extern const f32 lbl_805DF350;

extern const f32 lbl_805DF374;
extern const f32 lbl_805DF378;
extern f32 lbl_805DF37C;
extern f32 lbl_805DF380;
extern const f32 lbl_805DF384;
extern const f32 lbl_805DF388;
extern const f32 lbl_805DF38C;

extern "C" {
void *__dt__22TObjEneMe3SinowZoaRealFv(void *arg0, s16 arg1);
}

extern "C" {
extern u8 lbl_80475E2C[];
}
extern "C" {
extern u8 lbl_80475E3C[];
}
extern "C" {
extern u8 lbl_80475E54[];
}
extern "C" {
extern u8 lbl_80475E68[];
}
extern "C" {
extern u8 lbl_80475E84[];
}
extern "C" {
extern u8 lbl_80475E9C[];
}
extern "C" {
extern u8 lbl_80475EB4[];
}
extern "C" {
extern u8 lbl_80475EC8[];
}
extern "C" {
extern u8 lbl_80475EE0[];
}
extern "C" {
extern u8 lbl_80475EF4[];
}
extern "C" {
extern u8 lbl_80475F10[];
}
extern "C" {
extern u8 lbl_80475F24[];
}
extern "C" {
extern u8 lbl_80475F38[];
}
extern "C" {
extern u8 lbl_80475F54[];
}
extern "C" {
extern u8 lbl_80475F64[];
}

extern void *lbl_804E87F0[2];
extern const char *lbl_804E87F8[12];
extern void *lbl_804E8838[2];
extern const char *lbl_804E8840[12];
void *TObjEneMe3SinowZoa_init_params[7] = {
    (void *)0x43610000, (void *)0x0, (void *)0x600, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0,
};
CollisionBody sinow_zoa_collision_parts[] = {
    {{0.0f, 0.0f, 0.0f}, 12.0f, 0.0f, 0, 0x8003, {0.0f, 0.0f, 0.0f}, 0.0f}
};
__declspec(section ".data") void *lbl_804E87F0[2] = {
    (void *)&lbl_80475E2C, (void *)0x0,
};
const char *lbl_804E87F8[12] = {(const char *)&lbl_80475E3C, (const char *)&lbl_80475E54, (const char *)&lbl_80475E68, (const char *)&lbl_80475E84, (const char *)&lbl_80475E9C, (const char *)&lbl_80475EB4, (const char *)&lbl_80475EC8, (const char *)&lbl_80475EE0, (const char *)&lbl_80475EF4, (const char *)&lbl_80475F10, (const char *)&lbl_80475F24, 0};
BmlResourceDescriptor sinow_zoa_bml_desc = {(const char *)&lbl_80475F38, (const char *const *)lbl_804E87F0, lbl_804E87F8, 1, 11};
__declspec(section ".data") void *lbl_804E8838[2] = {
    (void *)&lbl_80475F54, (void *)0x0,
};
const char *lbl_804E8840[12] = {(const char *)&lbl_80475E3C, (const char *)&lbl_80475E54, (const char *)&lbl_80475E68, (const char *)&lbl_80475E84, (const char *)&lbl_80475E9C, (const char *)&lbl_80475EB4, (const char *)&lbl_80475EC8, (const char *)&lbl_80475EE0, (const char *)&lbl_80475EF4, (const char *)&lbl_80475F10, (const char *)&lbl_80475F24, 0};
BmlResourceDescriptor sinow_zoa_multiplayer_bml_desc = {(const char *)&lbl_80475F64, (const char *const *)lbl_804E8838, lbl_804E8840, 1, 11};
TObjMotionAction lbl_804E8880[13] = {
    {1, 0, 0, 0.5f, 0x80000000},
    {3, 0, 1, 0.69999999f, 0x80000000},
    {1, 0, 9, 0.5f, 0x80000000},
    {3, 0, 2, 0.80000001f, 0x00000000},
    {3, 0, 4, 0.40000001f, 0x00000000},
    {3, 0, 5, 0.60000002f, 0x00000000},
    {3, 0, 6, 0.69999999f, 0x00000000},
    {3, 0, 7, 1.0f, 0x00000000},
    {3, 0, 8, 1.0f, 0x00000000},
    {1, 0, 9, 0.5f, 0x00000000},
    {1, 0, 10, 1.1f, 0x00000000},
    {3, 0, 3, 0.69999999f, 0x00000000},
    {3, 0, 8, 1.0f, 0x00000000}
};

struct VBase_14_aa9368 { char pad[0x14]; };
struct VObj_14_aa9368 : VBase_14_aa9368 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual s32 m6();
    virtual s32 m7();
};
struct VBase_18_fc0b09 { char pad[0x18]; };
struct VObj_18_fc0b09 : VBase_18_fc0b09 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual s32 m8(f32, f32);
    virtual s32 m9(f32, f32, f32);
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
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void m60();
    virtual void m61();
    virtual void m62();
    virtual void m63();
    virtual void m64();
    virtual void m65();
    virtual void m66();
    virtual void m67();
    virtual void m68();
    virtual void m69();
    virtual void m70();
    virtual void m71();
    virtual void m72();
    virtual void m73();
    virtual void m74();
    virtual void m75();
    virtual void m76();
    virtual void m77();
    virtual void m78();
    virtual void m79();
    virtual void m80();
    virtual void m81();
    virtual void m82();
    virtual void m83();
    virtual void m84();
    virtual void m85();
    virtual void m86();
    virtual void m87();
    virtual void m88();
    virtual void m89();
    virtual void m90();
    virtual void m91();
    virtual void m92();
    virtual void m93();
    virtual void m94();
    virtual void m95();
    virtual void m96();
    virtual void m97();
    virtual void m98();
    virtual void m99();
    virtual void m100();
    virtual void m101();
    virtual void m102();
    virtual void m103();
    virtual void m104();
    virtual void m105();
    virtual s32 m106();
    virtual s32 m107();
    virtual s32 m108();
    virtual void m109();
    virtual void m110();
    virtual void m111();
    virtual void m112();
    virtual s32 m113();
};

struct Zoa_8031786C {
    u8 pad0[0x3C0];
    s32 f3C0;
    u8 pad3C4[0x3CC - 0x3C4];
    s32 f3CC;
    s32 f3D0;
    u8 pad3D4[0x3F8 - 0x3D4];
    s32 f3F8;
    u8 pad3FC[0x414 - 0x3FC];
    VObj_14_aa9368 sub;
};

s32 is_main_phase_15__9TObjEneDDFv();
s32 defer_render__7TObjectFv(void *);
s32 rotate_matrix_y(int, int);
void translate_matrix(u32 arg0, f32 x, f32 y, f32 z);
s32 push_matrix();
s32 post_translate_matrix(void *);
extern u8 saved_model_draw_color[];

extern u8 model_material_color[];
extern s32 saved_model_render_flags;
extern s32 saved_chunk_polygon_flags_and_mask;
extern s32 saved_chunk_polygon_flags_or_mask;
extern s32 lbl_805D6ADC;
extern s32 chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_and_mask;
extern s32 model_render_flags;
extern const f32 lbl_805D9E84;
extern const f32 lbl_805D9E88;
extern const f32 lbl_805DF318;

struct VBase_14_c5778e { char pad[0x14]; };
struct VObj_14_c5778e : VBase_14_c5778e {
    virtual void m0();
    virtual s32 m1(s32);
    virtual void m2();
    virtual void m3();
    virtual s32 m4();
};
struct Vec_80317B50 { f32 x, y, z; };
u32 csnVectorUnder(void *, void *, int);
u32 csnVector(void *, void *, int);
s32 check_move_collision__18TObjEneMe3SinowZoaFP3Vec(void *, void *);
extern const f32 TObjEneMe3SinowZoa__data_805DF308;

void TObjEneMe3SinowZoa__sub_80317B50(void *arg0_, s32 arg1);

void TObjEneMe3SinowZoa__sub_80317F90(u8 *arg0, s32 arg1);

struct VBase_14_803182F8 { char pad[0x14]; };
struct VObj_14_803182F8 : VBase_14_803182F8 {
    virtual void m0();
    virtual void m1(s32);
    virtual void m2();
    virtual void m3();
    virtual s32 m4();
};

extern "C" {

void TObjEneMe3SinowZoa__sub_803182F8(u8 *ene_dd, s32 arg1);

}

struct Base18_80318564 { char pad[0x18]; };
struct VObj_80318564 : Base18_80318564 {
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
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void m60();
    virtual void m61();
    virtual void m62();
    virtual void m63();
    virtual void m64();
    virtual void m65();
    virtual void m66();
    virtual void m67();
    virtual void m68();
    virtual void m69();
    virtual void m70();
    virtual void m71();
    virtual void m72();
    virtual void m73();
    virtual void m74();
    virtual void m75();
    virtual void m76();
    virtual void m77();
    virtual void m78();
    virtual void m79();
    virtual void m80();
    virtual void m81();
    virtual void m82();
    virtual void m83();
    virtual void m84();
    virtual void m85();
    virtual void m86();
    virtual void m87();
    virtual void m88();
    virtual void m89();
    virtual void m90();
    virtual void m91();
    virtual void m92();
    virtual void m93();
    virtual void m94();
    virtual void m95();
    virtual void m96();
    virtual void m97();
    virtual void m98();
    virtual void m99();
    virtual void m100();
};
struct Base14_80318564 { char pad[0x14]; };
struct VSub_80318564 : Base14_80318564 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual s32 s4();
};

extern "C" {

extern const f32 TObjEneMe3SinowZoa__data_805DF30C;
extern const f32 TObjEneMe3SinowZoa__data_805DF310;

void TObjEneMe3SinowZoa__sub_80318564(u8 *arg0, s32 arg1);

}

struct VBase_18_347dfc { char pad[0x18]; };
struct VObj_18_347dfc : VBase_18_347dfc {
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
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void m60();
    virtual void m61();
    virtual void m62();
    virtual void m63();
    virtual void m64();
    virtual void m65();
    virtual void m66();
    virtual void m67();
    virtual void m68();
    virtual void m69();
    virtual void m70();
    virtual void m71();
    virtual void m72();
    virtual void m73();
    virtual void m74();
    virtual void m75();
    virtual void m76();
    virtual void m77();
    virtual void m78();
    virtual void m79();
    virtual void m80();
    virtual void m81();
    virtual void m82();
    virtual void m83();
    virtual void m84();
    virtual void m85();
    virtual void m86();
    virtual s32 m87();
    virtual void m88();
    virtual s32 m89();
    virtual s32 m90();
    virtual void m91();
    virtual void m92();
    virtual void m93();
    virtual s32 m94();
    virtual void m95();
    virtual void m96();
    virtual void m97();
    virtual void m98();
    virtual void m99();
    virtual s32 m100();
    virtual void m101();
    virtual s32 m102(f32);
};
f64 atan2_float(f32, f32);
extern const f64 TObjEneMe3SinowZoa__data_804760A0;
extern const f32 lbl_805DF338;
extern const f32 lbl_805DF33C;
extern const f32 lbl_805DF340;
extern const f32 lbl_805DF344;
void TObjEneMe3SinowZoa__sub_8031884C(void *arg0_, s32 arg1);

struct VBase_14_6ea8ee { char pad[0x14]; };
struct VObj_14_6ea8ee : VBase_14_6ea8ee {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual s32 m3();
    virtual s32 m4();
};
struct VBase_18_4f5f2e { char pad[0x18]; };
struct VObj_18_4f5f2e : VBase_18_4f5f2e {
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
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void m60();
    virtual void m61();
    virtual void m62();
    virtual void m63();
    virtual void m64();
    virtual void m65();
    virtual void m66();
    virtual void m67();
    virtual void m68();
    virtual void m69();
    virtual void m70();
    virtual void m71();
    virtual void m72();
    virtual void m73();
    virtual void m74();
    virtual void m75();
    virtual void m76();
    virtual void m77();
    virtual void m78();
    virtual void m79();
    virtual void m80();
    virtual void m81();
    virtual void m82();
    virtual void m83();
    virtual void m84();
    virtual void m85();
    virtual void m86();
    virtual s32 m87();
    virtual void m88();
    virtual void m89();
    virtual void m90();
    virtual void m91();
    virtual void m92();
    virtual void m93();
    virtual s32 m94();
    virtual void m95();
    virtual void m96();
    virtual void m97();
    virtual void m98();
    virtual void m99();
    virtual s32 m100();
    virtual void m101();
    virtual void m102();
    virtual s32 m103();
    virtual void m104();
    virtual s32 m105();
    virtual void m106();
    virtual void m107();
    virtual void m108();
    virtual void m109();
    virtual s32 m110();
};

s32 move_to_shot_position__9TObjEneDDFfff(void *, f32 *, f32, f32, f32);

void TObjEneMe3SinowZoa__sub_80318C0C(void *arg0_, s32 arg1);

struct Vec_80318F7C { f32 x, y, z; };

struct SubBase_80318F7C { char pad[0x14]; };
struct Sub_80318F7C : SubBase_80318F7C {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual s32 m4();
};

struct TgtBase_80318F7C { char pad[0x18]; };
struct Tgt_80318F7C : TgtBase_80318F7C {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17();
    virtual s32 m18(void *, f32);
    virtual void m19();
    virtual void m20(void *, f32);
    virtual void m21(); virtual void m22();
    virtual void m23(void *, f32);
};

struct ObjBase_80318F7C { char pad[0x18]; };
struct Obj_80318F7C : ObjBase_80318F7C {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23();
    virtual void m24(); virtual void m25(); virtual void m26(); virtual void m27();
    virtual void m28(); virtual void m29(); virtual void m30(); virtual void m31();
    virtual void m32(); virtual void m33(); virtual void m34(); virtual void m35();
    virtual void m36(); virtual void m37(); virtual void m38(); virtual void m39();
    virtual void m40(); virtual void m41(); virtual void m42(); virtual void m43();
    virtual void m44(); virtual void m45(); virtual void m46(); virtual void m47();
    virtual void m48(); virtual void m49(); virtual void m50(); virtual void m51();
    virtual void m52(); virtual void m53(); virtual void m54(); virtual void m55();
    virtual void m56(); virtual void m57(); virtual void m58(); virtual void m59();
    virtual void m60(); virtual void m61(); virtual void m62(); virtual void m63();
    virtual void m64(); virtual void m65(); virtual void m66(); virtual void m67();
    virtual void m68(); virtual void m69(); virtual void m70(); virtual void m71();
    virtual void m72(); virtual void m73(); virtual void m74(); virtual void m75();
    virtual void m76(); virtual void m77(); virtual void m78(); virtual void m79();
    virtual void m80(); virtual void m81(); virtual void m82(); virtual void m83();
    virtual void m84(); virtual void m85(); virtual void m86();
    virtual void m87();
    virtual void m88();
    virtual void m89();
    virtual void m90();
    virtual void m91(); virtual void m92(); virtual void m93();
    virtual void m94();
    virtual void m95(); virtual void m96(); virtual void m97(); virtual void m98(); virtual void m99();
    virtual u32 m100();
};

struct Ene_80318F7C : Obj_80318F7C {
    u8 pad1c[0x28 - 0x1C];
    s16 f28;
    u8 pad2a[0x38 - 0x2A];
    Vec_80318F7C pos;
    u8 pad44[0x60 - 0x44];
    s32 f60;
    u8 pad64[0xB0 - 0x64];
    s32 fB0;
    u8 padb4[0xB8 - 0xB4];
    s16 fB8;
    u8 padba[0xC0 - 0xBA];
    f32 fC0;
    u8 padc4[0xC8 - 0xC4];
    f32 fC8;
    u8 padcc[0x390 - 0xCC];
    Tgt_80318F7C *f390;
    u8 pad394[0x3A0 - 0x394];
    f32 f3A0;
    u8 pad3a4[0x3A8 - 0x3A4];
    f32 f3A8;
    f32 f3AC;
    u8 pad3b0[0x3C0 - 0x3B0];
    s32 f3C0;
    u8 pad3c4[0x3CC - 0x3C4];
    s32 f3CC;
    u8 pad3d0[0x3E0 - 0x3D0];
    f32 f3E0;
    f32 f3E4;
    u8 pad3e8[0x414 - 0x3E8];
    Sub_80318F7C sub;
    u8 pad42c[0x434 - 0x42C];
    s32 f434;
    u8 pad438[0x440 - 0x438];
    f32 f440;
    f32 f444;
};

extern "C" {

u32 csnVecterUnder(void *, int);
extern const f32 lbl_805DF348;
extern const f32 lbl_805DF34C;
extern const f32 lbl_805DF354;

void TObjEneMe3SinowZoa__sub_80318F7C(Ene_80318F7C *self, s32 arg1);

}

void TObjEneMe3SinowZoa__sub_80319748(u8 *ene_me3_sinow_zoa, s32 arg1);

extern "C" {

s32 enemy_validate_retained_target(u8 *arg0);
extern const u32 lbl_805DF368;

}

struct VBase_18_bb4b7f { char pad[0x18]; };
struct VObj_18_bb4b7f : VBase_18_bb4b7f {
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
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void m60();
    virtual void m61();
    virtual void m62();
    virtual void m63();
    virtual void m64();
    virtual void m65();
    virtual void m66();
    virtual void m67();
    virtual void m68();
    virtual void m69();
    virtual void m70();
    virtual void m71();
    virtual void m72();
    virtual void m73();
    virtual void m74();
    virtual void m75();
    virtual void m76();
    virtual void m77();
    virtual void m78();
    virtual void m79();
    virtual void m80();
    virtual void m81();
    virtual void m82();
    virtual void m83();
    virtual void m84();
    virtual void m85();
    virtual void m86();
    virtual s32 m87();
    virtual void m88();
    virtual void m89();
    virtual void m90();
    virtual void m91();
    virtual void m92();
    virtual void m93();
    virtual s32 m94();
    virtual void m95();
    virtual void m96();
    virtual void m97();
    virtual void m98();
    virtual void m99();
    virtual s32 m100();
    virtual void m101();
    virtual s32 m102(f32);
    virtual void m103();
    virtual s32 m104();
};

extern "C" {

extern const f32 lbl_805DF36C;
extern const f32 lbl_805DF370;

void TObjEneMe3SinowZoa__sub_80319B8C(u8 *ene_dd, s32 arg1);

}

void cast_technique__18TObjEneMe3SinowZoaFPv(u8 *arg0);

bool TObjEneMe3SinowZoa__sub_8031A820(u8 *ene_dd);

}

extern "C" void *__ct__12TObjEneDD_STFP7TObject(void *);
#include "pso/enemy/TUnk_80494938.h"

extern s32 __vt__18TObjEneMe3SinowZoa[];
extern void *lbl_805D4120;

extern "C" {

extern const f32 lbl_805DF38C;
void mem_free(void *p);

}

extern "C" {

s32 is_split_screen();
void *mem_alloc(u32);
void *init__11TBreakUpMdlFPviif(void *, s32, s32, f32);
extern const s32 lbl_80475E0C[];
extern const s32 lbl_80475E14[];
extern const s32 lbl_80475E1C[];
extern const s32 lbl_80475E24[];
}
extern "C" {
extern NpcAnimationBinding lbl_80475FA8;
extern NpcAnimationBinding lbl_80475FB8;
}

inline void configure_sinow_animation_speeds(const SinowZoaKindParameters *parameters);

#undef V8
#undef V64

// MWCC deferred generation emits these definitions in original address order.

#define V8(n) virtual void v##n();
#define V64(n) V8(n##0) V8(n##1) V8(n##2) V8(n##3) V8(n##4) V8(n##5) V8(n##6) V8(n##7)
#define sinow_zoa_collision_parts ((u8 *)sinow_zoa_collision_parts)
#define F(T, o) (*(T *)(arg0 + (o)))
#define VO ((VObj_80318564 *)arg0)
#define VS ((VSub_80318564 *)(arg0 + 0x414))
#define TBL(o) (((s32 *)TObjEneMe3SinowZoa__kind_param_tbls[F(s32, 0x3C8)])[(o) / 4])
#pragma opt_common_subs off
void TObjEneMe3SinowZoa::load_resources() {
    s32 i;
    NJS_TEXLIST *source;
    s32 count;
    NJS_OBJECT *root;
    NJS_CNK_MODEL *model;
    AnimationMotion *motion;
    TUnk_8048FA00 *breakup;

    lbl_80542FB0.x = TObjEneMe3SinowZoa__data_805DF31C;
    lbl_80542FB0.y = TObjEneMe3SinowZoa__data_805DF31C;
    lbl_80542FB0.z = TObjEneMe3SinowZoa__data_805DF31C;
    if (is_split_screen()) {
        TObjEneMe3SinowZoa__data_805D6AD8 = (BmlResource *)load_enemy_bml_resource(&sinow_zoa_multiplayer_bml_desc);
    } else {
        TObjEneMe3SinowZoa__data_805D6AD8 = (BmlResource *)load_enemy_bml_resource(&sinow_zoa_bml_desc);
    }
    source = (NJS_TEXLIST *)TObjEneMe3SinowZoa__data_805D6AD8->models[0].m_c;
    count = source->nbTexture;
    lbl_80542FDC.nbTexture = count;
    lbl_80542FDC.textures = (NJS_TEXNAME *)mem_alloc(count * sizeof(NJS_TEXNAME));
    for (i = 0; i < count; ++i) {
        ((TObjPlayer *)&lbl_80542FDC.textures[i])->copy_vec3(&source->textures[i]);
    }
    for (i = 0; i < 3; ++i) {
        NJS_TEXNAME *texture = &lbl_80542FDC.textures[i];
        texture->texaddr = texture[3].texaddr;
    }
    for (i = 0; i < 2; ++i) {
        s32 *table = sinow_zoa_base_parameters;
        table[i] = (s32)get_battle_base_stats(lbl_80475E0C[i]);
    }
    for (i = 0; i < 2; ++i) {
        s32 *table = sinow_zoa_attack_parameters;
        table[i] = (s32)get_battle_attack_params(lbl_80475E14[i]);
    }
    for (i = 0; i < 2; ++i) {
        s32 *table = sinow_zoa_resistance_parameters;
        table[i] = (s32)get_battle_resistance_params(lbl_80475E1C[i]);
    }
    for (i = 0; i < 2; ++i) {
        TObjEneMe3SinowZoa__kind_param_tbls[i] = (SinowZoaKindParameters *)get_battle_movement_params(lbl_80475E24[i]);
    }
    configure_sinow_animation_speeds(TObjEneMe3SinowZoa__kind_param_tbls[0]);
    lbl_805D6ADC = 0;
    Vec *alternate_position = &sinow_zoa_alternate_position;
    alternate_position->x = TObjEneMe3SinowZoa__data_805DF31C;
    alternate_position->y = TObjEneMe3SinowZoa__data_805DF31C;
    alternate_position->z = TObjEneMe3SinowZoa__data_805DF31C;
    root = (NJS_OBJECT *)TObjEneMe3SinowZoa__data_805D6AD8->models[0].model;
    model = (NJS_CNK_MODEL *)((NJS_OBJECT *)find_model_node((u32)root, 9))->model;
    if (model) lbl_80542FF0[0] = (u32 *)(model->polygon_list + 2);
    else lbl_80542FF0[0] = 0;
    model = (NJS_CNK_MODEL *)((NJS_OBJECT *)find_model_node((u32)root, 0xD))->model;
    if (model) lbl_80542FF0[1] = (u32 *)(model->polygon_list + 2);
    else lbl_80542FF0[1] = 0;
    model = (NJS_CNK_MODEL *)((NJS_OBJECT *)find_model_node((u32)root, 0x26))->model;
    if (model) lbl_80542FF0[2] = (u32 *)(model->polygon_list + 2);
    else lbl_80542FF0[2] = 0;
    motion = TObjEneMe3SinowZoa__data_805D6AD8->motions[lbl_804E8880[5].motion].motion;
    breakup = (TUnk_8048FA00 *)::operator new(sizeof(TUnk_8048FA00));
    if (breakup) {
        breakup = (TUnk_8048FA00 *)init__11TBreakUpMdlFPviif(breakup, TObjEneMe3SinowZoa__data_805D6AD8->models[0].model,
            (s32)motion, (f32)(motion->frameCount - 1));
    }
    TObjEneMe3SinowZoa__data_805D6AE0 = (TUnk_8048FA00 *)breakup;
    NpcAnimationBinding a = lbl_80475FA8;
    a.motions = TObjEneMe3SinowZoa__data_805D6AD8->motions;
    NpcAnimationBinding b = lbl_80475FB8;
    b.motions = TObjEneMe3SinowZoa__data_805D6AD8->motions;
    NpcModelRegistry::register_animated_chunk(0x49, (void *)TObjEneMe3SinowZoa__data_805D6AD8->models[0].model,
            (void *)TObjEneMe3SinowZoa__data_805D6AD8->models[0].m_c, &a, TObjEneMe3SinowZoa__data_805DF2FC, TObjEneMe3SinowZoa__data_805DF31C);
    NpcModelRegistry::register_animated_chunk(0x4A, (void *)TObjEneMe3SinowZoa__data_805D6AD8->models[0].model,
            (void *)(s32)&lbl_80542FDC, &a, TObjEneMe3SinowZoa__data_805DF2FC, TObjEneMe3SinowZoa__data_805DF31C);
    NpcModelRegistry::register_animated_chunk(0x4B, (void *)TObjEneMe3SinowZoa__data_805D6AD8->models[0].model,
            (void *)TObjEneMe3SinowZoa__data_805D6AD8->models[0].m_c, &b, TObjEneMe3SinowZoa__data_805DF2FC, TObjEneMe3SinowZoa__data_805DF31C);
    NpcModelRegistry::register_animated_chunk(0x4C, (void *)TObjEneMe3SinowZoa__data_805D6AD8->models[0].model,
            (void *)(s32)&lbl_80542FDC, &b, TObjEneMe3SinowZoa__data_805DF2FC, TObjEneMe3SinowZoa__data_805DF31C);
}

inline void configure_sinow_animation_speeds(const SinowZoaKindParameters *parameters) {
    TObjEneMe3SinowZoa::set_entry_value_clamped(7, parameters->attack_speed);
    TObjEneMe3SinowZoa::set_entry_value_clamped(4, parameters->cast_speed);
}

#pragma opt_common_subs on
void *TObjEneMe3SinowZoaReal::create(void *data) { return create_instance(data); }

void TObjEneMe3SinowZoa::free_resources() {
    if (TObjEneMe3SinowZoa__data_805D6AE0 != NULL) {
        delete TObjEneMe3SinowZoa__data_805D6AE0;
        TObjEneMe3SinowZoa__data_805D6AE0 = 0;
    }
    if (lbl_80542FDC.textures != 0) {
        mem_free((void *)lbl_80542FDC.textures);
        lbl_80542FDC.textures = 0;
    }
    if (TObjEneMe3SinowZoa__data_805D6AD8 != 0) {
        delete TObjEneMe3SinowZoa__data_805D6AD8;
        TObjEneMe3SinowZoa__data_805D6AD8 = 0;
    }
}

void TObjEneMe3SinowZoa::set_entry_value_clamped(s32 action, f32 speed) {
    if (speed < lbl_805DF38C) {
        speed = lbl_805DF38C;
    }
    lbl_804E8880[action].speed = speed;
}

TObjEneMe3SinowZoa::TObjEneMe3SinowZoa(TObject *parent) : TObjEneDD_ST(parent) {
    m_name = (const char *)lbl_805D4120;
}

#pragma opt_propagation off
void TObjEneMe3SinowZoaReal::init_enemy() {
    s32 temp_r0;
    u8 *temp_r6;


    init_position_vectors();
    sub_8031A3D8();
    temp_r6 = (u8 *)(*(u8 **)((s8 *)TObjEneMe3SinowZoa__data_805D6AD8 + 0x42C));
    *(s32 *)((s8 *)((u8 *)this) + 0x34) = (s32) *(s32 *)((s8 *)temp_r6 + 8);
    init_model__9TObjEneDDFP13CollisionBodyl((void *)this, ((void * *)sinow_zoa_collision_parts), 1, (int)temp_r6);
    *(s32 *)((s8 *)((u8 *)this) + 0xB0) = 0;
    this->set_field_d8((s32)lbl_804E8880);
    this->set_field_dc((int) (*(s32 *)((s8 *)TObjEneMe3SinowZoa__data_805D6AD8 + 0x430)));
    set_animation((*(s16 *)((s8 *)((u8 *)this) + 0xB8)));
    temp_r0 = *(s32 *)((s8 *)((u8 *)this) + 0x3C8);
    {
        s32 *a = sinow_zoa_base_parameters;
        s32 *b = sinow_zoa_attack_parameters;
        s32 *c = sinow_zoa_resistance_parameters;
        reset_hp__9TObjEneDDFP15BattleBaseStatsP12AttackParamsP15ActorParamBlock((void *)this, a[temp_r0], b[temp_r0], c[temp_r0]);
    }
    this->check_state_flag_4();
    *(void **)((s8 *)((u8 *)this) + 0x350) = TObjEneMe3SinowZoa_init_params;
    *(f32 *)((s8 *)((u8 *)this) + 0x37C) = (f32) TObjEneMe3SinowZoa__data_805DF314;
    enemy_init_acquire_period(0x1E);
    enemy_init_validate_period(0x1E);
    *(s32 *)((s8 *)((u8 *)this) + 0x3CC) = 0;
    *(s32 *)((s8 *)((u8 *)this) + 0x3D0) = 0;
    VecCopy((Vec *)((u8 *)this + 0x3D4), (const Vec *)((u8 *)this + 0x38));
    *(f32 *)((s8 *)((u8 *)this) + 0x3E0) = (*(f32 *)((s8 *)((u8 *)this) + 0x3C));
    *(f32 *)((s8 *)((u8 *)this) + 0x3E4) = (f32) TObjEneMe3SinowZoa__data_805DF31C;
    *(s32 *)((s8 *)((u8 *)this) + 0x3F8) = 0;
    *(s32 *)((s8 *)((u8 *)this) + 0x3FC) = 0;
    *(s16 *)((s8 *)((u8 *)this) + 0x404) = (s16) *(s16 *)((s8 *)((u8 *)this) + 0x2CC);
    ((VObj_14_2ab9de *)((u8 *)this + (1044)))->m3();
    *(s32 *)((s8 *)((u8 *)this) + 0x434) = 0;
    *(s32 *)((s8 *)((u8 *)this) + 0x438) = 0;
    *(s32 *)((s8 *)((u8 *)this) + 0x43C) = 0;
    *(f32 *)((s8 *)((u8 *)this) + 0x440) = (f32) TObjEneMe3SinowZoa__data_805DF31C;
    *(f32 *)((s8 *)((u8 *)this) + 0x444) = (f32) TObjEneMe3SinowZoa__data_805DF31C;
    *(f32 *)((s8 *)((u8 *)this) + 0x448) = (f32) TObjEneMe3SinowZoa__data_805DF31C;
    *(f32 *)((s8 *)((u8 *)this) + 0x44C) = (f32) TObjEneMe3SinowZoa__data_805DF31C;
    *(f32 *)((s8 *)((u8 *)this) + 0x450) = (f32) TObjEneMe3SinowZoa__data_805DF31C;
    *(s32 *)((s8 *)((u8 *)this) + 0x454) = 0;
    *(s32 *)((s8 *)((u8 *)this) + 0x458) = 0;
    if ((s32) *(s32 *)((s8 *)((u8 *)this) + 0x3C0) == 1) {
        set_indexed_flags(0, 0x08000000);
    } else {
        this->clear_player_status_flag(0, 0x08000000);
    }
}

#pragma opt_propagation on
TObjEneMe3SinowZoa::~TObjEneMe3SinowZoa() {
    if (effect_454) { queue_destruction__7TObjectFv(effect_454); effect_454 = 0; }
    if (effect_458) { queue_destruction__7TObjectFv(effect_458); effect_458 = 0; }
    free_collision_body_parts(this);
}

void TObjEneMe3SinowZoa::run_task() {
    s32 temp_r3;
    if (TObjPlayer::check_demo_mode() != 0) {
        this->action();
        return;
    }
    if (this->vfunc_83() != 4) {
        this->vfunc_85();
    }
    sub_8031AC74();
    this->copy_pos_with_height_offset();
    this->vfunc_88();
    temp_r3 = *(s32 *)((s8 *)((u8 *)this) + 0x3CC);
    if (temp_r3 & 0x40000) {
        *(s32 *)((s8 *)((u8 *)this) + 0x3CC) = (s32) (temp_r3 & 0xFFFBFFFF);
    } else {
        ((TObjEnemy *)((u8 *)this))->submit_default_cursor_candidate();
    }
    if (((s32) *(s32 *)((s8 *)((u8 *)this) + 0x3C0) == 0) || (TObjEneMe3SinowZoa__sub_800D72A4(((u8 *)this) + 0x414) != 0)) {
        this->vfunc_100();
    }
    if (*(s32 *)((s8 *)((u8 *)this) + 0x3D0) & 0x4000) {
        TObjEneRecon::set_active();
    }
}

void TObjEneMe3SinowZoa::sub_8031AC74() {
    s32 temp_r3;
    s32 temp_r3_2;
    u8 *arg0 = (u8 *)this;
    if (*(s32 *)((s8 *)arg0 + 0x30) & 0x24) {
        if (((s32) *(s32 *)((s8 *)arg0 + 0x3C0) != 0) || (temp_r3 = *(s32 *)((s8 *)arg0 + 0x3CC), (((temp_r3 & 0x100000) == 0) == 0)) || (temp_r3 & 4)) {
            *(s32 *)((s8 *)arg0 + 0x3CC) = (s32) (*(s32 *)((s8 *)arg0 + 0x3CC) | 4);
            if (((VObj_14_c143b1 *)(arg0 + (1044)))->m5() != 0) {
                *(s32 *)((s8 *)arg0 + 0x3C0) = 0;
                *(s32 *)((s8 *)arg0 + 0x3CC) = (s32) (*(s32 *)((s8 *)arg0 + 0x3CC) & 0xFFEFFFFB);
                *(s32 *)((s8 *)arg0 + 0x3CC) = (s32) (*(s32 *)((s8 *)arg0 + 0x3CC) | 0x40000);
                ((TObjCollidable *)arg0)->clear_player_status_flag(0, 0x08000000);
            }
        }
        if ((s16) *(s16 *)((s8 *)arg0 + 0x326) == 0x11) {
            transition_enemy_state__9TObjEneDDFl(arg0, 0x12);
        }
    } else {
        temp_r3_2 = *(s32 *)((s8 *)arg0 + 0x3CC);
        if (!(temp_r3_2 & 0x100000) && !(temp_r3_2 & 4) && (TObjEneMe3SinowZoa__sub_800D72A4(arg0 + 0x414) != 0)) {
            if ((s32) *(s32 *)((s8 *)arg0 + 0x3C0) != 0) {
                if (((VObj_14_c143b1 *)(arg0 + (1044)))->m4() != 0) {
                    *(s32 *)((s8 *)arg0 + 0x3CC) = (s32) (*(s32 *)((s8 *)arg0 + 0x3CC) | 0x40000);
                    ((TObjCollidable *)arg0)->set_indexed_flags(0, 0x08000000);
                }
            } else if (((VObj_14_c143b1 *)(arg0 + (1044)))->m5() != 0) {
                *(s32 *)((s8 *)arg0 + 0x3CC) = (s32) (*(s32 *)((s8 *)arg0 + 0x3CC) | 0x40000);
                ((TObjCollidable *)arg0)->clear_player_status_flag(0, 0x08000000);
            }
        }
    }
}

void TObjEneMe3SinowZoa::vfunc_28() {  }

void TObjEneMe3SinowZoa::vfunc_63() { if (*(short*)((char*)this + 0x326) != 15) { ((int (*)(void*, void*))transition_enemy_state__9TObjEneDDFl)(this, (void*)15); } }

void TObjEneMe3SinowZoa::vfunc_62() {
    u8 *arg0 = (u8 *)this;
    if (*(s32 *)((s8 *)arg0 + 0x3CC) & 1) {
        ((TObjEneDD *)arg0)->clear_attack_receipts();
        if (((s32) *(s32 *)((s8 *)arg0 + 0x3C0) == 1) && (random_ratio__9TObjCharaFv((s32) arg0) <= *(f32 *)((s8 *)arg0 + 0x3F0))) {
            ((int (*)(void*, void*))transition_enemy_state__9TObjEneDDFl)(arg0, (void*)(0x12));
        }
    } else if ((s16) *(s16 *)((s8 *)arg0 + 0x326) != 0xE) {
        ((int (*)(void*, void*))transition_enemy_state__9TObjEneDDFl)(arg0, (void*)(0xE));
    }
}

void TObjEneMe3SinowZoa::vfunc_61() {  }

void TObjEneMe3SinowZoa::copy_pos_with_height_offset() {
    u8 *arg0 = (u8 *)this;
    VecCopy((Vec *)(arg0 + 0x2FC), (const Vec *)(arg0 + 0x38));
    *(f32 *)((s8 *)arg0 + 0x300) = (f32) (*(f32 *)((s8 *)arg0 + 0x300) + (TObjEneMe3SinowZoa__data_805DF2FC + *(f32 *)((s8 *)arg0 + 0x3E4)));
    VecCopy((Vec *)(arg0 + 0x74), (const Vec *)(arg0 + 0x38));
}

void TObjEneMe3SinowZoa::vfunc_88() {
    *(f32 *)((s8 *)(*(void **)((s8 *)this + 0xA4)) + 4) = (f32) (*(f32 *)((s8 *)this + 0x300) - *(f32 *)((s8 *)this + 0x3C));
}

void TObjEneMe3SinowZoa::vfunc_95() { vfunc_95__9TObjEneDDFv(this); sub_800F5874((s32)((void*)38)); }

void TObjEneMe3SinowZoa::vfunc_96() { vfunc_96__9TObjEneDDFv(this); sub_800F5864((s32)((void*)38)); }

void TObjEneMe3SinowZoa::setup_move_bounds() {
    if (((s32 (*)(void))sub_8031A4D0__18TObjEneMe3SinowZoaFv)() != 0) {
        *(s32 *)((s8 *)this + 0x3C0) = 1;
    } else {
        *(s32 *)((s8 *)this + 0x3C0) = 0;
    }
    *(s32 *)((s8 *)this + 0x3C4) = ((s32 (*)(void *))is_outside_visible_range__18TObjEneMe3SinowZoaFv)(this);
    if ((s32) *(s32 *)((s8 *)this + 0x3C4) == 1) {
        *(s16 *)((s8 *)this + 0xB8) = 2;
    } else {
        *(s16 *)((s8 *)this + 0xB8) = 0;
    }
    *(f32 *)((s8 *)this + 0x3E8) = (f32) (lbl_805DF388 + *(f32 *)((s8 *)this + 0x35C));
    *(f32 *)((s8 *)this + 0x3EC) = (f32) (0.3f + *(f32 *)((s8 *)this + 0x358));
    *(f32 *)((s8 *)this + 0x3F0) = (f32) (lbl_805DF38C + *(f32 *)((s8 *)this + 0x364));
    *(f32 *)((s8 *)this + 0x3F4) = (f32) (lbl_805DF304 + *(f32 *)((s8 *)this + 0x360));
    *(s32 *)((s8 *)this + 0x400) = (s32) *(s32 *)((s8 *)this + 0x368);
}

#pragma fp_contract on
f32 TObjEneMe3SinowZoa::get_node_height() {
    Obj_800E75AC *self = (Obj_800E75AC *)this;
    Vec_800E75AC v;
    Node_800E75AC *node;
    v.x = TObjEneMe3SinowZoa__data_805DF31C;
    v.y = TObjEneMe3SinowZoa__data_805DF31C;
    v.z = TObjEneMe3SinowZoa__data_805DF31C;
    push_matrix_from(identity_matrix);
    bind_motion_context((NJS_MOTION *)self->ff8, self->fc0);
    node = self->node;
    compose_motion_node_matrix(node);
    compose_motion_node_matrix(node->child);
    matrix_mult_vec(0, &v, &v);
    pop_matrix();
    return v.y;
}

u8 TObjEneMe3SinowZoa::check_body_collision_at(s32 arg1, f32 farg0) {
    f32 f2 = farg0 * lbl_805DF304;
    Sub_800E750C *s = ((Obj_800E750C *)this)->fA4;
    u8 res;
    s32 a = ((Obj_800E750C *)this)->f60;
    s32 b = s->f18;
    s->f0 = TObjEneMe3SinowZoa__data_805DF31C;
    s->f8 = f2;
    s->fC = f2;
    s->f10 = TObjEneMe3SinowZoa__data_805DF2FC;
    s->f14 = 1;
    s->f18 = 0x9D01;
    ((Obj_800E750C *)this)->f60 = arg1;
    ((void (*)(void *, s32, f32, f32))check_enemy_body_collisions)(this, arg1, TObjEneMe3SinowZoa__data_805DF31C, f2);
    res = (s->f18 & 0x380000) != 0;
    copy_collision_body((CollisionBody *)s, (const CollisionBody *)sinow_zoa_collision_parts);
    s->f18 = b;
    ((Obj_800E750C *)this)->f60 = a;
    return res;
}

bool TObjEneMe3SinowZoa__sub_8031A820(u8 *ene_dd) {
    f32 temp_f31;
    if (fabs_float(*(f32 *)((s8 *)(*(u8 **)((s8 *)ene_dd + 0x390)) + 0x3C) - *(f32 *)((s8 *)ene_dd + 0x3C)) >= TObjEneMe3SinowZoa__data_805DF320) {
        if (random_ratio__9TObjCharaFv((s32) ene_dd) <= *(f32 *)((s8 *)ene_dd + 0x3F4)) {
            transition_enemy_state__9TObjEneDDFl(ene_dd, 0xC);
            goto block_4;
        }
        return 0;
    }
block_4:
    if (*(f32 *)((s8 *)ene_dd + 0x3AC) > lbl_805DF350) {
        return 0;
    }
    temp_f31 = (*(f32 *)((s8 *)ene_dd + 0x3A0) * sin_table_lookup(*(s32 *)((s8 *)ene_dd + 0x60))) + (*(f32 *)((s8 *)ene_dd + 0x3A8) * cos_table_lookup(*(s32 *)((s8 *)ene_dd + 0x60)));
    return (temp_f31 < cos_table_lookup(0x1E00)) == 0;
}

#pragma fp_contract off
void TObjEneMe3SinowZoa::vfunc_105() {
    f32 damage;
    s32 near;
    TObjPlayer *player;
    near = is_passing_frame( lbl_805DF2F8);
    if (is_passing_frame( TObjEneMe3SinowZoa__data_805DF2F0) != 0 || near != 0) {
        if (enemy_check_target_valid() != 0) {
            if (((TObjChara *)target)->select_melee_contact_body(this, TObjEneMe3SinowZoa__data_805DF2F4) != 0) {
                damage = ((TObjChara *)target)->receive_physical_attack(this, TObjEneMe3SinowZoa__data_805DF2F4);
                ((TObjChara *)target)->apply_knockback_from_attacker((u8 *)this, TObjEneMe3SinowZoa__data_805DF328);
                if (damage > TObjEneMe3SinowZoa__data_805DF31C) {
                    if (sub_8031A454() != 0) {
                        player = (TObjPlayer *)target;
                        if (is_locally_controlled__10TObjPlayerFPv(player) != 0 && get_item_field_6__10TObjPlayerFPv(player) != 0) {
                            send_6x26_unequip_item__10TObjPlayerFPvPv(player, get_item_id__5TItemFv());
                            player->get_hand_joint_position((s32)&strike_position);
                            spawn_particle_effect(&strike_position, 0x1D0);
                        }
                    } else if (near != 0 && random_ratio() <= lbl_805DF384) {
                        TObjEneDD__sub_800BA438((u8 *)this, target);
                    }
                }
            }
        }
        play_sound_effect(0x4003AA2B, &position, 0, 0);
    }
}

void TObjEneMe3SinowZoa::vfunc_108() {  }

u8 TObjEneMe3SinowZoa::is_target_in_range() {
    f32 temp_f1;
    s32 var_r31;

    var_r31 = 0;
    if (!(*(s32 *)((s8 *)this + 0x3CC) & 0x10000)) {
        temp_f1 = *(f32 *)((s8 *)this + 0x3AC);
        if ((temp_f1 > lbl_805DF37C) && (temp_f1 < lbl_805DF380) && (((s32 (*)(void *, s32, f32))check_body_collision_at__18TObjEneMe3SinowZoaFlf)(this, *(s32 *)((s8 *)this + 0x60), temp_f1 - (*(f32 *)&TObjEneMe3SinowZoa__data_805DF320)) == 0)) {
            var_r31 = 1;
        }
    }
    return (u8)var_r31;
}

void TObjEneMe3SinowZoa::vfunc_107() {  }

s32 TObjEneMe3SinowZoa::try_run_effect_m6() {
    u8 *arg0 = (u8 *)this;

    if (*(s32 *)((s8 *)arg0 + 0x3CC) & 4) {
        ((VObj8031A5E0*)(arg0 + 0x414))->m6();
        return 1;
    }
    return 0;
}

s32 TObjEneMe3SinowZoa::try_run_effect_m7() {
    u8 *arg0 = (u8 *)this;

    if (*(s32 *)((s8 *)arg0 + 0x3CC) & 4) {
        ((VObj8031A598*)(arg0 + 0x414))->m7();
        return 1;
    }
    return 0;
}

void TObjEneMe3SinowZoa::vfunc_111() {  }

void TObjEneMe3SinowZoa::vfunc_112() {  }

void TObjEneMe3SinowZoa::update_distance_state() {
    VObj_8031A538 *o = (VObj_8031A538 *)this;
    f32 thr = lbl_805DF378;
    if ((*(f32 *)((s8 *)this + 0x3E0) - *(f32 *)((s8 *)this + 0x3C)) > thr) {
        o->m95();
        return;
    }
    o->m96();
}

void TObjEneMe3SinowZoa::vfunc_89() {
    struct VObj_8031A4E8 *o = (struct VObj_8031A4E8 *)this;
    o->m86();
    ((TObjPlayer *)this)->check_object_collisions();
    check_enemy_body_collisions(this);
    ((TObjPlayer *)this)->update_enemy_collision_flags();
}

s32 TObjEneMe3SinowZoa::sub_8031A4D0() {
    return *(f32 *)((s8 *)((u8 *)this) + 0x354) < TObjEneMe3SinowZoa__data_805DF32C;
}

s32 TObjEneMe3SinowZoa::is_outside_visible_range() {
    T_8031A494 *self = (T_8031A494 *)this;
    bool r = false;
    if (self->f354 < (*(f32 *)&TObjEneMe3SinowZoa__data_805DF2F4) ||
        (self->f354 >= (*(f32 *)&TObjEneMe3SinowZoa__data_805DF32C) && self->f354 < (*(f32 *)&TObjEneMe3SinowZoa__data_805DF328))) r = true;
    return r;
}

s32 TObjEneMe3SinowZoa::vfunc_104(f32 value) { return TObjEneDD_ST::select_and_apply_target(value); }

s32 TObjEneMe3SinowZoa::sub_8031A454() {
    return (u8) (*(s32 *)((s8 *)((u8 *)this) + 0x400) >= 1);
}

void TObjEneMe3SinowZoa::sub_8031A3D8() {
    if (((s32 (*)(void *))sub_8031A454__18TObjEneMe3SinowZoaFv)(this) != 0) {
        *(s32 **)((s8 *)((u8 *)this) + 0x24) = (s32 *)&lbl_80542FDC;
        initialize_enemy_state__9TObjEneDDFl(this, 0x46);
        *(s32 *)((s8 *)((u8 *)this) + 0x3C8) = 1;
        return;
    }
    *(s32 **)((s8 *)((u8 *)this) + 0x24) = (s32 *) *(s32 **)((s8 *)(*(u8 **)((s8 *)TObjEneMe3SinowZoa__data_805D6AD8 + 0x42C)) + 0xC);
    initialize_enemy_state__9TObjEneDDFl(this, 0x45);
    *(s32 *)((s8 *)((u8 *)this) + 0x3C8) = 0;
}

void cast_technique__18TObjEneMe3SinowZoaFPv(u8 *arg0) {
    s32 lv;
    lv = TObjEneDD::clamp_frame_index(((Param_8031A2A0 * *)TObjEneMe3SinowZoa__kind_param_tbls)[*(s32 *)((s8 *)arg0 + 0x3C8)]->level);
    if (((s32 (*)(void *))sub_8031A454__18TObjEneMe3SinowZoaFv)(arg0) != 0) {
        if (game_difficulty_selection == 3) {
            TTecSifta::create((void *)arg0, arg0 + 0x38, (void *)(TObjEneDD::clamp_frame_index(((Param_8031A2A0 * *)TObjEneMe3SinowZoa__kind_param_tbls)[*(s32 *)((s8 *)arg0 + 0x3C8)]->level)));
            create__10TTecDebandFlll(arg0, arg0 + 0x38, TObjEneDD::clamp_frame_index(((Param_8031A2A0 * *)TObjEneMe3SinowZoa__kind_param_tbls)[*(s32 *)((s8 *)arg0 + 0x3C8)]->level));
        } else {
            create_instance__9TTecZaruaFllll(arg0, arg0 + 0x38, arg0 + 0x38, TObjEneDD::clamp_frame_index(((Param_8031A2A0 * *)TObjEneMe3SinowZoa__kind_param_tbls)[*(s32 *)((s8 *)arg0 + 0x3C8)]->level));
            create__9TTecJelinFllll(arg0, arg0 + 0x38, arg0 + 0x38, TObjEneDD::clamp_frame_index(((Param_8031A2A0 * *)TObjEneMe3SinowZoa__kind_param_tbls)[*(s32 *)((s8 *)arg0 + 0x3C8)]->level));
        }
    } else {
        TTecResta::create((void *)arg0, arg0 + 0x38, (void *)lv);
    }
}

void TObjEneMe3SinowZoa::dispatch_action(u32 arg1, s32 arg2) {
    u8 *arg0 = (u8 *)this;
    switch (arg1) {
    case 0:
        state_action(arg2);
        return;
    case 1:
        ((TObjEneMe3SinowZoa *)arg0)->sub_80319E74(arg2);
        return;
    case 3:
        ((s32 (*)(void *, s32))TObjEneMe3SinowZoa__sub_80319B8C)(arg0, arg2);
        return;
    case 2:
        ((TObjEneMe3SinowZoa *)arg0)->state_chase(arg2);
        return;
    case 4:
        ((TObjEneMe3SinowZoa *)arg0)->update_state_action(arg2);
        return;
    case 5:
        ((s32 (*)(void *, s32))TObjEneMe3SinowZoa__sub_80319748)(arg0, arg2);
        return;
    case 6:
        ((TObjEneMe3SinowZoa *)arg0)->state_chase_target(arg2);
        return;
    case 7:
        TObjEneMe3SinowZoa__sub_80318F7C((Ene_80318F7C *)arg0, arg2);
        return;
    case 8:
        TObjEneMe3SinowZoa__sub_80318C0C(arg0, arg2);
        return;
    case 9:
        TObjEneMe3SinowZoa__sub_8031884C(arg0, arg2);
        return;
    case 13:
        ((TObjEneMe3SinowZoa *)arg0)->handle_state_substate(arg2);
        return;
    case 10:
        TObjEneMe3SinowZoa__sub_803182F8(arg0, arg2);
        return;
    case 11:
        TObjEneMe3SinowZoa__sub_80318564(arg0, arg2);
        return;
    case 14:
        ((TObjEneMe3SinowZoa *)arg0)->state_knockback(arg2);
        return;
    case 15:
        ((s32 (*)(void *, s32))TObjEneMe3SinowZoa__sub_80317F90)(arg0, arg2);
        return;
    case 12:
        TObjEneMe3SinowZoa__sub_80317B50(arg0, arg2);
        return;
    case 16:
        fn_80316C3C__18TObjEneMe3SinowZoaFl(arg0, arg2);
        return;
    case 17:
        fn_80317254__18TObjEneMe3SinowZoaFl(arg0, arg2);
        return;
    case 18:
        fn_803170F0__18TObjEneMe3SinowZoaFl(arg0, arg2);
    default:
        return;
    }
}

void TObjEneMe3SinowZoa::state_action(s32 arg1) {
    u8 *ene_me3_sinow_zoa = (u8 *)this;
    s32 temp_r3;
    s32 temp_r4;

    switch (arg1) {
    case 4:
        if ((s32) *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3C4) == 1) {
            *(s16 *)((s8 *)ene_me3_sinow_zoa + 0xB8) = 2;
            ((TObjEneDD *)ene_me3_sinow_zoa)->set_field_378(1);
        } else {
            *(s16 *)((s8 *)ene_me3_sinow_zoa + 0xB8) = 0;
            ((TObjEneDD *)ene_me3_sinow_zoa)->set_field_378(3);
        }
        ((TObjEneMe3SinowZoa *)ene_me3_sinow_zoa)->vfunc_95();
        temp_r4 = *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC);
        *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC) = (s32) (temp_r4 | 2);
        temp_r3 = *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC);
        *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC) = (s32) (temp_r3 & 0xFFEFFFFA);
        if (check_v2_mode__9TObjEneDDFv(temp_r3, temp_r4) != 0) {
            *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC) = (s32) (*(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC) & 0xFFFEFFFF);
        }
        *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x434) = 0;
        VecCopy((Vec *)(ene_me3_sinow_zoa + 0x38), (const Vec *)(ene_me3_sinow_zoa + 0x50));
        VecCopy((Vec *)(ene_me3_sinow_zoa + 0x44), (const Vec *)(ene_me3_sinow_zoa + 0x50));
        VecCopy((Vec *)(ene_me3_sinow_zoa + 0x2FC), (const Vec *)(ene_me3_sinow_zoa + 0x50));
        *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E0) = (f32) *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3C);
        *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3F8) = 0;
        *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3FC) = 0;
        return;
    case 3:
        if ((s32) *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x434) > 5) {
            if ((s32) *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3C4) == 1) {
                ((s32 (*)(void *, s32))transition_enemy_state__9TObjEneDDFl)(ene_me3_sinow_zoa, 1);
            } else {
                ((s32 (*)(void *, s32))transition_enemy_state__9TObjEneDDFl)(ene_me3_sinow_zoa, 3);
            }
        }
    case 5:
        return;
    case 0:
        *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x434) = (s32) (*(s32 *)((s8 *)ene_me3_sinow_zoa + 0x434) + 1);
        if ((s32) *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x434) == 1) {
            *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E0) = (f32) *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3C);
            ((TObjEneMe3SinowZoa *)ene_me3_sinow_zoa)->vfunc_102();
            *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E4) = (f32) (*(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E0) - *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3C));
        }
        break;
    }
}

void TObjEneMe3SinowZoa::sub_80319E74(s32 arg1) {
    Vec_80319E74 v;
    f32 t;
    u8 *arg0 = (u8 *)this;
    switch (arg1) {
    case 4:
        *(s16 *)((s8 *)arg0 + 0xB8) = 2;
        ((TObjEneDD *)arg0)->set_field_378(0);
        ((TObjEneMe3SinowZoa *)arg0)->vfunc_95();
        *(s32 *)((s8 *)arg0 + 0x3CC) &= 0xFFEFFFFD;
        *(s32 *)((s8 *)arg0 + 0x3CC) |= 5;
        ((TUnk_80494938 *)(arg0 + 0x414))->start_fade_in();
        VecCopy((Vec *)&v, (const Vec *)(arg0 + 0x38));
        t = *(f32 *)((s8 *)arg0 + 0x3E0);
        v.y = t - TObjEneMe3SinowZoa__data_805DF320;
        if (*(s32 *)((s8 *)arg0 + 0x3C0) == 0) {
            TBoss3Volopt__sub_800D8D88(&v, t);
        } else {
            create_timed_particle_emitter(arg0 + 0x38, 0x79, 0, 0xF);
        }
        break;
    case 3:
        if (((VObj_14_948132 *) (arg0 + 0x414))->m5() != 0) {
            if (*(s32 *)((s8 *)arg0 + 0x3C0) == 1) {
                transition_enemy_state__9TObjEneDDFl(arg0, 2);
            } else {
                transition_enemy_state__9TObjEneDDFl(arg0, 0xD);
            }
        }
        break;
    case 0:
        if (*TBoss3Volopt__sub_800F059C(arg0 + 0x414) >= lbl_805DF374) {
            ((TObjMotion *)arg0)->advance_animation();
        }
        ((TObjEneMe3SinowZoa *)arg0)->vfunc_102();
        ((TObjEneMe3SinowZoa *)arg0)->vfunc_89();
        break;
    case 5:
        *(s32 *)((s8 *)arg0 + 0x3CC) &= ~4;
        break;
    }
}

#pragma fp_contract on
void TObjEneMe3SinowZoa::state_chase(s32 arg1) {
#define arg0 ((u8 *)this)
    s32 temp_r0;
    s32 temp_r4;

    switch (arg1) {
    case 4:
        *(s16 *)((s8 *)arg0 + 0xB8) = 9;
        ((TObjEneDD *)arg0)->set_field_378(0xD);
        ((VObj_18_bb4b7f *)(arg0))->m94();
        *(s32 *)((s8 *)arg0 + 0x3CC) = (s32) (*(s32 *)((s8 *)arg0 + 0x3CC) & 0xFFEFFFF8);
        *(s32 *)((s8 *)arg0 + 0x434) = 0;
        *(s32 *)((s8 *)arg0 + 0x438) = 0;
        *(f32 *)((s8 *)arg0 + 0x444) = (f32) TObjEneMe3SinowZoa__data_805DF31C;
        return;
    case 3:
        if (((VObj_18_bb4b7f *)(arg0))->m102(TObjEneMe3SinowZoa__data_805DF324) != 0) {
            if (*(f32 *)((s8 *)arg0 + 0x3AC) <= lbl_805DF36C) {
                transition_enemy_state__9TObjEneDDFl(arg0, 0xD);
                return;
            }
            temp_r0 = *(s32 *)((s8 *)arg0 + 0x438) - 1;
            *(s32 *)((s8 *)arg0 + 0x438) = temp_r0;
            if ((temp_r0 <= 0) && (((VObj_18_bb4b7f *)(arg0))->m104() != 0)) {
                *(s32 *)((s8 *)arg0 + 0x438) = 0x3C;
                if (((f32 (*)(void *))random_ratio__9TObjCharaFv)(arg0) <= lbl_805DF370) {
                    transition_enemy_state__9TObjEneDDFl(arg0, 7);
                    return;
                }
            }
        } else if ((s32) *(s32 *)((s8 *)arg0 + 0x434) >= 0xE10) {
            transition_enemy_state__9TObjEneDDFl(arg0, 0xD);
            return;
        }
        break;
    case 5:
        break;
    case 0:
        (*(s32 *)((s8 *)arg0 + 0x434))++;
        ((TObjMotion *)arg0)->advance_animation();
        if (((TObjEneDD_ST *)arg0)->update_linked_position(TObjEneMe3SinowZoa__data_805DF324) != 0) {
            ((TObjEneDD_ST *)arg0)->enemy_copy_target_destination();
            ((TObjEneDD *)arg0)->update_velocity();
            *(f32 *)((s8 *)arg0 + 0x444) = (f32) ((*(f32 *)((s8 *)arg0 + 0x3A0) * sin_table_lookup((int) (*(s32 *)((s8 *)arg0 + 0x60)))) + (*(f32 *)((s8 *)arg0 + 0x3A8) * cos_table_lookup((int) (*(s32 *)((s8 *)arg0 + 0x60)))));
            if (*(f32 *)((s8 *)arg0 + 0x444) < cos_table_lookup(0x1000)) {
                ((TObjEneDD *)arg0)->turn_toward_target_direction(0x500);
                ((VObj_18_bb4b7f *)(arg0))->m100();
            }
        }
        ((VObj_18_bb4b7f *)(arg0))->m87();
        break;
    }
}

#undef arg0
void TObjEneMe3SinowZoa__sub_80319B8C(u8 *ene_dd, s32 arg1) {
    typedef char sp8_offset[(offsetof(Stack_80319B8C, sp8) == 0x0) ? 1 : -1];
    typedef char spC_offset[(offsetof(Stack_80319B8C, spC) == 0x4) ? 1 : -1];
    Stack_80319B8C stack;
    f32 temp_f1;
    switch (arg1) {
    case 4:
        *(s16 *)((s8 *)ene_dd + 0xB8) = 0;
        ((TObjEneDD *)ene_dd)->set_field_378(0);
        ((TObjEneDD *)(ene_dd))->vfunc_95();
        *(s32 *)((s8 *)ene_dd + 0x3CC) = (s32) (*(s32 *)((s8 *)ene_dd + 0x3CC) | 7);
        ((TUnk_80494938 *)(ene_dd + 0x414))->start_fade_in();
        VecCopy((Vec *)(&stack.sp8), (const Vec *)(ene_dd + 0x38));
        temp_f1 = *(f32 *)((s8 *)ene_dd + 0x3E0);
        stack.spC = temp_f1 - TObjEneMe3SinowZoa__data_805DF314;
        TBoss3Volopt__sub_800D8D88(&stack.sp8, temp_f1);
        break;
    case 3:
        if (((VObj_14_948132 *)(ene_dd + (1044)))->m5() != 0) {
            transition_enemy_state__9TObjEneDDFl(ene_dd, 4);
            break;
        }
    case 0:
        break;
    case 5:
        *(s32 *)((s8 *)ene_dd + 0x3CC) = (s32) (*(s32 *)((s8 *)ene_dd + 0x3CC) & 0xFFFFFFFB);
        break;
    }
}

#pragma fp_contract off
void TObjEneMe3SinowZoa::update_state_action(s32 arg1) {
    switch (arg1) {
    case 4:
        *(s16 *)((s8 *)this + 0xB8) = 0;
        set_field_378(5);
        this->vfunc_95();
        *(u32 *)((s8 *)this + 0x3CC) &= 0xFFEFFFF8;
        *(s32 *)((s8 *)this + 0x434) = 0;
        *(s32 *)((s8 *)this + 0x438) = 0;
        break;
    case 3:
        if (*(s32 *)((s8 *)this + 0x434) > 0x1E) {
            transition_enemy_state__9TObjEneDDFl(this, 5);
        }
        break;
    case 0:
        advance_animation();
        if (*(s32 *)((s8 *)this + 0x434) == 0) {
            if (update_linked_position(TObjEneMe3SinowZoa__data_805DF324) != 0) {
                *(s32 *)((s8 *)this + 0x434) = 1;
                *(u32 *)((s8 *)this + 0x3F8) = 0x1C00FFFF;
                *(u32 *)((s8 *)this + 0x3F8) &= lbl_805DF368;
                *(s32 *)((s8 *)this + 0x438) = 0;
            }
        } else {
            (*(s32 *)((s8 *)this + 0x434))++;
            *(s32 *)((s8 *)this + 0x438) += 0x10;
            if (*(s32 *)((s8 *)this + 0x438) > 0xFF) {
                *(s32 *)((s8 *)this + 0x438) = 0xFF;
            }
            *(u32 *)((s8 *)this + 0x3F8) = (*(s32 *)((s8 *)this + 0x438) << 24) | (*(u32 *)((s8 *)this + 0x3F8) & 0xFFFFFF);
            if (enemy_validate_retained_target((u8 *)this) == 0) {
                *(s32 *)((s8 *)this + 0x434) = 0;
                *(s32 *)((s8 *)this + 0x3F8) = 0;
            }
        }
        this->vfunc_102();
        update_distance_state();
        this->vfunc_89();
        *(f32 *)((s8 *)this + 0x3E4) = *(f32 *)((s8 *)this + 0x3E0) - *(f32 *)((s8 *)this + 0x3C);
        break;
    case 5:
        *(s32 *)((s8 *)this + 0x3F8) = 0x1C00FFFF;
        *(f32 *)((s8 *)this + 0x3E4) = TObjEneMe3SinowZoa__data_805DF31C;
        break;
    }
}

void TObjEneMe3SinowZoa__sub_80319748(u8 *ene_me3_sinow_zoa, s32 arg1) {
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f31;

    switch (arg1) {
    case 4:
        *(s16 *)((s8 *)ene_me3_sinow_zoa + 0xB8) = 1;
        ((TObjEneDD *)ene_me3_sinow_zoa)->set_field_378(0xD);
        ((TObjEneDD *)(ene_me3_sinow_zoa))->vfunc_96();
        *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC) = (s32) (*(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC) & 0xFFEFFFF9);
        *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC) = (s32) (*(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC) | 1);
        *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x434) = 0;
        *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x440) = (f32) TObjEneMe3SinowZoa__data_805DF31C;
        if (((TObjEneDD_ST *)ene_me3_sinow_zoa)->enemy_has_live_target() != 0) {
            ((TObjEneDD_ST *)ene_me3_sinow_zoa)->enemy_copy_target_destination();
            ((TObjEneDD *)ene_me3_sinow_zoa)->update_velocity();
        }
        break;
    case 3:
        if ((s32) *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x434) == 3) {
            transition_enemy_state__9TObjEneDDFl(ene_me3_sinow_zoa, 0xD);
        }
        break;
    case 0:
        switch (*(s32 *)((s8 *)ene_me3_sinow_zoa + 0x434)) {
        case 0:
            temp_f31 = ((TObjEneMe3SinowZoa *)ene_me3_sinow_zoa)->get_node_height();
            ((TObjMotion *)ene_me3_sinow_zoa)->advance_animation();
            *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x444) = ((TObjEneMe3SinowZoa *)ene_me3_sinow_zoa)->get_node_height();
            *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E0) = (f32) (*(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E0) + (temp_f31 - *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x444)));
            *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x434) = 1;
            *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E4) = (f32) (*(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E0) - *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3C));
            break;
        case 1:
            ((TObjMotion *)ene_me3_sinow_zoa)->advance_animation();
            if (*(f32 *)((s8 *)ene_me3_sinow_zoa + 0xC0) > 29.0f) {
                *(f32 *)((s8 *)ene_me3_sinow_zoa + 0xC0) = 29.0f;
            }
            *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x440) -= 0.3f;
            if (*(f32 *)((s8 *)ene_me3_sinow_zoa + 0x440) < -5.0f) {
                *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x440) = -5.0f;
            }
            *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E0) = (f32) (*(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E0) + *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x440));
            temp_f1 = ((TObjEneMe3SinowZoa *)ene_me3_sinow_zoa)->get_node_height();
            *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E0) = (f32) (*(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E0) - (temp_f1 - *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x444)));
            *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x444) = temp_f1;
            if (*(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E0) < *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3C)) {
                *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E0) = *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3C);
                *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x434) = 2;
                play_sound_effect(0x4003A82A, ene_me3_sinow_zoa + 0x38, 0, 0);
                ((TObjEneMe3SinowZoa *)ene_me3_sinow_zoa)->check_and_notify();
            }
            break;
        case 2:
            if (((TObjEneDD *)ene_me3_sinow_zoa)->get_flag_b4() != 0) {
                *(s16 *)((s8 *)ene_me3_sinow_zoa + 0xB8) = 9;
                *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x434) = 3;
                *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E0) = (f32) *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3C);
                *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E4) = (f32) TObjEneMe3SinowZoa__data_805DF31C;
            }
            ((TObjMotion *)ene_me3_sinow_zoa)->advance_animation();
            break;
        }
        ((TObjEneDD *)(ene_me3_sinow_zoa))->vfunc_102();
        ((TObjEneMe3SinowZoa *)ene_me3_sinow_zoa)->update_distance_state();
        ((TObjEneDD *)(ene_me3_sinow_zoa))->vfunc_89();
        *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E4) = (f32) (*(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E0) - *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3C));
        break;
    case 5:
        *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC) = (s32) (*(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC) & 0xFFFFFFFE);
        *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E4) = (f32) TObjEneMe3SinowZoa__data_805DF31C;
        break;
    }
}

#pragma fp_contract on
void TObjEneMe3SinowZoa::state_chase_target(s32 arg1) {
    u8 *arg0 = (u8 *)this;
    switch (arg1) {
    case 4:
        *(s16 *)((s8 *)arg0 + 0xB8) = 0xA;
        ((TObjEneDD *)arg0)->set_field_378(6);
        this->vfunc_96();
        *(s32 *)((s8 *)arg0 + 0x3CC) = (s32) (*(s32 *)((s8 *)arg0 + 0x3CC) & 0xFFEFFFF8);
        *(f32 *)((s8 *)arg0 + 0x3AC) = (f32) 300.0f;
        *(f32 *)((s8 *)arg0 + 0x440) = *(f32 *)TObjEneMe3SinowZoa__kind_param_tbls[*(s32 *)((s8 *)arg0 + 0x3C8)];
        *(f32 *)((s8 *)arg0 + 0x444) = (f32) TObjEneMe3SinowZoa__data_805DF31C;
        return;
    case 3:
        if ((u32) *(u32 *)((s8 *)arg0 + 0x390) == 0U) {
            this->vfunc_111();
            transition_enemy_state__9TObjEneDDFl(arg0, 0xD);
            return;
        }
        if (((s32 (*)(f32))TObjEneMe3SinowZoa__sub_8031A820)((f32) (*(f32 *)((s8 *)arg0 + 0x444))) != 0) {
            transition_enemy_state__9TObjEneDDFl(arg0, 8);
            return;
        }
        if (((VObj_18_e66632 *)(arg0))->m104() != 0) {
            transition_enemy_state__9TObjEneDDFl(arg0, 7);
        }
    case 5:
        return;
    case 0:
        ((TObjMotion *)arg0)->advance_animation();
        if (((TObjEneDD_ST *)arg0)->update_linked_position(TObjEneMe3SinowZoa__data_805DF324) != 0) {
            ((TObjEneDD_ST *)arg0)->enemy_copy_target_destination();
            ((TObjEneDD *)arg0)->update_velocity();
            TObjEneMe3SinowZoa__sub_80316840(arg0);
            *(f32 *)((s8 *)arg0 + 0x444) = (f32) ((*(f32 *)((s8 *)arg0 + 0x3A0) * sin_table_lookup((s32)((int) (*(s32 *)((s8 *)arg0 + 0x60))))) + (*(f32 *)((s8 *)arg0 + 0x3A8) * cos_table_lookup((s32)((int) (*(s32 *)((s8 *)arg0 + 0x60))))));
            if (*(f32 *)((s8 *)arg0 + 0x444) < cos_table_lookup(0x1000)) {
                ((TObjEneDD *)arg0)->turn_toward_target_direction(0x500);
                this->vfunc_102();
            } else {
                enemy_turn_and_move_on_ground((arg0), 0x500, (f32) (*(f32 *)((s8 *)arg0 + 0x440)));
            }
            this->vfunc_89();
        }
        break;
    }
}

void TObjEneMe3SinowZoa__sub_80318F7C(Ene_80318F7C *self, s32 arg1) {
    switch (arg1) {
    case 4:
        self->fB8 = 6;
        ((TObjEneDD *)self)->set_field_378(6);
        self->m94();
        self->f3CC &= 0xFFEFFFF8;
        self->f3CC |= 0x10000;
        self->f434 = 0;
        self->f440 = TObjEneMe3SinowZoa__data_805DF31C;
        ((TObjEneDD_ST *)self)->set_active();
        break;
    case 3:
        if (self->f434 == 7 || ((TObjEneDD *)self)->get_flag_b4() != 0) {
            if (self->m100() == 0) {
                transition_enemy_state__9TObjEneDDFl(self, 10);
            } else {
                transition_enemy_state__9TObjEneDDFl(self, 6);
            }
        }
        break;
    case 0:
        switch ((u32)self->f434) {
        case 0:
            ((TObjMotion *)self)->advance_animation();
            if (self->fB0 & 8) {
                self->f434 = 1;
            }
            self->m100();
            self->m87();
            break;
        case 1: {
            s32 target;
            ((TObjMotion *)self)->advance_animation();
            if (((TObjEneDD_ST *)self)->check_target_validity() != 0) {
                ((TObjEneDD_ST *)self)->enemy_copy_target_destination();
                ((TObjEneDD *)self)->update_velocity();
                target = (s32)(TObjEneMe3SinowZoa__data_804760A0 * atan2_float(self->f3A0, self->f3A8));
            } else {
                target = self->f60;
            }
            self->f60 = approach_angle_limited(self->f60, target, 0x1000);
            if (((TObjMotion *)self)->is_passing_frame((f32)TObjEneMe3SinowZoa__data_805DF314) != 0) {
                self->f434 = 2;
            }
            self->m100();
            self->m87();
            break;
        }
        case 2:
            ((TObjMotion *)self)->advance_animation();
            if (((TObjEneDD_ST *)self)->check_target_validity() != 0) {
                ((TObjEneDD_ST *)self)->enemy_copy_target_destination();
                ((TObjEneDD *)self)->update_velocity();
            }
            if (self->fC0 + self->fC8 >= lbl_805DF348) {
                if (((s32 (*)(void *, s32, f32))check_body_collision_at__18TObjEneMe3SinowZoaFlf)(self, self->f60, self->f3AC - TObjEneMe3SinowZoa__data_805DF320) != 0) {
                    self->f434 = 7;
                } else {
                    Vec_80318F7C v;
                    f32 d = self->f3AC - TObjEneMe3SinowZoa__data_805DF320;
                    VecCopy((Vec *)&v, (const Vec *)&self->pos);
                    v.x = self->f3A0 * d + v.x;
                    v.y = v.y + TObjEneMe3SinowZoa__data_805DF320;
                    v.z = self->f3A8 * d + v.z;
                    if (csnVecterUnder(&v, 0x15) != 0) {
                        if (self->f28 == ((TScene *)(&v))->find_section_at_position()) {
                            if (self->f3C0 != 0) {
                                ((TUnk_80494938 *)(&self->sub))->set_rate(TObjEneMe3SinowZoa__data_805DF30C);
                                self->sub.m3();
                                self->f3CC |= 0x100000;
                                self->f3CC |= 0x40000;
                                ((TObjCollidable *)self)->clear_player_status_flag(0, 0x08000000);
                                self->f434 = 3;
                            } else {
                                self->f434 = 4;
                            }
                            self->f444 = (self->f3AC - TObjEneMe3SinowZoa__data_805DF320) / lbl_805DF34C;
                            self->m89();
                            play_sound_effect(0x4003A82C, &self->pos, 0, 0);
                        } else {
                            self->f434 = 7;
                        }
                    } else {
                        self->f434 = 7;
                    }
                }
            }
            self->m100();
            self->m87();
            break;
        case 3:
            if (((TUnk_80494938 *)(&self->sub))->advance_timer(TObjEneMe3SinowZoa__data_805DF310) != 0) {
                self->f434 = 4;
            }
        case 4:
            ((TObjMotion *)self)->advance_animation();
            if (self->fC0 + self->fC8 >= lbl_805DF2F8) {
                if (self->f3CC & 0x100000) {
                    self->f434 = 5;
                } else {
                    self->f434 = 6;
                }
                self->m90();
                play_sound_effect(0x4003A82A, &self->pos, 0, 0);
                ((TObjEneMe3SinowZoa *)self)->check_and_notify();
            }
            ((TObjEneDD *)self)->move_with_wall_slide_commit(self->f3A0, self->f3A8, self->f444);
            break;
        case 5:
            if (self->fC0 > TObjEneMe3SinowZoa__data_805DF2F0 && self->sub.m4() != 0) {
                self->f3CC &= ~0x100000;
                self->f434 = 6;
                self->f3CC |= 0x40000;
                ((TObjCollidable *)self)->set_indexed_flags(0, 0x08000000);
            }
        case 6:
            ((TObjMotion *)self)->advance_animation();
            if (((TObjMotion *)self)->is_passing_frame((f32)lbl_805DF350) != 0 && ((TObjEneDD_ST *)self)->enemy_check_target_valid() != 0) {
                if (self->f390->m18(self, TObjEneMe3SinowZoa__data_805DF2F4) != 0) {
                    self->f390->m20(self, TObjEneMe3SinowZoa__data_805DF2F4);
                    self->f390->m23(self, TObjEneMe3SinowZoa__data_805DF328);
                }
            }
            self->f444 *= lbl_805DF354;
            ((TObjEneDD *)self)->move_with_wall_slide_on_ground(self->f3A0, self->f3A8, self->f444);
            self->m87();
            break;
        }
        break;
    case 5:
        self->f3E0 = self->pos.y;
        self->f3E4 = TObjEneMe3SinowZoa__data_805DF31C;
        self->m90();
        ((TObjEneDD *)self)->clear_field_388();
        break;
    }
}

#pragma fp_contract off
#pragma opt_common_subs off
void TObjEneMe3SinowZoa__sub_80318C0C(void *arg0_, s32 arg1) {
    u8 *ene_epsilon = (u8 *)arg0_;
    s32 var_r4;
    f32 temp_f1;

    switch (arg1) {
    case 4:
        *(s16 *)((s8 *)ene_epsilon + 0xB8) = 7;
        ((TObjEneDD *)ene_epsilon)->set_field_378(0xC);
        ((TObjEneEpsilon *)(ene_epsilon))->vfunc_96();
        *(s32 *)((s8 *)ene_epsilon + 0x3CC) = (s32) (*(s32 *)((s8 *)ene_epsilon + 0x3CC) & 0xFFEFFFF8);
        *(s32 *)((s8 *)ene_epsilon + 0x3CC) |= 0x10000;
        *(s32 *)((s8 *)ene_epsilon + 0x3CC) |= 0x40000;
        ((TObjCollidable *)ene_epsilon)->clear_player_status_flag(0, 0x08000000);
        if (*(s32 *)((s8 *)ene_epsilon + 0x3C0) != 0) {
            ((TUnk_80494938 *)(ene_epsilon + 0x414))->set_rate(TObjEneMe3SinowZoa__data_805DF30C);
            ((VObj_14_6ea8ee *)(ene_epsilon + 0x414))->m3();
            *(s32 *)((s8 *)ene_epsilon + 0x3CC) |= 0x100000;
            *(s32 *)((s8 *)ene_epsilon + 0x434) = 0;
        } else {
            *(s32 *)((s8 *)ene_epsilon + 0x434) = 1;
        }
        *(s32 *)((s8 *)ene_epsilon + 0x438) = 0;
        return;
    case 3:
        if (*(s32 *)((s8 *)ene_epsilon + 0x434) == 4) {
            *(s32 *)((s8 *)ene_epsilon + 0x3CC) |= 0x80000;
            ((VObj_18_4f5f2e *)(ene_epsilon))->m105();
        }
        return;
    case 0:
        switch (*(s32 *)((s8 *)ene_epsilon + 0x434)) {
        case 0:
            if (((TUnk_80494938 *)(ene_epsilon + 0x414))->advance_timer(TObjEneMe3SinowZoa__data_805DF310) != 0) {
                *(s32 *)((s8 *)ene_epsilon + 0x434) = 1;
            }
        case 1:
            ((TObjMotion *)ene_epsilon)->advance_animation();
            ((VObj_18_4f5f2e *)(ene_epsilon))->m103();
            if (*(f32 *)((s8 *)ene_epsilon + 0xC0) < TObjEneMe3SinowZoa__data_805DF320) {
                if (((TObjEneDD_ST *)ene_epsilon)->check_target_validity() != 0) {
                    ((TObjEneDD_ST *)ene_epsilon)->enemy_copy_target_destination();
                    ((TObjEneDD *)ene_epsilon)->update_velocity();
                    var_r4 = (s32) (TObjEneMe3SinowZoa__data_804760A0 * atan2_float(*(f32 *)((s8 *)ene_epsilon + 0x3A0), *(f32 *)((s8 *)ene_epsilon + 0x3A8)));
                } else {
                    var_r4 = *(s32 *)((s8 *)ene_epsilon + 0x60);
                }
                *(s32 *)((s8 *)ene_epsilon + 0x60) = approach_angle_limited(*(s32 *)((s8 *)ene_epsilon + 0x60), var_r4, 0x300);
                *(f32 *)((s8 *)ene_epsilon + 0x3A0) = sin_table_lookup(*(s32 *)((s8 *)ene_epsilon + 0x60));
                *(f32 *)((s8 *)ene_epsilon + 0x3A8) = cos_table_lookup(*(s32 *)((s8 *)ene_epsilon + 0x60));
            }
            ((VObj_18_4f5f2e *)(ene_epsilon))->m110();
            TObjEneMe3SinowZoa__sub_80316840(ene_epsilon);
            temp_f1 = *(f32 *)((s8 *)ene_epsilon + 0xC0);
            if (temp_f1 >= TObjEneMe3SinowZoa__data_805DF31C && temp_f1 <= TObjEneMe3SinowZoa__data_805DF308) {
                f32 *rec = (f32 *)TObjEneMe3SinowZoa__kind_param_tbls[*(s32 *)((s8 *)ene_epsilon + 0x3C8)];
                move_to_shot_position__9TObjEneDDFfff(ene_epsilon, rec, *(f32 *)((s8 *)ene_epsilon + 0x3A0), *(f32 *)((s8 *)ene_epsilon + 0x3A8), rec[2]);
            } else {
                ((TObjEneEpsilon *)(ene_epsilon))->vfunc_102();
            }
            if (((TObjEneDD *)ene_epsilon)->get_flag_b4() != 0) {
                *(s32 *)((s8 *)ene_epsilon + 0x434) = 2;
            }
            break;
        case 2:
            *(s32 *)((s8 *)ene_epsilon + 0x438) += 1;
            if (*(s32 *)((s8 *)ene_epsilon + 0x438) >= ((s32 *)TObjEneMe3SinowZoa__kind_param_tbls[*(s32 *)((s8 *)ene_epsilon + 0x3C8)])[8]) {
                if (*(s32 *)((s8 *)ene_epsilon + 0x3CC) & 0x100000) {
                    *(s32 *)((s8 *)ene_epsilon + 0x434) = 3;
                } else {
                    *(s32 *)((s8 *)ene_epsilon + 0x434) = 4;
                }
            }
            ((TObjEneEpsilon *)(ene_epsilon))->vfunc_102();
            break;
        case 3:
            if (((VObj_14_6ea8ee *)(ene_epsilon + 0x414))->m4() != 0) {
                *(s32 *)((s8 *)ene_epsilon + 0x434) = 4;
                *(s32 *)((s8 *)ene_epsilon + 0x3CC) |= 0x40000;
                ((TObjCollidable *)ene_epsilon)->set_indexed_flags(0, 0x08000000);
            }
            break;
        }
        ((TObjEneEpsilon *)(ene_epsilon))->vfunc_89();
        break;
    case 5:
        break;
    }
}

#define arg0 ((u8 *)arg0_)
#pragma opt_common_subs on
void TObjEneMe3SinowZoa__sub_8031884C(void *arg0_, s32 arg1) {
    s32 temp_r5;
    s32 zero;

    switch (arg1) {
    case 4:
        *(s16 *)((s8 *)arg0 + 0xB8) = 3;
        ((TObjEneDD *)arg0)->set_field_378(6);
        ((TObjEneMe3SinowZoa *)(arg0))->vfunc_96();
        zero = 0;
        *(s32 *)((s8 *)arg0 + 0x3CC) &= 0xFFEFFFF8;
        *(s32 *)((s8 *)arg0 + 0x3FC) = zero;
        *(s32 *)((s8 *)arg0 + 0x434) = 3;
        if (((VObj_18_347dfc *)(arg0))->m102(TObjEneMe3SinowZoa__data_805DF324) != 0) {
            ((TObjEneDD_ST *)arg0)->enemy_copy_target_destination();
            ((TObjEneDD *)arg0)->update_velocity();
            *(s32 *)((s8 *)arg0 + 0x43C) = (s32) (TObjEneMe3SinowZoa__data_804760A0 * atan2_float((f32) (*(f32 *)((s8 *)arg0 + 0x3A0)), (f32) (*(f32 *)((s8 *)arg0 + 0x3A8))));
            if (((s32 (*)(void *, s32, f32))check_body_collision_at__18TObjEneMe3SinowZoaFlf)(arg0, (int) (*(s32 *)((s8 *)arg0 + 0x43C) + 0x8000), lbl_805DF338) == 0) {
                *(f32 *)((s8 *)arg0 + 0x3A0) = (f32) (*(f32 *)((s8 *)arg0 + 0x3A0) * lbl_805DF33C);
                *(f32 *)((s8 *)arg0 + 0x3A8) = (f32) (*(f32 *)((s8 *)arg0 + 0x3A8) * lbl_805DF33C);
                *(s32 *)((s8 *)arg0 + 0x434) = 0;
                *(f32 *)((s8 *)arg0 + 0x440) = (f32) lbl_805DF340;
            }
        }
        ((TObjEneDD_ST *)arg0)->set_active();
        return;
    case 3:
        if ((s32) *(s32 *)((s8 *)arg0 + 0x434) == 3) {
            if (((s32) *(s32 *)((s8 *)arg0 + 0x3C0) == 0) && (random_ratio__9TObjCharaFv((s32)arg0) <= *(f32 *)((s8 *)arg0 + 0x3EC))) {
                transition_enemy_state__9TObjEneDDFl(arg0, 0x11);
            } else if (random_ratio__9TObjCharaFv((s32)arg0) <= *(f32 *)((s8 *)arg0 + 0x3E8)) {
                if (((s32 (*)(u8 *))sub_8031A454__18TObjEneMe3SinowZoaFv)(arg0) != 0) {
                    if (random_ratio__9TObjCharaFv((s32)arg0) > ((f32 *)TObjEneMe3SinowZoa__kind_param_tbls[*(s32 *)((s8 *)arg0 + 0x3C8)])[5]) {
                        transition_enemy_state__9TObjEneDDFl(arg0, 0x10);
                    } else {
                        transition_enemy_state__9TObjEneDDFl(arg0, 0xB);
                    }
                } else {
                    transition_enemy_state__9TObjEneDDFl(arg0, 0x10);
                }
            } else if (random_ratio__9TObjCharaFv((s32)arg0) <= *(f32 *)((s8 *)arg0 + 0x3F4)) {
                transition_enemy_state__9TObjEneDDFl(arg0, 0xC);
            } else {
                transition_enemy_state__9TObjEneDDFl(arg0, 6);
            }
        }
        break;
    case 0:
        ((TObjMotion *)arg0)->advance_animation();
        switch (*(s32 *)((s8 *)arg0 + 0x434)) {
        case 0:
            *(s32 *)((s8 *)arg0 + 0x60) = approach_angle_limited((int) (*(s32 *)((s8 *)arg0 + 0x60)), (int) (*(s32 *)((s8 *)arg0 + 0x43C)), 0x31C7);
            if ((*(f32 *)((s8 *)arg0 + 0xC0) + *(f32 *)((s8 *)arg0 + 0xC8)) >= TObjEneMe3SinowZoa__data_805DF2F0) {
                *(s32 *)((s8 *)arg0 + 0x434) = 1;
                ((TObjEneMe3SinowZoa *)(arg0))->vfunc_91();
                play_sound_effect(0x4003A829, arg0 + 0x38, 0, 0);
            }
            ((TObjEneMe3SinowZoa *)(arg0))->vfunc_102();
            ((TObjEneMe3SinowZoa *)(arg0))->vfunc_89();
            return;
        case 1:
            if ((*(f32 *)((s8 *)arg0 + 0xC0) + *(f32 *)((s8 *)arg0 + 0xC8)) >= lbl_805DF344) {
                *(s32 *)((s8 *)arg0 + 0x434) = 2;
                ((TObjEneMe3SinowZoa *)(arg0))->vfunc_92();
                play_sound_effect(0x4003A82A, arg0 + 0x38, 0, 0);
                ((TObjEneMe3SinowZoa *)arg0)->check_and_notify();
            }
            ((TObjEneDD *)arg0)->move_clamped_on_ground((f32) (*(f32 *)((s8 *)arg0 + 0x3A0)), (f32) (*(f32 *)((s8 *)arg0 + 0x3A8)), (f32) (*(f32 *)((s8 *)arg0 + 0x440)));
            return;
        case 2:
            if (((TObjEneDD *)arg0)->get_flag_b4() != 0) {
                *(s32 *)((s8 *)arg0 + 0x434) = 3;
            }
            ((TObjEneMe3SinowZoa *)(arg0))->vfunc_102();
            ((TObjEneMe3SinowZoa *)(arg0))->vfunc_89();
            return;
        }
        break;
    case 5:
        ((TObjEneMe3SinowZoa *)(arg0))->vfunc_92();
        ((TObjEneDD *)arg0)->clear_field_388();
        break;
    }
}

#undef arg0
void TObjEneMe3SinowZoa__sub_80318564(u8 *arg0, s32 arg1) {
    switch (arg1) {
    case 4:
        F(s16, 0xB8) = 8;
        ((TObjEneDD *)arg0)->set_field_378(0xB);
        VO->m94();
        F(s32, 0x3CC) &= 0xFFEFFFF8;
        if (F(s32, 0x3C0) != 0) {
            ((TUnk_80494938 *)(arg0 + 0x414))->set_rate(TObjEneMe3SinowZoa__data_805DF30C);
            VS->s3();
            F(s32, 0x3CC) |= 0x100000;
            F(s32, 0x3CC) |= 0x40000;
            ((TObjCollidable *)arg0)->clear_player_status_flag(0, 0x08000000);
            F(s32, 0x434) = 0;
        } else {
            F(s32, 0x434) = 1;
        }
        F(s32, 0x438) = 0;
        break;
    case 3:
        if (F(s32, 0x438) > TBL(0x1C)) {
            transition_enemy_state__9TObjEneDDFl(arg0, 6);
        }
        break;
    case 5:
        break;
    case 0:
        ((TObjMotion *)arg0)->advance_animation();
        switch (F(s32, 0x434)) {
        case 0:
            ((TObjMotion *)arg0)->advance_animation();
            if (((TUnk_80494938 *)(arg0 + 0x414))->advance_timer(TObjEneMe3SinowZoa__data_805DF310) != 0) {
                F(s32, 0x434) = 1;
            }
        case 1:
            if (((TObjEneDD *)arg0)->get_flag_b4() != 0) {
                cast_technique__18TObjEneMe3SinowZoaFPv(arg0);
                if (((s32 (*)(void))check_v2_mode__9TObjEneDDFv)() != 0) {
                    F(s32, 0x434) = 3;
                } else if (F(s32, 0x3CC) & 0x100000) {
                    F(s32, 0x434) = 4;
                } else {
                    F(s32, 0x434) = 2;
                }
                F(s32, 0x438) = 0;
            }
            break;
        case 2:
            F(s32, 0x438)++;
            break;
        case 3:
            F(s32, 0x438)++;
            if (F(s32, 0x438) == 5) {
                TTecSifta::create((void *)arg0, arg0 + 0x38, (void *)(TObjEneDD::clamp_frame_index(TBL(0x18))));
            } else if (F(s32, 0x438) == 0xA) {
                create__10TTecDebandFlll(arg0, arg0 + 0x38, TObjEneDD::clamp_frame_index(TBL(0x18)));
                if (F(s32, 0x3CC) & 0x100000) {
                    F(s32, 0x434) = 4;
                } else {
                    F(s32, 0x434) = 2;
                }
                F(s32, 0x438) = 0;
            }
            break;
        case 4:
            if (VS->s4() != 0) {
                F(s32, 0x434) = 2;
                F(s32, 0x3CC) |= 0x40000;
                ((TObjCollidable *)arg0)->set_indexed_flags(0, 0x08000000);
            }
            break;
        }
        VO->m100();
        break;
    }
}

#undef F
#undef VO
#undef VS
#undef TBL
void TObjEneMe3SinowZoa::handle_state_substate(s32 arg1) {
    switch (arg1) {
    case 4:
        *(s16 *)((s8 *)this + 0xB8) = 9;
        set_field_378(0xD);
        *(u32 *)((s8 *)this + 0x3CC) &= 0xFFEFFFF8;
        this->vfunc_95();
        *(s32 *)((s8 *)this + 0x3FC) = 0;
        *(s32 *)((s8 *)this + 0x434) = 0;
        break;
    case 3:
        if (update_linked_position(TObjEneMe3SinowZoa__data_805DF324) != 0) {
            transition_enemy_state__9TObjEneDDFl(this, 6);
        } else if (*(s32 *)((s8 *)this + 0x434) >= 0x5A) {
            transition_enemy_state__9TObjEneDDFl(this, 0xA);
        }
        break;
    case 5:
        break;
    case 0:
        (*(s32 *)((s8 *)this + 0x434))++;
        advance_animation();
        this->vfunc_102();
        this->vfunc_89();
        break;
    }
}

void TObjEneMe3SinowZoa__sub_803182F8(u8 *ene_dd, s32 arg1) {
    switch (arg1) {
    case 4:
        *(s16 *)((s8 *)ene_dd + 0xB8) = 8;
        ((TObjEneDD *)ene_dd)->set_field_378(6);
        ((TObjEneDD *)(ene_dd))->vfunc_95();
        *(s32 *)((s8 *)ene_dd + 0x3CC) = (s32) (*(s32 *)((s8 *)ene_dd + 0x3CC) & 0xFFEFFFFC);
        *(s32 *)((s8 *)ene_dd + 0x3CC) = (s32) (*(s32 *)((s8 *)ene_dd + 0x3CC) | 4);
        ((VObj_14_803182F8 *)(ene_dd + 0x414))->m1(0x1E);
        ((VObj_14_803182F8 *)(ene_dd + 0x414))->m2();
        *(s32 *)((s8 *)ene_dd + 0x434) = 1;
        break;
    case 3:
        if (*(s32 *)((s8 *)ene_dd + 0x434) == 2) {
            transition_enemy_state__9TObjEneDDFl(ene_dd, 0);
        }
        break;
    case 0:
        ((TObjMotion *)ene_dd)->advance_animation();
        switch (*(s32 *)((s8 *)ene_dd + 0x434)) {
        case 0:
            if (((TObjEneDD *)ene_dd)->get_flag_b4() != 0) {
                *(s32 *)((s8 *)ene_dd + 0x434) = 1;
            }
            break;
        case 1:
            if (((VObj_14_803182F8 *)(ene_dd + 0x414))->m4() != 0) {
                *(s32 *)((s8 *)ene_dd + 0x434) = 2;
            }
            break;
        }
        ((TObjEneDD *)(ene_dd))->vfunc_102();
        break;
    case 5:
        *(s32 *)((s8 *)ene_dd + 0x3CC) = (s32) (*(s32 *)((s8 *)ene_dd + 0x3CC) & 0xFFFFFFFB);
        break;
    }
}

void TObjEneMe3SinowZoa::state_knockback(s32 arg1) {
    u8 *arg0 = (u8 *)this;
    Vec_803181A8 v;
    f32 len;
    switch (arg1) {
    case 4:
        *(s16 *)((s8 *)arg0 + 0xB8) = 4;
        ((TObjMotion *)arg0)->advance_animation();
        ((TObjEneDD_ST *)arg0)->set_active();
        play_sound_effect(0x4003A82D, arg0 + 0x38, 0, 0);
        *(s32 *)((s8 *)arg0 + 0x3CC) &= 0xFFEFFFF8;
        break;
    case 3:
        if (((TObjEneDD *)arg0)->get_flag_b4() != 0) {
            if (*(s32 *)((s8 *)arg0 + 0x3C0) == 1 && random_ratio__9TObjCharaFv((s32)arg0) <= *(f32 *)((s8 *)arg0 + 0x3F0)) {
                transition_enemy_state__9TObjEneDDFl(arg0, 0x12);
            } else {
                transition_enemy_state__9TObjEneDDFl(arg0, *(s32 *)((s8 *)arg0 + 0x378));
            }
        }
        break;
    case 0:
        ((TObjMotion *)arg0)->advance_animation();
        VecCopy((Vec *)&v, (const Vec *)(arg0 + 0x308));
        len = normalize_vector_xz((Vec *)(&v));
        ((TObjEneDD *)arg0)->move_clamped_on_ground(v.x, v.z, len);
        *(f32 *)((s8 *)arg0 + 0x308) *= lbl_805DF334;
        *(f32 *)((s8 *)arg0 + 0x310) *= lbl_805DF334;
        this->vfunc_89();
        break;
    case 5:
        ((TObjEneDD *)arg0)->clear_attack_receipts();
        ((TObjEneDD *)arg0)->clear_field_388();
        break;
    }
}

#pragma fp_contract on
void TObjEneMe3SinowZoa__sub_80317F90(u8 *arg0, s32 arg1) {
    Vec_80317F90 v;
    Vec_80317F90 p;
    *(s32 *)((s8 *)arg0 + 0x3C0) = 0;
    switch (arg1) {
    case 3:
    case 5:
        break;
    case 4:
        *(s16 *)((s8 *)arg0 + 0xB8) = 5;
        ((TObjEnemy *)arg0)->refresh_and_send_entity_flags();
        ((VObj_18_64d9d3 *)(arg0))->m92();
        *(s32 *)((s8 *)arg0 + 0x3CC) = (s32) (*(s32 *)((s8 *)arg0 + 0x3CC) & 0xFFEFFFF8);
        *(s32 *)((s8 *)arg0 + 0x434) = 0;
        break;
    case 0:
        switch (*(s32 *)((s8 *)arg0 + 0x434)) {
        case 0:
            ((TObjMotion *)arg0)->advance_animation();
            if (((TObjMotion *)arg0)->is_passing_frame((f32)lbl_805DF330) != 0 || ((TObjMotion *)arg0)->is_passing_frame((f32)((f32)lbl_805DF300)) != 0) {
                play_sound_effect(0x4003A82A, arg0 + 0x38, 0, 0);
            }
            if (((TObjEneDD *)arg0)->get_flag_b4() != 0) {
                *(s32 *)((s8 *)arg0 + 0x434) = 1;
                *(s32 *)((s8 *)arg0 + 0x438) = 0;
                v.x = TObjEneMe3SinowZoa__data_805DF31C;
                v.y = TObjEneMe3SinowZoa__data_805DF314;
                v.z = TObjEneMe3SinowZoa__data_805DF320;
                ((TObjBoss2Tunnel *)(&v))->init_zako(arg0 + 0x38, *(s32 *)((s8 *)arg0 + 0x60));
                TObjPlayer::spawn_effect_f8((s32)&v, 0x14);
            }
            break;
        case 1:
            *(s32 *)((s8 *)arg0 + 0x438) += 1;
            if (*(s32 *)((s8 *)arg0 + 0x438) >= 0x14) {
                *(s32 *)((s8 *)arg0 + 0x434) = 2;
                *(s32 *)((s8 *)arg0 + 0x3CC) |= 2;
                TBoss3Volopt::create_breakup_mdl((s32)TObjEneMe3SinowZoa__data_805D6AE0, (s32)sinow_zoa_breakup_params, (s32)(*(s32 *)((s8 *)arg0 + 0x24)), (s32)(arg0 + 0x38), (s32)(*(s32 *)((s8 *)arg0 + 0x60)));
                VecCopy((Vec *)&p, (const Vec *)(arg0 + 0x38));
                p.x += TObjEneMe3SinowZoa__data_805DF320 * sin_table_lookup(*(s32 *)((s8 *)arg0 + 0x60));
                p.z += TObjEneMe3SinowZoa__data_805DF320 * cos_table_lookup(*(s32 *)((s8 *)arg0 + 0x60));
                ((TObjPlayer *)(&p))->trigger_dell_biter_events();
                play_sound_effect(0x4003AD2E, arg0 + 0x38, 0, 0);
            }
            ((VObj_18_64d9d3 *)(arg0))->m100();
            break;
        case 2:
            queue_destruction__7TObjectFv(arg0);
            break;
        }
        break;
    }
}

void TObjEneMe3SinowZoa__sub_80317B50(void *arg0_, s32 arg1) {
    Vec_80317B50 v;
    Vec_80317B50 pos;
    Vec_80317B50 tmp;
    s32 d[3];
    s32 i;
    u8 *ene_me3_sinow_zoa = (u8 *)arg0_;

    switch (arg1) {
    case 4:
        *(s16 *)((s8 *)ene_me3_sinow_zoa + 0xB8) = 0xC;
        ((TObjEneDD *)ene_me3_sinow_zoa)->set_field_378(0xC);
        ((TObjEneMe3SinowZoa *)ene_me3_sinow_zoa)->vfunc_95();
        *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC) &= 0xFFEFFFF9;
        *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC) |= 1;
        *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x434) = 0;
        break;
    case 3:
        if (*(s32 *)((s8 *)ene_me3_sinow_zoa + 0x434) == 2) {
            *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3C0) = 1;
            *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC) |= 0x40000;
            ((TObjCollidable *)ene_me3_sinow_zoa)->set_indexed_flags(0, 0x08000000);
            if (random_ratio__9TObjCharaFv((s32)ene_me3_sinow_zoa) <= *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E8)) {
                if (((s32 (*)(u8 *))sub_8031A454__18TObjEneMe3SinowZoaFv)(ene_me3_sinow_zoa) != 0) {
                    if (random_ratio__9TObjCharaFv((s32)ene_me3_sinow_zoa) > ((f32 *)TObjEneMe3SinowZoa__kind_param_tbls[*(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3C8)])[5]) {
                        transition_enemy_state__9TObjEneDDFl(ene_me3_sinow_zoa, 0x10);
                    } else {
                        transition_enemy_state__9TObjEneDDFl(ene_me3_sinow_zoa, 0xB);
                    }
                } else {
                    transition_enemy_state__9TObjEneDDFl(ene_me3_sinow_zoa, 0x10);
                }
            } else {
                transition_enemy_state__9TObjEneDDFl(ene_me3_sinow_zoa, 1);
            }
        }
        break;
    case 0:
        switch (*(s32 *)((s8 *)ene_me3_sinow_zoa + 0x434)) {
        case 0:
            ((TObjMotion *)ene_me3_sinow_zoa)->advance_animation();
            if (((TObjEneDD *)ene_me3_sinow_zoa)->get_flag_b4() != 0) {
                *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC) |= 4;
                play_sound_effect(0x4003AD2F, ene_me3_sinow_zoa + 0x38, 0, 0);
                ((VObj_14_c5778e *)(ene_me3_sinow_zoa + 0x414))->m1(0x1E);
                VecCopy((Vec *)&v, (const Vec *)(ene_me3_sinow_zoa + 0x38));
                v.y = *(f32 *)((s8 *)ene_me3_sinow_zoa + 0x3E0) - TObjEneMe3SinowZoa__data_805DF320;
                *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x434) = 1;
            }
            ((TObjEneMe3SinowZoa *)ene_me3_sinow_zoa)->vfunc_102();
            ((TObjEneMe3SinowZoa *)ene_me3_sinow_zoa)->vfunc_89();
            break;
        case 1:
            if (((VObj_14_c5778e *)(ene_me3_sinow_zoa + 0x414))->m4() != 0) {
                *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC) |= 2;
                if (((TObjEneDD_ST *)ene_me3_sinow_zoa)->update_linked_position(TObjEneMe3SinowZoa__data_805DF324) != 0) {
                    if (*(u8 **)((s8 *)ene_me3_sinow_zoa + 0x390) == NULL) {
                        break;
                    }
                    d[0] = (s32)(TObjEneMe3SinowZoa__data_805DF328 * random_ratio__9TObjCharaFv((s32)ene_me3_sinow_zoa)) - 1;
                    d[1] = (s32)(TObjEneMe3SinowZoa__data_805DF32C * random_ratio__9TObjCharaFv((s32)ene_me3_sinow_zoa)) - 1;
                    if (d[1] <= d[0]) {
                        d[1]++;
                    }
                    d[2] = -(d[0] + d[1]);
                    for (i = 0; i < 3; i++) {
                        s32 ang;
                        VecCopy((Vec *)&pos, (const Vec *)(*(u8 **)((s8 *)ene_me3_sinow_zoa + 0x390) + 0x38));
                        ang = *(s32 *)((s8 *)(*(u8 **)((s8 *)ene_me3_sinow_zoa + 0x390)) + 0x60) + ((d[i] + 1) << 14);
                        pos.x += TObjEneMe3SinowZoa__data_805DF320 * cos_table_lookup(ang);
                        pos.z -= TObjEneMe3SinowZoa__data_805DF320 * sin_table_lookup(ang);
                        pos.y += TObjEneMe3SinowZoa__data_805DF308;
                        VecCopy((Vec *)&tmp, (const Vec *)&pos);
                        tmp.x += pos.x - *(f32 *)((s8 *)(*(u8 **)((s8 *)ene_me3_sinow_zoa + 0x390)) + 0x38);
                        tmp.z += pos.z - *(f32 *)((s8 *)(*(u8 **)((s8 *)ene_me3_sinow_zoa + 0x390)) + 0x40);
                        if (check_move_collision__18TObjEneMe3SinowZoaFP3Vec(ene_me3_sinow_zoa, &tmp) == 0 &&
                            csnVector(*(u8 **)((s8 *)ene_me3_sinow_zoa + 0x390) + 0x38, &tmp, 0x88E0) == 0 &&
                            csnVectorUnder(&pos, ene_me3_sinow_zoa + 0x120, 0x15) != 0 &&
                            *(s16 *)((s8 *)ene_me3_sinow_zoa + 0x28) == ((TScene *)(&pos))->find_section_at_position()) {
                            VecCopy((Vec *)(ene_me3_sinow_zoa + 0x38), (const Vec *)&pos);
                            *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x60) = ang + 0xC000;
                            break;
                        }
                    }
                }
                *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x434) = 2;
            }
            break;
        }
        break;
    case 5:
        *(s32 *)((s8 *)ene_me3_sinow_zoa + 0x3CC) &= ~4;
        break;
    }
}

#define v ((VObj_18_fc0b09 *)((u8 *)this))
void TObjEneMe3SinowZoa::render() {
    s32 mode;
    s32 draw;
    s32 i;
    Zoa_8031786C *o = (Zoa_8031786C *)this;

    if (TObjPlayer::check_demo_mode() != 0) {
        v->m113();
        return;
    }
    sub_8031A454__18TObjEneMe3SinowZoaFv(((u8 *)this));
    if (o->f3CC & 2) {
        mode = 0;
    } else if (is_main_phase_15__9TObjEneDDFv() != 0) {
        mode = v->m9(lbl_805D9E88, lbl_805D9E84, TObjEneMe3SinowZoa__data_805DF2F0);
    } else if (v->m8(lbl_805DF318, TObjEneMe3SinowZoa__data_805DF2F0) != 0) {
        mode = 1;
    } else {
        mode = 0;
    }
    if (mode != 0) {
        if (this->render_model_if_visible() != 0) {
            return;
        }
        this->update_secondary_light();
        saved_model_render_flags = model_render_flags;
        saved_chunk_polygon_flags_and_mask = chunk_polygon_flags_and_mask;
        saved_chunk_polygon_flags_or_mask = chunk_polygon_flags_or_mask;
        copy_argb((NJS_ARGB *)saved_model_draw_color, (NJS_ARGB *)model_material_color);
        if (!(o->f3D0 & 0x4000)) {
            v->m106();
            TObjEneDD::clear_global_flag_400();
        }
        TObjPlayer::toggle_particle_effect();
        TObjFish::set_global_param(*(s32 *)(((u8 *)this) + 0x24));
        for (i = 0; i < 3; i++) {
            if (lbl_80542FF0[i] != NULL) {
                *lbl_80542FF0[i] = o->f3F8;
            }
        }
        draw = 1;
        if (v->m107() != 0) {
            if (defer_render__7TObjectFv(this) != 0) {
                draw = 0;
            } else if (o->f3C0 != 0) {
                draw = 0;
            }
        } else if (TObjEneMe3SinowZoa__sub_800D72A4(&o->sub) != 0) {
            o->sub.m6();
            if (defer_render__7TObjectFv(this) != 0) {
                draw = 0;
            }
        } else if (o->f3C0 != 0) {
            draw = 0;
        }
        if (draw != 0) {
            push_matrix();
            post_translate_matrix(((u8 *)this) + 0x38);
            translate_matrix(0, TObjEneMe3SinowZoa__data_805DF31C, *(f32 *)(((u8 *)this) + 0x3E4), TObjEneMe3SinowZoa__data_805DF31C);
            rotate_matrix_y(0, *(s32 *)(((u8 *)this) + 0x60));
            lbl_805D6ADC = 0;
            if (mode == 1) {
                this->draw();
            } else {
                this->draw_motion_model();
            }
            pop_matrix();
        }
        if (v->m108() == 0 && TObjEneMe3SinowZoa__sub_800D72A4(&o->sub) != 0) {
            o->sub.m7();
        }
        copy_argb((NJS_ARGB *)model_material_color, (NJS_ARGB *)saved_model_draw_color);
        chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;
        chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask;
        model_render_flags = saved_model_render_flags;
        this->update_primary_light();
    }
    TParticleCtrl::end_effect_render();
}

#undef V8
#undef V64
#undef sinow_zoa_collision_parts
#undef v
#pragma fp_contract off
void TObjEneMe3SinowZoa::action() { if (get_target_info() != 0) { setup_move_bounds(); sub_8031A3D8(); } }

s32 TObjEneMe3SinowZoa::render_model_if_visible() {
    if (get_mode__11TCameraCtrlFPv(((s32 *)&main_task)) & 0x20) {
        if (push_reflection_matrix((Vec *)(((u8 *)this) + 0x3D4)) != 0) {
            TObjFish::set_global_param((int) (*(s32 *)((s8 *)((u8 *)this) + 0x24)));
            push_matrix();
            post_translate_matrix((void *) (((u8 *)this) + 0x38));
            translate_matrix(0, TObjEneMe3SinowZoa__data_805DF31C, (f32) (*(f32 *)((s8 *)((u8 *)this) + 0x3E4)), TObjEneMe3SinowZoa__data_805DF31C);
            rotate_matrix_y(0, (int) (*(s32 *)((s8 *)((u8 *)this) + 0x60)));
            this->draw();
            pop_matrix();
            restore_render_scissor(1);
        }
        return 1;
    }
    return 0;
}

void TObjEneMe3SinowZoa::vfunc_115() {
    s32 save[3];
    s32 flag;
    AnimationMotion *motion;
    f32 frame;
    if (get_target_info() != 0) {
        if (sub_8031A4D0() != 0) {
            debug_printf_at(pack_debug_text_position(0, 2), lbl_80475FD4);
        } else {
            debug_printf_at(pack_debug_text_position(0, 2), lbl_80475FE4);
        }
        if (is_outside_visible_range() != 0) {
            debug_printf_at(pack_debug_text_position(0xF, 2), lbl_80475FF4);
        } else {
            debug_printf_at(pack_debug_text_position(0xF, 2), lbl_80476004);
        }
        TObjEneMe1Gee::queue_debug_text(pack_debug_text_position(0, 4), lbl_80476010);
        TObjEneMe1Gee::queue_debug_text(pack_debug_text_position(0, 3), lbl_80476028);
        TObjEneMe1Gee::queue_debug_text(pack_debug_text_position(0, 6), lbl_80476040);
        TObjEneMe1Gee::queue_debug_text(pack_debug_text_position(0, 5), lbl_80476058);
        if (sub_8031A454() != 0) {
            debug_printf_at(pack_debug_text_position(0, 9), lbl_80476070);
        } else {
            debug_printf_at(pack_debug_text_position(0, 9), lbl_80476084);
        }
    }
    flag = sub_8031A454();
    if (update_object_view_visibility(lbl_805DF318, TObjEneMe3SinowZoa__data_805DF2F0) != 0) {
        TObjFish::set_global_param((s32)((NJS_TEXLIST *)texlist));
        TObjPlayer::toggle_particle_effect();
        if (flag != 0) {
            NJS_TEXNAME *parts = ((NJS_TEXLIST *)texlist)->textures;
            s32 i;
            for (i = 0; i < 3; i++) {
                save[i] = parts[i].texaddr;
            }
            for (i = 0; i < 3; i++) {
                parts[i].texaddr = parts[i + 3].texaddr;
            }
        }
        push_matrix();
        post_translate_matrix(&position);
        rotate_matrix_y(0, rotation_y);
        scale_matrix(0, TObjEneMe3SinowZoa__data_805DF2F4, TObjEneMe3SinowZoa__data_805DF2F4, TObjEneMe3SinowZoa__data_805DF2F4);
        {
            s32 i;
            for (i = 0; i < 3; i++) {
                if (lbl_80542FF0[i] != NULL) {
                    *lbl_80542FF0[i] = 0xB000FFB0;
                }
            }
        }
        if (mode == 0) {
            s32 idx = requested_action;
            if (idx < 0) {
                idx = 0;
            } else if (idx >= 0xD) {
                idx = 0xC;
            }
            TObjMotionAction *actions = (TObjMotionAction *)action_table;
            BmlMotionEntry *motions = (BmlMotionEntry *)motion_list;
            motion = motions[actions[idx].motion].motion;
            frame = parameters[3];
            if (frame < TObjEneMe3SinowZoa__data_805DF31C) {
                frame = TObjEneMe3SinowZoa__data_805DF31C;
            } else if (frame > (motion->frameCount - 1)) {
                frame = (motion->frameCount - 1);
            }
            set_motion_packed_rotation();
            draw_model_motion(model, motion, frame);
            clear_motion_packed_rotation();
            current_motion = (NJS_MOTION *)motion;
            this->frame = frame;
            frame = get_node_height();
            print_float_padded(pack_debug_text_position(0, 7), 5, frame);
        } else {
            model_render_flags &= ~0x400;
        }
        pop_matrix();
        if (flag != 0) {
            s32 i;
            NJS_TEXNAME *parts = ((NJS_TEXLIST *)texlist)->textures;
            for (i = 0; i < 3; i++) {
                parts[i].texaddr = save[i];
            }
        }
        TParticleCtrl::end_effect_render();
    }
}

void TObjEneMe3SinowZoa::fn_80317254(s32 arg1) {
    switch (arg1) {
    case 4:
        requested_action = 0xC;
        set_field_378(6);
        vfunc_96();
        state_flags &= 0xFFEFFFFD;
        state_flags |= 5;
        fade.set_rate_from_divisor(0x1E);
        play_sound_effect(0x4003AD2F, &position, 0, 0);
        substate = 0;
        break;
    case 3:
        if ((substate == 1) && (fade.decay_value_toward_floor() != 0)) {
            m_3c0 = 1;
            transition_enemy_state(6);
            state_flags &= ~5;
            state_flags |= 0x40000;
            set_indexed_flags(0, 0x08000000);
            break;
        }
    case 5:
        break;
    case 0:
        advance_animation();
        if (get_flag_b4() != 0) {
            substate = 1;
        }
        vfunc_102();
        vfunc_89();
        break;
    }
}

void TObjEneMe3SinowZoa::fn_803170F0(s32 arg1) {
    switch (arg1) {
    case 4:
        requested_action = 0xB;
        set_field_378(6);
        vfunc_96();
        state_flags &= 0xFFEFFFFD;
        state_flags |= 5;
        fade.set_rate_from_divisor(0x1E);
        m_3c0 = 0;
        state_flags |= 0x40000;
        clear_player_status_flag(0, 0x08000000U);
        substate = 0;
        break;
    case 3:
        if ((substate == 1) && (fade.advance_toward_max() != 0)) {
            transition_enemy_state(6);
            state_flags &= ~5;
            break;
        }
    case 5:
        break;
    case 0:
        advance_animation();
        if (get_flag_b4() != 0) {
            substate = 1;
        }
        vfunc_102();
        vfunc_89();
        break;
    }
}

#pragma dont_inline off
#pragma inline_depth(4)
void TObjEneMe3SinowZoa::fn_80316C3C(s32 arg1) {
    s32 angle;
    Vec diff;
    Vec out;
    switch (arg1) {
    case 5:
        break;
    case 4:
        requested_action = 0xA;
        set_field_378(6);
        vfunc_96();
        state_flags &= 0xFFEFFFF8;
        state_flags |= 0x10000;
        enemy_copy_target_destination();
        substate = 0;
        break;
    case 3:
        if (substate == 5) {
            transition_enemy_state(6);
        }
        break;
    case 0:
        switch (substate) {
        case 0:
        default:
            if (target == 0) {
                transition_enemy_state(6);
                break;
            }
            if (select_enemy_destination(this, target_destination, 1) != 0) {
                copy_position_if_valid__10TObjPlayerFii(this, *((Vec *)&body_center_position));
                body_center_position.y += TObjEneMe3SinowZoa__data_805DF308;
                angle = enemy_turn_toward_dest(this, ((SinowZoaMoveParameters *)movementParameters)->turn_speed);
                enemy_set_heading_velocity(((SinowZoaMoveParameters *)movementParameters)->speed, this, rotation_y);
                move_with_wall_slide((u8 *)this);
            } else {
                VecCopy(&diff, &target_destination);
                subtract_vector(&diff, ((Vec *)&body_center_position));
                angle = turn_toward_direction( ((SinowZoaMoveParameters *)movementParameters)->turn_speed, &diff);
            }
            if (angle < 0x100) {
                if (m_3c0 != 0) {
                    fade.set_rate(TObjEneMe3SinowZoa__data_805DF30C);
                    fade.reset_obstruction_fade();
                    state_flags |= 0x100000;
                    state_flags |= 0x40000;
                    clear_player_status_flag(0, 0x08000000);
                    substate = 1;
                } else {
                    substate = 2;
                }
                requested_action = 8;
            } else {
                requested_action = 0xA;
            }
            break;
        case 1:
            advance_animation();
            if (fade.advance_timer(TObjEneMe3SinowZoa__data_805DF310) != 0) {
                substate = 2;
            }
        case 2:
            advance_animation();
            if (get_flag_b4() != 0) {
                state_timer = 0;
                substate = 3;
            }
            if (is_passing_frame( (f32)TObjEneMe3SinowZoa__data_805DF314) != 0) {
                advance_animation();
                push_matrix_from(identity_matrix);
                post_translate_matrix(&position);
                rotate_matrix_y(0, rotation_y);
                set_motion_packed_rotation();
                calc_joint_matrices(TObjEneMe3SinowZoa__data_805DF314);
                clear_motion_packed_rotation();
                pop_matrix();
                push_matrix_from(anim_model_matrix_array[3]);
                Vec source = lbl_80475FC8[0];
                matrix_mult_vec(0, &source, &out);
                pop_matrix();
                if (target != 0) {
                    VecCopy(&diff, &target_destination);
                    subtract_vector(&diff, ((Vec *)&body_center_position));
                    angle = turn_toward_direction( ((SinowZoaMoveParameters *)movementParameters)->turn_speed, &diff);
                } else {
                    angle = ((SinowZoaTargetParameters *)m_318)->angle_range;
                }
                if (angle < ((SinowZoaTargetParameters *)m_318)->angle_range / 2 && target != 0) {
                    if (game_difficulty_selection == 3) {
                        create__11TTecRaBartaFPvPvPvPv(this, &out, &position,
                            TObjEneDD::clamp_frame_index(TObjEneMe3SinowZoa__kind_param_tbls[kind]->barta_level));
                    } else {
                        ((TTecGiBarta *)this)->create_ex(&out, (void *)rotation_y, (void *)(TObjEneDD::clamp_frame_index(TObjEneMe3SinowZoa__kind_param_tbls[kind]->barta_level)));
                    }
                } else if (state_flags & 0x100000) {
                    substate = 4;
                } else {
                    substate = 5;
                }
            }
            break;
        case 3:
            if (++state_timer >= 0x28) {
                if (state_flags & 0x100000) {
                    substate = 4;
                } else {
                    substate = 5;
                }
            }
            break;
        case 4:
            if (fade.decay_value_toward_floor() != 0) {
                substate = 5;
                state_flags |= 0x40000;
                set_indexed_flags(0, 0x08000000);
            }
            break;
        }
        break;
    }
    ((TObjPlayer *)this)->update_collisions();
}

u32 TObjEneMe3SinowZoa::check_move_collision(Vec *destination) {
    CollisionBody *body = bodies;
    u32 result;
    u32 saved = body->flags;
    Vec saved_position;
    body->flags = 0x9d01;
    VecCopy(&saved_position, &position);
    VecCopy(&position, destination);
    TObjPlayer::init_all_slots();
    vfunc_89();
    update_enemy_collision_flags();
    if (body->flags & 0x80000) {
        if (get_valid_target_player__10TNpcPlayerFv(get_entity_id((TObjBase *)target)) == 0) {
            VecCopy(&position, &saved_position);
            TObjPlayer::init_all_slots();
            return 1;
        }
    }
    if ((body->flags & 0x100000) && get_valid_target_player__10TNpcPlayerFv(entity_id) == 0) {
        VecCopy(&position, &saved_position);
        TObjPlayer::init_all_slots();
        return 1;
    }
    result = (body->flags & 0x200000) != 0;
    VecCopy(&position, &saved_position);
    TObjPlayer::init_all_slots();
    copy_collision_body(body, sinow_zoa_collision_parts);
    body->flags = saved;
    return result;
}

f32 TObjEneMe3SinowZoa::receive_direct_attack(void *source, DirectAttackPayload damage, void *hit, s32, s32) {
    f32 result = TObjChara::receive_direct_attack(source, damage, hit, -1, -1);
    if (m_3c0 == 1 && random_ratio() <= damage_transition_probability) {
        transition_enemy_state(0x12);
    } else if (mode == 2) {
        transition_enemy_state(6);
    }
    return result;
}

#pragma dont_inline on
#pragma inline_depth(0)
void *TObjEneMe3SinowZoaReal::create_instance(void *data) {
    return new TObjEneMe3SinowZoaReal(tl_04, data);
}

#pragma opt_propagation off
TObjEneMe3SinowZoaReal::TObjEneMe3SinowZoaReal(TObject *parent, void *data)
    : TObjEneMe3SinowZoa(parent) {
    m_name = TObjEneMe3SinowZoaReal__name;
    invoke_initialization_hook__9TObjEneDDFPv(this, data);
    setup_move_bounds();
    init_enemy();
    mode = 0;
    dispatch_action(mode, 4);
}

#pragma opt_propagation on
TObjEneMe3SinowZoaReal::~TObjEneMe3SinowZoaReal() {}

void TObjEneMe3SinowZoaReal::vfunc_63() { TObjEneMe3SinowZoa::vfunc_63(); }

void TObjEneMe3SinowZoaReal::vfunc_62() { TObjEneMe3SinowZoa::vfunc_62(); }

void TObjEneMe3SinowZoaReal::vfunc_107() {
    ++attack_count;
    if (attack_count >= 2 || random_ratio() < lbl_805DF304) {
        transition_enemy_state(9);
        return;
    }
    transition_enemy_state(6);
}

void TObjEneMe3SinowZoaReal::vfunc_111() {}


// Expand the inline speed setup after all deferred bodies have been parsed.
#pragma dont_inline off
#pragma inline_depth(4)
