#ifndef PSO_EFFECT_TUNK_804DDF04_H
#define PSO_EFFECT_TUNK_804DDF04_H

#include "pso/TObject.h"
#include <stddef.h>

// Indirect-effect manager: its original name remains unresolved.
struct TUnk_804DDF04 : TObject {
    TUnk_804DDF04(s32 kind, TObject *parent);
    virtual ~TUnk_804DDF04();

    u8 kind;
};

typedef char IndirectManagerSize[sizeof(TUnk_804DDF04) == 0x20 ? 1 : -1];
typedef char IndirectManagerKind[offsetof(TUnk_804DDF04, kind) == 0x1C ? 1 : -1];
typedef char IndirectManagerBaseSize[sizeof(TObject) == 0x1C ? 1 : -1];
typedef char IndirectManagerBaseDataEnd[offsetof(TObject, m_down) + sizeof(TObject *) == 0x18 ? 1 : -1];
// MWCC's inherited vptr follows that base data; constructor/destructor probes
// additionally verify their native vptr stores at 0x18.
typedef char IndirectManagerVptrSlot[sizeof(TObject) - sizeof(void *) == 0x18 ? 1 : -1];

// Keep the existing external spelling while giving the original manager
// receiver its actual type. This boundary emits no forwarding thunk.
extern "C" void draw_field_1c__6TSceneFlll(TUnk_804DDF04 *manager, s32 sampler, s32 arg2, s32 arg3);

#endif
