#include "types.h"
#include "pso/misc/TLobby.h"
#include "pso/network/DhcpClient.h"
#include "pso/system/memory.h"
#include "pso/system/ControllerInputState.h"
#include "pso/misc/TKeyBoardControl.h"

struct RecoveredGlobal_80146CB8_lbl_8050CCE8 {
    s32 value;
    u8 remaining[0x128];
};

struct RecoveredGlobal_8014672C_lbl_8050C0A8 {
    s32 value;
    u8 remaining[0x6D8];
};

struct RecoveredGlobal_80146588_lbl_8050CCE8 {
    s32 value;
    u8 remaining[0x128];
};

struct RecoveredGlobal_80146D14_lbl_8050CCE8 {
    s32 value;
    u8 remaining[0x128];
};

struct RecoveredGlobal_80146CA0_lbl_8050C784 {
    s32 value;
    u8 remaining[0x560];
};

struct RecoveredGlobal_80146D44_lbl_8050CE14 {
    s32 value;
    u8 remaining[0x150];
};

struct RecoveredGlobal_80146D50_lbl_8050C784 {
    s32 value;
    u8 remaining[0x560];
};

extern "C" {
s32 TLobby__sub_803FAFDC();
s32 TLobby__sub_803FB184(void *);
s32 TLobby__sub_803FB1A4(s16 *wait);
s32 TLobby__sub_80407358();
s32 TLobby__sub_8041509C();
s16 TLobby__sub_80423064(s16 idx, s32 arg1);
void TLobby__sub_80424CA8(void);
s32 TLobby__sub_80424CF4(void *, void *, s32 timeout);
void TLobby__sub_801469B8(void* p);
    extern int lbl_805D5708;
void* TLobby__sub_80146D68(int a0);
void TLobby__sub_8014715C(void* p, void* q);
s32 TLobby__sub_8040A3C0();
extern s32 lbl_805D570C;
s32 TLobby__sub_8014618C(void);
char *strncpy(char *dst, const char *src, u32 n);
void *memset(void *dst, int value, u32 n);
s32 strlen(const char *s);
s32 TLobby__sub_803FAEA0(s32 cmd, s32 arg);
s32 TLobby__sub_803FB280(void *cfg);
s32 TLobby__sub_803F5524(char *dst, s32 len);
s32 TWindowShortListCtrl__check_controller_button(ControllerInputContext *ctx, int mask);
extern char lbl_8043F418[];
extern char lbl_805DB1B0[3];
void TLobby__sub_801472F8(s16 *state, s16 *reason);
void TLobby__sub_8014672C(s32 *arg0);
extern s32 lbl_805D56D8;
extern s32 lobby_dns_server_addr;
extern s32 lbl_805D56E0;
extern s32 lobby_connect_battle_flag;
s32 TLobby__sub_80146588(s32 *arg0);
u8 *TLobby__sub_80146D14(void);
u8 *TLobby__sub_80146CA0(s32 arg0);
char *TLobby__sub_80146D44(void);
u8 *TLobby__sub_80146D50(s32 arg0);
s32 TLobby__sub_801466F4(u32 arg0);
s32 TLobby__sub_80145EE4(void);
s32 TLobby__sub_80146314(s32 *);
s32 TLobby__sub_801465C0(s32 *);
void fn_80147A68(void);
void TLobby__sub_804073B8(void);
s16 run_connect_step__6TLobbyFv(void);
s16 TLobby__sub_804150EC(void);
s16 TLobby__sub_8042315C(s16, void *);
extern s32 lbl_805D2D00;
extern s32 TLobby__connect_pending_flags;
extern s32 lobby_connect_active_flag;
s32 TLobby__sub_803F861C(void *info);
s32 TLobby__sub_803F8470(u8 *data, s32 size);
s32 TLobby__sub_801478C4(s32 arg0);
s32 TLobby__sub_8014734C(s32 idx, s16 arg1);
extern s32 actor_frame_tick;
}
s32 NetSetDefaultThreadPriority(s32 priority);

struct Sub_801465C0 {
    u8 pad0[0x1C];
    char name[0x124 - 0x1C];
};

struct Acct_80146D7C {
    char host[0x80];
    char user[0x20];
    char pass[0x20];
    char dns1[0x20];
    char dns2[0x20];
    char f100[0x40];
    char f140[0x40];
    char f180[0x40];
    u32 f1C0;
    u32 f1C4;
    s32 valid;
};
struct Work_80146D7C {
    s32 f0;
    char host[0x80];
    char user[0x20];
    char pass[0x40];
    char dns1[0x40];
    char dns2[0x40];
    u32 f164;
    u32 f168;
    char f16C[0x20];
    char f18C[0x40];
    char f1CC[0x40];
    u8 pad[0x274 - 0x20C];
};
struct Conn_80146D7C {
    s32 f0;
    s32 f4, f8, fC, f10, f14, f18;
    char f1C[0x20];
    char f3C[0x40];
    char f7C[0x80];
    char fFC[0x20];
    u16 f11C;
    s32 f120;
};
struct Info_80146D7C {
    s32 f0;
    s32 f4;
    char f8[0x80];
    char f88[0x20];
    s32 fA8, fAC, fB0, fB4, fB8, fBC;
    s32 fC0;
    char fC4[0x40];
    char f104[0x140];
    u16 f244;
    u8 pad[0x26C - 0x246];
};

extern "C" {
void fn_80147A60(int a0);
s16 TLobby__sub_8042455C(void *);
s16 TLobby__sub_8042489C(void *, void *);
s16 validate_slot_buffers__6TLobbyFlPvPvPv(void *, void *, void *, void *);
s16 TLobby__sub_80424E44(s16);
extern s32 lbl_805D56E8;
extern s32 lbl_805D56EC;
extern s32 lbl_805D56F0;
extern s32 lbl_805D56F4;
int TLobby__sub_80145E40(void);
int TLobby__sub_80146724(void);
int TLobby__sub_80146740(void);
int TLobby__sub_8014677C(void);
s32 TLobby__sub_80145A94(void);
s32 TLobby__sub_80145DB4(s32 arg0);
s32 TLobby__sub_80147284();
}
s32 init_struct(u8 *arg0);
s32 init_work(s32 arg0, u8 *arg1);
s32 get_network_config_buffer_size(s32 mode);
extern "C" {
s32 TLobby__sub_804219D0(s32, s32, s32);
s32 TLobby__sub_80421A50(s32, s32, s32);
s8 func_801A5E54__Fv();
s32 send_and_handle__6TLobbyFv();
void xfree__FPv(void*);

    extern void *lbl_805D56C8;
    extern short lbl_805D56CE;
    extern int keyboard_buffer_cursor;
struct PhoneNumber {
    char number[0x20];
};
struct AccountEntry {
    char host[0x80];
    char user[0x20];
    PhoneNumber phone[3];
    char f100[0x40];
    char f140[0x40];
    char f180[0x40];
    u32 dns1;
    u32 dns2;
    s32 valid;
};
u32 lbl_8050C0A8[7];
u32 lbl_8050C0C4[368];
u32 lbl_8050C684[64];
AccountEntry lobby_account_entries[3]; /* cleared by TLobby::init_account_entries, filled by load_network_configs; [2] is the modem account */
u32 lbl_8050CCE8[73];
__declspec(section ".data") s32 lbl_8050CE0C[2];
char lbl_8050CE14[0x20];
char lbl_8050CE34[0x20];
u8 lbl_8050CE54[0x114];
extern s32 lbl_805D5714;
#define lbl_8050C0A8 (*(RecoveredGlobal_8014672C_lbl_8050C0A8 *)lbl_8050C0A8)
#define lbl_8050C784 (*(unsigned char (*)[0x564])lobby_account_entries)
#define lbl_8050CCE8 (*(RecoveredGlobal_80146CB8_lbl_8050CCE8 *)lbl_8050CCE8)
#define lbl_8050CE14 (*(RecoveredGlobal_80146D44_lbl_8050CE14 *)lbl_8050CE14)

void TLobby::init_keyboard_buffer() {
    keyboard_buffer_cursor = 0;
    lbl_805D56CE = 0;
    lbl_805D56C8 = NULL;
    lbl_805D56C8 = xmalloc(get_network_config_buffer_size(0));
    TLobby__sub_80145A94();
}

s32 TLobby::poll_connect() {
    s32 var_r31;

    var_r31 = 0;
loop_1:
    if (var_r31 > 0x12C) {
        return 0;
    }
    var_r31 += 1;
    send_and_handle__6TLobbyFv();
    if (func_801A5E54__Fv() != 0) {
        return 1;
    }
    if (TLobby::query_link_status() == 1) {
        return 2;
    }
    goto loop_1;
}

extern s32 TLobby__battle_flag;

void TLobby::flush_pending_flag2() {
    if (TLobby__connect_pending_flags & 2) {
        TLobby__sub_804219D0(0, 0, TLobby__battle_flag);
        TLobby__connect_pending_flags &= 0xFFFFFFFD;
    }
}

void TLobby::set_battle_flag(s32 arg0) {
    TLobby__battle_flag = arg0;
    TLobby__connect_pending_flags |= 2;
    TLobby__sub_80421A50(0, 0, arg0);
}

// Upstream #190 (5695627bd) connect_pppoe, named for the fork symbol.
// Raw offset casts into lbl_8050CCE8 are upstream catch-up, rewrite later.
struct NetConnectCfg {
    u16 flags;
    s16 h2;
    s16 wait;
    u8 pad_6[2];
    void *wC;
    void *password;
    void *phone_number;
    void *callback;
    s16 h18;
    s16 h1A;
    s16 h1C;
    s16 h1E;
    s16 h20;
    u8 pad_22[2];
    s16 h24;
    s16 h26;
    s16 h28;
    s16 h2A;
    s16 h2C;
    u8 pad_2E[2];
    void *prefix;
    s16 h34;
    s16 mtu;
    s32 start_tick;
    s16 h3C;
    s16 h3E;
    s16 h40;
    u8 pad_42[2];
    s32 w44;
    s32 w48;
    s32 w4C;
    s32 w50;
    s32 w54;
    s32 w58;
    u8 b5C[8];
    u8 b64[8];
};
struct NetLinkStatus {
    s16 link_up;
    s16 ppp_up;
    s16 state;
    s16 h6;
    u32 w8;
    s16 hC;
    u8 padE[2];
    u32 w10;
    u32 w14;
    u32 w18;
    u32 w1C;
    u32 w20;
    u32 w24;
    u8 addr[4][4];
};
struct NetWaitParam {
    s16 wait;
};

s32 TLobby__sub_80146314(s32 *out_value) {
    NetConnectCfg cfg;
    NetLinkStatus status;
    s16 state;
    s16 reason;
    NetWaitParam stop;
    NetWaitParam stop2;
    s16 id;
    s32 cancel;
    s32 result;

    id = TLobby::init_net_session();
    TLobby__connect_pending_flags |= 4;
    lbl_805D2D00 = id;
    if (id == -1) {
        return 9;
    }
    cfg.flags = 5;
    cfg.wait = 0;
    cfg.wC = (char *)&lbl_8050CCE8 + 0x7C;
    cfg.password = (char *)&lbl_8050CCE8 + 0xFC;
    cfg.callback = 0;
    cfg.h2 = 4;
    cfg.h18 = 6;
    cfg.h1A = 0;
    cfg.h1C = 0;
    cfg.h1E = 3;
    cfg.h20 = 1;
    cfg.h28 = 90;
    cfg.h2A = 0;
    cfg.h2C = 20;
    cfg.phone_number = 0;
    cfg.h24 = 0;
    cfg.h26 = 0;
    cfg.prefix = 0;
    cfg.h34 = 4;
    cfg.mtu = 1500;
    cfg.start_tick = 0x12345678;
    cfg.h3C = 0;
    cfg.h3E = 0;
    cfg.h40 = 1;
    cfg.w44 = 0;
    cfg.w48 = 0;
    cfg.w4C = 0;
    cfg.w50 = 0;
    cfg.w54 = 0;
    cfg.w58 = 0;
    TLobby__sub_803FAEA0(1, 10);
    TLobby__sub_803FB280(&cfg);
    state = -1;
    do {
        cancel = 0;
        if (TWindowShortListCtrl__check_controller_button(&controller_input_state.controllers[0], 2) != 0 ||
            TKeyBoardControl::read_key_checked(0x4C) != 0) {
            cancel = 1;
            result = 0x10;
        }
        if (func_801A5E54__Fv() != 0) {
            cancel = 1;
            result = 0x11;
        }
        if (cancel != 0) {
            stop.wait = 1;
            TLobby__sub_803FB1A4(&stop.wait);
            lbl_805D2D00 = -1;
            return result;
        }
        TLobby__sub_801472F8(&state, &reason);
        if (state == 5 || state == 8 || state == 4) {
            break;
        }
        send_and_handle__6TLobbyFv();
    } while (state != 4);
    if (state == 4) {
        TLobby__sub_803FB184(&status);
        lbl_805D56D8 = status.w10;
        *out_value = 0;
        lobby_dns_server_addr = status.w18;
        lbl_805D56E0 = status.w1C;
        lobby_connect_battle_flag = status.w10;
        return 0;
    }
    stop2.wait = 1;
    TLobby__sub_803FB1A4(&stop2.wait);
    switch (reason) {
    case 3:
        return 5;
    case 2:
        return 7;
    case 6:
        return 8;
    case 0:
    case 1:
    case 7:
    default:
        return 4;
    }
}

typedef char RecoveredGlobal_80146588_lbl_8050CCE8_size[sizeof(RecoveredGlobal_80146588_lbl_8050CCE8) == 0x12C ? 1 : -1];
s32 TLobby__sub_80146588(s32 *arg0) {
    lbl_805D56D8 = *(s32 *)((s8 *)(&(*(RecoveredGlobal_80146588_lbl_8050CCE8 *)&lbl_8050CCE8).value) + 4);
    *(s32 *)((s8 *)arg0 + 0) = *(s32 *)((s8 *)(&(*(RecoveredGlobal_80146588_lbl_8050CCE8 *)&lbl_8050CCE8).value) + 8);
    lobby_connect_battle_flag = *(s32 *)((s8 *)(&(*(RecoveredGlobal_80146588_lbl_8050CCE8 *)&lbl_8050CCE8).value) + 0x18);
    lobby_dns_server_addr = *(s32 *)((s8 *)(&(*(RecoveredGlobal_80146588_lbl_8050CCE8 *)&lbl_8050CCE8).value) + 0x10);
    lbl_805D56E0 = *(s32 *)((s8 *)(&(*(RecoveredGlobal_80146588_lbl_8050CCE8 *)&lbl_8050CCE8).value) + 0x14);
    return 0;
}

s32 TLobby__sub_801465C0(s32 *arg0) {
    s32 sp8;

    if (TLobby__sub_80424E44((s16)lbl_805D2D00) != 0) {
        return 0xC;
    }
    Sub_801465C0 *sub = (Sub_801465C0 *)&lbl_8050CCE8;
    TLobby__connect_pending_flags |= 0x10;
    lobby_connect_active_flag = 1;
    char *name = sub->name;
    if (*name != 0 && TLobby__sub_8042455C(name) < 0) {
        return 0xC;
    }
    lbl_805D56D8 = 0;
    lbl_805D56E8 = 0;
    if (TLobby__sub_80424D58((s16)lbl_805D2D00, 0, 0, lbl_8050C0C4, &lbl_805D56D8, arg0, &sp8, 3) != 0) {
        return 0xC;
    }
    if (TLobby__sub_8042489C(lbl_8050C0C4, &lobby_connect_battle_flag) != 0) {
        return 0xC;
    }
    if (TLobby__sub_8042474C(&lbl_805D56EC, &lbl_805D56F0, &lbl_805D56F4) != 0) {
        return 0xC;
    }
    fn_80147A60(lbl_805D56EC);
    return validate_slot_buffers__6TLobbyFlPvPvPv(lbl_8050C0C4, lbl_8050C684, &lobby_dns_server_addr, &lbl_805D56E0) != 0 ? 0xC : 0;
}

s32 TLobby__sub_801466F4(u32 arg0) {
    switch (arg0) {
    case 0:
    case 1:
    case 2:
    case 5:
    case 6:
    case 8:
    case 11:
    case 16:
    case 17:
        return 0;
    default:
        return 1;
    }
}

int TLobby__sub_80146724(void) { return 3; }

typedef char RecoveredGlobal_8014672C_lbl_8050C0A8_size[sizeof(RecoveredGlobal_8014672C_lbl_8050C0A8) == 0x6DC ? 1 : -1];
void TLobby__sub_8014672C(s32 *arg0) {
    *(s32 *)((s8 *)arg0 + 0) = *(s32 *)((s8 *)&lbl_8050C0A8.value + 4);
}

int TLobby__sub_80146740(void) { return 0; }

s32 TLobby::query_task_active() {
    if ((s32) lobby_connect_active_flag != 0) {
        return TLobby::get_task_count();
    }
    return 0;
}

int TLobby__sub_8014677C(void) { return TLobby__sub_80145DB4(1); }
int TLobby::get_link_status_value() { return TLobby__sub_80145DB4(4); }

extern u32 lbl_805D5700;
extern s32 TLobby__net_session_mode;

struct LinkState_801467C4 { u8 pad0[4]; s16 state; u8 pad6[0x32]; };

}
int get_link_status() {
    LinkState_801467C4 link;
    if (TLobby__net_session_mode == 0) {
        if ((s16)TLobby__sub_803FB184(&link) < 0) {
            return 0;
        }
        switch (link.state) {
        case 5:
        case 6:
        case 7:
        case 8:
            return 0;
        }
        if (actor_frame_tick % 900 == 0 && (s16)TLobby__sub_8014677C() == 0) {
            return 0;
        }
    } else {
        if (actor_frame_tick % 900 == 0 && (s16)TLobby::get_link_status_value() == 0) {
            return 0;
        }
        if ((TLobby__connect_pending_flags & 1) && TLobby::query_link_status() == 0) {
            return 0;
        }
    }
    return 1;
}
extern "C" {

void TLobby::cleanup() {
    if ((s32) TLobby__net_session_mode != 0) {
        TLobby__sub_801469B8(this);
    } else {
        TLobby__sub_80147284();
    }
    if (TLobby__connect_pending_flags & 8) {
        TLobby::cleanup_subsystems();
        TLobby__connect_pending_flags &= 0xFFFFFFF7;
    }
    if ((u32) lbl_805D5700 != 0U) {
        xfree__FPv((void*)lbl_805D5700);
        lbl_805D5700 = 0U;
    }
}
struct NetParams_80146908 { s16 a; s16 b; u16 c; u16 d; s32 e; s32 f; s32 g; s32 h; s32 i; };

s32 TLobby__sub_80146908() {
    NetParams_80146908 params;
    s32 size;
    NetSetDefaultThreadPriority(0x10);
    size = TLobby__sub_803F861C(&params);
    params.d = 1;
    params.e = 0x1000;
    params.f = 0x3000;
    ((TLobby *)&params)->validate_and_store_net_params();
    lbl_805D5700 = (u32)xmalloc(size);
    if (lbl_805D5700 != 0) {
        TLobby__sub_803F8470((u8 *)lbl_805D5700, size);
    }
    TLobby::init_network_stack();
    TLobby__connect_pending_flags |= 8;
    lobby_connect_active_flag = 0;
    lbl_805D570C = 0;
    if (TLobby__net_session_mode != 0) {
        return TLobby::run_connect_sequence();
    }
    return TLobby__sub_801478C4(TLobby::init_net_session());
}
void TLobby__sub_801469B8(void* p) { TLobby::flush_pending_flags(); }
void TLobby::flush_pending_flags() {
    struct { u8 pad0[4]; s16 f4; u8 pad6[0x3E]; } spC;
    s16 sp8;

    TLobby__connect_pending_flags &= 0xFFFFFFFE;
    TLobby::teardown_boss2();
    if (TLobby__sub_80145EE4() != 0) {
        if (TLobby__connect_pending_flags & 0x10) {
            TLobby__sub_80424CF4((void *)((s16) lbl_805D2D00), (void *)lbl_805D56D8, 3);
            TLobby__connect_pending_flags &= 0xFFFFFFEF;
            TLobby__sub_80424CA8();
        }
    } else if (TLobby::is_state_active() != 0) {
        if ((s32) lbl_805D2D00 != -1) {
            TLobby__sub_80423064(((s16) lbl_805D2D00), 0);
            sp8 = 0;
            TLobby__sub_803FB1A4(&sp8);
            do {
                TLobby__sub_803FB184(&spC);
                send_and_handle__6TLobbyFv();
            } while (spC.f4 != 0);
        }
        if (TLobby__connect_pending_flags & 4) {
            TLobby__sub_803FAFDC();
            TLobby__connect_pending_flags &= 0xFFFFFFFB;
        }
    }
    lbl_805D2D00 = -1;
    if (TLobby__connect_pending_flags & 0x20) {
        TLobby__sub_8041509C();
        TLobby__connect_pending_flags &= 0xFFFFFFDF;
    }
    if (TLobby__connect_pending_flags & 0x40) {
        TLobby::flush_flags_step();
        TLobby__connect_pending_flags &= 0xFFFFFFBF;
    }
    if (TLobby__connect_pending_flags & 0x80) {
        TLobby__sub_80407358();
        TLobby__connect_pending_flags &= 0xFFFFFF7F;
    }
}

s32 TLobby::run_connect_sequence() {
    s32 sp8;
    s32 id;
    s32 r;
    s16 ok;
    TLobby__connect_pending_flags &= ~1;
    fn_80147A68();
    if (*(s32 *)((u8 *)&lbl_8050CCE8 + 0x120) != 0) {
        TLobby__sub_804073B8();
        TLobby__connect_pending_flags |= 0x80;
        id = run_connect_step__6TLobbyFv();
        TLobby__connect_pending_flags |= 0x40;
        r = TLobby::poll_connect();
        if (r == 0) {
            return 0xF;
        }
        if (r == 1) {
            return 0x11;
        }
        TLobby__connect_pending_flags |= 1;
        TLobby::set_connect_mode(4);
        ok = TLobby__sub_804150EC();
        TLobby__connect_pending_flags |= 0x20;
        lobby_connect_active_flag = 0;
        if (ok != 0) {
            return 0xE;
        }
        if (TLobby__sub_80145EE4() != 0) {
            lbl_805D2D00 = id;
            r = TLobby__sub_801465C0(&sp8);
        } else if (TLobby::is_state_active() != 0) {
            r = TLobby__sub_80146314(&sp8);
        } else {
            lbl_805D2D00 = id;
            r = TLobby__sub_80146588(&sp8);
        }
        if (r == 0) {
            s32 *m = (s32 *)&lbl_8050C0A8;
            m[0] = 4;
            m[1] = lbl_805D56D8;
            m[2] = sp8;
            m[3] = 0;
            if (TLobby__sub_8042315C((s16)lbl_805D2D00, &lbl_8050C0A8) == 0) {
                TLobby::set_battle_flag(lobby_connect_battle_flag);
            } else {
                return 0xD;
            }
            return TLobby::set_dns_servers();
        }
        return r;
    }
    return 0xE;
}

void TLobby::call_146CA0_with_5708() { TLobby__sub_80146CA0(lbl_805D5708); }

typedef char RecoveredGlobal_80146CB8_lbl_8050CCE8_size[sizeof(RecoveredGlobal_80146CB8_lbl_8050CCE8) == 0x12C ? 1 : -1];

typedef char RecoveredGlobal_80146CA0_lbl_8050C784_size[sizeof(RecoveredGlobal_80146CA0_lbl_8050C784) == 0x564 ? 1 : -1];
u8 *TLobby__sub_80146CA0(s32 arg0) {
    return (u8 *)&(*(RecoveredGlobal_80146CA0_lbl_8050C784 *)&lbl_8050C784).value + (arg0 << 5) + 0x438;
}

void TLobby::set_ppp_password(s32 arg0) {
    u8 *temp_r31;
    TLobby__sub_8014618C();
    TLobby::is_state_active();
    temp_r31 = (u8 *)&lbl_8050CCE8.value + 0xFC;
    memset(temp_r31, 0, 0x20);
    strncpy((char *)temp_r31, (const char *)arg0, 0x1F);
}

typedef char RecoveredGlobal_80146D14_lbl_8050CCE8_size[sizeof(RecoveredGlobal_80146D14_lbl_8050CCE8) == 0x12C ? 1 : -1];
u8 *TLobby__sub_80146D14(void) {
    TLobby__sub_8014618C();
    TLobby::is_state_active();
    return (u8 *)&(*(RecoveredGlobal_80146D14_lbl_8050CCE8 *)&lbl_8050CCE8).value + 0xFC;
}

typedef char RecoveredGlobal_80146D44_lbl_8050CE14_size[sizeof(RecoveredGlobal_80146D44_lbl_8050CE14) == 0x154 ? 1 : -1];
char *TLobby__sub_80146D44(void) {
    return (char *)&lbl_8050CE14.value;
}

typedef char RecoveredGlobal_80146D50_lbl_8050C784_size[sizeof(RecoveredGlobal_80146D50_lbl_8050C784) == 0x564 ? 1 : -1];
u8 *TLobby__sub_80146D50(s32 arg0) {
    return (u8 *)&(*(RecoveredGlobal_80146D50_lbl_8050C784 *)&lbl_8050C784).value + (arg0 * 0x1CC) + 0x80;
}

void* TLobby__sub_80146D68(int a0) {  return (char*)lbl_8050C784 + a0 * 460; }
#define A_80146D7C (*(Acct_80146D7C (*)[3])lbl_8050C784)
#define C_80146D7C (*(Conn_80146D7C *)&lbl_8050CCE8)
#define S_80146D7C ((char *(*)(char *, const char *, u32))strncpy)
void TLobby::load_network_configs() {
    Work_80146D7C w;
    Info_80146D7C info;

    if (TLobby__sub_80145E40() == 1) {
        lbl_8050CE0C[1] = 1;
    } else {
        lbl_8050CE0C[1] = 0;
    }
    if (init_work(1, (u8 *)&w) == 0) {
        S_80146D7C(A_80146D7C[0].host, w.host, 0x7F);
        S_80146D7C(A_80146D7C[0].user, w.user, 0x1F);
        S_80146D7C(A_80146D7C[0].pass, w.pass, 0x1F);
        S_80146D7C(A_80146D7C[0].dns1, w.dns1, 0x1F);
        S_80146D7C(A_80146D7C[0].dns2, w.dns2, 0x1F);
        S_80146D7C(A_80146D7C[0].f100, w.f16C, 0x3F);
        S_80146D7C(A_80146D7C[0].f140, w.f18C, 0x3F);
        S_80146D7C(A_80146D7C[0].f180, w.f1CC, 0x3F);
        TLobby__sub_8014715C(&A_80146D7C[0].f1C0, &w.f164);
        TLobby__sub_8014715C(&A_80146D7C[0].f1C4, &w.f168);
        A_80146D7C[0].valid = 1;
    } else {
        A_80146D7C[0].valid = 0;
    }
    if (init_work(2, (u8 *)&w) == 0) {
        S_80146D7C(A_80146D7C[1].host, w.host, 0x7F);
        S_80146D7C(A_80146D7C[1].user, w.user, 0x1F);
        S_80146D7C(A_80146D7C[1].pass, w.pass, 0x1F);
        S_80146D7C(A_80146D7C[1].dns1, w.dns1, 0x1F);
        S_80146D7C(A_80146D7C[1].dns2, w.dns2, 0x1F);
        S_80146D7C(A_80146D7C[1].f100, w.f16C, 0x3F);
        S_80146D7C(A_80146D7C[1].f140, w.f18C, 0x3F);
        S_80146D7C(A_80146D7C[1].f180, w.f1CC, 0x3F);
        TLobby__sub_8014715C(&A_80146D7C[1].f1C0, &w.f164);
        TLobby__sub_8014715C(&A_80146D7C[1].f1C4, &w.f168);
        A_80146D7C[1].valid = 1;
    } else {
        A_80146D7C[1].valid = 0;
    }
    if (init_work(0, (u8 *)&w) == 0) {
        S_80146D7C(A_80146D7C[2].host, w.host, 0x7F);
        S_80146D7C(A_80146D7C[2].user, w.user, 0x1F);
        S_80146D7C(A_80146D7C[2].pass, w.pass, 0x1F);
        S_80146D7C(A_80146D7C[2].dns1, w.dns1, 0x1F);
        S_80146D7C(A_80146D7C[2].dns2, w.dns2, 0x1F);
        S_80146D7C(A_80146D7C[2].f100, w.f16C, 0x3F);
        S_80146D7C(A_80146D7C[2].f140, w.f18C, 0x3F);
        S_80146D7C(A_80146D7C[2].f180, w.f1CC, 0x3F);
        TLobby__sub_8014715C(&A_80146D7C[2].f1C0, &w.f164);
        TLobby__sub_8014715C(&A_80146D7C[2].f1C4, &w.f168);
        A_80146D7C[2].valid = 1;
    } else {
        A_80146D7C[2].valid = 0;
    }
    C_80146D7C.f120 = 0;
    if (TLobby__net_session_mode == 1 && init_struct((u8 *)&info) == 0) {
        C_80146D7C.f0 = info.f4;
        C_80146D7C.f4 = info.fA8;
        C_80146D7C.f8 = info.fAC;
        C_80146D7C.fC = info.fB0;
        C_80146D7C.f10 = info.fB4;
        C_80146D7C.f14 = info.fB8;
        C_80146D7C.f18 = info.fBC;
        S_80146D7C(C_80146D7C.f7C, info.f8, 0x7F);
        S_80146D7C(C_80146D7C.fFC, info.f88, 0x1F);
        S_80146D7C(C_80146D7C.f1C, info.fC4, 0x1F);
        S_80146D7C(C_80146D7C.f3C, info.f104, 0x3F);
        C_80146D7C.f11C = info.f244;
        C_80146D7C.f120 = 1;
    }
}
#undef A_80146D7C
#undef C_80146D7C
#undef S_80146D7C
void TLobby__sub_8014715C(void* p, void* q) { *(u32*)((char*)p + 0x0) = *(u32*)((char*)q + 0x0); }
void TLobby::teardown_boss2() {
    if ((s32) lbl_805D570C != 0) {
        TLobby::clear_all_used_records();
        TLobby__sub_8040A3C0();
        lbl_805D570C = 0;
    }
}
}

#undef lbl_8050C0A8
#undef lbl_8050C784
#undef lbl_8050CCE8
#undef lbl_8050CE14

struct RecoveredGlobal_80147A74_lbl_804EF500 {
    s32 value;
    u8 remaining[0x94];
};

struct S_801472F8 { u8 pad0[4]; s16 a; s16 b; u8 rest[0x38]; };

struct Req_801471A0 { s32 type; u32 addr; u8 pad[0x18]; };

struct Cfg_801471A0 { u8 pad[0x558]; u32 dns1; u32 dns2; };

extern RecoveredGlobal_80147A74_lbl_804EF500 ppp_password_buffer;
s32 *get_ppp_password_buffer(void);
extern "C" {
void TLobby__sub_801472F8(s16 *arg0, s16 *arg1);
s32 fn_80145A44(char *dst);
void OSReport(const char *, ...);
s16 init_net_tables__6TLobbyFv();
s16 TLobby__sub_8040ADE8(Req_801471A0 *);
extern char lbl_8043F3F0[];
extern char lbl_8043F404[];
s32 TLobby__sub_80147284(void);
void TLobby__sub_80147978(void);

#define lbl_8050C784 (*(Cfg_801471A0 *)lobby_account_entries)
#define TLobby__sub_803FB184 ((s16 (*)(void *))TLobby__sub_803FB184)

s32 TLobby::set_dns_servers() {
    Req_801471A0 req;
    s16 r1;
    s16 r2;
    if (init_net_tables__6TLobbyFv() == 0) {
        lbl_805D570C = 1;
        req.type = 4;
        req.addr = lobby_dns_server_addr;
        if (lbl_8050C784.dns1 != 0) {
            req.addr = lbl_8050C784.dns1;
        }
        r1 = TLobby__sub_8040ADE8(&req);
        req.addr = lbl_805D56E0;
        if (lbl_8050C784.dns2 != 0) {
            req.addr = lbl_8050C784.dns2;
        }
        r2 = TLobby__sub_8040ADE8(&req);
        OSReport(lbl_8043F3F0, r1);
        OSReport(lbl_8043F404, r2);
        if (r1 == 0 || r2 == 0) {
            return 0;
        }
        return 0xB;
    }
    return 0xB;
}

s32 TLobby__sub_80147284(void) {
    s16 sp8;

    if ((s32) lbl_805D2D00 != -1) {
        TLobby__sub_80423064((s16) lbl_805D2D00, 0);
        sp8 = 1;
        TLobby__sub_803FB1A4(&sp8);
    }
    TLobby::flush_pending_flag2();
    if (TLobby__connect_pending_flags & 4) {
        TLobby__sub_803FAFDC();
        TLobby__connect_pending_flags &= 0xFFFFFFFB;
    }
    TLobby::teardown_boss2();
    lbl_805D2D00 = -1;
    return 0;
}

void TLobby__sub_801472F8(s16 *arg0, s16 *arg1) {
    S_801472F8 s;
    if (TLobby__sub_803FB184(&s) < 0) {
        s.a = 0;
    }
    *arg0 = s.a;
    *arg1 = s.b;
}

// Upstream #190 (5695627bd) connect_modem, named for the fork symbol.
#undef lbl_8050C784
struct ModemDialConfig {
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
    s32 w44;
    char *s48;
    s32 w4C;
    s32 w50;
    s32 w54;
    s32 init_count;
    char *init_command;
};
s32 TLobby__sub_8014734C(s32 idx, s16 id) {
    NetConnectCfg cfg;
    ModemDialConfig modem;
    NetLinkStatus status;
    NetLinkStatus final_status;
    char dial_prefix[0x20];
    char response[0x100];
    char command[0x100];
    s16 state;
    s16 reason;
    NetWaitParam stop;
    s32 cancel;
    s32 result;
    s32 countdown;
    s32 len;
    s32 n;

    if (TLobby__sub_80145DB4(1) == 0) {
        return 6;
    }
    if (lobby_account_entries[2].valid == 0) {
        return 1;
    }
    if (lbl_8050CE0C[1] == 0) {
        return 1;
    }
    if (lobby_account_entries[2].phone[idx].number[0] == 0) {
        return 3;
    }
    lbl_805D2D00 = id;
    if (id == -1) {
        return 2;
    }
    modem.h0 = 1;
    modem.h2 = 1;
    modem.h4 = 1;
    modem.h6 = 0;
    modem.numeric_result = 0;
    modem.prefix0 = 0;
    modem.prefix1 = 0;
    modem.w14 = 0;
    modem.w18 = 0;
    modem.result_ok = 0;
    modem.result_error = 0;
    modem.result_busy = 0;
    modem.result_no_dialtone = 0;
    modem.result_no_carrier = 0;
    modem.result_no_answer = 0;
    modem.w34 = 0;
    modem.terminator = '\r';
    modem.w3C = 0;
    modem.w40 = 0;
    modem.w44 = 0;
    modem.s48 = lbl_805DB1B0;
    len = strlen(lbl_8043F418);
    memset(command, 0, sizeof(command));
    strncpy(command, lbl_8043F418, len);
    command[len] = '\r';
    command[len + 1] = '\0';
    modem.init_count = 1;
    modem.init_command = command;
    memset(response, 0, sizeof(response));
    switch (TLobby__sub_803F5524(response, sizeof(response))) {
    case 0:
        memset(command, 0, sizeof(command));
        n = strlen(response);
        if (n < 254) {
            if (n != 0) {
                strncpy(command, response, n);
                command[n] = '\r';
                command[n + 1] = '\0';
                modem.init_count = 1;
                modem.init_command = command;
            } else {
                len = strlen(lbl_8043F418);
                memset(command, 0, sizeof(command));
                strncpy(command, lbl_8043F418, len);
                command[len] = '\r';
                command[len + 1] = '\0';
                modem.init_count = 1;
                modem.init_command = command;
            }
        }
        break;
    case -1:
    case -2:
    case -3:
    case -5:
        return 9;
    case -4:
    default:
        break;
    }
    modem.w4C = 2;
    modem.w50 = 0;
    modem.w54 = 0;
    TLobby::copy_name_buffer(&modem);
    cfg.flags = 1;
    cfg.wait = 0;
    cfg.wC = lobby_account_entries[2].host;
    if (*TLobby__sub_80146D44() == 0) {
        cfg.password = get_ppp_password_buffer();
    } else {
        cfg.password = lbl_8050CE14;
    }
    cfg.phone_number = TLobby__sub_80146CA0(idx);
    cfg.callback = 0;
    cfg.h2 = 4;
    cfg.h18 = 6;
    cfg.h1A = 0;
    cfg.h1C = 0;
    cfg.h1E = 3;
    cfg.h20 = 1;
    if (TLobby::is_status_zero() != 0) {
        cfg.h24 = 0;
    } else {
        cfg.h24 = 1;
    }
    cfg.h28 = 90;
    cfg.h2A = 0;
    cfg.h2C = 20;
    if (fn_80145A44(dial_prefix) != 0) {
        cfg.h26 = 1;
        cfg.prefix = dial_prefix;
    } else {
        cfg.h26 = 0;
        cfg.prefix = 0;
    }
    cfg.h34 = 4;
    cfg.mtu = 1500;
    cfg.start_tick = 0x12345678;
    cfg.h3C = 0;
    cfg.h3E = 0;
    cfg.h40 = 1;
    cfg.w44 = 0;
    cfg.w48 = 0;
    cfg.w4C = 0;
    cfg.w50 = 0;
    cfg.w54 = 0;
    cfg.w58 = 0;
    TLobby__sub_803FB280(&cfg);
    TLobby__connect_pending_flags |= 4;
    state = -1;
    cancel = 0;
    result = 0x10;
    countdown = 0;
    do {
        if (countdown == 0) {
            if (TWindowShortListCtrl__check_controller_button(&controller_input_state.controllers[0], 2) != 0 ||
                TKeyBoardControl::read_key_checked(0x4C) != 0) {
                cancel = 1;
                result = 0x10;
            }
            if (func_801A5E54__Fv() != 0) {
                cancel = 1;
                result = 0x11;
            }
        } else {
            countdown--;
        }
        TLobby__sub_801472F8(&state, &reason);
        if (state == 5 || state == 8 || state == 4) {
            break;
        }
        if (cancel != 0) {
            break;
        }
        send_and_handle__6TLobbyFv();
    } while (state != 4);
    if (state == 4 && cancel == 0) {
        TLobby__sub_803FB184(&status);
        lbl_8050C0A8[0] = 4;
        lbl_8050C0A8[1] = status.w10;
        lbl_8050C0A8[2] = 0;
        lbl_8050C0A8[3] = 0;
        TLobby__sub_8042315C((s16)lbl_805D2D00, lbl_8050C0A8);
        TLobby::set_battle_flag(status.w10);
        lobby_dns_server_addr = status.w18;
        lbl_805D56E0 = status.w1C;
        return TLobby::set_dns_servers();
    }
    lbl_805D2D00 = -1;
    stop.wait = 0;
    TLobby__sub_803FB1A4(&stop.wait);
    do {
        TLobby__sub_803FB184(&final_status);
        send_and_handle__6TLobbyFv();
    } while (final_status.state != 0);
    if (cancel != 0) {
        return result;
    }
    switch (reason) {
    case 3:
        return 5;
    case 2:
        return 7;
    case 6:
        return 8;
    case 0:
    case 1:
    case 7:
    default:
        return 4;
    }
}
#define lbl_8050C784 (*(Cfg_801471A0 *)lobby_account_entries)

s32 TLobby__sub_801478C4(s32 arg0) {
    s32 count;
    s32 result;
    char name[0x81];
    result = 4;
    count = TLobby__sub_80146724();
    for (lbl_805D5708 = 0; lbl_805D5708 < count; lbl_805D5708++) {
        ((void *(*)(void *, s32, u32))memset)(name, 0, sizeof(name));
        ((char *(*)(char *, const char *, u32))strncpy)(name, (const char *)TLobby__sub_80146CA0(lbl_805D5708), sizeof(name));
        if (name[0] != 0) {
            result = TLobby__sub_8014734C(lbl_805D5708, arg0);
            if (TLobby__sub_801466F4(result) == 0) {
                return result;
            }
        }
    }
    return result;
}

void TLobby__sub_80147978(void) {  }
#undef lbl_8050C784
struct Acct_8014797C {
    char host[0x80];
    char user[0x20];
    char pass[0x20];
    char dns1[0x20];
    char dns2[0x20];
    char f100[0x40];
    char f140[0x40];
    char f180[0x40];
    u32 f1C0;
    u32 f1C4;
    s32 valid;
};
#define lbl_8050C784 (*(Acct_8014797C (*)[3])lobby_account_entries)
#define memset ((void *(*)(void *, s32, u32))memset)
#define strncpy ((char *(*)(char *, const char *, u32))strncpy)
void TLobby::init_account_entries() {
    memset(&lbl_8050C784[0], 0, sizeof(Acct_8014797C));
    memset(&lbl_8050C784[1], 0, sizeof(Acct_8014797C));
    memset(&lbl_8050C784[2], 0, sizeof(Acct_8014797C));
    lbl_8050C784[0].valid = 0;
    lbl_8050C784[1].valid = 0;
    lbl_8050C784[2].valid = 0;
    lbl_805D5714 = 0;
    TLobby__net_session_mode = 0;
    TLobby__connect_pending_flags = 0;
    if (TLobby__sub_8014618C() != 0) {
        TLobby__net_session_mode = 1;
    }
    TLobby::load_network_configs();
    memset(lbl_8050CE14, 0, 0x20);
    strncpy(lbl_8050CE14, lbl_8050C784[2].user, 0x1F);
    memset(lbl_8050CE34, 0, 0x20);
    strncpy(lbl_8050CE34, lbl_8050C784[0].user, 0x1F);
}
#undef lbl_8050C784
#undef memset
#undef strncpy

void fn_80147A60(int a0) { keyboard_buffer_cursor = a0; }

void fn_80147A68(void) { keyboard_buffer_cursor = 0; }
}
typedef char RecoveredGlobal_80147A74_lbl_804EF500_size[sizeof(RecoveredGlobal_80147A74_lbl_804EF500) == 0x98 ? 1 : -1];
s32 *get_ppp_password_buffer(void) {
    return &ppp_password_buffer.value;
}
#undef TLobby__sub_803FB184
