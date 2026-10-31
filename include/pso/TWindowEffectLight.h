#ifndef PSO_TWINDOWEFFECTLIGHT_H
#define PSO_TWINDOWEFFECTLIGHT_H
#include "pso/TObject.h"
#include "types.h"

class TWindowEffectLight : public TObject {
public:
    TWindowEffectLight(void *arg1, s16 arg2, u32 id);
    virtual ~TWindowEffectLight();
    void draw_outline_quad(s32);
    virtual void render();
    virtual void run_task();
public:
    f32 calc_scale();
    u32 calc_alpha();
    static void *create(void *arg0, s16 arg1, u32 arg2);
    f32 x, y;
    s16 effect_kind, age;
    u32 player_id;
};

typedef char TWindowEffectLight_size[sizeof(TWindowEffectLight) == 0x2C ? 1 : -1];

#endif
