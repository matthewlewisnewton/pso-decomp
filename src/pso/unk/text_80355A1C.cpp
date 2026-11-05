#include "types.h"
#include "pso/unk/text_80355A1C.h"

extern "C" {
s32 TBoss8Dragon__sub_8005D700(void *self);
extern u8 lbl_804792D8[];
extern void *gryphon_tornado_particle_id_table;

void TBoss8Dragon__sub_80355A1C(void) {  }
void TBoss8Dragon__sub_80355A20(void *self) {
    switch (TBoss8Dragon__sub_8005D700(self)) {
    case 0:
        gryphon_tornado_particle_id_table = lbl_804792D8;
        break;
    }
}

}
