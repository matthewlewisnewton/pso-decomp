#ifndef PSO_NETWORK_RECEIVE_CALLBACK_H
#define PSO_NETWORK_RECEIVE_CALLBACK_H
#include "types.h"
#include <stddef.h>

// Common prefix of the raw IPv4, raw IPv6 and UDP receive event records.
// Protocol-specific addresses and (for UDP) the port follow this prefix.
struct NetworkReceivePrefix {
    s16 flags;
    s16 length;
    u8 *buffer;
};
typedef char NetworkReceivePrefix_flags_offset[offsetof(NetworkReceivePrefix, flags) == 0 ? 1 : -1];
typedef char NetworkReceivePrefix_length_offset[offsetof(NetworkReceivePrefix, length) == 2 ? 1 : -1];
typedef char NetworkReceivePrefix_buffer_offset[offsetof(NetworkReceivePrefix, buffer) == 4 ? 1 : -1];
typedef char NetworkReceivePrefix_size[sizeof(NetworkReceivePrefix) == 8 ? 1 : -1];

// The receive event supplies a protocol-specific byte record. The callback
// decodes that record; the native UDP runtime stores its address in one word.
typedef s32 (*NetworkReceiveCallback)(s16 event, u8 *record);
extern "C" {
s16 TUdpSocket__sub_80421DEC(void *src, s32 sport, void *dst, s32 dport,
                            s32 arg4, NetworkReceiveCallback callback);
s32 dhcp_handle_reply__6TLobbyFsPv(s16 event, u8 *record);
}
#endif
