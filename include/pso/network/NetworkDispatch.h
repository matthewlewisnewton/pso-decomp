#ifndef PSO_NETWORK_NETWORK_DISPATCH_H
#define PSO_NETWORK_NETWORK_DISPATCH_H

#include "types.h"
#include "pso/network/NetworkTimer.h"
#include <stddef.h>

extern "C" {
void TLobby__sub_80419A00(void);
s32 TLobby__sub_80419A34(void);
s32 TLobby__sub_80419A7C(void);
s16 NetInitializeDispatcher(void);
}

struct NetProtocolHandlerEntry {
    s16 used;
    u16 type;
    void (*fn)(s32, s16, s16, s16);
};

struct NetTimerRecord {
    s16 active;
    s16 lock_callback;
    s32 period;
    u32 last;
    u32 next;
    NetTimerCallback fn;
};

struct NetworkDispatchState {
    s32 lock_handle;
    s32 queue_handle;
    u32 protocol_thread_handle;
    u32 timer_thread_handle;
    s32 interval;
    NetProtocolHandlerEntry handlers[3];
    NetTimerRecord timers[10];
    u8 unknown_F4[4];
};

struct NetProtocolMessage {
    s16 first;
    s16 second;
    u16 protocol;
    s16 detail;
    s32 payload;
};

#define NET_DISPATCH_OFFSET(type, member, value) \
    typedef char type##_##member##_offset[(offsetof(type, member) == value) ? 1 : -1]
NET_DISPATCH_OFFSET(NetProtocolHandlerEntry, used, 0x00);
NET_DISPATCH_OFFSET(NetProtocolHandlerEntry, type, 0x02);
NET_DISPATCH_OFFSET(NetProtocolHandlerEntry, fn, 0x04);
NET_DISPATCH_OFFSET(NetTimerRecord, active, 0x00);
NET_DISPATCH_OFFSET(NetTimerRecord, lock_callback, 0x02);
NET_DISPATCH_OFFSET(NetTimerRecord, period, 0x04);
NET_DISPATCH_OFFSET(NetTimerRecord, last, 0x08);
NET_DISPATCH_OFFSET(NetTimerRecord, next, 0x0C);
NET_DISPATCH_OFFSET(NetTimerRecord, fn, 0x10);
NET_DISPATCH_OFFSET(NetworkDispatchState, lock_handle, 0x00);
NET_DISPATCH_OFFSET(NetworkDispatchState, queue_handle, 0x04);
NET_DISPATCH_OFFSET(NetworkDispatchState, protocol_thread_handle, 0x08);
NET_DISPATCH_OFFSET(NetworkDispatchState, timer_thread_handle, 0x0C);
NET_DISPATCH_OFFSET(NetworkDispatchState, interval, 0x10);
NET_DISPATCH_OFFSET(NetworkDispatchState, handlers, 0x14);
NET_DISPATCH_OFFSET(NetworkDispatchState, timers, 0x2C);
NET_DISPATCH_OFFSET(NetworkDispatchState, unknown_F4, 0xF4);
NET_DISPATCH_OFFSET(NetProtocolMessage, first, 0x00);
NET_DISPATCH_OFFSET(NetProtocolMessage, second, 0x02);
NET_DISPATCH_OFFSET(NetProtocolMessage, protocol, 0x04);
NET_DISPATCH_OFFSET(NetProtocolMessage, detail, 0x06);
NET_DISPATCH_OFFSET(NetProtocolMessage, payload, 0x08);
#undef NET_DISPATCH_OFFSET

typedef char NetProtocolHandlerEntry_size[(sizeof(NetProtocolHandlerEntry) == 8) ? 1 : -1];
typedef char NetTimerRecord_size[(sizeof(NetTimerRecord) == 0x14) ? 1 : -1];
typedef char NetworkDispatchState_size[(sizeof(NetworkDispatchState) == 0xF8) ? 1 : -1];
typedef char NetProtocolMessage_size[(sizeof(NetProtocolMessage) == 0x0C) ? 1 : -1];

#endif
