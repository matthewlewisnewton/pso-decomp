#ifndef PSO_NETWORK_SOCKET_EVENTS_H
#define PSO_NETWORK_SOCKET_EVENTS_H

#include "types.h"

extern "C" void NetDispatchSocketEvent(s16 handle, s32 callback, s32 protocol, s16 event);

// Legacy native export for the TCP accept notification.
extern "C" s32 TLobby__sub_80422AB8(s16 listener_index,
    void (*callback)(s16, s16, s32, s32),
    s16 accepted_index, s32 address, s32 local_port, s32 remote_port);

#endif
