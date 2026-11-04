#ifndef PSO_TBOSS7TENTACLE_H
#define PSO_TBOSS7TENTACLE_H
#include "pso/TObject.h"
#include "pso/system/vector.h"
#include "types.h"
#include <stddef.h>

class TBoss7Tentacle : public TObject {
public:
    TBoss7Tentacle(TObject *arg1, s32 arg2, s32 arg3);
    virtual ~TBoss7Tentacle();
    void sub_802F09FC();
    void sub_802F09EC();
    virtual void render();
    virtual void run_task();
    static void update_retract_state(void *p);
    static void damage_nearby_players(void *p);

public:
    void restart_particle_effect();
    s32 advance_anim_time_wrapped(f32 d);
    s32 advance_toward_limit(f32 farg0);
    void update_extend_amount();
    void switch_state();
    void advance_path_position();
    void reset_state();
    void setup_state();
    void init_segments();
    void start_attack_at_position(u8 *arg1, s32 arg2);

    // 0x1C is used both as a position Vec and as the (model, anim, scale_x)
    // triple, so the two views are declared as one union.
    union {
        Vec position;
        struct {
            void *m_1c;
            void *m_20;
            f32 m_24;
        } ent;
    };
    f32 m_28;
    f32 m_2c;
    s32 m_30;
    s32 m_34;
    s32 m_38;
    s32 m_3c;
    // 0x40 is the particle effect handle in restart_particle_effect and the
    // attack origin Vec in run_task/render; the Vec overlaps m_44/unk_48/m_4c.
    union {
        Vec m_40;
        struct {
            TObject *m_40_effect;
            f32 m_44;
            u8 unk_48[0x4];
            s32 m_4c;
        } fld;
    };
    Vec m_50[14];
    s32 m_f8[14];
    s32 m_130;
    f32 m_134;
    f32 m_138;
    s32 m_13c;
    s32 m_140;
    s32 m_144;
    s32 m_148;
    Vec m_14c;
    f32 m_158;
    f32 m_15c;
    f32 m_160;
    s32 m_164;
    s32 m_168;
};

#endif
