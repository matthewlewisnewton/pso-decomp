#ifndef PSO_UI_TADPSOPASSSAVEGC_H
#define PSO_UI_TADPSOPASSSAVEGC_H

#include "types.h"
#include "pso/ui/TAdYesNoBaseGC.h"

struct TAdPsoPassSaveGC : public TAdYesNoBaseGC {
    virtual ~TAdPsoPassSaveGC();
    virtual void render();
    virtual void run_task();
};

typedef char TAdPsoPassSaveGC_size[sizeof(TAdPsoPassSaveGC) == 0x48 ? 1 : -1];

extern "C" {
void *TAdPsoPassSaveGC__ct(void *parent);
void TAdPsoPassSaveGC__vt4(void);
void TAdPsoPassSaveGC__vt5(void);
void TAdPsoPassSaveGC__vt8(void);
void *__dt__16TAdPsoPassSaveGCFv(void *arg0, s16 arg1);
}

// --- C functions defined in TAdPsoPassSaveGC.cpp ---
extern "C" {
void *TAdPsoPassSaveGC__ct(void *parent);
void TAdPsoPassSaveGC__vt4(void);
void TAdPsoPassSaveGC__vt5(void);
void TAdPsoPassSaveGC__vt8(void);
void *__dt__16TAdPsoPassSaveGCFv(void *arg0, s16 arg1);
}
// --- end of C functions

#endif
