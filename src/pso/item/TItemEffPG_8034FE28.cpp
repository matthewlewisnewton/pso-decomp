#include "types.h"
#include "pso/item/TItemEffPG_8034FE28.h"
#include "pso/item/TItemEffPG_8034FF4C.h"
#include "pso/item/TUnk_804F0C08.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_801AF2F0.h"

extern "C" {

void *__nw__7TObjectFUl(int);

extern s32 lbl_804F0C08[];

void *TUnk_804F0C08::initialize(void *arg1, void *arg2, void *arg3) {
    TItemEffPG__ct((u8 *)this, (s32)arg1, (u8 *)arg2);
    *(s32 **)((s8 *)this + 0x18) = lbl_804F0C08;
    *(void * *)&this->unk_D4 = arg3;
    return this;
}

void create__10TItemEffPGFPvPvPv(void *arg0, void *parent, void *item) {
    void *o;
    o = __nw__7TObjectFUl(0xD8);
    if (o != NULL) {
        ((TUnk_804F0C08 *)o)->initialize(arg0, parent, item);
    }
}

}

s32 TItemEffPG::vfunc_7() {
    TObjPlayer *player = get_player_by_client_id(m_a8);
    if (player == NULL) {
        return 0;
    }
    // 8034FEBC reads the opaque CC field as a floating-point charge threshold.
    if ((f32)player->get_photon_blast_charge() < *(f32 *)unk_CC) {
        return 0;
    }
    player->vfunc_76();
    return 1;
}
