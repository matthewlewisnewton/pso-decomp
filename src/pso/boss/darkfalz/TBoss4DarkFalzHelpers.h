#ifndef PSO_BOSS_DARKFALZ_TBOSS4DARKFALZHELPERS_H
#define PSO_BOSS_DARKFALZ_TBOSS4DARKFALZHELPERS_H

// Source-private definitions, included only by TBoss4DarkFalz_8004C93C.cpp.
void TBoss4DarkFalz__sub_8004D9A0(void* p, s32 v) { *(s32*)((char*)p + 0x90) = v; }

s32 TBoss4DarkFalz__sub_8004D990(u8 *arg0) {
    return *(s32 *)((s8 *)arg0 + 0x388) - *(s32 *)((s8 *)arg0 + 0x38C);
}

void TBoss4DarkFalz::get_demo2_params(u16 *a, u16 *b, u16 *out) {
    s32 i;
    *a = ((Obj_8004D92C *)this)->f2d6;
    *b = ((Obj_8004D92C *)this)->f2d4;
    for (i = 0; i < 4; i++) {
        out[i] = obj_getArrU16_FC(this, i);
    }
}

void get_defeat_params__14TBoss4DarkFalzFPvPvPvPv(Obj_8004D8C8 *self, u16 *a, u16 *b, u16 *out) {
    s32 i;
    *a = self->f2d6;
    *b = self->f2d4;
    for (i = 0; i < 4; i++) {
        out[i] = obj_getArrU16_FC(self, i);
    }
}

#endif
