#ifndef PSO_BOSS_TBOSS6TYPE1_H
#define PSO_BOSS_TBOSS6TYPE1_H
#include "types.h"
#include <stddef.h>
#include "pso/enemy/TObjEnemy.h"

typedef Vec Boss6EffectPoint;
struct ModelNodePositionCapture;
struct Boss6Motion { s32 f0; u32 frames; };
struct Boss6Anim {
    Boss6Motion *motion;
    f32 t;
    f32 speed;
    f32 blend;
    f32 rate;
    Boss6Motion *prev_motion;
    f32 prev_t;
};

struct TBoss6Type1 : public TObjEnemy {
    virtual ~TBoss6Type1();
    void set_action_state(s32);
    void sub_802B5CB4();
    void sub_802B4C28();
    virtual void vfunc_62();
    virtual void clear_harmful_statuses();
    virtual void apply_shock_status();
    virtual void apply_movement_ailment(s32);
    virtual void apply_confusion_status();
    virtual void apply_slow_status();
    virtual void apply_paralysis();
    virtual void apply_poison_status();
    virtual void vfunc_63();
    void run_task();
    void update_effect_points();
    void update_trail_points();
    s32 m_374;
    // set_action_state shifts the previous action states through this ring.
    // get_mag_mine_ptr returns this + 0x10 (the block
    // TBoss4DarkFalz__sub_8004B4F0 copies); its field layout is still open.
    s32 hist[32];
    s32 m_3f8;
    s32 m_3fc;
    void* trail_point_receiver;
    void* effect_point_receiver;
    s32 unk_408;
    s32 m_40c;
    s32 action_timer;
    s32 m_414;
    s32 unk_418;
    s8 m_41c;
    u8 unk_41D[0x3];
    Vec m_420;
    Vec m_42C;
    s32 m_438;
    s32 motion_set;
    s32 motion_mode;
    Boss6Anim anims[2];
    s32 m_47c;
    s32 unk_480;
    s32 m_484;
    s32 unk_488;
    s32 m_48c;
    s32 unk_490;
    s32 m_494;
    s32 unk_498;
    s32 m_49c;
    s32 laser_fire_time;
    s32 m_4a4;
    s32 unk_4A8;
    s32 m_4ac;
    s32 unk_4B0;
    f32 m_4b4;
    s32 unk_4b8;
    s32 unk_4bc;
    s32 unk_4c0;
    s32 unk_4c4;
    u8 unk_4c8[0xC];
    f32 m_4d4;
    f32 m_4d8;
    f32 m_4dc;
    s32 m_4e0;
    s32 unk_4e4;
    f32 m_4e8;
    s32 m_4ec;
    s32 m_4f0;
    s32 m_4f4;
    // Particle emitters release_effect_slot / spawn_effect_slot index.
    u32 effect_slots[4];
    s32 m_508;
    u32 unk_50C[24];
    Vec m_56C;
    // Node positions ModelNodePositionCapture writes for draw_callback_lists[1].
    // [1] anchors the roar sound and radar marker, [7] is where the flash model
    // is drawn, [8..10] are the trail points (the beam runs from [8] to [9]).
    Vec node_positions_578[11];
    // Node positions for draw_callback_lists[0].
    Vec node_positions_5FC[5];
    Boss6EffectPoint effect_points[2];
    // One node-position capture per model; render installs each before it
    // draws that model (upstream: TObjFish__sub_800E3124 lists).
    ModelNodePositionCapture *draw_callback_lists[2];
    u8 scroll_strips_u[0x14]; // scroll_strips_uv(8, 0) every frame
    u8 scroll_strips_v[0x14]; // scroll_strips_uv(0, 0x22) every frame
    TObject *map_csn;
    static u8 *create_kakusan(s32 arg0, u8 *arg1, u8 *arg2, s16 arg3, f32 farg0);
    static void *copy_block(void *d, void *s);
    static void fire_at_all_players(void *self, f32 dy);
    static void calc_grid_cell_position(void *o, void *out);
    static void clamp_to_arena_radius(void *o, void *out, f32 w);
    static void randomize_attack(void *self, void *atk);
    void clear_slot_array();
    void release_effect_slot(s32 arg1);
    void spawn_effect_slot(s32 arg1);
    void rotate_around_center(s32 num, s32 den);
    void interpolate_pos_to_target(s32 step, s32 total);
    void ease_toward_target(s32 a, s32 b);
    s32 count_matches(s32 arg1, s32 arg2);
    static s32 pick_random_entry(s32 arg0, s32 arg1, s32 arg2);
    static int rand_range_inclusive(s32 arg0, int arg1, int arg2);
    s32 pick_remapped_list_value(s32 a, s32 b, s32 n);
    void handle_6xa4_action(u8 * _w1);
    void decode_polar_position(u8 *arg1);
    static s32 request_jittered_camera(void *arg0, void *arg1, void *arg2, int arg3);
    void request_default_jittered_camera();
    u8 is_timer_expired();
    void reset_fields_4e0();
    s32 is_field3F8_over_0x20();
    int is_field4b0_delta_reached();
    s32 is_ready();
    s32 check_field4b0_threshold();
    int is_time_up();
    void set_flag_on_threshold();
    static void set_part_default_value(int a0, void* a1);
    void init_parts();
    void reset_param();
    void decrease_field_clamped_min();
    void increase_field_clamped_max();
    void enable_parts();
    void set_child_flags();
    void clear_part_flag_bit0();
    void update_parts_flags();
    void update_part_positions();
    void update_position();
    void update_sway();
    void update_turn_to_center();
    s32 calc_field4b0_delta();
    void latch_phase_counter();
    void load_params_from_table();
    void draw_part_motions();
    void set_motion_set(s32 arg1);
    void advance_animations();
    void copy_transform(void* q);
    void render_shadows();
    void do_attack();
    s32 send_6xA4_action(s32 t, s32 *src);
    void load_params(void *arg1);
    void set_sync_data(void *arg1);
    static s32 create(s32 arg0);
    void*get_mag_mine_ptr();
    int is_idle();
    void read_be16_field2();
    void step_and_send_60();
    void enter_flag800_state();
    void update_attack_countdown();
    void update_countdown_state();
    void update_if_ready();
    void set_phase_555();
    void update_countdown();
    void update_state();
    void update_attack_timer();
    void tick_attack_sequence();
    void update_if_idle();
    void enter_release_state();
    void tick_state_410_timer();
    void init_move_attack();
    void update_attack_state();
    void advance_plot_to_state2();
    void init_params();
    void update_phase();
    void trigger_falz_phase();
    void tick_flee_countdown();
    void update_timer_transition();
    void init_hp_and_state();
    void update_charge();
    void start_action_if_idle();
    void set_phase_90();
    void update_timer();
    void update_attack_timer2();
    void init_dice_state();
    void init_action_timer();
    void init_attack_timer();
    void update_timer_state();
    void set_phase_timer_3E();
    void update_action_timer();
    void init_hp_state();
    void init_state_90();
    void update_attack_countdown_reset();
    void start_attack();
    void tick_countdown();
    void choose_next_action();
    void init_attack_timers();
    void init_effect_slot_1();
    void sub_802B245C();
    void sub_802B24B4();
    void sub_802B2724();
    void sub_802B2A94();
    void sub_802B2CB4();
    void sub_802B2D68();
    void sub_802B2F00();
    void sub_802B3178();
    void sub_802B31E4();
    void sub_802B3320();
    void sub_802B343C();
    void sub_802B3564();
    void sub_802B381C();
    void sub_802B3B94();
    void draw_model();
    void render();
    static void release_object(void *);
    void spawn_map_csn();
    static void *create_zanzo(void *arg0, void *arg1, void *arg2);
    static void *create_grav_ball(void *arg0, void *arg1);
    void set_effect_points(f32 *a, u32 *b);
    void spawn_grav_ball();
    void damage_players_in_range();
    void update_beam_attack();
    void init_charge_attack();
    void reset_effects();
    void init_charge();
    void update_hit_timer();
    void init_state();
    void tick_trap_countdown();
    void init_work();
};
extern "C" {
void TBoss6Type1__sub_802B626C(TBoss6Type1 *boss);
}

typedef char Boss6EffectPoint_size[(sizeof(Boss6EffectPoint)==0xC)?1:-1];
typedef char TBoss6Type1_receiver_offset[(offsetof(TBoss6Type1,effect_point_receiver)==0x404)?1:-1];
typedef char TBoss6Type1_points_offset[(offsetof(TBoss6Type1,effect_points)==0x638)?1:-1];
typedef char TBoss6Type1_trail_receiver_offset[(offsetof(TBoss6Type1,trail_point_receiver)==0x400)?1:-1];
typedef char TBoss6Type1_map_csn_offset[(offsetof(TBoss6Type1,map_csn)==0x680)?1:-1];
typedef char TBoss6Type1_node_positions_offset[(offsetof(TBoss6Type1,node_positions_578)==0x578)?1:-1];
#endif
