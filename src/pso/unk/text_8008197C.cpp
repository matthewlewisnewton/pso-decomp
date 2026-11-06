#include "types.h"
#include "pso/effect/TEF_PvrWave.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
struct Ent_8008197C { s32 a; s32 b; s32 c; };

struct Q_8008197C { Ent_8008197C *arr; };

struct R_8008197C { u8 pad[0x14]; Q_8008197C *q; };

struct O_8008197C { u8 pad0[0x18]; void *f18; s32 f1c; s32 f20; u8 pad24[8]; s32 f2c; s32 f30; s32 f34; };

extern "C" {
R_8008197C *TScene__sub_80081B24(void);
}
TEF_PvrWave::~TEF_PvrWave() {
    Q_8008197C *q;
    q = TScene__sub_80081B24()->q;
    q->arr[((O_8008197C *)this)->f20].c = ((O_8008197C *)this)->f34;
    q->arr[((O_8008197C *)this)->f20].b = ((O_8008197C *)this)->f30;
    q->arr[((O_8008197C *)this)->f20].a = ((O_8008197C *)this)->f2c;
    ((TAdSinglePlyChrSelectGC *)(((O_8008197C *)this)->f1c))->destroy_and_free(1);
}
