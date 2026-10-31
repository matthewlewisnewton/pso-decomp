#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/enemy/BattleParameters.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/system/SoundEffect.h"
struct NJS_OBJECT;
#include "pso/unk/TUnk_80494968.h"
#include "pso/misc/GroundEffects.h"
#include "pso/misc/PositionSoundEffects.h"
#include "pso/player/demo_mode.h"
#include "pso/enemy/TUnk_80493450.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjChara.h"
#include "pso/enemy/TObjEneMoja.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/object/TObjMotion.h"
#include "pso/enemy/TObjEneShark.h"
#include "pso/enemy/TObjEneLappy_800F5DE0.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/TParticleCtrl.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/enemy/TObjEneRe7Berura_803E4CE0.h"
#include "pso/object/TObjFish.h"

#include "pso/misc/MaterialOpacityFade.h"

#include "pso/system/NinjaTypes.h"
#include "pso/system/BmlResource.h"
#include "pso/system/EnemyBmlResource.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/npc/NpcAnimationBinding.h"
#include "pso/npc/NpcModelRegistry.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/TObjControl.h"
#include "pso/TMainTask.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/RenderFadeState.h"
#include "pso/misc/TNowLoading.h"
#include <dolphin/mtx.h>
#include "pso/system/BmlResourceClass.h"
#include "pso/misc/SampledMotionPoints.h"
#include "pso/system/SoundEffect.h"
#include "pso/system/MatrixStack.h"
#include "pso/system/MatrixOps.h"
#include "pso/player/TObjPlayer_800D8FDC.h"
#include "pso/math/MatrixVector.h"
#include "pso/system/MatrixVectorArray.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/unk/text_803E2D70.h"
extern "C" {

extern s32 model_render_flags;
extern s32 shark_render_node_index;


extern __declspec(section ".sdata2") const f32 shark_zero;
extern __declspec(section ".sdata2") const f32 shark_ground_effect_y;
extern __declspec(section ".sdata2") const f32 shark_ground_effect_height_factor;


extern SampledMotionPoints *shark_attack3_trail_buffer;
extern SampledMotionPoints *shark_attack4_trail_buffer;
extern __declspec(section ".sdata2") const f32 shark_attack_trail_end_frame;


s32 restore_scene_lighting();
s32 select_actor_lighting(void *);

extern s32 saved_model_render_flags;
extern s32 saved_chunk_polygon_flags_and_mask;
extern s32 saved_chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_and_mask;
extern __declspec(section ".sdata2") const f32 shark_near_view_depth;
extern __declspec(section ".sdata2") const f32 shark_far_view_depth;
extern __declspec(section ".sdata2") const f32 shark_view_radius;
extern __declspec(section ".sdata2") const f32 shark_shadow_scale_x;
extern __declspec(section ".sdata2") const f32 shark_one;
extern __declspec(section ".sdata2") const f32 shark_shadow_scale_z;

}

void TObjEneShark::vfunc_101() {  }

void TObjEneShark::vfunc_98() {
    play_sound_effect((s32)(remap_sound_for_area(0x4003A60C)), &position, 0, 0);
    TObjPlayer::play_effect_if_v2(-0x300);
}

void TObjEneShark::vfunc_97() {
    play_sound_effect((s32)(remap_sound_for_area(0x4003A60B)), &position, 0, 0);
    TObjPlayer::play_effect_if_v2(-0x300);
}

void TObjEneShark::vfunc_96() {
    play_sound_effect((s32)(remap_sound_for_area(0x4003A60D)), &position, 0, 0);
}

void TObjEneShark::vfunc_95() {
    play_sound_effect((s32)(remap_sound_for_area(0x4003A60B)), &position, 0, 0);
    TObjPlayer::play_effect_if_v2(-0x300);
}

void TObjEneShark::vfunc_94() {
    Vec impactPosition;
    impactPosition.x = shark_zero;
    impactPosition.y = shark_ground_effect_y;
    impactPosition.z = shark_ground_effect_height_factor * *(f32 *)(m_2b0 + 0x10);
    push_matrix_from(&identity_matrix);
    rotate_matrix_y(0, rotation_y);
    rotate_vector_by_matrix(0, &impactPosition, &impactPosition);
    pop_matrix();
    vec3_add_to(&impactPosition, &position);
    spawn_ground_effect(&impactPosition, 0x23);
    TObjPlayer__sub_800D92BC((s32)&impactPosition, 0xF);
}

void TObjEneShark::vfunc_93() {
    Vec endpoints[2];
    Vec *e;
    s32 idx;
    TUnk_80494968 *eff;
    if (!(frame < shark_attack_trail_end_frame)) {
        return;
    }
    switch (requested_action) {
    case 3:
        e = shark_attack3_trail_buffer->lookup(frame);
        idx = 0;
        break;
    case 4:
        e = shark_attack4_trail_buffer->lookup(frame);
        idx = 1;
        break;
    default:
        e = 0;
        break;
    }
    if (e == 0) {
        return;
    }
    push_matrix();
    set_matrix_identity(0);
    post_translate_matrix(&position.x);
    rotate_matrix_y(0, rotation_y);
    matrix_mult_vec_array(NULL, e, endpoints, 2);
    pop_matrix();
    eff = attack_trails[idx];
    if (eff != NULL) {
        eff->vfunc_6(&endpoints[0], &endpoints[1]);
    }
}

void TObjEneShark::configure_subtype() {
    s32 selectedSubtype;
    selectedSubtype = subtype;
    if (selectedSubtype < 0) {
        subtype = 0;
    } else if (selectedSubtype > 2) {
        subtype = 2;
    }
    switch (subtype) {
    case 2:
        variant = 1;
        set_param(0x12);
        return;
    case 1:
        variant = 0;
        set_param(0x11);
        return;
    default:
        variant = 2;
        set_param(0x10);
        return;
    }
}

void TObjEneShark::vfunc_83() {
    advance_animation();
    switch (phase) {
    case 0:
    default:
        if (m_390 != 0) {
            appearance_fade.start_fade_in();
            play_area_sound_and_particles_b(&position);
            phase = 1;
        } else {
            phase = 2;
        }
        break;
    case 1:
        if (appearance_fade.advance_toward_max() == 1) {
            phase = 2;
            m_390 = 0;
        }
        break;
    case 2:
        mode = 1;
        phase = 0;
        break;
    }
}

void TObjEneShark::update_node_particle_state(NJS_OBJECT *) {
    switch (shark_render_node_index) {
    case 0x10:
    case 0x1A:
    case 0x20:
        TParticleCtrl::begin_effect_render();
        break;
    default:
        TParticleCtrl::end_effect_render();
        break;
    }
    shark_render_node_index += 1;
}

void TObjEneShark::render() {
    s32 viewDetail;
    s32 camera;
    s32 fadeActive;
    s32 savedFirstPolygonWord3;
    s16 savedSecondPolygonWord3;
    s16 savedSecondPolygonWord2;
    if (actorFlags & 0x02000000) {
        return;
    }
    camera = 0;
    if (is_split_screen() != 0) {
        camera = TCameraCtrl::get_camera_mode();
    }
    viewDetail = classify_actor_view_detail(shark_near_view_depth, shark_far_view_depth, shark_view_radius);
    if (viewDetail == 0) {
        return;
    }
    fadeActive = 0;
    if (TObjEneDD::check_v2_mode() != 0) {
        RenderFadeState *f = &camera_fades[camera];
        f->update();
        fadeActive = f->updateFromCamera(&body_center_position.x);
    }
    select_actor_lighting(this);
    model_render_flags |= 1;
    set_current_texture_list((GinjaTextureList *)(texlist));
    push_matrix();
    translate_matrix(0, shark_zero, unk_380, shark_zero);
    post_translate_matrix(&position.x);
    rotate_matrix_y(0, rotation_y);
    if (check_demo_mode() == 1) {
        draw_chunk_object(model);
    } else {
        switch (mode) {
        case 0:
        case 1:
        case 8:
        case 9: {
            s16 *polygon = static_cast<NJS_CNK_MODEL *>(static_cast<NJS_OBJECT *>(model)->child->sibling->model)->polygon_list;
            s16 t = polygon[3];
            static_cast<NJS_CNK_MODEL *>(static_cast<NJS_OBJECT *>(model)->child->sibling->model)->polygon_list[3] = (u8)polygon[3];
            savedFirstPolygonWord3 = t;
            break;
        }
        }
        if (m_378 == 0) {
            s16 a;
            s16 b;
            s16 *polygon = static_cast<NJS_CNK_MODEL *>(static_cast<NJS_OBJECT *>(model)->child->sibling->sibling->model)->polygon_list;
            a = polygon[2];
            b = polygon[3];
            polygon[2] = -0xB4;
            savedSecondPolygonWord2 = a;
            savedSecondPolygonWord3 = b;
            static_cast<NJS_CNK_MODEL *>(static_cast<NJS_OBJECT *>(model)->child->sibling->sibling->model)->polygon_list[3] = -1;
        }
        TObjPlayer::toggle_particle_effect();
        shark_render_node_index = 0;
        set_chunk_model_node_callback(TObjEneShark::update_node_particle_state);
        if (m_390 == 1) {
            if (appearance_fade.has_visible_opacity() != 0) {
                saved_model_render_flags = model_render_flags;
                saved_chunk_polygon_flags_and_mask = chunk_polygon_flags_and_mask;
                saved_chunk_polygon_flags_or_mask = chunk_polygon_flags_or_mask;
                appearance_fade.set_flags_and_apply_damage_color();
                if (defer_render() == 0) {
                    model_render_flags |= 1;
                    draw();
                    model_render_flags &= ~1;
                }
                appearance_fade.clear_flag_and_notify();
                chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;
                chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask;
                model_render_flags = saved_model_render_flags;
            }
        } else {
            if (fadeActive != 0) {
                camera_fades[camera].set_flags_and_apply_damage_color();
            }
            if (fadeActive != 0) {
                if (defer_render() == 0) {
                    if (viewDetail == 1) {
                        draw();
                    } else {
                        draw_motion_model();
                    }
                }
            } else if (viewDetail == 1) {
                draw();
            } else {
                draw_motion_model();
            }
            if (fadeActive != 0) {
                camera_fades[camera].clear_flag_and_notify();
            }
        }
        set_chunk_model_node_callback(0);
        TParticleCtrl::end_effect_render();
        if (m_378 == 0) {
            static_cast<NJS_CNK_MODEL *>(static_cast<NJS_OBJECT *>(model)->child->sibling->sibling->model)->polygon_list[2] = savedSecondPolygonWord2;
            static_cast<NJS_CNK_MODEL *>(static_cast<NJS_OBJECT *>(model)->child->sibling->sibling->model)->polygon_list[3] = savedSecondPolygonWord3;
        }
        switch (mode) {
        case 0:
        case 1:
        case 8:
        case 9:
            static_cast<NJS_CNK_MODEL *>(static_cast<NJS_OBJECT *>(model)->child->sibling->model)->polygon_list[3] = savedFirstPolygonWord3;
            break;
        }
    }
    pop_matrix();
    model_render_flags &= ~1;
    restore_scene_lighting();
    switch (mode) {
    case 0:
    case 1:
    case 8:
    case 9:
        return;
    default: {
        Vec scale;
        scale.x = shark_shadow_scale_x;
        scale.y = shark_one;
        scale.z = shark_shadow_scale_z;
        TObjEnemy::draw_ground_shadow(&scale, 0);
    }
    }
}


extern "C" {
extern BmlResource *shark_bml_resource;
extern s32 game_difficulty_selection;

void *mem_alloc(u32 size);
extern const char shark_alt_archive_filename[];
extern BattleBaseStats **shark_combat_stats;
extern AttackParams **shark_attack_stats;
extern ActorParamBlock **shark_resistance_stats;
extern f32 **shark_movement_parameter_sets;
extern __declspec(section ".sdata2") const f32 shark_attack_trail_start_frame;
extern __declspec(section ".sdata2") const f32 shark_npc_collision_radius;

void mem_free(void*);


extern "C" __declspec(section ".rodata") const char shark_model_filename_0[] = "bm1f_s_wala_body.nj";
extern "C" __declspec(section ".rodata") const char shark_model_filename_1[] = "bm1tl_s_wala_body.nj";
extern "C" __declspec(section ".rodata") const char shark_model_filename_2[] = "bm1_s_wala_body.nj";
extern "C" __declspec(section ".rodata") const char shark_appear_motion_filename[] = "appear_bm1_s_wala_body.njm";
extern "C" __declspec(section ".rodata") const char shark_left_attack_motion_filename[] = "atackl_bm1_s_wala_body.njm";
extern "C" __declspec(section ".rodata") const char shark_right_attack_motion_filename[] = "atackr_bm1_s_wala_body.njm";
extern "C" __declspec(section ".rodata") const char shark_damage_motion_filename[] = "damage_bm1_s_wala_body.njm";
extern "C" __declspec(section ".rodata") const char shark_deadb_motion_filename[] = "deadb_bm1_s_wala_body.njm";
extern "C" __declspec(section ".rodata") const char shark_death_motion_filename[] = "dead_bm1_s_wala_body.njm";
extern "C" __declspec(section ".rodata") const char shark_leader_motion_filename[] = "leader_bm1_s_wala_body.njm";
extern "C" __declspec(section ".rodata") const char shark_mihari_motion_filename[] = "mihari_bm1_s_wala_body.njm";
extern "C" __declspec(section ".rodata") const char shark_run_motion_filename[] = "run_bm1_s_wala_body.njm";
extern "C" __declspec(section ".rodata") const char shark_stund_motion_filename[] = "stund_bm1_s_wala_body.njm";
extern "C" __declspec(section ".rodata") const char shark_wakeup_motion_filename[] = "wakeup_bm1_s_wala_body.njm";
extern "C" __declspec(section ".rodata") const char shark_walk_motion_filename[] = "walk_bm1_s_wala_body.njm";
extern "C" __declspec(section ".rodata") const char shark_archive_filename[] = "bm_ene_bm1_shark.bml";
extern "C" __declspec(section ".rodata") const char shark_class_name[] = "TObjEneShark";
extern const char *bm_ene_bm1_shark_model_names[4];
extern const char *bm_ene_bm1_shark_motion_names[13];
const char *bm_ene_bm1_shark_model_names[4] = {
    shark_model_filename_0, shark_model_filename_1, shark_model_filename_2, NULL,
};
const char *bm_ene_bm1_shark_motion_names[13] = {
    shark_appear_motion_filename, shark_left_attack_motion_filename, shark_right_attack_motion_filename, shark_damage_motion_filename,
    shark_deadb_motion_filename, shark_death_motion_filename, shark_leader_motion_filename, shark_mihari_motion_filename,
    shark_run_motion_filename, shark_stund_motion_filename, shark_wakeup_motion_filename, shark_walk_motion_filename,
    NULL,
};
BmlResourceDescriptor bm_ene_bm1_shark_resource_descriptor = {
    shark_archive_filename, bm_ene_bm1_shark_model_names, bm_ene_bm1_shark_motion_names, 3, 12
};
TObjMotionAction shark_actions[11] = {
    { MOTION_MODE_LOOP, 0, 9, 0.6f, 0x1 },
    { MOTION_MODE_CHAIN, 0, 7, 0.6f, 0x20 },
    { MOTION_MODE_LOOP, 2, 11, 1.0f, 0x1 },
    { MOTION_MODE_CHAIN, 0, 1, 1.0f, 0x4 },
    { MOTION_MODE_CHAIN, 0, 2, 1.0f, 0x4 },
    { MOTION_MODE_LOOP, 0, 8, 1.0f, 0x1 },
    { MOTION_MODE_CHAIN, 0, 3, 1.0f, 0x8 },
    { MOTION_MODE_CHAIN, 0, 10, 0.8f, 0x20 },
    { MOTION_MODE_ONCE, 0, 5, 0.6f, 0x10 },
    { MOTION_MODE_ONCE, 0, 4, 0.6f, 0x10 },
    { MOTION_MODE_CHAIN, 0, 6, 0.6f, 0x20 },
};

SharkMovementParameters shark_movement_parameters[3] = {
    { 225.0f, 0.75f, 0x400, 0, 0x1E0000, 1, 0 },
    { 250.0f, 0.9f, 0x400, 0, 0x1E0000, 1, 0 },
    { 300.0f, 1.0f, 0x400, 0, 0x1E0000, 1, 0 },
};
CollisionBody shark_collision_bodies[3] = {
    { { 0.0f, 12.5f, 0.0f }, 7.0f, 0.0f, 0, 0x8003, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 0.0f, 12.5f, 0.0f }, 7.0f, 0.0f, 0, 0x8003, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 0.0f, 15.0f, 0.0f }, 8.0f, 0.0f, 0, 0x8003, { 0.0f, 0.0f, 0.0f }, 0.0f },
};

}

void *TObjEneShark::create(void *setData) {
    TObjControl *control = new TObjControl(tl_04);
    return new TObjEneShark(control, setData);
}

void TObjEneShark::free_resources() {
    if (shark_combat_stats != NULL) {
        mem_free(shark_combat_stats);
        shark_combat_stats = NULL;
    }
    if (shark_attack_stats != NULL) {
        mem_free(shark_attack_stats);
        shark_attack_stats = NULL;
    }
    if (shark_resistance_stats != NULL) {
        mem_free(shark_resistance_stats);
        shark_resistance_stats = NULL;
    }
    if (shark_movement_parameter_sets != NULL) {
        mem_free(shark_movement_parameter_sets);
        shark_movement_parameter_sets = NULL;
    }
    if (shark_attack4_trail_buffer != NULL) {
        delete shark_attack4_trail_buffer;
        shark_attack4_trail_buffer = NULL;
    }
    if (shark_attack3_trail_buffer != NULL) {
        delete shark_attack3_trail_buffer;
        shark_attack3_trail_buffer = NULL;
    }
    if (shark_bml_resource != NULL) {
        delete shark_bml_resource;
        shark_bml_resource = NULL;
    }
}

void TObjEneShark::load_resources() {
    s32 i;
    if (TObjEneDD::check_v2_mode() != 0) {
        shark_bml_resource = load_enemy_bml_resource_named(&bm_ene_bm1_shark_resource_descriptor, shark_alt_archive_filename);
    } else {
        shark_bml_resource = new BmlResource(1, &bm_ene_bm1_shark_resource_descriptor, 0, 0, NULL);
    }
    shark_attack3_trail_buffer = new SampledMotionPoints(2, shark_attack_trail_start_frame, shark_attack_trail_end_frame, shark_one);
    shark_attack4_trail_buffer = new SampledMotionPoints(2, shark_attack_trail_start_frame, shark_attack_trail_end_frame, shark_one);
    shark_attack3_trail_buffer->sample_two_nodes((NJS_OBJECT *)shark_bml_resource->models->model, (NJS_MOTION *)shark_bml_resource->motions[shark_actions[3].motion].motion, 5, 8);
    shark_attack4_trail_buffer->sample_two_nodes((NJS_OBJECT *)shark_bml_resource->models->model, (NJS_MOTION *)shark_bml_resource->motions[shark_actions[4].motion].motion, 0xA, 0xD);
    shark_combat_stats = static_cast<BattleBaseStats **>(mem_alloc(3 * sizeof(*shark_combat_stats)));
    shark_attack_stats = static_cast<AttackParams **>(mem_alloc(3 * sizeof(*shark_attack_stats)));
    shark_resistance_stats = static_cast<ActorParamBlock **>(mem_alloc(3 * sizeof(*shark_resistance_stats)));
    shark_movement_parameter_sets = (f32 **)mem_alloc(0xC);
    shark_combat_stats[0] = get_battle_base_stats(0x4F);
    shark_combat_stats[1] = get_battle_base_stats(0x50);
    shark_combat_stats[2] = get_battle_base_stats(0x51);
    shark_attack_stats[0] = get_battle_attack_params(0x54);
    shark_attack_stats[1] = get_battle_attack_params(0x55);
    shark_attack_stats[2] = get_battle_attack_params(0x56);
    shark_resistance_stats[0] = get_battle_resistance_params(0x4E);
    shark_resistance_stats[1] = get_battle_resistance_params(0x4F);
    shark_resistance_stats[2] = get_battle_resistance_params(0x50);
    shark_movement_parameter_sets[0] = (f32 *)get_battle_movement_params(0x4E);
    shark_movement_parameter_sets[1] = (f32 *)get_battle_movement_params(0x4F);
    shark_movement_parameter_sets[2] = (f32 *)get_battle_movement_params(0x50);
    shark_render_node_index = 0;
    {
        s16 ids[3] = { 0x2F, 0x30, 0x31 };
        NpcAnimationBinding anim = { shark_bml_resource->motions, shark_actions, 0, 2, 12 };
        for (i = 0; i < 3; i++) {
            NpcModelRegistry::register_animated_chunk(ids[i], (void *)shark_bml_resource->models[i].model, (void *)shark_bml_resource->models[i].m_c, &anim,
                shark_npc_collision_radius, shark_zero);
        }
    }
}

extern "C" __declspec(section ".rodata") const char shark_alt_archive_filename[] = "bm_ene_bm1_shark_a.bml";

TObjEneShark::~TObjEneShark() {
    for (s32 i = 0; i < 2; i++) {
        if (attack_trails[i] != NULL) {
            attack_trails[i]->queue_destruction();
            attack_trails[i] = NULL;
        }
    }
    unlink_enemy_group_relations();
    free_collision_body_parts(this);
}

extern "C" {

extern const char *TObjEneShark_name_ref;
extern __declspec(section ".sdata2") const f32 shark_angle_units_per_degree;
extern __declspec(section ".sdata2") const f32 shark_full_circle_degrees;

}

#pragma defer_codegen on
s32 TObjEneMoja::calc_technique_level() {
    MojaBattleStat *p = (MojaBattleStat *)m_2b0;
    s32 v = 0;
    if (p != 0) {
        v = p->techniqueLevel;
        if (v < 0) {
            return 0;
        }
        if (game_difficulty_selection == 3) {
            if (v > 0x1D) {
                v = 0x1D;
            }
            return v;
        }
        if (v > 0xE) {
            v = 0xE;
        }
    }
    return v;
}

void TObjEneMoja::fn_800ACA0C() {  }

void TObjEneShark::bind_variant_model(s32 i) {
    model = (void *)shark_bml_resource->models[i].model;
    texlist = shark_bml_resource->models[i].m_c;
}

void TUnk_80493450::vfunc_99() {  }

TObjEneShark::TObjEneShark(TObject *parent, void *setData)
    : TUnk_80493450(parent) {
    s32 color;
    s32 i;
    m_name = TObjEneShark_name_ref;
    apply_set_data(setData);
    initialize_position_copies();
    subtype = variant;
    configure_subtype();
    bind_variant_model(variant);
    action_table = shark_actions;
    set_action_table(action_table);
    motion_list = shark_bml_resource->motions;
    requested_action = 0;
    set_animation(requested_action);
    set_field_b8(requested_action);
    init_collision_body_parts(this, &shark_collision_bodies[subtype], 1);
    bind_enemy_combat_stats(reinterpret_cast<u8 *>(shark_combat_stats[subtype]),
        reinterpret_cast<u8 *>(shark_attack_stats[subtype]), reinterpret_cast<u8 *>(shark_resistance_stats[subtype]));
    movementParameters = &shark_movement_parameters[subtype];
    referenceHp = hp;
    update_prev_position();
    copy_body_to_center();
    initialize_enemy_photon_effect(this);
    m_2ac = (s32)(shark_angle_units_per_degree * (shark_full_circle_degrees * random_ratio()));
    resetTimer = 0xF;
    timer = resetTimer;
    phase = 0;
    m_374 = 0;
    m_376 = 0;
    m_378 = 0;
    m_37c = 0;
    add_flags_2e4(2);
    actorFlags |= 0x40000;
    if (TObjEneDD::check_v2_mode() != 0) {
        switch (subtype) {
        case 0:
        default:
            color = 0xFF20FF20;
            break;
        case 1:
            color = 0xFFFF0040;
            break;
        case 2:
            color = 0xFFFFFF00;
            break;
        }
    } else {
        switch (subtype) {
        default:
            color = 0xFF0000FF;
            break;
        case 1:
            color = 0xFFFF0000;
            break;
        case 2:
            color = 0xFFFFFF00;
            break;
        }
    }
    appearance_fade.reset_obstruction_fade();
    m_390 = 1;
    attack_trails[0] = TUnk_80494968::create((u32)0xA0303030, (u32)color);
    attack_trails[1] = TUnk_80494968::create((u32)0xA0303030, (u32)color);
    m_398 = shark_movement_parameter_sets[subtype][0];
    m_3a0 = shark_movement_parameter_sets[subtype][1];
    unk_39C = shark_movement_parameter_sets[subtype][2];
    unk_3A4 = shark_movement_parameter_sets[subtype][3];
    for (i = 0; i < 4; i++) {
        camera_fades[i].activate_and_dispatch();
    }
    clear_lobby_object_state();
}

extern "C" {
BattleBaseStats **shark_combat_stats;
AttackParams **shark_attack_stats;
ActorParamBlock **shark_resistance_stats;
f32 **shark_movement_parameter_sets;
BmlResource *shark_bml_resource;
SampledMotionPoints *shark_attack3_trail_buffer;
SampledMotionPoints *shark_attack4_trail_buffer;
s32 shark_render_node_index;

extern __declspec(section ".sdata2") const f32 shark_zero = 0.0f;
extern __declspec(section ".sdata2") const f32 shark_ground_effect_y = 10.0f;
extern __declspec(section ".sdata2") const f32 shark_ground_effect_height_factor = 0.5f;
extern __declspec(section ".sdata2") const f32 shark_attack_trail_end_frame = 12.0f;
extern __declspec(section ".sdata2") const f32 shark_near_view_depth = 200.0f;
extern __declspec(section ".sdata2") const f32 shark_far_view_depth = 400.0f;
extern __declspec(section ".sdata2") const f32 shark_view_radius = 30.0f;
extern __declspec(section ".sdata2") const f32 shark_shadow_scale_x = 1.5f;
extern __declspec(section ".sdata2") const f32 shark_one = 1.0f;
extern __declspec(section ".sdata2") const f32 shark_shadow_scale_z = 2.0f;
extern __declspec(section ".sdata2") const f32 shark_attack_trail_start_frame = 7.0f;
extern __declspec(section ".sdata2") const f32 shark_npc_collision_radius = 7.5f;
extern __declspec(section ".sdata2") const f32 shark_angle_units_per_degree = 182.04445f;
extern __declspec(section ".sdata2") const f32 shark_full_circle_degrees = 360.0f;
}
