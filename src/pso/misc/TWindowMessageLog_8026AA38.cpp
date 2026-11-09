#include "pso/misc/Scroll_8026D790.h"
#include "pso/misc/TWindowDrawContext.h"
#include "types.h"
#include "pso/misc/TWindowCtrl_8026AD44.h"
#include "pso/misc/TWindowMessageLog_8026AA38.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowMessage.h"
#include "pso/misc/TWindowMessageLog.h"

struct RecoveredGlobal_8026AB3C___vt__17TWindowMessageLog { s32 value; u8 remaining[0x14]; };
typedef char RecoveredGlobal_8026AB3C___vt__17TWindowMessageLog_size[sizeof(RecoveredGlobal_8026AB3C___vt__17TWindowMessageLog) == 0x18 ? 1 : -1];

#include <stddef.h>
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowSubStatusDisp.h"

#pragma readonly_strings on

extern "C" {
const char *lbl_805D3990 = "TWindowMessageLog";
}

struct Stack_8026ABA8 {
    f32 sp8;
    f32 spC;
};

struct RecoveredGlobal_8026ABA8___vt__17TWindowMessageLog {
    s32 value;
    u8 remaining[0x14];
};

extern "C" {
s32 draw_visible_window_entries(void *, void *, int);
s32 draw_window_scrollbar(int, int, void *);
extern const f32 lbl_805DD254;
void *__dt__14TWindowMessageFv(void *arg0, s16 arg1);
s32 __dl__7TObjectFPv(void *);
extern RecoveredGlobal_8026AB3C___vt__17TWindowMessageLog __vt__17TWindowMessageLog;
extern const char *lbl_805D3990;
extern const f32 lbl_805DD240;
extern const f32 lbl_805DD258;
void TWindowMessageLog::render() {
    s32 temp_r3;
    temp_r3 = (s32)get_draw_context__11TWindowBaseFPv(this);
    draw_window_frame((void *)temp_r3);
    draw_visible_window_entries(this, (void *) (((u8 *)this) + 0x24), temp_r3);
    draw_window_scrollbar((int) (*(s32 *)((s8 *)((u8 *)this) + 0x90)), temp_r3, (void *) (((u8 *)this) + 0x68));
}
void TWindowMessageLog::run_task() {
    if (!(*(s32 *)&this->m_2c & 2)) {
        *(s32 *)&this->m_5c = 0x01000000;
    }
    if ((f32) *(s32 *)&this->m_5c >= lbl_805DD254) {
        fn_8026D9C0((void *)(*(u8 **)((s8 *)((u8 *)this) + 0x90)));
    }
    update_scroll_animation();
    update_scroll();
    ((TWindowDD *)((u8 *)this))->initialize_subwindow();
    update_fade_offset();
    update_window_entry_list(((u8 *)this) + 0x24);
}
TWindowMessageLog::~TWindowMessageLog() {
    fn_8026D9D0((void *)((s32)m_90), 1);
    TWindowCtrl__sub_8026AD60();
}
typedef char RecoveredGlobal_8026ABA8___vt__17TWindowMessageLog_size[sizeof(RecoveredGlobal_8026ABA8___vt__17TWindowMessageLog) == 0x18 ? 1 : -1];
TWindowMessageLog::TWindowMessageLog(s32 arg1, s32 arg2)
    : TWindowMessage(arg1, 0x1E, arg2) {
    typedef char sp8_offset[(offsetof(Stack_8026ABA8, sp8) == 0x0) ? 1 : -1];
    typedef char spC_offset[(offsetof(Stack_8026ABA8, spC) == 0x4) ? 1 : -1];
    Stack_8026ABA8 stack;
    f32 temp_f1;
    f32 temp_f2;
    s32 temp_r3;
    s32 var_r0;
    m_name = lbl_805D3990;
    TWindowCtrl__sub_8026AD78(this);
    temp_f2 = m_38;
    temp_f1 = temp_f2 - lbl_805DD258;
    stack.spC = lbl_805DD240;
    stack.sp8 = temp_f1;
    m_90 = (u32)new Scroll_8026D790(&stack.sp8);
    m_2c = (s32) (m_2c | 0x80);
    m_94 = (f32) lbl_805DD240;
    load_chat_history();
}

}
