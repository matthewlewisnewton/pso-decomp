#ifndef PSO_NETWORK_TCP_SEND_QUEUE_H
#define PSO_NETWORK_TCP_SEND_QUEUE_H

#include "pso/network/TcpProtocolState.h"

typedef void (*TcpSendCompletion)(s16 status, s16 handle);
typedef void (*TcpSendCallback)(s16 status, s16 handle, s32 value);

struct TcpSendRequest {
    NetBufferRef buffer;
    s16 length;
    s16 offset;
    TcpSendCallback callback;
};

typedef char TcpSendRequest_size_check[sizeof(TcpSendRequest) == 16 ? 1 : -1];

extern "C" {
s32 set_thread_state_and_resume__6TLobbyFv(s32 handle, TcpSendCompletion callback, s16 status);
s32 TLobby__sub_8041FFF8(u32 acknowledged, TcpTcb *control);
s32 TLobby__sub_80420410(u32 offset, u32 length, NetPacket *packet, TcpTcb *control);
s32 complete_request_callback__6TLobbyFv(s16 handle, TcpSendCallback callback,
                                         s16 status, const TcpSendRequest *request);
}

#endif
