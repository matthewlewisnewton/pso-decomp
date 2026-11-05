#ifndef PSO_ITEMS_TITEMWEAPONFIST_H
#define PSO_ITEMS_TITEMWEAPONFIST_H
#include "types.h"
#include <stddef.h>
struct WeaponPlayerAttachmentInterface;
struct TItemWeaponFist {
    void emit_marker_effects();
    u8 item_prefix[0xF0];
    WeaponPlayerAttachmentInterface* player;
    u8 weapon_fields[0x1F8-0xF4];
};
typedef char FistPlayerOffset[(offsetof(TItemWeaponFist, player)==0xF0)?1:-1];
typedef char FistObjectSize[(sizeof(TItemWeaponFist)==0x1F8)?1:-1];
#endif
