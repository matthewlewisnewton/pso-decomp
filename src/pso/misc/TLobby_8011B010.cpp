#include "pso/protocol/ItemDropPacket.h"
#include "types.h"
#include "pso/misc/TLobby_801E43E4.h"
#include "pso/system/memory.h"
#include "pso/system/byteswap.h"
#include "pso/misc/TLobby.h"
#include "pso/item/TItemIdCounters.h"
#include "pso/unk/text_8011A780.h"

extern "C" {
void *mem_alloc(u32 size);
extern s32 item_sync_counter_table;
extern s32 item_id_counter_table;
extern s32 quest_object_entries;
void mem_free(void *p);

TItemIdCounters::~TItemIdCounters() {
    mem_free((void *)item_sync_counter_table);
    item_sync_counter_table = 0;
    mem_free((void *)item_id_counter_table);
    item_id_counter_table = 0;
}

TItemIdCounters::TItemIdCounters() {
    item_id_counter_table = (s32)mem_alloc(48);
    item_sync_counter_table = (s32)mem_alloc(48);
    TLobby::reset_item_id_counters();
    lbl_805D54E0 = 0;
    build_item_id_mode = 0;
}
void G_DropItem_PC_V3_BB_6x5F::send() {
    bswap_item_packet__6TLobbyFv(this);
    send_subcommand(reinterpret_cast<u8 *>(this));
}
void bswap_item_packet__6TLobbyFv(void *packet) {
    static_cast<G_ClientIDHeader *>(packet)->bswap();
    bswap_item__6TLobbyFv(static_cast<u8 *>(packet) + 4);
}
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
