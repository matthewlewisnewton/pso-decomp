#ifndef PSO_BOSS_TUNK_804E4BF0_H
#define PSO_BOSS_TUNK_804E4BF0_H
#include "types.h"
#include "pso/system/task/TObject.h"
#include <dolphin/mtx/GeoTypes.h>

class TUnk_804E4BF0 : public TObject {
public:
    TUnk_804E4BF0(TObject *arg1, void *arg1p);
    virtual ~TUnk_804E4BF0();
    virtual void render();
    virtual void run_task();
    u8 unk_1C[0x6];
    u16 first_part_id;
    u8 unk_24[0x38];
    u16 get_part_entity_id(s32 part);
    s32 spawn_attack_object(Vec *pos, s32 angle, s32 hp, s32 part);
};
typedef char TUnk_804E4BF0_size[sizeof(TUnk_804E4BF0) == 0x5C ? 1 : -1];

#endif
