#include "pso/protocol/protocol_types.h"
#include "types.h"
#include "pso/misc/TLobby_801E43E4.h"
#include "pso/system/byteswap.h"
#include "pso/misc/TOMineIcon01.h"
#include "pso/misc/TOMine.h"
#include "pso/misc/TOMineTrap.h"
#include "pso/player/TObjPlayer.h"

extern "C" {
extern f32 lbl_805D307C;
void TOMineTrap__sub_80171368(f32 farg0);
s16 TOMineTrap__sub_80171340(void* p);
int TOMineTrap__sub_80171350(void);
u16 TOMineTrap__sub_80171358(void* p);
void TOMineTrap__sub_8017141C(void* p);

s32 fn_80171314(TObjPlayer *player) { return player->check_flag(0x10000); }
u16 TOMineTrap::get_trap_type() { return this->m_2d8; }
s16 TOMineTrap__sub_80171340(void* p) { return *(s16*)((char*)p + 0x326); }
void TOMineTrap::sub_80171348(u16 v) { this->m_2d8 = v; }

    extern int mine_trap_instance_id;
int TOMineTrap__sub_80171350(void) {  return mine_trap_instance_id; }

u16 TOMineTrap__sub_80171358(void* p) { return *(u16*)((char*)p + 0x37e); }

    extern int mine_trap_count;
int TOMineTrap::get_trap_count() {  return mine_trap_count; }

void TOMineTrap__sub_80171368(f32 farg0) {
    lbl_805D307C = farg0;
}

void TOMineTrap::set_instance(int a0) { mine_trap_instance_id = a0; }

void TOMineTrap::set_trap_count(int a0) { mine_trap_count = a0; }

void TOMine::vfunc_84() {  }

s32 TOMineTrap::select_melee_contact_body(void *attacker, f32) {
    return attacker != target ? 1 : 0;
}

int TOMineTrap::calc_distance_accuracy_penalty(void *attacker, void *, void *, f32) {
    return attacker != target ? 1 : 0;
}

void TOMineTrap::bswap_6x80_trigger_trap() { ((G_ClientIDHeader *)this)->bswap(); bswap_16((u16 *)((char*)this + 0x4)); bswap_16((u16 *)((char*)this + 0x6)); }
void TOMineTrap::send_and_handle_60() { bswap_6x80_trigger_trap(); send_subcommand((u8 *)this); }

void TOMineTrap__sub_8017141C(void* p) { *(u8*)((char*)p + 0x0) = 128; *(u8*)((char*)p + 0x1) = 2; }

void TOMineIcon01::vfunc_84() {  }

}
