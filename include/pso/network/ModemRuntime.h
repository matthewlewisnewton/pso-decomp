#ifndef PSO_NETWORK_MODEMRUNTIME_H
#define PSO_NETWORK_MODEMRUNTIME_H

#include "types.h"
#include "dolphin/os/OSContext.h"

extern "C" {
s32 TAdSinglePlyChrSelectGC__sub_8042DD70(s32 arg0, s32 arg1, s32 arg2);
void TAdSinglePlyChrSelectGC__sub_8042DDE4(s32 channel, OSContext *context);
void TAdSinglePlyChrSelectGC__sub_8042D6A4(char *command);
s32 TAdSinglePlyChrSelectGC__sub_8042CD64(void);
s32 TAdSinglePlyChrSelectGC__sub_8042D49C(char *command);
s32 TAdSinglePlyChrSelectGC__sub_8042E320(const char *number, s32 mode, void (*callback)(s32 result));
void TAdSinglePlyChrSelectGC__sub_8042E488(s32 value);
// Reserved launch-context address; converted to its record view by the caller.
u32 fn_8042E8B8(void);
}

#endif
