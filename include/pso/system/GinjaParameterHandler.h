#ifndef PSO_SYSTEM_GINJAPARAMETERHANDLER_H
#define PSO_SYSTEM_GINJAPARAMETERHANDLER_H

#include "types.h"

// Native dispatch passes a value and its changed-bit mask in r3/r4. Only
// the channel-count handler consumes the second word. Ports use an erased
// storage type and restore the actual signature before making the call.
#ifdef __MWERKS__
typedef void (*GinjaParameterHandler)(u32 value, u32 changed);
#else
typedef void (*GinjaParameterHandler)();
#endif

#ifndef __MWERKS__
// Restore each entry's declared type before invoking it on other platforms.
inline void invoke_ginja_parameter_handler(GinjaParameterHandler handler,
                                           u8 kind, u32 value, u32 changed) {
    if (kind == 2) {
        reinterpret_cast<void (*)(s32, s32)>(handler)(value, changed);
    } else if (kind == 1) {
        reinterpret_cast<void (*)(s32)>(handler)(value);
    } else {
        reinterpret_cast<void (*)(u32)>(handler)(value);
    }
}
#endif

#endif
