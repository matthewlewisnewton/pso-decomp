#ifndef PSO_BOSS_TBOSS6ZANZO_H
#define PSO_BOSS_TBOSS6ZANZO_H

#include "types.h"
#include "pso/TObject.h"
#include <dolphin/mtx.h>
#include <stddef.h>

struct Boss6TrailPoint { u32 color; Vec position; };
struct Boss6TrailFrame { s32 active; Boss6TrailPoint *points; };

struct TBoss6Zanzo : public TObject {
    TBoss6Zanzo(TObject *arg1, s32 arg2, s32 arg3);
    virtual ~TBoss6Zanzo();
    void copy_trail_buffer(Boss6TrailFrame *, Boss6TrailFrame *);
    void set_effect_points(const Vec *, const u32 *);
    void draw_trail();
    virtual void run_task();
    Boss6TrailFrame *frames;
    Boss6TrailFrame *current;
    s32 point_count;
    s32 frame_count;
    virtual void render();
};

typedef char Boss6TrailPoint_size[sizeof(Boss6TrailPoint) == 0x10 ? 1 : -1];
typedef char Boss6TrailPoint_position_offset[offsetof(Boss6TrailPoint, position) == 0x4 ? 1 : -1];
typedef char Boss6TrailFrame_size[sizeof(Boss6TrailFrame) == 0x8 ? 1 : -1];
typedef char TBoss6Zanzo_size[sizeof(TBoss6Zanzo) == 0x2C ? 1 : -1];
typedef char TBoss6Zanzo_current_offset[offsetof(TBoss6Zanzo, current) == 0x20 ? 1 : -1];
typedef char TBoss6Zanzo_point_count_offset[offsetof(TBoss6Zanzo, point_count) == 0x24 ? 1 : -1];

extern "C" {
void TBoss6Zanzo__sub_803205A0(Boss6TrailPoint *arg0, const Boss6TrailPoint *arg1);
}

// --- C functions defined in TBoss6Zanzo.cpp ---
extern "C" {
void TBoss6Zanzo__sub_803205A0(Boss6TrailPoint *arg0, const Boss6TrailPoint *arg1);
}
// --- end of C functions

#endif
