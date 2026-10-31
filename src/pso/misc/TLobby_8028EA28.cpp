#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/misc/TKeyBoardControl_80131C58.h"
#include "pso/misc/TLobby_800FC3CC.h"
#include "pso/unk/text_802910EC.h"
#include "pso/camera/CreationCamera.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TWindowCtrlMain.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

extern "C" {

void reset__11TCameraCtrlFv(void);

    extern int creation_menu_main_obj;
void TLobby::free_all_resources() { fn_80291138(); TLobby::stop_audio_streams(); delete (BmlResource *)((void*)creation_menu_main_obj); creation_menu_main_obj = 0; TAdSinglePlyChrSelectGC::free_global(); TAdSinglePlyChrSelectGC::free_singleton_805D65C0(); end_creation_view(); reset__11TCameraCtrlFv(); TCameraCtrl::reset_default_view(); TWindowCtrlMain::free_all_windows(); TKeyBoardControl__sub_80131F5C(); TLobby__sub_800FC3CC(); TLobby::free_keyboard_soft_resources(); TLobby::refresh_render_state(); }

}
