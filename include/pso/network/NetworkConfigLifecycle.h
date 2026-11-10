#ifndef PSO_NETWORK_NETWORK_CONFIG_LIFECYCLE_H
#define PSO_NETWORK_NETWORK_CONFIG_LIFECYCLE_H

#include "types.h"

s32 update_network_info_request(void);

extern "C" {
s32 TLobby__sub_803F3BF8(s32 backup_mode, void *buffer, u32 status);
s32 TLobby__sub_803F3D60(void);
}

#endif
