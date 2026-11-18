#include "pso/ui/window/TWindowMenuIconLine.h"
#include "pso/unk/WindowLayoutRecord.h"

extern "C" WindowDescriptor lbl_804D0604;

TWindowMenuIconLine::TWindowMenuIconLine(u8 *position, u32 count, s16 client, u8 *descriptor)
    : TWindowAddition(descriptor, client, position) {
    vfunc_6(count, client);
}

TWindowMenuIconLine::TWindowMenuIconLine(u8 *position, u32 count, s16 client)
    : TWindowAddition((u8 *)&lbl_804D0604, client, position) {
    vfunc_6(count, client);
}
