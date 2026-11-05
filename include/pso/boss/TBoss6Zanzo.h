#ifndef PSO_BOSS_TBOSS6ZANZO_H
#define PSO_BOSS_TBOSS6ZANZO_H

#include "types.h"
#include "pso/TObject.h"
#include "pso/system/vector.h"

// One afterimage point: the word fn_80257720 fills from the offset table, then
// the position.
struct Boss6ZanzoPoint {
    u8 unk_00[0x4];
    Vec pos;
};

struct Boss6ZanzoPoints {
    s32 dirty;
    Boss6ZanzoPoint *points;
};

struct TBoss6Zanzo : public TObject {
    TBoss6Zanzo(TObject *arg1, s32 arg2, s32 arg3);
    virtual ~TBoss6Zanzo();
    static TBoss6Zanzo *create(TObject *parent, s32 arg2, s32 arg3);
    void copy_trail_buffer(void *, void *);
    void set_effect_points(Vec *points, u32 *offsets);
    virtual void run_task();
    u32 m_1c;
    Boss6ZanzoPoints *m_20;
    u32 m_24;
    u32 m_28;
    virtual void render();
};

typedef char TBoss6Zanzo_size[sizeof(TBoss6Zanzo) == 0x2C ? 1 : -1];

extern "C" {
void TBoss6Zanzo__sub_803205A0(s32 *arg0, s32 *arg1);
s32 fn_803204B0(void *p);
}

// --- C functions defined in TBoss6Zanzo.cpp ---
extern "C" {
void TBoss6Zanzo__sub_803205A0(s32 *arg0, s32 *arg1);
s32 fn_803204B0(void *p);
}
// --- end of C functions

#endif
