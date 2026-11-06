#ifndef PSO_ITEM_TUNK_804A1190_H
#define PSO_ITEM_TUNK_804A1190_H
#include "types.h"
#include "pso/items/TItemWeapon.h"

class TUnk_804A1190 : public TItemWeapon {
public:
    virtual ~TUnk_804A1190();
    virtual void emit_marker_effects();
    void *destruct_and_set_vtable();
};

#endif
