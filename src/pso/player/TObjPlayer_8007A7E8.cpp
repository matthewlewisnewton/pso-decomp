#include "types.h"
#include "pso/unk/text_8007A7B8.h"

extern const float lbl_805D91F0;

// Retain the original export while describing its actual record receiver.
extern "C" void clear_velocity_vectors__10TObjPlayerFv(Record_8007A7B8 *record) {
    record->point.z = lbl_805D91F0;
    record->point.y = lbl_805D91F0;
    record->point.x = lbl_805D91F0;
    record->normal.z = lbl_805D91F0;
    record->normal.y = lbl_805D91F0;
    record->normal.x = lbl_805D91F0;
    record->flags = 0;
}
