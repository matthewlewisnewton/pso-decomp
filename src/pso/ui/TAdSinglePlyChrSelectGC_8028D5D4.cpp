#include "types.h"
#include "pso/ui/TAdSinglePlyChrSelectGC_8028D5D4.h"

s32 is_selection_done__23TAdSinglePlyChrSelectGCFPv(void *arg0) {
    return (u8) (*(s32 *)((s8 *)arg0 + 0x2C) == 2);
}

#include "pso/misc/TLobby.h"
#include "pso/misc/CharacterLoadBuffer.h"
#include "pso/misc/TLobby_8028D714.h"
#include "pso/misc/TQuestVmDownLoadServer.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

extern "C" {
u32 lbl_80518850[4];
u32 chr_select_load_buffer_table[8];
s32 TAdSinglePlyChrSelectGC::get_result() {
    if (is_selection_done__23TAdSinglePlyChrSelectGCFPv(this) != 0) {
        return this->m_28;
    }
    return 0;
}
u32 advance_character_load_buffer(s32 slot, s32 size) {
    u32 p;
    if (chr_select_load_buffer_base == 0U) {
        return 0U;
    }
    TLobby__sub_8028D7D0(slot);
    if ((size < 0) || (size > 0xA000)) {
        return 0U;
    }
    size = (size + 0x1F) & ~0x1F;
    if (slot < 4) {
        p = lbl_80518850[slot];
        p += size;
        if (p >= chr_select_load_buffer_base + (slot + 1) * 0xA000) {
            return 0U;
        }
        lbl_80518850[slot] = p;
        return p;
    }
    {
        s32 j = slot - 4;
        p = chr_select_load_buffer_table[j];
        p += size;
        if (p >= chr_select_load_buffer + (j + 1) * 0xA000) {
            return 0U;
        }
        chr_select_load_buffer_table[j] = p;
    }
    return p;
}

}

void *get_character_load_buffer(s32 slot) { return (void *)advance_character_load_buffer(slot, 0); }

u32 TLobby__sub_8028D738(s32 slot) {
    u32 address;
    s32 extended_slot;
    if (chr_select_load_buffer_base == 0U) {
        return 0U;
    }
    TLobby__sub_8028D7D0(slot);
    if (slot < 4) {
        address = chr_select_load_buffer_base + (u32)slot * 0xA000U;
        lbl_80518850[slot] = address;
        return address;
    }
    extended_slot = slot - 4;
    address = chr_select_load_buffer + (u32)extended_slot * 0xA000U;
    chr_select_load_buffer_table[extended_slot] = address;
    return address;
}

void TLobby__sub_8028D7D0(s32 i) {
    s32 n = 4;
    if (chr_select_load_buffer_base == 0) return;
    if (chr_select_load_buffer != 0) n = 12;
    if (i < 0) return;
    if (i >= n) return;
}

void TLobby::free_single_player_chr_select() {
    if (((u32) chr_select_load_buffer_base != 0U) && ((u32) chr_select_load_buffer != 0U)) {
        TAdSinglePlyChrSelectGC::safe_free((void *)chr_select_load_buffer);
        chr_select_load_buffer = 0U;
    }
}

void TLobby::alloc_download_server() {
    if (((u32) chr_select_load_buffer_base != 0U) && ((u32) chr_select_load_buffer == 0U)) {
        chr_select_load_buffer = (u32)TQuestVmDownLoadServer::alloc(0x50000);
        if ((u32) chr_select_load_buffer == 0U) {
            return;
        }
    }
}

void TLobby::free_chr_select_singleton() {
    if ((u32) chr_select_load_buffer_base != 0U) {
        TAdSinglePlyChrSelectGC::safe_free((void *)chr_select_load_buffer_base);
        chr_select_load_buffer_base = 0U;
    }
}
