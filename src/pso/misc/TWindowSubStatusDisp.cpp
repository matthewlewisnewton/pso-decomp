#include "types.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowSubStatusDisp.h"

void *TWindowBase::get_array_entry(int i) { return ((void **)*(void **)((char *)this + 0x28))[i]; }
