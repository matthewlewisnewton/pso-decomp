#ifndef PSO_BOSS_DARKFALZ_TOBJDFDEMO4_H
#define PSO_BOSS_DARKFALZ_TOBJDFDEMO4_H

#include "types.h"
#include "pso/object/base/TObjMotion.h"

struct TObjDFDemo4 : public TObjBase {
    TObjDFDemo4(TObject *parent, const Vec *position, s32 angle);
    virtual ~TObjDFDemo4();
    void draw_afterimages();
    void draw_body();
    virtual void render();
    virtual void run_task();
    void* m_90;
    u8 _pad94[0x54];
    void* m_e8;
    u8 _padEC[0x8];
    u32 m_f4;
    u32 m_f8;
    u8 _padFC[0x4];
    u32 m_100;
    void* m_104;
    static TObjDFDemo4 *create(TObject *parent, const Vec *position, s32 angle);
    u8 unk_108[0x14];
};

typedef char TObjDFDemo4_size[sizeof(TObjDFDemo4) == 0x11C ? 1 : -1];
#endif
