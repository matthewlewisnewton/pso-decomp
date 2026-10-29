#ifndef PSO_MISC_TODRAGONFLY_H
#define PSO_MISC_TODRAGONFLY_H

#include "types.h"
#include "pso/misc/TUnk_804AFBF8.h"

struct TODragonfly : public TUnk_804AFBF8 {
    virtual ~TODragonfly();
    virtual void vfunc_14();
    void sub_80164A90();
    void sub_80164990();
    virtual void render();
    virtual void run_task();
    u8 unk_C8[0x4];
    u32 m_cc;
    u8 _padD0[0x4];
    void* m_d4;
    u8 unk_D8[0x8];
    f32 m_e0;
    u8 unk_E4[0x4];
    f32 m_e8;
    f32 m_ec;
    union { u8 unk_F0[4]; f32 bob_offset; };
    f32 m_f4;
    u32 m_f8;
    u32 m_fc;
    s32 pick_random_destination(f32 farg0);
    void move_toward_target();
    void update_idle();
};

typedef char TODragonfly_size[sizeof(TODragonfly) == 0x100 ? 1 : -1];
#endif
