#ifndef PSO_ITEM_TUNK_804A0AC4_H
#define PSO_ITEM_TUNK_804A0AC4_H
#include "types.h"
#include "pso/items/TItemWeapon.h"

class TUnk_804A0AC4 : public TItemWeapon {
public:
    virtual ~TUnk_804A0AC4();
    virtual void emit_marker_effects();
    void*init_state_34();
};

#endif
