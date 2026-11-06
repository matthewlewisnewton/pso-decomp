#include "types.h"
#include "pso/player/TObjPlayer.h"
#include "pso/misc/TLobby.h"

struct RecoveredGlobal_801BE388_lbl_8050EA40 {
    s32 value;
    u8 remaining[0x2C];
};

extern RecoveredGlobal_801BE388_lbl_8050EA40 lobby_rule_settings;

typedef char RecoveredGlobal_801BE388_lbl_8050EA40_size[sizeof(RecoveredGlobal_801BE388_lbl_8050EA40) == 0x30 ? 1 : -1];
s8 TObjPlayer::get_rule_field_0() {
    return ((TLobby *)(&lobby_rule_settings.value))->get_rule_field_0();
}
