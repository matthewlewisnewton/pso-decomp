#ifndef PSO_ITEM_TUNK_804A3070_H
#define PSO_ITEM_TUNK_804A3070_H
#include "types.h"
#include "pso/items/TItemWeapon.h"

class TUnk_804A3070 : public TItemWeapon {
public:
    virtual ~TUnk_804A3070();
    u8 *construct_agito(s32, void *);
};

#endif
