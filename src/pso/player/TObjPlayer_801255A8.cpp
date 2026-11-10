#include "types.h"
#include "pso/player/TUnk_804A2548.h"
#include "pso/unk/text_802E4A4C.h"

extern "C" {

extern unsigned char lbl_804A2548[];
extern const float lbl_805DAD54;

void *construct_explosion_collider__13TUnk_804A2548Fv(void *storage, TObject *parent, void *params) {
    TUnk_804A2548 *self = (TUnk_804A2548 *)storage;
    __ct__13TUnk_804E355CFP7TObjectPv(self, parent, params);
    *(const void **)((u8 *)self + 0x18) = lbl_804A2548;
    *(f32 *)&self->unk_C4 = lbl_805DAD54;
    return self;
}

}
