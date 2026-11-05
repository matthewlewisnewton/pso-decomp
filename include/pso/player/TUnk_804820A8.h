#ifndef PSO_PLAYER_TUNK_804820A8_H
#define PSO_PLAYER_TUNK_804820A8_H
#include "types.h"
#include "pso/player/TUnk_804820C0.h"

class TUnk_804820A8 : public TUnk_804820C0 {
public:
    virtual ~TUnk_804820A8();
    virtual void run_task();
    virtual void render();
    u8 unk_20[0x344];
};
typedef char TUnk_804820A8_size[sizeof(TUnk_804820A8) == 0x364 ? 1 : -1];

#endif
