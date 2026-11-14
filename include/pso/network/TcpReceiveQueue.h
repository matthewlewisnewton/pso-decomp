#ifndef PSO_NETWORK_TCPRECEIVEQUEUE_H
#define PSO_NETWORK_TCPRECEIVEQUEUE_H

#include "pso/network/TcpProtocolState.h"

extern "C" {
s32 TLobby__sub_8041F914(NetPacket *pkt, u16 offset, TcpTcb *tcb, TcpHdr *header);
void TLobby__sub_8041FDA0(TcpTcb *tcb, s16 index, s32 start, s32 end);
void TLobby__sub_8041FED4(TcpTcb *tcb);
}

#endif
