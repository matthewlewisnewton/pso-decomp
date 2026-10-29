#include "types.h"
#include "pso/unk/text_80191D14.h"

struct RecoveredGlobal_80191D14_lbl_8050DCB8 {
    s32 value;
    u8 remaining[0x2C];
};

extern "C" {
RecoveredGlobal_80191D14_lbl_8050DCB8 handle_6x78_entry_table;
}


struct RecoveredGlobal_80191D5C_lbl_8050DCB8 {
    s32 value;
    u8 remaining[0x2C];
};

struct RecoveredGlobal_80191D34_lbl_8050DCB8 {
    s32 value;
    u8 remaining[0x2C];
};

extern RecoveredGlobal_80191D14_lbl_8050DCB8 handle_6x78_entry_table;
typedef char RecoveredGlobal_80191D14_lbl_8050DCB8_size[sizeof(RecoveredGlobal_80191D14_lbl_8050DCB8) == 0x30 ? 1 : -1];

void fn_80191D14(u16 arg0, s32 arg1) {
    if (arg0 < 0xCU) {
        *(s32 *)((s8 *)&handle_6x78_entry_table.value + ((arg0 * 4) & 0x3FFFC)) = arg1;
    }
}
typedef char RecoveredGlobal_80191D5C_lbl_8050DCB8_size[sizeof(RecoveredGlobal_80191D5C_lbl_8050DCB8) == 0x30 ? 1 : -1];

typedef char RecoveredGlobal_80191D34_lbl_8050DCB8_size[sizeof(RecoveredGlobal_80191D34_lbl_8050DCB8) == 0x30 ? 1 : -1];
s32 get_handle_6x78_entry(u16 arg0) {
    if (arg0 >= 0xCU) {
        return 0;
    }
    return *(s32 *)((s8 *)(&(*(RecoveredGlobal_80191D34_lbl_8050DCB8 *)&handle_6x78_entry_table).value) + ((arg0 * 4) & 0x3FFFC));
}

void fn_80191D5C(u16 arg0) {
    if (arg0 < 0xCU) {
        *(s32 *)((s8 *)(&(*(RecoveredGlobal_80191D5C_lbl_8050DCB8 *)&handle_6x78_entry_table).value) + ((arg0 * 4) & 0x3FFFC)) = 0x12C;
    }
}
