#ifndef PSO_NETWORK_NETSESSIONLAYOUT_H
#define PSO_NETWORK_NETSESSIONLAYOUT_H
#include "types.h"
#include <stddef.h>

// Native session/control record views recovered from the network callers.
typedef struct SessionDialRequest {
    s16 type;
    s16 has_arg;
    s16 timeout;
    u8 pad06[6];
    char *arg;
} SessionDialRequest;

typedef struct SessionModemConfig {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 numeric_result;
    u8 pad0A[2];
    char *prefix0;
    char *prefix1;
    s32 w14;
    s32 w18;
    char *result_ok;
    char *result_error;
    char *result_busy;
    char *result_no_dialtone;
    char *result_no_carrier;
    char *result_no_answer;
    s32 w34;
    u8 terminator;
    u8 pad39[3];
    s32 w3C;
    s32 w40;
    char *w44;          /* the script run after hanging up (TLobby__sub_803FB6A0), when h6 is set */
    char *s48;
    s32 w4C;
    s32 w50;
    s32 w54;
    s32 init_count;
    char *init_command; /* "AT+MS=V34\r" by default (connect_modem) */
} SessionModemConfig;

/* The session (lbl_805BFF68, TLobby_803FAEA0.c): NetApplyConnectionConfig copies the connection request (NetConnectCfg)
 * into it and TLobby__sub_803FB7A4 connects with it. A dial script substitutes %t, %u and %p with phone_number, user and
 * password. */
typedef struct NetSession {
    u16 flags;                  /* NetConnectCfg.flags; bit 2: no modem */
    s16 h2;                     /* 0x02 */
    s16 h4;                     /* 0x04 */
    u8 pad6[2];
    s32 connect_ms;             /* 0x08: when PPP started (state 3); is_timed_out gives up 60 s later */
    char *user;                 /* 0x0C */
    char *password;             /* 0x10 */
    char *phone_number;         /* 0x14 */
    void (*cb)(s16, s32);       /* 0x18: status callback */
    SessionModemConfig modem;          /* 0x1C: a copy of the default (init_net_session, copy_name_buffer) */
    s16 h7C;                    /* 0x7C: NetConnectCfg.h18 .. h20 */
    s16 h7E;
    s16 h80;
    s16 h82;
    s16 h84;
    u8 pad86[2];
    SessionDialRequest req;           /* 0x88: NetConnectCfg.h24 .. prefix */
    s16 h98;                    /* 0x98: NetConnectCfg.h34 .. h40; the low 7 bits select the authentication */
    s16 mtu;                    /* 0x9A: 0 = the default (lobby_net_buffer_desc_b) */
    s32 start_tick;             /* 0x9C */
    u16 uA0;
    u16 uA2;
    s16 hA4;
    u8 padA6[2];
    s32 wA8;                    /* 0xA8: NetConnectCfg.w44 .. w58 */
    s32 wAC;
    s32 wB0;
    s32 wB4;
    s32 wB8;
    s32 wBC;
    u8 bufC0[8];                /* 0xC0: NetConnectCfg.b5C */
    u8 bufC8[8];                /* 0xC8: NetConnectCfg.b64 */
} NetSession;
typedef char NetSession_size_check[sizeof(NetSession) == 0xD0 ? 1 : -1];


typedef char NetSession_modem_offset[offsetof(NetSession, modem) == 0x1C ? 1 : -1];
typedef char NetSession_request_offset[offsetof(NetSession, req) == 0x88 ? 1 : -1];
typedef char NetSession_auth_offset[offsetof(NetSession, h98) == 0x98 ? 1 : -1];
typedef char SessionModemConfig_size[sizeof(SessionModemConfig) == 0x60 ? 1 : -1];
#endif
