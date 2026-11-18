#ifndef PSO_TECHNIQUE_TTECGIFOIE_H
#define PSO_TECHNIQUE_TTECGIFOIE_H

#include "types.h"
#include "pso/effect/TUnk_804CC148.h"
#include "pso/effect/particle/TParticleCtrl.h"
#include "pso/system/task/TObject.h"
#include <dolphin/mtx.h>

// One flame of Gifoie, a task TTecGiFoie creates per orbit (vtable at 0x804CC800).
// Nothing names the class or its fields; the comments are readings of the code.
class TUnk_804CC800 : public TObject {
public:
    TUnk_804CC800(Vec *pos, s32 angle, s32 level_band, s32 tech_level, TObject *parent, u8 single_particle);
    virtual ~TUnk_804CC800();
    virtual void run_task();

    TParticleCtrl **emitters;
    Vec origin;
    Vec position;
    f32 radius;
    s32 phase;
    s32 ticks;
    u8 band;       // level band, 0..5
    s8 level;
    u8 orbit_mode; // nonzero selects the plane facing axis_yaw
    u8 single;     // nonzero selects one continuous particle
    s32 axis_yaw;
};

typedef char TUnk_804CC800_size[sizeof(TUnk_804CC800) == 0x4C ? 1 : -1];

struct TTecGiFoie : public TUnk_804CC148 {
    virtual ~TTecGiFoie();
    virtual void vfunc_6(void *);
    virtual void run_task();
    u32 m_ec;
    u8 _padF0[0x48];
    u32 m_138;
    void calc_params();
    static void create(void *arg0, void *arg1, void *arg2);
    virtual void render();
};

typedef char TTecGiFoie_size[sizeof(TTecGiFoie) == 0x13C ? 1 : -1];
#endif
