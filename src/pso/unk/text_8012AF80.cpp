#include "types.h"
struct Obj_8012AF80 { u16 a; u16 b; };

extern "C" {
void TObjPlayer__sub_8012AF80(Obj_8012AF80 *self);
void TObjPlayer__sub_8012AF80(Obj_8012AF80 *self) {
    self->a = 0xffff;
    self->b = 0;
}

}
