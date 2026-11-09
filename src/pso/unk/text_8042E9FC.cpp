#include "types.h"
#include "pso/network/ModemLaunchContext.h"
#include "pso/unk/text_8042EE4C.h"
#include "pso/ui/TAdTrialModemChkGC.h"

extern "C" {
int sprintf(char *, const char *, ...);
void *memset(void *, int, u32);
extern char lbl_80480270[];

// 0x8042E9FC..0x8042EA10 is LaunchDol's dead frame restore
// (lmw r26, 8(r1); lwz r0, 0x24(r1); mtlr r0; addi r1, r1, 0x20; blr).
// LaunchDol's final jump starts at 0x8042E9EC; symbols.txt ends the
// function at 0x8042E9FC (start 0x8042E8C4, size 0x138).
// init_modem_check_params starts at 0x8042EA10, and
// skip_cfa_ranges covers the gap. A C function needs a prologue to emit
// this restore, so the bytes stay unmatched.
s32 TAdTrialModemChkGC::init_modem_check_params() {
    if ((s32) lbl_805D7CA8 == 0) {
        return -1;
    }
    memset(&lbl_805D7CC0->options, 0, 0x800);
    lbl_805D7CC0->options_size = 0x674;
    sprintf(lbl_805D7CC4->text, lbl_80480270);
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
    return 0;
}

}
