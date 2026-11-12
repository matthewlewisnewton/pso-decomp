#ifndef PSO_NETWORK_TCP_CONTROL_BLOCK_H
#define PSO_NETWORK_TCP_CONTROL_BLOCK_H

#include "types.h"
#include "pso/network/BufferRef.h"
#include "pso/network/IPv6Send.h"
#include <stddef.h>

typedef void (*TcpOperationCallback)(s16 status, s16 handle);
typedef void (*TcpSendCallback)(s16 status, s16 handle, s32 value);

struct TcpSendRequest {
    NetBufferRef buffer;
    s16 length;
    s16 offset;
    TcpSendCallback callback;
};

struct TcpReassemblyRange {
    u32 start;
    u32 end;
};

struct TcpSackRange {
    u32 start;
    u32 end;
};

// The allocation stride is 0x544. Unknown spans retain their verified offsets;
// this record describes the TCP buffer interface, not the original C++ class.
struct TcpControlBlock {
    u8 signature[3];
    u8 index;
    u16 active;
    s16 state;
    s16 listener;
    u8 unknown_0a;
    u8 flags;
    u8 unknown_0c[4];
    NetBufferRef send_buffer;
    NetBufferRef send_allocation;
    u32 send_count;
    u32 send_read;
    u32 send_write;
    NetPacket send_request;
    NetBufferRef receive_buffer;
    NetBufferRef receive_allocation;
    u32 received;
    u32 receive_read;
    u32 receive_write;
    NetBufferRef read_buffer;
    u32 read_length;
    s32 read_done;
    s32 reassembly_bytes;
    s16 reassembly_last;
    s16 reassembly_recent;
    TcpReassemblyRange reassembly[32];
    TcpOperationCallback write_callback;
    TcpOperationCallback read_callback;
    u8 queued_send : 1;
    u8 read_closed : 1;
    u8 other_io_flags : 6;
    u8 unknown_205[0x23];
    u32 receive_sequence;
    u8 unknown_22c[0xA4];
    s32 event_callback;
    u8 unknown_2d4[0x24];
    // Five active ranges and the lookahead slot read by 0x8041FED4.
    TcpSackRange sack[6];
    u8 unknown_328[0x208];
    u32 send_capacity;
    u32 receive_capacity;
    u32 unknown_538;
    u32 unknown_53c;
    u32 unknown_540;
};

typedef char TcpSendRequest_size_check[sizeof(TcpSendRequest) == 16 ? 1 : -1];
typedef char TcpControlBlock_size_check[sizeof(TcpControlBlock) == 0x544 ? 1 : -1];
typedef char TcpControlBlock_send_request_check[offsetof(TcpControlBlock, send_request) == 0x2C ? 1 : -1];
typedef char TcpControlBlock_receive_buffer_check[offsetof(TcpControlBlock, receive_buffer) == 0xC8 ? 1 : -1];
typedef char TcpControlBlock_reassembly_check[offsetof(TcpControlBlock, reassembly) == 0xFC ? 1 : -1];
typedef char TcpControlBlock_io_byte_check[offsetof(TcpControlBlock, unknown_205) == 0x205 ? 1 : -1];
typedef char TcpControlBlock_receive_sequence_check[offsetof(TcpControlBlock, receive_sequence) == 0x228 ? 1 : -1];
typedef char TcpControlBlock_sack_check[offsetof(TcpControlBlock, sack) == 0x2F8 ? 1 : -1];

extern "C" {
s32 TLobby__sub_8041FFF8(u32 acknowledged, TcpControlBlock *control);
s32 complete_request_callback__6TLobbyFv(s16 handle, TcpSendCallback callback,
                                         s16 status, const TcpSendRequest *request);
}

#endif
