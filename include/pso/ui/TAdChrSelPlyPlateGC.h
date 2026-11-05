#ifndef PSO_UI_TADCHRSELPLYPLATEGC_H
#define PSO_UI_TADCHRSELPLYPLATEGC_H

#include "types.h"
#include "pso/TObject.h"

struct TAdChrSelPlyPlateGC : public TObject {
    virtual ~TAdChrSelPlyPlateGC();
    u8 unk_1C[0x46C];
    void* m_4a4;
    u8 _pad4A8[0x40];
    u32 m_4e8;
    u32 m_4ec;
    u32 m_4f0;
    u32 m_4f4;
    u32 m_4f8;
    u32 m_4fc;
    u8 _pad500[0x34];
    u32 m_534;
    u8 unk_51C[0x1C];
};

typedef char TAdChrSelPlyPlateGC_size[sizeof(TAdChrSelPlyPlateGC) == 0x538 ? 1 : -1];

extern "C" {
void *__dt__19TAdChrSelPlyPlateGCFv(void *arg0, s16 arg1);
}

// --- C functions defined in TAdChrSelPlyPlateGC.cpp ---
extern "C" {
void *__dt__19TAdChrSelPlyPlateGCFv(void *arg0, s16 arg1);
}
// --- end of C functions

#endif
