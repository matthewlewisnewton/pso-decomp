#include "pso/ui/window/TWindowAddition.h"

extern "C" void sub_802443B4__15TWindowAdditionFv(void *, void *);

TWindowAddition::~TWindowAddition() {}

TWindowAddition::TWindowAddition(u8 *descriptor, s16 client, u8 *parent)
    : TWindowBase(descriptor, client, parent) {
    sub_802443B4__15TWindowAdditionFv(this, descriptor);
}
