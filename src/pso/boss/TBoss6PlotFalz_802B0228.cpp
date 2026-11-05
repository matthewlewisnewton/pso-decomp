// This call site branches to the out-of-line TObject::queue_destruction.
#define TOBJECT_OUT_OF_LINE_HELPERS
#include "types.h"
#include "pso/boss/TBoss6PlotFalz.h"
#include "pso/boss/TBoss6PlotFalzState.h"
#include "pso/boss/Boss6Type1Appearance.h"
#include "pso/boss/Boss6Type2Appearance.h"
#include "pso/boss/Boss6Type2Death.h"
#include "pso/boss/TBoss6Type2.h"
#include "pso/boss/TBoss4DarkFalz.h"
#include "pso/boss/TBoss6Thanks.h"
#include "pso/boss/TBoss6EmptyWarp.h"
#include "pso/object/TObjOnlineEnding.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"
#include "pso/misc/TLoadCtrl_80227390.h"
#include "pso/misc/TLobby.h"
#include "pso/system/SoundEffect.h"

// The Falz plot script: one {name, enter, leave, tick, update} entry per
// plot state. run_task calls tick through call_state_action, then update
// through run_phase_action. Built with deferred
// code generation, so the actions below are written in table order and come
// out in reverse.

extern "C" {
void obj_setArrS16_FC(void *obj, int index, u16 value);
}

extern u32 TBoss6PlotFalz__type2_instance;

// --- FALL_ELEV ---
void TBoss6PlotFalz::sub_802B0A34() {
    m_3d0 = 0;
    m_3cc = 0;
}
void TBoss6PlotFalz::advance_if_ready() {
    if (is_ready() != 0) {
        send_6xA3_action(2);
    }
}
void TBoss6PlotFalz::advance_intro_timer() {
    if (m_3cc == 0x69) {
        play_sound_effect(0x40030F00, 0, 0, 0);
    }
    m_3cc = m_3cc + 1;
    if (m_3cc > 0x12C) {
        set_state(1);
    }
}

// --- DEMO_START ---
void TBoss6PlotFalz::init_proto1_adx() {
    play_area_music("proto1.adx");
    TBoss6PlotFalz::freeze_all_players();
    m_3d0 = 0;
    m_3cc = 0;
    TBoss4DarkFalz::dispatch_by_main_phase(0x56);
    TBoss6Demo10_TYPE1_APPEAR__create(this);
}
void TBoss6PlotFalz::sub_802B08F0() {
    if (is_ready() != 0) {
        send_6xA3_action(2);
    }
}
void TBoss6PlotFalz::tick_timeout() {
    s32 next;

    refresh_players_equipment();
    next = m_3cc + 1;
    m_3cc = next;
    if (next > 0x1F4) {
        set_state(2);
    }
}

// --- VS_TYPE1 ---
void TBoss6PlotFalz::enter_active_state() {
    end_cutscene_camera();
    refresh_players_equipment();
    m_3d0 = 1;
    m_3cc = 0;
    spawn_type1();
}
void TBoss6PlotFalz::update_phase() {
    if ((TBoss6PlotFalz__sub_802ABADC() == 0) || (is_ready() != 0)) {
        send_6xA3_action(3);
    }
}
void TBoss6PlotFalz::sub_802B0808() {  }

// --- DEMO_DED_T1 ---
void TBoss6PlotFalz::reset_and_recreate() {
    s32 sp8;
    TBoss6PlotFalz::get_target_pos_b((s32)this, (s32)((void *)&sp8));
    queue_instance_destruction();
    TLobby::stop_audio_streams();
    TBoss6PlotFalz::freeze_all_players();
    m_3d0 = 0;
    m_3cc = 0;
    TBoss6PlotFalz::create(this, &sp8);
}
void TBoss6PlotFalz::set_state4_if_ready() {
    if (is_ready() != 0) {
        send_6xA3_action(4);
    }
}
void TBoss6PlotFalz::sub_802B06D0() {
    f32 f;
    refresh_players_equipment();
    if (m_3cc > 0xF7) {
        f = (f32)(m_3cc - 0xF7) / 8.0f;
        if (f > 1.0f) {
            f = 1.0f;
        }
        apply_fade_alpha(0, f);
    }
    if (++m_3cc > 0x101) {
        set_state(4);
    }
}

// --- DEMO_WAIT_T2 ---
void TBoss6PlotFalz::init_hall_boss_scene() {
    TBoss6EmptyWarp::init_warp();
    release_object();
    play_area_music("HALL.adx");
    refresh_players_equipment();
    m_3cc = 0;
    m_3dc = TObjFish::alloc(this);
}
void TBoss6PlotFalz::check_and_advance_state() {
    TObjPlayer *player = (TObjPlayer *)m_3dc;
    if ((player != NULL) && ((player->get_plot_state() != 0) || (is_ready() != 0))) {
        send_6xA3_action(5);
    }
}
void TBoss6PlotFalz::update_cutscene_fade() {
    s32 t = m_3cc;
    if (t <= 0x2D) {
        apply_fade_alpha(0, 1.0f);
    } else if (t > 0x2D && t < 0x10E) {
        apply_fade_alpha(0, (f32)(0x10E - t) / 225.0f);
    }
    if (m_3cc == 0x2D) {
        end_cutscene_camera();
    }
    m_3cc = m_3cc + 1;
}

// --- DEMO_APP_T2 ---
void TBoss6PlotFalz::stop_adx_audio() {
    if (m_3dc != NULL) {
        static_cast<TObject *>(m_3dc)->TObject::queue_destruction();
    }
    m_3dc = NULL;
    TBoss6PlotFalz::freeze_all_players();
    TLobby::stop_audio_streams();
    play_area_music("proto2.adx");
    m_3cc = 0;
    create_boss6_type2_appearance(this);
}
void TBoss6PlotFalz::advance_phase_if_ready() {
    if (is_ready() != 0) {
        send_6xA3_action(6);
    }
}
void TBoss6PlotFalz::advance_timer() {
    s32 next;

    refresh_players_equipment();
    next = m_3cc + 1;
    m_3cc = next;
    if (next > 0x198) {
        set_state(6);
    }
}

// --- VS_TYPE2 ---
void TBoss6PlotFalz::sub_802B0448() {
    end_cutscene_camera();
    refresh_players_equipment();
    m_3d0 = 0;
    m_3cc = 0;
    spawn_type2();
}
void TBoss6PlotFalz::check_action_7() {
    if ((TBoss6PlotFalz::is_boss_active() == 0) || (is_ready() != 0)) {
        send_6xA3_action(7);
    }
}
void TBoss6PlotFalz::sub_802B03F4() {  }

// --- DEMO_END ---
void TBoss6PlotFalz::finish_and_dispatch_next_phase() {
    s32 sp10[2];
    u16 out[4];
    s32 i;

    if ((u32)TBoss6PlotFalz__type2_instance != 0U) {
        ((TBoss6Type2 *)TBoss6PlotFalz__type2_instance)->get_phase_values(&m_2d6, &m_2d4, out);
        i = 0;
        do {
            obj_setArrS16_FC(this, i, out[i]);
            i += 1;
        } while (i < 4);
    }
    TBoss6PlotFalz::get_target_pos_a((s32)this, (s32)sp10);
    destroy_static_instance();
    TLobby::stop_audio_streams();
    TBoss6PlotFalz::freeze_all_players();
    m_3d0 = 0;
    m_3cc = 0;
    TBoss4DarkFalz::dispatch_by_main_phase(0x57);
    TBoss6Thanks::try_dispatch_darkfalz_phase();
    create_boss6_type2_death(this, sp10);
}
void TBoss6PlotFalz::update_plot_timer() {
    s32 next;

    refresh_players_equipment();
    if ((m_3cc > 1) && (is_ready() != 0)) {
        m_3cc = 0x2CA;
    }
    next = m_3cc + 1;
    m_3cc = next;
    if (next > 0x2CA) {
        if (is_ending_or_split_screen() != 0) {
            set_state(8);
            return;
        }
        end_cutscene_camera();
        award_exp_and_destroy();
    }
}

// --- OL_ENDING ---
void TBoss6PlotFalz::reset_ending_state() {
    TBoss6PlotFalz::freeze_all_players();
    m_3d0 = 0;
    m_3cc = 0;
    TObjOnlineEnding::create(this);
}
void TBoss6PlotFalz::sub_802B0228() {
    s32 next;

    next = m_3cc + 1;
    m_3cc = next;
    if (next > 0x1C6) {
        end_cutscene_camera();
        award_exp_and_destroy();
    }
}

TBoss6PlotFalzScriptState TBoss6PlotFalz__data_804DE66C[9] = {
    { "FALL_ELEV", &TBoss6PlotFalz::sub_802B0A34, 0,
      &TBoss6PlotFalz::advance_if_ready, &TBoss6PlotFalz::advance_intro_timer },
    { "DEMO_START", &TBoss6PlotFalz::init_proto1_adx, 0,
      &TBoss6PlotFalz::sub_802B08F0, &TBoss6PlotFalz::tick_timeout },
    { "VS_TYPE1", &TBoss6PlotFalz::enter_active_state, 0,
      &TBoss6PlotFalz::update_phase, &TBoss6PlotFalz::sub_802B0808 },
    { "DEMO_DED_T1", &TBoss6PlotFalz::reset_and_recreate, 0,
      &TBoss6PlotFalz::set_state4_if_ready, &TBoss6PlotFalz::sub_802B06D0 },
    { "DEMO_WAIT_T2", &TBoss6PlotFalz::init_hall_boss_scene, 0,
      &TBoss6PlotFalz::check_and_advance_state, &TBoss6PlotFalz::update_cutscene_fade },
    { "DEMO_APP_T2", &TBoss6PlotFalz::stop_adx_audio, 0,
      &TBoss6PlotFalz::advance_phase_if_ready, &TBoss6PlotFalz::advance_timer },
    { "VS_TYPE2", &TBoss6PlotFalz::sub_802B0448, 0,
      &TBoss6PlotFalz::check_action_7, &TBoss6PlotFalz::sub_802B03F4 },
    { "DEMO_END", &TBoss6PlotFalz::finish_and_dispatch_next_phase, 0, 0,
      &TBoss6PlotFalz::update_plot_timer },
    { "OL_ENDING", &TBoss6PlotFalz::reset_ending_state, 0, 0,
      &TBoss6PlotFalz::sub_802B0228 },
};
