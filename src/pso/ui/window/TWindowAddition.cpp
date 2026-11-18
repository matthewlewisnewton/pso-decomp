#include "pso/ui/window/TWindowAddition.h"

TWindowAddition::~TWindowAddition() {}

TWindowAddition::TWindowAddition(u8 *descriptor, s16 client, u8 *parent)
    : TWindowBase(descriptor, client, parent) {
    init_content_frame(descriptor);
}
