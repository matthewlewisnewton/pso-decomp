#ifndef PSO_WEAPON_TUNK_804A6200_H
#define PSO_WEAPON_TUNK_804A6200_H
#include <stddef.h>
#include "pso/weapon/WeaponCanopyScale.h"
#include "pso/weapon/TItemWeapon.h"

// The Madam's Parasol weapon class (vtable 0x804A6200): the canopy opens while
// idle and closes during an attack; vfunc_57 starts a regeneration timer.
class TUnk_804A6200 : public TItemWeapon {
public:
    virtual void vfunc_60();
    virtual void vfunc_57();
    virtual void update_idle();
    virtual void update_attack();
    virtual ~TUnk_804A6200();
    TUnk_804A6200(TObject *parent, u8 *item);
    WeaponCanopyScale scale;  // canopy scale (scale_current_matrix)
};

extern "C" u8 *TObjPlayer__sub_8012F298(s32 item);

typedef char TUnk_804A6200_scale_offset[offsetof(TUnk_804A6200, scale) == 0x1F8 ? 1 : -1];
typedef char TUnk_804A6200_size[sizeof(TUnk_804A6200) == 0x204 ? 1 : -1];

#endif
