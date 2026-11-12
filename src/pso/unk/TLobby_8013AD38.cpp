#include "types.h"
#include "pso/unk/TLobby_8013AD38.h"
#include "pso/ui/window/TWindowMenuIconLine.h"
#include "pso/unk/TLobby.h"
#include "pso/ui/city/TCheckRoomSequence.h"

struct RecoveredGlobal_8013ADB0_TAdEnterSerialAccessGC__data_804EC9B8 {
    s32 value;
    u8 remaining[0x8];
};

struct RecoveredGlobal_8013AD80_TAdEnterSerialAccessGC__data_804EC9C4 {
    s32 value;
    u8 remaining[0xC];
};

extern "C" {
extern u8 *text_language_group_table;
extern RecoveredGlobal_8013ADB0_TAdEnterSerialAccessGC__data_804EC9B8 TAdEnterSerialAccessGC__raw_serial_buffer;
extern RecoveredGlobal_8013AD80_TAdEnterSerialAccessGC__data_804EC9C4 TAdEnterSerialAccessGC__access_key_input_buffer;
int hex_to_decimal_string__22TAdEnterSerialAccessGCFi(void);

int TWindowMenuIconLine::is_decided() { return (this->state_flags >> 1) & 0x1; }
int TWindowMenuIconLine::is_cancelled() { return (this->state_flags >> 2) & 0x1; }
int test_flag_1d_bit1__15TWindowMakeTeamFv(void* p) { return (*(u8*)((char*)p + 0x1d) >> 1) & 0x1; }
s32 get_field_20__15TWindowMakeTeamFv(void* p) { return *(s32*)((char*)p + 0x20); }
u8 TLobby::get_mode() { return *(u8*)((char*)this + 0x1e); }
u8 read_mode__15TWindowMakeTeamFv(void* p) { return *(u8*)((char*)p + 0x1e); }
int test_flag_1d_bit0__15TWindowMakeTeamFv(void* p) { return *(u8*)((char*)p + 0x1d) & 0x1; }

typedef char RecoveredGlobal_8013AD80_TAdEnterSerialAccessGC__data_804EC9C4_size[sizeof(RecoveredGlobal_8013AD80_TAdEnterSerialAccessGC__data_804EC9C4) == 0x10 ? 1 : -1];
s32 *get_access_key_input_buffer(void) {
    return &TAdEnterSerialAccessGC__access_key_input_buffer.value;
}

void TLobby::init_serial_access() { get_raw_serial_input_buffer(); hex_to_decimal_string__22TAdEnterSerialAccessGCFi(); }

typedef char RecoveredGlobal_8013ADB0_TAdEnterSerialAccessGC__data_804EC9B8_size[sizeof(RecoveredGlobal_8013ADB0_TAdEnterSerialAccessGC__data_804EC9B8) == 0xC ? 1 : -1];
s32 *get_raw_serial_input_buffer(void) {
    return &TAdEnterSerialAccessGC__raw_serial_buffer.value;
}

s32 TAdDialingGC__sub_8013ADBC(s32 arg0) {
    return *(s32 *)((s8 *)(*(s32 *)((s8 *)text_language_group_table + 0x30)) + (arg0 * 4));
}

}
