#include "pso/item/TItemReverseTech_8011A1E8.h"

#include "pso/TAdEndText.h"
#include "pso/TItemReverseTech.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TLobby_800FC3CC.h"
#include "pso/ui/TAdRicoRingCtrl.h"

extern "C" void reset__11TCameraCtrlFv();

ReverseTechSceneHook TItemReverseTech__cleanup_callback_table[] = {
    {TCameraCtrl::reset_view_state, reset__11TCameraCtrlFv},
    {TCameraCtrl::init_default_view, TCameraCtrl::reset_default_view},
    {TLobby::update_keyboard_menu, TLobby::free_keyboard_soft_resources},
    {TLobby::set_ending_callback, TLobby__sub_800FC3CC},
    {TAdRicoRingCtrl::load_static_resource, TAdRicoRingCtrl::release_global_805D4A00},
    {TAdEndText::load_ending_font, TAdEndText::free_resources},
    {TItemReverseTech::load_textures, free__16TItemReverseTechFv},
};
