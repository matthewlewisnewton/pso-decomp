#include "types.h"
#include "pso/item/TItemEffPG_8034FE28.h"
#include "pso/item/TItemEffPG_8034FF4C.h"
#include "pso/item/TUnk_804F0C08.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_801AF2F0.h"

#include "pso/object/TObject_80019A50.h"
#include "pso/object/TObject_8001A448.h"
#include "pso/item/TUnk_804E355C.h"
#include "pso/item/TItemEffPG.h"
#include "pso/item/TItemAttackCol.h"

#pragma readonly_strings on

extern "C" {
const char *lbl_805D4350 = "TItemEffPG";
}

extern "C" {

void *__nw__7TObjectFUl(int);

TUnk_804F0C08::TUnk_804F0C08(TObject *parent, void *params, void *duration)
    : TItemEffPG(parent, params) {
    *(void **)&unk_D4 = duration;
}

void create__10TItemEffPGFPvPvPv(void *arg0, void *parent, void *item) {
    new TUnk_804F0C08((TObject *)arg0, parent, item);
}

}

s32 TItemEffPG::vfunc_7() {
    TObjPlayer *player = get_player_by_client_id(m_a8);
    if (player == NULL) {
        return 0;
    }
    if ((f32)player->get_photon_blast_charge() < m_cc) {
        return 0;
    }
    player->vfunc_76(m_cc);
    return 1;
}


extern "C" {
void *__nw__7TObjectFUl(int);
extern const char *lbl_805D4350;
extern const float lbl_805DFE14;
extern const f32 lbl_805DFE18;
int TObjPlayer__sub_802E451C(void);
s32 has_game_join_id__13TUnk_804E355CFv();

void TItemEffPG::run_task() {
    f32 temp_f1;
    f32 temp_f1_2;
    s32 var_r31;

    var_r31 = 1;
    if (has_game_join_id__13TUnk_804E355CFv() == 0) {
        var_r31 = 0;
    }
    if (this->vfunc_7() == 0) {
        var_r31 = 0;
    }
    if (var_r31 != 0) {
        temp_f1 = this->m_40;
        if (temp_f1 < *(f32 *)&this->unk_C4) {
            this->m_40 = (f32) (temp_f1 + this->m_c8);
            temp_f1_2 = *(f32 *)&this->unk_C4;
            if (temp_f1_2 < this->m_40) {
                this->m_40 = temp_f1_2;
            }
        }
        check_hits();
        return;
    }
    if ((u32) this->m_down == 0U) {
        queue_destruction__7TObjectFv(this);
        disallow_rendering__7TObjectFv(this);
        return;
    }
    if ((u32) this->m_d0 != 0U) {
        TItemEffPG__begin_visual_fade(*(void * *)&this->m_d0);
        this->m_d0 = 0U;
    }
}

TItemEffPG::~TItemEffPG() {}

TItemEffPG::TItemEffPG(TObject *parent, void *params)
    : TUnk_804E355C(parent, params) {
    u8 *arg2 = (u8 *)params;
    s32 temp_r3;
    s32 var_r0;
    *(s32 *)((s8 *)this + 0) = (s32) ((s32)lbl_805D4350);
    *(f32 *)((s8 *)this + 0xC4) = (f32) *(f32 *)((s8 *)arg2 + 0x28);
    if ((*(const f32 *)&lbl_805DFE14) < *(f32 *)((s8 *)this + 0xC4)) {
        *(f32 *)((s8 *)this + 0xC4) = (f32) (*(const f32 *)&lbl_805DFE14);
    }
    ((TItemEffPG *)this)->m_c8 = (f32) *(f32 *)((s8 *)arg2 + 0x30);
    ((TItemEffPG *)this)->m_cc = (f32) *(f32 *)((s8 *)arg2 + 0x2C);
    *(f32 *)((s8 *)this + 0xB0) = (f32) (*(f32 *)((s8 *)this + 0xB0) * lbl_805DFE18);
    temp_r3 = ((s32)__nw__7TObjectFUl(0x68));
    var_r0 = temp_r3;
    if (var_r0 != 0) {
        var_r0 = (s32)TItemEffPG__visual_ct((u8 *)temp_r3, (u8 *)this, (u8 *)arg2);
    }
    ((TItemEffPG *)this)->m_d0 = var_r0;
}

void TItemEffPG::create(void *arg0, void *arg1) {
    new TItemEffPG((TObject *)arg0, arg1);
}

    extern const float lbl_805DFE1C;
    extern const float lbl_805DFE20;
void*TItemEffPG::init_params() { TObjPlayer__sub_802E451C(); *(int *)&this->m_up = 10; this->position.y = lbl_805DFE14; this->position.z = lbl_805DFE1C; *(f32 *)&this->facing_yaw = lbl_805DFE20; return this; }

}
