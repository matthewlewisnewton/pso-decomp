#include "types.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/enemy/TObjEneRe7Berura_803E4CE0.h"

struct Node_803E49FC {
    u32 flags;
    u32 f4;
    u8 pad8[0x2C - 0x8];
    struct Node_803E49FC *child;
    struct Node_803E49FC *next;
};

extern "C" {
s32 draw_chunk_vertices_cached(void *);
struct B_803E4BDC { u8 pad[0x28]; s32 f28; };
void bind_motion_context(void * motion, f32 frame);
extern s32 motion_angle_sampler_table[];
extern B_803E4BDC *current_motion_context;
void draw_model_motion(void *arg0, void *arg1, f32 farg0);
void bind_motion_blend_channels(u8 *link, f32 blend);
void draw_motion_bound(void *, void *, void *, f32, ModelDrawCallback);
void draw_chunk_model_with_shape_motion(void *arg0, void *arg1, void *arg2, f32 farg0);
s32 push_matrix();
s32 pop_matrix();
void compose_motion_node_matrix(void *arg0);
}
void select_motion_context(s32 arg0);
void draw_model_blend_motion(void *arg0, void *arg1, f32 farg0);
s32 draw_object_tree_recursive(void *arg);
void traverse_animated_node_tree(void *arg);
extern s32 chunk_render_flags;

void TObjPlayer::clear_move_state_bits() {
    chunk_render_flags &= 0xFFFFF9FF;
}

extern s32 player_chunk_draw_end_callback;

void TObjPlayer::set_global_state(s32 arg0) {
    player_chunk_draw_end_callback = arg0;
}

extern s32 motion_packed_rotation_mode;

void draw_blend_motion_tree(void *arg0, void *arg1, f32 blend, ModelDrawCallback draw) {
    bind_motion_blend_channels((u8 *)arg1, blend);
    if ((s32) motion_packed_rotation_mode != 0) {
        select_motion_context(1);
        *(s32 *)((s8 *)current_motion_context + 0x28) = (s32) *(s32 *)((s8 *)motion_angle_sampler_table + 0xC);
        select_motion_context(0);
        *(s32 *)((s8 *)current_motion_context + 0x28) = (s32) *(s32 *)((s8 *)motion_angle_sampler_table + 0xC);
    }
    model_draw_context->draw = draw;
    draw_object_tree_recursive(arg0);
}

s32 draw_object_tree_recursive(void *arg) {
    struct Node_803E49FC *arg0 = (struct Node_803E49FC *)arg;
    u32 t;
    do {
        push_matrix();
        ((TObjPlayer *)arg0)->apply_motion_node_transform();
        if (chunk_model_node_callback != NULL) {
            chunk_model_node_callback((NJS_OBJECT *)arg0);
        }
        t = arg0->f4;
        if (t != 0 && (arg0->flags & 8) == 0) {
            model_draw_context->draw((void *)t);
        }
        if (arg0->child != NULL) {
            draw_object_tree_recursive((void *)arg0->child);
        }
        pop_matrix();
        arg0 = arg0->next;
    } while (arg0 != NULL);
}

void draw_model_blend_motion(void *arg0, void *arg1, f32 farg0) {
    TObjPlayer::setup_model_draw_state(arg0);
    draw_blend_motion_tree(arg0, arg1, farg0, draw_chunk_vertices_cached);
    TObjPlayer::end_chunk_draw();
}

void draw_model_motion(void *arg0, void *arg1, f32 farg0) {
    TObjPlayer::setup_model_draw_state(arg0);
    draw_motion_tree(arg0, arg1, farg0, draw_chunk_vertices_cached);
    TObjPlayer::end_chunk_draw();
}

void draw_chunk_model_with_shape_motion(void *child, void *arg1, void *arg2, f32 farg0) {
    TObjPlayer::setup_model_draw_state(child);
    draw_motion_bound(child, arg1, arg2, farg0, draw_chunk_vertices_cached);
    TObjPlayer::end_chunk_draw();
}

void set_motion_packed_rotation() {
    motion_packed_rotation_mode = 1;
}

void clear_motion_packed_rotation() {
    motion_packed_rotation_mode = 0;
}
void draw_motion_tree(void *arg0, void *arg1, f32 frame, ModelDrawCallback draw) {
    bind_motion_context((void *)(arg1), frame);
    model_draw_context->draw = draw;
    if (motion_packed_rotation_mode != 0) {
        current_motion_context->f28 = motion_angle_sampler_table[3];
    }
    traverse_animated_node_tree(arg0);
}
void traverse_animated_node_tree(void *arg) {
    struct Node_803E49FC *arg0 = (struct Node_803E49FC *)arg;
    u32 t;
    do {
        push_matrix();
        compose_motion_node_matrix(arg0);
        if (chunk_model_node_callback != NULL) {
            chunk_model_node_callback((NJS_OBJECT *)arg0);
        }
        t = arg0->f4;
        if (t != 0 && (arg0->flags & 8) == 0) {
            model_draw_context->draw((void *)t);
        }
        if (arg0->child != NULL) {
            traverse_animated_node_tree((void *)arg0->child);
        }
        pop_matrix();
        arg0 = arg0->next;
    } while (arg0 != NULL);
}
