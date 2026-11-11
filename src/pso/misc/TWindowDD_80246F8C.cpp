#include "types.h"
#include "pso/misc/TextEntryMeasurement.h"

extern "C" {
void measure_message_text_width(void *entry, f32 max_width);
extern const f32 lbl_805DCB70;

void measure_text_entry(void *entry) {
    measure_message_text_width(entry, lbl_805DCB70);
}
}
