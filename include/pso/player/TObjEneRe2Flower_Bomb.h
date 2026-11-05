#ifndef PSO_PLAYER_TOBJENERE2FLOWER_BOMB_H
#define PSO_PLAYER_TOBJENERE2FLOWER_BOMB_H
#include "types.h"
#include "pso/player/TUnk_804928CC.h"

class TObjEneRe2Flower_Bomb : public TUnk_804928CC {
public:
    virtual ~TObjEneRe2Flower_Bomb();
    virtual s32 area_attack_deliver_direct(void *, s32, void *, f32);
    void *destroy_and_free(s16);
    virtual void render();
    virtual void run_task();
    u8 unk_B0[0x4];
    Vec startPosition;
    u8 unk_C0[0x18];
    Vec ground_normal;
    u8 unk_E4[0x18];
    void * m_fc;
    s32 m_100;
};
typedef char TObjEneRe2Flower_Bomb_size[sizeof(TObjEneRe2Flower_Bomb) == 0x104 ? 1 : -1];

typedef char FlowerBombStartOffset[offsetof(TObjEneRe2Flower_Bomb, startPosition) == 0xB4 ? 1 : -1];
typedef char FlowerBombGroundNormalOffset[offsetof(TObjEneRe2Flower_Bomb, ground_normal) == 0xD8 ? 1 : -1];
#endif
