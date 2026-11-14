#include "pso/object/TObjCMIcon_80299488.h"
#include "pso/object/TObjCMMainMenu.h"
#include "pso/render/render_util.h"
#include "pso/ui/UISprite.h"

#pragma common off
CreationIconState creation_icon_states[7];
f32 TObjCMIcon__horizontal_scroll_offset;
#pragma common reset

extern "C" {
extern f32 cm_icon_screen_position[];
static const f32 lbl_805DDC44 = 0.1666666716337204f;
static const f32 lbl_805DDC48 = -0.06666667014360428f;
static const f32 lbl_805DDC4C = 0.05000000074505806f;
static const f32 lbl_805DDC50 = 8.0f;
static const f32 lbl_805DDC54 = 0.15000000596046448f;
}

void TObjCMIcon::reset_icon_flags() {
    s32 i;
    CreationIconState *p = creation_icon_states;
    for (i = 0; i < 7; i++) {
        p->hidden = 1;
        p++;
    }
}

void TObjCMIcon__sub_802994B0(s32 icon_index) {
    creation_icon_states[icon_index].hidden = 0;
}

void TObjCMIcon__sub_802994C8(s32 count, const s32 *icon_indices) {
    s32 i;
    TObjCMIcon::reset_icon_flags();
    for (i = 0; i < count; i++) {
        TObjCMIcon__sub_802994B0(icon_indices[i]);
    }
}

void TObjCMIcon::init_icon_table() {
    CreationIconState *entry;
    s32 i;
    i = 0;
    entry = creation_icon_states;
    do {
        TObjCMIcon__sub_8029957C(entry, &creation_initial_icon_state);
        i += 1;
        entry++;
    } while (i < 7);
    TObjCMIcon__horizontal_scroll_offset = 0.0f;
}

// A mutable source preserves the original interleaved load/store order.
void TObjCMIcon__sub_8029957C(CreationIconState *destination, CreationIconState *source) {
    destination->hidden = source->hidden;
    destination->fade = source->fade;
    destination->x = source->x;
}

// Both callers supply the icon receiver; the helper currently returns the ID unchanged.
s32 TObjCMIcon__sub_80299598(TObjCMIcon *icon, s32 sprite_id) {
    return sprite_id;
}

void TObjCMIcon::render() {
    s32 sorted_indices[7];
    f32 sorted_alpha[7];
    vec2f position;
    s32 index;
    s32 sort_index;
    s32 icon_index;
    CreationIconState *state;
    CreationIconGroup *group;
    s32 sprite_index;
    s32 previous_index;
    s32 sprite_id;
    f32 alpha;
    f32 previous_alpha;
    f32 depth;
    f32 draw_alpha;
    f32 screen_x;
    // Draw smaller squared fades first; equal fades retain their icon order.
    state = creation_icon_states;
    for (index = 0; index < 7; index++, state++) {
        alpha = state->fade * state->fade;
        icon_index = index;
        for (sort_index = 0; sort_index < index; sort_index++) {
            if (alpha < sorted_alpha[sort_index]) {
                previous_alpha = alpha;
                previous_index = icon_index;
                icon_index = sorted_indices[sort_index];
                alpha = sorted_alpha[sort_index];
                sorted_indices[sort_index] = previous_index;
                sorted_alpha[sort_index] = previous_alpha;
            }
        }
        sorted_indices[sort_index] = icon_index;
        sorted_alpha[sort_index] = alpha;
    }
    set_depth_buffer_settings_1();
    set_draw_list_mask(2);
    screen_x = cm_icon_screen_position[0] - TObjCMIcon__horizontal_scroll_offset;
    for (index = 0; index < 7; index++) {
        icon_index = sorted_indices[index];
        draw_alpha = sorted_alpha[index];
        group = &TObjCMIcon__icon_group_table[icon_index];
        position.x = screen_x + creation_icon_states[icon_index].x;
        position.y = cm_icon_screen_position[1] * TObjCMMainMenu::get_scale();
        // Preserve the integer division used by the original depth calculation.
        depth = (-2.0f) - (1.0f - (f32)(index / 7));
        for (sprite_index = 0; sprite_index < group->count; sprite_index++) {
            sprite_id = TObjCMIcon__sub_80299598(this, group->sprite_ids[sprite_index]);
            draw_ui_sprite(sprite_id, &position, depth, draw_alpha);
            position.x += (f32)(TObjCMMainMenu::get_creation_sprite_id(sprite_id) + 4);
        }
    }
    restore_saved_depth_alpha_state();
}
#pragma push
#pragma fp_contract on
void TObjCMIcon::run_task() {
    CreationIconState *state;
    CreationIconGroup *group;
    s32 index;
    f32 shifted_x;
    f32 target_x;
    state = creation_icon_states;
    for (index = 0; index < 7; index++, state++) {
        if (state->hidden == 0) {
            if ((state->fade += lbl_805DDC44) > 1.0f) {
                state->fade = 1.0f;
            }
        } else {
            if ((state->fade += lbl_805DDC48) < 0.0f) {
                state->fade = 0.0f;
            }
        }
    }
    target_x = 0.0f;
    group = TObjCMIcon__icon_group_table;
    state = creation_icon_states;
    {
        s32 icon_index;
        for (icon_index = 0; icon_index < 7; icon_index++, state++, group++) {
            if (state->hidden == 1) {
                shifted_x = state->x - 1.0f;
                state->x = shifted_x;
                if (shifted_x < 0.0f) {
                    state->x = 0.0f;
                }
            } else {
                s32 sprite_index;
                state->x += lbl_805DDC4C * (target_x - state->x);
                for (sprite_index = 0; sprite_index < group->count; sprite_index++) {
                    target_x += (f32)(TObjCMMainMenu::get_creation_sprite_id(
                        TObjCMIcon__sub_80299598(this, group->sprite_ids[sprite_index])) + 4);
                }
                target_x += lbl_805DDC50;
            }
        }
    }
    TObjCMIcon__horizontal_scroll_offset += lbl_805DDC54 * (target_x - TObjCMIcon__horizontal_scroll_offset);
}
#pragma pop
