#include "types.h"
#include "pso/object/TObjMotion.h"
#include "pso/player/TObjPlayer.h"
#include "pso/misc/TPlyPhotonChair.h"

extern "C" {

int TFontSmallLobby__sub_801C0228(void*);
int check_flag__10TObjPlayerFl(void*, int);
int sub_8011E204__10TObjPlayerFl(void*, int);
int set_state_flags__10TObjPlayerFUl(void*, int);

void TObjPlayer::set_flag_200000() {
    s32 arg0 = (s32)this;
    sub_8011E204__10TObjPlayerFl((void*)arg0, 0x200000);
}
int TObjPlayer::check_flag_4() { return check_flag__10TObjPlayerFl(this, 4); }
void*TObjPlayer::set_invisible() { TFontSmallLobby__sub_801C0228(this); return this; }
int TObjPlayer::clear_flag_4000_callback() { return set_flag_4000(); }
int TObjPlayer::set_flag_4000() { return sub_8011E204__10TObjPlayerFl(this, 16384); }
int TObjPlayer::clear_flag_4000() { return set_state_flags__10TObjPlayerFUl(this, 16384); }
void TObjPlayer::set_battle_flag(s32 v) { this->m_3b4 = v; }
s32 TObjPlayer::get_anim_id() { return this->m_3b4; }
int TObjPlayer::check_flag_0x40000000() { return (this->m_334 >> 30) & 0x1; }
void TObjPlayer::clear_flag_0x2() { this->m_334 &= 0xfffffffd; }

}
