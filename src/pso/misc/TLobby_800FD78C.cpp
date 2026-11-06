#include "types.h"
#include "pso/misc/TLobby_800FD78C.h"
#include "pso/misc/TLobby.h"

extern "C" {

int TCameraCtrl__sub_8006B370(f32 farg0);

void TLobby::init_range(s32 flags) {
    s32 temp_r5;

    *(s32 *)&this->m_flags = flags;
    temp_r5 = flags + 1;
    *(s32 *)&this->m_prev = temp_r5;
    *(s32 *)&this->m_next = temp_r5;
    *(s32 *)&this->m_up = 0;
    *(s32 *)&this->m_down = 0;
    *(s32 *)((s8 *)this + 0x18) = 0;
    *(s32 *)&this->m_name = -1;
    *(s32 *)((s8 *)this + 0x1C) = 0;
    *(s32 *)((s8 *)this + 0x20) = 0;
}

u8 fn_800FD7C0(void *arg0) {
    int var_r31;

    var_r31 = 0;
    if ((TCameraCtrl__sub_8006B370(*(f32 *)((s8 *)arg0 + 0)) != 0) || (TCameraCtrl__sub_8006B370(*(f32 *)((s8 *)arg0 + 4)) != 0)) {
        var_r31 = 1;
    }
    return (u8)var_r31;
}

}
