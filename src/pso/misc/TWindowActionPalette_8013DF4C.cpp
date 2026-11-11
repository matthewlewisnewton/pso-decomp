#include "types.h"
#include "pso/misc/TWindowActionPalette.h"
#include "pso/misc/TForceOperate.h"
#include "pso/misc/TMainCursor.h"

// These legacy entry points receive the four-byte palette entry, not a window.
void TWindowActionPalette::set_slot(u8 v) { ((u8 *)this)[1] = v; }
void TWindowActionPalette::set_mode(u8 v) { *(u8*)((char*)this + 0x0) = v; }
