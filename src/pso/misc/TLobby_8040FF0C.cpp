#include "pso/network/NetworkRecordConfig.h"
#include "pso/network/BufferRef.h"
#include "pso/misc/LobbyNetworkInternal.h"

extern "C" {

s32 NetIPv6Shutdown(void) {
    TLobby::release_slot_by_id(0x86DD);
    TLobby__sub_803F87DC((void *)((void *) (&ipv6_protocol_state.value)));
    ipv6_protocol_state.value = 0;
    return 0;
}

s32 NetIPv6Init(void) {
    s16 i;
    E_8040FF58 *e;
    RecoveredGlobal_8040FF0C_lbl_805C1B78 *g = &ipv6_protocol_state;

    NetInitIpv6InterfaceConfig((Obj_803F87E0 *)&g->value);
    e = g->ents;
    for (i = 0; i < g->value; i++) {
        e->c0 = 0x49;
        e->c1 = 0x50;
        e->c2 = 0x36;
        e->c3 = i;
        e->f4 = 0;
        e++;
    }
    g->f8 = 1;
    register_protocol_handler__6TLobbyFUsi(0x86DD, (Handler_8041A130)TLobby__sub_8040FFF8);
    return 0;
}

static inline s16 *ipv6_input_interface(s16 id)
{
  return TLobby::get_valid_entry(id);
}

static inline void release_ipv6_input_record(NetPacket *record)
{
  NetReleasePacket(record);
}

static inline NetPacket *reassemble_ipv6_input(u8 *ip, Ipv6FragmentHeader *frag, s32 remaining, s16 total_len, s16 iface, NetworkAddress *src, Icmp6ErrorInfo *error) {
    u32 offset_flags;
    u32 more;
    u32 offset;
    offset_flags = frag->offset_flags;
    more = offset_flags & 1;
    offset = (offset_flags >> 3) & 0x1FFF;
    if (((u8) offset_flags & 1) && (((remaining - sizeof(Ipv6FragmentHeader)) & 7) != 0)) {
        if (offset == 0) {
            error->type = ICMP6_PARAM_PROB;
            error->code = ICMP6_PARAMPROB_HEADER;
            error->pointer = offsetof(Ipv6Header, payload_length);
            TLobby__sub_8040D510(error, ip, total_len, iface);
        }
        return 0;
    }
    return (NetPacket *) TLobby__sub_80418C40(ip, total_len - (remaining - sizeof(Ipv6FragmentHeader)), remaining - sizeof(Ipv6FragmentHeader), IPV6_REASSEMBLY_TIMEOUT, frag->ident, (u8 *)src, offset, more, iface);
}
#pragma opt_loop_invariants off
#pragma opt_strength_reduction off
#pragma cplusplus off
s32 TLobby__sub_8040FFF8(u8 *ip, int len, s16 id) {
    s16 TLobby__sub_8040D510(struct Icmp6ErrorInfo *msg, u8 *ip, s32 len, s16 iface); /* the definition takes an s16 len */
    s16 TLobby__sub_804105E0(u8 *ip, u8 *packet, s16 len, s16 iface); /* the definition returns s32 */
    s16 TLobby__sub_8041B974(u8 *, u8 *, u8 *);
    s32 TLobby__sub_80421938(struct O_80421938 *, void *, void *, void *, s16);
    s16 TLobby__sub_804136CC(s16);
    s16 NetIPv6IsMulticast(u8 *);
    s16 NetIPv6IsUnspecified(u8 *);
    struct NetworkAddress src_addr;
    struct NetworkAddress dst_addr;
    struct Icmp6ErrorInfo error;
    struct Icmp6ErrorInfo options_error;
    struct Icmp6ErrorInfo frag_error;
    s16 total_len;
    s16 iface;
    u8 next_header;
    s16 i;
    s32 remaining;
    u8 *ext;
    u8 *next_header_field;
    u8 *src;
    struct RecoveredGlobal_8040FF0C_lbl_805C1B78 *state;
    u8 *hdr;
    s16 result;
    u8 *dst_cmp;
    s16 status;
    u8 *dst;
    s16 delivered;
    struct NetPacket *pkt;
    s16 reassembled;
    struct E_8040FF58 *sock;

    if (((s16) len) < (s32) sizeof(struct Ipv6Header)) {
        goto ret;
    }
    iface = id;
    if (ipv6_input_interface(iface) == 0) {
        goto ret;
    }
    if ((ip[0] & 0xF0) != 0x60) {
        return -1;
    }
    total_len = min_8040FFF8(((struct Ipv6Header *) ip)->payload_length + sizeof(struct Ipv6Header), (s16) len);
    if (TLobby__sub_804136CC(iface) == 0) {
        if (TLobby__sub_804136EC(((struct Ipv6Header *) ip)->dst.bytes) < 0) {
            if (NetIPv6IsMulticast(((struct Ipv6Header *) ip)->dst.bytes) == 0) {
                if (TLobby__sub_804105E0(ip, ip, total_len, iface) == 0) {
                    return 0;
                }
                return -1;
            }
        }
    }
    src_addr.family = 6;
    src = src_addr.address;
    NetMemcpy(src, ((struct Ipv6Header *) ip)->src.bytes, 16);
    dst_addr.family = 6;
    dst = dst_addr.address;
    NetMemcpy(dst, ((struct Ipv6Header *) ip)->dst.bytes, 16);
    next_header = ((struct Ipv6Header *) ip)->next_header;
    remaining = total_len - sizeof(struct Ipv6Header);
    hdr = ip;
    ext = hdr + sizeof(struct Ipv6Header);
    next_header_field = hdr + offsetof(struct Ipv6Header, next_header);
    reassembled = 0;
    dst_cmp = dst;
    delivered = 0;
    for (;;) {
        if (next_header == IPV6_NH_NONE) {
            return 0;
        }
        if (((s16) remaining) < 8) {
            error.type = ICMP6_PARAM_PROB;
            error.code = ICMP6_PARAMPROB_NEXTHEADER;
            error.pointer = next_header_field - hdr;
            TLobby__sub_8040D510(&error, hdr, total_len, iface);
            goto ret;
        }
        switch (next_header) {
        case IPV6_NH_HOP_BY_HOP:
            if (total_len != (((s16) remaining) + (s32) sizeof(struct Ipv6Header))) {
                options_error.type = ICMP6_PARAM_PROB;
                options_error.code = ICMP6_PARAMPROB_NEXTHEADER;
                options_error.pointer = next_header_field - hdr;
                TLobby__sub_8040D510(&options_error, hdr, total_len, iface);
                status = -1;
            } else {
                status = process_options_header(ext, remaining, hdr, total_len, iface);
            }
            if (status < 0) {
                goto ret;
            }
            goto adv;

        case IPV6_NH_ICMP:
        case IPV6_NH_IPV4:
        case IPV6_NH_ESP:
        case IPV6_NH_AH:
            goto ret;

        case IPV6_NH_FRAGMENT:
            pkt = reassemble_ipv6_input(hdr, (struct Ipv6FragmentHeader *) ext, remaining, total_len, iface, &src_addr, &frag_error);
            if (pkt == 0) {
                return -1;
            }
            next_header = ext[0];
            reassembled = 1;
            goto payload;

        case IPV6_NH_DEST_OPTIONS:
            status = process_options_header(ext, remaining, hdr, total_len, iface);
            if (status < 0) {
                goto ret;
            }
            /* fallthrough */
        case IPV6_NH_ROUTING:
        adv:
            next_header_field = ext;
            next_header = ext[0];
            remaining -= (ext[1] + 1) << 3;
            ext += (ext[1] + 1) << 3;
            continue;

        case 10:
        case 20:
        case 30:
        case 40:
            break;
        }
        break;
    }

payload:
    if (reassembled == 0) {
        pkt = buildrec_8040FFF8(hdr, total_len, ext, remaining);
        if (pkt == 0) {
            return -257;
        }
    }

    switch (next_header) {
    case IPV6_NH_ICMPV6:
        result = NetIPv6HandleIcmpMessage(pkt, src, dst, ((struct Ipv6Header *) hdr)->hop_limit, iface);
        iface = id;
        if (result < 0) {
            goto fail;
        }
        delivered = 1;
        break;

    case IPV6_NH_TCP:
        result = TLobby__sub_8041B974((u8 *)pkt, (u8 *)&src_addr, (u8 *)&dst_addr);
        if (result < 0) {
            goto fail;
        }
        goto ok;

    case IPV6_NH_UDP:
        result = udp_input__6TLobbyFPvPvPvi((struct O_80420DE4 *)pkt, &src_addr, &dst_addr, iface);
        if (result >= 0) {
            goto ok;
        }
        switch (result) {
        case -2:
            error.type = ICMP6_DST_UNREACH;
            error.code = ICMP6_DST_UNREACH_NOPORT;
            error.pointer = 0;
            TLobby__sub_8040D510(&error, hdr, total_len, iface);
            goto fail;

        default:
            goto fail;
        }

    default:
        break;
    }

    state = &ipv6_protocol_state;
    sock = state->ents;
    for (i = 0; i < state->value; i++, sock++) {
        if ((((u16)sock->f4 == 1) && (sock->proto == next_header)) && (sock->owner != 0)) {
            if ((NetIPv6IsUnspecified(sock->local) != 0) || (NetIPv6CompareAddresses((s32)sock->local, (s32)src) == 0)) {
                if ((NetIPv6IsUnspecified(sock->remote) != 0) || (NetIPv6CompareAddresses((s32)sock->remote, (s32)dst_cmp) == 0)) {
                    TLobby__sub_80421938((struct O_80421938 *)pkt, src, dst, (void *)sock->owner, i);
                    delivered = 1;
                }
            }
        }
    }

    if (delivered == 1) {
    ok:
        if (reassembled == 1) {
            TUdpSocket__sub_80418BD8((struct A_80418BD8 *)pkt);
        }
        release_ipv6_input_record(pkt);
        return 0;
    }
    if (reassembled != 1) {
        error.type = ICMP6_PARAM_PROB;
        error.code = ICMP6_PARAMPROB_NEXTHEADER;
        error.pointer = next_header_field - hdr;
        TLobby__sub_8040D510(&error, hdr, total_len, iface);
    }
fail:
    if (reassembled == 1) {
        TUdpSocket__sub_80418BD8((struct A_80418BD8 *)pkt);
    }
    release_ipv6_input_record(pkt);
ret:
    return -1;
}

#pragma opt_strength_reduction reset
#pragma cplusplus on
#pragma opt_propagation off
extern s32 TLobby__sub_804105E0(u8 *self, u8 *p, s16 lim, s16 ctx)
{
  s16 TLobby__sub_804136AC(s16);
  s32 TLobby__sub_80415D0C(NetPacket *, u8 *, NetIPv6SendParameters *, s16);
  s32 TLobby__sub_80410BA8(NetPacket *, NetIPv6SendParameters *, s16, void *);
  s16 NetIPv6IsMulticast(u8 *);
  NetIPv6SendParameters params;
  u8 err[8];
  s32 tot;
  NetPacket *e;
  s16 rem;
  u8 *q;
  Ipv6Route *hit;
  u8 *hop_limit;
  u8 *prev;
  s16 l;
  s16 flag;
  s16 h6;
  u16 flags;
  u8 state;
  u8 *dst;
  s32 adv;
  s32 r21;
  l = lim;
  tot = l - 0x28;
  hop_limit = &params.hop_limit;

  rem = tot;
  q = p + 0x28;
  prev = p + 6;
  flag = 0;
  params.flow_label = *((s32 *) self);
  params.traffic_class_bits = *((u16 *) self);
  params.next_header = self[6];
  state = self[7];
  params.hop_limit = state;
  state = self[6];
  while (rem >= 8)
  {
    switch (state)
    {
      case 0:
        if (chk_804105E0(p, lim, ctx, l, rem, q, prev) < 0)
      {
        return -1;
      }
        prev = q;
        state = q[0];
        adv = (q[1] + 1) << 3;
        rem -= adv;
        q += adv;
        break;

      case 0x2c:
        flags = (*((u16 *) (q + 2))) & 0xFFF8;
        flag = 1;

      default:
        rem = 0;
        break;

    }

  }

  if (((*hop_limit) == 0) || ((--*hop_limit) == 0))
  {
    if ((flag == 0) || (flags == 0))
    {
      err[0] = 3;
      err[1] = 0;
      *((s32 *) (err + 4)) = 0;
      TLobby__sub_8040D510((Icmp6ErrorInfo *)err, p, lim, ctx);
    }
    return -1;
  }
  hit = (Ipv6Route *)TLobby__sub_80413264(self + 0x18, (s32)(self + 8));
  if (hit == ((void *) 0))
  {
    if ((flag == 0) || (flags == 0))
    {
      err[0] = 1;
      err[1] = 0;
      *((s32 *) (err + 4)) = 0;
      TLobby__sub_8040D510((Icmp6ErrorInfo *)err, p, lim, ctx);
    }
    return -1;
  }
  switch (hit->type)
  {
    case 1:
      dst = self + 0x18;
      break;

    case 2:

    case 3:
      dst = hit->gateway;
      break;

  }

  if (lim > (h6 = TLobby::get_entry_field_26(hit->iface)))
  {
    if ((flag == 0) || (flags == 0))
    {
      err[0] = 2;
      err[1] = 0;
      *((s32 *) (err + 4)) = h6;
      TLobby__sub_8040D510((Icmp6ErrorInfo *)err, p, lim, ctx);
    }
    return -1;
  }
  e = TLobby::alloc_free_entry();
  if (e == ((void *) 0))
  {
    return -1;
  }
  e->fragment_count = 0;
  e->total_bytes = tot;
  e->fragments[e->fragment_count].length = (s16) tot;
  NetBufferRefInitKind1(&e->fragments[e->fragment_count].buffer,  (s32) (p + 0x28));
  e->fragment_count = e->fragment_count + 1;
  NetMemcpy(params.source.bytes, self + 8, 0x10);
  NetMemcpy(params.destination.bytes, self + 0x18, 0x10);
  if ((NetIPv6IsMulticast(dst) == 0) && (TLobby__sub_804136AC(hit->iface) != 0))
  {
    r21 = TLobby__sub_80415D0C(e, dst, &params, hit->iface);
  }
  else
  {
    r21 = TLobby__sub_80410BA8(e, &params, hit->iface, 0);
  }
  NetReleasePacket(e);
  return r21;
}

#pragma opt_propagation reset
s16 TLobby__sub_80410958(u8 *opt, s16 len, u8 *hdr, s16 pktlen, s16 idx) {
    s16 NetIPv6IsMulticast(u8 *arg0);
    Icmp6ErrorInfo err;
    s32 optlen;

    while (len > 0) {
        switch (opt[0]) {
        case 0:
            len -= 1;
            opt += 1;
            continue;
        case 1:
            optlen = opt[1] + 2;
            len -= optlen;
            opt += optlen;
            continue;
        }
        switch (opt[0] & 0xC0) {
        case 0x00:
            optlen = opt[1] + 2;
            len -= optlen;
            opt += optlen;
            continue;
        case 0xC0:
            if (NetIPv6IsMulticast(hdr + 0x18)) {
                return -1;
            }
        case 0x80:
            err.type = 4;
            err.code = 2;
            err.pointer = opt - hdr;
            TLobby__sub_8040D510(&err, hdr, pktlen, idx);
        case 0x40:
        default:
            return -1;
        }
    }
    if (len != 0) {
        return -1;
    }
    return 0;
}

s32 TLobby__sub_80410A98(NetPacket *pkt, u8 *dst, u8 *src, Ipv6SendOptions *opts, s32 next_header) {
    s32 TLobby__sub_80410BA8(void *, void *, s32, void *);
    s32 TLobby__sub_80415D0C(NetPacket *, u8 *, NetIPv6SendParameters *, s32);
    s16 NetIPv6IsMulticast(u8 *arg0);
    s16 TLobby__sub_804136AC(s16 arg0);
    u8 *nexthop;
    Ipv6Route *rt;
    u8 *gateway;
    Ipv6SendOptions defaults;
    NetIPv6SendParameters params;

    rt = (Ipv6Route *)TLobby__sub_80413264(dst, (s32)src);
    if (rt == NULL) {
        return -6;
    }
    if (rt->type == 1) {
        gateway = dst;
    } else {
        gateway = rt->gateway;
    }
    if (opts == NULL) {
        NetMemset(&defaults, 0, sizeof(defaults));
        opts = &defaults;
    }
    nexthop = gateway;
    params.flow_label = opts->flow_label;
    params.traffic_class_bits = opts->traffic_class;
    params.hop_limit = opts->hop_limit;
    params.next_header = next_header;
    NetMemcpy(&params.source, src, sizeof(params.source));
    NetMemcpy(&params.destination, dst, sizeof(params.destination));
    if (!NetIPv6IsMulticast(nexthop) && TLobby__sub_804136AC(rt->iface)) {
        return TLobby__sub_80415D0C(pkt, nexthop, &params, rt->iface);
    }
    return TLobby__sub_80410BA8(pkt, &params, rt->iface, NULL);
}

#pragma opt_common_subs on
s16 TLobby__sub_80410BA8(NetPacket *pkt, NetIPv6SendParameters *params, s16 iface, void *opts) {
    s16 NetIPv6IsMulticast(u8 *arg0);
    s16 TLobby__sub_804112B8(s32 packet, s32 dst, s16 iface);
    s16 TLobby__sub_8041123C(s32 packet, s32 opts, s16 iface);
    RecoveredGlobal_8040FF0C_lbl_805C1B78 *g;
    u32 len;
    Ipv6Header *hdr;
    s16 mtu;
    u32 room;

    len = pkt->total_bytes;
    g = &ipv6_protocol_state;
    hdr = &g->hdr;
    if (len == 0) {
        return 0;
    }
    hdr->vtf.word = 0;
    if (params->flow_label != 0) {
        hdr->vtf.word = params->flow_label & 0xFFFFF;
    } else {
        hdr->vtf.word = g->flow_label;
    }
    if (params->traffic_class_bits != 0) {
        hdr->vtf.half |= params->traffic_class_bits & 0xFF0;
    } else {
        hdr->vtf.half |= g->traffic_class;
    }
    hdr->vtf.version = 0x60;
    hdr->payload_length = len;
    hdr->next_header = params->next_header;
    if (params->hop_limit != 0) {
        hdr->hop_limit = params->hop_limit;
    } else {
        hdr->hop_limit = g->f14;
    }
    NetMemcpy(&hdr->src, &params->source, sizeof(hdr->src));
    NetMemcpy(&hdr->dst, &params->destination, sizeof(hdr->dst));
    mtu = get_mtu_80410BA8(&params->destination, iface);
    if (mtu < 0) {
        return mtu;
    }
    room = mtu - sizeof(Ipv6Header);
    g->f8++;
    if (len > room) {
        return TLobby__sub_80410D6C(pkt, hdr, iface, opts, room);
    }
    pkt->total_bytes += sizeof(Ipv6Header);
    pkt->fragments[pkt->fragment_count].length = sizeof(Ipv6Header);
    NetBufferRefInitKind1(&pkt->fragments[pkt->fragment_count].buffer, (s32)hdr);
    pkt->fragment_count++;
    if (NetIPv6IsMulticast((u8 *)&params->destination)) {
        return TLobby__sub_804112B8((s32)pkt, (s32)&params->destination, iface);
    }
    return TLobby__sub_8041123C((s32)pkt, (s32)opts, iface);
}

s16 TLobby__sub_80410D6C(NetPacket *pkt, Ipv6Header *hdr, s16 iface, void *opts, u32 room) {
    s16 NetIPv6IsMulticast(u8 *addr);
    s16 TLobby__sub_804112B8(s32 packet, s32 dst, s16 iface);
    s16 TLobby__sub_8041123C(s32 packet, s32 opts, s16 iface);
    NetPacket out;
    Ipv6FragmentHeader fh;
    s16 j;
    s16 i;
    s32 flen;
    s32 offset;
    s16 left;
    NetPacket *frag;
    u32 chunk;
    s16 n;
    s16 ret;
    NetPacketFragment *f;

    if (room < sizeof(fh)) {
        return -6;
    }
    fh.next_header = hdr->next_header;
    fh.reserved = 0;
    chunk = room - sizeof(fh);
    chunk &= 0xFFF8;
    fh.offset_flags = 0;
    offset = 0;
    fh.ident = ipv6_protocol_state.f8;
    hdr->next_header = 44;
    while (pkt->total_bytes != 0) {
        out.total_bytes = 0;
        out.fragment_count = 0;
        for (n = pkt->fragment_count - 1; n >= 0; n--) {
            if (out.total_bytes + (flen = pkt->fragments[n].length) < chunk) {
                out.total_bytes += pkt->fragments[n].length;
                out.fragment_count++;
            } else {
                out.total_bytes = chunk;
                out.fragment_count++;
                break;
            }
        }
        j = out.fragment_count - 1;
        frag = &out;
        i = pkt->fragment_count - 1;
        left = out.total_bytes;
        while (j >= 0 && left > 0) {
            NetMemcpy(&out.fragments[j].buffer, &pkt->fragments[i].buffer, sizeof(NetBufferRef));
            if (left < pkt->fragments[i].length) {
                out.fragments[j].length = left;
                pkt->total_bytes -= left;
                f = (NetPacketFragment *)((u8 *)pkt + i * sizeof(NetPacketFragment));
                f[1].length -= left;
                TLobby__sub_80406EB8(&f[1].buffer, left);
                break;
            }
            out.fragments[j].length = pkt->fragments[i].length;
            left -= pkt->fragments[i].length;
            pkt->total_bytes -= pkt->fragments[i].length;
            pkt->fragments[i].length = 0;
            pkt->fragment_count--;
            j--;
            i--;
        }
        fh.offset_flags = offset & 0xFFF8;
        if (pkt->total_bytes != 0) {
            fh.offset_flags |= 1;
        }
        offset += (s16)out.total_bytes;
        out.total_bytes += sizeof(fh);
        out.fragments[out.fragment_count].length = sizeof(fh);
        NetBufferRefInitKind1(&out.fragments[out.fragment_count].buffer, (s32)&fh);
        out.fragment_count++;
        hdr->payload_length = out.total_bytes;
        out.total_bytes += sizeof(Ipv6Header);
        out.fragments[out.fragment_count].length = sizeof(Ipv6Header);
        NetBufferRefInitKind1(&out.fragments[out.fragment_count].buffer, (s32)hdr);
        out.fragment_count++;
        if (NetIPv6IsMulticast(hdr->dst.bytes)) {
            ret = TLobby__sub_804112B8((s32)frag, (s32)&hdr->dst, iface);
        } else {
            ret = TLobby__sub_8041123C((s32)frag, (s32)opts, iface);
        }
        if (ret < 0) {
            break;
        }
    }
    return ret;
}

u16 TLobby__sub_80411040(const IPv6Address *src, const IPv6Address *dst, u8 next_header, const NetPacket *pkt, s16 flag) {
    PH_80411040 ph;
    u32 sum;

    NetMemcpy(&ph.src, (void *)src, sizeof(IPv6Address));
    NetMemcpy(&ph.dst, (void *)dst, sizeof(IPv6Address));
    ph.zero[0] = 0;
    ph.zero[1] = 0;
    ph.zero[2] = 0;
    ph.next_header = next_header;
    if (flag == 0) {
        ph.len = (u16)(pkt->total_bytes - pkt->fragments[0].length);
    } else {
        ph.len = (u16)pkt->total_bytes;
    }
    sum = TUdpSocket__sub_80419864(&ph, sizeof(ph) / 2);
    sum += TLobby__sub_80406BD8((void *)pkt, flag);
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += sum >> 16;
    return ~sum;
}

RecoveredGlobal_8040FF0C_lbl_805C1B78 ipv6_protocol_state;
}
