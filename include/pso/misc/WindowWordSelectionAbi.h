#ifndef PSO_MISC_WINDOW_WORD_SELECTION_ABI_H
#define PSO_MISC_WINDOW_WORD_SELECTION_ABI_H

#include "types.h"

// Existing raw selection accessor: reads a signed halfword or returns 0x685.
// The receiver remains an opaque byte view; this does not establish ownership.
// Callers that retain a short result perform that conversion explicitly.
extern "C" int TWindowDD__sub_80342158(u8 *receiver);

#endif
