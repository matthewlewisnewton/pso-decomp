#ifndef PSO_MISC_TWINDOWDUELRESULT_H
#define PSO_MISC_TWINDOWDUELRESULT_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowDuelResult : public TWindowBase {
    TWindowDuelResult(s32 arg1);
    virtual ~TWindowDuelResult();
    virtual void run_task();
    virtual void render();
    void sub_8024F094();
    void sub_8024EF40();
    void sub_8024F090();
    void sub_8024EF3C();
    f32 m_60;
    f32 m_64;
    u32 m_68;
    void *init(void *arg1, void *arg2, void *arg3);
    static int set_default_status(void* p, int a1);
};

typedef char TWindowDuelResult_size[sizeof(TWindowDuelResult) == 0x6C ? 1 : -1];
#endif
