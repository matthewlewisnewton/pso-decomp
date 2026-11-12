#include "types.h"
#include "pso/ui/window/TWindowDD.h"

extern "C" {

s32 measure_message_text_width(f32);


void measure_text_entry() {
    measure_message_text_width(1000000.0f);
}

}
