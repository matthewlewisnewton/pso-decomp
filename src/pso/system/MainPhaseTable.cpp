#include "pso/system/MainPhaseTable.h"

#include "pso/TAdEndText.h"
#include "pso/TAdMultiChgGameModeGC.h"
#include "pso/TItemReverseTech.h"
#include "pso/menu/TAdEndText_80307A34.h"
#include "pso/misc/TEnding.h"
#include "pso/misc/TKeyBoardControl.h"
#include "pso/misc/TKeyBoardControl_802A1180.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TLogo.h"
#include "pso/ui/TAdMultiChgGameModeGC_8023F4E4.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/ui/TAdSinglePlyChrSelectGC_8033A8EC.h"
#include "pso/ui/TAdTrialModemChkGC.h"
#include "pso/unk/text_8008C4F4.h"
#include "pso/unk/text_8023F3F8.h"
#include "pso/unk/text_80290BEC.h"
#include "pso/unk/text_802A1154.h"

void init_offline_game_scene();
void dispatch_offline_main_frame();
void run_online_lobby_scene();
void cleanup_online_lobby_scene();

MainPhaseEntry main_phase_table[] = {
    {0, 0, 0},
    {init_logo_scene__5TLogoFv, run_frame__5TLogoFv, TLogo__sub_8013F5AC},
    {TAdMultiChgGameModeGC__sub_8023F62C, fn_8023F3F8, TLobby::release_scene_resources},
    {TKeyBoardControl::update_menu_scene, update_movie_phase, fn_802A1154},
    {TAdMultiChgGameModeGC__sub_8023F4E4, fn_8023F3F8, TLobby::release_scene_resources},
    {TKeyBoardControl::update_main_menu_scene, run_main_frame, fn_80290BEC},
    {TAdMultiChgGameModeGC::render_game_mode_change, fn_8023F3F8, TLobby::release_scene_resources},
    {TAdMultiChgGameModeGC__sub_8023F5B4, fn_8023F3F8, TLobby::release_scene_resources},
    {start_ending_sequence, TKeyBoardControl::run_main_frame, TAdEndText::cleanup},
    {TAdMultiChgGameModeGC::render_scene, fn_8023F3F8, TLobby::release_scene_resources},
    {TAdMultiChgGameModeGC__sub_8023F564, fn_8023F3F8, TLobby::release_scene_resources},
    {TAdMultiChgGameModeGC__sub_8023F58C, fn_8023F3F8, TLobby::release_scene_resources},
    {TEnding::set_flag_and_advance, run_game_frame, fn_8008C4F4},
    {TAdMultiChgGameModeGC__sub_8023F50C, fn_8023F3F8, TLobby::release_scene_resources},
    {init_offline_game_scene, dispatch_offline_main_frame, TLobby::teardown_scene},
    {run_online_lobby_scene, TLobby::update_camera_state, cleanup_online_lobby_scene},
    {TEnding::start_ending_scene, run_game_frame, fn_8008C4F4},
    {0, 0, 0},
    {init_single_player_char_select_scene, TAdSinglePlyChrSelectGC::run_frame, TAdSinglePlyChrSelectGC__sub_8033B264},
    {TAdTrialModemChkGC__sub_803354E8, TAdTrialModemChkGC::check_modem_result, TAdTrialModemChkGC__sub_803354A4},
    {0, 0, 0},
    {TItemReverseTech::init_scene, TItemReverseTech::run_frame, TItemReverseTech::run_cleanup_callbacks},
};
