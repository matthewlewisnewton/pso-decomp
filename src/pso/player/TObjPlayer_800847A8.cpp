#include "types.h"
#include "pso/player/TObjPlayer_800847A8.h"
#include "pso/player/TObjPlayer.h"

extern "C" {
f64 atan();
s32 GXSetTexCoordGen2(s32 a0 = 0, s32 a1 = 0, s32 a2 = 0, s32 a3 = 0, s32 a4 = 0, s32 a5 = 0);
    extern unsigned char camera_capture_flags;
extern u8 camera_capture_flags;
s32 TObjPlayer__sub_800847A8(void) {
    if ((camera_capture_flags & 2) && (camera_capture_flags & 1)) {
        return 1;
    }
    return 0;
}
unsigned char TObjPlayer__sub_800847CC(void) {  return camera_capture_flags; }
void TObjPlayer::set_tex_coord_gen(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    GXSetTexCoordGen2(arg0, arg1, arg2, arg3, 0, 0x7D);
}
void TObjPlayer__sub_800847FC(void) {  }
f32 TObjPlayer::get_end_text_value() {
    return (f32) atan();
}
void TObjPlayer__sub_80084824(f32 farg0, f32 farg1) {
    *(f32 *)0xCC008000 = farg0;
    *(f32 *)0xCC008000 = farg1;
}

void TObjPlayer__sub_80084834(s32 arg0) {
    *(s32 *)0xCC008000 = arg0;
}

void TObjPlayer__sub_80084840(f32 farg0, f32 farg1, f32 farg2) {
    *(f32 *)0xCC008000 = farg0;
    *(f32 *)0xCC008000 = farg1;
    *(f32 *)0xCC008000 = farg2;
}

int TObjPlayer::is_inactive() { return this->m_cfc == 0; }

}
