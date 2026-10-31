#include "pso/player/demo_mode.h"
#include "pso/misc/PositionSoundEffects.h"
#include "pso/misc/GroundEffects.h"
#include "pso/map/CsnGroundQuery.h"
#include "pso/system/MatrixVectorArray.h"
#include "pso/player/demo_mode.h"
#include "pso/misc/MaterialOpacityFade.h"
#include "pso/misc/RenderFadeState.h"
#include "pso/enemy/TObjEneRe7Berura_803E4CE0.h"
#include "pso/player/TObjPlayer_803E4954.h"
#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/system/BmlResource.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/enemy/EnemyTargetCandidate.h"
#include "pso/system/vector.h"
#include "pso/system/NinjaTypes.h"
#include "types.h"
#include "pso/misc/TRaderMapCore.h"
#include "pso/object/TObjMotion.h"
#include "pso/enemy/TObjEneEpsilonGuard.h"
#include "pso/TObject.h"
#include "pso/TParticleCtrl.h"
#include "pso/enemy/TObjEneDD_ST.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjChara.h"
#include "pso/unk/TObjEneEpsilonBody.h"
#include "pso/render/render_util.h"
#include <stddef.h>
#include "pso/boss/TBoss3Volopt.h"
#include "pso/boss/TBoss8Dragon.h"
#include "pso/boss/TObjBoss2Tunnel.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/enemy/TObjEneEpsilon.h"
#include "pso/enemy/TObjEneRe7Berura.h"
#include "pso/misc/RenderFadeState.h"
#include "pso/misc/TNowLoading.h"
#include "pso/object/TObjFish.h"
struct EpsilonMovementParameters {
    f32 radius;
    f32 speed;
    s32 angle;
    s16 period;
    s16 flags;
    s32 field_10;
    s32 field_14;
    s32 field_18;
};
static TObjMotionAction epsilon_body_actions[2] = {{1, 0, 0, 0.3f, 0}, {1, 1, 1, 0.6f, 0}};
static EpsilonMovementParameters epsilon_body_movement = {150.0f, 0.5555555f, 0x400, 30, 0, 0, 1, 0};
static CollisionBody epsilon_body_collision[2] = {
    {{0.0f, 12.0f, 0.0f}, 12.0f, 0.0f, 0, 0x8003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 12.0f, 0.0f}, 20.0f, 0.0f, 0, 0x8003, {0.0f, 0.0f, 0.0f}, 0.0f}
};
__declspec(section ".data") u32 epsilon_body_line_colors[2] = {0x80FF4040, 0x80FF4040};
struct SubBase { char pad[0x14]; };
struct VSub : SubBase { virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual s32 m4(); };
struct EpsilonLineList {
    Vec *positions;
    u32 *colors;
    s32 first;
    s32 count;
};
struct RecoveredGlobal_80360638_lbl_805439FC {
    s32 value;
    u8 remaining[0x18];
};
struct Stack_8035F8F0 {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
};
struct RecoveredGlobal_8035F8F0_lbl_80479E6C {
    s32 value;
    u8 remaining[0xC];
};
struct VBase_14_948132 { char pad[0x14]; };
struct VObj_14_948132 : VBase_14_948132 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual s32 m5();
};
struct VBase_18_1fdb47 { char pad[0x18]; };
struct VObj_18_1fdb47 : VBase_18_1fdb47 {
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
    virtual s32 m104();
};
struct W_8035F844 { u8 pad0[0x4DC]; u16 h[4]; };
struct T_8035F8A8 { s16 v[4]; };
struct W_8035F8A8 { u8 pad0[0x43E]; s16 idx; };
struct W_8035FA50 { u8 pad0[0x4DC]; u16 h[4]; };
struct W_8035FBBC { u8 pad0[0x4DC]; u16 h[4]; };
struct W_8035FC20 { u8 pad0[0x4DC]; u16 h[4]; };
struct W_8035FC8C { u8 pad0[0x4DC]; u16 h[4]; };
struct W_8035FCEC { u8 pad0[0x4DC]; u16 h[4]; };
struct V3_8035F970 { f32 x, y, z; };
struct Guard_8035F970 {
    u8 pad0[0x460];
    s32 ids[4];
    V3_8035F970 pos[4];
    u8 pad4a0[0x3C];
    u16 h[4];
};
struct Tbl_8035FFA8 { s32 v[20][4]; };
struct Self_8035FFA8 { u8 pad0[0x438]; s32 flags; u8 pad43C[0xC]; s32 timer; };
struct Self_8035F5C8 { u8 pad0[0x38]; u8 x38[0x2FC - 0x38]; u8 x2FC[0x438 - 0x2FC]; s32 flags; };
struct Hit_8035F5C8 { u8 pad0[0x18]; s32 flags; };
struct Vec_803606A0 { f32 x, y, z; };
struct Tbl_803606A0 { s32 v[4]; };
struct Obj_803606A0 {
    u8 pad0[0x38];
    Vec_803606A0 pos;
    u8 pad44[0x60 - 0x44];
    s32 x60;
    u8 pad64[0xC0 - 0x64];
    f32 xC0;
    u8 padC4[0x460 - 0xC4];
    s32 ang[4];
    Vec_803606A0 pts[4];
};
struct W_8035FA50;
struct W_8035FBBC;
struct Guard_8035F970;
struct VBase_18_80361508 { char pad[0x18]; };
struct VObj_18_80361508 : VBase_18_80361508 {
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
    virtual void m84(); virtual void m85(); virtual void m86(); virtual void m87();
    virtual void m88(); virtual void m89(); virtual void m90(); virtual void m91();
    virtual void m92(); virtual void m93(); virtual void m94();
};
struct W_80361508 : VObj_18_80361508 {
    u8 pad1C[0x438 - 0x1C];
    s32 flags;
    u8 pad43C[0x4E4 - 0x43C];
    s32 state;
    s32 timer;
};
struct VBase_8036033C { char pad[0x14]; };
struct VObj_8036033C : VBase_8036033C {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual s32 m8();
};
struct Rec_8036033C { u8 b[0x1C]; };
struct Self_8036033C { u8 pad[0x3C0]; Rec_8036033C recs[4]; };
struct Vec4_80360D9C { f32 x, y, z, w; };
struct Guard_80360D9C {
    u8 pad0[0x2FC];
    u8 f2fc[0x430 - 0x2FC];
    u32 emitter;
    u8 pad434[0x438 - 0x434];
    s32 flags;
    u8 pad43c[2];
    s16 idx;
    u8 pad440[0x4A0 - 0x440];
    Vec4_80360D9C pos;
    u8 pad4b0[4];
    f32 vx, vy, vz;
    u8 pad4c0[0x4E4 - 0x4C0];
    s32 state;
    s32 timer;
    u8 pad4ec[0x4F8 - 0x4EC];
    f32 alpha;
};
struct VBase_18_a39899 { char pad[0x18]; };
struct VObj_18_a39899 : VBase_18_a39899 {
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
    virtual f32 m21(void *, void *, s32, s32, s32);
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
};
struct Dmg_803616E4 { s32 a; f32 b; };
struct Vec_803616E4 { f32 x, y, z; };
struct Induction_8035FAA8_var_r31 { u8 bytes[0x2]; };
struct Induction_8035FAA8_var_r31_owner { u8 padding[0x4DC]; Induction_8035FAA8_var_r31 elements[4]; };
struct Induction_8035FAA8_var_r31_2 { u8 bytes[0x2]; };
struct Induction_8035FAA8_var_r31_2_owner { u8 padding[0x4DC]; Induction_8035FAA8_var_r31_2 elements[4]; };
extern "C"{
    f32 atan2_float(f32 y, f32 x);
    s32 matrix_mult_vec(int, void *, void *);
    s32 push_matrix_from(void *);
    extern Tbl_803606A0 epsilon_guard_attack_offset_table;
    extern Vec_803606A0 lbl_80479D10;
    extern const f64 lbl_80479E90[];
    extern u8 identity_matrix[];
        f32 receive_physical_attack__9TObjCharaFPvf(void *, void *, f32);
    extern BmlResource *lbl_805D6FA0;
    s32 post_translate_matrix(void *);
    s32 scale_matrix(int, f32, f32, f32);
    s32 draw_chunk_object();
    s32 rotate_matrix_y(int, int);
    s32 translate_matrix(int, f32, f32, f32);
    s32 push_matrix();
    s32 pop_matrix();
    s32 get_mode__11TCameraCtrlFPv(void *);
    s32 set_field_378__9TObjEneDDFl(void *, s32);
    s32 transition_enemy_state__9TObjEneDDFl(void *, s32);
    void set_guard_state__18TObjEneEpsilonBodyFv(void *, s32);
    s32 clear_attack_receipts__9TObjEneDDFv();
    s32 VecCopy__FP3VecPC3Vec(void *, void *);
    void set_guard_state__18TObjEneEpsilonBodyFv(void *arg0, s32 _w1);
    void TObjEneEpsilonGuard__sub_80360BF8(u8 *arg0, s32 arg1);
        extern void *lbl_805D6F8C;
    void action__19TObjEneEpsilonGuardFPvi(void *arg0, s32 arg1);
    s32 draw_line_list(void *, int, int);
    extern RecoveredGlobal_80360638_lbl_805439FC lbl_805439FC;
    EpsilonLineList TObjEneEpsilonGuard__debug_line_list = {(Vec *)&lbl_805439FC, epsilon_body_line_colors, 0, 4};
    extern RecoveredGlobal_8035F8F0_lbl_80479E6C epsilon_guard_table_value_set;
        void TObjEneEpsilonGuard__sub_80361C70(u8 *arg0, s32 arg1);
    s32 is_split_screen();
    s32 get_camera_mode__11TCameraCtrlFv();
    s32 is_main_phase_15__9TObjEneDDFv();
        u32 find_entity_by_id(s32);
    s32 is_state_flag_set__19TObjEneEpsilonGuardFv();
    void TObjEneEpsilonGuard__sub_8035F844(W_8035F844 *arg0, s32 arg1);
    extern T_8035F8A8 lbl_80479E7C[];
    void TObjEneEpsilonGuard__sub_8035DEC0();
    void TObjEneEpsilonGuard__sub_8035FA50(W_8035FA50 *arg0);
    s32 is_guard_active__19TObjEneEpsilonGuardFv();
    s32 TObjEneEpsilonGuard__sub_8035FBBC(W_8035FBBC *arg0);
    s32 TObjEneEpsilonGuard__sub_8035FC20(W_8035FC20 *arg0);
    s32 is_guard_ready__19TObjEneEpsilonGuardFv();
    s32 TObjEneEpsilonGuard__sub_8035FCEC(W_8035FCEC *arg0);
    f32 random_ratio__9TObjCharaFv(s32 arg0);
    s32 TObjEneEpsilonGuard__sub_8035DD74(u8 *arg0);
    void set_target__19TObjEneEpsilonGuardFlll(u32, V3_8035F970 *, s32, s32);
    extern const f64 lbl_80479E88;
    extern Tbl_8035FFA8 epsilon_guard_attack_pattern_table[];
    f32 receive_weapon_special_attack__9TObjCharaFPvPv(void *, void *, void *);
    s32 obj_testFlags30__14TObjCollidableFUl(void *, int);
    u16 get_entity_id(void *);
    void play_sound_effect(s32, void *, s32, s32);
    void handle_guard_action_state__19TObjEneEpsilonGuardFPvi(W_80361508 *self, s32 arg1);
    void queue_destruction__7TObjectFv(void *);
    void *create_particle_emitter(void *pos, s32 id);
    void TObjEneEpsilonGuard__sub_803610D0(u8 *arg0, s32 arg1);
    extern u8 epsilon_guard_destroy_breakup_params[];
    extern s32 lbl_805D6FA4;
        s32 update__15RenderFadeStateFv(void *);
    s32 set_guard_part_colors(void *, void *, void *, int);
    extern s32 saved_model_render_flags;
    extern s32 saved_chunk_polygon_flags_and_mask;
    extern s32 saved_chunk_polygon_flags_or_mask;
    extern s32 epsilon_guard_camera_sample_phase;
    extern u8 *epsilon_guard_angle_sample_write_ptr;
    extern u8 *epsilon_guard_camera_sample_read_ptr;
    extern u8 *epsilon_guard_camera_sample_end_ptr;
    extern s32 chunk_polygon_flags_or_mask;
    extern s32 chunk_polygon_flags_and_mask;
    extern s32 model_render_flags;
    void draw_with_fade__19TObjEneEpsilonGuardFPvi(u8 *arg0, s32 arg1);
    s32 play_persistent_sound(s32 id, s32 a1, u32 src, s32 a3, s32 flags);
    extern Vec4_80360D9C lbl_80479CAC[];
    s32 check_path_obstructed(void *, void *);
    int get_player_data__10TObjPlayerFi(int a0);
    void obj_setFlags30(void *, s32);
    u32 csnVector(void *, void *, s32);
}
s16 obj_getS16_118(u8 *p);
void enemy_turn_and_move_on_ground(u8 *arg0, s32 arg1, f32 farg0);
extern "C"{
        s32 project_actor_to_ground(void *, void *, s32);
    void *get_player_by_client_id(s32 i);
    void *__nw__7TObjectFUl(u32);
    void create_fire_explosion_effect(void *, void *, s32, s32, f32);
    f32 sin_table_lookup(s32);
    f32 cos_table_lookup(s32);
    void subtract_vector(void *, void *);
    extern s32 tl_07;
    void TObjEneEpsilonGuard__sub_803616E4(void *arg0_, s32 arg1);
    void transform_point_to_view(void *, void *);
    extern u8 lbl_805439F0[];
    s32 TObjEneEpsilonGuard__sub_8035DD68();
    void TObjEneEpsilonGuard__sub_8035FB44(u8 *arg0);
    s32 set_flag_8_and_notify__19TObjEneEpsilonGuardFv();
    s32 TObjEneEpsilonGuard__sub_8035FAA8(s32 arg0);
    int TObjEneEpsilonGuard__sub_8035F968(void);
    struct W_8035F8A8;

    typedef char RecoveredGlobal_8035F8F0_lbl_80479E6C_size[sizeof(RecoveredGlobal_8035F8F0_lbl_80479E6C) == 0x10 ? 1 : -1];

    typedef char Induction_8035FAA8_var_r31_size_check[sizeof(Induction_8035FAA8_var_r31) == 0x2 ? 1 : -1];
    typedef char Induction_8035FAA8_var_r31_offset_check[((size_t) & (((Induction_8035FAA8_var_r31_owner*)0)->elements)) == 0x4DC ? 1 : -1];
    typedef char Induction_8035FAA8_var_r31_2_size_check[sizeof(Induction_8035FAA8_var_r31_2) == 0x2 ? 1 : -1];
    typedef char Induction_8035FAA8_var_r31_2_offset_check[((size_t) & (((Induction_8035FAA8_var_r31_2_owner*)0)->elements)) == 0x4DC ? 1 : -1];

    struct W_8035F844;
    struct W_8035FC20;
    struct EpsilonTargetOrder { s32 indices[4]; };
    extern const EpsilonTargetOrder lbl_80479E5C;
    extern s32 registered_player_count;
    extern s32 lbl_805D5870;

    typedef char EpsilonLineList_size[sizeof(EpsilonLineList) == 0x10 ? 1 : -1];
    typedef char RecoveredGlobal_80360638_lbl_805439FC_size[sizeof(RecoveredGlobal_80360638_lbl_805439FC) == 0x1C ? 1 : -1];

    struct W_8035FCEC;

}
extern "C"{
    s32 update_linked_position__12TObjEneDD_STFf(f32);

    int vfunc_89__9TObjEneDDFv(void*);

}
extern "C"{
    void free_collision_body_parts(TObjCollidable *);
    s32 TObjFish__sub_8001EDB0(BmlResource *, s32);
    extern const char *lbl_805D4460;
    extern BattleBaseStats *lbl_805D6F80;
    extern AttackParams *lbl_805D6F84;
    extern ActorParamBlock *lbl_805D6F88;
}
extern TObject *tl_04;
struct EpsilonParameters { u8 reserved[0x20]; s32 field_20; };

#pragma defer_codegen on

TObjEneEpsilonBody::TObjEneEpsilonBody(TObject *parent, s32 *set_data): TObjEneEpsilon(parent) {
    m_name = lbl_805D4460;
    invoke_initialization_hook(set_data);
    init_params();
    set_param(0x54);
    init_position_vectors();
    init_model(epsilon_body_collision, 2);
    m_438 = 0;
    m_438 |= 2;
    set_guard_state();
    texlist = TObjFish__sub_8001EDB0(lbl_805D6FA0, 0);
    set_field_d8((s32)epsilon_body_actions);
    set_field_dc((s32)lbl_805D6FA0->motions);
    set_animation(requested_action);
    set_field_b8(requested_action);
    reset_hp(lbl_805D6F80, lbl_805D6F84, lbl_805D6F88);
    check_state_flag_4();
    movementParameters = &epsilon_body_movement;
    m_37c = 10.0f;
    enemy_init_acquire_period(30);
    enemy_init_validate_period(30);
    m_43e = (s32)(4.0f * random_ratio()) % 4;
    copy_argb(&color, (NJS_ARGB *)&lbl_80479CAC[m_43e]);
    field_440 = m_450;
    m_444 = field_454;
    field_448 = ((EpsilonParameters *)lbl_805D6F8C)->field_20;
    m_4e4 = 0;
    field_4e8 = 0;
    field_4ec = 0;
    field_4f0 = 0;
    field_4f4 = 0;
    m_4f8 = 0.0f;
    effect_position.x = 0.0f;
    effect_position.y = 0.0f;
    effect_position.z = 0.0f;
    target_position.x = 0.0f;
    target_position.y = 0.0f;
    target_position.z = 0.0f;
    for (s32 i = 0; i < 4; ++i) {
        const s32 first_child_id = entity_id + 1;
        const s32 first_child_index = set_index + 1;
        TObjBase *guard = create_guard((u16)(first_child_id + i), first_child_index + i, &position, rotation_y);
        if (guard) guard_ids[i] = get_entity_id(guard);
        VecCopy(&guard_positions[i], &position);
        guard_angles[i] = rotation_y;
    }
    mode = 0;
    dispatch_action(mode, 4);
    for (s32 i = 0; i < 4; ++i) camera_fades[i].activate_and_dispatch();
    emitter_a = 0 ;
    emitter_b = 0 ;
    sub_800F5874(0x3f);
}

TObjEneEpsilonBody::~TObjEneEpsilonBody() {
    free_collision_body_parts(this);
    if (emitter_a) { emitter_a->queue_destruction(); emitter_a = 0 ; }
    if (emitter_b) { emitter_b->queue_destruction(); emitter_b = 0 ; }
    for (s32 i = 0; i < 4; ++i) {
        if (guard_ids[i]) {
            TObject *guard = (TObject *)find_entity_by_id(guard_ids[i]);
            if (guard) guard->queue_destruction();
        }
    }
}

void *create_TObjEneEpsilonBody(void *set_data) {
    return new TObjEneEpsilonBody(tl_04, (s32 *)set_data);
}

void TObjEneEpsilonBody::run_task() {
    if (check_demo_mode() != 0) {
        this->vfunc_105();
        return;
    }
    if (this->vfunc_83() != 4) {
        this->update_guard_flag();
        this->vfunc_85();
    } else if ((s16) this->mode == 1) {
        transition_enemy_state(0);
    }
    if ((s16) this->mode != 9) {
        play_persistent_sound(0x4003AD43, (s32)this, (u32)(((u8 *)this) + 0x38), 0, 0);
    }
    this->vfunc_88();
    update_position();
    ((TObjEnemy *)((u8 *)this))->submit_default_cursor_candidate();
    this->vfunc_100();
}

void TObjEneEpsilonBody::dispatch_action(u32 arg1, s32 arg2) {
    s32 arg0 = (s32)this;
    switch (arg1) {
        case 0:
        ((TObjEneEpsilonBody *)arg0)->sub_80361D4C((arg2));
        return;
        case 1:
        TObjEneEpsilonGuard__sub_80361C70((u8 *)arg0, (arg2));
        return;
        case 2:
        TObjEneEpsilonGuard__sub_803616E4((void *)arg0, (arg2));
        return;
        case 3:
        ((s32 (*)(void *, void *))handle_guard_action_state__19TObjEneEpsilonGuardFPvi) ((void *)arg0, (void *)arg2);
        return;
        case 4:
        action__19TObjEneEpsilonGuardFPvi((void *)arg0, (arg2));
        return;
        case 5:
        TObjEneEpsilonGuard__sub_803610D0((u8 *)arg0, (arg2));
        return;
        case 6:
        ((TObjEneEpsilonGuard *)arg0)->handle_warp_state((arg2));
        return;
        case 7:
        TObjEneEpsilonGuard__sub_80360BF8((u8 *)arg0, (arg2));
        return;
        case 8:
        ((TObjEneEpsilonGuard *)arg0)->update_fade((arg2));
        return;
        case 9:
        ((TObjEneEpsilonBody *)arg0)->action_destroy((arg2));
        default:
        return;
    }
}

void TObjEneEpsilonBody::vfunc_28() { }

void TObjEneEpsilonBody::vfunc_63() { if (this->mode != 9) { ((int (*)(void*, void*))transition_enemy_state__9TObjEneDDFl) (this, (void*)9); } }

void TObjEneEpsilonBody::vfunc_62() {
    s32 temp_r4;
    if ((s16) this->mode != 8) {
        temp_r4 = this->m_438;
        if (!(temp_r4 & 2) && !(temp_r4 & 0x40)) {
            ((int (*)(void*, void*))transition_enemy_state__9TObjEneDDFl) (this, (void*)(8));
        }
    }
}

void TObjEneEpsilonBody::vfunc_61() { }

void TObjEneEpsilonBody::update_position() {
    u8 *arg0 = (u8 *)this;
    *(f32 *)((s8 *)arg0 + 0x2FC) = (f32) *(f32 *)((s8 *)arg0 + 0x38);
    *(f32 *)((s8 *)arg0 + 0x300) = (f32) (24.0f + *(f32 *)((s8 *)arg0 + 0x3C));
    *(f32 *)((s8 *)arg0 + 0x304) = (f32) *(f32 *)((s8 *)arg0 + 0x40);
    ((s32 (*)(void *, void *, void *, f32))VecCopy__FP3VecPC3Vec) ((void *) (arg0 + 0x74), (void *) (arg0 + 0x2FC), arg0, 24.0f);
}

void TObjEneEpsilonBody::vfunc_88() { }

void TObjEneEpsilonBody::vfunc_89() { vfunc_89__9TObjEneDDFv(this); update_position(); }

#pragma push
#pragma opt_common_subs off
void TObjEneEpsilonBody::init_params() {
    f32 frames = 30.0f;
    u8 *arg0 = (u8 *)this;
    this->m_458 = (f32) (0.5f + *(f32 *)((s8 *)arg0 + 0x354));
    if (this->m_458 < 0.0f) {
        this->m_458 = (f32) 0.0f;
    }
    *(s32 *)((s8 *)arg0 + 0x45C) = (s32) (512.0f + *(f32 *)((s8 *)arg0 + 0x358));
    if (this->m_458 <= 0.0f) {
        this->m_458 = (f32) 0.0f;
    }
    this->m_450 = (s32) (20.0f + *(f32 *)((s8 *)arg0 + 0x35C));
    if ((s32) this->m_450 < 5) {
        this->m_450 = 5;
    }
    this->m_450 = (s32) ((f32) this->m_450 * frames);
    *(s32 *)((s8 *)arg0 + 0x454) = (s32) (20.0f + *(f32 *)((s8 *)arg0 + 0x360));
    if ((s32) *(s32 *)((s8 *)arg0 + 0x454) < 5) {
        *(s32 *)((s8 *)arg0 + 0x454) = 5;
    }
    *(s32 *)((s8 *)arg0 + 0x454) = (s32) ((f32) *(s32 *)((s8 *)arg0 + 0x454) * frames);
}
#pragma pop

void TObjEneEpsilonBody::update_guard_flag() {
    if (update_linked_position__12TObjEneDD_STFf(400.0f) == 1) {
        this->m_438 = (s32) (this->m_438 & 0xFFFFFF7F);
        return;
    }
    this->m_438 = (s32) (this->m_438 | 0x80);
}

void TObjEneEpsilonBody::vfunc_105() { }

void TObjEneEpsilonBody::sub_80361D4C(s32 arg1) {
    u8 *arg0 = (u8 *)this;
    switch (arg1) {
        case 4:
        ((s32 (*)(void *, int))set_field_378__9TObjEneDDFl) (arg0, 0);
        ((TObjEneEpsilonBody *)arg0)->vfunc_95();
        this->m_438 = (s32) (this->m_438 | 0x43);
        this->m_438 = (s32) (this->m_438 & 0xFFFFFDFF);
        ((s32 (*)(void *))set_guard_state__18TObjEneEpsilonBodyFv) (arg0);
        VecCopy__FP3VecPC3Vec((u8 *)&this->position, (u8 *)&this->home_position);
        VecCopy__FP3VecPC3Vec((u8 *)&this->prev_position, (u8 *)&this->home_position);
        VecCopy__FP3VecPC3Vec((u8 *)&this->body_center_position, (u8 *)&this->home_position);
        *(s32 *)((s8 *)arg0 + 0x440) = (s32) this->m_450;
        this->m_444 = (s32) *(s32 *)((s8 *)arg0 + 0x454);
        return;
        case 3:
        if (!(this->m_438 & 0x80)) {
            ((s32 (*)(void *, int))transition_enemy_state__9TObjEneDDFl) (arg0, 1);
        }
        case 5:
        case 0:
        return;
    }
}

extern "C" void TObjEneEpsilonGuard__sub_80361C70(u8 *arg0, s32 arg1) {
    s32 temp_r4;
    switch (arg1) {
        case 4:
        set_field_378__9TObjEneDDFl(arg0, 0);
        ((TObjEneEpsilonBody *)(arg0))->vfunc_96();
        ((TObjEneEpsilonBody *)arg0)->m_438 = (s32) (((TObjEneEpsilonBody *)arg0)->m_438 | 0x42);
        temp_r4 = ((TObjEneEpsilonBody *)arg0)->m_438;
        ((TObjEneEpsilonBody *)arg0)->m_438 = (s32) (temp_r4 & ~0x201);
        set_guard_state__18TObjEneEpsilonBodyFv(arg0, temp_r4);
        ((TObjEneEpsilonBody *)arg0)->fade.start_fade_in();
        break;
        case 3:
        if (((TObjEneEpsilonBody *)arg0)->fade.advance_toward_max() != 0) {
            transition_enemy_state__9TObjEneDDFl(arg0, 2);
            break;
        }
        case 5:
        break;
        case 0:
        ((TObjMotion *)arg0)->advance_animation();
        ((TObjEneEpsilonBody *)(arg0))->vfunc_89();
        break;
    }
}

#pragma push
#pragma fp_contract on
extern "C" void TObjEneEpsilonGuard__sub_803616E4(void *arg0_, s32 arg1) {
    f32 *d;
    f32 *tgt;
    u8 *arg0;
    arg0 = (u8 *)arg0_;
    d = (f32 *)(arg0 + 0x4FC);
    tgt = (f32 *)(arg0 + 0x508);
    switch (arg1) {
        case 4:
        set_field_378__9TObjEneDDFl(arg0, 2);
        ((VObj_18_a39899 *)(arg0)) ->m94();
        (*(s32 *)(arg0 + (0x438))) |= 0x42;
        (*(s32 *)(arg0 + (0x438))) &= ~0x309;
        ((void (*)(void *))set_guard_state__18TObjEneEpsilonBodyFv)(arg0);
        (*(s32 *)(arg0 + (0x4E4))) = 0;
        (*(s32 *)(arg0 + (0x4E8))) = 0;
        (*(s32 *)(arg0 + (0x4EC))) = 0;
        (*(s32 *)(arg0 + (0x4F0))) = 0xFFFF;
        (*(s32 *)(arg0 + (0x4F4))) = 0;
        break;
        case 3:
        if ((*(s32 *)(arg0 + (0x438))) & 0x80) {
            transition_enemy_state__9TObjEneDDFl(arg0, 7);
        } else if ((*(s32 *)(arg0 + (0x4E4))) == 1) {
            (*(s32 *)(arg0 + (0x440))) = (*(s32 *)(arg0 + (0x450))) ;
            transition_enemy_state__9TObjEneDDFl(arg0, 3);
        }
        break;
        case 5:
        break;
        case 0:
        ((TObjMotion *)arg0)->advance_animation();
        ((TObjEneEpsilonGuard *)arg0)->tick_timer_set_flag();
        if (!((*(s32 *)(arg0 + (0x438))) & 0x80)) {
            ((TObjEneDD_ST *)arg0)->enemy_copy_target_destination();
            ((TObjEneDD *)arg0)->update_velocity();
            (*(f32 *)(arg0 + (0x4F8))) = (*(f32 *)(arg0 + (0x3A0))) * sin_table_lookup((*(s32 *)(arg0 + (0x60))) ) + (*(f32 *)(arg0 + (0x3A8))) * cos_table_lookup((*(s32 *)(arg0 + (0x60))) );
            if ((*(f32 *)(arg0 + (0x4F8))) < cos_table_lookup(0x1000)) {
                ((TObjEneDD *)arg0)->turn_toward_target_direction((*(s32 *)(arg0 + (0x45C))));
                ((VObj_18_a39899 *)(arg0)) ->m100();
            } else {
                enemy_turn_and_move_on_ground(arg0, (*(s32 *)(arg0 + (0x45C))) , (*(f32 *)(arg0 + (0x458))) );
            }
            if ((*(s32 *)(arg0 + (0x4F0))) != 0xFFFF) {
                u8 *p = (u8 *)get_player_data__10TObjPlayerFi((*(s32 *)(arg0 + (0x4F0))) );
                if (TObjPlayer::is_valid_and_active((u32)p) != 0) {
                    if (check_path_obstructed(arg0, p + 0x2FC) == 1) {
                        (*(s32 *)(arg0 + (0x4E8))) = 0;
                        (*(s32 *)(arg0 + (0x4F0))) = 0xFFFF;
                    } else {
                        VecCopy__FP3VecPC3Vec(tgt, p + 0x38);
                    }
                } else {
                    (*(s32 *)(arg0 + (0x4E8))) = 0;
                    (*(s32 *)(arg0 + (0x4F0))) = 0xFFFF;
                }
            } else {
                (*(s32 *)(arg0 + (0x4E8))) = 0;
            }
        } else {
            (*(s32 *)(arg0 + (0x4E8))) = 0;
        }
        switch ((*(s32 *)(arg0 + (0x4E8))) ) {
            case 0:
            (*(s32 *)(arg0 + (0x438))) &= ~0x100;
            if ((*(s32 *)(arg0 + (0x438))) & 8) {
                (*(s32 *)(arg0 + (0x4E4))) = 1;
            } else {
                (*(s32 *)(arg0 + (0x4F4))) ++;
                (*(s32 *)(arg0 + (0x4F0))) = ((TObjEneEpsilonBody *)arg0)->select_attack_target((*(s32 *)(arg0 + (0x4F4))) );
                if ((*(s32 *)(arg0 + (0x4F0))) != 0xFFFF) {
                    if (TObjPlayer::is_valid_and_active((u32)(get_player_data__10TObjPlayerFi((*(s32 *)(arg0 + (0x4F0))) ))) != 0) {
                        VecCopy__FP3VecPC3Vec(d, arg0 + 0x38);
                        d[1] += 10.0f;
                        if (project_actor_to_ground(arg0, d, 0) != 0) {
                            (*(s32 *)(arg0 + (0x4E8))) = 1;
                            (*(s32 *)(arg0 + (0x4EC))) = *(s32 *)(((u8 *)lbl_805D6F8C) + 0x18);
                        }
                    }
                }
            }
            break;
            case 1: {
                Vec_803616E4 b;
                Vec_803616E4 a;
                f32 s;
                (*(s32 *)(arg0 + (0x438))) |= 0x100;
                VecCopy__FP3VecPC3Vec(&a, tgt);
                VecCopy__FP3VecPC3Vec(&b, d);
                subtract_vector(&a, d);
                normalize_vector_xz((Vec *)(&a));
                s = *(f32 *)(((u8 *)lbl_805D6F8C) + 4);
                b.x += a.x * s;
                b.y += 10.0f;
                b.z += a.z * s;
                if (project_actor_to_ground(arg0, &b, 0) != 0 && csnVector(d, &b, 0x88E0) == 0) {
                    VecCopy__FP3VecPC3Vec(d, &b);
                }
                (*(s32 *)(arg0 + (0x4EC))) --;
                if ((*(s32 *)(arg0 + (0x4EC))) <= 0) {
                    (*(s32 *)(arg0 + (0x4E8))) = 2;
                    (*(s32 *)(arg0 + (0x4EC))) = *(s32 *)(((u8 *)lbl_805D6F8C) + 0x1C);
                }
                play_persistent_sound(0x4003BC47, (s32)arg0, (u32)(arg0 + 0x38), 0, 0);
                break;
            }
            case 2:
            (*(s32 *)(arg0 + (0x438))) |= 0x100;
            (*(s32 *)(arg0 + (0x4EC))) --;
            if ((*(s32 *)(arg0 + (0x4EC))) <= 0) {
                u8 *p;
                s32 i;
                void *e = __nw__7TObjectFUl(0x64);
                if (e != 0) {
                    ((void (*)(void *, f32, void *, s32, s32))create_fire_explosion_effect)(e, 40.0f, d, 0, tl_07);
                }
                play_sound_effect(0x4003A348, arg0 + 0x38, 0, 0);
                for (i = 0; i < 4; i++) {
                    p = (u8 *)get_player_by_client_id(i);
                    if (p != 0 && horizontal_distance_squared((const Vec *)(p + 0x38), (const Vec *)d) <= 1600.0f) {
                        Dmg_803616E4 t;
                        t.a = 1;
                        t.b = *(f32 *)(((u8 *)lbl_805D6F8C) + 8);
                        Dmg_803616E4 s = t;
                        if (((VObj_18_a39899 *)p)->m21(arg0, &s, 0, -1, -1) > 0.0f) {
                            obj_setFlags30(p, 0x600);
                        }
                        play_sound_effect(0x4002A828, p + 0x38, 0, 0);
                    }
                }
                (*(s32 *)(arg0 + (0x4EC))) = 30;
                (*(s32 *)(arg0 + (0x4E8))) = 3;
            }
            break;
            case 3:
            (*(s32 *)(arg0 + (0x438))) &= ~0x100;
            (*(s32 *)(arg0 + (0x4EC))) --;
            if ((*(s32 *)(arg0 + (0x4EC))) <= 0) {
                (*(s32 *)(arg0 + (0x4E8))) = 0;
                (*(s32 *)(arg0 + (0x4F0))) = 0xFFFF;
            }
            break;
            default:
            (*(s32 *)(arg0 + (0x438))) &= ~0x100;
            (*(s32 *)(arg0 + (0x4E8))) = 0;
            (*(s32 *)(arg0 + (0x4F0))) = 0xFFFF;
            break;
        }
        ((VObj_18_a39899 *)(arg0)) ->m87();
        break;
    }
}
#pragma pop

extern "C" void handle_guard_action_state__19TObjEneEpsilonGuardFPvi(W_80361508 *self, s32 arg1) {
    switch (arg1) {
        case 4:
        set_field_378__9TObjEneDDFl(self, 3);
        self->m94();
        self->flags |= 0x42;
        self->flags &= ~0x201;
        ((void (*)(void *))set_guard_state__18TObjEneEpsilonBodyFv)(self);
        self->state = 0;
        self->timer = 0xF;
        play_sound_effect(0x4003A64B, (u8 *)self + 0x38, 0, 0);
        break;
        case 3:
        if (self->state == 3) {
            TObjEneEpsilonGuard__sub_8035FA50((W_8035FA50 *)self);
            self->flags &= ~0x10;
            transition_enemy_state__9TObjEneDDFl(self, 4);
        } else if (self->state == 2) {
            transition_enemy_state__9TObjEneDDFl(self, 2);
        }
        break;
        case 0:
        ((TObjMotion *)self)->advance_animation();
        switch (self->state) {
            case 0:
            self->timer--;
            if (((TObjEneEpsilonGuard *)self)->assign_guard_targets() == 1) {
                self->flags &= ~2;
                ((void (*)(void *))set_guard_state__18TObjEneEpsilonBodyFv)(self);
                self->state = 1;
                self->timer = 0x3C;
            } else if (self->timer <= 0) {
                self->state = 2;
            }
            break;
            case 1:
            self->timer--;
            if (self->timer == 0xF) {
                play_sound_effect(0x4003A345, (u8 *)self + 0x38, 0, 0);
            }
            if (TObjEneEpsilonGuard__sub_8035FBBC((W_8035FBBC *)self) != 0 || self->timer <= 0) {
                self->state = 3;
            }
            break;
        }
        self->m87();
        break;
        case 5:
        return;
    }
}

extern "C" void action__19TObjEneEpsilonGuardFPvi(void *arg0, s32 arg1) {
    s32 temp_r3;
    s32 temp_r4;
    switch (arg1) {
        case 4:
        set_field_378__9TObjEneDDFl(arg0, 4);
        ((TObjEneEpsilonBody *)arg0)->vfunc_96();
        *(s32 *)((s8 *)arg0 + 0x438) = (s32) (*(s32 *)((s8 *)arg0 + 0x438) | 0x400);
        temp_r4 = *(s32 *)((s8 *)arg0 + 0x438);
        *(s32 *)((s8 *)arg0 + 0x438) = (s32) (temp_r4 & ~0x247);
        set_guard_state__18TObjEneEpsilonBodyFv(arg0, temp_r4);
        *(s32 *)((s8 *)arg0 + 0x4E4) = 0;
        return;
        case 3:
        if ((s32) *(s32 *)((s8 *)arg0 + 0x4E4) == 2) {
            transition_enemy_state__9TObjEneDDFl(arg0, 5);
        }
        break;
        case 5:
        break;
        case 0:
        ((TObjMotion *)arg0)->advance_animation();
        ((TObjEneEpsilonGuard *)arg0)->tick_stun_timer();
        switch (*(s32 *)((s8 *)arg0 + 0x4E4)) {
            case 0:
            temp_r3 = *(s32 *)((s8 *)arg0 + 0x438);
            if (((temp_r3 & 4) || (temp_r3 & 0x80)) && (TObjEneEpsilonGuard__sub_8035FCEC((W_8035FCEC *)(arg0)) != 0)) {
                *(s32 *)((s8 *)arg0 + 0x4E4) = 2;
                *(s32 *)((s8 *)arg0 + 0x444) = (s32) *(s32 *)((s8 *)arg0 + 0x454);
            } else {
                TObjEneEpsilonGuard__sub_8035FB44((u8 *)arg0);
                TObjEneEpsilonGuard::update_attack_pattern(arg0);
                if (*(s32 *)((s8 *)arg0 + 0x438) & 0x10) {
                    *(s32 *)((s8 *)arg0 + 0x4E4) = 1;
                    *(s32 *)((s8 *)arg0 + 0x4E8) = (s32) *(s32 *)((s8 *)lbl_805D6F8C + 0x24);
                }
            }
            break;
            case 1:
            *(s32 *)((s8 *)arg0 + 0x4E8) = (s32) (*(s32 *)((s8 *)arg0 + 0x4E8) - 1);
            if ((s32) *(s32 *)((s8 *)arg0 + 0x4E8) <= 0) {
                *(s32 *)((s8 *)arg0 + 0x438) = (s32) (*(s32 *)((s8 *)arg0 + 0x438) & 0xFFFFFFEF);
                *(s32 *)((s8 *)arg0 + 0x4E4) = 0;
            }
            break;
        }
        ((TObjEneEpsilonBody *)arg0)->vfunc_89();
        break;
    }
}

extern "C" void TObjEneEpsilonGuard__sub_803610D0(u8 *arg0, s32 arg1) {
    switch (arg1) {
        case 4:
        set_field_378__9TObjEneDDFl(arg0, 4);
        ((TObjEneDD *)(arg0))->vfunc_96();
        (*(s32 *)(arg0 + (0x438))) &= ~0x253;
        ((void (*)(void *))set_guard_state__18TObjEneEpsilonBodyFv)(arg0);
        (*(s32 *)(arg0 + (0x4E4))) = 0;
        (*(s32 *)(arg0 + (0x4E8))) = 0xF;
        (*(u32 *)(arg0 + (0x434))) = (u32)create_particle_emitter(arg0 + 0x38, 0x225);
        if ((*(u32 *)(arg0 + (0x434))) != 0) {
            ((TParticleCtrl *)((*(void * *)(arg0 + (0x434))) ))->enable();
        }
        play_sound_effect(0x4003A64B, arg0 + 0x38, 0, 0);
        break;
        case 3:
        if ((*(s32 *)(arg0 + (0x4E4))) == 5) {
            transition_enemy_state__9TObjEneDDFl(arg0, 6);
        } else if ((*(s32 *)(arg0 + (0x4E4))) == 4) {
            transition_enemy_state__9TObjEneDDFl(arg0, 4);
        }
        break;
        case 0:
        ((TObjMotion *)arg0)->advance_animation();
        switch ((*(s32 *)(arg0 + (0x4E4))) ) {
            case 0:
            (*(s32 *)(arg0 + (0x4E8))) --;
            if (TObjEneEpsilonGuard__sub_8035FAA8((s32)arg0) == 1) {
                set_field_378__9TObjEneDDFl(arg0, 5);
                (*(s32 *)(arg0 + (0x438))) |= 0x40;
                (*(s32 *)(arg0 + (0x4E4))) = 1;
                (*(s32 *)(arg0 + (0x4E8))) = 0x3C;
            } else if ((*(s32 *)(arg0 + (0x4E8))) <= 0) {
                (*(s32 *)(arg0 + (0x4E4))) = 4;
            }
            if ((*(u32 *)(arg0 + (0x434))) != 0) {
                ((TParticleCtrl *)((*(void * *)(arg0 + (0x434))) ))->enable();
            }
            break;
            case 1:
            (*(s32 *)(arg0 + (0x4E8))) --;
            if (TObjEneEpsilonGuard__sub_8035FCEC((W_8035FCEC *)arg0) != 0 || (*(s32 *)(arg0 + (0x4E8))) <= 0) {
                (*(s32 *)(arg0 + (0x4E4))) = 2;
                (*(s32 *)(arg0 + (0x4E8))) = 8;
            }
            if ((*(u32 *)(arg0 + (0x434))) != 0) {
                ((TParticleCtrl *)((*(void * *)(arg0 + (0x434))) ))->enable();
            }
            break;
            case 2:
            (*(s32 *)(arg0 + (0x4E8))) --;
            if ((*(s32 *)(arg0 + (0x4E8))) <= 0) {
                (*(s32 *)(arg0 + (0x438))) |= 2;
                ((void (*)(void *))set_guard_state__18TObjEneEpsilonBodyFv)(arg0);
                (*(s32 *)(arg0 + (0x4E4))) = 3;
                (*(s32 *)(arg0 + (0x4E8))) = 8;
                play_sound_effect(0x4003A344, arg0 + 0x38, 0, 0);
            }
            if ((*(u32 *)(arg0 + (0x434))) != 0) {
                ((TParticleCtrl *)(*(void * *)(arg0 + (0x434))) )->set_position(arg0 + 0x38);
            }
            break;
            case 3:
            (*(s32 *)(arg0 + (0x4E8))) --;
            if ((*(s32 *)(arg0 + (0x4E8))) <= 0) {
                (*(s32 *)(arg0 + (0x4E4))) = 5;
            }
            if ((*(u32 *)(arg0 + (0x434))) != 0) {
                ((TParticleCtrl *)(*(void * *)(arg0 + (0x434))) )->set_position(arg0 + 0x38);
            }
            break;
        }
        ((TObjEneDD *)(arg0))->vfunc_89();
        break;
        case 5:
        if ((*(u32 *)(arg0 + (0x434))) != 0) {
            queue_destruction__7TObjectFv((*(void * *)(arg0 + (0x434))) );
            (*(u32 *)(arg0 + (0x434))) = 0;
        }
        break;
    }
}

void TObjEneEpsilonGuard::handle_warp_state(s32 arg1) {
    Guard_80360D9C *g = (Guard_80360D9C *)this;
    switch (arg1) {
        case 4:
        set_field_378__9TObjEneDDFl(this, 4);
        this->vfunc_96();
        g->flags |= 0x242;
        g->flags &= ~1;
        ((void (*)(void *))set_guard_state__18TObjEneEpsilonBodyFv)(this);
        g->state = 0;
        g->timer = 0;
        g->alpha = 0.0f;
        g->emitter = (u32)create_particle_emitter(g->f2fc, 0x220);
        break;
        case 3:
        if (g->state == 3) {
            transition_enemy_state__9TObjEneDDFl(this, 2);
        }
        break;
        case 0:
        advance_animation();
        if (g->emitter != 0) {
            ((TParticleCtrl *)(void *)g->emitter)->set_position(g->f2fc);
        }
        switch (g->state) {
            case 0:
            g->alpha += 0.033333335f;
            if (g->alpha >= 1.0f) {
                g->alpha = 1.0f;
                g->state = 1;
                g->timer = 0x1E;
                copy_argb((NJS_ARGB *)&g->pos, (NJS_ARGB *)&lbl_80479CAC[g->idx]);
                f32 transitionFrames = 30.0f;
                g->idx = (g->idx + 1) % 4;
                g->vx = (lbl_80479CAC[g->idx].y - g->pos.y) / transitionFrames;
                g->vy = (lbl_80479CAC[g->idx].z - g->pos.z) / transitionFrames;
                g->vz = (lbl_80479CAC[g->idx].w - g->pos.w) / transitionFrames;
            }
            play_persistent_sound(0x4003A349, (s32)this, (u32)(((u8 *)this) + 0x38), 0, 0);
            break;
            case 1:
            g->timer--;
            g->pos.y += g->vx;
            g->pos.z += g->vy;
            g->pos.w += g->vz;
            if (g->timer <= 0) {
                copy_argb((NJS_ARGB *)&g->pos, (NJS_ARGB *)&lbl_80479CAC[g->idx]);
                g->alpha = 1.0f;
                g->state = 2;
            }
            play_persistent_sound(0x4003A349, (s32)this, (u32)(((u8 *)this) + 0x38), 0, 0);
            break;
            case 2:
            g->alpha = g->alpha - 0.033333335f;
            if (g->alpha <= 0.0f) {
                g->alpha = 0.0f;
                g->state = 3;
                play_sound_effect(0x40039F4A, ((u8 *)this) + 0x38, 0, 0);
            } else {
                play_persistent_sound(0x4003A349, (s32)this, (u32)(((u8 *)this) + 0x38), 0, 0);
            }
            break;
        }
        this->vfunc_89();
        break;
        case 5:
        if (g->emitter != 0) {
            queue_destruction__7TObjectFv((void *)g->emitter);
            g->emitter = 0;
        }
        break;
    }
}

#pragma push
#pragma fp_contract on
extern "C" void TObjEneEpsilonGuard__sub_80360BF8(u8 *arg0, s32 arg1) {
    s32 temp_r4;
    switch (arg1) {
        case 4:
        set_field_378__9TObjEneDDFl((void *)(arg0), 4);
        ((TObjEneEpsilonBody *)(arg0))->vfunc_96();
        ((TObjEneEpsilonBody *)arg0)->m_438 = (s32) (((TObjEneEpsilonBody *)arg0)->m_438 | 0x42);
        temp_r4 = ((TObjEneEpsilonBody *)arg0)->m_438;
        ((TObjEneEpsilonBody *)arg0)->m_438 = (s32) (temp_r4 & ~0x201);
        set_guard_state__18TObjEneEpsilonBodyFv((void *)(arg0), (s32)(temp_r4));
        ((TObjEneEpsilonBody *)arg0)->m_4e4 = 0;
        *(s32 *)((s8 *)arg0 + 0x4E8) = 0x3C;
        return;
        case 5:
        break;
        case 3:
        if ((s32) ((TObjEneEpsilonBody *)arg0)->m_4e4 == 3) {
            transition_enemy_state__9TObjEneDDFl((void *)(arg0), 0);
            ((TObjEneEpsilonBody *)(arg0))->vfunc_95();
        }
        break;
        case 0:
        ((TObjMotion *)arg0)->advance_animation();
        switch (((TObjEneEpsilonBody *)arg0)->m_4e4) {
            case 0:
            if (!(((TObjEneEpsilonBody *)arg0)->m_438 & 0x80)) {
                ((TObjEneEpsilonBody *)arg0)->m_4e4 = 2;
            } else {
                *(s32 *)((s8 *)arg0 + 0x4E8) = (s32) (*(s32 *)((s8 *)arg0 + 0x4E8) - 1);
                if ((s32) ((TObjEneEpsilonBody *)arg0)->m_4e4 <= 0) {
                    ((TObjEneEpsilonBody *)arg0)->m_438 = (s32) (((TObjEneEpsilonBody *)arg0)->m_438 | 0x40);
                    set_field_378__9TObjEneDDFl((void *)(arg0), 4);
                    ((TObjEneEpsilonBody *)arg0)->m_4e4 = 1;
                    ((TObjEneEpsilonBody *)arg0)->fade.reset_color();
                }
            }
            break;
            case 1:
            if (((TObjEneEpsilonBody *)arg0)->fade.decay_value_toward_floor() != 0) {
                VecCopy__FP3VecPC3Vec((void *) (arg0 + 0x38), (void *) (arg0 + 0x50));
                ((TObjEneEpsilonBody *)arg0)->m_438 = (s32) (((TObjEneEpsilonBody *)arg0)->m_438 | 1);
                ((TObjEneEpsilonBody *)arg0)->m_4e4 = 3;
            }
            break;
        }
        ((TObjEneEpsilonBody *)(arg0))->vfunc_89();
        break;
    }
}
#pragma pop

void TObjEneEpsilonGuard::update_fade(s32 arg1) {
    s32 temp_r4;
    switch (arg1) {
        case 4:
        set_field_378__9TObjEneDDFl(this, 2);
        this->vfunc_96();
        this->m_438 = (s32) (this->m_438 | 0x10);
        temp_r4 = this->m_438;
        this->m_438 = (s32) (temp_r4 & ~0x243);
        set_guard_state__18TObjEneEpsilonBodyFv(this, temp_r4);
        *(s32 *)((s8 *)this + 0x4E4) = 0;
        *(u32 *)((s8 *)this + 0x44C) = -0x22U;
        return;
        case 3:
        if ((s32) *(s32 *)((s8 *)this + 0x4E4) == 2) {
            transition_enemy_state__9TObjEneDDFl(this, 4);
        }
        break;
        case 0:
        advance_animation();
        switch (*(s32 *)((s8 *)this + 0x4E4)) {
            case 0:
            *(u32 *)((s8 *)this + 0x44C) = (u32) (*(u32 *)((s8 *)this + 0x44C) + 0x22);
            if ((u32) *(u32 *)((s8 *)this + 0x44C) > 0xFFU) {
                *(u32 *)((s8 *)this + 0x44C) = 0xFFU;
                *(s32 *)((s8 *)this + 0x4E4) = 1;
            }
            break;
            case 1:
            *(u32 *)((s8 *)this + 0x44C) = (u32) (*(u32 *)((s8 *)this + 0x44C) - 0x22);
            if ((u32) *(u32 *)((s8 *)this + 0x44C) <= 0x22U) {
                *(u32 *)((s8 *)this + 0x44C) = 0U;
                *(s32 *)((s8 *)this + 0x4E4) = 2;
            }
            break;
            default:
            *(u32 *)((s8 *)this + 0x44C) = 0U;
            *(s32 *)((s8 *)this + 0x4E4) = 2;
            break;
        }
        this->vfunc_89();
        return;
        case 5:
        clear_attack_receipts__9TObjEneDDFv();
        break;
    }
}

void TObjEneEpsilonBody::action_destroy(s32 arg1) {
    u8 *arg0 = (u8 *)this;
    s32 temp_r4;
    switch (arg1) {
        case 4:
        set_field_378__9TObjEneDDFl(arg0, 9);
        ((TObjEneEpsilonBody *)(arg0))->vfunc_96();
        this->m_438 |= 0x800;
        temp_r4 = this->m_438;
        this->m_438 = temp_r4 & ~0x243;
        set_guard_state__18TObjEneEpsilonBodyFv(arg0, temp_r4);
        ((TObjEnemy *)arg0)->refresh_and_send_entity_flags();
        *(s32 *)((s8 *)arg0 + 0x4E4) = 0;
        *(s32 *)((s8 *)arg0 + 0x4E8) = 0;
        break;
        case 3:
        if (*(s32 *)((s8 *)arg0 + 0x4E4) == 1 && all_children_gone() != 0) {
            queue_destruction__7TObjectFv(arg0);
        }
        break;
        case 5:
        break;
        case 0:
        if (*(s32 *)((s8 *)arg0 + 0x4E4) == 0) {
            ((TObjMotion *)arg0)->advance_animation();
            (*(s32 *)((s8 *)arg0 + 0x4E8))++;
            if (*(s32 *)((s8 *)arg0 + 0x4E8) >= 0x14) {
                ((TObjEneEpsilonBody *)(arg0))->vfunc_95();
                TBoss3Volopt::create_breakup_mdl((s32)lbl_805D6FA4, (s32)epsilon_guard_destroy_breakup_params, (s32)(this->texlist), (s32)(arg0 + 0x2FC), (s32)(this->rotation_y));
                play_sound_effect(0x4003AD4C, (u8 *)&this->body_center_position, 0, 0);
                ((TObjPlayer *)(arg0 + 0x2FC))->trigger_dell_biter_events();
                this->m_438 |= 1;
                *(s32 *)((s8 *)arg0 + 0x4E4) = 1;
            }
        }
        break;
    }
}

#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
void TObjEneEpsilonBody::render() {
    s32 var_r31;
    s32 i;
    if (check_demo_mode() != 0) {
        this->vfunc_106();
        return;
    }
    if (!(this->actorFlags & 0x02000000)) {
        if (is_split_screen() != 0) {
            get_camera_mode__11TCameraCtrlFv();
        }
        if (this->m_438 & 1) {
            var_r31 = 0;
        } else if (is_main_phase_15__9TObjEneDDFv() != 0) {
            var_r31 = ((VObj_18_1fdb47 *)(this))->m9(650.0f, 650.0f, 30.0f);
        } else if (((VObj_18_1fdb47 *)(this))->m8(600.0f, 30.0f) != 0) {
            var_r31 = 1;
        } else {
            var_r31 = 0;
        }
        if (var_r31 != 0) {
            TObjEneDD::draw_ground_shadow(0, 0);
            this->defer_render();
            draw_with_fade__19TObjEneEpsilonGuardFPvi((u8 *)(this), (s32)(var_r31));
            if ((s16) this->mode == 6) {
                if (this->m_438 & 0x200) {
                    this->render_body_effect();
                }
            }
        } else {
            i = 0;
            do {
                sub_803606A0(i);
                i += 1;
            } while (i < 4);
        }
        if ((s16) this->mode == 2) {
            if (this->m_438 & 0x100) {
                ((TObjEneEpsilonGuard *)((u8 *)this))->draw_debug_line();
            }
        }
    }
}
#pragma pop

void TObjEneEpsilonBody::sub_803606A0(s32 i) {
    Obj_803606A0 *g6 = (Obj_803606A0 *)this;
    Tbl_803606A0 t = epsilon_guard_attack_offset_table;
    if (i < 0) {
        i = 0;
    } else if (i > 3) {
        i = 3;
    }
    push_matrix_from(identity_matrix);
    post_translate_matrix(&g6->pos);
    rotate_matrix_y(0, g6->x60);
    set_motion_packed_rotation();
    ((TObjEnemy *)g6)->calc_joint_matrices(g6->xC0);
    clear_motion_packed_rotation();
    pop_matrix();
    push_matrix_from(anim_model_matrix_array[t.v[i]]);
    {
        Vec_803606A0 v = lbl_80479D10;
        matrix_mult_vec(0, &v, &g6->pts[i]);
    }
    pop_matrix();
    g6->ang[i] = (s32)(lbl_80479E90[0] * atan2_float(g6->pts[i].x - g6->pos.x, g6->pts[i].z - g6->pos.z));
}

void TObjEneEpsilonGuard::draw_debug_line() {
    s32 arg0 = (s32)this;
    VecCopy__FP3VecPC3Vec((void *) (&lbl_805439FC.value), (void *) (arg0 + 0x2FC));
    VecCopy__FP3VecPC3Vec((void *) ((u8 *)&lbl_805439FC.value + 0xC), (void *) (arg0 + 0x4FC));
    set_additive_blend();
    draw_line_list((void *) (&TObjEneEpsilonGuard__debug_line_list), 1, 5);
    set_default_alpha_blend();
}

extern "C" void draw_with_fade__19TObjEneEpsilonGuardFPvi(u8 *arg0, s32 arg1) {
    s32 i;
    MaterialColorFade *r;
    i = 0;
    if (is_split_screen() != 0) {
        i = get_camera_mode__11TCameraCtrlFv();
    }
    saved_model_render_flags = model_render_flags;
    saved_chunk_polygon_flags_and_mask = chunk_polygon_flags_and_mask;
    saved_chunk_polygon_flags_or_mask = chunk_polygon_flags_or_mask;
    set_guard_part_colors((void *)arg0, (void *) (arg0 + 0x4A0), (void *)chunk_polygon_flags_and_mask, (int)model_render_flags);
    r = (MaterialColorFade *)&((Self_8036033C *)arg0)->recs[i];
    update__15RenderFadeStateFv(r);
    if (((RenderFadeState *)r)->updateFromCamera((const f32*)(arg0 + 0x2FC)) != 0) {
        r->set_flags_and_apply_damage_color();
        if (!(get_mode__11TCameraCtrlFPv(((s32 *)&main_task)) & 0x200)) {
            model_render_flags = saved_model_render_flags;
            chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;
            chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask;
            return;
        }
    } else if (((TObjEneEpsilonBody *)arg0)->fade.has_visible_opacity() != 0) {
        if (((TObjEneEpsilonBody *)arg0)->fade.has_partial_opacity() != 0) {
            ((TObjEneEpsilonBody *)arg0)->fade.set_flags_and_apply_damage_color();
            if (!(get_mode__11TCameraCtrlFPv(((s32 *)&main_task)) & 0x200)) {
                model_render_flags = saved_model_render_flags;
                chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;
                chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask;
                return;
            }
        } else if (get_mode__11TCameraCtrlFPv(((s32 *)&main_task)) & 0x200) {
            model_render_flags = saved_model_render_flags;
            chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;
            chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask;
            return;
        }
    } else {
        model_render_flags = saved_model_render_flags;
        chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;
        chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask;
        return;
    }
    ((TObjEneDD *)arg0)->update_secondary_light();
    TObjFish::set_global_param(((TObjEneDD_ST *)arg0)->texlist);
    push_matrix();
    post_translate_matrix(arg0 + 0x38);
    translate_matrix(0, 0.0f, 24.0f, 0.0f);
    rotate_matrix_y(0, ((TObjEneDD_ST *)arg0)->rotation_y);
    TObjEneDD::clear_global_flag_400();
    if (*(s32 *)((s8 *)arg0 + 0x438) & 2) {
        set_chunk_model_node_callback((s32)((void *) TObjEneEpsilonGuard::record_camera_angle_samples));
    }
    TObjPlayer::toggle_particle_effect();
    epsilon_guard_camera_sample_read_ptr = arg0 + 0x470;
    epsilon_guard_angle_sample_write_ptr = arg0 + 0x460;
    epsilon_guard_camera_sample_end_ptr = arg0 + 0x38;
    if (((TObjEneDD_ST *)arg0)->mode == 8) {
        s32 c = (*(s32 *)((s8 *)arg0 + 0x44C) & 0xFF) << 0x10;
        epsilon_guard_camera_sample_phase = -1;
        ((TObjEneDD_ST *)arg0)->draw_with_alt_model(c | 0xFF000000);
    } else {
        epsilon_guard_camera_sample_phase = 0;
        if (arg1 == 1) {
            ((TObjMotion *)arg0)->draw();
        } else {
            ((TObjEnemy *)arg0)->draw_motion_model();
        }
    }
    TParticleCtrl::end_effect_render();
    if (*(s32 *)((s8 *)arg0 + 0x438) & 2) {
        set_chunk_model_node_callback((s32)0);
    }
    pop_matrix();
    ((TObjEneDD *)arg0)->update_primary_light();
    if (((RenderFadeState *)r)->updateFromCamera((const f32*)(arg0 + 0x2FC)) != 0) {
        r->clear_flag_and_notify();
    } else if ((((TObjEneEpsilonBody *)arg0)->fade.has_visible_opacity() != 0) && (((TObjEneEpsilonBody *)arg0)->fade.has_partial_opacity() != 0)) {
        ((TObjEneEpsilonBody *)arg0)->fade.clear_flag_and_notify();
    }
    model_render_flags = saved_model_render_flags;
    chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;
    chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask;
}

void TObjEneEpsilonBody::render_body_effect() {
    u8 *arg0 = (u8 *)this;
    f32 temp_f1;
    if (get_mode__11TCameraCtrlFPv(((s32 *)&main_task)) & 0x200) {
        push_matrix();
        post_translate_matrix((void *) (arg0 + 0x38));
        translate_matrix(0, 0.0f, 24.0f, 0.0f);
        rotate_matrix_y(0, (int) (this->rotation_y));
        temp_f1 = this->m_4f8;
        scale_matrix(0, temp_f1, 1.0f, temp_f1);
        TObjFish::set_global_param((int) (this->texlist));
        TObjPlayer::toggle_particle_effect();
        get_bml_model(lbl_805D6FA0, 4);
        draw_chunk_object();
        TParticleCtrl::end_effect_render();
        pop_matrix();
    }
}

void TObjEneEpsilonGuard::record_camera_angle_samples() {
    switch (epsilon_guard_camera_sample_phase) {
        case 0x1C:
        case 0x26:
        case 0x30:
        case 0x3A:
        transform_point_to_view(lbl_805439F0, (*(f32 * *)&epsilon_guard_camera_sample_read_ptr));
        *(*(s32 * *)&epsilon_guard_angle_sample_write_ptr) = (s32)((*(const f64 *)&lbl_80479E90) * atan2_float(
        (*(f32 * *)&epsilon_guard_camera_sample_read_ptr)[0] - (*(f32 * *)&epsilon_guard_camera_sample_end_ptr)[0],
        (*(f32 * *)&epsilon_guard_camera_sample_read_ptr)[2] - (*(f32 * *)&epsilon_guard_camera_sample_end_ptr)[2]));
        (*(f32 * *)&epsilon_guard_camera_sample_read_ptr) += 3;
        (*(s32 * *)&epsilon_guard_angle_sample_write_ptr)++;
        break;
    }
    epsilon_guard_camera_sample_phase++;
}

void TObjEneEpsilonBody::vfunc_106() { }

void TObjEneEpsilonBody::set_guard_state() {
    void *arg0 = (void *)this;
    if (this->m_438 & 2) {
        *(s16 *)((s8 *)arg0 + 0x43C) = 1;
        *(s32 *)((s8 *)arg0 + 0x34) = get_bml_model(lbl_805D6FA0, 0);
        this->requested_action = 0;
        ((TObjCollidable *)arg0)->set_indexed_flags(1, 1);
        ((TObjCollidable *)arg0)->clear_player_status_flag(0, 1);
    } else {
        *(s16 *)((s8 *)arg0 + 0x43C) = 0;
        *(s32 *)((s8 *)arg0 + 0x34) = get_bml_model(lbl_805D6FA0, 1);
        this->requested_action = 1;
        ((TObjCollidable *)arg0)->set_indexed_flags(0, 1);
        ((TObjCollidable *)arg0)->clear_player_status_flag(1, 1);
    }
    ((TObjMotion *)arg0)->advance_animation();
}

void TObjEneEpsilonGuard::tick_timer_set_flag() {
    this->m_440 = (s32) (this->m_440 - 1);
    if ((s32) this->m_440 <= 0) {
        this->m_438 = (s32) (this->m_438 | 8);
    }
}

void TObjEneEpsilonGuard::tick_stun_timer() {
    *(s32 *)((s8 *)this + 0x444) = (s32) (*(s32 *)((s8 *)this + 0x444) - 1);
    if ((s32) *(s32 *)((s8 *)this + 0x444) <= 0) {
        this->m_438 = (s32) (this->m_438 | 4);
    }
}

void TObjEneEpsilonGuard::update_attack_pattern(void *arg0) {
    Tbl_8035FFA8 t = epsilon_guard_attack_pattern_table[0];
    s32 *row;
    s32 i;
    if (((Self_8035FFA8 *)arg0) ->flags & 0x400) {
        ((Self_8035FFA8 *)arg0) ->timer--;
        if (((Self_8035FFA8 *)arg0) ->timer <= 0) {
            row = t.v[(s32)(20.0f * random_ratio__9TObjCharaFv((s32)((Self_8035FFA8 *)arg0) )) % 20];
            for (i = 0; i < 4; i++) {
                if (row[i] == 1) {
                    TObjEneEpsilonGuard__sub_8035F844((W_8035F844 *)((Self_8035FFA8 *)arg0) , i);
                }
            }
            ((Self_8035FFA8 *)arg0) ->flags &= ~0x400;
        }
    } else if (TObjEneEpsilonGuard__sub_8035FC20((W_8035FC20 *)((Self_8035FFA8 *)arg0) ) != 0) {
        ((Self_8035FFA8 *)arg0) ->flags |= 0x400;
        ((Self_8035FFA8 *)arg0) ->timer = *(s32 *)((u8 *)lbl_805D6F8C + 0x20);
    }
}

#pragma push
#pragma fp_contract off
u32 TObjEneEpsilonBody::select_attack_target(s32 sequence) {
    EnemyTargetCandidate candidates[4];
    candidates[0].id = 0xFFFF;
    candidates[0].distance_squared = 0.0f;
    EpsilonTargetOrder order = lbl_80479E5C;
    s32 count = 0;
    s32 playerCount;
    if (vfunc_99() != 0) {
        playerCount = registered_player_count + lbl_805D5870;
    } else {
        playerCount = registered_player_count;
    }
    for (s32 i = 0; i < playerCount; i++) {
        TObjPlayer *player = TObjPlayer::get_player_data(i);
        if (TObjPlayer::is_valid_and_active((u32)player) == 0) continue;
        if (player->actorFlags & 0x2000800) continue;
        Vec difference;
        VecCopy(&difference, (Vec *)&player->body_center_position);
        subtract_vector(&difference, (Vec *)&body_center_position);
        f32 distance = difference.x * difference.x + difference.z * difference.z;
        if (!(distance < 160000.0f)) continue;
        if (check_path_obstructed(this, (Vec *)&player->body_center_position) == 1) continue;
        candidates[count].distance_squared = distance;
        candidates[count].id = i;
        count++;
        if (count >= 4) break;
    }
    if (count <= 0) return 0xFFFF;
    if (count >= 2) {
        for (s32 i = 0; i < count - 1; i++) {
            for (s32 j = i + 1; j < count; j++) {
                if (candidates[i].distance_squared > candidates[j].distance_squared) {
                    EnemyTargetCandidate temporary;
                    temporary.copy_from(&candidates[i]);
                    candidates[i].copy_from(&candidates[j]);
                    candidates[j].copy_from(&temporary);
                }
            }
        }
    }
    for (s32 i = count; i < 4; i++) {
        candidates[i].copy_from(&candidates[i % count]);
    }
    return candidates[order.indices[sequence % 4]].id;
}
#pragma pop

extern "C" s32 TObjEneEpsilonGuard__sub_8035FCEC(W_8035FCEC *arg0) {
    s32 i;
    for (i = 0; i < 4; i++) {
        find_entity_by_id(arg0->h[i]);
        if (is_guard_ready__19TObjEneEpsilonGuardFv() == 0) {
            return 0;
        }
    }
    return 1;
}

s32 TObjEneEpsilonBody::all_children_gone() {
    W_8035FC8C *arg0 = (W_8035FC8C *)this;
    s32 i;
    for (i = 0; i < 4; i++) {
        if (find_entity_by_id(arg0->h[i]) != 0) {
            return 0;
        }
    }
    return 1;
}

extern "C" s32 TObjEneEpsilonGuard__sub_8035FC20(W_8035FC20 *arg0) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (find_entity_by_id(arg0->h[i]) != 0 && is_state_flag_set__19TObjEneEpsilonGuardFv() == 0) {
            return 0;
        }
    }
    return 1;
}

extern "C" s32 TObjEneEpsilonGuard__sub_8035FBBC(W_8035FBBC *arg0) {
    s32 i;
    for (i = 0; i < 4; i++) {
        find_entity_by_id(arg0->h[i]);
        if (is_guard_active__19TObjEneEpsilonGuardFv() == 0) {
            return 0;
        }
    }
    return 1;
}

extern "C" void TObjEneEpsilonGuard__sub_8035FB44(u8 *arg0) {
    s32 var_r30;
    var_r30 = 0;
    *(s32 *)((s8 *)arg0 + 0x438) = (s32) (*(s32 *)((s8 *)arg0 + 0x438) & 0xFFFFFFDF);
    do {
        if ((find_entity_by_id((s32) *(u16 *)((s8 *)(arg0 + var_r30 * 2) + 0x4DC)) != 0U) && (TObjEneEpsilonGuard__sub_8035DD68() == 1)) {
            *(s32 *)((s8 *)arg0 + 0x438) = (s32) (*(s32 *)((s8 *)arg0 + 0x438) | 0x20);
        }
        var_r30 += 1;
    } while (var_r30 < 4);
}

extern "C" s32 TObjEneEpsilonGuard__sub_8035FAA8(s32 arg0) {
    s32 var_r30;
    s32 var_r30_2;
    var_r30 = 0;
    loop_1:
    if ((find_entity_by_id((s32)((int) (*(u16 *)((s8 *)((s32)&((Induction_8035FAA8_var_r31_owner *)arg0)->elements[var_r30]) + 0)))) != 0U) && (is_guard_ready__19TObjEneEpsilonGuardFv() == 0)) {
        return 0;
    }
    var_r30 += 1;
    if (var_r30 >= 4) {
        var_r30_2 = 0;
        do {
            if (find_entity_by_id((s32)((int) (*(u16 *)((s8 *)((s32)&((Induction_8035FAA8_var_r31_2_owner *)arg0)->elements[var_r30_2]) + 0)))) != 0U) {
                set_flag_8_and_notify__19TObjEneEpsilonGuardFv();
            }
            var_r30_2 += 1;
        } while (var_r30_2 < 4);
        return 1;
    }
    goto loop_1;
}

extern "C" void TObjEneEpsilonGuard__sub_8035FA50(W_8035FA50 *arg0) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (find_entity_by_id(arg0->h[i]) != 0) {
            TObjEneEpsilonGuard__sub_8035DEC0();
        }
    }
}

s32 TObjEneEpsilonGuard::assign_guard_targets() {
    s32 i;
    s32 near;
    u32 p;
    for (i = 0; i < 4; i++) {
        p = find_entity_by_id(((Guard_8035F970 *)this)->h[i]);
        if (p != 0 && TObjEneEpsilonGuard__sub_8035DD74((u8 *)p) == 0) {
            return 0;
        }
    }
    near = random_ratio__9TObjCharaFv((s32)this) < lbl_80479E88;
    for (i = 0; i < 4; i++) {
        p = find_entity_by_id(((Guard_8035F970 *)this)->h[i]);
        if (p != 0) {
            set_target__19TObjEneEpsilonGuardFlll(p, &((Guard_8035F970 *)this)->pos[i], ((Guard_8035F970 *)this)->ids[i], near);
        }
    }
    return 1;
}

extern "C" int TObjEneEpsilonGuard__sub_8035F968(void) { return 0; }

s32 TObjEneEpsilonBody::has_state_flag_0x20() { return (m_438 >> 5) & 1; }

s32 TObjEneEpsilonBody::has_state_flag_0x800() { return (m_438 >> 11) & 1; }

s16 TObjEneEpsilonBody::get_table_value_by_index() {
    typedef char sp8_offset[(((size_t) & (((Stack_8035F8F0*)0)->sp8)) == 0x0) ? 1 : -1];
    typedef char spC_offset[(((size_t) & (((Stack_8035F8F0*)0)->spC)) == 0x4) ? 1 : -1];
    typedef char sp10_offset[(((size_t) & (((Stack_8035F8F0*)0)->sp10)) == 0x8) ? 1 : -1];
    typedef char sp14_offset[(((size_t) & (((Stack_8035F8F0*)0)->sp14)) == 0xC) ? 1 : -1];
    Stack_8035F8F0 stack;
    s16 temp_r7;
    temp_r7 = this->m_43e;
    stack.sp8 = *(s32 *)((s8 *)(&epsilon_guard_table_value_set.value) + 0);
    stack.spC = *(s32 *)((s8 *)(&epsilon_guard_table_value_set.value) + 4);
    stack.sp10 = *(s32 *)((s8 *)(&epsilon_guard_table_value_set.value) + 8);
    stack.sp14 = *(s32 *)((s8 *)(&epsilon_guard_table_value_set.value) + 0xC);
    if ((temp_r7 < 0) || (temp_r7 > 3)) {
        return 0;
    }
    return (s16) (&stack.sp8)[temp_r7];
}

s16 TObjEneEpsilonBody::sub_8035F8A8() {
    s16 i = ((W_8035F8A8 *)this)->idx;
    T_8035F8A8 t = lbl_80479E7C[0];
    if (i < 0 || i > 3) {
        return 0;
    }
    return t.v[i];
}

extern "C" void TObjEneEpsilonGuard__sub_8035F844(W_8035F844 *arg0, s32 arg1) {
    u32 r;
    if (arg1 < 0 || arg1 >= 4) {
        return;
    }
    r = find_entity_by_id(arg0->h[arg1]);
    if (r != 0 && is_state_flag_set__19TObjEneEpsilonGuardFv() == 1) {
        ((TObjEneEpsilonGuard *)r)->clear_and_flag_state();
    }
}

f32 TObjEneEpsilonBody::receive_direct_attack(void *source, DirectAttackPayload attack, void *hit, s32 arg3, s32 arg4) {
    if (!(m_438 & 2) && !(m_438 & 0x40)) {
        if (attack.kind != get_table_value_by_index()) {
            return TObjChara::receive_direct_attack(source, attack, hit, arg3, arg4);
        }
    } else if (attack.kind == 20) {
        return TObjChara::receive_direct_attack(source, attack, hit, arg3, arg4);
    }
    try_apply_damage((u32)&body_center_position, 0);
    return 0.0f;
}

f32 TObjEneEpsilonBody::receive_physical_attack(void *arg1_arg, f32 farg0) {
    u8 *att = (u8 *)arg1_arg;
    s32 temp_r5;
    temp_r5 = this->m_438;
    if (!(temp_r5 & 2) && !(temp_r5 & 0x40)) {
        return receive_physical_attack__9TObjCharaFPvf(this, att, farg0);
    }
    try_apply_damage((u32) (((u8 *)this) + 0x2FC), 0);
    return 0.0f;
}

f32 TObjEneEpsilonBody::receive_weapon_special_attack(void *src, void *hit) {
    if (!(((Self_8035F5C8 *)this)->flags & 2) && !(((Self_8035F5C8 *)this)->flags & 0x40)) {
        s16 kind = ((TObjPlayer *)src)->obj_getS16_116();
        s32 strong;
        obj_getS16_118((u8 *)src);
        strong = 0;
        if (src == 0 || get_entity_id(src) == 0xFFFF) {
            ((TObjChara *)((Self_8035F5C8 *)this))->show_miss_popup((const float *)(((Self_8035F5C8 *)this)->x38));
            return 0.0f;
        }
        if (obj_testFlags30__14TObjCollidableFUl(this, 0x04000000) != 0) {
            strong = 1;
        }
        if (((Hit_8035F5C8 *)hit) != 0 && (((Hit_8035F5C8 *)hit)->flags & 0x02000000)) {
            strong = 1;
        }
        if (strong != 0) {
            switch (kind) {
                case 0:
                break;
                case 1:
                case 2:
                case 5:
                case 6:
                case 7:
                case 9:
                case 10:
                ((TObjChara *)((Self_8035F5C8 *)this))->try_apply_damage((u32)((Self_8035F5C8 *)this)->x2FC, 0);
                break;
                case 3:
                case 4:
                case 8:
                case 11:
                case 12:
                case 13:
                ((TObjChara *)((Self_8035F5C8 *)this))->show_miss_popup((const float *)(((Self_8035F5C8 *)this)->x2FC));
                break;
            }
            return 0.0f;
        }
        if (((TObjPlayer *)src)->obj_getS16_116() != ((TObjEneEpsilonBody *)this)->sub_8035F8A8()) {
            return receive_weapon_special_attack__9TObjCharaFPvPv(this, src, ((Hit_8035F5C8 *)hit));
        }
    }
    ((TObjChara *)((Self_8035F5C8 *)this))->try_apply_damage((u32)((Self_8035F5C8 *)this)->x2FC, 0);
    return 0.0f;
}
