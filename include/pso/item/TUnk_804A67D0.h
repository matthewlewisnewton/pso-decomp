#ifndef PSO_ITEM_TUNK_804A67D0_H
#define PSO_ITEM_TUNK_804A67D0_H
#include "types.h"
#include "pso/item/WeaponAnimationChannels.h"
#include <stddef.h>
#include "pso/items/TItemWeapon.h"

class TUnk_804A67D0 : public TItemWeapon {
public:
    virtual ~TUnk_804A67D0();
    virtual void update_idle();
    void*init_fields();
    virtual void update_attack();
    WeaponAnimationChannels animation;
};

typedef char TUnk_804A67D0_AnimationOffset[offsetof(TUnk_804A67D0, animation) == 0x1F8 ? 1 : -1];
typedef char TUnk_804A67D0_Size[sizeof(TUnk_804A67D0) == 0x204 ? 1 : -1];

#endif
