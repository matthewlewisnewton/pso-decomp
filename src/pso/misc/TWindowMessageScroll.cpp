#include "types.h"
#include "pso/misc/TWindowMessageScroll.h"
#include "pso/misc/TWindowMessageQuest.h"
#include "pso/unk/text_8026B260.h"
#include "pso/misc/TWindowBase.h"

#include "pso/misc/TLobby.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowSubComCard.h"

struct RecoveredGlobal_8035D694___vt__20TWindowMessageScroll {
    s32 value;
    u8 remaining[0x14];
};

extern "C" {
s32 retire_scrolled_lines__14TWindowMessageFv(f32);
extern s32 __vt__20TWindowMessageScroll[];
extern s32 TWindowMessageScroll__class_name;
extern const f32 lbl_805E01B8;

void TWindowMessageScroll::run_task() {
    u8 *arg0 = (u8 *)this;
    f32 temp_f1;
    temp_f1 = this->m_6c;
    this->m_6c = (f32) (temp_f1 + *(f32 *)((s8 *)arg0 + 0x94));
    retire_scrolled_lines__14TWindowMessageFv(temp_f1);
    ((TWindowDD *)arg0)->initialize_subwindow();
    ((TWindowBase *)arg0)->update_fade();
    ((TWindowBase *)arg0)->update_window_entry_list((u8 *)&this->m_24);
    if ((((TWindowBase *)arg0)->sub_80244994() != 0) && (*(f32 *)&this->unk_80 <= this->m_6c)) {
        *this->m_98 = 1;
    }
}

}
TWindowMessageScroll::~TWindowMessageScroll() {

}

typedef char RecoveredGlobal_8035D694___vt__20TWindowMessageScroll_size[sizeof(RecoveredGlobal_8035D694___vt__20TWindowMessageScroll) == 0x18 ? 1 : -1];
TWindowMessageScroll::TWindowMessageScroll(s32 layout, s32 *completion)
    : TWindowMessageQuest(layout) {
    m_name = (const char *)TWindowMessageScroll__class_name;
    m_94 = lbl_805E01B8;
    m_98 = completion;
    *m_98 = 0;
}
