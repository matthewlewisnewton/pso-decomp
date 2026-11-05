#ifndef PSO_MISC_TUNK_804B7C04_H
#define PSO_MISC_TUNK_804B7C04_H
#include "types.h"
#include "pso/TObject.h"

class TUnk_804B7C04 : public TObject {
public:
    virtual ~TUnk_804B7C04();
    virtual void run_task();
    u8 unk_1C[0x10];
    int m_2c;
    u8 unk_30[0xC];
};
typedef char TUnk_804B7C04_size[sizeof(TUnk_804B7C04) == 0x3C ? 1 : -1];

#endif
