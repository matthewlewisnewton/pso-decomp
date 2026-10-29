#include "types.h"
#include "pso/misc/TPlayerFootStamp_802B01D8.h"
#include "pso/TPlayerFootStamp.h"
#include "pso/boss/TBoss6PlotFalz.h"
#include "pso/object/TObjOnlineEnding.h"

#pragma readonly_strings on


struct Obj_802B0204 { u8 pad[0xbe]; s16 fbe; };

extern "C" {

s32 end_cutscene_camera__14TBoss6PlotFalzFPv();
int freeze_all_players__14TBoss6PlotFalzFv(void*);
u8 *load_gvm_texture_file(s32 arg0);
}

    extern int player_footstamp_texture_gvm_handle;
void load_player_footstamp(void) { player_footstamp_texture_gvm_handle = (int)load_gvm_texture_file((s32)(unsigned char *)"player_footstamp.GVM"); }

void TPlayerFootStamp::sub_802B0204(s32 v) {
    Obj_802B0204 *self = (Obj_802B0204 *)this;
    if (v < 0 || v > 1) {
        self->fbe = 0;
    } else {
        self->fbe = v;
    }
}

void TBoss6PlotFalz__sub_802B0228(TBoss6PlotFalz *boss6_plot_falz) {
    s32 temp_r0;

    temp_r0 = *(s32 *)((s8 *)boss6_plot_falz + 0x3CC) + 1;
    *(s32 *)((s8 *)boss6_plot_falz + 0x3CC) = temp_r0;
    if (temp_r0 > 0x1C6) {
        end_cutscene_camera__14TBoss6PlotFalzFPv();
        boss6_plot_falz->award_exp_and_destroy();
    }
}

void TBoss6PlotFalz::reset_ending_state() { freeze_all_players__14TBoss6PlotFalzFv(this); *(int*)((char*)this + 0x3d0) = 0; *(int*)((char*)this + 0x3cc) = 0; TObjOnlineEnding::create(this); }
