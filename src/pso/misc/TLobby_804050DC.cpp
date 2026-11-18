#include "pso/protocol/PppControlRuntime.h"
#include "pso/network/UdpRuntime.h"
#include "pso/network/NetworkRequestRuntime.h"
#include "pso/network/NetworkRecordConfig.h"
#include "pso/network/IPv6Send.h"
#include "pso/network/BufferRef.h"
#include "pso/misc/LobbyNetworkInternal.h"

extern "C" {
#undef lbl_805C1AD8
u32 lbl_805C1AD8[6];
#define lbl_805C1AD8 (*(Tbl_80408F2C *)lbl_805C1AD8)

void TLobby__sub_804050DC(s16 arg0) {
    *(s16 *)((s8 *)(&lbl_805C18A0.value) + 8) = arg0;
}

void TLobby::init_net_block_18A0() {
    TLobby__sub_803F79AC((void *) (&(*(RecoveredGlobal_804050EC_lbl_805C18A0 *)&lbl_805C18A0).value));
}

s32 TLobby::run_net_init_step() {
    TLobby__sub_803F79B0((u8 *)(&(*(RecoveredGlobal_80405114_lbl_805C18A0 *)&lbl_805C18A0).value));
    return 0;
}

s16 reset_network_timer_list(void) {
    lobby_timer_list_head = 0;
    return 0;
}

void TLobby::run_net_thread_loop() {
    G_80405150 *g = (G_80405150 *)&lbl_805C18A0;
    for (;;) {
        if (lbl_805D7A86 != 0) {
            TLobby::lock_mutex(g->p0);
            TLobby__sub_803FB6A0();
            TUdpSocket::unlock_mutex(g->p0);
            continue;
        }
        if (lbl_805D7A88 != 0) {
            TLobby::lock_mutex(g->p0);
            TLobby__sub_803FB7A4();
            TUdpSocket::unlock_mutex(g->p0);
            continue;
        }
        TLobby__sub_803F97E8(g->h8);
        if (lbl_805D7A84 != 0) {
            TLobby::process_expired_timers();
        }
    }
}

void TLobby::process_expired_timers() {
    s32 now;
    Timer_804051CC *t;

    TLobby::lock_mutex(lbl_805C18A0.value);
    TLobby__sub_80405700();
    TLobby::get_time_ms(&now);
    t = (Timer_804051CC *)lobby_timer_list_head;
    while (t != NULL) {
        if (t->f18 == 1 && (u32)(now - t->fC) > t->f8) {
            if (t != NULL && t->f18 == 1) {
                t->f18 = 0;
            }
            t->f18 = 2;
            if (t->f10 != NULL) {
                t->f18 = 0;
                t->f10(t->f14);
            }
        }
        t = t->next;
    }
    TUdpSocket::unlock_mutex(lbl_805C18A0.value);
}

void TLobby__sub_80405298(N_80405298 *o, s32 v) {
    N_80405298 *p, *n;
    if (o == 0) {
        return;
    }
    o->f4 = v;
    if (HEAD_80405298 == 0) {
        HEAD_80405298 = o;
        o->next = 0;
    } else {
        p = HEAD_80405298;
        while ((n = p->next) != 0) {
            if (p == o) {
                o->b18 = 0;
                return;
            }
            p = n;
        }
        p->next = o;
        o->next = 0;
    }
    o->b18 = 0;
}

s32 TLobby__sub_80405304(void *arg0) {
    Obj_80405304 *o = (Obj_80405304 *)arg0;
    if (o == NULL || o->f18 != 1) {
        return;
    }
    o->f18 = 0;
}

void TLobby__sub_80405328(u8 *arg0) {
    struct Fields_arg0 { u8 pad_0[4]; u32 field_4; u32 field_8; u8 pad_C[4]; u32 field_10; u8 pad_14[4]; u8 field_18; };
    u32 temp_r0_2;
    u8 temp_r0;
    if (arg0 != NULL) {
        temp_r0 = ((Fields_arg0*)arg0)->field_18;
        if ((temp_r0 == 1) && (arg0 != NULL) && (temp_r0 == 1)) {
            ((Fields_arg0*)arg0)->field_18 = 0U;
        }
        temp_r0_2 = ((Fields_arg0*)arg0)->field_4;
        if (temp_r0_2 != 0U) {
            ((Fields_arg0*)arg0)->field_8 = temp_r0_2;
            if ((u32) ((Fields_arg0*)arg0)->field_8 == 0U) {
                ((Fields_arg0*)arg0)->field_8 = 1U;
            }
            TLobby::get_time_ms((s32 *)((void *) (arg0 + 0xC)));
            if ((u32) ((Fields_arg0*)arg0)->field_10 != 0U) {
                ((Fields_arg0*)arg0)->field_18 = 1U;
            }
        }
    }
}

extern s32 TLobby__sub_804053B8(void *self, u8 **pp)
{
  struct Hdr_804053B8
  {
    u16 h0;
    u16 h2;
    u32 h4;
    u32 h8;
    u8 hc;
    u8 hd;
    u16 he;
    u16 h10;
    u16 h12;
  } hdr;
  u8 *b = (u8 *) self;
  u8 *p;
  u16 size;
  u16 rem;
  u8 flags;
  u8 cb;
  u32 pad;
  s32 ret;
  u8 c;
  u32 n;
  ret = TLobby__sub_80401BCC(pp, &hdr, 0x14);
  (void) (&pad);
  *((u16 *) b) = hdr.h0;
  *((u16 *) (b + 0x2)) = hdr.h2;
  *((u32 *) (b + 0x4)) = hdr.h4;
  *((u32 *) (b + 0x8)) = hdr.h8;
  flags = hdr.hd;
  cb = hdr.hc;
  b[0x15] = flags & 0x20;
  b[0x16] = flags & 0x10;
  b[0x17] = flags & 0x8;
  b[0x18] = flags & 0x4;
  b[0x19] = flags & 0x2;
  b[0x1a] = flags & 0x1;
  cb = (cb & 0xf0) >> 2;
  *((u16 *) (b + 0xc)) = hdr.he;
  *((u16 *) (b + 0xe)) = hdr.h10;
  *((u16 *) (b + 0x10)) = hdr.h12;
  *((u16 *) (b + 0x12)) = 0;
  b[0x1b] = cb - 0x14;
  if ((((u16) ret) < 0x14) || (0x14 > cb))
  {
    return 0;
  }
  if (b[0x1b] == 0)
  {
    return cb;
  }
  if (b[0x1b] > (u16)buffer_length((B_803FADA0 *)*pp))
  {
    return 0;
  }
  TLobby__sub_80401BCC(pp, b + 0x1c, b[0x1b]);
  rem = b[0x1b];
  p = b + 0x1c;
  while (rem != 0)
  {
    c = p[0];
    if (c == 0)
    {
      break;
    }
    if (c == 1)
    {
      size = 1;
    }
    else
    {
      n = p[1];
      size = n;
      if (n == 0)
        break;
    }
    switch (c)
    {
      case 2:
        if (size == 4)
      {
        *((u16 *) (b + 0x12)) = (p[2] << 8) | p[3];
      }
        break;

    }

    rem -= size;
    p += size;
  }

  return cb;
}

extern u8 *TLobby__sub_8040555C(u8 *self, void *lobby, u8 *obj) {
    u8 hdr[0x3c];
    u32 n = 0;
    u8 *buf;
    u8 *hp;
    u8 *dst;
    u8 flags;
    u32 len;

    if (self[0x1b] != 0 && self[0x1b] <= 0x28) {
        n = self[0x1b];
    } else if (*(u16 *)(self + 0x12) != 0) {
        n = 4;
    }
    buf = (u8 *)alloc_from_buffer((B_803FADA0 *)lobby, n + 0x14);
    if (buf == NULL) {
        return NULL;
    }
    dst = *(u8 **)buf;
    hp = hdr;
    flags = 0;
    *(u16 *)(hp + 0) = *(u16 *)(self + 0);
    *(u16 *)(hp + 2) = *(u16 *)(self + 2);
    *(u32 *)(hp + 4) = *(u32 *)(self + 4);
    *(u32 *)(hp + 8) = *(u32 *)(self + 8);
    hp[0xc] = (u8)((n + 0x14) << 2);
    if (self[0x15]) {
        flags |= 0x20;
    }
    if (self[0x16]) {
        flags |= 0x10;
    }
    if (self[0x17]) {
        flags |= 0x8;
    }
    if (self[0x18]) {
        flags |= 0x4;
    }
    if (self[0x19]) {
        flags |= 0x2;
    }
    if (self[0x1a]) {
        flags |= 0x1;
    }
    hp[0xd] = flags;
    *(u16 *)(hp + 0xe) = *(u16 *)(self + 0xc);
    if (obj == NULL) {
        *(u16 *)(hp + 0x10) = *(u16 *)(self + 0xe);
    } else {
        *(u16 *)(hp + 0x10) = 0;
    }
    *(u16 *)(hp + 0x12) = *(u16 *)(self + 0x10);
    len = 0;
    if ((u16)n > len) {
        NetMemcpy(hp + 0x14, self + 0x1c, self[0x1b]);
    }
    len = (u16)(n + 0x14);
    NetMemcpy(dst, hp, len);
    if (obj != NULL) {
        *(u16 *)(hp + 0x10) = TLobby__sub_803FE934(obj, (B_803FADA0 *)buf, *(u16 *)(obj + 0xa));
    }
    NetMemcpy(dst, hp, len);
    return buf;
}

#pragma opt_common_subs on
#pragma opt_loop_invariants off
inline s32 TLobby__sub_80405700_impl(u8 &c)
{
  u16 st;
  Strm_80405A74 *frame;
  u32 b;
  u16 id;
  Strm_80405A74 **new_var;
  u16 n;
  RecoveredGlobal_80401A68_lbl_805C04A8 *base;
  u8 *buf = lbl_805C18B0;
  if (lbl_805D7A8A == 10)
  {
    if (TLobby__sub_804290D4(0x7fff) == 0)
    {
      lbl_805D7A8A = 1;
    }
    return 0;
  }
  if (lbl_805D7A7A != 0)
  {
    base = &lbl_805C04A8;
    for (;;)
    {
      new_var = &base->frame_in;
      ppp_rx_frame_ptr = (frame = *new_var);
      ppp_rx_frame_ptr->buf = ((u8 *) frame) + ((base->value + 0x83) & (~3));
      ppp_rx_frame_ptr->len = 0;
      if ((TLobby__sub_803F812C(0x5d6, ppp_rx_frame_ptr->buf, &ppp_rx_frame_ptr->len) != 0) || (ppp_rx_frame_ptr->len < 1))
      {
        break;
      }
      TLobby::get_time_ms(&lbl_805D7A94);
      frame = ppp_rx_frame_ptr;
      b = (frame->buf[0] & 0xFFFFFFFFFFFFFFFFu);
      id = b;
      if (!(b & 1))
      {
        id = (b << 8) | frame->buf[1];
      }
      ppp_input_packet__6TLobbyFPv(frame);
      if (((id != 0x21) && (id != 0x2d)) && (id != 0x2f))
      {
        break;
      }
    }

    if ((lbl_805D7A8A == 4) && ((u16)TLobby__sub_803F8090() == 0))
    {
      lbl_805D7A8A = 5;
    }
    return 0;
  }
  if (lbl_805D7ADC == 0)
  {
    lbl_805D7ADC = buf;
    ppp_rx_frame_ptr = 0;
    lbl_805D7AE8 = 0xffff;
    lbl_805D7AE4 = 0;
    lbl_805D7AE0 = buf;
  }
  base = &lbl_805C04A8;
  for (;;)
  {
    if (lbl_805D7ADC == lbl_805D7AE0)
    {
      if ((TLobby__sub_803F812C(0x200, buf, &st) != 0) || (st < 1))
      {
        goto tail;
      }
      lbl_805D7ADC = buf;
      lbl_805D7AE0 = buf + st;
    }
    c = *(lbl_805D7ADC++);
    if (c == 0x7e)
    {
      if (((ppp_rx_frame_ptr != 0) && (ppp_rx_frame_ptr->len < 0x800)) && (lbl_805D7AE8 == 0xf0b8))
      {
        n = buffer_length((B_803FADA0 *)ppp_rx_frame_ptr) - 2;
        TLobby__sub_80401CAC((Outer_80401CAC *)&ppp_rx_frame_ptr, n);
        TLobby::get_time_ms(&lbl_805D7A94);
        ppp_input_packet__6TLobbyFPv(ppp_rx_frame_ptr);
        ppp_rx_frame_ptr = 0;
        return 1;
      }
      ppp_rx_frame_ptr = 0;
      continue;
    }
    if ((c == 0x7d) != 0U)
    {
      lbl_805D7AE4 |= 1;
      continue;
    }
    if (ppp_rx_frame_ptr == 0)
    {
      ppp_rx_frame_ptr = (frame = base->frame_in);
      ppp_rx_frame_ptr->buf = ((u8 *) frame) + ((base->value + 0x83) & (~3));
      ppp_rx_frame_ptr->len = 0;
      lbl_805D7AE4 = 0;
      lbl_805D7AE8 = 0xffff;
    }
    if (lbl_805D7AE4 & 1)
    {
      lbl_805D7AE4 &= ~1;
      c ^= 0x20;
    }
    if (ppp_rx_frame_ptr->len >= 0x800)
    {
      continue;
    }
    ppp_rx_frame_ptr->buf[ppp_rx_frame_ptr->len++] = c;
    lbl_805D7AE8 = (lbl_805D7AE8 >> 8) ^ lbl_804FD3A8[(lbl_805D7AE8 ^ c) & 0xff];
  }

  tail:
  if ((((u16) (lbl_805D7A8A - 3)) <= 1) && ((u16)TLobby__sub_803F8090() == 0))
  {
    if ((((u32) lbl_805D7A8C) != 0) && (lbl_805D7A8A == 4))
    {
      TUdpSocket::unlock_mutex(lbl_805C18A0.value);
      ((void (*)(s32, s32)) lbl_805D7A8C)(-1, 0);
      TLobby::lock_mutex(lbl_805C18A0.value);
    }
    lbl_805D7A8A = 5;
  }

  return 0;
}
s32 TLobby__sub_80405700() { u8 c; return TLobby__sub_80405700_impl(c); }

#pragma opt_common_subs reset
#pragma opt_loop_invariants reset
void ppp_input_packet__6TLobbyFPv(Strm_80405A74 *arg0) {
    u16 code;
    u8 *G;
    Strm_80405A74 *t;
    u8 *p;
    Strm_80405A74 *u;
    u8 pad[0x24];
    if (arg0 == NULL) {
        return;
    }
    G = lbl_805C0038;
    if (lbl_805D7A7A == 0 && arg0->buf[0] == 0xFF && arg0->buf[1] == 3 &&
        TLobby__sub_80401BCC(&arg0, &lobby_ppp_read_buf, 2) == 2) {
        read_network_u16_be(&lobby_ppp_read_buf);
    }
    code = (u16)get_80405A74(&arg0);
    if (!(code & 1)) {
        code = (code << 8) | get_80405A74(&arg0);
    }
    switch (code) {
    case 0x21:
        if (*(u8 *)((s8 *)G + 0x6C) != 5) {
            (*(s16 *)((s8 *)G + 0x140))++;
            return;
        }
        TLobby__sub_804060B8(arg0->buf, arg0->len, 0x800);
        return;
    case 0x57:
        if (*(u8 *)((s8 *)G + 0xD4) != 5) {
            (*(s16 *)((s8 *)G + 0x140))++;
            return;
        }
        TLobby__sub_804060B8(arg0->buf, arg0->len, -0x7923);
        return;
    case 0x2D:
        if (*(u8 *)((s8 *)G + 0x6C) != 5) {
            (*(s16 *)((s8 *)G + 0x140))++;
            return;
        }
        if (!(*(s16 *)((s8 *)(*(u8 **)((s8 *)G + 0x9C)) + 0x28) & 4)) {
            (*(s16 *)((s8 *)G + 0x140))++;
            return;
        }
        if (TLobby__sub_804040E0(*(void **)((s8 *)(*(u8 **)((s8 *)G + 0x9C)) + 0x98), &arg0) <= 0) {
            (*(s16 *)((s8 *)G + 0x140))++;
            return;
        }
        TLobby__sub_804060B8(arg0->buf, arg0->len, 0x800);
        return;
    case 0x2F:
        if (*(u8 *)((s8 *)G + 0x6C) != 5) {
            (*(s16 *)((s8 *)G + 0x140))++;
            return;
        }
        if (!(*(s16 *)((s8 *)(*(u8 **)((s8 *)G + 0x9C)) + 0x28) & 4)) {
            (*(s16 *)((s8 *)G + 0x140))++;
            return;
        }
        if (TLobby__sub_80403F4C(*(void **)((s8 *)(*(u8 **)((s8 *)G + 0x9C)) + 0x98), &arg0) <= 0) {
            (*(s16 *)((s8 *)G + 0x140))++;
            return;
        }
        TLobby__sub_804060B8(arg0->buf, arg0->len, 0x800);
        return;
    case 0xC021:
        (*(s16 *)((s8 *)G + 0x130))++;
        TLobby__sub_803FDBF8((Fsm_803FDBF8 *)(G + 4), arg0);
        return;
    case 0xC023:
        if (G[0] != 2 && G[0] != 3) {
            (*(s16 *)((s8 *)G + 0x140))++;
            if (G[0] == 0) {
                TLobby__sub_8040098C(G + 4);
            }
            return;
        }
        (*(s16 *)((s8 *)G + 0x132))++;
        NetPapDispatch((Conn_804004DC *)(G + 0x38), arg0);
        return;
    case 0xC223:
        if (G[0] != 2 && G[0] != 3) {
            (*(s16 *)((s8 *)G + 0x140))++;
            if (G[0] == 0) {
                TLobby__sub_8040098C(G + 4);
            }
            return;
        }
        (*(s16 *)((s8 *)G + 0x136))++;
        NetChapDispatch((Conn_804004DC *)(G + 0xA0), (B_803FADA0 *)(arg0));
        return;
    case 0x8021:
        if (G[0] != 3) {
            (*(s16 *)((s8 *)G + 0x140))++;
            return;
        }
        (*(s16 *)((s8 *)G + 0x134))++;
        TLobby__sub_803FDBF8((Fsm_803FDBF8 *)(G + 0x6C), arg0);
        return;
    case 0x8057:
        if (G[0] != 3) {
            (*(s16 *)((s8 *)G + 0x140))++;
            return;
        }
        if (lbl_805D7A7C != 6 && (s16)(s32)lbl_805D7A7C) {
            FWD_80405A74()
        }
        (*(s16 *)((s8 *)G + 0x138))++;
        TLobby__sub_803FDBF8((Fsm_803FDBF8 *)(G + 0xD4), arg0);
        return;
    default:
        FWD_80405A74()
    }
}

#pragma opt_common_subs on
s32 TLobby__sub_804060B8(u8 *data, s32 len, int type) {
    s16 slot;
    s16 i;
    s16 j;
    u8 *buf;
    s16 *used;
    s16 n;

    for (i = 0; i < 2; i++) {
        if (lobby_net_buffer_desc_b.slots[i].active != 0 && lobby_net_buffer_desc_b.slots[i].type == (u16)type) {
            slot = i;
            break;
        }
    }
    if (i >= 2) {
        return 0;
    }
    used = lobby_net_buffer_desc_b.used;
    buf = lobby_net_buffer_desc_b.bufs;
    for (j = 0; j < lobby_net_buffer_desc_b.count; j++, used++) {
        if (*used == 0) {
            *used = 1;
            n = (s16)len < lobby_net_buffer_desc_b.size ? (s16)len : lobby_net_buffer_desc_b.size;
            NetMemcpy(buf, data, n);
            TLobby__sub_80409818((s32)buf, n, lobby_net_buffer_desc_b.handler, slot, lobby_net_buffer_desc_b.slots[slot].type);
            return 0;
        }
        buf += lobby_net_buffer_desc_b.size;
    }
    return 0;
}

#pragma opt_common_subs reset
s32 TLobby__sub_804061FC(s32 arg0) {
    Lobby_804062A0 *conn;
    (void)arg0;

    lbl_805D7ADC = 0;
    conn = (Lobby_804062A0 *)lbl_805C0038;
    NetMemset(lbl_805C0038, 0, sizeof(Lobby_804062A0));
    ((Lobby_804062A0 *)lbl_805C0038)->state = 0;
    TLobby__sub_8040059C((u8 *)conn);
    TLobby__sub_80402CE0((u8 *)conn);
    TLobby__sub_803FC318((u8 *)conn);
    TLobby__sub_803FEF4C((u8 *)conn);
    TLobby__sub_803F9FAC((u8 *)conn);
    open_conn_804062A0();
    return 0;
}

s32 TLobby__sub_804062A0(s16 arg0) {
    Lobby_804062A0 *l = (Lobby_804062A0 *)lbl_805C0038;

    switch (arg0) {
    case 0x82:
        if (l->state == 0) {
            l->state = 1;
        }
        TLobby__sub_803FD958(l->sub);
        return 0;
    case 0x81:
        TLobby__sub_803FD85C(l->sub);
        l->state = 0;
        return 0;
    default:
        return -1;
    }
}

struct PppFrameWriter {
    B_803FADA0 *frame;
    u8 *cursor;
    u16 protocol;
};

inline void begin_ppp_frame(PppFrameWriter &writer, B_803FADA0 *source) {
    writer.frame = alloc_from_buffer(source, 4);
    writer.cursor = writer.frame->buf;
}

s16 TLobby__sub_80406328(s32 self, s16 type) {
    Strm_80405A74 *sv = (Strm_80405A74 *)self;
    void *me = (void *)self;
    s32 ty = type;
    PppLinkState *G;
    u8 *p;
    s16 tag = 0x21;
    if (ty == -0x7923) {
        G = (PppLinkState *)lbl_805C0038;
        if (G->ipv6cp.state != 5) {
            G->transmit_errors++;
            return -1;
        }
        if (G->active == 0) {
            G->transmit_errors++;
            return -1;
        }
        PppFrameWriter writer;
        writer.protocol = 0x57;
        begin_ppp_frame(writer, (B_803FADA0 *)me);
        p = writer.cursor;
        *p++ = 0xff;
        *p++ = 3;
        write_network_u16_be(p, writer.protocol);
        if (writer.frame == NULL) {
            G->allocation_errors++;
            return -1;
        }
        return TLobby__sub_804066D8((Strm_80405A74 *)writer.frame);
    }
    G = (PppLinkState *)lbl_805C0038;
    if (G->ipcp.state != 5) {
        G->transmit_errors++;
        return -1;
    }
    if (ty == 0x86dd) {
        if (G->active == 0) {
            G->transmit_errors++;
            return -1;
        }
        PppFrameWriter writer;
        writer.protocol = 0x57;
        begin_ppp_frame(writer, (B_803FADA0 *)me);
        p = writer.cursor;
        *p++ = 0xff;
        *p++ = 3;
        write_network_u16_be(p, writer.protocol);
        if (writer.frame == NULL) {
            G->allocation_errors++;
            return -1;
        }
        return TLobby__sub_804066D8((Strm_80405A74 *)writer.frame);
    }
    {
        IpcpConfigureOptions *e = (IpcpConfigureOptions *)G->ipcp.opts;
        if (lbl_805D7A90 & 2) {
            s16 r;
            if (!(e->sides[0].agreed.mask & 4)) goto skip;
            r = TLobby__sub_804048E8(e->compression_state, &sv, e->sides[1].agreed.slot_id);
            switch (r) {
            case 0x40: tag = 0x21; break;
            case 0x80: tag = 0x2d; break;
            case 0x70: tag = 0x2f; break;
            default:
                G->transmit_errors++;
                return -1;
            }
        } else {
            s16 r;
            if (!(e->sides[1].agreed.mask & 4)) goto skip;
            r = TLobby__sub_804048E8(e->compression_state, &sv, e->sides[1].agreed.slot_id);
            switch (r) {
            case 0x40: tag = 0x21; break;
            case 0x80: tag = 0x2d; break;
            case 0x70: tag = 0x2f; break;
            default:
                G->transmit_errors++;
                return -1;
            }
        }
    }
skip:
    {
        void *a = (void *)sv;
        G = (PppLinkState *)lbl_805C0038;
        if (G->active == 0) {
            G->transmit_errors++;
            return -1;
        }
        {
            PppFrameWriter writer;
            writer.protocol = tag;
            begin_ppp_frame(writer, (B_803FADA0 *)a);
            p = writer.cursor;
            *p++ = 0xff;
            *p++ = 3;
            write_network_u16_be(p, writer.protocol);
            if (writer.frame == NULL) {
                G->allocation_errors++;
                return -1;
            }
            return TLobby__sub_804066D8((Strm_80405A74 *)writer.frame);
        }
    }
}

s16 TLobby__sub_80406624(s32 a, s32 b, u16 code, void *self) {
    B_803FADA0 *prepared;

    PppLinkState *link = (PppLinkState *)lbl_805C0038;
    if (link->active == 0) {
        link->transmit_errors++;
        return -1;
    }
    PppFrameWriter writer;
    writer.protocol = code;
    begin_ppp_frame(writer, (B_803FADA0 *)self);
    *writer.cursor++ = 0xff;
    *writer.cursor++ = 3;
    write_network_u16_be(writer.cursor, writer.protocol);
    prepared = writer.frame;
    if (writer.frame == 0) {
        link->allocation_errors++;
        return -1;
    }
    return TLobby__sub_804066D8((Strm_80405A74 *)prepared);
}

inline s32 ppp_keep_field(s32 is_lcp, LcpOpts *opts, s32 opt) {
    s32 r = 1;
    if (!is_lcp && (opts->remote.got.mask & opt)) {
        r = 0;
    }
    return r;
}

inline s32 ppp_protocol_field_is_two_bytes(s32 is_lcp, LcpOpts *opts, u16 proto) {
    s32 r = 1;
    if (ppp_keep_field(is_lcp, opts, LCP_OPT_PFC) == 0 && proto < 0xff) {
        r = 0;
    }
    return r;
}

inline void ppp_update_send_timestamp() {
    TLobby::get_time_ms(&lbl_805D7A94);
}

#pragma push
#pragma opt_propagation off
#pragma cplusplus off
s16 TLobby__sub_804066D8(Strm_80405A74 *p) {
    Strm_80405A74 *frame;
    u8 *out;
    u8 *hdr;
    struct LcpOpts *opts;
    RecoveredGlobal_80401A68_lbl_805C04A8 *bufs;
    u16 fcs;
    s32 crc = 0xffff;
    u8 *src;
    u8 ctrl;
    u8 addr;
    s32 two;
    s32 is_lcp;
    s16 state;
    u32 accm = -1;
    s32 n = 4;
    struct PppLinkState *ppp;
    s32 sz;
    u16 proto;
    s32 c;
    s32 pfc;
    s32 skip;
    s32 acfc;

    ppp = (struct PppLinkState *)lbl_805C0038;
    opts = (struct LcpOpts *)ppp->lcp.opts;
    ppp->transmit_bytes += ((u16)buffer_length((B_803FADA0 *)p)) + 2;
    if (p == NULL || p->len < 4) {
        ppp->transmit_errors += 1;
        return -1;
    }
    src = p->buf;
    addr = src[0];
    ctrl = src[1];
    proto = read_network_u16_be(src + 2);
    is_lcp = proto == 0xc021;
    if (proto != 0xc021 && (opts->remote.got.mask & LCP_OPT_ACCM)) {
        accm = opts->remote.got.accm;
    }
    two = ppp_protocol_field_is_two_bytes(is_lcp, opts, proto);
    if (two == 0) {
        n = 3;
    }
    if (lbl_805D7A7A != 0) {
        acfc = 0;
    } else {
        acfc = ppp_keep_field(is_lcp, opts, LCP_OPT_ACFC);
    }
    if (acfc == 0) {
        n -= 2;
    }
    skip = 4 - n;
    p->len -= skip;
    p->buf += skip;
    hdr = p->buf;
    if (acfc != 0) {
        hdr[0] = addr;
        hdr[1] = ctrl;
        hdr += 2;
    }
    if (two != 0) {
        *hdr++ = proto >> 8;
    }
    *hdr++ = proto;
    bufs = &lbl_805C04A8;
    frame = bufs->frame_out;
    frame->buf = (u8 *)frame + ((bufs->value + 3) & ~3);
    out = frame->buf;
    if (lbl_805D7A7A != 0) {
        NetMemcpy(out + 0x14, p->buf, p->len);
        frame->len = p->len;
    } else {
        *out++ = 0x7e;
        ppp->transmit_frames += 1;
        while ((c = get_80405A74(&p)) != -1) {
            crc = (u16)(((u16)crc >> 8) ^ lbl_804FD3A8[((u16)crc ^ c) & 0xff]);
            if ((c < 0x20 && (accm & (1u << c))) || c == 0x7d || c == 0x7e) {
                *out++ = 0x7d;
                *out++ = c ^ 0x20;
            } else {
                *out++ = c;
            }
        }

        crc ^= 0xffff;
        fcs = crc;
        c = fcs & 0xff;
        if ((c < 0x20 && (accm & (1u << c))) || c == 0x7d || c == 0x7e) {
            *out++ = 0x7d;
            *out++ = c ^ 0x20;
        } else {
            *out++ = c;
        }
        c = fcs >> 8;
        if ((c < 0x20 && (accm & (1u << c))) || c == 0x7d || c == 0x7e) {
            *out++ = 0x7d;
            *out++ = c ^ 0x20;
        } else {
            *out++ = c;
        }
        *out++ = 0x7e;
        frame->len = out - frame->buf;
    }
    state = lbl_805D7A8A;
    if (state == 7 || state == 0) {
        return 0;
    }
    ppp_update_send_timestamp();
    return (s16)send_network_frame(frame->len, frame->buf);
}
#pragma pop

s32 TLobby::shutdown_network_handle() {
    TLobby__sub_803F8A08((void *)((void *) (&lobby_udp_socket_table)));
    lobby_udp_socket_table = 0;
    return 0;
}

#pragma push
#pragma optimization_level 3
s32 TLobby::reset_socket_table() {
    s16 n;
    s16 i;
    Ent_80406B14 *p;
    TLobby__sub_803F8A0C((u8 *)&lobby_udp_socket_table);
    n = ((Tbl_80406B14 *)&lobby_udp_socket_table)->count;
    p = ((Tbl_80406B14 *)&lobby_udp_socket_table)->list;
    for (i = 0; i < n; i++, p++) {
        p->st = 0;
    }
    return 0;
}

#pragma pop
s32 TLobby__sub_80406B6C(O_80406B6C *o) {
    if (o != 0) {
        switch (o->b4) {
        case 1:
        case 3:
            break;
        case 2:
        case 4:
            if (TLobby__sub_8041579C(o) < 0) {
                return -1;
            }
            return 0;
        }
    }
    return -1;
}

#pragma opt_lifetimes off
u16 TLobby__sub_80406BD8(void *arg, s16 flag)
{
    NetPacket *pkt = (NetPacket *)arg;
    NetPacketFragment *e;
    u32 sum;
    u8 *ptr;
    s32 count;
    s32 i;
    s16 carry;
    u8 hdr[2];

    count = pkt->fragment_count;
    sum = 0;
    carry = 0;
    *(u16 *)hdr = 0;
    if (flag == 1) {
        e = pkt->fragments + count - 1;
        while (count != 0) {
            u8 kind = e->buffer.kind;
            u32 *w = &e->buffer.value;
            s16 len;
            e--;
            count--;
            switch (kind) {
            case 1:
            case 4:
                ptr = (u8 *)*w;
                break;
            case 2: {
                u32 word = *w;
                s16 k = (s16)(word >> 24);
                Ent_80415690 *ent;
                u16 seg;
                if (network_buffer_pool_state.count < k) {
                    return 0;
                }
                ent = network_buffer_pool_state.ents;
                ent = ent + k;
                seg = ent->segs[(s16)((len = word >> 16) & 0xff)].offset;
                {
                    u32 t = (u32)ent->buf;
                    t = (word & 0xffff) + t;
                    t = seg + t;
                    ptr = (u8 *)t;
                }
                break;
            }
            case 3:
                ptr = (u8 *)e[1].buffer.value;
                break;
            }
            len = e[1].length;
            if (carry) {
                hdr[1] = *ptr++;
                sum += *(u16 *)hdr;
                len--;
            }
            if (len & 1) {
                hdr[0] = ptr[len - 1];
                hdr[1] = 0;
                carry = 1;
                len--;
            } else {
                *(u16 *)hdr = 0;
                carry = 0;
            }
            len = len >> 1;
            sum += TUdpSocket__sub_80419864(ptr, len);
        }
        if (carry) {
            sum += *(u16 *)hdr;
        }
    } else {
        e = pkt->fragments;
        for (i = 1; i < count; e++, i++) {
            u32 *w = &e[1].buffer.value;
            s16 len;
            switch (e[1].buffer.kind) {
            case 1:
            case 4:
                ptr = (u8 *)*w;
                break;
            case 2: {
                u32 word = *w;
                s16 k = (s16)(word >> 24);
                Ent_80415690 *ent;
                u16 seg;
                if (network_buffer_pool_state.count < k) {
                    return 0;
                }
                ent = network_buffer_pool_state.ents;
                ent = ent + k;
                {
                    u32 t = (u32)ent->buf;
                    seg = ent->segs[(s16)((len = word >> 16) & 0xff)].offset;
                    t = (word & 0xffff) + t;
                    t = seg + t;
                    ptr = (u8 *)t;
                }
                break;
            }
            case 3:
                ptr = (u8 *)e[1].buffer.value;
                break;
            }
            len = e[1].length;
            if (carry) {
                hdr[1] = *ptr++;
                sum += *(u16 *)hdr;
                len--;
            }
            if (len & 1) {
                hdr[0] = ptr[len - 1];
                hdr[1] = 0;
                carry = 1;
                len--;
            } else {
                *(u16 *)hdr = 0;
                carry = 0;
            }
            len = len >> 1;
            sum += TUdpSocket__sub_80419864(ptr, len);
        }
        if (carry) {
            sum += *(u16 *)hdr;
        }
    }
    if (sum & 0xffff0000) {
        sum = (sum >> 16) + (sum & 0xffff);
        sum += sum >> 16;
    }
    return (u16)sum;
}

void TLobby__sub_80406EB8(NetBufferRef *ref, s32 n) {
    switch (ref->kind) {
    case 4:
        break;
    case 1:
        ref->value += n;
        break;
    case 2:
        ref->value += n;
        break;
    case 3:
        ref->value += n;
        break;
    }
}

#pragma opt_propagation off
u8 *TLobby__sub_80406F0C(void *arg) {
    NetBufferRef *ref = (NetBufferRef *)arg;
    switch (ref->kind) {
    case 1:
    case 4:
        return (u8 *)ref->value;
    case 2: {
        u32 value = ref->value;
        s16 index = value >> 24;
        // The original resolver and release routine use a strict comparison.
        if (network_buffer_pool_state.count < index) {
            return NULL;
        }
        Ent_80415690 *entry = &network_buffer_pool_state.ents[index];
        s16 segment = (value >> 16) & 0xFF;
        // After decoding, the opaque pointer carries only the buffer address.
        arg = entry->buf;
        u16 offset = value;
        u16 segment_offset = entry->segs[segment].offset;
        arg = (void *)(offset + (u32)arg);
        return (u8 *)(segment_offset + (u32)arg);
    }
    case 3:
        return (u8 *)ref->value;
    default:
        return NULL;
    }
}

#pragma opt_lifetimes reset
void NetBufferRefInitKind4(NetBufferRef *ref, s32 value) {
    ref->value = (u32)value;
    ref->kind = 4;
}

void NetBufferRefInitKind3(NetBufferRef *ref, s32 value) {
    ref->value = (u32)value;
    ref->kind = 3;
}

void NetBufferRefInitKind1(NetBufferRef *ref, s32 value) {
    ref->value = (u32)value;
    ref->kind = 1;
}

void TLobby__sub_80406FD8(void *a, void *b, s32 v) {
    switch (((NetBufferRef *)b)->kind) {
    case 1:
    case 4:
        switch (((NetBufferRef *)a)->kind) {
        case 1:
        case 4:
            NetMemcpy((void *)((NetBufferRef *)a)->value, (void *)((NetBufferRef *)b)->value, v);
            break;
        case 2:
            {
        u32 word = ((NetBufferRef *)a)->value;
        s16 id = (s16)(word >> 24);
        u32 hi;
        u8 *rec;
        u8 *ent;
        u32 t;
        if (network_buffer_pool_state.count < id) {
            return;
        }
        hi = word >> 16;
        rec = (u8 *)network_buffer_pool_state.ents;
        rec += id * (s32)sizeof(Ent_80415690);
        ent = rec + (s16)(hi & 0xff) * (s32)sizeof(Seg_80415690);
        t = *(u16 *)(ent + offsetof(Ent_80415690, segs[0].offset)) + (word & 0xffff) + *(u32 *)(rec + offsetof(Ent_80415690, buf));
        NetMemcpy((void *)t, (void *)((NetBufferRef *)b)->value, v);
        break;
    }
        case 3:
            NetMemcpy((void *)((NetBufferRef *)a)->value, (void *)((NetBufferRef *)b)->value, v);
            break;
        }
        break;
    case 2:
        switch (((NetBufferRef *)a)->kind) {
        case 1:
        case 4:
            {
        u32 word = ((NetBufferRef *)b)->value;
        s16 id = (s16)(word >> 24);
        u32 hi;
        u8 *rec;
        u8 *ent;
        u32 t;
        if (network_buffer_pool_state.count < id) {
            return;
        }
        hi = word >> 16;
        rec = (u8 *)network_buffer_pool_state.ents;
        rec += id * (s32)sizeof(Ent_80415690);
        ent = rec + (s16)(hi & 0xff) * (s32)sizeof(Seg_80415690);
        t = *(u16 *)(ent + offsetof(Ent_80415690, segs[0].offset)) + (word & 0xffff) + *(u32 *)(rec + offsetof(Ent_80415690, buf));
        NetMemcpy((void *)((NetBufferRef *)a)->value, (void *)t, v);
        break;
    }
        case 2:
            {
        u32 word = ((NetBufferRef *)b)->value;
        u32 word2;
        s16 id = (s16)(word >> 24);
        s16 cnt = network_buffer_pool_state.count;
        Ent_80415690 *ents;
        u32 hi;
        u8 *ent;
        u32 t;
        s16 id2;
        u32 raw;
        u8 *rec;
        u32 t2;
        if (cnt < id) {
            return;
        }
        hi = word >> 16;
        word2 = ((NetBufferRef *)a)->value;
        ents = network_buffer_pool_state.ents;
        rec = (u8 *)&ents[id];
        raw = word2 >> 24;
        ent = rec + (s16)(hi & 0xff) * (s32)sizeof(Seg_80415690);
        id2 = (s16)raw;
        t = *(u16 *)(ent + offsetof(Ent_80415690, segs[0].offset)) + (word & 0xffff) + *(u32 *)(rec + offsetof(Ent_80415690, buf));
        if (cnt < id2) {
            return;
        }
        hi = word2 >> 16;
        rec = (u8 *)&ents[id2];
        ent = rec + (s16)(hi & 0xff) * (s32)sizeof(Seg_80415690);
        t2 = *(u16 *)(ent + offsetof(Ent_80415690, segs[0].offset)) + (word2 & 0xffff) + *(u32 *)(rec + offsetof(Ent_80415690, buf));
        NetMemcpy((void *)t2, (void *)t, v);
        break;
    }
        case 3:
            {
        u32 word = ((NetBufferRef *)b)->value;
        s16 id = (s16)(word >> 24);
        u32 hi;
        u8 *rec;
        u8 *ent;
        u32 t;
        if (network_buffer_pool_state.count < id) {
            return;
        }
        hi = word >> 16;
        rec = (u8 *)network_buffer_pool_state.ents;
        rec += id * (s32)sizeof(Ent_80415690);
        ent = rec + (s16)(hi & 0xff) * (s32)sizeof(Seg_80415690);
        t = *(u16 *)(ent + offsetof(Ent_80415690, segs[0].offset)) + (word & 0xffff) + *(u32 *)(rec + offsetof(Ent_80415690, buf));
        NetMemcpy((void *)((NetBufferRef *)a)->value, (void *)t, v);
        break;
    }
        }
        break;
    case 3:
        switch (((NetBufferRef *)a)->kind) {
        case 1:
        case 4:
            NetMemcpy((void *)((NetBufferRef *)a)->value, (void *)((NetBufferRef *)b)->value, v);
            break;
        case 2:
            {
        u32 word = ((NetBufferRef *)a)->value;
        s16 id = (s16)(word >> 24);
        u32 hi;
        u8 *rec;
        u8 *ent;
        u32 t;
        if (network_buffer_pool_state.count < id) {
            return;
        }
        hi = word >> 16;
        rec = (u8 *)network_buffer_pool_state.ents;
        rec += id * (s32)sizeof(Ent_80415690);
        ent = rec + (s16)(hi & 0xff) * (s32)sizeof(Seg_80415690);
        t = *(u16 *)(ent + offsetof(Ent_80415690, segs[0].offset)) + (word & 0xffff) + *(u32 *)(rec + offsetof(Ent_80415690, buf));
        NetMemcpy((void *)t, (void *)((NetBufferRef *)b)->value, v);
        break;
    }
        case 3:
            NetMemcpy((void *)((NetBufferRef *)a)->value, (void *)((NetBufferRef *)b)->value, v);
            break;
        }
        break;
    }
}

#pragma opt_propagation reset
void NetReleasePacket(NetPacket *packet) {
    s16 i;
    s16 n = ((Tbl_80407310 *)&lobby_udp_socket_table)->count;
    NetPacket *p = ((Tbl_80407310 *)&lobby_udp_socket_table)->list;
    for (i = 0; i < n; i++, p++) {
        if (p->in_use == 1 && p == packet) {
            p->in_use = 0;
            return;
        }
    }
}

NetPacket *TLobby::alloc_free_entry() {
    s16 n = ((Tbl_80407310 *)&lobby_udp_socket_table)->count;
    NetPacket *p = ((Tbl_80407310 *)&lobby_udp_socket_table)->list;
    s16 i;
    for (i = 0; i < n; i++, p++) {
        if (p->in_use == 0) {
            p->in_use = 1;
            return p;
        }
    }
    return 0;
}

s32 TLobby__sub_80407358(void) {
    Tbl_80408718 *g = &lbl_805C1AB0;
    s32 tmp[2];
    TLobby::release_slot_by_id(0x806);
    NetUnregisterTimer(TLobby__sub_804078B4);
    TLobby__sub_803F8A24(g);
    g->count = 0;
    g->h2 = 0;
    g->h4 = 0;
    g->h8 = 0;
    return 0;
}

void TLobby__sub_804073B8(void) {
    TUdpSocket__sub_80407508();
}

s32 TLobby::dispatch_slot_a(s16 arg0, s32 arg1) {
    return TLobby__sub_80407C60(arg0, arg1);
}

s32 TLobby::dispatch_slot_b(s16 arg0, s32 arg1) {
    return TLobby__sub_80407D98(arg0, arg1);
}

s32 TLobby__sub_80407418(s16 id) {
    Tbl_80407418 *t = (Tbl_80407418 *)&lbl_805C1AB0;
    Ent_80407418 *e;
    s16 ok;
    s32 tmp[2];

    e = t->ents;
    if (id >= 0 && id < t->count) {
        ok = 1;
    } else {
        ok = -1;
    }
    if (ok >= 0) {
        e = &e[id];
    } else {
        e = NULL;
    }
    if (e == NULL) {
        return -2;
    }
    if (e->active == 0) {
        return -2;
    }
    TLobby::call_entry_callback(e->a, e->b);
    TLobby__sub_80408388(id);
    return 0;
}

s32 TLobby::forward_net_op(s16 arg0, u8 *arg1, u8 *arg2) {
    return TLobby__sub_8040799C(arg0, arg1, arg2);
}

s16 TLobby::forward_net_op_5args(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s32 arg5, s16 arg6, s32 arg7) {
    return TLobby__sub_80407F20(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

s32 TUdpSocket__sub_80407508(void) {
    s16 n4;
    Ent_8040799C *e;
    Peer_8040799C *p;
    s16 n2;
    s16 n3;
    s16 n1;
    Node_80407C60 *q;
    Conn_8040799C *b;
    Tbl_8040799C *t = ((Tbl_8040799C *)&lbl_805C1AB0);
    s16 *size;
    u8 *data;

    NetInitNetworkBufferConfig((NetConfig_803F8A28 *)((Tbl_8040799C *)&lbl_805C1AB0));
    for (n1 = t->count, p = t->list; n1 > 0; p++, n1--) {
        NetMemset(p, 0, sizeof(Peer_8040799C));
        p->st = 0;
        p->conn = NULL;
    }
    for (n2 = t->h2, e = t->ents; n2 > 0; e++, n2--) {
        NetMemset(e, 0, sizeof(Ent_8040799C));
    }
    size = &t->h6;
    for (n3 = t->h4, b = t->bufs, data = t->pool; n3 > 0; b++, n3--) {
        NetMemset(b, 0, sizeof(Conn_8040799C));
        b->f8 = *size;
        b->fC = data;
        data += *size;
    }
    for (n4 = t->h8, q = t->nodes; n4 > 0; q++, n4--) {
        NetMemset(q, 0, sizeof(Node_80407C60));
    }
    register_protocol_handler__6TLobbyFUsi(0x806, (Handler_8041A130)TLobby__sub_80407640);
    NetRegisterTimer(60000, 1, (NetTimerCallback)TLobby__sub_804078B4);
    return 0;
}

#pragma opt_common_subs on
extern s32 TLobby__sub_80407640(void *pkt, s16 a, s16 b, s16 c)
{
  Tbl_8040799C *t = (Tbl_8040799C *)&lbl_805C1AB0;
  ArpHeader *pp;
  Ent_8040799C *hit;
  Peer_8040799C *peer;
  u8 *p2;
  Out_804081C0 in;
  u8 buf[8];
  Out_804081C0 out;
  Pkt_804081C0 *r;
  if (a < 8) {
    return -1;
  }
  if (b < 0) {
    return -1;
  }
  hit = FindHit_80407640(t, b, c);
  if (hit == NULL) {
    return -1;
  }
  pp = (ArpHeader *) pkt;
  if (CheckPkt_80407640(pp, hit) < 0) {
    return -1;
  }
  in.f0 = (u8 *)pp;
  p2 = (u8 *)pp + sizeof(ArpHeader);
  in.f4 = p2;
  p2 += hit->fE;
  in.f8 = p2;
  p2 += hit->fF;
  in.fC = p2;
  p2 += hit->fE;
  in.f10 = p2;
  peer = FindPeer_80407640(t->list, t->count, hit->fF, in.f8);
  if (peer != NULL) {
    find_or_add_peer_entry__6TLobbyFssUcPvUcPvs(hit->f2, hit->f4, hit->fF, in.f8, hit->fE, in.f4, 2);
  }
  if (pp->op == 1) {
    if (TLobby__sub_804082AC((Ent_804082AC *)hit, (Key_804082AC *)&in, buf) > 0) {
      r = alloc_packet_with_header__6TLobbyFPvPv(&out, (u8 *)hit);
      if (r != NULL) {
        *(u16 *)(out.f0 + 6) = 2;
        NetMemcpy(out.f4, buf, hit->fE);
        NetMemcpy(out.fC, in.f4, hit->fE);
        NetMemcpy(out.f8, in.f10, hit->fF);
        NetMemcpy(out.f10, in.f8, hit->fF);
        TLobby::call_handler_by_index(hit->f2, c, 0, (s32)in.f4, (s32)r);
        if (r != NULL) {
          NetReleasePacket((NetPacket *)r);
        }
      }
    }
  }
  return 0;
}

#pragma opt_common_subs reset
void TLobby__sub_804078B4(void) {
    Peer_8040799C *p;
    s16 n;

    n = ((Tbl_8040799C *)&lbl_805C1AB0)->count;
    p = ((Tbl_8040799C *)&lbl_805C1AB0)->list;

    for (; n > 0; n--, p++) {
        if (p->st == 0) {
            continue;
        }
        if (p->f2 != 0) {
            p->f2--;
        }
        if (p->f2 != 0 || p->st == 4 || p->st == 8) {
            continue;
        }
        if (p->conn != NULL) {
            clear_peer_conn_804078B4(p);
            p->conn = NULL;
        }
        p->st = 0;
        p->f2 = 0;
        NetMemset(p->addr, 0, 6);
        NetMemset(p->name, 0, 4);
    }
}

s32 TLobby__sub_8040799C(s16 idx, void *name, void *arg2) {
    Tbl_8040799C *t = ((Tbl_8040799C *)&lbl_805C1AB0);
    Ent_8040799C *e;
    Peer_8040799C *p;
    s32 ret;
    Peer_8040799C *np;

    e = Lookup_8040799C(t, idx);
    if (e == NULL) {
        return -2;
    }
    ret = 0;
    p = Find_8040799C(t, e->fF, name);
    if (p != NULL) {
        p->f2 = t->hA;
        if (p->st != 1) {
            ret = TLobby::call_handler_by_index(e->f2, e->f4, 0, (s32)p->addr, (s32)arg2);
        } else {
            if (p->conn != NULL) {
                Clear_8040799C(p);
                p->conn = NULL;
            }
            TLobby__sub_80408060(p, (NetPacket *)arg2);
            Send_8040799C(e, name);
            p->f2 = t->hC;
        }
    } else {
        u8 buf[6];
        NetMemset(buf, 0, 6);
        np = (Peer_8040799C *)find_or_add_peer_entry__6TLobbyFssUcPvUcPvs(e->f2, e->f4, e->fF, name, e->fE, buf, 1);
        TLobby__sub_80408060(np, (NetPacket *)arg2);
        Send_8040799C(e, name);
        np->f2 = t->hC;
    }
    return ret;
}

s32 TLobby__sub_80407C60(s16 idx, s32 addr) {
    Tbl_8040799C *t = ((Tbl_8040799C *)&lbl_805C1AB0);
    Ent_8040799C *e;
    Node_80407C60 *prev;
    Node_80407C60 *p;
    s16 k;

    e = Lookup_8040799C(t, idx);
    if (e == NULL) {
        return -1;
    }
    if (e->f0 == 0) {
        return -1;
    }
    if (e->head == NULL) {
        return -1;
    }
    p = e->head;
    k = 0;
    while (p->next != NULL) {
        k++;
        if (t->h8 <= k) {
            return -1;
        }
        if (NetMemcmp(p->addr, (void *)addr, 4) == 0) {
            if (e->head == p) {
                e->head = p->next;
            } else {
                prev->next = p->next;
            }
            p->next = NULL;
            p->used = 0;
            return 0;
        }
        prev = p;
        p = p->next;
    }
    return -1;
}

s32 TLobby__sub_80407D98(s16 idx, s32 addr) {
    s16 lim;
    Node_80407C60 *next;
    Node_80407C60 *p;
    Ent_8040799C *e;
    Node_80407C60 *node;
    s16 *max;
    Tbl_8040799C *t = ((Tbl_8040799C *)&lbl_805C1AB0);
    s16 k;

    e = Lookup_8040799C(t, idx);
    if (e == NULL) {
        return -1;
    }
    if (e->f0 == 0) {
        return -1;
    }
    node = AllocNode_80407D98(t, max = &t->h8);
    if (node == NULL) {
        return -1;
    }
    NetMemcpy(node->addr, (void *)addr, 4);
    node->used = 1;
    node->next = NULL;
    if (e->head == NULL) {
        e->head = node;
    } else {
        lim = *max;
        p = e->head;
        k = 0;
        while ((next = p->next) != NULL) {
            k++;
            if (lim <= k) {
                return -1;
            }
            p = next;
        }
        p->next = node;
    }
    return 0;
}

s16 TLobby__sub_80407F20(s16 a, s16 b, s16 c, s16 d, s16 e, s32 f, s16 g, s32 h)
{
    Ent_8040799C *base;
    Ent_8040799C *slot;
    s16 res;
    s16 idx;

    if (a < 0) {
        return -1;
    }
    res = TLobby__sub_8040A044(a, 0x806, g, (u8 *)h);
    if (res < 0) {
        return res;
    }
    base = ((Tbl_8040799C *)&lbl_805C1AB0)->ents;
    slot = findfree_80407F20(base);
    if (slot == NULL) {
        TLobby::call_entry_callback(a, res);
        return -0x10d;
    }
    slot->f0 = 1;
    idx = (s16)(slot - base);
    slot->f2 = a;
    slot->f4 = b;
    slot->f6 = res;
    slot->index = idx;
    slot->hardware_type = c;
    slot->protocol_type = d;
    slot->fE = e;
    slot->fF = g;
    slot->status = 0;
    NetMemcpy(slot->a12, (void *)f, e);
    NetMemcpy(slot->a18, (void *)h, g);
    slot->head = NULL;
    return idx;
}

void TLobby__sub_80408060(Peer_8040799C *peer, NetPacket *pkt) {
    Conn_8040799C *slot;
    s16 total;
    Conn_8040799C *oldest;
    Conn_8040799C *c;
    s16 n;
    Peer_8040799C *owner;
    s16 i;
    u8 *data;
    NetBufferRef ref;

    total = 0;
    slot = NULL;
    c = ((Tbl_8040799C *)&lbl_805C1AB0)->bufs;
    n = ((Tbl_8040799C *)&lbl_805C1AB0)->h4;
    oldest = NULL;
    for (; n > 0; c++, n--) {
        if (c->f4 == 0) {
            slot = c;
            break;
        }
        if (oldest == NULL) {
            oldest = c;
        } else if (c->a->f2 < oldest->a->f2) {
            oldest = c;
        }
    }
    if (slot == NULL) {
        owner = oldest->a;
        Clear_8040799C(owner);
        owner->conn = NULL;
        slot = oldest;
    }
    if (slot->f8 < (s16)pkt->total_bytes) {
        return;
    }
    slot->f4 = 1;
    data = slot->fC;
    for (i = pkt->fragment_count; i > 0; i--) {
        NetBufferRefInitKind1(&ref, (s32)data);
        TLobby__sub_80406FD8(&ref, &pkt->fragments[i - 1].buffer, pkt->fragments[i - 1].length);
        data += pkt->fragments[i - 1].length;
        total += pkt->fragments[i - 1].length;
    }
    slot->f6 = total;
    slot->a = peer;
    peer->conn = slot;
}

Pkt_804081C0 *alloc_packet_with_header__6TLobbyFPvPv(Out_804081C0 *arg0, u8 *arg1) {
    s16 len;
    Pkt_804081C0 *pkt;
    u8 *buf;
    u16 t;
    u8 *q;
    t = arg1[0xE] * 2 + 8;
    t += arg1[0xF] * 2;
    len = t;
    if ((u32)len > 0x1CU) {
        return NULL;
    }
    pkt = (Pkt_804081C0 *)TLobby::alloc_free_entry();
    if (pkt == NULL) {
        return NULL;
    }
    pkt->f4 = 1;
    pkt->f8 = len;
    buf = (u8 *)&((Pool_804081C0 *)&lbl_805C1AB0)->f24;
    pkt->fC = t;
    NetBufferRefInitKind1((NetBufferRef *)pkt->f10, *(s32 *)buf);
    buf = *(u8 **)buf;
    NetMemset(buf, 0, len);
    NetMemcpy(buf, arg1 + 0xA, 6);
    arg0->f0 = buf;
    q = buf + 8;
    arg0->f4 = q;
    q += arg1[0xE];
    arg0->f8 = q;
    q += arg1[0xF];
    arg0->fC = q;
    q += arg1[0xE];
    arg0->f10 = q;
    return pkt;
}

s16 TLobby__sub_804082AC(Ent_804082AC *arg0, Key_804082AC *arg1, void *arg2) {
    s16 i;
    Node_804082AC *p;

    if (NetMemcmp(arg0->f18, arg1->f10, arg0->fF) == 0) {
        NetMemcpy(arg2, arg0->f12, arg0->fE);
        return 1;
    }
    if (arg0->f1C != NULL) {
        p = arg0->f1C;
        i = 0;
        while (p != NULL) {
            i++;
            if (lbl_805C1AB0.h8 <= i) {
                return -1;
            }
            if (NetMemcmp(p->f6, arg1->f10, arg0->fF) == 0) {
                NetMemcpy(arg2, arg0->f12, arg0->fE);
                return 1;
            }
            p = p->next;
        }
    }
    return -1;
}

s32 TLobby__sub_80408388(s16 id) {
    Tbl_80408388 *t = (Tbl_80408388 *)&lbl_805C1AB0;
    Ent_80408388 *e;
    Node_80408388 *n;
    Node_80408388 *next;
    s16 ok;

    e = t->ents;
    if (id >= 0 && id < t->count) {
        ok = 1;
    } else {
        ok = -1;
    }
    if (ok >= 0) {
        e = &e[id];
        for (n = e->head; n != NULL; n = next) {
            next = n->next;
            n->next = NULL;
            n->used = 0;
        }
        NetMemset(e, 0, 0x20);
        return 1;
    }
    return -1;
}

static inline Ent_80408428 *notify_and_detach_peer(Ent_80408428 *e, s16 arg0, s16 arg1) {
    NetPacket *packet;
    if (e->sub != NULL) {
        packet = TLobby::alloc_free_entry();
        if (packet != NULL) {
            packet->fragment_count = 1;
            packet->total_bytes = e->sub->f6;
            packet->fragments[0].length = e->sub->f6;
            NetBufferRefInitKind1(&packet->fragments[0].buffer, e->sub->fC);
            TLobby::call_handler_by_index(arg0, arg1, 0, (s32)e->addrC, (s32)packet);
            NetReleasePacket(packet);
        }
    }
    detach_80408428(e);
    return e;
}

Ent_80408428 *find_or_add_peer_entry__6TLobbyFssUcPvUcPvs(s16 arg0, s16 arg1, u8 type, void *addr, u8 type2, void *addr2, s16 state) {
    Tbl_80408428 *t = (Tbl_80408428 *)&lbl_805C1AB0;
    Ent_80408428 *e;

    e = find_80408428(t, type, addr);
    if (e != NULL) {
        e->stamp = t->stampA;
        if (addr2 == NULL) {
            return e;
        }
        if (e->state != 1) {
            int n2 = type2;
            if (NetMemcmp(e->addrC, addr2, n2) != 0) {
                NetMemcpy(e->addrC, addr2, n2);
                e->state = state;
            }
            return e;
        }
        NetMemcpy(e->addrC, addr2, type2);
        e->state = state;
        Ent_80408428 *result = notify_and_detach_peer(e, arg0, arg1);
        return result;
    }
    if (addr2 == NULL) {
        return NULL;
    }
    e = (Ent_80408428 *)find_free_peer_entry__6TLobbyFv();
    if (e == NULL) {
        e = (Ent_80408428 *)find_oldest_peer_entry__6TLobbyFs(4);
        if (e == NULL) {
            e = (Ent_80408428 *)find_oldest_peer_entry__6TLobbyFs(0);
        }
        if (e->sub != NULL) {
            detach_80408428(e);
        }
        e->state = 0;
        e->stamp = 0;
        NetMemset(e->addrC, 0, 6);
        NetMemset(e->addr12, 0, 4);
    }
    if (addr2 != NULL) {
        NetMemcpy(e->addrC, addr2, type2);
    }
    NetMemcpy(e->addr12, addr, type);
    e->type4 = type2;
    e->type5 = type;
    e->state = state;
    e->stamp = t->stampA;
    e->sub = NULL;
    return e;
}

Ent_804086B4 *find_oldest_peer_entry__6TLobbyFs(s16 key) {
    Ent_804086B4 *best = 0;
    Ent_804086B4 *p;
    s16 n = ((Tbl_804086B4 *)&lbl_805C1AB0)->count;
    s32 v;
    p = ((Tbl_804086B4 *)&lbl_805C1AB0)->list;
    for (; n > 0; n--, p++) {
        v = p->f0;
        if ((s16)v != 0 && v != key) {
            if (best == 0) {
                best = p;
            } else if (best->f2 > p->f2) {
                best = p;
            }
        }
    }
    return best;
}

Ent_80408718 *find_free_peer_entry__6TLobbyFv(void) {
    s16 n = lbl_805C1AB0.count;
    Ent_80408718 *e = lbl_805C1AB0.list;
    while (n > 0) {
        if (e->f0 == 0) {
            return e;
        }
        n--;
        e++;
    }
    return NULL;
}

void TLobby::flush_flags_step() {
    TLobby__sub_8040878C();
}

void TLobby::run_connect_step() {
    TLobby::init_net_sockets();
}

s32 TLobby__sub_8040878C(void) {
    s16 n = LG_8040881C.count;
    s16 i = 0;
    Ent_8040881C *e = LG_8040881C.ents;

    for (; i < n; i++, e++) {
        if (e->used != 0) {
            TLobby::clear_table_entry_locked(e->id);
            e->used = 0;
            e->id = 0;
            e->idx = 0;
        }
    }
    LG_8040881C.n2 = 0;
    LG_8040881C.n4 = 0;
    LG_8040881C.n6 = 0;
    TLobby__sub_803F8AB8(&LG_8040881C);
    return 0;
}

s16 TLobby::init_net_sockets() {
    Fn_8040881C fns[11];
    s16 r;
    s16 first;
    s16 cnt;
    s16 i;
    Ent_8040881C *e;
    Desc_8040881C *d;
    Ent_8040881C **pe;

    NetInitFunctionTable((Desc_803F8AD8 *)&LG_8040881C);
    pe = &LG_8040881C.ents;
    NetMemset(*pe, 0, LG_8040881C.n2 * 0x10);
    NetMemset(LG_8040881C.p10, 0, LG_8040881C.n4 * 0x10);
    NetMemset(LG_8040881C.p14, 0, LG_8040881C.n6 * 0x5F8);
    fns[0] = (Fn_8040881C)TLobby__sub_8040970C;
    fns[1] = (Fn_8040881C)TLobby__sub_804094B8;
    fns[2] = (Fn_8040881C)TLobby__sub_804093EC;
    fns[3] = (Fn_8040881C)TLobby__sub_8040939C;
    fns[4] = (Fn_8040881C)TLobby__sub_804092FC;
    fns[5] = (Fn_8040881C)TLobby__sub_8040920C;
    fns[6] = (Fn_8040881C)TLobby__sub_80409130;
    fns[7] = (Fn_8040881C)TLobby__sub_80408FD8;
    fns[8] = (Fn_8040881C)TLobby__sub_80408F2C;
    fns[9] = (Fn_8040881C)TLobby::forward_socket_op_by_handle;
    fns[10] = (Fn_8040881C)TLobby::send_ethernet_frame;
    first = -1;
    cnt = LG_8040881C.count;
    d = LG_8040881C.descs;
    e = *pe;
    i = 0;
    while (i < cnt) {
        if (d->fn != NULL) {
            r = d->fn(i);
            if (r < 0) {
                return r;
            }
        } else {
            return -0x111;
        }
        r = TLobby__sub_80409A3C((u8 *)fns, 0x7C);
        if (r < 0) {
            return r;
        }
        if (first < 0) {
            first = r;
        }
        e->used = 1;
        e->id = r;
        e->idx = i;
        d++;
        i++;
        e++;
    }
    return first;
}

u8 *TLobby__sub_804089A8(s16 iface, s16 op, s16 len, u8 *pkt) {
    EtherRxTable *t = (EtherRxTable *)&lbl_805C1AD8;
    EtherProtocolBinding *ents;
    EtherProtocolBinding *e;
    EtherRxBuffer *b;
    s16 slot;
    u16 type;
    EthernetFrameHeader hdr;

    NetMemcpy(hdr.destination, pkt, 6);
    NetMemcpy(hdr.source, pkt + 6, 6);
    NetMemcpy(&hdr.ether_type, pkt + 12, 2);
    if (op == 0) {
        if (len > 0x5EA) {
            return NULL;
        }
        ents = t->bindings;
        e = find_protocol_binding(ents, t->nbindings, iface, hdr.ether_type);
        if (e == NULL) {
            return NULL;
        }
        e->buf = NULL;
        slot = e - ents;
        b = alloc_rx_buffer(t->bufs, t->nbufs, iface, slot, e->handler, len);
        if (b == NULL) {
            return NULL;
        }
        e->buf = b;
        return b->data;
    } else if (op == 1) {
        ents = t->bindings;
        type = hdr.ether_type;
        e = find_protocol_binding(ents, t->nbindings, iface, type);
        if (e == NULL) {
            return NULL;
        }
        b = e->buf;
        slot = e - ents;
        if (b == NULL) {
            return NULL;
        }
        if (b->iface != iface || b->slot != slot || b->handler != e->handler || b->len != len) {
            s32 lvl = OSDisableInterrupts();
            b->used = 0;
            b->iface = 0;
            b->slot = 0;
            b->handler = 0;
            b->len = 0;
            OSRestoreInterrupts(lvl);
            return NULL;
        }
        TLobby__sub_80409818((s32)(b->data + sizeof(EthernetFrameHeader)), b->len - sizeof(EthernetFrameHeader), b->handler, b->slot, type);
        return NULL;
    }
    return NULL;
}

s32 TLobby::send_ethernet_frame(s16 idx, s16 mode, u8 *addr, void *pkt) {
    void NetMemset(void *, int, int);
    void NetMemcpy(void *, void *, int);
    Glob_80408C24 *g = (Glob_80408C24 *)&lbl_805C1AD8;
    Hdr_80408C24 hdr;
    Conn_80408C24 *c;
    Ent_80408C24 *e;
    s16 len;
    SendFn_80408C24 fn;

    if (idx < 0 || idx >= g->nent) {
        return -0x111;
    }
    e = g->ents;
    e += idx;
    if (e->used == 0) {
        return -2;
    }
    c = find_conn_80408C24(g, e->id);
    if (c == NULL) {
        return -2;
    }
    switch (mode) {
    case 0:
        NetMemcpy(hdr.dst, addr, 6);
        break;
    case 1:
        NetMemset(hdr.dst, 0xFF, 6);
        break;
    case 2:
        if (e->type == 0x800) {
            hdr.dst[0] = 1;
            hdr.dst[1] = 0;
            hdr.dst[2] = 5;
            hdr.dst[3] = addr[1] & 0x7F;
            hdr.dst[4] = addr[2];
            hdr.dst[5] = addr[3];
        } else if (e->type == 0x86DD) {
            hdr.dst[0] = 0x33;
            hdr.dst[1] = 0x33;
            hdr.dst[2] = addr[12];
            hdr.dst[3] = addr[13];
            hdr.dst[4] = addr[14];
            hdr.dst[5] = addr[15];
        } else {
            return -2;
        }
        break;
    default:
        return -2;
    }
    c->buf = TLobby__sub_8042558C(0x5EA);
    if (c->buf == NULL) {
        return 0;
    }
    NetMemcpy(hdr.src, c->mac, 6);
    hdr.type = e->type;
    NetMemcpy(c->buf, &hdr, 0xE);
    len = TLobby__sub_804098B4((NetPacket *)pkt);
    if (len > 0x5DC) {
        TLobby::clear_message_entry((s32)c->buf);
        return -2;
    }
    TLobby__sub_80409908(c->buf + 0xE, (NetPacket *)pkt);
    if (len + 0xE < 0x3C) {
        len = 0x2E;
    }
    fn = g->ifaces[e->iface].send;
    if (fn != NULL) {
        fn(c->handle, c->buf, len + 0xE);
    } else {
        TLobby::clear_message_entry((s32)c->buf);
        return -0x111;
    }
    return 0;
}

s32 TLobby::forward_socket_op_by_handle(s16 id, u8 *a, u8 *b) {
    Ent_80408E98 *e;
    s32 sock;

    if (id < 0 || id >= ((Tbl_80408E98 *)&lbl_805C1AD8)->count) {
        return -0x111;
    }
    e = ((Tbl_80408E98 *)&lbl_805C1AD8)->ents;
    e += id;
    if (e->active == 0) {
        return -2;
    }
    switch (e->type) {
    case 0x800:
        sock = e->sock;
        if ((s16)sock >= 0) {
            return TLobby::forward_net_op(sock, a, b);
        }
        return -2;
    default:
        return -2;
    }
}

s32 TLobby__sub_80408F2C(s16 id, u8 *pkt) {
    Tbl_80408F2C *t = &lbl_805C1AD8;
    Buf_80408F2C *b;
    u8 *data;
    s16 n;
    s16 i;

    if (id < 0 || id >= t->count) {
        return -0x111;
    }
    b = t->bufs;
    data = pkt - 0xE;
    n = t->nbufs;
    i = 0;
    while (i < n) {
        if (b->data == data) {
            s32 lvl = OSDisableInterrupts();
            b->h0 = 0;
            b->h2 = 0;
            b->h4 = 0;
            b->h6 = 0;
            b->h8 = 0;
            OSRestoreInterrupts(lvl);
            return 0;
        }
        i++;
        b++;
    }
    return -2;
}

s32 TLobby__sub_80408FD8(s16 idx, s16 op, u8 *addr) {
    Glob_80408C24 *g = (Glob_80408C24 *)&lbl_805C1AD8;
    Ent_80408C24 *e;
    If_80408C24 *ifc;
    u16 type;
    u8 mac[6];

    if (idx < 0 || idx >= g->nent) {
        return -0x111;
    }
    e = g->ents;
    e += idx;
    if (e->used == 0) {
        return -2;
    }
    type = e->type;
    if (type == 0x800 || type == 0x86DD) {
        ifc = g->ifaces;
        ifc += e->iface;
        if (ifc->fC == NULL) {
            return -0x111;
        }
        if (type == 0x800) {
            mac[0] = 1;
            mac[1] = 0;
            mac[2] = 5;
            mac[3] = addr[1] & 0x7F;
            mac[4] = addr[2];
            mac[5] = addr[3];
        } else {
            mac[0] = 0x33;
            mac[1] = 0x33;
            mac[2] = addr[12];
            mac[3] = addr[13];
            mac[4] = addr[14];
            mac[5] = addr[15];
        }
        if (op == 1) {
            return ifc->fC(e->iface, mac);
        }
        if (op == 2) {
            return ifc->f10(e->iface, mac);
        }
        return -2;
    }
    return -2;
}

s32 TLobby__sub_80409130(s16 arg0, s16 arg1, s32 arg2) {
    s32 h;
    Sock_80409130 *e;

    if (arg0 < 0 || arg0 >= lbl_805C1AD8.count) {
        return -0x111;
    }
    e = *(Sock_80409130 **)((s8 *)(&lbl_805C1AD8) + 0x10);
    e += arg0;
    if (e->f0 == 0) {
        return -2;
    }
    switch (e->f6) {
    case 0x800:
        h = e->f8;
        if ((s16)h < 0) {
            return -2;
        }
        if (arg1 == 1) {
            return TLobby::dispatch_slot_b(h, arg2);
        }
        if (arg1 == 2) {
            return TLobby::dispatch_slot_a(h, arg2);
        }
        return -2;
    default:
        return -2;
    case 0x86DD:
        return 0;
    }
}

s32 TLobby__sub_8040920C(s16 idx, u8 *mac) {
    Glob_80408C24 *g = (Glob_80408C24 *)&lbl_805C1AD8;
    Ent_80408C24 *e;
    Conn_80408C24 *c;

    if (idx < 0 || idx >= g->nent) {
        return -0x111;
    }
    e = g->ents;
    e += idx;
    if (e->used == 0) {
        return -2;
    }
    c = find_conn_80408C24(g, e->id);
    if (c == NULL) {
        return -2;
    }
    if (g->ifaces[e->iface].f14 != NULL) {
        NetMemcpy(mac, c->mac, 6);
    } else {
        return -0x111;
    }
    return 0;
}

// Keep the id inside the lookup to preserve its iterator/id lifetimes and early return when inlined.
static inline Conn_80408C24 *find_conn_for_socket_804092FC(Glob_80408C24 *g, Ent_80408C24 *socket) {
    s16 id;
    s16 n;
    Conn_80408C24 *cursor;
    id = socket->id;
    cursor = g->conns;
    n = g->nconn;
    for (; n > 0; n--, cursor++) {
        if (cursor->used != 0 && cursor->id == id) return cursor;
    }
    return NULL;
}
s32 TLobby__sub_804092FC(s16 idx) {
    Glob_80408C24 *g = (Glob_80408C24 *)&lbl_805C1AD8;
    Ent_80408C24 *e;
    Conn_80408C24 *c;

    if (idx < 0 || idx >= g->nent) {
        return -0x111;
    }
    e = g->ents;
    e += idx;
    if (e->used == 0) {
        return -2;
    }
    c = find_conn_for_socket_804092FC(g, e);
    if (c == NULL) {
        return -2;
    }
    return 6;
}

s32 TLobby__sub_8040939C(s16 idx) {
    Ent_80408C24 *e;

    if (idx < 0 || idx >= ((Glob_80408C24 *)&lbl_805C1AD8)->nent) {
        return -0x111;
    }
    e = ((Glob_80408C24 *)&lbl_805C1AD8)->ents;
    e += idx;
    if (e->used == 0) {
        return -2;
    }
    return 1500;
}

s32 TLobby__sub_804093EC(s16 idx) {
    Glob_80408C24 *g = (Glob_80408C24 *)&lbl_805C1AD8;
    Ent_80408C24 *e;
    CloseFn_80408C24 fn;
    s32 h;

    if (idx < 0 || idx >= g->nent) {
        return -0x111;
    }
    e = g->ents;
    e += idx;
    if (e->used == 0) {
        return -2;
    }
    h = e->f8;
    if ((s16)h >= 0) {
        TLobby__sub_80407418(h);
    }
    fn = g->ifaces[e->iface].f8;
    if (fn != NULL) {
        fn(e->iface, e->type);
    }
    e->used = 0;
    e->id = 0;
    e->iface = 0;
    e->type = 0;
    e->f8 = 0;
    e->fC = 0;
    return 0;
}

// Both searches own their iterators; CSE shares the pool start between them.
static inline Ent_80408C24 *find_free_from_pool_804094B8(Ent_80408C24 **pool, s16 &count) {
    Ent_80408C24 *cursor = *pool;
    for (; count > 0; count--, cursor++) {
        if (cursor->used == 0) return cursor;
    }
    return NULL;
}
#pragma opt_propagation off
#pragma opt_common_subs on
static inline Ent_80408C24 *find_matching_socket_804094B8(Ent_80408C24 **pool, s16 n, s16 dev, u16 type) {
    Ent_80408C24 *ent = *pool;
    for (; n > 0; n--, ent++) {
        if (ent->used != 0 && ent->iface == dev && ent->type == type) return ent;
    }
    return NULL;
}
s16 TLobby__sub_804094B8(s16 a, u16 b, s16 c, void *k) {
    Glob_80408C24 *g = (Glob_80408C24 *)&lbl_805C1AD8;
    Conn_80408C24 *p1;
    Ent_80408C24 *p3;
    s16 result;
    s16 n;
    Ent_80408C24 **pl;
    s16 idx;
    s16 ret;
    s16 err;
    If_80408C24 *cb;

    p1 = find_conn_80408C24(g, a);
    if (p1 == NULL) {
        return -0x111;
    }
    if (b != 0x800 && b != 0x86dd && b != 0x806) {
        return -2;
    }
    pl = &g->ents;
    n = g->nent;
    if (find_matching_socket_804094B8(pl, n, p1->handle, b) != NULL) {
        return -2;
    }
    p3 = find_free_from_pool_804094B8(pl, n);
    if (p3 == NULL) {
        return -0x111;
    }

    p3->used = 1;
    p3->type = b;
    p3->id = a;
    p3->iface = p1->handle;
    idx = p3 - *pl;
    cb = g->ifaces;
    cb += p1->handle;
    if (cb->open != NULL) {
        result = idx;
        ret = cb->open(p1->handle, b);
        if (ret < 0) {
            err = ret;
            goto fail;
        }
        if (cb->f14 != NULL) {
            err = cb->f14(p1->handle, p1->mac);
            if (err != 6) {
                goto fail;
            }
        } else {
            err = -0x111;
            goto fail;
        }
    } else {
        err = -0x111;
        goto fail;
    }
    switch (b) {
    case 0x800:
        ret = TLobby::forward_net_op_5args(a, idx, 1, b, 6, (s32)p1->mac, c, (s32)k);
        if (ret < 0) {
            err = ret;
            goto fail;
        }
        p3->f8 = ret;
        break;
    default:
        p3->f8 = -1;
        break;
    }
    return result;

fail:
    p3->used = 0;
    p3->type = 0;
    return err;
}

#pragma opt_propagation reset
#pragma opt_common_subs reset
s32 TLobby__sub_8040970C(s16 id, u8 *out) {
    Glob_80408C24 *g = (Glob_80408C24 *)&lbl_805C1AD8;
    Conn_80408C24 *c;
    If_80408C24 *ifc;
    u8 mac[6];

    c = find_conn_80408C24(g, id);
    if (c == NULL) {
        return -0x111;
    }
    ifc = g->ifaces;
    ifc += c->handle;
    if (ifc->f14 != NULL) {
        if (ifc->f14(c->handle, mac) != 6) {
            return -0x111;
        }
    } else {
        return -0x111;
    }
    out[0] = mac[0] | 2;
    out[1] = mac[1];
    out[2] = mac[2];
    out[3] = 0xFF;
    out[4] = 0xFE;
    out[5] = mac[3];
    out[6] = mac[4];
    out[7] = mac[5];
    return 0;
}

void TLobby__sub_80409818(s32 msg, s16 len, s16 idx, s16 arg3, u16 type) {
    if (idx < 0 || idx >= TBL_80409818.count) {
        return;
    }
    switch (type) {
    default:
        TBL_80409818.ents[idx].fn(arg3, msg);
        break;
    case 0x800:
    case 0x806:
    case 0x86DD:
        NetEnqueueProtocolMessage(msg, len, idx, arg3, type);
        break;
    }
}

s16 TLobby__sub_804098B4(NetPacket *pkt) {
    return packet_length_804098B4(pkt);
}

s16 TLobby__sub_80409908(u8 *dst, NetPacket *pkt) {
    s16 len = copy_packet_80409908(dst, pkt);
    return len;
}

s32 TLobby::clear_table_entry_locked(s16 arg0) {
    s32 ret;
    TLobby::lock_mutex(network_dispatch_state.lock_handle);
    if (arg0 < 0 || arg0 > TBL_804099B4.count) {
        ret = -0x10F;
    } else {
        Ent_804099B4 *e = TBL_804099B4.ents;
        e += arg0;
        NetMemset(e, 0, 0x30);
        ret = 0;
    }
    TUdpSocket::unlock_mutex(network_dispatch_state.lock_handle);
    return ret;
}

s16 TLobby__sub_80409A3C(u8 *arg0, s16 arg1) {
    s16 temp_r31;
    TLobby::lock_mutex((*(RecoveredGlobal_80409A3C_lbl_805C1C50 *)&network_dispatch_state).value);
    temp_r31 = TLobby__sub_8040A2BC((Fn_8040881C *)arg0, arg1);
    TUdpSocket::unlock_mutex((*(RecoveredGlobal_80409A3C_lbl_805C1C50 *)&network_dispatch_state).value);
    return temp_r31;
}

s32 TLobby__sub_80409AA8(void) {
    TLobby__sub_803F8A9C((void *)((void *) (&lobby_handler_table_desc)));
    lobby_handler_table_desc = 0;
    return 0;
}

s32 TLobby__sub_80409AD8(void) {
    s16 i;
    u8 *p;
    TLobby__sub_803F8AA0((u8 *)&T_);
    p = T_.list;
    i = 0;
    while (i < T_.count) {
        NetMemset(p, 0, 0x30);
        i++;
        p += 0x30;
    }
    return 0;
}

s32 TLobby::call_handler_by_index(s16 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 (*fn)(s16, s32, s32, s32);
    if (arg0 < 0 || arg0 > TBL_80409B48.count) {
        return -0x10F;
    }
    Ent_80409B48 *e = TBL_80409B48.ents;
    e += arg0;
    if (e->active == 0) {
        return -2;
    }
    fn = e->fn;
    if (fn == NULL) {
        return -2;
    }
    return fn(arg1, arg2, arg3, arg4);
}

s32 TLobby::dispatch_handler_by_index(s16 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 (*fn)(s32, s32, s32);
    if (arg0 < 0 || arg0 > TBL_80409BD4.count) {
        return -0x10F;
    }
    Ent_80409BD4 *e = TBL_80409BD4.ents;
    e += arg0;
    if (e->active == 0) {
        return -2;
    }
    fn = e->fn;
    if (fn == NULL) {
        return -2;
    }
    return fn(arg1, arg2, arg3);
}

s32 TLobby::dispatch_handler_by_id(s16 arg0, s32 arg1, s32 arg2) {
    s32 (*fn)(s32, s32);

    if (arg0 < 0 || arg0 > TBL_80409C5C.count) {
        return -0x10F;
    }
    Ent_80409C5C *e = TBL_80409C5C.ents;
    e += arg0;
    if (e->active == 0) {
        return -2;
    }
    fn = e->fn;
    if (fn == NULL) {
        return -2;
    }
    return fn(arg1, arg2);
}

s32 TLobby__sub_80409CE0(s16 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 (*fn)(s32, s32, s32);

    if (arg0 < 0 || arg0 > TBL_80409CE0.count) {
        return -0x10F;
    }
    Ent_80409CE0 *e = TBL_80409CE0.ents;
    e += arg0;
    if (e->active == 0) {
        return -2;
    }
    if (!(e->flags & 4)) {
        return 0;
    }
    fn = e->fn;
    if (fn == NULL) {
        return -2;
    }
    return fn(arg1, arg2, arg3);
}

s32 TLobby__sub_80409D7C(s16 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 (*fn)(s32, s32, s32);

    if (arg0 < 0 || arg0 > TBL_80409D7C.count) {
        return -0x10F;
    }
    Ent_80409D7C *e = TBL_80409D7C.ents;
    e += arg0;
    if (e->active == 0) {
        return -2;
    }
    if (!(e->flags & 4)) {
        return 0;
    }
    fn = e->fn;
    if (fn == NULL) {
        return -2;
    }
    return fn(arg1, arg2, arg3);
}

s32 TLobby__sub_80409E18(s16 arg0, s32 arg1, s32 arg2) {
    s32 (*fn)(s32, s32);

    if (arg0 < 0 || arg0 > TBL_80409E18.count) {
        return -0x10F;
    }
    Ent_80409E18 *e = TBL_80409E18.ents;
    e += arg0;
    if (e->active == 0) {
        return -2;
    }
    if (!(e->flags & 4)) {
        return 0;
    }
    fn = e->fn;
    if (fn == NULL) {
        return -2;
    }
    return fn(arg1, arg2);
}

s32 TLobby__sub_80409EB0(s16 arg0, s32 arg1) {
    s32 (*fn)(s32);

    if (arg0 < 0 || arg0 > TBL_80409EB0.count) {
        return -0x10F;
    }
    Ent_80409EB0 *e = TBL_80409EB0.ents;
    e += arg0;
    if (e->active == 0) {
        return -2;
    }
    if (!(e->flags & 4)) {
        return 0;
    }
    fn = e->fn;
    if (fn == NULL) {
        return -2;
    }
    return fn(arg1);
}

#pragma opt_propagation off
s16 TLobby::invoke_socket_callback(s16 i, s32 arg) {
    Ent_80409F44 *e;
    if (i < 0 || i > (*(Tbl_80409F44 *)&lobby_handler_table_desc).count) {
        return -0x10F;
    }
    e = (*(Tbl_80409F44 *)&lobby_handler_table_desc).list + i;
    if (e->st == 0) {
        return -2;
    }
    if (e->f10 == 0) {
        return -2;
    }
    return e->f10(arg);
}

s32 TLobby::call_entry_callback(s16 i, s16 arg) {
    Ent_80409FC4 *e;
    if (i < 0 || i > (*(Tbl_80409FC4 *)&lobby_handler_table_desc).count) {
        return -0x10F;
    }
    e = (*(Tbl_80409FC4 *)&lobby_handler_table_desc).list + i;
    if (e->st == 0) {
        return -2;
    }
    if (e->fC == 0) {
        return -2;
    }
    return e->fC(arg);
}

s16 TLobby__sub_8040A044(s16 i, s32 type, s16 len, u8 *addr) {
    Ent_8040A044 *e;
    s16 (*fn)(s16, s32, s16, u8 *);
    if (i < 0 || i > (*(Tbl_8040A044 *)&lobby_handler_table_desc).count) {
        return -0x10F;
    }
    e = (*(Tbl_8040A044 *)&lobby_handler_table_desc).list + i;
    if (e->st == 0) {
        return -2;
    }
    fn = e->f8;
    if (fn == NULL) {
        return -2;
    }
    return fn(i, type, len, addr);
}

s32 TLobby__sub_8040A0C0(s16 i, u8 *buf) {
    Ent_8040A044 *e;
    s32 (*fn)(s16, u8 *);
    if (i < 0 || i > (*(Tbl_8040A044 *)&lobby_handler_table_desc).count) {
        return -0x10F;
    }
    e = (*(Tbl_8040A044 *)&lobby_handler_table_desc).list + i;
    if (e->st == 0) {
        return -2;
    }
    fn = e->f4;
    if (fn == NULL) {
        return -2;
    }
    return fn(i, buf);
}

#pragma opt_propagation reset
#pragma push
#pragma optimization_level 2
s16 TLobby::is_slot_flag_0x40_set(s16 i) {
    if (i < 0 || i > (*(G_8040A13C *)&lobby_handler_table_desc).n) { return 0; }
    Ent_8040A13C *e = (*(G_8040A13C *)&lobby_handler_table_desc).p;
    if (e[i].f0 == 0) { return 0; }
    if (e[i].f2 & 0x40) { return 1; }
    return 0;
}

s32 TLobby::is_slot_flag_0x20_set(s16 i) {
    Ent_8040A19C *e;
    if (i < 0 || i > (*(G_8040A19C *)&lobby_handler_table_desc).n) { return 0; }
    e = (*(G_8040A19C *)&lobby_handler_table_desc).p;
    if (e[i].f0 == 0) { return 0; }
    e = &e[i];
    if (e->f2 & 0x20) { return 1; }
    return 0;
}

s16 TLobby::is_entry_flag10_set(s16 i) {
    if (i < 0 || i > (*(G_8040A1FC *)&lobby_handler_table_desc).n) { return 0; }
    Ent_8040A1FC *e = (*(G_8040A1FC *)&lobby_handler_table_desc).p;
    if (e[i].f0 == 0) { return 0; }
    if (e[i].f2 & 0x10) { return 1; }
    return 0;
}

s16 is_socket_flag_set__6TLobbyFs(s16 i) {
    if (i < 0 || i > (*(G_8040A25C *)&lobby_handler_table_desc).n) { return 0; }
    Ent_8040A25C *e = (*(G_8040A25C *)&lobby_handler_table_desc).p;
    if (e[i].f0 == 0) { return 0; }
    if (e[i].f2 & 1) { return 1; }
    return 0;
}

#pragma pop
s16 TLobby__sub_8040A2BC(Fn_8040881C *fns, s16 kind) {
    Ent_8040A044 *e;
    s16 i;

    if (fns == NULL || fns[1] == NULL) {
        return -2;
    }
    switch (kind) {
    case 1:
        e = (*(Tbl_8040A044 *)&lobby_handler_table_desc).list;
        if (e->st == 0) {
            NetMemcpy(&e->f4, fns, 0x2C);
            e->f2 = kind;
            e->st = 1;
            return 0;
        }
        return -2;
    default:
        for (i = 1, e = (*(Tbl_8040A044 *)&lobby_handler_table_desc).list + 1; i < (*(Tbl_8040A044 *)&lobby_handler_table_desc).count; i++, e++) {
            if (e->st == 0) {
                NetMemcpy(&e->f4, fns, 0x2C);
                e->f2 = kind;
                e->st = 1;
                return i;
            }
        }
        return -0x10F;
    }
}

s32 TLobby__sub_8040A3C0(void) {
    s32 ret;
    s16 i;
    Mgr_8040A3C0 *m = (Mgr_8040A3C0 *)&dns_resolver_state;
    DnsQuery *e;

    ret = TLobby__sub_80421844((s32)((void *)TLobby::tick_connection_timeouts));
    e = m->ents;
    i = 0;
    while (i < m->count) {
        if (e->active != 0) {
            NetConnectionCloseAndReset((DnsQuery *)e);
        }
        i++;
        e++;
    }
    TLobby__sub_803F86BC(m);
    return ret;
}

void TLobby::init_net_tables() {
    G_8040A45C *g = &dns_resolver_state;
    s16 i;

    NetMemset(&g->h0, 0, sizeof(G_8040A45C));
    NetInitNetworkConfig((Cfg_803F86C0 *)&g->h0);
    {
        DnsBuffer *p = g->a;
        i = 0;
        while (i < g->na) {
            p->used = 0;
            p->data = (u8 *)(g->base + g->step * i);
            i++;
            p++;
        }
    }
    {
        Rec_8040B33C *p = g->b;
        i = 0;
        while (i < g->nb) {
            p->f0 = 0;
            i++;
            p++;
        }
    }
    {
        C_8040A45C *p = g->c;
        i = 0;
        while (i < g->nc) {
            p->f0 = 0;
            i++;
            p->f20 = 0;
            p++;
        }
    }
    {
        D_8040A45C *p = g->d;
        i = 0;
        while (i < g->nd) {
            p->f0 = 0;
            i++;
            p->f104 = 0;
            p->f204 = 0;
            p->f208 = 0;
            p++;
        }
    }
    {
        E_8040A45C *p = g->e;
        i = 0;
        while (i < g->ne) {
            p->f0 = 0;
            i++;
            p->f18 = 0;
            p->f1C = 0;
            p++;
        }
    }
    {
        DnsQuery *p = g->f;
        i = 0;
        while (i < g->nf) {
            p->index = i;
            i++;
            p->active = 0;
            p->socket = -1;
            p->id = 0;
            p->waiter = -1;
            p->status = -65;
            p->outstanding = 0;
            p->message = 0;
            p->reply = 0;
            p->req.lookup.cb = 0;
            p->req.ptr.cb = 0;
            p++;
        }
    }
    TLobby__sub_804218AC(TLobby::tick_connection_timeouts, 1000);
}

#pragma opt_propagation off
s32 TLobby::close_connection_by_index(s16 i) {
    G_8040A630 *g = (G_8040A630 *)&dns_resolver_state;
    if (i < 0 || i > g->n) { return -2; }
    DnsQuery *e = (DnsQuery *)((u8 *)g->p + i * 0x3C);
    if (e->active == 0) { return -2; }
    return NetConnectionCloseAndReset((DnsQuery *)e);
}

s16 TLobby__sub_8040A698(s16 idx, void *buf, s16 *len, void *buf2, s16 *len2, u32 mode) {
    G_8040A45C *g = &dns_resolver_state;
    DnsQuery *f;
    DnsQuery *e;
    DnsLookupRequest *req;
    s16 st;

    if (idx < 0 || idx >= g->nf) {
        return -2;
    }
    f = &g->f[idx];
    e = (DnsQuery *)f;
    if (f->active == 0) {
        return -2;
    }
    if (e->kind != 1) {
        return -2;
    }
    if (len == NULL) {
        return -2;
    }
    if (buf != NULL && *len <= 0) {
        return -2;
    }
    if (buf2 != NULL && (len2 == NULL || *len2 < 0)) {
        return -2;
    }
    req = &e->req.lookup;
    req->addrs = (NetworkAddress *)buf;
    req->naddrs = *len;
    req->cname = (u8 *)buf2;
    if (len2 != NULL) {
        req->cname_len = *len2;
    } else {
        req->cname_len = 0;
    }
    req->cb = (DnsLookupCallback)mode;
    if (mode == 0) {
        TLobby__sub_80421814();
        if (e->status > 0 || e->outstanding > 0) {
            if (e->waiter != 0xFFFFFFFF) {
                TLobby__sub_804217E4();
                return -2;
            }
            NetStoreCurrentThread((s32 *)&e->waiter);
            TLobby__sub_804217E4();
            NetSuspendCurrentThread();
        } else {
            TLobby__sub_804217E4();
        }
        st = e->status;
        if (st < 0) {
            return st;
        }
    } else if (mode == 0xFFFFFFFF) {
        st = e->status;
        if (st > 0 || e->outstanding > 0) {
            return -1;
        }
        if (st < 0) {
            return st;
        }
    } else {
        if (e->status <= 0 && e->outstanding <= 0) {
            NetDispatchRequestCallback((DnsQuery *)e, 1);
        }
        return -1;
    }
    TLobby__sub_8040C74C((DnsLookupRequest *)req);
    if (len2 != NULL) {
        *len2 = req->cname_len;
    }
    *len = req->naddrs;
    return 0;
}

static inline void claim_dns_query(G_8040A45C *state, DnsQuery *&query) {
    s16 i;
    TLobby__sub_80421814();
    query = state->f;
    for (i = 0; i < state->nf; i++, query++) {
        if (query->active == 0) {
            query->active = 1;
            break;
        }
    }
    TLobby__sub_804217E4();
    if (i == state->nf) {
        query = NULL;
    }
}

s16 TLobby__sub_8040A8B0(u8 *self, s16 idx, s32 type)
{
  union {
    G_8040A45C *state;
    Rec_8040B33C *server;
  } cursor;
  D_8040A45C *p;
  DnsBuffer *m;
  u8 *query_name;
  DnsQuery *e;
  s32 len;
  DnsLookupRequest *t;
  u32 ty;
  Rec_8040B33C *selected_server;
  s16 i;
  cursor.state = &dns_resolver_state;
  if (self == NULL)
  {
    return -2;
  }
  if ((idx <= 0) || (idx > cursor.state->max_name))
  {
    return -2;
  }
  switch (type)
  {
    case 0:

    case 4:

    case 6:
      break;

    default:
      return -2;

  }

  if (((s32) self[idx - 1]) == '.')
  {
    idx--;
  }
  claim_dns_query(cursor.state, e);
  if (e == (NULL))
  {
    return -0x40;
  }
  e->kind = 1;
  {
    len = idx;
    e->req.lookup.family = type;
    query_name = self;
    t = &e->req.lookup;
    p = find_host_8040A8B0(cursor.state, query_name, len);
    if (p != (NULL))
    {
      e->status = 0;
      t->host = p;
      ty = t->family;
      if (ty == 0)
      {
        if (p->f204 > 0)
        {
          return e->index;
        }
      }
      else
      {
        C_8040A45C *node;
        for (node = p->f208; node != (NULL); node = node->f20)
        {
          if (node->f4.f0 == ty)
          {
            return e->index;
          }
        }

      }
    }
    m = grab_slot_8040A8B0(cursor.state);
    e->message = (DnsBuffer *)m;
    if (m == (NULL))
    {
      NetConnectionCloseAndReset((DnsQuery *)e);
      return -0x43;
    }
    e->id = cursor.state->h0++;
    e->timer = cursor.state->fC[0];
    e->server = cursor.state->f18;
    e->status = 0;
    cursor.server = select_dns_lookup_server(cursor.state, e);
    selected_server = cursor.server;
    if (selected_server == NULL)
    {
      NetConnectionCloseAndReset((DnsQuery *)e);
      return -0x44;
    }
    e->socket = TUdpSocket__sub_80421DEC(0, 0, 0, 0x35, (s32)TLobby::complete_pending_request, TLobby__sub_8040B4BC);
    i = e->socket;
    if (i < 0)
    {
      NetConnectionCloseAndReset((DnsQuery *)e);
      return i;
    }
    if (t->host == (NULL))
    {
      p = (D_8040A45C *)TLobby__sub_8040C09C();
      p->name_len = idx;
      NetMemcpy(p->name, self, len);
      t->host = p;
    }
    switch (t->family)
    {
      case 0:
      {
        UdpBuf_8040AFE0 buf;
        NetDnsBuildQueryAAAA(e, query_name, idx);
        buf.len = e->message->len;
        buf.data = e->message->data;
        i = TUdpSocket__sub_80421BAC(e->socket, NULL, &selected_server->f0, 0, NULL, 1, &buf);
        if (i < 0)
        {
          e->timer = 1;
          e->status = e->status + 1;
        }
        else
        {
          e->timer = 2;
          e->outstanding = 1;
        }
        break;
      }

      case 4:
      {
        UdpBuf_8040AFE0 buf;
        NetDnsBuildQueryA(e, query_name, idx);
        buf.len = e->message->len;
        buf.data = e->message->data;
        i = TUdpSocket__sub_80421BAC(e->socket, NULL, &selected_server->f0, 0, NULL, 1, &buf);
        if (i < 0)
        {
          e->timer = 1;
        }
        e->status = e->status + 1;
        break;
      }

      case 6:
      {
        UdpBuf_8040AFE0 buf;
        NetDnsBuildQueryAAAA(e, query_name, idx);
        buf.len = e->message->len;
        buf.data = e->message->data;
        i = TUdpSocket__sub_80421BAC(e->socket, NULL, &selected_server->f0, 0, NULL, 1, &buf);
        if (i < 0)
        {
          e->timer = 1;
        }
        e->status = e->status + 1;
        break;
      }

    }

    {
      u32 pad[4];
    }
  }
  return e->index;
}

#pragma opt_propagation reset
s32 TLobby::clear_all_used_records() {
    Mgr_8040AD64 *g = (Mgr_8040AD64 *)&dns_resolver_state;
    s32 cnt;
    s16 i;
    Rec_8040AD64 *r;

    TLobby__sub_80421814();
    g->f18 = 0;
    cnt = 0;
    i = 0;
    r = g->recs;
    while (i < g->n) {
        if (r->used != 0) {
            r->used = 0;
            cnt++;
        }
        i++;
        r++;
    }
    TLobby__sub_804217E4();
    return cnt;
}

s16 TLobby__sub_8040ADE8(Rec_8040B33C *addr) {
    G_8040A45C *g;
    s16 ret;
    s16 i;
    Rec_8040B33C *p;
    Rec_8040B33C *slot;
    u32 family;

    switch (addr->f0) {
    case 4:
    case 6:
        break;
    default:
    case 0:
        return -2;
    }
    TLobby__sub_80421814();
    g = &dns_resolver_state;
    p = g->b;
    slot = NULL;
    for (i = 0; i < g->nb; i++, p++) {
        if (p->f0 == 0) {
            if (slot == NULL) {
                ret = i;
                slot = p;
            }
            continue;
        }
        family = addr->f0;
        if (family != p->f0) {
            continue;
        }
        if (compare_family_addr(family, addr, p) == 0) {
            ret = -2;
            slot = NULL;
            break;
        }
    }
    if (slot != NULL) {
        NetMemcpy(slot, addr, sizeof(Rec_8040B33C));
    } else {
        ret = -2;
    }
    TLobby__sub_804217E4();
    return ret;
}

void TLobby::tick_connection_timeouts() {
    Mgr_8040AF48 *g;
    Conn_8040AF48 *c;
    s16 i;

    TLobby__sub_8040B3B4();
    g = (Mgr_8040AF48 *)&dns_resolver_state;
    c = g->conns;
    i = 0;
    while (i < g->nconns) {
        if (c->state == 1 && c->timer > 0) {
            if (--c->timer <= 0) {
                reset_connection_requests__6TLobbyFPvs(c, 0);
            }
        }
        i++;
        c++;
    }
    TLobby__sub_8040AFE0();
}

void TLobby__sub_8040AFE0(void) {
    G_8040A45C *g;
    Rec_8040B33C *rec;
    s16 *nb;
    s16 i;
    DnsQuery *req;
    s16 r;
    s16 *fc;

    g = &dns_resolver_state;
    nb = &g->nb;
    i = 0;
    req = g->f;
    while (i < g->nf) {
        if (req->active == 1 && req->socket >= 0 && (req->status > 0 || req->outstanding > 0)) {
            if (--req->timer <= 0) {
                if (req->status >= g->lim) {
                    g->f18 = 0;
                    TLobby__sub_8040BE40(req, -0x45, 0);
                } else if (req->outstanding != 0) {
                    rec = find_next_active_record__6TLobbyFPv((A_8040B33C *)req);
                    if (rec == NULL) {
                        TLobby__sub_8040BE40(req, -0x44, 0);
                    } else {
                        g->f18 = req->status % *nb;
                        fc = g->fC;
                        req->timer = fc[req->status / *nb];
                        put_tag_8040AFE0(req, 1);
                        r = send_8040AFE0(req, rec);
                        if (r < 0) {
                            req->timer = 1;
                        }
                        req->outstanding = 0;
                        req->status++;
                    }
                } else {
                    TLobby__sub_8040B1C4(req);
                }
            }
        }
        i++;
        req++;
    }
}

static inline s16 dns_send_message(DnsQuery *query, Rec_8040B33C *server) {
    UdpBuf_8040AFE0 tmp;
    tmp.len = query->message->len;
    tmp.data = query->message->data;
    return TUdpSocket__sub_80421BAC(query->socket, NULL, &server->f0, 0, NULL, 1, &tmp);
}

extern void TLobby__sub_8040B1C4(DnsQuery *e)
{
    G_8040A45C *base;
    Rec_8040B33C *found;
    s16 ret;
    s16 *dp;

    base = &dns_resolver_state;
    if ((found = fnar_8040B1C4(base, e)) == NULL) {
        TLobby__sub_8040BE40(e, -0x44, 0);
        return;
    }
    dp = &base->nb;
    base->f18 = e->status % *dp;
    e->timer = base->fC[e->status / *dp];

    ret = dns_send_message(e, found);
    if (ret < 0) {
        e->timer = 1;
        e->status = e->status + 1;
        return;
    }
    if (e->kind == 1 && e->req.lookup.family == 0) {
        e->timer = 2;
        e->outstanding = 1;
        return;
    }
    e->status = e->status + 1;
}

Rec_8040B33C *find_next_active_record__6TLobbyFPv(A_8040B33C *a) {
    G_8040A45C *g = &dns_resolver_state;
    s16 n, t, i;
    for (i = 0; i < (n = g->nb); i++) {
        Rec_8040B33C *r = &g->b[(a->off + (t = a->idx)) % n];
        if (r->f0 != 0) {
            if (t < g->lim) {
                return r;
            }
            break;
        }
        a->idx = t + 1;
    }
    return 0;
}

void TLobby__sub_8040B3B4(void) {
    s16 n;
    s16 j;
    C_8040A45C *prev;
    G_8040A45C *g;
    C_8040A45C *dead;
    s16 i;
    C_8040A45C *c;
    D_8040A45C *q;

    g = &dns_resolver_state;
    for (i = 0, q = g->d; i < g->nd; i++, q++) {
        if (q->f0 != 1) {
            continue;
        }
        if ((n = q->f204) == 0) {
            continue;
        }
        c = q->f208;
        prev = NULL;
        for (j = 0; j < n && c != NULL; j++) {
            if (--c->f1C > 0) {
                prev = c;
                c = c->f20;
            } else {
                dead = c;
                c = c->f20;
                if (prev != NULL) {
                    prev->f20 = c;
                } else {
                    q->f208 = c;
                }
                q->f204--;
                dead->f0 = 0;
                dead->f20 = NULL;
            }
        }
        if (q->f204 <= 0) {
            TLobby__sub_8040C178((Query_8040C09C *)q, 0);
        }
    }
}

#pragma inline_depth(1)
s32 TLobby__sub_8040B4BC(s16 phase, u8 *record) {
    UdpRx_8040B4BC *rx = (UdpRx_8040B4BC *)record;
    G_8040A45C *g = &dns_resolver_state;
    DnsQuery *e;
    s16 len;
    DnsBuffer *b;

    if (rx->port != 53) {
        return 1;
    }
    e = find_req_8040B4BC(rx->sock);
    if (e == NULL) {
        return 1;
    }
    if (e->status < 0) {
        return 1;
    }
    len = rx->len;
    if (len > g->step) {
        return 1;
    }
    switch (phase) {
    case 0:
        b = alloc_rx_8040B4BC(g);
        e->reply = b;
        if (b == NULL) {
            return 1;
        }
        rx->buf = (s32)e->reply->data;
        return 0;
    default:
        e->reply->len = len;
        if (TLobby__sub_8040B8BC((DnsQuery *)e) < 0) {
            e->reply->used = 0;
            e->reply = NULL;
            return 1;
        }
        e->reply->used = 0;
        e->reply = NULL;
        if (e->outstanding == 0) {
            e->status = 0;
            NetDispatchRequestCallback((DnsQuery *)e, 0);
        }
        return 0;
    }
}

#pragma inline_depth(4)
void TLobby::complete_pending_request(s16 id) {
    DnsQuery *e;

    if ((e = find_8040B654(id)) != NULL) {
        e->timer = 1;
        if (e->status < 0) {
            NetDispatchRequestCallback((DnsQuery *)e, 0);
        }
    }
}

#pragma opt_propagation off
s32 NetDnsBuildQueryAAAA(DnsQuery *self, u8 *name, s16 len) {
    s32 TLobby__sub_8040B838(u8 *, u8 *, s16);
    DnsQuery *q = self;
    Hdr_8040B6E4 *h;
    u8 *body;
    s32 n;
    s16 total;
    QT_8040B6E4 qt;
    h = (Hdr_8040B6E4 *)q->message->data;
    h->id = q->id;
    body = h->body;
    h->f2 = 1;
    h->f3 = 0;
    h->qd = 1;
    h->an = 0;
    h->ns = 0;
    h->ar = 0;
    n = TLobby__sub_8040B838(body, name, len);
    qt.type = 0x1C;
    body += (s16)n;
    qt.cls = 1;
    total = n + 0xC;
    NetMemcpy(body, &qt, 4);
    q->message->len = total + 4;
    return 0;
}

s32 NetDnsBuildQueryA(DnsQuery *self, u8 *name, s16 len) {
    s32 TLobby__sub_8040B838(u8 *, u8 *, s16);
    DnsQuery *q = self;
    Hdr_8040B790 *h;
    u8 *body;
    s32 n;
    s16 total;
    QT_8040B790 qt;
    h = (Hdr_8040B790 *)q->message->data;
    h->id = q->id;
    body = h->body;
    h->f2 = 1;
    h->f3 = 0;
    h->qd = 1;
    h->an = 0;
    h->ns = 0;
    h->ar = 0;
    n = TLobby__sub_8040B838(body, name, len);
    qt.type = 1;
    body += (s16)n;
    qt.cls = 1;
    total = n + 0xC;
    NetMemcpy(body, &qt, 4);
    q->message->len = total + 4;
    return 0;
}

s32 TLobby__sub_8040B838(u8 *dst, u8 *src, s32 max)
{
    s8 c;
    s16 i;
    u8 n;
    u8 *len;
    s32 ret;
    len = dst;
    n = 0;
    i = 0;
    dst++;
    while (i < (s16)max) {
        c = *src;
        if (c == '.') {
            *len = n;
            len = dst;
            n = 0;
        } else {
            *dst = c;
            n++;
        }
        i++;
        dst++;
        src++;
    }
    if (n != 0) {
        *len = n;
        *dst = 0;
        ret = max + 2;
    } else {
        dst[-1] = 0;
        ret = max + 1;
    }
    return ret;
}

struct DnsWireHeader {
    u16 id;
    u8 flags;
    u8 response_flags;
    u16 question_count;
    u16 answer_count;
    u16 authority_count;
    u16 additional_count;
};

s16 TLobby__sub_8040B8BC(DnsQuery *self)
{
  struct DnsReplyInput {
      DnsQuery *query;
      DnsBuffer *buffer;
  } input;
  s32 len;
  DnsQuery *s;
  DnsWireHeader *hdr;
  u8 *new_var;
  u16 cnt;
  s16 n;
  u16 t;
  u8 *cur;
  s32 op;
  s32 r;
  input.query = self;
  s = input.query;
  input.buffer = s->reply;
  hdr = (DnsWireHeader *)input.buffer->data;
  len = input.buffer->len;
  if (hdr->id != (u16) s->id)
  {
    return -1;
  }
  if (!(hdr->flags & 0x80))
  {
    return -1;
  }
  op = hdr->response_flags & 0xF;
  switch (op)
  {
    case 1:
      TLobby__sub_8040BE40(s, -0x46, 0);
      return -1;

    case 3:
      TLobby__sub_8040BE40(s, -0x47, 0);
      return -1;

    case 2:

    case 4:

    case 5:

    default:
      s->timer = 1;
      return -1;

    case 0:
      if ((hdr->answer_count) == 0)
    {
      s->timer = 1;
      return -1;
    }
      break;

  }

  cur = (u8 *)(hdr + 1);
  len -= sizeof(DnsWireHeader);
  t = hdr->question_count;
  if (t != 0)
  {
    n = t;
    while (n > 0)
    {
      new_var = cur;
      r = TLobby__sub_8040BD40(s, new_var, len, 0) + 4;
      len -= r;
      cur += (s16) r;
      n--;
    }

  }
  cnt = hdr->answer_count;
  if (cnt != 0)
  {
    while (((s16) cnt) > 0)
    {
      r = TLobby__sub_8040BA38(s, cur, len);
      len -= r;
      cur += (s16) r;
      cnt--;
    }

  }
  return 0;
}

extern s32 TLobby__sub_8040BA38(DnsQuery *self, u8 *rr, s32 avail) {
    DnsRrHeader hdr;
    C_8040A45C rec;
    C_8040A45C *found;
    s16 m;
    D_8040A45C *host;
    s32 ret;
    s32 rdlength;

    ret = TLobby__sub_8040BD40(self, rr, avail, 0);
    m = (s16) ret;
    rr += m;
    m = (s16) avail;
    if (m < (s16) ret + 10) {
        return avail;
    }
    NetMemcpy(&hdr, rr, 10);
    ret += 10;
    rdlength = hdr.rdlength;
    if (m < (s16) ret + (s16) rdlength) {
        return avail;
    }
    ret += rdlength;
    switch (hdr.rclass) {
    case 1:
        switch (hdr.type) {
        case 1: {
            host = (D_8040A45C *)self->req.lookup.host;
            if (host == 0) {
                break;
            }
            rec.record_type = 1;
            rec.f4.f0 = 4;
            NetMemcpy(rec.f4.addr, rr + 10, 4);
            found = find_8040BA38(host, &rec);
            if (found == 0) {
                found = TLobby__sub_8040C248(host);
                if (found == 0) {
                    break;
                }
                found->f0 = 1;
                found->record_type = 1;
                found->f4.f0 = 4;
                NetMemcpy(found->f4.addr, rr + 10, 4);
                found->f24 = host;
                append_to_list__6TLobbyFPvPv((O_8040C4B0 *)host, (N_8040C4B0 *)found);
            }
            found->f1C = hdr.ttl;
            break;
        }
        case 5: {
            host = (D_8040A45C *)self->req.lookup.host;
            if (host != 0 && (s8) host->canonical_name[0] == 0) {
                TLobby__sub_8040BD40(self, rr + 10, rdlength, host->canonical_name);
            }
            break;
        }
        case 0x1c: {
            host = (D_8040A45C *)self->req.lookup.host;
            if (host == 0) {
                break;
            }
            rec.record_type = 0x1c;
            rec.f4.f0 = 6;
            NetMemcpy(rec.f4.addr, rr + 10, 0x10);
            found = find_8040BA38(host, &rec);
            if (found == 0) {
                found = TLobby__sub_8040C248(host);
                if (found == 0) {
                    break;
                }
                found->f0 = 1;
                found->record_type = 0x1c;
                found->f4.f0 = 6;
                NetMemcpy(found->f4.addr, rr + 10, 0x10);
                found->f24 = host;
                append_to_list__6TLobbyFPvPv((O_8040C4B0 *)host, (N_8040C4B0 *)found);
            }
            found->f1C = hdr.ttl;
            break;
        }
        case 12: {
            E_8040A45C *ptr = self->req.ptr.entry;
            if (ptr != 0) {
                ptr->f18 = hdr.ttl;
                TLobby__sub_8040BD40(self, rr + 10, rdlength, ptr->wire_name);
            }
            break;
        }
        }
        break;
    }
    return ret;
}

#pragma opt_propagation reset
#pragma opt_lifetimes off
extern s32 TLobby__sub_8040BD40(DnsQuery *self, u8 *p, s32 n, u8 *dst)
{
  s32 offset;
  s32 count;
  s16 limit;
  u8 *data;
  u8 c;
  u8 *d;
  u8 c2;
  u8 *s;
  s32 len;
  count = 0;
  limit = (s16) n;
  while ((s16) count < limit)
  {
    c = *p;
    if (c == 0)
    {
      count++;
      break;
    }
    if (c & 0xC0)
    {
      limit = offset = ((c & ~0xC0) << 8) | p[1];
      s = data = self->reply->data;
      s += (u16) limit;
      c2 = *s;
      d = dst;
      while (c2 != 0)
      {
        if (d != 0)
        {
          len = c2 + 1;
          NetMemcpy(d, s, len);
          d += len;
        }
        s += c2 + 1;
        c2 = *s;
      }
      count += 2;
      break;
    }
    if (dst != 0)
    {
      len = c + 1;
      NetMemcpy(dst, p, len);
      dst += len;
    }
    count += c;
    p += c + 1;
    count++;
  }
  return count;
}

#pragma opt_lifetimes reset
void TLobby__sub_8040BE40(DnsQuery *req, s16 err, s16 arg) {
    E_8040A45C *c;
    D_8040A45C *q;

    switch (req->kind) {
    case 1:
        q = req->req.lookup.host;
        if (q != NULL) {
            req->req.lookup.host = NULL;
            TLobby__sub_8040C178((Query_8040C09C *)q, arg);
        }
        break;
    case 12:
        c = req->req.ptr.entry;
        if (c != NULL) {
            req->req.ptr.entry = NULL;
            reset_requests_8040BE40(c, arg);
        }
        break;
    }
    req->status = err;
    req->outstanding = 0;
    NetDispatchRequestCallback((DnsQuery *)req, arg);
}

s32 NetConnectionCloseAndReset(DnsQuery *self) {
    u8 *arg0 = (u8 *)self;
    s16 *temp_r3_2;
    s16 *temp_r3_3;
    s32 temp_r3;
    s32 var_r31;
    var_r31 = close_8040BF38(arg0, *(s16 *)(arg0 + 4));
    TLobby__sub_80421814();
    temp_r3_2 = (s16 *)(*(s16 **)((s8 *)arg0 + 0x18));
    if (temp_r3_2 != NULL) {
        *(s16 *)((s8 *)temp_r3_2 + 0) = 0;
        *(s16 **)((s8 *)arg0 + 0x18) = NULL;
    }
    temp_r3_3 = (s16 *)(*(s16 **)((s8 *)arg0 + 0x1C));
    if (temp_r3_3 != NULL) {
        *(s16 *)((s8 *)temp_r3_3 + 0) = 0;
        *(s16 **)((s8 *)arg0 + 0x1C) = NULL;
    }
    *(s32 *)((s8 *)arg0 + 0x34) = 0;
    *(s32 *)((s8 *)arg0 + 0x28) = 0;
    *(s32 *)((s8 *)arg0 + 0x38) = 0;
    *(s32 *)((s8 *)arg0 + 0x2C) = 0;
    *(s16 *)(arg0 + 0) = 0;
    *(s16 *)(arg0 + 8) = 0;
    *(s16 *)(arg0 + 0x10) = -0x41;
    *(s16 *)((s8 *)arg0 + 0x12) = 0;
    if (*(u32 *)(arg0 + 0xC) != 0xFFFFFFFFU) {
        TLobby::resume_thread((s32)(*(u32 *)(arg0 + 0xC)));
        *(s32 *)(arg0 + 0xC) = -1;
    }
    TLobby__sub_804217E4();
    return var_r31;
}

void reset_connection_requests__6TLobbyFPvs(Conn_8040AF48 *o_, s16 arg1) {
    s16 i;
    DnsQuery *e;

    ((O_8040C00C *)o_)->f0 = 0;
    ((O_8040C00C *)o_)->f18 = 0;
    ((O_8040C00C *)o_)->f1C = 0;
    i = 0;
    e = ((G_8040C00C *)&dns_resolver_state)->ents;
    while (i < ((G_8040C00C *)&dns_resolver_state)->count) {
        if (e->req.ptr.entry == (E_8040A45C *)o_) {
            e->status = -0x42;
            e->outstanding = 0;
            e->req.ptr.entry = 0;
            NetDispatchRequestCallback((DnsQuery *)e, arg1);
        }
        i++;
        e++;
    }
}

Query_8040C09C *TLobby__sub_8040C09C(void) {
    s16 i = 0;
    Query_8040C09C *best = NULL;
    Query_8040C09C *q = ((G_8040C09C *)&dns_resolver_state)->queries;

    for (; i < ((G_8040C09C *)&dns_resolver_state)->nqueries; i++, q++) {
        if (q->f0 == 0) {
            q->f0 = 1;
            return q;
        }
        if (best == NULL) {
            best = q;
        } else if (best->f204 != 0 && q->f204 != 0) {
            s32 q_time = q->f208->f1C;
            s32 best_time = best->f208->f1C;
            if (q_time < best_time) {
                best = q;
            }
        } else if (q->f204 != 0) {
            best = q;
        }
    }
    TLobby__sub_8040C178(best, 1);
    best->f0 = 1;
    return best;
}

void TLobby__sub_8040C178(Query_8040C09C *q, s16 arg1) {
    G_8040C09C *state = (G_8040C09C *)&dns_resolver_state;
    s16 i;
    DnsQuery *e;
    Node_8040C09C *n;
    Node_8040C09C *cur;

    q->f0 = 0;
    q->f104 = 0;
    q->f204 = 0;
    n = q->f208;
    i = 0;
    while (n != NULL && i < state->nnodes) {
        cur = n;
        n = n->next;
        i++;
        cur->f0 = 0;
        cur->next = NULL;
    }
    q->f208 = NULL;
    i = 0;
    e = state->ents;
    while (i < state->nents) {
        if (e->req.lookup.host == (D_8040A45C *)q) {
            e->status = -0x42;
            e->outstanding = 0;
            e->req.lookup.host = NULL;
            NetDispatchRequestCallback((DnsQuery *)e, arg1);
        }
        i++;
        e++;
    }
}

C_8040A45C *TLobby__sub_8040C248(D_8040A45C *q) {
    G_8040A45C *g;
    C_8040A45C *best;
    s16 i;
    C_8040A45C *c;

    if (q == NULL) {
        return NULL;
    }
    g = &dns_resolver_state;
    c = g->c;
    best = NULL;
    for (i = 0; i < g->nc; i++, c++) {
        if (c->f0 == 0) {
            c->f0 = 1;
            c->f20 = NULL;
            return c;
        }
        if (c->f24 == q) {
            continue;
        }
        if (best == NULL) {
            best = c;
        } else if (c->f1C < best->f1C) {
            best = c;
        }
    }
    if (best == NULL) {
        return NULL;
    }
    if (TLobby__sub_8040C340(best->f24, best) < 0) {
        return NULL;
    }
    best->f0 = 1;
    best->f20 = NULL;
    return best;
}

s16 TLobby__sub_8040C340(D_8040A45C *self_m, C_8040A45C *arg) {
G_8040A45C *tbl;
C_8040A45C *node;
C_8040A45C *prev;
u8 *key;
s16 i;
s32 r;
if (arg == ((void *) 0))
{
return -1;
}
if (self_m == ((void *) 0))
{
return -1;
}
if ((self_m->f0 == 0) || (self_m->f208 == ((void *) 0)))
{
return -1;
}
node = self_m->f208;
tbl = &dns_resolver_state;
key = arg->f4.addr;
prev = (C_8040A45C *)((void *) 0);
for (i = 0; (node != ((void *) 0)) && (i < tbl->nc); node = node->f20, (unsigned long long) (i++))
{
switch ((s32) node->f4.f0)
{
case 4:
if (arg->f4.f0 != 4)
{
r = -1;
}
else
{
r = NetMemcmp((void *)(node->f4.addr), (void *)(key), (int)(4));
}
break;
case 6:
if (arg->f4.f0 != 6)
{
r = -1;
}
else
{
r = NetMemcmp((void *)(node->f4.addr), (void *)(key), (int)(0x10));
}
break;
case 0:
default:
r = -1;
break;
}
if (r != 0)
{
prev = node;
}
else
{
self_m->f204--;
if (prev == ((void *) 0))
{
self_m->f208 = node->f20;
}
else
{
prev->f20 = node->f20;
}
node->f0 = 0;
node->f20 = (C_8040A45C *)((void *) 0);
return 0;
}
}
return -1;
}

s32 append_to_list__6TLobbyFPvPv(O_8040C4B0 *o, N_8040C4B0 *n) {
    s16 i;
    N_8040C4B0 *p;

    if (o == NULL || n == NULL) {
        return -1;
    }
    if (o->head == NULL) {
        o->count = 1;
        o->head = n;
        return 0;
    }
    for (p = o->head, i = 0; i < ((G_8040C4B0 *)&dns_resolver_state)->lim; i++) {
        if (p->next == NULL) {
            o->count++;
            p->next = n;
            return 0;
        }
        p = p->next;
    }
    return -1;
}

void NetDispatchRequestCallback(DnsQuery *self, s16 status) {
    DnsQuery *connection = (DnsQuery *)self;
    DnsLookupRequest *a;
    DnsPtrRequest *b;
    s32 err;

    switch (connection->kind) {
    case 1:
        a = &connection->req.lookup;
        if ((u32)a->cb == 0xFFFFFFFFU) {
            return;
        }
        if (a->cb == NULL) {
            if (status != 0) {
                TLobby__sub_80421814();
                if (connection->waiter != 0xFFFFFFFFU) {
                    TLobby::resume_thread(connection->waiter);
                    connection->waiter = -1;
                }
                TLobby__sub_804217E4();
                return;
            }
            if (connection->waiter != 0xFFFFFFFFU) {
                TLobby::resume_thread(connection->waiter);
                connection->waiter = -1;
            }
            return;
        }
        err = connection->status;
        if ((s16)err < 0) {
            a->cb(connection->index, a->addrs, err, a->cname, 0);
        } else {
            TLobby__sub_8040C74C(a);
            a->cb(connection->index, a->addrs, a->naddrs, a->cname, a->cname_len);
        }
        a->cb = NULL;
        break;
    case 12:
        b = &connection->req.ptr;
        if ((u32)b->cb == 0xFFFFFFFFU) {
            return;
        }
        if (b->cb == NULL) {
            if (status != 0) {
                TLobby__sub_80421814();
                if (connection->waiter != 0xFFFFFFFFU) {
                    TLobby::resume_thread(connection->waiter);
                    connection->waiter = -1;
                }
                TLobby__sub_804217E4();
                return;
            }
            if (connection->waiter != 0xFFFFFFFFU) {
                TLobby::resume_thread(connection->waiter);
                connection->waiter = -1;
            }
            return;
        }
        err = connection->status;
        if ((s16)err < 0) {
            b->cb(connection->index, b->name, err);
        } else {
            if (b->entry == NULL) {
                b->len = -0x42;
            } else if (b->name == 0) {
                b->len = TLobby__sub_8040C978(b->entry->wire_name);
            } else {
                b->len = TLobby__sub_8040C8A8((u8 *)b->name, b->entry->wire_name, b->len);
            }
            b->cb(connection->index, b->name, b->len);
        }
        b->cb = NULL;
        break;
    }
}

void TLobby__sub_8040C74C(DnsLookupRequest *a) {
    s16 n;
    s8 *s;
    s32 len;
    s16 i;
    D_8040A45C *q;
    s16 cnt;
    u8 *out;
    C_8040A45C *node;

    q = a->host;
    if (q == NULL) {
        a->naddrs = -0x42;
        return;
    }
    s16 max;
    if (q->f104 != 0 && (max = a->cname_len) != 0) {
        if (a->cname == 0) {
            s = &q->f104;
            n = 0;
            while (n < 0xFF) {
                s8 c = *s++;
                if (c == 0) {
                    n--;
                    break;
                }
                len = c;
                if (n + len + 1 <= 0xFF) {
                    s += len;
                } else {
                    n = 0xFF;
                    break;
                }
                n += len + 1;
            }
            a->cname_len = n;
        } else {
            a->cname_len = TLobby__sub_8040C8A8((u8 *)a->cname, (u8 *)&q->f104, max);
        }
    } else {
        a->cname_len = 0;
    }
    out = (u8 *)a->addrs;
    cnt = 0;
    node = q->f208;
    for (i = 0; i < q->f204; i++, node = node->f20) {
        if (a->family == 0 || a->family == node->f4.f0) {
            cnt++;
            if (out != NULL) {
                NetMemcpy(out, &node->f4, sizeof(Rec_8040B33C));
                out += sizeof(Rec_8040B33C);
                if (cnt >= a->naddrs) {
                    break;
                }
            }
        }
    }
    a->naddrs = cnt;
}

#pragma push
#pragma optimization_level 2
#pragma opt_common_subs off
s16 TLobby__sub_8040C8A8(u8 *dst, u8 *src, s16 max) {
    s32 limit = max;
    s32 n;
    s16 len = 0;

    while (len < limit) {
        s8 c = *src++;
        if (c == 0) {
            *dst = 0;
            return --len;
        }
        n = c;
        if (limit >= len + n + 1) {
            NetMemcpy(dst, src, n);
            dst += n;
            *dst = '.';
            src += n;
            dst++;
        } else {
            NetMemcpy(dst, src, limit - len);
            return max;
        }
        len += n + 1;
    }
    return len;
}

#pragma pop
s16 TLobby__sub_8040C978(u8 *name) {
    s32 n;
    s16 len = 0;

    while (len < 0xFF) {
        s8 c = *name++;
        if (c == 0) {
            return --len;
        }
        n = c;
        if (0xFF >= len + n + 1) {
            name += n;
        } else {
            return 0xFF;
        }
        len += n + 1;
    }
    return len;
}

s32 TLobby__sub_8040C9E0(u8 *arg0, u8 *arg1) {
    struct Fields_arg0 { u8 pad_0[4]; s32 field_4; u8 pad_8[16]; u16 field_18; };
    struct Fields_arg1 { u8 pad_0[4]; u32 field_4; u8 pad_8[16]; u16 field_18; };
    s32 var_r5;
    u8 *var_r3;
    u8 *var_r4;
    switch ((s32) (((Fields_arg0*)arg0)->field_18)) {
    case 1:
        if ((u16) ((Fields_arg1*)arg1)->field_18 != 1) {
            var_r3 = (u8 *)((void *)-1);
            return -1;
        }
        switch (((Fields_arg0*)arg0)->field_4) {
        case 4:
            if ((u32) ((Fields_arg1*)arg1)->field_4 != 4U) {
                var_r3 = (u8 *)((void *)-1);
                return -1;
            }
            var_r3 = (u8 *)(arg0 + 8);
            var_r4 = (u8 *)(arg1 + 8);
            var_r5 = 4;
            return NetMemcmp((void *)(var_r3), (void *)(var_r4), 4);
        case 6:
            if ((u32) ((Fields_arg1*)arg1)->field_4 != 6U) {
                var_r3 = (u8 *)((void *)-1);
                return -1;
            }
            var_r3 = (u8 *)(arg0 + 8);
            var_r4 = (u8 *)(arg1 + 8);
            var_r5 = 0x10;
            return NetMemcmp((void *)(var_r3), (void *)(var_r4), 0x10);
        default:
        case 0:
            var_r3 = (u8 *)((void *)-1);
            return -1;
        }
        break;
    case 28:
        if ((u16) ((Fields_arg1*)arg1)->field_18 != 0x1C) {
            var_r3 = (u8 *)((void *)-1);
            return -1;
        }
        switch (((Fields_arg0*)arg0)->field_4) {
        case 4:
            if ((u32) ((Fields_arg1*)arg1)->field_4 != 4U) {
                var_r3 = (u8 *)((void *)-1);
                return -1;
            }
            var_r3 = (u8 *)(arg0 + 8);
            var_r4 = (u8 *)(arg1 + 8);
            var_r5 = 4;
            return NetMemcmp((void *)(var_r3), (void *)(var_r4), 4);
        case 6:
            if ((u32) ((Fields_arg1*)arg1)->field_4 != 6U) {
                var_r3 = (u8 *)((void *)-1);
                return -1;
            }
            var_r3 = (u8 *)(arg0 + 8);
            var_r4 = (u8 *)(arg1 + 8);
            var_r5 = 0x10;
            return NetMemcmp((void *)(var_r3), (void *)(var_r4), 0x10);
        default:
        case 0:
            var_r3 = (u8 *)((void *)-1);
            return -1;
        }
        break;
    default:
        var_r3 = (u8 *)((void *)-1);
        return -1;
    }
}

s16 TLobby__sub_8040CB44(u8 *self, u32 d, u32 c)
{
  s16 TLobby__sub_8040CFE8(u8 type, u8 code, u32 src, u32 dst, NetPacket *pkt);
  s32 TLobby__sub_8040F8A4(u32, u32, u32, u16, u32);
  s32 TLobby__sub_80420D38(u16, u8);
  NetPacketFragment *p;
  u8 stream[0xc];
  u8 hdr[8];
  u32 *new_var;
  u8 ip[24];
  u8 udp[8];
  u8 addr[4];
  u8 pad[12];
  NetPacketFragment *q;
  s16 r;
  u32 i;
  NetPacketFragment *rec;
  NetPacket *out;
  unsigned int a;
  u32 net;
  u32 mask;
  NetPacket *pkt = (NetPacket *)self;
  rec = &pkt->fragments[1];
  NetBufferRefInitKind1((NetBufferRef *)stream, (s32) hdr);
  TLobby__sub_80406FD8(stream, &rec->buffer, 8);
  if (NetPacketChecksum((NetPacket *)self, 0) != 0)
  {
    return -1;
  }
  switch (hdr[0])
  {
    case 0:

    case 4:

    case 11:

    case 12:

    case 13:

    case 14:

    case 17:

    case 18:
      break;

    case 8:
      out = TLobby::alloc_free_entry();
      if (out == ((void *) 0))
    {
      return -0x101;
    }
      out->fragment_count = pkt->fragment_count - 1;
      out->total_bytes = pkt->total_bytes - pkt->fragments[0].length;
      p = (pkt->fragments - 1) + pkt->fragment_count;
      for (i = 0, q = out->fragments - 1; i < out->fragment_count; i++)
    {
      q[1].length = p->length;
      NetMemcpy(&q[1].buffer, &(--p)[1].buffer, 8);
      q++;
    }

      r = TLobby__sub_8040CFE8(0, 0, c, d, out);
      if (r < 0)
    {
      NetReleasePacket(out);
      return r;
    }
      NetReleasePacket(out);
      return 0;

    case 3:
      TLobby__sub_80406EB8(&rec->buffer, 8);
      NetBufferRefInitKind1((NetBufferRef *)stream, (s32) ip);
      TLobby__sub_80406FD8(stream, &rec->buffer, 20);
      TLobby__sub_80406EB8(&rec->buffer, (ip[0] & 0xf) << 2);
      switch (ip[9])
    {
      case 6:
        break;

      case 17:
        NetBufferRefInitKind1((NetBufferRef *)stream, (s32) udp);
        TLobby__sub_80406FD8(stream, &rec->buffer, 8);
        TLobby__sub_80420D38(*((u16 *) udp), hdr[1]);
        break;

    }

      return 0;

    case 5:
      TLobby__sub_80406EB8(&rec->buffer, 8);
      NetBufferRefInitKind1((NetBufferRef *)stream, (s32) ip);
      TLobby__sub_80406FD8(stream, &rec->buffer, 20);
      switch (hdr[1])
    {
      case 0:

      case 2:
        NetMemcpy(addr, hdr + 4, 4);
        a = *((u32 *) (ip + 16));
        net = ((a & 0x80000000) == 0) ? (a & 0xFF000000) : (((a & 0xC0000000) == 0x80000000) ? (a & 0xFFFF0000) : (((a & 0xE0000000) == 0xC0000000) ? (a & 0xFFFFFF00) : (0)));
        new_var = (u32 *) addr;
        mask = ((a & 0x80000000) == 0) ? (0xFF000000) : (((a & 0xC0000000) == 0x80000000) ? (0xFFFF0000) : (((a & 0xE0000000) == 0xC0000000) ? (0xFFFFFF00) : (0)));
        TLobby__sub_8040F8A4(net, (*new_var), mask, 2, d);
        break;

      case 1:

      case 3:
        NetMemcpy(addr, hdr + 4, 4);
        TLobby__sub_8040F8A4(*((u32 *) (ip + 16)), (*((u32 *) addr)), -1, 6, d);
        break;

    }

      return 0;

    default:
      return -1;

  }

  return 0;
}

s32 TUdpSocket__sub_8040CE58(Icmp4Header *icmp, Ipv4Header *ip, s16 len, s16 idx) {
    s16 NetIPv4IsUnspecified(u32 arg0);
    s16 NetIPv4IsLoopback(u32 arg0);
    s16 TLobby__sub_8040FDA0(u32, s16);
    s32 TLobby__sub_8040E780(NetPacket *, u32, u32, s32, s32, s32, s32);
    NetPacket *pkt;
    s16 hlen;
    s32 ret;

    if (NetIPv4IsUnspecified(ip->src) || NetIPv4IsLoopback(ip->src) || TLobby__sub_8040FDA0(ip->src, idx)) {
        return -1;
    }
    if (TLobby__sub_8040FDA0(ip->dst, idx)) {
        return -1;
    }
    pkt = TLobby::alloc_free_entry();
    if (pkt == NULL) {
        return -1;
    }
    hlen = (ip->version_ihl & 0xF) << 2;
    len = len < hlen + 8 ? len : hlen + 8;
    pkt->fragment_count = 0;
    pkt->total_bytes = len;
    pkt->fragments[pkt->fragment_count].length = len;
    NetBufferRefInitKind1(&pkt->fragments[pkt->fragment_count].buffer, (s32)ip);
    pkt->fragment_count++;
    pkt->total_bytes += sizeof(Icmp4Header);
    pkt->fragments[pkt->fragment_count].length = sizeof(Icmp4Header);
    NetBufferRefInitKind1(&pkt->fragments[pkt->fragment_count].buffer, (s32)icmp);
    pkt->fragment_count++;
    icmp->checksum = 0;
    icmp->checksum = NetPacketChecksum((NetPacket *)pkt, 1);
    ret = TLobby__sub_8040E780(pkt, ip->src, ip->dst, 0, 0, 0, 1);
    NetReleasePacket(pkt);
    return ret;
}

s16 TLobby__sub_8040CFE8(u8 type, u8 code, u32 src, u32 dst, NetPacket *pkt) {
    s16 TLobby__sub_8040E780(NetPacket *, u32, u32, s32, s32, s32, s32);
    NetBufferRef ref;
    Icmp4Header hdr;

    switch (type) {
    case 0:
        NetBufferRefInitKind1(&ref, (s32)&hdr);
        TLobby__sub_80406FD8(&ref, &pkt->fragments[pkt->fragment_count - 1].buffer, sizeof(hdr));
        TLobby__sub_80406EB8(&pkt->fragments[pkt->fragment_count - 1].buffer, sizeof(hdr));
        pkt->fragments[pkt->fragment_count - 1].length -= sizeof(hdr);
        pkt->fragments[pkt->fragment_count].length = sizeof(hdr);
        NetBufferRefInitKind1(&pkt->fragments[pkt->fragment_count].buffer, (s32)&hdr);
        pkt->fragment_count++;
        break;
    default:
        return -1;
    }
    hdr.type = type;
    hdr.code = code;
    hdr.checksum = 0;
    hdr.checksum = NetPacketChecksum((NetPacket *)pkt, 1);
    if (TLobby__sub_8040E780(pkt, dst, src, 0, 0, 0, 1)) {
        return -1;
    }
    return 0;
}

s16 NetIPv6HandleIcmpMessage(NetPacket *pkt, u8 *src, u8 *dst, u8 hop_limit, s16 iface) {
    s16 NetIPv6HandleRouterSolicitation(NetPacket *pkt, u8 *src, u8 *dst, s16 iface);
    s16 NetIPv6HandleRouterAdvertisement(NetPacket *pkt, u8 *src, u8 *dst, s16 iface);
    s16 NetIPv6HandleNeighborSolicitation(NetPacket *pkt, u8 *src, u8 *dst, s16 iface);
    s16 NetIPv6HandleNeighborAdvertisement(NetPacket *pkt, u8 *src, u8 *dst, s16 iface);
    s16 NetIPv6HandleRedirect(NetPacket *pkt, u8 *src, u8 *dst, s16 iface);
    s32 TLobby__sub_80411DEC(IPv6Address *addr, s16 mtu);
    void TLobby__sub_80420D38(u16 port, u8 code);
    s16 TLobby__sub_8040D718(u8 type, u8 code, u8 *src, u8 *dst, NetPacket *pkt, s16 idx);
    NetBufferRef ref;
    Ipv6Header_8040D120 ip;
    Icmp6ErrorInfo icmp;
    UdpHeader udp;
    NetPacketFragment *from;
    NetBufferRef *buf;
    s32 mtu;
    s16 r;
    u32 i;
    NetPacketFragment *body;
    NetPacket *reply;

    if (TLobby__sub_80411040((const IPv6Address *)src, (const IPv6Address *)dst, 0x3A, pkt, 0)) {
        return -1;
    }
    body = &pkt->fragments[1];
    NetBufferRefInitKind1(&ref, (s32)&icmp);
    TLobby__sub_80406FD8(&ref, &body->buffer, 8);
    switch (icmp.type) {
    case 128:
        reply = TLobby::alloc_free_entry();
        if (reply == NULL) {
            return -257;
        }
        reply->fragment_count = pkt->fragment_count - 1;
        reply->total_bytes = pkt->total_bytes - pkt->fragments[0].length;
        from = &pkt->fragments[pkt->fragment_count] - 1;
        for (i = 0; i < reply->fragment_count; i++) {
            reply->fragments[i].length = from->length;
            buf = &from->buffer;
            from--;
            NetMemcpy(&reply->fragments[i].buffer, buf, 8);
        }
        r = TLobby__sub_8040D718(0x81, 0, dst, src, reply, iface);
        NetReleasePacket(reply);
        return r;
    case 1:
        TLobby__sub_80406EB8(&body->buffer, 8);
        NetBufferRefInitKind1(&ref, (s32)&ip);
        TLobby__sub_80406FD8(&ref, &body->buffer, sizeof(ip));
        TLobby__sub_80406EB8(&body->buffer, sizeof(ip));
        switch (ip.next_header) {
        case 17:
            NetBufferRefInitKind1(&ref, (s32)&udp);
            TLobby__sub_80406FD8(&ref, &body->buffer, sizeof(udp));
            TLobby__sub_80420D38(udp.src_port, icmp.code);
            break;
        case 6:
            break;
        }
        return 0;
    case 2:
        mtu = icmp.pointer;
        if (mtu > 0 && mtu < 0x8000) {
            TLobby__sub_80406EB8(&body->buffer, 8);
            NetBufferRefInitKind1(&ref, (s32)&ip);
            TLobby__sub_80406FD8(&ref, &body->buffer, sizeof(ip));
            TLobby__sub_80411DEC(&ip.dst, mtu);
        }
        return 0;
    case 133:
        if (hop_limit != 255) {
            return -1;
        }
        switch (icmp.code) {
        case 0:
            r = NetIPv6HandleRouterSolicitation(pkt, src, dst, iface);
            if (r < 0) {
                return r;
            }
            break;
        }
        return 0;
    case 134:
        if (hop_limit != 255) {
            return -1;
        }
        switch (icmp.code) {
        case 0:
            r = NetIPv6HandleRouterAdvertisement(pkt, src, dst, iface);
            if (r < 0) {
                return r;
            }
            break;
        }
        return 0;
    case 135:
        if (hop_limit != 255) {
            return -1;
        }
        switch (icmp.code) {
        case 0:
            r = NetIPv6HandleNeighborSolicitation(pkt, src, dst, iface);
            if (r < 0) {
                return r;
            }
            break;
        }
        return 0;
    case 136:
        if (hop_limit != 255) {
            return -1;
        }
        switch (icmp.code) {
        case 0:
            r = NetIPv6HandleNeighborAdvertisement(pkt, src, dst, iface);
            if (r < 0) {
                return r;
            }
            break;
        }
        return 0;
    case 137:
        if (hop_limit != 255) {
            return -1;
        }
        switch (icmp.code) {
        case 0:
            r = NetIPv6HandleRedirect(pkt, src, dst, iface);
            if (r < 0) {
                return r;
            }
            break;
        }
        return 0;
    case 3:
    case 4:
    case 129:
        break;
    default:
        return 0;
    }
    return 0;
}

s16 TLobby__sub_8040D510(Icmp6ErrorInfo *err, u8 *hdr, s16 len, s16 idx) {
    s16 NetIPv6IsMulticast(u8 *addr);
    s16 NetIPv6IsUnspecified(u8 *addr);
    s16 TLobby__sub_80411F1C(u8 *, u8 *, s16);
    s16 TLobby__sub_80413D78(u8 *addr, s16 idx);
    u8 *src;
    NetPacket *pkt;
    u8 source[16];
    s32 excess;
    s16 over;
    s16 r;

    if (NetIPv6IsUnspecified(hdr + 8) || NetIPv6IsMulticast(hdr + 8) || TLobby__sub_80413D78(hdr + 8, idx)) {
        return -1;
    }
    if (NetIPv6IsMulticast(hdr + 0x18)) {
        switch (err->type) {
        case 3:
        default:
            return -1;
        case 2:
        case 4:
            r = TLobby__sub_80411F1C(source, hdr + 8, idx);
            if (r < 0) {
                return r;
            }
            break;
        }
    } else {
        NetMemcpy(source, hdr + 0x18, 0x10);
    }
    src = hdr + 8;
    pkt = TLobby::alloc_free_entry();
    if (pkt == NULL) {
        return -1;
    }
    pkt->fragment_count = 0;
    pkt->total_bytes = len;
    pkt->fragments[pkt->fragment_count].length = len;
    NetBufferRefInitKind1(&pkt->fragments[pkt->fragment_count].buffer, (s32)hdr);
    pkt->fragment_count++;
    pkt->total_bytes += sizeof(Icmp6ErrorInfo);
    pkt->fragments[pkt->fragment_count].length = sizeof(Icmp6ErrorInfo);
    NetBufferRefInitKind1(&pkt->fragments[pkt->fragment_count].buffer, (s32)err);
    pkt->fragment_count++;
    if (pkt->total_bytes + 0x28 > 0x500) {
        over = excess = pkt->total_bytes - 0x4D8;
        if (over > pkt->fragments[0].length) {
            return -1;
        }
        pkt->total_bytes -= over;
        pkt->fragments[0].length -= over;
    }
    err->checksum = 0;
    err->checksum = TLobby__sub_80411040((const IPv6Address *)source, (const IPv6Address *)src, 0x3A, pkt, 1);
    r = TLobby__sub_80410A98(pkt, src, source, NULL, 0x3A);
    NetReleasePacket(pkt);
    return r;
}

s16 TLobby__sub_8040D718(u8 type, u8 code, u8 *src, u8 *dst, NetPacket *pkt, s16 idx) {
    s16 NetIPv6IsMulticast(u8 *arg0);
    s16 NetIPv6IsUnspecified(u8 *arg0);
    s16 TLobby__sub_80411F1C(u8 *, u8 *, s16);
    Icmp6MessageHeader hdr;
    s16 r;

    if (NetIPv6IsMulticast(src) || NetIPv6IsUnspecified(src)) {
        r = TLobby__sub_80411F1C(src, dst, idx);
        if (r < 0) {
            return r;
        }
    }
    switch (type) {
    case 0x81:
        TLobby__sub_80406EB8(&pkt->fragments[pkt->fragment_count - 1].buffer, sizeof(hdr));
        pkt->fragments[pkt->fragment_count - 1].length -= sizeof(hdr);
        pkt->fragments[pkt->fragment_count].length = sizeof(hdr);
        NetBufferRefInitKind1(&pkt->fragments[pkt->fragment_count].buffer, (s32)&hdr);
        pkt->fragment_count++;
        break;
    default:
        return -1;
    }
    hdr.type = type;
    hdr.code = code;
    hdr.checksum = 0;
    hdr.checksum = TLobby__sub_80411040((const IPv6Address *)src, (const IPv6Address *)dst, 0x3A, pkt, 1);
    if (TLobby__sub_80410A98(pkt, dst, src, NULL, 0x3A)) {
        return -1;
    }
    return 0;
}

s16 TLobby__sub_8040E780(NetPacket *, u32, u32, u8, u8, u8, s32);

s16 TLobby::dispatch_by_addr_family(NetPacket *packet, NetworkAddress *dst, NetworkAddress *src,
                                       u8 *ipv4_options, void *ipv6_options, s32 protocol) {
    switch (src->family) {
    case 4:
        return TLobby__sub_8040E780(packet, dst->ipv4, src->ipv4, ipv4_options[0], ipv4_options[1], ipv4_options[2], protocol);
    case 6:
        return TLobby__sub_80410A98(packet, dst->address, src->address, (Ipv6SendOptions *)ipv6_options, protocol);
    case 0:
    default:
        return -2;
    }
}

u16 TLobby__sub_8040D8F0(u8 *arg0, u8 *arg1, s8 arg2, u8 *pkt, s16 flag) {
    struct Fields_arg0 { s32 field_0; s32 field_4; };
    struct Fields_arg1 { u8 pad_0[4]; s32 field_4; };
    switch (((Fields_arg0*)arg0)->field_0) {
    case 4:
        return TLobby::calc_pseudo_header_checksum(((Fields_arg0*)arg0)->field_4, ((Fields_arg1*)arg1)->field_4, arg2, pkt, flag);
    case 6:
        return TLobby__sub_80411040((const IPv6Address *)((void *) (arg0 + 4)), (const IPv6Address *)((void *) (arg1 + 4)), arg2, (const NetPacket *)(pkt), flag);
    case 0:
    default:
        return 0xFFFEU;
    }
}

s32 select_source_address__6TLobbyFPvPv(Out_8040D95C *arg0, In_8040D95C *arg1) {
    Ent_8040D95C *e;
    s16 ok;
    s16 NetIPv6IsUnspecified(u8 *arg0);

    switch (arg1->type) {
    case 4:
        {
        u32 v = arg0->f4;
        if (v != 0) {
            return 0;
        }
        e = (Ent_8040D95C *)TLobby__sub_8040F76C(arg1->f4, v);
        if (e == NULL) {
            return -6;
        }
        arg0->type = 4;
        return TLobby__sub_8040EF50(&arg0->f4, e->fC, e->f2);
        }
    case 6:
        ok = NetIPv6IsUnspecified((u8 *)&arg0->f4);
        if (ok == 0) {
            return 0;
        }
        e = (Ent_8040D95C *)TLobby__sub_80413264(&arg1->f4, (s32)&arg0->f4);
        if (e == NULL) {
            return -6;
        }
        arg0->type = 6;
        return TLobby__sub_80411F1C((u8 *)&arg0->f4, (u8 *)&arg1->f4, e->f6);
    case 0:
    default:
        return -2;
    }
}

s32 TLobby__sub_8040DA54(u8 *arg0, u8 *arg1) {
    struct Fields_arg0 { s32 field_0; u8 * field_4; };
    struct Fields_arg1 { u8 pad_0[4]; s32 field_4; };
    s32 var_r4;
    u8 *var_r3;
    switch (((Fields_arg0*)arg0)->field_0) {
    case 4:
        var_r3 = (u8 *)(((Fields_arg0*)arg0)->field_4);
        var_r4 = ((Fields_arg1*)arg1)->field_4;
        return TLobby::is_lookup_found((u32)var_r3, (u32)(var_r4));
    case 6:
        var_r3 = (u8 *)(arg0 + 4);
        var_r4 = (long) (arg1 + 4);
        return TLobby__sub_80413230((u8 *)(var_r3), (s32)(var_r4));
    default:
    case 0:
        var_r3 = (u8 *)((void *)-2);
        return -2;
    }
}

s16 NetValidateLocalAddress(NetworkAddress* address) {
    u32 ip;
    switch ((s32)address->family) {
    case 0:
        return 0;
    case 4:
        ip = address->ipv4;
        if (ip != 0) {
            return TLobby__sub_8040FCEC(ip);
        }
        return 0;
    case 6:
        return TLobby__sub_804136EC(address->address);
    default:
        return -2;
    }
}

s32 NetIsMulticastAddress(NetworkAddress *self, s16 arg1) {
    u8 *arg0 = (u8 *)self;
    struct Fields_arg0 { s32 field_0; u32 field_4; };
    switch (((Fields_arg0*)arg0)->field_0) {
    case 4:
        return TLobby__sub_8040FDA0(((Fields_arg0*)arg0)->field_4, arg1);
    case 6:
        return NetIPv6IsMulticast((u8 *)(arg0 + 4));
    case 0:
    default:
        return 0;
    }
}

s32 is_addr_unspecified__6TLobbyFPv(u8 *arg0) {
    struct Fields_arg0 { s32 field_0; u32 field_4; };
    switch (((Fields_arg0*)arg0)->field_0) {
    case 0:
        return 1;
    case 4:
        return NetIPv4IsUnspecified((u32)(((Fields_arg0*)arg0)->field_4));
    case 6:
        return NetIPv6IsUnspecified((u8 *)(arg0 + 4));
    default:
        return 0;
    }
}

s16 NetCompareAddresses(NetworkAddress *self, NetworkAddress *arg1) {
    u8 *arg0 = (u8 *)self;
    struct Fields_arg0 { s32 field_0; u8 * field_4; };
    struct Fields_arg1 { u32 field_0; u8 * field_4; };
    u8 *var_r3;
    u8 *var_r4;
    switch (((Fields_arg0*)arg0)->field_0) {
    case 4:
        if ((u32) ((Fields_arg1*)arg1)->field_0 != 4U) {
            var_r3 = (u8 *)((void *)-1);
            return -1;
        }
        var_r3 = (u8 *)(((Fields_arg0*)arg0)->field_4);
        var_r4 = (u8 *)(((Fields_arg1*)arg1)->field_4);
        return TLobby__sub_8040FEE4((s32)(var_r3), (s32)(var_r4));
    case 6:
        if ((u32) ((Fields_arg1*)arg1)->field_0 != 6U) {
            var_r3 = (u8 *)((void *)-1);
            return -1;
        }
        var_r3 = (u8 *)(arg0 + 4);
        var_r4 = (u8 *)((u8 *)arg1 + 4);
        return NetIPv6CompareAddresses((s32)(var_r3), (s32)(var_r4));
    default:
    case 0:
        var_r3 = (u8 *)((void *)-1);
        return -1;
    }
}

s16 TLobby__sub_8040DC8C(u8 *arg0, u8 *arg1) {
    s16 temp_r3;
    s16 entry_field_26;
    u32 temp_r5;
    u8 *temp_r3_3;
    u8 *temp_r3_4;
    temp_r5 = *(u32 *)((s8 *)arg0 + 0);
    if ((u32) *(u32 *)((s8 *)arg1 + 0) != temp_r5) {
        return -2;
    }
    switch ((s32) temp_r5) {
    case 4:
        temp_r3_3 = (u8 *)(TLobby__sub_8040F76C(*(s32 *)((s8 *)arg0 + 4), *(s32 *)((s8 *)arg1 + 4)));
        if (temp_r3_3 == NULL) {
            return -6;
        }
        temp_r3 = TLobby__sub_8040EF00(*(s16 *)((s8 *)temp_r3_3 + 2));
        if (temp_r3 < 0x28) {
            return -6;
        }
        return temp_r3 - 0x28;
    case 6:
        temp_r3_4 = (u8 *)(TLobby__sub_80413264(arg0 + 4, (s32)(arg1 + 4)));
        if (temp_r3_4 == NULL) {
            return -6;
        }
        entry_field_26 = TLobby::get_entry_field_26(*(s16 *)((s8 *)temp_r3_4 + 6));
        if (entry_field_26 < 0x3C) {
            return -6;
        }
        return entry_field_26 - 0x3C;
    case 0:
    default:
        return -2;
    }
}

s32 TLobby__sub_8040DD68(void) {
    TLobby::release_slot_by_id(0x800);
    TLobby__sub_803F892C((void *)((void *) (&ipv4_protocol_state.value)));
    ipv4_protocol_state.value = 0;
    return 0;
}

s32 TLobby::init_ipv4_interfaces() {
    s16 i;
    E_8040DDB0 *e;
    Ipv4ProtocolState *g = &ipv4_protocol_state;

    TLobby__sub_803F8930((u8 *)&g->value);
    e = g->ents;
    for (i = 0; i < g->value; i++) {
        e->c0 = 0x49;
        e->c1 = 0x50;
        e->c2 = 0x34;
        e->c3 = i;
        e->f4 = 0;
        e++;
    }
    g->packet_id = 1;
    register_protocol_handler__6TLobbyFUsi(0x800, (Handler_8041A130)TUdpSocket__sub_8040DE4C);
    return 0;
}

#pragma opt_propagation off
#pragma opt_lifetimes off
static inline void release_ipv4_input_record(NetPacket *record, s16 reassembled) {
    if (reassembled == 1) {
        TUdpSocket__sub_80418BD8((A_80418BD8 *)record);
    }
    NetReleasePacket(record);
}

struct Ipv4AddressCopy {
    u32 *destination;
    u32 *source;
    s32 bytes;
};

s32 TUdpSocket__sub_8040DE4C(u8 *ip, s16 x, s16 id) {
    s16 iface;
    s16 length;
    Ipv4Header *header;
    length = x;
    header = (Ipv4Header *)ip;
    iface = id;
    s16 TLobby__sub_8040FDA0(u32, s16);
    s16 TLobby__sub_8040FE40(s16);
    s16 TLobby__sub_8041B974(u8 *, u8 *, u8 *);
    u32 length_or_index;
    u8 *cursor;
    Ipv4ProtocolState *state;
    u8 header_length;
    s16 status;
    NetPacket *record;
    s16 payload_length;
    s16 reassembled;
    s16 delivered;
    u32 fragment_flags;
    u8 more_fragments;
    u32 checksum;
    u16 TUdpSocket__sub_80419864(void *, s16);
    NetworkAddress src;
    NetworkAddress dst;
    Icmp4Header ic;
    Ipv4AddressCopy copy;
    if (length < 5) {
        return -1;
    }
    if (TLobby::get_active_entry_by_index(iface) == 0) {
        return -1;
    }
    u32 family = 4;
    src.family = family;
    copy.destination = &src.ipv4;
    copy.source = &header->src;
    copy.bytes = sizeof(u32);
    NetMemcpy(copy.destination, copy.source, copy.bytes);
    dst.family = family;
    copy.destination = &dst.ipv4;
    copy.source = &header->dst;
    NetMemcpy(copy.destination, copy.source, copy.bytes);
    header_length = (header->version_ihl << 2) & 0x3C;
    cursor = (u8 *)&header->length;
    length_or_index = *(u16 *)cursor;
    payload_length = length_or_index - header_length;
    if (header_length < 20) {
        return -1;
    }
    if ((header->version_ihl >> 4) != 4) {
        return -1;
    }
    checksum = TUdpSocket__sub_80419864(header, (s16)(header_length >> 1));
    checksum = (checksum >> 16) + (checksum & 0xFFFF);
    checksum += checksum >> 16;
    if ((u16)~checksum != 0) {
        return -1;
    }
    if (length_or_index < header_length) {
        return -1;
    }
    if (iface != 0 && TLobby__sub_8040FCEC(dst.ipv4) < 0 &&
        TLobby__sub_8040FDA0(dst.ipv4, iface) == 0 && TLobby__sub_8040FE40(iface) != 0) {
        status = TUdpSocket__sub_8040E354((u8 *)dst.ipv4, src.ipv4, (u8 *)header, length, iface);
        if (status < 0) {
            return -1;
        }
        return -1;
    }
    fragment_flags = header->fragment;
    if (fragment_flags & ~0x4000) {
        if (fragment_flags & 0x2000) {
            more_fragments = 1;
        } else {
            more_fragments = 0;
        }
        u16 offset = fragment_flags & 0x1fff;
        record = (NetPacket *)TLobby__sub_80418C40((u8 *)header, header_length, payload_length, header->ttl,
            header->id, (u8 *)&src, offset, more_fragments, iface);
        if (record == 0) {
            return 0;
        }
        reassembled = 1;
    } else {
        record = TLobby::alloc_free_entry();
        if (record == 0) {
            return -257;
        }
        record->fragment_count = 0;
        record->total_bytes = length_or_index;
        record->fragments[record->fragment_count].length = header_length;
        NetBufferRefInitKind1(&record->fragments[record->fragment_count].buffer, (s32)header);
        record->fragment_count++;
        record->fragments[record->fragment_count].length = payload_length;
        NetBufferRefInitKind1(&record->fragments[record->fragment_count].buffer, (s32)((u8 *)header + header_length));
        record->fragment_count++;
        reassembled = 0;
    }
    switch (header->protocol) {
    case 1:
        delivered = 1;
        status = TLobby__sub_8040CB44((u8 *)record, src.ipv4, dst.ipv4);
        if (status < 0) {
            release_ipv4_input_record(record, reassembled);
            return -1;
        }
        release_ipv4_input_record(record, reassembled);
        break;

    case 6:
        status = TLobby__sub_8041B974((u8 *)record, (u8 *)&src, (u8 *)&dst);
        if (status < 0) {
            release_ipv4_input_record(record, reassembled);
            return -1;
        }
        release_ipv4_input_record(record, reassembled);
        return 0;

    case 17:
        status = udp_input__6TLobbyFPvPvPvi((O_80420DE4 *)record, &src, &dst, iface);
        if (status < 0) {
            switch (status) {
            case -2: {
                s32 icmp_result;
                ic.type = 3;
                ic.code = 3;
                ic.rest = 0;
                icmp_result = TUdpSocket__sub_8040CE58(&ic, header, length, iface);
                release_ipv4_input_record(record, reassembled);
                return icmp_result;
            }

            default:
                release_ipv4_input_record(record, reassembled);
                return -1;
            }
        }
        release_ipv4_input_record(record, reassembled);
        return 0;

    default:
        delivered = 0;
        break;
    }

    state = &ipv4_protocol_state;
    cursor = (u8 *)state->ents;
    length_or_index = 0;
    for (; (s16)length_or_index < state->value; length_or_index++) {
        E_8040DDB0 *socket = (E_8040DDB0 *)cursor;
        if ((u16)socket->f4 == 1 && (socket->address == 0 || socket->address == src.ipv4) &&
            socket->protocol == header->protocol && socket->owner != 0) {
            TLobby__sub_80421AD8((u8 *)record, src.ipv4, dst.ipv4, socket->owner, length_or_index);
            delivered = 1;
        }
        cursor += sizeof(E_8040DDB0);
    }

    if (delivered == 1) {
        release_ipv4_input_record(record, reassembled);
        return 0;
    }
    ic.type = 3;
    ic.code = 2;
    ic.rest = 0;
    TUdpSocket__sub_8040CE58(&ic, header, length, iface);
    release_ipv4_input_record(record, reassembled);
    return -1;
}

#pragma opt_lifetimes reset
s16 TUdpSocket__sub_8040E354(u8 *self, u32 key, u8 *pkt, s16 total, s16 id)
{
  s32 header_length;
  int fragment_length;
  s32 aligned_bytes;
  s16 result;
  NetPacket *plain_record;
  u8 header_bytes;
  s16 dont_fragment;
  s16 off;
  s16 mtu;
  s16 ifidx;
  u8 *target;
  NetPacket *fragment_record;
  u32 checksum;
  u16 flags;
  s16 units;
  s16 fragment_units;
  s32 fragment_field;
  s16 rem;
  u8 *fragment_header;
  u8 *route;
  u8 *plain_header;
  u8 *payload;
  s16 len;
  s16 fragment_tail_bytes;
  u8 *header;
  u16 TUdpSocket__sub_80419864(void *, s16);
  s16 TLobby__sub_8040EDE4(s32, u32, s16);
  u16 t46;
  u16 t44;
  u16 g1[2];
  s16 t36;
  u16 t34;
  u8 g2[10];
  header = pkt;
  header_bytes = (header[0] << 2) & 0x3C;
  if (header_bytes == 20)
  {
    len = total - 20;
  }
  else
  {
    len = total - header_bytes;
  }
  if (len <= 0)
  {
    return -1;
  }
  NetMemcpy(&t46, header + 6, 2);
  header = pkt;
  fragment_field = t46;
  flags = fragment_field & (~0x1FFF);
  t46 = flags;
  dont_fragment = fragment_field & 0x4000;
  off = fragment_field & 0xFF;
  if (((u8) (header[8] - 1)) < 1)
  {
    return -1;
  }
  header[8] = header[8] - 1;
  route = (u8 *)TLobby__sub_8040F76C((u32) self, key);
  if (route == 0)
  {
    return -6;
  }
  ifidx = *((s16 *) (route + 2));
  if ((*((s16 *) (route + 18))) == 1)
  {
    target = self;
  }
  else
  {
    target = *((u8 **) (route + 12));
  }
  mtu = TLobby__sub_8040EF00(ifidx);
  if (mtu < 0)
  {
    return mtu;
  }
  if (mtu < (header_bytes + len))
  {

    if (dont_fragment & 0xFF)
    {
      return -1;
    }
    fragment_record = TLobby::alloc_free_entry();
    if (fragment_record == 0)
    {
      return -257;
    }
    rem = len;
    payload = header + header_bytes;
    units = (mtu - header_bytes) / 8;
    do
    {
      fragment_header = pkt;

      if (mtu > (rem + (header_length = header_bytes)))
      {
        t46 = flags;
        fragment_tail_bytes = rem % 8;
        fragment_units = rem / 8;
        mtu = rem;
      }
      else
      {
        t46 |= 0x2000;
        fragment_units = units;
        fragment_tail_bytes = 0;
      }
      t36 = off;
      t36 |= t46;
      NetMemcpy(fragment_header + 6, &t36, 2);
      fragment_length = fragment_tail_bytes + (aligned_bytes = fragment_units << 3);
      t34 = header_length + fragment_length;
      NetMemcpy(fragment_header + 2, &t34, 2);
      NetMemset(fragment_header + 10, 0, 2);
      checksum = TUdpSocket__sub_80419864(fragment_header, header_length / 2);
      checksum = (checksum >> 16) + (checksum & 0xFFFF);
      checksum += checksum >> 16;
      t44 = ~checksum;
      NetMemcpy(fragment_header + 10, &t44, 2);
      fragment_record->fragment_count = 0;
      fragment_record->total_bytes = (u16) fragment_length;
      fragment_record->fragments[fragment_record->fragment_count].length = fragment_length;
      NetBufferRefInitKind1(&fragment_record->fragments[fragment_record->fragment_count].buffer, (s32)payload);
      fragment_record->fragment_count += 1;
      fragment_record->total_bytes += header_bytes;
      fragment_record->fragments[fragment_record->fragment_count].length = header_bytes;
      NetBufferRefInitKind1(&fragment_record->fragments[fragment_record->fragment_count].buffer, (s32)fragment_header);
      fragment_record->fragment_count += 1;
      result = TLobby__sub_8040EDE4((s32)fragment_record, (u32) target, ifidx);
      if (result < 0)
      {
        NetReleasePacket(fragment_record);
        break;
      }
      off += fragment_units;
      payload += aligned_bytes;
      header_bytes = 20;
      if (mtu == rem)
      {
        rem = 0;
      }
      else
      {
        rem = rem - fragment_length;
      }
    }
    while (rem > 0);
    NetReleasePacket(fragment_record);
  }
  else
  {
    plain_header = pkt;

    NetMemset(plain_header + 10, 0, 2);
    checksum = TUdpSocket__sub_80419864(plain_header, header_bytes / 2);
    checksum = (checksum >> 16) + (checksum & 0xFFFF);
    checksum += checksum >> 16;
    t44 = ~checksum;
    NetMemcpy(plain_header + 10, &t44, 2);
    plain_record = TLobby::alloc_free_entry();
    if (plain_record == 0)
    {
      return -257;
    }
    plain_record->fragment_count = 0;
    plain_record->total_bytes = len;
    plain_record->fragments[plain_record->fragment_count].length = len;
    NetBufferRefInitKind1(&plain_record->fragments[plain_record->fragment_count].buffer, (s32)(plain_header + header_bytes));
    plain_record->fragment_count += 1;
    plain_record->total_bytes += header_bytes;
    plain_record->fragments[plain_record->fragment_count].length = header_bytes;
    NetBufferRefInitKind1(&plain_record->fragments[plain_record->fragment_count].buffer, (s32)plain_header);
    plain_record->fragment_count += 1;
    result = TLobby__sub_8040EDE4((s32)plain_record, (u32) target, ifidx);
    NetReleasePacket(plain_record);
  }
  return result;
}

s16 TLobby__sub_8040E780(NetPacket *rec, u32 dst, u32 src, u8 ttl, u8 tos, u8 df, s32 proto)
{
  u8 *output_fragment;
  s32 offset_step;
  s16 *length_field;
  NetBufferRef *buffer_ref;
  s32 last_source_index;
  s16 scan_remaining;
  s16 copy_remaining;
  s32 copy_index;
  s16 ifidx;
  Ipv4Header *ip;
  s32 fragment_count;
  u32 target;
  s16 chunk;
  u8 *source_fragment;
  Ipv4ProtocolState *state;
  u32 checksum;
  s32 fragment_offset;
  NetPacket *fragment_record;
  s16 last;
  s32 amount;
  s32 source_index;
  s16 mtu;
  s32 scan_index;
  s16 *source_length;
  s16 result;
  s32 output_byte_offset;
  s16 total_bytes;
  s32 source_byte_offset;
  Ipv4Route *route;
  s16 TLobby__sub_8040EDE4(s32, u32, s16);
  s16 TLobby__sub_8040FDA0(u32, s16);
  s16 TLobby__sub_8040EF50(u32 *, u32, s16);
  union {
    s64 alignment;
    NetPacket packet;
  } workspace;
  state = &ipv4_protocol_state;
  route = TLobby__sub_8040F76C(dst, src);
  if (route == NULL)
  {
    return -6;
  }
  if (src == 0)
  {
    result = TLobby__sub_8040EF50(&src, route->gateway, route->iface);
    if (result < 0)
    {
      return result;
    }
  }
  if (TLobby__sub_8040FDA0(src, route->iface) != 0)
  {
    result = TLobby__sub_8040EF50(&src, route->gateway, route->iface);
    if (result < 0)
    {
      return result;
    }
  }
  ifidx = route->iface;
  if ((route->type) == 1)
  {
    target = dst;
  }
  else
  {
    target = route->gateway;
  }
  ip = &state->header;
  ip->version_ihl = 0x40;
  ip->version_ihl |= 5;
  if (tos != 0)
  {
    ip->tos = tos;
  }
  else
  {
    ip->tos = state->default_tos;
  }
  if (ttl != 0)
  {
    ip->ttl = ttl;
  }
  else
  {
    ip->ttl = state->default_ttl;
  }
  total_bytes = rec->total_bytes;
  if (total_bytes == 0)
  {
    return 0;
  }
  total_bytes = total_bytes + 20;
  ip->length = total_bytes;
  state->packet_id += 1;
  ip->protocol = (u8)proto;
  ip->id = state->packet_id;
  NetMemcpy(&ip->src, &src, 4);
  NetMemcpy(&ip->dst, &dst, 4);
  mtu = TLobby__sub_8040EF00(ifidx);
  if (mtu < 0)
  {
    return mtu;
  }
  if (total_bytes <= mtu)
  {
    ip->fragment = 0;
    if (df != 0)
    {
      ip->fragment = 0x4000;
    }
    ip->checksum = 0;
    checksum = TUdpSocket__sub_80419864(ip, 10);
    checksum = (checksum >> 16) + (checksum & 0xFFFF);
    checksum += checksum >> 16;
    ip->checksum = ~checksum;
    rec->total_bytes += 20;
    rec->fragments[rec->fragment_count].length = 20;
    NetBufferRefInitKind1(&rec->fragments[rec->fragment_count].buffer, (s32)ip);
    rec->fragment_count += 1;
    return TLobby__sub_8040EDE4((s32)rec, (u32) target, ifidx);
  }
  fragment_offset = 0;
  if (df != 0)
  {
    return -2;
  }
  chunk = (mtu - 20) / 8;
  chunk *= 8;
  ip->fragment = 0;
  offset_step = chunk / 8;
  fragment_record = &workspace.packet;
  do
  {
    fragment_record->fragment_count = 0;
    fragment_record->total_bytes = 0;
    scan_remaining = chunk;
    fragment_count = 0;
    scan_index = (last_source_index = rec->fragment_count - 1);
    source_fragment = (u8 *)rec + (scan_index * (s32)sizeof(NetPacketFragment));
    while ((scan_remaining > 0) && (scan_index >= 0))
    {
      scan_remaining -= *(s16 *)(source_fragment + offsetof(NetPacket, fragments[0].length));
      source_fragment -= sizeof(NetPacketFragment);
      scan_index--;
      fragment_count++;
    }

    source_index = last_source_index;
    copy_index = (s16)fragment_count - 1;
    source_byte_offset = source_index * (s32)sizeof(NetPacketFragment);
    output_byte_offset = copy_index * (s32)sizeof(NetPacketFragment);
    copy_remaining = chunk;
    last = 0;
    while ((copy_remaining > 0) && (copy_index >= 0))
    {
      source_fragment = (u8 *)rec + source_byte_offset;
      output_fragment = (u8 *)fragment_record + output_byte_offset;
      buffer_ref = (NetBufferRef *)(source_fragment + offsetof(NetPacket, fragments[0].buffer));
      NetMemcpy(output_fragment + offsetof(NetPacket, fragments[0].buffer), buffer_ref, 8);
      length_field = (s16 *)(source_fragment + offsetof(NetPacket, fragments[0].length));
      source_length = length_field;
      amount = copy_remaining;
      if (*length_field > amount)
      {
        *(s16 *)(output_fragment + offsetof(NetPacket, fragments[0].length)) = copy_remaining;
        fragment_record->total_bytes += amount;
        *source_length -= copy_remaining;
        rec->total_bytes -= amount;
        TLobby__sub_80406EB8(buffer_ref, amount);
        copy_remaining = 0;
      }
      else
      {
        *(s16 *)(output_fragment + offsetof(NetPacket, fragments[0].length)) = *length_field;
        fragment_record->total_bytes += *source_length;
        rec->total_bytes -= *source_length;
        copy_remaining -= *source_length;
        if (source_index == 0)
        {
          copy_remaining = *source_length;
          last = 1;
          copy_index--;
          output_byte_offset -= sizeof(NetPacketFragment);
          source_index--;
          source_byte_offset -= sizeof(NetPacketFragment);
        }
        else
        {
          rec->fragment_count -= 1;
          copy_index--;
          output_byte_offset -= sizeof(NetPacketFragment);
          source_index--;
          source_byte_offset -= sizeof(NetPacketFragment);
        }
      }
      fragment_record->fragment_count += 1;
    }

    if (last == 1)
    {
      ip->fragment = 0;
    }
    else
    {
      ip->fragment = 0x2000;
    }
    ip->fragment |= fragment_offset;
    ip->length = fragment_record->total_bytes + 20;
    ip->checksum = 0;
    checksum = TUdpSocket__sub_80419864(ip, 10);
    checksum = (checksum >> 16) + (checksum & 0xFFFF);
    checksum += checksum >> 16;
    ip->checksum = ~checksum;
    fragment_record->total_bytes += 20;
    fragment_record->fragments[fragment_record->fragment_count].length = 20;
    NetBufferRefInitKind1(&fragment_record->fragments[fragment_record->fragment_count].buffer, (s32)ip);
    fragment_record->fragment_count += 1;
    result = TLobby__sub_8040EDE4((s32)fragment_record, (u32) target, ifidx);
    if (result < 0)
    {
      return result;
    }
    fragment_offset += offset_step;
  }
  while (last != 1);
  return 0;
}

#pragma opt_propagation reset
u16 TLobby::calc_pseudo_header_checksum(s32 src, s32 dst, s8 proto, void *pkt, s16 flag) {
    PH_8040EC38 ph;
    u32 sum;

    ph.src = src;
    ph.dst = dst;
    ph.zero = 0;
    ph.proto = proto;
    if (flag == 0) {
        ph.len = ((P_8040EC38 *)pkt)->f8 - ((P_8040EC38 *)pkt)->fC;
    } else {
        ph.len = ((P_8040EC38 *)pkt)->f8;
    }
    sum = TUdpSocket__sub_80419864(&ph, 6);
    sum += TLobby__sub_80406BD8(pkt, flag);
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += sum >> 16;
    return ~sum;
}

u16 NetPacketChecksum(NetPacket *self, s16 b) {
    u32 s = TLobby__sub_80406BD8(self, b);
    s = (s >> 16) + (s & 0xFFFF);
    s += (s >> 16);
    return ~s;
}

s32 TLobby__sub_8040ED28(void) {
    TLobby__sub_803F8958((void *)((void *) (&(*(RecoveredGlobal_8040ED28_lbl_805C1B60 *)&ipv4_address_routing_state).value)));
    *(s16 *)((s8 *)(&(*(RecoveredGlobal_8040ED28_lbl_805C1B60 *)&ipv4_address_routing_state).value) + 0) = 0;
    *(s16 *)((s8 *)(&(*(RecoveredGlobal_8040ED28_lbl_805C1B60 *)&ipv4_address_routing_state).value) + 2) = 0;
    *(s16 *)((s8 *)(&(*(RecoveredGlobal_8040ED28_lbl_805C1B60 *)&ipv4_address_routing_state).value) + 4) = 0;
    return 0;
}

s32 TLobby__sub_8040ED70(void) {
    NetInitBufferDescriptorA((NetConfig_803F895C *)(&(*(RecoveredGlobal_8040ED70_lbl_805C1B60 *)&ipv4_address_routing_state).value));
    NetMemset((void *)((int) (*(s32 *)((s8 *)(&(*(RecoveredGlobal_8040ED70_lbl_805C1B60 *)&ipv4_address_routing_state).value) + 8))), 0, (int)((int) (*(s16 *)((s8 *)(&(*(RecoveredGlobal_8040ED70_lbl_805C1B60 *)&ipv4_address_routing_state).value) + 0) * 0x14)));
    NetMemset((void *)((int) (*(s32 *)((s8 *)(&(*(RecoveredGlobal_8040ED70_lbl_805C1B60 *)&ipv4_address_routing_state).value) + 0xC))), 0, (int)((int) (*(s16 *)((s8 *)(&(*(RecoveredGlobal_8040ED70_lbl_805C1B60 *)&ipv4_address_routing_state).value) + 2) * 0x14)));
    NetMemset((void *)((int) (*(s32 *)((s8 *)(&(*(RecoveredGlobal_8040ED70_lbl_805C1B60 *)&ipv4_address_routing_state).value) + 0x10))), 0, (int)((int) (*(s16 *)((s8 *)(&(*(RecoveredGlobal_8040ED70_lbl_805C1B60 *)&ipv4_address_routing_state).value) + 4) * 0x18)));
    return 0;
}

s32 TLobby__sub_8040EDE4(s32 arg0, u32 dst, s16 idx) {
    Ipv4RoutingState *g;
    Ipv4Iface *ifc;

    if (idx < 0 || idx >= (g = (Ipv4RoutingState *)&ipv4_address_routing_state)->nifaces) {
        return -0x109;
    }
    ifc = g->ifaces;
    ifc += idx;
    if (ifc->state != 1) {
        return -6;
    }
    if (dst == 0 || is_iface_destination_8040EDE4(idx, dst)) {
        return TLobby::call_handler_by_index(idx, ifc->handle, 1, (s32)&dst, arg0);
    }
    return TLobby::dispatch_handler_by_index(idx, ifc->handle, (s32)&dst, arg0);
}

#pragma opt_common_subs on
s16 TLobby__sub_8040EF00(s16 arg0) {
    struct Fields_temp_r3 { s16 field_0; u8 pad_2[2]; s16 field_4; };
    u8 *temp_r3;
    if ((arg0 < 0) || (arg0 >= (s16) *(s16 *)((s8 *)(&ipv4_address_routing_state.value) + 2))) {
        return -0x109;
    }
    temp_r3 = (u8 *)(*(s32 *)((s8 *)(&ipv4_address_routing_state.value) + 0xC) + (arg0 * 0x1C));
    if ((s16) ((Fields_temp_r3*)temp_r3)->field_0 != 1) {
        return -2;
    }
    return ((Fields_temp_r3*)temp_r3)->field_4;
}

s32 TLobby__sub_8040EF50(u32 *out, u32 dst, s16 idx) {
    Ipv4RoutingState *g = (Ipv4RoutingState *)&ipv4_address_routing_state;
    Ipv4Iface *ifc;
    s16 count;
    u32 addr;
    u32 alias_addr;
    s16 i;
    Ipv4Alias *alias;

    if (idx < 0 || idx >= g->nifaces) {
        return -6;
    }
    if ((ifc = g->ifaces + idx)->state == 1) {
        if ((ifc->mask & (addr = ifc->addr)) == (ifc->mask & dst)) {
            *out = addr;
            return 0;
        }
        alias = ifc->aliases;
        i = 0;
        count = g->max_aliases;
        while (alias != NULL && i < count) {
            if ((alias->mask & (alias_addr = alias->addr)) == (alias->mask & dst)) {
                *out = alias_addr;
                return 0;
            }
            alias = alias->next;
            i++;
        }
    }
    return -6;
}

s32 TLobby__sub_8040F00C(s16 idx, NetBufferRef *out, s16 len, s32 arg3) {
    s16 TLobby__sub_80409EB0(s16 arg0, s32 arg1);
    Ipv4RoutingState *g = (Ipv4RoutingState *)&ipv4_address_routing_state;
    Ipv4Iface *ifc;
    s16 n;
    s32 count;
    Ipv4Alias *alias;
    Ipv4IfaceAddrRecord rec;
    NetBufferRef ref;

    if (idx < 0 || idx >= g->nifaces) {
        return -0x109;
    }
    ifc = g->ifaces;
    ifc += idx;
    if (ifc->state != 1) {
        return -2;
    }
    if (len < sizeof(rec)) {
        return -2;
    }
    rec.kind = 4;
    rec.addr = ifc->addr;
    rec.mask = ifc->mask;
    rec.broadcast = ifc->broadcast;
    NetBufferRefInitKind1(&ref, (s32)&rec);
    TLobby__sub_80406FD8(out, &ref, sizeof(rec));
    TLobby__sub_80406EB8(out, sizeof(rec));
    alias = ifc->aliases;
    count = 1;
    n = 0;
    len -= sizeof(rec);
    while (len >= sizeof(rec) && alias != NULL && n < g->max_aliases) {
        rec.kind = 4;
        rec.addr = alias->addr;
        rec.mask = alias->mask;
        rec.broadcast = alias->broadcast;
        NetBufferRefInitKind1(&ref, (s32)&rec);
        TLobby__sub_80406FD8(out, &ref, sizeof(rec));
        TLobby__sub_80406EB8(out, sizeof(rec));
        alias = alias->next;
        count++;
        n++;
        len -= sizeof(rec);
    }
    if (TLobby__sub_80409EB0(idx, ifc->handle) <= 6) {
        TLobby__sub_80409E18(idx, ifc->handle, arg3);
    }
    return count;
}

s16 TLobby__sub_8040F1A0(s16 idx) {
    Ipv4RoutingState *g = (Ipv4RoutingState *)&ipv4_address_routing_state;
    s16 *pn;
    Ipv4Iface **pifs;
    s16 count;
    Ipv4Iface *ifc;
    Ipv4Alias *alias;
    u32 gateway;

    if (idx < 0 || idx >= *(pn = &g->nifaces)) {
        return -0x109;
    }
    ifc = *(pifs = &g->ifaces);
    ifc += idx;
    if (ifc->state != 1) {
        return 0;
    }
    alias = ifc->aliases;
    count = 0;
    while (alias != NULL && count < g->max_aliases) {
        Ipv4Alias *next;
        if (is_socket_flag_set__6TLobbyFs(idx) == 0 && get_iface_addr_8040F1A0(pn, pifs, &gateway)) {
            remove_host_route_8040F1A0(g, alias->addr, gateway);
        }
        TLobby__sub_80409D7C(idx, ifc->handle, 2, (s32)&alias->addr);
        next = alias->next;
        count++;
        alias->f0 = 0;
        alias->addr = 0;
        alias->network = 0;
        alias->broadcast = 0;
        alias->mask = 0;
        alias->next = NULL;
        alias = next;
    }
    if (is_socket_flag_set__6TLobbyFs(idx) == 0 && get_iface_addr_8040F1A0(pn, pifs, &gateway)) {
        remove_host_route_8040F1A0(g, ifc->addr, gateway);
    }
    {
        Ipv4Route *e;
        s16 n;
        n = g->nroutes;
        e = g->routes;
        for (; n > 0; n--, e++) {
            if ((e->flags & 1) && e->iface == idx) {
                e->flags = 0;
            }
        }
    }
    TLobby::call_entry_callback(idx, ifc->handle);
    ifc->state = 0;
    ifc->handle = 0;
    ifc->f4 = 0;
    ifc->addr = 0;
    ifc->network = 0;
    ifc->broadcast = 0;
    ifc->mask = 0;
    ifc->aliases = NULL;
    return 0;
}

extern s16 TLobby__sub_8040F454(u32 addr, u32 mask, u32 broadcast, s16 idx) {
    Ipv4RoutingState *g = (Ipv4RoutingState *)&ipv4_address_routing_state;
    s16 *pn;
    Ipv4Iface **pifs;
    s16 unspecified;
    Ipv4Iface *ifc;
    s16 r;
    s16 err;
    s16 found;
    u32 gateway;

    if (idx < 0 || idx >= *(pn = &g->nifaces)) {
        return -0x109;
    }
    ifc = *(pifs = &g->ifaces);
    ifc += idx;
    if (ifc->state == 1) {
        return -2;
    }
    ifc->state = 1;
    ifc->handle = TLobby__sub_8040A044(idx, 0x800, 4, (u8 *)&addr);
    if (ifc->handle < 0) {
        ifc->state = 0;
        return ifc->handle;
    }
    if (addr == 0 && mask == 0xFFFFFFFF) {
        unspecified = 1;
    } else {
        unspecified = 0;
    }
    ifc->addr = addr;
    ifc->network = addr & mask;
    if (broadcast != 0) {
        ifc->broadcast = broadcast;
    } else {
        ifc->broadcast = ifc->network | ~mask;
    }
    ifc->mask = mask;
    r = TLobby::invoke_socket_callback(idx, ifc->handle);
    if (r < g->f6) {
        ifc->state = 0;
        return -6;
    }
    ifc->f4 = r;
    found = 0;
    ifc->aliases = NULL;
    gateway = 0xFFFFFFFF;
    if (is_socket_flag_set__6TLobbyFs(idx) == 0 && !unspecified) {
        found = get_iface_addr_8040F1A0(pn, pifs, &gateway);
        if (found) {
            found = TRKValidMemory32(addr, 0xFFFFFFFF, gateway, 0, 1, 0);
            if (found < 0) {
                TLobby::call_entry_callback(idx, ifc->handle);
                ifc->state = 0;
                ifc->handle = 0;
                ifc->f4 = 0;
                ifc->addr = 0;
                ifc->network = 0;
                ifc->broadcast = 0;
                ifc->mask = 0;
                return found;
            }
        }
    }
    err = TRKValidMemory32(addr & mask, mask, addr, 0, 1, 0);
    if (err < 0) {
        if (is_socket_flag_set__6TLobbyFs(idx) == 0 && gateway != 0xFFFFFFFF && !unspecified) {
            remove_host_route_8040F1A0(g, addr, gateway);
        }
        TLobby::call_entry_callback(idx, ifc->handle);
        ifc->state = 0;
        ifc->handle = 0;
        ifc->f4 = 0;
        ifc->addr = 0;
        ifc->network = 0;
        ifc->broadcast = 0;
        ifc->mask = 0;
        return err;
    }
    return 0;
}

#pragma opt_common_subs reset
s32 TLobby::is_lookup_found(u32 arg0, u32 arg1) {
    if (TLobby__sub_8040F76C(arg0, arg1) != NULL) {
        return 1;
    }
    return 0;
}

Ipv4Route *TLobby__sub_8040F76C(u32 dst, u32 gateway) {
    Ipv4RoutingState *g = (Ipv4RoutingState *)&ipv4_address_routing_state;
    s16 n;
    u16 flags;
    s16 i;
    Ipv4Route *e;
    Ipv4Route *host;
    Ipv4Route *net;
    Ipv4Route *def;
    u32 masked;

    host = NULL;
    e = g->routes;
    net = NULL;
    n = g->nroutes;
    def = NULL;
    for (i = 0; i < n; i++, e++) {
        flags = e->flags;
        masked = dst & e->mask;
        if (!(flags & 1)) {
            continue;
        }
        if ((flags & 4) && e->dst == dst) {
            return e;
        }
        if ((flags & 8) && e->type == 1) {
            if (dst == 0xFFFFFFFF || dst == 0) {
                if (e->gateway == gateway) {
                    host = e;
                    continue;
                }
            } else if (e->dst == masked) {
                host = e;
                continue;
            }
        }
        if (flags & 2) {
            if (e->dst == 0) {
                if (def == NULL) {
                    def = e;
                }
            } else if (e->dst == masked && net == NULL) {
                net = e;
            }
        }
    }
    if (host != NULL) {
        return host;
    }
    if (net != NULL) {
        return net;
    }
    if (def != NULL) {
        return def;
    }
    return NULL;
}

#pragma opt_common_subs on
s32 TLobby__sub_8040F8A4(u32 dst, u32 gateway, u32 mask, u16 flags, u32 old_gateway) {
    Ipv4RoutingState *g = (Ipv4RoutingState *)&ipv4_address_routing_state;
    s16 i;
    s16 add_host;
    Ipv4Route *e;

    add_host = 0;
    i = 0;
    e = g->routes;
    for (; i < g->nroutes; i++, e++) {
        if (!(e->flags & 1) || e->gateway != old_gateway) {
            continue;
        }
        if (e->dst == 0) {
            flags |= 2;
            add_host = 1;
            continue;
        }
        if (flags & 4) {
            if (!e->flags & 4) {
                continue;
            }
            if (e->dst == dst) {
                e->flags = flags | 0x20;
                e->gateway = gateway;
                return 0;
            }
        } else {
            if (e->flags & 4) {
                continue;
            }
            if ((dst & e->mask) == (e->dst & mask)) {
                e->flags = flags | 0x10;
                e->gateway = gateway;
                return 0;
            }
        }
    }
    if (add_host && TRKValidMemory32(dst, mask, gateway, 1, 2, flags)) {
        return -1;
    }
    return 0;
}

s32 TLobby__sub_8040F9CC(u32 dst, u32 mask, u32 gateway, s16 flags) {
    G_8040F9CC *g = (G_8040F9CC *)&ipv4_address_routing_state;
    s32 type_bit;
    s16 i;
    s16 n;
    Ent_8040F9CC *e;

    e = g->ents;
    n = g->count;
    type_bit = flags & 1;
    for (i = 0; i < n; i++, e++) {
        if ((e->flags & 1) && e->dst == dst && e->gateway == gateway && type_bit == (e->type & 1)) {
            e->flags = 0;
            return 0;
        }
    }
    return -2;
}

s16 TRKValidMemory32(u32 dst, u32 mask, u32 gateway, s16 f10, u8 type, u16 flags) {
    Ipv4RoutingState *g = (Ipv4RoutingState *)&ipv4_address_routing_state;
    Ipv4Iface *ifaces;
    s16 m;
    s16 n;
    s16 idx;
    s16 i;
    Ipv4Route *e;
    Ipv4Route *slot;

    ifaces = get_ifaces_8040FA48(g);
    m = g->max_aliases;
    n = g->nifaces;
    idx = find_iface_by_addr_8040FA48(ifaces, n, m, gateway);
    if (idx < 0) {
        idx = find_iface_by_network_8040FA48(ifaces, n, m, gateway);
        if (idx < 0) {
            return -2;
        }
    }
    e = g->routes;
    slot = NULL;
    for (i = 0; i < g->nroutes; i++, e++) {
        if (e->flags & 1) {
            if (e->dst == dst && (dst != 0 || mask != 0 || gateway != 0 || type != 1)) {
                return -2;
            }
        } else {
            slot = e;
            break;
        }
    }
    if (slot == NULL) {
        return -0x107;
    }
    slot->dst = dst;
    slot->gateway = gateway;
    slot->type = type;
    slot->f10 = f10;
    slot->iface = idx;
    switch (type) {
    case 1:
        if (mask == 0xFFFFFFFF) {
            slot->flags = 0xD;
        } else {
            slot->flags = 9;
        }
        slot->mask = mask;
        break;
    case 2:
        slot->flags = flags | 1;
        if (flags & 4) {
            slot->mask = 0xFFFFFFFF;
        } else {
            slot->mask = mask;
        }
        break;
    case 3:
        slot->flags = 0xB;
        slot->mask = mask;
        break;
    default:
        if (mask == 0xFFFFFFFF) {
            slot->flags = 0xF;
        } else {
            slot->flags = 0xB;
        }
        slot->mask = mask;
        break;
    }
    return 0;
}

s16 TLobby__sub_8040FCEC(u32 ip) {
    G_RT *g;
    s16 m;
    s16 n;
    s16 i;
    s16 j;
    E_RT *e;
    A_RT *a;

    g = (G_RT *)&ipv4_address_routing_state;
    e = g->ents;
    i = 0;
    m = g->maxalias;
    n = g->count;

    for (; i < n; i++, e++) {
        if (e->state == 1) {
            if (e->addr == ip) {
                return i;
            }
            for (a = e->alias, j = 0; a != NULL && j < m; j++) {
                if (a->addr == ip) {
                    return i;
                }
                a = a->next;
            }
        }
    }
    return -1;
}

s32 NetIPv4IsLoopback(s32 arg0) {
    if ((u32) ((arg0 & 0xFF000000) + 0x81000000) == 0U) {
        return 1;
    }
    return 0;
}

s32 TLobby__sub_8040FDA0(u32 arg0, s16 arg1) {
    Ent_8040FDA0 *e;
    if (arg1 < 0 || arg1 >= ((G_8040FDA0 *)&ipv4_address_routing_state)->count) {
        e = NULL;
    } else {
        e = ((G_8040FDA0 *)&ipv4_address_routing_state)->ents;
        e += arg1;
        if (e->state != 1) {
            e = NULL;
        }
    }
    if (e == NULL) {
        return 0;
    }
    if (e->f8 == 0 || arg0 == 0xFFFFFFFF || arg0 == e->fC) {
        return 1;
    }
    return 0;
}

s32 NetIPv4IsUnspecified(u32 arg0) {
    if (arg0 == 0U) {
        return 1;
    }
    return 0;
}

s32 TLobby__sub_8040FE40(s16 arg0) {
    struct Fields_var_r3 { s16 field_0; };
    s16 *var_r3;
    if ((arg0 < 0) || (arg0 >= (s16) *(s16 *)((s8 *)(&(*(RecoveredGlobal_8040FE40_lbl_805C1B60 *)&ipv4_address_routing_state).value) + 2))) {
        var_r3 = (s16 *)(NULL);
    } else {
        var_r3 = (s16 *)(*(s32 *)((s8 *)(&(*(RecoveredGlobal_8040FE40_lbl_805C1B60 *)&ipv4_address_routing_state).value) + 0xC) + (arg0 * 0x1C));
        if ((s16) ((Fields_var_r3*)var_r3)->field_0 != 1) {
            var_r3 = (s16 *)(NULL);
        }
    }
    if (var_r3 != NULL) {
        return 1;
    }
    return 0;
}

s16 *TLobby::get_active_entry_by_index(s16 arg0) {
    s16 *temp_r3;
    if ((arg0 < 0) || (arg0 >= (s16) *(s16 *)((s8 *)(&(*(RecoveredGlobal_8040FE9C_lbl_805C1B60 *)&ipv4_address_routing_state).value) + 2))) {
        return NULL;
    }
    temp_r3 = (s16 *)(*(s32 *)((s8 *)(&(*(RecoveredGlobal_8040FE9C_lbl_805C1B60 *)&ipv4_address_routing_state).value) + 0xC) + (arg0 * 0x1C));
    if ((s16) *temp_r3 != 1) {
        return NULL;
    }
    return temp_r3;
}

s16 TLobby__sub_8040FEE4(s32 arg0, s32 arg1) {
    s32 temp_r0;
    temp_r0 = arg0 - arg1;
    if (temp_r0 < 0) {
        return -1;
    }
    if (temp_r0 > 0) {
        return 1;
    }
    return 0;
}

G_8040A45C dns_resolver_state;
Ipv4ProtocolState ipv4_protocol_state;
RecoveredGlobal_8040EF00_lbl_805C1B60 ipv4_address_routing_state;
}
