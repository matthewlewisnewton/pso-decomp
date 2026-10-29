#include "types.h"
#include "pso/enemy/TObjEneRe2Flower.h"

struct O_800C3B8C { u8 pad[0x3c4]; u32 flags; };

s32 TObjEneRe2Flower::sub_800C3B8C() {
    O_800C3B8C *self = (O_800C3B8C *)this;
    u32 f = self->flags;
    if (f & 0x800) {
        return false;
    }
    return (f & 0x400) != 0;
}
