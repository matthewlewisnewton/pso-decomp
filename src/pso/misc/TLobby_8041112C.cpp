#pragma opt_common_subs on
#include "pso/network/UdpRuntime.h"
#include "pso/network/NetworkRequestRuntime.h"
#include "pso/network/NetworkRecordConfig.h"
#include "pso/network/BufferRef.h"
#include "pso/misc/LobbyNetworkInternal.h"

extern "C" {

s32 TLobby__sub_8041112C(void) {
    RecoveredGlobal_8041123C_lbl_805C1BB8 *g = &ipv6_address_routing_state;
    NetUnregisterTimer(TLobby__sub_80411334);
    NetUnregisterTimer(TLobby::tick_entry_timers);
    TLobby__sub_803F8864(g);
    g->ab.a = 0;
    g->ab.b = 0;
    g->c = 0;
    return 0;
}

s32 TUdpSocket__sub_8041118C(void) {
    NetInitUdpSocketConfig((Cfg_803F8868 *)((G_8041118C *)&ipv6_address_routing_state));
    NetMemset(((G_8041118C *)&ipv6_address_routing_state)->p18, 0, ((G_8041118C *)&ipv6_address_routing_state)->n0 * 0x2A);
    NetMemset(((G_8041118C *)&ipv6_address_routing_state)->p1C, 0, ((G_8041118C *)&ipv6_address_routing_state)->n1 * 0x2A);
    NetMemset(((G_8041118C *)&ipv6_address_routing_state)->p20, 0, ((G_8041118C *)&ipv6_address_routing_state)->n2 * 0x2C);
    NetMemset(((G_8041118C *)&ipv6_address_routing_state)->p24, 0, ((G_8041118C *)&ipv6_address_routing_state)->n14 * 0x16);
    NetRegisterTimer(0x3E8, (s16)(1), (NetTimerCallback)(TLobby__sub_80411334));
    NetRegisterTimer(0x3E8, (s16)(1), (NetTimerCallback)(TLobby::tick_entry_timers));
    return 0;
}

s32 TLobby__sub_8041123C(s32 arg0, s32 arg1, s16 arg2) {
    struct Fields_temp_r3 { s16 field_0; s16 field_2; };
    u8 *temp_r3;
    if ((arg2 < 0) || (arg2 >= (s16) *(s16 *)((s8 *)(&ipv6_address_routing_state.value) + 2))) {
        return -0x10A;
    }
    temp_r3 = (u8 *)(*(s32 *)((s8 *)(&ipv6_address_routing_state.value) + 0x1C) + (arg2 * 0x30));
    if ((s16) ((Fields_temp_r3*)temp_r3)->field_0 != 1) {
        return -6;
    }
    return TLobby::call_handler_by_index(arg2, ((Fields_temp_r3*)temp_r3)->field_2, 0, arg1, arg0);
}

s32 TLobby__sub_804112B8(s32 arg0, s32 arg1, s16 arg2) {
    u8 *temp_r3;
    if ((arg2 < 0) || (arg2 >= (s16) *(s16 *)((s8 *)(&(*(RecoveredGlobal_804112B8_lbl_805C1BB8 *)&ipv6_address_routing_state).value) + 2))) {
        return -0x10A;
    }
    temp_r3 = (u8 *)(*(s32 *)((s8 *)(&(*(RecoveredGlobal_804112B8_lbl_805C1BB8 *)&ipv6_address_routing_state).value) + 0x1C) + (arg2 * 0x30));
    if (((Ipv6NdIface *)temp_r3)->state != 1) {
        return -6;
    }
    return TLobby::call_handler_by_index(arg2, ((Ipv6NdIface *)temp_r3)->f2, 2, arg1, arg0);
}

#pragma opt_common_subs reset
void TLobby__sub_80411334(void) {
    s16 NetIPv6SendRouterSolicitation(s16);

    Ipv6NdState *g = (Ipv6NdState *)&ipv6_address_routing_state;
    s16 i;
    s16 j;
    Ipv6NdIface *ifc;
    Ipv6NdAddr *a;
    Ipv6NdEvent ev;

    ifc = g->ifaces;
    for (i = 0; i < g->count; i++, ifc++) {
        if (ifc->state != 1 || i == 0) {
            continue;
        }
        switch (ifc->dad_state) {
        case 1:
            if (ifc->dad_count > 0) {
                if (ifc->dad_timer > 0) {
                    ifc->dad_timer--;
                } else {
                    NetIPv6SendUnspecifiedSourceNeighborSolicitation(ifc->addr, i);
                    ifc->dad_count--;
                    ifc->dad_timer = g->dad_interval;
                }
            } else {
                if (ifc->f18 == 0) {
                    ifc->dad_state = 4;
                } else {
                    ifc->dad_state = 3;
                }
                ev.addr = ifc->addr;
                ev.prefix_len = ifc->prefix_len;
                TLobby__sub_80411604(i, 0, &ev);
            }
            break;
        }
        if (ifc->rs_count > 0 && ifc->dad_state != 0) {
            if (ifc->rs_timer > 0) {
                ifc->rs_timer--;
            } else {
                NetIPv6SendRouterSolicitation(i);
                ifc->rs_count--;
                ifc->rs_timer = g->rs_interval;
            }
        }
        a = ifc->addrs;
        for (j = 0; a != NULL && j < g->max_addrs; j++) {
            switch (a->state) {
            case 0:
                break;
            case 1:
                if (a->dad_count > 0) {
                    if (a->dad_timer > 0) {
                        a->dad_timer--;
                    } else {
                        NetIPv6SendUnspecifiedSourceNeighborSolicitation(a->addr, i);
                        a->dad_count--;
                        a->dad_timer = g->dad_interval;
                    }
                } else {
                    if (a->f16 == 0) {
                        a->state = 4;
                    } else {
                        a->state = 3;
                    }
                    ev.addr = a->addr;
                    ev.prefix_len = a->prefix_len;
                    TLobby__sub_80411604(i, 0, &ev);
                }
                break;
            case 3:
                if (a->f24 != 0xFFFFFFFF && a->f24 != 0) {
                    a->f24--;
                    if (a->f24 == 0) {
                        a->state = 2;
                    }
                }
                if (a->f20 != 0xFFFFFFFF && a->f20 != 0) {
                    a->f20--;
                    if (a->f20 == 0) {
                        a->state = 0;
                    }
                }
                break;
            case 2:
                if (a->f20 != 0xFFFFFFFF && a->f20 != 0) {
                    a->f20--;
                    if (a->f20 == 0) {
                        a->state = 0;
                    }
                }
                break;
            case 4:
                break;
            }
            a = a->next;
        }
    }
}

s32 TLobby__sub_80411604(s16 id, int n, void *pp)
{
  s16 TLobby__sub_8042325C(s16, s32, s32, s32 (*)(s32, s32, s32));
  s32 TLobby__sub_8041347C(u8 *src, s16 id, u8 *key, s16 a, s16 b, s16 c);
  s16 TLobby__sub_80412618(void *, s16);
  void *h;
  s16 i;
  Ipv6NdState *g = (Ipv6NdState *)&ipv6_address_routing_state;
  s16 t;
  u8 *e;
  u8 *p = (u8 *) pp;
  u8 a92[16];
  s32 ret; /* results of the adds below, never checked; the original frame keeps both slots */
  s16 err;
  if ((id < 0) || (id >= (*((s16 *) (((u8 *) g) + offsetof(Ipv6NdState, count))))))
  {
    return -266;
  }
  e = *((u8 **) (((u8 *)g) + offsetof(Ipv6NdState, ifaces)));
  e += id * sizeof(Ipv6NdIface);
  if (((Ipv6NdIface *)e)->state != 1)
  {
    return -2;
  }
  t = 1;
  if ((h = ((Ipv6NdIface *)e)->f28) != 0)
  {
    t = TLobby__sub_8042325C(id, n, (s32)p, (s32 (*)(s32, s32, s32))h);
  }
  switch (n)
  {
    case 0:
    {
      u8 *ent = (u8 *)g->routes;
      Ipv6NdEvent *event = (Ipv6NdEvent *)p;
      for (i = 0; i < g->route_count; i++, ent += sizeof(Ipv6NdRoute))
    {
      Ipv6NdRoute *route = (Ipv6NdRoute *)ent;
      if (route->state == 1 && route->type == 0)
      {
        if (route->prefix_len == event->prefix_len)
        {
          if (cmp16_80411604(route->gateway, event->addr) == 0)
          {
            route->type = 1;
          }
        }
        else
          if (route->prefix_len == 128)
        {
          if (cmp16_80411604(route->prefix, event->addr) == 0)
          {
            route->type = 1;
          }
        }
      }
    }

      break;
    }

    case 1:
      if (((Ipv6NdIface *)e)->dad_timer > 0)
    {
      ((Ipv6NdIface *)e)->dad_timer = 0;
    }
      break;

    case 2:
      if (t == 1)
    {
      err = TLobby__sub_80412618(p, id);
    }
      break;

    case 3:
      ipv6_protocol_state.f14 = p[4];
      break;

    case 4:
      ((Ipv6NdIface *)e)->mtu = *((s32 *) (p + 4));
      break;

    case 5:
      if (t == 1)
    {
      NetMemset(a92, 0, 16);
      ret = TLobby__sub_8041347C(a92, 0, *((u8 **) p), id, 2, 4);
    }
      break;

    case 6:
      if (t == 1)
    {
      NetMemset(a92, 0, 16);
      remove_80411604(g, 0, a92, *((u8 **) p));
    }
      break;

    case 7:
      if (t == 1)
    {
      NetMemset(a92, 0, 16);
      remove_80411604(g, 0, a92, *((u8 **) p));
      ret = TLobby__sub_8041347C(a92, 0, *((u8 **) (p + 4)), id, 2, 4);
    }
      break;

    case 8:

    case 11:

    case 12:
      break;

    case 9:
      if (t == 1)
    {
      NetMemset(a92, 0, 16);
      remove_80411604(g, 0, a92, *((u8 **) p));
    }
      break;

    case 10:
      if (t == 1)
    {
      remove_80411604(g, *((s16 *) (p + 4)), *((u8 **) p), *((u8 **) (p + 8)));
      ret = TLobby__sub_8041347C(*((u8 **) p), 128, *((u8 **) (p + 12)), id, 3, 4);
    }
      break;

  }

  return 0;
}

void TLobby::tick_entry_timers() {
    G_80411BE8 *G = (G_80411BE8 *)&ipv6_address_routing_state;
    s16 i;
    Ent_80411BE8 *e = G->p;
    for (i = 0; i < G->n; i++, e++) {
        if (e->f0 == 1) {
            if (e->f14 > 0) {
                e->f14--;
            } else {
                e->f0 = 0;
            }
        }
    }
}

#pragma opt_common_subs on
s16 TLobby__sub_80411C44(IPv6Address *addr, s16 idx) {
    G_80411DEC *g = (G_80411DEC *)&ipv6_address_routing_state;
    Iface_80411C44 *ifc = iface_80411C44(g, idx);
    Ent_80411DEC *slot = NULL;
    s16 i;
    Ent_80411DEC *e;
    Ent_80411DEC *oldest = NULL;

    if (is_link_local_80411C44(addr)) {
        return ifc->mtu;
    }
    e = g->ents;
    for (i = 0; i < g->count; i++, e++) {
        if (e->state != 1) {
            if (slot == NULL) {
                slot = e;
            }
        } else {
            if (compare_addr_80411C44(&e->addr, addr) == 0) {
                if (e->mtu > ifc->mtu) {
                    if (ifc->mtu < 40) {
                        return -6;
                    }
                    e->mtu = ifc->mtu;
                }
                e->timer = g->lifetime;
                return e->mtu;
            }
            if (oldest == NULL) {
                oldest = e;
            } else if (e->timer < oldest->timer) {
                oldest = e;
            }
        }
    }
    if (slot == NULL) {
        slot = oldest;
    }
    if (ifc->mtu < 40) {
        return -6;
    }
    slot->state = 1;
    slot->timer = g->lifetime;
    NetMemcpy(&slot->addr, addr, sizeof(IPv6Address));
    slot->mtu = ifc->mtu;
    return slot->mtu;
}

s32 TLobby__sub_80411DEC(IPv6Address *addr, s16 mtu) {
    G_80411DEC *g = (G_80411DEC *)&ipv6_address_routing_state;
    s16 i;
    Ent_80411DEC *e;

    if (mtu < 40) {
        return -1;
    }
    e = g->ents;
    for (i = 0; i < g->count; i++, e++) {
        if (e->state == 1) {
            s32 r = NetMemcmp(&e->addr, addr, sizeof(IPv6Address));
            s16 c;
            if (r < 0) {
                c = -1;
            } else if (r > 0) {
                c = 1;
            } else {
                c = 0;
            }
            if (c == 0) {
                if (mtu >= 1280 && mtu < e->mtu) {
                    e->mtu = mtu;
                }
                e->timer = g->lifetime;
                return 0;
            }
        }
    }
    return -1;
}

s16 TLobby::get_entry_field_26(s16 arg0) {
    u8 *temp_r3;
    if ((arg0 < 0) || (arg0 >= (s16) *(s16 *)((s8 *)(&(*(RecoveredGlobal_80411ECC_lbl_805C1BB8 *)&ipv6_address_routing_state).value) + 2))) {
        return -0x10A;
    }
    temp_r3 = (u8 *)(*(s32 *)((s8 *)(&(*(RecoveredGlobal_80411ECC_lbl_805C1BB8 *)&ipv6_address_routing_state).value) + 0x1C) + (arg0 * 0x30));
    if (((Ipv6NdIface *)temp_r3)->state != 1) {
        return -2;
    }
    return ((Ipv6NdIface *)temp_r3)->mtu;
}

s32 TLobby__sub_80411F1C(u8 *out, u8 *dst, s16 idx) {
    Ipv6AddressState *g = (Ipv6AddressState *)&ipv6_address_routing_state;
    u8 *sel = NULL;
    s16 best = 0;
    s16 scope;
    Ipv6Iface *ifc;
    s16 n;
    Ipv6AddrNode *node;
    s16 score;
    s16 NetIPv6GetAddressScopeClass(u8 *);

    if (idx < 0 || idx >= g->count) {
        return -6;
    }
    ifc = g->ifaces + idx;
    scope = NetIPv6GetAddressScopeClass(dst);
    if (ifc->state == 1) {
        if (ifc->scope == scope) {
            score = TLobby__sub_80414218(ifc->addr, dst);
            if (score > 0) {
                best = score;
                sel = ifc->addr;
            }
        } else {
            best = 0;
            sel = ifc->addr;
        }
        node = ifc->nodes;
        for (n = 0; node != NULL && n < g->max_nodes; n++) {
            if (node->scope == scope) {
                score = TLobby__sub_80414218(node->addr, dst);
                if (score > best) {
                    best = score;
                    sel = node->addr;
                }
            }
            node = node->next;
        }
    }
    if (sel == NULL) {
        return -6;
    }
    NetMemcpy(out, sel, 16);
    return 0;
}

extern s32 TLobby__sub_80412058(s16 id, u8 *self, s32 len, u8 *out) {
    struct AddrRec_80412058 {
        u32 kind;
        u8 addr[0x10];
        s16 a;
        s16 b;
        u32 c;
    };
    s16 n;
    s32 i;
    struct AddrRec_80412058 rec;
    u8 *ent;
    u8 ref[8];
    u8 *cur;
    u8 *st;

    st = (u8 *)&ipv6_address_routing_state;
    if (id < 0 || id >= *(s16 *)(st + offsetof(Ipv6NdState, count))) {
        return -0x10A;
    }
    ent = *(u8 **)(st + offsetof(Ipv6NdState, ifaces));
    ent += id * sizeof(Ipv6NdIface);
    if (((Ipv6NdIface *)ent)->state != 1) {
        return -2;
    }
    if ((u32)(s16)len < 0x1C) {
        return -2;
    }
    rec.kind = 6;
    NetMemcpy(rec.addr, ((Ipv6NdIface *)ent)->addr, 0x10);
    rec.a = ((Ipv6NdIface *)ent)->prefix_len;
    rec.b = ((Ipv6NdIface *)ent)->f1A;
    rec.c = (u32)((Ipv6NdIface *)ent)->f28;
    NetBufferRefInitKind1((NetBufferRef *)ref, (s32)&rec);
    TLobby__sub_80406FD8(self, ref, 0x1C);
    TLobby__sub_80406EB8((NetBufferRef *)self, 0x1C);
    cur = (u8 *)((Ipv6NdIface *)ent)->addrs;
    i = 1;
    n = 0;
    len -= 0x1C;
    while ((u32)(s16)len >= 0x1C && cur != NULL && n < *(s16 *)(st + offsetof(Ipv6NdState, max_addrs))) {
        rec.kind = 6;
        NetMemcpy(rec.addr, ((Ipv6NdAddr *)cur)->addr, 0x10);
        rec.a = ((Ipv6NdAddr *)cur)->prefix_len;
        rec.b = ((Ipv6NdAddr *)cur)->f18;
        rec.c = 0;
        NetBufferRefInitKind1((NetBufferRef *)ref, (s32)&rec);
        TLobby__sub_80406FD8(self, ref, 0x1C);
        TLobby__sub_80406EB8((NetBufferRef *)self, 0x1C);
        cur = (u8 *)((Ipv6NdAddr *)cur)->next;
        i++;
        n++;
        len -= 0x1C;
    }
    if ((s16)TLobby__sub_80409EB0(id, *(s16 *)(ent + offsetof(Ipv6NdIface, f2))) <= 6) {
        TLobby__sub_80409E18(id, *(s16 *)(ent + offsetof(Ipv6NdIface, f2)), (s32)out);
    }
    return i;
}

s16 TLobby__sub_80412210(s16 idx) {
    G_80412210 *g = ((G_80412210 *)&ipv6_address_routing_state);
    u8 d[16];
    u8 c[16];
    u8 b[16];
    u8 a[16];
    s16 *pn;
    If_80412210 **pifs;
    s16 count;
    If_80412210 *ifc;
    Grp_80412210 *grp;

    if (idx < 0 || idx >= *(pn = &g->f2)) {
        return -0x10A;
    }
    ifc = *(pifs = &g->ifs);
    ifc += idx;
    if (ifc->f0 != 1) {
        return 0;
    }
    grp = ifc->f2c;
    count = 0;
    while (grp != NULL && count < g->f4) {
        Grp_80412210 *next;
        if (is_socket_flag_set__6TLobbyFs(idx) == 0 && getaddr_80412210(pn, pifs, d)) {
            TLobby__sub_80414B98(b, 0x80, grp->f2);
            remove_80412210(g, b, d);
        }
        TLobby__sub_80409D7C(idx, ifc->f2, 2, (s32)grp->f2);
        NetIPv6MakeSolicitedNodeMulticastAddress(c, grp->f2);
        TLobby__sub_80409CE0(idx, ifc->f2, 2, (s32)c);
        next = grp->f28;
        grp->f0 = 0;
        NetMemset(grp->f2, 0, 16);
        grp->f12 = 0;
        count++;
        grp->f28 = NULL;
        grp = next;
    }
    if (is_socket_flag_set__6TLobbyFs(idx) == 0 && getaddr_80412210(pn, pifs, d)) {
        TLobby__sub_80414B98(a, 0x80, ifc->f4);
        remove_80412210(g, a, d);
    }
    {
        Ent_80412210 *e;
        s16 n;
        n = g->f0;
        e = g->table;
        for (; n > 0; n--, e++) {
            if (e->f0 == 1 && e->f6 == idx) {
                e->f0 = 0;
            }
        }
    }
    NetIPv6MakeSolicitedNodeMulticastAddress(c, ifc->f4);
    TLobby__sub_80409CE0(idx, ifc->f2, 2, (s32)c);
    init_ipv6_all_nodes_multicast_address(c, (s8)(2));
    TLobby__sub_80409CE0(idx, ifc->f2, 2, (s32)c);
    init_ipv6_all_nodes_multicast_address(c, (s8)(1));
    TLobby__sub_80409CE0(idx, ifc->f2, 2, (s32)c);
    TLobby::call_entry_callback(idx, ifc->f2);
    ifc->f0 = 0;
    ifc->f2 = 0;
    ifc->f26 = 0;
    NetMemset(ifc->f4, 0, 16);
    ifc->f14 = 0;
    ifc->f2c = NULL;
    ifc->f28 = 0;
    return 0;
}

s16 TLobby__sub_80412618(void *pi_arg, s16 idx)
{
  s16 TLobby__sub_8040A0C0(s16, u8 *);
  s16 TLobby__sub_80409D7C(s16, s32, s32, s32);
  s16 TLobby__sub_80409CE0(s16, s32, s32, s32);
  s16 NetCompareBitPrefix(u8 *, u8 *, s16);
  s16 TLobby__sub_8041347C(u8 *, s16, u8 *, s16, s16, s16);
    Ipv6NdPrefixEvent *pi = (Ipv6NdPrefixEvent *)pi_arg;
    Ipv6NdState *g = (Ipv6NdState *)&ipv6_address_routing_state;
    u8 *pfx;
    Ipv6NdRoute *route;
    u32 v;
    s16 rem;
    u8 *q;
    Ipv6NdIface *e;
    u8 mask;
    s32 plen;
    Ipv6NdAddr *cur;
    s16 r;
    s16 *pc;
    s16 n8;
    s16 fl;
    s16 found;
    s16 i;
    u8 new_addr[16];
    u8 iface0_addr[16];
    u8 solicited[16];
    s16 err;
    Ipv6NdAddr *node;

    if (idx <= 0 || idx >= *(s16 *)((u8 *)g + offsetof(Ipv6NdState, count))) {
        return -266;
    }
    e = *(Ipv6NdIface **)((u8 *)g + offsetof(Ipv6NdState, ifaces));
    e += idx;
    if (e->state != 1) {
        return -2;
    }
    NetMemset(new_addr, 0, 8);
    r = TLobby__sub_8040A0C0(idx, new_addr + 8);
    if (r < 0) {
        return r;
    }
    pfx = (u8 *)pi_arg;
    plen = ((Ipv6NdPrefixEvent *)pfx)->prefix_len;
    pfx = ((Ipv6NdPrefixEvent *)pfx)->prefix;
    if ((s16)plen > 0) {
        n8 = plen / 8;
        NetMemcpy(new_addr, pfx, n8);
        if ((rem = plen % 8) != 0) {
            q = new_addr + n8;
            mask = 255 >> rem;
            *q = (mask & *q) | (pfx[n8] & ~mask);
        }
    }
    if (cmp16_80412618(new_addr, e->addr) == 0) {
        return 0;
    }
    if (e->addrs != 0) {
        node = e->addrs;
        found = 0;
        i = 0;
        for (; node != 0 && i < g->max_addrs; node = node->next, i++) {
            if (node->f16 == 0) {
                if (cmp16_80412618(new_addr, node->addr) == 0) {
                    found = 1;
                }
            } else if (pi->prefix_len == node->prefix_len) {
                if (NetCompareBitPrefix(pi->prefix, node->addr, pi->prefix_len) == 0) {
                    found = 1;
                    v = pi->valid_lifetime;
                    if (v > 7200 || v > node->f20) {
                        node->f20 = v;
                        node->f24 = pi->preferred_lifetime;
                    } else if (node->f20 > 7200 || v > node->f20) {
                        node->f20 = 7200;
                    }
                }
            }
        }

        if (found) {
            return 0;
        }
    }
    pc = (s16 *)((u8 *)g + offsetof(Ipv6NdState, max_addrs));
    pfx = (u8 *)g->addr_pool;
    r = *(s16 *)((u8 *)g + offsetof(Ipv6NdState, max_addrs));
    for (i = 0; i < r; i++, pfx += sizeof(Ipv6NdAddr)) {
        if (((Ipv6NdAddr *)pfx)->f0 == 0) {
            ((Ipv6NdAddr *)pfx)->f0 = 1;
            break;
        }
    }

    if (i >= *pc) {
        return -266;
    }
    r = TLobby__sub_80409D7C(idx, e->f2, 1, (s32)new_addr);
    if (r < 0) {
        ((Ipv6NdAddr *)pfx)->f0 = 0;
        return r;
    }
    NetMemcpy(((Ipv6NdAddr *)pfx)->addr, new_addr, 16);
    ((Ipv6NdAddr *)pfx)->prefix_len = pi->prefix_len;
    fl = 1;
    ((Ipv6NdAddr *)pfx)->f16 = fl;
    ((Ipv6NdAddr *)pfx)->f18 = 0;
    ((Ipv6NdAddr *)pfx)->scope = NetIPv6GetAddressScopeClass(new_addr);
    if (TLobby::is_entry_flag10_set(idx) != 0) {
        ((Ipv6NdAddr *)pfx)->state = fl;
        fl = 0;
        ((Ipv6NdAddr *)pfx)->dad_count = g->dad_count_init;
        ((Ipv6NdAddr *)pfx)->dad_timer = g->dad_timer_init;
    } else {
        ((Ipv6NdAddr *)pfx)->state = 3;
        fl = 1;
        ((Ipv6NdAddr *)pfx)->dad_count = 0;
        ((Ipv6NdAddr *)pfx)->dad_timer = 0;
    }
    ((Ipv6NdAddr *)pfx)->f20 = pi->valid_lifetime;
    ((Ipv6NdAddr *)pfx)->f24 = pi->preferred_lifetime;
    ((Ipv6NdAddr *)pfx)->next = 0;
    if (e->addrs == 0) {
        e->addrs = (Ipv6NdAddr *)pfx;
    } else {
        cur = e->addrs;
        for (i = 0; i < *pc; i++) {
            if (cur->next == 0) {
                break;
            }
            cur = cur->next;
        }

        if (cur->next == 0) {
            cur->next = (Ipv6NdAddr *)pfx;
        }
    }
    found = getaddr_80412618((s16 *)((u8 *)g + offsetof(Ipv6NdState, count)),
                             (u8 **)((u8 *)g + offsetof(Ipv6NdState, ifaces)), iface0_addr);
    if (found != 0) {
        r = TLobby__sub_8041347C(new_addr, 128, iface0_addr, 0, 3, 1);
        if (r < 0) {
            goto release;
        }
    }
    route = (Ipv6NdRoute *)TLobby__sub_80413264(new_addr, (s32)new_addr);
    if (route != 0 && route->prefix_len == pi->prefix_len) {
        if (route->iface != idx) {
            goto drop_route;
        }
    } else {
        r = TLobby__sub_8041347C(new_addr, pi->prefix_len, new_addr, idx, fl, 1);
        if (r < 0) {
            goto drop_route;
        }
    }
    NetIPv6MakeSolicitedNodeMulticastAddress(solicited, new_addr);
    r = TLobby__sub_80409CE0(idx, e->f2, 1, (s32)solicited);
    if (r >= 0) {
        return 0;
    }
    remove_80412618(g, pi->prefix_len, new_addr, new_addr);
drop_route:
    if (is_socket_flag_set__6TLobbyFs(idx) == 0) {
        remove_80412618(g, 128, new_addr, iface0_addr);
    }

release:
    err = TLobby__sub_80409D7C(idx, e->f2, 2, (s32)new_addr);

    if (e->addrs == (Ipv6NdAddr *)pfx) {
        e->addrs = 0;
    } else {
        cur->next = 0;
    }
    return r;
}

s16 TLobby__sub_80412CA4(u8 *addr, s16 plen, s16 x, s16 idx, s32 y)
{
  s16 TLobby__sub_8040A0C0(s16, u8 *);
  s16 TLobby__sub_8041347C(u8 *, s16, u8 *, s16, s16, s16);
  s16 TLobby__sub_80409CE0(s16, s32, s32, s32);
  s16 NetCompareBitsBackward(u8 *, u8 *, s16);
  s16 NetIPv6GetAddressScopeClass(u8 *);
    Ipv6NdState *g = (Ipv6NdState *)&ipv6_address_routing_state;
    s16 *pn;
    Ipv6NdIface **pifs;
    Ipv6NdIface *e;
    s16 r;
    s16 ret;
    s16 found;
    s16 fl;
    s16 n8;
    s16 rem;
    u8 *q;
    u8 mask;
    u8 tmp[16];
    u8 ll[16];
    u8 mcast[16];
    s32 err; /* release-path callback result, never checked (80411604 keeps such results too) */

    if (idx < 0 || idx >= *(pn = &g->count)) {
        return -266;
    }
    e = *(pifs = &g->ifaces);
    e += idx;
    if (e->state == 1) {
        return -2;
    }
    e->state = 1;
    NetMemset(tmp, 0, 16);
    if (NetCompareBitsBackward(tmp + 15, addr + 15, 128 - plen) != 0) {
        NetMemcpy(tmp, addr, 16);
    } else {
        r = TLobby__sub_8040A0C0(idx, tmp + 8);
        if (r < 0) {
            e->state = 0;
            return r;
        }
        if (plen > 0) {
            n8 = plen / 8;
            NetMemcpy(tmp, addr, n8);
            rem = plen % 8;
            if (rem != 0) {
                q = tmp + n8;
                mask = 255 >> rem;
                *q = (mask & *q) | (addr[n8] & ~mask);
            }
        }
    }
    e->f2 = TLobby__sub_8040A044(idx, 0x86DD, 16, tmp);
    if (e->f2 < 0) {
        e->state = 0;
        return e->f2;
    }
    r = TLobby::invoke_socket_callback(idx, e->f2);
    if (r < g->min_mtu) {
        e->state = 0;
        return -6;
    }
    e->mtu = r;
    NetMemcpy(e->addr, tmp, 16);
    e->prefix_len = plen;
    e->f18 = 0;
    e->f1A = x;
    e->scope = NetIPv6GetAddressScopeClass(tmp);
    if (TLobby::is_entry_flag10_set(idx)) {
        e->dad_state = 1;
        fl = 0;
        e->dad_count = g->dad_count_init;
        e->dad_timer = g->dad_timer_init;
    } else {
        e->dad_state = 4;
        fl = 1;
        e->dad_count = 0;
        e->dad_timer = 0;
    }
    if (TLobby::is_slot_flag_0x40_set(idx)) {
        e->rs_count = g->rs_count_init;
        e->rs_timer = g->rs_timer_init;
    } else {
        e->rs_count = 0;
        e->rs_timer = 0;
    }
    e->f28 = (void *)y;
    e->addrs = NULL;
    if (!is_socket_flag_set__6TLobbyFs(idx)) {
        found = getaddr_80412CA4(pn, pifs, ll);
        if (found) {
            ret = TLobby__sub_8041347C(tmp, 128, ll, 0, 3, 1);
            if (ret < 0) {
                goto release;
            }
        }
        ret = TLobby__sub_8041347C(tmp, plen, tmp, idx, fl, 1);
        if (ret < 0) {
            goto remove_ll;
        }
    } else {
        ret = TLobby__sub_8041347C(tmp, plen, tmp, idx, fl, 1);
        if (ret < 0) {
            goto remove_ll;
        }
    }
    init_ipv6_all_nodes_multicast_address(mcast, 1);
    ret = TLobby__sub_80409CE0(idx, e->f2, 1, (s32)mcast);
    if (ret < 0) {
        goto remove;
    }
    init_ipv6_all_nodes_multicast_address(mcast, 2);
    ret = TLobby__sub_80409CE0(idx, e->f2, 1, (s32)mcast);
    if (ret < 0) {
        goto remove;
    }
    NetIPv6MakeSolicitedNodeMulticastAddress(mcast, tmp);
    ret = TLobby__sub_80409CE0(idx, e->f2, 1, (s32)mcast);
    if (ret >= 0) {
        return 0;
    }
remove:
    remove_80412618(g, plen, tmp, tmp);
remove_ll:
    if (!is_socket_flag_set__6TLobbyFs(idx)) {
        remove_80412618(g, 128, tmp, ll);
    }
release:
    /* result never read: the original frame keeps its 4-byte slot (release-dead check) */
    err = TLobby::call_entry_callback(idx, e->f2);
    e->state = 0;
    e->f2 = 0;
    e->mtu = 0;
    NetMemset(e->addr, 0, 16);
    e->prefix_len = 0;
    return ret;
}

#pragma opt_common_subs reset
s32 TLobby__sub_80413230(u8 *arg0, s32 arg1) {
    if (TLobby__sub_80413264(arg0, arg1) != NULL) {
        return 1;
    }
    return 0;
}

u8 *TLobby__sub_80413264(void *dst, s32 src) {
    s16 NetCompareBitPrefix(u8 *a, u8 *b, s16 bits);
    s16 NetIPv6IsUnspecified(u8 *arg0);
    s16 TLobby__sub_804137FC(u8 *addr, s16 idx);
    Ipv6RouteTable *g = (Ipv6RouteTable *)&ipv6_address_routing_state;
    s16 i;
    Ipv6PrefixRoute *rt;
    Ipv6PrefixRoute *host = NULL;
    Ipv6PrefixRoute *prefix = NULL;
    Ipv6PrefixRoute *deflt = NULL;

    rt = routes_80413264(g);
    for (i = 0; i < g->count; i++, rt++) {
        if (rt->state != 1) {
            continue;
        }
        switch (rt->type) {
        case 3:
            if (NetCompareBitPrefix(rt->prefix, (u8 *)dst, rt->prefix_len) == 0) {
                return (u8 *)rt;
            }
            break;
        case 1:
            if (is_multicast_80413264((IPv6Address *)dst)) {
                if (TLobby__sub_804137FC((u8 *)src, rt->iface) != 0) {
                    host = rt;
                }
            } else if (NetCompareBitPrefix(rt->prefix, (u8 *)dst, rt->prefix_len) == 0) {
                if (is_link_local_80411C44((IPv6Address *)dst)) {
                    if (TLobby__sub_804137FC((u8 *)src, rt->iface) != 0) {
                        host = rt;
                    }
                } else if (host == NULL) {
                    host = rt;
                } else if (rt->prefix_len > host->prefix_len) {
                    host = rt;
                }
            }
            break;
        case 2:
            if (NetIPv6IsUnspecified(rt->prefix)) {
                if (deflt == NULL) {
                    deflt = rt;
                }
            } else if (NetCompareBitPrefix(rt->prefix, (u8 *)dst, rt->prefix_len) == 0) {
                if (prefix == NULL) {
                    prefix = rt;
                } else if (rt->prefix_len > prefix->prefix_len) {
                    prefix = rt;
                }
            }
            break;
        }
    }
    if (host != NULL) {
        return (u8 *)host;
    }
    if (prefix != NULL) {
        return (u8 *)prefix;
    }
    if (deflt != NULL) {
        return (u8 *)deflt;
    }
    return NULL;
}

s32 TLobby__sub_8041347C(u8 *prefix, s16 bits, u8 *addr, s16 idx, s16 kind, s16 mode) {
    s16 len;
    G_80412210 *g = (G_80412210 *)&ipv6_address_routing_state;
    s16 i;
    Ent_80412210 *e;
    Ent_80412210 *sel;
    u8 key[16];

    if (bits < 0 || bits > 0x80) {
        return -2;
    }
    if (idx < 0 || idx >= g->f2) {
        return -2;
    }
    if (kind != 1 && kind != 2 && kind != 3 && kind != 0) {
        return -2;
    }
    if (mode != 1 && mode != 2 && mode != 3 && mode != 4) {
        return -2;
    }
    TLobby__sub_80414B98(key, bits, prefix);
    e = g->table;
    len = bits;
    sel = NULL;
    for (i = 0; i < g->f0; i++, e++) {
        if (e->f0 == 1) {
            if (e->f28 == len && cmp_80412210(e->f8, key) == 0) {
                if (!is_link_local_8041347C(key) || cmp_80412210(e->f18, addr) == 0) {
                    return -2;
                }
            }
        } else {
            sel = e;
            break;
        }
    }
    if (sel == NULL) {
        return -0x108;
    }
    sel->f0 = 1;
    NetMemcpy(sel->f8, key, 16);
    NetMemcpy(sel->f18, addr, 16);
    sel->f2 = kind;
    sel->f4 = mode;
    sel->f28 = bits;
    sel->f6 = idx;
    return 0;
}

void TLobby__sub_804136AC(s16 i) {
    TLobby::is_slot_flag_0x20_set(i);
}

s16 TLobby__sub_804136CC(s16 i) {
    return is_socket_flag_set__6TLobbyFs(i);
}

s16 TLobby__sub_804136EC(u8 *addr) {
    Ipv6AddressState *g = (Ipv6AddressState *)&ipv6_address_routing_state;
    s16 i;
    s16 n;
    Ipv6Iface *ifc;
    Ipv6AddrNode *node;

    i = 0;
    ifc = g->ifaces;
    for (; i < g->count; i++, ifc++) {
        if (ifc->state == 1) {
            if (addr_cmp_804136EC(ifc->addr, addr) == 0) {
                return i;
            }
            node = ifc->nodes;
            for (n = 0; node != NULL && n < g->max_nodes; n++) {
                if (addr_cmp_804136EC(node->addr, addr) == 0) {
                    return i;
                }
                node = node->next;
            }
        }
    }
    return -6;
}

s16 TLobby__sub_804137FC(u8 *addr, s16 idx) {
    Ipv6AddressState *g = (Ipv6AddressState *)&ipv6_address_routing_state;
    Ipv6Iface *ifc;
    s16 n;
    Ipv6AddrNode *node;

    if (idx < 0 || idx >= g->count) {
        return 0;
    }
    ifc = g->ifaces;
    ifc += idx;
    if (ifc->state != 1) {
        return 0;
    }
    if (addr_cmp_804136EC(ifc->addr, addr) == 0) {
        return 1;
    }
    node = ifc->nodes;
    for (n = 0; node != NULL && n < g->max_nodes; n++) {
        if (addr_cmp_804136EC(node->addr, addr) == 0) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

s16 TLobby__sub_80413934(u8 *addr, s16 idx) {
    Ipv6AddressState *g = (Ipv6AddressState *)&ipv6_address_routing_state;
    Ipv6Iface *ifc;
    s16 n;
    Ipv6AddrNode *node;

    ifc = get_iface_804136EC(g, idx);
    if (ifc == NULL) {
        return 0;
    }
    if (addr_cmp_804136EC(ifc->addr, addr) == 0) {
        if (ifc->f16 < 3) {
            return 0;
        }
        return 1;
    }
    node = ifc->nodes;
    for (n = 0; node != NULL && n < g->max_nodes; n++) {
        if (addr_cmp_804136EC(node->addr, addr) == 0) {
            if (node->f14 < 3) {
                return 0;
            }
            return 1;
        }
        node = node->next;
    }
    return 0;
}

s16 TLobby__sub_80413AA0(u8 *addr, s16 idx) {
    Ipv6AddressState *g = (Ipv6AddressState *)&ipv6_address_routing_state;
    Ipv6Iface *ifc;
    s16 n;
    Ipv6AddrNode *node;

    ifc = get_iface_804136EC(g, idx);
    if (ifc == NULL) {
        return 0;
    }
    if (addr_cmp_804136EC(ifc->addr, addr) == 0) {
        if (ifc->f16 < 2) {
            return 0;
        }
        return 1;
    }
    node = ifc->nodes;
    for (n = 0; node != NULL && n < g->max_nodes; n++) {
        if (addr_cmp_804136EC(node->addr, addr) == 0) {
            if (node->f14 < 2) {
                return 0;
            }
            return 1;
        }
        node = node->next;
    }
    return 0;
}

s16 TLobby__sub_80413C0C(u8 *addr, s16 idx) {
    Ipv6AddressState *g = (Ipv6AddressState *)&ipv6_address_routing_state;
    Ipv6Iface *ifc;
    s16 n;
    Ipv6AddrNode *node;

    ifc = get_iface_804136EC(g, idx);
    if (ifc == NULL) {
        return 0;
    }
    if (addr_cmp_804136EC(ifc->addr, addr) == 0) {
        if (ifc->f16 == 1) {
            return 1;
        }
        return 0;
    }
    node = ifc->nodes;
    for (n = 0; node != NULL && n < g->max_nodes; n++) {
        if (addr_cmp_804136EC(node->addr, addr) == 0) {
            if (node->f14 == 1) {
                return 1;
            }
            return 0;
        }
        node = node->next;
    }
    return 0;
}

s16 TLobby__sub_80413D78(u8 *addr, s16 idx) {
    Ipv6AddressState *g = (Ipv6AddressState *)&ipv6_address_routing_state;
    Ipv6Iface *ifc;
    s16 n;
    Ipv6AddrNode *node;

    if (is_multicast_804136EC(addr)) {
        return 0;
    }
    ifc = get_iface_804136EC(g, idx);
    if (ifc == NULL) {
        return 0;
    }
    if (addr_cmp_804136EC(ifc->addr, addr) == 0) {
        if (!(ifc->f1A & 1)) {
            return 0;
        }
        return 1;
    }
    node = ifc->nodes;
    for (n = 0; node != NULL && n < g->max_nodes; n++) {
        if (addr_cmp_804136EC(node->addr, addr) == 0) {
            if (!(node->f18 & 1)) {
                return 0;
            }
            return 1;
        }
        node = node->next;
    }
    return 0;
}

s16 TLobby__sub_80413F0C(u8 *addr, s16 idx) {
    Ipv6AddressState *g = (Ipv6AddressState *)&ipv6_address_routing_state;
    Ipv6Iface *ifc;
    s16 n;
    Ipv6AddrNode *node;
    u8 solicited[16];

    if (!is_multicast_804136EC(addr)) {
        return 0;
    }
    ifc = get_iface_804136EC(g, idx);
    if (ifc == NULL) {
        return 0;
    }
    NetIPv6MakeSolicitedNodeMulticastAddress(solicited, ifc->addr);
    if (addr_cmp_804136EC(solicited, addr) == 0) {
        return 1;
    }
    node = ifc->nodes;
    for (n = 0; node != NULL && n < g->max_nodes; n++) {
        NetIPv6MakeSolicitedNodeMulticastAddress(solicited, node->addr);
        if (addr_cmp_804136EC(solicited, addr) == 0) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

s16 TLobby__sub_80414090(u8 *addr, s16 idx) {
    Ipv6AddressState *g = (Ipv6AddressState *)&ipv6_address_routing_state;
    Ipv6Iface *ifc;
    s16 n;
    Ipv6AddrNode *node;

    if (!is_link_local_804136EC(addr)) {
        return 0;
    }
    ifc = lookup_iface_804136EC(g, idx);
    if (ifc == NULL) {
        return 0;
    }
    if (addr_cmp_804136EC(ifc->addr, addr) == 0) {
        return 1;
    }
    node = ifc->nodes;
    for (n = 0; node != NULL && n < g->max_nodes; n++) {
        if (addr_cmp_804136EC(node->addr, addr) == 0) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

s16 TLobby__sub_80414218(u8 *a, u8 *b) {
    s16 i;
    s16 bit;
    s16 count = 0;

    for (i = 0; i < 16; i++, a++, b++) {
        for (bit = 0; bit < 8; bit++) {
            switch (bit) {
            case 0:
                if ((*a & 0x80) != (*b & 0x80)) {
                    return count;
                }
                count++;
                break;
            case 1:
                if ((*a & 0x40) != (*b & 0x40)) {
                    return count;
                }
                count++;
                break;
            case 2:
                if ((*a & 0x20) != (*b & 0x20)) {
                    return count;
                }
                count++;
                break;
            case 3:
                if ((*a & 0x10) != (*b & 0x10)) {
                    return count;
                }
                count++;
                break;
            case 4:
                if ((*a & 0x08) != (*b & 0x08)) {
                    return count;
                }
                count++;
                break;
            case 5:
                if ((*a & 0x04) != (*b & 0x04)) {
                    return count;
                }
                count++;
                break;
            case 6:
                if ((*a & 0x02) != (*b & 0x02)) {
                    return count;
                }
                count++;
                break;
            case 7:
                if ((*a & 0x01) != (*b & 0x01)) {
                    return count;
                }
                count++;
                break;
            }
        }
    }
    return count;
}

s32 NetIPv6GetAddressScopeClass(u8 *arg0) {
    s16 var_r0;
    s16 var_r0_2;
    s16 var_r0_3;
    s16 var_r0_4;
    s32 var_r3;
    u8 var_r4;
    u8 var_r5;

    var_r5 = ((RecoveredFields_804143BC_arg0 *)arg0)->field_0;
    if (var_r5 != 0xFE) {
        var_r0 = 0;
    } else {
        var_r4 = ((RecoveredFields_804143BC_arg0 *)arg0)->field_1;
        if (!(var_r4 & 0x80) || (var_r4 & 0x40)) {
            var_r0 = 0;
        } else {
            var_r0 = 1;
        }
    }
    if (var_r0 != 0) {
        var_r3 = 2;
        return 2;
    }
    if (var_r5 != 0xFE) {
        var_r0_2 = 0;
    } else {
        var_r4 = ((RecoveredFields_804143BC_arg0 *)arg0)->field_1;
        if (!(var_r4 & 0x80) || !(var_r4 & 0x40)) {
            var_r0_2 = 0;
        } else {
            var_r0_2 = 1;
        }
    }
    if (var_r0_2 != 0) {
        var_r3 = 3;
        return 3;
    }
    if ((s32) (var_r5 & 0xE0) != 0x20) {
        var_r0_3 = 0;
    } else {
        var_r0_3 = 1;
    }
    if (var_r0_3 != 0) {
        var_r3 = 4;
        return 4;
    }
    if (var_r5 == 0xFF) {
        var_r0_4 = 1;
    } else {
        var_r0_4 = 0;
    }
    if (var_r0_4 != 0) {
        switch (((RecoveredFields_804143BC_arg0 *)arg0)->field_1 & 0xF) {
        case 1:
            var_r3 = 1;
            return 1;
        case 2:
            var_r3 = 2;
            return 2;
        case 5:
            var_r3 = 3;
            return 3;
        default:
            var_r3 = 4;
            return 4;
        }
    } else {
        if (NetIPv6IsLoopback(arg0) != 0) {
            var_r3 = 1;
            return 1;
        }
        var_r3 = 0;
        return 0;
    }
}

s16 NetIPv6GetInterfaceLinkLayerAddress(s32 arg0, s16 arg1, s16 id) {
    Ent_80414504 *e;
    s16 r;
    s16 TLobby__sub_80409EB0(s16 arg0, s32 arg1);

    e = find_80414504(id);
    if (e == NULL) {
        return -0x10A;
    }
    r = TLobby__sub_80409EB0(id, e->f2);
    if (r < 0) {
        return r;
    }
    if (r > arg1) {
        return -2;
    }
    TLobby__sub_80409E18(id, e->f2, arg0);
    return r;
}

s16 TLobby__sub_804145D4(u8 *out, s16 idx) {
    Ipv6AddressState *g = (Ipv6AddressState *)&ipv6_address_routing_state;
    Ipv6Iface *ifc;
    s16 n;
    Ipv6AddrNode *node;
    u8 *addr;
    s16 max_nodes;

    ifc = get_iface_804136EC(g, idx);
    if (ifc == NULL) {
        return -0x10A;
    }
    addr = ifc->addr;
    if (is_link_local_804136EC(addr)) {
        NetMemcpy(out, ifc->addr, 16);
        return 0;
    }
    node = ifc->nodes;
    n = 0;
    max_nodes = g->max_nodes;
    for (; node != NULL && n < max_nodes; n++) {
        addr = node->addr;
        if (is_link_local_804136EC(addr)) {
            NetMemcpy(out, node->addr, 16);
            return 0;
        }
        node = node->next;
    }
    return -0x10A;
}

#pragma opt_common_subs on
s16 *TLobby::get_valid_entry(s16 arg0) {
    s16 *temp_r3;
    if ((arg0 < 0) || (arg0 >= (s16) *(s16 *)((s8 *)(&(*(RecoveredGlobal_8041471C_lbl_805C1BB8 *)&ipv6_address_routing_state).value) + 2))) {
        return NULL;
    }
    temp_r3 = (s16 *)(*(s32 *)((s8 *)(&(*(RecoveredGlobal_8041471C_lbl_805C1BB8 *)&ipv6_address_routing_state).value) + 0x1C) + (arg0 * 0x30));
    if (((Ipv6NdIface *)temp_r3)->state != 1) {
        return NULL;
    }
    return temp_r3;
}

s32 NetIPv6MakeSolicitedNodeMulticastAddress(u8 *arg0, u8 *arg1) {
    IPv6Address *dst = (IPv6Address *)arg0;
    IPv6Address *src = (IPv6Address *)arg1;
    dst->bytes[0] = 0xFF;
    dst->bytes[1] = 2;
    dst->bytes[2] = 0;
    dst->bytes[3] = 0;
    dst->bytes[4] = 0;
    dst->bytes[5] = 0;
    dst->bytes[6] = 0;
    dst->bytes[7] = 0;
    dst->bytes[8] = 0;
    dst->bytes[9] = 0;
    dst->bytes[0xA] = 0;
    dst->bytes[0xB] = 1;
    dst->bytes[0xC] = 0xFF;
    dst->bytes[0xD] = src->bytes[0xD];
    dst->bytes[0xE] = src->bytes[0xE];
    dst->bytes[0xF] = src->bytes[0xF];
    return 0;
}

s32 init_ipv6_all_routers_multicast_address(u8 *address, s8 scope) {
    address[0] = 0xFF;
    address[1] = scope;
    address[2] = 0;
    address[3] = 0;
    address[4] = 0;
    address[5] = 0;
    address[6] = 0;
    address[7] = 0;
    address[8] = 0;
    address[9] = 0;
    address[0xA] = 0;
    address[0xB] = 0;
    address[0xC] = 0;
    address[0xD] = 0;
    address[0xE] = 0;
    address[0xF] = 2;
    return 0;
}

bool init_ipv6_all_nodes_multicast_address(u8 *address, s8 scope) {
    address[0] = 0xFF;
    address[1] = scope;
    address[2] = 0;
    address[3] = 0;
    address[4] = 0;
    address[5] = 0;
    address[6] = 0;
    address[7] = 0;
    address[8] = 0;
    address[9] = 0;
    address[0xA] = 0;
    address[0xB] = 0;
    address[0xC] = 0;
    address[0xD] = 0;
    address[0xE] = 0;
    address[0xF] = 1;
    return 0;
}

s32 NetIPv6IsLinkLocal(u8 *arg0) {
    u8 temp_r3;

    if ((u8) *(u8 *)((s8 *)arg0 + 0) != 0xFE) {
        return 0;
    }
    temp_r3 = *(u8 *)((s8 *)arg0 + 1);
    if (!(temp_r3 & 0x80) || (temp_r3 & 0x40)) {
        return 0;
    }
    return 1;
}

s16 NetIPv6IsLoopback(u8 *arg0) {
    struct Fields_arg0 { u8 field_0; u8 field_1; u8 field_2; u8 field_3; u8 field_4; u8 field_5; u8 field_6; u8 field_7; u8 field_8; u8 field_9; u8 field_A; u8 field_B; u8 field_C; u8 field_D; u8 field_E; u8 field_F; };
    if ((u8) ((Fields_arg0*)arg0)->field_0 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_1 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_2 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_3 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_4 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_5 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_6 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_7 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_8 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_9 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_A != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_B != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_C != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_D != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_E != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_F == 1) {
        return 1;
    }
    return 0;
}

s32 NetIPv6IsMulticast(u8 *arg0) {
    if ((u8) *arg0 == 0xFF) {
        return 1;
    }
    return 0;
}

s32 NetIPv6IsUnspecified(u8 *arg0) {
    struct Fields_arg0 { u8 field_0; u8 field_1; u8 field_2; u8 field_3; u8 field_4; u8 field_5; u8 field_6; u8 field_7; u8 field_8; u8 field_9; u8 field_A; u8 field_B; u8 field_C; u8 field_D; u8 field_E; u8 field_F; };
    if ((u8) ((Fields_arg0*)arg0)->field_0 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_1 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_2 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_3 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_4 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_5 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_6 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_7 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_8 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_9 != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_A != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_B != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_C != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_D != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_E != 0) {
        return 0;
    }
    if ((u8) ((Fields_arg0*)arg0)->field_F != 0) {
        return 0;
    }
    return 1;
}

s16 NetIPv6CompareAddresses(s32 arg0, s32 arg1) {
    s32 temp_r3;
    temp_r3 = NetMemcmp((void *)arg0, (void *)arg1, 0x10);
    if (temp_r3 < 0) {
        return -1;
    }
    if (temp_r3 > 0) {
        return 1;
    }
    return 0;
}

void TLobby__sub_80414B98(u8 *dst, s16 bits, u8 *src) {
    s16 len;
    s16 i;
    s16 rem;
    s16 bytes;

    if (bits < 0 || bits > 0x80) {
        return;
    }
    bytes = (len = bits) / 8;
    rem = len % 8;
    for (i = 0; i < bytes; i++) {
        *dst++ = *src++;
    }
    switch (rem) {
    case 7:
        *dst++ = *src & 0xFE;
        bytes++;
        break;
    case 6:
        *dst++ = *src & 0xFC;
        bytes++;
        break;
    case 5:
        *dst++ = *src & 0xF8;
        bytes++;
        break;
    case 4:
        *dst++ = *src & 0xF0;
        bytes++;
        break;
    case 3:
        *dst++ = *src & 0xE0;
        bytes++;
        break;
    case 2:
        *dst++ = *src & 0xC0;
        bytes++;
        break;
    case 1:
        *dst++ = *src & 0x80;
        bytes++;
        break;
    }
    for (; bytes < 16; bytes++) {
        *dst++ = 0;
    }
}

s32 NetCompareBitsBackward(u8 *arg0, u8 *arg1, s16 arg2) {
    s16 n;
    s16 rem;
    s32 a;
    s32 b;
    if (arg2 <= 0) {
        return 0;
    }
    rem = arg2 % 8;
    n = arg2 / 8;
    while (n > 0) {
        if (*arg0 != *arg1) {
            return *arg0 - *arg1;
        }
        arg0--;
        arg1--;
        n--;
    }
    switch (rem) {
    case 1:
        a = *arg0 & 1;
        b = *arg1 & 1;
        if (a != b) {
            return a - b;
        }
        return 0;
    case 2:
        a = *arg0 & 3;
        b = *arg1 & 3;
        if (a != b) {
            return a - b;
        }
        return 0;
    case 3:
        a = *arg0 & 7;
        b = *arg1 & 7;
        if (a != b) {
            return a - b;
        }
        return 0;
    case 4:
        a = *arg0 & 0xF;
        b = *arg1 & 0xF;
        if (a != b) {
            return a - b;
        }
        return 0;
    case 5:
        a = *arg0 & 0x1F;
        b = *arg1 & 0x1F;
        if (a != b) {
            return a - b;
        }
        return 0;
    case 6:
        a = *arg0 & 0x3F;
        b = *arg1 & 0x3F;
        if (a != b) {
            return a - b;
        }
        return 0;
    case 7:
        a = *arg0 & 0x7F;
        b = *arg1 & 0x7F;
        if (a != b) {
            return a - b;
        }
        return 0;
    }
    return 0;
}

s32 NetCompareBitPrefix(u8 *a, u8 *b, s16 bits) {
    s16 n;
    s16 rem;
    if (bits <= 0) {
        return 0;
    }
    rem = bits % 8;
    n = bits / 8;
    for (; n > 0; n--) {
        if (*a != *b) {
            return *a - *b;
        }
        a++;
        b++;
    }
    switch (rem) {
    case 1:
        if ((*a & 0x80) != (*b & 0x80)) return (*a & 0x80) - (*b & 0x80);
        return 0;
    case 2:
        if ((*a & 0xC0) != (*b & 0xC0)) return (*a & 0xC0) - (*b & 0xC0);
        return 0;
    case 3:
        if ((*a & 0xE0) != (*b & 0xE0)) return (*a & 0xE0) - (*b & 0xE0);
        return 0;
    case 4:
        if ((*a & 0xF0) != (*b & 0xF0)) return (*a & 0xF0) - (*b & 0xF0);
        return 0;
    case 5:
        if ((*a & 0xF8) != (*b & 0xF8)) return (*a & 0xF8) - (*b & 0xF8);
        return 0;
    case 6:
        if ((*a & 0xFC) != (*b & 0xFC)) return (*a & 0xFC) - (*b & 0xFC);
        return 0;
    case 7:
        if ((*a & 0xFE) != (*b & 0xFE)) return (*a & 0xFE) - (*b & 0xFE);
        return 0;
    case 0:
    default:
        return 0;
    }
}

static inline s32 reset_loopback_entry(s16 id) {
    TLobby::clear_table_entry_locked(id);
    G_.a = -1;
    TLobby__sub_803F8B78(&G_);
    G_.c = 0;
    return 0;
}

s32 TLobby__sub_8041509C(void) {
    s32 status = reset_loopback_entry(G_.a);
    return status;
}

void TLobby__sub_804150EC(void) {
    TLobby__sub_8041510C();
}

s16 TLobby__sub_8041510C(void) {
    G_80415230 *g = (G_80415230 *)&network_loopback_state;
    Fn_8040881C fns[11];
    s16 r;
    s16 i;
    s16 *used;

    fns[0] = (Fn_8040881C)TLobby::fill_reply_buffer;
    fns[1] = (Fn_8040881C)TLobby::alloc_conn_slot;
    fns[2] = (Fn_8040881C)TLobby::clear_conn_slot;
    fns[3] = (Fn_8040881C)TLobby::get_slot_offset_or_default;
    fns[4] = (Fn_8040881C)TLobby__sub_80415508;
    fns[5] = (Fn_8040881C)TLobby__sub_804154E4;
    fns[6] = (Fn_8040881C)TLobby__sub_804154C0;
    fns[7] = (Fn_8040881C)TLobby__sub_8041549C;
    fns[8] = (Fn_8040881C)TLobby__sub_80415410;
    fns[9] = (Fn_8040881C)TLobby__sub_80415320;
    fns[10] = (Fn_8040881C)TLobby__sub_80415230;
    r = TLobby__sub_80409A3C((u8 *)fns, 1);
    if (r < 0) {
        return r;
    }
    NetInitReceiveDescriptor((NetConfig_803F8B7C *)&network_loopback_state);
    g->handler = r;
    g->protos[0].used = 0;
    g->protos[0].type = 0;
    g->protos[1].used = 0;
    g->protos[1].type = 0;
    used = g->slot_used;
    for (i = 0; i < g->slot_count; i++, used++) {
        *used = 0;
    }
    return r;
}

s32 TLobby__sub_80415230(s16 idx, s16 mode, u8 *addr, NetPacket *pkt) {
    G_80415230 *g = (G_80415230 *)&network_loopback_state;
    u8 *slot;
    s16 len;
    s16 i;
    s16 *used;

    if (idx != 0 && idx != 1) {
        return -0x110;
    }
    len = TLobby__sub_804098B4(pkt);
    if (g->slot_size < len) {
        return -0x110;
    }
    used = g->slot_used;
    slot = g->slots;
    for (i = 0; i < g->slot_count; i++, used++) {
        if (*used == 0) {
            *used = 1;
            TLobby__sub_80409908(slot, pkt);
            TLobby__sub_80409818((s32)slot, len, g->handler, idx, g->protos[idx].type);
            return 0;
        }
        slot += g->slot_size;
    }
    return -0x110;
}

s32 TLobby__sub_80415320(s16 idx, u8 *addr, NetPacket *pkt) {
    G_80415230 *g = (G_80415230 *)&network_loopback_state;
    u8 *slot;
    s16 len;
    s16 i;
    s16 *used;

    if (idx != 0 && idx != 1) {
        return -0x110;
    }
    len = TLobby__sub_804098B4(pkt);
    if (g->slot_size < len) {
        return -0x110;
    }
    used = g->slot_used;
    slot = g->slots;
    for (i = 0; i < g->slot_count; i++, used++) {
        if (*used == 0) {
            *used = 1;
            TLobby__sub_80409908(slot, pkt);
            TLobby__sub_80409818((s32)slot, len, g->handler, idx, g->protos[idx].type);
            return 0;
        }
        slot += g->slot_size;
    }
    return -0x110;
}

s32 TLobby__sub_80415410(s16 idx, u8 *pkt) {
    G_80415230 *g = (G_80415230 *)&network_loopback_state;
    s16 i;
    s16 *used;
    u8 *slot;
    s16 size;

    if (idx != 0 && idx != 1) {
        return -0x110;
    }
    used = g->slot_used;
    slot = g->slots;
    size = g->slot_size;
    for (i = 0; i < g->slot_count; i++, used++) {
        if (*used != 0 && slot <= pkt && pkt < slot + size) {
            *used = 0;
            return 0;
        }
        slot += size;
    }
    return -0x110;
}

s32 TLobby__sub_8041549C(s16 arg0) {
    if ((arg0 != 0) && (arg0 != 1)) {
        return -0x110;
    }
    return 0;
}

s32 TLobby__sub_804154C0(s16 arg0) {
    if ((arg0 != 0) && (arg0 != 1)) {
        return -0x110;
    }
    return 0;
}

s32 TLobby__sub_804154E4(s16 arg0) {
    if ((arg0 != 0) && (arg0 != 1)) {
        return -0x110;
    }
    return 0;
}

s32 TLobby__sub_80415508(s16 arg0) {
    if ((arg0 != 0) && (arg0 != 1)) {
        return -0x110;
    }
    return 0;
}

s16 TLobby::get_slot_offset_or_default(s16 arg0) {
    if ((arg0 != 0) && (arg0 != 1)) {
        return -0x110;
    }
    return *(s16 *)((s8 *)(&network_loopback_state.value) + 0xA);
}

s32 TLobby::clear_conn_slot(s16 i) {
    if (i != 0 && i != 1) { return -0x110; }
    G_80415558 *g = (G_80415558 *)&network_loopback_state;
    g->e[i].a = 0;
    g->e[i].b = 0;
    return 0;
}

s16 TLobby::alloc_conn_slot(s16 h, s16 v) {
    s16 r;
    G_8041559C *g = (G_8041559C *)&network_loopback_state;
    if (h != g->h) { return -0x110; }
    if (g->e[0].a == 0) {
        r = 0;
    } else if (g->e[1].a == 0) {
        r = 1;
    } else {
        return -0x110;
    }
    g->e[r].a = 1;
    g->e[r].b = v;
    return r;
}

s32 TLobby::fill_reply_buffer(s16 h, u8 *p) {
    if (h != *(s16 *)&network_loopback_state) { return -0x110; }
    p[0] = 0;
    *++p = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[6] = 1;
    return 0;
}

s32 TLobby::reset_net_value() {
    TLobby__sub_803F89D8(&network_buffer_pool_state.count);
    network_buffer_pool_state.count = 0;
    return 0;
}

s16 TLobby__sub_80415690(void) {
    u8 *buf;
    s16 i;
    Ent_80415690 *e;
    s16 j;

    init_buffer_desc_a__6TLobbyFv(&network_buffer_pool_state);
    buf = network_buffer_pool_state.data;
    e = network_buffer_pool_state.ents;
    for (i = 0; i < network_buffer_pool_state.count; i++, e++) {
        e->buf = buf;
        buf += network_buffer_pool_state.size & 0xFFFF;
        e->free_segs = 8;
        e->free_bytes = network_buffer_pool_state.size;
        e->segs[0].owner = -1;
        e->segs[0].offset = 0;
        e->segs[0].len = network_buffer_pool_state.size;
        for (j = 1; j < 8; j++) {
            e->segs[j].owner = 0;
            e->segs[j].offset = network_buffer_pool_state.size;
            e->segs[j].len = 0;
        }
    }
    return 0;
}

#pragma opt_common_subs reset
s16 TLobby__sub_8041579C(void *self)
{
  s16 *cursor;
  s32 pos;
  s16 f;
  u8 *a;
  s16 id1;
  u8 *b;
  s16 id2;
  s16 m;
  u8 *rec;
  int new_var2;
  u32 word;
  if (((NetBufferRef *)self)->kind == 4)
  {
    TLobby__sub_803F8D84(((NetBufferRef *)self)->value);
    return 0;
  }
  word = ((NetBufferRef *)self)->value;
  id1 = (s16) (word >> 24);
  id2 = (s16) ((word >> 16) & 0xff);
  if ((id1 < 0) || (id2 < 0))
  {
    return -1;
  }
  if (id1 > network_buffer_pool_state.count)
  {
    return -1;
  }
  if (id2 > 8)
  {
    return -1;
  }
  rec = (u8 *)network_buffer_pool_state.ents;
  rec += id1 * (s32)sizeof(Ent_80415690);
  pos = id2 * (s32)sizeof(Seg_80415690);
  cursor = (s16 *)(rec + pos);
  if ((*((s16 *) (cursor += offsetof(Ent_80415690, segs) / sizeof(s16)))) == (-1))
  {
    return -1;
  }
  ((Seg_80415690 *)cursor)->owner = -1;
  ((Ent_80415690 *)rec)->free_segs += 1;
  ((Ent_80415690 *)rec)->free_bytes += *((u16 *) ((u8 *)(self = (void *)(rec + pos)) + offsetof(Ent_80415690, segs[0].len)));
  if ((id2 == 7) || ((*((s16 *) ((u8 *)self + offsetof(Ent_80415690, segs[1].owner)))) != (-1)))
  {
    pos = (u16) id2;
  }
  else
  {
    pos = id2 + 1;
  }
  pos = (s16) pos;
  new_var2 = pos - 1;
  m = new_var2;
  a = rec + (m * (s32)sizeof(Seg_80415690));
  b = rec + (pos * (s32)sizeof(Seg_80415690));
  while ((m >= 0) && ((f = ((Ent_80415690 *)a)->segs[0].owner) <= 0))
  {
    if (f == 0)
    {
      ((Ent_80415690 *)a)->segs[0].owner = -1;
      ((Ent_80415690 *)b)->segs[0].owner = 0;
      ((Ent_80415690 *)a)->segs[0].offset = ((Ent_80415690 *)b)->segs[0].offset;
      ((Ent_80415690 *)a)->segs[0].len = ((Ent_80415690 *)b)->segs[0].len;
      ((Ent_80415690 *)b)->segs[0].offset = ((Ent_80415690 *)b)->segs[0].offset + ((Ent_80415690 *)a)->segs[0].len;
      ((Ent_80415690 *)b)->segs[0].len = 0;
    }
    else
      if (f == (-1))
    {
      ((Ent_80415690 *)b)->segs[0].owner = 0;
      ((Ent_80415690 *)a)->segs[0].len = ((Ent_80415690 *)a)->segs[0].len + ((Ent_80415690 *)b)->segs[0].len;
      ((Ent_80415690 *)b)->segs[0].len = 0;
      ((Ent_80415690 *)b)->segs[0].offset = ((Ent_80415690 *)a)->segs[0].offset + ((Ent_80415690 *)a)->segs[0].len;
    }
    else
    {
      break;
    }
    b = b - (s32)sizeof(Seg_80415690);
    a = a - (s32)sizeof(Seg_80415690);
    m--;
  }

  return 0;
}

#pragma opt_common_subs on
s16 TLobby__sub_80415954(NetBufferRef *ref, s32 size, s16 owner) {
    Pool_80415690 *pool;
    Ent_80415690 *e;
    u32 p;
    s16 i;
    s16 j;

    if (owner == 1) {
        p = TLobby::alloc_buffer_slot(size);
        if (p == 0) {
            return -1;
        }
        ref->kind = 4;
        ref->value = p;
        return 0;
    }
    if (size < 0x400) {
        size = 0x400;
    }
    pool = &network_buffer_pool_state;
    e = pool->ents;
    for (i = 0; i < pool->count; i++, e++) {
        if (e->free_segs == 0 || size > e->free_bytes) {
            continue;
        }
        for (j = 0; j < 8; j++) {
            if (e->segs[j].owner != 0 && e->segs[j].owner == -1 && e->segs[j].len >= (u16)size) {
                ref->value = (i << 24) + (j << 16);
                ref->kind = 2;
                e->segs[j].owner = owner;
                if (j + 1 < 8 && e->segs[j].len - (u16)size != 0 && e->segs[j + 1].owner == 0) {
                    e->segs[j + 1].offset = e->segs[j].offset + size;
                    e->segs[j + 1].len = e->segs[j].len - size;
                    e->segs[j + 1].owner = -1;
                    e->segs[j].len = size;
                }
                e->free_segs--;
                e->free_bytes -= e->segs[j].len;
                return 0;
            }
        }
    }
    return -1;
}

#pragma opt_common_subs reset
void NetIPv6ShutdownNeighborDiscovery(void) {
    G_80415B38 *g = &ipv6_neighbor_discovery_state;
    NetUnregisterTimer(NetIPv6TickNeighborDiscovery);
    TLobby__sub_803F88E0(g);
    g->nb = 0;
    g->nc = 0;
}

s32 NetIPv6InitNeighborDiscovery(void) {
    s16 n;
    s32 off;
    A_80415B38 *a;
    C_80415B38 *c;
    B_80415B38 *b;
    Ent_80418670 *r;
    G_80415B38 *g;
    s16 stride;
    Arg2_80415B38 a2;
    Arg2_80415B38 a1;

    g = &ipv6_neighbor_discovery_state;
    NetMemset(g, 0, sizeof(G_80415B38));
    NetInitBufferDescriptorB((RecoveredFields_803F88E4_arg0 *)g);
    NetIPv6ApplyNeighborDiscoveryDefaults(g);
    n = g->na;
    a = g->a;
    off = g->base;
    stride = g->stride;
    for (; n > 0; n--) {
        a->c0 = 0x50;
        a->c1 = 0x45;
        a->c2 = 0x4E;
        a->off = off;
        off += stride;
        a->c3 = 0;
        a++;
    }
    n = g->nc;
    c = g->c;
    for (; n > 0; n--) {
        c->c0 = 0x44;
        c->c1 = 0x4C;
        c->c2 = 0x45;
        c->c3 = 0;
        c->f6 = 0;
        c++;
    }
    n = g->nb;
    b = g->b;
    for (; n > 0; n--) {
        b->c0 = 0x4E;
        b->c1 = 0x43;
        b->c2 = 0x45;
        b->flags = 0;
        b->link = NULL;
        if (b->link != NULL) {
            b->link->c3 = 0;
            b->link = NULL;
        }
        if (b->flags & 0x80) {
            r = NetIPv6SelectDefaultRouter(b->addr);
            if (r == NULL) {
                a1.addr = b->addr;
                TLobby__sub_80411604(b->id, 6, &a1);
            } else {
                a2.val = r->f14;
                a2.addr = b->addr;
                TLobby__sub_80411604(b->id, 7, &a2);
            }
        }
        b->c3 = 0;
        b->f26 = 0;
        b++;
    }
    NetRegisterTimer(1000, (s16)(1), (NetTimerCallback)(NetIPv6TickNeighborDiscovery));
    return 0;
}

void NetIPv6TickNeighborDiscovery(void) {
    NetIPv6TickNeighborCache();
    TLobby__sub_8041615C();
}

s16 TLobby__sub_80415D0C(NetPacket *pkt, u8 *nexthop, NetIPv6SendParameters *params, s16 idx) {
    s16 NetIPv6IsMulticast(u8 *addr);
    E_804179A4 *NetIPv6FindOrSelectNeighborCacheEntry(void *, int, int);
    Q_804179A4 *NetIPv6SelectPendingPacketSlot(void);

    G_80415B38 *g = &ipv6_neighbor_discovery_state;
    E_804179A4 *e;
    Ent_80418670 *r;
    Arg2_80415B38 a2;
    Arg2_80415B38 a1;
    NetBufferRef ref;
    Arg2_80415B38 b2;
    Arg2_80415B38 b1;

    if (NetIPv6IsMulticast(nexthop)) {
        return -2;
    }
    e = NetIPv6FindOrSelectNeighborCacheEntry(nexthop, 0, 0);
    if (e == NULL) {
        return -0x10E;
    }
    switch (e->f6) {
    case 2:
        switch (e->f4) {
        case 0:
            break;
        case 2:
            e->f8 = idx;
            e->f4 = 3;
            e->fa = g->f2C;
        case 1:
        case 3:
        case 4:
            return TLobby__sub_80410BA8(pkt, params, idx, e->f28);
        }
        break;
    case 0:
    case 1:
    case 3:
        if (e->f10 != NULL) {
            e->f10->f3 = 0;
            e->f10 = NULL;
        }
        if (e->fc & 0x80) {
            r = NetIPv6SelectDefaultRouter(e->f16);
            if (r == NULL) {
                a1.addr = e->f16;
                TLobby__sub_80411604(e->f8, 6, &a1);
            } else {
                a2.val = r->f14;
                a2.addr = e->f16;
                TLobby__sub_80411604(e->f8, 7, &a2);
            }
        }
        e->f3 = 0;
        e->f26 = 0;
        e->f3 = 1;
        e->f8 = idx;
        NetMemcpy(e->f16, nexthop, 0x10);
        e->f4 = 0;
        break;
    default:
        return -0x10E;
    }
    {
        s16 ret;
        u8 *src;
        u32 n;
        Q_804179A4 *q;
        NetPacketFragment *frag;
        if (e->f10 == NULL) {
            e->f10 = NetIPv6SelectPendingPacketSlot();
        }
        q = e->f10;
        n = pkt->fragment_count;
        src = q->f34;
        q->f30 = 0;
        frag = pkt->fragments + n - 1;
        while (n != 0) {
            s16 l = frag->length;
            q->f30 += l;
            if (q->f30 > g->stride) {
                ret = -0x10E;
                goto done;
            }
            NetBufferRefInitKind1(&ref, (s32)src);
            TLobby__sub_80406FD8(&ref, &pkt->fragments[n - 1].buffer, l);
            src += l;
            frag--;
            n--;
        }
        ret = 0;
done:
        if (ret < 0) {
            if (e->f10 != NULL) {
                e->f10->f3 = 0;
                e->f10 = NULL;
            }
            if (e->fc & 0x80) {
                r = NetIPv6SelectDefaultRouter(e->f16);
                if (r == NULL) {
                    b1.addr = e->f16;
                    TLobby__sub_80411604(e->f8, 6, &b1);
                } else {
                    b2.val = r->f14;
                    b2.addr = e->f16;
                    TLobby__sub_80411604(e->f8, 7, &b2);
                }
            }
            e->f3 = 0;
            e->f26 = 0;
            return ret;
        }
        NetMemcpy(e->f10->f8, params, sizeof(NetIPv6SendParameters));
        e->fa = g->f2A;
        e->f10->f4 = e->fa;
        e->f14 = 0;
        return NetIPv6SendMulticastNeighborProbe((u8 *)e);
    }
}

s16 NetIPv6SendUnspecifiedSourceNeighborSolicitation(u8 *target, s16 iface) {
    s16 TLobby__sub_80413D78();
    typedef char sp10_offset[(offsetof(Stack_80416008, sp10) == 0x0) ? 1 : -1];
    typedef char sp20_offset[(offsetof(Stack_80416008, sp20) == 0x10) ? 1 : -1];
    Stack_80416008 stack;
    s16 result;
    NetPacket *free_entry;
    if (TLobby__sub_80413D78() != 0) {
        return -0x10E;
    }
    free_entry = TLobby::alloc_free_entry();
    if (free_entry == NULL) {
        return -0x10E;
    }
    free_entry->fragment_count = 0;
    free_entry->total_bytes = 0;
    NetMemset((void *) (&stack.sp10), 0, 0x10);
    NetIPv6MakeSolicitedNodeMulticastAddress((u8 *)((void *) (&stack.sp20)), target);
    result = NetIPv6EmitNeighborSolicitation(free_entry, target, (NetIPv6SendParameters *)(&stack.sp10), iface, NULL);
    NetReleasePacket(free_entry);
    return result;
}

s16 NetIPv6SendRouterSolicitation(s16 arg0) {
    s16 TLobby__sub_804145D4(u8 *, s16);
    u8 address[0x1C];
    u8 addr[0x10];
    s16 temp_r31;
    NetPacket *free_entry;

    free_entry = TLobby::alloc_free_entry();
    if (free_entry == NULL) {
        return -0x10E;
    }
    free_entry->fragment_count = 0;
    free_entry->total_bytes = 0;
    init_ipv6_all_routers_multicast_address((u8 *)(address), (s8)(2));
    if (TLobby__sub_804145D4(addr, arg0) < 0) {
        NetMemset(addr, 0, 0x10);
    }
    temp_r31 = NetIPv6EmitRouterSolicitation(free_entry, (NetIPv6SendParameters *)(addr), arg0);
    NetReleasePacket(free_entry);
    return temp_r31;
}

void TLobby__sub_8041615C(void) {
    G_8041615C *g = (G_8041615C *)&ipv6_neighbor_discovery_state;
    Nbr_8041615C *nb;
    s16 n;
    Rtr_8041615C *r;
    Rtr_8041615C *alive = NULL;
    Rtr_8041615C *expired = NULL;
    Arg2_80415B38 a6;
    Arg2_80415B38 a7;

    n = g->nrtr;
    r = g->rtrs;
    for (; n > 0; n--, r++) {
        if (r->state == 1) {
            if (r->lifetime > 1) {
                r->lifetime--;
                alive = r;
            } else {
                r->state = 0;
                expired = r;
                r->f6 = 0;
            }
        }
    }
    if (expired == NULL) {
        return;
    }
    nb = (Nbr_8041615C *)find_nbr_8041615C(g, expired->addr);
    if (nb != NULL) {
        nb->flags &= ~0x80;
    }
    if (alive != NULL) {
        a7.addr = expired->addr;
        a7.val = alive->addr;
        TLobby__sub_80411604(alive->id, 7, &a7);
    } else {
        a6.addr = expired->addr;
        TLobby__sub_80411604(expired->id, 6, &a6);
    }
}

void NetIPv6TickNeighborCache(void) {
    Arg_804162A4 a7;
    Arg_804162A4 a6;
    Arg_804162A4 a7b;
    Arg_804162A4 a6b;
    Glob_804162A4 *g = (Glob_804162A4 *)&ipv6_neighbor_discovery_state;
    s16 n;
    Ent_804162A4 *e;
    Ent_80418670 *r;

    n = g->count;
    e = g->ents;
    while (n > 0) {
        if (e->state == 1) {
            if (e->timer > 1) {
                e->timer--;
                if (e->sub != NULL) {
                    e->sub->count--;
                }
            } else {
                switch (e->phase) {
                case 0:
                    if (++e->tries < g->maxTries0) {
                        NetIPv6SendMulticastNeighborProbe((u8 *)e);
                        e->timer = g->delay;
                    } else {
                        if (e->sub != NULL) {
                            e->sub->state = 0;
                            e->sub = NULL;
                        }
                        if (e->flags & 0x80) {
                            r = NetIPv6SelectDefaultRouter(e->name);
                            if (r == NULL) {
                                a6.p = e->name;
                                TLobby__sub_80411604(e->id, 6, &a6);
                            } else {
                                a7.v = (s32)r->f14;
                                a7.p = e->name;
                                TLobby__sub_80411604(e->id, 7, &a7);
                            }
                        }
                        e->state = 0;
                        e->f26 = 0;
                    }
                    break;
                case 1:
                    e->phase = 2;
                    e->timer = g->delay1;
                    break;
                case 2:
                    e->timer = 0;
                    break;
                case 3:
                    NetIPv6SendUnicastNeighborProbe((u8 *)e);
                    e->phase = 4;
                    e->timer = g->delay;
                    e->tries = 0;
                    break;
                case 4:
                    if (++e->tries < g->maxTries1) {
                        NetIPv6SendUnicastNeighborProbe((u8 *)e);
                        e->timer = g->delay;
                    } else {
                        if (e->sub != NULL) {
                            e->sub->state = 0;
                            e->sub = NULL;
                        }
                        if (e->flags & 0x80) {
                            r = NetIPv6SelectDefaultRouter(e->name);
                            if (r == NULL) {
                                a6b.p = e->name;
                                TLobby__sub_80411604(e->id, 6, &a6b);
                            } else {
                                a7b.v = (s32)r->f14;
                                a7b.p = e->name;
                                TLobby__sub_80411604(e->id, 7, &a7b);
                            }
                        }
                        e->state = 0;
                        e->f26 = 0;
                    }
                    break;
                }
            }
        }
        n--;
        e++;
    }
}

#pragma opt_propagation off
s16 NetIPv6HandleRedirect(NetPacket *pkt, u8 *src, void *arg2, s16 iface) {
    NetBufferRef ref;
    Redirect_80416508 msg;
    u8 opts[0x38];
    s16 optlen;
    Arg_80416508 arg;
    u8 *e;
    u8 *dest;
    u8 *target;
    u32 len;
    NetPacketFragment *frag;
    s16 r;
    s16 NetIPv6IsLinkLocal(u8 *arg0);
    s16 NetIPv6IsMulticast(u8 *arg0);
    s16 NetIPv6ParseRedirectOptions(u8 *arg0, s32 n, u8 *arg2, s32 arg3, s16 *arg4, s16 arg5);


    frag = &pkt->fragments[1];
    optlen = sizeof(opts);
    len = pkt->fragments[1].length;
    if (len < sizeof(Redirect_80416508)) {
        return -1;
    }
    if (NetIPv6IsLinkLocal(src) == 0) {
        return -1;
    }
    NetBufferRefInitKind1(&ref, (s32)&msg);
    TLobby__sub_80406FD8(&ref, &frag->buffer, sizeof(Redirect_80416508));
    dest = msg.dest.bytes;
    if (NetIPv6IsMulticast(dest) != 0) {
        return -1;
    }
    target = msg.target.bytes;
    if (NetIPv6IsLinkLocal(target) == 0 && NetMemcmp(target, dest, 0x10) != 0) {
        return -1;
    }
    e = TLobby__sub_80413264(dest, (s32)src);
    if (e == NULL || NetMemcmp(e + 0x18, src, 0x10) != 0) {
        return -1;
    }
    len -= sizeof(Redirect_80416508);
    if (len >= 8) {
        TLobby__sub_80406EB8(&frag->buffer, sizeof(Redirect_80416508));
        r = NetIPv6ParseRedirectOptions((u8 *)frag, len, (u8 *)&msg, (s32)opts, &optlen, iface);
        if (r < 0) {
            return r;
        }
    }
    arg.dest = dest;
    arg.id = *(s16 *)(e + 0x28);
    arg.router = e + 0x18;
    arg.target = target;
    TLobby__sub_80411604(iface, 10, &arg);
    return 0;
}

#pragma opt_propagation reset
s32 NetIPv6ParseRedirectOptions(u8 *arg0, s32 n, u8 *arg2, s32 arg3, s16 *arg4, s16 arg5) {
    u8 sp20[8];
    u8 *h;
    s16 len;
    Ent_80416678 *e;
    void TLobby__sub_80406EB8(void *, s32);
    u8 *TLobby__sub_80406F0C(void *);
    void TLobby__sub_80406FD8(void *, void *, s32);
    Ent_80416678 *TLobby__sub_804182DC(void *, void *, s32, s16);

    while (n >= 8) {
        h = TLobby__sub_80406F0C(arg0 + 4);
        if (h[1] == 0) {
            return -0x10E;
        }
        len = h[1] * 8;
        n -= len;
        if (n < 0) {
            return -0x10E;
        }
        switch (h[0]) {
        case 1:
        case 3:
        case 5:
        default:
            TLobby__sub_80406EB8(arg0 + 4, len);
            break;
        case 4:
            *arg4 = (*arg4 < len) ? *arg4 : len;
            NetBufferRefInitKind1((NetBufferRef *)sp20, arg3);
            TLobby__sub_80406FD8(sp20, arg0 + 4, *arg4);
            TLobby__sub_80406EB8(arg0 + 4, len);
            break;
        case 2: {
            u8 *p = h + 2;
            s32 l = len - 2;
            e = TLobby__sub_804182DC(arg2 + 8, p, l, arg5);
            if (e != NULL && NetMemcmp(arg2 + 8, arg2 + 0x18, 0x10) != 0) {
                e->fC |= 0x80;
            }
            TLobby__sub_80406EB8(arg0 + 4, len);
            break;
        }
        }
    }
    return 0;
}

s16 NetIPv6HandleNeighborAdvertisement(NetPacket *arg0, u8 *arg1, u8 *arg2, s16 arg3) {
    // These scoped short-result declarations preserve the native C caller ABI.
    s16 NetIPv6FindTargetLinkLayerAddressOption(u8 *, s32, u8 **, s16 *);
    s16 NetIPv6ApplyNeighborAdvertisement(Msg_80416994 *, u8 *, s16, s32, s32, s16);
    s16 NetIPv6IsMulticast(u8 *);
    NetBufferRef sp30;
    Msg_80416994 sp18;
    u8 *lladdr;
    s16 lladlen;
    NetPacketFragment *hdr;
    u32 len;
    s16 r;
    lladdr = 0;
    lladlen = 0;

    hdr = &arg0->fragments[1];
    len = arg0->fragments[1].length;
    if (len < 0x18) {
        return -1;
    }
    NetBufferRefInitKind1((NetBufferRef *)&sp30, (s32)&sp18);
    TLobby__sub_80406FD8(&sp30, &hdr->buffer, 0x18);
    if (NetIPv6IsMulticast(sp18.name)) {
        return -1;
    }
    len -= 0x18;
    if (len >= 8) {
        TLobby__sub_80406EB8(&hdr->buffer, 24);
        r = NetIPv6FindTargetLinkLayerAddressOption((u8 *)hdr, len, &lladdr, &lladlen);
        if (r < 0) {
            return r;
        }
    }
    if (NetIPv6IsMulticast(arg2)) {
        if ((sp18.flags & 0x40) || lladlen == 0) {
            return -1;
        }
    }
    return NetIPv6ApplyNeighborAdvertisement(&sp18, lladdr, lladlen, (s32)arg1, (s32)arg2, arg3);
}

s32 NetIPv6FindTargetLinkLayerAddressOption(u8 *o, s32 len, u8 **out, s16 *outlen) {
    u8 *p;
    s16 sz;

    while (len >= 8) {
        p = TLobby__sub_80406F0C(o + 4);
        if (p[1] == 0) {
            return -0x10E;
        }
        sz = p[1] << 3;
        len -= sz;
        if (len < 0) {
            return -0x10E;
        }
        if ((s32)p[0] != 2) {
            TLobby__sub_80406EB8((NetBufferRef *)(o + 4), sz);
        } else {
            *out = p + 2;
            *outlen = sz - 2;
            TLobby__sub_80406EB8((NetBufferRef *)(o + 4), sz);
        }
    }
    return 0;
}

s16 NetIPv6ApplyNeighborAdvertisement(Msg_80416994 *msg, u8 *name, s16 len, s32 arg3, s32 arg4, s16 id) {

    s16 TLobby__sub_80413C0C(void *, s16);
    s16 TLobby__sub_80413AA0(void *, s16);
    Arg_80416994 a;
    Arg_80416994 b;
    Glob_80416994 *g = (Glob_80416994 *)&ipv6_neighbor_discovery_state;
    Ent_80416994 *e;

    if (TLobby__sub_80413C0C(msg->name, id) != 0) {
        a.p = msg->name;
        TLobby__sub_80411604(id, 1, &a);
        return 0;
    }
    if (TLobby__sub_80413AA0(msg->name, id) != 0) {
        return 0;
    }
    e = FindEnt_80416994(g, msg->name);
    if (e == 0) {
        return 0;
    }
    if ((e->flags ^ msg->flags) & 0x80) {
        if (len == 0 || name == 0 || (e->len == len && NetMemcmp(e->data, name, len) == 0) || (msg->flags & 0x20)) {
            if (msg->flags & 0x80) {
                e->flags |= 0x80;
                a.p = msg->name;
                TLobby__sub_80411604(id, 8, &a);
            } else {
                Peer_80416994 *hit;
                e->flags |= ~0x80;
                hit = ScanPeers_80416994(g, msg->name);
                if (hit == 0) {
                    a.p = msg->name;
                    TLobby__sub_80411604(id, 9, &a);
                } else {
                    b.v = (s32)hit->name;
                    b.p = msg->name;
                    TLobby__sub_80411604(id, 7, &b);
                }
            }
        }
    }
    switch (e->phase) {
    case 0:
        if (len != 0 && name != 0) {
            e->len = ((u32)len > 0x20) ? 0x20 : len;
            NetMemcpy(e->data, name, e->len);
            if (msg->flags & 0x40) {
                e->phase = 1;
                e->timer = g->delay1;
            } else {
                e->phase = 2;
                e->timer = g->delay2;
            }
            e->flags = msg->flags;
            if (e->sub != 0) {
                Pkt_80416994 *pkt = (Pkt_80416994 *)TLobby::alloc_free_entry();
                s16 ret;
                if (pkt == 0) {
                    ret = -0x10E;
                } else {
                    pkt->n = 0;
                    pkt->port = e->sub->port;
                    pkt->items[pkt->n].port = e->sub->port;
                    NetBufferRefInitKind1((NetBufferRef *)pkt->items[pkt->n].val, e->sub->val);
                    pkt->n++;
                    ret = TLobby__sub_80410BA8((NetPacket *)pkt, (NetIPv6SendParameters *)e->sub->addr, e->f8, e->data);
                    NetReleasePacket((NetPacket *)pkt);
                }
                e->sub->state = 0;
                e->sub = 0;
                return ret;
            }
        }
        break;
    case 1:
        if (len != 0 && name != 0 && (e->len != len || NetMemcmp(e->data, name, len) != 0)) {
            if (msg->flags & 0x20) {
                e->len = ((u32)len > 0x20) ? 0x20 : len;
                NetMemcpy(e->data, name, e->len);
                e->flags = msg->flags;
                if (msg->flags & 0x40) {
                    e->phase = 1;
                    e->timer = g->delay1;
                    break;
                }
            }
            e->phase = 2;
            e->timer = g->delay2;
        }
        break;
    case 2:
    case 3:
    case 4:
        if (len != 0 && name != 0 && (e->len != len || NetMemcmp(e->data, name, len) != 0)) {
            if (msg->flags & 0x20) {
                e->len = ((u32)len > 0x20) ? 0x20 : len;
                NetMemcpy(e->data, name, e->len);
                if (msg->flags & 0x40) {
                    e->phase = 1;
                    e->timer = g->delay1;
                } else {
                    e->phase = 2;
                    e->timer = g->delay2;
                }
                e->flags = msg->flags;
            }
        } else if (msg->flags & 0x40) {
            e->phase = 1;
            e->timer = g->delay1;
            e->flags = msg->flags;
        }
        break;
    }
    return 0;
}

s16 NetIPv6HandleNeighborSolicitation(u8 *arg0, void *arg1, void *arg2, void *arg3) {
    s16 TLobby__sub_80413F0C(void *, void *);
    void TLobby__sub_80406EB8(void *, int);
    s16 TLobby__sub_80417028(void *, void *, void *, void *);
    s16 NetIPv6IsMulticast(u8 *arg0);
    s16 NetIPv6IsUnspecified(u8 *arg0);
    NetBufferRef sp30;
    IPv6NeighborSolicitation sp18;
    u8 *hdr;
    u32 len;
    s16 r;
    hdr = arg0 + 0x18;
    len = *(s16 *)(arg0 + 0x18);
    if (len < 0x18) {
        return -1;
    }
    if ((s16)NetIPv6IsUnspecified((u8 *)arg1) && TLobby__sub_80413F0C(arg2, arg3) == 0) {
        return -1;
    }
    NetBufferRefInitKind1((NetBufferRef *)((u8 *)&sp30), (s32)&sp18);
    TLobby__sub_80406FD8(&sp30, hdr + 4, 0x18);
    if ((s16)NetIPv6IsMulticast(sp18.target.bytes)) {
        return -1;
    }
    len -= 0x18;
    if (len >= 8) {
        TLobby__sub_80406EB8(hdr + 4, 24);
        r = TLobby__sub_80416F58(hdr, len, arg1, arg3);
        if (r < 0) {
            return r;
        }
    }
    return TLobby__sub_80417028(&sp18, arg1, arg2, arg3);
}

s16 TLobby__sub_80416F58(u8 *msg, s32 len, void *addr, void *ifindex) {
    void TLobby__sub_80406EB8(void *, int);
    u8 *TLobby__sub_80406F0C(void *);
    s16 NetIPv6IsUnspecified(u8 *arg0);
    Ent_80416678 *TLobby__sub_804182DC(void *, void *, s16, s32);
    u8 *opt;
    s16 size;

    while (len >= 8) {
        opt = TLobby__sub_80406F0C(msg + 4);
        if (opt[1] == 0) {
            return -0x10E;
        }
        size = opt[1] << 3;
        len -= size;
        if (len < 0) {
            return -0x10E;
        }
        if ((s32)opt[0] != 1) {
            TLobby__sub_80406EB8(msg + 4, size);
        } else {
            if (NetIPv6IsUnspecified((u8 *)addr)) {
                return -0x10E;
            }
            {
                u8 *p = opt + 2;
                s16 l = size - 2;
                TLobby__sub_804182DC(addr, p, l, (s32)ifindex);
            }
            TLobby__sub_80406EB8(msg + 4, size);
        }
    }
    return 0;
}

s16 TLobby__sub_80417028(IPv6NeighborSolicitation *ns, u8 *src, u8 *dst, s16 iface) {
    NetSourceLinkLayerOption opt;
    NetIPv6SendParameters params;
    Arg_80416994 a;
    NetPacket *pkt;
    u8 flags;
    s16 len;
    s16 r;
    s16 NetIPv6IsUnspecified(u8 *arg0);
    s16 TLobby__sub_80413C0C(u8 *, s16);
    s16 TLobby__sub_80413AA0(u8 *, s16);

    s16 NetIPv6IsMulticast(u8 *arg0);

    flags = 0;
    if (TLobby__sub_80413C0C(ns->target.bytes, iface) != 0) {
        a.p = ns->target.bytes;
        TLobby__sub_80411604(iface, 1, &a);
        return 0;
    }
    if (TLobby__sub_80413AA0(ns->target.bytes, iface) == 0) {
        return 0;
    }
    NetMemcpy(params.source.bytes, ns->target.bytes, 0x10);
    pkt = TLobby::alloc_free_entry();
    if (pkt == NULL) {
        return -0x10E;
    }
    pkt->fragment_count = 0;
    pkt->total_bytes = 0;
    if (NetIPv6IsUnspecified(src) != 0) {
        init_ipv6_all_nodes_multicast_address(params.destination.bytes, 2);
    } else {
        NetMemcpy(params.destination.bytes, src, 0x10);
    }
    if (NetIPv6IsMulticast(dst) != 0) {
        len = NetIPv6GetInterfaceLinkLayerAddress((s32)opt.address.bytes, sizeof(opt.address), iface);
        if (len > 0) {
            len += 2;
            opt.type = 2;
            opt.length_units = len >> 3;
            pkt->total_bytes += len;
            pkt->fragments[pkt->fragment_count].length = len;
            NetBufferRefInitKind1(&pkt->fragments[pkt->fragment_count].buffer, (s32)&opt);
            flags |= 0x20;
            pkt->fragment_count++;
        }
    }
    r = NetIPv6SendNeighborAdvertisement((Pkt_804179A4 *)pkt, ns->target.bytes, flags, (Sock_804179A4 *)&params, iface);
    NetReleasePacket(pkt);
    return r;
}

s16 NetIPv6HandleRouterAdvertisement(u8 *arg0, u8 *arg1, s32 arg2, s16 arg3) {
    s16 TLobby__sub_80417494(void *, u8 *, s16);
    u8 sp28[8];
    u8 sp18[16];
    u32 n;
    u8 *p;
    s16 r;
    void TLobby__sub_80406EB8(void *, s32);
    s16 NetIPv6IsLinkLocal(u8 *arg0);

    p = arg0 + 0x18;
    n = *(s16 *)(arg0 + 0x18);
    if (n < 0x10U) {
        return -1;
    }
    r = NetIPv6IsLinkLocal(arg1);
    if (r == 0) {
        return -1;
    }
    NetBufferRefInitKind1((NetBufferRef *)sp28, (s32)sp18);
    TLobby__sub_80406FD8(sp28, p + 4, 0x10);
    n -= 0x10;
    if (n >= 8U) {
        TLobby__sub_80406EB8(p + 4, 0x10);
        r = TLobby__sub_80417294((NetPacketFragment *)p, n, arg1, arg3);
        if (r < 0) {
            return r;
        }
    }
    return TLobby__sub_80417494(sp18, arg1, arg3);
}

#pragma opt_propagation off
extern s16 TLobby__sub_80417294(NetPacketFragment *self, s32 n, u8 *dst, s16 id)
{
  Ent_80416678 *TLobby__sub_804182DC(void *, void *, s16, s16);
  u8 buf58[8];
  u8 *new_var3;
  Ipv6NdPrefixInfoOption prefix_opt;
  Ipv6NdPrefixEvent prefix_event;
  Ipv6NdMtuOption mtu_opt;
  Ipv6NdMtuEvent mtu_event;
  long long new_var;
  u8 *payload = NULL;
  s16 len;
  u8 *new_var2;
  while (n >= 8)
  {
    u8 *p = TLobby__sub_80406F0C(&self->buffer);
    if (p[1] == 0)
    {
      return -0x10E;
    }
    len = (s16) (p[1] << 3);
    n -= len;
    if (n < 0)
    {
      do
      {
        return -0x10E;
      }
      while (0);
    }
    switch (p[0])
    {
      default:
        TLobby__sub_80406EB8(&self->buffer, len);
        break;

      case 1:
        new_var = len - 2;
        payload = p + 2;
        TLobby__sub_804182DC(dst, payload, new_var, id)->flags |= 0x80;
        TLobby__sub_80406EB8(&self->buffer, len);
        break;

      case 3:
        if (len == 0x20U)
      {
        NetBufferRefInitKind1((NetBufferRef *)buf58, (s32) &prefix_opt);
        new_var3 = prefix_opt.prefix.bytes;
        TLobby__sub_80406FD8(buf58, &self->buffer, 0x20);
        prefix_event.prefix = (new_var2 = new_var3);
        prefix_event.prefix_len = prefix_opt.prefix_len;
        prefix_event.preferred_lifetime = prefix_opt.preferred_lifetime;
        prefix_event.valid_lifetime = prefix_opt.valid_lifetime;
        TLobby__sub_80411604(id, 2, &prefix_event);
      }
        TLobby__sub_80406EB8(&self->buffer, len);
        break;

      case 5:
        if (len == 8U)
      {
        NetBufferRefInitKind1((NetBufferRef *)buf58, (s32) &mtu_opt);
        TLobby__sub_80406FD8(buf58, &self->buffer, 8);
        mtu_event.router = dst;
        mtu_event.mtu = mtu_opt.mtu;
        TLobby__sub_80411604(id, 4, &mtu_event);
      }
        TLobby__sub_80406EB8(&self->buffer, len);
        break;

    }

  }

  if (payload == ((void *) 0))
  {
    Ent_80416994 *e2 = FindEnt_80416994((Glob_80416994 *)&ipv6_neighbor_discovery_state, dst);
    if (e2 != 0)
    {
      e2->flags |= 0x80;
    }
  }
  return 0;
}

s16 TLobby__sub_80417494(void *buf, u8 *a, s16 c) {

    G_80415B38 *g = &ipv6_neighbor_discovery_state;
    s16 *pc = &g->nc;
    Rtr_80418734 **pl = (Rtr_80418734 **)&g->c;
    s16 cc;
    u8 *aa;
    Ra_80418734 *m;
    Rtr_80418734 *p;
    Ent_80416994 *e;
    s32 padx[2];
    struct {
        s32 pad[2];
        Ipv6NdHopLimitEvent s3;
        Ipv6NdAddrEvent s2;
        u8 *s1;
    } loc;

    m = (Ra_80418734 *)buf;
    aa = a;
    cc = c;
    p = FindPeer2_80417494(pc, pl, aa);
    if (p == 0) {
        if ((u16)m->router_lifetime != 0) {
            TLobby__sub_80418734(aa, m, cc);
            loc.s1 = aa;
            TLobby__sub_80411604(cc, 5, &loc.s1);
        } else {
            e = FindEnt_80416994((Glob_80416994 *)g, aa);
            if (e != 0) {
                e->flags &= ~0x80;
            }
            loc.s1 = aa;
            TLobby__sub_80411604(cc, 6, &loc.s1);
        }
    } else if ((u16)m->router_lifetime != 0) {
        loc.s1 = aa;
        TLobby__sub_80411604(cc, 5, &loc.s1);
        p->id = cc;
        p->lifetime = m->router_lifetime;
        if (m->reachable_time != 0) {
            p->reachable_time = m->reachable_time;
            g->reachable_time = p->reachable_time / 1000;
        }
        if (m->retrans_timer != 0) {
            p->retrans_timer = m->retrans_timer;
            g->retrans_timer = p->retrans_timer / 1000;
            g->f2A = p->retrans_timer / 1000 + 1;
        }
    } else {
        Rtr_80418734 *hit;
        e = FindEnt_80416994((Glob_80416994 *)g, aa);
        if (e != 0) {
            e->flags &= ~0x80;
        }
        if ((hit = ScanPeers2_80417494(pc, pl, aa)) == 0) {
            loc.s1 = aa;
            TLobby__sub_80411604(cc, 6, &loc.s1);
        } else {
            loc.s2.next_router = hit->addr;
            loc.s2.addr = aa;
            TLobby__sub_80411604(cc, 7, &loc.s2);
        }
    }
    if (m->cur_hop_limit != 0) {
        loc.s3.router = aa;
        loc.s3.hop_limit = m->cur_hop_limit;
        TLobby__sub_80411604(cc, 3, &loc.s3);
    }
    return 0;
}

#pragma opt_propagation reset
s16 NetIPv6HandleRouterSolicitation(u8 *o, s32 arg1, s32 arg2, s16 arg3) {
    s16 TLobby__sub_80417868(void *, u32, s32, s16);
    u8 b[8];
    u8 a[8];
    s32 pad;
    s32 v;
    Hdr_804177A0 *h = (Hdr_804177A0 *)(o + 0x18);
    u32 len = h->len;
    s16 r;
    void TLobby__sub_80406EB8(void *, s32);

    if (len < 8) {
        return -1;
    }
    NetBufferRefInitKind1((NetBufferRef *)b, (s32)a);
    TLobby__sub_80406FD8(b, h->data, 8);
    len -= 8;
    if (len >= 8) {
        TLobby__sub_80406EB8(h->data, 8);
        r = TLobby__sub_80417868(h, len, arg1, arg3);
        if (r < 0) {
            return r;
        }
    }
    v = arg1;
    TLobby__sub_80411604(arg3, 0xC, &v);
    return 0;
}

#pragma opt_propagation off
#pragma opt_common_subs on
s16 TLobby__sub_80417868(NetPacketFragment *frag, s32 len, u8 *src, s16 iface) {
    u8 *lladdr;
    u8 *h;
    s16 n;
    s16 l;
    Nbr_8041615C *nb;
    s16 NetIPv6IsUnspecified(u8 *arg0);
    Ent_80416678 *TLobby__sub_804182DC(void *, void *, s16, s16);

    lladdr = NULL;
    while (len >= 8) {
        h = TLobby__sub_80406F0C(&frag->buffer);
        if (h[1] == 0) {
            return -0x10E;
        }
        n = h[1] << 3;
        len -= n;
        if (len < 0) {
            return -0x10E;
        }
        if ((s32)h[0] != 1) {
            TLobby__sub_80406EB8(&frag->buffer, n);
        } else {
            if (NetIPv6IsUnspecified(src) == 0) {
                lladdr = h + 2;
                l = n - 2;
                TLobby__sub_804182DC(src, lladdr, l, iface);
            }
            TLobby__sub_80406EB8(&frag->buffer, n);
        }
    }
    if (lladdr != NULL) {
        nb = (Nbr_8041615C *)find_nbr_8041615C((G_8041615C *)&ipv6_neighbor_discovery_state, src);
        if (nb != NULL) {
            nb->flags &= ~0x80;
        }
    }
    return 0;
}

s16 NetIPv6SendNeighborAdvertisement(Pkt_804179A4 *arg0, u8 *address, u8 arg2, Sock_804179A4 *arg3, s16 arg4) {
    Na_804179A4 na;
    Cur_804179A4 cur;
    E_804179A4 *e;
    void *p6;
    s32 TLobby__sub_80406FD8(void *, void *, int);

    s16 TLobby__sub_80411040(void *, void *, int, void *, int);
    s16 TLobby__sub_804136AC(s16 arg0);
    s16 TLobby__sub_80413934(void *, s16);
    s16 TLobby__sub_804145D4(void *, s16);
    s16 NetIPv6IsMulticast(u8 *arg0);
    s16 NetIPv6IsUnspecified(u8 *arg0);
    E_804179A4 *NetIPv6FindOrSelectNeighborCacheEntry(void *, int, int);
    T_804179A4 *NetIPv6SelectDefaultRouter(void *arg0);
    Q_804179A4 *NetIPv6SelectPendingPacketSlot(void);
    if (NetIPv6IsMulticast(address) != 0) {
        return -0x10E;
    }
    if (NetIPv6IsUnspecified((u8 *)arg3) != 0) {
        s16 r = TLobby__sub_804145D4(arg3, arg4);
        if (r < 0) {
            return r;
        }
    } else if (TLobby__sub_80413934(arg3, arg4) == 0) {
        return -0x10E;
    }
    arg3->f24 = 0;
    arg3->f20 = 0;
    arg3->f27 = 0x3A;
    arg3->f26 = 0xFF;
    arg0->total += 0x18;
    arg0->seg[arg0->n].len = 0x18;
    NetBufferRefInitKind1((NetBufferRef *)arg0->seg[arg0->n].buf, (s32)&na);
    arg0->n++;
    na.type = 0x88;
    na.code = 0;
    na.flags = arg2;
    NetMemset(na.rsv, 0, 3);
    NetMemcpy(na.target, address, 0x10);
    if (NetIPv6IsMulticast(arg3->addr) != 0 || TLobby__sub_804136AC(arg4) == 0) {
        na.flags |= 0xFFBF;
        na.cksum = 0;
        na.cksum = TLobby__sub_80411040(arg3, arg3->addr, arg3->f27, arg0, 1);
        p6 = NULL;
    } else {
        e = NetIPv6FindOrSelectNeighborCacheEntry(arg3->addr, 0, 0);
        if (e == NULL) {
            return -0x10E;
        }
        na.flags |= 0x40;
        na.cksum = 0;
        na.cksum = TLobby__sub_80411040(arg3, arg3->addr, arg3->f27, arg0, 1);
        switch (e->f6) {
        case 1:
            break;
        case 3:
            break;
        case 2:
            p6 = e->f28;
            goto tail;
        }
        {
            s16 ret;
            u8 *src;
            u32 n;
            Q_804179A4 *q;
            void *b[2];
            void *a[2];
            Seg_804179A4 *seg;
            e->f8 = arg4;
            e->f4 = 0;
            e->fa = ((s16 *)&ipv6_neighbor_discovery_state)[0x15];
            e->f14 = 0;
            NetMemcpy(e->f16, arg3->addr, 0x10);
            if (e->f10 == NULL) {
                e->f10 = NetIPv6SelectPendingPacketSlot();
            }
            q = e->f10;
            n = arg0->n;
            src = q->f34;
            q->f30 = 0;
            seg = (Seg_804179A4 *)((u8 *)arg0 + n * 0xC);
            while (n != 0) {
                s16 l = seg->len;
                q->f30 += l;
                if (q->f30 > ((s16 *)&ipv6_neighbor_discovery_state)[0xA]) {
                    ret = -0x10E;
                    goto done;
                }
                NetBufferRefInitKind1((NetBufferRef *)((u8 *)&cur), (s32)src);
                TLobby__sub_80406FD8(&cur, arg0->seg[n - 1].buf, l);
                src += l;
                seg--;
                n--;
            }
            ret = 0;
done:
            if (ret < 0) {
                if (e->f10 != NULL) {
                    e->f10->f3 = 0;
                    e->f10 = NULL;
                }
                if (e->fc & 0x80) {
                    T_804179A4 *t = NetIPv6SelectDefaultRouter(e->f16);
                    if (t == NULL) {
                        a[0] = e->f16;
                        TLobby__sub_80411604(e->f8, 6, a);
                    } else {
                        b[1] = t->f14;
                        b[0] = e->f16;
                        TLobby__sub_80411604(e->f8, 7, b);
                    }
                }
                e->f3 = 0;
                e->f26 = 0;
                return ret;
            }
            NetMemcpy((u8 *)e->f10 + 8, arg3, 0x28);
            return NetIPv6SendMulticastNeighborProbe((u8 *)e);
        }
    }
tail:
    return TLobby__sub_80410BA8((NetPacket *)arg0, (NetIPv6SendParameters *)arg3, arg4, p6);
}

#pragma opt_propagation reset
#pragma opt_common_subs reset
/* The two neighbor-cache records share this prefix at the probe call sites. */
struct NetNeighborProbePending {
    u8 padding_0[3];
    u8 state;
    s16 count;
    u8 padding_6[2];
    u8 address[0x28];
};

struct NetNeighborProbeEntry {
    u8 padding_0[3];
    u8 state;
    s16 phase;
    s16 padding_6;
    s16 interface_id;
    s16 timer;
    u8 flags;
    u8 padding_D[3];
    NetNeighborProbePending *pending;
    s16 tries;
    u8 address[0x10];
    s16 result;
    u8 payload[1];
};

typedef char NeighborProbe_E_id_offset[offsetof(E_804179A4, f8) == offsetof(NetNeighborProbeEntry, interface_id) ? 1 : -1];
typedef char NeighborProbe_T_id_offset[offsetof(Ent_804162A4, id) == offsetof(NetNeighborProbeEntry, interface_id) ? 1 : -1];
typedef char NeighborProbe_E_address_offset[offsetof(E_804179A4, f16) == offsetof(NetNeighborProbeEntry, address) ? 1 : -1];
typedef char NeighborProbe_T_address_offset[offsetof(Ent_804162A4, name) == offsetof(NetNeighborProbeEntry, address) ? 1 : -1];

s16 NetIPv6SendMulticastNeighborProbe(u8 *arg0) {
    s32 TLobby__sub_804145D4(void *, int);
    u8 sp2C[0x18];
    u8 sp1C[0x10];
    Arg_80417D1C a7;
    Arg_80417D1C a6;
    s16 result;
    Ent_80418670 *temp_r3_3;
    NetPacket *free_entry;
    NetNeighborProbePending *temp_r3_2;

    free_entry = TLobby::alloc_free_entry();
    if (free_entry == NULL) {
        temp_r3_2 = ((NetNeighborProbeEntry *)arg0)->pending;
        if (temp_r3_2 != NULL) {
            temp_r3_2->state = 0;
            ((NetNeighborProbeEntry *)arg0)->pending = NULL;
        }
        if (((NetNeighborProbeEntry *)arg0)->flags & 0x80) {
            temp_r3_3 = NetIPv6SelectDefaultRouter(((NetNeighborProbeEntry *)arg0)->address);
            if (temp_r3_3 == NULL) {
                a6.p = ((NetNeighborProbeEntry *)arg0)->address;
                TLobby__sub_80411604(((NetNeighborProbeEntry *)arg0)->interface_id, 6, &a6);
            } else {
                a7.v = (s32)temp_r3_3->f14;
                a7.p = ((NetNeighborProbeEntry *)arg0)->address;
                TLobby__sub_80411604(((NetNeighborProbeEntry *)arg0)->interface_id, 7, &a7);
            }
        }
        ((NetNeighborProbeEntry *)arg0)->state = 0;
        ((NetNeighborProbeEntry *)arg0)->result = 0;
        return -0x10E;
    }
    free_entry->fragment_count = 0;
    free_entry->total_bytes = 0;
    if (((NetNeighborProbeEntry *)arg0)->pending != NULL &&
        TLobby__sub_804137FC(((NetNeighborProbeEntry *)arg0)->pending->address,
            ((NetNeighborProbeEntry *)arg0)->interface_id) != 0) {
        NetMemcpy(sp1C, ((NetNeighborProbeEntry *)arg0)->pending->address, 0x10);
    } else {
        TLobby__sub_804145D4(sp1C, ((NetNeighborProbeEntry *)arg0)->interface_id);
    }
    NetIPv6MakeSolicitedNodeMulticastAddress(sp2C, ((NetNeighborProbeEntry *)arg0)->address);
    result = NetIPv6EmitNeighborSolicitation(free_entry, ((NetNeighborProbeEntry *)arg0)->address,
        (NetIPv6SendParameters *)sp1C, ((NetNeighborProbeEntry *)arg0)->interface_id, NULL);
    NetReleasePacket(free_entry);
    return result;
}

s16 NetIPv6SendUnicastNeighborProbe(u8 *arg0) {
    s32 TLobby__sub_804145D4(void *, int);
    u8 sp2C[0x18];
    u8 sp1C[0x10];
    Arg_80417E60 a7;
    Arg_80417E60 a6;
    s16 result;
    Ent_80418670 *temp_r3_3;
    NetPacket *free_entry;
    NetNeighborProbePending *temp_r3_2;

    free_entry = TLobby::alloc_free_entry();
    if (free_entry == NULL) {
        temp_r3_2 = ((NetNeighborProbeEntry *)arg0)->pending;
        if (temp_r3_2 != NULL) {
            temp_r3_2->state = 0;
            ((NetNeighborProbeEntry *)arg0)->pending = NULL;
        }
        if (((NetNeighborProbeEntry *)arg0)->flags & 0x80) {
            temp_r3_3 = NetIPv6SelectDefaultRouter(((NetNeighborProbeEntry *)arg0)->address);
            if (temp_r3_3 == NULL) {
                a6.p = ((NetNeighborProbeEntry *)arg0)->address;
                TLobby__sub_80411604(((NetNeighborProbeEntry *)arg0)->interface_id, 6, &a6);
            } else {
                a7.v = (s32)temp_r3_3->f14;
                a7.p = ((NetNeighborProbeEntry *)arg0)->address;
                TLobby__sub_80411604(((NetNeighborProbeEntry *)arg0)->interface_id, 7, &a7);
            }
        }
        ((NetNeighborProbeEntry *)arg0)->state = 0;
        ((NetNeighborProbeEntry *)arg0)->result = 0;
        return -0x10E;
    }
    free_entry->fragment_count = 0;
    free_entry->total_bytes = 0;
    if (((NetNeighborProbeEntry *)arg0)->pending != NULL &&
        TLobby__sub_804137FC(((NetNeighborProbeEntry *)arg0)->pending->address,
            ((NetNeighborProbeEntry *)arg0)->interface_id) != 0) {
        NetMemcpy(sp1C, ((NetNeighborProbeEntry *)arg0)->pending->address, 0x10);
    } else {
        TLobby__sub_804145D4(sp1C, ((NetNeighborProbeEntry *)arg0)->interface_id);
    }
    NetMemcpy(sp2C, ((NetNeighborProbeEntry *)arg0)->address, 0x10);
    result = NetIPv6EmitNeighborSolicitation(free_entry, ((NetNeighborProbeEntry *)arg0)->address,
        (NetIPv6SendParameters *)sp1C, ((NetNeighborProbeEntry *)arg0)->interface_id,
        ((NetNeighborProbeEntry *)arg0)->payload);
    NetReleasePacket(free_entry);
    return result;
}

s16 NetIPv6EmitNeighborSolicitation(NetPacket *net_packet, u8 *target, NetIPv6SendParameters *addr, s16 iface, u8 *link_address) {
    s16 NetIPv6IsMulticast(u8 *);
    s16 NetIPv6IsUnspecified(u8 *);

    NetIcmpv6NeighborSolicitation message;
    NetSourceLinkLayerOption option;
    s16 result;
    s16 option_length;
    if (NetIPv6IsMulticast(target) != 0) {
        return -0x10E;
    }
    if (NetIPv6IsMulticast((u8 *)(&addr->destination)) != 0) {
        link_address = NULL;
    }
    if (NetIPv6IsUnspecified((u8 *)(&addr->source)) == 0) {
        result = TLobby__sub_80414090((u8 *)(&addr->source), iface);
        if (result < 0) {
            return result;
        }
        result = NetIPv6GetInterfaceLinkLayerAddress((s32)(&option.address), 0x20, iface);
        if (result > 0) {
            option_length = result + 2;
            option.type = 1;
            option.length_units = (u8)(option_length >> 3);
            net_packet->total_bytes += option_length;
            net_packet->fragments[net_packet->fragment_count].length = option_length;
            NetBufferRefInitKind1(&net_packet->fragments[net_packet->fragment_count].buffer, (s32)(&option));
            net_packet->fragment_count += 1;
        }
    }
    addr->traffic_class_bits = 0;
    addr->flow_label = 0;
    addr->next_header = 0x3A;
    addr->hop_limit = 0xFF;
    net_packet->total_bytes += sizeof(message);
    net_packet->fragments[net_packet->fragment_count].length = sizeof(message);
    NetBufferRefInitKind1(&net_packet->fragments[net_packet->fragment_count].buffer, (s32)(&message));
    net_packet->fragment_count += 1;
    message.header.type = 0x87;
    message.header.code = 0;
    message.header.reserved = 0;
    NetMemcpy(&message.target, target, sizeof(message.target));
    message.header.checksum = 0;
    message.header.checksum = TLobby__sub_80411040(&addr->source, &addr->destination, addr->next_header, net_packet, 1);
    return TLobby__sub_80410BA8(net_packet, addr, iface, link_address);
}

#pragma push
#pragma optimization_level 3
s16 NetIPv6EmitRouterSolicitation(NetPacket *net_packet, NetIPv6SendParameters *addr, s16 arg2) {

    s16 NetIPv6IsMulticast(u8 *);
    s16 NetIPv6IsUnspecified(u8 *);
    NetIcmpv6RouterSolicitation message;
    NetSourceLinkLayerOption option;
    s16 temp_r3;
    s16 temp_r5;
    if ((NetIPv6IsMulticast((u8 *)(&addr->destination))) == 0) {
        return -0x10E;
    }
    if ((NetIPv6IsUnspecified((u8 *)(&addr->source))) == 0) {
        temp_r3 = NetIPv6GetInterfaceLinkLayerAddress((s32)(&option.address), (s16)(0x20), arg2);
        if (temp_r3 > 0) {
            temp_r5 = temp_r3 + 2;
            option.type = 1;
            option.length_units = (u8) (temp_r5 >> 3);
            net_packet->total_bytes += temp_r5;
            net_packet->fragments[net_packet->fragment_count].length = temp_r5;
            NetBufferRefInitKind1(&net_packet->fragments[net_packet->fragment_count].buffer, (s32)(&option));
            net_packet->fragment_count += 1;
        }
    }
    addr->traffic_class_bits = 0;
    addr->flow_label = 0;
    addr->next_header = 0x3A;
    addr->hop_limit = 0xFF;
    net_packet->total_bytes += 8;
    net_packet->fragments[net_packet->fragment_count].length = 8;
    NetBufferRefInitKind1(&net_packet->fragments[net_packet->fragment_count].buffer, (s32)(&message));
    net_packet->fragment_count += 1;
    message.header.type = 0x85;
    message.header.code = 0;
    message.header.reserved = 0;
    message.header.checksum = 0;
    message.header.checksum = TLobby__sub_80411040((const IPv6Address *)(&addr->source), (const IPv6Address *)(&addr->destination), addr->next_header, (const NetPacket *)(net_packet), (s16)(1));
    return TLobby__sub_80410BA8(net_packet, addr, arg2, NULL);
}

#pragma pop
extern E_804184DC *TLobby__sub_804182DC(void *a, void *b, s16 len, s16 val) {
    s32 n;
    E_804184DC *e;

    if (a == 0) {
        return 0;
    }
    if (len == 0 || b == 0) {
        return 0;
    }
    e = NetIPv6FindOrSelectNeighborCacheEntry((u8 *)a, (u8 *)b, len);
    if (e == 0) {
        return 0;
    }
    switch (e->state) {
    case 0:
        e->used = 1;
    case 1:
        NetMemcpy(e->addr, a, 0x10);
        n = len;
        if ((u32)n > 0x20) {
            n = 0x20;
        }
        e->klen = n;
        NetMemcpy(e->key, b, e->klen);
        e->kind = 2;
        e->age = ipv6_neighbor_discovery_state.maxage;
        e->iface = val;
        break;
    case 2:
        n = len;
        if ((u32)n > 0x20) {
            n = 0x20;
        }
        e->klen = n;
        NetMemcpy(e->key, b, e->klen);
        if (e->kind == 0 && e->pending != 0) {
            notify_804182DC(e);
            e->pending->f3 = 0;
            e->pending = 0;
        }
        e->kind = 2;
        e->age = ipv6_neighbor_discovery_state.maxage;
        e->iface = val;
        break;
    case 3:
        e->iface = val;
        break;
    default:
        break;
    }
    return e;
}

E_804184DC *NetIPv6FindOrSelectNeighborCacheEntry(u8 *addr, u8 *key, s16 klen) {
    E_804184DC *e;
    s16 n;
    E_804184DC *oldest_b;
    E_804184DC *oldest_a;
    E_804184DC *empty;
    s16 age_b;
    s16 age_a;

    oldest_a = NULL;
    empty = NULL;
    {
        s16 m = ipv6_neighbor_discovery_state.maxage;
        age_b = m;
        age_a = m;
    }
    if (addr == NULL) {
        return NULL;
    }
    n = ipv6_neighbor_discovery_state.nb;
    e = (E_804184DC *)ipv6_neighbor_discovery_state.b;
    while (n > 0) {
        if (e->used != 1) {
            if (empty == NULL) {
                empty = e;
            }
        } else if (NetMemcmp(e->addr, addr, 0x10) == 0) {
            if (klen == 0) {
                if (e->klen != 0) {
                    e->state = 2;
                } else {
                    e->state = 3;
                }
            } else if (e->klen != klen || NetMemcmp(e->key, key, klen) != 0) {
                e->state = 2;
            } else {
                e->state = 3;
            }
            return e;
        } else {
            switch (e->kind) {
            case 2:
                if (e->age < age_a) {
                    oldest_a = e;
                    age_a = e->age;
                }
                break;
            default:
                if (e->age < age_b) {
                    oldest_b = e;
                    age_b = e->age;
                }
                break;
            }
        }
        n--;
        e++;
    }
    if (empty != NULL) {
        empty->state = 0;
        return empty;
    }
    if (oldest_a != NULL) {
        oldest_a->state = 1;
        return oldest_a;
    }
    oldest_b->state = 1;
    return oldest_b;
}

Ent_80418670 *NetIPv6SelectDefaultRouter(void *arg0) {
    s16 n;
    Ent_80418670 *e;
    Ent_80418670 *found;
    Ent_80418670 *best;

    found = NULL;
    best = NULL;
    n = (*(G_80418670 *)&ipv6_neighbor_discovery_state).f4;
    e = (*(G_80418670 *)&ipv6_neighbor_discovery_state).f10;
    while (n > 0) {
        if (e->f3 == 1) {
            if (NetMemcmp(e->f14, arg0, 0x10) == 0) {
                found = e;
                e->f6++;
            } else if (best == NULL) {
                best = e;
            } else if (e->f6 <= best->f6) {
                best = e;
            }
        }
        n--;
        e++;
    }
    if (best == NULL) {
        return found;
    }
    return best;
}

s32 TLobby__sub_80418734(u8 *addr, Ra_80418734 *ra, s16 id) {
    G_80418734 *g = (G_80418734 *)&ipv6_neighbor_discovery_state;
    s16 n;
    Rtr_80418734 *e;
    Rtr_80418734 *r;
    Rtr_80418734 *oldest;
    Rtr_80418734 *slot;
    s16 min;

    slot = NULL;
    min = g->maxage;
    n = g->nrtr;
    r = g->rtrs;
    while (n > 0) {
        if (r->state != 1) {
            if (slot == NULL) {
                slot = r;
            }
        } else if (NetMemcmp(r->addr, addr, 0x10) == 0) {
            r->id = id;
            r->lifetime = ra->router_lifetime;
            if (ra->reachable_time != 0) {
                r->reachable_time = ra->reachable_time;
            }
            if (ra->retrans_timer != 0) {
                r->retrans_timer = ra->retrans_timer;
            }
            return 0;
        } else if (r->lifetime < min) {
            oldest = r;
            min = r->lifetime;
        }
        n--;
        r++;
    }
    if (slot != NULL) {
        slot->state = 1;
        e = slot;
    } else if (oldest != NULL) {
        e = oldest;
    } else {
        return -0x10E;
    }
    NetMemcpy(e->addr, addr, 0x10);
    e->id = id;
    e->lifetime = ra->router_lifetime;
    if (ra->reachable_time != 0) {
        e->reachable_time = ra->reachable_time;
        g->reachable_time = e->reachable_time / 1000;
    }
    if (ra->retrans_timer != 0) {
        e->retrans_timer = ra->retrans_timer;
        g->retrans_timer = e->retrans_timer / 1000;
        g->f2A = e->retrans_timer / 1000 + 1;
    }
    return 0;
}

Ent_804188E4 *NetIPv6SelectPendingPacketSlot(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, Ent_804188E4 *best) {
    Ent_804188E4 *free_;
    G_804188E4 *g = (G_804188E4 *)&ipv6_neighbor_discovery_state;
    s16 v;
    s16 n;
    Ent_804188E4 *e;
    s16 bestv;
    Rec_804188E4 *r;

    bestv = g->f24;
    free_ = NULL;
    n = g->n0;
    e = g->e8;
    while (n > 0) {
        if (e->f3 != 1) {
            if (free_ == NULL) {
                free_ = e;
            }
        } else {
            v = e->f4;
            if (v < bestv) {
                best = e;
                bestv = v;
            }
        }
        n--;
        e++;
    }
    if (free_ != NULL) {
        free_->f3 = 1;
        return free_;
    }
    r = find_804188E4(g, best);
    if (r != NULL) {
        r->f10 = NULL;
    }
    return best;
}

void NetIPv6ApplyNeighborDiscoveryDefaults(G_80415B38 *arg0) {
    if (arg0->stride == 0) {
        arg0->stride = 0x5DC;
    }
    if (arg0->f1C == 0) {
        arg0->f1C = 3;
    }
    if (arg0->f1E == 0) {
        arg0->f1E = 3;
    }
    if (arg0->f20 == 0) {
        arg0->f20 = 1;
    }
    if (arg0->f22 == 0) {
        arg0->f22 = 3;
    }
    if (arg0->maxage == 0) {
        arg0->maxage = 0x1900;
    }
    if (arg0->reachable_time == 0) {
        arg0->reachable_time = 0x1E;
    }
    if (arg0->retrans_timer == 0) {
        arg0->retrans_timer = 1;
    }
    if (arg0->f2A == 0) {
        arg0->f2A = arg0->retrans_timer + 1;
    }
    if (arg0->f2C == 0) {
        arg0->f2C = 6;
    }
}

s32 TLobby__sub_80418A7C(void) {
    G_80418ACC *g = &packet_fragment_pool_state;
    NetUnregisterTimer(TLobby::update_timeout_entries);
    TLobby__sub_803F89A0(g);
    g->na = 0;
    g->nb = 0;
    return 0;
}

s32 TLobby::init_packet_fragment_pools() {
    s16 i;
    A_80418ACC *a;
    B_80418ACC *b;
    G_80418ACC *g = &packet_fragment_pool_state;

    TLobby__sub_803F89A4((u8 *)&packet_fragment_pool_state);
    g->f14 = 0;
    g->f10 = 0;
    a = g->a;
    for (i = 0; i < g->na; i++) {
        NetMemset(a, 0, sizeof(A_80418ACC));
        a->c0 = 0x46;
        a->c1 = 0x50;
        a->c2 = 0x4B;
        a->c3 = i;
        a->f4 = 0;
        a++;
    }
    b = g->b;
    for (i = 0; i < g->nb; i++) {
        NetMemset(b, 0, sizeof(B_80418ACC));
        b->c0 = 0x46;
        b->c1 = 0x52;
        b->c2 = 0x47;
        b->c3 = i;
        b->f4 = 0;
        b++;
    }
    NetRegisterTimer(1000, (s16)(1), (NetTimerCallback)(TLobby::update_timeout_entries));
    return 0;
}

s32 TUdpSocket__sub_80418BD8(A_80418BD8 *a) {
    u32 i;
    A_80418BD8 *b = a;
    for (i = 0; i < b->n; i++) {
        TLobby__sub_80406B6C((O_80406B6C *)&b->e[i]);
    }
    return 0;
}

s32 TLobby__sub_80418C40(u8* self, u16 hdr_len, s16 frag_len, u8 ttl, u32 ident, u8 *src, u16 frag_off, u8 more, s16 iface)
{
    G_80419258* base = (G_80419258 *)&packet_fragment_pool_state;
    s16 count;
    s32 ret;
    E_80419258* node;

    count = 0;
    node = base->head;
    while (node != NULL && count < base->count) {
        if (NetCompareAddresses((NetworkAddress *)(&node->addr), (NetworkAddress *)(src)) == 0 && node->port == ident) {
            ret = TLobby__sub_80418D7C(node, self, hdr_len, frag_off, frag_len, more, iface);
            if (ret == 0) {
                return 0;
            }
            TLobby__sub_80419470(src, ident);
            return ret;
        }
        node = node->next;
        count++;
    }
    node = TLobby__sub_8041955C(src, ident, ttl);
    if (node == NULL) {
        return 0;
    }
    ret = TLobby__sub_80418D7C(node, self, hdr_len, frag_off, frag_len, more, iface);
    if (ret == 0) {
        return 0;
    }
    TLobby__sub_80419470(src, ident);
    return ret;
}

s32 TLobby__sub_80418D7C(E_80419258 *node, u8 *self, u16 hdr_len, u16 frag_off, u16 frag_len, u8 more, s16 iface) {
    NetBufferRef src;
    s16 i;
    N_80419258 *f;
    s16 first_len;
    s16 *nfrags;
    N_80419258 *frag;
    NetPacket *pkt;
    u32 cur_off;
    N_80419258 *first;
    N_80419258 **pool_frags;
    NetPacketFragment *second;
    u32 off;
    N_80419258 *cur;
    N_80419258 *next;
    s32 len;
    s16 slot;
    G_80419258 *g = (G_80419258 *)&packet_fragment_pool_state;
    N_80419258 **frags;
    s32 total;
    s16 cnt;

    if (frag_off == 0) {
        node->f20 = hdr_len;
        node->f24 = iface;
    } else {
        self += hdr_len;
    }
    pool_frags = &g->frags;
    if ((frag = take_80418D7C(frags = pool_frags, nfrags = &g->sub)) == 0) {
        NetResetOtherFragmentLists((E_804196EC *)node);
        if ((frag = take_80418D7C(frags, nfrags)) == 0) {
            return 0;
        }
    }
    frag->f10 = frag_off;
    frag->f12 = frag_len;
    NetBufferRefInitKind1((NetBufferRef *)&src, (s32)self);
    if (frag_off == 0) {
        first_len = (total = frag_len + hdr_len);
        if (TLobby__sub_80415954((NetBufferRef *)&frag->o, first_len, 2) < 0) {
            NetResetOtherFragmentLists((E_804196EC *)node);
            if (TLobby__sub_80415954((NetBufferRef *)&frag->o, first_len, 2) < 0) {
                frag->f4 = 0;
                frag->next = 0;
                return 0;
            }
        }
        TLobby__sub_80406FD8(&frag->o, &src, total);
    } else {
        len = frag_len;
        if (TLobby__sub_80415954((NetBufferRef *)&frag->o, len, 2) < 0) {
            NetResetOtherFragmentLists((E_804196EC *)node);
            if (TLobby__sub_80415954((NetBufferRef *)&frag->o, len, 2) < 0) {
                frag->f4 = 0;
                frag->next = 0;
                return 0;
            }
        }
        TLobby__sub_80406FD8(&frag->o, &src, frag_len);
    }
    frag->next = 0;
    first = node->list;
    if (first == 0) {
        node->f30 = frag;
        node->list = frag;
    } else {
        pkt = (NetPacket *)node->f30;
        off = frag->f10;
        if (off > ((N_80419258 *)pkt)->f10) {
            ((N_80419258 *)pkt)->next = frag;
            node->f30 = frag;
        } else if (off < first->f10) {
            frag->next = first;
            node->list = frag;
        } else {
            f = first->next;
            cnt = *nfrags;
            cur = first;
            next = f;
            if (f == 0) {
                TLobby__sub_80406B6C(&frag->o);
                frag->f4 = 0;
                frag->next = 0;
                return 0;
            }
            while (next != 0 && cnt > 0) {
                cur_off = cur->f10;
                if (off > cur_off && off < next->f10) {
                    frag->next = next;
                    cur->next = frag;
                    break;
                }
                if (off == cur_off) {
                    TLobby__sub_80406B6C(&frag->o);
                    frag->f4 = 0;
                    frag->next = 0;
                    break;
                }
                cur = cur->next;
                cnt--;
                next = next->next;
            }
        }
    }
    if (node->f23 == 0) {
        if (more != 0) {
            return 0;
        }
        node->f23 = 1;
    }
    if (contig_80418D7C(node, nfrags, g) < 0) {
        return 0;
    }
    pkt = TLobby::alloc_free_entry();
    if (pkt == 0) {
        TLobby__sub_8041979C();
        return 0;
    }
    pkt->fragment_count = 0;
    pkt->total_bytes = 0;
    second = &pkt->fragments[1];
    slot = 0;
    i = 0;
    f = node->list;
    cnt = *nfrags;
    while (f != 0 && cnt > 0) {
        if (i == 0) {
            NetMemcpy(&pkt->fragments[0].buffer, &f->o, 8);
            pkt->fragment_count = 1;
            i++;
            pkt->total_bytes = node->f20;
            pkt->fragments[0].length = node->f20;
            NetMemcpy(&second->buffer, &f->o, 8);
            pkt->fragment_count += 1;
            pkt->total_bytes += f->f12;
            second->length = f->f12;
            slot = 2;
            TLobby__sub_80406EB8(&second->buffer, node->f20);
        } else {
            NetMemcpy(&pkt->fragments[slot].buffer, &f->o, 8);
            pkt->fragment_count += 1;
            pkt->total_bytes += f->f12;
            pkt->fragments[i].length = f->f12;
            slot++;
        }
        cur = f;
        f = f->next;
        cur->f4 = 0;
        cnt--;
        i++;
        cur->next = 0;
    }
    return (s32)pkt;
}

void TLobby::update_timeout_entries() {
    G_80419258 *g;
    E_80419258 **head;
    E_80419258 **tail;
    s16 n;
    s16 m;
    N_80419258 *p;
    N_80419258 *q;
    E_80419258 *e;
    E_80419258 *cur;
    E_80419258 *prev;

    g = (G_80419258 *)&packet_fragment_pool_state;
    head = &g->head;
    tail = &g->tail;

    prev = NULL;
    n = 0;
    cur = *head;
    while (cur != NULL && n < g->count) {
        if (cur->f22 != 0) {
            cur->f22--;
        }
        if (cur->f22 != 0) {
            prev = cur;
            cur = cur->next;
        } else {
            TLobby__sub_80419374(cur);
            p = cur->list;
            m = 0;
            while (p != NULL && m < g->sub) {
                q = p;
                p = p->next;
                TLobby__sub_80406B6C(&q->o);
                q->f4 = 0;
                m++;
                q->next = 0;
            }
            if (prev != NULL) {
                prev->next = cur->next;
            } else {
                *head = cur->next;
            }
            if (*tail == cur) {
                *tail = prev;
            }
            e = cur;
            cur = cur->next;
            e->f4 = 0;
            e->next = 0;
            e->f24 = 0;
        }
        n++;
    }
}

s16 TLobby__sub_80419374(E_80419258 *e) {
    IcmpError_80419374 v4;
    Icmp6ErrorInfo v6;
    u8 *data;
    u16 len;
    s16 TUdpSocket__sub_8040CE58(IcmpError_80419374 *icmp, u8 *data, s16 len, s16 id);

    if (e->list == NULL) {
        return 0;
    }
    if (e->list->f10 != 0) {
        return 0;
    }
    data = TLobby__sub_80406F0C(&e->list->o);
    if (data == NULL) {
        return -1;
    }
    len = e->f20 + e->list->f12;
    switch (e->addr.family) {
    case 4:
        v4.type = 11;
        v4.code = 1;
        v4.unused = 0;
        return TUdpSocket__sub_8040CE58(&v4, data, len, e->f24);
    case 6:
        v6.type = 3;
        v6.code = 1;
        v6.pointer = 0;
        return TLobby__sub_8040D510(&v6, data, len, e->f24);
    }
    return -1;
}

s32 TLobby__sub_80419470(u8 *addr, u32 id) {
    G_80419258 *g = (G_80419258 *)&packet_fragment_pool_state;
    E_80419258 **head;
    s16 n;
    E_80419258 *cur;
    E_80419258 *prev;

    if (*(head = &g->head) == NULL) {
        return -1;
    }
    cur = *head;
    prev = NULL;
    n = 0;
    while (cur != NULL && n < g->count) {
        if (NetCompareAddresses((NetworkAddress *)(&cur->addr), (NetworkAddress *)(addr)) == 0 && cur->port == id) {
            E_80419258 **tail;
            if (prev != NULL) {
                prev->next = cur->next;
            } else {
                *head = cur->next;
            }
            if (*(tail = &g->tail) == cur) {
                *tail = prev;
            }
            cur->f4 = 0;
            cur->next = NULL;
            cur->f24 = 0;
            return 0;
        }
        prev = cur;
        cur = cur->next;
        n++;
    }
    return -1;
}

#pragma opt_common_subs on
E_80419258 *TLobby__sub_8041955C(u8 *addr, s32 port, u8 ttl) {
    G_80419258 *g = (G_80419258 *)&packet_fragment_pool_state;
    E_80419258 *e;
    E_80419258 **head;

    e = alloc_entry_8041955C(g);
    if (e == NULL) {
        TLobby__sub_8041979C();
        e = alloc_entry_8041955C(g);
        if (e == NULL) {
            return NULL;
        }
    }
    if (*(head = &g->head) == NULL) {
        g->tail = e;
        *head = e;
    } else {
        g->tail->next = e;
        g->tail = e;
    }
    NetMemcpy(&e->addr, addr, sizeof(e->addr));
    e->port = port;
    e->f23 = 0;
    e->f22 = ttl;
    e->next = NULL;
    e->f30 = NULL;
    e->list = NULL;
    return e;
}

s32 NetResetOtherFragmentLists(E_804196EC *entry) {
    E_804196EC *self = (E_804196EC *)entry;
    G_804196EC *g = (G_804196EC *)&packet_fragment_pool_state;
    N_804196EC *p;
    N_804196EC *cur;
    E_804196EC *e;
    s16 n;

    n = g->count;
    e = g->ents;
    for (; n > 0; n--, e++) {
        if (e->f4 == 1 && e != self) {
            p = e->list;
            while (p != NULL) {
                cur = p;
                p = p->next;
                TLobby__sub_80406B6C(&cur->o);
                cur->f4 = 0;
                cur->next = 0;
            }
            e->f4 = 0;
            e->f28 = 0;
            e->f24 = 0;
        }
    }
    self->f28 = 0;
    g->p10 = self;
    g->p14 = self;
    return 0;
}

s32 TLobby__sub_8041979C(void) {
    G_8041979C *g = (G_8041979C *)&packet_fragment_pool_state;
    E_80419258 *e;
    s16 n;
    s16 m;
    N_80419258 *p;

    n = g->count;
    e = g->ents;
    for (; n > 0; n--, e++) {
        if (e->f4 == 1) {
            e->f4 = 0;
            e->next = NULL;
            e->f24 = 0;
        }
    }
    m = g->sub;
    p = g->nodes;
    for (; m > 0; m--, p++) {
        if (p->f4 == 1) {
            TLobby__sub_80406B6C(&p->o);
            p->f4 = 0;
            p->next = NULL;
        }
    }
    g->head = NULL;
    g->tail = NULL;
    return 0;
}

u16 TUdpSocket__sub_80419864(void *buf, s16 len) {
    union {
        u16 s;
        u8 c[2];
    } su;
    u16 *w;
    u32 sum;
    u32 swapped;

    if (len <= 0) {
        return 0;
    }
    w = (u16 *)buf;
    su.s = 0;
    swapped = 0;
    sum = 0;
    if ((u32)w & 1) {
        su.c[1] = *(u8 *)w;
        w = (u16 *)((u8 *)w + 1);
        len--;
        swapped = 1;
    }
    while (len > 0) {
        if (((u32)w & 0xF) == 0 && len >= 8) {
            break;
        }
        sum += *w++;
        len--;
    }
    if (len > 8) {
        sum += *w;
        for (len--; len > 8; len -= 8) {
            sum += w[4];
            sum += w[1];
            sum += w[2];
            sum += w[3];
            sum += w[8];
            sum += w[5];
            sum += w[6];
            sum += w[7];
            w += 8;
        }
        w++;
    }
    for (; len >= 8; len -= 8) {
        sum += w[0];
        sum += w[1];
        sum += w[2];
        sum += w[3];
        sum += w[4];
        sum += w[5];
        sum += w[6];
        sum += w[7];
        w += 8;
    }
    for (; len > 0; len--) {
        sum += *w++;
    }
    if (swapped) {
        su.c[0] = *(u8 *)w;
        sum += su.s;
        sum = (sum << 8) | (u8)(sum >> 24);
    }
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += sum >> 16;
    return sum;
}

RecoveredGlobal_8041123C_lbl_805C1BB8 ipv6_address_routing_state;
RecoveredGlobal_8041552C_lbl_805C1BE0 network_loopback_state;
Pool_80415690 network_buffer_pool_state;
G_80415B38 ipv6_neighbor_discovery_state;
G_80418ACC packet_fragment_pool_state;
}
