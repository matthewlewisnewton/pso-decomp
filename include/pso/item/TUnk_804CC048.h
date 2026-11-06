#ifndef PSO_ITEM_TUNK_804CC048_H
#define PSO_ITEM_TUNK_804CC048_H
#include "types.h"
#include "pso/TObject.h"

class TUnk_804CC048 : public TObject {
public:
    virtual ~TUnk_804CC048();
    void *construct(void *, void *, void *);
    virtual void render();
    u8 unk_1C[0x1080];
    u32 m_109c;
    u8 unk_10A0[0x4];
    void * m_10a4;
};
typedef char TUnk_804CC048_size[sizeof(TUnk_804CC048) == 0x10A8 ? 1 : -1];

#endif
