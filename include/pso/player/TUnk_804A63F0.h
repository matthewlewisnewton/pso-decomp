#ifndef PSO_PLAYER_TUNK_804A63F0_H
#define PSO_PLAYER_TUNK_804A63F0_H
#include "types.h"
#include "pso/items/TItemWeapon.h"

class TUnk_804A63F0 : public TItemWeapon {
public:
    virtual ~TUnk_804A63F0();
    virtual void emit_marker_effects();
    void *init_vtable_804A63F0();
};

#endif
