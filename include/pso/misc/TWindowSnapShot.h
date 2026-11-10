#ifndef PSO_MISC_TWINDOWSNAPSHOT_H
#define PSO_MISC_TWINDOWSNAPSHOT_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowSnapShot : public TWindowBase {
    virtual ~TWindowSnapShot();
    virtual void render();
    u8 m_60;
    void play_open_sound();
    virtual void run_task();
    u8 unk_61[0x3];
};

typedef char TWindowSnapShot_size[sizeof(TWindowSnapShot) == 0x64 ? 1 : -1];

extern "C" {
u8 *TWindowSnapShot__ct(TWindowSnapShot *arg0, s32 arg1);
void *__dt__15TWindowSnapShotFv(void *arg0, s16 arg1);
}
extern "C" {
void render__15TWindowSnapShotFv(u8 *arg0);
}

#endif
