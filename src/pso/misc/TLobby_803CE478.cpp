#include "types.h"
#include "pso/misc/TLobby_803CE200.h"
#include "pso/misc/TLobby_803CE478.h"
#include "pso/misc/TLobby.h"
#include "pso/system/AdxStreamRuntime.h"

void TLobby::update_scroll() {
    u8 *arg0 = (u8 *)this;
    s32 spC;
    s32 sp8;

    *(s32 *)((s8 *)arg0 + 0x1B0) = (s32) (*(s32 *)((s8 *)arg0 + 0x1B0) + 1);
    if (((s32) *(u8 *)((s8 *)arg0 + 0x1A8) == 1) && ((s32) *(s32 *)((s8 *)arg0 + 0x1B0) >= (s32) *(s32 *)((s8 *)arg0 + 0x1BC))) {
        *(s32 *)((s8 *)arg0 + 0x1B0) = (s32) *(s32 *)((s8 *)arg0 + 0x1B8);
    }
    if (((s32) *(u8 *)((s8 *)arg0 + 0x1A9) == 1) && ((s32) *(s32 *)((s8 *)arg0 + 0x1B0) < ((TLobby *)(*(s32 *)&this->m_flags))->get_scroll_offset())) {
        TLobby__sub_803CE220();
        ((TLobby *)(*(s32 *)&this->m_flags))->get_entry_pair((s32)((int) (*(s32 *)((s8 *)arg0 + 0x1B0))), &spC, &sp8);
        set_scroll_offset__6TLobbyFl((AdxStreamFile *)this->m_prev, spC / 2048);
        set_scroll_position__6TLobbyFl((AdxStreamFile *)this->m_prev, (spC + sp8) / 2048);
        init_stream_position__6TLobbyFv((AdxStreamFile *)this->m_prev);
        TLobby::update_scroll_impl();
    }
}


void cvFsEntryErrFunc(CvFsErrorCallback callback, s32 context) {
    if (callback == NULL) {
        cvfs_completion_callback = NULL;
        lbl_805D75FC = 0;
        return;
    }
    cvfs_completion_callback = callback;
    lbl_805D75FC = context;
}
