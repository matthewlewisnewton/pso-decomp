#ifndef PSO_PLAYER_TUNK_804B1B80_H
#define PSO_PLAYER_TUNK_804B1B80_H
#include "types.h"
#include "pso/misc/TUnk_804AFBF8.h"

class TUnk_804B1B80 : public TUnk_804AFBF8 {
public:
    virtual ~TUnk_804B1B80();
    virtual void vfunc_14();
    virtual void vfunc_15();
    virtual void vfunc_16();
    virtual void run_task();
    void check_trigger();
    void update_trigger();
    void *init_fields();
    void *destroy(s16);
    s32 sub_80166EA8(int);
    s32 sub_80166E64();
    union { u8 unk_C8[0x4]; s32 trigger_mode; };
    u32 m_cc;
    u8 unk_D0[0x4];
    u32 m_d4;
};

#endif
