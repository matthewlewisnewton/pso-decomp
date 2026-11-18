#ifndef PSO_MISC_ACTIONPALETTETAGABI_H
#define PSO_MISC_ACTIONPALETTETAGABI_H
#include "types.h"
// Historical exports operating on a four-byte tag prefix, not a palette window.
// Other legacy one-argument callers retain separate unresolved ABI views.
extern "C" {
void set_slot__20TWindowActionPaletteFUc(void *tag, u8 value);
void set_mode__20TWindowActionPaletteFUc(void *tag, u8 value);
}
#endif
