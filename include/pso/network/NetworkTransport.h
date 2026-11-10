#ifndef PSO_NETWORK_NETWORKTRANSPORT_H
#define PSO_NETWORK_NETWORKTRANSPORT_H
#include "types.h"

extern "C" {
void init_modem_buffer_config(void* config);
// Provisional native address-word command-stream boundary.
s32 TLobby__sub_803F7E50(s32 carrier, s32 error_correction, s32 compression, s32 count, s32 commands_address);
}
s32 init_modem_session_config();
#endif
