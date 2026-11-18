#include "pso/object/LobbyPigeonProfiles.h"
#include "pso/npc/NpcAnimationBinding.h"
#include "pso/object/TObjMotion.h"

extern "C" {
static __declspec(section ".rodata") const char path_object_class_name[] ATTRIBUTE_ALIGN(4) = "TObjPathObj";

extern const Entry_802C2C48 seabed_dolphin_path_profiles[5] = {
    {0, 0.2f, 0.6f, 0.1f, 182},
    {1, 0.2f, 0.6f, 0.1f, 182},
    {2, 0.2f, 0.6f, 0.1f, 182},
    {3, 0.2f, 0.6f, 0.1f, 182},
    {4, 0.2f, 0.6f, 0.1f, 182},
};
// The dolphin's one action (mode 1, motion 5 at 0.6 speed); inferred name: the action table of
// seabed_dolphin_anim_binding, which load_seabed_dolphin hands to TLobby::spawn_npc_enemy.
TObjMotionAction seabed_dolphin_actions[1] = {
    {1, 0, 5, 0.6f, 0},
};
extern const NpcAnimationBinding seabed_dolphin_anim_binding = {NULL, seabed_dolphin_actions, 0, 0, 1};
extern const Entry_802C2548 jungle_ebi_path_profiles[3] = {
    {1, 0.01f, 0.6f, 0.1f, 182, 5},
    {2, 0.01f, 0.6f, 0.1f, 182, 5},
    {3, 0.01f, 0.6f, 0.1f, 364, 5},
};
extern const Entry_802C1E34 lobby_pigeon_path_parameters[3] = {
    {1, 0.1f, 0.6f, 0.1f, 364},
    {2, 0.1f, 0.6f, 0.1f, 364},
    {3, 0.1f, 0.6f, 0.1f, 546},
};
extern const Entry_802C1660 jungle_seagull_path_profiles[3] = {
    {1, 0.1f, 0.6f, 0.1f, 364},
    {2, 0.1f, 0.6f, 0.1f, 364},
    {3, 0.1f, 0.6f, 0.1f, 546},
};
extern const Vec_802C17FC lbl_80471908 = {0.0f, 0.0f, 0.0f};
extern const Entry_802C0CAC lobby_pigeon_path_profiles[3] = {
    {1, {0.1f}, {2.0f}, 0.1f, 364},
    {2, {0.1f}, {2.0f}, 0.1f, 364},
    {3, {0.1f}, {2.0f}, 0.1f, 546},
};
extern const Vec_802C0F3C lobby_pigeon_zero_vec = {0.0f, 0.0f, 0.0f};
extern const f64 lbl_80471960[1] = {10430.38043493439};

const char *lbl_805D3EC0 = path_object_class_name;
}
