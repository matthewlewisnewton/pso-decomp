#ifndef PSO_UI_TADSNAKPASSCONFIRMGC_H
#define PSO_UI_TADSNAKPASSCONFIRMGC_H

#include "types.h"
#include "pso/ui/TAdYesNoBaseGC.h"

struct TAdSnAkPassConfirmGC : public TAdYesNoBaseGC {
    virtual ~TAdSnAkPassConfirmGC();
    virtual void vfunc_8();
    virtual void vfunc_9();
    u32 m_48;
    s32 get_confirm_state();
    virtual void render();
    virtual void run_task();
};

typedef char TAdSnAkPassConfirmGC_size[sizeof(TAdSnAkPassConfirmGC) == 0x4C ? 1 : -1];

extern "C" {
int TAdSnAkPassConfirmGC__vt4(void *p);
int TAdSnAkPassConfirmGC__vt5(void *p);
void TAdSnAkPassConfirmGC__vt8(void);
void *__dt__20TAdSnAkPassConfirmGCFv(void *arg0, s16 arg1);
}

// --- C functions defined in TAdSnAkPassConfirmGC.cpp ---
extern "C" {
int TAdSnAkPassConfirmGC__vt4(void *p);
int TAdSnAkPassConfirmGC__vt5(void *p);
void TAdSnAkPassConfirmGC__vt8(void);
void *__dt__20TAdSnAkPassConfirmGCFv(void *arg0, s16 arg1);
}
// --- end of C functions

#endif
