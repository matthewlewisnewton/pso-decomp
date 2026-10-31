#ifndef PSO_PLAYER_TOBJPLAYER_803E4954_H
#define PSO_PLAYER_TOBJPLAYER_803E4954_H

#include "types.h"
#include "pso/system/ModelDrawCallback.h"

extern "C" {
// Draws model posed by motion and deformed by shape (a Ninja shape motion) at frame.
void draw_chunk_model_with_shape_motion(void *model, void *motion, void *shape, f32 frame);
void draw_blend_motion_tree(void *root, void *link, f32 blend, ModelDrawCallback draw);
}
void draw_model_blend_motion(void *arg0, void *arg1, f32 farg0);
extern "C" {
void draw_model_motion(void *arg0, void *arg1, f32 farg0);
void draw_motion_tree(void *root, void *motion, f32 frame, ModelDrawCallback draw);
}
s32 draw_object_tree_recursive(void *arg);
// Motions sample packed (16-bit) rotation keys while set.
void set_motion_packed_rotation();
void clear_motion_packed_rotation();
void traverse_animated_node_tree(void *arg);

#endif
