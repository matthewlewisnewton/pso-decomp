#ifndef PSO_PLAYER_TUNK_80491460_H
#define PSO_PLAYER_TUNK_80491460_H
#include "types.h"
#include "pso/TObject.h"
#include <dolphin/mtx.h>

class TObjPlayer;
class TParticleCtrl;

class TUnk_80491460 : public TObject {
public:
    TUnk_80491460(void *start, s32 angle, s32 source, s32 power);
    virtual ~TUnk_80491460();
    virtual void run_task();

private:
    void try_hit_target(TObjPlayer *player);

    Vec position;
    Vec previous_position;
    Vec velocity;
    u8 unk_40[0x18];
    f32 distance_traveled;
    TParticleCtrl *particle;
    s32 frame;
    s32 source;
    s32 power;
};
typedef char TUnk_80491460_size[sizeof(TUnk_80491460) == 0x6C ? 1 : -1];

#endif
