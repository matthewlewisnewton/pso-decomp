#include "pso/ui/window/TextEntryMeasurement.h"
#include "types.h"

extern "C" void measure_message_text_width(void *entry, f32 max_width);

void measure_text_entry(void *entry) {
    measure_message_text_width(entry, 1000000.0f);
}
