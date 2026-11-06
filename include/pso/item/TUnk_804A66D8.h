#ifndef PSO_ITEM_TUNK_804A66D8_H
#define PSO_ITEM_TUNK_804A66D8_H
#include "types.h"
#include "pso/items/TItemWeapon.h"

class TUnk_804A66D8 : public TItemWeapon {
public:
    virtual ~TUnk_804A66D8();
    virtual void emit_marker_effects();
    virtual void reserved_53();
};

#endif
