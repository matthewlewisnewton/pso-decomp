#ifndef PSO_MISC_LOBBY_NETWORK_INTERNAL_H
#define PSO_MISC_LOBBY_NETWORK_INTERNAL_H

#include "pso/network/UdpRuntime.h"
#include "pso/network/NetworkReceiveCallback.h"
#include "pso/network/SocketEvents.h"
#include "pso/network/NetworkDispatch.h"
#include "pso/misc/TLobby.h"
#include "pso/network/NetworkRequestRuntime.h"
#include "pso/network/DnsQuery.h"
#include "pso/network/NetworkRecordConfig.h"
#include "pso/network/BufferRef.h"
#include "pso/network/IPv6.h"

#include "types.h"
#include "pso/protocol/PppControlRuntime.h"
#include "pso/network/BufferPool.h"
#include "pso/protocol/NetworkRuntime.h"
#include "pso/network/EthernetReceiveFilter.h"

struct Self_803FD85C;
struct Tbl_803FD85C {
    u8 pad[0x14];
    void (*f14)(Self_803FD85C *, Tbl_803FD85C *);
    u8 pad18[8];
    void (*f20)(Self_803FD85C *, Tbl_803FD85C *);
};
struct Self_803FD85C {
    u8 f0; u8 f1; u8 f2; u8 f3; u8 f4; u8 f5; u8 f6; u8 f7;
    u8 pad8[8];
    u8 f10[0x1C];
    Tbl_803FD85C *tbl;
    void *f30;
};

struct Info_8040098C { u8 pad[0x1C]; s16 f1C; u8 pad1E[6]; u16 f24; u8 pad26[0x2A]; s16 f50; u8 pad52[6]; u16 f58; };
struct St_8040098C { s8 f0; u8 f1; u8 f2; u8 pad3[0x69]; u8 f6C[0x9C]; s32 f108; s32 f10C; };
struct Self_8040098C { u8 pad[0xC]; St_8040098C *st; u8 pad10[0x20]; Info_8040098C *info; };

struct RecoveredGlobal_803F8AA0_lbl_805BA5C0 {
    s32 value;
    u8 remaining[0x30A8];
};

struct RecoveredGlobal_803F8A0C_lbl_805B9534 {
    s32 value;
    u8 remaining[0x1088];
};

struct RecoveredGlobal_8041552C_lbl_805C1BE0 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_803FB110_lbl_805BFF68 {
    s32 value;
    u8 remaining[0xCC];
};

struct RecoveredGlobal_804050DC_lbl_805C18A0 {
    s32 value;
    u8 remaining[0xC];
};

struct RecoveredGlobal_803FD520_lbl_805C0310 {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    u8 padA[2];
    s16 *buf;
    u8 pad10[6];
    s16 h16;
};

struct RecoveredGlobal_803F895C_lbl_805AEEB0 {
    s32 value;
    u8 remaining[0x49C4];
};

struct RecoveredGlobal_803F89A4_lbl_805B52D4 {
    s32 value;
    u8 remaining[0x17C];
};

struct RecoveredGlobal_803F89A4_lbl_805B5454 {
    s32 value;
    u8 remaining[0x64];
};

struct RecoveredGlobal_803F89DC_lbl_805B54BC {
    s32 value;
    u8 remaining[0x3FFC];
};

struct RecoveredGlobal_803F89DC_lbl_805B94BC {
    s32 value;
    u8 remaining[0x74];
};

struct RecoveredGlobal_803F8A28_lbl_805AEEB0 {
    s32 value;
    u8 remaining[0x49C4];
};

struct RecoveredGlobal_803F94A0_lbl_805BF770 {
    s32 value;
    u8 remaining[0x74C];
};

struct RecoveredGlobal_803FC178_lbl_805C02D0 {
    s32 value;
    u8 remaining[0x3C];
};

struct RecoveredGlobal_803FC1A0_lbl_805C02D0 {
    s32 value;
    u8 remaining[0x3C];
};

typedef B_803FADA0 Strm_80405A74;
struct RecoveredGlobal_80401A68_lbl_805C04A8 {
    s32 value;
    u8 *pool;
    s16 npool;
    s16 pool_words;
    Strm_80405A74 *packet;
    Strm_80405A74 *frame_out;
    Strm_80405A74 *ip_out;
    Strm_80405A74 *frame_in;
    Strm_80405A74 *reply;
    s16 packet_words;
    s16 frame_out_words;
    s16 ip_out_words;
    s16 frame_in_words;
    s16 reply_words;
    u8 pad2A[6];
};

struct RecoveredGlobal_80401A90_lbl_805C04A8 {
    s32 value;
    u8 remaining[0x2C];
};

struct RecoveredGlobal_80402B60_lbl_805C0620 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_80402B88_lbl_805C0620 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_80403D28_lbl_805C0638 {
    s32 value;
    u8 remaining[0x9C];
};

struct RecoveredGlobal_804050EC_lbl_805C18A0 {
    s32 value;
    u8 remaining[0xC];
};

struct RecoveredGlobal_80405114_lbl_805C18A0 {
    s32 value;
    u8 remaining[0xC];
};

struct RecoveredGlobal_8040EF00_lbl_805C1B60 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_8040FE40_lbl_805C1B60 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_8040FE9C_lbl_805C1B60 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_8041123C_lbl_805C1BB8 {
    union { s32 value; struct { s16 a; s16 b; } ab; };
    s16 c;
    u8 remaining[0x22];
};

struct RecoveredGlobal_804112B8_lbl_805C1BB8 {
    s32 value;
    u8 remaining[0x24];
};

struct RecoveredGlobal_80411ECC_lbl_805C1BB8 {
    s32 value;
    u8 remaining[0x24];
};

struct RecoveredGlobal_8041471C_lbl_805C1BB8 {
    s32 value;
    u8 remaining[0x24];
};

#include <stddef.h>
struct Stack_80416008 {
    s32 sp10;
    u8 pad_14[0xC];
    s32 sp20;
    u8 trailing_storage[0x14];
};

struct E_805C1D48 { u8 pad[4]; u16 f4; s16 f6; u8 pad2[0x53C]; };
struct RecoveredGlobal_8041E178_lbl_805C1D48 {
    union { s32 value; E_805C1D48 *p; };
    s16 n;
    u8 remaining[0xA2];
};

struct RecoveredGlobal_803AA0C0_lbl_80556E88 {
    s32 value;
    u8 remaining[0xFC];
};

struct RecoveredGlobal_803F8930_lbl_805B4F84 {
    s32 value;
    u8 remaining[0x34C];
};

struct RecoveredGlobal_803F8B7C_lbl_805BD66C {
    s32 value;
    u8 remaining[0xA00];
};

struct RecoveredFields_80401B8C_arg0 {
    s32 field_0;
    u16 field_4;
};

struct E_8040DDB0 {
    u8 c0, c1, c2, c3;
    s16 f4;
    u8 pad6[2];
    u32 address;
    u8 padC[4];
    u32 owner;
    u8 pad14[4];
    u8 protocol;
    u8 pad19[3];
};
typedef char Ipv4RawSocket_size[sizeof(E_8040DDB0) == 0x1C ? 1 : -1];
struct Ipv4Header {
    u8 version_ihl;
    u8 tos;
    u16 length;
    u16 id;
    u16 fragment;
    u8 ttl;
    u8 protocol;
    u16 checksum;
    u32 src;
    u32 dst;
};

struct Ipv4ProtocolState {
    s16 value;
    u8 pad2[2];
    E_8040DDB0 *ents;
    u16 packet_id;
    u8 default_tos;
    u8 default_ttl;
    Ipv4Header header;
    u8 pad20[8];
};

struct RecoveredGlobal_8040ED28_lbl_805C1B60 {
    union {
        s32 value;
        struct {
            s16 route_count;
            s16 interface_count;
        } counts;
    };
    s16 max_aliases;
    u8 remaining[0x12];
};

struct RecoveredGlobal_8040ED70_lbl_805C1B60 {
    s32 value;
    u8 remaining[0x14];
};

struct E_8040FF58 { u8 c0; u8 c1; u8 c2; u8 c3; s16 f4; u8 local[16]; u8 remote[16]; u8 pad26[2]; u32 owner; u8 pad2C[4]; u8 proto; u8 pad31[3]; };
struct Ipv6Header {
    union {
        u32 word;
        u16 half;
        u8 version;
    } vtf;
    u16 payload_length;
    u8 next_header;
    u8 hop_limit;
    IPv6Address src;
    IPv6Address dst;
};
struct RecoveredGlobal_8040FF0C_lbl_805C1B78 {
    s16 value;
    u8 pad2[2];
    E_8040FF58 *ents;
    s32 f8;
    u16 traffic_class;
    u8 padE[2];
    u32 flow_label;
    u8 f14;
    u8 pad15[3];
    Ipv6Header hdr;
};

struct RecoveredGlobal_80409A3C_lbl_805C1C50 {
    s32 value;
    u8 remaining[0xF4];
};

struct RecoveredGlobal_803F88E4_lbl_805AEEB0
{
  s32 value;
  u8 remaining[0x49C4];
};

struct RecoveredFields_803F88E4_arg0
{
  s16 field_0;
  s16 field_2;
  s16 field_4;
  u8 unknown_6[0x2];
  u8 *field_8;
  u8 *field_C;
  u8 *field_10;
  s16 field_14;
  u8 unknown_16[0x2];
  u8 *field_18;
};

struct Inner_80401CAC { u8 pad[4]; u16 f4; };

struct Outer_80401CAC { Inner_80401CAC *p; };

struct Ent_80408718 { s16 f0; u8 pad[0x16]; };

struct Tbl_80408718 { s16 count; s16 h2; s16 h4; s16 h6; s16 h8; u8 pad[4]; Ent_80408718 *list; };

struct Obj_80405304 { u8 pad[0x18]; u8 f18; };

struct Cfg_803F87E0 { s32 w[10]; };

struct Obj_803F87E0 {
    s16 x0;
    u8 pad2[2];
    void *x4;
    u8 pad8[4];
    s16 xc;
    u8 pade[2];
    s32 x10;
    s8 x14;
    u8 pad15[3];
    Cfg_803F87E0 cfg;
};

struct Desc_803F8AD8 {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    void *funcs;
    void *x;
    void *y;
    void *z;
};

typedef struct Blk_80400BA8 {
    s16 flags;
    u8 pad[2];
    s32 w8;
    s32 wC;
    s32 time;
    s32 w14;
    s32 w18;
} Blk_80400BA8;

typedef struct St_80400BA8 {
    s16 flags;
    u8 pad[2];
    Blk_80400BA8 cur;
    Blk_80400BA8 saved;
    s16 f34;
    u8 pad36[2];
    s16 f38;
    u8 pad3A[0x16];
    s16 f50;
} St_80400BA8;

typedef struct Cfg_804019A8 {
    u8 pad[4];
    s16 flags;
    u8 pad6[6];
    u16 mode;
    u8 padE[0xA];
    u8 b18;
    u8 b19;
} Cfg_804019A8;

typedef struct Names_80403168 {
    u8 pad[0x48];
    u8 a[0x80];
    u8 b[0x80];
} Names_80403168;

typedef struct Ent_804099B4 {
    s16 active;
    u8 pad[0x2E];
} Ent_804099B4;

typedef struct Tbl_804099B4 {
    s16 count;
    Ent_804099B4 *ents;
} Tbl_804099B4;

typedef struct Ent_80409B48 {
    s16 active;
    u8 pad[0x2A];
    s32 (*fn)(s16, s32, s32, s32);
} Ent_80409B48;

typedef struct Tbl_80409B48 {
    s16 count;
    Ent_80409B48 *ents;
} Tbl_80409B48;

typedef struct Ent_80409BD4 {
    s16 active;
    s16 flags;
    u8 pad[0x24];
    s32 (*fn)(s32, s32, s32);
    u8 pad2[0x4];
} Ent_80409BD4;

typedef struct Tbl_80409BD4 {
    s16 count;
    Ent_80409BD4 *ents;
} Tbl_80409BD4;

struct Hdr_8040B6E4 { u16 id; u8 f2; u8 f3; s16 qd; s16 an; s16 ns; s16 ar; u8 body[4]; };

struct QT_8040B6E4 { s16 type; s16 cls; };

struct Hdr_8040B790 { u16 id; u8 f2; u8 f3; u16 qd; u16 an; s16 ns; s16 ar; u8 body[4]; };

struct QT_8040B790 { s16 type; s16 cls; };

struct P_8041D2B8 { s32 a; s32 b; s32 c; s32 d; };

struct O_8041D2B8 { u8 pad0[0x238]; s32 f238; u8 pad23C[0x320 - 0x23C]; s16 n; u8 pad322[0xE]; P_8041D2B8 items[32]; };

typedef struct A_803FADA0 { u8 pad0[4]; u32 a; u32 b; } A_803FADA0;

struct G_8041509C { s16 a; u8 pad[0xA]; s16 c; };

struct Tbl_80409AD8 { s16 count; u8 *list; };

typedef struct Pkt_804081C0 { u8 pad0[4]; s32 f4; s32 f8; s16 fC; u8 padE[2]; u8 f10[8]; } Pkt_804081C0;

typedef struct Pool_804081C0 { u8 pad0[0x24]; u8 *f24; } Pool_804081C0;

typedef struct Out_804081C0 { u8 *f0; u8 *f4; u8 *f8; u8 *fC; u8 *f10; } Out_804081C0;

struct Ent_8040A13C { s16 f0; s16 f2; u8 pad[0x2C]; };

struct G_8040A13C { s16 n; Ent_8040A13C *p; };

struct Ent_8040A19C { s16 f0; s16 f2; u8 pad[0x2C]; };

struct G_8040A19C { s16 n; Ent_8040A19C *p; };

struct Ent_80409F44 { s16 st; s16 pad2; s32 (*f4)(s32); s32 (*f8)(s32); s32 (*fC)(s16); s16 (*f10)(s32); u8 pad14[0x30-0x14]; };

struct Tbl_80409F44 { s16 count; Ent_80409F44 *list; };

#include "pso/network/IPv6Send.h"
#include "pso/misc/TUdpSocket.h"

typedef struct T_804179A4 { u8 pad0[3]; u8 f3; u8 pad4[2]; s16 f6; u8 pad8[0xC]; u8 f14[0x10]; } T_804179A4;

struct Seg_804179A4 { s16 len; s16 pad; u8 buf[8]; };

struct Pkt_804179A4 { u8 pad0[4]; u32 n; s32 total; Seg_804179A4 seg[1]; };

struct Na_804179A4 { u8 type; u8 code; s16 cksum; u8 flags; u8 rsv[3]; u8 target[16]; };

struct Cur_804179A4 { u8 pad[8]; };

struct Sock_804179A4 { u8 pad0[0x10]; u8 addr[0x10]; s32 f20; s16 f24; u8 f26; u8 f27; };

struct Q_804179A4 { u8 pad0[3]; u8 f3; s16 f4; u8 pad6[2]; u8 f8[0x28]; s16 f30; u8 pad32[2]; u8 *f34; };

struct E_804179A4 { u8 pad0[3]; u8 f3; s16 f4; s16 f6; s16 f8; s16 fa; u8 fc; u8 pad[3]; Q_804179A4 *f10; s16 f14; u8 f16[0x10]; s16 f26; u8 f28[1]; };

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

extern "C" {
void TLobby__sub_803F8AA0(u8 *arg0);
void TLobby__sub_803F8A0C(u8 *arg0);
extern RecoveredGlobal_8041552C_lbl_805C1BE0 network_loopback_state;
extern RecoveredGlobal_804050DC_lbl_805C18A0 lbl_805C18A0;
void TLobby__sub_804050DC(s16 arg0);
extern s16 lbl_805D7A7A;
struct G_80415B38;
void NetIPv6ApplyNeighborDiscoveryDefaults(G_80415B38 *arg0);
void TLobby__sub_803F89A4(u8 *arg0);
void TLobby__sub_803FD85C(void *);
s32 TLobby__sub_804062A0(s16);
s32 TLobby__sub_803F79AC(void *);
void TLobby__sub_803F79B0(u8 *arg0);
extern s32 lobby_timer_list_head;
s16 reset_network_timer_list(void);
void TLobby__sub_803F8A08(void *);
extern s16 lobby_udp_socket_table;
s32 arp_init(void);
void TLobby__sub_804073B8(void);
s32 arp_remove_alias(s16, s32);
s32 arp_add_alias(s16, s32);
s32 arp_resolve_and_send(s16, void *, void *);
s16 register_arp_interface(s16, s16, s16, s16, s16, s32, s16, s32);
s32 TLobby__sub_8040878C(void);
void TLobby__sub_803F8A9C(void *);
extern s16 lobby_handler_table_desc;
s32 TLobby__sub_80409AA8(void);
s32 TLobby__sub_8040C9E0(u8 *arg0, u8 *arg1);
u16 TLobby__sub_8040D8F0(u8 *arg0, u8 *arg1, s8 arg2, u8 *arg3, s16 arg4);
s32 TLobby__sub_8040DA54(u8 *arg0, u8 *arg1);
s32 TLobby__sub_8040FDA0(u32, s16);
s32 is_addr_unspecified__6TLobbyFPv(u8 *arg0);
extern RecoveredGlobal_8040EF00_lbl_805C1B60 ipv4_address_routing_state;
struct Ipv4Route;
Ipv4Route *TLobby__sub_8040F76C(u32, u32);
s16 TLobby__sub_8040FEE4(s32 arg0, s32 arg1);
extern RecoveredGlobal_8041123C_lbl_805C1BB8 ipv6_address_routing_state;
u8 * TLobby__sub_80413264(void *, s32);
s32 TLobby__sub_80413230(u8 *arg0, s32 arg1);
void TLobby__sub_804136AC(s16 arg0);
s16 is_socket_flag_set__6TLobbyFs(s16);
s16 TLobby__sub_804136CC(s16 arg0);
s16 NetIPv6IsLoopback(u8 *arg0);
s32 NetIPv6IsUnspecified(u8 *arg0);
s16 NetIPv6CompareAddresses(s32 arg0, s32 arg1);
s16 TLobby__sub_8041510C(void);
void TLobby__sub_804150EC(void);
void TLobby__sub_8041615C(void);
void NetIPv6TickNeighborCache(void);
void NetIPv6TickNeighborDiscovery(void);
s16 NetIPv6SendUnspecifiedSourceNeighborSolicitation(u8 *target, s16 iface);
extern NetworkDispatchState network_dispatch_state;
s32 TLobby__sub_8041D368(u8 *arg0);
u8 * TLobby__sub_8041B5C0(void *);
extern RecoveredGlobal_8041E178_lbl_805C1D48 tcp_protocol_state;
s32 TLobby__sub_804112B8(s32 arg0, s32 arg1, s16 arg2);
s32 TLobby__sub_8041123C(s32 arg0, s32 arg1, s16 arg2);
s16 get_ipv4_interface_mtu(s16 arg0);
s32 TLobby__sub_8040FE40(s16 arg0);
void TLobby__sub_803F8930(u8 *arg0);
void TLobby__sub_80405328(u8 *arg0);
s16 TLobby__sub_8040FCEC(u32);
s16 TLobby__sub_804136EC(u8 *);
void TLobby__sub_803F892C(void *);
extern Ipv4ProtocolState ipv4_protocol_state;
s32 TLobby__sub_8040DD68(void);
void TLobby__sub_803F8958(void *);
s32 shutdown_ipv4_routing(void);
s32 init_ipv4_routing(void);
void TLobby__sub_803F87DC(void *);
extern RecoveredGlobal_8040FF0C_lbl_805C1B78 ipv6_protocol_state;
s32 NetIPv6Shutdown(void);
void TLobby__sub_803F89D8(void *);
extern Pool_80415690 network_buffer_pool_state;
s32 TLobby__sub_803F8E9C();
s16 TLobby__sub_8041579C(void *);
s32 TLobby__sub_8041EB74(u8 *arg0);
s16 TLobby__sub_80409A3C(u8 *arg0, s16 arg1);
s16 TLobby__sub_80415954(NetBufferRef *ref, s32 size, s16 owner);
s32 TLobby__sub_8041ECA4(u8 *arg0);
void TLobby__sub_803FD958(u8 *arg0);
void TLobby__sub_80401CAC(Outer_80401CAC *o, u16 v);
u16 read_network_u16_be(u8 *p);
u32 TLobby__sub_80402AFC(u8 *p);
u8 *write_network_u16_be(u8 *p, u16 v);
extern Tbl_80408718 lbl_805C1AB0;
Ent_80408718 *find_free_peer_entry__6TLobbyFv(void);
s32 TLobby__sub_80405304(void *arg0);
u16 TLobby__sub_80406BD8(void *, s16);
s32 OSDisableInterrupts(void);
s32 OSRestoreInterrupts(s32);
void TLobby__sub_803F97E8(int);
s32 TLobby__sub_803FC684(u8 *, u8 *, u8 *);
extern u8 lbl_805C0038[];
extern s16 lbl_805D7A7C;

s16 TLobby__sub_8040DC8C(u8 *arg0, u8 *arg1);
s32 TLobby__sub_804217E4(void);
s32 TLobby__sub_80421814(void);
s32 TLobby__sub_80421B3C(s32);
s16 TLobby__sub_80401BCC(void *, void *, int);
extern u8 lcp_read_value_buffer[4];
extern u8 lobby_read_byte_buffer[1];
s16 TLobby__sub_80403F4C(void *, Strm_80405A74 **);
s16 TLobby__sub_804040E0(void *, Strm_80405A74 **);
s32 TLobby__sub_804060B8(u8 *, s32, int);
extern u8 lobby_ppp_read_buf;
extern u8 ppp_input_byte;
void ppp_input_packet__6TLobbyFPv(Strm_80405A74 *arg0);
s32 NetCompareBitsBackward(u8 *arg0, u8 *arg1, s16 arg2);
s32 NetCompareBitPrefix(u8 *a, u8 *b, s16 bits);
s32 NetIPv6MakeSolicitedNodeMulticastAddress(u8 *arg0, u8 *arg1);
void TLobby__sub_803F8B78(void *);
s32 TLobby__sub_8041509C(void);
s32 TLobby__sub_80409AD8(void);
Pkt_804081C0 *alloc_packet_with_header__6TLobbyFPvPv(Out_804081C0 *arg0, u8 *arg1);
s32 init_ipv6_all_routers_multicast_address(u8 *arg0, s8 arg1);
bool init_ipv6_all_nodes_multicast_address(u8 *arg0, s8 arg1);
s32 TLobby__sub_8041A9AC(int);
s32 TLobby__sub_8041FFF8(int, int);
s32 TLobby__sub_80420BD0(void *, void *, s32);
s32 tcp_start_send(s16 arg0, u8 *arg1, void (*completion)(s16, s16), u8 arg3);
void TLobby__sub_80406EB8(NetBufferRef *ref, s32 n);
void TLobby__sub_80406FD8(void *, void *, s32);
s16 TLobby__sub_80416F58(u8 *, s32, void *, void *);
s16 TLobby__sub_80417028(IPv6NeighborSolicitation *ns, u8 *src, u8 *dst, s16 iface);
s16 NetIPv6HandleNeighborSolicitation(u8 *arg0, void *arg1, void *arg2, void *arg3);
u16 TLobby__sub_80411040(const IPv6Address *, const IPv6Address *, u8, const NetPacket *, s16);
s16 NetIPv6GetInterfaceLinkLayerAddress(s32 arg0, s16 arg1, s16 arg2);
s16 NetIPv6EmitRouterSolicitation(NetPacket *arg0, NetIPv6SendParameters *arg1, s16 arg2);
extern struct G_80415B38 ipv6_neighbor_discovery_state;
s16 NetIPv6SendNeighborAdvertisement(Pkt_804179A4 *arg0, u8 *arg1, u8 arg2, Sock_804179A4 *arg3, s16 arg4);
s32 NetRegisterTimer(s32 period, s16 locked, NetTimerCallback fn);
void TLobby__sub_8041A3CC(void);
void TLobby__sub_8041A5B4(void);
s32 NetTCPInit(void);
void TLobby__sub_803F9344(s32, void *, s32);
void NetEnqueueProtocolMessage(s32 arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4);
void TLobby__sub_803F8794(void *);
void TLobby__sub_803F8864(void *);
void TLobby__sub_803F88E0(void *);
void TLobby__sub_803F89A0(void *);
void TLobby__sub_803F8A24(void *);
s32 NetIPv6IsLinkLocal(u8 *arg0);
s32 TLobby__sub_8041549C(s16 arg0);
s32 TLobby__sub_804154C0(s16 arg0);
s32 TLobby__sub_804154E4(s16 arg0);
s32 TLobby__sub_80415508(s16 arg0);
s32 get_adjusted_slot_count__6TLobbyFPv(u8 *arg0);

void TLobby__sub_803F87DC(void * _w0);

typedef struct RecoveredFields_803F88E4_arg0 RecoveredFields_803F88E4_arg0;
typedef struct RecoveredGlobal_803F88E4_lbl_805AEEB0 RecoveredGlobal_803F88E4_lbl_805AEEB0;
typedef char RecoveredGlobal_803F88E4_lbl_805AEEB0_size[((sizeof(RecoveredGlobal_803F88E4_lbl_805AEEB0)) == 0x49C8) ? (1) : (-1)];

void TLobby__sub_803F892C(void * _w0);

typedef char RecoveredGlobal_803F8930_lbl_805B4F84_size[sizeof(RecoveredGlobal_803F8930_lbl_805B4F84) == 0x350 ? 1 : -1];

void TLobby__sub_803F8958(void * _w0);

typedef char RecoveredGlobal_803F895C_lbl_805AEEB0_size[sizeof(RecoveredGlobal_803F895C_lbl_805AEEB0) == 0x49C8 ? 1 : -1];

typedef char RecoveredGlobal_803F89A4_lbl_805B52D4_size[sizeof(RecoveredGlobal_803F89A4_lbl_805B52D4) == 0x180 ? 1 : -1];
typedef char RecoveredGlobal_803F89A4_lbl_805B5454_size[sizeof(RecoveredGlobal_803F89A4_lbl_805B5454) == 0x68 ? 1 : -1];

void TLobby__sub_803F89D8(void * _w0);

typedef char RecoveredGlobal_803F89DC_lbl_805B54BC_size[sizeof(RecoveredGlobal_803F89DC_lbl_805B54BC) == 0x4000 ? 1 : -1];
typedef char RecoveredGlobal_803F89DC_lbl_805B94BC_size[sizeof(RecoveredGlobal_803F89DC_lbl_805B94BC) == 0x78 ? 1 : -1];

void TLobby__sub_803F8A08(void * _w0);

typedef char RecoveredGlobal_803F8A0C_lbl_805B9534_size[sizeof(RecoveredGlobal_803F8A0C_lbl_805B9534) == 0x108C ? 1 : -1];

typedef char RecoveredGlobal_803F8A28_lbl_805AEEB0_size[sizeof(RecoveredGlobal_803F8A28_lbl_805AEEB0) == 0x49C8 ? 1 : -1];

void TLobby__sub_803F8A9C(void * _w0);

typedef char RecoveredGlobal_803F8AA0_lbl_805BA5C0_size[sizeof(RecoveredGlobal_803F8AA0_lbl_805BA5C0) == 0x30AC ? 1 : -1];

typedef char RecoveredGlobal_803F8B7C_lbl_805BD66C_size[sizeof(RecoveredGlobal_803F8B7C_lbl_805BD66C) == 0xA04 ? 1 : -1];

typedef char RecoveredGlobal_803F94A0_lbl_805BF770_size[sizeof(RecoveredGlobal_803F94A0_lbl_805BF770) == 0x750 ? 1 : -1];

typedef char RecoveredGlobal_803AA0C0_lbl_80556E88_size[sizeof(RecoveredGlobal_803AA0C0_lbl_80556E88) == 0x100 ? 1 : -1];

typedef char RecoveredGlobal_803FB110_lbl_805BFF68_size[sizeof(RecoveredGlobal_803FB110_lbl_805BFF68) == 0xD0 ? 1 : -1];

typedef char RecoveredGlobal_803FC178_lbl_805C02D0_size[sizeof(RecoveredGlobal_803FC178_lbl_805C02D0) == 0x40 ? 1 : -1];

extern s16 lbl_805D7A86;

typedef char RecoveredGlobal_803FC1A0_lbl_805C02D0_size[sizeof(RecoveredGlobal_803FC1A0_lbl_805C02D0) == 0x40 ? 1 : -1];

struct O_80400ACC;
void TLobby__sub_80400ACC(O_80400ACC *);
struct Outer_80401CAC;
void TLobby__sub_80401CAC(Outer_80401CAC *, u16);
s32 TLobby__sub_80405304(void *);

s32 TLobby__sub_803FC684(u8 *arg0, u8 *arg1, u8 *arg2);

typedef void (*Fn_803FD10C)(void);

typedef char RecoveredGlobal_803FD520_lbl_805C0310_size[sizeof(RecoveredGlobal_803FD520_lbl_805C0310) == 0x18 ? 1 : -1];

struct N_80405298;
void TLobby__sub_80405298(N_80405298 *o, s32 v);

#define self ((Self_803FD85C *)arg0)
void TLobby__sub_803FD85C(void *arg0);
#undef self

struct Self_803FDA68;
struct Tbl_803FDA68 {
    u8 pad[0x14];
    void (*f14)(Self_803FDA68 *, Tbl_803FDA68 *);
    u8 pad18[0xC];
    void (*f24)(Self_803FDA68 *, Tbl_803FDA68 *);
    void *(*f28)(Self_803FDA68 *, Tbl_803FDA68 *);
};
struct Self_803FDA68 {
    u8 f0; u8 f1; u8 f2; u8 f3; u8 f4; u8 f5; u8 f6; u8 f7;
    s16 f8; u8 padA[6];
    u8 f10[0x1C];
    Tbl_803FDA68 *tbl;
    void *f30;
};

struct V_803FE600;
struct O_803FE600 {
    u8 b0; u8 b1; u8 b2; u8 b3; u8 b4; u8 b5; u8 b6; u8 b7;
    u8 pad8[0x2C - 8];
    V_803FE600 *p2C;
};
struct V_803FE600 {
    u8 pad[0x14];
    void (*fn)(O_803FE600 *, V_803FE600 *);
};

struct O_80400ACC { u8 b0; u8 b1; u8 b2; u8 pad3[0x108 - 3]; s32 f108; };
void TLobby__sub_80400ACC(O_80400ACC *o);

typedef char RecoveredGlobal_80401A68_lbl_805C04A8_size[sizeof(RecoveredGlobal_80401A68_lbl_805C04A8) == 0x30 ? 1 : -1];

#define rd16_804012E0(src) (TLobby__sub_80401BCC(src, lcp_read_value_buffer, 2) != 2 ? -1 : read_network_u16_be(lcp_read_value_buffer))
#define rd32_804012E0(src) (TLobby__sub_80401BCC(src, lcp_read_value_buffer, 4) != 4 ? 0 : TLobby__sub_80402AFC(lcp_read_value_buffer))
#define rd8_804012E0(src) (TLobby__sub_80401BCC(src, lobby_read_byte_buffer, 1) != 1 ? -1 : (s16)lobby_read_byte_buffer[0])
#define F(t, o) (*(t *)(arg2 + (o)))

typedef char RecoveredGlobal_80401A90_lbl_805C04A8_size[sizeof(RecoveredGlobal_80401A90_lbl_805C04A8) == 0x30 ? 1 : -1];

typedef char RecoveredGlobal_80402B60_lbl_805C0620_size[sizeof(RecoveredGlobal_80402B60_lbl_805C0620) == 0x18 ? 1 : -1];

#define S11_80401FE8 7
#define S12_80401FE8 12
#define S13_80401FE8 17
#define S14_80401FE8 22
#define S21_80401FE8 5
#define S22_80401FE8 9
#define S23_80401FE8 14
#define S24_80401FE8 20
#define S31_80401FE8 4
#define S32_80401FE8 11
#define S33_80401FE8 16
#define S34_80401FE8 23
#define S41_80401FE8 6
#define S42_80401FE8 10
#define S43_80401FE8 15
#define S44_80401FE8 21
#define F_80401FE8(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G_80401FE8(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H_80401FE8(x, y, z) ((x) ^ (y) ^ (z))
#define I_80401FE8(x, y, z) ((y) ^ ((x) | (~z)))
#define ROTATE_LEFT_80401FE8(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define FF_80401FE8(a, b, c, d, x, s, ac) { (a) += F_80401FE8((b), (c), (d)) + (x) + ac; (a) = ROTATE_LEFT_80401FE8((a), (s)); (a) += (b); }
#define GG_80401FE8(a, b, c, d, x, s, ac) { (a) += G_80401FE8((b), (c), (d)) + (x) + ac; (a) = ROTATE_LEFT_80401FE8((a), (s)); (a) += (b); }
#define HH_80401FE8(a, b, c, d, x, s, ac) { (a) += H_80401FE8((b), (c), (d)) + (x) + ac; (a) = ROTATE_LEFT_80401FE8((a), (s)); (a) += (b); }
#define II_80401FE8(a, b, c, d, x, s, ac) { (a) += I_80401FE8((b), (c), (d)) + (x) + ac; (a) = ROTATE_LEFT_80401FE8((a), (s)); (a) += (b); }
#undef S11_80401FE8
#undef S12_80401FE8
#undef S13_80401FE8
#undef S14_80401FE8
#undef S21_80401FE8
#undef S22_80401FE8
#undef S23_80401FE8
#undef S24_80401FE8
#undef S31_80401FE8
#undef S32_80401FE8
#undef S33_80401FE8
#undef S34_80401FE8
#undef S41_80401FE8
#undef S42_80401FE8
#undef S43_80401FE8
#undef S44_80401FE8
#undef FF_80401FE8
#undef GG_80401FE8
#undef HH_80401FE8
#undef II_80401FE8
#undef ROTATE_LEFT_80401FE8
#undef F_80401FE8
#undef G_80401FE8
#undef H_80401FE8
#undef I_80401FE8

typedef char RecoveredGlobal_80402B88_lbl_805C0620_size[sizeof(RecoveredGlobal_80402B88_lbl_805C0620) == 0x18 ? 1 : -1];

typedef char RecoveredGlobal_804050DC_lbl_805C18A0_size[sizeof(RecoveredGlobal_804050DC_lbl_805C18A0) == 0x10 ? 1 : -1];

typedef char RecoveredGlobal_80403D28_lbl_805C0638_size[sizeof(RecoveredGlobal_80403D28_lbl_805C0638) == 0xA0 ? 1 : -1];

typedef struct B_80403F4C {
    u16 field_0;
    u16 field_2;
    u32 field_4;
    u32 field_8;
    u16 field_C;
    u16 field_E;
    u16 field_10;
    u16 field_12;
    u8 pad_14;
    u8 flag_15;
    u8 flag_16;
    u8 flag_17;
    u8 flag_18;
    u8 flag_19;
    u8 flag_1A;
    u8 options_len;
    u8 options[0x28];
} B_80403F4C;
typedef char B_80403F4C_size[sizeof(B_80403F4C) == 0x44 ? 1 : -1];

typedef struct Ent_80403F4C {
    u8 pad0[8];
    A_80403F4C a;
    B_80403F4C b;
} Ent_80403F4C;

typedef struct Obj_80403F4C {
    u8 pad0[4];
    Ent_80403F4C *ents;
    u8 pad8;
    u8 max;
    u8 padA[2];
    u8 cur;
    u8 flags;
    u8 padE[0x28 - 0xE];
    s32 n28;
    u8 pad2C[4];
    s32 n30;
} Obj_80403F4C;

#define o ((Obj_80403F4C *)ov)
#define pp ((u8 **)spp)
s16 TLobby__sub_80403F4C(void *ov, Strm_80405A74 **spp);
#undef o
#undef pp

extern u32 lbl_805C1AD8[6];
#define lbl_805C1AD8 (*(Tbl_80408F2C *)lbl_805C1AD8)

typedef char RecoveredGlobal_804050EC_lbl_805C18A0_size[sizeof(RecoveredGlobal_804050EC_lbl_805C18A0) == 0x10 ? 1 : -1];

typedef char RecoveredGlobal_80405114_lbl_805C18A0_size[sizeof(RecoveredGlobal_80405114_lbl_805C18A0) == 0x10 ? 1 : -1];

struct G_80405150 { s32 p0; s32 p4; s16 h8; };
extern s16 lbl_805D7A84;
extern s16 lbl_805D7A88;
s32 TLobby__sub_803FB6A0(void);
void TLobby__sub_803FB7A4(void);

typedef struct Timer_804051CC {
    struct Timer_804051CC *next;
    u8 pad4[4];
    u32 f8;
    s32 fC;
    void (*f10)(s32);
    s32 f14;
    u8 f18;
} Timer_804051CC;

s32 TLobby__sub_80405700();

struct N_80405298 { N_80405298 *next; s32 f4; u8 pad8[0x18 - 8]; u8 b18; };
#define HEAD_80405298 (*(N_80405298 **)&lobby_timer_list_head)

struct B_803FADA0;
u16 TLobby__sub_803FE934(u8 *, B_803FADA0 *, u16);

extern RecoveredGlobal_80401A68_lbl_805C04A8 lbl_805C04A8;
extern s16 lbl_805D7A8A;
extern s32 lbl_805D7A8C;
extern s32 lbl_805D7A94;
extern u8 lbl_805C18B0[];
extern Strm_80405A74 *ppp_rx_frame_ptr;
extern u8 *lbl_805D7ADC;
extern u8 *lbl_805D7AE0;
extern u32 lbl_805D7AE4;
extern u16 lbl_805D7AE8;
extern u16 lbl_804FD3A8[];
s32 TLobby__sub_803F812C(u16, void *, u16 *);
s32 TLobby__sub_803F8090(void);
s16 TLobby__sub_804290D4(s32);
struct Outer_80401CAC;
void TLobby__sub_80401CAC(Outer_80401CAC *, u16);

/* Transmit-side view of the three protocol state machines and link counters. */
typedef struct PppLinkState {
    u8 active;
    u8 pad01[3];
    Conn_804004DC lcp;
    Conn_804004DC pap;
    Conn_804004DC ipcp;
    Conn_804004DC chap;
    Conn_804004DC ipv6cp;
    u8 pad108[8];
    s32 transmit_bytes;
    s32 transmit_frames;
    u8 pad118[0x122 - 0x118];
    s16 transmit_errors;
    s16 allocation_errors;
    u8 pad126[0x130 - 0x126];
    s16 lcp_input_count;
    s16 pap_input_count;
    s16 ipcp_input_count;
    s16 chap_input_count;
    s16 ipv6cp_input_count;
    s16 protocol_reject_count;
    u8 pad13C[0x140 - 0x13C];
    s16 receive_errors;
    s16 control_frame_allocation_errors;
} PppLinkState;
typedef char PppLinkIpcpOffset[offsetof(PppLinkState, ipcp) == 0x6c ? 1 : -1];
typedef char PppLinkIpv6cpOffset[offsetof(PppLinkState, ipv6cp) == 0xd4 ? 1 : -1];
typedef char PppLinkErrorsOffset[offsetof(PppLinkState, transmit_errors) == 0x122 ? 1 : -1];
typedef char PppLinkPapOffset[offsetof(PppLinkState, pap) == 0x38 ? 1 : -1];
typedef char PppLinkChapOffset[offsetof(PppLinkState, chap) == 0xA0 ? 1 : -1];
typedef char PppLinkLcpCountOffset[offsetof(PppLinkState, lcp_input_count) == 0x130 ? 1 : -1];
typedef char PppLinkPapCountOffset[offsetof(PppLinkState, pap_input_count) == 0x132 ? 1 : -1];
typedef char PppLinkIpcpCountOffset[offsetof(PppLinkState, ipcp_input_count) == 0x134 ? 1 : -1];
typedef char PppLinkChapCountOffset[offsetof(PppLinkState, chap_input_count) == 0x136 ? 1 : -1];
typedef char PppLinkIpv6cpCountOffset[offsetof(PppLinkState, ipv6cp_input_count) == 0x138 ? 1 : -1];
typedef char PppLinkProtocolRejectCountOffset[offsetof(PppLinkState, protocol_reject_count) == 0x13A ? 1 : -1];
typedef char PppLinkReceiveErrorsOffset[offsetof(PppLinkState, receive_errors) == 0x140 ? 1 : -1];
typedef char PppLinkControlFrameAllocationErrorsOffset[offsetof(PppLinkState, control_frame_allocation_errors) == 0x142 ? 1 : -1];

typedef struct Lobby_804062A0 {
    u8 state;
    u8 pad[3];
    u8 sub[0x140];
} Lobby_804062A0;

struct RecoveredFields_80401B8C_arg0;
struct Self_8040098C;
inline s32 valid_80405A74(Strm_80405A74 **s) {
    s32 r = 0;
    if (s != NULL && *s != NULL) {
        r = 1;
    }
    return r;
}
inline s32 avail_80405A74(Strm_80405A74 **s) {
    s32 r = 0;
    if (valid_80405A74(s) && (*s)->len > 1) {
        r = 1;
    }
    return r;
}
inline s32 get_80405A74(Strm_80405A74 **s) {
    if (avail_80405A74(s)) {
        (*s)->len--;
        return *(*s)->buf++;
    }
    if (TLobby__sub_80401BCC(s, &ppp_input_byte, 1) != 1) {
        return -1;
    }
    return (s16)ppp_input_byte;
}
#define FWD_80405A74()                                                       \
    link->protocol_reject_count++;                                            \
    t = alloc_from_buffer(arg0, 4); \
    p = t->buf;                                                                \
    *p++ = 0xFF;                                                             \
    *p++ = 3;                                                                \
    write_network_u16_be(p, code);                                           \
    u = t;                                                                   \
    if (u == NULL) {                                                         \
        link->control_frame_allocation_errors++;                              \
        return;                                                              \
    }                                                                        \
    if (TLobby__sub_80401BCC(&u, &lobby_ppp_read_buf, 2) == 2) {                   \
        read_network_u16_be(&lobby_ppp_read_buf);                                 \
    }                                                                        \
    TLobby__sub_803FE6CC(G + 4, 8, 0, u);                                    \
    return;

struct LobbyNetBufferSlot {
    s16 active;
    u16 type;
};

struct LobbyNetBufferDesc {
    s16 handler;
    LobbyNetBufferSlot slots[2];
    s16 *used;
    u8 *bufs;
    s16 size;
    s16 count;
};

extern LobbyNetBufferDesc lobby_net_buffer_desc_b;
void TLobby__sub_80409818(s32 msg, s16 len, s16 idx, s16 arg3, u16 type);

void TLobby__sub_80402CE0(u8 *conn);
void TLobby__sub_803FC318(u8 *conn);
void TLobby__sub_803F9FAC(u8 *conn);
extern u8 *lbl_805D7ADC;

inline void open_conn_804062A0(void) {
    Lobby_804062A0 *l = (Lobby_804062A0 *)lbl_805C0038;

    if (l->state == 0) {
        l->state = 1;
    }
    TLobby__sub_803FD958(l->sub);
}

s16 TLobby__sub_804066D8(Strm_80405A74 *);
extern u32 lbl_805D7A90;
s32 TLobby__sub_804048E8(Obj_80403F4C *, Strm_80405A74 **, s16);

extern RecoveredGlobal_80401A68_lbl_805C04A8 lbl_805C04A8;
extern s16 lbl_805D7A8A;
extern u16 lbl_804FD3A8[];
extern s32 lbl_805D7A94;
s32 send_network_frame(u16, u8 *);
inline s32 acfc_804066D8(s32 lcp, u8 *ctx)
{
  s32 r = 1;
  if ((!lcp) && ((*((s16 *) (ctx + 0x50))) & 0x100))
  {
    r = 0;
  }
  return r;
}

struct Ent_80406B14 { s16 st; u8 pad[0x9c - 2]; };
struct Tbl_80406B14 { s16 count; Ent_80406B14 *list; };

u16 TUdpSocket__sub_80419864(void *, s16);

struct O_80406B6C { u32 w0; u8 b4; };

struct Tbl_80407310 { s16 count; NetPacket *list; };

void age_arp_cache(void);

typedef struct Ent_80407418 {
    s16 active;
    s16 a;
    s16 pad4;
    s16 b;
    u8 pad8[0x18];
} Ent_80407418;

typedef struct Tbl_80407418 {
    s16 pad0;
    s16 count;
    u8 pad4[0x10];
    Ent_80407418 *ents;
} Tbl_80407418;

s32 TLobby__sub_80408388(s16);

struct Node_80407C60 { Node_80407C60 *next; s16 used; u8 addr[4]; };
struct Peer_8040799C;
struct Conn_8040799C { Peer_8040799C *a; s16 f4; s16 f6; s16 f8; u8 padA[2]; u8 *fC; };
struct Peer_8040799C { s16 st; s16 f2; u8 pad4; u8 f5; u8 pad6[2]; Conn_8040799C *conn; u8 addr[6]; u8 name[6]; };
struct Ent_8040799C { s16 f0; s16 f2; s16 f4; s16 f6; s16 index; u16 hardware_type; u16 protocol_type; u8 fE; u8 fF; s16 status; u8 a12[6]; u8 a18[4]; Node_80407C60 *head; };
struct Tbl_8040799C { s16 count; s16 h2; s16 h4; s16 h6; s16 h8; s16 hA; s16 hC; u8 padE[2]; Peer_8040799C *list; Ent_8040799C *ents; Node_80407C60 *nodes; Conn_8040799C *bufs; u8 *pool; };
struct Out_8040799C { Conn_8040799C *a; void *b; void *c; void *d; void *e; };
void arp_hold_packet(Peer_8040799C *peer, NetPacket *pkt);
struct Ent_80408428;
struct Ent_80408428 *find_or_add_peer_entry__6TLobbyFssUcPvUcPvs(s16, s16, u8, void *, u8, void *, s16);

#define TBL ((Tbl_8040799C *)&lbl_805C1AB0)

typedef void (*Handler_8041A130)(s32, s16, s16, s16);
s32 register_protocol_handler__6TLobbyFUsi(u16 type, Handler_8041A130 fn);
s32 arp_handle_packet(void *, s16, s16, s16);

inline void clear_peer_conn_804078B4(Peer_8040799C *p) {
    if (p->conn != NULL) {
        p->conn->a = 0;
        p->conn->f6 = 0;
        p->conn->f4 = 0;
    }
}

inline Ent_8040799C *Lookup_8040799C(Tbl_8040799C *t, s16 idx) {
    Ent_8040799C *list = t->ents;
    s16 ok;
    if (idx >= 0 && idx < t->h2) {
        ok = 1;
    } else {
        ok = -1;
    }
    if (ok >= 0) {
        return &list[idx];
    }
    return NULL;
}

inline Peer_8040799C *Find_8040799C(Tbl_8040799C *t, u8 k, void *name) {
    s16 n = t->count;
    Peer_8040799C *p = t->list;
    for (; n > 0; n--, p++) {
        if (p->f5 == k && p->st != 0 && NetMemcmp(p->name, name, p->f5) == 0) {
            return p;
        }
    }
    return NULL;
}

inline void Clear_8040799C(Peer_8040799C *p) {
    if (p->conn != NULL) {
        p->conn->a = 0;
        p->conn->f6 = 0;
        p->conn->f4 = 0;
    }
}

inline void Send_8040799C(Ent_8040799C *e, void *name) {
    Out_8040799C o;
    void *r = alloc_packet_with_header__6TLobbyFPvPv((Out_804081C0 *)(&o), (u8 *)e);
    if (r != NULL) {
        o.a->f6 = 1;
        NetMemcpy(o.b, e->a12, e->fE);
        NetMemcpy(o.c, e->a18, e->fF);
        NetMemset(o.d, 0, e->fE);
        NetMemcpy(o.e, name, e->fF);
        TLobby::call_handler_by_index(e->f2, e->f6, 1, 0, (s32)r);
        if (r != NULL) {
            NetReleasePacket((NetPacket *)r);
        }
    }
}

inline Node_80407C60 *AllocNode_80407D98(Tbl_8040799C *t, s16 *count) {
    Node_80407C60 *p = t->nodes;
    s16 n = *count;
    for (; n > 0; n--, p++) {
        if (p->used == 0) {
            p->used = 1;
            p->next = NULL;
            NetMemset(p->addr, 0, 4);
            return p;
        }
    }
    return NULL;
}

s16 TLobby__sub_8040A044(s16, s32, s16, u8 *);
inline Ent_8040799C *findfree_80407F20(Ent_8040799C *base) {
    Ent_8040799C *p;
    s16 i;
    p = base;
    for (i = 0; i < TBL->h2; i++, p++) {
        if (p->f0 == 0) {
            return p;
        }
    }
    return NULL;
}

#undef TBL

typedef struct Node_804082AC { struct Node_804082AC *next; u8 pad4[2]; u8 f6[0x10]; } Node_804082AC;
typedef struct Ent_804082AC { u8 pad0[0xE]; u8 fE; u8 fF; u8 pad10[2]; u8 f12[6]; u8 f18[4]; Node_804082AC *f1C; } Ent_804082AC;
typedef struct Key_804082AC { u8 pad0[0x10]; void *f10; } Key_804082AC;
typedef struct Pool_804082AC { u8 pad0[8]; s16 f8; } Pool_804082AC;

struct Tbl_80408718;

struct ArpHeader { u16 hardware_type; u16 protocol_type; u8 hardware_length; u8 protocol_length; u16 op; };
s16 TLobby__sub_804082AC(Ent_804082AC *, Key_804082AC *, void *);
inline Ent_8040799C *FindHit_80407640(Tbl_8040799C *t, s16 b, s16 c) {
    Ent_8040799C *hit;
    s16 i;
    s16 n;
    if (b < 0) {
        return NULL;
    }
    hit = t->ents;
    n = t->h2;
    for (i = 0; i < n; i++, hit++) {
        if (hit->f0 == 1 && hit->f2 == b && hit->f6 == c) {
            return hit;
        }
    }
    return NULL;
}

inline s16 CheckPkt_80407640(ArpHeader *pkt, Ent_8040799C *hit) {
    if (NetMemcmp(pkt, &hit->hardware_type, 6) == 0) {
        if (pkt->op == 1 || pkt->op == 2) {
            return 1;
        }
    }
    return -1;
}

inline Peer_8040799C *FindPeer_80407640(Peer_8040799C *peer, s16 n, u8 ff, u8 *p2) {
    for (; n > 0; n--, peer++) {
        if (peer->f5 == ff && peer->st != 0 && NetMemcmp(peer->name, p2, peer->f5) == 0) {
            return peer;
        }
    }
    return 0;
}

typedef struct Node_80408388 {
    struct Node_80408388 *next;
    s16 used;
} Node_80408388;

typedef struct Ent_80408388 {
    u8 pad[0x1C];
    Node_80408388 *head;
} Ent_80408388;

typedef struct Tbl_80408388 {
    s16 pad0;
    s16 count;
    u8 pad4[0x10];
    Ent_80408388 *ents;
} Tbl_80408388;

typedef struct Sub_80408428 {
    s32 f0;
    s16 f4;
    s16 f6;
    u8 pad8[4];
    s32 fC;
} Sub_80408428;

typedef struct Ent_80408428 {
    s16 state;
    s16 stamp;
    u8 type4;
    u8 type5;
    u8 pad6[2];
    Sub_80408428 *sub;
    u8 addrC[6];
    u8 addr12[6];
} Ent_80408428;

typedef struct Tbl_80408428 {
    s16 count;
    u8 pad2[8];
    s16 stampA;
    u8 padC[4];
    Ent_80408428 *list;
} Tbl_80408428;

struct Ent_804086B4;
Ent_804086B4 *find_oldest_peer_entry__6TLobbyFs(s16 key);

inline Ent_80408428 *find_80408428(Tbl_80408428 *t, u8 type, void *addr) {
    s16 n = t->count;
    Ent_80408428 *e = t->list;
    while (n > 0) {
        if (e->type5 == type && e->state != 0 && NetMemcmp(e->addr12, addr, e->type5) == 0) {
            return e;
        }
        n--;
        e++;
    }
    return NULL;
}

inline void detach_80408428(Ent_80408428 *e) {
    if (e->sub != NULL) {
        e->sub->f0 = 0;
        e->sub->f6 = 0;
        e->sub->f4 = 0;
    }
    e->sub = NULL;
}

struct Ent_804086B4 { s16 f0; s16 f2; u8 pad[0x14]; };
struct Tbl_804086B4 { s16 count; u8 pad[0xE]; Ent_804086B4 *list; };

typedef void (*Fn_8040881C)(void);
typedef s16 (*Init_8040881C)(s16);

struct Desc_8040881C {
    Init_8040881C fn;
    u8 pad4[0x18];
};

struct Ent_8040881C {
    s16 used;
    s16 id;
    s16 idx;
    u8 pad6[0xA];
};

struct G_8040881C {
    s16 count;
    s16 n2;
    s16 n4;
    s16 n6;
    Desc_8040881C *descs;
    Ent_8040881C *ents;
    void *p10;
    void *p14;
};

s32 TLobby__sub_80408F2C(s16 id, u8 *pkt);
s32 TLobby__sub_80409130(s16 arg0, s16 arg1, s32 arg2);
s32 TLobby__sub_80408FD8(s16 idx, s16 op, u8 *addr);
s32 TLobby__sub_8040920C(s16 idx, u8 *mac);
s32 TLobby__sub_804092FC(s16 idx);
s32 TLobby__sub_8040939C(s16 idx);
s32 TLobby__sub_804093EC(s16 idx);
s16 TLobby__sub_804094B8(s16, u16, s16, void *);
s32 TLobby__sub_8040970C(s16 id, u8 *out);
struct Tbl_80408F2C;
#define LG_8040881C (*(G_8040881C *)&lbl_805C1AD8)
void TLobby__sub_803F8AB8(void *);

struct EtherRxBuffer {
    s16 used;
    s16 iface;
    s16 slot;
    s16 handler;
    s16 len;
    u8 data[0x5EE];
};
struct EtherProtocolBinding {
    s16 used;
    s16 handler;
    s16 iface;
    u16 ether_type;
    u8 pad8[4];
    EtherRxBuffer *buf;
};
struct EtherRxTable {
    u8 pad0[4];
    s16 nbindings;
    s16 nbufs;
    u8 pad8[8];
    EtherProtocolBinding *bindings;
    EtherRxBuffer *bufs;
};

inline EtherProtocolBinding *find_protocol_binding(EtherProtocolBinding *e, s16 n, s16 iface, u16 type) {
    for (; n > 0; n--, e++) {
        if (e->used != 0 && e->iface == iface && e->ether_type == type) {
            return e;
        }
    }
    return NULL;
}

inline EtherRxBuffer *alloc_rx_buffer(EtherRxBuffer *b, s16 n, s16 iface, s16 slot, s16 handler, s16 len) {
    for (; n > 0; n--, b++) {
        if (b->used == 0) {
            b->used = 1;
            b->iface = iface;
            b->slot = slot;
            b->handler = handler;
            b->len = len;
            return b;
        }
    }
    return NULL;
}

typedef s32 (*SendFn_80408C24)(s16, u8 *, s16);
typedef void (*CloseFn_80408C24)(s16, u16);
typedef s32 (*McastFn_80408C24)(s16, u8 *);
struct If_80408C24 { s16 (*init)(s16); s16 (*open)(s16, u16); CloseFn_80408C24 f8; McastFn_80408C24 fC; McastFn_80408C24 f10; s16 (*f14)(s16, u8 *); SendFn_80408C24 send; };
struct Conn_80408C24 { s16 used; s16 id; s16 handle; u8 mac[6]; u8 *buf; };
struct Ent_80408C24 { s16 used; s16 id; s16 iface; u16 type; s16 f8; u8 padA[2]; s32 fC; };
struct Glob_80408C24 {
    s16 f0;
    s16 nconn;
    s16 nent;
    s16 f6;
    If_80408C24 *ifaces;
    Conn_80408C24 *conns;
    Ent_80408C24 *ents;
};
struct Hdr_80408C24 { u8 dst[6]; u8 src[6]; u16 type; };

s16 TLobby__sub_804098B4(NetPacket *pkt);
s16 TLobby__sub_80409908(u8 *dst, NetPacket *pkt);
u8 *TLobby__sub_8042558C(u32 size);
struct Tbl_80408F2C;

inline Conn_80408C24 *find_conn_80408C24(Glob_80408C24 *g, s16 id) {
    Conn_80408C24 *c = g->conns;
    s16 n = g->nconn;
    for (; n > 0; n--, c++) {
        if (c->used != 0 && c->id == id) {
            return c;
        }
    }
    return NULL;
}

typedef char RecoveredGlobal_80409A3C_lbl_805C1C50_size[sizeof(RecoveredGlobal_80409A3C_lbl_805C1C50) == 0xF8 ? 1 : -1];

typedef struct Ent_80408E98 {
    s16 active;
    u8 pad2[4];
    u16 type;
    s16 sock;
    u8 padA[6];
} Ent_80408E98;

typedef struct Tbl_80408E98 {
    u8 pad0[4];
    s16 count;
    u8 pad6[0xA];
    Ent_80408E98 *ents;
} Tbl_80408E98;

#define TBL_80408E98 ((Tbl_80408E98 *)&lbl_805C1AD8)

#undef TBL_80408E98

typedef struct Buf_80408F2C {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    u8 data[0x5EE];
} Buf_80408F2C;

typedef struct Tbl_80408F2C {
    u8 pad0[4];
    s16 count;
    s16 nbufs;
    u8 pad8[0xC];
    Buf_80408F2C *bufs;
} Tbl_80408F2C;

typedef struct Sock_80409130 { s16 f0; u8 pad2[4]; u16 f6; s16 f8; u8 padA[6]; } Sock_80409130;

typedef struct Ent_80409818 {
    s16 active;
    u8 pad[0x22];
    void (*fn)(s16, s32);
    u8 pad28[0x8];
} Ent_80409818;

typedef struct Tbl_80409818 {
    s16 count;
    Ent_80409818 *ents;
} Tbl_80409818;

#define TBL_80409818 (*(Tbl_80409818 *)&lobby_handler_table_desc)

inline s16 packet_length_804098B4(NetPacket *pkt) {
    NetPacketFragment *f;
    s16 n;
    s16 total = 0;
    n = pkt->fragment_count;
    f = &pkt->fragments[n] - 1;
    for (; n > 0; n--) {
        total += f->length;
        f--;
    }
    if (total != (s16)pkt->total_bytes) {
        return total;
    }
    return pkt->total_bytes;
}

inline s16 copy_packet_80409908(u8 *dst, NetPacket *pkt) {
    NetBufferRef ref;
    NetPacketFragment *f;
    u8 *p;
    s16 n;
    s16 total = 0;
    n = pkt->fragment_count;
    p = dst;
    f = &pkt->fragments[n] - 1;
    for (; n > 0; n--) {
        NetBufferRefInitKind1(&ref, (s32)p);
        TLobby__sub_80406FD8(&ref, &pkt->fragments[n - 1].buffer, f->length);
        p += f->length;
        total += f->length;
        f--;
    }
    if (total != (s16)pkt->total_bytes) {
        return total;
    }
    return pkt->total_bytes;
}

#define TBL_804099B4 (*(Tbl_804099B4 *)&lobby_handler_table_desc)

s16 TLobby__sub_8040A2BC(Fn_8040881C *fns, s16 kind);

struct Rec_8040B33C { u32 f0; u8 addr[0x10]; };
struct A_8040B33C { u8 pad[0x10]; s16 idx; u8 pad2[2]; s16 off; };

struct D_8040A45C;
struct C_8040A45C { s16 f0; u8 pad2[2]; Rec_8040B33C f4; u16 record_type; u8 pad1A[2]; s32 f1C; C_8040A45C *f20; D_8040A45C *f24; };
struct D_8040A45C { s16 f0; u8 name[0x100]; s16 name_len; union { s8 f104; u8 canonical_name[0x100]; }; s16 f204; u8 pad206[2]; C_8040A45C *f208; };
struct E_8040A45C { s16 f0; u8 pad2[0x16]; s32 f18; union { u8 f1C; u8 wire_name[0x100]; }; };
struct Query_8040C09C;

struct G_8040A45C {
    s16 h0;
    s16 f2;
    s16 max_name;
    u8 pad6[6];
    s16 *fC;
    s16 nb;
    u8 pad12[2];
    Rec_8040B33C *b;
    s16 f18;
    s16 lim;
    s16 step;
    u8 pad1E[2];
    s32 base;
    s16 na;
    u8 pad26[2];
    DnsBuffer *a;
    s16 nc;
    s16 nd;
    s16 ne;
    u8 pad32[2];
    C_8040A45C *c;
    D_8040A45C *d;
    E_8040A45C *e;
    s16 nf;
    u8 pad42[2];
    DnsQuery *f;
};

extern G_8040A45C dns_resolver_state;

#define TBL_80409B48 (*(Tbl_80409B48 *)&lobby_handler_table_desc)

#define T_ (*(Tbl_80409AD8 *)&lobby_handler_table_desc)

#define TBL_80409BD4 (*(Tbl_80409BD4 *)&lobby_handler_table_desc)

typedef struct Ent_80409C5C {
    s16 active;
    s16 flags;
    u8 pad[0x20];
    s32 (*fn)(s32, s32);
    u8 pad2[0x8];
} Ent_80409C5C;

typedef struct Tbl_80409C5C {
    s16 count;
    Ent_80409C5C *ents;
} Tbl_80409C5C;

#define TBL_80409C5C (*(Tbl_80409C5C *)&lobby_handler_table_desc)

typedef struct Ent_80409CE0 {
    s16 active;
    s16 flags;
    u8 pad[0x1C];
    s32 (*fn)(s32, s32, s32);
    u8 pad2[0xC];
} Ent_80409CE0;

typedef struct Tbl_80409CE0 {
    s16 count;
    Ent_80409CE0 *ents;
} Tbl_80409CE0;

#define TBL_80409CE0 (*(Tbl_80409CE0 *)&lobby_handler_table_desc)

typedef struct Ent_80409D7C {
    s16 active;
    s16 flags;
    u8 pad[0x18];
    s32 (*fn)(s32, s32, s32);
    u8 pad2[0x10];
} Ent_80409D7C;

typedef struct Tbl_80409D7C {
    s16 count;
    Ent_80409D7C *ents;
} Tbl_80409D7C;

#define TBL_80409D7C (*(Tbl_80409D7C *)&lobby_handler_table_desc)

typedef struct Ent_80409E18 {
    s16 active;
    s16 flags;
    u8 pad[0x14];
    s32 (*fn)(s32, s32);
    u8 pad2[0x14];
} Ent_80409E18;

typedef struct Tbl_80409E18 {
    s16 count;
    Ent_80409E18 *ents;
} Tbl_80409E18;

#define TBL_80409E18 (*(Tbl_80409E18 *)&lobby_handler_table_desc)

typedef struct Ent_80409EB0 {
    s16 active;
    s16 flags;
    u8 pad[0x10];
    s32 (*fn)(s32);
    u8 pad2[0x18];
} Ent_80409EB0;

typedef struct Tbl_80409EB0 {
    s16 count;
    Ent_80409EB0 *ents;
} Tbl_80409EB0;

#define TBL_80409EB0 (*(Tbl_80409EB0 *)&lobby_handler_table_desc)

typedef struct Mgr_8040A3C0 {
    u8 pad[0x40];
    s16 count;
    u8 pad42[2];
    DnsQuery *ents;
} Mgr_8040A3C0;

void TLobby__sub_803F86BC(void *);
s32 TLobby__sub_80421844(s32 arg0);

typedef struct Ent_80409FC4 { s16 st; s16 pad2; s32 (*f4)(s32); s32 (*f8)(s32); s32 (*fC)(s16); s32 (*f10)(s32); u8 pad14[0x30-0x14]; } Ent_80409FC4;
typedef struct Tbl_80409FC4 { s16 count; Ent_80409FC4 *list; } Tbl_80409FC4;

typedef struct G_8040A630 { u8 pad[0x40]; s16 n; u8 pad2[2]; DnsQuery *p; } G_8040A630;

typedef struct Ent_8040A044 {
    s16 st;
    s16 f2;
    s32 (*f4)(s16, u8 *);
    s16 (*f8)(s16, s32, s16, u8 *);
    u8 padC[0x30 - 0xC];
} Ent_8040A044;
typedef struct Tbl_8040A044 { s16 count; Ent_8040A044 *list; } Tbl_8040A044;

struct Ent_8040A1FC { s16 f0; s16 f2; u8 pad[0x2C]; };
struct G_8040A1FC { s16 n; Ent_8040A1FC *p; };

struct Ent_8040A25C { s16 f0; s16 f2; u8 pad[0x2C]; };
struct G_8040A25C { s16 n; Ent_8040A25C *p; };

void TLobby__sub_804218AC(void (*)(void), int);

void TLobby__sub_8040C74C(DnsLookupRequest *);

typedef struct Rec_8040AD64 {
    u32 used;
    u8 pad[0x10];
} Rec_8040AD64;

typedef struct Mgr_8040AD64 {
    u8 pad[0x10];
    s16 n;
    u8 pad12[2];
    Rec_8040AD64 *recs;
    s16 f18;
} Mgr_8040AD64;

inline s32 compare_family_addr(u32 family, Rec_8040B33C *a, Rec_8040B33C *b) {
    switch (family) {
    case 4:
        if (b->f0 != 4) {
            return -1;
        }
        return NetMemcmp(a->addr, b->addr, 4);
    case 6:
        if (b->f0 != 6) {
            return -1;
        }
        return NetMemcmp(a->addr, b->addr, 0x10);
    default:
    case 0:
        return -1;
    }
}

typedef struct Conn_8040AF48 {
    s16 state;
    u8 pad[0x16];
    s32 timer;
    u8 pad1C[0x100];
} Conn_8040AF48;

typedef struct Mgr_8040AF48 {
    u8 pad[0x30];
    s16 nconns;
    u8 pad32[0xA];
    Conn_8040AF48 *conns;
} Mgr_8040AF48;

void TLobby__sub_8040AFE0(void);
void TLobby__sub_8040B3B4(void);
void reset_connection_requests__6TLobbyFPvs(Conn_8040AF48 *, s16);

struct UdpBuf_8040AFE0 {
    s16 len;
    u8 pad2[2];
    u8 *data;
};

Rec_8040B33C *find_next_active_record__6TLobbyFPv(A_8040B33C *a);
void TLobby__sub_8040BE40(DnsQuery *req, s16 err, s16 arg);
void TLobby__sub_8040B1C4(DnsQuery *req);
s16 TUdpSocket__sub_80421BAC(s32 h, u32 *src, u32 *dst, u16 port, u32 *opt, s8 n, UdpBuf_8040AFE0 *bufs);

Query_8040C09C *TLobby__sub_8040C09C(void);
s32 TLobby__sub_8040B4BC(s16, u8 *);
static inline D_8040A45C *find_host_8040A8B0(G_8040A45C *base, u8 *self, s32 len) {
    s16 j;
    D_8040A45C *p = base->d;
    for (j = 0; j < base->nd; j++, p++) {
        if (p->f0 == 1 && NetMemcmp(p->name, self, len) == 0) {
            return p;
        }
    }
    return NULL;
}
static inline DnsBuffer *grab_slot_8040A8B0(G_8040A45C *base) {
    s16 i;
    DnsBuffer *p = base->a;
    for (i = 0; i < base->na; i++, p++) {
        if (p->used == 0) {
            p->used = 1;
            return p;
        }
    }
    return NULL;
}
static inline Rec_8040B33C *dns_server_for_attempt(G_8040A45C *state,
        DnsQuery *query, s16 count, s16 &attempt) {
    Rec_8040B33C *server = &state->b[(query->server + (attempt = query->status)) % count];
    return server;
}

static inline Rec_8040B33C *select_dns_lookup_server(G_8040A45C *state, DnsQuery *query) {
    s16 attempt, count, i;
    for (i = 0; i < (count = state->nb); i++) {
        Rec_8040B33C *server = dns_server_for_attempt(state, query, count, attempt);
        if (server->f0 != 0) {
            if (attempt < state->lim) {
                return server;
            }
            break;
        }
        query->status = attempt + 1;
    }
    return NULL;
}

inline void put_tag_8040AFE0(DnsQuery *req, s16 tag) {
    NetMemcpy(req->message->data + req->message->len - 4, &tag, 2);
}

inline s16 send_8040AFE0(DnsQuery *req, Rec_8040B33C *rec) {
    UdpBuf_8040AFE0 buf;
    s16 r;
    u32 *dst = (u32 *)rec;

    buf.len = req->message->len;
    buf.data = req->message->data;
    r = TUdpSocket__sub_80421BAC(req->socket, NULL, dst, 0, NULL, 1, &buf);
    put_tag_8040AFE0(req, 0x1C);
    return r;
}

inline Rec_8040B33C *fnar_8040B1C4(G_8040A45C *g, DnsQuery *a) {
    s16 t, n, i;
    for (i = 0; i < (n = g->nb); i++) {
        Rec_8040B33C *r = &g->b[(a->server + (t = a->status)) % n];
        if (r->f0 != 0) {
            if (t < g->lim) {
                return r;
            }
            break;
        }
        a->status = t + 1;
    }
    return 0;
}

void TLobby__sub_8040C178(Query_8040C09C *q, s16 arg1);

typedef struct Mgr_8040B654 {
    u8 pad[0x40];
    s16 count;
    u8 pad42[2];
    DnsQuery *ents;
} Mgr_8040B654;

inline DnsQuery *find_8040B654(s16 id) {
    Mgr_8040B654 *g = (Mgr_8040B654 *)&dns_resolver_state;
    s16 n;
    DnsQuery *e;
    s16 i;

    e = g->ents;
    n = g->count;
    for (i = 0; i < n; i++, e++) {
        if (e->active == 1 && id == e->socket) {
            return e;
        }
    }
    return NULL;
}

s16 TLobby__sub_8040B8BC(DnsQuery *req);

struct UdpRx_8040B4BC { s16 sock; s16 len; s32 buf; u8 pad8[0x28]; u16 port; };

inline DnsBuffer *alloc_rx_8040B4BC(G_8040A45C *g) {
    s16 i;
    DnsBuffer *a = g->a;
    for (i = 0; i < g->na; i++, a++) {
        if (a->used == 0) {
            a->used = 1;
            return a;
        }
    }
    return NULL;
}

inline DnsQuery *find_req_8040B4BC(s16 id) {
    Mgr_8040B654 *g = (Mgr_8040B654 *)&dns_resolver_state;
    DnsQuery *e = g->ents;
    s16 i;

    for (i = 0; i < g->count; i++, e++) {
        if (e->active == 1 && id == e->socket) {
            return e;
        }
    }
    return NULL;
}

void TLobby__sub_8040BE40(DnsQuery *req, s16 err, s16 arg);

s32 TLobby__sub_8040BA38(DnsQuery *, u8 *, s32);

inline void reset_requests_8040BE40(E_8040A45C *o, s16 arg) {
    G_8040A45C *g = &dns_resolver_state;
    s16 i;
    DnsQuery *e;

    o->f0 = 0;
    o->f18 = 0;
    o->f1C = 0;
    i = 0;
    e = g->f;
    while (i < g->nf) {
        if (e->req.ptr.entry == o) {
            e->status = -0x42;
            e->outstanding = 0;
            e->req.ptr.entry = NULL;
            NetDispatchRequestCallback((DnsQuery *)e, arg);
        }
        i++;
        e++;
    }
}

struct N_8040C4B0 { u8 pad0[0x20]; N_8040C4B0 *next; };
struct O_8040C4B0 { u8 pad0[0x204]; s16 count; u8 pad206[2]; N_8040C4B0 *head; };
struct G_8040C4B0 { u8 pad0[0x2C]; s16 lim; };

inline s32 close_8040BF38(DnsQuery *p, s32 id) {
    s32 r;
    if ((s16)id < 0) {
        return 0;
    }
    r = TLobby__sub_80421B3C(id);
    p->socket = -1;
    return r;
}

struct O_8040C00C { s16 f0; u8 pad2[0x16]; s32 f18; u8 f1C; };

struct G_8040C00C { u8 pad0[0x40]; s16 count; u8 pad42[2]; DnsQuery *ents; };

#define g ((G_8040C00C *)&dns_resolver_state)
#define o ((O_8040C00C *)o_)

#undef g
#undef o

struct Node_8040C09C { s16 f0; u8 pad2[0x1A]; s32 f1C; Node_8040C09C *next; };
struct Query_8040C09C { s16 f0; u8 pad2[0x102]; u8 f104; u8 pad105[0xFF]; s16 f204; u8 pad206[2]; Node_8040C09C *f208; };

struct G_8040C09C {
    u8 pad0[0x2C];
    s16 nnodes;
    s16 nqueries;
    u8 pad30[8];
    Query_8040C09C *queries;
    u8 pad3C[4];
    s16 nents;
    u8 pad42[2];
    DnsQuery *ents;
};

void TLobby__sub_8040C178(Query_8040C09C *q, s16 arg1);

#define g ((G_8040C09C *)&dns_resolver_state)

#undef g

struct DnsRrHeader { u16 type; u16 rclass; s32 ttl; u16 rdlength; };
s32 append_to_list__6TLobbyFPvPv(O_8040C4B0 *, N_8040C4B0 *);
inline C_8040A45C *find_8040BA38(D_8040A45C *obj, C_8040A45C *rec) {
    s16 cnt;
    C_8040A45C *node;
    if (obj == 0 || rec == 0) {
        return 0;
    }
    for (node = obj->f208, cnt = 0; node != 0 && cnt < dns_resolver_state.nc; node = node->f20, cnt++) {
        if (TLobby__sub_8040C9E0((u8 *)node, (u8 *)rec) == 0) {
            return node;
        }
    }
    return 0;
}

/* DNS requests use the same native connection prefix and callback slot. */

void TLobby__sub_8040C74C(DnsLookupRequest *a);
s16 TLobby__sub_8040C8A8(u8 *dst, u8 *src, s16 max);
s16 TLobby__sub_8040C978(u8 *name);

struct Icmp4Header {
    u8 type;
    u8 code;
    u16 checksum;
    u32 rest;
};

struct Icmp6MessageHeader {
    u8 type;
    u8 code;
    u16 checksum;
};
struct Ipv6SendOptions;

struct Icmp6ErrorInfo {
    u8 type;
    u8 code;
    u16 checksum;
    s32 pointer;
};
struct Ipv6Header_8040D120 {
    u32 version_class_flow;
    u16 payload_length;
    u8 next_header;
    u8 hop_limit;
    IPv6Address src;
    IPv6Address dst;
};
struct UdpHeader {
    u16 src_port;
    u16 dst_port;
    u16 length;
    u16 checksum;
};

struct Ent_8040D95C { u8 pad0[2]; s16 f2; u8 pad4[2]; s16 f6; u8 pad8[4]; s32 fC; };
struct In_8040D95C { s32 type; s32 f4; };
struct Out_8040D95C { s32 type; u32 f4; };
s32 ipv4_source_for_subnet(u32 *out, u32 dst, s16 idx);
s32 TLobby__sub_80411F1C(u8 *, u8 *, s16);

typedef char RecoveredGlobal_8040EF00_lbl_805C1B60_size[sizeof(RecoveredGlobal_8040EF00_lbl_805C1B60) == 0x18 ? 1 : -1];

typedef char Ipv4ProtocolState_header_offset[(offsetof(Ipv4ProtocolState, header) == 0x0C) ? 1 : -1];
typedef char Ipv4ProtocolState_size[sizeof(Ipv4ProtocolState) == 0x28 ? 1 : -1];

typedef void (*Handler_8041A130)(s32, s16, s16, s16);
s32 register_protocol_handler__6TLobbyFUsi(u16 type, Handler_8041A130 fn);
s32 TUdpSocket__sub_8040DE4C(u8 *, s16, s16);

typedef char RecoveredGlobal_8040ED28_lbl_805C1B60_size[sizeof(RecoveredGlobal_8040ED28_lbl_805C1B60) == 0x18 ? 1 : -1];

struct PH_8040EC38 { s32 src; s32 dst; u8 zero; s8 proto; u16 len; };
struct P_8040EC38 { u8 pad0[8]; s32 f8; s16 fC; };

u16 TUdpSocket__sub_80419864(void *buf, s16 len);

typedef char RecoveredGlobal_8040ED70_lbl_805C1B60_size[sizeof(RecoveredGlobal_8040ED70_lbl_805C1B60) == 0x18 ? 1 : -1];

struct Ipv4Route {
    u16 flags;
    s16 iface;
    u32 dst;
    u32 mask;
    u32 gateway;
    s16 f10;
    s16 type;
};
struct Ipv4Alias {
    s16 f0;
    u8 pad2[2];
    u32 addr;
    u32 broadcast;
    u32 network;
    u32 mask;
    Ipv4Alias *next;
};
struct Ipv4Iface {
    s16 state;
    s16 handle;
    s16 f4;
    u8 pad6[2];
    u32 addr;
    u32 broadcast;
    u32 network;
    u32 mask;
    Ipv4Alias *aliases;
};
struct Ipv4RoutingState {
    s16 nroutes;
    s16 nifaces;
    s16 max_aliases;
    s16 f6;
    Ipv4Route *routes;
    Ipv4Iface *ifaces;
};
struct Ipv4IfaceAddrRecord {
    s32 kind;
    u32 addr;
    u32 mask;
    u32 broadcast;
    u8 pad10[0xC];
};

inline s16 is_iface_destination_8040EDE4(s16 idx, u32 dst) {
    Ipv4Iface *ifc = (Ipv4Iface *)TLobby::get_active_entry_by_index(idx);

    if (ifc == NULL) {
        return 0;
    }
    if (ifc->addr == 0 || dst == 0xFFFFFFFF || dst == ifc->broadcast) {
        return 1;
    }
    return 0;
}

s32 ipv4_send_to_interface(s32, u32, s16);

s32 ipv4_send_to_interface(s32, u32, s16);

struct A_80418BD8;
struct O_80420DE4;
s32 TUdpSocket__sub_80418BD8(A_80418BD8 *);
s32 TLobby__sub_80418C40(u8 *, u16, s16, u8, u32, u8 *, u16, u8, s16);
s32 TLobby__sub_8041B974(u8 *, u8 *, u8 *);
s32 TLobby__sub_80421AD8(u8 *, s32, s32, u32, s32);

// Select a source on the destination's subnet from an interface or its aliases.
// The existing IPv4 table view is provisional; original class ownership is unknown.
// Conditional assignments and separate candidate locals retain the native register allocation.

inline s16 get_iface_addr_8040F1A0(s16 *n, Ipv4Iface **ifaces, u32 *addr) {
    if (*n <= 0) {
        return 0;
    }
    if ((*ifaces)->state != 1) {
        return 0;
    }
    *addr = (*ifaces)->addr;
    return 1;
}

s16 TRKValidMemory32(u32, u32, u32, s16, u8, u16);

inline void remove_host_route_8040F1A0(Ipv4RoutingState *g, u32 dst, u32 gateway) {
    s16 i;
    Ipv4Route *e;

    e = g->routes;

    for (i = 0; i < g->nroutes; i++, e++) {
        if ((e->flags & 1) && e->dst == dst && e->gateway == gateway && (e->type & 1) == 1) {
            e->flags = 0;
            return;
        }
    }
}

s16 TRKValidMemory32(u32, u32, u32, s16, u8, u16);

s16 TRKValidMemory32(u32, u32, u32, s16, u8, u16);

struct Ent_8040F9CC { u16 flags; u8 pad2[2]; u32 dst; u8 pad8[4]; u32 gateway; u8 pad10[2]; s16 type; };
struct G_8040F9CC { s16 count; u8 pad2[6]; Ent_8040F9CC *ents; };

inline s16 find_iface_by_addr_8040FA48(Ipv4Iface *ifaces, s16 n, s16 m, u32 addr) {
    s16 i;
    s16 j;
    Ipv4Iface *ifc;
    Ipv4Alias *a;

    ifc = ifaces;

    for (i = 0; i < n; i++, ifc++) {
        if (ifc->state == 1) {
            if (ifc->addr == addr) {
                return i;
            }
            for (a = ifc->aliases, j = 0; a != NULL && j < m; j++) {
                if (a->addr == addr) {
                    return i;
                }
                a = a->next;
            }
        }
    }
    return -1;
}

inline s16 find_iface_by_network_8040FA48(Ipv4Iface *ifaces, s16 n, s16 m, u32 addr) {
    s16 i;
    s16 j;
    Ipv4Iface *ifc;
    Ipv4Alias *a;

    ifc = ifaces;

    for (i = 0; i < n; i++, ifc++) {
        if (ifc->state == 1) {
            if (ifc->network == (ifc->mask & addr)) {
                return i;
            }
            for (a = ifc->aliases, j = 0; a != NULL && j < m; j++) {
                if (a->network == (a->mask & addr)) {
                    return i;
                }
                a = a->next;
            }
        }
    }
    return -1;
}

inline Ipv4Iface *get_ifaces_8040FA48(Ipv4RoutingState *g) {
    return g->ifaces;
}

struct A_RT { u8 pad0[4]; u32 addr; u8 pad8[8]; u32 mask; A_RT *next; };
struct E_RT { s16 state; u8 pad2[6]; u32 addr; u8 padC[8]; u32 mask; A_RT *alias; };
struct G_RT { s16 f0; s16 count; s16 maxalias; u8 pad6[6]; E_RT *ents; };

struct Ent_8040FDA0 { s16 state; u8 pad2[6]; u32 f8; u32 fC; u8 pad10[0xC]; };
struct G_8040FDA0 { s16 f0; s16 count; u8 pad4[8]; Ent_8040FDA0 *ents; };

typedef char RecoveredGlobal_8040FE40_lbl_805C1B60_size[sizeof(RecoveredGlobal_8040FE40_lbl_805C1B60) == 0x18 ? 1 : -1];

typedef char RecoveredGlobal_8040FE9C_lbl_805C1B60_size[sizeof(RecoveredGlobal_8040FE9C_lbl_805C1B60) == 0x18 ? 1 : -1];

typedef char RecoveredGlobal_8041123C_lbl_805C1BB8_size[sizeof(RecoveredGlobal_8041123C_lbl_805C1BB8) == 0x28 ? 1 : -1];

typedef char RecoveredGlobal_804112B8_lbl_805C1BB8_size[sizeof(RecoveredGlobal_804112B8_lbl_805C1BB8) == 0x28 ? 1 : -1];

typedef char RecoveredGlobal_80411ECC_lbl_805C1BB8_size[sizeof(RecoveredGlobal_80411ECC_lbl_805C1BB8) == 0x28 ? 1 : -1];

typedef char RecoveredGlobal_8040FF0C_lbl_805C1B78_size[sizeof(RecoveredGlobal_8040FF0C_lbl_805C1B78) == 0x40 ? 1 : -1];

s32 TLobby__sub_8040FFF8(u8 *, int, s16);

s16 TLobby__sub_8040D510(Icmp6ErrorInfo *err, u8 *hdr, s16 len, s16 idx);

struct O_80421938;
s32 TLobby__sub_80421938(O_80421938 *, void *, void *, void *, s32);
s16 TLobby__sub_804105E0(u8 *, u8 *, s16, s16);
s16 TLobby__sub_80415D0C(NetPacket *, u8 *, NetIPv6SendParameters *, s16);
s16 TLobby__sub_80410BA8(NetPacket *, NetIPv6SendParameters *, s16, void *);
s16 TLobby__sub_80410A98(NetPacket *, u8 *, u8 *, Ipv6SendOptions *, s32);
inline s16 process_options_header(u8 *p, s16 rem, u8 *ip, s16 m, s16 id) {
    s16 TLobby__sub_80410958(u8 *, s16, u8 *, s16, s16);
    s32 n;
    u8 *d;
    d = p + 2;
    n = ((p[1] + 1) << 3) - 2;
    if ((s16)n > rem) {
        return -1;
    }
    if (TLobby__sub_80410958(d, n, ip, m, id) < 0) {
        return -1;
    }
    return 0;
}

inline s32 min_8040FFF8(s32 a, s32 b) {
    if (a < b) {
        return a;
    }
    return b;
}

inline NetPacket *buildrec_8040FFF8(u8 *ip, s16 m, u8 *p, s32 rem) {
    NetPacket *rec = TLobby::alloc_free_entry();
    if (rec == 0) {
        return 0;
    }
    rec->fragment_count = 0;
    rec->total_bytes = m;
    rec->fragments[rec->fragment_count].length = m - rem;
    NetBufferRefInitKind1(&rec->fragments[rec->fragment_count].buffer, (s32)ip);
    rec->fragment_count += 1;
    rec->fragments[rec->fragment_count].length = (u16)rem;
    NetBufferRefInitKind1(&rec->fragments[rec->fragment_count].buffer, (s32)p);
    rec->fragment_count += 1;
    return rec;
}

struct Ipv6Route {
    u8 pad0[2];
    s16 type;
    u8 pad4[2];
    s16 iface;
    u8 pad8[0x10];
    u8 gateway[16];
};
static inline s16 chk_804105E0(u8 *p, s16 lim, s16 ctx, s16 l, s16 rem, u8 *q, u8 *prev) {
    Icmp6ErrorInfo err4;
    if (l != rem + 0x28) {
        err4.type = 4;
        err4.code = 1;
        err4.pointer = prev - p;
        TLobby__sub_8040D510(&err4, p, lim, ctx);
        return -1;
    }
    return process_options_header(q, rem, p, lim, ctx);
}

struct Ipv6SendOptions {
    u8 traffic_class;
    u8 pad1[3];
    u32 flow_label;
    u8 hop_limit;
    u8 pad9[3];
};

struct Ipv6FragmentHeader {
    u8 next_header;
    u8 reserved;
    u16 offset_flags;
    u32 ident;
};

s16 TLobby__sub_80411C44(IPv6Address *addr, s16 idx);
s16 TLobby__sub_80410D6C(NetPacket *pkt, Ipv6Header *hdr, s16 iface, void *opts, u32 room);

inline s16 get_mtu_80410BA8(IPv6Address *dst, s16 iface) {
    return TLobby__sub_80411C44(dst, iface);
}

struct PH_80411040 { IPv6Address src; IPv6Address dst; u32 len; u8 zero[3]; u8 next_header; };

void TLobby__sub_80411334(void);

struct G_8041118C {
    s16 n0; s16 n1; s16 n2; u8 pad6[0xE]; s16 n14; u8 pad16[2];
    void *p18; void *p1C; void *p20; void *p24;
};

#define g ((G_8041118C *)&ipv6_address_routing_state)

#undef g

struct Ipv6NdAddr {
    s16 f0;
    u8 addr[16];
    s16 prefix_len;
    s16 state;
    s16 f16;
    s16 f18;
    u16 scope;
    s16 dad_count;
    s16 dad_timer;
    u32 f20;
    u32 f24;
    Ipv6NdAddr *next;
};
struct Ipv6NdIface {
    s16 state;
    s16 f2;
    u8 addr[16];
    s16 prefix_len;
    s16 dad_state;
    s16 f18;
    s16 f1A;
    s16 scope;
    s16 dad_count;
    s16 dad_timer;
    s16 rs_count;
    s16 rs_timer;
    s16 mtu;
    void *f28;
    Ipv6NdAddr *addrs;
};
struct Ipv6NdRoute;
struct Ipv6NdState {
    s16 route_count;
    s16 count;
    s16 max_addrs;
    s16 dad_timer_init;
    s16 dad_count_init;
    s16 dad_interval;
    s16 rs_timer_init;
    s16 rs_count_init;
    s16 rs_interval;
    s16 min_mtu;
    u8 pad14[4];
    Ipv6NdRoute *routes;
    Ipv6NdIface *ifaces;
    Ipv6NdAddr *addr_pool;
    void *pmtu;
};
struct Ipv6NdEvent {
    u8 *addr;
    s16 prefix_len;
};
struct Ipv6NdAddressRefEvent {
    u8 *addr;
};

struct Ipv6NdRoute {
    s16 state;
    s16 type;
    u8 pad4[2];
    s16 iface;
    u8 prefix[16];
    u8 gateway[16];
    s16 prefix_len;
};
void TLobby__sub_80414B98(u8 *, s16, u8 *);
inline s16 cmp16_80411604(void *a, void *b) {
    s32 t = NetMemcmp(a, b, 16);
    if (t < 0) {
        return -1;
    }
    if (t > 0) {
        return 1;
    }
    return 0;
}

inline void remove_80411604(Ipv6NdState *g, s16 len, u8 *addr, void *src) {
    u8 grp[16];
    s16 n;
    Ipv6NdRoute *e;
    TLobby__sub_80414B98(grp, len, addr);
    n = g->route_count;
    e = g->routes;
    for (; n > 0; n--, e++) {
        if (e->state == 1 && e->prefix_len == len && cmp16_80411604(e->prefix, grp) == 0 && cmp16_80411604(e->gateway, src) == 0) {
            e->state = 0;
            return;
        }
    }
}

struct Ent_80411BE8 { s16 f0; u8 pad[0x12]; s16 f14; };
struct G_80411BE8 { u8 pad[0x14]; s16 n; u8 pad2[0xE]; Ent_80411BE8 *p; };

struct Ent_80411DEC { s16 state; IPv6Address addr; s16 mtu; s16 timer; };
struct Iface_80411C44 { u8 pad0[0x26]; s16 mtu; u8 pad28[8]; };
struct G_80411DEC { u8 pad0[0x14]; s16 count; s16 lifetime; u8 pad18[4]; Iface_80411C44 *ifaces; u8 pad20[4]; Ent_80411DEC *ents; };

inline s16 is_link_local_80411C44(const IPv6Address *a) {
    u8 b;

    if (a->bytes[0] != 0xFE) {
        return 0;
    }
    b = a->bytes[1];
    if (!(b & 0x80) || (b & 0x40)) {
        return 0;
    }
    return 1;
}

inline s16 compare_addr_80411C44(const IPv6Address *a, const IPv6Address *b) {
    s32 r = NetMemcmp(a, b, sizeof(IPv6Address));

    if (r < 0) {
        return -1;
    } else if (r > 0) {
        return 1;
    }
    return 0;
}

inline Iface_80411C44 *iface_80411C44(G_80411DEC *g, s16 idx) {
    return &g->ifaces[idx];
}

s16 TLobby__sub_80414218(u8 *, u8 *);

struct Ipv6AddrNode {
    s16 f0;
    u8 addr[16];
    s16 f12;
    s16 f14;
    s16 f16;
    s16 f18;
    s16 scope;
    u8 pad1C[0xC];
    Ipv6AddrNode *next;
};
struct Ipv6Iface {
    s16 state;
    s16 f2;
    u8 addr[16];
    s16 f14;
    s16 f16;
    s16 f18;
    s16 f1A;
    s16 scope;
    u8 pad1E[0xE];
    Ipv6AddrNode *nodes;
};
struct Ipv6AddressState {
    s16 f0;
    s16 count;
    s16 max_nodes;
    u8 pad6[0x16];
    Ipv6Iface *ifaces;
};

struct Ent_80412210 {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    u8 f8[16];
    u8 f18[16];
    s16 f28;
};
struct Grp_80412210 {
    s16 f0;
    u8 f2[16];
    s16 f12;
    u8 p14[0x14];
    Grp_80412210 *f28;
};
struct If_80412210 {
    s16 f0;
    s16 f2;
    u8 f4[16];
    s16 f14;
    u8 p16[0x10];
    s16 f26;
    s32 f28;
    Grp_80412210 *f2c;
};
struct G_80412210 {
    s16 f0;
    s16 f2;
    s16 f4;
    u8 p6[0x12];
    Ent_80412210 *table;
    If_80412210 *ifs;
};

void TLobby__sub_80414B98(u8 *, s16, u8 *);

#define G ((G_80412210 *)&ipv6_address_routing_state)

s32 TLobby__sub_8041347C(u8 *, s16, u8 *, s16, s16, s16);
inline s16 cmp16_80412618(void *a, void *b) {
    s32 t = NetMemcmp(a, b, 16);
    if (t < 0) {
        return -1;
    }
    if (t > 0) {
        return 1;
    }
    return 0;
}

inline s16 getaddr_80412618(s16 *n, u8 **ents, void *out) {
    if (*n <= 0) {
        return 0;
    }
    if (*(s16 *)*ents != 1) {
        return 0;
    }
    NetMemcpy(out, *ents + 4, 16);
    return 1;
}

inline void remove_80412618(Ipv6NdState *g, s16 len, u8 *addr, void *src) {
    u8 grp[16];
    s16 n;
    Ipv6NdRoute *e;
    TLobby__sub_80414B98(grp, len, addr);
    n = g->route_count;
    e = g->routes;
    for (; n > 0; n--, e++) {
        if (e->state == 1 && e->prefix_len == len && cmp16_80412618(e->prefix, grp) == 0 && cmp16_80412618(e->gateway, src) == 0) {
            e->state = 0;
            return;
        }
    }
}

s32 NetIPv6GetAddressScopeClass(u8 *);

s32 NetCompareBitsBackward(u8 *, u8 *, s16);
inline s16 cmp16_80412CA4(void *a, void *b) {
    s32 t = NetMemcmp(a, b, 16);
    if (t < 0) {
        return -1;
    }
    if (t > 0) {
        return 1;
    }
    return 0;
}

inline s16 getaddr_80412CA4(s16 *n, Ipv6NdIface **ents, void *out) {
    if (*n <= 0) return 0;
    if ((*ents)->state != 1) return 0;
    NetMemcpy(out, (*ents)->addr, 16);
    return 1;
}

inline void remove_80412CA4(Ipv6NdState *g, s16 len, void *grp, void *src) {
    s16 n = g->route_count;
    Ipv6NdRoute *e = g->routes;
    for (; n > 0; n--, e++) {
        if (e->state == 1 && e->prefix_len == len && cmp16_80412CA4(e->prefix, grp) == 0 && cmp16_80412CA4(e->gateway, src) == 0) {
            e->state = 0;
            return;
        }
    }
}

inline s16 cmp_80412210(void *a, void *b) {
    s32 r = NetMemcmp(a, b, 16);
    if (r < 0) {
        return -1;
    }
    if (r > 0) {
        return 1;
    }
    return 0;
}

inline s16 getaddr_80412210(s16 *n, If_80412210 **ifs, void *out) {
    if (*n <= 0) {
        return 0;
    }
    if ((*ifs)->f0 != 1) {
        return 0;
    }
    NetMemcpy(out, (*ifs)->f4, 16);
    return 1;
}

inline void remove_80412210(G_80412210 *g, void *grp, void *src) {
    s16 n = g->f0;
    Ent_80412210 *e = g->table;
    for (; n > 0; n--, e++) {
        if (e->f0 == 1 && e->f28 == 0x80 && cmp_80412210(e->f8, grp) == 0 && cmp_80412210(e->f18, src) == 0) {
            e->f0 = 0;
            return;
        }
    }
}

#undef G

struct Ipv6PrefixRoute {
    s16 state;
    s16 type;
    u8 pad4[2];
    s16 iface;
    u8 prefix[16];
    u8 gateway[16];
    s16 prefix_len;
};
struct Ipv6RouteTable {
    s16 count;
    u8 pad2[0x16];
    Ipv6PrefixRoute *routes;
};

inline s16 is_multicast_80413264(const IPv6Address *a) {
    if (a->bytes[0] == 0xFF) {
        return 1;
    }
    return 0;
}

inline Ipv6PrefixRoute *routes_80413264(Ipv6RouteTable *g) {
    return g->routes;
}

inline s16 is_link_local_8041347C(u8 *a) {
    if (a[0] != 0xFE) {
        return 0;
    }
    if (!(a[1] & 0x80) || (a[1] & 0x40)) {
        return 0;
    }
    return 1;
}

inline s16 addr_cmp_804136EC(void *a, void *b) {
    s32 r = NetMemcmp(a, b, 16);
    if (r < 0) {
        return -1;
    }
    if (r > 0) {
        return 1;
    }
    return 0;
}

inline s16 is_multicast_804136EC(u8 *a) {
    if (a[0] == 0xFF) {
        return 1;
    }
    return 0;
}

inline s16 is_link_local_804136EC(u8 *a) {
    u8 b;

    if (a[0] != 0xFE) {
        return 0;
    }
    b = a[1];
    if (!(b & 0x80) || (b & 0x40)) {
        return 0;
    }
    return 1;
}

inline Ipv6Iface *get_iface_804136EC(Ipv6AddressState *g, s16 idx) {
    Ipv6Iface *ifc;

    if (idx < 0 || idx >= g->count) {
        return NULL;
    }
    ifc = g->ifaces;
    ifc += idx;
    if (ifc->state != 1) {
        return NULL;
    }
    return ifc;
}

inline Ipv6Iface *lookup_iface_804136EC(Ipv6AddressState *g, s16 idx) {
    return get_iface_804136EC(g, idx);
}

typedef char RecoveredGlobal_8041471C_lbl_805C1BB8_size[sizeof(RecoveredGlobal_8041471C_lbl_805C1BB8) == 0x28 ? 1 : -1];

struct RecoveredFields_804143BC_arg0 {
    u8 field_0;
    u8 field_1;
};
typedef char RecoveredFields_804143BC_arg0_0_offset[offsetof(RecoveredFields_804143BC_arg0, field_0) == 0x0 ? 1 : -1];
typedef char RecoveredFields_804143BC_arg0_1_offset[offsetof(RecoveredFields_804143BC_arg0, field_1) == 0x1 ? 1 : -1];

typedef struct Ent_80414504 { s16 state; s16 f2; u8 pad[0x2C]; } Ent_80414504;
typedef struct Mgr_80414504 {
    s16 a;
    s16 count;
    u8 pad4[0x18];
    Ent_80414504 *ents;
} Mgr_80414504;

inline Ent_80414504 *find_80414504(s16 id) {
    Mgr_80414504 *g;
    Ent_80414504 *e;

    if (id < 0 || id >= (g = (Mgr_80414504 *)&ipv6_address_routing_state)->count) {
        return NULL;
    }
    e = g->ents;
    e += id;
    if (e->state != 1) {
        return NULL;
    }
    return e;
}

#define G_ (*(G_8041509C *)&network_loopback_state)

void TLobby__sub_80409818(s32 msg, s16 len, s16 idx, s16 arg3, u16 type);

struct Proto_80415230 { s16 used; u16 type; };
struct G_80415230 {
    s16 handler;
    Proto_80415230 protos[2];
    s16 slot_size;
    s16 slot_count;
    u8 padE[2];
    s16 *slot_used;
    u8 *slots;
};

s32 TLobby__sub_80415230(s16 idx, s16 mode, u8 *addr, NetPacket *pkt);
s32 TLobby__sub_80415320(s16 idx, u8 *addr, NetPacket *pkt);
s32 TLobby__sub_80415410(s16 idx, u8 *pkt);

typedef char RecoveredGlobal_8041552C_lbl_805C1BE0_size[sizeof(RecoveredGlobal_8041552C_lbl_805C1BE0) == 0x18 ? 1 : -1];

struct E_80415558 { s16 a; s16 b; };
struct G_80415558 { s16 h; E_80415558 e[2]; };

struct E_8041559C { s16 a; s16 b; };
struct G_8041559C { s16 h; E_8041559C e[2]; };

typedef char Pool_80415690_size[sizeof(Pool_80415690) == 0x10 ? 1 : -1];

void TLobby__sub_803F8D84(u32 key);

struct A_80415B38 { s8 c0; s8 c1; s8 c2; s8 c3; u8 pad4[0x30]; s32 off; };
struct C_80415B38 { s8 c0; s8 c1; s8 c2; s8 c3; u8 pad4[2]; s16 f6; u8 pad8[0x1C]; };
struct B_80415B38 {
    s8 c0;
    s8 c1;
    s8 c2;
    s8 c3;
    u8 pad4[4];
    s16 id;
    u8 padA[2];
    u8 flags;
    u8 padD[3];
    A_80415B38 *link;
    u8 pad14[2];
    u8 addr[0x10];
    s16 f26;
    u8 pad28[0x20];
};
struct G_80415B38 {
    s16 na;
    s16 nb;
    s16 nc;
    u8 pad6[2];
    A_80415B38 *a;
    B_80415B38 *b;
    C_80415B38 *c;
    s16 stride;
    u8 pad16[2];
    s32 base;
    s16 f1C;
    s16 f1E;
    s16 f20;
    s16 f22;
    s16 maxage;
    s16 reachable_time;
    s16 retrans_timer;
    s16 f2A;
    s16 f2C;
    u8 pad2E[2];
};
extern G_80415B38 ipv6_neighbor_discovery_state;

struct Arg2_80415B38 { u8 *addr; u8 *val; };
typedef struct Ent_80418670 { u8 pad0[3]; u8 f3; u8 pad4[2]; s16 f6; u8 pad8[0xC]; u8 f14[0x10]; } Ent_80418670;
s32 TLobby__sub_80411604(s16, int, void *);
Ent_80418670 *NetIPv6SelectDefaultRouter(void *arg0);

typedef struct Rtr_8041615C {
    u8 pad0[3];
    u8 state;
    s16 id;
    s16 f6;
    s16 lifetime;
    u8 padA[0xA];
    u8 addr[0x10];
} Rtr_8041615C;
typedef struct Nbr_8041615C {
    u8 pad0[3];
    u8 state;
    u8 pad4[8];
    u8 flags;
    u8 padD[9];
    u8 addr[0x10];
    u8 pad26[0x22];
} Nbr_8041615C;
typedef struct G_8041615C {
    s16 f0;
    s16 nnbr;
    s16 nrtr;
    u8 pad6[6];
    Nbr_8041615C *nbrs;
    Rtr_8041615C *rtrs;
} G_8041615C;

inline u8 *find_nbr_8041615C(G_8041615C *g, u8 *addr) {
    s16 n = g->nnbr;
    Nbr_8041615C *nb = g->nbrs;
    for (; n > 0; n--, nb++) {
        if (nb->state == 1 && NetMemcmp(nb->addr, addr, 0x10) == 0) {
            return (u8 *)nb;
        }
    }
    return NULL;
}

typedef struct Sub_804162A4 { u8 pad0[3]; u8 state; s16 count; } Sub_804162A4;
typedef struct Ent_804162A4 {
    u8 pad0[3];
    u8 state;
    s16 phase;
    u8 pad6[2];
    s16 id;
    s16 timer;
    u8 flags;
    u8 padD[3];
    Sub_804162A4 *sub;
    s16 tries;
    u8 name[0x10];
    s16 f26;
    u8 pad28[0x20];
} Ent_804162A4;
typedef struct Glob_804162A4 {
    u8 pad0[2];
    s16 count;
    u8 pad4[8];
    Ent_804162A4 *ents;
    u8 pad10[0xC];
    s16 maxTries0;
    s16 maxTries1;
    u8 pad20[4];
    s16 delay1;
    u8 pad26[2];
    s16 delay;
} Glob_804162A4;
typedef struct Arg_804162A4 { u8 *p; s32 v; } Arg_804162A4;
s16 NetIPv6EmitNeighborSolicitation(NetPacket *packet, u8 *target, NetIPv6SendParameters *params,
                                 s16 iface, u8 *link_address);
s16 NetIPv6SendMulticastNeighborProbe(u8 *arg0);
s16 NetIPv6SendUnicastNeighborProbe(u8 *arg0);

struct Redirect_80416508 {
    NetIcmpv6Header header;
    IPv6Address target;
    IPv6Address dest;
};
struct Arg_80416508 {
    u8 *dest;
    s16 id;
    u8 *router;
    u8 *target;
};

struct Ent_80416678 {
    u8 pad0[3];
    u8 used;
    s16 kind;
    s16 state;
    s16 iface;
    s16 age;
    union { u8 flags; u8 fC; };
    u8 padD[3];
    Q_804179A4 *pending;
    s16 probes;
    u8 addr[0x10];
    s16 klen;
    u8 key[0x20];
};

u8 *TLobby__sub_80406F0C(void *);

struct Peer_80416994 { u8 pad0[3]; u8 state; u8 pad4[2]; s16 f6; u8 pad8[0x14 - 0x8]; u8 name[0x10]; };
struct Sub_80416994 { u8 pad0[3]; u8 state; u8 pad4[4]; u8 addr[0x30 - 0x8]; s16 port; u8 pad32[2]; s32 val; };
struct Ent_80416994 {
    u8 pad0[3];
    u8 state;
    s16 phase;
    u8 pad6[2];
    s16 f8;
    s16 timer;
    u8 flags;
    u8 padD[3];
    Sub_80416994 *sub;
    u8 pad14[2];
    u8 name[0x10];
    s16 len;
    u8 data[0x48 - 0x28];
};
struct Glob_80416994 {
    u8 pad0[2];
    s16 count;
    s16 count2;
    u8 pad6[0xC - 6];
    Ent_80416994 *ents;
    Peer_80416994 *peers;
    u8 pad14[0x24 - 0x14];
    s16 delay2;
    s16 delay1;
};
struct Msg_80416994 { u8 pad0[4]; u8 flags; u8 pad5[3]; u8 name[0x10]; };
struct Item_80416994 { s16 port; u8 pad2[2]; u8 val[8]; };
struct Pkt_80416994 { u8 pad0[4]; s32 n; s32 port; Item_80416994 items[1]; };
struct Arg_80416994 { u8 *p; s32 v; };

inline Ent_80416994 *FindEnt_80416994(Glob_80416994 *g, void *name) {
    s16 n = g->count;
    Ent_80416994 *e = g->ents;
    for (; n > 0; n--, e++) {
        if (e->state == 1 && NetMemcmp(e->name, name, 0x10) == 0) {
            return e;
        }
    }
    return 0;
}

inline void ClearPeer_80416994(Peer_80416994 *p) {
    p->state = 0;
    p->f6 = 0;
}

inline Peer_80416994 *ScanPeers_80416994(Glob_80416994 *g, void *name) {
    s16 m;
    Peer_80416994 *p;
    Peer_80416994 *hit;
    hit = 0;
    m = g->count2;
    p = g->peers;
    for (; m > 0; m--, p++) {
        if (p->state == 1) {
            if (NetMemcmp(p->name, name, 0x10) == 0) {
                ClearPeer_80416994(p);
            } else {
                hit = p;
            }
        }
    }
    return hit;
}

s16 TLobby__sub_80417294(NetPacketFragment *, s32, u8 *, s16);

/* Neighbour discovery option 3 (prefix information, 32 bytes): a router advertisement's on-link prefix. */
typedef struct Ipv6NdPrefixInfoOption {
    u8 type;
    u8 length;
    u8 prefix_len;
    u8 flags;
    s32 valid_lifetime;
    s32 preferred_lifetime;
    u8 reserved[4];
    IPv6Address prefix;
} Ipv6NdPrefixInfoOption;
typedef char Ipv6NdPrefixInfoOption_size_check[sizeof(Ipv6NdPrefixInfoOption) == 0x20 ? 1 : -1];

/* Neighbour discovery option 5 (MTU, 8 bytes). */
typedef struct Ipv6NdMtuOption {
    u8 type;
    u8 length;
    u16 reserved;
    s32 mtu;
} Ipv6NdMtuOption;
typedef char Ipv6NdMtuOption_size_check[sizeof(Ipv6NdMtuOption) == 8 ? 1 : -1];

/* Event 2: a prefix information option, passed on to TLobby__sub_80412618. */
typedef struct Ipv6NdPrefixEvent {
    u8 *prefix;
    s16 prefix_len;
    s32 preferred_lifetime;
    s32 valid_lifetime;
} Ipv6NdPrefixEvent;
typedef char Ipv6NdPrefixEvent_size_check[sizeof(Ipv6NdPrefixEvent) == 0x10 ? 1 : -1];

/* Event 4: an MTU option; TLobby__sub_80411604 stores mtu in the interface. */
typedef struct Ipv6NdMtuEvent {
    u8 *router;
    s32 mtu;
} Ipv6NdMtuEvent;
typedef char Ipv6NdMtuEvent_size_check[sizeof(Ipv6NdMtuEvent) == 8 ? 1 : -1];

Ent_80416678 *TLobby__sub_804182DC(void *, void *, s16, s16);

typedef struct Ra_80418734 { u8 pad0[4]; u8 cur_hop_limit; u8 pad5; s16 router_lifetime; u32 reachable_time; u32 retrans_timer; } Ra_80418734;
typedef struct Rtr_80418734 { u8 pad0[3]; u8 state; s16 id; s16 f6; s16 lifetime; u8 padA[2]; s32 reachable_time; s32 retrans_timer; u8 addr[0x10]; } Rtr_80418734;
typedef struct Ipv6NdAddrEvent {
    u8 *addr;
    u8 *next_router;
} Ipv6NdAddrEvent;
typedef char Ipv6NdAddrEvent_size_check[sizeof(Ipv6NdAddrEvent) == 8 ? 1 : -1];

/* Event 3: a router advertisement's current hop limit. */
typedef struct Ipv6NdHopLimitEvent {
    u8 *router;
    u8 hop_limit;
} Ipv6NdHopLimitEvent;
typedef char Ipv6NdHopLimitEvent_size_check[sizeof(Ipv6NdHopLimitEvent) == 8 ? 1 : -1];

s32 TLobby__sub_80418734(u8 *, Ra_80418734 *, s16);
inline Rtr_80418734 *FindPeer2_80417494(s16 *cnt, Rtr_80418734 **list, void *name) {
    s16 n = *cnt;
    Rtr_80418734 *p = *list;
    for (; n > 0; n--, p++) {
        if (p->state == 1 && NetMemcmp(p->addr, name, 0x10) == 0) {
            return p;
        }
    }
    return 0;
}

inline Rtr_80418734 *ScanPeers2_80417494(s16 *cnt, Rtr_80418734 **list, void *name) {
    s16 m;
    Rtr_80418734 *p;
    Rtr_80418734 *hit;
    hit = 0;
    m = *cnt;
    p = *list;
    for (; m > 0; m--, p++) {
        if (p->state == 1) {
            if (NetMemcmp(p->addr, name, 0x10) == 0) {
                p->state = 0;
                p->f6 = 0;
            } else {
                hit = p;
            }
        }
    }
    return hit;
}

typedef struct Hdr_804177A0 {
    s16 len;
    u8 pad[2];
    u8 data[8];
} Hdr_804177A0;

typedef struct Arg_80417D1C { u8 *p; s32 v; } Arg_80417D1C;
s16 TLobby__sub_804137FC(u8 *, s16);

struct G_80415B38;

typedef struct Arg_80417E60 { u8 *p; s32 v; } Arg_80417E60;

typedef Ent_80416678 E_804184DC;

typedef char Layout_pointer_size[sizeof(void *) == 4 ? 1 : -1];
typedef char Layout_word_size[sizeof(u32) == 4 ? 1 : -1];
typedef char Layout_NetBufferRef_size[sizeof(NetBufferRef) == 8 ? 1 : -1];
typedef char Layout_NetBufferRef_kind[offsetof(NetBufferRef, kind) == 4 ? 1 : -1];
typedef char Layout_NetBufferRef_value[offsetof(NetBufferRef, value) == 0 ? 1 : -1];
typedef char Layout_IPv6Address_size[sizeof(IPv6Address) == 16 ? 1 : -1];
typedef char Layout_IPv6Address_bytes[offsetof(IPv6Address, bytes) == 0 ? 1 : -1];
typedef char Layout_IPv6NeighborSolicitation_size[sizeof(IPv6NeighborSolicitation) == 24 ? 1 : -1];
typedef char Layout_IPv6NeighborSolicitation_header[offsetof(IPv6NeighborSolicitation, header) == 0 ? 1 : -1];
typedef char Layout_IPv6NeighborSolicitation_target[offsetof(IPv6NeighborSolicitation, target) == 8 ? 1 : -1];
typedef char Layout_NetPacketFragment_size[sizeof(NetPacketFragment) == 12 ? 1 : -1];
typedef char Layout_NetPacketFragment_buffer[offsetof(NetPacketFragment, buffer) == 4 ? 1 : -1];
typedef char Layout_NetPacketFragment_length[offsetof(NetPacketFragment, length) == 0 ? 1 : -1];
typedef char Layout_NetPacket_size[sizeof(NetPacket) == 156 ? 1 : -1];
typedef char Layout_NetPacket_fragment_count[offsetof(NetPacket, fragment_count) == 4 ? 1 : -1];
typedef char Layout_NetPacket_fragments[offsetof(NetPacket, fragments) == 12 ? 1 : -1];
typedef char Layout_NetPacket_in_use[offsetof(NetPacket, in_use) == 0 ? 1 : -1];
typedef char Layout_NetPacket_total_bytes[offsetof(NetPacket, total_bytes) == 8 ? 1 : -1];
typedef char Layout_NetIPv6SendParameters_size[sizeof(NetIPv6SendParameters) == 40 ? 1 : -1];
typedef char Layout_NetIPv6SendParameters_destination[offsetof(NetIPv6SendParameters, destination) == 16 ? 1 : -1];
typedef char Layout_NetIPv6SendParameters_flow_label[offsetof(NetIPv6SendParameters, flow_label) == 32 ? 1 : -1];
typedef char Layout_NetIPv6SendParameters_hop_limit[offsetof(NetIPv6SendParameters, hop_limit) == 38 ? 1 : -1];
typedef char Layout_NetIPv6SendParameters_next_header[offsetof(NetIPv6SendParameters, next_header) == 39 ? 1 : -1];
typedef char Layout_NetIPv6SendParameters_source[offsetof(NetIPv6SendParameters, source) == 0 ? 1 : -1];
typedef char Layout_NetIPv6SendParameters_traffic_class_bits[offsetof(NetIPv6SendParameters, traffic_class_bits) == 36 ? 1 : -1];
typedef char Layout_NetLinkLayerAddressBuffer_size[sizeof(NetLinkLayerAddressBuffer) == 32 ? 1 : -1];
typedef char Layout_NetLinkLayerAddressBuffer_bytes[offsetof(NetLinkLayerAddressBuffer, bytes) == 0 ? 1 : -1];
typedef char Layout_NetSourceLinkLayerOption_size[sizeof(NetSourceLinkLayerOption) == 34 ? 1 : -1];
typedef char Layout_NetSourceLinkLayerOption_address[offsetof(NetSourceLinkLayerOption, address) == 2 ? 1 : -1];
typedef char Layout_NetSourceLinkLayerOption_length_units[offsetof(NetSourceLinkLayerOption, length_units) == 1 ? 1 : -1];
typedef char Layout_NetSourceLinkLayerOption_type[offsetof(NetSourceLinkLayerOption, type) == 0 ? 1 : -1];
typedef char Layout_NetIcmpv6Header_size[sizeof(NetIcmpv6Header) == 8 ? 1 : -1];
typedef char Layout_NetIcmpv6Header_checksum[offsetof(NetIcmpv6Header, checksum) == 2 ? 1 : -1];
typedef char Layout_NetIcmpv6Header_code[offsetof(NetIcmpv6Header, code) == 1 ? 1 : -1];
typedef char Layout_NetIcmpv6Header_reserved[offsetof(NetIcmpv6Header, reserved) == 4 ? 1 : -1];
typedef char Layout_NetIcmpv6Header_type[offsetof(NetIcmpv6Header, type) == 0 ? 1 : -1];
typedef char Layout_NetIcmpv6NeighborSolicitation_size[sizeof(NetIcmpv6NeighborSolicitation) == 24 ? 1 : -1];
typedef char Layout_NetIcmpv6NeighborSolicitation_header[offsetof(NetIcmpv6NeighborSolicitation, header) == 0 ? 1 : -1];
typedef char Layout_NetIcmpv6NeighborSolicitation_target[offsetof(NetIcmpv6NeighborSolicitation, target) == 8 ? 1 : -1];
typedef char Layout_NetIcmpv6RouterSolicitation_size[sizeof(NetIcmpv6RouterSolicitation) == 8 ? 1 : -1];
typedef char Layout_NetIcmpv6RouterSolicitation_header[offsetof(NetIcmpv6RouterSolicitation, header) == 0 ? 1 : -1];

E_804184DC *NetIPv6FindOrSelectNeighborCacheEntry(u8 *, u8 *, s16);
inline s32 notify_804182DC(E_804184DC *e) {
    NetPacket *nw;
    nw = TLobby::alloc_free_entry();
    if (nw == 0) {
        return (s32)e;
    }
    nw->fragment_count = 0;
    nw->total_bytes = e->pending->f30;
    nw->fragments[nw->fragment_count].length = e->pending->f30;
    NetBufferRefInitKind1(&nw->fragments[nw->fragment_count].buffer, (s32)e->pending->f34);
    nw->fragment_count++;
    TLobby__sub_80410BA8(nw, (NetIPv6SendParameters *)e->pending->f8, e->iface, e->key);
    NetReleasePacket(nw);
    return 1;
}

typedef struct G_80418670 { u8 pad0[4]; s16 f4; u8 pad6[0xA]; Ent_80418670 *f10; } G_80418670;

typedef struct G_80418734 { u8 pad0[4]; s16 nrtr; u8 pad6[0xA]; Rtr_80418734 *rtrs; u8 pad14[0x10]; s16 maxage; s16 reachable_time; s16 retrans_timer; s16 f2A; } G_80418734;

struct Ent_804188E4 { u8 pad0[3]; u8 f3; s16 f4; u8 pad6[0x32]; };
struct Rec_804188E4 { u8 pad0[3]; u8 f3; u8 pad4[0xC]; Ent_804188E4 *f10; u8 pad14[0x34]; };
struct G_804188E4 { s16 n0; s16 n2; u8 pad4[4]; Ent_804188E4 *e8; Rec_804188E4 *rC; u8 pad10[0x14]; s16 f24; };
inline Rec_804188E4 *find_804188E4(G_804188E4 *g, Ent_804188E4 *e) {
    s16 n = g->n2;
    Rec_804188E4 *r = g->rC;
    while (n > 0) {
        if (r->f3 == 1 && r->f10 == e) {
            return r;
        }
        n--;
        r++;
    }
    return NULL;
}

struct A_80418ACC { s8 c0; s8 c1; s8 c2; s8 c3; s16 f4; u8 pad6[0x2E]; };
struct B_80418ACC { s8 c0; s8 c1; s8 c2; s8 c3; s16 f4; u8 pad6[0x12]; };
struct G_80418ACC {
    s16 na;
    s16 nb;
    u8 pad4[4];
    A_80418ACC *a;
    B_80418ACC *b;
    s32 f10;
    s32 f14;
};
extern G_80418ACC packet_fragment_pool_state;

struct E_80418BD8 { u8 pad[0xC]; };
struct A_80418BD8 { u8 pad[4]; u32 n; u8 pad2[8]; E_80418BD8 e[1]; };

struct N_80419258 { u8 pad0[4]; s16 f4; u8 pad6[2]; O_80406B6C o; u16 f10; u16 f12; N_80419258 *next; };
struct Addr_80419258 { s32 family; u8 data[0x10]; };
struct E_80419258 { u8 pad0[4]; s16 f4; u8 pad6[2]; Addr_80419258 addr; u32 port; u16 f20; u8 f22; u8 f23; s16 f24; u8 pad26[2]; E_80419258 *next; N_80419258 *list; N_80419258 *f30; };
struct G_80419258 { s16 count; s16 sub; s16 max_frags; u8 pad6[2]; E_80419258 *ents; N_80419258 *frags; E_80419258 *head; E_80419258 *tail; };
s16 TLobby__sub_80419374(E_80419258 *e);

E_80419258 *TLobby__sub_8041955C(u8 *, s32, u8);
s32 TLobby__sub_80419470(u8 *, u32);
s32 TLobby__sub_80418D7C(E_80419258 *, u8 *, u16, u16, u16, u8, s16);

s32 TLobby__sub_8041979C(void);
inline N_80419258 *take_80418D7C(N_80419258 **pb, s16 *pn) {
    s16 n;
    s16 i;
    N_80419258 *ent;
    ent = *pb;
    n = *pn;
    for (i = 0; i < n; i++) {
        if (ent->f4 == 0) {
            ent->f4 = 1;
            ent->f10 = 0;
            ent->f12 = 0;
            ent->next = 0;
            return ent;
        }
        ent++;
    }
    return 0;
}
inline s16 contig_80418D7C(E_80419258 *node, s16 *pn, G_80419258 *g) {
    s16 lim;
    N_80419258 *f;
    u32 acc;
    s16 n;
    s16 cnt;
    acc = 0;
    f = node->list;
    cnt = *pn;
    n = 0;
    lim = g->max_frags;
    while (f != 0 && cnt > 0) {
        if (f->f10 != (u16)acc) {
            return -1;
        }
        n++;
        if (n > lim) {
            return -1;
        }
        acc += f->f12 / 8;
        cnt--;
        f = f->next;
    }
    return 0;
}
/* Adds a fragment (frag_off in 8-byte units; more = the more-fragments flag) to node; returns the reassembled
   packet once every fragment is there, else 0. f starts the insertion search at the second fragment, then walks
   the fragments being copied. pkt holds the chain's last fragment until the packet is allocated. */

struct IcmpError_80419374 {
    u8 type;
    u8 code;
    u16 checksum;
    u32 unused;
};

s32 TLobby__sub_8041979C(void);

inline E_80419258 *alloc_entry_8041955C(G_80419258 *g) {
    E_80419258 *e = ((G_80419258 *)&packet_fragment_pool_state)->ents;
    s16 n = g->count;
    s16 i;

    for (i = 0; i < n; i++, e++) {
        if (e->f4 == 0) {
            e->f4 = 1;
            e->f20 = 0;
            e->port = 0;
            NetMemset(&e->addr, 0, sizeof(e->addr));
            e->f22 = 0;
            e->f23 = 0;
            e->next = NULL;
            e->f30 = NULL;
            e->list = NULL;
            return e;
        }
    }
    return NULL;
}

struct N_804196EC { u8 pad0[4]; s16 f4; u8 pad6[2]; O_80406B6C o; u8 pad10[4]; N_804196EC *next; };
struct E_804196EC { u8 pad0[4]; s16 f4; u8 pad6[0x1E]; s16 f24; u8 pad26[2]; s32 f28; N_804196EC *list; u8 pad30[4]; };
struct G_804196EC { s16 count; u8 pad2[6]; E_804196EC *ents; u8 padC[4]; E_804196EC *p10; E_804196EC *p14; };

s32 TLobby__sub_80406B6C(O_80406B6C *o);

struct G_8041979C { s16 count; s16 sub; u8 pad4[4]; E_80419258 *ents; N_80419258 *nodes; E_80419258 *head; E_80419258 *tail; };

typedef char OriginalBss_805C1AF0_size[(sizeof(G_8040A45C) == 0x48) ? 1 : -1];
typedef char OriginalBss_805C1B38_size[(sizeof(Ipv4ProtocolState) == 0x28) ? 1 : -1];
typedef char OriginalBss_805C1B60_size[(sizeof(RecoveredGlobal_8040EF00_lbl_805C1B60) == 0x18) ? 1 : -1];
typedef char OriginalBss_805C1B78_size[(sizeof(RecoveredGlobal_8040FF0C_lbl_805C1B78) == 0x40) ? 1 : -1];
typedef char OriginalBss_805C1BB8_size[(sizeof(RecoveredGlobal_8041123C_lbl_805C1BB8) == 0x28) ? 1 : -1];
typedef char OriginalBss_805C1BE0_size[(sizeof(RecoveredGlobal_8041552C_lbl_805C1BE0) == 0x18) ? 1 : -1];
typedef char OriginalBss_805C1BF8_size[(sizeof(Pool_80415690) == 0x10) ? 1 : -1];
typedef char OriginalBss_805C1C08_size[(sizeof(G_80415B38) == 0x30) ? 1 : -1];
extern G_8040A45C dns_resolver_state;
extern Ipv4ProtocolState ipv4_protocol_state;
extern RecoveredGlobal_8040EF00_lbl_805C1B60 ipv4_address_routing_state;
extern RecoveredGlobal_8040FF0C_lbl_805C1B78 ipv6_protocol_state;
extern RecoveredGlobal_8041123C_lbl_805C1BB8 ipv6_address_routing_state;
extern RecoveredGlobal_8041552C_lbl_805C1BE0 network_loopback_state;
extern Pool_80415690 network_buffer_pool_state;
extern G_80415B38 ipv6_neighbor_discovery_state;

typedef char OriginalBss_805C1C38_size[(sizeof(G_80418ACC) == 0x18) ? 1 : -1];
typedef char OriginalBss_805C1C50_size[(sizeof(NetworkDispatchState) == 0xF8) ? 1 : -1];
typedef char OriginalBss_805C1D48_size[(sizeof(RecoveredGlobal_8041E178_lbl_805C1D48) == 0xA8) ? 1 : -1];
extern G_80418ACC packet_fragment_pool_state;

// Kind 2 packs entry/segment indices above an unsigned byte offset.
// Keep both offsets live through the native 32-bit address additions.

s16 NetIPv6HandleIcmpMessage(NetPacket *, u8 *, u8 *, u8, s16);
s32 TLobby__sub_8040B838(u8 *, u8 *, s32);
s32 TLobby__sub_8040BD40(DnsQuery *, u8 *, s32, u8 *);
C_8040A45C *TLobby__sub_8040C248(D_8040A45C *);
s32 TLobby__sub_80409CE0(s16, s32, s32, s32);
s32 TLobby__sub_80409D7C(s16, s32, s32, s32);
s32 TLobby__sub_80409E18(s16, s32, s32);
s32 TLobby__sub_80409EB0(s16, s32);
s32 TLobby__sub_8040A0C0(s16, u8 *);
s16 TLobby__sub_8040C340(D_8040A45C *, C_8040A45C *);
s16 TUdpSocket__sub_8040E354(u8 *, u32, u8 *, s16, s16);
s32 NetIPv6FindTargetLinkLayerAddressOption(u8 *, s32, u8 **, s16 *);
s16 NetIPv6ApplyNeighborAdvertisement(Msg_80416994 *, u8 *, s16, s32, s32, s16);
}

/* Option bits of LcpVals.mask (bit N = LCP option type N). */
#define LCP_OPT_ACCM (1 << 2)
#define LCP_OPT_PFC (1 << 7)
#define LCP_OPT_ACFC (1 << 8)

/* LCP option values; mask has bit N set for option type N. */
typedef struct LcpVals {
    s16 mask;
    s16 mru;
    u32 accm;
    u16 auth_proto;
    u8 pad0A[2];
    u32 magic;
    u8 pad10[4];
    u8 chap_alg;
    u8 f15;
    u8 pad16[2];
} LcpVals;
typedef char LcpVals_size_check[sizeof(LcpVals) == 0x18 ? 1 : -1];

/* One side of the LCP negotiation: the options wanted and the ones agreed. */
typedef struct LcpSide {
    s16 mask;
    u8 pad2[2];
    LcpVals want;
    LcpVals got;
} LcpSide;
typedef char LcpSide_size_check[sizeof(LcpSide) == 0x34 ? 1 : -1];

/* The LCP options object (fsm->p30, lbl_805C0400's opts). */
typedef struct LcpOpts {
    LcpSide local;
    LcpSide remote;
} LcpOpts;
typedef char LcpOpts_size_check[sizeof(LcpOpts) == 0x68 ? 1 : -1];

typedef struct RecoveredGlobal_80401A68_lbl_805C04A8 RecoveredGlobal_80401A68_lbl_805C04A8;
#endif
