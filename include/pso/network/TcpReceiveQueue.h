#ifndef PSO_NETWORK_TCPRECEIVEQUEUE_H
#define PSO_NETWORK_TCPRECEIVEQUEUE_H

#include "pso/network/TcpProtocolState.h"

typedef void (*TcpReceiveCallback)(s16 status, s16 handle);

extern "C" {
s32 set_slot_state_and_resume__6TLobbyFv(s16 handle, TcpReceiveCallback callback, s16 status);
s32 TLobby__sub_8041ED8C(TcpTcb *control, NetBufferRef *destination, u32 length, TcpReceiveCallback callback);
s32 TLobby__sub_8041F11C(TcpTcb *control);
s32 TLobby__sub_8041F204(NetPacket *packet, u16 skip, TcpTcb *control);
s32 TLobby__sub_8041F914(NetPacket *pkt, u16 offset, TcpTcb *tcb, TcpHdr *header);
void TLobby__sub_8041FDA0(TcpTcb *tcb, s16 index, s32 start, s32 end);
void TLobby__sub_8041FED4(TcpTcb *tcb);
}

#endif
