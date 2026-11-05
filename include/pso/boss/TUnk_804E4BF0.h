#ifndef PSO_BOSS_TUNK_804E4BF0_H
#define PSO_BOSS_TUNK_804E4BF0_H
#include "types.h"
#include "pso/TObject.h"

struct Vec;

// The first one created is boss8_dragon_leader_part. It holds the set record
// the dragon's parts spawn from: part n gets the record's type and entity id
// plus n.
class TUnk_804E4BF0 : public TObject {
public:
    TUnk_804E4BF0(TObject *arg1, void *arg1p);
    virtual ~TUnk_804E4BF0();
    void *dt(s16);
    virtual void render();
    virtual void run_task();
    u16 get_part_entity_id(s32 part);
    s32 setup_attack_slot(Vec *pos, s32 angle, s32 part, u8 *slot);
    s32 spawn_attack_object(Vec *pos, s32 angle, s32 hp, s32 part);
    s16 part_type;
    u8 unk_1E[0x4];
    u16 first_part_id;
    u8 unk_24[0x38];
};
typedef char TUnk_804E4BF0_size[sizeof(TUnk_804E4BF0) == 0x5C ? 1 : -1];
#include <stddef.h>
typedef char TUnk_804E4BF0_first_part_id[offsetof(TUnk_804E4BF0, first_part_id) == 0x22 ? 1 : -1];

extern "C" TUnk_804E4BF0 *boss8_dragon_leader_part;

#endif
