#ifndef PSO_PROTOCOL_PPP_CONTROL_RUNTIME_H
#define PSO_PROTOCOL_PPP_CONTROL_RUNTIME_H

#include "types.h"
#include "pso/protocol/PacketBuffer.h"
#include "pso/protocol/PppConfigure.h"
#include <stddef.h>

/* Verified prefixes of the native PPP state and frame records. Buffer allocations
 * extend beyond this eight-byte cursor/length prefix. */
typedef struct Conn_804004DC {
    u8 state;
    u8 id;
    u8 pad2_[1];
    u8 retries;
    u8 unknown4;
    u8 unknown5;
    u8 secondary_retries;
    u8 unknown7;
    s16 abort;
    u8 pad2[2];
    u8 *sub;
    u8 pad10[0x20];
    void *opts;
} Conn_804004DC;

/* IPv4 configuration passed to the wire-header writer. */
typedef struct A_80403F4C {
    u32 src;
    u32 dst;
    u16 len;
    u16 id;
    u16 frag;
    u16 cksum;
    u8 pad10;
    u8 df;
    u8 mf;
    u8 version;
    u8 tos;
    u8 ttl;
    u8 count;
    u8 optlen;
    u8 opts[0x40 - 0x18];
} A_80403F4C;

typedef char PppConnection_prefix_size[sizeof(Conn_804004DC) == 0x34 ? 1 : -1];
typedef char PppBuffer_prefix_size[sizeof(B_803FADA0) == 8 ? 1 : -1];
typedef char PppIPv4_config_size[sizeof(A_80403F4C) == 0x40 ? 1 : -1];

typedef char PppHeader_size[sizeof(PppConfigureMessage) == 4 ? 1 : -1];
typedef char PppConnection_options_offset[offsetof(Conn_804004DC, opts) == 0x30 ? 1 : -1];
typedef char PppBuffer_length_offset[offsetof(B_803FADA0, len) == 4 ? 1 : -1];
typedef char PppIPv4_protocol_offset[offsetof(A_80403F4C, count) == 0x16 ? 1 : -1];

struct Fsm_803FDBF8;
struct Md5Ctx_80401EB8;
struct Self_80402CE0;
#ifdef __cplusplus
extern "C" {
#endif
s16 TLobby__sub_803FE658(struct Self_80402CE0 *state);
s16 TLobby__sub_803FE6CC(void *state, u8 code, int identifier, void *payload);
s16 TLobby__sub_803FE8BC(u8 *header, void *cursor);
s16 TLobby__sub_80406624(s32, s32, u16 protocol, void *frame);
void TLobby__sub_803FDBF8(struct Fsm_803FDBF8 *state, B_803FADA0 *frame);
void TLobby__sub_803FEF4C(u8 *connection);
void TLobby__sub_8040059C(u8 *connection);
s16 TLobby__sub_80400744(int connection, void *configuration);
s16 TLobby__sub_80403308(Conn_804004DC *state, PppConfigureMessage *header, B_803FADA0 *frame);
void TLobby__sub_803FF374(void *context);
void TLobby__sub_803FF384(void *context);
void TLobby__sub_803FF468(void *context);
void TLobby__sub_803FF48C(void *context);
void TLobby__sub_80400988(void *context);
void TLobby__sub_8040098C(void *context);
void TLobby__sub_80400B98(void *context);
void free_field_98__6TLobbyFv(void *context);
void free_field_98_and_clear__6TLobbyFv(void *context);
void reset_connection_slot__6TLobbyFv(void *context);
void queue_command_81__6TLobbyFv(void *context);
void save_timer_state__6TLobbyFv(void *context);
void init_md5_state__6TLobbyFv(struct Md5Ctx_80401EB8 *context);
void NetPapDispatch(Conn_804004DC *state, B_803FADA0 *frame);
u8 *NetIPv4WriteHeader(A_80403F4C *config, u8 *frame, s32 preserve_checksum);
#ifdef __cplusplus
}
#endif

#endif
