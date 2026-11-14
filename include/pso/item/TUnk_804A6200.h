#ifndef PSO_ITEM_TUNK_804A6200_H
#define PSO_ITEM_TUNK_804A6200_H
#include "types.h"
#include "pso/item/WeaponAnimationChannels.h"
#include <stddef.h>
#include "pso/items/TItemWeapon.h"

class TUnk_804A6200 : public TItemWeapon {
public:
    virtual ~TUnk_804A6200();
    virtual void update_idle();
    void*set_mode_vector();
    virtual void update_attack();
    WeaponAnimationChannels animation;
};

typedef char TUnk_804A6200_AnimationOffset[offsetof(TUnk_804A6200, animation) == 0x1F8 ? 1 : -1];
typedef char TUnk_804A6200_Size[sizeof(TUnk_804A6200) == 0x204 ? 1 : -1];

#endif
