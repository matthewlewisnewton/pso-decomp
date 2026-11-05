#include "pso/unk/text_8042EAD4.h"
#include "pso/unk/text_8042EE4C.h"
#include "pso/network/ModemLaunchContext.h"
#include "pso/network/ModemRuntime.h"

extern "C" {
char *strcpy(char *, const char *);
char *strncpy(char *, const char *, unsigned long);
void *memset(void *, int, unsigned long);
unsigned long strlen(const char *);
int sprintf(char *, const char *, ...);
void LaunchDol(ModemLaunchContext *);
extern const char lbl_80480404[];
// Address anchor into adjacent pooled literals; see modem-launch-recovery-evidence.md.
extern const char lbl_80480240[];
extern const u32 lbl_805E11F0;
}

#pragma push
#pragma optimize_for_size off
s32 fn_8042EAD4(u8 *arg0, u32 arg1) {
    u8 *dst;
    u32 i;
    if ((s32) lbl_805D7CA8 == 0) {
        return -1;
    }
    if (arg1 > 0x800U) {
        return -2;
    }
    dst = lbl_805D7CC0->arguments;
    for (i = arg1; i != 0; i--) {
        *dst++ = *arg0++;
    }
    lbl_805D7CC0->argument_size = arg1;
    lbl_805D7CC0->flags |= 1;
    return 0;
}
#pragma pop

#pragma push
#pragma optimize_for_size off
void fn_8042EBA4(s32 arg0, s32 arg1) {
    strcpy(lbl_805D7CB0->path, lbl_80480404);
    lbl_805D7CB0->field_100 = arg1;
    lbl_805D7CB0->field_104 = reinterpret_cast<DolImageHeader *>(arg0);
    lbl_805D7CB0->payload_size = 0x8000;
    LaunchDol(lbl_805D7CB0);
}
#pragma pop

#pragma push
#pragma optimize_for_size off
extern "C" void TAdTrialModemChkGC__sub_8042EC14(void) {
    const char *strings = lbl_80480240;
    lbl_805D7CB4 = lbl_805E11F0;
    if (lbl_805D7CA8 == 0) {
        lbl_805D7CB0 = reinterpret_cast<ModemLaunchContext *>(fn_8042E8B8());
        lbl_805D7CA8 = 1;
        lbl_805D7CC0 = reinterpret_cast<ModemLaunchData *>(lbl_805D7CB0->data);
        lbl_805D7CC4 = &lbl_805D7CC0->options;
        lbl_805D7CBC = lbl_805D7CC0->region_6820;
        lbl_805D7CB8 = &lbl_805D7CC0->parameters;
        if (lbl_805D7CC0->signature != 0x53454741) {
            memset(lbl_805D7CC0, 0, 0x8000);
            lbl_805D7CC0->signature = 0x53454741;
            lbl_805D7CC0->flags = 0x40;
            if (lbl_805D7CA8 != 0) {
                memset(&lbl_805D7CC0->options, 0, 0x800);
                lbl_805D7CC0->options_size = 0x674;
                sprintf(lbl_805D7CC4->text, strings + 0x30);
                TAdPlayerLoadGC__sub_8042F108(0);
                TAdTrialModemChkGC__sub_8042F0D4(3);
                set_modem_trial_param(1);
                TAdTrialModemChkGC__sub_8042F080(3);
                set_modem_check_param(3);
                set_modem_flag(1);
                set_modem_check_char(1);
                set_modem_param(5);
                set_modem_check_param_360(0);
                lbl_805D7CC0->flags &= ~0x800U;
            }
            fn_8042ED98(0, strings + 0x1D0);
            fn_8042ED98(1, strings + 0x220);
            fn_8042ED98(2, strings + 0x25C);
            fn_8042ED98(3, strings + 0x2E0);
            fn_8042ED98(4, strings + 0x324);
        }
    }
}
#pragma pop

#pragma push
#pragma optimize_for_size off
s32 fn_8042ED98(int arg0, const char *arg1) {
    s32 ret = 0;
    if (lbl_805D7CA8 == 0) {
        return -1;
    }
    if (arg0 < 0 || arg0 > 4) {
        return -2;
    }
    memset(lbl_805D7CB8->name[arg0], 0, 0x100);
    strncpy(lbl_805D7CB8->name[arg0], arg1, 0xFF);
    if (strlen(arg1) >= 0x100) {
        ret = -2;
    }
    return ret;
}
#pragma pop
