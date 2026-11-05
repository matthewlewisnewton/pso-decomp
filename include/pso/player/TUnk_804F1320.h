#ifndef PSO_PLAYER_TUNK_804F1320_H
#define PSO_PLAYER_TUNK_804F1320_H
#include "types.h"
#include "pso/items/TItemWeapon.h"

class TUnk_804F1320 : public TItemWeapon {
public:
    virtual ~TUnk_804F1320();
    void spawn_pg_effect(void *, s32, f32);
    virtual void vfunc_17(s32);
    virtual void emit_marker_effects();
    u8 unk_1F8[0x4];
};

#endif
