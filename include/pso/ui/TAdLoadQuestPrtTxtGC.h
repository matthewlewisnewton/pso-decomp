#ifndef PSO_UI_TADLOADQUESTPRTTXTGC_H
#define PSO_UI_TADLOADQUESTPRTTXTGC_H

#include "types.h"
#include "pso/TObject.h"

struct TAdLoadQuestPrtTxtGC : public TObject {
    virtual ~TAdLoadQuestPrtTxtGC();
    u32 m_1c;
    void* m_20;
    u8 _pad24[0x1FC];
    u32 m_220;
    u32 m_224;
    virtual void render();
    static void *create_particle(void *arg0, s32 arg1, s32 arg2);
    virtual void run_task();
};

typedef char TAdLoadQuestPrtTxtGC_size[sizeof(TAdLoadQuestPrtTxtGC) == 0x228 ? 1 : -1];
#endif
