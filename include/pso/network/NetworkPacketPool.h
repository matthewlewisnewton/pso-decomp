#ifndef PSO_NETWORK_NETWORK_PACKET_POOL_H
#define PSO_NETWORK_NETWORK_PACKET_POOL_H
#include "types.h"

enum { NETWORK_PACKET_BUFFER_COUNT = 32, NETWORK_PACKET_BUFFER_BYTES = 0x600 };
struct NetworkPacketBufferDescriptor {
    s32 in_use;
    s32 queued_length;
    u8 *data;
};
extern "C" {
NetworkPacketBufferDescriptor *TLobby__sub_804256B8(u32 address);
}
s16 initialize_network_packet_pool(void);
extern NetworkPacketBufferDescriptor network_packet_buffer_descriptors[NETWORK_PACKET_BUFFER_COUNT];
extern u8 network_packet_buffers[NETWORK_PACKET_BUFFER_COUNT][NETWORK_PACKET_BUFFER_BYTES];
#endif
