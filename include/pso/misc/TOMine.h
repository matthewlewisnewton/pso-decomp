#ifndef PSO_MISC_TOMINE_H
#define PSO_MISC_TOMINE_H

#include "types.h"
#include "pso/player/TObjChara.h"

struct TOMine : public TObjChara {
    virtual ~TOMine();
    virtual f32 receive_weapon_special_attack(void *, void *);
    void detonate();
    void update_float_height();
    void sub_80170BEC();
    void follow_target();
    void update_trigger();
    void sub_8017070C();
    void update_state();
    s32 is_target_in_list(void *);
    virtual void vfunc_79();
    virtual void vfunc_80();
    virtual void vfunc_81();
    virtual void vfunc_82();
    virtual void spawn_disp_objects();
    virtual void vfunc_84();
    virtual void vfunc_85();
    virtual void vfunc_86();
    virtual f32 receive_direct_attack(void *, DirectAttackPayload, void *, s32, s32);
    virtual void vfunc_6(s16 *, s32);
    virtual f32 receive_physical_attack(void *, f32);
    virtual const char *get_name();
    virtual void apply_object_set_data(void *);
    virtual void apply_knockback_from_attacker(u8 *, f32);
    virtual s32 try_start_action(s32, s32);
    virtual s32 roll_physical_accuracy(void *, s32, f32);
    Vec m_334;
    u32 m_340;
    u32 m_344;
    s32 m_348;
    f32 m_34c;
    f32 m_350;
    // 0x354: kind, 0x358: power. Passed whole to receive_direct_attack.
    DirectAttackPayload attack;
    u16 m_35c;
    u8 _pad35E[0x12];
    u32 m_370;
    int get_player_state();
    int find_target_player();
    virtual void run_task();
    void free_sub_objects();
    void free_parts();
    virtual void render();
    static void free_instance();
    static void load_static_resource();
};

typedef char TOMine_size[sizeof(TOMine) == 0x374 ? 1 : -1];
typedef char TOMine_m_334_offset[(offsetof(TOMine, m_334) == 0x334) ? 1 : -1];
typedef char TOMine_attack_offset[(offsetof(TOMine, attack) == 0x354) ? 1 : -1];
#endif
