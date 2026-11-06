#include "types.h"
#include "pso/unk/text_8023F160.h"

struct RecoveredGlobal_8023F160_lbl_804CCE60 {
    s32 value;
    u8 remaining[0x34];
};

struct RecoveredGlobal_8023F18C_lbl_804CCE60 {
    s32 value;
    u8 remaining[0x34];
};

extern "C" {
void call_funcs_reverse__6TLobbyFPvUi(s32, u32);
extern RecoveredGlobal_8023F160_lbl_804CCE60 lobby_scene_release_callback_table;
s32 run_load_callback_table(void *, int);
typedef char RecoveredGlobal_8023F160_lbl_804CCE60_size[sizeof(RecoveredGlobal_8023F160_lbl_804CCE60) == 0x38 ? 1 : -1];
void fn_8023F160(void) {
    call_funcs_reverse__6TLobbyFPvUi((s32) &lobby_scene_release_callback_table.value, 0x38U);
}
typedef char RecoveredGlobal_8023F18C_lbl_804CCE60_size[sizeof(RecoveredGlobal_8023F18C_lbl_804CCE60) == 0x38 ? 1 : -1];
void fn_8023F18C(void) {
    run_load_callback_table((void *) (&(*(RecoveredGlobal_8023F18C_lbl_804CCE60 *)&lobby_scene_release_callback_table).value), 0x38);
}

}
