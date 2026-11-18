#include "types.h"
#include "pso/misc/TWindowPartyStatus.h"
#include "pso/unk/text_8030C340.h"
extern "C" {
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
    o = new TWindowPartyStatus(slot, party_status_window_params);
    return o;
}
#pragma pop
