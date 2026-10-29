#ifndef PSO_UNK_TOBJENEEPSILONBODY_H
#define PSO_UNK_TOBJENEEPSILONBODY_H
#include "types.h"
#include "pso/enemy/TUnk_80494938.h"
#include "pso/system/NinjaTypes.h"
#include "pso/enemy/TObjEneEpsilon.h"

class TObjEneEpsilonBody : public TObjEneEpsilon {
public:
    virtual ~TObjEneEpsilonBody();
    virtual f32 receive_weapon_special_attack(void *, void *);
    u32 select_attack_target(s32 sequence);
    void init_params();
    void update_guard_flag();
    void sub_80361D4C(s32);
    void sub_803606A0(s32);
    void render_body_effect();
    void set_guard_state();
    s16 get_table_value_by_index();
    s16 sub_8035F8A8();
    virtual void run_task();
    virtual void render();
    virtual f32 receive_physical_attack(void *, f32);
    virtual void vfunc_28();
    virtual void vfunc_63();
    virtual void vfunc_62();
    virtual void vfunc_61();
    virtual void vfunc_88();
    virtual void vfunc_105();
    virtual void vfunc_106();
    virtual f32 receive_direct_attack(void *, DirectAttackPayload, void *, s32, s32);
    TObject *emitter_a;
    TObject *emitter_b;
    s32 m_438;
    s16 field_43c;
    s16 m_43e;
    s32 field_440;
    s32 m_444;
    s32 field_448;
    s32 field_44c;
    s32 m_450;
    s32 field_454;
    f32 m_458;
    s32 field_45c;
    s32 guard_angles[4];
    Vec guard_positions[4];
    NJS_ARGB color;
    f32 field_4b0;
    f32 color_steps[3];
    TUnk_80494938 fade;
    u16 guard_ids[4];
    s32 m_4e4;
    s32 field_4e8;
    s32 field_4ec;
    s32 field_4f0;
    s32 field_4f4;
    f32 m_4f8;
    Vec effect_position;
    Vec target_position;
    TObjEneEpsilonBody(TObject *parent, s32 *set_data);
    virtual void dispatch_action(u32, s32);
    virtual void vfunc_89();
    void update_position();
    TObjBase *create_guard(u32, s32, const Vec *, s32);
};
typedef char BodySize[sizeof(TObjEneEpsilonBody) == 0x514 ? 1 : -1];
#endif
