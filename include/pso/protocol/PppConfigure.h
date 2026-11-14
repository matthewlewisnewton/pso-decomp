#ifndef PSO_PROTOCOL_PPP_CONFIGURE_H
#define PSO_PROTOCOL_PPP_CONFIGURE_H
#include "types.h"
#include <stddef.h>

// Shared prefix consumed by the IPCP, IPv6CP and LCP configure handlers.
// The option storage is protocol-specific and has different layouts.
struct PppConfigureContext {
    u8 unknown00;
    u8 request_id;
    u8 unknown02[4];
    u8 nak_retries;
    u8 unknown07[4];
    u8 accepted_configures;
    u8 unknown0C[0x24];
    void *options;
};

// Length consumed by configure handlers; retain its signed interpretation.
struct PppConfigureMessage {
    u8 code;
    u8 identifier;
    s16 option_bytes;
};

typedef char PppConfigureContextSize[sizeof(PppConfigureContext) == 0x34 ? 1 : -1];
typedef char PppConfigureOptionsOffset[offsetof(PppConfigureContext, options) == 0x30 ? 1 : -1];
typedef char PppConfigureNakRetriesOffset[offsetof(PppConfigureContext, nak_retries) == 6 ? 1 : -1];
typedef char PppConfigureAcceptedOffset[offsetof(PppConfigureContext, accepted_configures) == 0xB ? 1 : -1];
typedef char PppConfigureMessageSize[sizeof(PppConfigureMessage) == 4 ? 1 : -1];

inline s32 ppp_is_extended_configure_option(u8 type) {
    s32 result = 0;
    if (type >= 0x80 && type < 0x90) {
        result = 1;
    }
    return result;
}

// Preserve the existing mapping, including bit zero for unrecognized types.
inline s32 ppp_configure_option_bit(u8 type) {
    if (type < 8) {
        return type;
    }
    if (ppp_is_extended_configure_option(type)) {
        return type - 120;
    }
    return 0;
}
#endif
