struct NJS_OBJECT;
#ifndef PSO_ENEMY_TOBJENERE7BERURA_H
#define PSO_ENEMY_TOBJENERE7BERURA_H

#include "types.h"
#include "pso/enemy/TObjEneRe7BeruraData.h"
#include "pso/enemy/TObjEneDD_ST.h"
#include "pso/player/TUnk_80490470.h"
#include "pso/misc/RenderFadeState.h"

class TUnk_80494968;

struct TObjEneRe7Berura : public TObjEneDD_ST {
    TObjEneRe7Berura(TObject *parent, void *set_data);
    virtual ~TObjEneRe7Berura();
    virtual void vfunc_88();
    virtual void fn_80092C90();
    virtual void fn_80092B10();
    virtual void dispatch_action(u32 state, s32 reason);
    void vfunc_63();
    void vfunc_62();
    void vfunc_61();
    void vfunc_28();
    void render();
    void run_task();
    u32 flags;
    s32 m_3c4;
    u32 m_3c8;
    s32 uv_scroll_step;
    s32 uv_scroll;
    s32 m_3d4;
    TUnk_80490470 fade;
    s32 active_part;
    TObject *punch;
    TUnk_80490470 part_fade;
    u32 part_flags[2];
    Vec part_positions[2];
    TObject *part_effects[2];
    TUnk_80494968 *traces[2];
    RenderFadeState camera_fades[4];
    void fn_80093470(s32 reason);
    void state_patrol(s32 reason);
    void fn_80093888(s32 reason);
    void fn_80093C80(s32 reason);
    void fn_800940E8(s32 reason);
    void fn_80094624(s32 reason);
    void fn_8009472C(s32 reason);
    void state_attack(s32 arg1);
    void handle_message_transition(s32 msg);
    s32 check_death_trigger();
    void play_band_sound();
    void fn_80094C68();
    void reload_stats_from_tables();
    void destroy_parts();
    s32 has_reached_turn_limit();
    s32 turn_toward_heading(s32 arg1, s32 arg2);
    void reset_turn_limit();
    void clear_active_part_flag_2();
    s32 fn_80094DB4();
    s32 fn_80094EE0();
    s32 fn_8009518C();
    void fn_80095328();
    static void init_part(s32 arg0);
    static void draw_node_tree(NJS_OBJECT *root);
    static void draw_node_tree(NJS_OBJECT *root, Mtx34 *matrices);
    static void capture_part_matrices(NJS_OBJECT *root, BeruraDetachedPart *part);
    static s32 collect_node_matrices(NJS_OBJECT *root, s32 index);
    void update_collision_center();
    void init_enemy();
    static void destroy_children();
    static void *create(void *set_data);
    static void load_static_resources();
    static void advance_state(NJS_OBJECT *);
    static void demo_frame_callback(NJS_OBJECT *);
    void run_flash_warning_state(s32 arg1);
    void handle_state(s32 arg1);
    static void *spawn_punch(void *arg0);
    s32 turn_limit;
    s32 accumulated_turn;
    s32 state_timer;
    s32 m_4c4;
    s32 m_4c8;
    s32 m_4cc;
    f32 m_4d0;
    f32 m_4d4;
    f32 m_4d8;
    f32 m_4dc;
    f32 m_4e0;
    void update_death_state(s32 mode);
    s32 acquire_target_in_view();
};

typedef char BeruraFadeOffset[offsetof(TObjEneRe7Berura, fade) == 0x3D8 ? 1 : -1];
typedef char BeruraPartFlagsOffset[offsetof(TObjEneRe7Berura, part_flags) == 0x418 ? 1 : -1];
typedef char BeruraCameraFadesOffset[offsetof(TObjEneRe7Berura, camera_fades) == 0x448 ? 1 : -1];
typedef char BeruraTurnLimitOffset[offsetof(TObjEneRe7Berura, turn_limit) == 0x4B8 ? 1 : -1];
typedef char TObjEneRe7Berura_size[sizeof(TObjEneRe7Berura) == 0x4E4 ? 1 : -1];
#endif
