#include "types.h"

// Scalar objects from the original 805D8E28..805D8ED0 data unit. Keep
// these definitions separate from their readers so the compiler retains
// each exported load without folding values or emitting duplicate literals.
// See docs/evidence/gryphon-behavior-constant-pool.md.
extern "C" {
extern const f32 lbl_805D8E28 = 16384.0f;
extern const f32 lbl_805D8E2C = 5120.0f;
extern const f32 lbl_805D8E30 = 230.0f;
extern const f32 lbl_805D8E34 = 0.25f;
extern const f32 lbl_805D8E38 = 1.5f;
extern const f32 lbl_805D8E3C = 2.1f;
extern const f32 lbl_805D8E40 = 66.5f;
extern const f32 lbl_805D8E44 = 6144.0f;
extern const f32 lbl_805D8E48 = 116.5f;
extern const f32 lbl_805D8E4C = 300.0f;
extern const f32 lbl_805D8E50 = 120.0f;
extern const f32 lbl_805D8E54 = -4.0f;
extern const f32 lbl_805D8E58 = 3.5f;
extern const f32 lbl_805D8E5C = 18.0f;
extern const f32 lbl_805D8E60 = 68.0f;
extern const f32 lbl_805D8E64 = 210.0f;
extern const f32 lbl_805D8E68 = 420.0f;
extern const f32 lbl_805D8E6C = 463.0f;
extern const f32 lbl_805D8E70 = 290.0f;
extern const f32 lbl_805D8E74 = 405.0f;
extern const f32 lbl_805D8E78 = 455.0f;
extern const f32 lbl_805D8E7C = 265.0f;
extern const f32 lbl_805D8E80 = 600.0f;
extern const f32 lbl_805D8E84 = 110.0f;
extern const f32 lbl_805D8E88 = -30.0f;
extern const f32 lbl_805D8E8C = 115.0f;
extern const f32 lbl_805D8E90 = 484.0f;
extern const f32 lbl_805D8E94 = 23.0f;
extern const f32 lbl_805D8E98 = 24.0f;
extern const f32 lbl_805D8E9C = 20.5f;
extern const f32 lbl_805D8EA0 = 150.0f;
extern const f32 lbl_805D8EA4 = 0.15f;
extern const f32 lbl_805D8EA8 = 27.0f;
extern const f32 lbl_805D8EAC = 30.0f;
extern const f32 lbl_805D8EB0 = 28.0f;
extern const f32 lbl_805D8EB4 = 1.8f;
extern const f32 lbl_805D8EB8 = 70.0f;
extern const f32 lbl_805D8EBC = 14.0f;
extern const f32 lbl_805D8EC0 = 21.0f;
extern const f32 lbl_805D8EC4 = 8000.0f;
// The remaining four zero bytes are linker alignment, not a second float.
extern const f32 lbl_805D8EC8 = 1000.0f;
}
