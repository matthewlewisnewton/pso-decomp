#ifndef PSO_NETWORK_RECEIVE_CALLBACK_H
#define PSO_NETWORK_RECEIVE_CALLBACK_H
#include "types.h"

// The receive event supplies a protocol-specific byte record. The callback
// decodes that record; the native UDP runtime stores its address in one word.
typedef s32 (*NetworkReceiveCallback)(s16 event, u8 *record);
extern "C" {
s16 TUdpSocket__sub_80421DEC(void *src, s32 sport, void *dst, s32 dport,
                            s32 arg4, NetworkReceiveCallback callback);
s32 dhcp_handle_reply__6TLobbyFsPv(s16 event, u8 *record);
}
#endif
