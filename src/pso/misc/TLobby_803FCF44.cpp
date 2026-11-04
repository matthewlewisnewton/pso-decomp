#include "types.h"
#include "pso/protocol/NetworkRuntime.h"

// CHAP challenge-buffer builder. The PPP units around this address are
// compiled -opt nocse, and a BSS object defined in that TU is pooled through
// ...bss.0. This function's two lbl_805C02D0 uses are direct ha/lo pairs,
// which MWCC 1.2.5n emits from the avetcp default (-O4,p, CSE on) when the
// object is defined in the other TU. See configure.py.

struct Self_803FD74C {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
    u8 f4;
    u8 f5;
    u8 f6;
    u8 f7;
    s16 f8;
    u8 padA[6];
    u8 f10[0x1C];
    void *tbl;
    void *f30;
};

struct Chap_803FC728 {
    const char *name;
    const char *secret;
    const char *msg;
    s16 active;
    u8 id;
    u8 padF;
    u16 len;
};

typedef struct B_803FADA0 {
    u8 *buf;
    u16 len;
} B_803FADA0;

struct RecoveredGlobal_803FC178_lbl_805C02D0 {
    union {
        s32 value;
        u8 *p0;
    };
    u8 *p4;
    u8 *p8;
    u8 *pC;
    u8 *p10;
    u8 *p14;
    u8 *p18;
    u8 *p1C;
    char *p20;
    u8 pad24[4];
    s16 f28;
    u8 pad2A[0xC];
    u8 f36;
    u8 f37;
    u16 f38;
    u8 pad3A[6];
};

extern RecoveredGlobal_803FC178_lbl_805C02D0 lbl_805C02D0;

struct ChapName_803FCF44 {
    char data[7];
};

extern "C" {
void NetMemcpy(void *, void *, int);
B_803FADA0 *init_net_buffer_entry__6TLobbyFUs(u16);
extern u16 lbl_805D7A9A;
}

// The binary's symbol is global in .sdata2. A plain C++ const lands there
// but is local, so the unit cannot be linked. extern without a section
// attribute moves it to .sdata (r13); the original loads are sda21 off r2.
__declspec(section ".sdata2") extern const ChapName_803FCF44 lbl_805E1158 = { "avetcp" };

extern "C" B_803FADA0 *TLobby__sub_803FCF44(Self_803FD74C *fsm) {
    Chap_803FC728 *chap = (Chap_803FC728 *)fsm->f30;
    s32 tick;
    ChapName_803FCF44 name = lbl_805E1158;
    B_803FADA0 *buf;
    u8 *p;
    s16 i;
    s16 len;

    if (chap->name == NULL || chap->secret == NULL) {
        return NULL;
    }
    buf = init_net_buffer_entry__6TLobbyFUs(0);
    if (buf == NULL) {
        return NULL;
    }
    p = buf->buf;
    NetStoreTick(&tick);
    lbl_805D7A9A = (tick & 0x1F) + 0x10;
    *p++ = lbl_805D7A9A;
    NetStoreTick(&tick);
    for (i = 0; i < lbl_805D7A9A; i++) {
        *p++ = tick;
    }
    NetCopyString((char *)p, name.data);
    buf->len += lbl_805D7A9A + (u16)NetStringLength(name.data) + 1;
    len = buf->len;
    if (len > lbl_805C02D0.f28) {
        len = lbl_805C02D0.f28;
    }
    NetMemcpy(lbl_805C02D0.p8, buf->buf, len);
    return buf;
}
