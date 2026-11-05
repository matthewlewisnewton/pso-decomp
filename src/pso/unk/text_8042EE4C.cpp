#include "types.h"
#include "pso/network/ModemLaunchContext.h"
#include "pso/unk/text_8042EE4C.h"

extern "C" {
u32 exi_read_status_byte__6TLobbyFv();
s32 EXIGetType(int, int, void *);
extern u32 lbl_805D7CC8;

s32 TLobby__sub_8042EE4C(s32 *arg0) {
    s32 sp8;
    if ((u32) lbl_805D7CC8 == 2U) {
        *arg0 = 2;
        goto block_18;
    }
    if ((u32) lbl_805D7CC8 == 5U) {
        *arg0 = 5;
        goto block_18;
    }
    if (EXIGetType(0, 2, &sp8) != 0) {
        switch (sp8) {
        case -1:
            *arg0 = 0;
            break;
        case 33685504:
            *arg0 = 2;
            lbl_805D7CC8 = 2U;
            break;
        case 67240448:
            if (exi_read_status_byte__6TLobbyFv() == 0U) {
                *arg0 = 5;
                lbl_805D7CC8 = 5U;
            } else {
                *arg0 = 1;
            }
            break;
        default:
            *arg0 = 1;
            break;
        }
    } else {
        return -5;
    }
block_18:
    return 0;
}

s32 fn_8042EF48(s8 arg0) {
    if ((s32) lbl_805D7CA8 == 0) {
        return -1;
    }
    lbl_805D7CB8->field_00 = arg0;
    lbl_805D7CC0->flags |= 0x1000;
    return 0;
}
}

s32 set_modem_check_param_360(s8 arg0) {
    if ((s32) lbl_805D7CA8 == 0) {
        return -1;
    }
    lbl_805D7CC4->field_360 = arg0;
    lbl_805D7CC0->flags |= 0x800;
    return 0;
}

s32 set_modem_param(s16 arg0) {
    if ((s32) lbl_805D7CA8 == 0) {
        return -1;
    }
    lbl_805D7CC4->field_23e = arg0;
    lbl_805D7CC0->flags |= 0x800;
    return 0;
}

s32 set_modem_check_char(s8 arg0) {
    if ((s32) lbl_805D7CA8 == 0) {
        return -1;
    }
    lbl_805D7CC4->field_23d = arg0;
    lbl_805D7CC0->flags |= 0x800;
    return 0;
}

s32 set_modem_flag(s8 arg0) {
    if ((s32) lbl_805D7CA8 == 0) {
        return -1;
    }
    lbl_805D7CC4->field_23c = arg0;
    lbl_805D7CC0->flags |= 0x800;
    return 0;
}

s32 set_modem_check_param(s32 arg0) {
    if ((s32) lbl_805D7CA8 == 0) {
        return -1;
    }
    lbl_805D7CC4->field_0f4 = arg0;
    lbl_805D7CC0->flags |= 0x800;
    return 0;
}

s32 TAdTrialModemChkGC__sub_8042F080(s16 arg0) {
    lbl_805D7CC4->field_1c2 = arg0;
    lbl_805D7CC0->flags |= 0x800;
    return 0;
}

s32 set_modem_trial_param(s16 arg0) {
    if ((s32) lbl_805D7CA8 == 0) {
        return -1;
    }
    lbl_805D7CC4->field_1c0 = arg0;
    lbl_805D7CC0->flags |= 0x800;
    return 0;
}

s32 TAdTrialModemChkGC__sub_8042F0D4(s8 arg0) {
    if ((s32) lbl_805D7CA8 == 0) {
        return -1;
    }
    lbl_805D7CC4->field_13d = arg0;
    lbl_805D7CC0->flags |= 0x800;
    return 0;
}

s32 TAdPlayerLoadGC__sub_8042F108(s8 arg0) {
    if ((s32) lbl_805D7CA8 == 0) {
        return -1;
    }
    lbl_805D7CC4->field_13c = arg0;
    lbl_805D7CC0->flags |= 0x800;
    return 0;
}
