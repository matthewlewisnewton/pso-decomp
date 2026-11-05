#ifndef PSO_TBOSS7TENTACLE_H
#define PSO_TBOSS7TENTACLE_H
#include "pso/TObject.h"
#include "pso/system/NinjaTypes.h"
#include "pso/system/vector.h"
#include "types.h"
#include <stddef.h>

class TBoss7Tentacle : public TObject {
public:
    TBoss7Tentacle(TObject *parent, const f32 (*matrix)[4], s32 kind);
    virtual ~TBoss7Tentacle();
    void sub_802F09FC();
    void sub_802F09EC();
    virtual void render();
    virtual void run_task();

public:
    void update_extend_amount();
    void switch_state();
    void advance_path_position();
    void reset_state();
    void setup_state();
    void init_segments();
    void start_attack_at_position(const Vec *target, s32 arg2);

    // 0x1C is used both as a position Vec and as the (model, anim, scale_x)
    // triple, so the two views are declared as one union.
    union {
        Vec position;
        struct {
            NJS_OBJECT *m_1c;
            NJS_MOTION *m_20;
            f32 m_24;
        } ent;
    };
    f32 m_28;
    f32 m_2c;
    s32 m_30;
    s32 m_34;
    s32 m_38;
    s32 m_3c;
    // 0x40 is the attack-origin Vec in run_task/render. fld.m_44 and
    // fld.m_4c sit on top of that Vec's y and the word after it.
    union {
        struct {
            Vec m_40;
            u8 gap_4c[4];
            Vec m_50[14];
        } geo;
        struct {
            u8 gap_40[4];
            f32 m_44;
            u8 unk_48[0x4];
            s32 m_4c;
        } fld;
    };
    s32 m_f8[14];
    const f32 (*m_130)[4];
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
