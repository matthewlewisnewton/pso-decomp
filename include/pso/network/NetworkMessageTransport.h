#ifndef PSO_NETWORK_NETWORKMESSAGETRANSPORT_H
#define PSO_NETWORK_NETWORKMESSAGETRANSPORT_H

#include "types.h"

extern "C" {
void TLobby__sub_80425D88(u8 v);
s16 TLobby__sub_804262CC(void *argp);
s16 TLobby__sub_80426440(void);
s16 TLobby__sub_80426660(u8 *arg0);
s32 TLobby__sub_80426B88(s16 arg0);
s16 post_send_message(u8 *frame, u16 arg1);
void forward_to_channel(void *frame, void *b);
}
void dispatch_received_ethernet_frame(void *q, void *a, void *b);

#endif
