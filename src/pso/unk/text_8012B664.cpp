#include "types.h"
#include "pso/item/TUnk_804A4E68.h"
#include "pso/player/TObjChara.h"
#include "pso/player/TObjPlayer.h"

extern "C" {
s32 test_action_mask__10TObjPlayerFl(void *, s32);
static const f32 lbl_805DAEA8 = 15.600000381469727f;
static const f32 lbl_805DAEAC = 20.399999618530273f;
static const f32 lbl_805DAEB0 = 12.0f;
static const f32 lbl_805DAEB4 = 24.0f;
static const f32 lbl_805DAEB8 = 14.399999618530273f;
static const f32 lbl_805DAEBC = 20.0f;
#pragma push
#pragma fp_contract on
void TUnk_804A4E68::update_attack() {
    s32 flag;
    s32 ok;
    s32 lo;
    s32 hi;
    f32 speed;
    f32 flo;
    f32 fhi;
    if (this->owner != NULL) {
        speed = ((TObjChara *)(this->owner))->get_frame();
        flag = ((TObjPlayer *)(this->owner))->is_flag_b0_4();
        ok = 1;
        if (test_action_mask__10TObjPlayerFl(this->owner, 0x20) != 0) {
            flo = lbl_805DAEA8;
            lo = 0;
            fhi = lbl_805DAEAC;
            hi = 0x4000;
        } else if (test_action_mask__10TObjPlayerFl(this->owner, 0x40) != 0) {
            flo = lbl_805DAEB0;
            lo = 0x4000;
            fhi = lbl_805DAEB4;
            hi = -0x4000;
        } else if (test_action_mask__10TObjPlayerFl(this->owner, 0x80) != 0) {
            flo = lbl_805DAEB8;
            lo = -0x4000;
            fhi = lbl_805DAEBC;
            hi = 0x2000;
        } else {
            ok = 0;
        }
        if (ok == 1) {
            if (flag == 0) {
                if (speed < flo) {
                    *(s32 *)&this->unk_1F8 = lo;
                } else if (flo <= speed && speed <= fhi) {
                    *(s32 *)&this->unk_1F8 = (s32)((speed - flo) * ((f32)(hi - lo) / (fhi - flo)) + (f32)lo);
                } else {
                    *(s32 *)&this->unk_1F8 = hi;
                }
            } else {
                *(s32 *)&this->unk_1F8 = hi;
            }
        }
    }
}
#pragma pop

}
