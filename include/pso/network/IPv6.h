#ifndef PSO_NETWORK_IPV6_H
#define PSO_NETWORK_IPV6_H

#include "types.h"
#include <stddef.h>

#define IPV6_NH_HOP_BY_HOP   0
#define IPV6_NH_ICMP         1
#define IPV6_NH_IPV4         4
#define IPV6_NH_TCP          6
#define IPV6_NH_UDP          17
#define IPV6_NH_ROUTING      43
#define IPV6_NH_FRAGMENT     44
#define IPV6_NH_ESP          50
#define IPV6_NH_AH           51
#define IPV6_NH_ICMPV6       58
#define IPV6_NH_NONE         59
#define IPV6_NH_DEST_OPTIONS 60
#define ICMP6_DST_UNREACH          1
#define ICMP6_DST_UNREACH_NOPORT   4
#define ICMP6_PARAM_PROB           4
#define ICMP6_PARAMPROB_HEADER     0 /* erroneous header field */
#define ICMP6_PARAMPROB_NEXTHEADER 1 /* unrecognized next header */
#define IPV6_REASSEMBLY_TIMEOUT 60

struct IPv6Address {
    u8 bytes[16];
};

struct IPv6NeighborSolicitation {
    u8 header[8];
    IPv6Address target;
};

typedef char IPv6Address_size_check[(sizeof(IPv6Address) == 16) ? 1 : -1];
typedef char IPv6NeighborSolicitation_size_check[
    (sizeof(IPv6NeighborSolicitation) == 24) ? 1 : -1];
typedef char IPv6NeighborSolicitation_target_check[
    (offsetof(IPv6NeighborSolicitation, target) == 8) ? 1 : -1];

#endif
