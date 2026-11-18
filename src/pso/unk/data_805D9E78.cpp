#include "types.h"

// Shared constants for grass placement and enemy behavior.
extern "C" {
// The original object includes a zero word after the angle.
#ifdef __MWERKS__
__declspec(section ".sdata2")
#endif
extern const f32 lbl_805D9E78[2] = {360.0f, 0.0f};
extern const f32 lbl_805D9E80 = -0.1f;
extern const f32 lbl_805D9E84 = 310.0f;
extern const f32 lbl_805D9E88 = 155.0f;
extern const f32 TObjEneDD__data_805D9E8C = 0.0f;
extern const f32 lbl_805D9E90 = 0.3f;
extern const f32 lbl_805D9E94 = 65535.0f;
}
