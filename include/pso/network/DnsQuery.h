// DNS layout adapted from zeroz41/pso-decomp (MIT); see third_party/README.md.
#ifndef PSO_NETWORK_DNS_QUERY_H
#define PSO_NETWORK_DNS_QUERY_H

#include "types.h"
#include "pso/network/UdpRuntime.h"
#include <stddef.h>

struct D_8040A45C;
struct E_8040A45C;

struct DnsBuffer {
    s16 used;
    s16 len;
    u8 *data;
};

typedef void (*DnsLookupCallback)(s16 index, NetworkAddress *addrs, s16 naddrs,
    u8 *cname, s16 cname_len);
typedef void (*DnsPtrCallback)(s16 index, u8 *name, s16 len);

struct DnsLookupRequest {
    u32 family; // 0: AAAA then A; 4: A; 6: AAAA.
    NetworkAddress *addrs;
    s16 naddrs;
    u8 pad0a[2];
    u8 *cname;
    s16 cname_len;
    u8 pad12[2];
    DnsLookupCallback cb;
    D_8040A45C *host;
};

struct DnsPtrRequest {
    u8 *name;
    s16 len;
    u8 pad06[2];
    DnsPtrCallback cb;
    E_8040A45C *entry;
};

struct DnsQuery {
    s16 active;
    s16 index;
    s16 socket; // -1 when no UDP socket is open.
    u16 id; // DNS wire transaction ID.
    s16 kind; // 1: name lookup; 12: PTR lookup.
    s16 timer; // Seconds until the next retry.
    u32 waiter; // Waiting thread, or 0xffffffff.
    s16 status; // Nonnegative attempt count, or a negative terminal error.
    s16 outstanding;
    s16 server; // First server index; attempts advance relative to it.
    u8 pad16[2];
    DnsBuffer *message;
    DnsBuffer *reply;
    union {
        DnsLookupRequest lookup;
        DnsPtrRequest ptr;
    } req;
};

typedef char DnsBufferSize[sizeof(DnsBuffer) == 8 ? 1 : -1];
typedef char DnsLookupRequestSize[sizeof(DnsLookupRequest) == 0x1c ? 1 : -1];
typedef char DnsPtrRequestSize[sizeof(DnsPtrRequest) == 0x10 ? 1 : -1];
typedef char DnsQuerySize[sizeof(DnsQuery) == 0x3c ? 1 : -1];
typedef char DnsQueryIdOffset[offsetof(DnsQuery, id) == 6 ? 1 : -1];
typedef char DnsQueryKindOffset[offsetof(DnsQuery, kind) == 8 ? 1 : -1];
typedef char DnsQueryTimerOffset[offsetof(DnsQuery, timer) == 0xa ? 1 : -1];
typedef char DnsQueryStatusOffset[offsetof(DnsQuery, status) == 0x10 ? 1 : -1];
typedef char DnsQueryMessageOffset[offsetof(DnsQuery, message) == 0x18 ? 1 : -1];
typedef char DnsQueryReplyOffset[offsetof(DnsQuery, reply) == 0x1c ? 1 : -1];
typedef char DnsQueryRequestOffset[offsetof(DnsQuery, req) == 0x20 ? 1 : -1];
typedef char DnsQueryLookupCallbackOffset[offsetof(DnsQuery, req) + offsetof(DnsLookupRequest, cb) == 0x34 ? 1 : -1];
typedef char DnsQueryLookupHostOffset[offsetof(DnsQuery, req) + offsetof(DnsLookupRequest, host) == 0x38 ? 1 : -1];
typedef char DnsQueryPtrCallbackOffset[offsetof(DnsQuery, req) + offsetof(DnsPtrRequest, cb) == 0x28 ? 1 : -1];
typedef char DnsQueryPtrEntryOffset[offsetof(DnsQuery, req) + offsetof(DnsPtrRequest, entry) == 0x2c ? 1 : -1];

#endif
