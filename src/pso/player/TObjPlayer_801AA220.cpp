#include "pso/misc/ParticleFactory.h"
#include "types.h"
#include "pso/misc/TPhotonMagicSquare.h"
#include "pso/player/TObjPlayer.h"
#include "pso/misc/TCameraCtrl.h"

extern "C" {


s32 is_locally_controlled__10TObjPlayerFPv(s32);
s32 get_player_by_client_id(u16);
u32 __nw__7TObjectFUl(s32);
void play_effect_default__10TObjPlayerFii(s32 arg0, s32 arg1);

extern s32 tl_07;

void TObjPlayer::start_photon_blast(s32 arg0, u16 arg1) {
    s32 temp_r3;
    void *photon_blast_entry;
    void *temp_nw;

    temp_r3 = get_player_by_client_id(arg1);
    if (temp_r3 != 0) {
        photon_blast_entry = TObjPlayer::get_photon_blast_entry(arg0);
        if (is_locally_controlled__10TObjPlayerFPv(temp_r3) != 0) {
            play_effect_default__10TObjPlayerFii(temp_r3, *(s16 *)((s8 *)photon_blast_entry + 0x20));
        }
        spawn_particle_effect((const Vec *)((temp_r3 + 0x38)), 0x13D);
        TCameraCtrl::set_shake_preset(0);
        switch (arg0) {
        case 2:
            temp_nw = (void *) __nw__7TObjectFUl(0xD0);
            if (temp_nw != NULL) {
                ((TPhotonMagicSquare *)temp_nw)->construct_at_owner(tl_07, 2, arg1);
                return;
            }
            break;
        case 3:
            temp_nw = (void *) __nw__7TObjectFUl(0xD0);
            if (temp_nw != NULL) {
                ((TPhotonMagicSquare *)temp_nw)->construct_at_owner(tl_07, 3, arg1);
                return;
            }
            break;
        case 4:
            temp_nw = (void *) __nw__7TObjectFUl(0xD0);
            if (temp_nw != NULL) {
                ((TPhotonMagicSquare *)temp_nw)->construct_at_owner(tl_07, 4, arg1);
                return;
            }
            break;
        case 0:
            temp_nw = (void *) __nw__7TObjectFUl(0xD0);
            if (temp_nw != NULL) {
                ((TPhotonMagicSquare *)temp_nw)->construct_at_owner(tl_07, 0, arg1);
                return;
            }
            break;
        case 1:
            temp_nw = (void *) __nw__7TObjectFUl(0xD0);
            if (temp_nw != NULL) {
                ((TPhotonMagicSquare *)temp_nw)->construct_at_owner(tl_07, 1, arg1);
                return;
            }
            break;
        case 5:
            temp_nw = (void *) __nw__7TObjectFUl(0xD0);
            if (temp_nw != NULL) {
                ((TPhotonMagicSquare *)temp_nw)->construct_at_owner(tl_07, 5, arg1);
            }
            break;
        }
    }
}

    extern unsigned char photon_blast_entry_table[];
void*TObjPlayer::get_photon_blast_entry(int a0) {  return (char*)photon_blast_entry_table + a0 * 44; }

}
