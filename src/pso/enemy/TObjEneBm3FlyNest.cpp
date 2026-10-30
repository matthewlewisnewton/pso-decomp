#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/npc/NpcAnimationBinding.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/system/MatrixStack.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/object/TObjFish.h"
#include "pso/system/MatrixOps.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/system/SoundEffect.h"
#include "pso/misc/TOTrapAncient01_80226534.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/system/EnemyBmlResource.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/enemy/TObjEneRe7Berura_803E4CE0.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/system/vector.h"
#include "types.h"
#include "pso/enemy/TObjEneBm3FlyNest_CarryFly.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjChara.h"
#include "pso/enemy/TObjEneBm3Fly.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/object/TObjMotion.h"
#include "pso/enemy/TObjEneBm3FlyNest.h"
#include "pso/system/BmlResource.h"

extern "C" void has_flag_0x800__9TObjCharaFv();
extern "C" void test_flag30_512__9TObjCharaFv();
extern "C" void test_flag_1000__9TObjCharaFv();
extern "C" void test_flag_256__9TObjCharaFv();

#include "pso/enemy/TObjEneDD_ST.h"
#include <stddef.h>
#include "pso/TObject.h"
#include "pso/TParticleCtrl.h"
#include "pso/boss/TBoss8Dragon.h"
#include "pso/boss/TObjBoss2Tunnel.h"
#include "pso/enemy/TObjEnePanarms.h"
#include "pso/enemy/TObjEneRe7Berura.h"
#include "pso/misc/RenderFadeState.h"
#include "pso/misc/TLobby.h"

#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/npc/NpcModelRegistry.h"

struct VBase_800B3EB8 { char pad[0x18]; };
struct VObj_800B3EB8 : VBase_800B3EB8 {
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual void p3();
    virtual void p4();
    virtual void p5();
    virtual void p6();
    virtual void p7();
    virtual void p8();
    virtual void p9();
    virtual void p10();
    virtual void p11();
    virtual void p12();
    virtual void p13();
    virtual void p14();
    virtual void p15();
    virtual void p16();
    virtual void p17();
    virtual void p18();
    virtual void p19();
    virtual void p20();
    virtual void p21();
    virtual void p22();
    virtual void p23();
    virtual void p24();
    virtual void p25();
    virtual void p26();
    virtual void p27();
    virtual void p28();
    virtual void p29();
    virtual void p30();
    virtual void p31();
    virtual void p32();
    virtual void p33();
    virtual void p34();
    virtual void p35();
    virtual void p36();
    virtual void p37();
    virtual void p38();
    virtual void p39();
    virtual void p40();
    virtual void p41();
    virtual void p42();
    virtual void p43();
    virtual void p44();
    virtual void p45();
    virtual void p46();
    virtual void p47();
    virtual void p48();
    virtual void p49();
    virtual void p50();
    virtual void p51();
    virtual void p52();
    virtual void p53();
    virtual void p54();
    virtual void p55();
    virtual void p56();
    virtual void p57();
    virtual void p58();
    virtual void p59();
    virtual void p60();
    virtual void p61();
    virtual void p62();
    virtual void p63();
    virtual void p64();
    virtual void p65();
    virtual void p66();
    virtual void p67();
    virtual void p68();
    virtual void p69();
    virtual void p70();
    virtual void p71();
    virtual void p72();
    virtual void p73();
    virtual void p74();
    virtual void p75();
    virtual void p76();
    virtual void p77();
    virtual void p78();
    virtual void p79();
    virtual void p80();
    virtual void p81();
    virtual void p82();
    virtual void p83();
    virtual void p84();
    virtual void m85(s16, int);
    virtual void m86();
};

extern const f32 lbl_805D9D6C;

extern "C" {




































struct VBase_18 { char pad[0x18]; };



struct VObj_18_p5 : VBase_18 {
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
    virtual s32 m81();
    virtual void m82();
    virtual s32 m83();
    virtual void m84();
    virtual void m85();
    virtual s32 m86();
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
    virtual s32 m98();
    virtual void m99();
    virtual void m100();
    virtual void m101();
    virtual s32 m102();
};

struct Obj_800B3E40 { u8 pad[0x18]; void *vtbl; u8 pad2[0x440 - 0x1c]; u8 arr[4][0x1c]; };


s32 is_split_screen();
f32 atan2_float(f32 y, f32 x);
s32 dispatch_shared_handler_a__6TLobbyFl(int);
s32 register_object__6TLobbyFl(int);
s32 dispatch_shared_handler_b__6TLobbyFl(int);
s32 register_boss__6TLobbyFl(int);
s32 get_camera_mode__11TCameraCtrlFv();
void rotate_xz_pair_by_angle(f32 *arg0, f32 *arg1, s32 arg2);
void *spawn_particle_effect(void *pos, s32 id);
void render_with_state_debug__17TObjEneBm3FlyNestFv(u8 *arg0);
void render__17TObjEneBm3FlyNestFv(u8 *arg0);
void init_params__17TObjEneBm3FlyNestFv(void *arg0);
void vfunc_88__17TObjEneBm3FlyNestFv(void* p);
void vfunc_61__17TObjEneBm3FlyNestFv(void);
void vfunc_62__17TObjEneBm3FlyNestFv(void *arg0);
void vfunc_63__17TObjEneBm3FlyNestFv(void *arg0);
void vfunc_28__17TObjEneBm3FlyNestFv(void);
void dispatch_state__17TObjEneBm3FlyNestFiUii(s32 arg0, u32 arg1, s32 arg2);
void run_task__17TObjEneBm3FlyNestFv(u8 *arg0);
Obj_800B3E40 * TObjEneBm3FlyNest__sub_800B3E40(Obj_800B3E40 *self, s16 flag);
void * TObjEneBm3FlyNest__ct(void *, void *, void *);
s32 is_main_phase_15__9TObjEneDDFv();
void update_player_state__9TObjEneDDFv(void *, Vec *, s32);
void get_camera_ctrl__9TObjEneDDFv(s32, s32);
s32 get_random_scaled__9TObjEneDDFv(void *);
s32 noop__12TBoss8DragonFv(void *);
s32 TBoss8Dragon__sub_800BB7D4(void *, s32);
s32 pack_debug_text_position(s32, s32);
void *__dt__9TObjEneDDFv(void *arg0, s16 arg1);
s32 update__15RenderFadeStateFv(void *);
void *__dt__15RenderFadeStateFv(void *arg0, s16 arg1);
s32 set_field_e4__10TObjPlayerFll(void *, int, f32);
void spawn_dead_spot_scale15(s32 point, s32 delay);
void *find_entity_by_id(u16 id);
void free_collision_body_parts(void *);
s32 send_entity_set_flags__9TObjEnemyFv();
s32 defer_render__7TObjectFv(void *);
void __dl__7TObjectFPv(void *);
void * __nw__7TObjectFUl(int);
void __dt__7TObjectFv(void *, int);
void __destroy_arr(void *, void *, u32, u32);
f32 sin_table_lookup(int);
f32 cos_table_lookup(int);
void debug_printf_at(s32, const char *, ...);
void draw_chunk_object(void *child);
void draw_model_motion(void *arg0, void *arg1, f32 farg0);

void vfunc_6__8TObjBaseFPsl();
void vfunc_103__9TObjEneDDFPUc();
void vfunc_79__9TObjEneDDFPl();
void vfunc_83__9TObjEneDDFv();
void vfunc_84__9TObjEneDDFv();
void vfunc_85__9TObjEneDDFv();
void vfunc_86__9TObjEneDDFv();
void vfunc_89__9TObjEneDDFv();
void vfunc_90__9TObjEneDDFv();
void vfunc_91__9TObjEneDDFv();
void vfunc_92__9TObjEneDDFv();
void vfunc_93__9TObjEneDDFv();
void vfunc_94__9TObjEneDDFv();
void vfunc_95__9TObjEneDDFv();
void vfunc_96__9TObjEneDDFv();
void vfunc_97__9TObjEneDDFv();
void vfunc_98__9TObjEneDDFv();
void vfunc_99__9TObjEneDDFv();
void vfunc_100__9TObjEneDDFv();
void vfunc_101__9TObjEneDDFPUc();
void vfunc_102__9TObjEneDDFv();
void vfunc_29__9TObjCharaFv();
void recalc_stats__9TObjCharaFv();
void consume_timer_field__9TObjCharaFl();
void vfunc_67__9TObjCharaFf();
void vfunc_66__9TObjCharaFv();
void get_anim_node_position__9TObjCharaFlP3Vec();
void vfunc_60__9TObjCharaFv();
void vfunc_59__9TObjCharaFv();
void vfunc_58__9TObjCharaFv();
void apply_slow_status__9TObjCharaFv();
void update_shock_clock__9TObjCharaFv();
void vfunc_43__9TObjCharaFv();
void vfunc_18__9TObjCharaFPUc();
void interact__14TObjCollidableFl();
void vfunc_74__9TObjEnemyFl();
void apply_hit_message_flags__9TObjEnemyFPv();
void add_actor_exp__9TObjCharaFl();
void apply_action_hold_status__9TObjCharaFf();
void apply_anti_technique__9TObjCharaFl();
void apply_attack_stat_status__9TObjCharaFPv();
void apply_confusion_status__9TObjCharaFv();
void apply_knockback_from_attacker__9TObjCharaFPUcf();
void apply_movement_ailment__9TObjCharaFl();
void apply_object_set_data__8TObjBaseFPv();
void apply_paralysis__9TObjCharaFv();
void apply_poison_status__9TObjCharaFv();
void apply_set_data__9TObjEnemyFPv();
void apply_shock_status__9TObjCharaFv();
void apply_switch_attack__9TObjCharaFv();
void calc_distance_accuracy_penalty__9TObjCharaFPvPvPvf();
void classify_actor_view_detail__8TObjBaseFfff();
void clear_all_status_effects__9TObjCharaFv();
void clear_harmful_statuses__9TObjCharaFv();
void cure_paralysis__9TObjCharaFv();
void cure_poison_ailment__9TObjCharaFv();
void enemy_spawn_jellen_effect__9TObjCharaFv();
void enemy_spawn_zalure_effect__9TObjCharaFv();
void vfunc_78__9TObjCharaFl();
void vfunc_77__9TObjCharaFv();
void vfunc_76__9TObjCharaFv();
void vfunc_75__9TObjCharaFf();
void clear_lobby_object_state__9TObjEnemyFv();
void get_center__9TObjCharaFv();
void get_actor_level_index__9TObjCharaFv();
void get_name__9TObjEnemyFv();
void get_pos__9TObjCharaFl();
void is_actor_cadence_frame__9TObjCharaFl();
void is_target_in_attack_range__9TObjCharaFv();
void receive_direct_attack__9TObjCharaFPv19DirectAttackPayloadPvll();
void receive_physical_attack__9TObjCharaFPvf();
void receive_weapon_special_attack__9TObjCharaFPvPv();
void apply_defense_stat_status__9TObjCharaFPv();
void render_shadows__17TObjEneBm3FlyNestFv();
void reset_motion_fields__9TObjCharaFv();
void reset_pose__9TObjCharaFv();
void roll_physical_accuracy__9TObjCharaFPvlf();
void select_melee_contact_body__9TObjCharaFPvf();
void trigger_switch_attack__9TObjCharaFv(s32 arg0);
void try_start_action__9TObjCharaFll();
void update_action_hold_status__9TObjCharaFv();
s32 vfunc_37__9TObjCharaFv(u8 *arg0);
void update_actor_ground_y__9TObjCharaFv();
s32 update_attack_stat_status__9TObjCharaFv(u8 *arg0);
s32 update_defense_stat_status__9TObjCharaFv(u8 *arg0);
void update_flag30_timer__9TObjCharaFv();
void update_movement_status__9TObjCharaFv();
void update_object_view_visibility__8TObjBaseFff();
void update_poison_status__9TObjCharaFv();
extern const char fly_body_model_filename[];
extern const char fly_nest_model_filename[];
extern const char fly_attack_motion_filename[];
extern const char fly_damage_motion_filename[];
extern const char nest_damage_motion_filename[];
extern const char fly_death_motion_filename[];
extern const char nest_death_motion_filename[];
extern const char nest_fall_motion_filename[];
extern const char fallen_nest_damage_motion_filename[];
extern const char fallen_nest_emit_motion_filename[];
extern const char fallen_nest_wait_motion_filename[];
extern const char nest_emit_motion_filename[];
extern const char fly_flight_motion_filename[];
extern const char nest_land_motion_filename[];
extern const char fly_move_motion_filename[];
extern const char nest_trance_motion_filename[];
extern const char nest_wait_motion_filename[];
extern const char fly_bml_filename[];
struct Params_80491DA0 { f32 f00; u32 w[6]; };
Params_80491DA0 bm3_fly_nest_params = { 225.0f, { 0x0, 0x600, 0x0, 0x0, 0x0, 0x0 } };
CollisionBody bm3_flynest_collider_params = { { 0.0f, 0.0f, 0.0f }, 10.0f, 0.0f, 0, 0x8003, { 0.0f, 0.0f, 0.0f }, 0.0f };
const char *bm_ene_bm3_fly_model_names[3] = { fly_body_model_filename, fly_nest_model_filename, 0 };
const char *bm_ene_bm3_fly_motion_names[16] = { fly_attack_motion_filename, fly_damage_motion_filename, nest_damage_motion_filename, fly_death_motion_filename, nest_death_motion_filename, nest_fall_motion_filename, fallen_nest_damage_motion_filename, fallen_nest_emit_motion_filename, fallen_nest_wait_motion_filename, nest_emit_motion_filename, fly_flight_motion_filename, nest_land_motion_filename, fly_move_motion_filename, nest_trance_motion_filename, nest_wait_motion_filename, 0 };
BmlResourceDescriptor bm3_fly_nest_resource_desc = { fly_bml_filename, bm_ene_bm3_fly_model_names, bm_ene_bm3_fly_motion_names, 0x2, 0xf };
TObjMotionAction bm3_flynest_hit_action_table[10] = {
    { 1, 0, 14, 0.3f, 0 },
    { 3, 0, 9, 0.7f, 0 },
    { 3, 0, 2, 1.0f, 0 },
    { 3, 0, 5, 0.5f, 0 },
    { 1, 0, 8, 0.3f, 0 },
    { 3, 0, 7, 0.7f, 0 },
    { 3, 0, 6, 1.0f, 0 },
    { 3, 0, 4, 0.3f, 0 },
    { 1, 0, 13, 0.3f, 0 },
    { 3, 0, 11, 0.2f, 0 }
};
void *lbl_80491EE4[106] = {
    0, 0, (void *)TObjEneBm3FlyNest__sub_800B3E40, (void *)run_task__17TObjEneBm3FlyNestFv,
    (void *)render__17TObjEneBm3FlyNestFv, (void *)render_shadows__17TObjEneBm3FlyNestFv, (void *)vfunc_6__8TObjBaseFPsl, (void *)apply_object_set_data__8TObjBaseFPv,
    (void *)reset_motion_fields__9TObjCharaFv, (void *)get_center__9TObjCharaFv, (void *)update_object_view_visibility__8TObjBaseFff, (void *)classify_actor_view_detail__8TObjBaseFfff,
    (void *)get_name__9TObjEnemyFv, (void *)interact__14TObjCollidableFl, (void *)add_actor_exp__9TObjCharaFl, (void *)consume_timer_field__9TObjCharaFl,
    (void *)get_actor_level_index__9TObjCharaFv, (void *)update_actor_ground_y__9TObjCharaFv, (void *)vfunc_18__9TObjCharaFPUc, (void *)is_actor_cadence_frame__9TObjCharaFl,
    (void *)select_melee_contact_body__9TObjCharaFPvf, (void *)calc_distance_accuracy_penalty__9TObjCharaFPvPvPvf, (void *)receive_physical_attack__9TObjCharaFPvf, (void *)receive_direct_attack__9TObjCharaFPv19DirectAttackPayloadPvll,
    (void *)receive_weapon_special_attack__9TObjCharaFPvPv, (void *)apply_knockback_from_attacker__9TObjCharaFPUcf, (void *)try_start_action__9TObjCharaFll, (void *)roll_physical_accuracy__9TObjCharaFPvlf,
    (void *)vfunc_28__17TObjEneBm3FlyNestFv, (void *)vfunc_29__9TObjCharaFv, (void *)is_target_in_attack_range__9TObjCharaFv, (void *)&test_flag_256__9TObjCharaFv,
    (void *)&test_flag30_512__9TObjCharaFv, (void *)&has_flag_0x800__9TObjCharaFv, (void *)&test_flag_1000__9TObjCharaFv, (void *)update_poison_status__9TObjCharaFv,
    (void *)update_action_hold_status__9TObjCharaFv, (void *)vfunc_37__9TObjCharaFv, (void *)update_flag30_timer__9TObjCharaFv, (void *)update_movement_status__9TObjCharaFv,
    (void *)update_shock_clock__9TObjCharaFv, (void *)update_attack_stat_status__9TObjCharaFv, (void *)update_defense_stat_status__9TObjCharaFv, (void *)vfunc_43__9TObjCharaFv,
    (void *)apply_poison_status__9TObjCharaFv, (void *)apply_paralysis__9TObjCharaFv, (void *)apply_slow_status__9TObjCharaFv, (void *)apply_confusion_status__9TObjCharaFv,
    (void *)apply_movement_ailment__9TObjCharaFl, (void *)apply_shock_status__9TObjCharaFv, (void *)clear_harmful_statuses__9TObjCharaFv, (void *)apply_attack_stat_status__9TObjCharaFPv,
    (void *)apply_defense_stat_status__9TObjCharaFPv, (void *)cure_poison_ailment__9TObjCharaFv, (void *)cure_paralysis__9TObjCharaFv, (void *)clear_all_status_effects__9TObjCharaFv,
    (void *)apply_action_hold_status__9TObjCharaFf, (void *)apply_anti_technique__9TObjCharaFl, (void *)vfunc_58__9TObjCharaFv, (void *)vfunc_59__9TObjCharaFv,
    (void *)vfunc_60__9TObjCharaFv, (void *)vfunc_61__17TObjEneBm3FlyNestFv, (void *)vfunc_62__17TObjEneBm3FlyNestFv, (void *)vfunc_63__17TObjEneBm3FlyNestFv,
    (void *)reset_pose__9TObjCharaFv, (void *)get_anim_node_position__9TObjCharaFlP3Vec, (void *)vfunc_66__9TObjCharaFv, (void *)vfunc_67__9TObjCharaFf,
    (void *)get_pos__9TObjCharaFl, (void *)apply_switch_attack__9TObjCharaFv, (void *)enemy_spawn_jellen_effect__9TObjCharaFv, (void *)trigger_switch_attack__9TObjCharaFv,
    (void *)enemy_spawn_zalure_effect__9TObjCharaFv, (void *)recalc_stats__9TObjCharaFv, (void *)vfunc_74__9TObjEnemyFl, (void *)vfunc_75__9TObjCharaFf,
    (void *)vfunc_76__9TObjCharaFv, (void *)vfunc_77__9TObjCharaFv, (void *)vfunc_78__9TObjCharaFl, (void *)vfunc_79__9TObjEneDDFPl,
    (void *)apply_hit_message_flags__9TObjEnemyFPv, (void *)apply_set_data__9TObjEnemyFPv, (void *)clear_lobby_object_state__9TObjEnemyFv, (void *)vfunc_83__9TObjEneDDFv,
    (void *)vfunc_84__9TObjEneDDFv, (void *)vfunc_85__9TObjEneDDFv, (void *)vfunc_86__9TObjEneDDFv, (void *)dispatch_state__17TObjEneBm3FlyNestFiUii,
    (void *)vfunc_88__17TObjEneBm3FlyNestFv, (void *)vfunc_89__9TObjEneDDFv, (void *)vfunc_90__9TObjEneDDFv, (void *)vfunc_91__9TObjEneDDFv,
    (void *)vfunc_92__9TObjEneDDFv, (void *)vfunc_93__9TObjEneDDFv, (void *)vfunc_94__9TObjEneDDFv, (void *)vfunc_95__9TObjEneDDFv,
    (void *)vfunc_96__9TObjEneDDFv, (void *)vfunc_97__9TObjEneDDFv, (void *)vfunc_98__9TObjEneDDFv, (void *)vfunc_99__9TObjEneDDFv,
    (void *)vfunc_100__9TObjEneDDFv, (void *)vfunc_101__9TObjEneDDFPUc, (void *)vfunc_102__9TObjEneDDFv, (void *)vfunc_103__9TObjEneDDFPUc,
    (void *)TObjEneBm3FlyNest::init, (void *)render_with_state_debug__17TObjEneBm3FlyNestFv,
};
extern const s32 bm3_fly_nest_attachment_sample_table[8];
extern const NpcAnimationBinding bm3_flynest_anim_binding;
extern Vec child_spawn_velocity;
extern const Vec lbl_8043B310;
extern const Vec lbl_8043B31C;
extern const char normal_state_text[];
extern const char dead_state_text[];
extern const char fallen_state_text[];
extern const char start_count_format[];
extern const char total_count_format[];
extern const f64 lbl_8043B398[];
typedef struct Ctl_800B47C4 {
    f32 *pv;
    s32 *pc;
    s32 d;
    s32 e;
    s32 f;
} Ctl_800B47C4;
Vec TObjEneBm3FlyNest__attachment_sample_origin;
f32 fly_nest_vertex_table[6];
__declspec(section ".data") s32 lbl_80500B24[2];
Ctl_800B47C4 lbl_80500B2C;
extern s32 debug_chunk_object;
extern const char *TObjEneBm3FlyNest_CarryFly__name;
extern s32 lbl_805D50F8;
extern s32 lbl_805D50FC;
extern s32 lbl_805D5100;
extern s32 lbl_805D5104;
BmlResource *nest_resources;
s32 attachment_node_index;
Vec *attachment_point_cursor;
Vec *carrier_point_cursor;
s32 carrier_sample_index;
extern s32 saved_model_render_flags;
extern s32 saved_chunk_polygon_flags_and_mask;
extern s32 saved_chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_and_mask;
extern const f32 lbl_805D9D08;
extern const f32 lbl_805D9D0C;
extern const f32 lbl_805D9D10;
extern const f32 lbl_805D9D14;
extern const f32 lbl_805D9D18;
extern const f32 lbl_805D9D1C;
extern const f32 lbl_805D9D20;
extern const f32 lbl_805D9D24;
extern const f32 lbl_805D9D28;
extern const f32 lbl_805D9D2C;
extern const f32 lbl_805D9D30;
extern const f32 lbl_805D9D34;
extern const f32 lbl_805D9D38;
extern const f32 lbl_805D9D3C;
extern const f32 lbl_805D9D40;
extern const f32 lbl_805D9D44;
extern const f32 lbl_805D9D48;
extern const f32 lbl_805D9D4C;
extern const f32 lbl_805D9D50;
extern const f32 lbl_805D9D54;
extern const f32 lbl_805D9D58;
extern const f32 lbl_805D9D5C;
extern const f32 lbl_805D9D60;
extern const f32 lbl_805D9D64;
extern const f32 lbl_805D9D68;
extern const f32 lbl_805D9E84;
extern const f32 lbl_805D9E88;
extern s32 model_render_flags;
extern void *tl_04;

__declspec(section ".rodata") extern const char fly_body_model_filename[] = "bm3_fly_body.nj";
__declspec(section ".rodata") extern const char fly_nest_model_filename[] = "bm3_s_nest.nj";
__declspec(section ".rodata") extern const char fly_attack_motion_filename[] = "atack_bm3_fly_body.njm";
__declspec(section ".rodata") extern const char fly_damage_motion_filename[] = "damage_bm3_fly_body.njm";
__declspec(section ".rodata") extern const char nest_damage_motion_filename[] = "dam_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char fly_death_motion_filename[] = "dead_bm3_fly_body.njm";
__declspec(section ".rodata") extern const char nest_death_motion_filename[] = "dead_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char nest_fall_motion_filename[] = "down_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char fallen_nest_damage_motion_filename[] = "dwndam_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char fallen_nest_emit_motion_filename[] = "dwnexit_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char fallen_nest_wait_motion_filename[] = "dwnwait_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char nest_emit_motion_filename[] = "exit_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char fly_flight_motion_filename[] = "fly_bm3_fly_body.njm";
__declspec(section ".rodata") extern const char nest_land_motion_filename[] = "land_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char fly_move_motion_filename[] = "move_bm3_fly_body.njm";
__declspec(section ".rodata") extern const char nest_trance_motion_filename[] = "trance_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char nest_wait_motion_filename[] = "wait_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char fly_bml_filename[] = "bm_ene_bm3_fly.bml";
__declspec(section ".rodata") extern const s32 bm3_fly_nest_attachment_sample_table[8] = { 2, 4, 9, 11, 16, 18, 24, 26 };
__declspec(section ".rodata") extern const char nest_class_string[] = "TObjEneBm3FlyNest";
__declspec(section ".rodata") extern const char carrier_class_string[] = "TObjEneBm3FlyNest_CarryFly";
__declspec(section ".rodata") extern const NpcAnimationBinding bm3_flynest_anim_binding = { 0, bm3_flynest_hit_action_table, 0, 8, 10 };
__declspec(section ".rodata") Vec child_spawn_velocity = { 0.0f, 3.0f, 0.0f };
__declspec(section ".rodata") extern const Vec lbl_8043B310 = { 5.0f, 1.0f, 5.0f };
__declspec(section ".rodata") extern const Vec lbl_8043B31C = { 5.0f, 1.0f, 5.0f };
__declspec(section ".rodata") extern const char normal_state_text[] = "STATE : NORMAL";
__declspec(section ".rodata") extern const char dead_state_text[] = "STATE : DEAD";
__declspec(section ".rodata") extern const char fallen_state_text[] = "STATE : FALLEN";
__declspec(section ".rodata") extern const char start_count_format[] = "START NUM : %2d";
__declspec(section ".rodata") extern const char total_count_format[] = "TOTAL NUM : %2d";
const char *bm3_fly_nest_class_name = nest_class_string;
const char *TObjEneBm3FlyNest_CarryFly__name = carrier_class_string;

#pragma push
#pragma pool_data off
void TObjEneBm3FlyNest::render_with_state_debug() {
    f32 motion_frame;
    AnimationMotion *motion;
    if (get_target_info() != 0) {
        switch (demo_state) {
        default:
        case 2:
            debug_printf_at(pack_debug_text_position(0, 0), normal_state_text);
            break;
        case 9:
            debug_printf_at(pack_debug_text_position(0, 0), dead_state_text);
            break;
        case 5:
            debug_printf_at(pack_debug_text_position(0, 0), fallen_state_text);
            break;
        }
        debug_printf_at(pack_debug_text_position(0, 1), start_count_format, initial_child_count);
        debug_printf_at(pack_debug_text_position(0, 2), total_count_format, spawn_limit);
    }
    switch (demo_state) {
    default:
    case 2:
        motion_frame = 0.0f;
        motion = motion_list[action_table[0].motion].motion;
        break;
    case 9:
        motion = motion_list[action_table[7].motion].motion;
        motion_frame = motion->frameCount - 1;
        break;
    case 5:
        motion = motion_list[action_table[3].motion].motion;
        motion_frame = motion->frameCount - 1;
        break;
    }
    if (update_object_view_visibility(500.0f, 120.0f) != 0) {
        Vec shadow_scale = lbl_8043B31C;
        update_player_state__9TObjEneDDFv(this, &shadow_scale, 1);
        TObjFish::set_global_param(texlist);
        push_matrix();
        post_translate_matrix(&position.x);
        translate_matrix(0, 0.0f, -5.0f, 0.0f);
        rotate_matrix_y(0, rotation_y);
        TObjEneDD::clear_global_flag_400();
        TObjPlayer::toggle_particle_effect();
        set_motion_packed_rotation();
        draw_model_motion(model, motion, motion_frame);
        clear_motion_packed_rotation();
        TParticleCtrl::end_effect_render();
        pop_matrix();
    }
    push_matrix();
    post_translate_matrix(&position.x);
    rotate_matrix_y(0, rotation_y);
    translate_matrix(0, parameters[2], parameters[3], parameters[4]);
    draw_chunk_object((void *)debug_chunk_object);
    pop_matrix();
}

#pragma pop

__declspec(section ".rodata") extern const char alternate_fly_bml_filename[] = "bm_ene_bm3_fly_a.bml";
__declspec(section ".rodata") extern const f64 lbl_8043B398[1] = { 10430.38043493439 };

void TObjEneBm3FlyNest::render() {
    RenderFadeState *fade;
    s32 camera;
    s32 detail;
    s32 draw_now;
    f32 factor;
    if (TObjPlayer::check_demo_mode() != 0) {
        render_with_state_debug();
        return;
    }
    camera = 0;
    if (is_split_screen() != 0) {
        camera = get_camera_mode__11TCameraCtrlFv();
    }
    visible = 0;
    if (mode != 9) {
        if (is_main_phase_15__9TObjEneDDFv() != 0) {
            detail = classify_actor_view_detail(lbl_805D9D08 + lbl_805D9E88, lbl_805D9D0C + lbl_805D9E84, 120.0f);
        } else if (update_object_view_visibility(500.0f, 120.0f) != 0) {
            detail = 1;
        } else {
            detail = 0;
        }
        if (detail != 0) {
            draw_now = 1;
            visible = 1;
            saved_model_render_flags = model_render_flags;
            saved_chunk_polygon_flags_and_mask = chunk_polygon_flags_and_mask;
            saved_chunk_polygon_flags_or_mask = chunk_polygon_flags_or_mask;
            fade = &camera_fades[camera];
            fade->update();
            if (fade->updateFromCamera(&body_center_position.x) != 0) {
                fade->set_flags_and_apply_damage_color();
                if (defer_render() != 0) {
                    draw_now = 0;
                }
            }
            if (mode != 9) {
                Vec shadow_scale = lbl_8043B310;
                if (mode == 0) {
                    factor = lbl_805D9D10 / (model_height - lbl_805D9D14);
                    if (factor < lbl_805D9D18 && factor > 0.0f) {
                        shadow_scale.x = shadow_scale.z = lbl_805D9D1C * factor;
                    }
                }
                update_player_state__9TObjEneDDFv(this, &shadow_scale, 1);
            }
            if (draw_now != 0) {
                update_secondary_light();
                TObjFish::set_global_param(texlist);
                push_matrix();
                attachment_node_index = 0;
                attachment_point_cursor = attachment_points;
                post_translate_matrix(&position.x);
                translate_matrix(0, 0.0f, model_height, 0.0f);
                if (mode == 0) {
                    carrier_sample_index = 0;
                    carrier_point_cursor = carrier_points;
                    set_chunk_model_node_callback((s32)TObjEneBm3FlyNest::sample_carrier_attachments);
                } else {
                    set_chunk_model_node_callback((s32)TObjEneBm3FlyNest::capture_attachment);
                }
                rotate_matrix_y(0, rotation_y);
                TObjEneDD::clear_global_flag_400();
                TObjPlayer::toggle_particle_effect();
                if (detail == 1) {
                    draw();
                } else {
                    draw_motion_model();
                }
                TParticleCtrl::end_effect_render();
                set_chunk_model_node_callback(0);
                pop_matrix();
            }
            update_primary_light();
            if (fade->updateFromCamera(&body_center_position.x) != 0) {
                fade->clear_flag_and_notify();
            }
            model_render_flags = saved_model_render_flags;
            chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;
            chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask;
        }
    }
    VecCopy(&body_center_position, &attachment_points[0]);
}

void TObjEneBm3FlyNest::sample_carrier_attachments(NJS_OBJECT *node) {
    Vec *pos;
    if ((s32) attachment_node_index == (s32) bm3_fly_nest_attachment_sample_table[carrier_sample_index]) {
        pos = carrier_point_cursor;
        carrier_sample_index += 1;
        carrier_point_cursor = pos + 1;
        get_camera_ctrl__9TObjEneDDFv((s32) &TObjEneBm3FlyNest__attachment_sample_origin, (s32)pos);
    }
    TObjEneBm3FlyNest::capture_attachment(node);
}

void TObjEneBm3FlyNest::capture_attachment(NJS_OBJECT *) {
    switch (attachment_node_index) {
    case 36: case 45:
        get_camera_ctrl__9TObjEneDDFv((s32)&TObjEneBm3FlyNest__attachment_sample_origin, (s32)(attachment_point_cursor++));
        break;
    }
    ++attachment_node_index;
}

int TObjEneBm3FlyNest::init(void* p) { return ((int (*)(void*))init_params__17TObjEneBm3FlyNestFv)(p); }

s32 TObjEneBm3FlyNest::remap_child_sound(s32 sound_id) {
    return TObjEnemy::remap_sound_for_area(sound_id);
}

Vec *TObjEneBm3FlyNest::get_spawn_point() { return &attachment_points[1]; }

void TObjEneBm3FlyNest::remove_child(u8 *child) {
    for (s32 i = 0; i < 6; i++) {
        if (find_entity_by_id(child_ids[i]) == child) {
            child_count--;
            child_ids[i] = child_ids[child_count];
            child_ids[child_count] = 0xFFFF;
            return;
        }
    }
}

s32 TObjEneBm3FlyNest::has_free_attack_slot(u16 id) {
    s32 count = 0;
    for (s32 i = 0; i < child_count; i++) {
        TObjEneBm3Fly *child = static_cast<TObjEneBm3Fly *>(find_entity_by_id(child_ids[i]));
        if (child != 0 && id == child->get_active_id()) {
            count++;
        }
    }
    if (TObjEneDD::check_v2_mode()) {
        return count < 4;
    }
    return count < 2;
}

void TObjEneBm3FlyNest::handle_state(s32 arg1) {
    switch (arg1) {
    case 4:
        vfunc_95();
        return;
    case 3:
        if ((s32) this->child_count == 0) {
            send_entity_set_flags__9TObjEnemyFv();
            queue_destruction();
        }
    case 5:
    case 0:
        return;
    }
}

#pragma push
#pragma fp_contract on
void TObjEneBm3FlyNest::state_dying(s32 arg1) {
    Vec v;
    Vec p;
    f32 r;
    s32 a;
    switch (arg1) {
    case 4:
        this->requested_action = 7;
        this->vfunc_96();
        this->model_height = 0.0f;
        ((TObjPlayer *)this)->refresh_lobby_state();
        this->state_timer = 4;
        this->state_counter = 0x14;
        this->substate = 0;
        this->sink_distance = 0.0f;
        break;
    case 3:
        if (this->sink_distance >= lbl_805D9D20) {
            transition_enemy_state(9);
        }
        break;
    case 5:
        break;
    case 0:
        switch (this->substate) {
        case 0:
            this->advance_animation();
            if (get_flag_b4() != 0) {
                this->substate = 1;
                v.x = lbl_805D9D24;
                v.y = 0.0f;
                v.z = lbl_805D9D28;
                rotate_xz_pair_by_angle((f32 *)&v, &v.z, this->rotation_y);
                vec3_add_to(&v, &position);
                spawn_dead_spot_scale15((s32)&v, 0x32);
                set_field_e4__10TObjPlayerFll(&v, 0x46, lbl_805D9D10);
            }
            if (this->frame < lbl_805D9D08) {
                this->state_timer += 1;
                if (this->state_timer >= 4) {
                    r = rand_range(lbl_805D9D1C, lbl_805D9D10);
                    a = get_random_scaled__9TObjEneDDFv(this);
                    VecCopy(&p, &body_center_position);
                    p.x = r * sin_table_lookup(a) + p.x;
                    p.y += lbl_805D9D1C;
                    p.z = r * cos_table_lookup(a) + p.z;
                    spawn_particle_effect(&p, 0xF1);
                    this->state_timer = 0;
                }
                this->state_counter += 1;
                if (this->state_counter >= 0x14) {
                    play_sound_effect(remap_sound_for_area(0x4003AD2B), &position, 0, 0);
                    this->state_counter = 0;
                }
            }
            this->vfunc_102();
            break;
        case 1:
            this->sink_distance += lbl_805D9D2C;
            position.y -= lbl_805D9D2C;
            break;
        }
        break;
    }
}
#pragma pop

void TObjEneBm3FlyNest::handle_motion_event(s32 arg1) {
    switch (arg1) {
    case 4:
        this->vfunc_96();
        noop__12TBoss8DragonFv(this);
        TBoss8Dragon__sub_800BB7D4(this, 0xF1);
        play_sound_effect(remap_sound_for_area(0x4003A829), &position, 0, 0);
        if ((s32) this->damage_phase != 0) {
            this->requested_action = 6;
            this->model_height = (f32) 0.0f;
            return;
        }
        this->requested_action = 2;
        this->model_height = (f32) -5.0f;
        return;
    case 3:
        if (get_flag_b4() != 0) {
            if ((s32) this->damage_phase != 0) {
                transition_enemy_state(5);
                return;
            }
            if ((s16) this->hp <= (s32) ((s16) this->hpmax / 2)) {
                transition_enemy_state(4);
                return;
            }
            transition_enemy_state(*(s32 *)((s8 *)this + 0x378));
            return;
        }
        break;
    case 0:
        this->advance_animation();
        this->vfunc_102();
        return;
    case 5:
        clear_attack_receipts();
        break;
    }
}

void TObjEneBm3FlyNest::state_spawn(s32 arg1) {
    switch (arg1) {
    case 4:
        this->requested_action = 5;
        this->vfunc_96();
        this->set_field_378(5);
        this->model_height = (f32) 0.0f;
        return;
    case 3:
        if (this->motion_flags & 0x10) {
            transition_enemy_state(5);
        }
        break;
    case 5:
    case 1:
        break;
    case 0:
        if (this->is_passing_frame(lbl_805D9D30) != 0) {
            this->spawn_child();
            this->pending_spawns = (s32) (this->pending_spawns - 1);
        }
        this->advance_animation();
        this->vfunc_102();
        break;
    }
}

void TObjEneBm3FlyNest::update_state(s32 arg1) {
    switch (arg1) {
    case 4:
        this->requested_action = 4;
        this->vfunc_96();
        this->set_field_378(5);
        this->model_height = (f32) 0.0f;
        if ((s32) this->damage_phase == 0) {
            this->damage_phase = 1;
            this->replenish_count = 2;
            this->replenish_delay = 0x78;
        }
        break;
    case 5:
        break;
    case 3:
        if (has_pending_spawns() != 0) {
            transition_enemy_state(6);
            return;
        }
        break;
    case 0:
        this->advance_animation();
        this->update_replenish();
        this->vfunc_102();
        break;
    }
}

#pragma push
#pragma opt_common_subs off
#pragma fp_contract on
void TObjEneBm3FlyNest::fn_800B318C(s32 arg1) {
    Vec effect_position;
    s32 temp_r31;
    switch (arg1) {
    case 4:
        this->vfunc_91();
        this->requested_action = 3;
        this->vfunc_96();
        this->set_field_378(5);
        this->model_height = (f32) -5.0f;
        break;
    case 3:
        if (this->motion_flags & 0x10) {
            transition_enemy_state(5);
            break;
        }
        break;
    case 0:
        (this->advance_animation());
        if ((this->is_passing_frame(lbl_805D9D10) != 0) || (this->is_passing_frame(lbl_805D9D34) != 0)) {
            play_sound_effect(this->remap_sound_for_area(0x4003B72A), &position, 0, 0);
        }
        if (this->is_passing_frame(lbl_805D9D38) != 0) {
            spawn_particle_effect((&position), 0xF0);
        } else if (this->is_passing_frame(lbl_805D9D3C) != 0) {
            temp_r31 = this->rotation_y - 0x4000;
            VecCopy(&effect_position, &position);
            effect_position.x += lbl_805D9D40 * sin_table_lookup(temp_r31);
            effect_position.z += lbl_805D9D40 * cos_table_lookup(temp_r31);
            spawn_particle_effect(&effect_position, 0xF0);
        }
        this->model_height = (f32) (this->model_height + lbl_805D9D2C);
        if (this->model_height > 0.0f) {
            this->model_height = (f32) 0.0f;
        }
        this->vfunc_102();
        break;
    case 5:
        this->vfunc_92();
        break;
    }
}
#pragma pop

void TObjEneBm3FlyNest::handle_event(s32 arg1) {
    switch (arg1) {
    case 4:
        this->requested_action = 1;
        this->vfunc_96();
        this->set_field_378(2);
        this->model_height = (f32) -5.0f;
        return;
    case 3:
        if (this->motion_flags & 0x10) {
            transition_enemy_state(2);
        }
        break;
    case 5:
        break;
    case 0:
        this->advance_animation();
        if (this->is_passing_frame(lbl_805D9D30) != 0) {
            this->spawn_child();
            this->pending_spawns = (s32) (this->pending_spawns - 1);
        }
        this->vfunc_102();
        break;
    }
}

void TObjEneBm3FlyNest::state_wait(s32 arg1) {
    switch (arg1) {
    case 4:
        this->requested_action = 0;
        vfunc_96();
        this->set_field_378(2);
        this->model_height = (f32) -5.0f;
        this->replenish_count = 1;
        this->replenish_delay = 0x96;
        return;
    case 3:
        if (has_pending_spawns() != 0) {
            transition_enemy_state(3);
        }
        break;
    case 5:
        break;
    case 0:
        this->advance_animation();
        this->update_replenish();
        vfunc_102();
        break;
    }
}

void TObjEneBm3FlyNest::state_initial_emit(s32 arg1) {
    switch (arg1) {
    case 4:
        this->requested_action = 0;
        this->vfunc_95();
        this->set_field_378(2);
        this->model_height = -5.0f;
        this->state_timer = 0;
        this->state_counter = 0;
        this->substate = 0;
        break;
    case 3:
        this->advance_animation();
        if (this->substate == 3) {
            switch (this->demo_state) {
            case 2:
                transition_enemy_state(this->demo_state);
                break;
            case 5:
                transition_enemy_state(this->demo_state);
                break;
            case 9:
                this->requested_action = 7;
                this->advance_animation();
                this->frame = lbl_805D9D14;
                this->advance_animation();
                this->frame = this->frame_count - lbl_805D9D18;
                this->actorFlags |= 0x800;
                this->damage_phase = 1;
                transition_enemy_state(this->demo_state);
                break;
            }
        }
        break;
    case 5:
        break;
    case 0:
        this->advance_animation();
        this->state_timer += 1;
        switch (this->substate) {
        case 0:
            if (this->state_timer > 0x3C) {
                this->substate = 2;
                this->requested_action = 1;
            }
            break;
        case 1:
            if (this->is_passing_frame(lbl_805D9D30) != 0) {
                this->substate = 2;
            }
            break;
        case 2:
            if (get_flag_b4() != 0) {
                this->requested_action = 0;
            }
            if ((this->state_timer % 10) == 0) {
                if (this->state_counter < *(s32 *)&this->initial_child_count) {
                    this->spawn_child();
                    this->state_counter += 1;
                } else {
                    this->substate = 3;
                }
            }
            break;
        }
        break;
    }
}

#pragma push
#pragma fp_contract on
void TObjEneBm3FlyNest::handle_appear(s32 arg1) {
    s32 *cnt = &state_counter;
    s32 i;

    switch (arg1) {
    case 4:
        this->requested_action = 8;
        this->vfunc_95();
        this->set_field_378(2);
        this->model_height = lbl_805D9D44;
        this->state_timer = 0;
        this->substate = 0;
        this->state_angle = 0;
        break;
    case 3:
        if (this->substate == 2 && get_flag_b4() != 0) {
            transition_enemy_state(1);
        }
        break;
    case 0:
        this->advance_animation();
        switch (this->substate) {
        case 0:
            this->state_timer += 1;
            if (this->state_timer == 1) {
                *cnt = 0;
                for (i = 0; i < 6; i++) {
                    new TObjEneBm3FlyNest_CarryFly(this, &carrier_points[i],
                        &attachment_points[1], &position, cnt, i + 1);
                }
            }
            this->model_height = this->model_height - ((lbl_805D9D4C * (lbl_805D9D18 + sin_table_lookup(this->state_angle))) + lbl_805D9D48);
            this->state_angle += 0x700;
            if (this->model_height < lbl_805D9D50 && this->requested_action != 9) {
                this->requested_action = 9;
            }
            if (this->model_height < -5.0f) {
                this->model_height = -5.0f;
                this->substate = 1;
                this->state_timer = 0;
                spawn_particle_effect(&position, 0xF0);
                play_sound_effect(this->remap_sound_for_area(0x4003B72A), &position, 0, 0);
            }
            break;
        case 1:
            this->state_timer += 1;
            if (this->state_timer > 3) {
                this->state_timer = 0;
                *cnt += 1;
                if (*cnt >= 6) {
                    this->substate = 2;
                }
            }
            break;
        }
        this->vfunc_102();
        break;
    case 5:
        *cnt = 6;
        break;
    }
}
#pragma pop

void TObjEneBm3FlyNest::init_params() {
    demo_state = 2;
    initial_child_count = parameters[1];
    if (initial_child_count < 0) {
        initial_child_count = 0;
    } else if (initial_child_count > 6) {
        initial_child_count = 6;
    }
    spawn_limit = parameters[2];
    if (spawn_limit < 0) {
        spawn_limit = 0;
        return;
    }
    if (spawn_limit > 30) {
        spawn_limit = 30;
    }
}

void TObjEneBm3FlyNest::spawn_child() {
    Vec velocity = child_spawn_velocity;
    Vec spawn_position;
    s32 n;
    if (child_count <= 6) {
        n = (set_index + 1) + children_spawned;
        VecCopy(&spawn_position, get_spawn_point());
        if (TObjEneBm3Fly::create(this, next_child_id, n, &spawn_position, &velocity) != 0) {
            child_ids[child_count++] = next_child_id;
            next_child_id++;
            children_spawned++;
            spawn_particle_effect(&attachment_points[1], 0xC8);
            play_sound_effect(TObjEnemy::remap_sound_for_area(0x4003AB27), &position, 0, 0);
            TObjPlayer::play_effect_if_v2(-0x400);
        }
    }
}

s32 TObjEneBm3FlyNest::has_pending_spawns() const {
    return pending_spawns > 0;
}

void TObjEneBm3FlyNest::update_replenish() {
    s32 count;
    s32 available;
    s32 remaining;
    switch (replenish_phase) {
    case 0:
        if (child_count <= initial_child_count / 2 || damage_phase != 0) {
            replenish_phase = 1;
            replenish_timer = 0;
        }
        return;
    case 1:
        if (replenish_count > 0) {
            replenish_timer++;
            if (replenish_timer > replenish_delay) {
                replenish_timer = 0;
                count = replenish_count;
                available = 6 - child_count;
                if (available < count) {
                    count = available;
                }
                remaining = spawn_limit - children_spawned;
                if (remaining < count) {
                    count = remaining;
                }
                pending_spawns = count;
                return;
            }
        }
        break;
    }
}

void TObjEneBm3FlyNest::vfunc_88() { set_part_local_pos(&body_center_position, 0); }

void TObjEneBm3FlyNest::copy_pos() { VecCopy(&center, &body_center_position); }

void TObjEneBm3FlyNest::vfunc_61() {  }

void TObjEneBm3FlyNest::vfunc_62() {
    s16 temp_r0;

    if (((s16) this->mode == 3) && (TObjEneDD::check_v2_mode() != 0)) {
        clear_attack_receipts();
        return;
    }
    temp_r0 = this->mode;
    if (temp_r0 == 4) {
        clear_attack_receipts();
        return;
    }
    if (temp_r0 != 7) {
        transition_enemy_state(7);
    }
}

void TObjEneBm3FlyNest::vfunc_63() {
    s16 temp_r0;

    temp_r0 = this->mode;
    if ((temp_r0 != 9) && (temp_r0 != 8) && (temp_r0 != 4)) {
        if (damage_phase == 0) {
            transition_enemy_state(4);
            return;
        }
        transition_enemy_state(8);
    }
}

void TObjEneBm3FlyNest::vfunc_28() {  }

void dispatch_state__17TObjEneBm3FlyNestFiUii(s32 arg0, u32 arg1, s32 arg2) {
    switch (arg1) {
    case 1:
        ((TObjEneBm3FlyNest *)arg0)->state_initial_emit(arg2);
        return;
    case 0:
        static_cast<TObjEneBm3FlyNest *>((void *)arg0)->handle_appear(arg2);
        return;
    case 2:
        static_cast<TObjEneBm3FlyNest *>((void *)arg0)->state_wait(arg2);
        return;
    case 3:
        static_cast<TObjEneBm3FlyNest *>((void *)arg0)->handle_event(arg2);
        return;
    case 4:
        static_cast<TObjEneBm3FlyNest *>((void *)arg0)->fn_800B318C(arg2);
        return;
    case 5:
        static_cast<TObjEneBm3FlyNest *>((void *)arg0)->update_state(arg2);
        return;
    case 6:
        static_cast<TObjEneBm3FlyNest *>((void *)arg0)->state_spawn(arg2);
        return;
    case 7:
        static_cast<TObjEneBm3FlyNest *>((void *)arg0)->handle_motion_event(arg2);
        return;
    case 8:
        static_cast<TObjEneBm3FlyNest *>((void *)arg0)->state_dying(arg2);
        return;
    case 9:
        static_cast<TObjEneBm3FlyNest *>((void *)arg0)->handle_state(arg2);
    default:
        return;
    }
}

#pragma push
#pragma fp_contract on
void TObjEneBm3FlyNest::run_task() {
    if (TObjPlayer::check_demo_mode() != 0) {
        ((VObj_18_p5 *)(this))->m102();
        return;
    }
    if (this->vfunc_83() != 4) {
        this->vfunc_85();
    } else if (this->mode == 0) {
        transition_enemy_state(1);
    }
    this->vfunc_88();
    this->copy_pos();
    submit_default_cursor_candidate();
    this->vfunc_100();
}
#pragma pop

Obj_800B3E40 *TObjEneBm3FlyNest__sub_800B3E40(Obj_800B3E40 *self, s16 flag) {
    if (self != 0) {
        self->vtbl = lbl_80491EE4;
        free_collision_body_parts(self);
        __destroy_arr(self->arr, (void *)__dt__15RenderFadeStateFv, 0x1c, 4);
        __dt__9TObjEneDDFv(self, 0);
        if (flag > 0) {
            __dl__7TObjectFPv(self);
        }
    }
    return self;
}

extern const char *bm3_fly_nest_class_name;

struct Sub_800B3EB8 { u8 pad[0x1c]; };

struct Nest_800B3EB8 {
    const char *id;
    u8 pad4[0x18 - 0x4];
    void *vt;
    u16 f1C;
    u8 pad1E[0x24 - 0x1E];
    s32 f24;
    u8 pad28[0x34 - 0x28];
    s32 f34;
    Vec pos;
    u8 pad44[0xB8 - 0x44];
    s16 fB8;
    u8 padBA[0x300 - 0xBA];
    f32 f300;
    u8 pad304[0x326 - 0x304];
    s16 f326;
    u8 pad328[0x350 - 0x328];
    void *f350;
    u8 pad354[0x37C - 0x354];
    f32 f37C;
    u8 pad380[0x394 - 0x380];
    s32 f394;
    s32 f398[4];
    s32 f3A8;
    s32 f3AC;
    s32 f3B0;
    s32 f3B4;
    u16 f3B8[6];
    u16 f3C4;
    u8 pad3C6[2];
    Vec f3C8[2];
    Vec f3E0[8];
    Sub_800B3EB8 f440[4];
    f32 f4B0;
    s32 f4B4[9];
    f32 f4D8;
};

void *__ct__9TObjEneDDFP7TObject(void *, void *, void *);
void __construct_array(void *, void *, void *, int, int);
void __ct__15RenderFadeStateFv(void *);
void invoke_initialization_hook__9TObjEneDDFPv(void *, void *);
void init_model__9TObjEneDDFP13CollisionBodyl(void *, void *, int);
s32 reset_hp__9TObjEneDDFPUcPUcPUc(void *, int, int, int);
s32 initialize_enemy_state__9TObjEneDDFl(void *, int);

#define self ((Nest_800B3EB8 *)arg0)
#pragma push
#pragma opt_loop_invariants off
void *TObjEneBm3FlyNest__ct(void *arg0, void *arg1, void *arg2) {
    s32 i;

    __ct__9TObjEneDDFP7TObject(self, arg1, arg2);
    self->vt = lbl_80491EE4;
    __construct_array(self->f440, __ct__15RenderFadeStateFv, __dt__15RenderFadeStateFv, 0x1C, 4);
    self->id = bm3_fly_nest_class_name;
    invoke_initialization_hook__9TObjEneDDFPv(self, arg2);
    ((TObjEneDD *)self)->init_position_vectors();
    self->f34 = *(s32 *)(*(u8 **)((int)nest_resources + 0x42C) + 0x18);
    self->f24 = *(s32 *)(*(u8 **)((int)nest_resources + 0x42C) + 0xC);
    init_model__9TObjEneDDFP13CollisionBodyl(self, &bm3_flynest_collider_params, 1);
    self->f300 = lbl_805D9D20 + self->pos.y;
    ((TObjEneDD *)self)->vfunc_88();
    ((TObjMotion *)self)->set_field_d8((s32)bm3_flynest_hit_action_table);
    ((TObjMotion *)self)->set_field_dc(*(s32 *)((int)nest_resources + 0x430));
    self->fB8 = 0;
    ((TObjMotion *)self)->set_animation(self->fB8);
    ((TObjMotion *)self)->set_field_b8(self->fB8);
    reset_hp__9TObjEneDDFPUcPUcPUc(self, lbl_805D50F8, lbl_805D50FC, lbl_805D5100);
    ((TObjEneDD *)self)->check_state_flag_1();
    self->f350 = &bm3_fly_nest_params;
    initialize_enemy_state__9TObjEneDDFl(self, 4);
    self->f37C = lbl_805D9D10;
    init_params__17TObjEneBm3FlyNestFv(self);
    if (self->f394 > *(s16 *)((u8 *)arg2 + 2)) {
        self->f394 = *(s16 *)((u8 *)arg2 + 2);
    }
    for (i = 0; i < 4; i++) {
        self->f398[i] = 0;
    }
    self->f3A8 = 0;
    self->f3AC = 0;
    self->f3B0 = 0;
    self->f3B4 = 0;
    self->f3C4 = self->f1C + 1;
    for (i = 0; i < 6; i++) {
        self->f3B8[i] = 0xFFFF;
    }
    for (i = 0; i < 2; i++) {
        VecCopy((Vec *)&self->f3C8[i], (const Vec *)&self->pos);
    }
    self->f3C8[1].y += lbl_805D9D08;
    for (i = 0; i < 8; i++) {
        VecCopy((Vec *)&self->f3E0[i], (const Vec *)&self->pos);
    }
    for (i = 0; i < 4; i++) {
        ((RenderFadeState *)(&self->f440[i]))->activate_and_dispatch();
    }
    self->f4B0 = 0.0f;
    self->f4B4[0] = 0;
    self->f4B4[1] = 0;
    self->f4B4[2] = 0;
    self->f4B4[3] = 0;
    self->f4B4[4] = 0;
    self->f4B4[5] = 0;
    self->f4B4[6] = 0;
    self->f4B4[7] = 0;
    self->f4B4[8] = 0;
    self->f4D8 = 0.0f;
    self->f326 = 0;
    ((VObj_800B3EB8 *)self)->m85(self->f326, 4);
    return self;
}
#pragma pop
#undef self

BmlResource *TObjEneBm3FlyNest::get_resources() { return nest_resources; }

void TObjEneBm3FlyNest::free_fly() {
    TObjEneBm3Fly::release_shared_data();
    if (nest_resources != 0) {
        delete nest_resources;
        nest_resources = 0;
    }
}

void *TObjEneBm3FlyNest::create(void *arg0) {
    void *o = __nw__7TObjectFUl(0x4DC);
    if (o != NULL) {
        o = TObjEneBm3FlyNest__ct(o, tl_04, arg0);
    }
    return o;
}

void TObjEneBm3FlyNest::load_resources() {
    TObjEneBm3FlyNest__attachment_sample_origin.x = 0.0f;
    TObjEneBm3FlyNest__attachment_sample_origin.y = 0.0f;
    TObjEneBm3FlyNest__attachment_sample_origin.z = 0.0f;
    attachment_node_index = 0;
    attachment_point_cursor = 0;
    carrier_point_cursor = 0;
    carrier_sample_index = 0;
    if (TObjEneDD::check_v2_mode() != 0) {
        nest_resources = load_enemy_bml_resource_named(&bm3_fly_nest_resource_desc, alternate_fly_bml_filename);
    } else {
        nest_resources = load_enemy_bml_resource(&bm3_fly_nest_resource_desc);
    }
    lbl_805D50F8 = register_boss__6TLobbyFl(1);
    lbl_805D50FC = dispatch_shared_handler_b__6TLobbyFl(1);
    lbl_805D5100 = register_object__6TLobbyFl(1);
    lbl_805D5104 = dispatch_shared_handler_a__6TLobbyFl(1);
    TObjEneBm3Fly::load_resources();
    TObjEneBm3FlyNest::init_vertex_table();
    {
        NpcAnimationBinding anim = bm3_flynest_anim_binding;
        anim.motions = nest_resources->motions;
        BmlModelEntry *models = nest_resources->models;
        NpcModelRegistry::register_animated_chunk(8, (void *)models[1].model,
            (void *)models[0].m_c, &anim, bm3_flynest_collider_params.radius, 0.0f);
    }
}

void TObjEneBm3FlyNest_CarryFly::render() {
    TObjFish::set_global_param(nest_resources->models[0].m_c);
    push_matrix();
    if (state == 0) {
        post_translate_matrix(&attachment->x);
    } else {
        post_translate_matrix(&destination->x);
    }
    post_translate_matrix(&position.x);
    rotate_matrix_y(0, rotation_y);
    set_motion_packed_rotation();
    draw_model_motion((void *)nest_resources->models[0].model, motion, frame);
    clear_motion_packed_rotation();
    pop_matrix();
}

#pragma push
#pragma fp_contract on
void TObjEneBm3FlyNest_CarryFly::run_task() {
    f32 lim;
    f32 v;
    f32 spd;

    lim = (f32) (motion->frameCount - 1);
    frame += lbl_805D9D54;
    if (frame > lim) {
        frame -= lim;
    }
    switch (state) {
    case 0:
        if (*release_counter == order) {
            Vec tmp;
            state = 1;
            VecCopy(&tmp, &position);
            vec3_add_to(&tmp, attachment);
            VecCopy(&direction, &tmp);
            subtract_vector(&direction, destination);
            direction.y -= lbl_805D9D1C;
            VecCopy(&position, &direction);
            distance = normalize_vector_xz(&direction);
            if (distance <= lbl_805D9D58) {
                queue_destruction();
                break;
            }
            curvature = lbl_805D9D5C / (distance * distance);
            flight_height = lbl_805D9D60;
        }
        play_persistent_sound((s32)(static_cast<TObjEneBm3FlyNest *>(m_up)->remap_child_sound(0x4003A828)), (s32)this, (u32)(attachment), 0, 0);
        TObjPlayer::play_effect_if_v2(-0x400);
        break;
    case 1:
        position.y += lbl_805D9D18;
        if (position.y > 0.0f) {
            state = 2;
            direction.y = lbl_805D9D64 * distance;
        }
        play_persistent_sound((s32)(static_cast<TObjEneBm3FlyNest *>(m_up)->remap_child_sound(0x4003A828)), (s32)this, (u32)(attachment), 0, 0);
        TObjPlayer::play_effect_if_v2(-0x400);
        break;
    case 2:
        spd = distance;
        v = direction.y;
        v = v - lbl_805D9D68 * spd;
        if (v < lbl_805D9D64 * -spd) {
            spawn_particle_effect((void *)(destination), 0xC8);
            play_sound_effect(static_cast<TObjEneBm3FlyNest *>(m_up)->remap_child_sound(0x4003AB27), (void *)destination, 0, 0);
            TObjPlayer::play_effect_if_v2(-0x400);
            queue_destruction();
            break;
        }
        position.y = curvature * (v * v) + flight_height;
        direction.y = v;
        v = lbl_805D9D64 * distance + v;
        position.x = direction.x * v;
        position.z = direction.z * v;
        play_persistent_sound((s32)(static_cast<TObjEneBm3FlyNest *>(m_up)->remap_child_sound(0x4003A828)), (s32)this, (u32)(destination), 0, 0);
        TObjPlayer::play_effect_if_v2(-0x400);
        break;
    }
}
#pragma pop

TObjEneBm3FlyNest_CarryFly::~TObjEneBm3FlyNest_CarryFly() {}

}
TObjEneBm3FlyNest_CarryFly::TObjEneBm3FlyNest_CarryFly(TObjEneBm3FlyNest *parent,
    const Vec *attachment, const Vec *destination, const Vec *, const s32 *counter,
    s32 order) : TObject(parent) {
    Vec direction;
    m_name = TObjEneBm3FlyNest_CarryFly__name;
    this->attachment = attachment;
    this->destination = destination;
    release_counter = counter;
    this->order = order;
    VecCopy(&direction, this->attachment);
    subtract_vector(&direction, this->destination);
    ((TObjBoss2Tunnel *)&direction)->update_scale();
    rotation_y = lbl_8043B398[0] * atan2_float(direction.x, direction.z);
    position.x = lbl_805D9D6C * direction.x;
    position.y = lbl_805D9D6C;
    position.z = lbl_805D9D6C * direction.z;
    motion = nest_resources->motions[10].motion;
    frame = this->order * 2;
    unknown_3c = lbl_805D9D18;
    unknown_44 = 0;
    this->direction.x = 0.0f;
    this->direction.y = 0.0f;
    this->direction.z = 0.0f;
    distance = 0.0f;
    flight_height = 0.0f;
    curvature = 0.0f;
    state = 0;
}

void TObjEneBm3FlyNest::init_vertex_table() {
    f32 *v = fly_nest_vertex_table;
    v[3] = v[2] = v[1] = v[0] = 0.0f;
    v[5] = v[4] = lbl_805D9D6C;
    lbl_80500B24[0] = -1;
    lbl_80500B24[1] = -1;
    lbl_80500B2C.pv = fly_nest_vertex_table;
    lbl_80500B2C.pc = lbl_80500B24;
    lbl_80500B2C.d = 0;
    lbl_80500B2C.e = 2;
}


void TObjEneBm3FlyNest::render_shadows() {}

extern "C" {
__declspec(section ".sdata2") extern const f32 lbl_805D9D08 = 25.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D0C = 50.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D10 = 10.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D14 = 2.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D18 = 1.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D1C = 5.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D20 = 20.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D24 = -10.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D28 = -8.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D2C = 0.1f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D30 = 15.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D34 = 28.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D38 = 9.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D3C = 27.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D40 = 16.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D44 = 100.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D48 = 0.2f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D4C = 0.3f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D50 = 18.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D54 = 0.8f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D58 = 0.01f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D5C = -120.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D60 = 30.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D64 = 0.5f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D68 = 0.05f;
__declspec(section ".sdata2") extern const f32 lbl_805D9D6C = 6.0f;
}
