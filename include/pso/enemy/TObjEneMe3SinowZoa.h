#ifndef PSO_ENEMY_TOBJENEME3SINOWZOA_H
#define PSO_ENEMY_TOBJENEME3SINOWZOA_H

#include "types.h"
#include "pso/enemy/TObjEneDD_ST.h"
#include "pso/misc/MaterialOpacityFade.h"

struct SinowZoaMoveParameters { s32 unknown; f32 speed; s32 turn_speed; };
struct SinowZoaTargetParameters { s32 unknown[3]; s32 angle_range; };
struct SinowZoaKindParameters { s32 unknown[3]; f32 attack_speed; f32 cast_speed; s32 unknown14[4]; s32 barta_level; };

struct TObjEneMe3SinowZoa : public TObjEneDD_ST {
    TObjEneMe3SinowZoa(TObject *parent);
    virtual ~TObjEneMe3SinowZoa();
    virtual void dispatch_action(u32, s32);
    virtual s32 vfunc_104(f32);
    void sub_8031AC74();
    void sub_80319E74(s32);
    virtual void run_task();
    virtual void render();
    u8 check_body_collision_at(s32, f32);
    s32 sub_8031A4D0();
    s32 is_outside_visible_range();
    s32 sub_8031A454();
    void sub_8031A3D8();
    s32 render_model_if_visible();
    virtual void vfunc_88();
    virtual void vfunc_95();
    virtual void vfunc_96();
    virtual void vfunc_89();
    virtual void vfunc_105();
    virtual u8 is_target_in_range();
    virtual void vfunc_107();
    virtual void vfunc_108();
    virtual s32 try_run_effect_m6();
    virtual s32 try_run_effect_m7();
    virtual void vfunc_111();
    virtual void vfunc_112();
    virtual void state_action(s32);
    virtual void action();
    virtual void vfunc_115();
    void vfunc_63();
    void vfunc_62();
    void vfunc_61();
    void vfunc_28();
    s32 m_3c0;
    s32 m_3c4;
    s32 kind;
    u32 state_flags;
    u8 unk_3d0[0x20];
    f32 damage_transition_probability;
    u8 unk_3f4[8];
    s32 attack_count;
    u8 unk_400[8];
    Vec strike_position;
    MaterialOpacityFade fade;
    s32 m_430;
    s32 substate;
    s32 state_timer;
    u8 unk_43c[0x18];
    TObject *effect_454;
    TObject *effect_458;
    virtual f32 receive_direct_attack(void *, DirectAttackPayload, void *, s32, s32);
    u32 check_move_collision(Vec *);
    void fn_80316C3C(s32);
    void fn_803170F0(s32);
    void fn_80317254(s32);
    void state_knockback(s32 arg1);
    void handle_state_substate(s32 arg1);
    void state_chase_target(s32 arg1);
    void update_state_action(s32 arg1);
    void state_chase(s32 arg1);
    void update_distance_state();
    f32 get_node_height();
    void setup_move_bounds();
    void copy_pos_with_height_offset();
    s32 check_floor_contact(void *arg1);
    void check_and_notify();
    static void set_entry_value_clamped(s32 arg0, f32 farg0);
    static void free_resources();
    static void load_resources();
    void copy_position_vector(void* q);
    void init_death_params();
};

typedef char SinowZoaFadeOffset[offsetof(TObjEneMe3SinowZoa, fade) == 0x414 ? 1 : -1];
typedef char SinowZoaSize[sizeof(TObjEneMe3SinowZoa) == 0x45c ? 1 : -1];

#endif
