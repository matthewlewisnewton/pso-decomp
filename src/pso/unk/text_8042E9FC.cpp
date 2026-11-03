#include "types.h"
#include "pso/network/ModemLaunchContext.h"
#include "pso/unk/text_8042EE4C.h"
#include "pso/ui/TAdTrialModemChkGC.h"

extern "C" {
int sprintf(char *, const char *, ...);
void *memset(void *, int, u32);
extern char lbl_80480270[];
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
