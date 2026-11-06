#ifndef PSO_BOSS_TUNK_804E4B3C_H
#define PSO_BOSS_TUNK_804E4B3C_H
#include "types.h"
#include <stddef.h>
#include "pso/TObject.h"
#include "pso/boss/TObjBoss2Tunnel.h"

struct Vec;

class TUnk_804E4B3C : public TObject {
public:
    virtual ~TUnk_804E4B3C();
    virtual void run_task();
    void *destroy(s16);
    void update_phase_motion();
    void sub_802F23FC();
    void sub_802F2400();
    void sub_802F273C();
    void init_effect();
    void update_dust_spawn();
    void update_spawn_timer(const s32 *table, s32 arg2, s32 arg3);
    void advance_effect_timer();
    void spawn_segment_row_a();
    void spawn_segment_row_b();
    void spawn(s32 kind, Vec *position);
    s32 check_both();
    s32 is_phase_active();
    virtual void render();
    s32 m_1c;
    PiecewiseCurve motion;
    s32 phase;
    f32 rate;
    f32 value;
    f32 m_58;
    f32 m_5c;
    u8 unk_60[0x10];
    s32 m_70;
    s32 m_74;
    f32 m_78;
    f32 m_7c;
    f32 m_80;
    f32 m_84;
    TObject *m_88;
    TObject *m_8c;
    TObject *m_90;
};
typedef char TUnk_804E4B3C_size[sizeof(TUnk_804E4B3C) == 0x94 ? 1 : -1];
typedef char TUnk_804E4B3C_motion[(offsetof(TUnk_804E4B3C, motion) == 0x20) ? 1 : -1];
typedef char TUnk_804E4B3C_phase[(offsetof(TUnk_804E4B3C, phase) == 0x4C) ? 1 : -1];
typedef char TUnk_804E4B3C_value[(offsetof(TUnk_804E4B3C, value) == 0x54) ? 1 : -1];
typedef char TUnk_804E4B3C_m58[(offsetof(TUnk_804E4B3C, m_58) == 0x58) ? 1 : -1];
typedef char TUnk_804E4B3C_m5c[(offsetof(TUnk_804E4B3C, m_5c) == 0x5C) ? 1 : -1];
typedef char TUnk_804E4B3C_m74[(offsetof(TUnk_804E4B3C, m_74) == 0x74) ? 1 : -1];
typedef char TUnk_804E4B3C_m70[(offsetof(TUnk_804E4B3C, m_70) == 0x70) ? 1 : -1];
typedef char TUnk_804E4B3C_m84[(offsetof(TUnk_804E4B3C, m_84) == 0x84) ? 1 : -1];
typedef char TUnk_804E4B3C_m88[(offsetof(TUnk_804E4B3C, m_88) == 0x88) ? 1 : -1];

#endif
