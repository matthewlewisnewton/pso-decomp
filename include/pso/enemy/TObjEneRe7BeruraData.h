#ifndef PSO_ENEMY_TOBJENERE7BERURADATA_H
#define PSO_ENEMY_TOBJENERE7BERURADATA_H

#include "pso/object/TObjMotion.h"
#include "pso/enemy/BattleParameters.h"

struct SampledMotionPoints;
struct BmlResource;
class TUnk_80490470;

struct BeruraDetachedPart {
    Mtx34 *matrices;
    s32 first_node_index;
    s32 last_node_index;
    s32 action;
    f32 m_10;
    f32 frame;
    NJS_OBJECT *first_node;
    NJS_OBJECT *last_node;
    NJS_OBJECT model;
    Vec origin;

    void show_end_nodes();
    void hide_end_nodes();
};

extern BeruraDetachedPart TObjEneRe7Berura__detached_part_states[2];
extern TObjMotionAction TObjEneRe7Berura__animation_definitions[8];
extern SampledMotionPoints *belra_trail_buffer;
extern Vec *re7_berura_demo_camera_ptr;
extern BattleBaseStats *berura_base_stats[1];
extern ActorParamBlock *berura_resistance_stats[1];
extern BattleMovementParams *TObjEneRe7Berura__handler_table_a[1];
extern BmlResource *TObjEneRe7Berura__shared_resource;
extern s32 re7_berura_demo_state;
extern s32 lbl_805D4F6C;
extern s32 berura_demo_flag;
extern s32 re7_berura_demo_flag;
extern TUnk_80490470 *TObjEneRe7Berura__demo_target;
extern Mtx34 *berura_detached_matrices;
extern s32 *berura_node_matrix_ptr_a;
extern s16 *berura_node_matrix_ptr_b;
extern void *belra_uv_animation_buffer;
extern s32 berura_attack_node_range_start;
extern s32 berura_attack_node_range_end;
extern Mtx34 *TObjEneRe7Berura__node_matrix_cursor;
extern Vec *berura_attack_node_vec_ptr;

typedef char BeruraDetachedPartSize[sizeof(BeruraDetachedPart) == 0x64 ? 1 : -1];
typedef char BeruraDetachedPartModelOffset[offsetof(BeruraDetachedPart, model) == 0x20 ? 1 : -1];
typedef char BeruraDetachedPartOriginOffset[offsetof(BeruraDetachedPart, origin) == 0x58 ? 1 : -1];

#endif
