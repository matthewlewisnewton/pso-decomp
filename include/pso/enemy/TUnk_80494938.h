#ifndef PSO_ENEMY_TUNK_80494938_H
#define PSO_ENEMY_TUNK_80494938_H

// Upstream calls this class TUnk_80494938. On the fork it is MaterialOpacityFade:
// the vtable is __vt__19MaterialOpacityFade at 0x80494938, and the constructor,
// destructor, and start_fade_in are the same addresses. A typedef keeps
// upstream's Dubchik source unchanged while relocations use the fork's symbols.
#include "pso/misc/MaterialOpacityFade.h"

// MWCC rejects alias-declarations. A typedef keeps the existing mangling.
typedef MaterialOpacityFade TUnk_80494938;

#endif
