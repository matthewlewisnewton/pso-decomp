#ifndef PSO_ITEM_TUNK_804A09B0_H
#define PSO_ITEM_TUNK_804A09B0_H
#include "types.h"
#include "pso/items/TItemWeapon.h"

class TUnk_804A09B0 : public TItemWeapon {
public:
    virtual ~TUnk_804A09B0();
    void*init_substate();
    virtual void emit_marker_effects();
};

#endif
