#ifndef PSO_MISC_TEXTENTRYMEASUREMENTINLINE_H
#define PSO_MISC_TEXTENTRYMEASUREMENTINLINE_H

#include "pso/misc/TextEntryMeasurement.h"
#include "types.h"

// ChallengeResult supplies the linked body at 0x80246F8C. The balloon also
// needs the weak inline copy to emit its own maximum-width literal.
extern "C" {
void measure_message_text_width(void *entry, f32 max_width);

inline void measure_text_entry(void *entry) {
    measure_message_text_width(entry, 1000000.0f);
}
}

#endif
