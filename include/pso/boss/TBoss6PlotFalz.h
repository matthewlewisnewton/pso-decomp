#ifndef PSO_BOSS_TBOSS6PLOTFALZ_H
#define PSO_BOSS_TBOSS6PLOTFALZ_H

#include "types.h"
#include <stddef.h>
#include "pso/enemy/TObjEnemy.h"

struct TBoss6Tube;

extern "C" {
s32 TBoss6PlotFalz__sub_802ABADC(void);
}

struct TBoss6PlotFalz : public TObjEnemy {
    virtual ~TBoss6PlotFalz();
    void ensure_field384();
    void set_visible_flag();
    void call_state_action();
    void sub_802AAC98();
    void vfunc_63();
    u8 unk_374[0x4];
    s32 m_378;
    u8 m_37c;
    u8 unk_37D[0x3];
    u8 * m_380;
    // Tube from ensure_field384 (create__10TBoss6Tube at 0x802ABD6C).
    // 0x802B0FC8 stores 1 at +0x1C and plays 0x4003351F, the same state-1
    // step as TBoss6Tube::update_timer. 0x802B1004 stores 0 at +0x20 and 2
    // at +0x1C; +0x20 is m_20, past TBoss6EmptyWarp's 0x20-byte allocation.
    TBoss6Tube *m_384;
    u8 unk_388[2];
    s16 m_38a;
    u8 unk_38C[0x28];
    u8 unk_3B4[0x18];
    // Plot-script frame counter and phase flag. Signed: the actions compare
    // them with cmpwi.
    s32 m_3cc;
    s32 m_3d0;
    s32 m_3d4;
    s32 m_3d8;
    // Object created for DEMO_WAIT_T2 (TObjFish::alloc) and later read back
    // as the player whose plot state advances the script.
    void *m_3dc;
    static s32 get_hp();
    static s32 damage_player_hp(s32 arg0, u32 arg1);
    static s32 sort_active_players();
    static u16 pick_random_active_player();
    s32 is_active();
    void set_state_2();
    void reset_state();
    void activate_warp();
    void free_child();
    void set_state(s32 arg1);
    static void spawn_player_hit_effects();
    void award_exp_and_destroy();
    void apply_fade_alpha(s32 arg1, f32 farg0);
    static s32 rand_vary_count(s32 arg0, f32 farg0);
    static f32 cosine_ease(f32 t);
    static f32 get_value();
    static s32 is_boss_active();
    void release_object();
    static s32 get_target_pos_a(s32 arg0, s32 arg1);
    static s32 get_target_pos_b(s32 arg0, s32 arg1);
    void spawn_type2();
    void spawn_type1();
    static void apply_radial_effect_to_players(void *pos, s16 amount, s16 kind, f32 range);
    static void set_fade_material_color(f32 f);
    static void update_camera_target();
    static void apply_fade_material_color(f32 farg0, f32 farg1, f32 farg2, f32 farg3);
    static int get_phase();
    void scroll_strips_uv(s32 dx, s32 dy);
    void free_buffer_pairs();
    static void freeze_all_players();
    void render();
    void run_task();
    void send_6xA3_action(s8 v);
    static void free_all();
    static void load_resources();
    static s32 create(s32 arg0);
    static s32 is_phase_reached();
    void reset_ending_state();
    void update_plot_timer();
    void check_and_advance_state();
    void set_state4_if_ready();
    void reset_and_recreate();
    void update_phase();
    void enter_active_state();
    void tick_timeout();
    void advance_intro_timer();
    void advance_if_ready();
    static void *create(void *arg0, void *arg1);
    int is_ending_or_split_screen();
    int is_ready();
    // Neither reads its receiver. Callers leave r3 alone, so they are static.
    static void end_cutscene_camera();
    static void refresh_players_equipment();
    void destroy_static_instance();
    void queue_instance_destruction();
    void finish_and_dispatch_next_phase();
    void check_action_7();
    void advance_timer();
    void advance_phase_if_ready();
    void update_cutscene_fade();
    static u8 is_flag_set();
    s32 get_next_point(s16 *arg1, s16 *arg2);
    void run_phase_action();
    static void warp_nearby_players();
    // Plot script state actions (installed in TBoss6PlotFalz__data_804DE66C).
    void sub_802B0228();
    void sub_802B03F4();
    void sub_802B0448();
    void stop_adx_audio();
    void init_hall_boss_scene();
    void sub_802B06D0();
    void sub_802B0808();
    void sub_802B08F0();
    void init_proto1_adx();
    void sub_802B0A34();
};

extern "C" {
void TBoss6PlotFalz__sub_802AC008(f32 a, f32 b);
}

typedef char TBoss6PlotFalz_m_384_offset[(offsetof(TBoss6PlotFalz, m_384) == 0x384) ? 1 : -1];
typedef char TBoss6PlotFalz_m_38a_offset[(offsetof(TBoss6PlotFalz, m_38a) == 0x38A) ? 1 : -1];
typedef char TBoss6PlotFalz_m_3cc_offset[(offsetof(TBoss6PlotFalz, m_3cc) == 0x3CC) ? 1 : -1];
typedef char TBoss6PlotFalz_m_3d0_offset[(offsetof(TBoss6PlotFalz, m_3d0) == 0x3D0) ? 1 : -1];
typedef char TBoss6PlotFalz_m_3d4_offset[(offsetof(TBoss6PlotFalz, m_3d4) == 0x3D4) ? 1 : -1];
typedef char TBoss6PlotFalz_m_3d8_offset[(offsetof(TBoss6PlotFalz, m_3d8) == 0x3D8) ? 1 : -1];
typedef char TBoss6PlotFalz_m_3dc_offset[(offsetof(TBoss6PlotFalz, m_3dc) == 0x3DC) ? 1 : -1];
typedef char TBoss6PlotFalz_size[(sizeof(TBoss6PlotFalz) == 0x3E0) ? 1 : -1];

#endif
