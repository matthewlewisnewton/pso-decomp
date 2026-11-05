#ifndef PSO_UI_TADLDQUESTPRTGC_H
#define PSO_UI_TADLDQUESTPRTGC_H

#include "types.h"
#include "pso/TObject.h"
#include <dolphin/mtx/GeoTypes.h>

class TParticleCtrl;

struct TAdLdQuestPrtGC : public TObject {
    TAdLdQuestPrtGC(TObject *parent);
    virtual ~TAdLdQuestPrtGC();
    virtual void run_task();
    TParticleCtrl *particles[4]; // 0x1c: queued for destruction by the owner
    Vec positions[4];           // 0x2c: retained by the particle factory
    struct Angles { u32 x, y, z; } angles[4]; // 0x5c
    struct AngleSteps { s32 x, y, z; } angle_steps[4];      // 0x8c
    u32 color_index;            // 0xbc
    u32 color_frames;           // 0xc0
    u32 frames;                 // 0xc4
    virtual void render();
    // Only RGBA are initialized here; the remaining record fields are unresolved.
    struct ColorRecord { f32 r, g, b, a; u8 remaining[0x14]; } colors[4]; // 0xc8
};

typedef char TAdLdQuestPrtGC_size[sizeof(TAdLdQuestPrtGC) == 0x158 ? 1 : -1];
#endif
