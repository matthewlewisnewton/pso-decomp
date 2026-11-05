#include "types.h"
#include "pso/ui/TAdFloorLoadPrtGC.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/unk/text_80086E28.h"
#include "pso/unk/text_8034AD38.h"
#include "pso/system/vector.h"
#include "pso/player/TObjPlayer.h"
struct Slot_8034AD38 { void *ctrl; u8 pad[0x18]; };

struct TAdFloorLoadPrtGC_8034AD38 {
    u8 pad0[0x18];
    void *vtable;
    u8 pad1c[0x34 - 0x1C];
    Slot_8034AD38 slots[32];
};

struct Vec_8034ADE0 { f32 x, y, z; };

struct Ang_8034ADE0 { s32 x, y, z; };

struct Slot_8034ADE0 { Vec_8034ADE0 pos; Ang_8034ADE0 ang; void *ctrl; };

struct Prt_8034ADE0 {
    s32 name;
    u8 pad4[0x18 - 4];
    void *vtable;
    Slot_8034ADE0 slots[32];
    void *bg;
};

struct Node_8034AF18 { s32 f0; s32 f4; };

extern "C" {
extern void *__vt__17TAdFloorLoadPrtGC[];
extern s16 lbl_804F0070[];
s32 __ct__7TObjectFP7TObject(void *);
void *memset(void *, int, u32);
extern Vec_8034ADE0 floor_load_particle_positions[];
extern Ang_8034ADE0 TAdFloorLoadPrtGC__emitter_angles[];
extern Vec_8034ADE0 lbl_80478B48[];
extern Ang_8034ADE0 lbl_80478B54[];
extern s32 lbl_805D4330;
Prt_8034ADE0 *TAdFloorLoadPrtGC__ct(Prt_8034ADE0 *arg0);
}
TAdFloorLoadPrtGC::~TAdFloorLoadPrtGC() {
    s32 i;
    if (*(void **)((u8 *)this + 0x39C)) {
        queue_destruction__7TObjectFv(*(void **)((u8 *)this + 0x39C));
        *(void **)((u8 *)this + 0x39C) = NULL;
    }
    for (i = 0; i < 32; i++) {
        if (((TAdFloorLoadPrtGC_8034AD38 *)this)->slots[i].ctrl) {
            queue_destruction__7TObjectFv(((TAdFloorLoadPrtGC_8034AD38 *)this)->slots[i].ctrl);
            ((TAdFloorLoadPrtGC_8034AD38 *)this)->slots[i].ctrl = NULL;
        }
    }
}


#pragma push
#pragma opt_common_subs off
Prt_8034ADE0 *TAdFloorLoadPrtGC__ct(Prt_8034ADE0 *arg0) {
    Ang_8034ADE0 *a;
    Vec_8034ADE0 *p;
    s32 i;
    __ct__7TObjectFP7TObject(arg0);
    arg0->vtable = __vt__17TAdFloorLoadPrtGC;
    arg0->name = lbl_805D4330;
    memset(arg0->slots, 0, sizeof(arg0->slots));
    arg0->bg = 0;
    for (i = 0; i < 12; i++) {
        VecCopy((Vec *)&arg0->slots[i].pos, (const Vec *)(p = &floor_load_particle_positions[i]));
        copy_xyz(&arg0->slots[i].ang, a = &TAdFloorLoadPrtGC__emitter_angles[i]);
        arg0->slots[i].ctrl = create_particle_controller_with_angles(p, a, 0x65, 1, 0x40);
    }
    arg0->bg = create_particle_controller_with_angles(lbl_80478B48, lbl_80478B54, 0x2F, 1, 0x40);
    return arg0;
}
#pragma pop

void push_recent_id(s16 arg0) {
    s32 i;
    if (arg0 != lbl_804F0070[0]) {
        for (i = 15; i > 0; i--) {
            lbl_804F0070[i] = lbl_804F0070[i - 1];
        }
        lbl_804F0070[0] = arg0;
    }
}
void clear_window_dd_nodes(void) {
    if (*(Node_8034AF18 **)((s8 *)lbl_804F0070 + 0x20) == NULL || *(Node_8034AF18 **)((s8 *)lbl_804F0070 + 0x24) == NULL) {
        return;
    }
    (*(Node_8034AF18 **)((s8 *)lbl_804F0070 + 0x20))->f4 = *(s32 *)((s8 *)lbl_804F0070 + 0x30);
    (*(Node_8034AF18 **)((s8 *)lbl_804F0070 + 0x24))->f4 = *(s32 *)((s8 *)lbl_804F0070 + 0x30);
    *(Node_8034AF18 **)((s8 *)lbl_804F0070 + 0x20) = NULL;
    *(Node_8034AF18 **)((s8 *)lbl_804F0070 + 0x24) = NULL;
    *(s32 *)((s8 *)lbl_804F0070 + 0x28) = 0;
    *(s32 *)((s8 *)lbl_804F0070 + 0x2C) = 0;
}
