#ifndef PSO_PLAYER_TUNK_804A1668_H
#define PSO_PLAYER_TUNK_804A1668_H
#include "types.h"
#include "pso/items/TItemWeapon.h"

class TUnk_804A1668 : public TItemWeapon {
public:
    virtual ~TUnk_804A1668();
    virtual void update_weapon();
    void *init_bringer_effect();
    u8 unk_1F8[0x4];
};

#endif
