#include "pso/misc/TUnk_804CE7E8.h"

TUnk_804CE7E8::TUnk_804CE7E8(void *position, s32 client)
    : TWindowMenuIconLine((u8 *)position, 5, (s16)client) {
    sub_80248B7C(client);
}
