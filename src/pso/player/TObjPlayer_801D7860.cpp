#include "types.h"
#include "pso/player/TObjPlayer.h"
#include "pso/misc/TLobby.h"

extern "C" {
s32 TObjPlayer__sub_801C19C8(f32);
extern const f32 lbl_805DC3F0;
extern const f32 lbl_805DC3F4;
s32 TObjPlayer::init_sub_object(s32 arg0) {
    TObjPlayer::init_sub_object_vectors(arg0);
    return arg0;
}
void TObjPlayer::init_sub_object_vectors(s32 arg0) {
    TObjPlayer__sub_801C19C8(lbl_805DC3F0);
    ((TLobby *)arg0)->set_float_4(lbl_805DC3F0);
    ((TLobby *)arg0)->set_pos_z(lbl_805DC3F4);
    ((TLobby *)arg0)->set_scale(lbl_805DC3F4);
}

}
