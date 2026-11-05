#ifndef PSO_UNK_TUNK_804E4B24_H
#define PSO_UNK_TUNK_804E4B24_H
#include "types.h"
#include "pso/TObject.h"

class TUnk_804E4B24 : public TObject {
public:
    virtual ~TUnk_804E4B24();
    void update_collision();
    virtual void run_task();
    u8 unk_1C[0x8];
    f32 m_24;
    u8 unk_28[0x4];
    void * m_2c;
    u8 unk_30[0x4];
    s32 m_34;
    u8 unk_38[0x4];
    s32 m_3c;
    s32 m_40;
    u8 unk_44[0x34];
};
typedef char TUnk_804E4B24_size[sizeof(TUnk_804E4B24) == 0x78 ? 1 : -1];

#endif
