#include "types.h"
#include "pso/enemy/berura/TObjEneRe7Berura_803E4CE0.h"
#include "pso/player/TObjPlayer.h"
#include "pso/unk/TUnk_804F1C58.h"
#include "pso/enemy/berura/TObjEneRe7Berura.h"
#include "pso/unk/TLobby_801E2F94.h"

extern "C" {


void process_node_callback(s32);
extern s32 player_node_matrix_cursor;
extern s32 player_node_matrix_count;
extern s32 node_matrix_array_base;
extern s32 player_apply_callback_fn;

void TUnk_804F1C58::apply_with_callback(NJS_MOTION *arg1, f32 farg0) {
    motion = arg1;
    frame = farg0;
    player_node_matrix_cursor = 0;
    player_node_matrix_count = node_count;
    node_matrix_array_base = (s32)m_28;
    player_apply_callback_fn = (s32)capture_callback;
    set_chunk_model_node_callback((ChunkModelNodeCallback)process_node_callback);
    draw_motion(root, arg1, farg0);
    set_chunk_model_node_callback((ChunkModelNodeCallback)NULL);
}

}
