#ifndef PSO_ENEMY_BERURA_TOBJENERE7BERURA_H
#define PSO_ENEMY_BERURA_TOBJENERE7BERURA_H

#include "types.h"
#include <stddef.h>
#include <dolphin/mtx/GeoTypes.h>
#include "pso/enemy/dd/TObjEneDD_ST.h"
#include "pso/render/RenderFadeState.h"
#include "pso/render/TUnk_80490470.h"
#include "pso/system/NinjaTypes.h"

class TParticleCtrl;
class TUnk_80494968;
struct TObjEneRe7BeruraPunch;

// What TObjEnemy::movementParameters points at for the Berura.
struct TObjEneRe7BeruraMovementParameters {
    f32 unknown_00;
    f32 unknown_04;
    s32 unknown_08;
    u32 unknown_0C[4];
};

// One element of TObjEneRe7Berura__detached_part_states.
struct BeruraDetachedPart {
    Mtx34 *matrices;
    s32 first_node_index;
    s32 last_node_index;
    s32 action;
    f32 m_10;
    f32 frame;
    NJS_OBJECT *first_node;
    NJS_OBJECT *last_node;
    NJS_OBJECT model;
    Vec origin;

    void show_end_nodes();
    void hide_end_nodes();
};

typedef char BeruraDetachedPartSize[sizeof(BeruraDetachedPart) == 0x64 ? 1 : -1];
typedef char BeruraDetachedPartModelOffset[offsetof(BeruraDetachedPart, model) == 0x20 ? 1 : -1];
typedef char BeruraDetachedPartOriginOffset[offsetof(BeruraDetachedPart, origin) == 0x58 ? 1 : -1];

struct TObjEneRe7Berura : public TObjEneDD_ST {
    TObjEneRe7Berura(TObject *parent, void *set_data);
    virtual ~TObjEneRe7Berura();
    virtual void vfunc_88();
    virtual void vfunc_105();
    virtual void vfunc_106();
    void vfunc_63();
    void vfunc_62();
    void vfunc_61();
    void vfunc_28();
    void sub_80095328();
    void render();
    void run_task();
    void state_attack(s32 arg1);
    virtual void dispatch_action(u32 state, s32 reason);
    void handle_message_transition(s32 msg);
    s32 check_death_trigger();
    void play_band_sound();
    void reload_stats_from_tables();
    void destroy_parts();
    u8 is_over_limit();
    s32 step_toward_target(s32 arg1, s32 arg2);
    void init_fields4B8();
    static void init_part(s32 arg0);
    static void capture_part_matrices(NJS_OBJECT *root, BeruraDetachedPart *part);
    static s32 collect_node_matrices(NJS_OBJECT *obj, s32 idx);
    void update_collision_center();
    void init_enemy();
    static void destroy_children();
    void *create();
    static void load_static_resources();
    static void advance_state();
    static void demo_frame_callback();
    void run_flash_warning_state(s32 arg1);
    void handle_state(s32 arg1);
    static void *spawn_punch(void *arg0);
    static void state_patrol(void *self, int msg);
    void update_death_state(s32 mode);
    s32 acquire_target_in_view();

    u32 m_3c0;
    u32 m_3c4;
    u32 m_3c8;
    s32 m_3cc;
    s32 m_3d0;
    s32 m_3d4;
    TUnk_80490470 m_3d8;
    s32 m_3f4;
    TObjEneRe7BeruraPunch *m_3f8;
    TUnk_80490470 m_3fc;
    u32 m_418[2];
    Vec m_420[2];
    TParticleCtrl *m_438[2];
    TUnk_80494968 *m_440[2];
    RenderFadeState m_448[4];
    s32 m_4b8;
    s32 m_4bc;
    s32 m_4c0;
    s32 m_4c4;
    s32 m_4c8;
    s32 m_4cc;
    f32 m_4d0;
    f32 m_4d4;
    f32 m_4d8;
    f32 m_4dc;
    f32 m_4e0;
    static void draw_node_tree(NJS_OBJECT *root);
    static void draw_node_tree(NJS_OBJECT *root, Mtx34 *matrices);
    s32 get_field_3D4_shifted();
};

typedef char TObjEneRe7Berura_size[sizeof(TObjEneRe7Berura) == 0x4E4 ? 1 : -1];
typedef char TObjEneRe7Berura_m_3d8[offsetof(TObjEneRe7Berura, m_3d8) == 0x3D8 ? 1 : -1];
typedef char TObjEneRe7Berura_m_448[offsetof(TObjEneRe7Berura, m_448) == 0x448 ? 1 : -1];
#endif
