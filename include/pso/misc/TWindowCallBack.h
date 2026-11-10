#ifndef PSO_MISC_TWINDOWCALLBACK_H
#define PSO_MISC_TWINDOWCALLBACK_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowCallBack : public TWindowBase {
    TWindowCallBack(u8 *position, u8 *scale, s32 callback_word);
    virtual ~TWindowCallBack();
    void render();
    void run_task();
    // Retained legacy invocation view; mixed producer signatures remain qualified.
    void (*callback)(TWindowCallBack *, s32);
};

typedef char TWindowCallBack_size[sizeof(TWindowCallBack) == 0x64 ? 1 : -1];
void build_6xA3_olga_flow_boss_actions(void *p);
extern "C" {
void fn_802ACD40(void *p);
void fn_802ACD60(void *p);
void set_field_60__15TWindowCallBackFPvi(void *p, s32 v);
}

#endif
