// TCP queue recovery adapted from zeroz41/pso-decomp (MIT); see third_party/README.md.
#include "pso/protocol/NetworkRuntime.h"
#include "pso/network/TcpReceiveQueue.h"
#include "pso/network/SocketEvents.h"
#include "types.h"
#include "pso/misc/TLobby.h"

struct S_80420BD0 {
    u8 pad0[0x20]; s32 f20; u8 pad24[8]; u8 data2C[8]; u32 f34;
    u8 pad38[0x1FC - 0x38]; s32 f1FC; u8 pad200[4];
    u8 flag : 1; u8 rest : 7;
};

extern "C" {
void NetMemcpy(void *_w0, void *_w1, int _w2);
s32 TLobby__sub_80420BD0(void *arg0, S_80420BD0 *s, s32 arg2);
void TLobby__sub_8041F66C(TcpTcb *o);
void expire_timeout_entries__6TLobbyFv(TcpTcb *o);
void TLobby__sub_80406EB8(void *, u32);
void TLobby__sub_80406FD8(void *, void *, u32);
s16 TLobby__sub_8041A9AC(void *);
extern TcpState tcp_protocol_state;

s32 TLobby__sub_8041ED8C(TcpTcb *self, NetBufferRef *data, u32 len, TcpReceiveCallback callback) {
    s16 idx = self - tcp_protocol_state.tcbs;
    s32 m;
    u32 k;
    NetBufferRef src;
    NetBufferRef dst;
    if (self->rcv_user.kind != 0) {
        return -4;
    }
    if (self->f204_b6) {
        return -4;
    }
    self->recv_done = callback;
    NetMemcpy(&self->rcv_user, data, sizeof(NetBufferRef));
    self->fEC = len;
    m = 0;
    self->fF0 = m;
    if (self->fD8 == 0) {
        switch (self->t_state) {
        case 0:
        case 5:
        case 7:
        case 8:
        case 10:
            self->rcv_user.kind = m;
            set_slot_state_and_resume__6TLobbyFv(idx, self->recv_done, -7);
            while (self->rcv_user.kind != 0) {
                self->rcv_user.kind = m;
                set_slot_state_and_resume__6TLobbyFv(idx, self->recv_done, -7);
            }
            return 0;
        case -1:
            self->rcv_user.kind = m;
            set_slot_state_and_resume__6TLobbyFv(idx, self->recv_done, -11);
            while (self->rcv_user.kind != 0) {
                self->rcv_user.kind = m;
                set_slot_state_and_resume__6TLobbyFv(idx, self->recv_done, -11);
            }
            return 0;
        default:
            return 0;
        }
    }
    do {
        m = (s32)(self->fD8 > self->fEC ? self->fEC : self->fD8);
        self->fF0 = m;
        NetMemcpy(&src, &self->rcv_buf, sizeof(src));
        TLobby__sub_80406EB8(&src, self->fDC);
        NetMemcpy(&dst, &self->rcv_user, sizeof(dst));
        if (self->fDC + m > self->f534) {
            k = self->f534 - self->fDC;
            TLobby__sub_80406FD8(&dst, &src, k);
            TLobby__sub_80406EB8(&dst, k);
            m -= k;
            self->fD8 -= k;
            self->fDC = 0;
            NetMemcpy(&src, &self->rcv_buf, sizeof(src));
        }
        TLobby__sub_80406FD8(&dst, &src, m);
        self->fD8 -= m;
        self->fDC += m;
        if (self->fDC >= self->f534) {
            self->fDC -= self->f534;
        }
        self->rcv_user.kind = 0;
        set_slot_state_and_resume__6TLobbyFv(idx, self->recv_done, self->fF0);
    } while (self->rcv_user.kind != 0 && self->fD8 != 0);
    if (self->f53C == 0) {
        self->flags &= ~1;
    }
    if (self->t_state != -1 && self->t_state != 0) {
        TLobby__sub_8041A9AC(self);
    }
    if (self->rcv_user.kind != 0) {
        switch (self->t_state) {
        case 0:
        case 5:
        case 7:
        case 8:
        case 10:
            set_slot_state_and_resume__6TLobbyFv(idx, self->recv_done, -7);
            break;
        case -1:
            set_slot_state_and_resume__6TLobbyFv(idx, self->recv_done, -11);
            break;
        default:
            return 0;
        }
    }
    if (self->fD8 == 0 && (self->flags & 8) && !(self->flags & 0x20)) {
        NetDispatchSocketEvent((s16)(self - tcp_protocol_state.tcbs), self->event_ctx, 3, 3);
        self->flags |= 0x20;
    }
    return 0;
}

s32 TLobby__sub_8041F11C(TcpTcb *self) {
    s16 idx = self - tcp_protocol_state.tcbs;
    while (self->rcv_user.kind != 0) {
        self->rcv_user.kind = 0;
        set_slot_state_and_resume__6TLobbyFv(idx, self->recv_done, -7);
    }
    if (self->fD8 == 0 && !(self->flags & 0x20)) {
        NetDispatchSocketEvent((s16)(self - tcp_protocol_state.tcbs), self->event_ctx, 3, 3);
        self->flags |= 0x20;
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
            goto check_pending_receive;
closed_state_receive:
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
check_pending_receive:
            if (control->rcv_user.kind != 0) {
                goto closed_state_receive;
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

}
