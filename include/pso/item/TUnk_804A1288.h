#ifndef PSO_ITEM_TUNK_804A1288_H
#define PSO_ITEM_TUNK_804A1288_H
#include "types.h"
#include "pso/items/TItemWeapon.h"

class TUnk_804A1288 : public TItemWeapon {
public:
    virtual ~TUnk_804A1288();
    void *init_vtable_804a1288();
    virtual void emit_marker_effects();
};

#endif
