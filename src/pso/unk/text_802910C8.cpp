#include "pso/ui/UISprite.h"

extern "C" void draw_default_sprite__12TChCrEffWallFv(s32 sprite_id,
                                                   const vec2f *position,
                                                   f32 depth) {
    draw_ui_sprite(sprite_id, position, depth, ui_sprite_unit_scale);
}
