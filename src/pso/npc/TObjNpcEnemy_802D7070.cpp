#include "pso/npc/NpcModelEntry.h"

extern const float lbl_805DE7D8;

void NpcModelEntry::reset() {
    id = 0;
    render_mode = 4;
    vertical_offset = lbl_805DE7D8;
    model = NULL;
    texture_list = NULL;
    collision_radius = lbl_805DE7D8;
    animation.motions = NULL;
    animation.actions = NULL;
    animation.default_action = 0;
    animation.mode2_action = 0;
    animation.debug_action_limit = 0;
}
