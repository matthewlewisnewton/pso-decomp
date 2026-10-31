#include "types.h"
#include "pso/enemy/TObjEneRe7Berura_803E4CE0.h"
#include "pso/player/TObjPlayer.h"
#include "pso/misc/TUnk_804F1C58.h"
#include "pso/enemy/TObjEneRe7Berura.h"
#include "pso/misc/TLobby_801E2F94.h"

extern "C" {


extern s32 player_node_matrix_cursor;
extern s32 player_node_matrix_count;
extern s32 node_matrix_array_base;
extern ChunkModelNodeCallback player_apply_callback_fn;

void TUnk_804F1C58::apply_with_callback(NJS_MOTION *arg1, f32 farg0) {
    motion = arg1;
    frame = farg0;
    player_node_matrix_cursor = 0;
    player_node_matrix_count = node_count;
    node_matrix_array_base = (s32)m_28;
    player_apply_callback_fn = capture_callback;
    set_chunk_model_node_callback(process_node_callback);
    draw_motion(root, arg1, farg0);
    set_chunk_model_node_callback(NULL);
}

}
