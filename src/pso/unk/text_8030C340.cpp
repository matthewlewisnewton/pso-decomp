#include "types.h"
#include "pso/unk/text_8030C340.h"
extern "C" {
void *__nw__7TObjectFUl(int);
u8 *TWindowPartyStatus__ct(u8 *arg0, s32 arg1, s32 arg2);
}
extern s32 local_client_id;
extern u8 party_status_window_params[];
#pragma push
#pragma opt_propagation off
void *create_party_status_window(s32 arg0) {
    void *o;
    s32 n = arg0 + 1;
    s32 g = local_client_id;
    u32 slot = (u32)(g + n) & 3;
    o = __nw__7TObjectFUl(0x78);
    if (o != NULL) {
        o = TWindowPartyStatus__ct((u8 *)o, slot, (s32)party_status_window_params);
    }
    return o;
}
#pragma pop
