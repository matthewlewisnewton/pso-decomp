#include "types.h"
#include "pso/misc/TUnk_804CE018.h"
#include "pso/misc/TWindowSubStatusDisp.h"

void *TUnk_804CE018::get_array_entry(int i) { return ((void **)*(void **)((char *)this + 0x28))[i]; }
