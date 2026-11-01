#ifndef PSO_MISC_TCHECKMEMORYCARD_H
#define PSO_MISC_TCHECKMEMORYCARD_H

#include "types.h"
#include "pso/TObject.h"
#include <stddef.h>

struct TCheckMemoryCard : public TObject {
    TCheckMemoryCard(TObject *arg1, void *arg2, void *arg3, void *arg4);
    virtual ~TCheckMemoryCard();
    s32 sub_8033BB14();
    u32 m_1c;
    u32 m_20;
    s32 m_24;
    u32 m_28;
    s32 m_2c;
    void * m_30;
    void *m_34;
    u32 m_38;
    u32 m_3c;
    s32 m_40;
    s32 m_44;
    u32 m_48;
    u32 m_4c;
    virtual void render();
    virtual void run_task();
    void create_message_and_menu(u32 message, s32 selection, u32 first, u32 second);
    void close_windows();
    void set_state(s32 state);
    void reset();
    void update_card_display(s32 kind, s32 menu, s32 first, s32 second);
    void init(u32 message, s32 selection, u32 first, u32 second);
    void close_and_update_display();
    void update_display_state();
    void fn_8033C19C();
    void fn_8033C198();
    void fn_8033C178();
    void poll_card_status();
    void init_from_keyboard_state();
    void handle_menu_selection();
    u8 unk_50[0x200];
};

typedef char TCheckMemoryCard_size[sizeof(TCheckMemoryCard) == 0x250 ? 1 : -1];

typedef char TCheckMemoryCard_offset_1c[offsetof(TCheckMemoryCard, m_1c) == 0x1c ? 1 : -1];
typedef char TCheckMemoryCard_offset_20[offsetof(TCheckMemoryCard, m_20) == 0x20 ? 1 : -1];
typedef char TCheckMemoryCard_offset_24[offsetof(TCheckMemoryCard, m_24) == 0x24 ? 1 : -1];
typedef char TCheckMemoryCard_offset_28[offsetof(TCheckMemoryCard, m_28) == 0x28 ? 1 : -1];
typedef char TCheckMemoryCard_offset_2c[offsetof(TCheckMemoryCard, m_2c) == 0x2c ? 1 : -1];
typedef char TCheckMemoryCard_offset_30[offsetof(TCheckMemoryCard, m_30) == 0x30 ? 1 : -1];
typedef char TCheckMemoryCard_offset_34[offsetof(TCheckMemoryCard, m_34) == 0x34 ? 1 : -1];
typedef char TCheckMemoryCard_offset_38[offsetof(TCheckMemoryCard, m_38) == 0x38 ? 1 : -1];
typedef char TCheckMemoryCard_offset_3c[offsetof(TCheckMemoryCard, m_3c) == 0x3c ? 1 : -1];
typedef char TCheckMemoryCard_offset_40[offsetof(TCheckMemoryCard, m_40) == 0x40 ? 1 : -1];
typedef char TCheckMemoryCard_offset_44[offsetof(TCheckMemoryCard, m_44) == 0x44 ? 1 : -1];
typedef char TCheckMemoryCard_offset_48[offsetof(TCheckMemoryCard, m_48) == 0x48 ? 1 : -1];
typedef char TCheckMemoryCard_offset_4c[offsetof(TCheckMemoryCard, m_4c) == 0x4c ? 1 : -1];

extern "C" {
void *fn_8033C5E4(TObject *parent, void *arg1, void *arg2);
void *__dt__16TCheckMemoryCardFv(void *arg0, s16 arg1);
}

#endif
