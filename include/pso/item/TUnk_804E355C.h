#ifndef PSO_ITEM_TUNK_804E355C_H
#define PSO_ITEM_TUNK_804E355C_H
#include "types.h"
#include "pso/TObject.h"
#include <dolphin/mtx/GeoTypes.h>

class TUnk_804E355C : public TObject {
public:
    TUnk_804E355C(TObject *parent, void *params);
    virtual ~TUnk_804E355C();
    void check_hits();
    s32 try_add_hit_target(void *);
    virtual void vfunc_6(s32 *);
    u8 has_game_join_id();
    s32 resolve_attack_col_hit(u8 *);
    u8 unk_1C[0x4];
    s32 m_20;
    Vec position;
    s32 facing_yaw;
    u8 unk_34[0x4];
    f32 m_38;
    u8 unk_3C[0x4];
    f32 m_40;
    u8 unk_44[0x4];
    s32 m_48;
    u8 unk_4C[0x4];
    f32 m_50;
    u8 unk_54[0x4];
    f32 m_58;
    u8 unk_5C[0x44];
    s32 m_a0;
    s32 m_a4;
    u16 m_a8;
    u8 unk_AA[0x2];
    s32 m_ac;
    u8 unk_B0[0x4];
    f32 m_b4;
    u8 unk_B8[0x4];
    s32 m_bc;
    u8 unk_C0[0x4];
};

#endif
