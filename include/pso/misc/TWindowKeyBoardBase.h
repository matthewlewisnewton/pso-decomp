#ifndef PSO_MISC_TWINDOWKEYBOARDBASE_H
#define PSO_MISC_TWINDOWKEYBOARDBASE_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowKeyBoardBase : public TWindowBase {
    TWindowKeyBoardBase();
    virtual ~TWindowKeyBoardBase();
    void init_keyboard_text_field(u32, u32);
    void set_text(char *text);
    void sub_8025E6DC(u8 *);
    void draw_wrapped_text(void *, void *);
    void draw_text_glyphs(void *, void *);
    int sub_8025EB68();
    bool sub_8025CB10();
    int is_key_active();
    void set_flag62_bit8();
    void set_flag62_bit2();
    int is_active();
    u16 m_60;
    u16 m_62;
    u8 _pad64[0x1];
    s8 m_65;
    u8 _pad66[0x2];
    u32 m_68;
    u16 *m_6c;
    s32 m_70;
    u8 unk_74[0x8];
    u32 m_7c;
    u8 unk_80[0x4];
    u16 *m_84;
    s32 m_88;
    u8 unk_8C[0x8];
    s32 m_94;
    u8 unk_98[0x4];
    u32 m_9c;
    u32 m_a0;
    u32 m_a4;
    u32 m_a8;
    u32 m_ac;
    u32 m_b0;
    u32 m_b4;
    virtual void render();
    virtual void run_task();
    void insert_character(u16 arg1);
};

typedef char KeyboardBase_holder_span[offsetof(TWindowKeyBoardBase, m_84) - offsetof(TWindowKeyBoardBase, m_6c) == 0x18 ? 1 : -1];
typedef char KeyboardBase_second_holder_span[offsetof(TWindowKeyBoardBase, m_9c) - offsetof(TWindowKeyBoardBase, m_84) == 0x18 ? 1 : -1];
typedef char TWindowKeyBoardBase_size[sizeof(TWindowKeyBoardBase) == 0xB8 ? 1 : -1];
#endif
