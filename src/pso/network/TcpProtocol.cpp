#include "pso/network/UdpRuntime.h"
#include "pso/network/TcpControlBlock.h"
#include "pso/network/SocketEvents.h"
#include "pso/network/NetworkDispatch.h"
#include "pso/misc/TLobby.h"
#include "pso/network/BufferRef.h"
#include "pso/network/IPv6.h"
#include "types.h"
#include "pso/network/BufferPool.h"
#include "pso/protocol/NetworkRuntime.h"
#include "pso/network/EthernetReceiveFilter.h"
#include <stddef.h>
#include "pso/network/IPv6Send.h"
#include "pso/misc/TUdpSocket.h"

struct RecoveredGlobal_8041E178_lbl_805C1D48;
struct O_8041D2B8;
struct E_8041A230;
struct G_8041A230;
struct P_8041D2B8;
typedef TcpControlBlock E_805C1D48;
struct RecoveredGlobal_8041E178_lbl_805C1D48 {
    union { s32 value; E_805C1D48 *p; };
    s16 n;
    u8 remaining[0xA2];
};
struct P_8041D2B8 { s32 a; s32 b; s32 c; s32 d; };
struct O_8041D2B8 { u8 pad0[0x238]; s32 f238; u8 pad23C[0x320 - 0x23C]; s16 n; u8 pad322[0xE]; P_8041D2B8 items[32]; };
struct E_8041A230 {
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
    s16 f4;
    u8 pad6[2];
    s16 f8;
    u8 padA[0x544 - 0xA];
};
struct G_8041A230 {
    E_8041A230 *ents;
    s16 count;
    s16 avail;
    u8 pad8[8];
    s16 h10;
    s16 h12;
    s16 h14;
    u8 pad16[2];
    u8 tick[6];
    s16 h1E;
    s16 h20;
    s16 h22;
    u8 pad24[0x2C];
    u8 b50;
    u8 b51;
    u8 b52;
    u8 b53;
    u8 b54;
    u8 b55;
    u8 b56;
    u8 b57;
    u8 b58;
    u8 b59;
    u8 b5A;
    u8 b5B;
    s16 s5C;
    s16 s5E;
    s16 s60;
    s16 s62;
    s16 s64;
    s16 s66;
    s16 s68;
    s16 s6A;
    s16 s6C;
    s16 s6E;
    s16 s70;
    s16 s72;
    s16 s74;
    u8 pad76[0x2C];
    u8 bA2;
    u8 padA3[5];
};

// These settings were active at this range in the former combined source.
#pragma dont_inline off
#pragma inline_depth(4)

extern "C" {
s16 TLobby__sub_80415954(NetBufferRef *ref, s32 size, s16 owner);
s32 get_adjusted_slot_count__6TLobbyFPv(u8 *arg0);
u8 * TLobby__sub_8041B5C0(void *);
u16 TLobby__sub_8040D8F0(u8 *arg0, u8 *arg1, s8 arg2, u8 *arg3, s16 arg4);
s16 TLobby__sub_8041579C(void *);
s16 TLobby__sub_8040DC8C(u8 *arg0, u8 *arg1);
s32 TLobby__sub_8041A9AC(int);
s32 TLobby__sub_80420BD0(void *, void *, s32);
s32 NetRegisterTimer(s32 period, s16 locked, NetTimerCallback fn);
void TLobby__sub_803F8794(void *);
void set_slot_state_and_resume__6TLobbyFv(s16, s32, s16);
void set_thread_state_and_resume__6TLobbyFv(s16, s32, s16);
s32 TLobby__sub_8041ED8C(int, void *, void *, void *);
void TLobby__sub_8041A5B4(void);
void TLobby__sub_8041A3CC(void);
RecoveredGlobal_8041E178_lbl_805C1D48 tcp_protocol_state;

#pragma push
#pragma opt_common_subs on
s32 NetTCPInit(void) {
    s16 n;
    s16 i;
    E_8041A230 *e;
    ((TLobby *)((u8 *)&tcp_protocol_state))->init_params();
    e = (*(G_8041A230 *)&tcp_protocol_state).ents;
    for (i = 0; i < (n = (*(G_8041A230 *)&tcp_protocol_state).count); i++) {
        e->f8 = -1;
        e->f4 = 0;
        e->c0 = 0x54;
        e->c1 = 0x43;
        e->c2 = 0x42;
        e->c3 = i;
        e++;
    }
    (*(G_8041A230 *)&tcp_protocol_state).avail = n;
    (*(G_8041A230 *)&tcp_protocol_state).h10 = 0;
    NetStoreTick((s32 *)(*(G_8041A230 *)&tcp_protocol_state).tick);
    (*(G_8041A230 *)&tcp_protocol_state).h14 = 0x7FF;
    (*(G_8041A230 *)&tcp_protocol_state).h12 = 0x400;
    (*(G_8041A230 *)&tcp_protocol_state).h22 = 0x3840;
    (*(G_8041A230 *)&tcp_protocol_state).h20 = 0x96;
    (*(G_8041A230 *)&tcp_protocol_state).h1E = 3;
    (*(G_8041A230 *)&tcp_protocol_state).b50 = 0;
    (*(G_8041A230 *)&tcp_protocol_state).b50 |= 1;
    (*(G_8041A230 *)&tcp_protocol_state).bA2 = 2;
    (*(G_8041A230 *)&tcp_protocol_state).b51 = 0x14;
    (*(G_8041A230 *)&tcp_protocol_state).b52 = 0;
    (*(G_8041A230 *)&tcp_protocol_state).b53 = 2;
    (*(G_8041A230 *)&tcp_protocol_state).b54 = 0x12;
    (*(G_8041A230 *)&tcp_protocol_state).b55 = 0x10;
    (*(G_8041A230 *)&tcp_protocol_state).b56 = 0x10;
    (*(G_8041A230 *)&tcp_protocol_state).b57 = 0x11;
    (*(G_8041A230 *)&tcp_protocol_state).b58 = 0x11;
    (*(G_8041A230 *)&tcp_protocol_state).b59 = 0x11;
    (*(G_8041A230 *)&tcp_protocol_state).b5A = 0x10;
    (*(G_8041A230 *)&tcp_protocol_state).b5B = 0x10;
    (*(G_8041A230 *)&tcp_protocol_state).s5C = 1;
    (*(G_8041A230 *)&tcp_protocol_state).s5E = 2;
    (*(G_8041A230 *)&tcp_protocol_state).s60 = 4;
    (*(G_8041A230 *)&tcp_protocol_state).s62 = 8;
    (*(G_8041A230 *)&tcp_protocol_state).s64 = 0x10;
    (*(G_8041A230 *)&tcp_protocol_state).s66 = 0x20;
    (*(G_8041A230 *)&tcp_protocol_state).s68 = 0x40;
    (*(G_8041A230 *)&tcp_protocol_state).s6A = 0x40;
    (*(G_8041A230 *)&tcp_protocol_state).s6C = 0x40;
    (*(G_8041A230 *)&tcp_protocol_state).s6E = 0x40;
    (*(G_8041A230 *)&tcp_protocol_state).s70 = 0x40;
    (*(G_8041A230 *)&tcp_protocol_state).s72 = 0x40;
    (*(G_8041A230 *)&tcp_protocol_state).s74 = 0x40;
    NetRegisterTimer(500, (s16)(1), (NetTimerCallback)(TLobby__sub_8041A5B4));
    NetRegisterTimer(100, (s16)(1), (NetTimerCallback)(TLobby__sub_8041A3CC));
    return 0;
}
#pragma pop

void TLobby::clear_position() {
    u8 *arg0 = (u8 *)this;
    *(s16 *)((s8 *)arg0 + 0x25C) = 0;
    *(s16 *)((s8 *)arg0 + 0x25E) = 0;
    *(s16 *)((s8 *)arg0 + 0x260) = 0;
    *(s16 *)((s8 *)arg0 + 0x262) = 0;
}

struct G_8041A1D8 { u8 pad[4]; s16 n; };
s32 TLobby__sub_8041A1D8(void) {
    NetUnregisterTimer(TLobby__sub_8041A5B4);
    NetUnregisterTimer(TLobby__sub_8041A3CC);
    TLobby__sub_803F8794((void *)&tcp_protocol_state);
    ((G_8041A1D8 *)&tcp_protocol_state)->n = 0;
    return 0;
}

struct Tcb_8041A3CC {
    u8 pad0[4];
    u16 state;
    s16 t_state;
    u8 pad8[3];
    u8 flags;
    u8 force;
    u8 padD[0x1FB];
    u32 snd_una;
    u32 snd_nxt;
    u8 pad210[0x10];
    u32 snd_wnd;
    u8 pad224[4];
    u32 rcv_nxt;
    u8 pad22C[0x10];
    u32 snd_cwnd;
    u32 snd_ssthresh;
    s16 idle;
    s16 rtt;
    u8 pad248[4];
    s16 srtt;
    s16 rttvar;
    u8 pad250[4];
    u16 rxtcur;
    u8 pad256[2];
    u32 rxtshift;
    s16 timers[4];
    u16 maxseg;
    u8 pad266[2];
    u16 f268;
    u16 f26A;
    u8 pad26C[0x10];
    u8 remote[0x14];
    u8 local[0x14];
    u8 pad2A4[0x30];
    s16 f2D4;
    u8 pad2D6[0x16];
    s32 f2EC;
    s32 f2F0;
    u32 f2F4;
    u8 pad2F8[0x240];
    s16 ack_delay;
    u8 pad53A[0xA];
};
struct G_8041A3CC {
    Tcb_8041A3CC *ents;
    s16 count;
    u8 pad6[0x12];
    s32 iss;
    u8 pad1C[4];
    s16 keepintvl;
    s16 keepidle;
    s16 maxidle;
    u8 pad26[0x36];
    s16 backoff[13];
    u8 pad76[0x2A];
    s16 ack_ticks;
};

void TLobby__sub_8041A3CC(void) {
    G_8041A3CC *g = (G_8041A3CC *)&tcp_protocol_state;
    s16 i;
    Tcb_8041A3CC *e;

    e = g->ents;
    for (i = 0; i < g->count; e++, i++) {
        if (e->state != 0 && e->ack_delay != 0) {
            e->ack_delay--;
            if (e->ack_delay == 0) {
                e->ack_delay = g->ack_ticks / 100;
                e->flags |= 1;
                TLobby__sub_8041A9AC((int)e);
            }
        }
    }
}

s32 TLobby__sub_8041A6A4(Tcb_8041A3CC *tcb, s16 timer);

void TLobby__sub_8041A5B4(void) {
    G_8041A3CC *g = (G_8041A3CC *)&tcp_protocol_state;
    Tcb_8041A3CC *e;
    s16 i;
    s16 j;

    i = 0;
    g->maxidle = g->keepintvl << 3;
    e = g->ents;
    for (; i < g->count; e++, i++) {
        if (e->state != 0 && e->state == 1) {
            for (j = 0; j < 4; j++) {
                if (e->timers[j] > 0) {
                    e->timers[j]--;
                    if (e->timers[j] == 0) {
                        TLobby__sub_8041A6A4(e, j);
                    }
                }
            }
            e->idle++;
            if (e->rtt != 0) {
                e->rtt++;
            }
        }
    }
    g->iss += 0xFA00;
}

struct E_8041A498 { u8 pad0[6]; s16 f6; u8 pad8[6]; u8 fE; u8 padF[0x1ED]; s32 f1FC; s32 f200; u8 pad204[0xCC]; s32 f2D0; u8 pad2D4[0x270]; };
void set_slot_state_and_resume__6TLobbyFv(s16, s32, s16);
void set_thread_state_and_resume__6TLobbyFv(s16, s32, s16);
void TLobby__sub_8041A498(E_8041A498 *arg0, s16 arg1) {
    s16 idx = arg0 - (E_8041A498 *)tcp_protocol_state.p;

    if (arg0->f6 >= 3) {
        arg0->f6 = 0;
        TLobby__sub_8041A9AC((int)arg0);
    }
    arg0->fE = arg1;
    switch (arg1) {
    case 4:
        set_thread_state_and_resume__6TLobbyFv(idx, arg0->f1FC, -8);
        set_slot_state_and_resume__6TLobbyFv(idx, arg0->f200, -8);
        NetDispatchSocketEvent(idx, arg0->f2D0, 3, 0xB);
        break;
    default:
        set_thread_state_and_resume__6TLobbyFv(idx, arg0->f1FC, -5);
        set_slot_state_and_resume__6TLobbyFv(idx, arg0->f200, -5);
        NetDispatchSocketEvent(idx, arg0->f2D0, 3, 0xA);
        break;
    }
    if (TLobby__sub_8041B5C0(arg0) != 0) {
        arg0->f6 = -1;
    }
}

struct TcpHeader_8041B3D4 {
    u16 src_port;
    u16 dst_port;
    s32 seq;
    s32 ack;
    u8 data_offset;
    u8 flags;
    u16 window;
    u16 checksum;
    u16 urgent;
};

#pragma push
#pragma opt_common_subs on
s32 TLobby__sub_8041B3D4(u8 *dst, u8 *src, u16 src_port, u16 dst_port, s32 seq, s32 ack, u8 flags) {
    s16 TLobby__sub_8040DA54(u8 *arg0, u8 *arg1);
    s16 dispatch_by_addr_family__6TLobbyFlPUcPUcPUcPvPv(NetPacket *, u8 *, u8 *, u8 *, u8 *, s32);
    TcpHeader_8041B3D4 hdr;
    u8 wire[20];
    u8 opts[16];
    NetPacket *pkt;

    NetMemset(opts, 0, sizeof(opts));
    if (TLobby__sub_8040DA54(dst, src) == 0) {
        return -1;
    }
    hdr.src_port = src_port;
    hdr.dst_port = dst_port;
    hdr.seq = seq;
    hdr.ack = ack;
    hdr.data_offset = 0x50;
    hdr.flags = flags;
    hdr.urgent = 0;
    hdr.checksum = 0;
    hdr.window = 0;
    pkt = (NetPacket *)TLobby::alloc_free_entry();
    if (pkt == NULL) {
        return -0x101;
    }
    pkt->fragment_count = 1;
    pkt->total_bytes = sizeof(wire);
    pkt->fragments[0].length = sizeof(wire);
    NetMemcpy(wire + 0, &hdr.src_port, 2);
    NetMemcpy(wire + 2, &hdr.dst_port, 2);
    NetMemcpy(wire + 4, &hdr.seq, 4);
    NetMemcpy(wire + 8, &hdr.ack, 4);
    NetMemcpy(wire + 12, &hdr.data_offset, 1);
    NetMemcpy(wire + 13, &hdr.flags, 1);
    NetMemcpy(wire + 14, &hdr.window, 2);
    NetMemcpy(wire + 16, &hdr.checksum, 2);
    NetMemcpy(wire + 18, &hdr.urgent, 2);
    ((TLobby *)&pkt->fragments[0].buffer)->set_value_and_enable((s32)wire);
    hdr.checksum = TLobby__sub_8040D8F0(src, dst, 6, (u8 *)pkt, 1);
    NetMemcpy(wire + 16, &hdr.checksum, 2);
    if (dispatch_by_addr_family__6TLobbyFlPUcPUcPUcPvPv(pkt, dst, src, opts + 4, opts + 4, 6) < 0) {
        ((TUdpSocket *)pkt)->release_entry();
        return -1;
    }
    ((TUdpSocket *)pkt)->release_entry();
    return 0;
}
#pragma pop

#pragma push
#pragma opt_common_subs on
s32 TLobby__sub_8041A6A4(Tcb_8041A3CC *tcb, s16 timer) {
    void TLobby__sub_8041B3D4(u8 *, u8 *, u16, u16, u32, u32, s32);
    G_8041A3CC *g = (G_8041A3CC *)&tcp_protocol_state;
    s16 keep;
    s32 win;
    s32 rexmt;
    s32 t;

    switch (timer) {
    case 3:
        if (tcb->t_state != 10 && tcb->idle <= g->maxidle) {
            tcb->timers[3] = g->keepintvl;
        } else {
            TLobby__sub_8041B5C0(tcb);
        }
        break;
    case 0:
        tcb->rxtshift++;
        if (tcb->rxtshift > 12) {
            tcb->rxtshift = 12;
            TLobby__sub_8041A498((E_8041A498 *)tcb, 4);
            break;
        }
        rexmt = (tcb->srtt >> 3) + tcb->rttvar;
        rexmt *= g->backoff[tcb->rxtshift];
        tcb->rxtcur = rexmt;
        if (tcb->rxtcur < 2) {
            tcb->rxtcur = 2;
        } else if (tcb->rxtcur > 128) {
            tcb->rxtcur = 128;
        }
        tcb->timers[0] = tcb->rxtcur;
        if (tcb->rxtshift > 3) {
            tcb->rttvar += tcb->srtt >> 3;
            tcb->srtt = 0;
        }
        ((TLobby *)tcb)->reset_slot_index();
        tcb->f2EC = 0;
        tcb->f2F0 = 0;
        tcb->f2F4 = tcb->snd_una;
        tcb->snd_nxt = tcb->snd_una;
        tcb->rtt = 0;
        win = ((tcb->snd_wnd < tcb->snd_cwnd) ? tcb->snd_wnd : tcb->snd_cwnd) / 2 / tcb->maxseg;
        if (win < 2) {
            win = 2;
        }
        tcb->snd_cwnd = tcb->maxseg;
        tcb->snd_ssthresh = win * tcb->maxseg;
        TLobby__sub_8041A9AC((int)tcb);
        break;
    case 1:
        t = ((tcb->srtt >> 2) + tcb->rttvar) >> 1;
        tcb->timers[1] = t * g->backoff[tcb->rxtshift];
        if (tcb->timers[1] < 10) {
            tcb->timers[1] = 10;
        } else if (tcb->timers[1] > 120) {
            tcb->timers[1] = 120;
        }
        if (tcb->rxtshift < 12) {
            tcb->rxtshift++;
        }
        tcb->force = 1;
        TLobby__sub_8041A9AC((int)tcb);
        tcb->force = 0;
        break;
    case 2:
        if (tcb->t_state < 4) {
            goto drop;
        }
        keep = tcb->f2D4;
        if (keep != 0 && tcb->t_state <= 5) {
            if (tcb->idle >= keep + ((g->maxidle < keep * 8) ? g->maxidle : keep * 8)) {
                goto drop;
            }
            TLobby__sub_8041B3D4(tcb->remote, tcb->local, tcb->f268, tcb->f26A, tcb->snd_una - 1, tcb->rcv_nxt, 16);
            tcb->timers[2] = (g->keepintvl < tcb->f2D4) ? g->keepintvl : tcb->f2D4;
        } else if (keep != 0) {
            tcb->timers[2] = keep;
        } else {
            tcb->timers[2] = g->keepidle;
        }
        break;
    drop:
        TLobby__sub_8041A498((E_8041A498 *)tcb, 4);
        break;
    }
    return 0;
}
#pragma pop

struct Tcb_8041B724 { u8 pad0[0x264]; u16 maxseg; u8 pad266[0x16]; u8 remote[0x14]; u8 local[0x14]; };

s16 TLobby__sub_8041B724(u8 *tcb) {
    Tcb_8041B724 *tp = (Tcb_8041B724 *)tcb;
    s32 mss = TLobby__sub_8040DC8C(tp->remote, tp->local);

    return tp->maxseg < mss ? tp->maxseg : mss;
}

struct Tcb_8041B774 {
    u8 pad0[4];
    u16 state;
    u8 pad6[2];
    s16 listener;
    u8 padA;
    u8 flags;
    u8 padC[0x258];
    u16 maxseg;
    u8 pad266[2];
    u16 lport;
    u16 f26A;
    u8 pad26C[0x10];
    u8 f27C[0x14];
    u8 laddr[0x14];
    u8 pad2A4[0x20];
    s16 f2C4;
    s16 pending;
    u8 pad2C8[8];
    s32 f2D0;
    u8 pad2D4[2];
    u8 f2D6[3];
    u8 pad2D9[3];
    u8 f2DC[0xC];
    u8 f2E8;
    u8 pad2E9[0x247];
    s32 f530;
    s32 f534;
    u8 pad538[4];
    s32 f53C;
    u32 f540;
};

#pragma push
#pragma pool_data off
Tcb_8041B774 *TLobby__sub_8041B774(Tcb_8041B774 *lst, u16 *port, u8 *local, u8 *remote) {
    s16 TLobby__sub_8041E780(void);
    s16 TLobby__sub_8041ECA4(u8 *);
    s16 TLobby__sub_8041EC14(u8 *);
    s16 is_addr_unspecified__6TLobbyFPv(u8 *);
    Tcb_8041B774 *tcb;
    s16 idx;
    s32 mss;
    s16 seg;

    if (lst->f2C4 <= lst->pending) {
        return NULL;
    }
    idx = TLobby__sub_8041E780();
    if (idx < 0) {
        return NULL;
    }
    tcb = (Tcb_8041B774 *)tcp_protocol_state.p;
    tcb += idx;
    tcb->lport = lst->lport;
    if (lst->f26A == 0) {
        tcb->f26A = *port;
    } else {
        tcb->f26A = lst->f26A;
    }
    if (is_addr_unspecified__6TLobbyFPv(lst->f27C)) {
        NetMemcpy(tcb->f27C, local, sizeof(tcb->f27C));
    } else {
        NetMemcpy(tcb->f27C, lst->f27C, sizeof(tcb->f27C));
    }
    NetMemcpy(tcb->laddr, remote, sizeof(tcb->laddr));
    NetMemcpy(tcb->f2D6, lst->f2D6, sizeof(tcb->f2D6));
    NetMemcpy(tcb->f2DC, lst->f2DC, sizeof(tcb->f2DC));
    mss = TLobby__sub_8040DC8C(tcb->f27C, tcb->laddr);
    seg = tcb->maxseg < mss ? tcb->maxseg : mss;
    if (seg < 0) {
        tcb->state = 0;
        return NULL;
    }
    tcb->f530 = lst->f530;
    tcb->f534 = lst->f534;
    if (TLobby__sub_8041ECA4((u8 *)tcb) < 0) {
        tcb->state = 0;
        return NULL;
    }
    if (TLobby__sub_8041EC14((u8 *)tcb) < 0) {
        ((TLobby *)tcb)->close_if_open();
        tcb->state = 0;
        return NULL;
    }
    tcb->f2D0 = lst->f2D0;
    tcb->listener = lst - (Tcb_8041B774 *)tcp_protocol_state.p;
    lst->pending++;
    tcb->f2E8 = lst->f2E8;
    tcb->f53C = lst->f53C;
    tcb->f540 = lst->f540;
    tcb->flags = lst->flags;
    tcb->maxseg = lst->maxseg;
    return tcb;
}
#pragma pop

void TLobby::insert_item_at(s16 idx, s32 a, s32 b) {
    O_8041D2B8 *o = (O_8041D2B8 *)this;
    s16 i;
    if (idx < 0) {
        return;
    }
    s16 n = o->n;
    if (idx > n + 1) {
        return;
    }
    if (idx > 0x1F) {
        return;
    }
    if (n >= 0x1F) {
        o->n = 0x1E;
    }
    for (i = o->n; i >= idx; i--) {
        o->items[i + 1] = o->items[i];
    }
    o->items[idx].a = a;
    o->items[idx].b = b;
    o->items[idx].c = b;
    o->items[idx].d = o->f238;
    o->n++;
}

s32 TLobby__sub_8041D368(u8 *arg0) {
    struct Fields_arg0 { u8 pad_0[800]; s16 field_320; };
    if ((s16) ((Fields_arg0*)arg0)->field_320 == -1) {
        return 1;
    }
    return 0;
}

void TLobby::reset_slot_index() {
    u8 *arg0 = (u8 *)this;
    *(s16 *)((s8 *)arg0 + 0x320) = -1;
    *(s32 *)((s8 *)arg0 + 0x328) = (s32) *(s32 *)((s8 *)arg0 + 0x324);
}

struct Seg_8041D460 { s32 start; s32 end; s32 edge; s32 stamp; };
struct Tcb_8041D460 {
    u8 pad0[0x238];
    s32 now;
    u8 pad23C[0xB0];
    s32 f2EC;
    u8 pad2F0[0x30];
    s16 n;
    u8 pad322[6];
    s32 edge;
    s32 stamp;
    Seg_8041D460 items[32];
};

s32 TLobby__sub_8041D460(Tcb_8041D460 *tp, s32 *start, s32 *end) {
    s16 n = tp->n;
    s16 i;

    if (n == -1) {
        *end = 0;
        *start = 0;
        return 0;
    }
    if (tp->edge - tp->items[0].start < 0) {
        *start = tp->edge;
        *end = tp->items[0].start;
        return *end - *start;
    }
    for (i = 0; i < n; i++) {
        if (tp->items[i].edge - tp->items[i + 1].start < 0) {
            *start = tp->items[i].edge;
            *end = tp->items[i + 1].start;
            return *end - *start;
        }
    }
    *end = 0;
    *start = 0;
    return 0;
}

struct A_8041D524 { u8 pad[0x320]; s16 n; u8 pad2[0xA]; s32 v0; u8 pad3[0xC]; s32 v1; };
s32 TLobby__sub_8041D524(A_8041D524 *a, s32 x) {
    s16 n = a->n;
    s16 i;
    if (n == -1) { return 0; }
    if (a->v0 - x < 0) { return 1; }
    for (i = 0; i < n; i++) {
        if (a->v1 - x < 0) { return 1; }
        a = (A_8041D524 *)((u8 *)a + 0x10);
    }
    return 0;
}

struct Th_8041D584 {
    u8 pad0[8];
    s32 ack;
};

struct Sack_8041D584 {
    s32 start;
    s32 end;
};

struct Tcb_8041D584 {
    u8 pad0[0x238];
    s32 now;
    u8 pad23C[0xB0];
    s32 f2EC;
    u8 pad2F0[0x30];
    s16 n;
    u8 pad322[2];
    s32 una;
    s32 edge;
    s32 stamp;
    Seg_8041D460 items[32];
};

#pragma push
#pragma dont_inline off
#pragma opt_common_subs on
inline void remove_8041D584(Tcb_8041D584 *tcb, s16 idx) {
    s16 n = tcb->n;
    s16 i;
    if (n >= 0 && idx >= 0 && idx <= n) {
        for (i = idx; i < tcb->n; i++) {
            tcb->items[i] = tcb->items[i + 1];
        }
        tcb->n--;
    }
}

void TLobby__sub_8041D584(Tcb_8041D584 *tcb, Th_8041D584 *th, Sack_8041D584 *blocks, s16 n) {
    s16 i;
    s16 j;
    s32 d;

    if (th->ack - tcb->una > 0) {
        for (;;) {
            if (tcb->n < 0) {
                break;
            }
            if (th->ack - tcb->edge > 0) {
                tcb->f2EC -= tcb->edge - tcb->una;
                tcb->edge = th->ack;
                if (tcb->f2EC < 0) {
                    tcb->f2EC = 0;
                }
            } else {
                tcb->f2EC -= th->ack - tcb->una;
                if (tcb->f2EC < 0) {
                    tcb->f2EC = 0;
                }
            }
            if (th->ack - tcb->items[0].end >= 0) {
                tcb->edge = tcb->items[0].edge;
                tcb->stamp = tcb->items[0].stamp;
                tcb->una = tcb->items[0].end;
                remove_8041D584(tcb, 0);
                continue;
            }
            if (th->ack - tcb->items[0].start >= 0) {
                tcb->n = -1;
                tcb->edge = tcb->una;
            }
            break;
        }
        tcb->una = th->ack;
    }

    for (i = 0; i < n; i++) {
        s32 end = blocks[i].end;
        s32 start = blocks[i].start;
        Sack_8041D584 *b = &blocks[i];
        if (start - end >= 0) {
            continue;
        }
        if (tcb->n == -1) {
            tcb->edge = th->ack;
            tcb->stamp = tcb->now;
            ((TLobby *)tcb)->insert_item_at(0, b->start, b->end);
            continue;
        }
        if (end - tcb->una <= 0) {
            continue;
        }
        if (start - tcb->una <= 0) {
            tcb->n = -1;
            tcb->edge = tcb->una;
            continue;
        }
        if (start - tcb->items[0].start <= 0) {
            if (start - tcb->edge < 0) {
                tcb->f2EC -= tcb->edge - start;
                tcb->edge = b->start;
                if (tcb->f2EC < 0) {
                    tcb->f2EC = 0;
                }
            }
            ((TLobby *)tcb)->insert_item_at(0, b->start, b->end);
            j = 0;
        } else {
            for (j = 1; j <= tcb->n; j++) {
                if (b->start - tcb->items[j].start > 0) {
                    continue;
                }
                if (b->start - tcb->items[j - 1].end < 0) {
                    if (b->end - tcb->items[j - 1].end < 0) {
                        continue;
                    }
                    if (end - tcb->items[j - 1].edge > 0) {
                        tcb->f2EC -= tcb->items[j - 1].edge - tcb->items[j - 1].end;
                        tcb->items[j - 1].end = b->end;
                        tcb->items[j - 1].edge = b->end;
                        if (tcb->f2EC < 0) {
                            tcb->f2EC = 0;
                        }
                    } else {
                        tcb->f2EC -= end - tcb->items[j - 1].end;
                        tcb->items[j - 1].end = b->end;
                        if (tcb->f2EC < 0) {
                            tcb->f2EC = 0;
                        }
                    }
                    j = j - 1;
                } else {
                    if (start - tcb->items[j - 1].edge < 0) {
                        tcb->f2EC -= tcb->items[j - 1].edge - start;
                        tcb->items[j - 1].edge = b->start;
                        if (tcb->f2EC < 0) {
                            tcb->f2EC = 0;
                        }
                    }
                    ((TLobby *)tcb)->insert_item_at(j, b->start, b->end);
                }
                break;
            }
            if (j == tcb->n + 1) {
                ((TLobby *)tcb)->insert_item_at(j, b->start, b->end);
                continue;
            }
        }
        while (j + 1 <= tcb->n && tcb->items[j].end - tcb->items[j + 1].start >= 0) {
            d = tcb->items[j].end - tcb->items[j + 1].end;
            if (0 <= d) {
                if (tcb->items[j + 1].edge - tcb->items[j].end > 0) {
                    tcb->f2EC -= d;
                    tcb->items[j].edge = tcb->items[j + 1].edge;
                    remove_8041D584(tcb, j + 1);
                    if (tcb->f2EC < 0) {
                        tcb->f2EC = 0;
                    }
                } else {
                    tcb->f2EC -= tcb->items[j + 1].edge - tcb->items[j + 1].end;
                    remove_8041D584(tcb, j + 1);
                    if (tcb->f2EC < 0) {
                        tcb->f2EC = 0;
                    }
                }
            } else {
                tcb->items[j].end = tcb->items[j + 1].end;
                tcb->items[j].edge = tcb->items[j + 1].edge;
                remove_8041D584(tcb, j + 1);
            }
        }
    }
}
#pragma pop

#pragma push
#pragma pool_data off
s16 TLobby::tcp_get_socket_handle(s16 i) {
    s16 r;
    if (i < 0 || i >= tcp_protocol_state.n) {
        r = -4;
    } else if (tcp_protocol_state.p[i].active != 1) {
        r = -4;
    } else {
        r = 0;
    }
    if (r < 0) { return -4; }
    return tcp_protocol_state.p[i].state;
}
#pragma pop

s32 TLobby__sub_8041ED8C(int, void *, void *, void *);

#pragma push
#pragma opt_propagation off
#pragma push
#pragma pool_data off
s32 TLobby__sub_8041DBD4(s16 arg0, s32 arg1, s32 len, s32 arg3) {
    s16 r;
    E_805C1D48 *e;

    if (arg0 < 0 || arg0 >= tcp_protocol_state.n) {
        r = -4;
    } else if (tcp_protocol_state.p[arg0].active != 1) {
        r = -4;
    } else {
        r = 0;
    }
    if (r < 0) {
        return -4;
    }
    e = tcp_protocol_state.p;
    e += arg0;
    switch (e->state) {
    case 0:
    case 4: case 5: case 6: case 7: case 8: case 9: case 10:
        if ((*(u8 *)((s8 *)e + 0xA) & 4) && (*(u8 *)((s8 *)e + 0xCC) == 0 || (u32)((TLobby *)e)->get_field_d8() == 0)) {
            return -4;
        }
        break;
    }
    return TLobby__sub_8041ED8C((int)e, (void *)arg1, (void *)len, (void *)arg3);
}
#pragma pop

#pragma pop

#pragma push
#pragma opt_propagation off
#pragma push
#pragma pool_data off
s32 tcp_start_send(s16 arg0, u8 *arg1, void (*completion)(s16, s16), u8 arg3) {
    s16 r;
    s16 v;
    s32 ret;
    E_805C1D48 *e;
    if (arg0 < 0 || arg0 >= tcp_protocol_state.n) {
        r = -4;
    } else if (tcp_protocol_state.p[arg0].active != 1) {
        r = -4;
    } else {
        r = 0;
    }
    if (r < 0) {
        return -4;
    }
    e = tcp_protocol_state.p;
    e += arg0;
    v = e->state;
    if (v <= 1) {
        return -4;
    }
    if (v < 4) {
        return -4;
    }
    if (v > 5 && (*(u8 *)((s8 *)e + 0xA) & 8)) {
        return -4;
    }
    TLobby__sub_80420BD0(arg1, e, (s32)completion);
    if (arg3 != 0) {
        *(s32 *)((s8 *)e + 0x210) = *(s32 *)((s8 *)e + 0x20C) + *(s32 *)((s8 *)arg1 + 8);
    }
    ret = ((s32)TLobby__sub_8041A9AC((int)e));
    TLobby__sub_8041FFF8(0, e);
    return ret;
}
#pragma pop

#pragma pop

struct Tcb_8041DE1C {
    u8 pad0[0xB];
    u8 flags;
    u8 padC[0x238];
    s16 f244;
    u8 pad246[0x1A];
    s16 f260;
    u8 pad262[2];
    u16 maxseg;
    u8 pad266[0x6E];
    s16 f2D4;
    u8 pad2D6[0x12];
    u8 f2E8;
    u8 pad2E9[0x247];
    u32 f530;
    u32 f534;
    u8 pad538[4];
    s32 f53C;
    u32 f540;
};

struct G_8041DE1C {
    Tcb_8041DE1C *tcbs;
    s16 count;
    s16 freed;
    u32 f8;
    u32 fC;
};

#pragma push
#pragma pool_data off
s32 TLobby__sub_8041DE1C(s16 i, s16 opt, u32 *val) {
    s16 r;
    G_8041DE1C *g;
    Tcb_8041DE1C *tcb;
    u16 seg;

    if (i < 0 || i >= tcp_protocol_state.n) {
        r = -4;
    } else if (tcp_protocol_state.p[i].active != 1) {
        r = -4;
    } else {
        r = 0;
    }
    if (r < 0) {
        return -4;
    }
    g = (G_8041DE1C *)&tcp_protocol_state;
    tcb = g->tcbs;
    tcb += i;
    switch (opt) {
    case 0x8:
        tcb->f2D4 = *val * 2;
        tcb->f260 = tcb->f2D4;
        tcb->f244 = 0;
        break;
    case 0x1001:
        if (*val > g->f8) {
            return -2;
        }
        tcb->f530 = *val;
        break;
    case 0x1002:
        if (*val > g->fC) {
            return -2;
        }
        tcb->f534 = *val;
        break;
    case 0x2001:
        if (*val != 0) {
            tcb->f53C = 1;
        } else {
            tcb->f53C = 0;
        }
        break;
    case 0x2002:
        if (*val != 0) {
            tcb->f2E8 |= 1;
        } else {
            tcb->f2E8 &= ~1;
        }
        break;
    case 0x2004:
        if (*val > 3) {
            return -2;
        }
        tcb->f540 = *val;
        break;
    case 0x2008:
        if (*val != 0) {
            tcb->flags |= 4;
        } else {
            tcb->flags &= ~4;
        }
        break;
    case 0x2010:
        seg = *val;
        if (seg < 40 || seg > tcb->maxseg) {
            return -2;
        }
        tcb->maxseg = seg;
        break;
    case 0x2020:
        if (*val != 0) {
            tcb->flags |= 0x40;
        } else {
            tcb->flags &= ~0x40;
        }
        break;
    default:
        return -2;
    }
    return 0;
}
#pragma pop

#pragma push
#pragma opt_propagation off
#pragma push
#pragma pool_data off
s32 TLobby::get_tcp_stat(s16 arg0, s16 *arg1, s16 *arg2, s32 *arg3, s32 *arg4) {
    s16 r;
    E_805C1D48 *e;

    if (arg0 < 0 || arg0 >= tcp_protocol_state.n) {
        r = -4;
    } else if (tcp_protocol_state.p[arg0].active != 1) {
        r = -4;
    } else {
        r = 0;
    }
    if (r < 0) {
        return -4;
    }
    e = tcp_protocol_state.p;
    e += arg0;
    if (arg1 != NULL) {
        *arg1 = e->state;
    }
    if (arg2 != NULL) {
        if (e->state == 1) {
            *arg2 = *(s16 *)((s8 *)e + 0x2C6);
        } else {
            *arg2 = 0;
        }
    }
    if (arg3 != NULL) {
        *arg3 = get_adjusted_slot_count__6TLobbyFPv((u8 *)e);
    }
    if (arg4 != NULL) {
        *arg4 = ((TLobby *)e)->get_field_d8();
    }
    return 0;
}
#pragma pop

#pragma pop

typedef char RecoveredGlobal_8041E178_lbl_805C1D48_size[sizeof(RecoveredGlobal_8041E178_lbl_805C1D48) == 0xA8 ? 1 : -1];
#pragma push
#pragma pool_data off
s32 TLobby::mark_connection_closed(s16 arg0) {
    struct Fields_var_r4 { u8 pad_0[4]; u16 field_4; };
    struct Fields_var_r3 { u8 pad_0[6]; s16 field_6; u8 pad_8[3]; u8 field_B; };
    s32 *var_r3;
    s32 *var_r4;
    s16 var_r0;
    s16 var_r5;
    if ((arg0 < 0) || (var_r4 = &tcp_protocol_state.value, var_r4 = &tcp_protocol_state.value, var_r5 = arg0, ((var_r5 < (s16) *(s16 *)((s8 *)(&tcp_protocol_state.value) + 4)) == 0))) {
        var_r0 = -4;
    } else {
        var_r4 = (s32 *)(*(s32 **)((s8 *)(&tcp_protocol_state.value) + 0));
        var_r4 = (s32 *)((u8 *)var_r4 + (var_r5 * 0x544));
        if ((u16) ((Fields_var_r4*)var_r4)->field_4 != 1) {
            var_r0 = -4;
        } else {
            var_r0 = 0;
        }
    }
    if (var_r0 < 0) {
        var_r3 = (s32 *)((u8 *)((s32 *)-4));
        return -4;
    }
    var_r3 = (s32 *)(&tcp_protocol_state.value);
    var_r3 = (s32 *)(&tcp_protocol_state.value);
    var_r3 = (s32 *)(*(s32 **)((s8 *)(&tcp_protocol_state.value) + 0));
    var_r3 = (s32 *)((u8 *)var_r3 + (arg0 * 0x544));
    ((Fields_var_r3*)var_r3)->field_6 = 0;
    ((Fields_var_r3*)var_r3)->field_B = (u8) (((Fields_var_r3*)var_r3)->field_B | 0x80);
    TLobby__sub_8041B5C0(var_r3);
    var_r3 = (s32 *)(NULL);
    return 0;
}
#pragma pop

#pragma push
#pragma opt_propagation off
#pragma push
#pragma pool_data off
s32 TLobby::abort_tcp_connection(s16 arg0) {
    s16 r;
    E_805C1D48 *e;

    if (arg0 < 0 || arg0 >= tcp_protocol_state.n) {
        r = -4;
    } else if (tcp_protocol_state.p[arg0].active != 1) {
        r = -4;
    } else {
        r = 0;
    }
    if (r < 0) {
        return -4;
    }
    e = tcp_protocol_state.p;
    e += arg0;
    if (e->state < 4) {
        e->state = 0;
    } else {
        e->state = 0;
        TLobby__sub_8041A9AC((int)e);
    }
    ((TLobby *)e)->clear_position();
    return 0;
}
#pragma pop

#pragma pop

struct Tcb_8041E2EC { u8 pad0[0x2D6]; u8 f2D6[3]; u8 pad2D9[3]; u8 f2DC[0xC]; u8 pad2E8[0x25C]; };

void TLobby__sub_8041E2EC(s16 idx, u8 *a, u8 *b) {
    Tcb_8041E2EC *e;

    e = (Tcb_8041E2EC *)tcp_protocol_state.p;
    e += idx;
    NetMemcpy(e->f2D6, a, sizeof(e->f2D6));
    NetMemcpy(e->f2DC, b, sizeof(e->f2DC));
}

s16 TLobby__sub_8041B724(u8 *);
u16 TLobby__sub_8041EA14(void);
#pragma push
#pragma opt_propagation off
#pragma push
#pragma pool_data off
s16 TLobby::tcp_connect_start(s16 arg0, s32 arg1, s16 arg2) {
    s16 r;
    E_805C1D48 *e;
    s16 TLobby__sub_8040DA54(u8 *arg0, u8 *arg1);
    s16 is_addr_unspecified__6TLobbyFPv(u8 *arg0);
    s16 select_source_address__6TLobbyFPvPv(void *, void *);
    s16 TLobby__sub_8041A9AC(void *);
    s16 TLobby__sub_8041EC14(u8 *);
    s16 TLobby__sub_8041ECA4(u8 *arg0);
    u16 get_adjusted_slot_count__6TLobbyFPv(u8 *arg0);
    void NetDispatchSocketEvent(s16, s32, s32, s16);

    if (arg0 < 0 || arg0 >= tcp_protocol_state.n) {
        r = -4;
    } else if (tcp_protocol_state.p[arg0].active != 1) {
        r = -4;
    } else {
        r = 0;
    }
    if (r < 0) {
        return -4;
    }
    e = tcp_protocol_state.p;
    e += arg0;
    if (TLobby__sub_8040DA54((u8 *)arg1, (u8 *)e + 0x290) == 0) {
        NetDispatchSocketEvent((s16)(e - tcp_protocol_state.p), *(s32 *)((s8 *)e + 0x2D0), 3, 0xC);
        return -6;
    }
    if (is_addr_unspecified__6TLobbyFPv((u8 *)e + 0x290) != 0 && select_source_address__6TLobbyFPvPv((u8 *)e + 0x290, (void *)arg1) < 0) {
        NetDispatchSocketEvent((s16)(e - tcp_protocol_state.p), *(s32 *)((s8 *)e + 0x2D0), 3, 0xC);
        return -6;
    }
    if (*(u16 *)((s8 *)e + 0x268) == 0) {
        *(u16 *)((s8 *)e + 0x268) = TLobby__sub_8041EA14();
    }
    NetMemcpy((u8 *)e + 0x27C, (void *)arg1, 0x14);
    *(s16 *)((s8 *)e + 0x26A) = arg2;
    if (TLobby__sub_8041B724((u8 *)e) < 0) {
        return -6;
    }
    r = TLobby__sub_8041ECA4((u8 *)e);
    if (r < 0) {
        return r;
    }
    r = TLobby__sub_8041EC14((u8 *)e);
    if (r < 0) {
        ((TLobby *)e)->close_if_open();
        return r;
    }
    *(u32 *)((s8 *)e + 0x23C) = get_adjusted_slot_count__6TLobbyFPv((u8 *)e);
    e->state = 2;
    *(s16 *)((s8 *)e + 0x260) = 0x96;
    {
        s32 *t = (s32 *)((u8 *)&tcp_protocol_state + 0x18);
        s32 v = *t;
        *(s32 *)((s8 *)e + 0x21C) = v;
        *(s32 *)((s8 *)e + 0x324) = v;
        *(s32 *)((s8 *)e + 0x2F4) = v;
        *(s32 *)((s8 *)e + 0x210) = v;
        *(s32 *)((s8 *)e + 0x238) = v;
        *(s32 *)((s8 *)e + 0x20C) = v;
        *(s32 *)((s8 *)e + 0x208) = v;
        *t += 0xFA00;
    }
    return TLobby__sub_8041A9AC(e);
}
#pragma pop

#pragma pop

struct Tcb_8041E590 { u8 pad0[4]; u16 state; s16 f6; s16 listener; u8 padA[0x2BC]; s16 pending; u8 pad2C8[0x27C]; };

s32 TLobby__sub_8041E590(s16 idx) {
    Tcb_8041E590 *ents;
    s16 l;
    Tcb_8041E590 *t;
    Tcb_8041E590 *e;

    ents = (Tcb_8041E590 *)tcp_protocol_state.p;
    e = ents;
    e += idx;
    if ((l = e->listener) >= 0) {
        t = ents;
        t += l;
        if (t->state == 1) {
            t->pending--;
        }
    }
    e->listener = -1;
    return 0;
}

struct Pair_8041E780 {
    s32 a;
    s32 b;
};
struct Tcb_8041E780 {
    u8 tag[3];
    u8 index;
    u16 state;
    s16 f6;
    s16 listener;
    u8 fA;
    u8 flags;
    u8 padC[0x234];
    s32 f240;
    u8 pad244[8];
    s16 f24C;
    s16 f24E;
    u8 pad250[4];
    u16 f254;
    u8 pad256[6];
    s16 timers[4];
    u16 maxseg;
    u16 f266;
    u16 lport;
    u8 pad26A[0x26];
    u8 laddr[0x14];
    u8 pad2A4[0x22];
    s16 pending;
    u8 pad2C8[8];
    s32 f2D0;
    u8 pad2D4[2];
    u8 f2D6[3];
    u8 pad2D9[3];
    u8 f2DC[0xC];
    u8 f2E8;
    u8 pad2E9[0xF];
    Pair_8041E780 f2F8[5];
    s16 f320;
    u8 pad322[0x20E];
    s32 f530;
    s32 f534;
    s16 ack_delay;
    u8 pad53A[2];
    s32 f53C;
    u32 f540;
};
struct G_8041E780 {
    Tcb_8041E780 *tcbs;
    s16 count;
    s16 freed;
    s32 f8;
    s32 fC;
    u16 port;
    u16 port_min;
    u16 port_max;
    u8 pad16[0x10];
    s16 f26;
    u8 pad28[0x28];
    u8 f50;
    u8 pad51[0x51];
    u8 fA2;
};

#pragma push
#pragma pool_data off
s16 TLobby__sub_8041E5E4(s16 h, u8 *addr, u16 port) {
    s16 r;
    s16 i;
    Tcb_8041E780 *e;
    Tcb_8041E780 *tcb;
    s16 is_addr_unspecified__6TLobbyFPv(u8 *arg0);

    if (h < 0 || h >= tcp_protocol_state.n) {
        r = -4;
    } else if (tcp_protocol_state.p[h].active != 1) {
        r = -4;
    } else {
        r = 0;
    }
    if (r < 0) {
        return -4;
    }
    tcb = (Tcb_8041E780 *)tcp_protocol_state.p;
    tcb += h;
    if (tcb->lport != 0) {
        return -3;
    }
    if (NetValidateLocalAddress((NetworkAddress *)addr) < 0) {
        return -6;
    }
    if (port == 0) {
        tcb->lport = TLobby__sub_8041EA14();
    } else {
        e = (Tcb_8041E780 *)tcp_protocol_state.p;
        for (i = 0; i < tcp_protocol_state.n; e++, i++) {
            if (e->state == 0 || e == tcb || e->lport != port) {
                continue;
            }
            if (is_addr_unspecified__6TLobbyFPv(addr) != 0 || is_addr_unspecified__6TLobbyFPv(e->laddr) != 0 ||
                ((TLobby *)e->laddr)->compare_sockaddr(addr) == 0) {
                if (e->f6 == 10 && (e->flags & 0x80)) {
                    TLobby__sub_8041B5C0(e);
                } else {
                    return -3;
                }
            }
        }
        tcb->lport = port;
    }
    NetMemcpy(tcb->laddr, addr, sizeof(tcb->laddr));
    return 0;
}
#pragma pop

void TLobby__sub_8041E8A8(s16 idx);

s16 TLobby__sub_8041E780(void) {
    G_8041E780 *g = (G_8041E780 *)&tcp_protocol_state;
    s16 vidx = 0;
    Tcb_8041E780 *victim = NULL;
    s16 idx;
    s16 n;
    Tcb_8041E780 *tcbs;
    Tcb_8041E780 *t;
    s16 i;

    idx = g->freed;
    n = g->count;
    tcbs = g->tcbs;
    for (i = 0; i < n; i++) {
        idx++;
        if (n <= idx) {
            idx = 0;
        }
        t = tcbs;
        t += idx;
        if (t->state == 0) {
            NetMemset(t, 0, sizeof(Tcb_8041E780));
            TLobby__sub_8041E8A8(idx);
            return idx;
        }
        if (t->f6 == 10 && (t->flags & 0x80)) {
            if (victim != NULL) {
                if (t->timers[3] < victim->timers[3]) {
                    victim = t;
                    vidx = idx;
                }
            } else {
                victim = t;
                vidx = idx;
            }
        }
    }
    if (victim != NULL) {
        TLobby__sub_8041B5C0(victim);
        NetMemset(victim, 0, sizeof(Tcb_8041E780));
        TLobby__sub_8041E8A8(vidx);
        return vidx;
    }
    return -0x103;
}

#pragma push
#pragma pool_data off
void TLobby__sub_8041E8A8(s16 idx) {
    Tcb_8041E780 *t;
    Pair_8041E780 *p;
    s16 i;

    t = ((G_8041E780 *)&tcp_protocol_state)->tcbs;
    t += idx;
    t->tag[0] = 'T';
    t->tag[1] = 'C';
    t->tag[2] = 'B';
    t->index = idx;
    t->state = 1;
    t->f6 = 0;
    t->maxseg = 0x7FFF;
    t->f266 = 0x218;
    t->flags = 0;
    t->fA = 0;
    t->f24C = 0;
    t->f24E = 24;
    t->f254 = 12;
    if (t->f254 < 2) {
        t->f254 = 2;
    } else if (t->f254 > 128) {
        t->f254 = 128;
    }
    t->f240 = 0xFFFF;
    t->listener = -1;
    ((TLobby *)t)->clear_position();
    NetMemset(t->f2D6, 0, sizeof(t->f2D6));
    NetMemset(t->f2DC, 0, sizeof(t->f2DC));
    t->f2E8 = ((G_8041E780 *)&tcp_protocol_state)->f50;
    p = t->f2F8;
    for (i = 0; i < 5; i++, p++) {
        p->b = 0;
        p->a = 0;
    }
    t->f320 = -1;
    t->f530 = ((G_8041E780 *)&tcp_protocol_state)->f8;
    t->f534 = ((G_8041E780 *)&tcp_protocol_state)->fC;
    t->f2D0 = 0;
    t->f53C = ((G_8041E780 *)&tcp_protocol_state)->f26;
    t->ack_delay = 0;
    t->f540 = ((G_8041E780 *)&tcp_protocol_state)->fA2;
}
#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(4)
#pragma pool_data off
inline s16 port_in_use_8041EA14(u16 port) {
    G_8041E780 *g = (G_8041E780 *)&tcp_protocol_state;
    s16 n;
    s16 i;
    Tcb_8041E780 *t;

    t = g->tcbs;
    n = g->count;
    for (i = 0; i < n; i++, t++) {
        if (t->state == 1 && port == t->lport) {
            return 1;
        }
    }
    return 0;
}

u16 TLobby__sub_8041EA14(void) {
    G_8041E780 *g = (G_8041E780 *)&tcp_protocol_state;
    u16 *port = &g->port;
    s32 tick;
    u16 p;

    p = g->port;
    if (p == 0) {
        NetStoreTick(&tick);
        *port = g->port_min;
        *port |= tick & 0x3FF;
    } else if (p < g->port_max) {
        *port = p + 1;
    } else {
        *port = g->port_min;
    }
    while (port_in_use_8041EA14(p = *port) != 0) {
        if (p < ((G_8041E780 *)&tcp_protocol_state)->port_max) {
            (*port)++;
        } else {
            *port = ((G_8041E780 *)&tcp_protocol_state)->port_min;
        }
    }
    return p;
}
#pragma pop

s16 TLobby::validate_tcp_handle(s16 i) {
    if (i < 0 || i >= tcp_protocol_state.n) { return -4; }
    if (tcp_protocol_state.p[i].active != 1) { return -4; }
    return 0;
}

s32 TLobby__sub_8041EB74(u8 *arg0) {
    struct Fields_arg0 { u8 pad_0[204]; u8 field_CC; };
    if ((u8) ((Fields_arg0*)arg0)->field_CC == 0) {
        return -1;
    }
    TLobby__sub_8041579C((void *) (arg0 + 0xD0));
    ((Fields_arg0*)arg0)->field_CC = 0U;
    return 0;
}

s32 TLobby::close_if_open() {
    u8 *arg0 = (u8 *)this;
    if ((u8) *(u8 *)&this->m_down == 0) {
        return -1;
    }
    TLobby__sub_8041579C((void *) (arg0 + 0x18));
    *(u8 *)&this->m_down = 0U;
    return 0;
}

s32 TLobby__sub_8041EC14(u8 *arg0) {
    s32 spC[3];

    if ((u8) *(u8 *)((s8 *)arg0 + 0xCC) == 0) {
        if (TLobby__sub_80415954((NetBufferRef *) (&spC[0]), (int) (*(s32 *)((s8 *)arg0 + 0x534)), 1) < 0) {
            return -0x102;
        }
        ((TLobby *)(arg0 + 0xD0))->init_msg(spC[0]);
        ((TLobby *)(arg0 + 0xC8))->set_value_and_enable(spC[0]);
        goto block_4;
    }
block_4:
    *(s32 *)((s8 *)arg0 + 0xD8) = 0;
    *(s32 *)((s8 *)arg0 + 0xDC) = 0;
    *(s32 *)((s8 *)arg0 + 0xE0) = 0;
    *(s32 *)((s8 *)arg0 + 0xF4) = 0;
    *(s16 *)((s8 *)arg0 + 0xF8) = -1;
    *(s16 *)((s8 *)arg0 + 0xFA) = -1;
    return 0;
}

s32 TLobby__sub_8041ECA4(u8 *arg0) {
  unsigned char new_var;
  s32 spC;
  if (((u8) (*((u8 *) (((s8 *) arg0) + 0x14)))) == 0)
  {
    if (TLobby__sub_80415954((NetBufferRef *) (&spC), (int) (*((s32 *) (((s8 *) arg0) + 0x530))), 1) < 0)
    {
      return -0x102;
    }
    ((TLobby *)(((u8 *) arg0) + 0x18))->init_msg((s32)((int) spC));
    ((TLobby *)(((u8 *) arg0) + 0x10))->set_value_and_enable((s32)((int) spC));
    goto block_4;
  }
  block_4:
  *((s32 *) (((s8 *) arg0) + 0x20)) = 0;
  new_var = 0x24;
  *((s32 *) (((s8 *) arg0) + new_var)) = 0;
  *((s32 *) (((s8 *) arg0) + 0x28)) = 0;
  return 0;
}

s32 TLobby::get_field_534() {
    u8 *arg0 = (u8 *)this;
    return *(s32 *)((s8 *)arg0 + 0x534);
}

s32 TLobby::get_field_d8() {
    u8 *arg0 = (u8 *)this;
    return *(s32 *)((s8 *)arg0 + 0xD8);
}

s32 TLobby::get_score() {
    u8 *arg0 = (u8 *)this;
    if (((u8) *(u8 *)((s8 *)arg0 + 0x204) >> 7U) & 1) {
        return *(s32 *)((s8 *)arg0 + 0x34);
    }
    return *(s32 *)((s8 *)arg0 + 0x20) + *(s32 *)((s8 *)arg0 + 0x34);
}

s32 TLobby::get_queue_diff() {
    u8 *arg0 = (u8 *)this;
    return *(s32 *)((s8 *)arg0 + 0x534) - *(s32 *)((s8 *)arg0 + 0xD8);
}

s32 get_adjusted_slot_count__6TLobbyFPv(u8 *arg0) {
    if (((u8) *(u8 *)((s8 *)arg0 + 0x204) >> 7U) & 1) {
        return *(s32 *)((s8 *)arg0 + 0x530);
    }
    return *(s32 *)((s8 *)arg0 + 0x530) - *(s32 *)((s8 *)arg0 + 0x20);
}


}
