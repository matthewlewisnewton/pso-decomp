#ifndef PSO_TTECZONDEEFF_H
#define PSO_TTECZONDEEFF_H
#include "pso/TObject.h"
#include "types.h"

class TTecZondeEff : public TObject {
public:
    virtual ~TTecZondeEff();
    void randomize_bolt_jitter();
    void calc_lightning_scatter_direction(s32, void *);
    s32 build_lightning_strip(void *, void *, f32 *, f32 *);
    virtual void run_task();
    virtual void render();
public:
    s32 calc_dominant_axis();
    void init_bolt_points();
    static void init_resources();
public:
    u8 *construct(u8 *arg1, u8 *arg2, u8 *arg3, f32 farg0);
    u8 *construct_bolt_effect(u8 *arg1, u8 *arg2, u8 *arg3, s32 arg4, s32 arg5, f32 farg0, f32 farg1);
};

#endif
