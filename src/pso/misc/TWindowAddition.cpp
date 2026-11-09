#include "pso/misc/WindowConstructorAbi.h"
#include "types.h"
#include "pso/misc/TLobby_8001D6A0.h"
#include "pso/misc/TWindowSubStatusDisp_80228CC0.h"
#include "pso/misc/TWindowSubStatusDisp_80228F5C.h"
#include "pso/ui/TObjBagWarnWin_8006EF24.h"
#include "pso/misc/TWindowAddition.h"
#include "pso/misc/TWindowSubStatusDisp.h"

extern "C" {
extern s32 TWindowSubStatusDisp__count_ratio_value;
extern s32 lbl_805DCAB8;
void sub_802443B4__15TWindowAdditionFPUc(void *, void *);
void __dl__7TObjectFPv(void *);
extern s32 __vt__15TWindowAddition[];

TWindowAddition::~TWindowAddition() {}

TWindowAddition::TWindowAddition(u8 *descriptor, s16 client, u8 *position)
    : TWindowBase(descriptor, client, position) {
    sub_802443B4(descriptor);
}
void TWindowSubStatusDisp::set_count_ratio_text(s32 arg1, s32 arg2) {
    s32 arg0 = (s32)this;
    text_builder_reset();
    text_builder_append((u8 *)(TQuestVmDownLoadServer__sub_8006EF6C(0x67)));
    append_text_space();
    append_padded_number((arg1), (2U));
    text_builder_append((u8 *)&lbl_805DCAB8);
    append_padded_number((arg2), (2U));
    ((TWindowSubStatusDisp *)arg0)->set_entry_display_value((int) (get_shared_text_buffer()));
    TWindowSubStatusDisp__count_ratio_value = arg1;
}

}
