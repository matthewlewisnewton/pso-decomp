#ifndef PSO_ITEM_TUNK_804A08B8_H
#define PSO_ITEM_TUNK_804A08B8_H
#include "types.h"
#include "pso/items/TItemWeapon.h"

class TUnk_804A08B8 : public TItemWeapon {
public:
    virtual ~TUnk_804A08B8();
    void *init_vtable_804A08B8();
    virtual void emit_marker_effects();
};

#endif
