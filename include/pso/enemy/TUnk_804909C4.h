#ifndef PSO_ENEMY_TUNK_804909C4_H
#define PSO_ENEMY_TUNK_804909C4_H
#include "types.h"
#include "pso/object/TObjMotion.h"

class TParticleCtrl;

class TUnk_804909C4 : public TObjCollidable {
public:
    TUnk_804909C4(u8 *player, s32 arg2, s32 arg3);
    virtual ~TUnk_804909C4();
    s32 sub_800A3290(s32);
    virtual void run_task();
    Vec velocity;
    s32 effect_rotation[3];
    s32 lifetime;
    u16 owner_id;
    u8 unk_CA[2];
    s32 effect_id;
    TParticleCtrl *effect;
};
typedef char TUnk_804909C4_size[sizeof(TUnk_804909C4) == 0xD4 ? 1 : -1];

#endif
