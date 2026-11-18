// TCP queue recovery adapted from zeroz41/pso-decomp (MIT); see third_party/README.md.
#ifdef PSO_SOCKET_QUEUE_PORT
#include "pso/port/SocketQueue.h"
#else
#include "pso/protocol/NetworkRuntime.h"
#include "pso/network/UdpRuntime.h"
#include "pso/network/TcpReceiveQueue.h"
#include "pso/network/TcpControlBlock.h"
#include "types.h"
#include "pso/misc/TLobby.h"

struct S_80420BD0 {
    u8 pad0[0x20]; s32 f20; u8 pad24[8]; u8 data2C[8]; u32 f34;
    u8 pad38[0x1FC - 0x38]; s32 f1FC; u8 pad200[4];
    u8 flag : 1; u8 rest : 7;
};

struct Item_80420FC8 { s16 len; u8 pad2[2]; u8 data[8]; };

struct Pkt_80420FC8 { u8 pad0[4]; s32 count; s32 len; Item_80420FC8 items[1]; };

struct Obj_8041ED8C {
    u8 pad0[6];
    s16 f6;
    u8 pad8[3];
    u8 fB;
    u8 padC[0xC8 - 0xC];
    u8 fC8[8];
    u8 padD0[0xD8 - 0xD0];
    u32 fD8;
    u32 fDC;
    u8 padE0[4];
    u8 fE4[4];
    u8 fE8;
    u8 padE9[3];
    u32 fEC;
    s32 fF0;
    u8 padF4[0x200 - 0xF4];
    s32 f200;
    u8 f204;
    u8 pad205[0x2D0 - 0x205];
    s32 f2D0;
    u8 pad2D4[0x534 - 0x2D4];
    u32 f534;
    u8 pad538[4];
    u32 f53C;
    u8 pad540[4];
};

struct G_8041ED8C { Obj_8041ED8C *p; s16 n; u8 pad[0xA2]; };

struct Buf_8041ED8C { u8 b[8]; };

struct Obj_8041F11C {
    u8 pad0[6];
    s16 f6;
    u8 pad8[3];
    u8 fB;
    u8 padC[0xD8 - 0xC];
    u32 fD8;
    u8 padDC[0xE8 - 0xDC];
    u8 fE8;
    u8 padE9[0x200 - 0xE9];
    s32 f200;
    u8 pad204[0x2D0 - 0x204];
    s32 f2D0;
    u8 pad2D4[0x544 - 0x2D4];
};

struct G_8041F11C { Obj_8041F11C *p; s16 n; u8 pad[0xA2]; };

struct Hdr_80420DE4 { u16 src; u16 dst; u16 len; u16 sum; };

struct O_80420DE4 { u8 pad0[8]; s32 f8; u8 padC[0xC]; s16 f18; u8 pad1A[2]; u8 f1C[4]; };

extern "C" {
void TLobby__sub_803F87C8(u8 *arg0);
s32 TLobby__sub_803F87C4(void *);
void NetMemcpy(void *_w0, void *_w1, int _w2);
s32 TLobby__sub_80420BD0(void *arg0, S_80420BD0 *s, s32 arg2);
s32 TLobby__sub_80420D38(u16 arg0, u8 arg1);
s16 dispatch_by_addr_family__6TLobbyFlPUcPUcPUcPvPv(void *, void *, void *, s32, s32, int);
s16 TLobby__sub_8040D8F0(void *, void *, int, void *, int);
s16 select_source_address__6TLobbyFPvPv(void *, void *);
s16 TLobby__sub_8040DA54(void *, void *);
s16 is_addr_unspecified__6TLobbyFPv(void *);
s16 udp_sendto__6TLobbyFsPvPvPvUsi(s16 id, Pkt_80420FC8 *pkt, NetworkAddress *src, NetworkAddress *dst, u16 port, s32 arg5);
void TLobby__sub_8041F66C(TcpTcb *o);
void expire_timeout_entries__6TLobbyFv(TcpTcb *o);
void TLobby__sub_80406EB8(void *, u32);
void TLobby__sub_80406FD8(void *, void *, u32);
void TLobby__sub_8041A9AC(Obj_8041ED8C *);
extern TcpState tcp_protocol_state;
s32 set_thread_state_and_resume__6TLobbyFv(s32, TcpOperationCallback, s16);
void set_value_and_enable__6TLobbyFl(NetBufferRef *, s32);
s32 TLobby__sub_8041ED8C(Obj_8041ED8C *self, void *data, u32 len, s32 arg3);
s32 TLobby__sub_8041F11C(Obj_8041F11C *self);
s16 compare_sockaddr__6TLobbyFPUc(void *, void *);
s16 is_multicast_address__6TLobbyFs(void *, s32);
s16 TLobby__sub_80421F10(void *, void *, void *, u16, s32, s16);
s32 udp_input__6TLobbyFPvPvPvi(O_80420DE4 *arg0, NetworkAddress *src, NetworkAddress *dst, s32 arg3);
UdpRuntimeState udp_runtime_state;

struct O_8041FE44;

s32 TLobby__sub_8041ED8C(Obj_8041ED8C *self, void *data, u32 len, s32 arg3) {
    s16 idx = self - (Obj_8041ED8C *)tcp_protocol_state.tcbs;
    s32 m;
    u32 k;
    Buf_8041ED8C src;
    Buf_8041ED8C dst;
    if (self->fE8 != 0) {
        return -4;
    }
    if ((self->f204 >> 6) & 1) {
        return -4;
    }
    self->f200 = arg3;
    NetMemcpy(self->fE4, data, 8);
    self->fEC = len;
    m = 0;
    self->fF0 = m;
    if (self->fD8 == 0) {
        switch (self->f6) {
        case 0:
        case 5:
        case 7:
        case 8:
        case 10:
            self->fE8 = m;
            set_slot_state_and_resume__6TLobbyFv(idx, (TcpOperationCallback)self->f200, -7);
            while (self->fE8 != 0) {
                self->fE8 = m;
                set_slot_state_and_resume__6TLobbyFv(idx, (TcpOperationCallback)self->f200, -7);
            }
            return 0;
        case -1:
            self->fE8 = m;
            set_slot_state_and_resume__6TLobbyFv(idx, (TcpOperationCallback)self->f200, -11);
            while (self->fE8 != 0) {
                self->fE8 = m;
                set_slot_state_and_resume__6TLobbyFv(idx, (TcpOperationCallback)self->f200, -11);
            }
            return 0;
        default:
            return 0;
        }
    }
    do {
        m = (s32)(self->fD8 > self->fEC ? self->fEC : self->fD8);
        self->fF0 = m;
        NetMemcpy(&src, self->fC8, 8);
        TLobby__sub_80406EB8(&src, self->fDC);
        NetMemcpy(&dst, self->fE4, 8);
        if (self->fDC + m > self->f534) {
            k = self->f534 - self->fDC;
            TLobby__sub_80406FD8(&dst, &src, k);
            TLobby__sub_80406EB8(&dst, k);
            m -= k;
            self->fD8 -= k;
            self->fDC = 0;
            NetMemcpy(&src, self->fC8, 8);
        }
        TLobby__sub_80406FD8(&dst, &src, m);
        self->fD8 -= m;
        self->fDC += m;
        if (self->fDC >= self->f534) {
            self->fDC -= self->f534;
        }
        self->fE8 = 0;
        set_slot_state_and_resume__6TLobbyFv(idx, (TcpOperationCallback)self->f200, self->fF0);
    } while (self->fE8 != 0 && self->fD8 != 0);
    if (self->f53C == 0) {
        self->fB &= ~1;
    }
    if (self->f6 != -1 && self->f6 != 0) {
        TLobby__sub_8041A9AC(self);
    }
    if (self->fE8 != 0) {
        switch (self->f6) {
        case 0:
        case 5:
        case 7:
        case 8:
        case 10:
            set_slot_state_and_resume__6TLobbyFv(idx, (TcpOperationCallback)self->f200, -7);
            break;
        case -1:
            set_slot_state_and_resume__6TLobbyFv(idx, (TcpOperationCallback)self->f200, -11);
            break;
        default:
            return 0;
        }
    }
    if (self->fD8 == 0 && (self->fB & 8) && !(self->fB & 0x20)) {
        NetDispatchSocketEvent((s16)(self - (Obj_8041ED8C *)tcp_protocol_state.tcbs), self->f2D0, 3, 3);
        self->fB |= 0x20;
    }
    return 0;
}

s32 TLobby__sub_8041F11C(Obj_8041F11C *self) {
    s16 idx = self - (*(G_8041F11C *)&tcp_protocol_state).p;
    while (self->fE8 != 0) {
        self->fE8 = 0;
        set_slot_state_and_resume__6TLobbyFv(idx, (TcpOperationCallback)self->f200, -7);
    }
    if (self->fD8 == 0 && !(self->fB & 0x20)) {
        NetDispatchSocketEvent((s16)(self - (*(G_8041F11C *)&tcp_protocol_state).p), self->f2D0, 3, 3);
        self->fB |= 0x20;
    }
    return 0;
}

s32 TLobby__sub_8041F204(NetPacket *packet, u16 skip, TcpTcb *control) {
    s16 handle;
    s16 index;
    unsigned int amount;
    unsigned int offset;
    NetBufferRef destination;
    NetBufferRef source;

    handle = control - tcp_protocol_state.tcbs;
    if (!control->f204_b6) {
        offset = 0;
        index = 1;
        while (index < (u32)packet->fragment_count) {
            if ((u16)packet->fragments[index].length > skip) {
                offset = skip;
                break;
            }
            skip -= packet->fragments[index].length;
            index++;
        }
        if (index == (u32)packet->fragment_count) {
            return 0;
        }
        if (control->rcv_user.kind) {
            NetMemcpy(&destination, &control->rcv_user, sizeof(NetBufferRef));
            while (index < (u32)packet->fragment_count) {
                NetMemcpy(&source, &packet->fragments[index].buffer, sizeof(NetBufferRef));
                if (offset != 0) {
                    TLobby__sub_80406EB8(&source, offset);
                }
                if (control->fEC - control->fF0 >= packet->fragments[index].length - offset) {
                    amount = packet->fragments[index].length - offset;
                    TLobby__sub_80406FD8(&destination, &source, amount);
                    control->fF0 += amount;
                    control->fDC += amount;
                    if (control->fDC >= control->f534) {
                        control->fDC -= control->f534;
                    }
                    control->fE0 += amount;
                    if (control->fE0 >= control->f534) {
                        control->fE0 -= control->f534;
                    }
                    TLobby__sub_80406EB8(&destination, amount);
                    offset = 0;
                    index++;
                } else {
                    amount = control->fEC - control->fF0;
                    TLobby__sub_80406FD8(&destination, &source, amount);
                    control->fF0 += amount;
                    control->fDC += amount;
                    if (control->fDC >= control->f534) {
                        control->fDC -= control->f534;
                    }
                    control->fE0 += amount;
                    if (control->fE0 >= control->f534) {
                        control->fE0 -= control->f534;
                    }
                    offset += amount;
                }
                if (control->fEC == control->fF0) {
                    control->rcv_user.kind = 0;
                    set_slot_state_and_resume__6TLobbyFv(handle, control->recv_done, (s16)control->fF0);
                    if (!control->rcv_user.kind) {
                        goto store_received;
                    }
                    NetMemcpy(&destination, &control->rcv_user, sizeof(NetBufferRef));
                    if (index < (u32)packet->fragment_count) {
                        continue;
                    }
                    switch (control->t_state) {
                    case 0:
                    case 5:
                    case 7:
                    case 8:
                    case 10:
                        control->rcv_user.kind = 0;
                        set_slot_state_and_resume__6TLobbyFv(handle, control->recv_done, -7);
                        break;
                    }
                    goto complete;
                }
            }
            control->rcv_user.kind = 0;
            set_slot_state_and_resume__6TLobbyFv(handle, control->recv_done, (s16)control->fF0);
            while (control->rcv_user.kind != 0) {
                switch (control->t_state) {
                case 0:
                case 5:
                case 7:
                case 8:
                case 10:
                    control->rcv_user.kind = 0;
                    set_slot_state_and_resume__6TLobbyFv(handle, control->recv_done, -7);
                    break;
                }
                goto complete;
            }
            goto complete;
        }
store_received:
        NetMemcpy(&destination, &control->rcv_buf, sizeof(NetBufferRef));
        TLobby__sub_80406EB8(&destination, control->fE0);
        while (index < (u32)packet->fragment_count) {
            NetMemcpy(&source, &packet->fragments[index].buffer, sizeof(NetBufferRef));
            if (offset != 0) {
                TLobby__sub_80406EB8(&source, offset);
            }
            amount = packet->fragments[index].length - offset;
            if (amount > control->f534 - control->fD8) {
                amount = control->f534 - control->fD8;
            }
            control->fD8 += amount;
            if (control->fE0 + amount >= control->f534) {
                TLobby__sub_80406FD8(&destination, &source, control->f534 - control->fE0);
                NetMemcpy(&destination, &control->rcv_buf, sizeof(NetBufferRef));
                TLobby__sub_80406EB8(&source, control->f534 - control->fE0);
                amount -= control->f534 - control->fE0;
                control->fE0 = 0;
            }
            if (amount != 0) {
                TLobby__sub_80406FD8(&destination, &source, amount);
                control->fE0 += amount;
                TLobby__sub_80406EB8(&destination, amount);
            }
            offset = 0;
            index++;
        }
complete:
        TLobby__sub_8041F66C(control);
        return 0;
    }
    return -1;
}


void TLobby__sub_8041F66C(TcpTcb *o) {
    s16 i;
    s16 cnt;
    s16 j;
    s32 d;
    u8 unused[8];
    if (o->reasm_n == -1) {
        return;
    }
    for (i = 0; i <= o->reasm_n; i++) {
        if ((s32)(o->rcv_nxt - o->reasm[i].end) < 0) {
            break;
        }
    }
    if (i <= o->reasm_n && (s32)(o->rcv_nxt - o->reasm[i].start) >= 0) {
        d = o->reasm[i].end - o->rcv_nxt;
        o->fE0 += d;
        if (o->fE0 >= o->f534) {
            o->fE0 -= o->f534;
        }
        cnt = i + 1;
        o->fD8 += d;
        o->rcv_nxt = o->reasm[i].end;
    } else {
        cnt = i;
    }
    expire_timeout_entries__6TLobbyFv(o);
    if (cnt <= 0) {
        return;
    }
    o->reasm_n -= cnt;
    for (j = 0; j < cnt; j++) {
        o->reasm_total -= o->reasm[j].end - o->reasm[j].start;
    }
    for (j = 0; j <= o->reasm_n; j++) {
        o->reasm[j] = o->reasm[j + cnt];
    }
    if (o->reasm_n == -1) {
        o->last_reasm = -1;
    } else {
        o->last_reasm = 0;
    }
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(4)
inline void sack_remove_8041F914(TcpTcb *o, s16 idx) {
    s16 j;
    s32 len;
    if (idx < 0 || o->reasm_n < 0 || idx > o->reasm_n) {
        return;
    }
    len = o->reasm[idx].end - o->reasm[idx].start;
    o->reasm_total -= len;
    for (j = idx; j < o->reasm_n; j++) {
        o->reasm[j] = o->reasm[j + 1];
    }
    o->reasm_n--;
}

/* Queues an out-of-order segment: copies it into the receive ring at its sequence offset and merges its range into
   the SACK/reassembly list.  Returns -1 when the connection no longer receives (f204_b6). */
s32 TLobby__sub_8041F914(NetPacket *pkt, u16 x, TcpTcb *o, TcpHdr *th) {
    if (!o->f204_b6) {
        u32 i;
        u32 skip;
        u32 n;
        u32 pos;
        s32 total;
        s32 d;
        s32 seq;
        s32 end;
        s16 j;
        s32 grow;
        NetBufferRef dst;
        NetBufferRef src;
        u32 len;
        skip = 0;
        total = 0;
        d = th->seq - o->rcv_nxt;
        if (d <= 0) {
            return 0;
        }
        len = pkt->total_bytes - x;
        if (d + len > o->f534 - o->fD8) {
            return 0;
        }
        for (i = 0; i < pkt->fragment_count; i++) {
            if ((u16)pkt->fragments[i].length > x) {
                skip = x;
                break;
            }
            x -= pkt->fragments[i].length;
        }
        if (i == pkt->fragment_count) {
            return 0;
        }
        pos = o->fE0 + d;
        if (pos > o->f534) {
            pos -= o->f534;
        }
        NetMemcpy(&dst, &o->rcv_buf, 8);
        TLobby__sub_80406EB8(&dst, pos);
        for (; i < pkt->fragment_count; i++) {
            NetMemcpy(&src, &pkt->fragments[i].buffer, 8);
            if (skip != 0) {
                TLobby__sub_80406EB8(&src, skip);
            }
            if ((n = pkt->fragments[i].length - skip) > o->f534 - o->fD8) {
                n = o->f534 - o->fD8;
            }
            total += n;
            if (pos + n >= o->f534) {
                TLobby__sub_80406FD8(&dst, &src, o->f534 - pos);
                NetMemcpy(&dst, &o->rcv_buf, 8);
                TLobby__sub_80406EB8(&src, o->f534 - pos);
                n -= o->f534 - pos;
            }
            if (n != 0) {
                TLobby__sub_80406FD8(&dst, &src, n);
                TLobby__sub_80406EB8(&dst, (s16)n);
            }
            skip = 0;
        }
        seq = th->seq;
        end = seq + total;
        if (o->reasm_n == -1) {
            TLobby__sub_8041FDA0(o, 0, seq, end);
            o->last_reasm = 0;
        } else {
            if (seq - o->reasm[0].start <= 0) {
                TLobby__sub_8041FDA0(o, 0, seq, end);
                j = 0;
            } else {
                for (j = 1; j <= o->reasm_n; j++) {
                    if (seq - o->reasm[j].start <= 0) {
                        if (seq - o->reasm[j - 1].end <= 0) {
                            grow = end - o->reasm[j - 1].end;
                            if (grow < 0) {
                                goto done;
                            }
                            o->reasm_total += grow;
                            o->reasm[j - 1].end = end;
                            j--;
                        } else {
                            TLobby__sub_8041FDA0(o, j, seq, end);
                        }
                        break;
                    }
                }
                if (j == o->reasm_n + 1) {
                    if (seq - o->reasm[j - 1].end <= 0) {
                        grow = end - o->reasm[j - 1].end;
                        if (grow < 0) {
                            goto done;
                        }
                        o->reasm_total += grow;
                        o->reasm[j - 1].end = end;
                        j--;
                    } else {
                        TLobby__sub_8041FDA0(o, j, seq, end);
                    }
                }
            }
            o->last_reasm = j;
            while (j + 1 <= o->reasm_n && o->reasm[j].end - o->reasm[j + 1].start >= 0) {
                if (o->reasm[j].end - o->reasm[j + 1].end >= 0) {
                    sack_remove_8041F914(o, j + 1);
                } else {
                    o->reasm_total += o->reasm[j + 1].end - o->reasm[j].end;
                    o->reasm[j].end = o->reasm[j + 1].end;
                    sack_remove_8041F914(o, j + 1);
                }
            }
        }
    done:
        TLobby__sub_8041FED4(o);
        return 0;
    }
    return -1;
}
#pragma pop

void TLobby__sub_8041FDA0(TcpTcb *o, s16 idx, s32 a, s32 b) {
    s16 i;
    if (idx < 0) {
        return;
    }
    if (idx > o->reasm_n + 1) {
        return;
    }
    if (idx > 0x1F) {
        return;
    }
    if (o->reasm_n >= 0x1F) {
        o->reasm_n = 0x1E;
    }
    for (i = o->reasm_n; i >= idx; i--) {
        o->reasm[i + 1] = o->reasm[i];
    }
    o->reasm[idx].start = a;
    o->reasm[idx].end = b;
    o->reasm_n++;
    o->reasm_total += b - a;
}

void expire_timeout_entries__6TLobbyFv(TcpTcb *o) {
    s16 i;
    s16 j;
    i = 0;
    while (i < 5) {
        if (o->sack[i].start == o->sack[i].end) {
            return;
        }
        if ((s32)(o->sack[i].end - o->rcv_nxt) <= 0) {
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

#endif

void TLobby__sub_8041FED4(TcpTcb *tcb) {
    u32 start;
    u32 end;
    s16 i;
    s16 j;
    s16 k;
    if (tcb->last_reasm == -1) {
        return;
    }
    start = tcb->reasm[tcb->last_reasm].start;
    end = tcb->reasm[tcb->last_reasm].end;
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
                for (k = i; k < 4; ++k) {
                    tcb->sack[k] = tcb->sack[k + 1];
                }
                tcb->sack[4].start = 0;
                tcb->sack[4].end = 0;
                break;
            }
        }
    }
}

#ifndef PSO_SOCKET_QUEUE_PORT
class TcpRequestBuffer {
public:
    void initialize() { ref.kind = 1; }
    void bind(TcpSendRequest &request) { set_value_and_enable__6TLobbyFl(&ref, (s32)&request); }
    void read(NetBufferRef &source) { TLobby__sub_80406FD8(&ref, &source, sizeof(TcpSendRequest)); }
    void write(NetBufferRef &dest) { TLobby__sub_80406FD8(&dest, &ref, sizeof(TcpSendRequest)); }
private:
    NetBufferRef ref;
};
#endif

#pragma push
#pragma opt_lifetimes off
// The head is a signed request index in queue mode and a byte offset in FIFO mode.
static inline s32 request_head_index(const TcpTcb *control) {
    return control->f24;
}

static inline void advance_to_request(NetBufferRef *cursor, s32 index) {
    TLobby__sub_80406EB8(cursor, index * sizeof(TcpSendRequest));
}

static inline void complete_and_seek_next_request(NetBufferRef *cursor, TcpTcb *control,
                                                 s16 handle, const TcpSendRequest *request) {
    complete_request_callback__6TLobbyFv(handle, request->callback, 0, request);
    // Completion can reenter the socket and move the head of its send queue.
    const s32 index = request_head_index(control);
    NetMemcpy(cursor, &control->snd_buf, sizeof(*cursor));
    if (index != 0) {
        advance_to_request(cursor, index);
    }
}

s32 TLobby__sub_8041FFF8(u32 acknowledged, TcpTcb *control) {
    TcpSendRequest request;
    NetBufferRef cursor;
    NetBufferRef destination;
    s16 handle;
    u32 remaining;
    s16 fragment_index;
    NetPacketFragment *copy_fragment;
    u32 available;
    NetPacketFragment *ack_fragment;
    s16 length;

    handle = control - tcp_protocol_state.tcbs;
    if ((u32)control->f204_b7 == 1) {
        TcpRequestBuffer request_ref;
        cursor.kind = 1;
        remaining = acknowledged;
        request_ref.initialize();
        if (acknowledged != 0 && control->f20 != 0) {
            request_ref.bind(request);
            NetMemcpy(&cursor, &control->snd_buf, sizeof(cursor));
            if (request_head_index(control) != 0) {
                advance_to_request(&cursor, request_head_index(control));
            }
            request_ref.read(cursor);
            while (request.length <= remaining && control->f20 != 0) {
                control->f20--;
                remaining -= request.length;
                control->req.total_bytes -= request.length;
                if ((u32)control->f24 < 64) {
                    control->f24++;
                } else {
                    control->f24 = 0;
                }
                if (control->f20 == 0) {
                    control->f28 = 0;
                    control->f24 = 0;
                    control->f204_b7 = 0;
                }
                complete_and_seek_next_request(&cursor, control, handle, &request);
                request_ref.read(cursor);
            }
            if (remaining != 0 && control->f20 != 0) {
                control->req.total_bytes -= remaining;
                length = remaining;
                request.length -= length;
                request.offset += length;
                request_ref.write(cursor);
            }
        }
        return 0;
    }
    if (acknowledged != 0) {
        if (acknowledged <= control->f20) {
            control->f20 -= acknowledged;
            control->f24 += acknowledged;
            if ((u32)control->f24 >= control->f530) {
                control->f24 -= control->f530;
            }
        } else {
            acknowledged = acknowledged - control->f20;
            control->f20 = 0;
            control->f24 = control->f28;
            control->req.total_bytes -= acknowledged;
            ack_fragment = control->req.fragments;
            for (fragment_index = 0; (u32)fragment_index < (u32)control->req.fragment_count && acknowledged != 0; ++fragment_index) {
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
    if (control->req.total_bytes != 0 && control->req.total_bytes <= control->f530 - control->f20) {
        NetMemcpy(&destination, &control->snd_buf, sizeof(destination));
        TLobby__sub_80406EB8(&destination, control->f28);
        for (fragment_index = 0, copy_fragment = control->req.fragments; (u32)fragment_index < (u32)control->req.fragment_count; fragment_index++) {
            if (copy_fragment->length > 0) {
                control->f20 += copy_fragment->length;
                if (copy_fragment->length > (available = control->f530 - control->f28)) {
                    TLobby__sub_80406FD8(&destination, &copy_fragment->buffer, available);
                    TLobby__sub_80406EB8(&copy_fragment->buffer, available);
                    copy_fragment->length -= available;
                    control->req.total_bytes -= available;
                    control->f28 = 0;
                    NetMemcpy(&destination, &control->snd_buf, sizeof(destination));
                }
                length = copy_fragment->length;
                TLobby__sub_80406FD8(&destination, &copy_fragment->buffer, length);
                control->f28 += length;
                TLobby__sub_80406EB8(&destination, length);
                control->req.total_bytes -= length;
                copy_fragment->length = 0;
            }
            copy_fragment++;
        }
        if (control->req.total_bytes != 0) {
            return 0;
        }
        control->req.total_bytes = 0;
        control->req.fragment_count = 0;
        set_thread_state_and_resume__6TLobbyFv(handle, control->send_done, 0);
    } else if (control->req.total_bytes == 0) {
        set_thread_state_and_resume__6TLobbyFv(handle, control->send_done, 0);
    }
    return 0;
}
#pragma pop

#pragma push
#pragma opt_propagation off
s32 TLobby__sub_80420410(u32 offset, u32 length, NetPacket *packet, TcpTcb *control) {
    s32 ring_index;
    s32 shift_count;
    TcpSendRequest request;
    u32 bytes_to_end;
    NetBufferRef ring_cursor;
    u32 ring_position;
    s32 swapped_length;
    u32 remaining;
    s32 first_fragment;
    s32 appended_count;
    u16 skip_in_fragment;
    NetBufferRef buffer_cursor;
    s32 left_index;
    u16 ring_offset;
    s32 right_index;
    s32 partial_fragment;
    NetPacketFragment *output_fragment;
    TcpRequestBuffer request_ref;
    s32 output_count;
    s32 fragment_length;
    s32 request_index;
    NetPacketFragment *queued_fragment;
    s32 destination_index;
    NetPacketFragment *source_end;
    NetBufferRef swap_buffer;
    NetPacketFragment *output_tail;

    if (control->f204_b7 == 1) {
        ring_cursor.kind = 1;
        buffer_cursor.kind = 1;
        request_ref.initialize();
        remaining = length;
        if (length != 0 && control->f20 != 0) {
            request_ref.bind(request);
            ring_index = control->f24;
            NetMemcpy(&ring_cursor, &control->snd_buf, sizeof(NetBufferRef));
            if (ring_index != 0) {
                TLobby__sub_80406EB8(&ring_cursor, ring_index * sizeof(TcpSendRequest));
            }
            request_ref.read(ring_cursor);
            if (offset != 0) {
                while ((u32)request.length <= offset) {
                    offset -= request.length;
                    if (ring_index < 64) {
                        ring_index++;
                    } else {
                        ring_index = 0;
                    }
                    NetMemcpy(&ring_cursor, &control->snd_buf, sizeof(NetBufferRef));
                    if (ring_index != 0) {
                        TLobby__sub_80406EB8(&ring_cursor, ring_index * sizeof(TcpSendRequest));
                    }
                    request_ref.read(ring_cursor);
                }
                NetMemcpy(&buffer_cursor, &request.buffer, sizeof(NetBufferRef));
                request.length -= (s16)offset;
                TLobby__sub_80406EB8(&buffer_cursor, request.offset);
                TLobby__sub_80406EB8(&buffer_cursor, offset);
            } else {
                NetMemcpy(&buffer_cursor, &request.buffer, sizeof(NetBufferRef));
                TLobby__sub_80406EB8(&buffer_cursor, request.offset);
            }
            first_fragment = packet->fragment_count;
            while (remaining != 0) {
                output_fragment = &packet->fragments[packet->fragment_count];
                if (remaining >= (u32)request.length) {
                    packet->total_bytes += output_fragment->length = request.length;
                    remaining -= request.length;
                } else {
                    output_fragment->length = remaining;
                    packet->total_bytes += remaining;
                    remaining = 0;
                }
                NetMemcpy(&output_fragment->buffer, &buffer_cursor, sizeof(NetBufferRef));
                packet->fragment_count++;
                if (remaining != 0) {
                    if (ring_index < 64) {
                        ring_index++;
                    } else {
                        ring_index = 0;
                    }
                    NetMemcpy(&ring_cursor, &control->snd_buf, sizeof(NetBufferRef));
                    if (ring_index != 0) {
                        TLobby__sub_80406EB8(&ring_cursor, ring_index * sizeof(TcpSendRequest));
                    }
                    request_ref.read(ring_cursor);
                    NetMemcpy(&buffer_cursor, &request.buffer, sizeof(NetBufferRef));
                }
            }
            appended_count = packet->fragment_count - first_fragment;
            left_index = (appended_count - 2) / 2;
            right_index = (appended_count + 1) / 2;
            // The reverse copy restores only the value word of the left descriptor.
            while (left_index >= 0 && right_index < appended_count) {
                NetMemcpy(&swap_buffer, &packet->fragments[right_index].buffer, sizeof(NetBufferRef));
                NetMemcpy(&packet->fragments[right_index].buffer, &packet->fragments[left_index].buffer, sizeof(NetBufferRef));
                NetMemcpy(&packet->fragments[left_index].buffer, &swap_buffer, sizeof(swap_buffer.value));
                swapped_length = packet->fragments[right_index].length;
                packet->fragments[right_index].length = packet->fragments[left_index].length;
                packet->fragments[left_index].length = swapped_length;
                left_index--;
                right_index++;
            }
            return 0;
        }
        return -1;
    }

    ring_offset = offset;
    partial_fragment = -1;
    ring_position = ring_offset + control->f24;
    output_count = 0;
    if (offset >= control->f20 + control->req.total_bytes) {
        return -1;
    }
    if (offset < control->f20) {
        if (length + offset <= control->f20) {
            if (control->f24 + offset < control->f530) {
                if (length + (control->f24 + offset) <= control->f530) {
                    packet->fragment_count = 1;
                    NetMemcpy(&packet->fragments[0].buffer, &control->snd_buf, sizeof(NetBufferRef));
                    TLobby__sub_80406EB8(&packet->fragments[0].buffer, ring_position);
                    packet->fragments[0].length = length;
                } else {
                    packet->fragment_count = 2;
                    NetMemcpy(&packet->fragments[0].buffer, &control->snd_buf, sizeof(NetBufferRef));
                    NetMemcpy(&packet->fragments[1].buffer, &control->snd_buf, sizeof(NetBufferRef));
                    TLobby__sub_80406EB8(&packet->fragments[1].buffer, ring_position);
                    bytes_to_end = control->f530 - ring_position;
                    packet->fragments[1].length = (u16)bytes_to_end;
                    packet->fragments[0].length = length - bytes_to_end;
                }
            } else {
                packet->fragment_count = 1;
                NetMemcpy(&packet->fragments[0].buffer, &control->snd_buf, sizeof(NetBufferRef));
                TLobby__sub_80406EB8(&packet->fragments[0].buffer, ring_position - control->f530);
                packet->fragments[0].length = length;
            }
            packet->total_bytes = length;
            return 0;
        }
        length -= control->f20 - ring_offset;
    } else {
        offset -= control->f20;
        queued_fragment = control->req.fragments;
        for (request_index = 0; request_index < (u32)control->req.fragment_count; request_index++) {
            if (offset < (u32)queued_fragment->length) {
                packet->fragment_count = 1;
                partial_fragment = request_index;
                skip_in_fragment = offset;
                NetMemcpy(&packet->fragments[0].buffer, &queued_fragment->buffer, sizeof(NetBufferRef));
                TLobby__sub_80406EB8(&packet->fragments[0].buffer, skip_in_fragment);
                packet->total_bytes = length;
                packet->fragments[0].length = length;
                if (length + offset <= (u32)queued_fragment->length) {
                    packet->total_bytes = length;
                    packet->fragments[0].length = length;
                    return 0;
                }
                fragment_length = queued_fragment->length - skip_in_fragment;
                packet->total_bytes = fragment_length;
                packet->fragments[0].length = fragment_length;
                for (request_index++; request_index < (u32)control->req.fragment_count; request_index++) {
                    shift_count = request_index - partial_fragment;
                    destination_index = shift_count;
                    left_index = shift_count - 1;
                    while (destination_index > 0) {
                        NetMemcpy(&packet->fragments[destination_index].buffer, &packet->fragments[left_index].buffer, sizeof(NetBufferRef));
                        packet->fragments[destination_index].length = packet->fragments[left_index].length;
                        destination_index--;
                        left_index--;
                    }
                    packet->fragment_count++;
                    queued_fragment++;
                    length -= fragment_length;
                    NetMemcpy(&packet->fragments[0].buffer, &queued_fragment->buffer, sizeof(NetBufferRef));
                    if ((s32)length <= queued_fragment->length) {
                        packet->fragments[0].length = length;
                        packet->total_bytes += length;
                        return 0;
                    }
                    packet->fragments[0].length = queued_fragment->length;
                    packet->total_bytes += queued_fragment->length;
                    fragment_length = queued_fragment->length;
                }
                packet->total_bytes = 0;
                packet->fragments[0].length = 0;
                packet->fragments[1].length = 0;
                break;
            }
            offset -= queued_fragment->length;
            queued_fragment++;
        }
        return 0;
    }

    request_index = partial_fragment + 1;
    source_end = &control->req.fragments[request_index];
    for (; request_index < (u32)control->req.fragment_count; request_index++) {
        if (length <= (u32)source_end->length) {
            packet->fragment_count = 1;
            NetMemcpy(&packet->fragments[0].buffer, &source_end->buffer, sizeof(NetBufferRef));
            packet->total_bytes = length;
            packet->fragments[0].length = length;
            output_count = 1;
            break;
        }
        length -= source_end->length;
        source_end++;
    }
    // source_end delimits the fully consumed prefix of the queued fragments.
    request_index--;
    while (request_index > partial_fragment) {
        NetPacketFragment &previous = source_end[-1];
        packet->fragment_count++;
        NetMemcpy(&packet->fragments[output_count].buffer, &previous.buffer, sizeof(NetBufferRef));
        packet->total_bytes += packet->fragments[output_count].length = previous.length;
        output_count++;
        --source_end;
        request_index--;
    }
    output_tail = &packet->fragments[output_count];
    if (partial_fragment < 0) {
        ring_position = ring_offset + control->f24;
        if (ring_position < control->f530) {
            if (control->f24 + control->f20 <= control->f530) {
                packet->fragment_count++;
                NetMemcpy(&output_tail->buffer, &control->snd_buf, sizeof(NetBufferRef));
                TLobby__sub_80406EB8(&output_tail->buffer, ring_position);
                output_tail->length = control->f20 - ring_offset;
            } else {
                packet->fragment_count += 2;
                NetMemcpy(&output_tail->buffer, &control->snd_buf, sizeof(NetBufferRef));
                NetMemcpy(&output_tail[1].buffer, &control->snd_buf, sizeof(NetBufferRef));
                TLobby__sub_80406EB8(&output_tail[1].buffer, ring_position);
                output_tail->length = control->f20 - ring_offset - (output_tail[1].length = control->f530 - ring_position);
            }
        } else {
            packet->fragment_count++;
            NetMemcpy(&output_tail->buffer, &control->snd_buf, sizeof(NetBufferRef));
            TLobby__sub_80406EB8(&output_tail->buffer, ring_position - control->f530);
            output_tail->length = control->f20 - ring_offset;
        }
        packet->total_bytes += control->f20 - ring_offset;
    } else {
        packet->fragment_count++;
        NetMemcpy(&output_tail->buffer, &control->req.fragments[partial_fragment].buffer, sizeof(output_tail->buffer.value));
        TLobby__sub_80406EB8(&output_tail->buffer, ring_offset);
        packet->total_bytes += output_tail->length = control->req.fragments[partial_fragment].length - ring_offset;
    }
    return 0;
}
#pragma pop


#ifndef PSO_SOCKET_QUEUE_PORT
s32 TLobby__sub_80420BD0(void *arg0, S_80420BD0 *s, s32 arg2) {
    u32 v;
    if (s->flag == 1) {
        if (s->flag) {
            v = s->f34;
        } else {
            v = s->f20 + s->f34;
        }
        if (v != 0) {
            return -1;
        }
    }
    s->f1FC = arg2;
    NetMemcpy(s->data2C, arg0, 0x9C);
    s->flag = 0;
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
#endif
