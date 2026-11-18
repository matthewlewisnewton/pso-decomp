#ifndef PSO_PORT_SOCKET_QUEUE_H
#define PSO_PORT_SOCKET_QUEUE_H

#include "pso/network/TcpControlBlock.h"
#include "pso/network/TcpReceiveQueue.h"
#include "pso/protocol/NetworkRuntime.h"

extern "C" {
extern TcpState tcp_protocol_state;
void TLobby__sub_80406EB8(NetBufferRef *buffer, u32 bytes);
void TLobby__sub_80406FD8(void *dest, void *source, u32 bytes);
s32 set_thread_state_and_resume__6TLobbyFv(s32 handle, TcpOperationCallback callback, s16 status);
}

// These operations transfer one host-endian, 16-byte request to or from the socket ring.
// The backend owns the address space and interprets the descriptor's kind and value.
void read_socket_request(const NetBufferRef &source, TcpSendRequest &request);
void write_socket_request(const NetBufferRef &dest, const TcpSendRequest &request);

class TcpRequestBuffer {
public:
    void initialize() { request = 0; }
    void bind(TcpSendRequest &value) { request = &value; }
    void read(NetBufferRef &source) { read_socket_request(source, *request); }
    void write(NetBufferRef &dest) { write_socket_request(dest, *request); }
private:
    TcpSendRequest *request;
};

#endif
