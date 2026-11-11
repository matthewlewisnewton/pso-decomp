#ifndef PSO_NETWORK_DHCPCLIENT_H
#define PSO_NETWORK_DHCPCLIENT_H

#include "types.h"
#include <stddef.h>

// RFC 951 BOOTP header; the DHCP magic cookie precedes the option bytes.
struct BootpPacket {
    u8 op;
    u8 htype;
    u8 hlen;
    u8 hops;
    u32 xid;
    u16 secs;
    u16 flags;
    s32 ciaddr;
    u32 yiaddr;
    u32 siaddr;
    u32 giaddr;
    u8 chaddr[16];
    u8 sname[64];
    u8 file[128];
    u32 cookie;
};

typedef char BootpPacket_size[sizeof(BootpPacket) == 0xF0 ? 1 : -1];
typedef char BootpPacket_flags[offsetof(BootpPacket, flags) == 0xA ? 1 : -1];
typedef char BootpPacket_ciaddr[offsetof(BootpPacket, ciaddr) == 0xC ? 1 : -1];
typedef char BootpPacket_chaddr[offsetof(BootpPacket, chaddr) == 0x1C ? 1 : -1];
typedef char BootpPacket_cookie[offsetof(BootpPacket, cookie) == 0xEC ? 1 : -1];

struct DhcpMessage {
    BootpPacket hdr;
    u8 options[0x5DC - sizeof(BootpPacket)];
    s32 build_release();
    s32 build_request();
    s32 build_discover();
};

typedef char DhcpMessage_size[sizeof(DhcpMessage) == 0x5DC ? 1 : -1];

// The UDP callback receives into scratch, then copies accepted replies into
// reply. Each region owns one 1500-byte message (0x804249F0 / 0x80424A48).
struct DhcpClientBuffers {
    DhcpMessage outgoing;
    DhcpMessage reply;
    DhcpMessage received;
};

typedef char DhcpClientBuffers_outgoing[offsetof(DhcpClientBuffers, outgoing) == 0 ? 1 : -1];
typedef char DhcpClientBuffers_reply[offsetof(DhcpClientBuffers, reply) == 0x5DC ? 1 : -1];
typedef char DhcpClientBuffers_received[offsetof(DhcpClientBuffers, received) == 0xBB8 ? 1 : -1];
typedef char DhcpClientBuffers_size[sizeof(DhcpClientBuffers) == 0x1194 ? 1 : -1];

// Reads the DHCP magic cookie followed by lease/renewal/rebinding options.
// The byte record starts at the cookie. The existing scanner has no input
// length; this interface does not add bounds validation.
extern "C" void dhcp_parse_lease_times(u8 *cookie_and_options);

// Native callers consume a word-sized option length (0..255).
// Zero also reports no match.
// The scanner still receives no packet length.
extern "C" s32 find_dhcp_option__6TLobbyFPvUcPv(u8 *cookie_and_options, u8 tag, u8 **value);

// Returns 0 for a known option ID, -1 otherwise. The legacy setter copies the
// table's fixed size; len controls string termination or clearing, not a bound.
extern "C" s32 TLobby__sub_80425288(s16 id, s16 len, void *value);

// Copies the lease/renewal/rebinding words to optional borrowed destinations.
// In active states the result stays zero even when option diagnostics are set.
extern "C" s16 TLobby__sub_8042474C(s32 *lease, s32 *renew, s32 *rebind);

// Reply configuration writes one address, subnet-mask and broadcast word.
extern "C" s16 TLobby__sub_80424D58(s16 iface, s32 arg1, s32 arg2, void *arg3,
                                   s32 *address, s32 *netmask, s32 *broadcast, s32 arg7);
extern "C" s32 TLobby__sub_80424DCC(s16 iface, s32 arg1, s32 arg2, void *arg3,
                                   s32 *address, s32 *netmask, s32 *broadcast, s32 arg7);

extern s32 *lbl_805D7B40;
extern s32 *lbl_805D7B44;
extern s32 *lbl_805D7B48;
extern DhcpClientBuffers lbl_805C1E00;
extern volatile s32 dhcp_state;
extern volatile s32 lbl_805D7B0C;
extern volatile s32 dhcp_reply_received;

#endif
