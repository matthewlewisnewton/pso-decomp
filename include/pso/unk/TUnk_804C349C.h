#ifndef PSO_UNK_TUNK_804C349C_H
#define PSO_UNK_TUNK_804C349C_H
#include "types.h"
#include "pso/TObject.h"
#include <dolphin/mtx/GeoTypes.h>
#include <stddef.h>

class TObjPlayer;

// The photon-blast sequence task. run_task stores the owner at +0x38 from the
// client id at +0x3C and passes this object to the result deliveries.
// calc_photon_blast_power reads that owner; it is not a TObjPlayer method.
class TUnk_804C349C : public TObject {
public:
    virtual ~TUnk_804C349C();
    void update_and_destroy();
    virtual void run_task();
    f32 calc_photon_blast_power(s32 kind, f32 value);

    TObject *summon;
    s32 summon_index;
    s32 state;
    s32 summon_count;
    Vec position;
    TObjPlayer *owner;
    u16 owner_client_id;
    s32 power_level;
    s32 elapsed;
    s32 delay;
    s32 animated;
    s32 kinds[4];
    u32 participants[4];
    s32 levels[4];
    u32 recipients[4];
    u16 holds[4];
};
typedef char TUnk_804C349C_size[sizeof(TUnk_804C349C) == 0x98 ? 1 : -1];
typedef char TUnk_804C349C_owner[(offsetof(TUnk_804C349C, owner) == 0x38) ? 1 : -1];
typedef char TUnk_804C349C_client[(offsetof(TUnk_804C349C, owner_client_id) == 0x3C) ? 1 : -1];
typedef char TUnk_804C349C_power[(offsetof(TUnk_804C349C, power_level) == 0x40) ? 1 : -1];
typedef char TUnk_804C349C_elapsed[(offsetof(TUnk_804C349C, elapsed) == 0x44) ? 1 : -1];
typedef char TUnk_804C349C_delay[(offsetof(TUnk_804C349C, delay) == 0x48) ? 1 : -1];
typedef char TUnk_804C349C_animated[(offsetof(TUnk_804C349C, animated) == 0x4C) ? 1 : -1];
typedef char TUnk_804C349C_kinds[(offsetof(TUnk_804C349C, kinds) == 0x50) ? 1 : -1];
typedef char TUnk_804C349C_participants[(offsetof(TUnk_804C349C, participants) == 0x60) ? 1 : -1];
typedef char TUnk_804C349C_levels[(offsetof(TUnk_804C349C, levels) == 0x70) ? 1 : -1];
typedef char TUnk_804C349C_recipients[(offsetof(TUnk_804C349C, recipients) == 0x80) ? 1 : -1];
typedef char TUnk_804C349C_holds[(offsetof(TUnk_804C349C, holds) == 0x90) ? 1 : -1];

#endif
