#include "types.h"
#include "pso/unk/TLobby.h"
#include "pso/ui/window/TWindowSubStatusDisp.h"
#include "pso/ui/window/TWindowBase.h"
#include "pso/ui/window/TUnk_804EF4E0.h"
#include "pso/system/task/TObject.h"
#include "pso/unk/WindowLayoutRecord.h"

struct O_80338D58 { u8 pad[0x72]; s16 idx; u8 pad2[2]; s16 count; };

extern "C" {
void *get_array_entry__11TWindowBaseFi(void *, s16);
s32 TWindowSubStatusDisp__sub_80338740(void *, void *, void *, void *, void *, void *, void *, void *, void *);

void fn_80338D58(O_80338D58 *arg0, void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8) {
    if (arg0->idx < arg0->count) {
        TWindowSubStatusDisp__sub_80338740(get_array_entry__11TWindowBaseFi(arg0, arg0->idx), a1, a2, a3, a4, a5, a6, a7, a8);
        arg0->idx += 1;
    }
}

}

// inferred: named after the class-name string it points to (TUnk_804EF4E0's m_name)
const char *TWindowMenuTeamStatus__name = "TWindowMenuTeamStatus";

void TUnk_804EF4E0::vfunc_6(u32 count, s32 id) {
    s32 i;
    TUnk_804EF4E0::Entry *entry;

    m_name = TWindowMenuTeamStatus__name;
    client_index = id;
    entry_count = 0;
    cursor = 0;
    entry_capacity = count;
    m_78 = 0;
    m_7c = 0;
    state_flags = 0;
    status_display = 0;
    unk_84 = 0;
    for (i = 0; i < (s32)count; i++) {
        entry = (TUnk_804EF4E0::Entry *)get_array_entry(i);
        entry->m_0c = i * 20;
    }
}

void *TLobby::create_object(void *heading) {
    return new TUnk_804EF4E0((s32)heading);
}

TUnk_804EF4E0::~TUnk_804EF4E0() {}

s32 lbl_804EF4C0[3] = {1, 0x40, 0xC};
WindowDescriptor lbl_804EF4CC = {
    {605.0f, 184.0f}, 50050.0f, lbl_804EF4C0, 3,
};

extern "C" u8 *get_window_layout_position(s32);

TUnk_804EF4E0::TUnk_804EF4E0(s32 heading)
    : TUnk_804D0948(get_window_layout_position(0xB0), heading, 0x40, (u8 *)&lbl_804EF4CC) {}
