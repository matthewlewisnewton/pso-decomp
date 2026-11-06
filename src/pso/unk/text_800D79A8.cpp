#include "types.h"
#include "pso/misc/TAttackTrace.h"
#include "pso/unk/TUnk_80494968.h"
struct Ent_800D79A8 { u8 pad[0xc]; s32 fc; u8 pad2[0xc]; s32 f1c; };

struct Obj_800D79A8 { u8 pad[0x18]; void *vt; u8 pad1c[4]; Ent_800D79A8 ents[8]; s32 f120; s32 f124; };

extern "C" {
extern u8 __vt__13TUnk_80494968[];
Obj_800D79A8 *fn_800D79A8(Obj_800D79A8 *self, s32 x, s32 a, s32 b);
Obj_800D79A8 *fn_800D79A8(Obj_800D79A8 *self, s32 x, s32 a, s32 b) {
    s32 i;
    Ent_800D79A8 *p;
    TAttackTrace__ct(self);
    self->vt = __vt__13TUnk_80494968;
    ((TUnk_80494968 *)self)->sub_800D7818(a, b);
    p = self->ents;
    for (i = 0; i < 8; i++) {
        p->fc = self->f120;
        p->f1c = self->f124;
        p++;
    }
    return self;
}

}
