#ifndef PSO_PLAYER_TUNK_804E23F0_H
#define PSO_PLAYER_TUNK_804E23F0_H
#include "types.h"
#include "pso/items/TItemWeapon.h"

class TUnk_804E23F0 : public TItemWeapon {
public:
    virtual ~TUnk_804E23F0();
    virtual void emit_marker_effects();
    virtual void reserved_53();
    virtual void update_weapon();
    virtual void init_weapon_effect_descriptor(Desc_8011E5C4 *);
    virtual void vfunc_60();
    virtual void vfunc_62(Vec *);
    u8 unk_1F8[0x4];
    u32 m_1fc;
    u8 unk_200[0x4];
};

#endif
