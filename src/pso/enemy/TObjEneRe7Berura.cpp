#include "pso/system/CurrentTextureList.h"
#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/enemy/BattleParameters.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/math/MatrixCopy.h"
#include "pso/animation/MotionContext.h"
#include "pso/misc/SampledMotionPoints.h"
#include "pso/player/demo_mode.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/system/EnemyBmlResource.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/system/vector.h"
#include "pso/system/SoundEffect.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/misc/RenderFadeState.h"
#include "types.h"
#include "pso/system/NinjaUtil.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/enemy/TObjEneDD_ST.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjChara.h"
#include "pso/enemy/TObjEneRe7Berura.h"
#include "pso/unk/TUnk_80494968.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/system/MatrixOps.h"
#include "pso/render/render_util.h"
#include "pso/system/MatrixStack.h"
#include "pso/unk/text_803D853C.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/object/TObjMotion.h"
#include "pso/boss/TBoss4Type3.h"

#include "pso/player/TUnk_80490470.h"
#include "pso/boss/TBoss3Volopt.h"
#include "pso/boss/TBoss8Dragon.h"
#include "pso/boss/TObjBoss2Tunnel.h"

#include "pso/enemy/TObjEnePanarms.h"
#include "pso/misc/TLobby.h"
#include "pso/npc/NpcModelRegistry.h"
#include "pso/npc/NpcAnimationBinding.h"

extern "C" {

u32 csnLookAt(void *, void *);
s32 enemy_set_target_id(void *, u16);
void mem_free(void*);
void *mem_alloc(u32 size);
f32 sin_table_lookup(s32);
f32 cos_table_lookup(s32);
void compose_motion_node_matrix(void *arg0);
}
void *destroy_buffer_pair(void *arg0, s16 arg1);
void get_current_matrix(void *);
void draw_chunk_model(void *arg0);

extern const s32 TObjEneRe7Berura__data_80439DA8[];
extern const s32 TObjEneRe7Berura__data_80439DB0[];
extern const s32 TObjEneRe7Berura__data_80439DB8[];
extern AttackParams *berura_attack_stats[2];
extern const f32 TObjEneRe7Berura__data_805D9724;
extern const f32 TObjEneRe7Berura__data_805D972C;
extern const f32 TObjEneRe7Berura__data_805D9730;
extern const f32 TObjEneRe7Berura__data_805D9738;
extern const f32 TObjEneRe7Berura__data_805D9740;
extern const f32 TObjEneRe7Berura__data_805D9764;
extern s32 lbl_80439DA0[];
extern NpcAnimationBinding ene_re7_berura_attack_def;
extern const char lbl_80439EF8[];
extern const char *lbl_805D2988;
extern const s32 lbl_805D9718[1];
extern const s32 lbl_805D971C[1];
extern const s32 lbl_805D9720[1];
extern const f32 lbl_805D974C;
extern const f32 lbl_805D9770;
extern const f32 lbl_805D9774;
extern const f32 lbl_805D9778;
extern const f32 lbl_805D977C;
extern const f32 lbl_805D9780;
extern const f32 lbl_805D9784;
extern const f32 lbl_805D9788;
extern TObject *tl_04;

extern const char lbl_80439DC0[];
extern const char lbl_80439DD4[];
extern const char lbl_80439DEC[];
extern const char lbl_80439E04[];
extern const char lbl_80439E18[];
extern const char lbl_80439E30[];
extern const char lbl_80439E48[];
extern const char lbl_80439E60[];
extern const char lbl_80439E74[];
extern const char lbl_80439E88[];

struct BeruraInitialParameters {
    f32 max_distance;
    f32 min_distance;
    s32 turn_speed;
    u32 unknown_c[4];
};

BeruraInitialParameters berura_init_params = {225.0f, 0.0f, 0x600, {0, 0, 0, 0}};
CollisionBody TObjEneRe7Berura__collision_body_template = {
    {0.0f, 0.0f, 0.0f}, 8.0f, 0.0f, 0, 0x8003,
    {0.0f, 0.0f, 0.0f}, 0.0f,
};
__declspec(section ".data") const char *bm_ene_re7_berura_model_names[2] = {
    lbl_80439DC0, NULL,
};
const char *bm_ene_re7_berura_motion_names[9] = {
    lbl_80439DD4, lbl_80439DEC,
    lbl_80439E04, lbl_80439E18,
    lbl_80439E30, lbl_80439E48,
    lbl_80439E60, lbl_80439E74, NULL,
};
BmlResourceDescriptor ene_berura_bml_descriptor = {
    lbl_80439E88, bm_ene_re7_berura_model_names,
    bm_ene_re7_berura_motion_names, 1, 8,
};
TObjMotionAction TObjEneRe7Berura__animation_definitions[8] = {
    {MOTION_MODE_LOOP, 0, 6, 0.8f, 0},
    {MOTION_MODE_LOOP, 0, 7, 0.8f, 0},
    {MOTION_MODE_ONCE, 0, 0, 0.8f, 0},
    {MOTION_MODE_CHAIN, 0, 3, 0.8f, 0},
    {MOTION_MODE_CHAIN, 0, 5, 0.8f, 0},
    {MOTION_MODE_LOOP, 0, 4, 0.8f, 0},
    {MOTION_MODE_ONCE, 0, 1, 0.8f, 0},
    {MOTION_MODE_ONCE, 0, 2, 0.8f, 0},
};

f32 lbl_805007C8[3];

__declspec(section ".data") AttackParams *berura_attack_stats[2];

BeruraDetachedPart TObjEneRe7Berura__detached_part_states[2];

BattleBaseStats *berura_base_stats[1];
ActorParamBlock *berura_resistance_stats[1];
BattleMovementParams *TObjEneRe7Berura__handler_table_a[1];
BmlResource *TObjEneRe7Berura__shared_resource;
s32 re7_berura_demo_state;
s32 lbl_805D4F6C;
Vec *re7_berura_demo_camera_ptr;
s32 berura_demo_flag;
s32 re7_berura_demo_flag;
TUnk_80490470 *TObjEneRe7Berura__demo_target;
Mtx34 *berura_detached_matrices;
s32 *berura_node_matrix_ptr_a;
s16 *berura_node_matrix_ptr_b;
void *belra_uv_animation_buffer;
s32 berura_attack_node_range_start;
s32 berura_attack_node_range_end;
Mtx34 *TObjEneRe7Berura__node_matrix_cursor;
Vec *berura_attack_node_vec_ptr;
SampledMotionPoints *belra_trail_buffer;

void BeruraDetachedPart::hide_end_nodes() {
    first_node->evalflags |= NJD_EVAL_HIDE;
    last_node->evalflags |= NJD_EVAL_HIDE;
}

void BeruraDetachedPart::show_end_nodes() {
    first_node->evalflags &= ~NJD_EVAL_HIDE;
    last_node->evalflags &= ~NJD_EVAL_HIDE;
}

void TObjEneRe7Berura::load_static_resources() {
    s32 pair[4];
    Vec vecs[4];
    BmlResource *r;
    u32 m;
    Mtx34 *matrices;
    s32 i;
    void *p;
    SampledMotionPoints *sampled;
    if (TObjEneDD::check_v2_mode() != 0) {
        r = load_enemy_bml_resource_named(&ene_berura_bml_descriptor, lbl_80439EF8);
    } else {
        r = load_enemy_bml_resource(&ene_berura_bml_descriptor);
    }
    TObjEneRe7Berura__shared_resource = r;
    lbl_805007C8[0] = TObjEneRe7Berura__data_805D972C;
    lbl_805007C8[1] = TObjEneRe7Berura__data_805D972C;
    lbl_805007C8[2] = TObjEneRe7Berura__data_805D972C;
    re7_berura_demo_state = 0;
    lbl_805D4F6C = 0;
    re7_berura_demo_camera_ptr = 0;
    berura_demo_flag = 0;
    re7_berura_demo_flag = 0;
    TObjEneRe7Berura__demo_target = 0;
    m = r->models[0].model;
    matrices = (Mtx34 *)mem_alloc(34 * sizeof(Mtx34));
    berura_detached_matrices = matrices;
    TObjEneRe7Berura__detached_part_states[0].matrices = matrices;
    TObjEneRe7Berura__detached_part_states[1].matrices = matrices + 17;
    TObjEneRe7Berura__detached_part_states[0].first_node_index = 0x21;
    TObjEneRe7Berura__detached_part_states[0].last_node_index = 0x31;
    TObjEneRe7Berura__detached_part_states[1].first_node_index = 0x38;
    TObjEneRe7Berura__detached_part_states[1].last_node_index = 0x48;
    TObjEneRe7Berura__detached_part_states[0].action = 3;
    TObjEneRe7Berura__detached_part_states[0].m_10 = TObjEneRe7Berura__data_805D9764;
    TObjEneRe7Berura__detached_part_states[0].frame = TObjEneRe7Berura__data_805D9740;
    TObjEneRe7Berura__detached_part_states[1].action = 4;
    TObjEneRe7Berura__detached_part_states[1].m_10 = lbl_805D9778;
    TObjEneRe7Berura__detached_part_states[1].frame = lbl_805D977C;
    for (i = 0; i < 2; i++) {
        BeruraDetachedPart *e = &TObjEneRe7Berura__detached_part_states[i];
        AnimationMotion *motion = TObjEneRe7Berura__shared_resource->motions[TObjEneRe7Berura__animation_definitions[e->action].motion].motion;
        set_motion_packed_rotation();
        bind_motion_context((NJS_MOTION *)motion, e->frame);
        capture_part_matrices((NJS_OBJECT *)m, e);
        clear_motion_packed_rotation();
        e->first_node = (NJS_OBJECT *)find_model_node(m, e->first_node_index);
        e->last_node = (NJS_OBJECT *)find_model_node(m, e->last_node_index);
        e->model.evalflags = 7;
        e->model.model = e->first_node->model;
        e->model.pos[0] = TObjEneRe7Berura__data_805D972C;
        e->model.pos[1] = TObjEneRe7Berura__data_805D972C;
        e->model.pos[2] = TObjEneRe7Berura__data_805D972C;
        e->model.ang[0] = 0;
        e->model.ang[1] = 0;
        e->model.ang[2] = 0;
        e->model.scl[0] = lbl_805D974C;
        e->model.scl[1] = lbl_805D974C;
        e->model.scl[2] = lbl_805D974C;
        e->model.child = e->first_node->child;
        e->model.sibling = 0;
    }
    berura_node_matrix_ptr_a = (s32 *)(((NJS_CNK_MODEL *)((NJS_OBJECT *)find_model_node(m, 2))->model)->polygon_list + 4);
    berura_node_matrix_ptr_b = ((NJS_CNK_MODEL *)((NJS_OBJECT *)find_model_node(m, 1))->model)->polygon_list + 4;
    p = ::operator new(0x14);
    if (p != NULL) {
        p = ((TLobby *)p)->alloc_tables(TObjEneRe7Berura__shared_resource->models[0].model, 2);
    }
    belra_uv_animation_buffer = p;
    sampled = new SampledMotionPoints(4, lbl_805D9780, lbl_805D9784,
        TObjEneRe7Berura__data_805D9738);
    belra_trail_buffer = sampled;
    pair[0] = 0x2E;
    pair[1] = 0x2E;
    pair[2] = 0x45;
    pair[3] = 0x45;
    for (i = 0; i < 4; i++) {
        vecs[i].x = TObjEneRe7Berura__data_805D972C;
        vecs[i].y = TObjEneRe7Berura__data_805D972C;
        vecs[i].z = TObjEneRe7Berura__data_805D972C;
    }
    vecs[0].x = TObjEneRe7Berura__data_805D9730;
    vecs[2].x = TObjEneRe7Berura__data_805D9730;
    sampled->sample((NJS_OBJECT *)TObjEneRe7Berura__shared_resource->models[0].model,
        (NJS_MOTION *)TObjEneRe7Berura__shared_resource->motions[TObjEneRe7Berura__animation_definitions[2].motion].motion,
        pair, vecs);
    for (i = 0; i < 1; i++) {
        berura_base_stats[i] = get_battle_base_stats(lbl_805D9718[i]);
    }
    for (s32 j = 0; j < 2; j++) {
        berura_attack_stats[j] = get_battle_attack_params(lbl_80439DA0[j]);
    }
    for (i = 0; i < 1; i++) {
        berura_resistance_stats[i] = get_battle_resistance_params(lbl_805D971C[i]);
    }
    for (i = 0; i < 1; i++) {
        TObjEneRe7Berura__handler_table_a[i] = get_battle_movement_params(lbl_805D9720[i]);
    }
    {
        NpcAnimationBinding animation = ene_re7_berura_attack_def;
        animation.motions = TObjEneRe7Berura__shared_resource->motions;
        NpcModelRegistry::register_animated_chunk(0x15,
            (void *)TObjEneRe7Berura__shared_resource->models[0].model,
            (void *)TObjEneRe7Berura__shared_resource->models[0].m_c,
            &animation, lbl_805D9788, TObjEneRe7Berura__data_805D972C);
    }
}

void *TObjEneRe7Berura::create(void *set_data) {
    return new TObjEneRe7Berura(tl_04, set_data);
}

void TObjEneRe7Berura::destroy_children() {
    if (belra_trail_buffer != NULL) {
        delete belra_trail_buffer;
        belra_trail_buffer = NULL;
    }
    if (belra_uv_animation_buffer != NULL) {
        destroy_buffer_pair(belra_uv_animation_buffer, 1);
        belra_uv_animation_buffer = NULL;
    }
    if (berura_detached_matrices != NULL) {
        mem_free(berura_detached_matrices);
        berura_detached_matrices = NULL;
    }
    if (TObjEneRe7Berura__shared_resource != NULL) {
        delete TObjEneRe7Berura__shared_resource;
        TObjEneRe7Berura__shared_resource = NULL;
    }
}

TObjEneRe7Berura::TObjEneRe7Berura(TObject *parent, void *set_data)
    : TObjEneDD_ST(parent) {
    m_name = lbl_805D2988;
    invoke_initialization_hook(set_data);
    fn_80095328();
    init_enemy();
}

void TObjEneRe7Berura::init_enemy() {
    s32 i;
    s32 j;
    init_position_vectors();
    model = (void *)TObjEneRe7Berura__shared_resource->models[0].model;
    texlist = TObjEneRe7Berura__shared_resource->models[0].m_c;
    init_model(&TObjEneRe7Berura__collision_body_template, 1);
    set_action_table(TObjEneRe7Berura__animation_definitions);
    set_motion_list(TObjEneRe7Berura__shared_resource->motions);
    requested_action = 0;
    set_animation(requested_action);
    set_field_b8(requested_action);
    reset_hp( berura_base_stats[TObjEneRe7Berura__data_80439DA8[0]],
        berura_attack_stats[TObjEneRe7Berura__data_80439DB0[0]],
        berura_resistance_stats[TObjEneRe7Berura__data_80439DB8[0]]);
    set_state_8();
    movementParameters = &berura_init_params;
    initialize_enemy_state(0x25);
    m_37c = TObjEneRe7Berura__data_805D9730;
    enemy_init_acquire_period(0x3C);
    enemy_init_validate_period(0x3C);
    flags = 0;
    m_3c4 = -1;
    m_3c8 = 0xFF000000;
    uv_scroll_step = 0;
    uv_scroll = 0;
    m_3d4 = 1;
    fade.reset_color();
    active_part = 1;
    punch = (TObject *)spawn_punch(this);
    part_fade.reset_color();
    if (TObjEneDD::check_v2_mode() != 0) {
        part_fade.set_rate_from_divisor(10);
    }
    for (i = 0; i < 2; i++) {
        part_flags[i] = 0;
        VecCopy(&part_positions[i], &position);
        part_effects[i] = 0;
    }
    traces[0] = TUnk_80494968::create(0xFF00FF00, 0xA0703030);
    traces[1] = TUnk_80494968::create(0xFF00FF00, 0xA0703030);
    for (j = 0; j < 4; j++) {
        camera_fades[j].activate_and_dispatch();
    }
    turn_limit = 0;
    accumulated_turn = 0;
    state_timer = 0;
    m_4c4 = 0;
    m_4c8 = 0;
    m_4cc = 0;
    m_4d0 = TObjEneRe7Berura__data_805D972C;
    m_4d4 = TObjEneRe7Berura__data_805D972C;
    m_4d8 = TObjEneRe7Berura__data_805D972C;
    m_4dc = TObjEneRe7Berura__data_805D972C;
    m_4e0 = TObjEneRe7Berura__data_805D972C;
    this->vfunc_95();
    mode = 0;
    dispatch_action(mode, 4);
}

TObjEneRe7Berura::~TObjEneRe7Berura() {
    destroy_parts();
    for (s32 i = 0; i < 2; i++) {
        if (traces[i] != NULL) {
            delete traces[i];
            traces[i] = NULL;
        }
    }
    if (punch != NULL) {
        punch->queue_destruction();
        punch = NULL;
    }
    free_collision_body_parts(this);
}

void TObjEneRe7Berura::run_task() {
    if (check_demo_mode() != 0) {
        fn_80092C90();
        return;
    }
    if (vfunc_83() != 4) {
        vfunc_85();
        uv_scroll += uv_scroll_step;
        uv_scroll = (u8)uv_scroll;
    }
    update_collision_center();
    submit_default_cursor_candidate();
    vfunc_100();
}

void TObjEneRe7Berura::vfunc_28() {  }

void TObjEneRe7Berura::vfunc_63() { if (this->mode != 11) { transition_enemy_state(11); } }

void TObjEneRe7Berura::vfunc_62() {
    if ((flags & 4) || (referenceHp - hp < hpmax / 5)) {
        clear_attack_receipts();
        return;
    }
    if (mode != 10) {
        transition_enemy_state(10);
    }
}

void TObjEneRe7Berura::vfunc_61() {  }

void TObjEneRe7Berura::update_collision_center() {
    body_center_position.x = position.x;
    body_center_position.y = TObjEneRe7Berura__data_805D9764 + position.y;
    body_center_position.z = position.z;
    VecCopy(&center, &body_center_position);
}

void TObjEneRe7Berura::vfunc_88() {
    bodies[0].offset.y = body_center_position.y - position.y;
}

void TObjEneRe7Berura::fn_80095328() {  }

#pragma push
#pragma fp_contract on
s32 TObjEneRe7Berura::acquire_target_in_view() {
    Vec v;
    s32 n;
    TObjPlayer *p;
    u16 id;
    s32 i;
    f32 c;
    f32 s;
    f32 limit;
    f32 d;
    f32 best;
    best = TObjEneRe7Berura__data_805D972C;
    id = 0xFFFF;
    limit = cos_table_lookup(0xAAA);
    s = sin_table_lookup(this->rotation.yaw);
    c = cos_table_lookup(this->rotation.yaw);
    n = TLobby::get_game_mode();
    for (i = 0; i < n; i++) {
        p = TObjPlayer::get_player_data(i);
        if (p->is_alive() != 0) {
            VecCopy(&v, &p->position);
            subtract_vector(&v, &body_center_position);
            v.y = TObjEneRe7Berura__data_805D972C;
            d = normalize_vector_xz(&v);
            if (d < TObjEneRe7Berura__data_805D9724 && d > best &&
                s * v.x + c * v.z > limit &&
                csnLookAt(&body_center_position, &p->body_center_position) == 0) {
                id = get_entity_id(p);
                best = d;
            }
        }
    }
    if (id != 0xFFFF) {
        enemy_set_target_id(this, id);
        return 1;
    }
    return 0;
}
#pragma pop

s32 TObjEneRe7Berura::fn_8009518C() {
    return !(part_flags[active_part] & 2);
}

s32 TObjEneRe7Berura::collect_node_matrices(NJS_OBJECT *root, s32 index) {
    Mtx34 matrix;
    u32 flags;
    do {
        push_matrix();
        compose_motion_node_matrix(root);
        flags = root->evalflags;
        if (index == berura_attack_node_range_start) {
            berura_attack_node_vec_ptr->x = TObjEneRe7Berura__data_805D972C;
            berura_attack_node_vec_ptr->y = TObjEneRe7Berura__data_805D972C;
            berura_attack_node_vec_ptr->z = TObjEneRe7Berura__data_805D972C;
            matrix_mult_vec(NULL, berura_attack_node_vec_ptr, berura_attack_node_vec_ptr);
            berura_attack_node_vec_ptr->y += lbl_805D9774;
            berura_attack_node_vec_ptr->z += TObjEneRe7Berura__data_805D9764;
            get_current_matrix(&matrix);
            push_matrix_from(identity_matrix);
            translate_matrix(0, -berura_attack_node_vec_ptr->x,
                -berura_attack_node_vec_ptr->y, -berura_attack_node_vec_ptr->z);
            concat_matrix(NULL, matrix);
            get_current_matrix(&matrix);
            pop_matrix();
            copy_matrix(NULL, matrix);
        }
        if (index >= berura_attack_node_range_start && index <= berura_attack_node_range_end) {
            Mtx34 *destination = TObjEneRe7Berura__node_matrix_cursor;
            TObjEneRe7Berura__node_matrix_cursor = destination + 1;
            get_current_matrix(destination);
        }
        index++;
        if (!(flags & NJD_EVAL_BREAK)) {
            index = collect_node_matrices(root->child, index);
        }
        pop_matrix();
        root = root->sibling;
    } while (root != NULL);
    return index;
}

void TObjEneRe7Berura::capture_part_matrices(NJS_OBJECT *root, BeruraDetachedPart *part) {
    TObjEneRe7Berura__node_matrix_cursor = part->matrices;
    berura_attack_node_range_start = part->first_node_index;
    berura_attack_node_range_end = part->last_node_index;
    berura_attack_node_vec_ptr = &part->origin;
    push_matrix_from(identity_matrix);
    collect_node_matrices(root, 0);
    pop_matrix();
}

void TObjEneRe7Berura::draw_node_tree(NJS_OBJECT *root) {
    do {
        push_matrix();
        Mtx34 *matrix = TObjEneRe7Berura__node_matrix_cursor;
        TObjEneRe7Berura__node_matrix_cursor = matrix + 1;
        concat_matrix(NULL, *matrix);
        u32 flags = root->evalflags;
        if (!(flags & NJD_EVAL_HIDE)) {
            draw_chunk_model(root->model);
        }
        pop_matrix();
        if (!(flags & NJD_EVAL_BREAK)) {
            draw_node_tree(root->child);
        }
        root = root->sibling;
    } while (root != NULL);
}

void TObjEneRe7Berura::draw_node_tree(NJS_OBJECT *root, Mtx34 *matrices) {
    TObjEneRe7Berura__node_matrix_cursor = matrices;
    draw_node_tree(root);
}

void TObjEneRe7Berura::init_part(s32 index) {
    set_current_texture_list((GinjaTextureList *)TObjEneRe7Berura__shared_resource->models[0].m_c);
    BeruraDetachedPart *part = &TObjEneRe7Berura__detached_part_states[index];
    draw_node_tree(&part->model, part->matrices);
}

s32 TObjEneRe7Berura::fn_80094EE0() {
    return m_3d4 << 15;
}

void TObjEneRe7Berura::reset_turn_limit() {
    this->turn_limit = fn_80094EE0();
    this->accumulated_turn = 0;
}

s32 TObjEneRe7Berura::turn_toward_heading(s32 heading, s32 max_step) {
    s32 previous_turn;
    s32 previous_negative_turn;
    s32 difference;
    s32 reached_heading;

    reached_heading = 0;
    difference = angle_diff_s16(this->rotation.yaw, heading);
    if (difference > max_step) {
        this->rotation.yaw = (s32) (this->rotation.yaw + max_step);
        previous_turn = this->accumulated_turn;
        if (previous_turn < 0) {
            this->accumulated_turn = 0;
        } else {
            this->accumulated_turn = (s32) (previous_turn + max_step);
        }
    } else if (difference < (s32) -max_step) {
        this->rotation.yaw = (s32) (this->rotation.yaw - max_step);
        previous_negative_turn = this->accumulated_turn;
        if (previous_negative_turn > 0) {
            this->accumulated_turn = 0;
        } else {
            this->accumulated_turn = (s32) (previous_negative_turn - max_step);
        }
    } else {
        this->rotation.yaw = heading;
        reached_heading = 1;
    }
    return reached_heading;
}

s32 TObjEneRe7Berura::has_reached_turn_limit() {
    int reached;
    s32 turn;
    s32 previous_turn;

    turn = this->accumulated_turn;
    reached = 0;
    previous_turn = this->turn_limit;
    if ((turn >= previous_turn) || (turn <= (s32) -previous_turn)) {
        reached = 1;
    }
    return (u8)reached;
}

s32 TObjEneRe7Berura::fn_80094DB4() {
    return m_3d4 * 150;
}

#pragma push
#pragma opt_common_subs off
void TObjEneRe7Berura::clear_active_part_flag_2() {
    part_flags[active_part] &= ~2;
}
#pragma pop

void TObjEneRe7Berura::destroy_parts() {
    for (s32 i = 0; i < 2; i++) {
        if (part_effects[i] != NULL) {
            part_effects[i]->queue_destruction();
            part_effects[i] = NULL;
        }
    }
}

void TObjEneRe7Berura::reload_stats_from_tables() {
    reload_stats_keep_hp_tp(berura_base_stats[TObjEneRe7Berura__data_80439DA8[1]],
                            berura_attack_stats[TObjEneRe7Berura__data_80439DB0[1]],
                            berura_resistance_stats[TObjEneRe7Berura__data_80439DB8[1]]);
}

void TObjEneRe7Berura::fn_80094C68() {
    reload_stats_keep_hp_tp(berura_base_stats[TObjEneRe7Berura__data_80439DA8[0]],
                            berura_attack_stats[TObjEneRe7Berura__data_80439DB0[0]],
                            berura_resistance_stats[TObjEneRe7Berura__data_80439DB8[0]]);
}

#pragma push
#pragma fp_contract on
void TObjEneRe7Berura::play_band_sound() {
    if (is_passing_frame(lbl_805D9770) || is_passing_frame(TObjEneRe7Berura__data_805D9764)) {
        play_sound_effect(remap_sound_for_area(0x4003BC1F), &position, 0, 0);
    }
}
#pragma pop

s32 TObjEneRe7Berura::check_death_trigger() {
    if (vfunc_99() != 0) {
        transition_enemy_state((s16)9);
        return 1;
    }
    return 0;
}

void TObjEneRe7Berura::dispatch_action(u32 state, s32 mode) {
    switch (state) {
    case 0:
        handle_message_transition(mode);
        return;
    case 1:
        state_attack(mode);
        return;
    case 3:
        fn_8009472C(mode);
        return;
    case 2:
        fn_80094624(mode);
        return;
    case 8:
        handle_state(mode);
        return;
    case 4:
        fn_800940E8(mode);
        return;
    case 5:
        fn_80093C80(mode);
        return;
    case 6:
        fn_80093888(mode);
        return;
    case 7:
        run_flash_warning_state(mode);
        return;
    case 9:
        state_patrol(mode);
        return;
    case 10:
        fn_80093470(mode);
        return;
    case 11:
        update_death_state(mode);
    default:
        return;
    }
}

void TObjEneRe7Berura::handle_message_transition(s32 msg) {
    switch (msg) {
    case 0:
        return;
    case 3:
        transition_enemy_state((s16)1);
        break;
    }
}

void TObjEneRe7Berura::state_attack(s32 reason) {
    u8 *arg0 = (u8 *)this;
    u32 previous_flags;

    switch (reason) {
    case 4:
        this->requested_action = 0;
        this->vfunc_95();
        previous_flags = flags;
        flags = previous_flags & ~5;
        flags |= 2;
        set_field_378(3);
        fade.start_negative_fade_phase();
        ((TBoss3Volopt *)(arg0 + 0x38))->play_area_se_with_particle();
        reset_turn_limit();
        return;
    case 3:
        if (fade.advance_toward_max() != 0) {
            transition_enemy_state(3);
        }
        return;
    case 0:
        this->vfunc_102();
        this->vfunc_88();
        return;
    case 5:
        flags &= ~2;
        break;
    }
}
