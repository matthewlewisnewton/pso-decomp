#ifndef PSO_MISC_TLOBBY_80429598_H
#define PSO_MISC_TLOBBY_80429598_H

#include "types.h"
struct OSContext;

// Provisional native C boundaries for the EXI Ethernet driver.
extern "C" {
void TLobby__sub_80429648(void);
void TLobby__sub_80429AC8(void);
void TLobby__sub_80429B8C(s32 channel, OSContext *context);
s32 TLobby__sub_8042AAA0(void *context);
void TLobby__sub_8042B434(s32 channel, OSContext *context);
void TLobby__sub_8042B58C(u32 arg0, s32 arg1);
void TLobby__sub_8042BA48(s32 arg0, s32 arg1);
u32 TLobby__sub_8042BA8C(void *address);
}

#endif
