#include "pso/protocol/NetworkRuntime.h"
#include "pso/network/UdpRuntime.h"
#include "pso/network/TcpControlBlock.h"
#include "types.h"
#include "pso/misc/TLobby.h"

struct Item_80420FC8 { s16 len; u8 pad2[2]; u8 data[8]; };

struct Pkt_80420FC8 { u8 pad0[4]; s32 count; s32 len; Item_80420FC8 items[1]; };

struct Hdr_80420DE4 { u16 src; u16 dst; u16 len; u16 sum; };

struct O_80420DE4 { u8 pad0[8]; s32 f8; u8 padC[0xC]; s16 f18; u8 pad1A[2]; u8 f1C[4]; };

struct TcpReceiveHeaderPrefix { u16 source; u16 destination; u32 sequence; };

struct TcpRuntimePrefix {
    TcpControlBlock *entries;
    s16 count;
    u8 unknown[0xA2];
};

extern "C" {
s32 set_slot_state_and_resume__6TLobbyFv(s16 handle, TcpOperationCallback callback, s16 status);
s32 set_thread_state_and_resume__6TLobbyFv(s16 handle, TcpOperationCallback callback, s16 status);
void TLobby__sub_803F87C8(u8 *arg0);
s32 TLobby__sub_803F87C4(void *);
void TLobby__sub_8041FDA0(TcpControlBlock *o, s16 idx, u32 a, u32 b);
void TLobby__sub_8041FED4(TcpControlBlock *tcb);
void expire_timeout_entries__6TLobbyFv(TcpControlBlock *control);
void set_value_and_enable__6TLobbyFl(NetBufferRef *reference, s32 value);
void NetMemcpy(void *_w0, void *_w1, int _w2);
s32 TLobby__sub_80420BD0(void *arg0, TcpControlBlock *s, TcpOperationCallback arg2);
s32 TLobby__sub_80420D38(u16 arg0, u8 arg1);
s16 dispatch_by_addr_family__6TLobbyFlPUcPUcPUcPvPv(void *, void *, void *, s32, s32, int);
s16 TLobby__sub_8040D8F0(void *, void *, int, void *, int);
s16 select_source_address__6TLobbyFPvPv(void *, void *);
s16 TLobby__sub_8040DA54(void *, void *);
s16 is_addr_unspecified__6TLobbyFPv(void *);
s16 udp_sendto__6TLobbyFsPvPvPvUsi(s16 id, Pkt_80420FC8 *pkt, NetworkAddress *src, NetworkAddress *dst, u16 port, s32 arg5);
void TLobby__sub_8041F66C(TcpControlBlock *o);
void TLobby__sub_80406EB8(void *, u32);
void TLobby__sub_80406FD8(void *, void *, u32);
s32 TLobby__sub_8041A9AC(TcpControlBlock *);
extern TcpRuntimePrefix tcp_protocol_state;
s32 TLobby__sub_8041ED8C(TcpControlBlock *self, void *data, u32 len, TcpOperationCallback arg3);
s32 TLobby__sub_8041F11C(TcpControlBlock *self);
s16 compare_sockaddr__6TLobbyFPUc(void *, void *);
s16 is_multicast_address__6TLobbyFs(void *, s32);
s16 TLobby__sub_80421F10(void *, void *, void *, u16, s32, s16);
s32 udp_input__6TLobbyFPvPvPvi(O_80420DE4 *arg0, NetworkAddress *src, NetworkAddress *dst, s32 arg3);
UdpRuntimeState udp_runtime_state;

s32 TLobby__sub_8041ED8C(TcpControlBlock *self, void *data, u32 len, TcpOperationCallback arg3) {
    s16 idx = self - tcp_protocol_state.entries;
    s32 m;
    u32 k;
    NetBufferRef src;
    NetBufferRef dst;
    if (self->read_buffer.kind != 0) {
        return -4;
    }
    if (self->read_closed) {
        return -4;
    }
    self->read_callback = arg3;
    NetMemcpy(&self->read_buffer, data, 8);
    self->read_length = len;
    m = 0;
    self->read_done = m;
    if (self->received == 0) {
        switch (self->state) {
        case 0:
        case 5:
        case 7:
        case 8:
        case 10:
            self->read_buffer.kind = m;
            set_slot_state_and_resume__6TLobbyFv(idx, self->read_callback, -7);
            while (self->read_buffer.kind != 0) {
                self->read_buffer.kind = m;
                set_slot_state_and_resume__6TLobbyFv(idx, self->read_callback, -7);
            }
            return 0;
        case -1:
            self->read_buffer.kind = m;
            set_slot_state_and_resume__6TLobbyFv(idx, self->read_callback, -11);
            while (self->read_buffer.kind != 0) {
                self->read_buffer.kind = m;
                set_slot_state_and_resume__6TLobbyFv(idx, self->read_callback, -11);
            }
            return 0;
        default:
            return 0;
        }
    }
    do {
        m = (s32)(self->received > self->read_length ? self->read_length : self->received);
        self->read_done = m;
        NetMemcpy(&src, &self->receive_buffer, 8);
        TLobby__sub_80406EB8(&src, self->receive_read);
        NetMemcpy(&dst, &self->read_buffer, 8);
        if (self->receive_read + m > self->receive_capacity) {
            k = self->receive_capacity - self->receive_read;
            TLobby__sub_80406FD8(&dst, &src, k);
            TLobby__sub_80406EB8(&dst, k);
            m -= k;
            self->received -= k;
            self->receive_read = 0;
            NetMemcpy(&src, &self->receive_buffer, 8);
        }
        TLobby__sub_80406FD8(&dst, &src, m);
        self->received -= m;
        self->receive_read += m;
        if (self->receive_read >= self->receive_capacity) {
            self->receive_read -= self->receive_capacity;
        }
        self->read_buffer.kind = 0;
        set_slot_state_and_resume__6TLobbyFv(idx, self->read_callback, self->read_done);
    } while (self->read_buffer.kind != 0 && self->received != 0);
    if (self->unknown_53c == 0) {
        self->flags &= ~1;
    }
    if (self->state != -1 && self->state != 0) {
        TLobby__sub_8041A9AC(self);
    }
    if (self->read_buffer.kind != 0) {
        switch (self->state) {
        case 0:
        case 5:
        case 7:
        case 8:
        case 10:
            set_slot_state_and_resume__6TLobbyFv(idx, self->read_callback, -7);
            break;
        case -1:
            set_slot_state_and_resume__6TLobbyFv(idx, self->read_callback, -11);
            break;
        default:
            return 0;
        }
    }
    if (self->received == 0 && (self->flags & 8) && !(self->flags & 0x20)) {
        NetDispatchSocketEvent((s16)(self - tcp_protocol_state.entries), self->event_callback, 3, 3);
        self->flags |= 0x20;
    }
    return 0;
}

s32 TLobby__sub_8041F11C(TcpControlBlock *self) {
    s16 idx = self - tcp_protocol_state.entries;
    while (self->read_buffer.kind != 0) {
        self->read_buffer.kind = 0;
        set_slot_state_and_resume__6TLobbyFv(idx, self->read_callback, -7);
    }
    if (self->received == 0 && !(self->flags & 0x20)) {
        NetDispatchSocketEvent((s16)(self - tcp_protocol_state.entries), self->event_callback, 3, 3);
        self->flags |= 0x20;
    }
    return 0;
}

s32 TLobby__sub_8041F204(NetPacket *packet, u16 skip, TcpControlBlock *control) {
    TcpControlBlock *read_control;
    s16 fragment_length;
    NetBufferRef destination;
    NetBufferRef source;
    s16 socket;
    s16 index;
    s32 completed;
    u32 available;
    u32 offset;
    u32 amount;
    u32 free_space;
    unsigned int read_limit;

    socket = control - tcp_protocol_state.entries;
    if (!(control->read_closed & 1)) {
        offset = 0;
        for (index = 1; ((u32) index) < ((u32) packet->fragment_count); index++) {
            if (((u16) packet->fragments[index].length) > skip) {
                offset = skip;
                break;
            }
            skip -= packet->fragments[index].length;
        }

        if (((u32) index) == ((u32) packet->fragment_count)) {
            return 0;
        }
        if (control->read_buffer.kind) {
            NetMemcpy(&destination, &control->read_buffer, 8);
            while (((u32) index) < ((u32) packet->fragment_count)) {
                NetMemcpy(&source, &packet->fragments[index].buffer, 8);
                if (offset != 0) {
                    TLobby__sub_80406EB8(&source, offset);
                }

                completed = (read_control = control)->read_done;
                amount = (fragment_length = packet->fragments[index].length);
                amount -= offset;
                available = (read_limit = control->read_length);
                available -= completed;

                if (available >= amount) {
                    available = amount;
                    TLobby__sub_80406FD8(&destination, &source, available);
                    control->read_done += amount;
                    control->receive_read += amount;
                    if (control->receive_read >= control->receive_capacity) {
                        control->receive_read -= control->receive_capacity;
                    }
                    control->receive_write += amount;
                    if (control->receive_write >= control->receive_capacity) {
                        control->receive_write -= control->receive_capacity;
                    }
                    TLobby__sub_80406EB8(&destination, available);
                    offset = 0;
                    index++;
                } else {
                    TLobby__sub_80406FD8(&destination, &source, available);
                    control->read_done += available;
                    control->receive_read += available;
                    if (control->receive_read >= control->receive_capacity) {
                        control->receive_read -= control->receive_capacity;
                    }
                    control->receive_write += available;
                    if (control->receive_write >= control->receive_capacity) {
                        control->receive_write -= control->receive_capacity;
                    }
                    offset += available;
                }
                if (control->read_length == control->read_done) {
                    control->read_buffer.kind = 0;
                    set_slot_state_and_resume__6TLobbyFv(socket, control->read_callback, control->read_done);
                    if (!control->read_buffer.kind) {
                        goto store_received;
                    }
                    NetMemcpy(&destination, &control->read_buffer, 8);
                    if (((u32) index) >= ((u32) packet->fragment_count)) {
                        switch (control->state) {
                            case 0:

                            case 5:

                            case 7:

                            case 8:

                            case 10:
                                control->read_buffer.kind = 0;
                                set_slot_state_and_resume__6TLobbyFv(socket, control->read_callback, -7);
                                break;

                        }

                        goto complete;
                    }
                }
            }
 {
                control->read_buffer.kind = 0;
                set_slot_state_and_resume__6TLobbyFv(socket, control->read_callback, control->read_done);
                while (control->read_buffer.kind) {
                    switch (control->state) {
                        case 0:

                        case 5:

                        case 7:

                        case 8:

                        case 10:
                            control->read_buffer.kind = 0;
                            set_slot_state_and_resume__6TLobbyFv(socket, control->read_callback, -7);
                            goto complete;

                        default:
                            goto complete;

                    }

                }

                goto complete;
            }
        }
        store_received:
        NetMemcpy(&destination, &control->receive_buffer, 8);

        TLobby__sub_80406EB8(&destination, control->receive_write);
        for (; ((u32) index) < ((u32) packet->fragment_count); index++) {
            NetMemcpy(&source, &packet->fragments[index].buffer, 8);
            if (offset) {
                TLobby__sub_80406EB8(&source, offset);
            }
            available = packet->fragments[index].length - offset;
            free_space = control->receive_capacity - control->received;
            if (available > free_space) {
                available = free_space;
            }
            control->received += available;
            if ((control->receive_write + available) >= control->receive_capacity) {
                TLobby__sub_80406FD8(&destination, &source, control->receive_capacity - control->receive_write);
                NetMemcpy(&destination, &control->receive_buffer, 8);
                TLobby__sub_80406EB8(&source, control->receive_capacity - control->receive_write);
                available -= control->receive_capacity - control->receive_write;
                control->receive_write = 0;
            }
            if (available) {
                TLobby__sub_80406FD8(&destination, &source, available);
                control->receive_write += available;
                TLobby__sub_80406EB8(&destination, available);
            }
            offset = 0;
        }

        complete:
        TLobby__sub_8041F66C(control);

        return 0;
    }
    return -1;
}


void TLobby__sub_8041F66C(TcpControlBlock *o) {
    s16 i;
    s16 cnt;
    s16 j;
    s32 d;
    u8 unused[8];
    if (o->reassembly_last == -1) {
        return;
    }
    for (i = 0; i <= o->reassembly_last; i++) {
        if ((s32)(o->receive_sequence - o->reassembly[i].end) < 0) {
            break;
        }
    }
    if (i <= o->reassembly_last && (s32)(o->receive_sequence - o->reassembly[i].start) >= 0) {
        d = o->reassembly[i].end - o->receive_sequence;
        o->receive_write += d;
        if (o->receive_write >= o->receive_capacity) {
            o->receive_write -= o->receive_capacity;
        }
        cnt = i + 1;
        o->received += d;
        o->receive_sequence = o->reassembly[i].end;
    } else {
        cnt = i;
    }
    expire_timeout_entries__6TLobbyFv(o);
    if (cnt <= 0) {
        return;
    }
    o->reassembly_last -= cnt;
    for (j = 0; j < cnt; j++) {
        o->reassembly_bytes -= o->reassembly[j].end - o->reassembly[j].start;
    }
    for (j = 0; j <= o->reassembly_last; j++) {
        o->reassembly[j] = o->reassembly[j + cnt];
    }
    if (o->reassembly_last == -1) {
        o->reassembly_recent = -1;
    } else {
        o->reassembly_recent = 0;
    }
}

static inline void remove_reassembly_range(TcpControlBlock *control, s16 erase, TcpReassemblyRange *moved) {
    s16 last;
    s16 slot;
    if (erase < 0) return;
    last = control->reassembly_last;
    if (!(last < 0 || erase > last)) {
        control->reassembly_bytes -= control->reassembly[erase].end - control->reassembly[erase].start;
        for (slot = erase; slot < control->reassembly_last; slot++) {
            *moved = control->reassembly[slot + 1];
            control->reassembly[slot] = *moved;
        }
        control->reassembly_last--;
    }
}
s32 TLobby__sub_8041F914(NetPacket *packet, u16 skip, TcpControlBlock *control, TcpReceiveHeaderPrefix *header) {
    NetBufferRef destination;
    NetBufferRef source;
    u32 offset;
    u32 index;
    u32 position;
    TcpReassemblyRange moved;
    s32 copied;
    s32 gap;
    u32 end;
    u32 sequence;
    int initial_count;
    s16 range;
    if (!(control->read_closed & 1)) {

        index = (initial_count = 0);
        copied = offset = index;
        copied = initial_count;

        gap = header->sequence - control->receive_sequence;
        if (gap <= 0) {
            return 0;
        }
        if ((gap + (packet->total_bytes - skip)) > (control->receive_capacity - control->received)) {
            return 0;
        }
        for (index = 0; ((u32) index) < ((u32) packet->fragment_count); index++) {
            if (((u16) packet->fragments[index].length) > skip) {
                offset = skip;
                break;
            }
            skip -= packet->fragments[index].length;
        }

        if (index == packet->fragment_count) {
            return 0;
        }
        position = control->receive_write + gap;
        if (position > control->receive_capacity) {
            position -= control->receive_capacity;
        }
        NetMemcpy(&destination, &control->receive_buffer, 8);
        TLobby__sub_80406EB8(&destination, position);
        for (; ((u32) index) < ((u32) packet->fragment_count); index++) {
            NetMemcpy(&source, &packet->fragments[index].buffer, 8);
            if (offset) {
                TLobby__sub_80406EB8(&source, offset);
            }

            offset = packet->fragments[index].length - offset;
            if (offset > (control->receive_capacity - control->received)) {
                offset = control->receive_capacity - control->received;
            }
            copied += offset;

            if ((position + offset) >= control->receive_capacity) {
                TLobby__sub_80406FD8(&destination, &source, control->receive_capacity - position);
                NetMemcpy(&destination, &control->receive_buffer, 8);
                TLobby__sub_80406EB8(&source, control->receive_capacity - position);
                offset -= control->receive_capacity - position;
            }
            if (offset) {
                TLobby__sub_80406FD8(&destination, &source, offset);
                TLobby__sub_80406EB8(&destination, (s16) offset);
            }
            offset = 0;
        }

        sequence = header->sequence;
        end = sequence + copied;
        if (control->reassembly_last == (-1)) {
            TLobby__sub_8041FDA0(control, 0, sequence, end);
            control->reassembly_recent = 0;
        }
        else {
            if (((s32) (sequence - control->reassembly[0].start)) <= 0) {
                TLobby__sub_8041FDA0(control, 0, sequence, end);
                range = 0;
            }
            else {
                for (range = 1; range <= control->reassembly_last; range++) {
                    if (((s32) (sequence - control->reassembly[range].start)) <= 0) {
                        if (((s32) (sequence - control->reassembly[range - 1].end)) <= 0) {
                            if (((s32) (end - control->reassembly[range - 1].end)) < 0) {
                                goto finished;
                            } {
                                control->reassembly_bytes += end - control->reassembly[range - 1].end;
                                control->reassembly[range - 1].end = end;
                                range--;
                            }
                        }
                        else {
                            TLobby__sub_8041FDA0(control, range, sequence, end);
                        }
                        break;
                    }
                }

                if (range == (control->reassembly_last + 1)) {
                    if (((s32) (sequence - control->reassembly[range - 1].end)) <= 0) {
                        if (((s32) (end - control->reassembly[range - 1].end)) < 0) {
                            goto finished;
                        } {
                            control->reassembly_bytes += end - control->reassembly[range - 1].end;
                            control->reassembly[range - 1].end = end;
                            range--;
                        }
                    }
                    else {
                        TLobby__sub_8041FDA0(control, range, sequence, end);
                    }
                }
            }
            control->reassembly_recent = range;
            while (((range + 1) <= control->reassembly_last) && (((s32) (control->reassembly[range].end - control->reassembly[range + 1].start)) >= 0)) {
                if (((s32) (control->reassembly[range].end - control->reassembly[range + 1].end)) >= 0) {
                    remove_reassembly_range(control, range + 1, &moved);
                }
                else {
                    control->reassembly_bytes += control->reassembly[range + 1].end - control->reassembly[range].end;
                    control->reassembly[range].end = control->reassembly[range + 1].end;
                    remove_reassembly_range(control, range + 1, &moved);
                }
            }

        }
    finished:
        TLobby__sub_8041FED4(control);

        return 0;
    }
    return -1;
}


void TLobby__sub_8041FDA0(TcpControlBlock *o, s16 idx, u32 start, u32 end) {
    s16 i;
    if (idx < 0) {
        return;
    }
    if (idx > o->reassembly_last + 1) {
        return;
    }
    if (idx > 0x1F) {
        return;
    }
    if (o->reassembly_last >= 0x1F) {
        o->reassembly_last = 0x1E;
    }
    for (i = o->reassembly_last; i >= idx; i--) {
        o->reassembly[i + 1] = o->reassembly[i];
    }
    o->reassembly[idx].start = start;
    o->reassembly[idx].end = end;
    o->reassembly_last++;
    o->reassembly_bytes += end - start;
}

void expire_timeout_entries__6TLobbyFv(TcpControlBlock *o) {
    s16 i;
    s16 j;
    i = 0;
    while (i < 5) {
        if (o->sack[i].start == o->sack[i].end) {
            return;
        }
        if ((s32)(o->sack[i].end - o->receive_sequence) <= 0) {
            for (j = i; j < 4; j++) {
                o->sack[j] = o->sack[j + 1];
            }
            o->sack[4].start = 0;
            o->sack[4].end = 0;
        } else {
            i++;
        }
    }
}

void TLobby__sub_8041FED4(TcpControlBlock *tcb) {
    u32 start;
    u32 end;
    s16 i;
    s16 j;
    s16 k;
    if (tcb->reassembly_recent == -1) {
        return;
    }
    start = tcb->reassembly[tcb->reassembly_recent].start;
    end = tcb->reassembly[tcb->reassembly_recent].end;
    for (i = 4; i > 0; i--) {
        tcb->sack[i] = tcb->sack[i - 1];
    }
    tcb->sack[0].start = start;
    tcb->sack[0].end = end;
    for (i = 4; i > 0; i--) {
        if (tcb->sack[i].start == tcb->sack[i].end) {
            continue;
        }
        for (j = i - 1; j >= 0; j--) {
            if ((s32)(tcb->sack[i].start - tcb->sack[j].start) >= 0 && (s32)(tcb->sack[i].end - tcb->sack[j].end) <= 0) {
                for (k = i; k < 5; k++) {
                    tcb->sack[k] = tcb->sack[k + 1];
                }
                tcb->sack[4].start = 0;
                tcb->sack[4].end = 0;
                break;
            }
        }
    }
}

#pragma push
#pragma dont_inline on
#pragma opt_lifetimes off
s32 TLobby__sub_8041FFF8(u32 acknowledged, TcpControlBlock *control) {
    struct { u32 read_index; } ring;
    TcpSendRequest request;
    NetBufferRef cursor;
    u8 reserved_stack[8]; // Unreferenced area of the native 96-byte frame.
    NetBufferRef request_ref;
    NetBufferRef destination;
    s16 handle;
    u32 remaining;
    s16 fragment_index;
    NetPacketFragment *copy_fragment;
    u32 available;
    NetPacketFragment *ack_fragment;
    s16 length;

    handle = control - tcp_protocol_state.entries;
    if ((u32)control->queued_send == 1) {
        cursor.kind = 1;
        remaining = acknowledged;
        request_ref.kind = 1;
        if (acknowledged != 0 && control->send_count != 0) {
            set_value_and_enable__6TLobbyFl(&request_ref, (s32)&request);
            NetMemcpy(&cursor, &control->send_buffer, 8);
            if ((s32)control->send_read != 0) {
                TLobby__sub_80406EB8(&cursor, control->send_read * 16);
            }
            TLobby__sub_80406FD8(&request_ref, &cursor, 16);
            while (request.length <= remaining && control->send_count != 0) {
                control->send_count--;
                remaining -= request.length;
                control->send_request.total_bytes -= request.length;
                if ((u32)control->send_read < 64) {
                    control->send_read++;
                } else {
                    control->send_read = 0;
                }
                if (control->send_count == 0) {
                    control->send_write = 0;
                    control->send_read = 0;
                    control->queued_send = 0;
                }
                complete_request_callback__6TLobbyFv(handle, request.callback, 0, &request);
                ring.read_index = control->send_read;
                NetMemcpy(&cursor, &control->send_buffer, 8);
                if ((s32)ring.read_index != 0) {
                    TLobby__sub_80406EB8(&cursor, ring.read_index * 16);
                }
                TLobby__sub_80406FD8(&request_ref, &cursor, 16);
            }
            if (remaining != 0 && control->send_count != 0) {
                control->send_request.total_bytes -= remaining;
                length = remaining;
                request.length -= length;
                request.offset += length;
                TLobby__sub_80406FD8(&cursor, &request_ref, 16);
            }
        }
        return 0;
    }
    if (acknowledged != 0) {
        if (acknowledged <= control->send_count) {
            control->send_count -= acknowledged;
            control->send_read += acknowledged;
            if ((u32)control->send_read >= control->send_capacity) {
                control->send_read -= control->send_capacity;
            }
        } else {
            acknowledged = acknowledged - control->send_count;
            control->send_count = 0;
            control->send_read = control->send_write;
            control->send_request.total_bytes -= acknowledged;
            ack_fragment = control->send_request.fragments;
            for (fragment_index = 0;
            (u32)fragment_index < (u32)control->send_request.fragment_count && acknowledged != 0; fragment_index++) {
                if (acknowledged >= ack_fragment->length) {
                    acknowledged -= ack_fragment->length;
                    ack_fragment->length = 0;
                } else {
                    ack_fragment->length -= acknowledged;
                    TLobby__sub_80406EB8(&ack_fragment->buffer, acknowledged);
                    acknowledged = 0;
                }
                ack_fragment++;
            }
        }
    }
    if (control->send_request.total_bytes != 0 && control->send_request.total_bytes <= control->send_capacity - control->send_count) {
        NetMemcpy(&destination, &control->send_buffer, 8);
        TLobby__sub_80406EB8(&destination, control->send_write);
        for (fragment_index = 0, copy_fragment = control->send_request.fragments; (u32)fragment_index < (u32)control->send_request.fragment_count; fragment_index++) {
            if (copy_fragment->length > 0) {
                control->send_count += copy_fragment->length;
                if (copy_fragment->length > (available = control->send_capacity - control->send_write)) {
                    TLobby__sub_80406FD8(&destination, &copy_fragment->buffer, available);
                    TLobby__sub_80406EB8(&copy_fragment->buffer, available);
                    copy_fragment->length -= available;
                    control->send_request.total_bytes -= available;
                    control->send_write = 0;
                    NetMemcpy(&destination, &control->send_buffer, 8);
                }
                length = copy_fragment->length;
                TLobby__sub_80406FD8(&destination, &copy_fragment->buffer, length);
                control->send_write += length;
                TLobby__sub_80406EB8(&destination, length);
                control->send_request.total_bytes -= length;
                copy_fragment->length = 0;
            }
            copy_fragment++;
        }
        if (control->send_request.total_bytes != 0) return 0;
        {
            control->send_request.total_bytes = 0;
            control->send_request.fragment_count = 0;
            set_thread_state_and_resume__6TLobbyFv(handle, control->write_callback, 0);
        }
    } else if (control->send_request.total_bytes == 0) {
        set_thread_state_and_resume__6TLobbyFv(handle, control->write_callback, 0);
    }
    return 0;
}
#pragma pop

#pragma push
#pragma dont_inline on
#pragma opt_propagation off
s32 TLobby__sub_80420410(s32 offset, s32 length, NetPacket *packet, TcpControlBlock *control) {
    TcpSendRequest request;
    NetBufferRef request_cursor;
    NetBufferRef buffer_cursor;
    NetBufferRef request_ref;
    NetBufferRef swap_buffer;
    u32 shift_source_address;
    u32 wrap_length;
    s32 ring_index;
    u32 partial_total;
    s16 segment_length;
    s32 first_fragment;
    u32 reverse_right_address;
    u32 prepend_address;
    s32 appended_count;
    s32 prepend_length;
    s32 tail_index;
    u32 prepend_total;
    s32 lower;
    NetPacketFragment *output_fragment;
    u32 unwrapped_position;
    u32 ring_position;
    s32 shifted_count;
    // Widening keeps the 16-bit store and signed extension distinct in MWCC.
    s64 partial_length;
    u16 fragment_offset;
    s32 swapped_length;
    u16 ring_offset;
    s32 upper;
    u32 queued_remaining;
    s32 partial_fragment;
    u32 shift_destination_address;
    NetPacketFragment *scan_fragment;
    s32 output_index;
    s32 scan_index;
    u32 reverse_left_address;
    s32 segment_remaining;
    u32 send_fragment;
    NetPacketFragment *output_tail;
    s16 split_length;
    u32 queued_total;

    // Integer address cursors permit the unused final decrement before an array.
    // Convert back to pointers only when the guarded fragment access is valid.
    if (control->queued_send == 1) {
        request_cursor.kind = 1;
        queued_remaining = length;
        buffer_cursor.kind = 1;
        request_ref.kind = 1;
        if ((u32)length == 0) {
            goto neg1;
        }
        if (control->send_count == 0) {
            goto neg1;
        }
        set_value_and_enable__6TLobbyFl(&request_ref, (s32)&request);
        ring_index = control->send_read;
        NetMemcpy(&request_cursor, &control->send_buffer, 8);
        if (ring_index != 0) {
            TLobby__sub_80406EB8(&request_cursor, ring_index << 4);
        }
        TLobby__sub_80406FD8(&request_ref, &request_cursor, 16);
        if ((u32)offset != 0) {
            while ((u32)request.length <= (u32)offset) {
                offset -= request.length;
                if (ring_index < 64) {
                    ring_index++;
                } else {
                    ring_index = 0;
                }
                NetMemcpy(&request_cursor, &control->send_buffer, 8);
                if (ring_index != 0) {
                    TLobby__sub_80406EB8(&request_cursor, ring_index << 4);
                }
                TLobby__sub_80406FD8(&request_ref, &request_cursor, 16);
            }
            NetMemcpy(&buffer_cursor, &request.buffer, 8);
            request.length -= (s16)offset;
            TLobby__sub_80406EB8(&buffer_cursor, request.offset);
            TLobby__sub_80406EB8(&buffer_cursor, offset);
        } else {
            NetMemcpy(&buffer_cursor, &request.buffer, 8);
            TLobby__sub_80406EB8(&buffer_cursor, request.offset);
        }
        length = packet->fragment_count;
        while (queued_remaining != 0) {
            output_fragment = &packet->fragments[packet->fragment_count];
            if (queued_remaining >= (u32)(segment_length = request.length)) {
                queued_total = packet->total_bytes;
                output_fragment->length = segment_length;
                packet->total_bytes = queued_total + segment_length;
                queued_remaining -= request.length;
            } else {
                output_fragment->length = queued_remaining;
                packet->total_bytes += queued_remaining;
                queued_remaining = 0;
            }
            NetMemcpy(&output_fragment->buffer, &buffer_cursor, 8);
            packet->fragment_count++;
            if (queued_remaining != 0) {
                if (ring_index < 64) {
                    ring_index++;
                } else {
                    ring_index = 0;
                }
                NetMemcpy(&request_cursor, &control->send_buffer, 8);
                if (ring_index != 0) {
                    TLobby__sub_80406EB8(&request_cursor, ring_index << 4);
                }
                TLobby__sub_80406FD8(&request_ref, &request_cursor, 16);
                NetMemcpy(&buffer_cursor, &request.buffer, 8);
            }
        }
        appended_count = packet->fragment_count - length;
        lower = (appended_count - 2) / 2;
        upper = (appended_count + 1) / 2;
        // Swap fragment values while retaining the destination kind byte.
        reverse_right_address = (u32)packet + sizeof(NetPacketFragment) * (upper);
        reverse_left_address = (u32)packet + sizeof(NetPacketFragment) * (lower);
        for (; lower >= 0 && upper < appended_count; ) {
            NetMemcpy(
                &swap_buffer,
                (void *)(reverse_right_address + offsetof(NetPacket, fragments) + offsetof(NetPacketFragment, buffer)),
                8);
            NetMemcpy(
                (void *)(reverse_right_address + offsetof(NetPacket, fragments) + offsetof(NetPacketFragment, buffer)),
                (void *)(reverse_left_address + offsetof(NetPacket, fragments) + offsetof(NetPacketFragment, buffer)),
                8);
            NetMemcpy(
                (void *)(reverse_left_address + offsetof(NetPacket, fragments) + offsetof(NetPacketFragment, buffer)),
                &swap_buffer,
                4);
            swapped_length = *(s16 *)(reverse_right_address + offsetof(NetPacket, fragments));
            *(s16 *)(reverse_right_address + offsetof(NetPacket, fragments)) =
                *(s16 *)(reverse_left_address + offsetof(NetPacket, fragments));
            *(s16 *)(reverse_left_address + offsetof(NetPacket, fragments)) = swapped_length;
            reverse_right_address += sizeof(NetPacketFragment);
            reverse_left_address -= sizeof(NetPacketFragment);
            lower--;
            upper++;
        }
        return 0;
neg1:
        return -1;
    }

    ring_offset = (u16)offset;
    partial_fragment = -1;
    unwrapped_position = ring_offset + control->send_read;
    output_index = 0;
    if ((u32)offset >= control->send_count + control->send_request.total_bytes) {
        return -1;
    }
    if ((u32)offset < control->send_count) {
        if ((u32)(length + offset) > control->send_count) {
            goto adj;
        }
        if (control->send_read + offset < control->send_capacity) {
            if (length + (control->send_read + offset) <= control->send_capacity) {
                packet->fragment_count = 1;
                NetMemcpy(&packet->fragments[0].buffer, &control->send_buffer, 8);
                TLobby__sub_80406EB8(&packet->fragments[0].buffer, unwrapped_position);
                packet->fragments[0].length = length;
            } else {
                packet->fragment_count = 2;
                NetMemcpy(&packet->fragments[0].buffer, &control->send_buffer, 8);
                NetMemcpy(&packet->fragments[1].buffer, &control->send_buffer, 8);
                TLobby__sub_80406EB8(&packet->fragments[1].buffer, unwrapped_position);
                *(u16 *)&packet->fragments[1].length = (wrap_length = control->send_capacity - unwrapped_position);
                packet->fragments[0].length = length - wrap_length;
            }
        } else {
            packet->fragment_count = 1;
            NetMemcpy(&packet->fragments[0].buffer, &control->send_buffer, 8);
            TLobby__sub_80406EB8(&packet->fragments[0].buffer, unwrapped_position - control->send_capacity);
            packet->fragments[0].length = length;
        }
        packet->total_bytes = length;
        return 0;
adj:
        length -= control->send_count - ring_offset;
        goto tail;
    }
    offset -= control->send_count;
    scan_fragment = control->send_request.fragments;
    for (scan_index = 0; (u32)scan_index < control->send_request.fragment_count; ) {
        if ((u32)offset < (u32)(s32)scan_fragment->length) {
            packet->fragment_count = 1;
            first_fragment = scan_index;
            fragment_offset = (u16)offset;
            NetMemcpy(&packet->fragments[0].buffer, &scan_fragment->buffer, 8);
            TLobby__sub_80406EB8(&packet->fragments[0].buffer, fragment_offset);
            packet->total_bytes = length;
            packet->fragments[0].length = length;
            if ((u32)(length + offset) <= (u32)(s32)scan_fragment->length) {
                packet->total_bytes = length;
                packet->fragments[0].length = length;
                return 0;
            }
            segment_remaining = scan_fragment->length - fragment_offset;
            packet->total_bytes = segment_remaining;
            packet->fragments[0].length = segment_remaining;
            scan_index++;
            while ((u32)scan_index < control->send_request.fragment_count) {
                shifted_count = scan_index - first_fragment;
                s32 shift_index = shifted_count;
                shift_source_address = (u32)packet + sizeof(NetPacketFragment) * ((shifted_count - 1));
                shift_destination_address = (u32)packet + sizeof(NetPacketFragment) * (shift_index);
                for (; shift_index > 0; ) {
                    NetMemcpy(
                        (void *)(shift_destination_address + offsetof(NetPacket, fragments) + offsetof(NetPacketFragment, buffer)),
                        (void *)(shift_source_address + offsetof(NetPacket, fragments) + offsetof(NetPacketFragment, buffer)),
                        8);
                    *(s16 *)(shift_destination_address + offsetof(NetPacket, fragments)) =
                        *(s16 *)(shift_source_address + offsetof(NetPacket, fragments));
                    shift_index--;
                    shift_source_address -= sizeof(NetPacketFragment);
                    shift_destination_address -= sizeof(NetPacketFragment);
                }
                packet->fragment_count++;
                scan_fragment++;
                length -= segment_remaining;
                NetMemcpy(&packet->fragments[0].buffer, &scan_fragment->buffer, 8);
                if (length <= (s32)scan_fragment->length) {
                    packet->fragments[0].length = length;
                    packet->total_bytes += length;
                    return 0;
                }
                packet->fragments[0].length = scan_fragment->length;
                scan_index++;
                packet->total_bytes += scan_fragment->length;
                segment_remaining = scan_fragment->length;
            }
            packet->total_bytes = 0;
            packet->fragments[0].length = 0;
            packet->fragments[1].length = 0;
            break;
        }
        offset -= scan_fragment->length;
        scan_fragment++;
        scan_index++;
    }
    return 0;
tail:
    tail_index = 0;
    send_fragment = (u32)&control->send_request.fragments[tail_index];
    for (; (u32)tail_index < control->send_request.fragment_count; ) {
        if ((u32)length <= (u32)(s32)*(s16 *)(send_fragment + offsetof(NetPacketFragment, length))) {
            packet->fragment_count = 1;
            NetMemcpy(
                &packet->fragments[0].buffer,
                (NetBufferRef *)(send_fragment + offsetof(NetPacketFragment, buffer)),
                8);
            packet->total_bytes = length;
            packet->fragments[0].length = length;
            output_index = 1;
            break;
        }
        length -= *(s16 *)(send_fragment + offsetof(NetPacketFragment, length));
        send_fragment += sizeof(NetPacketFragment);
        tail_index++;
    }
    prepend_address = (u32)packet + sizeof(NetPacketFragment) * (output_index);
    send_fragment -= sizeof(NetPacketFragment);
    tail_index--;
    while (tail_index > -1) {
        packet->fragment_count++;
        NetMemcpy(
            (void *)(prepend_address + offsetof(NetPacket, fragments) + offsetof(NetPacketFragment, buffer)),
            (NetBufferRef *)(send_fragment + offsetof(NetPacketFragment, buffer)),
            8);
        output_index++;
        prepend_length = *(s16 *)(send_fragment + offsetof(NetPacketFragment, length));
        send_fragment -= sizeof(NetPacketFragment);
        tail_index--;
        prepend_total = packet->total_bytes;
        *(s16 *)(prepend_address + offsetof(NetPacket, fragments)) = prepend_length;
        packet->total_bytes = prepend_total + prepend_length;
        prepend_address += sizeof(NetPacketFragment);
    }
    output_tail = &packet->fragments[output_index];
    if (partial_fragment < 0) {
        ring_position = ring_offset + control->send_read;
        if (ring_position < control->send_capacity) {
            if (control->send_read + control->send_count <= control->send_capacity) {
                packet->fragment_count++;
                NetMemcpy(&output_tail->buffer, &control->send_buffer, 8);
                TLobby__sub_80406EB8(&output_tail->buffer, ring_position);
                output_tail->length = control->send_count - ring_offset;
            } else {
                packet->fragment_count += 2;
                NetMemcpy(&output_tail->buffer, &control->send_buffer, 8);
                NetMemcpy(&output_tail[1].buffer, &control->send_buffer, 8);
                TLobby__sub_80406EB8(&output_tail[1].buffer, ring_position);
                output_tail[1].length = (split_length = control->send_capacity - ring_position);
                output_tail->length = control->send_count - ring_offset - split_length;
            }
        } else {
            packet->fragment_count++;
            NetMemcpy(&output_tail->buffer, &control->send_buffer, 8);
            TLobby__sub_80406EB8(&output_tail->buffer, ring_position - control->send_capacity);
            output_tail->length = control->send_count - ring_offset;
        }
        packet->total_bytes += control->send_count - ring_offset;
    } else {
        /* Unreachable: partial_fragment is only ever -1. */
        packet->fragment_count++;
        NetMemcpy(&output_tail->buffer, &control->send_request.fragments[partial_fragment].buffer, 4);
        TLobby__sub_80406EB8(&output_tail->buffer, ring_offset);
        partial_length = control->send_request.in_use - ring_offset;
        partial_total = packet->total_bytes;
        output_tail->length = partial_length;
        packet->total_bytes = partial_total + (s16)partial_length;
    }
    return 0;
}
#pragma pop


s32 TLobby__sub_80420BD0(void *arg0, TcpControlBlock *s, TcpOperationCallback arg2) {
    u32 v;
    if (s->queued_send == 1) {
        if (s->queued_send) {
            v = s->send_request.total_bytes;
        } else {
            v = s->send_count + s->send_request.total_bytes;
        }
        if (v != 0) {
            return -1;
        }
    }
    s->write_callback = arg2;
    NetMemcpy(&s->send_request, arg0, 0x9C);
    s->queued_send = 0;
    return 0;
}

s32 TLobby::reset_stack_module() {
    TLobby__sub_803F87C4(&udp_runtime_state.count);
    udp_runtime_state.count = 0;
    return 0;
}
s32 TLobby::init_ucb_entries() {
    s16 i;
    UdpControlBlock *e;

    TLobby__sub_803F87C8((u8 *)&udp_runtime_state);
    e = udp_runtime_state.entries;
    i = 0;
    while (i < udp_runtime_state.count) {
        e->signature[0] = 0x55;
        e->signature[1] = 0x43;
        e->signature[2] = 0x42;
        e->index = i;
        e->active = 0;
        i++;
        e++;
    }
    udp_runtime_state.ephemeralPort = 0;
    udp_runtime_state.ephemeralPortEnd = 0x7FF;
    udp_runtime_state.ephemeralPortStart = 0x400;
    return 0;
}
s32 TLobby__sub_80420D38(u16 arg0, u8 arg1) {
    s16 i;
    UdpControlBlock *e;
    UdpRuntimeState *g = &udp_runtime_state;
    for (i = 0, e = g->entries; i < g->count; i++, e++) {
        if (e->active != 0 && e->localPort == arg0) {
            s16 f = 0;
            if ((u8)(arg1 - 2) <= 1) {
                f = 0x81;
            } else if (arg1 <= 1) {
                f = 0x80;
            }
            if (f != 0) {
                NetDispatchSocketEvent(i, e->eventCallback, 2, f);
            }
            break;
        }
    }
    return 0;
}
#pragma push
#pragma dont_inline off
#pragma inline_depth(4)
inline void add_item_80420FC8(Pkt_80420FC8 *pkt, void *data, s32 len) {
    s32 n = pkt->count;
    s32 off = pkt->len;
    pkt->items[n].len = len;
    pkt->len = off + len;
    ((TLobby *)(pkt->items[n].data))->set_value_and_enable((s32)data);
    pkt->count++;
}

s32 udp_input__6TLobbyFPvPvPvi(O_80420DE4 *arg0, NetworkAddress *src, NetworkAddress *dst, s32 arg3) {
    u8 sp20[8];
    Hdr_80420DE4 hdr;
    UdpRuntimeState *g;
    s16 i;
    s16 *plen;
    UdpControlBlock *e;
    plen = &arg0->f18;
    ((TLobby *)sp20)->set_value_and_enable((s32)&hdr);
    TLobby__sub_80406FD8(sp20, plen + 2, 8);
    if (hdr.sum != 0 && (u16)TLobby__sub_8040D8F0(src, dst, 0x11, arg0, 0) != 0) {
        return -1;
    }
    g = &udp_runtime_state;
    e = g->entries;
    i = 0;
    while (i < g->count) {
        if (e->active == 0) {
            goto next;
        }
        if (is_addr_unspecified__6TLobbyFPv(&e->remoteAddress) != 0) {
            if (e->remoteAddress.family != 0 && e->remoteAddress.family != src->family) {
                goto next;
            }
        } else if (compare_sockaddr__6TLobbyFPUc(&e->remoteAddress, src) != 0) {
            goto next;
        }
        if (is_addr_unspecified__6TLobbyFPv(&e->localAddress) != 0) {
            if (e->localAddress.family != 0 && e->localAddress.family != dst->family) {
                goto next;
            }
        } else if (compare_sockaddr__6TLobbyFPUc(&e->localAddress, dst) != 0) {
            goto next;
        }
        if (e->remotePort != 0 && e->remotePort != hdr.src) {
            goto next;
        }
        if (e->localPort != hdr.dst) {
            goto next;
        }
        arg0->f8 -= 8;
        *plen -= 8;
        TLobby__sub_80406EB8(plen + 2, 8);
        if (TLobby__sub_80421F10(arg0, src, dst, hdr.src, e->receiveCallback, i) != 0) {
            return -1;
        }
        return 0;
    next:
        i++;
        e++;
    }
    if (is_multicast_address__6TLobbyFs(dst, arg3) == 1) {
        return 0;
    }
    return -2;
}

s16 udp_sendto__6TLobbyFsPvPvPvUsi(s16 id, Pkt_80420FC8 *pkt, NetworkAddress *src, NetworkAddress *dst, u16 port, s32 arg5) {
    s16 r;
    UdpControlBlock *e;
    if (id < 0 || id >= udp_runtime_state.count) {
        return -4;
    }
    e = udp_runtime_state.entries;
    e += id;
    if (e->active == 0) {
        return -4;
    }
    if (is_addr_unspecified__6TLobbyFPv(&e->remoteAddress) == 0) {
        dst = &e->remoteAddress;
    }
    if (e->localAddress.family != 0) {
        src = &e->localAddress;
    }
    if (src->family != 0 && src->family != dst->family) {
        return -2;
    }
    if (e->remotePort != 0) {
        e->destinationPort = e->remotePort;
    } else {
        e->destinationPort = port;
    }
    if (TLobby__sub_8040DA54(dst, src) == 0) {
        NetDispatchSocketEvent(id, e->eventCallback, 2, 0x80);
        return -6;
    }
    r = select_source_address__6TLobbyFPvPv(src, dst);
    if (r < 0) {
        return r;
    }
    e->length = pkt->len + 8;
    add_item_80420FC8(pkt, &e->sourcePort, 8);
    e->checksum = 0;
    e->checksum = TLobby__sub_8040D8F0(src, dst, 0x11, pkt, 1);
    return dispatch_by_addr_family__6TLobbyFlPUcPUcPUcPvPv(pkt, dst, src, arg5 + 4, arg5 + 4, 0x11);
}
#pragma pop

}

extern "C" {
s32 NetUdpClose(s16 id) {
    if (id < 0 || id >= udp_runtime_state.count) return -4;
    UdpControlBlock* entry = udp_runtime_state.entries;
    entry += id;
    if (!entry->active) return -4;
    NetDispatchSocketEvent(id, entry->eventCallback, 2, 0xFF);
    entry->active = 0;
    return 0;
}
s16 NetUdpConnect(s16 id, NetworkAddress* remoteAddress, s32 port, s32 eventCallback, u32 receiveCallback) {
    if (id < 0 || id >= udp_runtime_state.count) return -4;
    UdpControlBlock* entry = udp_runtime_state.entries;
    entry += id;
    if (!entry->active) return -4;
    if (entry->receiveCallback != 0) return -4;
    if (remoteAddress->family != 0) {
        NetMemcpy(&entry->remoteAddress, remoteAddress, sizeof(NetworkAddress));
    } else {
        NetMemset(&entry->remoteAddress, 0, sizeof(NetworkAddress));
    }
    entry->remotePort = port;
    entry->destinationPort = port;
    entry->eventCallback = eventCallback;
    entry->receiveCallback = receiveCallback;
    return 0;
}

s16 NetUdpBind(s16 id, NetworkAddress* localAddress, s32 port) {
    if (id < 0 || id >= udp_runtime_state.count) return -4;
    if (localAddress != NULL && NetValidateLocalAddress(localAddress) < 0) return -4;
    UdpControlBlock* entry = udp_runtime_state.entries;
    entry += id;
    if (!entry->active) return -4;
    if ((u16)port != 0) {
        s16 index = 0;
        UdpControlBlock* other = udp_runtime_state.entries;
        for (; index < udp_runtime_state.count; index++, other++) {
            if (other->active && other->localPort == (u16)port) return -3;
        }
    }
    if (localAddress->family != 0) {
        NetMemcpy(&entry->localAddress, localAddress, sizeof(NetworkAddress));
    } else {
        NetMemset(&entry->localAddress, 0, sizeof(NetworkAddress));
    }
    // Keep both narrowing casts to preserve MWCC's register allocation.
    if ((u16)(s16)port != 0) {
        entry->localPort = port;
    } else {
        entry->localPort = NetUdpAllocateEphemeralPort();
    }
    entry->sourcePort = entry->localPort;
    return 0;
}

#pragma push
#pragma opt_dead_assignments off
s16 NetUdpCreate(void) {
    s16 index = 0;
    UdpControlBlock* entry = udp_runtime_state.entries;
    for (; index < udp_runtime_state.count; index++, entry++) {
        if (!entry->active) {
            entry->signature[0] = 'U';
            entry->signature[1] = 'C';
            entry->signature[2] = 'B';
            entry->index = index;
            entry->active = 1;
            entry->sourcePort = 0;
            entry->destinationPort = 0;
            entry->length = 0;
            entry->checksum = 0;
            entry->localPort = 0;
            entry->remotePort = 0;
            NetMemset(&entry->remoteAddress, 0, sizeof(NetworkAddress));
            NetMemset(&entry->localAddress, 0, sizeof(NetworkAddress));
            entry->receiveCallback = 0;
            entry->eventCallback = 0;
            return index;
        }
    }
    return -0x104;
}

#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(4)
inline s16 IsUdpPortInUse(u16 port) {
    s16 index = 0;
    UdpControlBlock* entry = udp_runtime_state.entries;
    for (; index < udp_runtime_state.count; index++, entry++) {
        if (entry->active == 1 && port == entry->localPort) return 1;
    }
    return 0;
}

u16 NetUdpAllocateEphemeralPort() {
    if (!udp_runtime_state.ephemeralPort) {
        s32 tick;
        NetStoreTick(&tick);
        udp_runtime_state.ephemeralPort = udp_runtime_state.ephemeralPortStart;
        udp_runtime_state.ephemeralPort |= tick & 0x3FF;
    } else if (udp_runtime_state.ephemeralPort < udp_runtime_state.ephemeralPortEnd) {
        udp_runtime_state.ephemeralPort++;
    } else {
        udp_runtime_state.ephemeralPort = udp_runtime_state.ephemeralPortStart;
    }
    while (IsUdpPortInUse(udp_runtime_state.ephemeralPort)) {
        if (udp_runtime_state.ephemeralPort < udp_runtime_state.ephemeralPortEnd) {
            udp_runtime_state.ephemeralPort++;
        } else {
            udp_runtime_state.ephemeralPort = udp_runtime_state.ephemeralPortStart;
        }
    }
    return udp_runtime_state.ephemeralPort;
}
#pragma pop

}
