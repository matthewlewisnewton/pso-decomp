#include "pso/player/TUnk_804A2548.h"

extern "C" const f32 lbl_805DAD54;

TUnk_804A2548::TUnk_804A2548(TObject *parent, void *params)
    : TUnk_804E355C(parent, params) {
    *(f32 *)&unk_C4 = lbl_805DAD54;
}
