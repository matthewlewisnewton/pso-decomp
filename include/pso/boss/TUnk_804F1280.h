#ifndef PSO_BOSS_TUNK_804F1280_H
#define PSO_BOSS_TUNK_804F1280_H
#include "types.h"
#include "pso/TObject.h"

class TUnk_804F1280 : public TObject {
public:
    virtual ~TUnk_804F1280();
    void *init_object(void *);
    void *destroy(s16);
    virtual void render();
    virtual void run_task();
    u8 unk_1C[0x10];
    f32 m_2c;
    u8 unk_30[0x4];
    s32 m_34;
    u8 unk_38[0x4];
    s32 m_3c;
    u8 unk_40[0x4];
};
typedef char TUnk_804F1280_size[sizeof(TUnk_804F1280) == 0x44 ? 1 : -1];

#endif
