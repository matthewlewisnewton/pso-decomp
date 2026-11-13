#include "pso/network/protocol/subcmd_6x.h"
#include "pso/network/protocol/protocol_types.h"
#include "types.h"
#include "pso/system/ArrayAllocation.h"
#include "pso/unk/TLobby_801E43E4.h"
#include "pso/system/memory.h"
#include "pso/system/byteswap.h"
#include "pso/unk/TLobby.h"
#include "pso/item/TItemIdCounters.h"
#include "pso/unk/text_8011A780.h"


extern "C" {
extern s32 item_sync_counter_table;
extern s32 item_id_counter_table;
extern s32 quest_object_entries;

TItemIdCounters::~TItemIdCounters() {
    ::operator delete[]((void *)item_sync_counter_table);
    item_sync_counter_table = 0;
    ::operator delete[]((void *)item_id_counter_table);
    item_id_counter_table = 0;
}

TItemIdCounters::TItemIdCounters() {
    item_id_counter_table = (s32)::operator new[](48);
    item_sync_counter_table = (s32)::operator new[](48);
    TLobby::reset_item_id_counters();
    lbl_805D54E0 = 0;
    build_item_id_mode = 0;
}
void G_DropItem_PC_V3_BB_6x5F::send() { ((TLobby *)this)->bswap_item_packet(); send_subcommand((u8 *)this); }
void TLobby::bswap_item_packet() { ((G_ClientIDHeader *)this)->bswap(); ((TLobby *)((char*)this + 0x4))->bswap_item(); }
G_DropItem_PC_V3_BB_6x5F::G_DropItem_PC_V3_BB_6x5F() {
    __base_G_DropItem_DC_6x5F.header.subcommand = 0x5F;
    unused3[0] = 2;
    unused3[1] = 0;
    unused3[2] = 0;
    unused3[3] = 0;
    __base_G_DropItem_DC_6x5F.header.size = 0xB;
}
G_DropItem_DC_6x5F::G_DropItem_DC_6x5F() {
    header.subcommand = 0x5F;
    header.size = 0xA;
}
void TLobby::bswap_packet() { ((G_ClientIDHeader *)this)->bswap(); bswap_32((u32 *)((char*)this + 0x8)); bswap_32((u32 *)((char*)this + 0x4)); }
s32 TLobby::apply_table_entry(s16 arg0, void * _w1) {
    if (arg0 > 0xB9F) {
        return 0;
    }
    ((TLobby *)(quest_object_entries + (arg0 * 4)))->copy_short_fields(_w1);
    return 1;
}
void TLobby::copy_short_fields(void *arg1) {
    *(s16 *)&this->m_name = (s16) *(s16 *)((s8 *)arg1 + 0);
    *(u16 *)((s8 *)this + 2) = (u16) *(u16 *)((s8 *)arg1 + 2);
}

}
