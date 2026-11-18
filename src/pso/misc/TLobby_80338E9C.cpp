#include "pso/misc/TLobby.h"
#include "pso/misc/TUnk_804EF4E0.h"

void *TLobby::create_object(void *heading) {
    return new TUnk_804EF4E0((s32)heading);
}

TUnk_804EF4E0::~TUnk_804EF4E0() {}
