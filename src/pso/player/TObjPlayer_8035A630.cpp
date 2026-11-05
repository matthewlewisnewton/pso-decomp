#include "pso/math/MatrixCopy.h"
#include "types.h"
#include "pso/unk/text_803D853C.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/unk/text_803E2D70.h"
#include "pso/player/TObjPlayer.h"
#include "pso/misc/TUnk_804F1C58.h"
#include "pso/enemy/TObjEneRe7Berura_803E4CE0.h"

extern "C" {

extern ChunkModelNodeCallback player_apply_callback_fn;
s32 push_matrix();

extern s32 player_node_matrix_cursor;
extern s32 player_node_matrix_count;
extern s32 node_matrix_array_base;

void process_node_callback(NJS_OBJECT *arg0) {
    if ((s32) player_node_matrix_cursor < (s32) player_node_matrix_count) {
        get_current_matrix((void *)(node_matrix_array_base + (player_node_matrix_cursor * 0x30)));
    }
    if (player_apply_callback_fn != NULL) {
        player_apply_callback_fn(arg0);
    }
    player_node_matrix_cursor += 1;
}

void TUnk_804F1C58::draw_node_tree(NJS_OBJECT *arg1) {
    ChunkModelNodeCallback temp_r12;
    s32 temp_r31;
    void *var_r30;

    var_r30 = arg1;
    do {
        temp_r31 = *(s32 *)((s8 *)var_r30 + 0);
        push_matrix();
        concat_matrix((MtxP)(0), (const f32 (*)[4])(node_matrix_array_base + (this->m_30 * 0x30)));
        this->m_30 = (this->m_30 + 1);
        temp_r12 = draw_callback;
        if (temp_r12 != NULL) {
            temp_r12((NJS_OBJECT *)var_r30);
        }
        if (!(temp_r31 & 8)) {
            draw_chunk_model((void *)(*(s32 *)((s8 *)var_r30 + 4)));
        }
        pop_matrix();
        if (!(temp_r31 & 0x10)) {
            draw_node_tree(*(NJS_OBJECT **)((s8 *)var_r30 + 0x2C));
        }
        var_r30 = *(void **)((s8 *)var_r30 + 0x30);
    } while (var_r30 != NULL);
}

}
