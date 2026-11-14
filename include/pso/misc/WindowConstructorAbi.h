#ifndef PSO_MISC_WINDOWCONSTRUCTORABI_H
#define PSO_MISC_WINDOWCONSTRUCTORABI_H

#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowAddition.h"

// Existing C-named initializers receive allocated object storage. These are the
// actual compiler-emitted constructors, with their complete native argument
// contracts. The destructor flags below are the native hidden deleting flags;
// existing raw initializers/destroyers pass zero for base cleanup, as automatic
// C++ base destruction does. An explicit C++ destructor expression uses -1.
// No wrapper bodies or alternate mangled signatures are supplied.
// Recovered C++ constructors use base initializers, and factories use normal new.
extern "C" {
TWindowBase *__ct__11TWindowBaseFPUcsPUc(TWindowBase *storage, u8 * arg1, s16 arg2, u8 * arg3);
TWindowBase *__dt__11TWindowBaseFv(TWindowBase *storage, s16 flags);
TWindowAddition *__dt__15TWindowAdditionFv(TWindowAddition *storage, s16 flags);
}

#endif
