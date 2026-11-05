#ifndef PSO_PLAYER_TUNK_804A4B80_H
#define PSO_PLAYER_TUNK_804A4B80_H
#include "types.h"
#include "pso/items/TItemWeapon.h"

class TUnk_804A4B80 : public TItemWeapon {
public:
    virtual ~TUnk_804A4B80();
    void heaven_punisher_strike_locks();
    virtual void vfunc_17(s32);
    virtual void emit_marker_effects();
};

#endif
