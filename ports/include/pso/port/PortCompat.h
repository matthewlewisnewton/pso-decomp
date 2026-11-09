#ifndef PSO_PORT_COMPAT_H
#define PSO_PORT_COMPAT_H

// Host compatibility layer for the x86 port build.
//
// The matching GameCube build uses MWCC and the MSL/Dolphin headers. A host
// build uses the platform C/C++ library instead. The SMS PC and TP ports use
// a force-included compat header plus a host SDK overlay; this is the start of
// that layer for PSO. It is included only by the portable fallbacks and the
// x86 harness, never by the matching build.

#include <cmath>

#endif
