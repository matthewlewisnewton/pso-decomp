#include "pso/network/NetworkDispatch.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TUdpSocket.h"
#include "pso/protocol/NetworkRuntime.h"

extern "C" {
typedef void (*Handler_8041A130)(s32, s16, s16, s16);
s32 TLobby__sub_803F8E9C();
void TLobby__sub_803F97E8(int);
void TLobby__sub_803F9344(s32, void *, s32);

NetworkDispatchState network_dispatch_state;

void TLobby__sub_80419A00(void) {
    NetMemset(&network_dispatch_state.lock_handle, 0, offsetof(NetworkDispatchState, unknown_F4));
    TLobby::cancel_pending_alarms();
}

s32 TLobby__sub_80419A34(void) {
    NetMemset(&network_dispatch_state.lock_handle, 0, offsetof(NetworkDispatchState, unknown_F4));
    network_dispatch_state.interval = 0x1E;
    return TLobby__sub_803F8E9C();
}

#pragma push
#pragma opt_common_subs on
s32 TLobby__sub_80419A7C(void) {
    TLobby::lock_mutex(network_dispatch_state.lock_handle);
    ((TLobby *)network_dispatch_state.timer_thread_handle)->cancel_thread_if_running();
    ((TLobby *)network_dispatch_state.protocol_thread_handle)->cancel_thread_if_running();
    TLobby::deactivate_entry_by_key(network_dispatch_state.timer_thread_handle);
    TLobby::deactivate_entry_by_key(network_dispatch_state.protocol_thread_handle);
    TLobby::clear_slot_for_handle(network_dispatch_state.queue_handle);
    TUdpSocket::unlock_mutex(network_dispatch_state.lock_handle);
    NetReleaseMutex(network_dispatch_state.lock_handle);
    return 0;
}
#pragma pop

s16 TLobby__sub_803F94F0(s32 *queue);
s16 TLobby__sub_803F96AC(s32 *lock);
s16 TLobby__sub_803F9B94(void (*fn)(void), u32 *thread);
void NetRunProtocolDispatchLoop(void);
void NetRunTimerDispatchLoop(void);

s16 NetInitializeDispatcher(void) {
    s32 *queue;
    u32 *proto_thread;
    u32 *timer_thread;

    queue = &network_dispatch_state.queue_handle;
    if (TLobby__sub_803F94F0(queue) < 0) {
        return -0x100;
    }
    if (TLobby__sub_803F96AC(&network_dispatch_state.lock_handle) < 0) {
        TLobby::clear_slot_for_handle(*queue);
        return -0x100;
    }
    proto_thread = &network_dispatch_state.protocol_thread_handle;
    if (TLobby__sub_803F9B94(NetRunProtocolDispatchLoop, proto_thread) < 0) {
        TLobby::clear_slot_for_handle(*queue);
        NetReleaseMutex(network_dispatch_state.lock_handle);
        return -0x100;
    }
    timer_thread = &network_dispatch_state.timer_thread_handle;
    if (TLobby__sub_803F9B94(NetRunTimerDispatchLoop, timer_thread) < 0) {
        TLobby::deactivate_entry_by_key(*proto_thread);
        TLobby::clear_slot_for_handle(*queue);
        NetReleaseMutex(network_dispatch_state.lock_handle);
        return -0x100;
    }
    NetResumeThread(*proto_thread);
    NetResumeThread(*timer_thread);
    return 0;
}

void NetYieldOutsideDispatcherThread(void) {
    NetworkDispatchState *g = &network_dispatch_state;
    s32 self;

    NetStoreCurrentThread(&self);
    if (self != g->protocol_thread_handle && self != g->timer_thread_handle) {
        TUdpSocket::unlock_mutex(g->lock_handle);
        NetYieldThread();
        TLobby::lock_mutex(g->lock_handle);
    }
}

#pragma push
#pragma opt_common_subs on
#pragma pool_data off
void NetRunTimerDispatchLoop(void) {
    NetworkDispatchState *g = &network_dispatch_state;
    s32 now;
    s16 i;
    s16 j;
    s16 due;
    u32 next;

    for (;;) {
        TLobby__sub_803F97E8(network_dispatch_state.interval);
        for (i = 0; i < 10; i++) {
            if (g->timers[i].active == 0 || g->timers[i].fn == NULL) {
                continue;
            }
            TLobby::get_time_ms(&now);
            due = 0;
            if (g->timers[i].last < g->timers[i].next) {
                if (g->timers[i].next <= now || now < g->timers[i].last) {
                    due = 1;
                }
            } else if (g->timers[i].next <= now && now < g->timers[i].last) {
                due = 1;
            }
            if (due == 0) {
                continue;
            }
            if (g->timers[i].lock_callback != 0) {
                TLobby::lock_mutex(network_dispatch_state.lock_handle);
            }
            g->timers[i].fn();
            if (g->timers[i].lock_callback != 0) {
                TUdpSocket::unlock_mutex(network_dispatch_state.lock_handle);
            }
            next = now + g->timers[i].period;
            if (g->timers[i].period > network_dispatch_state.interval) {
                for (j = 0; j < 10; j++) {
                    if (i != j && g->timers[j].active != 0 && g->timers[j].next == next &&
                        g->timers[j].period > network_dispatch_state.interval) {
                        next += network_dispatch_state.interval;
                    }
                }
            }
            g->timers[i].last = now;
            g->timers[i].next = next;
        }
    }
}
#pragma pop

s32 NetUnregisterTimer(NetTimerCallback fn) {
    NetworkDispatchState *g = &network_dispatch_state;
    s16 i;

    if (fn == NULL) {
        return -0x100;
    }
    for (i = 0; i < 10; i++) {
        if (network_dispatch_state.timers[i].active != 0 && network_dispatch_state.timers[i].fn == fn) {
            g->timers[i].active = 0;
            g->timers[i].fn = NULL;
            g->timers[i].lock_callback = 0;
            g->timers[i].period = 0;
            g->timers[i].last = 0;
            g->timers[i].next = 0;
            return 0;
        }
    }
    return -0x100;
}

#pragma push
#pragma opt_common_subs on
s32 NetRegisterTimer(s32 period, s16 locked, NetTimerCallback fn) {
    u32 now;
    s32 *pint;
    s16 slot;
    s16 i;
    u32 cur;
    s32 iv;
    s16 j;
    u32 nxt;
    if (fn == NULL) {
        return -0x100;
    }
    pint = &network_dispatch_state.interval;
    if (period < network_dispatch_state.interval) {
        period = network_dispatch_state.interval;
    }
    slot = -1;
    i = 0;
    while (i < 10) {
        if (network_dispatch_state.timers[i].active != 0) {
            if (network_dispatch_state.timers[i].fn == fn) {
                return -0x100;
            }
        } else if (slot < 0) {
            slot = i;
        }
        i++;
    }
    if (slot < 0 || slot >= 10) {
        return -0x100;
    }
    TLobby::get_time_ms((s32 *)&now);
    iv = *pint;
    cur = now;
    nxt = cur + period;
    if (period > iv) {
        j = 0;
        while (j < 10) {
            if (network_dispatch_state.timers[j].active != 0 && network_dispatch_state.timers[j].next == nxt && network_dispatch_state.timers[j].period > iv) {
                nxt += iv;
            }
            j++;
        }
    }
    network_dispatch_state.timers[slot].period = period;
    network_dispatch_state.timers[slot].last = cur;
    network_dispatch_state.timers[slot].next = nxt;
    network_dispatch_state.timers[slot].lock_callback = locked;
    network_dispatch_state.timers[slot].fn = fn;
    network_dispatch_state.timers[slot].active = 1;
    return 0;
}
#pragma pop

void NetEnqueueProtocolMessage(s32 arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
    NetProtocolMessage message;
    message.first = arg2;
    message.second = arg3;
    message.protocol = arg4;
    message.detail = arg1;
    message.payload = arg0;
    TLobby__sub_803F9344(network_dispatch_state.queue_handle, &message, 0xC);
}

void NetRunProtocolDispatchLoop(void) {
    NetProtocolMessage msg;
    s16 i;

    for (;;) {
        NetReceiveMessage(network_dispatch_state.queue_handle, &msg, sizeof(msg));
        TLobby::lock_mutex(network_dispatch_state.lock_handle);
        for (i = 0; i < 3; i++) {
            if (network_dispatch_state.handlers[i].used != 0 && network_dispatch_state.handlers[i].type == msg.protocol) {
                if (network_dispatch_state.handlers[i].fn != NULL) {
                    network_dispatch_state.handlers[i].fn(msg.payload, msg.detail, msg.first, msg.second);
                }
                break;
            }
        }
        TUdpSocket::unlock_mutex(network_dispatch_state.lock_handle);
        TLobby::dispatch_handler_by_id(msg.first, msg.second, msg.payload);
        NetYieldThread();
    }
}

s32 TLobby::release_slot_by_id(u16 type) {
    NetworkDispatchState *g = &network_dispatch_state;
    s16 i;
    for (i = 0; i < 3; i++) {
        if (g->handlers[i].used != 0 && g->handlers[i].type == type) {
            g->handlers[i].used = 0;
            g->handlers[i].type = 0;
            g->handlers[i].fn = NULL;
            return 0;
        }
    }
    return -0x100;
}

s32 register_protocol_handler__6TLobbyFUsi(u16 type, Handler_8041A130 fn) {
    NetworkDispatchState *g = &network_dispatch_state;
    s16 i;
    s16 freei;

    if (fn == NULL) {
        return -0x100;
    }
    freei = -1;
    for (i = 0; i < 3; i++) {
        if (network_dispatch_state.handlers[i].used != 0) {
            if (network_dispatch_state.handlers[i].type == type) {
                return -0x100;
            }
        } else if (freei < 0) {
            freei = i;
        }
    }
    if (freei < 0 || freei >= 3) {
        return -0x100;
    }
    g->handlers[freei].used = 1;
    g->handlers[freei].type = type;
    g->handlers[freei].fn = fn;
    return 0;
}

}
