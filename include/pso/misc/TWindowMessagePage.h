#ifndef PSO_MISC_TWINDOWMESSAGEPAGE_H
#define PSO_MISC_TWINDOWMESSAGEPAGE_H

#include "types.h"
#include <stddef.h>
#include "pso/misc/TWindowMessage.h"

struct TWindowMessagePage : public TWindowMessage {
    TWindowMessagePage(s32 layout, s32 capacity, s32 client);
    virtual ~TWindowMessagePage();
    s32 is_message_window_ready();
    s32 is_ready();
    void update_message();
    void set_message(void *msg, s32 flags);
    static u8 *create(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
    static void set_text(s32 a, s32 b, s32 c);
    void render();
    void run_task();
    s32 m_90;
    u32 m_94;
};

typedef char TWindowMessagePage_size[sizeof(TWindowMessagePage) == 0x98 ? 1 : -1];

extern "C" {
void *__dt__18TWindowMessagePageFv(void *arg0, s16 arg1);
}

// --- C functions defined in TWindowMessagePage.cpp ---
extern "C" {
}
// --- end of C functions

typedef char TWindowMessagePage_owned_field_offset[offsetof(TWindowMessagePage, m_90) == 0x90 ? 1 : -1];

#endif
