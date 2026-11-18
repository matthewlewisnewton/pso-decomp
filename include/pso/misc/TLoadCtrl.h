#ifndef PSO_MISC_TLOADCTRL_H
#define PSO_MISC_TLOADCTRL_H

#include "types.h"
#include "pso/TObject.h"

struct TLoadCtrl : public TObject {
    explicit TLoadCtrl(TObject *parent);
    virtual ~TLoadCtrl();
    s32 m_1c;
    s32 m_20;
    virtual void render();
    virtual void run_task();
    static void cleanup_scene();
    static void start_loading(u32 arg0);
    static void poll_default();
    static void step();
    static void set_field1C(s32 arg0);
};

extern "C" {
extern TLoadCtrl *TLoadCtrl__instance;
extern TObject *TLoadCtrl__fade_task;
}

typedef char TLoadCtrl_size[sizeof(TLoadCtrl) == 0x24 ? 1 : -1];
#endif
