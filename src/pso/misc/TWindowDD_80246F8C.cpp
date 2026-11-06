#include "types.h"
#include "pso/misc/TWindowDD.h"

extern "C" {

s32 measure_message_text_width(f32);

extern const f32 lbl_805DCB70;

void TWindowDD::refresh_status_display() {
    measure_message_text_width(lbl_805DCB70);
}

}
