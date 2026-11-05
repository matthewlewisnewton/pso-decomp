#include "types.h"
#include "pso/player/TObjPlayer_8012AF50.h"
struct Elem_8012AF00 { u8 b[4]; };

struct Obj_8012AF00 { u32 f0; Elem_8012AF00 arr[10]; };

extern "C" {
void *__construct_array(void *, void *, void *, u32, u32);
void clear_lockon_list__10TObjPlayerFPvPvff(void *p);
Obj_8012AF00 *TObjPlayer__sub_8012AF00(Obj_8012AF00 *self);
Obj_8012AF00 *TObjPlayer__sub_8012AF00(Obj_8012AF00 *self) {
    __construct_array(self->arr, (void *)TObjPlayer__sub_8012AF50, 0, 4, 10);
    clear_lockon_list__10TObjPlayerFPvPvff(self);
    return self;
}

}
