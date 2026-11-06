#ifndef PSO_PLAYER_TUNK_804A2D88_H
#define PSO_PLAYER_TUNK_804A2D88_H
#include "types.h"
#include "pso/items/TItemWeapon.h"

class TUnk_804A2D88 : public TItemWeapon {
public:
    virtual ~TUnk_804A2D88();
    void *init_with_update_handler();
};

#endif
