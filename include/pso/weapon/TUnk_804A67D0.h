#ifndef PSO_WEAPON_TUNK_804A67D0_H
#define PSO_WEAPON_TUNK_804A67D0_H
#include <stddef.h>
#include "pso/weapon/WeaponCanopyScale.h"
#include "pso/weapon/TItemWeapon.h"

// The Madam's Umbrella weapon class (vtable 0x804A67D0): the canopy opens while
// idle and closes during an attack; vfunc_57 starts a regeneration timer.
class TUnk_804A67D0 : public TItemWeapon {
public:
    virtual void vfunc_60();
    virtual void vfunc_57();
    virtual void update_idle();
    virtual void update_attack();
    virtual ~TUnk_804A67D0();
    TUnk_804A67D0(TObject *parent, u8 *item);
    WeaponCanopyScale scale;  // canopy scale (scale_current_matrix)
};

typedef char TUnk_804A67D0_scale_offset[offsetof(TUnk_804A67D0, scale) == 0x1F8 ? 1 : -1];
typedef char TUnk_804A67D0_size[sizeof(TUnk_804A67D0) == 0x204 ? 1 : -1];

#endif
