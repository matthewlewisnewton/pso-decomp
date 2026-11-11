#ifndef PSO_NETWORK_DHCP_ACCESSORS_H
#define PSO_NETWORK_DHCP_ACCESSORS_H

#include "types.h"

extern "C" {
// Copies the table's fixed extent; len controls termination/clearing, not bounds.
s32 TLobby__sub_80425288(s16 id, s16 len, void *value);
// Preserves the original 16-bit length checks and fixed-size option copy.
s16 TLobby__sub_8042455C(char *hostname);
// Optional borrowed word outputs; active states return zero despite diagnostics.
s16 TLobby__sub_8042474C(s32 *lease, s32 *renew, s32 *rebind);
s16 TLobby__sub_8042489C(void *arg0, s32 *router);
// arg0 remains opaque. The original domain copy has no destination bound.
s16 dhcp_copy_domain_and_dns(void *arg0, char *domain, s32 *dns1, s32 *dns2);
}

#endif
